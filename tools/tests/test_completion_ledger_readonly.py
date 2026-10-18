"""Verify explicit readonly ownership never hides unfinished instruction code."""
from pathlib import Path
import contextlib
import hashlib
import importlib.util
import io
import json
import sys
import unittest
from unittest import mock

import test_module_readonly_layout as fixtures
from test_module_readonly_layout import tool, CONFIG

PROJECT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PROJECT / 'tools'))
spec = importlib.util.spec_from_file_location('completion_ledger', PROJECT / 'tools/completion_ledger.py')
ledger = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ledger)


class LedgerTests(unittest.TestCase):
    write = fixtures.LayoutTests.write
    save_config = fixtures.LayoutTests.save_config
    prepare = fixtures.LayoutTests.prepare

    def setUp(self):
        fixtures.LayoutTests.setUp(self)
        self.write('config/us/modules.yaml', json.dumps({'Modules': [
            {'name': 'uvdyn_rom', 'done_sections': ['rodata'], 'readonly_layout': CONFIG}]}).encode())
        tool.apply(self.prepare())
        self.write('src/modules/code.c', b'#pragma GLOBAL_ASM("asm/code.s")\n'
                   b'#pragma GLOBAL_ASM("asm/__entrypoint_func_sample_00400000.s")\n'
                   b'void func_code_00401234(void) {}\n')
        self.write('asm/code.s', b'nonmatching example, 0x10\n')
        self.write('asm/__entrypoint_func_sample_00400000.s', b'nonmatching __entrypoint_func_sample_00400000, 0x8\n')
        rom = b'synthetic ROM-hash fixture; never compiled or accepted game output'
        self.write('build/beetleadventurerac.us.z64', rom)
        self.write('beetleadventurerac.us.sha1', (hashlib.sha1(rom).hexdigest() + '\n').encode())

    def test_only_declared_data_is_separated_from_instruction_counts(self):
        report = ledger.collect(self.root)
        self.assertEqual(report['assembly_references'], 3)
        self.assertEqual(report['ordinary_assembly_references'], 2)
        self.assertEqual(report['entrypoint_assembly_references'], 1)
        self.assertEqual(report['known_remaining_code_bytes'], 256 + 16 + 8)
        self.assertEqual(report['remaining_sizes_unknown'], 0)
        self.assertEqual(report['c_definitions_with_address_names'], 1)
        self.assertEqual(report['assembly_data_references'], 1)
        row = report['assembly_data'][0]
        self.assertEqual((row['bytes'], row['original_readonly_bytes'], row['retained_readonly_bytes']), (588, 880, 800))
        self.assertEqual(row['metadata'], CONFIG)
        self.assertEqual(len(report['remaining']), 3)
        self.assertNotIn(row, report['remaining'])

    def test_generic_rodata_filename_does_not_hide_a_function(self):
        self.write('src/modules/ordinary.c', b'#pragma GLOBAL_ASM("asm/function.rodata.s")\n')
        self.write('asm/function.rodata.s', b'nonmatching real_function, 0x20\n')
        report = ledger.collect(self.root)
        self.assertEqual(report['assembly_references'], 4)
        self.assertEqual(report['assembly_data_references'], 1)
        self.assertEqual(report['known_remaining_code_bytes'], 256 + 16 + 8 + 32)

    def test_missing_metadata_rejected(self):
        (self.root / CONFIG).unlink()
        with self.assertRaises((ValueError, FileNotFoundError)):
            ledger.collect(self.root)

    def test_missing_config_cannot_silently_reclassify_prefix(self):
        (self.root / 'config/us/modules.yaml').unlink()
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_changed_prefix_cannot_hide_instructions(self):
        path = self.root / self.layout['prefix_assembly']
        path.write_bytes(path.read_bytes() + b'.section .text\nnop\n')
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_changed_witness_or_bad_ownership_rejected(self):
        self.layout['readonly_sha256'] = '0' * 64
        self.save_config()
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_other_source_cannot_reuse_prefix_exemption(self):
        self.write('src/modules/other.c', ('#pragma GLOBAL_ASM("' + self.layout['prefix_assembly'] + '")\n').encode())
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_require_complete_still_checks_code_names_and_rom(self):
        report = ledger.collect(self.root)
        args = ['completion_ledger', '--root', str(self.root), '--require-complete']
        with mock.patch.object(sys, 'argv', args), contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(ledger.main(), 1)
        # Exercise the completion-policy predicate independently of this native
        # layout's still-assembly host. Declared retained data alone is not an
        # instruction-function debt; each real completion condition still gates.
        complete = dict(report, assembly_references=0, c_definitions_with_address_names=0, rom_matches=True)
        for field, value, expected in [(None, None, 0), ('assembly_references', 1, 1),
                                       ('c_definitions_with_address_names', 1, 1), ('rom_matches', False, 1)]:
            candidate = dict(complete)
            if field:
                candidate[field] = value
            with self.subTest(field=field), mock.patch.object(ledger, 'collect', return_value=candidate), \
                    mock.patch.object(sys, 'argv', args), contextlib.redirect_stdout(io.StringIO()):
                self.assertEqual(ledger.main(), expected)


class MultiLedgerTests(unittest.TestCase):
    write = fixtures.LayoutTests.write
    save_config = fixtures.LayoutTests.save_config
    prepare = fixtures.LayoutTests.prepare

    def setUp(self):
        fixtures.MultiLayoutTests.setUp(self)
        self.write('config/us/modules.yaml', json.dumps({'Modules': [
            {'name': 'uvdyn_rom', 'done_sections': ['rodata'], 'readonly_layout': CONFIG}]}).encode())
        tool.apply(self.prepare())
        self.write('beetleadventurerac.us.sha1', ('0' * 40 + '\n').encode())

    def test_two_tables_keep_one_data_reference_and_both_code_hosts(self):
        report = ledger.collect(self.root)
        self.assertEqual(report['assembly_references'], 2)
        self.assertEqual(report['known_remaining_code_bytes'], 512)
        self.assertEqual(report['remaining_sizes_unknown'], 0)
        self.assertEqual(report['assembly_data_references'], 1)
        row = report['assembly_data'][0]
        self.assertEqual((row['bytes'], row['original_readonly_bytes'], row['retained_readonly_bytes'],
                          row['compiler_owned_readonly_bytes']), (252, 880, 688, 192))

    def test_coverage_or_real_reference_cannot_hide_code(self):
        self.layout['late_spans'][0]['end'] -= 4
        self.save_config()
        with self.assertRaises(ValueError):
            ledger.collect(self.root)
        self.layout['late_spans'][0]['end'] += 4
        self.save_config()
        self.write('src/modules/reference.c', b'void *table(void) { return D_uvdyn_rom_00411B1C; }\n')
        with self.assertRaises(ValueError):
            ledger.collect(self.root)




class AdjacentLedgerTests(unittest.TestCase):
    write = fixtures.LayoutTests.write
    save_config = fixtures.LayoutTests.save_config
    prepare = fixtures.LayoutTests.prepare

    def setUp(self):
        fixtures.AdjacentLayoutTests.setUp(self)
        self.write('config/us/modules.yaml', json.dumps({'Modules': [
            {'name': 'uvdyn_rom', 'done_sections': ['rodata'], 'readonly_layout': CONFIG}]}).encode())
        tool.apply(self.prepare())
        self.write('beetleadventurerac.us.sha1', ('0' * 40 + '\n').encode())

    def test_three_owned_tables_keep_two_real_code_hosts_and_one_data_prefix(self):
        report = ledger.collect(self.root)
        self.assertEqual(report['assembly_references'], 2)
        self.assertEqual(report['known_remaining_code_bytes'], 512)
        self.assertEqual(report['remaining_sizes_unknown'], 0)
        self.assertEqual(report['assembly_data_references'], 1)
        row = report['assembly_data'][0]
        self.assertEqual((row['bytes'], row['original_readonly_bytes'], row['retained_readonly_bytes'],
                          row['compiler_owned_readonly_bytes']), (252, 880, 612, 268))

    def test_adjacent_data_cannot_conceal_a_function_or_real_table_user(self):
        self.write('src/modules/ordinary.c', b'#pragma GLOBAL_ASM("asm/function.rodata.s")\n')
        self.write('asm/function.rodata.s', b'nonmatching real_function, 0x20\n')
        report = ledger.collect(self.root)
        self.assertEqual(report['assembly_references'], 3)
        self.assertEqual(report['known_remaining_code_bytes'], 544)
        self.write('src/modules/reference.c', b'void *read(void) { return D_uvdyn_rom_00411C20; }\n')
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_broken_adjacency_and_missing_owned_table_rejected(self):
        self.layout['tables'][1]['table_end'] -= 4
        self.save_config()
        with self.assertRaises(ValueError):
            ledger.collect(self.root)



class TerminalLiteralLedgerTests(unittest.TestCase):
    """Synthetic guard/classification fixture; no recovered code is compiled."""
    def setUp(self):
        import tempfile
        self.temp = tempfile.TemporaryDirectory(prefix='terminal-ledger-test-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.layout = fixtures.natural_terminal_fixture113300(json.loads((PROJECT / CONFIG).read_text(encoding='utf-8')))
        self.assertIn('terminal_literal_tail', self.layout)
        def write(name, raw):
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(raw)
            return path
        self.write = write
        write(CONFIG, (json.dumps(self.layout, sort_keys=True, indent=2) + '\n').encode())
        for name in [self.layout['witness'], 'tools/readonly_layout/uvdyn_rom.original-rodata.s', 'Makefile']:
            write(name, (PROJECT / name).read_bytes())
        write('config/us/modules.yaml', json.dumps({'Modules': [{'name': 'uvdyn_rom', 'done_sections': ['rodata'], 'readonly_layout': CONFIG}]}).encode())
        _, decoded, prefix, suffix = tool.load(self.root, CONFIG, 'uvdyn_rom')
        write(self.layout['prefix_assembly'], prefix)
        tail = self.layout['terminal_literal_tail']
        write(tail['assembly'], suffix[tail['assembly']])
        # Existing real host declarations remain instruction debt. The fixture
        # deliberately has no host bodies, so their unknown sizes remain visible.
        source = '#pragma GLOBAL_ASM("' + self.layout['prefix_assembly'] + '")\n'
        for table, span in zip(self.layout['tables'], self.layout['late_spans']):
            source += 'void ' + table['owner_c_symbol'] + '(void) {}\n'
            if span is not None:
                source += '#pragma GLOBAL_ASM("' + span['host_assembly'] + '")\n'
        source += '#pragma GLOBAL_ASM("' + tail['assembly'] + '")\n'
        write(self.layout['source'], source.encode())
        write('beetleadventurerac.us.sha1', ('0' * 40 + '\n').encode())

    def test_terminal44_is_only_subordinate_data_and_hosts_remain_debt(self):
        report = ledger.collect(self.root)
        self.assertEqual(report['ordinary_assembly_references'], 2)
        self.assertEqual(report['remaining_sizes_unknown'], 2)
        self.assertEqual(report['known_remaining_code_bytes'], 0)
        self.assertEqual(report['assembly_data_references'], 1)
        row, = report['assembly_data']
        self.assertEqual((row['original_readonly_bytes'], row['compiler_owned_readonly_bytes'], row['retained_readonly_bytes']), (880, 364, 516))
        island, = row['retained_islands']
        self.assertEqual(island['bytes'], 44)
        self.assertEqual(island['assembly'], self.layout['terminal_literal_tail']['assembly'])

    def test_changed_terminal_data_cannot_be_reclassified(self):
        path = self.root / self.layout['terminal_literal_tail']['assembly']
        path.write_bytes(path.read_bytes() + b'.section .text\nnop\n')
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

    def test_undeclared_or_shared_tail_cannot_hide_a_function(self):
        self.write('src/modules/other.c', ('#pragma GLOBAL_ASM("' + self.layout['terminal_literal_tail']['assembly'] + '")\n').encode())
        with self.assertRaises(ValueError):
            ledger.collect(self.root)

if __name__ == '__main__':
    unittest.main()
