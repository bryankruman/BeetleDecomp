"""Exercise the real parser class without executing its unconditional CLI.

Only the module constants and ModuleFileParse class AST are loaded, so these
unit tests need neither spimdisasm nor command-line side effects. Method bodies
are compiled unchanged from tools/moduleFileDisasm.py, never reimplemented.
"""
import ast
import contextlib
import io
import os
from pathlib import Path
import struct
import unittest

SOURCE = Path(os.environ.get("MODULE_FILE_DISASM_SOURCE", Path(__file__).resolve().parents[1] / "tools/moduleFileDisasm.py"))

def load_parser():
    tree = ast.parse(SOURCE.read_text(encoding="utf-8"), filename=str(SOURCE))
    selected = [node for node in tree.body if
                isinstance(node, ast.AnnAssign) and isinstance(node.target, ast.Name) and node.target.id.startswith("MODULE_FILES_") or
                isinstance(node, ast.Assign) and all(isinstance(target, ast.Name) and target.id.startswith(("MIPS_", "INSTRUCTION_SECTION_", "SYM_SECTION_")) for target in node.targets) or
                isinstance(node, ast.ClassDef) and node.name == "ModuleFileParse"]
    assert sum(isinstance(node, ast.ClassDef) for node in selected) == 1
    namespace = {"struct": struct}
    exec(compile(ast.Module(body=selected, type_ignores=[]), str(SOURCE), "exec"), namespace)
    return namespace["ModuleFileParse"]

Parser = load_parser()

def encoded(site_section, symbol_section, kind, byte_offset):
    assert byte_offset % 2 == 0
    return (symbol_section << 28) | (site_section << 26) | (kind << 22) | (byte_offset >> 1)

def fixture(records, *, text=0x20, rodata=0x18, data=0x10, count=None):
    rela_offset = 0x50 + text + rodata + data + 0x28
    blob = bytearray(rela_offset + 8 + len(records) * 4)
    for offset, tag in [(0, b"FORM"), (8, b"MODU"), (12, b"PAD "), (24, b"COMM")]:
        blob[offset:offset+4] = tag
    struct.pack_into(">5I", blob, 0x28, text, rodata, data, 0, len(records) if count is None else count)
    blob[rela_offset:rela_offset+4] = b"RELA"
    struct.pack_into(">I", blob, rela_offset+4, len(records)*4)
    for index, value in enumerate(records):
        struct.pack_into(">I", blob, rela_offset+8+index*4, value)
    return blob, rela_offset

def scan(blob):
    parser = Parser(blob)
    with contextlib.redirect_stdout(io.StringIO()):
        parser.scanRela()
    return parser.relocs

class ModuleRelocationTests(unittest.TestCase):
    def test_distinct_text_data_rodata_site_bases_and_unchanged_fields(self):
        # Symbol-section ordering intentionally differs from site-section ordering.
        records = [encoded(0, 3, 1, 4), encoded(1, 1, 5, 8), encoded(2, 2, 6, 12)]
        rows = scan(fixture(records)[0])
        self.assertEqual([(row.romOffset, row.symSection, row.targetInstructionSection, row.relocType) for row in rows],
                         [(0x54, 3, 0, 1), (0x90, 1, 1, 5), (0x7C, 2, 2, 6)])

    def test_single_record_is_not_lost(self):
        rows = scan(fixture([encoded(0, 0, 2, 4)])[0])
        self.assertEqual(len(rows), 1)
        self.assertEqual(rows[0].romOffset, 0x54)

    def test_final_record_is_included(self):
        rows = scan(fixture([encoded(0, 0, 0, 0), encoded(0, 0, 1, 4)])[0])
        self.assertEqual([row.romOffset for row in rows], [0x50, 0x54])
        self.assertEqual(rows[-1].relocType, 1)

    def test_zero_records(self):
        self.assertEqual(scan(fixture([])[0]), [])

    def test_count_size_mismatch(self):
        for count in (0, 2):
            with self.subTest(count=count), self.assertRaisesRegex(ValueError, "size.*count"):
                scan(fixture([encoded(0, 0, 0, 0)], count=count)[0])

    def test_unaligned_size_rejected(self):
        blob, offset = fixture([encoded(0, 0, 0, 0)])
        struct.pack_into(">I", blob, offset+4, 3)
        with self.assertRaisesRegex(ValueError, "size.*count"):
            scan(blob)

    def test_truncated_rela_header(self):
        blob, offset = fixture([])
        for length in (offset, offset+4, offset+7):
            with self.subTest(length=length), self.assertRaisesRegex(ValueError, "RELA header"):
                scan(blob[:length])

    def test_truncated_rela_records(self):
        blob, _ = fixture([encoded(0, 0, 0, 0)])
        with self.assertRaisesRegex(ValueError, "RELA records"):
            scan(blob[:-1])

    def test_wrong_rela_tag(self):
        blob, offset = fixture([])
        blob[offset:offset+4] = b"NOPE"
        with self.assertRaisesRegex(ValueError, "RELA tag"):
            scan(blob)

    def test_existing_unknown_site_section_behavior_is_preserved(self):
        row = scan(fixture([encoded(3, 0, 0, 4)])[0])[0]
        self.assertEqual((row.romOffset, row.targetInstructionSection), (3, 3))

    def test_all_original_caranim_label_table_sites(self):
        # Original metadata only: 63 encoded RELA words from records532..594.
        # Native644B ELF/ROM witness: f59170de8f582ca3477305fc1a3a0eaa7a61f684b811257c7f37ff9ce6b2e5df.
        records = ORIGINAL_CARANIM_LABEL_RELOCATIONS
        rows = scan(fixture(records, text=0x61D0, rodata=0x660, data=0xB00)[0])
        self.assertEqual(len(rows), 63)
        self.assertEqual([row.romOffset for row in rows], list(range(0x7278, 0x7374, 4)))
        self.assertTrue(all((row.symSection, row.targetInstructionSection, row.relocType) == (1, 1, 5) for row in rows))

ORIGINAL_CARANIM_LABEL_RELOCATIONS = [
    0x154004fc, 0x154004fe, 0x15400500, 0x15400502, 0x15400504, 0x15400506, 0x15400508,
    0x1540050a, 0x1540050c, 0x1540050e, 0x15400510, 0x15400512, 0x15400514, 0x15400516,
    0x15400518, 0x1540051a, 0x1540051c, 0x1540051e, 0x15400520, 0x15400522, 0x15400524,
    0x15400526, 0x15400528, 0x1540052a, 0x1540052c, 0x1540052e, 0x15400530, 0x15400532,
    0x15400534, 0x15400536, 0x15400538, 0x1540053a, 0x1540053c, 0x1540053e, 0x15400540,
    0x15400542, 0x15400544, 0x15400546, 0x15400548, 0x1540054a, 0x1540054c, 0x1540054e,
    0x15400550, 0x15400552, 0x15400554, 0x15400556, 0x15400558, 0x1540055a, 0x1540055c,
    0x1540055e, 0x15400560, 0x15400562, 0x15400564, 0x15400566, 0x15400568, 0x1540056a,
    0x1540056c, 0x1540056e, 0x15400570, 0x15400572, 0x15400574, 0x15400576, 0x15400578,
]

if __name__ == "__main__":
    unittest.main()
