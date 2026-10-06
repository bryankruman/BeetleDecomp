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
void func_ripple_004002D8(void);
void addRipple(Mtx4F *mtx, f32 initSize);
void func_ripple_004005A0(s32 arg0);
s32 getActiveRippleCount(void);
void func_ripple_004006B8(void);
void resetRipple(void);

// .bss
s32 B_ripple_00400740[2]; // unreferenced padding
Ripple sRipples[MAX_RIPPLE];
s32 sActiveRippleCount;

void drawRipple(Ripple *ripple) {
    s32 nSize;
    s32 pSize;
    Mtx4F mtx;
    s32 alpha;

    alpha = (s32) (ripple->fade * 255.0f);
    pSize = (s32) (ripple->initSize * ripple->curSize * 100.0f);
    gUvFmtxExports->func_uvfmtx_rom_00400370(&mtx, &ripple->mtx);
    gUvFmtxExports->uvGfxMtxViewLoad(&mtx, 1U);
    gUvDGeomExports->uvVtxBeginPoly();
    nSize = -pSize;
    gUvDGeomExports->uvVtx(nSize, nSize, 0, -1024, -1024, 255, 255, 255, alpha);
    gUvDGeomExports->uvVtx(pSize, nSize, 0, 1024, -1024, 255, 255, 255, alpha);
    gUvDGeomExports->uvVtx(pSize, pSize, 0, 1024, 1024, 255, 255, 255, alpha);
    gUvDGeomExports->uvVtx(nSize, pSize, 0, -1024, 1024, 255, 255, 255, alpha);
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

void func_ripple_004002D8(void) {
    s32 i;
    Ripple *ripple;

    for (i = 0; i < ARRAY_COUNT(sRipples); i++) {
        ripple = &sRipples[i];
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

void func_ripple_004005A0(s32 arg0) {
    s32 sp1C;

    gUvChanExports->func_uvchannel_rom_00400288(arg0, 6, &sp1C, 0);
    if (sp1C != 0) {
        gUvCbckExports->uvAddCallback(sp1C, drawRipples, 0, 0xD2);
    }
}

void __entrypoint_func_ripple_400604(Ripple_Exports *exports) {
    int i;
    uvUpdateFileAllocPtr(exports);
    exports->resetRipple = resetRipple;
    exports->func_ripple_004006B8 = func_ripple_004006B8;
    exports->func_ripple_004002D8 = func_ripple_004002D8;
    exports->addRipple = addRipple;
    exports->func_ripple_004005A0 = func_ripple_004005A0;
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

void func_ripple_004006B8(void) {
    uvUnloadFile('UVTX', 125);
}

void resetRipple(void) {
    int i;
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(sRipples); i++) { sRipples[i].active = FALSE; }
    // clang-format on
    sActiveRippleCount = 0;
}

s32 D_ripple_00400730[] = {0x00180000, __entrypoint_func_ripple_400604, 0, 0};