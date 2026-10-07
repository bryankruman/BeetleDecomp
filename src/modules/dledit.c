// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
/* Original address storage; slot signatures remain separate contracts. */
typedef struct { u32 slots[9]; } DleditModuleAddressStorage;
void func_dledit_00400090(void);
typedef struct { u32 word0, word1; } DleditCommand;
typedef struct { f32 r, g, b, a; } DleditRgba;
extern s32 D_dledit_00400600, D_dledit_00400658, D_dledit_004006C4, D_dledit_00400708;
u8 * dleditFindOpcodeWithOriginalEndTest();
void dleditPatchTextureImageAddress();
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column);
void func_dledit_00400174();
void func_dledit_004001F8();
void dleditUnpackRgba(DleditCommand *command, DleditRgba *rgba);
void func_dledit_004003D4();
s32 * dleditFindCommandWordWithOriginalEndTest();
#line 18 "src/modules/dledit.c"
/* Register the original dledit module addresses in their observed store order
 * after updating the file allocation pointer. Preserve separate empty exports.
 * RE_UNKNOWN: historical full export type and remaining callback signatures,
 * purposes and consumer contracts. Trace slot consumers and original target
 * bodies before assigning callable types or changing empty callbacks. */
void __entrypoint_func_dleditInitializeModuleExports(DleditModuleAddressStorage *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->slots[0] = (u32)func_dledit_00400090; /* 0x00 */
    exports->slots[1] = (u32)dleditFindOpcodeWithOriginalEndTest; /* 0x04 */
    exports->slots[2] = (u32)dleditPatchTextureImageAddress; /* 0x08 */
    exports->slots[3] = (u32)dleditLookupMappedWord; /* 0x0C */
    exports->slots[4] = (u32)func_dledit_00400174; /* 0x10 */
    exports->slots[5] = (u32)func_dledit_004001F8; /* 0x14 */
    exports->slots[6] = (u32)dleditUnpackRgba; /* 0x18 */
    exports->slots[7] = (u32)func_dledit_004003D4; /* 0x1C */
    exports->slots[8] = (u32)dleditFindCommandWordWithOriginalEndTest; /* 0x20 */
}
#line 19 "src/modules/dledit.c"

#line 16 "src/modules/dledit.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_dledit_00400090(void) {
}
#line 18 "src/modules/dledit.c"

#line 19 "src/modules/dledit.c"
/* Scan eight-byte display-list commands for the requested opcode.
 * Preserve the original defective end test: sign-extending the command byte
 * can never equal positive 0xDF, so callers must contain the target opcode. */
u8 *dleditFindOpcodeWithOriginalEndTest(u8 *commands, s32 opcode) {
    s32 commandByte;

loop:
    commandByte = *commands;
    if (commandByte == opcode) {
        return commands;
    }
    commands += 8;
    if (((commandByte << 24) >> 24) == 0xDF) {
        return NULL;
    }
    goto loop;
}
#line 33 "src/modules/dledit.c"

#line 34 "src/modules/dledit.c"
/* Find command 0xFD and replace its address word with the supplied value
 * plus 0x80000000. Preserve the scanner end-test hazard and unsigned wrap. */
void dleditPatchTextureImageAddress(u8 *commands, s32 address) {
    u8 *command;

    command = dleditFindOpcodeWithOriginalEndTest(commands, 0xFD);
    if (command != NULL) {
        *(s32 *)(command + 4) = (s32)((u32)address + 0x80000000U);
    }
}
#line 42 "src/modules/dledit.c"

#line 41 "src/modules/dledit.c"
/* Select an index from the original direct, eight-column or nine-column
 * lookup tables, then return the mapped 32-bit word. Preserve the unused
 * context and unchecked signed row/column contracts. */
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column) {
    s32 index;
    if (column >= 9) index = ((s32 *)&D_dledit_004006C4)[column];
    else if (alternate) index = *(s32 *)((u8 *)&D_dledit_00400708 + (row << 5) + column * 4);
    else index = *(s32 *)((u8 *)&D_dledit_00400658 + row * 0x24 + column * 4);
    return ((s32 *)&D_dledit_00400600)[index];
}
#line 42 "src/modules/dledit.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_00400174.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_004001F8.s")

#line 47 "src/modules/dledit.c"
/* Normalize each byte of display-list word one to RGBA floats in byte order.
 * A null command leaves the output unchanged; output validity is caller-owned. */
void dleditUnpackRgba(DleditCommand *command, DleditRgba *rgba) {
    u32 packed;
    if (command != NULL) {
        packed = command->word1;
        rgba->r = (f32)((packed >> 24) & 0xFF) / 255.0f;
        rgba->g = (f32)((packed >> 16) & 0xFF) / 255.0f;
        rgba->b = (f32)((packed >> 8) & 0xFF) / 255.0f;
        rgba->a = (f32)(packed & 0xFF) / 255.0f;
    }
}
#line 48 "src/modules/dledit.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/dledit/func_dledit_004003D4.s")

#line 51 "src/modules/dledit.c"
/* Scan eight-byte display-list commands for the requested first word.
 * Preserve the original defective end test: sign-extending the opcode byte
 * cannot equal positive 0xDF, so the command stream must contain the target.
 * RE_ORIGINAL_QUIRK: The sign-extended opcode cannot equal positive 0xDF; target absence does not terminate at that opcode. */
s32 *dleditFindCommandWordWithOriginalEndTest(s32 *commands, s32 targetWord) {
    s32 opcode;
    s32 word;

loop:
    opcode = *(u8 *)commands;
    word = *commands;
    if (word == targetWord) {
        return commands;
    }
    commands += 2;
    if (((opcode << 24) >> 24) == 0xDF) {
        return NULL;
    }
    goto loop;
}
#line 67 "src/modules/dledit.c"

