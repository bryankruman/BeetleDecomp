// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvcback_rom.h"
#include "uvfmtx_rom.h"
#include "uvgfxmgr_rom.h"
#include "uvimtx_rom.h"
#include "uvmath_rom.h"

/* Original readonly objects in module order: two double-precision
 * thresholds followed by the single-precision fog factor limits.
 * Preserve both independent threshold objects and their exact precision. */
const f64 D_uvgfxstate_rom_00402C00[1] = { 0.1 };
const f64 D_uvgfxstate_rom_00402C08[1] = { 0.1 };



typedef struct UnkStruct_uvgfxstate_rom_00402D18_s {
    char pad[4];
    void (*unk4)(s32);
} UnkStruct_uvgfxstate_rom_00402D18;

typedef struct UnkStruct_uvgfxstate_rom_00402D14_s {
    char pad[0x10];
    s32 (*unk10)(s32);
    void (*unk14)(void);
} UnkStruct_uvgfxstate_rom_00402D14;

typedef struct UnkStruct_80001724_s {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ s32 unk14;                           /* inferred */
    /* 0x18 */ char pad18[4];
    /* 0x1C */ u16 unk1C;                           /* inferred */
    /* 0x1E */ u16 unk1E;                            /* inferred */
} UnkStruct_80001724;                               /* size = 0x1F */

extern s32 D_uvgfxstate_rom_00402C48;

void __entrypoint_func_uvgfxstate_rom_400000(UvGfxState_Rom_Exports* exports);
void uvGfxStateDraw(uvGfxState *); /* extern */
void uvGfxClampLook(LookAt *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                    f32 arg8, f32 arg9);
void func_uvgfxstate_rom_00400C68(LookAt *arg0, Hilite *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                                  f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11,
                                  f32 arg12, f32 arg13, f32 arg14, f32 arg15, f32 arg16, s32 arg17,
                                  s32 arg18);

void uvGfxStateCleanup(void);
void uvGfxSetColorDither(u32 mode);
void uvGfxEmitLookAtAndOptionalHilites(Mtx4F *arg0, s32 arg1);
void uvGfxStateSetFlags(s32 arg0);
void uvGfxClearCurrentStateBits(s32 arg0);
void uvGfxStateBindTexture(s32 arg0);
void uvGfxStateClearBits(uvGfxState *gs, s32 arg1);
void uvGfxStateSetBits(uvGfxState *gs, s32 arg1);
void uvGfxStateSetTextureId(uvGfxState *gs, s32 arg1);
void uvGfxStateReplaceTextureId(uvGfxState *arg0, s32 arg1, s32 arg2);
s32 uvGfxStateHasTextureId(uvGfxState *arg0, s32 arg1);
void uvGfxSetSharedStateWord50(s32 arg0);
void uvGfxSetSharedStateWord4C(s32 arg0);
void uvGfxDrawStateThroughDepthAndColorPasses(uvGfxState *gs);
void uvGfxResetDefaultRenderState(void);
void uvGfxBeginStateFrame(s32 arg0);
void uvGfxSetTerrainDepthBufferEnabled(s32 arg0);
void uvGfxSetFogParameters(f32 arg0, f32 arg1);
void uvGfxGetFogParameters(f32 *arg0, f32 *arg1);
void uvGfxSetCullFaces(s32 arg0, s32 arg1);
void uvGfxStatePush(void);
void uvGfxStatePop(void);
void uvGfxResetShadeCombineMode(void);
s32 uvGfxGetPreviousBufferCounter(u32 arg0);
void uvGfxSetSharedStateWords(s32 arg0, s32 arg1);
void uvGfxSetHiliteVector(s32 arg0, Vec3F arg1);
void uvGfxSync(void); /* extern */
void uvGfxDrawTextureRectangleWithUvRange(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6,
                                  f32 arg7);
// .bss
extern UvFMtx_Rom_Exports *sUvFmtxExports;
extern UvGfxMgr_Exports *sUvGfxMgrExports;
extern UvMath_Exports *sUvMathExports;
extern UvImtx_Rom_Exports *sUvImtxExports;

// Not classified yet
extern Vec3F D_uvgfxstate_rom_00402C60[];
extern s32 D_uvgfxstate_rom_00402D30;
extern s32 D_uvgfxstate_rom_00402DEC;
extern s32 D_uvgfxstate_rom_00402DF0;
extern LookAt *D_uvgfxstate_rom_00402DF8[];
extern s32 D_uvgfxstate_rom_00402E00;
extern s32 D_uvgfxstate_rom_00402E04;
extern Hilite *D_uvgfxstate_rom_00402E08[];
extern UvFMtx_Rom_Exports *sUvFmtxExports;
extern UvGfxMgr_Exports *sUvGfxMgrExports;
extern UvMath_Exports *sUvMathExports;
extern UvImtx_Rom_Exports *sUvImtxExports;
extern UvCback_Exports *sUvCbackExports;
extern s32 D_uvgfxstate_rom_00402D00;
extern s32 D_uvgfxstate_rom_00402D30;
extern s32 D_uvgfxstate_rom_00402D60[];
extern s32 D_uvgfxstate_rom_00402C50;
extern s32 D_uvgfxstate_rom_00402C4C;
extern s32 D_uvgfxstate_rom_00402D38[];
extern s32 D_uvgfxstate_rom_00402D40[];
extern s32 D_uvgfxstate_rom_00402D48[];
extern s32 D_uvgfxstate_rom_00402D50[];
extern s32 D_uvgfxstate_rom_00402D58[];
extern s32 D_uvgfxstate_rom_00402C5C;
extern f32 D_uvgfxstate_rom_00402C54;
extern f32 D_uvgfxstate_rom_00402C58;
extern Gfx D_uvgfxstate_rom_00402C78[];
extern UnkStruct_uvgfxstate_rom_00402D14 *D_uvgfxstate_rom_00402D14;
extern UnkStruct_uvgfxstate_rom_00402D18 *D_uvgfxstate_rom_00402D18;
extern s32 D_uvgfxstate_rom_00402D68[];
extern u8 D_uvgfxstate_rom_00402DE8;
extern s32 D_uvgfxstate_rom_00402C40;
extern s32 D_uvgfxstate_rom_00402D2C;

extern s32 D_uvgfxstate_rom_00402D04;
extern s32 D_uvgfxstate_rom_00402D08;
extern void* D_uvgfxstate_rom_00402D10;

/* Publish graphics-state exports, choose allocation counts for two buffers, import providers, and register the frame callback. */
#line 122 "src/modules/uvgfxstate_rom.c"
void __entrypoint_func_uvgfxstate_rom_400000(UvGfxState_Rom_Exports* moduleExports) {
    s32 bufferIndex;
    s32* allocationCounts;

    uvUpdateFileAllocPtr(moduleExports);
    moduleExports->uvGfxSetColorDither = uvGfxSetColorDither;
    moduleExports->uvGfxEmitLookAtAndOptionalHilites = uvGfxEmitLookAtAndOptionalHilites;
    moduleExports->uvGfxStateSetFlags = uvGfxStateSetFlags;
    moduleExports->uvGfxClearCurrentStateBits = uvGfxClearCurrentStateBits;
    moduleExports->uvGfxStateBindTexture = uvGfxStateBindTexture;
    moduleExports->uvGfxStateClearBits = uvGfxStateClearBits;
    moduleExports->uvGfxStateSetBits = uvGfxStateSetBits;
    moduleExports->uvGfxStateSetTextureId = uvGfxStateSetTextureId;
    moduleExports->uvGfxStateReplaceTextureId = uvGfxStateReplaceTextureId;
    moduleExports->uvGfxStateCleanup = uvGfxStateCleanup;
    moduleExports->uvGfxStateHasTextureId = uvGfxStateHasTextureId;
    moduleExports->uvGfxStatePush = uvGfxStatePush;
    moduleExports->uvGfxSetSharedStateWord50 = uvGfxSetSharedStateWord50;
    moduleExports->uvGfxStatePop = uvGfxStatePop;
    moduleExports->uvGfxSetSharedStateWord4C = uvGfxSetSharedStateWord4C;
    moduleExports->uvGfxResetShadeCombineMode = uvGfxResetShadeCombineMode;
    moduleExports->uvGfxDrawStateThroughDepthAndColorPasses = uvGfxDrawStateThroughDepthAndColorPasses;
    moduleExports->uvGfxDrawTextureRectangleWithUvRange = uvGfxDrawTextureRectangleWithUvRange;
    moduleExports->uvGfxStateDraw = uvGfxStateDraw;
    moduleExports->uvGfxGetPreviousBufferCounter = uvGfxGetPreviousBufferCounter;
    moduleExports->uvGfxResetDefaultRenderState = uvGfxResetDefaultRenderState;
    moduleExports->uvGfxSetSharedStateWords = uvGfxSetSharedStateWords;
    moduleExports->uvGfxSetTerrainDepthBufferEnabled = uvGfxSetTerrainDepthBufferEnabled;
    moduleExports->uvGfxSetHiliteVector = uvGfxSetHiliteVector;
    moduleExports->uvGfxSetFogParameters = uvGfxSetFogParameters;
    moduleExports->uvGfxSync = uvGfxSync;
    moduleExports->uvGfxGetFogParameters = uvGfxGetFogParameters;
    moduleExports->uvGfxSetCullFaces = uvGfxSetCullFaces;
    moduleExports->unk70 = &D_uvgfxstate_rom_00402D00;
    moduleExports->unk74 = &D_uvgfxstate_rom_00402D04;
    moduleExports->unk78 = &D_uvgfxstate_rom_00402D08;
    #line 1
    allocationCounts = uvGetSystemProp(0x14); /* Read two count words with independent defaults; RE_UNKNOWN: property extent and signed count domains need producer proof. */
    #line 45
    if (allocationCounts == NULL) {
        D_uvgfxstate_rom_00402DEC = 30;
        if (D_uvgfxstate_rom_00402E00) {} // FAKE; RE_UNKNOWN: historical source/scaffold shape is unproved; retain exact lowering.
        D_uvgfxstate_rom_00402E00 = 1;
    } else {
        if (allocationCounts[0] != 0) {
            D_uvgfxstate_rom_00402DEC = allocationCounts[0];
        } else {
            D_uvgfxstate_rom_00402DEC = 0x1E;
        }

        if (allocationCounts[1] != 0) {
            D_uvgfxstate_rom_00402E00 = allocationCounts[1];
        } else {
            D_uvgfxstate_rom_00402E00 = 1;
        }
    }

    for (bufferIndex = 0; bufferIndex < 2; bufferIndex++) { /* Allocate only for positive counts; preserve existing slots otherwise. */
        if (D_uvgfxstate_rom_00402DEC > 0) {
            D_uvgfxstate_rom_00402DF8[bufferIndex] = _uvMemAlloc(D_uvgfxstate_rom_00402DEC * 0x20, 8U); /* RE_UNKNOWN: scaled sizes, allocation failure, storage extent/lifetime need allocator/caller proof. */
        }
        if (D_uvgfxstate_rom_00402E00 > 0) {
            D_uvgfxstate_rom_00402E08[bufferIndex] = _uvMemAlloc(D_uvgfxstate_rom_00402E00 * 0x10, 8U);
        }
    }

    sUvGfxMgrExports = uvLoadModule('GMGR'); /* Keep all eight provider loads in order; RE_UNKNOWN: replacement/export lifetimes need module-loader/caller proof. */
    D_uvgfxstate_rom_00402D10 = uvLoadModule('GEOM');
    D_uvgfxstate_rom_00402D14 = uvLoadModule('TEXT');
    D_uvgfxstate_rom_00402D18 = uvLoadModule('LGHT');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvImtxExports = uvLoadModule('IMTX');
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvMathExports = uvLoadModule('MATH');
    D_uvgfxstate_rom_00402C4C = 0;
    D_uvgfxstate_rom_00402C50 = 0;
    sUvCbackExports->uvAddCallback(sUvGfxMgrExports->uvGfxGetCallbackList(1), uvGfxBeginStateFrame, 0, 0); /* Register after the callback-list lookup; RE_UNKNOWN: callback/list capacity and invocation lifetime need owner proof. */
}

// Module cleanup function
#line 194 "src/modules/uvgfxstate_rom.c"
/* Remove the frame callback and unload all eight graphics-state dependencies. */
void uvGfxStateCleanup(void) {
    sUvCbackExports->uvRemoveCallback(sUvGfxMgrExports->uvGfxGetCallbackList(1),
                                               (s32) uvGfxBeginStateFrame);
    uvUnloadModule('GMGR');
    uvUnloadModule('GEOM');
    uvUnloadModule('TEXT');
    uvUnloadModule('CBCK');
    uvUnloadModule('LGHT');
    uvUnloadModule('IMTX');
    uvUnloadModule('FMTX');
    uvUnloadModule('MATH');
}
#line 206 "src/modules/uvgfxstate_rom.c"

#line 207 "src/modules/uvgfxstate_rom.c"
/* Synchronize graphics state and emit the requested color-dither command. */
void uvGfxSetColorDither(u32 mode) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    uvGfxSync();
    gDPSetColorDither(gdl[0]++, mode);
}
#line 214 "src/modules/uvgfxstate_rom.c"

#line 215 "src/modules/uvgfxstate_rom.c"
/* Allocate a look-at record from the current frame bank and emit it.
 * Unless look-at-only is requested, also allocate and configure two
 * highlight tiles when their original capacity check permits. */
void uvGfxEmitLookAtAndOptionalHilites(Mtx4F *modelTransform, s32 lookAtOnly) {
    Mtx4F viewTransform;
    Mtx4F inverseViewTransform;
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();

    if (D_uvgfxstate_rom_00402DEC > D_uvgfxstate_rom_00402DF0) {
        sUvFmtxExports->uvGfxMtxCopySharedFloatMatrix(&viewTransform);
        sUvFmtxExports->uvMat4InvertTranslationRotation(&inverseViewTransform, &viewTransform);
        if (lookAtOnly != 0) {
            uvGfxClampLook(
                &D_uvgfxstate_rom_00402DF8[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402DF0],
                inverseViewTransform.m[3][0], inverseViewTransform.m[3][1], inverseViewTransform.m[3][2], modelTransform->m[3][0], modelTransform->m[3][1], modelTransform->m[3][2],
                inverseViewTransform.m[1][0], inverseViewTransform.m[1][1], inverseViewTransform.m[1][2]);
            goto lookAt; // Required to match
        }
        if (D_uvgfxstate_rom_00402E04 < D_uvgfxstate_rom_00402E00) {
            func_uvgfxstate_rom_00400C68(
                &D_uvgfxstate_rom_00402DF8[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402DF0],
                &D_uvgfxstate_rom_00402E08[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402E04], 0.0f,
                0.0f, 500.0f, modelTransform->m[3][0], modelTransform->m[3][1], modelTransform->m[3][2], 0.0f, 1.0f, 0.0f,
                D_uvgfxstate_rom_00402C60->x, D_uvgfxstate_rom_00402C60->y,
                D_uvgfxstate_rom_00402C60->z, D_uvgfxstate_rom_00402C60[1].x,
                D_uvgfxstate_rom_00402C60[1].y, D_uvgfxstate_rom_00402C60[1].z, 32, 32);
            gDPSetHilite1Tile(gdl[0]++, G_TX_RENDERTILE, &D_uvgfxstate_rom_00402E08[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402E04], 32, 32);
            gDPSetHilite2Tile(gdl[0]++, G_TX_MIRROR, &D_uvgfxstate_rom_00402E08[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402E04], 32, 32);
            D_uvgfxstate_rom_00402E04++;
        lookAt:
            uvGfxSync();
            gSPLookAt(gdl[0]++,
                      &D_uvgfxstate_rom_00402DF8[D_uvgfxstate_rom_00402D30][D_uvgfxstate_rom_00402DF0])
                D_uvgfxstate_rom_00402DF0++;
        }
    }
}
#line 251 "src/modules/uvgfxstate_rom.c"

/* Build and pack two LookAt directions from a point difference and successive cross products. */
#line 252 "src/modules/uvgfxstate_rom.c"
void uvGfxClampLook(LookAt *outputLookAt, f32 pointAX, f32 pointAY, f32 pointAZ, f32 pointBX, f32 pointBY, f32 pointBZ, f32 referenceAxisX,
                    f32 referenceAxisY, f32 referenceAxisZ) {
    f32 lengthScale;
    f32 directionX;
    f32 directionY;
    f32 directionZ;
    f32 crossAxisX;
    f32 crossAxisY;
    f32 crossAxisZ;

    directionX = pointBX - pointAX; /* Use the point difference and retain grouped FP operations; RE_UNKNOWN: input/FPU-exception contracts need callers. */
    directionY = pointBY - pointAY;
    directionZ = pointBZ - pointAZ;

    lengthScale = sqrtf(SQ(directionX) + SQ(directionY) + SQ(directionZ));
    if (lengthScale != 0.0f) {
        lengthScale = -1.0f / lengthScale;
    } else {
        lengthScale = -255.0f; /* Keep the zero-length fallback, distinct from the later positive fallbacks. */
    }
    directionX *= lengthScale;
    directionY *= lengthScale;
    directionZ *= lengthScale;

    crossAxisX = (referenceAxisY * directionZ) - (referenceAxisZ * directionY);
    crossAxisY = (referenceAxisZ * directionX) - (referenceAxisX * directionZ);
    crossAxisZ = (referenceAxisX * directionY) - (referenceAxisY * directionX);

    lengthScale = sqrtf(SQ(crossAxisX) + SQ(crossAxisY) + SQ(crossAxisZ));
    if (lengthScale != 0.0f) {
        lengthScale = 1.0f / lengthScale;
    } else {
        lengthScale = 255.0f;
    }
    crossAxisX *= lengthScale;
    crossAxisY *= lengthScale;
    crossAxisZ *= lengthScale;

    referenceAxisX = (directionY * crossAxisZ) - (directionZ * crossAxisY); /* Reuse the input components for the second cross-axis; retain component order. */
    referenceAxisY = (directionZ * crossAxisX) - (directionX * crossAxisZ);
    referenceAxisZ = (directionX * crossAxisY) - (directionY * crossAxisX);

    lengthScale = sqrtf(SQ(referenceAxisX) + SQ(referenceAxisY) + SQ(referenceAxisZ));
    if (lengthScale != 0.0f) {
        lengthScale = 1.0f / lengthScale;
    } else {
        lengthScale = 255.0f;
    }
    referenceAxisX *= lengthScale;
    referenceAxisY *= lengthScale;
    referenceAxisZ *= lengthScale;

    outputLookAt->l[0].l.dir[0] = (s32) MIN(crossAxisX * 128.0f, 127.0f) & 0xFF; /* Retain upper-only limits, truncation and byte stores; RE_UNKNOWN: axis convention and output storage/lifetime need consumers/callers. */
    outputLookAt->l[0].l.dir[1] = (s32) MIN(crossAxisY * 128.0f, 127.0f) & 0xFF;
    outputLookAt->l[0].l.dir[2] = (s32) MIN(crossAxisZ * 128.0f, 127.0f) & 0xFF;

    outputLookAt->l[1].l.dir[0] = (s32) MIN(referenceAxisX * 128.0f, 127.0f) & 0xFF;
    outputLookAt->l[1].l.dir[1] = (s32) MIN(referenceAxisY * 128.0f, 127.0f) & 0xFF;
    outputLookAt->l[1].l.dir[2] = (s32) MIN(referenceAxisZ * 128.0f, 127.0f) & 0xFF;
    outputLookAt->l[0].l.col[0] = 0;
    outputLookAt->l[0].l.col[1] = 0;
    outputLookAt->l[0].l.col[2] = 0;
    outputLookAt->l[0].l.pad1 = 0;
    outputLookAt->l[0].l.colc[0] = 0;
    outputLookAt->l[0].l.colc[1] = 0;
    outputLookAt->l[0].l.colc[2] = 0;
    outputLookAt->l[0].l.pad2 = 0;
    outputLookAt->l[1].l.col[0] = 0;
    outputLookAt->l[1].l.col[1] = 0x80;
    outputLookAt->l[1].l.col[2] = 0;
    outputLookAt->l[1].l.pad1 = 0;
    outputLookAt->l[1].l.colc[0] = 0;
    outputLookAt->l[1].l.colc[1] = 0x80;
    outputLookAt->l[1].l.colc[2] = 0;
    outputLookAt->l[1].l.pad2 = 0;
}

#if 0
extern const f64 D_uvgfxstate_rom_00402C00[1];
extern const f64 D_uvgfxstate_rom_00402C08[1];

void func_uvgfxstate_rom_00400C68(LookAt* arg0, Hilite* arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11, f32 arg12, f32 arg13, f32 arg14, f32 arg15, f32 arg16, s32 arg17, s32 arg18) {
    f32 temp_fa0;
    f32 temp_fa1_3;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 temp_fs3;
    f32 temp_ft4_3;
    f32 temp_ft5_3;
    s32 pad[4];
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fv1;

    temp_fs1 = arg5 - arg2;
    temp_fs2 = arg6 - arg3;
    temp_fs3 = arg7 - arg4;

    temp_fv1 = -1.0 / sqrtf(SQ(temp_fs1) + SQ(temp_fs2) + SQ(temp_fs3));
    temp_fs1 *= temp_fv1;
    temp_fs2 *= temp_fv1;
    temp_fs3 *= temp_fv1;

    sp74 = (arg9 * temp_fs3) - (arg10 * temp_fs2);
    sp70 = (arg10 * temp_fs1) - (arg8 * temp_fs3);
    sp6C = (arg8 * temp_fs2) - (arg9 * temp_fs1);

    temp_fv1 = 1.0 / sqrtf(SQ(sp74) + SQ(sp70) + SQ(sp6C));

    sp74 *= temp_fv1;
    sp70 *= temp_fv1;
    sp6C *= temp_fv1;

    arg8 = (temp_fs2 * sp6C) - (temp_fs3 * sp70);
    arg9 = (temp_fs3 * sp74) - (temp_fs1 * sp6C);
    arg10 = (temp_fs1 * sp70) - (temp_fs2 * sp74);

    temp_fv1 = 1.0 / sqrtf(SQ(arg8) + SQ(arg9) + SQ(arg10));
    arg8 *= temp_fv1;
    arg9 *= temp_fv1;
    arg10 *= temp_fv1;

    temp_fv1 = 1.0 / sqrtf(SQ(arg11) + SQ(arg12) + SQ(arg13));
    arg11 *= temp_fv1;
    arg12 *= temp_fv1;
    arg13 *= temp_fv1;

    sp4C = arg11 + temp_fs1;
    sp48 = arg12 + temp_fs2;
    sp44 = arg13 + temp_fs3;

    temp_fv1 = sqrtf(SQ(sp44)+ SQ(sp48) + SQ(sp4C));
    if (D_uvgfxstate_rom_00402C00[0] < temp_fv1) {
        temp_fa0 = 1.0 / temp_fv1;
        temp_fa1_3 = sp4C * temp_fa0;
        temp_ft4_3 = sp48 * temp_fa0;
        temp_ft5_3 = sp44 * temp_fa0;
        arg1->h.x1 = ((arg17 * 4) + (((temp_fa1_3 * sp74) + (temp_ft4_3 * sp70) + (temp_ft5_3 * sp6C)) * arg17 * 2));
        arg1->h.y1 = ((arg18 * 4) + (((temp_fa1_3 * arg8) + (temp_ft4_3 * arg9) + (temp_ft5_3 * arg10)) * arg18 * 2));
    } else {
        arg1->h.x1 = arg17 * 2;
        arg1->h.y1 = arg18 * 2;
    }
    temp_fv1 = 1.0 / sqrtf(SQ(arg14) + SQ(arg15) + SQ(arg16));

    arg14 *= temp_fv1;
    arg15 *= temp_fv1;
    arg16 *= temp_fv1;

    sp4C = arg14 + temp_fs1;
    sp48 = arg15 + temp_fs2;
    sp44 = arg16 + temp_fs3;

    temp_fv1 = sqrtf(SQ(sp44)+ SQ(sp48) + SQ(sp4C));
    if (D_uvgfxstate_rom_00402C08[0] < temp_fv1) {
        temp_fa0 = 1.0 / temp_fv1;
        temp_fa1_3 = sp4C * temp_fa0;
        temp_ft4_3 = sp48 * temp_fa0;
        temp_ft5_3 = sp44 * temp_fa0;
        arg1->h.x2 = (arg17 * 4) + (((temp_fa1_3 * sp74) + (temp_ft4_3 * sp70) + (temp_ft5_3 * sp6C)) * arg17 * 2);
        arg1->h.y2 = (arg18 * 4) + (((temp_fa1_3 * arg8) + (temp_ft4_3 * arg9) + (temp_ft5_3 * arg10)) * arg18 * 2);
    } else {
        arg1->h.x2 = arg17 * 2;
        arg1->h.y2 = arg18 * 2;
    }


    arg0->l[0].l.dir[0] = (s32) MIN(sp74 * 128.0f, 127.0f) & 0xFF;
    arg0->l[0].l.dir[1] = (s32) MIN(sp70 * 128.0f, 127.0f) & 0xFF;
    arg0->l[0].l.dir[2] = (s32) MIN(sp6C * 128.0f, 127.0f) & 0xFF;
    arg0->l[1].l.dir[0] = (s32) MIN(arg8 * 128.0f, 127.0f) & 0xFF;
    arg0->l[1].l.dir[1] = (s32) MIN(arg9 * 128.0f, 127.0f) & 0xFF;
    arg0->l[1].l.dir[2] = (s32) MIN(arg10 * 128.0f, 127.0f) & 0xFF;
    arg0->l[0].l.col[0] = 0;
    arg0->l[0].l.col[1] = 0;
    arg0->l[0].l.col[2] = 0;
    arg0->l[0].l.pad1 = 0;
    arg0->l[0].l.colc[0] = 0;
    arg0->l[0].l.colc[1] = 0;
    arg0->l[0].l.colc[2] = 0;
    arg0->l[0].l.pad2 = 0;
    arg0->l[1].l.col[0] = 0;
    arg0->l[1].l.col[1] = 0x80;
    arg0->l[1].l.col[2] = 0;
    arg0->l[1].l.pad1 = 0;
    arg0->l[1].l.colc[0] = 0;
    arg0->l[1].l.colc[1] = 0x80;
    arg0->l[1].l.colc[2] = 0;
    arg0->l[1].l.pad2 = 0;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvgfxstate_rom/func_uvgfxstate_rom_00400C68.s")
#endif

#line 450 "src/modules/uvgfxstate_rom.c"

void uvGfxStateSetFlags(s32 flagsToSet) {
    s32 requestedState;

    requestedState = flagsToSet | D_uvgfxstate_rom_00402C48;
    if (requestedState != D_uvgfxstate_rom_00402C48) {
        uvGfxState stateUpdate;
        stateUpdate.state = requestedState;
        stateUpdate.unkC = -1;
        stateUpdate.displayList = 0;
        uvGfxStateDraw(&stateUpdate);
    }
}
#line 462 "src/modules/uvgfxstate_rom.c"

#line 463 "src/modules/uvgfxstate_rom.c"
/* Draw a state update only when clearing the requested bits changes
 * the current state word; preserve the original sentinel and null display list. */
void uvGfxClearCurrentStateBits(s32 mask) {
    s32 stateWord;
    uvGfxState state;

    stateWord = ~mask & D_uvgfxstate_rom_00402C48;
    if (stateWord != D_uvgfxstate_rom_00402C48) {
        state.state = stateWord;
        state.unkC = -1;
        state.displayList = NULL;
        uvGfxStateDraw(&state);
    }
}
#line 475 "src/modules/uvgfxstate_rom.c"

#line 476 "src/modules/uvgfxstate_rom.c"

void uvGfxStateBindTexture(s32 textureStateBits) {
    uvGfxState stateUpdate;

    stateUpdate.displayList = NULL;
    stateUpdate.unkC = -1;
    stateUpdate.state = (D_uvgfxstate_rom_00402C48 & ~0xFFF) | textureStateBits;
    uvGfxStateDraw(&stateUpdate);
}
#line 484 "src/modules/uvgfxstate_rom.c"

#line 485 "src/modules/uvgfxstate_rom.c"
/* Clear the requested state bits. */
void uvGfxStateClearBits(uvGfxState *gs, s32 mask) {
    gs->state = gs->state & ~mask;
}
#line 488 "src/modules/uvgfxstate_rom.c"

#line 489 "src/modules/uvgfxstate_rom.c"
/* Set the requested state bits. */
void uvGfxStateSetBits(uvGfxState *gs, s32 mask) {
    gs->state |= mask;
}
#line 492 "src/modules/uvgfxstate_rom.c"

#line 493 "src/modules/uvgfxstate_rom.c"
/* Replace the low twelve texture-ID bits. The supplied ID is not masked. */
void uvGfxStateSetTextureId(uvGfxState *gs, s32 textureId) {
    gs->state = (gs->state & ~0xFFF) | textureId;
}
#line 496 "src/modules/uvgfxstate_rom.c"

#line 497 "src/modules/uvgfxstate_rom.c"
/* On a low-twelve-bit ID match, OR the unmasked new ID into retained high bits; RE_UNKNOWN: caller ID domain needs original callers. */
void uvGfxStateReplaceTextureId(uvGfxState *state, s32 oldTextureId, s32 newTextureId) {
    if (oldTextureId == (state->state & 0xFFF)) {
        state->state = (state->state & ~0xFFF) | newTextureId;
    }
}
#line 502 "src/modules/uvgfxstate_rom.c"

#line 503 "src/modules/uvgfxstate_rom.c"
/* Return whether the low twelve state bits equal the requested texture ID. */
s32 uvGfxStateHasTextureId(uvGfxState *state, s32 textureId) {
    if (textureId == (state->state & 0xFFF)) {
        return TRUE;
    }
    return FALSE;
}
#line 509 "src/modules/uvgfxstate_rom.c"

#line 510 "src/modules/uvgfxstate_rom.c"
/* Store graphics-state word 0x50 without guessing its detailed role. */
void uvGfxSetSharedStateWord50(s32 value) {
    D_uvgfxstate_rom_00402C50 = value;
}
#line 513 "src/modules/uvgfxstate_rom.c"

#line 514 "src/modules/uvgfxstate_rom.c"
/* Store graphics-state word 0x4C, or clear both 0x4C and 0x50 for -1. */
void uvGfxSetSharedStateWord4C(s32 value) {
    if (value == -1) {
        D_uvgfxstate_rom_00402C4C = 0;
        D_uvgfxstate_rom_00402C50 = 0;
        return;
    }
    D_uvgfxstate_rom_00402C4C = value;
}
#line 522 "src/modules/uvgfxstate_rom.c"

#line 523 "src/modules/uvgfxstate_rom.c"
/* Draw the state display list first into the depth-image buffer with
 * front-face culling, then into the current color framebuffer with
 * back-face culling; account for both passes in the shared counters. */
void uvGfxDrawStateThroughDepthAndColorPasses(uvGfxState *state) {
    Gfx **displayListHead;
    s32 colorFramebuffer;
    void *depthImageBuffer;

    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();
    colorFramebuffer = sUvGfxMgrExports->uvGfxGetCurrentFramebuffer();
    depthImageBuffer = sUvGfxMgrExports->uvGfxGetDepthImageBuffer();
    gSPClearGeometryMode(displayListHead[0]++, G_CULL_BACK | G_LIGHTING);
    gSPSetGeometryMode(displayListHead[0]++, G_ZBUFFER | G_SHADE | G_CULL_FRONT);
    uvGfxSync();
    gDPSetCycleType(displayListHead[0]++, G_CYC_2CYCLE);
    gDPSetTextureLOD(displayListHead[0]++, G_TL_TILE);
    gDPSetCombineLERP(displayListHead[0]++, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
    gDPSetAlphaCompare(displayListHead[0]++, G_AC_NONE);
    uvGfxSync();
    gDPSetRenderMode(displayListHead[0]++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gDPSetColorImage(displayListHead[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sUvGfxMgrExports->uvGetScreenWidth(),
                     osVirtualToPhysical(depthImageBuffer));
    gSPDisplayList(displayListHead[0]++, state->displayList);
    uvGfxSync();
    gDPSetColorImage(displayListHead[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sUvGfxMgrExports->uvGetScreenWidth(),
                     osVirtualToPhysical(colorFramebuffer));
    gDPSetCombineMode(displayListHead[0]++, G_CC_SHADE, G_CC_PASS2);
    gDPSetRenderMode(displayListHead[0]++, G_RM_PASS, G_RM_ZB_XLU_SURF2);
    gSPClearGeometryMode(displayListHead[0]++, G_CULL_FRONT);
    gSPSetGeometryMode(displayListHead[0]++, G_CULL_BACK);
    gSPDisplayList(displayListHead[0]++, state->displayList);
    D_uvgfxstate_rom_00402D38[D_uvgfxstate_rom_00402D30] += state->unk10 * 2;
    D_uvgfxstate_rom_00402D50[D_uvgfxstate_rom_00402D30] += state->unk14 * 2;
    D_uvgfxstate_rom_00402D58[D_uvgfxstate_rom_00402D30] += state->unkE * 2;
    D_uvgfxstate_rom_00402D40[D_uvgfxstate_rom_00402D30] += state->unk12 * 2;
    D_uvgfxstate_rom_00402D48[D_uvgfxstate_rom_00402D30] += 2;
    uvGfxResetShadeCombineMode();
}
#line 558 "src/modules/uvgfxstate_rom.c"

/* Apply changed texture/render/geometry state, append the optional display list, and accumulate the active-buffer counters. */
#line 559 "src/modules/uvgfxstate_rom.c"
void uvGfxStateDraw(uvGfxState *drawState) {
    s32 pad; /* RE_UNKNOWN: retain unused storage; historical declarations remain unproved. */
    Gfx *cursor;
    s32 modeBits;
    s32 geometryBitsToClear;
    s32 previousTextureIdBits;
    s32 snapshotStateBits;
    s32 textureIdBits;
    Gfx **displayListHead;
    s32 returnedTextureStateBits;

    snapshotStateBits = drawState->state; /* Keep the pre-callback snapshot and later member/cache reloads; RE_UNKNOWN: callback mutation and cache coherence need writer/caller proof. */

    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();
    cursor = *displayListHead;

    if (snapshotStateBits & 0x40000) {
        *displayListHead = cursor;
        D_uvgfxstate_rom_00402D18->unk4(drawState->unkC); /* LGHT slot04 validates/caches the signed member+0C record selector; RE_UNKNOWN: record/storage domains need caller/allocation proof. */
        cursor = *displayListHead;
    }

    if (snapshotStateBits != D_uvgfxstate_rom_00402C48) {
        gDPPipeSync(cursor++);
        textureIdBits = snapshotStateBits & 0xFFF;
        previousTextureIdBits = D_uvgfxstate_rom_00402C48 & 0xFFF;
        if (previousTextureIdBits != textureIdBits) {
            *displayListHead = cursor;
            D_uvgfxstate_rom_00402C5C = D_uvgfxstate_rom_00402D14->unk10(snapshotStateBits); /* TEXT slot10 returns packed texture state; publish/reload the shared cursor around the callback. */
            cursor = *displayListHead;
        }
        returnedTextureStateBits = D_uvgfxstate_rom_00402C5C;
        if (((snapshotStateBits & 0x01E00000) != (D_uvgfxstate_rom_00402C48 & 0x01E00000)) || (textureIdBits != previousTextureIdBits)) {
            if (snapshotStateBits & 0x01000000) {
                switch (snapshotStateBits & 0xC00000) {
                    case 0x400000:
                        modeBits = 0x112D58;
                        break;
                    case 0xC00000:
                        modeBits = 0x104DD8;
                        break;
                    case 0x800000:
                        modeBits = 0x104E50;
                        break;
                    case 0x0:
                        modeBits = 0x112E10;
                        break;
                }
            } else if (snapshotStateBits & 0x800000) {
                switch (snapshotStateBits & 0x600000) {
                    case 0x600000:
                        if (textureIdBits == 0xFFF) {
                            modeBits = 0x1045D8;
                        } else if (returnedTextureStateBits & 0x10000) {
                            modeBits = 0x105278;
                        } else if ((returnedTextureStateBits & 0x8000) || (returnedTextureStateBits & 0x4000) || (snapshotStateBits & 0x04000000)) {
                            modeBits = 0x1049D8;
                        } else {
                            modeBits = 0x103078;
                        }
                        break;
                    case 0x400000:
                        if (textureIdBits == 0xFFF) {
                            modeBits = 0x1041C8;
                        } else if ((returnedTextureStateBits & 0x8000) || (returnedTextureStateBits & 0x4000) || (snapshotStateBits & 0x04000000)) {
                            modeBits = 0x1041C8;
                        } else {
                            modeBits = 0x103048;
                        }
                        break;
                    case 0x200000:
                        if (textureIdBits == 0xFFF) {
                            modeBits = 0x104B50;
                        } else if (returnedTextureStateBits & 0x10000) {
                            modeBits = 0x105278;
                        } else {
                            modeBits = 0x104A50;
                        }
                        break;
                    case 0:
                        if (textureIdBits == 0xFFF) {
                            modeBits = 0x104340;
                        } else {
                            modeBits = 0x104240;
                        }
                        break;
                }
            } else {
                switch (snapshotStateBits & 0x600000) {
                    case 0x200000:
                        modeBits = 0x112230;
                        break;
                    case 0x400000:
                        modeBits = 0x102048;
                        break;
                    case 0x600000:
                        modeBits = 0x102078;
                        break;
                    case 0x0:
                        modeBits = 0x03024000;
                        break;
                    default:
                        break;
                }
            }

            gDPSetRenderMode(cursor++, G_RM_PASS, modeBits); /* Retain the literal render-mode table and all masked selector branches. */
        }
        if ((snapshotStateBits & 0x887C0000) != (D_uvgfxstate_rom_00402C48 & 0x887C0000)) {
            modeBits = 0; /* Reuse this local for geometry bits to set; keep clear-before-set emission order. */
            geometryBitsToClear = 0;
            if (snapshotStateBits & 0x08000000) {
                modeBits |= 0x40000;
            } else {
                geometryBitsToClear |= 0x40000;
            }
            if (snapshotStateBits & 0x100000) {
                modeBits |= 0x400;
            } else {
                geometryBitsToClear |= 0x400;
            }
            if (snapshotStateBits & 0x80000) {
                modeBits |= 0x200;
            } else {
                geometryBitsToClear |= 0x200;
            }
            if (snapshotStateBits & 0x08040000) {
                modeBits |= 0x20000;
            } else {
                geometryBitsToClear |= 0x20000;
            }
            if (snapshotStateBits & 0x200000) {
                modeBits |= 1;
            } else {
                geometryBitsToClear |= 1;
            }
            if (geometryBitsToClear != 0) {
                gSPClearGeometryMode(cursor++, geometryBitsToClear);
            }
            if (modeBits != 0) {
                gSPSetGeometryMode(cursor++, modeBits);
            }
        }
        D_uvgfxstate_rom_00402C48 = snapshotStateBits;
    }
    if (drawState->displayList != NULL) { /* RE_UNKNOWN: display-list extent/lifetime and cursor capacity require allocation/caller proof. */
        gSPDisplayList(cursor++, drawState->displayList);
        D_uvgfxstate_rom_00402D38[D_uvgfxstate_rom_00402D30] += drawState->unk10; /* Keep signed halfword contributions and fresh buffer-index loads; RE_UNKNOWN: counter units/index/overflow domains need writer/consumer proof. */
        D_uvgfxstate_rom_00402D50[D_uvgfxstate_rom_00402D30] += drawState->unk14;
        D_uvgfxstate_rom_00402D58[D_uvgfxstate_rom_00402D30] += drawState->unkE;
        D_uvgfxstate_rom_00402D40[D_uvgfxstate_rom_00402D30] += drawState->unk12;
        D_uvgfxstate_rom_00402D48[D_uvgfxstate_rom_00402D30] += 1;
    }
    *displayListHead = cursor;
}

#line 715 "src/modules/uvgfxstate_rom.c"
/* Emit default geometry/display-list state, reset the tracked state word,
 * invoke the original hook and restore the stored fog parameters. */
void uvGfxResetDefaultRenderState(void) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    if (D_uvgfxstate_rom_00402C54 > 0.0f) {
        gSPSetGeometryMode(gdl[0]++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH);
    } else {
        gSPSetGeometryMode(gdl[0]++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    }
    gSPDisplayList(gdl[0]++, D_uvgfxstate_rom_00402C78);
    D_uvgfxstate_rom_00402C48 = 0x500FFF;
    D_uvgfxstate_rom_00402D14->unk14();
    uvGfxSetFogParameters(D_uvgfxstate_rom_00402C54, D_uvgfxstate_rom_00402C58);
}
#line 729 "src/modules/uvgfxstate_rom.c"

#line 730 "src/modules/uvgfxstate_rom.c"
/* Reset look-at/highlight cursors, alternate the two statistics buffers,
 * clear current counters and restore the default render state. */
void uvGfxBeginStateFrame(s32 unused) {
    D_uvgfxstate_rom_00402DF0 = 0;
    D_uvgfxstate_rom_00402E04 = 0;
    D_uvgfxstate_rom_00402D30 = D_uvgfxstate_rom_00402D30 ^ 1;
    D_uvgfxstate_rom_00402D38[D_uvgfxstate_rom_00402D30] = 0;
    D_uvgfxstate_rom_00402D50[D_uvgfxstate_rom_00402D30] = 0;
    D_uvgfxstate_rom_00402D58[D_uvgfxstate_rom_00402D30] = 0;
    D_uvgfxstate_rom_00402D60[D_uvgfxstate_rom_00402D30] = 0;
    D_uvgfxstate_rom_00402D40[D_uvgfxstate_rom_00402D30] = 0;
    D_uvgfxstate_rom_00402D48[D_uvgfxstate_rom_00402D30] = 0;
    uvGfxResetDefaultRenderState();
}
#line 742 "src/modules/uvgfxstate_rom.c"

#line 743 "src/modules/uvgfxstate_rom.c"
/* Select the original terrain render mode and update the depth-buffer
 * geometry bit and tracked state bit together. */
void uvGfxSetTerrainDepthBufferEnabled(s32 enabled) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    if (enabled != 0) {
        gDPSetRenderMode(gdl[0]++, G_RM_PASS, G_RM_AA_ZB_OPA_TERR2);
        gSPSetGeometryMode(gdl[0]++, G_ZBUFFER);
        D_uvgfxstate_rom_00402C48 |= 0x200000;
    } else {
        gDPSetRenderMode(gdl[0]++, G_RM_PASS, G_RM_AA_OPA_TERR2);
        gSPClearGeometryMode(gdl[0]++, G_ZBUFFER);
        D_uvgfxstate_rom_00402C48 &= 0xFFDFFFFF;
    }
}
#line 757 "src/modules/uvgfxstate_rom.c"

#line 758 "src/modules/uvgfxstate_rom.c"

/* Clamp both fog controls to [0, 1] and retain their shared values.
 * A positive first control enables fog and derives the display-list
 * multiplier from 255 * secondControl / (1 - firstControl), clamped to
 * the original coefficient limits; zero disables fog geometry mode.
 * RE_UNKNOWN: the two controls' physical interpretation and caller domain.
 * Trace original STAT export0x44 callers and the paired export0x48 getter
 * before describing these controls as world-space near/far distances. */
void uvGfxSetFogParameters(f32 firstControl, f32 secondControl) {
    Gfx **displayList;
    f32 fogMultiplier;

    displayList = sUvGfxMgrExports->uvGetDisplayListHead();
    if (firstControl < 0.0f) {
        firstControl = 0.0f;
    } else if (firstControl > 1.0f) {
        firstControl = 1.0f;
    }
    if (secondControl < 0.0f) {
        secondControl = 0.0f;
    } else if (secondControl > 1.0f) {
        secondControl = 1.0f;
    }
    D_uvgfxstate_rom_00402C54 = firstControl;
    D_uvgfxstate_rom_00402C58 = secondControl;
    if (firstControl > 0.0f) {
        secondControl *= 255.0f;
        fogMultiplier = secondControl / (1.0f - firstControl);
        gSPSetGeometryMode(displayList[0]++, G_FOG);

        if (32767.0f < fogMultiplier) {
            fogMultiplier = 32767.0f;
        }
        if (fogMultiplier < -32467.0f) {
            fogMultiplier = -32467.0f;
        }
        gSPFogFactor(displayList[0]++, ((s32) fogMultiplier), ((s32) (secondControl - fogMultiplier)));
    } else {
        gSPClearGeometryMode(displayList[0]++, G_FOG);
    }
}
#line 795 "src/modules/uvgfxstate_rom.c"

#line 796 "src/modules/uvgfxstate_rom.c"
/* Copy both stored normalized fog parameters to caller storage. */
void uvGfxGetFogParameters(f32 *first, f32 *second) {
    *first = D_uvgfxstate_rom_00402C54;
    *second = D_uvgfxstate_rom_00402C58;
}
#line 800 "src/modules/uvgfxstate_rom.c"

#line 801 "src/modules/uvgfxstate_rom.c"
/* Update front/back culling geometry commands and tracked state bits. */
void uvGfxSetCullFaces(s32 front, s32 back) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    if (front != 0) {
        gSPSetGeometryMode(gdl[0]++, G_CULL_FRONT);
        D_uvgfxstate_rom_00402C48 |= 0x80000;
    } else {
        gSPClearGeometryMode(gdl[0]++, G_CULL_FRONT);
        D_uvgfxstate_rom_00402C48 &= 0xFFF7FFFF;
    }
    if (back != 0) {
        gSPSetGeometryMode(gdl[0]++, G_CULL_BACK);
        D_uvgfxstate_rom_00402C48 |= 0x100000;
    } else {
        gSPClearGeometryMode(gdl[0]++, G_CULL_BACK);
        D_uvgfxstate_rom_00402C48 &= 0xFFEFFFFF;
    }
}
#line 820 "src/modules/uvgfxstate_rom.c"

void uvGfxStatePush(void) {
    if (D_uvgfxstate_rom_00402DE8 < 0x1F) {
        D_uvgfxstate_rom_00402D68[D_uvgfxstate_rom_00402DE8++] = D_uvgfxstate_rom_00402C48;
    }
}

// uvGfxStatePop
#line 828 "src/modules/uvgfxstate_rom.c"

void uvGfxStatePop(void) {
    u32 newState;
    uvGfxState stateUpdate;

    if (D_uvgfxstate_rom_00402DE8 != 0) {
        D_uvgfxstate_rom_00402DE8--;
        newState = D_uvgfxstate_rom_00402D68[D_uvgfxstate_rom_00402DE8];
        stateUpdate.unkC = -1;
        stateUpdate.displayList = NULL;
        stateUpdate.state = newState;
        uvGfxStateDraw(&stateUpdate);
    }
}
#line 841 "src/modules/uvgfxstate_rom.c"

#line 842 "src/modules/uvgfxstate_rom.c"
/* Restore two-cycle shade/pass combination, mark texture sentinel 0xFFF
 * and invoke the original graphics hook. */
void uvGfxResetShadeCombineMode(void) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    gDPSetCycleType(gdl[0]++, G_CYC_2CYCLE);
    gDPSetCombineMode(gdl[0]++, G_CC_SHADE, G_CC_PASS2);
    D_uvgfxstate_rom_00402C48 = (D_uvgfxstate_rom_00402C48 & ~0xFFF) | 0xFFF;
    D_uvgfxstate_rom_00402D14->unk14();
}
#line 851 "src/modules/uvgfxstate_rom.c"

#line 852 "src/modules/uvgfxstate_rom.c"
/* Draw a screen rectangle using the shared texture and caller UV range,
 * or primitive color for the original texture sentinel. Preserve the
 * one-pixel edge adjustments, mirrored tile and bottom-origin Y mapping. */
void uvGfxDrawTextureRectangleWithUvRange(s32 left, s32 right, s32 bottom, s32 top, f32 sStart, f32 sEnd, f32 tStart,
                                  f32 tEnd) {
    f32 temp_fa0;
    f32 temp_ft4;
    f32 textureWidth;
    s32 textureId;
    s16 textureS;
    s16 textureT;
    s16 textureStepS;
    s16 textureStepT;
    UnkStruct_80001724 *texture;
    s32 pad;
    f32 horizontalDivisor;
    Gfx **displayListHead;
    f32 textureHeight;

    textureId = D_uvgfxstate_rom_00402C48 & 0xFFF;
    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();

    if ((right - left) <= 0) {
        return;
    }

    if ((top - bottom) <= 0) {
        return;
    }

    if (textureId < 0xFFE) {
        texture = uvGetLoadedFile('UVTX', textureId);
        textureWidth = texture->unk1C;
        textureHeight = texture->unk1E;
        sEnd += 1.0f / texture->unk1C;
        sStart += 1.0f / texture->unk1C;

        textureS = texture->unk1C * sStart * 32.0f;
        textureT = textureHeight * tEnd * 32.0f;
        if (sStart <= sEnd) {
            horizontalDivisor = 1.0f;
            horizontalDivisor += (right - left);
        } else {
            horizontalDivisor = (right - left);
        }
        textureStepS = (1024.0f * textureWidth * (sEnd - sStart)) / horizontalDivisor;
        textureStepT = (1024.0f * textureHeight * (tEnd - tStart)) / (1.0f + (top - bottom));
        uvGfxSync();
        if (!(texture->unk14 & 0x1000)) {
            gDPSetCombineMode(displayListHead[0]++, G_CC_MODULATEIA_PRIM, G_CC_PASS2);
        }
        gDPSetTexturePersp(displayListHead[0]++, G_TP_NONE);
    } else {
        uvGfxSync();
        gDPSetCombineMode(displayListHead[0]++, G_CC_PRIMITIVE, G_CC_PASS2);
        textureStepS = 0;
        textureStepT = 0;
        textureS = 0;
        textureT = 0;
    }

    bottom--;
    right++;
    gSPScisTextureRectangle(displayListHead[0]++,
                            left << 2,                                           // xl
                            (sUvGfxMgrExports->uvGetScreenHeight() - top) << 2, // yl
                            right << 2,                                           // xh
                            (sUvGfxMgrExports->uvGetScreenHeight() - bottom) << 2, // yh
                            G_TX_MIRROR,                                         // tile
                            textureS,                                                // s
                            textureT,                                                // t
                            textureStepS,                                                // dsdx
                            -textureStepT                                                // dtdy
    );
}
#line 924 "src/modules/uvgfxstate_rom.c"

extern s32 D_uvgfxstate_rom_00402D3C[];
extern s32 D_uvgfxstate_rom_00402D44[];
extern s32 D_uvgfxstate_rom_00402D4C[];
extern s32 D_uvgfxstate_rom_00402D54[];
extern s32 D_uvgfxstate_rom_00402D5C[];
extern s32 D_uvgfxstate_rom_00402D64[];

#line 932 "src/modules/uvgfxstate_rom.c"
/* Return the selected graphics statistic from the other buffer bank,
 * delegating matrix and texture counters to their modules. Selectors
 * 0..8 follow the original jump table and debug labels: VXFM, TRI, MLD,
 * MMU, TXL, GFX, VCL, VTX and SYNC; other values return zero.
 * RE_ORIGINAL_QUIRK: counter aliases address slot one and subtract the
 * current bank, preserving the original address calculation.
 * RE_UNKNOWN: retain the displayed abbreviations where a more detailed
 * counter definition has not been independently established. */
s32 uvGfxGetPreviousBufferCounter(u32 counterId) {
    switch (counterId) {
        case 0:
            return D_uvgfxstate_rom_00402D3C[0 - D_uvgfxstate_rom_00402D30];
        case 1:
            return D_uvgfxstate_rom_00402D44[0 - D_uvgfxstate_rom_00402D30];
        case 5:
            return D_uvgfxstate_rom_00402D4C[0 - D_uvgfxstate_rom_00402D30];
        case 6:
            return D_uvgfxstate_rom_00402D54[0 - D_uvgfxstate_rom_00402D30];
        case 7:
            return D_uvgfxstate_rom_00402D5C[0 - D_uvgfxstate_rom_00402D30];
        case 8:
            return D_uvgfxstate_rom_00402D64[0 - D_uvgfxstate_rom_00402D30];
        case 4:
            return ((UvTexture_Exports *) D_uvgfxstate_rom_00402D14)->uvTextureGetOtherBufferValue(0);
        case 2:
            return sUvImtxExports->uvIMtxGetOtherBufferValue(0);
        case 3:
            return sUvImtxExports->uvIMtxGetOtherBufferValue(1);
        default:
            return 0;
    }
}
#line 933 "src/modules/uvgfxstate_rom.c"

#line 960 "src/modules/uvgfxstate_rom.c"
/* Store the original pair of shared graphics-state words. */
void uvGfxSetSharedStateWords(s32 first, s32 second) {
    D_uvgfxstate_rom_00402D2C = second;
    D_uvgfxstate_rom_00402C40 = first;
}
#line 964 "src/modules/uvgfxstate_rom.c"

#line 965 "src/modules/uvgfxstate_rom.c"
/* Store a shared highlight vector when index<3; preserve that upper-only guard.
 * RE_UNKNOWN: negative-index exclusion and vector storage extent need original producers/callers. */
void uvGfxSetHiliteVector(s32 index, Vec3F vector) {
    if (index < 3) {
        D_uvgfxstate_rom_00402C60[index] = vector;
    }
}
#line 970 "src/modules/uvgfxstate_rom.c"

void uvGfxSync(void) {
    Gfx **gdl;

    gdl = sUvGfxMgrExports->uvGetDisplayListHead();
    if (D_uvgfxstate_rom_00402D00 != 2) {
        D_uvgfxstate_rom_00402D60[D_uvgfxstate_rom_00402D30]++;
        gDPPipeSync(gdl[0]++);
    }
}
