// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvled_rom_400000(UvLed_Exports *exports);
void uvLedModuleCleanup(void);
void uvLedDrawTextString(u8 *arg0);
void uvLedDrawDecimalInteger(s32 arg0);
void uvLedDrawBinaryInteger(s32 arg0);
void uvLedDrawHexInteger(s32 arg0);
void uvLedSetSharedShortPair(s16 arg0, s16 arg1);
void uvLedSetPositionAndCellCoordinates(f32 arg0, f32 arg1);
void uvLedSetVertexColors(u8 r, u8 g, u8 b, u8 a);
void uvLedDrawIntegerInRadix(s32 arg0, u16 arg1);
void uvLedDrawFloatWithTwoFractionDigits(f32 arg0);
void uvLedDrawSevenSegmentGlyph(u16 arg0);
void uvLedDrawFourteenSegmentCharacter(u8 arg0);
void uvLedDrawFormattedWordArguments(u8 *fmt, s32 arg1, ...);

u16 D_uvled_rom_004011B0[0x32] = {
    0xFC0, 0x840, 0,    0x40,   0x2000, 0x500, 0x3F,  6,     0x6D,  0x4F,  0x56,  0x5B,  0x7B,
    0xE,   0x7F,  0x5F, 0x3000, 0,      0x600, 0x41,  0x180, 0,     0,     0x7E,  0x47B, 0x39,
    0x1B0, 0x79,  0x78, 0x239,  0x76,   0x809, 0x27,  0xE00, 0x31,  0x4B6, 0x2B6, 0x3F,  0x7C,
    0x23F, 0x27C, 0x5B, 0x808,  0x37,   0x286, 0x336, 0x780, 0x580, 0x509, 0,
};

u8 D_uvled_rom_00401214[0x14] = {
    0x3F, 6,    0x6D, 0x4F, 0x56, 0x5B, 0x7B, 0xE, 0x7F, 0x5F,
    0x7E, 0x73, 0x39, 0x67, 0x79, 0x78, 0,    0,   0,    0,
};

Vtx D_uvled_rom_00401228[14] = {
    { { { 2, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Vtx D_uvled_rom_00401308[15] = {
    { { { 0, 0xD, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 1, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 1, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 9, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 1, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0xD, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 9, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 1, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 5, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 5, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Vtx D_uvled_rom_004013F8[1] = { { { { 6, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } } };
Vtx D_uvled_rom_00401408[8] = {
    { { { 4, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0xA, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0xA, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 4, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 4, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Gfx D_uvled_rom_00401488[] = {
    gsSPVertex(D_uvled_rom_00401228, 14, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401498[] = {
    gsSPVertex(D_uvled_rom_00401308, 15, 0),
    gsSPVertex(D_uvled_rom_004013F8, 1, 15),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014B0[] = {
    gsSPVertex(D_uvled_rom_00401408, 8, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014C0[] = {
    gsSP1Triangle(10, 11, 1, 0),
    gsSP1Triangle(10, 1, 0, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014D8[] = {
    gsSP1Triangle(11, 8, 2, 0),
    gsSP1Triangle(11, 2, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014F0[] = {
    gsSP1Triangle(8, 12, 4, 0),
    gsSP1Triangle(8, 4, 3, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401508[] = {
    gsSP1Triangle(12, 13, 5, 0),
    gsSP1Triangle(12, 5, 4, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401520[] = {
    gsSP1Triangle(13, 9, 6, 0),
    gsSP1Triangle(13, 6, 5, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401538[] = {
    gsSP1Triangle(9, 10, 0, 0),
    gsSP1Triangle(9, 0, 7, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401550[] = {
    gsSP1Triangle(6, 9, 7, 0), gsSP1Triangle(2, 6, 7, 0), gsSP1Triangle(2, 3, 6, 0),
    gsSP1Triangle(2, 8, 3, 0), gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401578[] = {
    gsSP1Triangle(0, 9, 11, 0),
    gsSP1Triangle(0, 11, 7, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401590[] = {
    gsSP1Triangle(2, 9, 11, 0),
    gsSP1Triangle(2, 11, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015A8[] = {
    gsSP1Triangle(4, 11, 9, 0),
    gsSP1Triangle(4, 9, 3, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015C0[] = {
    gsSP1Triangle(6, 11, 9, 0),
    gsSP1Triangle(6, 9, 5, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015D8[] = {
    gsSP1Triangle(12, 13, 15, 0),
    gsSP1Triangle(12, 15, 14, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015F0[] = {
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401608[] = {
    gsSP1Triangle(4, 5, 7, 0),
    gsSP1Triangle(4, 7, 6, 0),
    gsSPEndDisplayList(),
};

Gfx *D_uvled_rom_00401620[0xE] = {
    D_uvled_rom_004014C0, D_uvled_rom_004014D8, D_uvled_rom_004014F0, D_uvled_rom_00401508,
    D_uvled_rom_00401520, D_uvled_rom_00401538, D_uvled_rom_00401550, D_uvled_rom_00401578,
    D_uvled_rom_00401590, D_uvled_rom_004015A8, D_uvled_rom_004015C0, D_uvled_rom_004015D8,
    D_uvled_rom_004015F0, D_uvled_rom_00401608,
};

s32 D_uvled_rom_00401658[] = { 0x00240000, __entrypoint_func_uvled_rom_400000 };

// .bss
s16 D_uvled_rom_00401660;
s16 D_uvled_rom_00401662;
f32 D_uvled_rom_00401664;
f32 D_uvled_rom_00401668;
s16 D_uvled_rom_0040166C;
s16 D_uvled_rom_0040166E;
s32 D_uvled_rom_00401670;
UvFMtx_Rom_Exports *D_uvled_rom_00401674;
UvGfxMgr_Exports *D_uvled_rom_00401678;

/*
 * Install nine text/number/format exports and load FMTX and GMGR. Reset the
 * two floating cell coordinates, choose 12-by-16 cells, set the left position
 * zero and the vertical position to screen height minus the cell height,
 * then clear the shared formatting word.
 * RE_ORIGINAL_QUIRK: The screen-derived position is stored as a halfword
 * without clipping. Preserve the unconditional line directive and store order.
 * RE_UNKNOWN: Screen-height stability/range, repeated initialization and
 * provider/buffer lifetime require the text renderer and graphics owner.
 */
#line 198 "src/modules/uvled_rom.c"
void __entrypoint_func_uvled_rom_400000(UvLed_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvLedModuleCleanup = uvLedModuleCleanup;
    exports->uvLedDrawTextString = uvLedDrawTextString;
    exports->uvLedDrawDecimalInteger = uvLedDrawDecimalInteger;
    exports->uvLedDrawBinaryInteger = uvLedDrawBinaryInteger;
    exports->uvLedDrawHexInteger = uvLedDrawHexInteger;
    exports->uvLedSetSharedShortPair = uvLedSetSharedShortPair;
    exports->uvLedSetPositionAndCellCoordinates = uvLedSetPositionAndCellCoordinates;
    exports->uvLedSetVertexColors = uvLedSetVertexColors;
    exports->uvLedDrawFormattedWordArguments = uvLedDrawFormattedWordArguments;
#line 200
    D_uvled_rom_00401674 = uvLoadModule('FMTX');
    D_uvled_rom_00401678 = uvLoadModule('GMGR');
    D_uvled_rom_00401664 = 0.0f;
    D_uvled_rom_00401668 = 0.0f;
    D_uvled_rom_0040166C = 0xC;
    D_uvled_rom_0040166E = 0x10;
    D_uvled_rom_00401660 = 0;
    D_uvled_rom_00401662 = D_uvled_rom_00401678->uvGetScreenHeight() - D_uvled_rom_0040166E;
    D_uvled_rom_00401670 = 0;
}

#line 211 "src/modules/uvled_rom.c"
/* Unload FMTX and GMGR dependencies in their original order. */
void uvLedModuleCleanup(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('GMGR');
}
#line 215 "src/modules/uvled_rom.c"

#line 216 "src/modules/uvled_rom.c"
/* Draw a zero-terminated string in the shared LED position and scale
 * using the fourteen-segment character renderer. Advance the local
 * matrix by the configured character spacing after each glyph. */
void uvLedDrawTextString(u8 *text) {
    Mtx4F projection;
    Mtx4F textTransform;
    u16 i;
    u8 character;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&projection, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&projection);
    D_uvled_rom_00401674->uvMat4SetIdentity(&textTransform);
    textTransform.m[0][0] = D_uvled_rom_00401664;
    textTransform.m[1][1] = D_uvled_rom_00401668;
    textTransform.m[3][0] = D_uvled_rom_00401660;
    textTransform.m[3][1] = D_uvled_rom_00401662;

    i = 0;
    while (character = text[i]) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        uvLedDrawFourteenSegmentCharacter(character);
        textTransform.m[3][0] += D_uvled_rom_0040166C;
        i++;
    }
}
#line 240 "src/modules/uvled_rom.c"

#line 241 "src/modules/uvled_rom.c"
/* Draw the signed integer through the original shared LED renderer
 * with radix ten, preserving its position update and sign handling. */
void uvLedDrawDecimalInteger(s32 value) {
    uvLedDrawIntegerInRadix(value, 0xA);
}
#line 244 "src/modules/uvled_rom.c"

#line 245 "src/modules/uvled_rom.c"
/* Draw the signed integer through the original shared LED renderer
 * with radix two, preserving its position update and sign handling. */
void uvLedDrawBinaryInteger(s32 value) {
    uvLedDrawIntegerInRadix(value, 2);
}
#line 248 "src/modules/uvled_rom.c"

#line 249 "src/modules/uvled_rom.c"
/* Draw the signed integer through the original shared LED renderer
 * with radix sixteen, preserving its position update and sign handling. */
void uvLedDrawHexInteger(s32 value) {
    uvLedDrawIntegerInRadix(value, 0x10);
}
#line 252 "src/modules/uvled_rom.c"

#line 253 "src/modules/uvled_rom.c"
/* Store the two shared signed shorts in order without inferring their units. */
void uvLedSetSharedShortPair(s16 first, s16 second) {
    D_uvled_rom_00401660 = first;
    D_uvled_rom_00401662 = second;
}
#line 257 "src/modules/uvled_rom.c"

#line 258 "src/modules/uvled_rom.c"
/* Divide caller coordinates by ten and fourteen, then derive shared
 * short coordinates with the original quarter-cell bias. Preserve double
 * arithmetic in the literal expressions and original narrowing. */
void uvLedSetPositionAndCellCoordinates(f32 x, f32 y) {
    D_uvled_rom_00401664 = (x / 10.0);
    D_uvled_rom_00401668 = (y / 14.0);
    D_uvled_rom_0040166C = ((D_uvled_rom_00401664 + 0.25) * 10);
    D_uvled_rom_0040166E = ((D_uvled_rom_00401668 + 0.25) * 14);
}
#line 264 "src/modules/uvled_rom.c"

#line 265 "src/modules/uvled_rom.c"
/* Set all 38 shared LED vertices to the caller RGBA byte values. */
void uvLedSetVertexColors(u8 r, u8 g, u8 b, u8 a) {
    s32 index;

    for (index = 0; index < 0x26; index++) {
        D_uvled_rom_00401228[index].v.cn[0] = r;
        D_uvled_rom_00401228[index].v.cn[1] = g;
        D_uvled_rom_00401228[index].v.cn[2] = b;
        D_uvled_rom_00401228[index].v.cn[3] = a;
    }
}
#line 275 "src/modules/uvled_rom.c"

#line 276 "src/modules/uvled_rom.c"
/* Draw least-significant digits then an optional minus glyph; keep
 * cursor updates. RE_UNKNOWN: value/radix/glyph domains and
 * overflow/termination guarantees need original input producers and callers. */
void uvLedDrawIntegerInRadix(s32 value, u16 radix) {
    Mtx4F projection;
    Mtx4F textTransform;
    u16 digit;
    s32 i;
    u16 isNegative;
    u16 digitCount;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&projection, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&projection);
    D_uvled_rom_00401674->uvMat4SetIdentity(&textTransform);
    textTransform.m[0][0] = D_uvled_rom_00401664;
    textTransform.m[1][1] = D_uvled_rom_00401668;
    if (value < 0) {
        isNegative = TRUE;
        value = -value;
    } else {
        isNegative = FALSE;
    }

    digitCount = 0;
    i = 1;
    if (value != 0) {
        while (value >= i) {
            digitCount++;
            i *= radix;
        }

    } else {
        digitCount = 1;
    }

    textTransform.m[3][0] = (D_uvled_rom_00401660 + ((digitCount + isNegative) * D_uvled_rom_0040166C));
    textTransform.m[3][1] = D_uvled_rom_00401662;
    for (i = 0; i < digitCount; i++) {
        digit = value % radix;
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        uvLedDrawSevenSegmentGlyph(digit);
        textTransform.m[3][0] -= D_uvled_rom_0040166C;
        value = (value - digit) / radix;
    }
    if (isNegative) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401550);
    }
    D_uvled_rom_00401660 += D_uvled_rom_0040166C * digitCount;
}
#line 325 "src/modules/uvled_rom.c"

#line 326 "src/modules/uvled_rom.c"
/* Draw two digits extracted from the fractional part and then the
 * decimal integer digits, retaining the original right-to-left order,
 * sign glyph and shared cursor update without adding rounding. */
void uvLedDrawFloatWithTwoFractionDigits(f32 value) {
    Mtx4F projection;
    Mtx4F textTransform;
    f32 fraction;
    u16 digit;
    s32 i;
    u16 isNegative;
    s32 integerPart;
    u16 digitCount;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&projection, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&projection);
    D_uvled_rom_00401674->uvMat4SetIdentity(&textTransform);
    textTransform.m[0][0] = D_uvled_rom_00401664;
    textTransform.m[1][1] = D_uvled_rom_00401668;
    if (value < 0.0f) {
        isNegative = TRUE;
        value = -value;
    } else {
        isNegative = FALSE;
    }
    digitCount = 0;
    i = 1;
    integerPart = value;
    if (integerPart != 0) {
        while (integerPart >= i) {
            digitCount++;
            i *= 10;
        }
    } else {
        digitCount = 1;
    }

    textTransform.m[3][0] = (D_uvled_rom_00401660 + ((digitCount + isNegative + 2) * D_uvled_rom_0040166C));
    textTransform.m[3][1] = D_uvled_rom_00401662;

    fraction = value - integerPart;
    for (i = 0; i < 2; i++) {
        fraction *= 10.0f;
        digit = (s32) fraction;
        fraction -= digit;
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        uvLedDrawSevenSegmentGlyph(digit);
        textTransform.m[3][0] -= (f32) D_uvled_rom_0040166C;
    }

    for (i = 0; i < digitCount; i++) {
        digit = (integerPart % 10);
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        uvLedDrawSevenSegmentGlyph(digit);
        textTransform.m[3][0] -= D_uvled_rom_0040166C;
        integerPart = (integerPart - (digit)) / 10;
    }
    if (isNegative) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401550);
    }
    D_uvled_rom_00401660 += D_uvled_rom_0040166C * digitCount;
}
#line 387 "src/modules/uvled_rom.c"

#line 388 "src/modules/uvled_rom.c"
/* Draw background unless mode 1, then segments enabled
 * by the glyph mask. RE_UNKNOWN: glyph-table
 * index/storage bounds need original glyph producers and callers. */
void uvLedDrawSevenSegmentGlyph(u16 glyph) {
    u8 segments;
    u8 segment;

    segments = D_uvled_rom_00401214[glyph];
    if (D_uvled_rom_00401670 != 1) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401488);
    }
    for (segment = 0; segment < 7; segment++) {
        if ((1 << segment) & segments) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[segment]);
        }
    }
}
#line 402 "src/modules/uvled_rom.c"

#line 403 "src/modules/uvled_rom.c"
/* Map the original character range to a fourteen-segment mask and emit
 * its three segment groups. Preserve the original uppercase conversion
 * and shared suppression value for each group transition. */
void uvLedDrawFourteenSegmentCharacter(u8 character) {
    u16 i;
    u16 segmentMask;

    if (character >= 0x61) {
        character -= 32;
    }
    if ((character < 0x2A) || (character >= 0x5B)) {
        return;
    }

    character -= 0x2A;
    segmentMask = D_uvled_rom_004011B0[character];
    if (D_uvled_rom_00401670 != 1) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401488);
    }

    for (i = 0; i < 7; i++) {
        if ((1 << i) & segmentMask) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
    if (D_uvled_rom_00401670 != 2) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401498);
    }

    for (i = 7; i < 12; i++) {
        if ((1 << i) & segmentMask) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
    if (D_uvled_rom_00401670 != 3) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_004014B0);
    }

    for (i = 12; i < 14; i++) {
        if ((1 << i) & segmentMask) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
}
#line 444 "src/modules/uvled_rom.c"

#line 445 "src/modules/uvled_rom.c"
/* Render the original limited format language: radix x/d/b, string s
 * and newline. Keep the existing word-stream argument ABI, cursor rules
 * and unsupported f behavior; do not substitute standard printf parsing. */
void uvLedDrawFormattedWordArguments(u8 *format, s32 firstArgument, ...) {
    s32 *argumentWords;
    s32 formatIndex;
    s32 base;
    char character;
    Mtx4F projection;
    Mtx4F textTransform;
    u8 *stringArgument;
    s32 stringIndex;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&projection, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&projection);
    D_uvled_rom_00401674->uvMat4SetIdentity(&textTransform);
    argumentWords = &firstArgument;
    textTransform.m[0][0] = D_uvled_rom_00401664;
    textTransform.m[1][1] = D_uvled_rom_00401668;
    textTransform.m[3][0] = D_uvled_rom_00401660;
    textTransform.m[3][1] = D_uvled_rom_00401662;

    formatIndex = 0;
    character = format[formatIndex];
    while (character != 0) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
        if (character == '%') {
            formatIndex++;
            character = format[formatIndex];
            base = 0;
            if (character == 'x') {
                base = 16;
            } else if (character == 'd') {
                base = 10;
            } else if (character == 'b') {
                base = 2;
            } else if (character == 'f') {
            } else if (character == 's') {
                stringArgument = (u8 *) *argumentWords;
                stringIndex = 0;
                textTransform.m[0][0] = D_uvled_rom_00401664;
                textTransform.m[1][1] = D_uvled_rom_00401668;
                while (stringArgument[stringIndex] != 0) {
                    D_uvled_rom_00401674->uvGfxMtxViewLoad(&textTransform, 2U);
                    textTransform.m[3][0] += D_uvled_rom_0040166C;
                    uvLedDrawFourteenSegmentCharacter(stringArgument[stringIndex]);
                    stringIndex += 1;
                }
                textTransform.m[3][0] -= D_uvled_rom_0040166C;
            }
            if (base != 0) {
                D_uvled_rom_00401660 = (textTransform.m[3][0] - D_uvled_rom_0040166C);
                D_uvled_rom_00401662 = textTransform.m[3][1];
                uvLedDrawIntegerInRadix(*argumentWords, base);
                textTransform.m[3][0] = D_uvled_rom_00401660;
                textTransform.m[3][1] = D_uvled_rom_00401662;
            }
            argumentWords += 1;
        } else if (character == '\n') {
            textTransform.m[3][0] = -D_uvled_rom_0040166C;
            textTransform.m[3][1] -= D_uvled_rom_0040166E;
            D_uvled_rom_00401662 += D_uvled_rom_0040166E;
        } else {
            uvLedDrawFourteenSegmentCharacter(character);
        }

        formatIndex += 1;
        character = format[formatIndex];
        textTransform.m[3][0] += D_uvled_rom_0040166C;
    }
    D_uvled_rom_00401660 = textTransform.m[3][0];
    D_uvled_rom_00401662 = textTransform.m[3][1];
}
#line 517 "src/modules/uvled_rom.c"
