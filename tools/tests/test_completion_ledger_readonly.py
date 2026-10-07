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

from test_module_readonly_layout import LayoutTests, tool, CONFIG

PROJECT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(PROJECT / 'tools'))
spec = importlib.util.spec_from_file_location('completion_ledger', PROJECT / 'tools/completion_ledger.py')
ledger = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ledger)


class LedgerTests(unittest.TestCase):
    write = LayoutTests.write
    save_config = LayoutTests.save_config
    prepare = LayoutTests.prepare

    def setUp(self):
        LayoutTests.setUp(self)
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


if __name__ == '__main__':
    unittest.main()
