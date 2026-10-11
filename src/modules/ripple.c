// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "macros.h"
#include "module.h"
#include "global_exports.h"

#define MAX_RIPPLE 48

typedef struct Ripple_s {
    Mtx4F mtx;
    f32 curSize;
    f32 fade;
    f32 initSize;
    s32 active;
} Ripple; // size = 0x50

void __entrypoint_func_ripple_400604(Ripple_Exports *exports);
void drawRipple(Ripple *ripple);
void drawRipples(s32 arg0);
void rippleAdvanceFadeAndSize(void);
void addRipple(Mtx4F *mtx, f32 initSize);
void rippleAttachDrawCallbackToChannel(s32 arg0);
s32 getActiveRippleCount(void);
void rippleUnloadSharedTexture(void);
void resetRipple(void);

// .bss
s32 B_ripple_00400740[2]; // unreferenced padding
Ripple sRipples[MAX_RIPPLE];
s32 sActiveRippleCount;

/*
 * Draw one XY quad at Z zero using the shared inverse-translation matrix and
 * a pushed view matrix. Convert fade times 255 and size product times 100 to
 * integers, emit four white vertices with texture coordinates +/-1024, then
 * end the polygon and pop the view matrix in the original order.
 * RE_ORIGINAL_QUIRK: Alpha and size are truncated without clamping; retain
 * negative/out-of-range values and the exact floating-point product order.
 * RE_UNKNOWN: Ripple validity, finite ranges and matrix/vertex capacity are
 * caller/provider preconditions; no clipping or allocation recovery is added.
 */
#line 32 "src/modules/ripple.c"
void drawRipple(Ripple *ripple) {
    s32 negatedSize;
    s32 scaledSize;
    Mtx4F translatedMatrix;
    s32 vertexAlpha;

    vertexAlpha = (s32) (ripple->fade * 255.0f);
    scaledSize = (s32) (ripple->initSize * ripple->curSize * 100.0f);
    gUvFmtxExports->uvMat4ApplySharedInverseTranslation(&translatedMatrix, &ripple->mtx);
    gUvFmtxExports->uvGfxMtxViewLoad(&translatedMatrix, 1U);
    gUvDGeomExports->uvVtxBeginPoly();
    negatedSize = -scaledSize;
    gUvDGeomExports->uvVtx(negatedSize, negatedSize, 0, -1024, -1024, 255, 255, 255, vertexAlpha);
    gUvDGeomExports->uvVtx(scaledSize, negatedSize, 0, 1024, -1024, 255, 255, 255, vertexAlpha);
    gUvDGeomExports->uvVtx(scaledSize, scaledSize, 0, 1024, 1024, 255, 255, 255, vertexAlpha);
    gUvDGeomExports->uvVtx(negatedSize, scaledSize, 0, -1024, 1024, 255, 255, 255, vertexAlpha);
    gUvDGeomExports->uvVtxEndPoly();
    gUvFmtxExports->uvGfxMtxFViewPop();
}

void drawRipples(s32 arg0) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(sRipples); i++) {
        if (sRipples[i].active) {
            break;
        }
    }

    if (i == ARRAY_COUNT(sRipples)) {
        return;
    }

    gUvGfxStateExports->uvGfxStatePush();
    gUvGfxStateExports->uvGfxStateBindTexture(0x7D);
    gUvGfxStateExports->uvGfxStateSetFlags(0x04E00000);
    for (; i < ARRAY_COUNT(sRipples); i++) {
        if (sRipples[i].active) {
            drawRipple(&sRipples[i]);
        }
    }
    gUvGfxStateExports->uvGfxStatePop();
}

#line 77 "src/modules/ripple.c"
/* Advance every active ripple by reducing fade by 0.02 and increasing
 * size by 0.01. Deactivate a ripple and decrement the active count when
 * fade is below zero or size exceeds one; preserve the original comparisons. */
void rippleAdvanceFadeAndSize(void) {
    s32 index;
    Ripple *ripple;

    for (index = 0; index < ARRAY_COUNT(sRipples); index++) {
        ripple = &sRipples[index];
        if (ripple->active) {
            ripple->fade -= 0.02f;
            ripple->curSize += 0.01f;
            if ((ripple->fade < 0.0) || (ripple->curSize > 1.0)) {
                ripple->active = FALSE;
                sActiveRippleCount -= 1;
            }
        }
    }
}
#line 93 "src/modules/ripple.c"

void addRipple(Mtx4F *mtx, f32 initSize) {
    s32 i;
    Ripple *ripple;

    for (i = 0; i < ARRAY_COUNT(sRipples); i++) {
        if (!sRipples[i].active) {
            break;
        }
    }

    if (i == ARRAY_COUNT(sRipples)) {
        return;
    }

    ripple = &sRipples[i];
    gUvFmtxExports->uvMat4FCopy(&ripple->mtx, mtx);
    gUvFmtxExports->uvMat4Scale(&ripple->mtx, 0.01f, 0.01f, 0.01f);
    ripple->initSize = initSize;
    ripple->curSize = 0;
    ripple->fade = 1;
    ripple->active = TRUE;
    sActiveRippleCount++;
}

#line 118 "src/modules/ripple.c"
/* Query channel property six and attach the ripple callback at priority
 * 210 only when the returned callback host is nonzero. */
void rippleAttachDrawCallbackToChannel(s32 channel) {
    s32 callbackHost;

    gUvChanExports->uvChannelGetProperties(channel, 6, &callbackHost, 0);
    if (callbackHost != 0) {
        gUvCbckExports->uvAddCallback(callbackHost, drawRipples, 0, 0xD2);
    }
}
#line 126 "src/modules/ripple.c"

void __entrypoint_func_ripple_400604(Ripple_Exports *exports) {
    int i;
    uvUpdateFileAllocPtr(exports);
    exports->resetRipple = resetRipple;
    exports->rippleUnloadSharedTexture = rippleUnloadSharedTexture;
    exports->rippleAdvanceFadeAndSize = rippleAdvanceFadeAndSize;
    exports->addRipple = addRipple;
    exports->rippleAttachDrawCallbackToChannel = rippleAttachDrawCallbackToChannel;
    exports->getActiveRippleCount = getActiveRippleCount;
#line 132
    uvLoadFile('UVTX', 125);
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(sRipples); i++) { sRipples[i].active = FALSE; }
    // clang-format on
    sActiveRippleCount = 0;
}

s32 getActiveRippleCount(void) {
    return sActiveRippleCount;
}

#line 143 "src/modules/ripple.c"
/* Unload the shared ripple texture, UVTX file 125, through the
 * original file manager. Preserve the fixed file identity and unload order. */
void rippleUnloadSharedTexture(void) {
    uvUnloadFile('UVTX', 125);
}
#line 146 "src/modules/ripple.c"

void resetRipple(void) {
    int i;
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(sRipples); i++) { sRipples[i].active = FALSE; }
    // clang-format on
    sActiveRippleCount = 0;
}

s32 D_ripple_00400730[] = {0x00180000, __entrypoint_func_ripple_400604, 0, 0};