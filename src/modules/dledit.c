// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
/* Original address storage; slot signatures remain separate contracts. */
typedef struct { u32 slots[9]; } DleditModuleAddressStorage;
/* Consumed views for RGBA commands and two combiner cycles.
 * RE_UNKNOWN: nominal original type names, allocation ownership, aliasing and
 * caller value domains remain unproved; these declarations allocate no storage.
 * Each cycle supplies color A/B/C/D followed by alpha A/B/C/D selectors to
 * the existing GBI masks. No global export/header migration is implied. */
typedef struct RGBAF_s {
    f32 red;
    f32 green;
    f32 blue;
    f32 alpha;
} RGBAF;

typedef struct CombineMode_inner_s {
    s32 colorA;
    s32 colorB;
    s32 colorC;
    s32 colorD;
    s32 alphaA;
    s32 alphaB;
    s32 alphaC;
    s32 alphaD;
} CombineMode_inner;

typedef struct CombineMode_s {
    union {
        CombineMode_inner cycles[2];
    };
} CombineMode;

#define BAR_gDPSetCombineLERP2(pkt,a0,b0,c0,d0,Aa0,Ab0,Ac0,Ad0,a1,b1,c1,d1,Aa1,Ab1,Ac1,Ad1) { Gfx *_g = (Gfx *)(pkt); _g->words.w0 = _SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(GCCc0w0(a0, c0, Aa0, Ac0) | GCCc1w0(a1, c1), 0, 24); _g->words.w1 = (unsigned int)(GCCc0w1(b0, d0, Ab0, Ad0) | GCCc1w1(b1, Aa1, Ac1, d1, Ab1, Ad1)); }

void func_dledit_00400090(void);
typedef struct { u32 word0, word1; } DleditCommand;
typedef struct { f32 r, g, b, a; } DleditRgba;
extern s32 D_dledit_00400600, D_dledit_00400658, D_dledit_004006C4, D_dledit_00400708;
u8 * dleditFindOpcodeWithOriginalEndTest();
void dleditPatchTextureImageAddress();
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column);
void func_dledit_00400174(Gfx *gdl, RGBAF *color, s32 arg2);
void func_dledit_004001F8(CombineMode *mode, Gfx *arg1);
void dleditUnpackRgba(DleditCommand *command, DleditRgba *rgba);
void func_dledit_004003D4(CombineMode* arg0, Gfx* gdl);
s32 * dleditFindCommandWordWithOriginalEndTest();
typedef char DleditRgbaViewIs16Bytes[(sizeof(RGBAF) == 16) ? 1 : -1];
typedef char DleditCombineCycleIs32Bytes[(sizeof(CombineMode_inner) == 32) ? 1 : -1];
typedef char DleditCombineViewIs64Bytes[(sizeof(CombineMode) == 64) ? 1 : -1];
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
 * RE_ORIGINAL_QUIRK: the sign-extended command byte cannot equal positive 0xDF.
 * RE_UNKNOWN: target presence, readable command span and reachable failure require original UVTX streams and callers; the nominal terminator does not establish a bound. */
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
/* Find command 0xFD and replace its address word with the supplied value plus 0x80000000, preserving unsigned wrap.
 * RE_ORIGINAL_QUIRK: the scanner cannot stop at positive 0xDF. RE_UNKNOWN: required FD presence, address representation and command backing extent/lifetime require original UVTX producers and callers. */
void dleditPatchTextureImageAddress(u8 *commands, s32 address) {
    u8 *command;

    command = dleditFindOpcodeWithOriginalEndTest(commands, 0xFD);
    if (command != NULL) {
        *(s32 *)(command + 4) = (s32)((u32)address + 0x80000000U);
    }
}
#line 42 "src/modules/dledit.c"

#line 41 "src/modules/dledit.c"
/* Return an original combiner-source label address through the direct, eight-column or nine-column index table.
 * Preserve the unused context word and unchecked signed alternate/row/column selectors.
 * RE_UNKNOWN: valid selector domains, historical source prototype and each label's readable extent require original selection writers, table consumers and callers; a mapped label does not prove GUI C4's full 30-byte source window. */
s32 dleditLookupMappedWord(s32 context, s32 alternate, s32 row, s32 column) {
    s32 index;
    if (column >= 9) index = ((s32 *)&D_dledit_004006C4)[column];
    else if (alternate) index = *(s32 *)((u8 *)&D_dledit_00400708 + (row << 5) + column * 4);
    else index = *(s32 *)((u8 *)&D_dledit_00400658 + row * 0x24 + column * 4);
    return ((s32 *)&D_dledit_00400600)[index];
}
#line 42 "src/modules/dledit.c"
/* RE_UNKNOWN: original RGBA packing truncates channel*255 with byte wrapping, no clamps, and stores opcode word before reading channels; historical channel domains (including nonfinite/out-of-range inputs), command/color backing extent and alias/lifetime guarantees require original color producers, UVTX assets and callers. Preserve operand order and null-command behavior. */
/* Write the opcode and packed RGBA channels into one display-list command.
 * RE_ORIGINAL_QUIRK: scale by255, truncate and retain the original masks/shifts; no clamp.
 * RE_UNKNOWN: finite channel range, aliasing, allocation bounds and caller return use. */
#line 137 "src/modules/dledit.c"
void dleditWriteRgbaCommand(Gfx *command, RGBAF *color, s32 opcode) {
    if (command == NULL) {
        return;
    }
    command->words.w0 = (opcode << 8) << 16;
    command->words.w1 =
        (((((s32) (color->alpha * 255.0f)) & 0xFF) | ((((s32) (255.0f * color->red)) << 19) << 5))
         | ((((s32) (255.0f * color->green)) & 0xFF) << 0x10))
        | ((((s32) (255.0f * color->blue)) & 0xFF) << 8);
}
/* RE_UNKNOWN: original FC packing reads a 16-word selection window, preserves masks/shifts, and stores word0 before second-stage source reads; selector domains, complete source/command backing layout, alias/lifetime and historical declarations require original selection writers, command consumers and callers. Preserve that store boundary and null-command behavior. */
/* Pack two cycles of color and alpha selectors into a combiner command.
 * RE_ORIGINAL_QUIRK: store word0 before reading selector expressions for word1.
 * RE_UNKNOWN: selector domains, source/destination aliasing and caller return use. */
#line 148 "src/modules/dledit.c"
void dleditPackCombineSelectors(CombineMode *selectors, Gfx *command) {
    if (command == NULL) {
        return;
    }

    BAR_gDPSetCombineLERP2(command, selectors->cycles[0].colorA, selectors->cycles[0].colorB, selectors->cycles[0].colorC,
                           selectors->cycles[0].colorD, selectors->cycles[0].alphaA, selectors->cycles[0].alphaB,
                           selectors->cycles[0].alphaC, selectors->cycles[0].alphaD, selectors->cycles[1].colorA, selectors->cycles[1].colorB,
                           selectors->cycles[1].colorC, selectors->cycles[1].colorD, selectors->cycles[1].alphaA, selectors->cycles[1].alphaB,
                           selectors->cycles[1].alphaC, selectors->cycles[1].alphaD);
}

#line 47 "src/modules/dledit.c"
/* Normalize display-list word one's four bytes to RGBA floats in byte order; a null command leaves output untouched.
 * RE_UNKNOWN: complete command/output backing extent, alias and lifetime guarantees require original command and color-window producers/callers; four observed float stores do not establish ownership. */
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
/* RE_UNKNOWN: original combiner decoding snapshots both command words before 16 output stores, then caps only selectors0/1/2 and8/9/10 at8/8/16 even for null input, preserving negative existing values; output capacity, alias/lifetime and UI selector meanings require original shared-window writers/readers and callers. Preserve snapshot/store/clamp order. */
/* Read sixteen combiner selectors, then clamp color A/B to8 and color C to16.
 * RE_ORIGINAL_QUIRK: a null command still clamps the existing selector rows;
 * negative signed selectors survive these upper-bound tests unchanged.
 * RE_UNKNOWN: nominal ownership, valid command opcode and caller return use. */
#line 175 "src/modules/dledit.c"
void dleditReadAndClampCombineSelectors(CombineMode* selectors, Gfx* command) {
    s32 cycleIndex;
    u32 commandWord0;
    u32 commandWord1;

    if (command != NULL) {
        commandWord0 = command->words.w0;
        commandWord1 = command->words.w1;
        selectors->cycles[0].colorA = (s32) ((commandWord0 >> 0x14) & 0xF);
        selectors->cycles[0].colorB = (s32) ((commandWord1 >> 0x1C) & 0xF);
        selectors->cycles[0].colorC = (s32) ((commandWord0 >> 0xF) & 0x1F);
        selectors->cycles[0].colorD = (s32) ((commandWord1 >> 0xF) & 7);
        selectors->cycles[0].alphaA = (s32) ((commandWord0 >> 0xC) & 7);
        selectors->cycles[0].alphaB = (s32) ((commandWord1 >> 0xC) & 7);
        selectors->cycles[0].alphaC = (s32) ((commandWord0 >> 9) & 7);
        selectors->cycles[0].alphaD = (s32) ((commandWord1 >> 9) & 7);
        selectors->cycles[1].colorA = (s32) ((commandWord0 >> 5) & 0xF);
        selectors->cycles[1].colorB = (s32) ((commandWord1 >> 0x18) & 0xF);
        selectors->cycles[1].colorC = (s32) (commandWord0 & 0x1F);
        selectors->cycles[1].colorD = (s32) ((commandWord1 >> 6) & 7);
        selectors->cycles[1].alphaA = (s32) ((commandWord1 >> 0x15) & 7);
        selectors->cycles[1].alphaB = (s32) ((commandWord1 >> 3) & 7);
        selectors->cycles[1].alphaC = (s32) ((commandWord1 >> 0x12) & 7);
        selectors->cycles[1].alphaD = (s32) (commandWord1 & 7);
    }
    for (cycleIndex = 0; cycleIndex < 2; cycleIndex++) {
        if (selectors->cycles[cycleIndex].colorA >= 9) {
            selectors->cycles[cycleIndex].colorA = 8;
        }
        if (selectors->cycles[cycleIndex].colorB >= 9) {
            selectors->cycles[cycleIndex].colorB = 8;
        }
        if (selectors->cycles[cycleIndex].colorC >= 0x11) {
            selectors->cycles[cycleIndex].colorC = 0x10;
        }
    }
}

#line 51 "src/modules/dledit.c"
/* Scan eight-byte display-list commands for the requested first word.
 * RE_ORIGINAL_QUIRK: the sign-extended opcode cannot equal positive 0xDF;
 * target absence does not terminate at that opcode.
 * RE_UNKNOWN: target presence, readable command span and reachable failure require original command streams and callers; the nominal terminator does not establish a bound. */
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

