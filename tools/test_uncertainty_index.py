#!/usr/bin/env python3
"""Regression tests for physical-source uncertainty declaration contexts.

Run with python3 -m unittest discover -s tools -p 'test_uncertainty_index.py'.
UNCERTAINTY_INDEX_TOOL optionally selects an isolated staged tool for review.
"""
from contextlib import redirect_stdout
from pathlib import Path
from tempfile import TemporaryDirectory
from unittest.mock import patch
import hashlib
import importlib.util
import io
import json
import os
import sys
import unittest

TOOL_PATH=Path(os.environ.get('UNCERTAINTY_INDEX_TOOL',Path(__file__).with_name('uncertainty_index.py')))
SPEC=importlib.util.spec_from_file_location('uncertainty_index_under_test',TOOL_PATH)
tool=importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(tool)


class DeclarationContextTests(unittest.TestCase):
    def setUp(self):
        self.directory=TemporaryDirectory();self.addCleanup(self.directory.cleanup)
        self.root=Path(self.directory.name)
        (self.root/'src').mkdir();(self.root/'include').mkdir()

    def source(self,text,path='src/example.c'):
        destination=self.root/path;destination.parent.mkdir(parents=True,exist_ok=True)
        destination.write_text(text,encoding='utf8')
        return tool.collect(self.root)

    def note(self,index,word):
        return next(x for x in index['items'] if x['kind']=='explicit_unknown' and word in x['symbol'])

    def names(self,item):
        return [(o['kind'],o['name']) for o in item.get('owners',[])]

    def query(self,needle):
        output=io.StringIO()
        with patch.object(sys,'argv',[str(TOOL_PATH),'--root',str(self.root),'--query',needle]),redirect_stdout(output):
            tool.main()
        return output.getvalue()

    def test_leading_function_note_is_searchable_by_named_routine(self):
        index=self.source('/* RE_UNKNOWN: query units need producer evidence. */\nvoid tdataBuildMatrixFromQuery(void) {}\n')
        item=self.note(index,'query units')
        self.assertEqual(self.names(item),[('function','tdataBuildMatrixFromQuery')])
        self.assertEqual(item['owners'][0]['declaration_line'],2)
        self.assertIn('src/example.c:1: explicit_unknown [tdataBuildMatrixFromQuery]',self.query('tdatabuildmatrixfromquery'))
        self.assertIn('1 search groups',self.query('tdataBuildMatrixFromQuery'))

    def test_inline_note_and_identifiers_stay_with_enclosing_function(self):
        index=self.source('void first(void) {\n if (1) { /* RE_UNKNOWN: retained pointer lifetime. */ use(unk18); }\n}\nvoid second(void) {}\n')
        self.assertEqual(self.names(self.note(index,'retained')),[('function','first')])
        identifier=next(x for x in index['items'] if x['symbol']=='unk18')
        self.assertEqual(self.names(identifier),[('function','first')])
        self.assertIn('2 search groups',self.query('first'))
        self.assertIn('0 search groups',self.query('second'))

    def test_multiline_signature_and_signature_comment(self):
        index=self.source('/* RE_UNKNOWN: caller owns the record. */\nstatic const State *\nreadState(\n int mode, /* RE_UNKNOWN: mode domain. */\n void *context\n)\n{ return context; }\n')
        self.assertEqual(self.names(self.note(index,'caller owns')),[('function','readState')])
        self.assertEqual(self.names(self.note(index,'mode domain')),[('function','readState')])
        self.assertEqual(self.note(index,'mode domain')['owners'][0]['declaration_line'],2)

    def test_quoted_fake_functions_and_braces_do_not_create_owners(self):
        index=self.source('const char *message="void fake(void) { } /* RE_UNKNOWN: fake */";\nvoid actual(void) {\n const char *nested="} void impostor(void) {";\n /* RE_UNKNOWN: actual ownership. */\n}\n')
        self.assertEqual(self.names(self.note(index,'actual ownership')),[('function','actual')])
        self.assertIn('0 search groups',self.query('impostor'))
        self.assertIn('0 search groups',self.query('fake'))

    def test_leading_and_inline_type_notes(self):
        index=self.source('/* RE_UNKNOWN: record format. */\ntypedef struct {\n /* RE_UNKNOWN: payload ownership. */\n void *payload;\n} QueryRecord;\n\n/* RE_UNKNOWN: tagged record layout. */\nstruct TaggedRecord { int field; };\n',path='include/records.h')
        self.assertEqual(self.names(self.note(index,'record format')),[('type','QueryRecord')])
        self.assertEqual(self.names(self.note(index,'payload ownership')),[('type','QueryRecord')])
        self.assertEqual(self.names(self.note(index,'tagged record')),[('type','TaggedRecord')])
        self.assertIn('2 search groups',self.query('QueryRecord'))

    def test_scalar_array_and_alias_declaration_notes(self):
        index=self.source('/* RE_UNKNOWN: global lifetime. */\nstatic State *cachedState;\n/* RE_UNKNOWN: array extent. */\nint cachedValues[4];\n/* RE_UNKNOWN: handle representation. */\ntypedef unsigned int Handle;\n')
        self.assertEqual(self.names(self.note(index,'global lifetime')),[('global','cachedState')])
        self.assertEqual(self.names(self.note(index,'array extent')),[('global','cachedValues')])
        self.assertEqual(self.names(self.note(index,'handle representation')),[('type','Handle')])

    def test_function_prototype_context(self):
        index=self.source('/* RE_UNKNOWN: callback lifetime. */\nextern void retainCallback(\n void (*callback)(void)\n);\n')
        self.assertEqual(self.names(self.note(index,'callback lifetime')),[('function','retainCallback')])

    def test_function_pointer_and_array_aliases_use_declarator_names(self):
        index=self.source('/* RE_UNKNOWN: callback type contract. */\ntypedef void (*Callback)(void);\n/* RE_UNKNOWN: buffer type extent. */\ntypedef unsigned char ByteBuffer[CAPACITY];\n/* RE_UNKNOWN: callback global lifetime. */\nvoid (*activeCallback)(void);\n/* RE_UNKNOWN: anonymous instance ownership. */\nstruct { int value; } activeRecord;\n')
        self.assertEqual(self.names(self.note(index,'callback type')),[('type','Callback')])
        self.assertEqual(self.names(self.note(index,'buffer type')),[('type','ByteBuffer')])
        self.assertEqual(self.names(self.note(index,'callback global')),[('global','activeCallback')])
        self.assertEqual(self.names(self.note(index,'anonymous instance')),[('global','activeRecord')])

    def test_unsupported_declarator_does_not_use_later_function(self):
        index=self.source('/* RE_UNKNOWN: multiple declarations. */\nint firstGlobal, secondGlobal;\nvoid following(void) {}\n')
        self.assertEqual(self.names(self.note(index,'multiple declarations')),[])
        self.assertIn('0 search groups',self.query('following'))

    def test_trailing_comments_do_not_borrow_next_function(self):
        index=self.source('void first(void) {} /* RE_UNKNOWN: trailing first note. */\nvoid second(void) {}\n/* RE_UNKNOWN: trailing file note. */\n')
        self.assertEqual(self.names(self.note(index,'trailing first')),[])
        self.assertEqual(self.names(self.note(index,'trailing file')),[])
        self.assertIn('0 search groups',self.query('second'))

    def test_detached_file_note_and_intervening_global_do_not_borrow_function(self):
        index=self.source('/* RE_UNKNOWN: file-wide audit. */\n\nvoid unrelated(void) {}\n/* RE_UNKNOWN: global contract. */\nint actualGlobal;\nvoid later(void) {}\n')
        self.assertEqual(self.names(self.note(index,'file-wide')),[])
        self.assertEqual(self.names(self.note(index,'global contract')),[('global','actualGlobal')])
        self.assertIn('0 search groups',self.query('later'))

    def test_line_directives_preserve_physical_positions(self):
        index=self.source('#line 900 "void fabricated(void) {"\n/* RE_UNKNOWN: physical source note. */\nvoid realFunction(void) {\n#line 1200 "another.c"\n /* RE_UNKNOWN: body note. */\n}\n')
        item=self.note(index,'physical source')
        self.assertEqual(item['lines'],[2]);self.assertEqual(item['owners'][0]['declaration_line'],3)
        self.assertEqual(self.note(index,'body note')['lines'],[5])
        self.assertEqual(self.names(self.note(index,'body note')),[('function','realFunction')])
        self.assertIn('0 search groups',self.query('fabricated'))

    def test_multiline_preprocessor_macro_does_not_create_declarations(self):
        index=self.source('#define FAKE_FN \\\n void fake(void) { }\n/* RE_UNKNOWN: real only. */\nvoid real(void) {}\n')
        self.assertEqual(self.names(self.note(index,'real only')),[('function','real')])
        self.assertIn('0 search groups',self.query('fake'))

    def test_q_ids_do_not_depend_on_owner_name_or_source_line(self):
        comment='RE_UNKNOWN: unchanged indexed note.'
        first=self.note(self.source(f'/* {comment} */\nvoid oldName(void) {{}}\n'),'unchanged')
        second=self.note(self.source(f'\n\n/* {comment} */\nvoid newName(void) {{}}\n'),'unchanged')
        expected='Q-'+hashlib.sha256('\0'.join(('explicit_unknown','src/example.c',comment)).encode()).hexdigest()[:12]
        self.assertEqual(first['id'],expected);self.assertEqual(second['id'],expected)
        self.assertNotEqual(first['owners'],second['owners'])

    def test_identical_notes_retain_all_owner_occurrences(self):
        index=self.source('void alpha(void) { /* RE_UNKNOWN: shared note. */ }\nvoid beta(void) { /* RE_UNKNOWN: shared note. */ }\n')
        item=self.note(index,'shared note')
        self.assertEqual(item['lines'],[1,2])
        self.assertEqual(self.names(item),[('function','alpha'),('function','beta')])
        self.assertEqual([o['lines'] for o in item['owners']],[[1],[2]])
        output=self.query('beta')
        self.assertIn('src/example.c:1: explicit_unknown [alpha]',output)
        self.assertIn('src/example.c:2: explicit_unknown [beta]',output)
        self.assertIn('1 search groups',output)

    def test_arbitrary_source_path_query_and_markdown_context(self):
        index=self.source('/* RE_UNKNOWN: note text. */\nvoid render(void) {}\n',path='src/modules/arbitrary_rom.c')
        output=self.query('modules/arbitrary_rom.c')
        self.assertIn('src/modules/arbitrary_rom.c:1',output)
        self.assertIn('Declaration context',tool.markdown(index))
        self.assertIn('function `render`',tool.markdown(index))
        self.assertIn('[1](../src/modules/arbitrary_rom.c#L1)',tool.markdown(index))

    def test_generate_check_and_determinism(self):
        index=self.source('/* RE_UNKNOWN: persistent note. */\nvoid own(void) {}\n')
        self.assertEqual(index,tool.collect(self.root))
        with patch.object(sys,'argv',[str(TOOL_PATH),'--root',str(self.root)]),redirect_stdout(io.StringIO()):tool.main()
        generated=json.loads((self.root/'docs/UNCERTAINTIES.json').read_text())
        self.assertEqual(generated,index)
        with patch.object(sys,'argv',[str(TOOL_PATH),'--root',str(self.root),'--check']),redirect_stdout(io.StringIO()):tool.main()

    def test_leading_assembly_note_is_searchable_by_original_symbol(self):
        index=self.source('/* RE_ORIGINAL_QUIRK: unwritten original local. RE_UNKNOWN: caller domain. */\n#pragma GLOBAL_ASM("asm/us/nonmatchings/misc/func_misc_004019FC.s")\nvoid following(void) {}\n')
        self.assertEqual(self.names(self.note(index,'caller domain')),[('assembly','func_misc_004019FC')])
        self.assertIn('explicit_unknown [func_misc_004019FC]',self.query('func_misc_004019FC'))
        self.assertIn('original_quirk [func_misc_004019FC]',self.query('func_misc_004019FC'))
        self.assertIn('0 search groups',self.query('following'))

    def test_retained_data_note_has_assembly_context_without_function_claim(self):
        index=self.source('/* RE_UNKNOWN: retained table interpretation. */\n#pragma GLOBAL_ASM("asm/us/data/modules/example.rodata.retained.s")\n')
        self.assertEqual(self.names(self.note(index,'table interpretation')),[('assembly','example.rodata.retained')])
        self.assertIn('assembly `example.rodata.retained`',tool.markdown(index))

    def test_detached_and_trailing_notes_do_not_borrow_assembly(self):
        index=self.source('/* RE_UNKNOWN: detached note. */\n\n#pragma GLOBAL_ASM("asm/func_first_00400000.s") /* RE_UNKNOWN: trailing note. */\n#pragma GLOBAL_ASM("asm/func_second_00400010.s")\n')
        self.assertEqual(self.names(self.note(index,'detached')),[])
        self.assertEqual(self.names(self.note(index,'trailing')),[])
        self.assertNotIn('explicit_unknown',self.query('func_second_00400010'))

    def test_quoted_commented_and_macro_pragmas_are_not_assembly_context(self):
        source=('const char *example="\\\n#pragma GLOBAL_ASM(\\"asm/fake_00400000.s\\")";\n'
                '/* #pragma GLOBAL_ASM("asm/commented_00400000.s") */\n'
                '#define EXAMPLE \\\n#pragma GLOBAL_ASM("asm/macro_00400000.s")\n'
                '/* RE_UNKNOWN: actual function note. */\nvoid actual(void) {}\n')
        index=self.source(source)
        self.assertFalse(any(x['kind']=='assembly' for x in index['items']))
        self.assertEqual(self.names(self.note(index,'actual function')),[('function','actual')])

    def test_assembly_note_keeps_group_identity_and_physical_line(self):
        comment='RE_UNKNOWN: original call contract.'
        index=self.source('#line 900 "unrelated.c"\n/* '+comment+' */\n#pragma GLOBAL_ASM("asm/func_original_00400000.s")\n')
        item=self.note(index,'original call')
        expected='Q-'+hashlib.sha256('\0'.join(('explicit_unknown','src/example.c',comment)).encode()).hexdigest()[:12]
        self.assertEqual(item['id'],expected);self.assertEqual(item['lines'],[2])
        self.assertEqual(item['owners'][0]['declaration_line'],3)


    def test_leading_assembly_note_crosses_location_directive(self):
        source=('/* RE_UNKNOWN: original callback contract.\n'
                ' * RE_ORIGINAL_QUIRK: original input home. */\n'
                '#line 235 "src/modules/ted.c"\n'
                '#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ted/func_ted_00406610.s")\n')
        index=self.source(source)
        item=self.note(index,'callback contract')
        self.assertEqual(self.names(item),[('assembly','func_ted_00406610')])
        self.assertEqual(item['lines'],[1])
        self.assertEqual(item['owners'][0]['declaration_line'],4)
        output=self.query('func_ted_00406610')
        self.assertIn('src/example.c:1: explicit_unknown [func_ted_00406610]',output)
        self.assertIn('src/example.c:1: original_quirk [func_ted_00406610]',output)

    def test_only_complete_location_directives_are_transparent(self):
        for directives in ['#line 42\n', '# line\t42 "another.c"\n',
                           '#line 42 "void fabricated(void) {}"\n#line 90\n',
                           '#line 42 "escaped\\\"filename.c"\n']:
            with self.subTest(directives=directives):
                index=self.source('/* RE_UNKNOWN: linked location. */\n'+directives+'void actual(void) {}\n')
                item=self.note(index,'linked location')
                self.assertEqual(self.names(item),[('function','actual')])
                self.assertEqual(item['owners'][0]['declaration_line'],2+directives.count('\n'))
                self.assertIn('0 search groups',self.query('fabricated'))

    def test_location_directives_do_not_erase_detached_blank_lines(self):
        for gap in ['\n\n#line 42 "x.c"\n', '\n#line 42 "x.c"\n\n',
                    '\n#line 42\n\n#line 90\n']:
            with self.subTest(gap=gap):
                index=self.source('/* RE_UNKNOWN: detached location. */'+gap+
                                  '#pragma GLOBAL_ASM("asm/func_actual_00400000.s")\n')
                self.assertEqual(self.names(self.note(index,'detached location')),[])
                self.assertNotIn('explicit_unknown',self.query('func_actual_00400000'))

    def test_location_directives_do_not_hide_macros_or_real_code(self):
        for blocker in ['#define AUDIT_GATE 1\n', '#if AUDIT_GATE\n',
                        '#pragma unrelated\n', ';\n', '#define CONTINUED \\\n#line 42\n']:
            with self.subTest(blocker=blocker):
                index=self.source('/* RE_UNKNOWN: blocked location. */\n#line 10\n'+blocker+
                                  '#line 90 "x.c"\n#pragma GLOBAL_ASM("asm/func_actual_00400000.s")\n')
                self.assertEqual(self.names(self.note(index,'blocked location')),[])

    def test_incomplete_or_extended_line_directives_block_ownership(self):
        for directive in ['#line\n', '#line RESTORE_LINE\n', '#line 10 FILE_NAME\n',
                          '#line 10 "x.c" trailing\n', '#line 10 "x.c" 1\n',
                          '# 10 "x.c"\n', '#line 10 \\\n "x.c"\n',
                          '#line 10 "x.c\n', '#line 10 /* not in narrow whitelist */\n']:
            with self.subTest(directive=directive):
                index=self.source('/* RE_UNKNOWN: incomplete location. */\n'+directive+
                                  '#pragma GLOBAL_ASM("asm/func_actual_00400000.s")\n')
                self.assertEqual(self.names(self.note(index,'incomplete location')),[])
        index=self.source('/* RE_UNKNOWN: same-line partial directive. */\n#line 10 void actual(void) {}\n')
        self.assertEqual(self.names(self.note(index,'same-line partial')),[])

    def test_trailing_note_stays_unowned_across_line_directive(self):
        index=self.source('int first; /* RE_UNKNOWN: trailing location. */\n#line 10\n'
                          '#pragma GLOBAL_ASM("asm/func_actual_00400000.s")\n')
        self.assertEqual(self.names(self.note(index,'trailing location')),[])

    def test_quoted_and_commented_line_text_is_not_transparent(self):
        for gap in ['\n/*\n#line 42\n*/\n', '\n"\\\n#line 42\\\n"\n']:
            with self.subTest(gap=gap):
                index=self.source('/* RE_UNKNOWN: literal location. */'+gap+
                                  '#pragma GLOBAL_ASM("asm/func_actual_00400000.s")\n')
                self.assertEqual(self.names(self.note(index,'literal location')),[])

    def test_location_association_preserves_group_id_and_physical_offsets(self):
        note='RE_UNKNOWN: stable location association.'
        first=self.note(self.source('/* '+note+' */\nvoid actual(void) {}\n'),'stable location')
        second=self.note(self.source('/* '+note+' */\n#line 900 "misleading.c"\nvoid actual(void) {}\n'),'stable location')
        self.assertEqual(first['id'],second['id'])
        self.assertEqual(first['lines'],second['lines'])
        self.assertEqual(second['lines'],[1])
        self.assertEqual(self.names(second),[('function','actual')])
        self.assertEqual(second['owners'][0]['declaration_line'],3)
        self.assertEqual(self.names(first),self.names(second))

    def test_autogenerated_new_var_identifiers_are_bounded_and_lexical(self):
        index=self.source('void actual(void) {\n int new_var, new_var2, new_var27;\n'
                          ' int new_variable, my_new_var, new_var_suffix, new_var2_more, New_var;\n'
                          ' const char *example="new_var42 new_var";\n'
                          ' /* new_var99 is only a quoted example. */\n}\n')
        items=[x for x in index['items'] if x['kind']=='decompiler_local']
        self.assertEqual({x['symbol'] for x in items},{'new_var','new_var2','new_var27'})
        for item in items:
            self.assertEqual(item['lines'],[2])
            self.assertEqual(self.names(item),[('function','actual')])


    def test_stack_offsets_require_a_digit_or_uppercase_hex(self):
        index=self.source('void actual(float speed) {\n'
                          ' int sp0, sp18, sp1c, spBC, spDE, spb4, spdE, spF;\n'
                          ' int space, spec, sp, sp1_more, speedFactor, stackspBC;\n'
                          ' const char *example="sp24 sp40"; /* sp48 */\n}\n')
        records=[x for x in index['items'] if x['kind']=='decompiler_local']
        self.assertEqual({x['symbol'] for x in records},{'sp0','sp18','sp1c','spBC','spDE','spb4','spdE','spF'})
        for item in records:
            self.assertEqual(item['lines'],[2])
            self.assertEqual(self.names(item),[('function','actual')])

    def test_stack_pattern_does_not_classify_sdk_speed_or_space_directive(self):
        index=self.source('typedef struct { unsigned int speed; } Device;\n'
                          '#define STORAGE(length) .space length * 4\n',path='include/example.h')
        self.assertEqual([x for x in index['items'] if x['kind']=='decompiler_local'],[])

    def test_stack_pattern_keeps_supported_identifier_ids_and_locations(self):
        index=self.source('void actual(void) { int spBC, spb4, arg2, temp_v0, var_s0, new_var2; }\n')
        records={x['symbol']:x for x in index['items'] if x['kind']=='decompiler_local'}
        self.assertEqual(set(records),{'spBC','spb4','arg2','temp_v0','var_s0','new_var2'})
        for name,item in records.items():
            self.assertEqual(item['lines'],[1])
            self.assertEqual(self.names(item),[('function','actual')])
            expected='Q-'+hashlib.sha256(('decompiler_local\0src/example.c\0'+name).encode()).hexdigest()[:12]
            self.assertEqual(item['id'],expected)


if __name__=='__main__':unittest.main()
