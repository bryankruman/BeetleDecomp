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


class LayoutTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='readonly-layout-test-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.layout = json.loads((PROJECT / CONFIG).read_text(encoding='utf-8'))
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


if __name__ == '__main__':
    unittest.main()
