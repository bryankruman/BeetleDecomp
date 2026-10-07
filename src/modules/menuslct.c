// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvfmtx_rom.h"
#include "uvgfxmgr_rom.h"
#include "uvgfxstate_rom.h"
#include "uvdgeom_rom.h"
extern UvFMtx_Rom_Exports *gUvFmtxExports;
extern UvGfxMgr_Exports *gUvGfxMgrExports;
extern UvGfxState_Rom_Exports *gUvGfxStateExports;
extern UvDGeom_Rom_Exports *gUvDGeomExports;
typedef struct { u8 unk00[0x28]; s32 (*hasFlags)(s32, s32); f32 (*axis)(s32, s32); } MenuAxisReplayExports;
extern f32 D_menuslct_00401668, D_menuslct_0040166C;
typedef struct { u8 unk00[4]; s16 value; u8 unk06[6]; } MenuInputRecord;
typedef struct { u8 unk00[8]; MenuInputRecord *records; } MenuInputState;
typedef struct { u8 unk00[0x24]; s32 (*busy)(void); } MenuInputGuiExports;
typedef struct { u8 unk00[0x28]; s32 (*hasFlags)(s32, s32); } MenuInputReplayExports;
#include "module.h"

/*__SEEDEXTERNS__*/
extern UvFont_Exports *gUvFontExports;
extern void *gGameGuiExports;
extern void *gReplayExports;
void menuslctDrawSolidRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 red, s32 green, s32 blue, s32 alpha);
void func_menuslct_004000F8();
s32 menuslctGetHorizontalInputAction(s32 controller, MenuInputState *state);
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state);
void func_menuslct_0040062C();
s32 menuslctFindFirstSelectedEntry(void *arg0);
s32 menuslctAreAllBytesNonzero(u8 *values, s16 count);
s32 menuslctAreAllBytesZero(u8 *values, s16 count);
void menuslctDrawSolidRectangle();
void menuslctDrawGradientRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 firstRed, s32 firstGreen, s32 firstBlue, s32 secondRed, s32 secondGreen, s32 secondBlue);
void func_menuslct_004010C4();
void menuslctDrawBottomLabel(s8 *label);
void func_menuslct_0040126C();
void func_menuslct_00401320();
void menuslctDrawBottomBlackPanel();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/__entrypoint_func_menuslct_400000.s")

#line 41 "src/modules/menuslct.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_menuslct_004000F0(void) {
}
#line 43 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004000F8.s")

#line 46 "src/modules/menuslct.c"
/* Return action seven for replay input mask 0x4000, or action eight
 * for masks 0x8000/0x1000 when the player entry is enabled. The global
 * GUI gate wins first. Preserve both original 0x1000 queries and their side effects. */
s32 menuslctGetConfirmOrCancelAction(s32 playerIndex, s32 playerEntries) {
    if ((*(s32 (**)(void))((u8 *)gGameGuiExports + 0x24))() != 0) {
        return 0;
    }
    if ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(playerIndex, 0x4000) != 0) {
        return 7;
    }
    if (*(s16 *)((u8 *)playerEntries + (playerIndex * 0xC) + 0x4) == -1) {
        return 0;
    }
    if ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(playerIndex, 0x8000) != 0) {
        return 8;
    }
    if (((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(playerIndex, 0x1000) != 0) || ((*(s32 (**)(s32, s32))((u8 *)gReplayExports + 0x28))(playerIndex, 0x1000) != 0)) {
        return 8;
    }
    return 0;
}
#line 64 "src/modules/menuslct.c"

#line 56 "src/modules/menuslct.c"
/* Return horizontal action one or two from axis zero or left/right replay
 * flags, giving the negative/left direction priority. A busy GUI or invalid
 * controller record suppresses input; replay flag tests remain level-triggered. */
s32 menuslctGetHorizontalInputAction(s32 controller, MenuInputState *state) {
    if (((MenuInputGuiExports *)gGameGuiExports)->busy() != 0) return 0;
    if (state->records[controller].value != -1) {
        if (((MenuAxisReplayExports *)gReplayExports)->axis(controller, 0) < D_menuslct_00401668 || ((MenuAxisReplayExports *)gReplayExports)->hasFlags(controller, 0x200) != 0) return 1;
        if (D_menuslct_0040166C < ((MenuAxisReplayExports *)gReplayExports)->axis(controller, 0) || ((MenuAxisReplayExports *)gReplayExports)->hasFlags(controller, 0x100) != 0) return 2;
    }
    return 0;
}
#line 57 "src/modules/menuslct.c"

#line 56 "src/modules/menuslct.c"
/* When the GUI is not busy and this controller has a valid record, map
 * replay flag 0x20 to action five and 0x10 to action six, in that order.
 * All other paths return zero; controller/table bounds remain unchanged. */
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state) {
    if (((MenuInputGuiExports *)gGameGuiExports)->busy() != 0) return 0;
    if (state->records[controller].value != -1) {
        if (((MenuInputReplayExports *)gReplayExports)->hasFlags(controller, 0x20) != 0) return 5;
        if (((MenuInputReplayExports *)gReplayExports)->hasFlags(controller, 0x10) != 0) return 6;
    }
    return 0;
}
#line 57 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040062C.s")

#line 60 "src/modules/menuslct.c"
/* Scan the signed-short entry count and return the first index whose
 * selection short equals one, or -1. Preserve the twenty-byte entry
 * stride and signed-short scan index. */
s32 menuslctFindFirstSelectedEntry(void *menu)
{
  s16 count;
  s16 index;
  void *entries;
  count = *((s16 *) (((u8 *) menu) + 0x0));
  index = 0;
  if (count > 0)
  {
    entries = (void *) (*((s32 *) (((u8 *) menu) + 0x8)));
    do
    {
      if ((*((s16 *) ((((u8 *) entries) + (index * 0x14)) + 0x2))) == 1)
      {
        return index;
      }
      index = index + 1;
    }
    while (index < count);
  }
  return -1;
  return -1;
}
#line 83 "src/modules/menuslct.c"

#line 80 "src/modules/menuslct.c"
/* Return one only when every byte in the signed-length range is nonzero.
 * Zero or negative lengths are vacuously true, as in the original. */
s32 menuslctAreAllBytesNonzero(u8 *values, s16 count) {
    s32 index;
    for (index = 0; index < count; index++) {
        if (values[index] == 0) return 0;
    }
    return 1;
}
#line 81 "src/modules/menuslct.c"

#line 82 "src/modules/menuslct.c"
/* Return one only when every byte in the signed-length range is zero.
 * Zero or negative lengths are vacuously true, as in the original. */
s32 menuslctAreAllBytesZero(u8 *values, s16 count) {
    s32 index;
    for (index = 0; index < count; index++) {
        if (values[index] != 0) return 0;
    }
    return 1;
}
#line 83 "src/modules/menuslct.c"

#line 84 "src/modules/menuslct.c"
/* Draw the caller rectangle with one RGBA color in the original 320-by-240
 * orthographic setup. Preserve vertex order, graphics-state push/pop and
 * untextured rendering flags rather than changing caller coordinates. */
void menuslctDrawSolidRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 red, s32 green, s32 blue, s32 alpha) {
    Mtx4F projection;
    Mtx4F model;
    gUvGfxStateExports->uvGfxStatePush();
    gUvGfxStateExports->uvGfxStateBindTexture(0xFFF);
    gUvGfxStateExports->func_uvgfxstate_rom_00401F54(0.0f,0.0f);
    gUvGfxStateExports->uvGfxResetDefaultRenderState();
    gUvGfxStateExports->uvGfxStateSetFlags(0x04820000);
    gUvGfxStateExports->uvGfxClearCurrentStateBits(0x337C0000);
    gUvGfxMgrExports->uvGfxAppendViewport(0,320,0,240);
    gUvFmtxExports->uvMat4SetOrtho(&projection,0.0f,320.0f,0.0f,240.0f);
    gUvFmtxExports->uvGfxMtxProjPushF(&projection);
    gUvFmtxExports->uvMat4SetIdentity(&model);
    gUvFmtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&model);
    gUvDGeomExports->uvVtxBeginPoly();
    gUvDGeomExports->uvVtx(firstX,firstY,0,0,0,red,green,blue,alpha);
    gUvDGeomExports->uvVtx(firstX,secondY,0,0,0,red,green,blue,alpha);
    gUvDGeomExports->uvVtx(secondX,secondY,0,0,0,red,green,blue,alpha);
    gUvDGeomExports->uvVtx(secondX,firstY,0,0,0,red,green,blue,alpha);
    gUvDGeomExports->uvVtxEndPoly();
    gUvGfxStateExports->uvGfxStatePop();
}
#line 85 "src/modules/menuslct.c"

#line 86 "src/modules/menuslct.c"
/* Draw the caller rectangle with distinct RGB colors on its two Y edges,
 * fully opaque alpha and the original orthographic setup. Preserve winding
 * and graphics-state restoration. */
void menuslctDrawGradientRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 firstRed, s32 firstGreen, s32 firstBlue, s32 secondRed, s32 secondGreen, s32 secondBlue) {
    Mtx4F projection;
    Mtx4F model;
    gUvGfxStateExports->uvGfxStatePush();
    gUvGfxStateExports->uvGfxStateBindTexture(0xFFF);
    gUvGfxStateExports->func_uvgfxstate_rom_00401F54(0.0f,0.0f);
    gUvGfxStateExports->uvGfxResetDefaultRenderState();
    gUvGfxStateExports->uvGfxStateSetFlags(0x04820000);
    gUvGfxStateExports->uvGfxClearCurrentStateBits(0x337C0000);
    gUvGfxMgrExports->uvGfxAppendViewport(0,320,0,240);
    gUvFmtxExports->uvMat4SetOrtho(&projection,0.0f,320.0f,0.0f,240.0f);
    gUvFmtxExports->uvGfxMtxProjPushF(&projection);
    gUvFmtxExports->uvMat4SetIdentity(&model);
    gUvFmtxExports->uvGfxMtxLoadProjectionWithQuarterTurn(&model);
    gUvDGeomExports->uvVtxBeginPoly();
    gUvDGeomExports->uvVtx(firstX,firstY,0,0,0,firstRed,firstGreen,firstBlue,255);
    gUvDGeomExports->uvVtx(firstX,secondY,0,0,0,secondRed,secondGreen,secondBlue,255);
    gUvDGeomExports->uvVtx(secondX,secondY,0,0,0,secondRed,secondGreen,secondBlue,255);
    gUvDGeomExports->uvVtx(secondX,firstY,0,0,0,firstRed,firstGreen,firstBlue,255);
    gUvDGeomExports->uvVtxEndPoly();
    gUvGfxStateExports->uvGfxStatePop();
}
#line 87 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_004010C4.s")

#line 90 "src/modules/menuslct.c"
/* Draw a black, opaque label centered at X=159 above the menu's bottom edge.
 * Font metrics determine the horizontal center and baseline. */
void menuslctDrawBottomLabel(s8 *label) {
    s32 height;
    s32 width;

    gUvFontExports->uvFontColor(0U, 0U, 0U, 0xFFU);
    gUvFontExports->uvSetFont(0);
    width = gUvFontExports->uvFontWidth(label);
    height = gUvFontExports->uvFontHeight();
    gUvFontExports->uvFontPrintStr(159 - (width / 2), 218 - height, label);
}
#line 91 "src/modules/menuslct.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_0040126C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/menuslct/func_menuslct_00401320.s")

#line 96 "src/modules/menuslct.c"
/* Draw the black rectangle from (22, 225) to (298, 16) with caller alpha;
 * retain the original coordinate order and graphics-state helper. */
void menuslctDrawBottomBlackPanel(s32 alpha) {
    menuslctDrawSolidRectangle(0x16, 0xE1, 0x12A, 0x10, 0, 0, 0, alpha);
}
#line 99 "src/modules/menuslct.c"

#line 100 "src/modules/menuslct.c"
/* Draw selected text in caller RGBA with black shadows, using a wider
 * shadow for font zero and none for font three. Unselected text uses
 * the fixed muted color and one-pixel shadow. Preserve the existing font-scale ABI. */
void menuslctDrawTextWithSelectionShadow(s32 x, s32 y, s32 fontId, s32 red, s32 green, s32 blue, s32 alpha, s32 textAddress, s32 selected) {
    s32 shadowOffset;

    shadowOffset = 2;
    (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(fontId);
    (*(void (*)(f64, f64))(*(s32 *)((u8 *)gUvFontExports + 0x8)))(1.0, 1.0);
    if (fontId == 0) {
        (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(2);
        shadowOffset = 4;
    }
    if (selected != 0) {
        if (fontId != 3) {
            (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xAF);
            (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(x + shadowOffset, y - shadowOffset, textAddress);
            (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(fontId);
            (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xFF);
            (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(x + 1, y - 1, textAddress);
        }
        (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))((u8)red, (u8)green, (u8)blue, (u8)alpha);
        (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(x, y, textAddress);
        return;
    }
    (*(void (*)(s32))(*(s32 *)((u8 *)gUvFontExports + 0x4)))(fontId);
    (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0, 0, 0, 0xFF);
    (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(x + 1, y - 1, textAddress);
    (*(void (*)(s32, s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0xC)))(0x78, 0x78, 0xBE, 0xE1);
    (*(void (*)(s32, s32, s32))(*(s32 *)((u8 *)gUvFontExports + 0x24)))(x, y, textAddress);
}
#line 128 "src/modules/menuslct.c"

