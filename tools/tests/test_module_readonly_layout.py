"""Pure extraction-ownership tests. No compiler, ROM or worker is required."""
from pathlib import Path
import copy
import hashlib
import importlib.util
import json
import struct
import tempfile
import unittest

PROJECT = Path(__file__).resolve().parents[2]
spec = importlib.util.spec_from_file_location('moduleReadonlyLayout', PROJECT / 'tools/moduleReadonlyLayout.py')
tool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tool)
CONFIG = 'config/us/readonly_layout/uvdyn_rom.json'


def v1_fixture(layout):
    """Keep the original one-table tests independent of the project's V2 config."""
    if layout['version'] == 1:
        return layout
    common = {k: v for k, v in layout.items() if k not in ('tables', 'late_spans')}
    return dict(common, **layout['tables'][-1],
                **{k: v for k, v in layout['late_spans'][-1].items() if k.startswith('host_') and k != 'host_address'},
                version=1)



def v2_fixture(layout):
    """Keep accepted two-table regression cases independent of the V3 config."""
    layout = copy.deepcopy(layout)
    if layout['version'] == 3:
        layout['version'] = 2
        layout['tables'] = [layout['tables'][0], layout['tables'][-1]]
        layout['late_spans'] = [layout['late_spans'][0], layout['late_spans'][-1]]
        layout['late_spans'][0]['end'] = layout['tables'][1]['table_begin']
    return layout

class LayoutTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='readonly-layout-test-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.layout = v1_fixture(json.loads((PROJECT / CONFIG).read_text(encoding='utf-8')))
        self.write(self.layout['witness'], (PROJECT / self.layout['witness']).read_bytes())
        witness = (PROJECT / self.layout['witness']).read_text(encoding='utf-8')
        self.original = tool.original_bytes(witness, self.layout['begin'], self.layout['end'])
        # This is only a synthetic file fixture for extraction guards; these
        # instructions are never compiled or proposed as recovered game code.
        self.layout['host_bytes'] = 256
        self.host = ('nonmatching ' + self.layout['host_symbol'] + ', 0x100\n\n'
                     + 'glabel ' + self.layout['host_symbol'] + '\n'
                     + ''.join('    /* %06X %08X 00000000 */ nop\n' % (i*4, 0x4050EC+i*4) for i in range(64))
                     + 'endlabel ' + self.layout['host_symbol'] + '\n').encode('utf-8')
        self.layout['host_sha256'] = hashlib.sha256(self.host).hexdigest()
        self.write(self.layout['host_assembly'], self.host)
        self.write(self.layout['source'], ('#pragma GLOBAL_ASM("' + self.layout['prefix_assembly'] + '")\n'
                    + 'void ' + self.layout['owner_c_symbol'] + '(void) { }\n'
                    + '#pragma GLOBAL_ASM("' + self.layout['host_assembly'] + '")\n').encode())
        self.write(self.layout['monolithic_assembly'], witness.encode('utf-8'))
        begin = witness.index('nonmatching ' + self.layout['table_label'] + '\n')
        end = witness.index('enddlabel ' + self.layout['table_label'], begin) + len('enddlabel ' + self.layout['table_label'])
        self.write(self.layout['duplicate_assembly'], ('.section .rodata\n' + witness[begin:end] + '\n').encode())
        self.raw = bytearray(0x50 + (self.layout['begin'] - 0x400000) + len(self.original))
        self.raw[:4], self.raw[8:12], self.raw[0x18:0x1C] = b'FORM', b'MODU', b'COMM'
        struct.pack_into('>II', self.raw, 0x28, self.layout['begin'] - 0x400000, len(self.original))
        self.raw[-len(self.original):] = self.original
        self.binary = self.write('patched_modules/uvdyn_rom.uvmo', self.raw)
        self.save_config()

    def write(self, relative, raw):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(raw)
        return path

    def save_config(self):
        self.write(CONFIG, (json.dumps(self.layout) + '\n').encode())

    def prepare(self):
        return tool.prepare(self.root, CONFIG, 'uvdyn_rom', self.binary)

    def outputs(self):
        return {p.relative_to(self.root).as_posix(): p.read_bytes() for p in self.root.rglob('*') if p.is_file()}

    def rejected_unchanged(self, action):
        before = self.outputs()
        with self.assertRaises((ValueError, KeyError)):
            action()
        self.assertEqual(before, self.outputs())

    def test_original_exact_split_and_repeated_extraction(self):
        plan = self.prepare()
        tool.apply(plan)
        first = self.outputs()
        self.assertFalse((self.root / self.layout['monolithic_assembly']).exists())
        raw_host = (self.root / self.layout['host_assembly']).read_bytes()
        self.assertTrue(raw_host.startswith(self.host + tool.SUFFIX_MARKER))
        self.assertEqual(tool.host_text(self.layout, raw_host, plan['suffix']), self.host)
        self.assertEqual(len(self.original[:588]) + len(self.original[668:]), 800)
        self.assertEqual(tool.original_bytes(plan['prefix'].decode('utf-8'), self.layout['begin'], self.layout['table_begin']), self.original[:588])
        self.assertEqual(tool.original_bytes(plan['suffix'].decode('utf-8'), self.layout['table_end'], self.layout['end']), self.original[668:])
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())
        # Model the ordinary disassembler rerendering its untouched host; the
        # ownership hook must reproduce exactly the same final files again.
        self.write(self.layout['host_assembly'], self.host)
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())

    def test_fresh_generated_host(self):
        (self.root / self.layout['host_assembly']).unlink()
        plan = self.prepare()
        self.write(self.layout['host_assembly'], self.host)
        tool.apply(plan)
        self.assertTrue((self.root / self.layout['host_assembly']).read_bytes().startswith(self.host))

    def test_changed_module_bytes_rejected_before_writes(self):
        self.raw[-1] ^= 1
        self.binary.write_bytes(self.raw)
        self.rejected_unchanged(self.prepare)

    def test_changed_original_host_rejected_before_writes(self):
        self.write(self.layout['host_assembly'], self.host.replace(b'00000000', b'00000001', 1))
        self.rejected_unchanged(self.prepare)

    def test_host_migration_to_c_rejected_before_writes(self):
        source = (self.root / self.layout['source']).read_bytes()
        host_pragma = ('#pragma GLOBAL_ASM("' + self.layout['host_assembly'] + '")').encode()
        self.write(self.layout['source'], source.replace(host_pragma, ('void ' + self.layout['host_symbol'] + '(void) {}').encode()))
        self.rejected_unchanged(self.prepare)

    def test_extra_table_user_rejected_before_writes(self):
        self.write('src/modules/other.c', ('extern int *' + self.layout['table_label'] + ';\n').encode())
        self.rejected_unchanged(self.prepare)

    def test_conditional_host_cannot_evade_migration_guard(self):
        path = self.root / self.layout['source']
        source = path.read_text(encoding='utf-8')
        pragma = '#pragma GLOBAL_ASM("' + self.layout['host_assembly'] + '")'
        path.write_bytes(source.replace(pragma, '#if 0\n' + pragma + '\n#endif').encode())
        self.rejected_unchanged(self.prepare)

    def test_source_order_cannot_move_host_ahead_of_table(self):
        prefix = '#pragma GLOBAL_ASM("' + self.layout['prefix_assembly'] + '")\n'
        host = '#pragma GLOBAL_ASM("' + self.layout['host_assembly'] + '")\n'
        self.write(self.layout['source'], (prefix + host + 'void ' + self.layout['owner_c_symbol'] + '(void) {}\n').encode())
        self.rejected_unchanged(self.prepare)

    def test_conditional_or_duplicate_owner_rejected(self):
        path = self.root / self.layout['source']
        original = path.read_text(encoding='utf-8')
        definition = 'void ' + self.layout['owner_c_symbol'] + '(void) { }'
        for replacement in ('#if 0\n' + definition + '\n#endif', definition + '\n' + definition,
                            '/* ' + definition + ' */'):
            with self.subTest(replacement=replacement):
                path.write_bytes(original.replace(definition, replacement).encode())
                self.rejected_unchanged(self.prepare)

    def test_duplicate_is_not_ignored_if_executable(self):
        p = self.root / self.layout['duplicate_assembly']
        p.write_bytes(p.read_bytes().replace(b'enddlabel', b'nop\nenddlabel'))
        self.rejected_unchanged(self.prepare)

    def add_synthetic_unused_owner(self, name):
        self.layout['owner_bytes'] = 16
        raw = ('nonmatching ' + name + ', 0x10\n\n' + 'glabel ' + name + ' # 32\n'
               + ''.join('    /* %06X %08X 00000000 */ nop\n' % (0x4430+i*4, self.layout['owner_address']+i*4) for i in range(4))
               + 'endlabel ' + name + '\n')
        self.layout['owner_instruction_sha256'] = tool.sha(bytes(16))
        self.layout['owner_asm_normalized_sha256'] = tool.sha(tool.normalized_owner_asm(raw, name).encode())
        self.save_config()
        relative = 'asm/us/nonmatchings/modules/' + self.layout['module'] + '/' + name + '.s'
        return self.write(relative, raw.encode())

    def test_exact_unused_owner_under_both_names_allowed(self):
        self.add_synthetic_unused_owner(self.layout['owner_original_symbol'])
        self.add_synthetic_unused_owner(self.layout['owner_c_symbol'])
        self.prepare()

    def test_unused_owner_changed_operand_or_instruction_rejected(self):
        path = self.add_synthetic_unused_owner(self.layout['owner_c_symbol'])
        original = path.read_bytes()
        for altered in (original.replace(b'nop', b'addiu $v0, $zero, 1', 1),
                        original.replace(b'00000000', b'00000001', 1), original + b'.word 0\n'):
            with self.subTest(altered=altered):
                path.write_bytes(altered)
                self.rejected_unchanged(self.prepare)

    def test_semantic_owner_asm_must_be_unreferenced(self):
        path = self.add_synthetic_unused_owner(self.layout['owner_c_symbol'])
        source = self.root / self.layout['source']
        source.write_bytes(source.read_bytes() + ('#pragma GLOBAL_ASM("' + path.relative_to(self.root).as_posix() + '")\n').encode())
        self.rejected_unchanged(self.prepare)

    def test_unrecognised_monolithic_file_not_deleted(self):
        self.write(self.layout['monolithic_assembly'], b'local unrelated content\n')
        self.rejected_unchanged(self.prepare)

    def test_modified_managed_suffix_rejected(self):
        tool.apply(self.prepare())
        p = self.root / self.layout['host_assembly']
        p.write_bytes(p.read_bytes() + b'nop\n')
        self.rejected_unchanged(self.prepare)

    def test_metadata_boundary_and_path_guards(self):
        baseline = copy.deepcopy(self.layout)
        cases = [('version', 2), ('table_begin', baseline['begin']), ('table_end', baseline['end'] + 4),
                 ('prefix_assembly', '../escape.s'), ('prefix_assembly', 'asm/us/data/modules/bad.rodata.s'),
                 ('host_sha256', 'not-a-hash'), ('module', 'other')]
        for name, value in cases:
            with self.subTest(name=name, value=value):
                self.layout = copy.deepcopy(baseline)
                self.layout[name] = value
                self.save_config()
                self.rejected_unchanged(self.prepare)

    def test_witness_change_and_incomplete_coverage(self):
        witness = self.root / self.layout['witness']
        witness.write_bytes(witness.read_bytes() + b'\n')
        self.rejected_unchanged(self.prepare)
        with self.assertRaises(ValueError):
            tool.original_bytes('/* 0000 00411A20 00000000 */ .word 0x00000000\n', 0x411A20, 0x411A28)


class MultiLayoutTests(unittest.TestCase):
    write = LayoutTests.write
    save_config = LayoutTests.save_config
    prepare = LayoutTests.prepare
    outputs = LayoutTests.outputs
    rejected_unchanged = LayoutTests.rejected_unchanged

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='readonly-multi-test-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.layout = v2_fixture(json.loads((PROJECT / CONFIG).read_text(encoding='utf-8')))
        self.assertEqual(self.layout['version'], 2)
        witness = (PROJECT / self.layout['witness']).read_bytes()
        self.write(self.layout['witness'], witness)
        self.original = tool.original_bytes(witness.decode(), self.layout['begin'], self.layout['end'])
        source = '#pragma GLOBAL_ASM("' + self.layout['prefix_assembly'] + '")\n'
        self.hosts = {}
        for table, span in zip(self.layout['tables'], self.layout['late_spans']):
            # Synthetic guard fixtures only; never game-code recovery candidates.
            span['host_bytes'] = 256
            raw = ('nonmatching ' + span['host_symbol'] + ', 0x100\n\n'
                   + 'glabel ' + span['host_symbol'] + '\n'
                   + ''.join('    /* %06X %08X 00000000 */ nop\n' %
                             (i * 4, span['host_address'] + i * 4) for i in range(64))
                   + 'endlabel ' + span['host_symbol'] + '\n').encode()
            span['host_sha256'] = tool.sha(raw)
            self.hosts[span['host_assembly']] = raw
            self.write(span['host_assembly'], raw)
            source += ('void ' + table['owner_c_symbol'] + '(void) { }\n'
                       + '#pragma GLOBAL_ASM("' + span['host_assembly'] + '")\n')
            text = witness.decode()
            a = text.index('nonmatching ' + table['table_label'] + '\n')
            b = text.index('enddlabel ' + table['table_label'], a) + len('enddlabel ' + table['table_label'])
            self.write(table['duplicate_assembly'], ('.section .rodata\n' + text[a:b] + '\n').encode())
        self.write(self.layout['source'], source.encode())
        self.write(self.layout['monolithic_assembly'], witness)
        raw = bytearray(0x50 + self.layout['begin'] - 0x400000 + len(self.original))
        raw[:4], raw[8:12], raw[0x18:0x1C] = b'FORM', b'MODU', b'COMM'
        struct.pack_into('>II', raw, 0x28, self.layout['begin'] - 0x400000, len(self.original))
        raw[-len(self.original):] = self.original
        self.binary = self.write('patched_modules/uvdyn_rom.uvmo', raw)
        self.save_config()

    def test_exact_spans_and_repeated_regeneration_preserve_c(self):
        source = (self.root / self.layout['source']).read_bytes()
        plan = self.prepare()
        tool.apply(plan)
        first = self.outputs()
        self.assertEqual((self.root / self.layout['source']).read_bytes(), source)
        self.assertEqual(tool.original_bytes(plan['prefix'].decode(), 0x411A20, 0x411B1C), self.original[:252])
        for table, span in zip(self.layout['tables'], self.layout['late_spans']):
            fragment = plan['suffix'][span['host_assembly']]
            self.assertEqual(tool.original_bytes(fragment.decode(), span['begin'], span['end']),
                             self.original[span['begin'] - self.layout['begin']:span['end'] - self.layout['begin']])
            self.assertEqual((self.root / span['host_assembly']).read_bytes(),
                             self.hosts[span['host_assembly']] + tool.SUFFIX_MARKER + fragment)
        self.assertEqual(252 + 224 + 212, 688)
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())
        # Ordinary extraction rerenders both original hosts and monolithic data.
        for name, raw in self.hosts.items():
            self.write(name, raw)
        self.write(self.layout['monolithic_assembly'], (self.root / self.layout['witness']).read_bytes())
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())
        self.assertEqual((self.root / self.layout['source']).read_bytes(), source)

    def test_both_fresh_hosts_are_required_before_first_write(self):
        for name in self.hosts:
            (self.root / name).unlink()
        plan = self.prepare()
        self.rejected_unchanged(lambda: tool.apply(plan))
        for name, raw in self.hosts.items():
            self.write(name, raw)
        tool.apply(plan)

    def test_exact_v1_prefix_migrates_but_changed_prefix_is_rejected(self):
        witness = (self.root / self.layout['witness']).read_text()
        old_prefix = tool.render(dict(self.layout, **self.layout['tables'][-1]), witness)[0]
        prefix = self.write(self.layout['prefix_assembly'], old_prefix)
        plan = self.prepare()
        tool.apply(plan)
        self.assertEqual(prefix.read_bytes(), plan['prefix'])
        self.assertNotEqual(old_prefix, plan['prefix'])
        prefix.write_bytes(old_prefix + b'.section .text\nnop\n')
        self.rejected_unchanged(self.prepare)

    def test_bad_coverage_ownership_and_paths_rejected(self):
        original = copy.deepcopy(self.layout)
        changes = [lambda x: x['late_spans'][0].update(begin=0x411B90),
                   lambda x: x['late_spans'][0].update(end=0x411C68),
                   lambda x: x['tables'][1].update(table_begin=0x411C70),
                   lambda x: x['tables'][0].update(table_end=0x411B90),
                   lambda x: x['tables'][0].update(owner_address=0x403C3C),
                   lambda x: x['tables'][0].update(owner_bytes=4),
                   lambda x: x['tables'][1].update(owner_c_symbol=x['tables'][0]['owner_c_symbol']),
                   lambda x: x['late_spans'][0].update(host_assembly=x['late_spans'][1]['host_assembly']),
                   lambda x: x['tables'][0].update(duplicate_assembly='../escape.s'),
                   lambda x: x['late_spans'][0].update(host_address=0x403C38),
                   lambda x: x['late_spans'][0].update(host_bytes=4),
                   lambda x: x['tables'].reverse(),
                   lambda x: x['late_spans'].pop(),
                   lambda x: x.update(undeclared=True)]
        for change in changes:
            with self.subTest(change=change):
                self.layout = copy.deepcopy(original)
                change(self.layout)
                self.save_config()
                self.rejected_unchanged(self.prepare)

    def test_owner_and_host_source_order_and_conditionals_rejected(self):
        source_path = self.root / self.layout['source']
        original = source_path.read_text()
        first, second = self.layout['tables']
        owner = 'void ' + first['owner_c_symbol'] + '(void) { }'
        host = '#pragma GLOBAL_ASM("' + self.layout['late_spans'][0]['host_assembly'] + '")'
        modifications = [original.replace(owner, '#if 0\n' + owner + '\n#endif'),
                         original.replace(owner, owner + '\n' + owner),
                         original.replace(host, '#if 0\n' + host + '\n#endif'),
                         original.replace(host, 'void migrated_host(void) {}'),
                         original.replace(host + '\n', '').replace('void ' + second['owner_c_symbol'], host + '\nvoid ' + second['owner_c_symbol'])]
        # Move the middle host after the second owner instead of immediately before.
        modifications[-1] = original.replace(host + '\n', '') + host + '\n'
        for changed in modifications:
            with self.subTest(changed=changed):
                source_path.write_bytes(changed.encode())
                self.rejected_unchanged(self.prepare)

    def test_real_and_unused_table_source_references_rejected(self):
        source = self.root / self.layout['source']
        original = source.read_bytes()
        for table in self.layout['tables']:
            for text in ('extern void *%s;\n', 'void *read_table(void) { return %s; }\n'):
                with self.subTest(table=table['table_label'], text=text):
                    source.write_bytes(original + (text % table['table_label']).encode())
                    self.rejected_unchanged(self.prepare)

    def test_changed_duplicate_and_managed_middle_rejected(self):
        duplicate = self.root / self.layout['tables'][0]['duplicate_assembly']
        original = duplicate.read_bytes()
        duplicate.write_bytes(original.replace(b'enddlabel', b'nop\nenddlabel'))
        self.rejected_unchanged(self.prepare)
        duplicate.write_bytes(original)
        tool.apply(self.prepare())
        middle = self.root / self.layout['late_spans'][0]['host_assembly']
        middle.write_bytes(middle.read_bytes() + b'.word 0\n')
        self.rejected_unchanged(self.prepare)

    def test_host_original_operand_change_is_rejected(self):
        host = self.root / self.layout['late_spans'][0]['host_assembly']
        host.write_bytes(host.read_bytes().replace(b'nop', b'addiu $v0, $zero, 1', 1))
        self.rejected_unchanged(self.prepare)

    def test_original_and_semantic_owner_asm_exemptions_are_exact(self):
        table = self.layout['tables'][0]
        name = table['owner_original_symbol']
        raw = ('nonmatching ' + name + ', 0x158\n\nglabel ' + name + ' # 26\n'
               + ''.join('    /* %06X %08X 00000000 */ nop\n' %
                         (i * 4, table['owner_address'] + i * 4) for i in range(86))
               + 'endlabel ' + name + '\n')
        table['owner_instruction_sha256'] = tool.sha(bytes(344))
        table['owner_asm_normalized_sha256'] = tool.sha(tool.normalized_owner_asm(raw, name).encode())
        self.save_config()
        folder = 'asm/us/nonmatchings/modules/uvdyn_rom/'
        self.write(folder + name + '.s', raw.encode())
        path = self.write(folder + table['owner_c_symbol'] + '.s', raw.replace(name, table['owner_c_symbol']).encode())
        self.prepare()
        path.write_bytes(path.read_bytes().replace(b'nop', b'addiu $v0, $zero, 1', 1))
        self.rejected_unchanged(self.prepare)




class AdjacentLayoutTests(unittest.TestCase):
    write = LayoutTests.write
    save_config = LayoutTests.save_config
    prepare = LayoutTests.prepare
    outputs = LayoutTests.outputs
    rejected_unchanged = LayoutTests.rejected_unchanged

    def setUp(self):
        layout = json.loads((PROJECT / CONFIG).read_text(encoding='utf-8'))
        self.assertEqual(layout['version'], 3)
        MultiLayoutTests.setUp(self)
        old = self.layout
        for span, previous in zip((layout['late_spans'][0], layout['late_spans'][-1]), old['late_spans']):
            span['host_bytes'] = previous['host_bytes']
            span['host_sha256'] = previous['host_sha256']
        self.layout = layout
        source = self.root / layout['source']
        text = source.read_text()
        new_owner = 'void ' + layout['tables'][1]['owner_c_symbol'] + '(void) { }\n'
        last_owner = 'void ' + layout['tables'][2]['owner_c_symbol']
        source.write_bytes(text.replace(last_owner, new_owner + last_owner).encode())
        table = layout['tables'][1]
        witness = (self.root / layout['witness']).read_text()
        start = witness.index('nonmatching ' + table['table_label'] + '\n')
        stop = witness.index('enddlabel ' + table['table_label'], start) + len('enddlabel ' + table['table_label'])
        self.write(table['duplicate_assembly'], ('.section .rodata\n' + witness[start:stop] + '\n').encode())
        self.save_config()

    def test_adjacent_tables_exact_880_byte_composition_and_c_identity(self):
        source = (self.root / self.layout['source']).read_bytes()
        plan = self.prepare()
        self.assertEqual(len(plan['suffix']), 2)
        self.assertIsNone(self.layout['late_spans'][1])
        self.assertEqual(self.layout['tables'][1]['table_begin'] % 8, 0)
        self.assertEqual(self.layout['tables'][1]['table_end'] % 8, 4)
        self.assertEqual(252 + 112 + 148 + 76 + 80 + 212, 880)
        middle = self.layout['late_spans'][0]
        self.assertEqual(tool.original_bytes(plan['suffix'][middle['host_assembly']].decode(),
                                            0x411B8C, 0x411C20), self.original[364:512])
        tool.apply(plan)
        first = self.outputs()
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())
        # Ordinary extraction replaces only the two real original ASM hosts.
        for name, raw in self.hosts.items():
            self.write(name, raw)
        self.write(self.layout['monolithic_assembly'], (self.root / self.layout['witness']).read_bytes())
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())
        self.assertEqual(source, (self.root / self.layout['source']).read_bytes())

    def previous_middle(self):
        witness = (self.root / self.layout['witness']).read_text()
        bounds = tool.v3_witness_bounds(self.layout, witness)
        span = self.layout['late_spans'][0]
        return tool.v3_fragment(span['begin'], witness[bounds[0][1]:bounds[2][0]])

    def test_native_alignment_phase_does_not_add_data(self):
        text = '/* 000000 00411C20 12345678 */ .word 0x12345678\n'
        aligned = tool.v3_fragment(0x411C20, text)
        word_aligned = tool.v3_fragment(0x411C24, text.replace('00411C20', '00411C24'))
        self.assertTrue(aligned.startswith(b'.section .late_rodata\n.late_rodata_alignment 8\n'))
        self.assertTrue(word_aligned.startswith(b'.section .late_rodata\n.late_rodata_alignment 4\n'))
        self.assertEqual(tool.original_bytes(aligned.decode(), 0x411C20, 0x411C24), bytes.fromhex('12345678'))
        self.assertEqual(tool.original_bytes(word_aligned.decode(), 0x411C24, 0x411C28), bytes.fromhex('12345678'))

    def test_exact_previous_v2_middle_migrates_without_hiding_a_user(self):
        span = self.layout['late_spans'][0]
        previous = self.previous_middle()
        self.assertEqual(tool.original_bytes(previous.decode(), 0x411B8C, 0x411C6C), self.original[364:588])
        self.write(span['host_assembly'], self.hosts[span['host_assembly']] + tool.SUFFIX_MARKER + previous)
        tool.apply(self.prepare())
        migrated = (self.root / span['host_assembly']).read_bytes()
        self.assertNotIn(b'D_uvdyn_rom_00411C20', migrated)
        self.write('src/modules/real.c', b'void *read(void) { return D_uvdyn_rom_00411C20; }\n')
        self.rejected_unchanged(self.prepare)

    def test_previous_middle_transition_rejects_changed_data_or_code(self):
        span = self.layout['late_spans'][0]
        raw = self.hosts[span['host_assembly']] + tool.SUFFIX_MARKER + self.previous_middle()
        for bad in (raw + b'nop\n', raw.replace(b'.word .Luvdyn_rom_00404054', b'.word .Luvdyn_rom_00404078', 1),
                    raw.replace(tool.SUFFIX_MARKER, tool.SUFFIX_MARKER + tool.SUFFIX_MARKER, 1)):
            with self.subTest(bad=bad):
                self.write(span['host_assembly'], bad)
                self.rejected_unchanged(self.prepare)

    def test_null_span_requires_exact_adjacency_and_no_fake_host(self):
        original = copy.deepcopy(self.layout)
        changes = [lambda x: x['late_spans'].__setitem__(0, None),
                   lambda x: x['late_spans'].__setitem__(-1, None),
                   lambda x: x['late_spans'].__setitem__(1, dict(x['late_spans'][0], begin=0x411C6C, end=0x411C6C)),
                   lambda x: x['tables'][1].update(table_end=0x411C68),
                   lambda x: x['tables'][2].update(table_begin=0x411C70)]
        for change in changes:
            with self.subTest(change=change):
                self.layout = copy.deepcopy(original)
                change(self.layout)
                self.save_config()
                self.rejected_unchanged(self.prepare)

    def test_word_alignment_and_original_table_targets_remain_strict(self):
        original = copy.deepcopy(self.layout)
        for change in [lambda x: x['tables'][1].update(table_begin=0x411C22),
                       lambda x: x['tables'][1].update(table_end=0x411C6E),
                       lambda x: x['tables'][1].update(owner_address=0x40401C),
                       lambda x: x['tables'][1].update(owner_bytes=4),
                       lambda x: x['tables'][1].update(duplicate_assembly='../outside.s')]:
            with self.subTest(change=change):
                self.layout = copy.deepcopy(original)
                change(self.layout)
                self.save_config()
                self.rejected_unchanged(self.prepare)

    def test_adjacent_owner_still_requires_one_unconditional_c_definition(self):
        path = self.root / self.layout['source']
        original = path.read_text()
        owner = 'void ' + self.layout['tables'][1]['owner_c_symbol'] + '(void) { }'
        for changed in ('#if 0\n' + owner + '\n#endif', owner + '\n' + owner, '/* ' + owner + ' */'):
            with self.subTest(changed=changed):
                path.write_bytes(original.replace(owner, changed).encode())
                self.rejected_unchanged(self.prepare)

    def test_every_table_real_reference_is_rejected(self):
        path = self.root / self.layout['source']
        original = path.read_bytes()
        for table in self.layout['tables']:
            for extra in ('extern void *%s;\n', 'void *read(void) { return %s; }\n'):
                with self.subTest(table=table['table_label'], extra=extra):
                    path.write_bytes(original + (extra % table['table_label']).encode())
                    self.rejected_unchanged(self.prepare)

    def test_both_real_host_migrations_and_reordering_are_rejected(self):
        path = self.root / self.layout['source']
        original = path.read_text()
        for span in self.layout['late_spans']:
            if span is None:
                continue
            pragma = '#pragma GLOBAL_ASM("' + span['host_assembly'] + '")'
            for changed in ('#if 0\n' + pragma + '\n#endif', 'void migrated(void) {}'):
                with self.subTest(pragma=pragma, changed=changed):
                    path.write_bytes(original.replace(pragma, changed).encode())
                    self.rejected_unchanged(self.prepare)
        first, second = self.layout['tables'][1:]
        a = 'void ' + first['owner_c_symbol'] + '(void) { }'
        b = 'void ' + second['owner_c_symbol'] + '(void) { }'
        path.write_bytes(original.replace(a, 'REPLACE_OWNER').replace(b, a).replace('REPLACE_OWNER', b).encode())
        self.rejected_unchanged(self.prepare)

    def test_new_duplicate_cannot_hide_instructions(self):
        path = self.root / self.layout['tables'][1]['duplicate_assembly']
        path.write_bytes(path.read_bytes().replace(b'enddlabel', b'nop\nenddlabel'))
        self.rejected_unchanged(self.prepare)

    def test_new_owner_original_and_semantic_asm_guards(self):
        table = self.layout['tables'][1]
        name = table['owner_original_symbol']
        raw = ('nonmatching ' + name + ', 0x1B4\n\nglabel ' + name + ' # 29\n'
               + ''.join('    /* %06X %08X 00000000 */ nop\n' %
                         (i * 4, table['owner_address'] + i * 4) for i in range(109))
               + 'endlabel ' + name + '\n')
        table['owner_instruction_sha256'] = tool.sha(bytes(436))
        table['owner_asm_normalized_sha256'] = tool.sha(tool.normalized_owner_asm(raw, name).encode())
        self.save_config()
        folder = 'asm/us/nonmatchings/modules/uvdyn_rom/'
        self.write(folder + name + '.s', raw.encode())
        path = self.write(folder + table['owner_c_symbol'] + '.s', raw.replace(name, table['owner_c_symbol']).encode())
        self.prepare()
        path.write_bytes(path.read_bytes().replace(b'nop', b'addiu $v0, $zero, 1', 1))
        self.rejected_unchanged(self.prepare)

    def test_missing_or_changed_patched_module_rejected(self):
        self.binary.write_bytes(self.binary.read_bytes()[:-1])
        self.rejected_unchanged(self.prepare)

class TerminalLayoutTests(unittest.TestCase):
    """Synthetic ownership fixtures only; no game code or binary is fabricated."""
    write = LayoutTests.write
    save_config = LayoutTests.save_config
    prepare = LayoutTests.prepare
    outputs = LayoutTests.outputs
    rejected_unchanged = LayoutTests.rejected_unchanged

    def setUp(self):
        AdjacentLayoutTests.setUp(self)
        last = self.layout['tables'][-1]
        old_span = self.layout['late_spans'][-1]
        self.layout['end'] = last['table_end']
        self.layout['late_spans'][-1] = None
        path = self.root / self.layout['witness']
        witness = path.read_text()
        marker = 'enddlabel ' + last['table_label']
        witness = witness[:witness.index(marker) + len(marker)] + '\n'
        path.write_bytes(witness.encode())
        self.original = self.original[:self.layout['end'] - self.layout['begin']]
        self.layout['witness_sha256'] = tool.sha(path.read_bytes())
        self.layout['readonly_sha256'] = tool.sha(self.original)
        self.write(self.layout['monolithic_assembly'], path.read_bytes())
        source = self.root / self.layout['source']
        source.write_bytes(source.read_bytes().replace(
            ('#pragma GLOBAL_ASM("' + old_span['host_assembly'] + '")\n').encode(), b''))
        (self.root / old_span['host_assembly']).unlink()
        raw = bytearray(self.binary.read_bytes()[:0x50 + self.layout['begin'] - 0x400000])
        struct.pack_into('>I', raw, 0x2C, len(self.original))
        self.binary.write_bytes(raw + self.original)
        self.save_config()

    def test_terminal_table_has_no_fake_host_and_is_deterministic(self):
        plan = self.prepare()
        self.assertEqual(len(plan['suffix']), 1)
        self.assertIsNone(self.layout['late_spans'][-1])
        self.assertEqual(self.layout['tables'][-1]['table_end'], self.layout['end'])
        tool.apply(plan)
        first = self.outputs()
        tool.apply(self.prepare())
        self.assertEqual(first, self.outputs())

    def previous_suffix(self):
        witness = (self.root / self.layout['witness']).read_text()
        bounds = tool.v3_witness_bounds(self.layout, witness)
        return tool.v3_fragment(self.layout['late_spans'][0]['begin'], witness[bounds[0][1]:])

    def test_exact_previous_suffix_migrates_terminal_adjacent_tables(self):
        span = self.layout['late_spans'][0]
        path = self.root / span['host_assembly']
        path.write_bytes(self.hosts[span['host_assembly']] + tool.SUFFIX_MARKER + self.previous_suffix())
        tool.apply(self.prepare())
        self.assertNotIn(self.layout['tables'][-1]['table_label'].encode(), path.read_bytes())
        tool.apply(self.prepare())

    def test_terminal_transition_rejects_changed_bytes_code_or_extra_contents(self):
        span = self.layout['late_spans'][0]
        original = self.hosts[span['host_assembly']] + tool.SUFFIX_MARKER + self.previous_suffix()
        # Alter an actual table operand, an original instruction, or add data.
        suffix = self.previous_suffix()
        word = next(line for line in suffix.splitlines() if b'.word .L' in line)
        target = word.rsplit(b'_', 1)[1]
        changed_word = word[:-len(target)] + ('%08X' % (int(target, 16) + 4)).encode()
        for bad in (original.replace(word, changed_word, 1),
                    original.replace(b'nop', b'addiu $v0, $zero, 1', 1),
                    original + b'.word 0\n'):
            with self.subTest(bad=bad):
                self.write(span['host_assembly'], bad)
                self.rejected_unchanged(self.prepare)

    def test_terminal_gap_or_extra_witness_bytes_rejected(self):
        self.layout['end'] += 4
        self.save_config()
        self.rejected_unchanged(self.prepare)


if __name__ == '__main__':
    unittest.main()
