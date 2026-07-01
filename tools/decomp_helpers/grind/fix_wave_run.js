export const meta = {
  name: 'bar-decomp-fix-wave',
  description: 'Fix compile errors in byte-match seeds (given the exact compiler output)',
  phases: [{ title: 'Fix', detail: 'one writer per BUILDERR function' }],
}
const items = [{"mod": "selection", "fn": "func_selection_00419038"}, {"mod": "battle", "fn": "func_battle_00406900"}, {"mod": "battle", "fn": "func_battle_004090F0"}, {"mod": "letter", "fn": "func_letter_00400420"}, {"mod": "selection", "fn": "func_selection_00415D48"}, {"mod": "selection", "fn": "func_selection_00402E34"}, {"mod": "selection", "fn": "func_selection_00416A50"}, {"mod": "selection", "fn": "func_selection_00415E80"}, {"mod": "selection", "fn": "func_selection_00415FB4"}, {"mod": "selection", "fn": "func_selection_00403938"}, {"mod": "cam", "fn": "func_cam_00403A20"}, {"mod": "battle", "fn": "func_battle_00406784"}, {"mod": "battle", "fn": "func_battle_0040733C"}, {"mod": "med", "fn": "func_med_004000DC"}, {"mod": "pause", "fn": "func_pause_00403E6C"}, {"mod": "battle", "fn": "func_battle_00407FF4"}, {"mod": "selection", "fn": "func_selection_004039B0"}, {"mod": "selection", "fn": "func_selection_00415DEC"}, {"mod": "battle", "fn": "func_battle_00405034"}, {"mod": "glare", "fn": "func_glare_004000D0"}, {"mod": "filmroll", "fn": "func_filmroll_00400588"}, {"mod": "selection", "fn": "func_selection_0040A778"}, {"mod": "selection", "fn": "func_selection_00415CA0"}, {"mod": "pause", "fn": "func_pause_00402854"}, {"mod": "battle", "fn": "func_battle_00407DC4"}, {"mod": "menuslct", "fn": "func_menuslct_0040126C"}, {"mod": "battle", "fn": "func_battle_00407E78"}, {"mod": "menuslct", "fn": "func_menuslct_004011B0"}, {"mod": "battle", "fn": "func_battle_00401318"}, {"mod": "battle", "fn": "func_battle_00405A1C"}, {"mod": "selection", "fn": "func_selection_004136CC"}, {"mod": "selection", "fn": "func_selection_00415AD0"}, {"mod": "selection", "fn": "func_selection_00415EF4"}, {"mod": "battle", "fn": "func_battle_00407F30"}, {"mod": "selection", "fn": "func_selection_00408B24"}, {"mod": "selection", "fn": "func_selection_004162D4"}]
const FIX = "C:/Users/Bryan/Projects/BeetleRecomp/.grind/fixcards"
const HDRS = "C:/Users/Bryan/Projects/BeetleRecomp/.grind/headers"
const SEEDS = "C:/Users/Bryan/Projects/BeetleRecomp/.grind/seeds"

const GUIDE = `You previously wrote C for a Beetle Adventure Racing function that FAILS TO COMPILE. Fix it so it
(a) compiles under IDO 7.1 and (b) STILL assembles to the target asm byte-for-byte (DaisyBox hash gate).

READ: the fix-card ${FIX}/<fn>.txt = your broken C + the EXACT compiler errors + the target asm. Also the
headers in ${HDRS}/ (structs.h, global_exports.h, functions.h, variables.h, uv*_rom.h, ...).

The module only includes common.h (structs.h/functions.h/variables.h/file_manager.h/mem_allocator.h/macros.h).
FIX EACH compiler error. The usual causes and their fixes:
- "'gXxxExports' undeclared": you used an engine export table without declaring it. Add
    typedef struct { char pad[0xNN]; RET (*unkNN)(ARGS); } XxxExp_<ADDR>;  extern XxxExp_<ADDR> *gXxxExports;
  where 0xNN is the offset from the asm 'lw $t9,0xNN($t7)', member is unk<offset>, and gXxxExports is the
  EXACT name from global_exports.h. NEVER name a member 'func_uvgfxmgr_rom_XXXX' — always unk<hexoffset>.
- "conflicting types for 'gGameSettings'" (or any symbol already in a header): DELETE your redeclaration of
  it; common.h already declares it. Use the header's type (e.g. gGameSettings is UnkStruct_80025CF0[]).
- "has no member named 'unkXX'": add that member at the right offset to your struct, or fix the offset.
- "conflicting types for 'func_...'": make your extern proto match how it's really called (arg widths).
- "unknown type name 's32'": you must NOT emit #include lines; put decls after (they inject into common.h scope).
Keep statement order/immediates identical so it still byte-matches. Give inferred structs unique names
(suffix the function's hex address). ASCII, no markdown, no #include.

OUTPUT: Write the corrected full C (preamble decls + the one function) to ${SEEDS}/<fn>.c (overwrite).`

phase('Fix')
const results = await parallel(items.map((it) => () => {
  const addr = it.fn.replace('func_' + it.mod + '_', '')
  return agent(
    `${GUIDE}\n\nFIX TARGET: module="${it.mod}" function="${it.fn}" (ADDR=${addr}).\n` +
    `Read ${FIX}/${it.fn}.txt and the headers, then Write corrected C to ${SEEDS}/${it.fn}.c.`,
    { label: `fix:${it.mod}/${addr}`, phase: 'Fix', model: 'sonnet', effort: 'medium',
      schema: { type: 'object', additionalProperties: false, required: ['fn','fixed','note'],
        properties: { fn:{type:'string'}, fixed:{type:'boolean'}, note:{type:'string'} } } }
  ).then(r => r || { fn: it.fn, fixed: false, note: 'died' })
}))
const fixed = results.filter(r => r && r.fixed).length
log(`fix wave: ${fixed}/${items.length} rewritten`)
return { total: items.length, fixed }
