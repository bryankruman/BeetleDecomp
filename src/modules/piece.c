// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004000CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004001F4.s")

/* Original five-slot walk at stride0x20: re-read each byte0x10 and call
 * helper0x401F4 on that indexed record only when the byte is nonzero.
 * RE_UNKNOWN: byte meaning, complete record layout/extent, ownership and
 * helper update lifetime require original creation/field writers and callers.
 * RE_UNKNOWN: historical source access views; the readable draft preserves
 * the observed loop, loads, call and argument but compiler base-address
 * reuse/scheduling still differs. Retain native assembly until grounded. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400670.s")
#line 9 "src/modules/piece.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_004006E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/__entrypoint_func_piece_400e90.s")

#line 16 "src/modules/piece.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_piece_00400F48(void) {
}
#line 18 "src/modules/piece.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00400F50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/piece/func_piece_00401104.s")

