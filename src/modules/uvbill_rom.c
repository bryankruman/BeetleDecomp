// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "stdarg.h"

#define DEG_TO_RAD 0.0174533f
#define DEFAULT_BILLBOARD_COUNT 100

typedef struct UnkTerraExports_s {
    /* 0x00 */ char pad0[0xAC];
    /* 0xAC */ void (*unkAC)(s32, s32, f32, f32, void (*)(s32, void *), void *, f32);
} UnkTerraExports;

typedef struct BillBoard_s {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 allocated;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 active;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ char pad7[1];
    /* 0x08 */ u16 textureSeq; 
    /* 0x0A */ u16 texture; 
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 angle; // rot angle?
    /* 0x14 */ f32 scaleX;
    /* 0x18 */ f32 scaleY;
    /* 0x1C */ f32 scaleZ;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 colorRed;
    /* 0x25 */ u8 colorGreen;
    /* 0x26 */ u8 colorBlue;
    /* 0x27 */ u8 colorAlpha;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ char pad2E[2];
    /* 0x30 */ Mtx4F trans;        
    /* 0x70 */ void (*unk70)(void);
    /* 0x74 */ void (*unk74)(void);
} BillBoard;    /* size = 0x78 */

void uvBillDestroy(void);
void uvBillDraw(s32 arg0, BillBoard *arg1);
void uvBillboardClearFrameMarks(s32 arg0);
void uvBillboardQueueVisibleForChannel(s32 arg0);
s32 uvBillboardCollectSegmentHits(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6,
                             s32 **arg7, f32 **arg8, Vec3F **arg9);
s32 uvBillboardIntersectsSphere(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
s32 uvBillboardQuerySphere(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 **arg5);
void uvBillSetTransMtx(s32 arg0, Mtx4F *arg1);
void uvBillProps(s32 arg0, ...);
s32 uvBillInit(void);
void uvBillboardRelease(s32 arg0);
void uvBillboardAttachChannelCallback(s32 arg0);
void __entrypoint_func_uvbill_rom_400000(UvBill_Exports *exports);

// .data
BillBoard *sBillBoardPool = NULL;
s32 *D_uvbill_rom_00402004 = NULL;
Vec3F *D_uvbill_rom_00402008 = NULL;
f32 *D_uvbill_rom_0040200C = NULL;
s32 D_uvbill_rom_00402010[] = { 0x00240000, __entrypoint_func_uvbill_rom_400000, 0, 0 };

// .bss
s32 sBillBoardCount;
static UvGfxState_Rom_Exports *sUvGfxState;
static UvFMtx_Rom_Exports *sUvFmtxExports;
static UvChannel_Exports *sUvChannel_Exports;
static UvMath_Exports *sUvMathExports;
static UvIntersect_Exports *sUvIntersectExports;
static UvDGeom_Rom_Exports *sUvDGeomExports;
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvCback_Exports *sUvCbackExports;
static UvTSeq_Exports *sUvTSeqExports;
static UnkTerraExports *sUvTerraExports; // terra exports

/*
 * Publish nine billboard exports and choose the pool count from system
 * property 13, using 100 when the property is absent or its word is zero.
 * Allocate and zero, in order, 120-byte records and parallel 4-, 12- and
 * 4-byte-per-record arrays. Load STAT, CHAN, FMTX, MATH, TSEQ, DGEO, GMGR,
 * CBCK and TERR, then register the frame-mark reset callback on GMGR list 1.
 * RE_ORIGINAL_QUIRK: Retain any nonzero signed count, repeated count reads
 * across calls, original allocation order and the inherited empty do/while.
 * RE_UNKNOWN: Settings and export lifetime, count/multiplication bounds,
 * allocation success and dependency/callback teardown require loader proof.
 */
#line 79 "src/modules/uvbill_rom.c"
void __entrypoint_func_uvbill_rom_400000(UvBill_Exports *exports) {
    s32 *billBoardCount;

    uvUpdateFileAllocPtr(exports);
    exports->uvBillDestroy = uvBillDestroy;
    exports->uvBillboardAttachChannelCallback = uvBillboardAttachChannelCallback;
    exports->uvBillboardCollectSegmentHits = uvBillboardCollectSegmentHits;
    exports->uvBillboardIntersectsSphere = uvBillboardIntersectsSphere;
    exports->uvBillboardQuerySphere = uvBillboardQuerySphere;
    exports->uvBillSetTransMtx = uvBillSetTransMtx;
    exports->uvBillProps = uvBillProps;
    exports->uvBillInit = uvBillInit;
    exports->uvBillboardRelease = uvBillboardRelease;
    billBoardCount = uvGetSystemProp(SYSTEM_PROPID_BILLBOARD_COUNT);
    if (billBoardCount == NULL) {
        sBillBoardCount = DEFAULT_BILLBOARD_COUNT;
    } else {
        if (*billBoardCount != 0) {
            sBillBoardCount = *billBoardCount;
        } else {
            sBillBoardCount = DEFAULT_BILLBOARD_COUNT;
        }
    }
    // FAKE
    do {
    } while (0);
    sBillBoardPool =
        _uvMemAllocAlign8(sBillBoardCount * sizeof(BillBoard));
    D_uvbill_rom_00402004 = _uvMemAllocAlign8(sBillBoardCount * sizeof(s32));
    D_uvbill_rom_00402008 = _uvMemAllocAlign8(sBillBoardCount * sizeof(Vec3F));
    D_uvbill_rom_0040200C = _uvMemAllocAlign8(sBillBoardCount * sizeof(f32));

    uvMemSet(sBillBoardPool, 0, sBillBoardCount * sizeof(BillBoard));
    uvMemSet(D_uvbill_rom_00402004, 0, sBillBoardCount * sizeof(s32));
    uvMemSet(D_uvbill_rom_00402008, 0, sBillBoardCount * sizeof(Vec3F));
    uvMemSet(D_uvbill_rom_0040200C, 0, sBillBoardCount * sizeof(f32));
    sUvGfxState = uvLoadModule('STAT');
    sUvChannel_Exports = uvLoadModule('CHAN');
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvMathExports = uvLoadModule('MATH');
    sUvTSeqExports = uvLoadModule('TSEQ');
    sUvDGeomExports = uvLoadModule('DGEO');
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvTerraExports = uvLoadModule('TERR');
    sUvCbackExports->uvAddCallback(sUvGfxMgrExports->uvGfxGetCallbackList(1),
                                   uvBillboardClearFrameMarks, 0, 0);
}

#line 128 "src/modules/uvbill_rom.c"
/* Attach billboard processing to channel property six at priority 0x32. */
void uvBillboardAttachChannelCallback(s32 channel) {
    CallbackList *callbackList;

    sUvChannel_Exports->uvChannelGetProperties(channel, 6, &callbackList, 0);
    sUvCbackExports->uvAddCallback(callbackList, uvBillboardQueueVisibleForChannel, 0, 0x32);
}
#line 134 "src/modules/uvbill_rom.c"

void uvBillDestroy(void) {
    _uvMemFree(D_uvbill_rom_0040200C);
    _uvMemFree(D_uvbill_rom_00402008);
    _uvMemFree(D_uvbill_rom_00402004);
    _uvMemFree(sBillBoardPool);
    uvUnloadModule('STAT');
    uvUnloadModule('CHAN');
    uvUnloadModule('FMTX');
    uvUnloadModule('MATH');
    uvUnloadModule('TSEQ');
    uvUnloadModule('DGEO');
    uvUnloadModule('CBCK');
}

/* Draw one billboard using texture coordinates, a scaled matrix and a cached four-vertex range. */
#line 149 "src/modules/uvbill_rom.c"
void uvBillDraw(s32 unusedCallbackArgument, BillBoard *billboard) {
    s32 texture;
    u16 textureS0;
    u16 textureT0;
    u16 textureS1;
    u16 textureT1;
    u16 textureS2;
    u16 textureT2;
    u16 textureS3;
    u16 textureT3;
    s16 historicalUnusedPad; /* RE_UNKNOWN: retain unused argument/pad storage; historical declarations are unproved. */
    s16 row0Z;
    s16 row1Z;
    s32 scaledTextureHeight;
    f32 angleCosine;
    f32 angleSine;
    f32 halfTextureWidth;
    f32 angleOrHalfTextureHeight;
    Mtx4F scaledMatrix;
    ParsedUVTX *textureAsset;
    s32 coordinateOrWidth;

    if (billboard->colorAlpha == 0) {
        return;
    }

    sUvGfxState->uvGfxStatePush();
    sUvGfxState->uvGfxStateSetFlags(0x04E20FFF);
    sUvGfxState->uvGfxClearCurrentStateBits(0x99140000);
    if (billboard->unk70 != NULL) { /* RE_UNKNOWN: callback targets, mutation/reentry and billboard lifetime need caller/provider proof; keep fresh member reads. */
        billboard->unk70();
    }
    if (billboard->unk2 == 0) {
        if (billboard->unk74 != NULL) {
            billboard->unk74();
        }
        sUvGfxState->uvGfxStatePop();
        return;
    }
    if (billboard->textureSeq != 0xFF) {
        texture = sUvTSeqExports->uvTexSeqGetCurFrameTexture(billboard->textureSeq);
    } else {
        if (billboard->texture != 0xFFF) {
            texture = billboard->texture;
        } else {
            texture = 0xFFF;
        }
    }
    if (texture != 0xFFF) {
        textureAsset = uvGetLoadedFile('UVTX', texture);
    } else {
        textureAsset = NULL;
    }
    if ((texture != 0xFFF) && (textureAsset != NULL)) { /* RE_UNKNOWN: texture/sequence storage, ID domains and coordinate/FP conversion ranges need producer proof. */
        sUvGfxState->uvGfxStateBindTexture(texture);
        if (billboard->angle == 0.0f) {
            textureS0 = 0;
            textureT0 = 0;
            coordinateOrWidth = textureAsset->width << 5;
            textureS2 = textureS1 = coordinateOrWidth;
            textureT1 = 0;
            scaledTextureHeight = textureAsset->height << 5;
            textureT3 = textureT2 = scaledTextureHeight;
            textureS3 = 0;
        } else {
            angleOrHalfTextureHeight = billboard->angle * DEG_TO_RAD;
            angleSine = sUvMathExports->uvSinF(angleOrHalfTextureHeight);
            angleCosine = sUvMathExports->uvCosF(angleOrHalfTextureHeight);
            halfTextureWidth = textureAsset->width * 16.0f;
            angleOrHalfTextureHeight = textureAsset->height * 16.0f;
            textureS0 = ((-halfTextureWidth * angleCosine) + (angleOrHalfTextureHeight * angleSine) + halfTextureWidth);
            textureT0 = (((-halfTextureWidth * angleSine) - (angleOrHalfTextureHeight * angleCosine)) + angleOrHalfTextureHeight);
            textureS1 = ((halfTextureWidth * angleCosine) + (angleOrHalfTextureHeight * angleSine) + halfTextureWidth);
            textureT1 = (((halfTextureWidth * angleSine) - (angleOrHalfTextureHeight * angleCosine)) + angleOrHalfTextureHeight);
            textureS2 = (((halfTextureWidth * angleCosine) - (angleOrHalfTextureHeight * angleSine)) + halfTextureWidth);
            textureT2 = ((halfTextureWidth * angleSine) + (angleOrHalfTextureHeight * angleCosine) + angleOrHalfTextureHeight);
            textureS3 = (((-halfTextureWidth * angleCosine) - (angleOrHalfTextureHeight * angleSine)) + halfTextureWidth);
            textureT3 = ((-halfTextureWidth * angleSine) + (angleOrHalfTextureHeight * angleCosine) + angleOrHalfTextureHeight);
        }
        if (billboard->unk5 != 0) {
            coordinateOrWidth = textureS0;
            textureS0 = textureS2;
            textureS2 = coordinateOrWidth;
            coordinateOrWidth = textureS1;
            textureS1 = textureS3;
            textureS3 = coordinateOrWidth;
        }
        if (billboard->unk6 != 0) {
            coordinateOrWidth = textureT0;
            textureT0 = textureT2;
            textureT2 = coordinateOrWidth;
            coordinateOrWidth = textureT1;
            textureT1 = textureT3;
            textureT3 = coordinateOrWidth;
        }
    }
    if (billboard->colorAlpha < 0xFF) {
        sUvGfxState->uvGfxStateSetFlags(0x04800000);
    }
    sUvFmtxExports->uvMat4FCopy(&scaledMatrix, &billboard->trans);
    sUvFmtxExports->uvMat4Scale(&scaledMatrix, billboard->scaleX, billboard->scaleY, billboard->scaleZ);
    sUvFmtxExports->uvMat4PushFloatMatrix(&scaledMatrix);
    sUvDGeomExports->uvVtxBeginPoly();
    if (billboard->unk4 != 0) {
        row0Z = -1;
        row1Z = 1;
    } else {
        row0Z = 0;
        row1Z = 2;
    }
    if (billboard->unk2C != 0) { /* RE_UNKNOWN: cached range lifetime and DGEO capacity need allocation/frame/caller proof; preserve signed halfword reads. */
        sUvDGeomExports->uvDgeomSetVertexRange(billboard->unk2C - 1, 4);
    } else {
        billboard->unk2C = sUvDGeomExports->uvVtx(-1, 0, row0Z, textureS0, textureT0, billboard->colorRed, billboard->colorGreen, /* RE_ORIGINAL_QUIRK: absent texture skips coordinate initialization; RE_UNKNOWN: reachability of this uncached path needs resource/caller proof. */
                                             billboard->colorBlue, billboard->colorAlpha)
                      + 1;

        sUvDGeomExports->uvVtx(1, 0, row0Z, textureS1, textureT1, billboard->colorRed, billboard->colorGreen, billboard->colorBlue,
                               billboard->colorAlpha);
        sUvDGeomExports->uvVtx(1, 0, row1Z, textureS2, textureT2, billboard->colorRed, billboard->colorGreen, billboard->colorBlue,
                               billboard->colorAlpha);
        sUvDGeomExports->uvVtx(-1, 0, row1Z, textureS3, textureT3, billboard->colorRed, billboard->colorGreen, billboard->colorBlue,
                               billboard->colorAlpha);
    }
    sUvDGeomExports->uvVtxEndPoly(); /* Keep matrix/state pop order and ignored geometry results; no failure-path cleanup is invented. */
    sUvFmtxExports->uvGfxMtxFViewPop();
    if (billboard->unk74 != NULL) {
        billboard->unk74();
    }
    sUvGfxState->uvGfxStatePop();
}

#line 281 "src/modules/uvbill_rom.c"
/* Clear field 0x2C for every billboard. The incoming argument is unused. */
void uvBillboardClearFrameMarks(s32 unused) {
    s32 i;

    for (i = 0; i < sBillBoardCount; i++) {
        BillBoard *billboard = &sBillBoardPool[i];
        billboard->unk2C = 0;
    }
}
#line 289 "src/modules/uvbill_rom.c"

/* Test active billboards against channel vectors, update selected matrix components and queue the drawing callback. */
#line 290 "src/modules/uvbill_rom.c"
void uvBillboardQueueVisibleForChannel(s32 channel) {
    f32 relativeZ;
    f32 relativeX;
    f32 relativeY;
    f32 distance;
    f32 xyLengthOrUnitX;
    f32 unitY;
    f32 inverseXYLength;
    s32 billboardIndex;
    BillBoard *billboard;
    Mtx4F channelMatrix;
    Vec3F channelPosition;

    for (billboardIndex = 0; billboardIndex < sBillBoardCount; billboardIndex++) { /* RE_UNKNOWN: pool/count/channel validity and callback mutation/lifetimes need producer/caller proof; keep live reloads. */
        billboard = &sBillBoardPool[billboardIndex];
        if (!billboard->active) {
            continue;
        }
        sUvChannel_Exports->uvChannelGetProperties(channel, 7, &channelPosition, 3, &channelMatrix, 0);
        relativeX = billboard->trans.m[3][0] - channelPosition.x;
        relativeY = billboard->trans.m[3][1] - channelPosition.y;
        relativeZ = billboard->trans.m[3][2] - channelPosition.z;
        distance = sUvMathExports->uvSqrtf(SQ(relativeX) + SQ(relativeY) + SQ(relativeZ));
        if (billboard->unk20 < distance) { /* RE_ORIGINAL_QUIRK: unordered distance comparisons bypass rejection; RE_UNKNOWN: FP and scalar conventions need producer/caller proof. */
            continue;
        } else if (sUvChannel_Exports->uvChannelTestCachedVectorPairs(channel, relativeX, relativeY, relativeZ,
                                                                  billboard->unkC)
                   == 0) {
            continue;
        }

        if (billboard->unk0 == 3) { /* Mode 3 copies only the linear 3x3; mode 2 keeps the original grouped arithmetic and partial matrix store order. */
            sUvFmtxExports->uvMat4CopyLinear3x3(&billboard->trans, &channelMatrix);
        } else if (billboard->unk0 == 2) {
            xyLengthOrUnitX = sUvMathExports->uvSqrtf(SQ(relativeX) + SQ(relativeY));
            if (xyLengthOrUnitX != 0.0f) { /* Exact zero selects reciprocal 1; RE_UNKNOWN: other FP domains and physical orientation need producer proof. */
                inverseXYLength = 1.0f / xyLengthOrUnitX;
            } else {
                inverseXYLength = 1.0f;
            }
            xyLengthOrUnitX = relativeX * inverseXYLength;
            unitY = relativeY * inverseXYLength;
            billboard->trans.m[0][2] = 0.0f;
            billboard->trans.m[1][2] = 0.0f;
            billboard->trans.m[2][0] = 0.0f;
            billboard->trans.m[1][1] = unitY;
            billboard->trans.m[0][0] = (f32) -unitY;
            billboard->trans.m[0][1] = xyLengthOrUnitX;
            billboard->trans.m[1][0] = xyLengthOrUnitX;
            billboard->trans.m[2][1] = 0.0f;
            billboard->trans.m[2][2] = 1.0f;
        }
        sUvTerraExports->unkAC(channel, 1, billboard->trans.m[3][0], billboard->trans.m[3][1], /* TERR slot 0xAC selects a queue and forwards callback/data/distance; RE_UNKNOWN: queue capacity/ABI/lifetime need caller/provider proof. */
                               (void*)uvBillDraw, billboard, distance);
    }
}

/* Collect active billboard segment hits and publish shared ID, fraction and normal buffers. */
#line 347 "src/modules/uvbill_rom.c"
s32 uvBillboardCollectSegmentHits(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, s32 filterMask,
                             s32 **outIds, f32 **outFractions, Vec3F **outNormals) {
    f32 zeroFraction;
    s32 billboardIndex;
    s32 historicalUnusedIndex; /* RE_UNKNOWN: unused local storage and historical declarations remain unproved. */
    f32 hitFraction;
    s32 hitCount;
    BillBoard *billboard;

    *outIds = D_uvbill_rom_00402004; /* Publish shared bases before endpoint tests; RE_UNKNOWN: output aliasing/capacity/reentry/lifetime need allocation/caller proof. */
    *outFractions = D_uvbill_rom_0040200C;
    *outNormals = D_uvbill_rom_00402008;
    hitCount = 0;

    if ((startX == endX) && (startY == endY) && (startZ == endZ)) {
        hitCount = uvBillboardQuerySphere(startX, startY, startZ, 0.0f, filterMask, outIds);
        if (hitCount > 0) { /* RE_ORIGINAL_QUIRK: coincident endpoints zero only the first fraction/normal, then return the entire sphere-hit count. */
            *D_uvbill_rom_0040200C = 0.0f;
            zeroFraction = *D_uvbill_rom_0040200C;
            D_uvbill_rom_00402008->z = zeroFraction;
            D_uvbill_rom_00402008->y = zeroFraction;
            D_uvbill_rom_00402008->x = zeroFraction;
            *outFractions = D_uvbill_rom_0040200C;
            *outNormals = D_uvbill_rom_00402008;
            return hitCount;
        }
    }
    for (billboardIndex = 0; billboardIndex < sBillBoardCount; billboardIndex++) {
        billboard = &sBillBoardPool[billboardIndex];
        if ((billboard->active) && ((filterMask == 0) || (billboard->unk28 & filterMask))) {
            // RE_UNKNOWN: BILL native initializer/current source show no ISCT import assignment; valid publication/caller paths are unproved.
            if (sUvIntersectExports->uvIntersectSegmentSphereFraction(
                    startX, startY, startZ, endX, endY, endZ, billboard->trans.m[3][0], billboard->trans.m[3][1],
                    billboard->trans.m[3][2], billboard->unkC, &hitFraction)
                == 0) {
                continue;
            }
            sUvIntersectExports->uvIntersectGetSegmentSphereNormal( /* Preserve fresh import/center reads after the fraction callback; no alias or callback stability is assumed. */
                startX, startY, startZ, endX, endY, endZ, hitFraction, billboard->trans.m[3][0],
                billboard->trans.m[3][1], billboard->trans.m[3][2], &D_uvbill_rom_00402008[hitCount]);
            D_uvbill_rom_00402004[hitCount] = billboardIndex;
            D_uvbill_rom_0040200C[hitCount] = hitFraction;
            hitCount++;
        }
    }
    return hitCount;
}

#line 395 "src/modules/uvbill_rom.c"
/* Test squared center distance against the squared sum of radii.
 * Preserve the inclusive boundary and original unchecked billboard index. */
s32 uvBillboardIntersectsSphere(s32 billboardId, f32 x, f32 y, f32 z, f32 radius) {
    BillBoard *billboard;
    f32 dz;
    f32 combinedRadius;
    f32 dx;
    f32 dy;

    billboard = &sBillBoardPool[billboardId];
    dx = x - billboard->trans.m[3][0];
    dy = y - billboard->trans.m[3][1];
    dz = z - billboard->trans.m[3][2];
    combinedRadius = billboard->unkC + radius;
    if ((SQ(dx) + SQ(dy) + SQ(dz)) <= SQ(combinedRadius)) {
        return TRUE;
    }
    return FALSE;
}
#line 412 "src/modules/uvbill_rom.c"

#line 413 "src/modules/uvbill_rom.c"
/* Collect active billboards intersecting the sphere and optional flag mask.
 * Return the shared scratch-list count and base; lifetime stays module-owned. */
s32 uvBillboardQuerySphere(f32 x, f32 y, f32 z, f32 radius, s32 mask, s32 **output) {
    s32 i;
    s32 count;
    BillBoard *billboard;

    count = 0;
    for (i = 0; i < sBillBoardCount; i++) {
        billboard = &sBillBoardPool[i];
        if ((billboard->active != 0) && ((mask == 0) || (billboard->unk28 & mask))) {
            if (uvBillboardIntersectsSphere(i, x, y, z, radius) == 0) {
                continue;
            }
            D_uvbill_rom_00402004[count] = i;
            count++;
        }
    }
    *output = D_uvbill_rom_00402004;
    return count;
}
#line 432 "src/modules/uvbill_rom.c"

void uvBillSetTransMtx(s32 bill, Mtx4F *mtx) {
    BillBoard *a0;
    if ((bill >= 0) && (bill < sBillBoardCount)) {
        sUvFmtxExports->uvMat4FCopy(&GET_ITEM(BillBoard, sBillBoardPool, bill)->trans, mtx);
    }
}

/* Consume tagged billboard properties, retaining selector termination, narrowing and radius recomputation. */
#line 440 "src/modules/uvbill_rom.c"
void uvBillProps(s32 billboardId, ...) {
    BillBoard *billboard;
    f32 scalarOrExtent;
    s32 selectorOrMode;
    va_list arguments;
    f32 historicalRegisterLiteral = 10.0f;

    if ((billboardId < 0) || (billboardId >= sBillBoardCount)) {
        return;
    }
    billboard = &sBillBoardPool[billboardId];
    va_start(arguments, billboardId); /* RE_UNKNOWN: vararg types/termination, allocation lifetime and output alias/FP domains need producer/caller proof. */
    while (TRUE) {
        selectorOrMode = va_arg(arguments, s32);
        // RE_UNKNOWN: retain five empty tests as the existing register-allocation scaffold; historical source form is unproved.
        if (historicalRegisterLiteral > 4) {
        }
        if (historicalRegisterLiteral > 4) {
        }
        if (historicalRegisterLiteral > 4) {
        }
        if (historicalRegisterLiteral > 4) {
        }
        if (historicalRegisterLiteral > 4) {
        }

        switch (selectorOrMode) {
            case 0:
                return;
            case 1:
                billboard->trans.m[3][0] = va_arg(arguments, f64);
                billboard->trans.m[3][1] = va_arg(arguments, f64);
                billboard->trans.m[3][2] = va_arg(arguments, f64);
                break;
            case 2:
                billboard->active = va_arg(arguments, s32);
                break;
            case 3:
                selectorOrMode = va_arg(arguments, s32);
                if (selectorOrMode > 0 && selectorOrMode < 4) {
                    billboard->unk0 = selectorOrMode;
                }
                break;
            case 4:
                billboard->textureSeq = va_arg(arguments, s32);
                break;
            case 5:
                billboard->texture = va_arg(arguments, s32);
                break;
            case 6:
                billboard->unk4 = va_arg(arguments, s32);
                if (billboard->unk4 != 0) {
                    scalarOrExtent = billboard->scaleZ;
                } else {
                    scalarOrExtent = 2.0f * billboard->scaleZ;
                }
                billboard->unkC = sUvMathExports->uvSqrtf(SQ(billboard->scaleX) + SQ(scalarOrExtent)); /* RE_ORIGINAL_QUIRK: radius uses X/Z and field 0x04, omitting Y; preserve grouped arithmetic. */
                break;
            case 7:
                billboard->scaleX = va_arg(arguments, f64);
                billboard->scaleY = va_arg(arguments, f64);
                billboard->scaleZ = va_arg(arguments, f64);
                if (billboard->unk4 != 0) {
                    scalarOrExtent = billboard->scaleZ;
                } else {
                    scalarOrExtent = 2.0f * billboard->scaleZ;
                }
                billboard->unkC = sUvMathExports->uvSqrtf(SQ(billboard->scaleX) + SQ(scalarOrExtent));
                break;
            case 9:
                billboard->unk28 = va_arg(arguments, s32);
                break;
            case 8:
                scalarOrExtent = va_arg(arguments, f64);
                billboard->colorRed = scalarOrExtent * 255.0f; /* Preserve f64-to-f32 and byte narrowing without clamps; RE_UNKNOWN: valid value/FP ranges need producer/caller proof. */
                scalarOrExtent = va_arg(arguments, f64);
                billboard->colorGreen = scalarOrExtent * 255.0f;
                scalarOrExtent = va_arg(arguments, f64);
                billboard->colorBlue = scalarOrExtent * 255.0f;
                scalarOrExtent = va_arg(arguments, f64);
                billboard->colorAlpha = scalarOrExtent * 255.0f;
                break;
            case 10:
                billboard->unk20 = va_arg(arguments, f64);
                break;
            case 11:
                billboard->angle = va_arg(arguments, f64);
                break;
            case 12:
                scalarOrExtent = va_arg(arguments, f64);
                billboard->colorAlpha = scalarOrExtent * 255.0f;
                break;
            case 13:
                billboard->unk2 = va_arg(arguments, s32);
                break;
            case 14:
                billboard->unk5 = va_arg(arguments, s32);
                break;
            case 15:
                billboard->unk6 = va_arg(arguments, s32);
                break;
            default: /* Unknown selectors terminate immediately; keep consumed arguments and partial earlier stores. */
                return;
        }
    }
}

/*
 * Claim the first unallocated billboard slot and return its index. Set the
 * original flags, texture sentinels, white RGBA bytes, unit scales and zero
 * fields; request sqrt(5), retain the 100000 scalar, clear the two pointers
 * and initialize the transform. Return 0xFFFF when no free slot exists.
 * RE_ORIGINAL_QUIRK: The allocated and active bytes are set before provider
 * calls. Only listed fields are reset; no full-record clear or rollback occurs.
 * RE_UNKNOWN: Pool/count validity, the meanings of private fields, provider
 * failure and concurrent/repeated allocation require the billboard owner.
 */
#line 547 "src/modules/uvbill_rom.c"
s32 uvBillInit(void) {
    s32 slotIndex;
    BillBoard *billBoard;

    for (slotIndex = 0; slotIndex < sBillBoardCount; slotIndex++) {
        billBoard = &sBillBoardPool[slotIndex];
        if (!billBoard->allocated) {
            billBoard->unk0 = 2;
            billBoard->allocated = TRUE;
            billBoard->active = TRUE;
            billBoard->texture = 0xFFF;
            billBoard->textureSeq = 0xFF;
            billBoard->colorAlpha = 0xFF;
            billBoard->colorBlue = 0xFF;
            billBoard->colorGreen = 0xFF;
            billBoard->colorRed = 0xFF;
            billBoard->unk4 = 0;
            billBoard->unk28 = 0;
            billBoard->scaleZ = 1.0f;
            billBoard->scaleY = 1.0f;
            billBoard->scaleX = 1.0f;
            billBoard->unkC = sUvMathExports->uvSqrtf(5.0f);
            billBoard->unk5 = 0;
            billBoard->unk6 = 0;
            billBoard->angle = 0.0f;
            billBoard->unk20 = 100000.0f;
            billBoard->unk2 = 1;
            billBoard->unk2C = 0;
            billBoard->unk74 = NULL;
            billBoard->unk70 = NULL;
            sUvFmtxExports->uvMat4SetIdentity(&billBoard->trans);
            return slotIndex;
        }
    }
    return 0xFFFF;
}

#line 584 "src/modules/uvbill_rom.c"
/* For a valid allocated billboard, clear active and allocation state. */
void uvBillboardRelease(s32 billboardId) {
    if ((billboardId < 0) || (billboardId >= sBillBoardCount)) {
        return;
    }

    if (sBillBoardPool[billboardId].allocated) {
        sBillBoardPool[billboardId].active = FALSE;
        sBillBoardPool[billboardId].allocated = FALSE;
    }
}
#line 594 "src/modules/uvbill_rom.c"
