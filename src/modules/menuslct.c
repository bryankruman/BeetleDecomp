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
/* Original GAMEGUI slot 0x24 returns shared debug byte D_gamegui_00402C68.
 * This is an input gate, not evidence of a general GUI busy-state API.
 * RE_UNKNOWN: historical caller return declaration and the byte's complete
 * state meanings. Preserve the existing full-word caller view here. */
typedef struct { u8 unused00[0x24]; s32 (*getDebugByte)(void); } MenuInputGuiExports;
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
/* Initializer-only address registry: these original words are addresses,
 * not an inferred callable API. Existing unresolved prototypes remain
 * unchanged; opaque linker code labels are never dereferenced or called here.
 * RE_UNKNOWN: recover each original target and its actual callers before
 * replacing unresolved declarations or expanding callback contracts. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 unknownCallback04Address;
    /* 0x08 */ u32 confirmOrCancelActionAddress;
    /* 0x0C */ u32 horizontalInputActionAddress;
    /* 0x10 */ u32 gatedInputActionAddress;
    /* 0x14 */ u32 unknownCallback14Address;
    /* 0x18 */ u32 findSelectedEntryAddress;
    /* 0x1C */ u32 allBytesNonzeroAddress;
    /* 0x20 */ u32 allBytesZeroAddress;
    /* 0x24 */ u32 drawSolidRectangleAddress;
    /* 0x28 */ u32 drawGradientRectangleAddress;
    /* 0x2C */ u32 unknownCallback2CAddress;
    /* 0x30 */ u32 drawBottomLabelAddress;
    /* 0x34 */ u32 unknownCallback34Address;
    /* 0x38 */ u32 unknownCallback38Address;
    /* 0x3C */ u32 drawBottomBlackPanelAddress;
    /* 0x40 */ u32 drawTextWithSelectionShadowAddress;
} MenuSlctExportAddresses;
void func_menuslct_004000F0(void);
s32 menuslctGetConfirmOrCancelAction(s32 playerIndex, s32 playerEntries);
s32 menuslctGetHorizontalInputAction(s32 controller, MenuInputState *state);
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state);
s32 menuslctFindFirstSelectedEntry(void *menu);
s32 menuslctAreAllBytesNonzero(u8 *values, s16 count);
s32 menuslctAreAllBytesZero(u8 *values, s16 count);
void menuslctDrawSolidRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 red, s32 green, s32 blue, s32 alpha);
void menuslctDrawGradientRectangle(s32 firstX, s32 firstY, s32 secondX, s32 secondY, s32 firstRed, s32 firstGreen, s32 firstBlue, s32 secondRed, s32 secondGreen, s32 secondBlue);
void menuslctDrawBottomLabel(s8 *label);
void menuslctDrawBottomBlackPanel(s32 alpha);
void menuslctDrawTextWithSelectionShadow(s32 x, s32 y, s32 fontId, s32 red, s32 green, s32 blue, s32 alpha, s32 textAddress, s32 selected);

#line 80 "src/modules/menuslct.c"
/* Register the seventeen original menu-selector callback addresses after
 * updating the allocation pointer. Preserve the original interleaving of
 * input/drawing slots and the empty callback's separate identity; this
 * initializer performs no other state reset or dependency load.
 * RE_UNKNOWN: callback 0x04/14/2C/34/38 contracts and caller-owned table
 * capacity/lifetime require their original implementations and table users.
 * The address registry is not a recovered callable interface; input bounds,
 * flags and drawing state remain the individual callbacks' caller contracts. */
void __entrypoint_func_menuslctInitializeModuleExports(MenuSlctExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_menuslct_004000F0;
    exports->drawGradientRectangleAddress = (u32) menuslctDrawGradientRectangle;
    exports->unknownCallback04Address = (u32) func_menuslct_004000F8;
    exports->unknownCallback2CAddress = (u32) func_menuslct_004010C4;
    exports->confirmOrCancelActionAddress = (u32) menuslctGetConfirmOrCancelAction;
    exports->drawBottomLabelAddress = (u32) menuslctDrawBottomLabel;
    exports->horizontalInputActionAddress = (u32) menuslctGetHorizontalInputAction;
    exports->unknownCallback34Address = (u32) func_menuslct_0040126C;
    exports->gatedInputActionAddress = (u32) menuslctGetGatedInputAction;
    exports->unknownCallback38Address = (u32) func_menuslct_00401320;
    exports->unknownCallback14Address = (u32) func_menuslct_0040062C;
    exports->drawBottomBlackPanelAddress = (u32) menuslctDrawBottomBlackPanel;
    exports->findSelectedEntryAddress = (u32) menuslctFindFirstSelectedEntry;
    exports->drawTextWithSelectionShadowAddress = (u32) menuslctDrawTextWithSelectionShadow;
    exports->allBytesNonzeroAddress = (u32) menuslctAreAllBytesNonzero;
    exports->allBytesZeroAddress = (u32) menuslctAreAllBytesZero;
    exports->drawSolidRectangleAddress = (u32) menuslctDrawSolidRectangle;
}
#line 81 "src/modules/menuslct.c"

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

/* Return action 7 for replay mask 0x4000 or action 8 for 0x8000/0x1000 when
 * the player entry is enabled. A nonzero GAMEGUI slot 0x24 debug byte gates all input
 * first. Preserve both 0x1000 queries and the existing raw-word return view.
 * RE_UNKNOWN: the debug byte's complete state meanings and player-entry bounds.
 * Trace original byte writers/menu consumers and entry allocation to resolve. */
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

/* Return horizontal action 1/2 from axis 0 or left/right replay flags, giving
 * the negative/left direction priority. A nonzero GAMEGUI slot 0x24 debug byte or an
 * invalid controller record suppresses input; preserve every replay query.
 * RE_UNKNOWN: debug-byte state meanings and caller record bounds. Resolve the
 * original byte writers/menu consumers and state allocation before rewrite. */
s32 menuslctGetHorizontalInputAction(s32 controller, MenuInputState *state) {
    if (((MenuInputGuiExports *)gGameGuiExports)->getDebugByte() != 0) return 0;
    if (state->records[controller].value != -1) {
        if (((MenuAxisReplayExports *)gReplayExports)->axis(controller, 0) < D_menuslct_00401668 || ((MenuAxisReplayExports *)gReplayExports)->hasFlags(controller, 0x200) != 0) return 1;
        if (D_menuslct_0040166C < ((MenuAxisReplayExports *)gReplayExports)->axis(controller, 0) || ((MenuAxisReplayExports *)gReplayExports)->hasFlags(controller, 0x100) != 0) return 2;
    }
    return 0;
}
#line 57 "src/modules/menuslct.c"

#line 56 "src/modules/menuslct.c"

/* When the GAMEGUI slot 0x24 debug byte is zero and the controller record is valid,
 * map replay flag 0x20 to action 5 and 0x10 to action 6 in that order; otherwise
 * return zero. The original target is a debug-byte getter, not a busy query.
 * RE_UNKNOWN: complete debug-byte states and controller/table bounds. Trace
 * original byte writers, menu consumers and record allocation before rewrite. */
s32 menuslctGetGatedInputAction(s32 controller, MenuInputState *state) {
    if (((MenuInputGuiExports *)gGameGuiExports)->getDebugByte() != 0) return 0;
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
    gUvGfxStateExports->uvGfxSetFogParameters(0.0f,0.0f);
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
    gUvGfxStateExports->uvGfxSetFogParameters(0.0f,0.0f);
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

