// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

s32 uvModelContainsLocalPoint(f32 arg0, f32 arg1, f32 arg2, uvModelLOD_inner *arg3);
void uvModelGetProps(s32 arg0, ...);
s16 uvModelAppendScalarExtentLodQueryResults(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Mtx4F *arg4, uvModelLOD *arg5,
                              ParsedUVMD *arg6);
s16 uvModelAppendSegmentLodQueryResults(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F *arg6,
                              uvModelLOD *arg7, ParsedUVMD *arg8);
void uvModelCleanup(void);
void uvModelReservedCallback0(s32 arg0);
void uvModelReservedCallback1(s32 arg0, s32 arg1);
void uvModelReservedCallback2(s32 arg0, s32 arg1, s32 arg2);
s32 uvModelGetFirstStateWordAddress(s32 arg0);
void uvModelGetPosm(s32 fileId, s32 arg1, Mtx4F *arg2);
void uvModelGetProps(s32 arg0, ...);
u8 uvModelFindThresholdBand(ParsedUVMD *arg0, f32 arg1);
s16 uvModelTestWorldPointInLodBounds(f32 x, f32 y, f32 z, Mtx4F *arg3, uvModelLOD *arg4);
s32 uvModelContainsLocalPoint(f32 arg0, f32 arg1, f32 arg2, uvModelLOD_inner *arg3);
u8 uvModelIntersectSegmentWithBoundsFaces(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                             UnkUVMD_24_Unk4 *arg6, f32 *arg7, f32 *arg8, s16 *arg9, s16 *arg10);
void uvModelResetMatrixStack(void);
Mtx4F *uvModelGetCurrentMatrix(void);
void uvModelPushMatrix(Mtx4F *src);
void uvModelPopMatrix(void);
void uvModelReplaceTextureId(ParsedUVMD *uvmd, s32 arg1, s32 arg2);
s32 uvModelCollectStatesByTextureId(ParsedUVMD *uvmd, uvGfxState **stateTable, s32 arg2);
void uvModelSetCollisionMetadataWord38(s32 id, s32 arg1);
void __entrypoint_func_uvmodel_rom_400000(UvModel_Exports *exports);

// .rodata
static const char sDevString[] = { "        checking bboxs %f %f %f\n" };
static const char sDevString1[] = { "        passed bbox test\n" };
static const char sDevString2[] = { "in bbox\n" };
static const char sDevString3[] = { "   tv = %f %f %f\n" };
static const char sDevString4[] = { "   inside case\n" };
static const char sDevString5[] = { "   max = %f  face = %d _dbnhits = %d\n" };
static const char sDevString6[] = { "   outside case\n" };
static const char sDevString7[] = { "  hits = %d  dist = %f  nrm = %f %f %f\n" };
static const char sDevString8[] = { "       checking surfaces for sphere\n" };
static const char sDevString9[] = { "         hit surf with *_dbnhits = %d\n" };
static const char sDevString10[] = { "             checking seg in bbox returned %d hits\n" };
static const char sDevString11[] = { "               no surfaces %d hits\n" };
static const char sDevString12[] = { "                checking surfaces for seg\n" };
static const char sDevString13[] = { "          seg: (%.1f %.1f %.1f) - (%.1f %.1f %.1f)\n" };
static const char sDevString14[] = { "          v0:  (%d %d %d)\n" };
static const char sDevString15[] = { "          v1:  (%d %d %d)\n" };
static const char sDevString16[] = { "          v2:  (%d %d %d)\n" };
static const char sDevString17[] = { "          hit a surface\n" };

// .data
s32 D_uvmodel_rom_00403130 = 0;
s32 D_uvmodel_rom_00403134[] = { 0x00500000, __entrypoint_func_uvmodel_rom_400000, 0 };

// .bss
s32 D_uvmodel_rom_00403140;
f32 *D_uvmodel_rom_00403144;
s32 *D_uvmodel_rom_00403148;
s32 *D_uvmodel_rom_0040314C;
Vec3F *D_uvmodel_rom_00403150;
s32 *D_uvmodel_rom_00403154;
s32 *D_uvmodel_rom_00403158;
s32 *D_uvmodel_rom_0040315C;
Mtx4F *D_uvmodel_rom_00403160;
static UvFMtx_Rom_Exports *sUvFmtxExports;
static UvFVec_Rom_Exports *sUvFvecExports;
static UvQuery_Exports *sUvQueryExports;
static UvIntersect_Exports *sUvIntersectExports;
static UvMath_Exports *sUvMathExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;

void __entrypoint_func_uvmodel_rom_400000(UvModel_Exports *exports) {
    s32 *mtxCount;

    uvUpdateFileAllocPtr(exports);
    exports->uvModelReservedCallback0 = uvModelReservedCallback0;
    exports->uvModelReservedCallback1 = uvModelReservedCallback1;
    exports->uvModelReservedCallback2 = uvModelReservedCallback2;
    exports->uvModelGetFirstStateWordAddress = uvModelGetFirstStateWordAddress;
    exports->uvModelGetPosm = uvModelGetPosm;
    exports->uvModelGetProps = uvModelGetProps;
    exports->uvModelFindThresholdBand = uvModelFindThresholdBand;
    exports->uvModelAppendScalarExtentLodQueryResults = uvModelAppendScalarExtentLodQueryResults;
    exports->uvModelAppendSegmentLodQueryResults = uvModelAppendSegmentLodQueryResults;
    exports->uvModelCleanup = uvModelCleanup;
    exports->uvModelTestWorldPointInLodBounds = uvModelTestWorldPointInLodBounds;
    exports->uvModelContainsLocalPoint = uvModelContainsLocalPoint;
    exports->uvModelIntersectSegmentWithBoundsFaces = uvModelIntersectSegmentWithBoundsFaces;
    exports->uvModelResetMatrixStack = uvModelResetMatrixStack;
    exports->uvModelGetCurrentMatrix = uvModelGetCurrentMatrix;
    exports->uvModelPushMatrix = uvModelPushMatrix;
    exports->uvModelPopMatrix = uvModelPopMatrix;
    exports->uvModelReplaceTextureId = uvModelReplaceTextureId;
    exports->uvModelCollectStatesByTextureId = uvModelCollectStatesByTextureId;
    exports->uvModelSetCollisionMetadataWord38 = uvModelSetCollisionMetadataWord38;
    mtxCount = uvGetSystemProp(SYSTEM_PROPID_MODEL_MTX_COUNT);
    if (mtxCount == NULL) {
        D_uvmodel_rom_00403140 = 5;
    } else {
        if (*mtxCount != 0) {
            D_uvmodel_rom_00403140 = *mtxCount;
        } else {
            D_uvmodel_rom_00403140 = 5;
        }
    }

    D_uvmodel_rom_00403160 = _uvMemAllocAlign8(D_uvmodel_rom_00403140 * sizeof(Mtx4F));
    uvMemSet(D_uvmodel_rom_00403160, 0, D_uvmodel_rom_00403140 * sizeof(Mtx4F));
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvFvecExports = uvLoadModule('FVEC');
    sUvQueryExports = uvLoadModule('QERY');
    sUvIntersectExports = uvLoadModule('ISCT');
    sUvMathExports = uvLoadModule('MATH');
    // ! unused export
    sUvGfxStateExports = uvLoadModule('STAT');
    D_uvmodel_rom_00403144 = sUvQueryExports->uvQueryGetFloatValues();
    D_uvmodel_rom_00403148 = sUvQueryExports->uvQueryGetIntValues();
    D_uvmodel_rom_00403150 = sUvQueryExports->uvQueryGetFloatVectors();
    D_uvmodel_rom_00403158 = sUvQueryExports->uvQueryGetHitCountAddress();
    D_uvmodel_rom_00403154 = sUvQueryExports->uvQueryGetSharedWord40Address();
    D_uvmodel_rom_0040314C = sUvQueryExports->uvQueryGetAuxiliaryArrayAddress();
    D_uvmodel_rom_0040315C = sUvQueryExports->uvQueryGetSecondaryCountAddress();
}

#line 127 "src/modules/uvmodel_rom.c"
/* Release the model matrix stack and unload the original five dependency tags.
 * RE_UNKNOWN: this module also loads STAT during initialization but does not
 * unload STAT here; its ownership/release contract remains unproved. Trace module reference
 * accounting and the complete model-module lifetime to resolve this. */
void uvModelCleanup(void) {
    _uvMemFree(D_uvmodel_rom_00403160);
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('QERY');
    uvUnloadModule('ISCT');
    uvUnloadModule('MATH');
}
#line 135 "src/modules/uvmodel_rom.c"

#line 136 "src/modules/uvmodel_rom.c"
/* Original empty model callback with one argument. */
void uvModelReservedCallback0(s32 unused) {
}
#line 138 "src/modules/uvmodel_rom.c"

#line 139 "src/modules/uvmodel_rom.c"
/* Original empty model callback with two arguments. */
void uvModelReservedCallback1(s32 unused0, s32 unused1) {
}
#line 141 "src/modules/uvmodel_rom.c"

#line 142 "src/modules/uvmodel_rom.c"
/* Original empty model callback with three arguments. */
void uvModelReservedCallback2(s32 unused0, s32 unused1, s32 unused2) {
}
#line 144 "src/modules/uvmodel_rom.c"

#line 145 "src/modules/uvmodel_rom.c"
/* Return zero for a missing model or empty first state table; otherwise
 * return its first state-word address through the original integer ABI. */
s32 uvModelGetFirstStateWordAddress(s32 modelId) {
    ParsedUVMD *uvmd;

    uvmd = uvGetLoadedFile('UVMD', modelId);
    if (uvmd == NULL) {
        return 0;
    }
    if (uvmd->unk0->unk0->unk4 == 0) {
        return 0;
    }
    return &uvmd->unk0->unk0->stateTable->state;
}
#line 157 "src/modules/uvmodel_rom.c"

/* Copy a model-part matrix, then divide its translation components by the live model scalar. */
#line 158 "src/modules/uvmodel_rom.c"
void uvModelGetPosm(s32 modelId, s32 partIndex, Mtx4F *posm) {
    ParsedUVMD *model;

    model = uvGetLoadedFile('UVMD', modelId); /* RE_UNKNOWN: resource/model/output lifetime and alias contracts need caller/allocation proof. */
    if ((model == NULL) || (partIndex >= model->unk0->unk8)) { /* RE_ORIGINAL_QUIRK: only an upper index bound is checked; RE_UNKNOWN: negative-index validity needs caller proof. */
        return;
    }
    sUvFmtxExports->uvMat4FCopy(posm, &model->unk8[partIndex]);
    posm->m[3][0] /= model->unk10; /* Keep each scalar reload; RE_UNKNOWN: scalar meaning, zero/nonfinite values and FP contracts need producer/caller proof. */
    posm->m[3][1] /= model->unk10;
    posm->m[3][2] /= model->unk10;
}

#line 171 "src/modules/uvmodel_rom.c"

void uvModelGetProps(s32 modelId, ...) {
    s32 lodIndex;
    u8 hasStateFlag;
    u32 prop;
    uvModelLOD *modelLod;
    ParsedUVMD *uvmd;
    va_list args;

    if (modelId == 0xFFFF) {
        return;
    }
    uvmd = uvGetLoadedFile('UVMD', modelId);
    va_start(args, modelId);
    if (uvmd == NULL) {
        return;
    }

    while (TRUE) {
        prop = va_arg(args, s32);
        switch (prop) {
            case 2:
                *va_arg(args, s32 *) = uvmd->unk4;
                break;
            case 5:
                modelLod = uvmd->unk0->unk0;
                if (modelLod->unk4 == 0) {
                    hasStateFlag = FALSE;
                } else {
                    if (modelLod->stateTable->state & 0x02000000) {
                        hasStateFlag = TRUE;
                    } else {
                        hasStateFlag = FALSE;
                    }
                }
                *va_arg(args, u8 *) = hasStateFlag;
                break;
            case 4:
                *va_arg(args, s32 *) = uvmd->unk0->unk8;
                break;
            case 1:
                *va_arg(args, f32 *) = uvmd->unkC;
                break;
            case 9:
                *va_arg(args, f32 *) = uvmd->unk10;
                break;
            case 8:
                *va_arg(args, s32 *) = uvmd->unk5;
                break;
            case 7:
                lodIndex = va_arg(args, s32);
                *va_arg(args, s32 *) = uvmd->unk0->unk0[lodIndex].unk6;
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}
#line 230 "src/modules/uvmodel_rom.c"

#line 231 "src/modules/uvmodel_rom.c"
/* Scan model thresholds backward, returning the first strict-lower band;
 * retain zero/default and 255 upper-threshold sentinels and byte indices. */
u8 uvModelFindThresholdBand(ParsedUVMD *model, f32 value) {
    s32 unused0;
    s32 unused1;
    u8 count;
    ParsedUVMD_1 *bands;
    u8 i;

    count = model->unk4;
    bands = model->unk0;

    if (bands->unk4 == 0.0f) {
        return 0;
    }
    if (bands[count - 1].unk4 <= value) {
        return 0xFF;
    }

    for (i = count; i > 0; i--) {
        if (bands[i - 1].unk4 < value) {
            return i;
        }
    }

    return 0;
}
#line 256 "src/modules/uvmodel_rom.c"

/* Transform a point and scalar extent into model space and append bounds, axis or decoded-triangle query results. */
#line 257 "src/modules/uvmodel_rom.c"
s16 uvModelAppendScalarExtentLodQueryResults(f32 queryX, f32 queryY, f32 queryZ, f32 scalarExtent, Mtx4F *modelMatrix, uvModelLOD *lod,
                              ParsedUVMD *model) {
    Mtx4F inverseMatrix;
    Vec3F localPoint;
    Vec3F transformedExtent;
    uvModelLOD_inner *bounds;
    Vec3F *outputNormal;
    f32 rootOrDistance;
    s32 initialHitCount;
    f32 radicand;
    s32 queryMode;
    f32 rangeOrGap;
    f32 localExtent;
    f32 extentXY;
    f32 historicalUnusedScalar; /* RE_UNKNOWN: unused declaration and empty scaffolds retain compiler behavior; historical source needs independent evidence. */
    f64 boundedFraction;
    s32 commandElementCount;
    s32 commandWord0;
    s32 commandWord1;
    s32 opcodeVertexBaseOrContact;
    f32 lowerXGap;
    f32 upperXGap;
    f32 lowerYGap;
    f32 upperYGap;
    f32 lowerZGap;
    f32 upperZGap;
    s32 elementIndex;
    s32 loadedVertexCount;
    Vec3F axisEndpoint;
    Vtx *vertices;
    Gfx *command;
    s32 vertexMap[32];
    u32 vertex2;
    u32 vertex0;
    u32 vertex1;
    f32 normalizedGapZ;
    f32 normalizedGapY;
    f32 normalizedGapX;
    uvModelLOD_inner *axisBounds;
    query_78 *detailRecord;
    query_28 *axisRecord;
    s32 signedFace;
    u32 vertexCountBits;
    s32 index;

    initialHitCount = *D_uvmodel_rom_00403158; /* RE_UNKNOWN: shared arrays/counts/IDs, callback mutation, aliases and lifetimes need allocation/caller proof. */
    // clang-format off
    localPoint.x = queryX;localPoint.y = queryY;localPoint.z = queryZ;
    // clang-format on
    if (queryZ) { /* Retain the historical empty conditional. */
    }
    transformedExtent.x = scalarExtent;
    transformedExtent.y = scalarExtent;
    transformedExtent.z = scalarExtent;

    if (sUvFmtxExports->uvMat4InvertAffineByCofactors(&inverseMatrix, modelMatrix) == 0) {
        return -1;
    }
    sUvFmtxExports->uvMat4TransformPoint(&inverseMatrix, &localPoint, &localPoint);
    sUvFmtxExports->uvMat4TransformDirection(&inverseMatrix, &transformedExtent, &transformedExtent);
    transformedExtent.x = (transformedExtent.x > 0.00f) ? (transformedExtent.x) : (-transformedExtent.x); /* Keep ordered comparisons and arithmetic grouping; RE_UNKNOWN: extent conventions and FP/nonfinite domains need caller proof. */
    transformedExtent.y = (transformedExtent.y > 0.00f) ? (transformedExtent.y) : (-transformedExtent.y);
    transformedExtent.z = (transformedExtent.z > 0.00f) ? (transformedExtent.z) : (-transformedExtent.z);
    if (transformedExtent.y < transformedExtent.x) {
        extentXY = transformedExtent.x;
    } else {
        extentXY = transformedExtent.y;
    }

    if (transformedExtent.z < extentXY) {
        if (transformedExtent.y < transformedExtent.x) {
            extentXY = transformedExtent.x;
        } else {
            extentXY = transformedExtent.y;
        }
        localExtent = extentXY;
    } else {
        localExtent = transformedExtent.z;
    }
    sUvQueryExports->uvQueryGetProps(0, 1, &queryMode, 0);
    if (model->unk5 & 2) { /* Only this flag initializes bounds/gaps; RE_UNKNOWN: later bounds-path validity needs complete flag/asset/caller proof. */
        bounds = &lod->unk8;
        lowerXGap = lod->unk8.unk0 - localPoint.x;
        if (localExtent < lowerXGap) {
            return -1;
        }
        upperXGap = localPoint.x - bounds->unkC;
        if (localExtent < upperXGap) {
            return -1;
        }
        lowerYGap = bounds->unk4 - localPoint.y;
        if (localExtent < lowerYGap) {
            return -1;
        }
        upperYGap = localPoint.y - bounds->unk10;
        if (localExtent < upperYGap) {
            return -1;
        }
        lowerZGap = bounds->unk8 - localPoint.z;
        if (localExtent < lowerZGap) {
            return -1;
        }
        upperZGap = localPoint.z - bounds->unk14;
        if (localExtent < upperZGap) {
            return -1;
        }
        if (1) { /* Retain six empty compiler scaffolds; historical source remains unknown. */
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
    }
    if (model->unk5 & 0x10) { /* Prioritize X, then Y, then Z axis records; each tests the live secondary count before writing. */
        if ((queryMode != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->uvQueryGetSecondaryValue())) {
            radicand = (localExtent * localExtent) - ((localPoint.y * localPoint.y) + (localPoint.z * localPoint.z));
            if (((localPoint.y * localPoint.y) + (localPoint.z * localPoint.z)) <= (localExtent * localExtent)) {
                rootOrDistance = sUvMathExports->uvSqrtf(radicand);
                axisBounds = &lod->unk8;
                rangeOrGap = axisBounds->unkC - axisBounds->unk0;
                if (rangeOrGap > 0.00001f) {
                    if ((axisBounds->unk0 <= (localPoint.x + rootOrDistance))
                        && ((localPoint.x - rootOrDistance) <= axisBounds->unkC)) {
                        axisRecord =
                            sUvQueryExports->uvQueryGetSecondaryRecordArray() + (*D_uvmodel_rom_0040315C);
                        axisRecord->unk0 = *D_uvmodel_rom_00403154;
                        axisEndpoint.x = axisBounds->unk0;
                        axisEndpoint.y = 0.0f;
                        axisEndpoint.z = 0.0f;
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk14,
                                                                 (Vec3F *) (&axisEndpoint));
                        axisEndpoint.x = axisBounds->unkC;
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk8,
                                                                 (Vec3F *) (&axisEndpoint));
                        axisRecord->unk20 = rangeOrGap;
                        axisRecord->unk24 = (-axisBounds->unk0) / rangeOrGap;
                        if (lod->unk4 != 0) {
                            axisRecord->unk4 = (s32) lod->stateTable->state;
                            if (detailRecord) { /* RE_UNKNOWN: retained source test uses a conditionally assigned local; historical declaration/control needs source evidence. */
                            }
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (model->unk5 & 0x20) {
        if ((queryMode != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->uvQueryGetSecondaryValue())) {
            radicand = (localExtent * localExtent) - ((localPoint.x * localPoint.x) + (localPoint.z * localPoint.z));
            if (((localPoint.x * localPoint.x) + (localPoint.z * localPoint.z)) <= (localExtent * localExtent)) {
                rootOrDistance = sUvMathExports->uvSqrtf(radicand);
                axisBounds = &lod->unk8;
                rangeOrGap = axisBounds->unk10 - axisBounds->unk4;
                if (rangeOrGap > 0.00001f) {
                    if ((axisBounds->unk4 <= (localPoint.y + rootOrDistance))
                        && ((localPoint.y - rootOrDistance) <= axisBounds->unk10)) {
                        axisRecord =
                            sUvQueryExports->uvQueryGetSecondaryRecordArray() + (*D_uvmodel_rom_0040315C);
                        axisRecord->unk0 = (s32) (*D_uvmodel_rom_00403154);
                        axisEndpoint.y = axisBounds->unk4;
                        axisEndpoint.x = (axisEndpoint.z = 0.0f);
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk14, &axisEndpoint);
                        axisEndpoint.y = axisBounds->unk10;
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk8, &axisEndpoint);
                        axisRecord->unk20 = rangeOrGap;
                        axisRecord->unk24 = (-axisBounds->unk4) / rangeOrGap;
                        if (lod->unk4 != 0) {
                            axisRecord->unk4 = (s32) lod->stateTable->state;
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (model->unk5 & 0x40) {
        if ((queryMode != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->uvQueryGetSecondaryValue())) {
            radicand = (localExtent * localExtent) - ((localPoint.x * localPoint.x) + (localPoint.y * localPoint.y));
            if (((localPoint.x * localPoint.x) + (localPoint.y * localPoint.y)) <= (localExtent * localExtent)) {
                rootOrDistance = sUvMathExports->uvSqrtf(radicand);
                axisBounds = &lod->unk8;
                rangeOrGap = axisBounds->unk14 - axisBounds->unk8;
                if (rangeOrGap > 0.00001f) {
                    if ((axisBounds->unk8 <= (localPoint.z + rootOrDistance))
                        && ((localPoint.z - rootOrDistance) <= axisBounds->unk14)) {
                        axisRecord =
                            &sUvQueryExports->uvQueryGetSecondaryRecordArray()[*D_uvmodel_rom_0040315C];
                        axisRecord->unk0 = *D_uvmodel_rom_00403154;
                        axisEndpoint.z = axisBounds->unk8;
                        axisEndpoint.x = (axisEndpoint.y = 0.0f);
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk14, &axisEndpoint);
                        axisEndpoint.z = axisBounds->unk14;
                        sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &axisRecord->unk8, &axisEndpoint);
                        axisRecord->unk20 = rangeOrGap;
                        axisRecord->unk24 = (-axisBounds->unk8) / rangeOrGap;
                        if (lod->unk4 != 0) {
                            axisRecord->unk4 = (s32) lod->stateTable->state;
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (!(model->unk5 & 4)) { /* RE_ORIGINAL_QUIRK: consumes conditionally initialized bounds/gaps; no defaults are invented. */
        normalizedGapX = (normalizedGapY = (normalizedGapZ = 0.0f));
        outputNormal = &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158];
        if (lowerXGap > 0.0f) {
            normalizedGapX += lowerXGap / localExtent;
        }
        if (upperXGap > 0.0f) {
            normalizedGapX += upperXGap / localExtent;
        }
        if (lowerYGap > 0.0f) {
            normalizedGapY += lowerYGap / localExtent;
        }
        if (upperYGap > 0.0f) {
            if (1) {
                normalizedGapY += upperYGap / localExtent;
            }
        }
        if (lowerZGap > 0.0f) {
            normalizedGapZ += lowerZGap / localExtent;
        }
        if (upperZGap > 0.0f) {
            normalizedGapZ += upperZGap / localExtent;
        }
        if (((normalizedGapX == 0.0f) && (normalizedGapY == 0.0f)) && (normalizedGapZ == 0.0f)) {
            rangeOrGap = -10000000000.0f; /* RE_UNKNOWN: face initialization when ordered comparisons all fail needs nonfinite-input/caller proof. */
            if (rangeOrGap < upperXGap) {
                rangeOrGap = upperXGap;
                signedFace = 1;
            }
            if (rangeOrGap < lowerXGap) {
                rangeOrGap = lowerXGap;
                signedFace = -1;
            }
            if (rangeOrGap < upperYGap) {
                rangeOrGap = upperYGap;
                signedFace = 2;
            }
            if (rangeOrGap < lowerYGap) {
                rangeOrGap = lowerYGap;
                signedFace = -2;
            }
            if (rangeOrGap < upperZGap) {
                rangeOrGap = upperZGap;
                signedFace = 3;
            }
            if (rangeOrGap < lowerZGap) {
                rangeOrGap = lowerZGap;
                signedFace = -3;
            }
            sUvIntersectExports->uvIntersectCopySignedMatrixRowVector(modelMatrix, signedFace, outputNormal);
            boundedFraction = (-rangeOrGap) / localExtent; /* RE_ORIGINAL_QUIRK: divide without a zero guard; unordered upper-clamp comparison takes the 1.0 branch. */
            // clang-format off
            if (boundedFraction < 1.0) { D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = boundedFraction; } else { boundedFraction = 1.0; D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = boundedFraction;
            }
            // clang-format on
            D_uvmodel_rom_0040314C[*D_uvmodel_rom_00403158] |= 1;
        } else {
            rootOrDistance = sUvMathExports->uvSqrtf(((normalizedGapX * normalizedGapX) + (normalizedGapY * normalizedGapY)) + (normalizedGapZ * normalizedGapZ));
            if (rootOrDistance > 1.0f) {
                return -1;
            }
            outputNormal->x = (-normalizedGapX) / rootOrDistance;
            outputNormal->y = (-normalizedGapY) / rootOrDistance;
            outputNormal->z = (-normalizedGapZ) / rootOrDistance;
            sUvFmtxExports->uvMat4TransformDirection(modelMatrix, outputNormal, outputNormal);
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = rootOrDistance;
        }
        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
        if (queryMode != 0) {
            detailRecord = sUvQueryExports->uvQueryGetActiveRecordArray() + (*D_uvmodel_rom_00403158);
            detailRecord->unk0.x = bounds->unk0;
            detailRecord->unk0.y = bounds->unk4;
            detailRecord->unk0.z = bounds->unk8;
            detailRecord->unkC.x = bounds->unkC;
            detailRecord->unkC.y = bounds->unk10;
            detailRecord->unkC.z = bounds->unk14;
            sUvFmtxExports->uvMat4FCopy(&detailRecord->unk30, &inverseMatrix);
            detailRecord->unk70 &= ~1;
            if (lod->unk4 != 0) {
                detailRecord->unk74 = (s32) lod->stateTable->state;
            }
        }
        *D_uvmodel_rom_00403158 += 1; /* This bounds path publishes without a capacity check; RE_UNKNOWN: buffer extent needs allocation/caller proof. */
        return 1;
    }
    if (!(model->unk5 & 4)) {
        return (s16) ((*D_uvmodel_rom_00403158) - initialHitCount); /* RE_UNKNOWN: signed count subtraction/narrowing domain needs caller/count-producer proof. */
    }
    vertices = model->vtxTable; /* RE_UNKNOWN: vertex-map indices, command extents/termination and resource lifetimes need asset/caller proof. */
    for (index = 0; index < 32; index++) {
        vertexMap[index] = -1;
    }

    for (index = 0; index < lod->unk4; index++) {
        command = lod->stateTable[index].displayList;
        for (command = ((u32) command) | 0x80000000;; command++) {
            commandWord0 = command->words.w0;
            commandWord1 = command->words.w1;
            commandElementCount = ((u32) (commandWord0 & 0xFF000)) >> 0xC;
            opcodeVertexBaseOrContact = commandWord0 & 0xFF000000;
            if (opcodeVertexBaseOrContact == 0xDF000000) {
                break;
            }
            if (opcodeVertexBaseOrContact == 0x01000000) {
                opcodeVertexBaseOrContact = ((u32) commandWord1) - ((u32) model->vtxTable);
                opcodeVertexBaseOrContact = ((u32) ((void *) (((u32) opcodeVertexBaseOrContact) + 0x80000000))) / (sizeof(Vtx));
                vertexCountBits = commandWord0 & 0xFF000;
                loadedVertexCount = vertexCountBits >> 0xC;
                for (elementIndex = 0; elementIndex < loadedVertexCount; elementIndex++) {
                    s32 vertexSlotOffset = (((u32) (commandWord0 & 0xFE)) >> 1) - commandElementCount;
                    vertexMap[elementIndex + vertexSlotOffset] = elementIndex + opcodeVertexBaseOrContact;
                }

            } else { /* Every other non-end opcode reaches triangle decoding; do not restrict this to a guessed command subset. */
                commandElementCount = 1;
                if (opcodeVertexBaseOrContact == 0x06000000) {
                    commandElementCount = 2;
                }
                for (elementIndex = 0; elementIndex < commandElementCount; elementIndex++) {
                    if (elementIndex == 0) {
                        vertex0 = ((u32) (commandWord0 & 0xFF0000)) >> 0x11;
                        vertex1 = ((u32) (commandWord0 & 0xFF00)) >> 9;
                        vertex2 = ((u32) (commandWord0 & 0xFF)) >> 1;
                    } else {
                        vertex0 = ((u32) (commandWord1 & 0xFF0000)) >> 0x11;
                        vertex1 = ((u32) (commandWord1 & 0xFF00)) >> 9;
                        vertex2 = ((u32) (commandWord1 & 0xFF)) >> 1;
                    }
                    vertex0 = vertexMap[vertex0];
                    vertex1 = vertexMap[vertex1];
                    vertex2 = vertexMap[vertex2];
                    opcodeVertexBaseOrContact = sUvIntersectExports->uvIntersectClassifySphereTriangleContact(
                        localPoint.x, localPoint.y, localPoint.z, localExtent, 1.0f, vertices[vertex0].v.ob[0],
                        vertices[vertex0].v.ob[1], vertices[vertex0].v.ob[2], vertices[vertex1].v.ob[0],
                        vertices[vertex1].v.ob[1], vertices[vertex1].v.ob[2], vertices[vertex2].v.ob[0],
                        vertices[vertex2].v.ob[1], vertices[vertex2].v.ob[2],
                        &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                        &D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158]);
                    if (opcodeVertexBaseOrContact != 0) {
                        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
                        D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] /= -localExtent;
                        if (opcodeVertexBaseOrContact == 1) {
                            D_uvmodel_rom_0040314C[*D_uvmodel_rom_00403158] |= 1;
                        }
                        sUvFmtxExports->uvMat4TransformDirection(
                            modelMatrix, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        sUvFvecExports->uvVec3FNormalize( /* Preserve the ignored normalization result and callback-visible component writes. */
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        if (queryMode != 0) {
                            detailRecord =
                                &sUvQueryExports->uvQueryGetActiveRecordArray()[*D_uvmodel_rom_00403158];
                            detailRecord->unk0.x = vertices[vertex0].v.ob[0];
                            detailRecord->unk0.y = vertices[vertex0].v.ob[1];
                            detailRecord->unk0.z = vertices[vertex0].v.ob[2];
                            detailRecord->unkC.x = vertices[vertex1].v.ob[0];
                            detailRecord->unkC.y = vertices[vertex1].v.ob[1];
                            detailRecord->unkC.z = vertices[vertex1].v.ob[2],
                            detailRecord->unk18.x = vertices[vertex2].v.ob[0];
                            detailRecord->unk18.y = vertices[vertex2].v.ob[1];
                            detailRecord->unk18.z = vertices[vertex2].v.ob[2];
                            detailRecord->unk70 |= 1;
                            detailRecord->unk74 = lod->stateTable[index].state;
                            sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &detailRecord->unk0,
                                                                     &detailRecord->unk0);
                            sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &detailRecord->unkC,
                                                                     &detailRecord->unkC);
                            sUvFmtxExports->uvMat4TransformPoint(modelMatrix, &detailRecord->unk18,
                                                                     &detailRecord->unk18);
                            detailRecord->unk24 = D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158];
                        }
                        if ((++(*D_uvmodel_rom_00403158)) /* RE_ORIGINAL_QUIRK: result writes precede capacity testing; overflow decrements only the count and retains writes. */
                            >= sUvQueryExports->uvQueryGetRecordCapacity()) {
                            --(*D_uvmodel_rom_00403158);
                            return (*D_uvmodel_rom_00403158) - initialHitCount;
                        }
                    }
                }
            }
        }
    }

    return (*D_uvmodel_rom_00403158) - initialHitCount;
}

/* Transform segment endpoints into model space and append bounds-face or decoded-triangle query results. */
#line 654 "src/modules/uvmodel_rom.c"
s16 uvModelAppendSegmentLodQueryResults(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, Mtx4F *modelMatrix,
                              uvModelLOD *lod, ParsedUVMD *model) {
    Mtx4F inverseMatrix;
    Vec3F localStart;
    Vec3F localEnd;
    u8 boundsResult;
    f32 triangleFraction;
    f32 firstFraction;
    f32 lastFraction;
    s16 hitCount; /* RE_UNKNOWN: signed 16-bit hit/state/element counters and return narrowing need count/asset/caller-domain proof. */
    s16 stateIndex;
    s16 elementIndex;
    s16 firstFace;
    s16 lastFace;
    s16 mapIndex;
    Gfx *command;
    s32 commandWord0;
    s32 commandWord1;
    s32 historicalUnusedWord; /* RE_UNKNOWN: unused declarations/storage retain compiler behavior; historical source needs independent evidence. */
    s32 opcodeOrVertexBase;
    s32 vertexCountBitsOrVertex0;
    s32 triangleCount;
    s32 vertex1;
    s32 vertex2;
    s32 vertexSlotOffset;
    s32 historicalUnusedStorage;
    s32 vertexMap[32];
    s32 loadedVertexCount;
    if (sUvFmtxExports->uvMat4InvertAffineByCofactors(&inverseMatrix, modelMatrix) == 0) { /* RE_UNKNOWN: FP domains and matrix/vector conventions need producer/caller proof. */
        return -1;
    }
    localStart.x = startX;
    localStart.y = startY;
    localStart.z = startZ;
    localEnd.x = endX;
    localEnd.y = endY;
    localEnd.z = endZ;
    sUvFmtxExports->uvMat4TransformPoint(&inverseMatrix, (Vec3F *) (&localStart), (Vec3F *) (&localStart));
    sUvFmtxExports->uvMat4TransformPoint(&inverseMatrix, (Vec3F *) (&localEnd), (Vec3F *) (&localEnd));
    hitCount = 0;
    if (model->unk5 & 2) { /* Only this flag initializes bounds results/fractions/faces; RE_UNKNOWN: other paths need flag/asset/caller proof. */
        boundsResult = uvModelIntersectSegmentWithBoundsFaces(localStart.x, localStart.y, localStart.z, localEnd.x, localEnd.y, localEnd.z,
                                          (UnkUVMD_24_Unk4 *) (&lod->unk8), &firstFraction, &lastFraction, &firstFace,
                                          &lastFace);
        if (boundsResult == 0) {
            return -1;
        }
    }
    if (!(model->unk5 & 4)) { /* RE_ORIGINAL_QUIRK: reads conditionally initialized bounds outputs; preserve byte result and per-output store order. */
        sUvIntersectExports->uvIntersectCopySignedMatrixRowVector(
            modelMatrix, firstFace, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
        sUvFvecExports->uvVec3FScale(&D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                                     &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], model->unk10);
        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
        if (boundsResult == 1) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = firstFraction;
        } else if (boundsResult == 2) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = firstFraction;
            *D_uvmodel_rom_00403158 += 1;
            D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
            sUvIntersectExports->uvIntersectCopySignedMatrixRowVector(
                modelMatrix, lastFace, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
            sUvFvecExports->uvVec3FScale(&D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                                         &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], model->unk10);
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = lastFraction;
        } else if (boundsResult == 3) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = 1.0f;
        }
        *D_uvmodel_rom_00403158 += 1;
        return 1; /* RE_ORIGINAL_QUIRK: returns 1 even when bounds result 2 appended two records; no capacity check occurs here. */
    }
    for (mapIndex = 0; mapIndex < 32; mapIndex++) { /* RE_UNKNOWN: shared-buffer capacity, aliases/callback mutation, vertex indices, command termination and lifetimes need producer/caller proof. */
        vertexMap[mapIndex] = -1;
    }

    for (stateIndex = 0; stateIndex < lod->unk4; stateIndex++) {
        command = lod->stateTable[stateIndex].displayList;
        for (command = (Gfx *) (((u32) command) | 0x80000000);; command++) {
            commandWord0 = command->words.w0;
            commandWord1 = command->words.w1;
            opcodeOrVertexBase = commandWord0 & 0xFF000000;
            if (opcodeOrVertexBase == (0xdf << 24)) {
                break;
            }
            if (opcodeOrVertexBase == (0x01 << 24)) {
                opcodeOrVertexBase = ((u32) commandWord1) - ((u32) model->vtxTable);
                opcodeOrVertexBase = ((u32) ((void *) (((u32) opcodeOrVertexBase) + 0x80000000))) / (sizeof(Vtx));
                vertexCountBitsOrVertex0 = (u32) (commandWord0 & 0xFF000);
                loadedVertexCount = vertexCountBitsOrVertex0 >> 0xC;
                // clang-format off
                for (elementIndex = 0; elementIndex < loadedVertexCount; elementIndex++) { \
                    vertexSlotOffset = ((commandWord0 & 0xFE) >> 1) - (vertexCountBitsOrVertex0 >> 0xC); \
                    vertexMap[elementIndex + vertexSlotOffset] = elementIndex + opcodeOrVertexBase; \
                } \
                // clang-format off
            } else { /* Every other non-end opcode reaches triangle decoding; preserve the two-triangle special case. */
                triangleCount = 1;
                if (opcodeOrVertexBase == (0x06 << 24)) {
                    triangleCount = 2;
                }
                for (elementIndex = 0; elementIndex < triangleCount; elementIndex++) {
                    if (elementIndex == 0) {
                        vertexCountBitsOrVertex0 = (commandWord0 & 0xFF0000) >> 17;
                        vertex1 = (commandWord0 & 0xFF00) >> 9;
                        vertex2 = (commandWord0 & 0xFF) >> 1;
                    } else {
                        vertexCountBitsOrVertex0 = (commandWord1 & 0xFF0000) >> 17;
                        vertex1 = (commandWord1 & 0xFF00) >> 9;
                        vertex2 = (commandWord1 & 0xFF) >> 1;
                    }
                    vertexCountBitsOrVertex0 = vertexMap[vertexCountBitsOrVertex0];
                    vertex1 = vertexMap[vertex1];
                    vertex2 = vertexMap[vertex2];
                    if (sUvIntersectExports->uvIntersectSegmentScaledTriangle( /* Provider may write the shared normal before rejecting; early rejection can leave the scalar output untouched. */
                            localStart.x, localStart.y, localStart.z, localEnd.x, localEnd.y, localEnd.z,
                            model->vtxTable[vertexCountBitsOrVertex0].v.ob[0], model->vtxTable[vertexCountBitsOrVertex0].v.ob[1],
                            model->vtxTable[vertexCountBitsOrVertex0].v.ob[2], model->vtxTable[vertex1].v.ob[0],
                            model->vtxTable[vertex1].v.ob[1], model->vtxTable[vertex1].v.ob[2],
                            model->vtxTable[vertex2].v.ob[0], model->vtxTable[vertex2].v.ob[1],
                            model->vtxTable[vertex2].v.ob[2], 1.0f, 1.0f, &triangleFraction,
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158])
                        != 0) {
                        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
                        D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = triangleFraction;
                        sUvFmtxExports->uvMat4TransformDirection(
                            modelMatrix, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        sUvFvecExports->uvVec3FScale(
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], model->unk10);
                        *D_uvmodel_rom_00403158 += 1; /* RE_ORIGINAL_QUIRK: appends without checking capacity; preserve every live count/ID/pointer reload. */
                        hitCount += 1;
                    }
                }
            }
        }
    }

    if (hitCount != 0) {
        return hitCount;
    }
    return -1;
}

#line 798 "src/modules/uvmodel_rom.c"
/* Reject the original absent-bounds sentinel or a failed matrix inverse,
 * transform the point to local space and delegate to the bounds predicate.
 * RE_UNKNOWN: whether original callers guarantee finite points/transforms
 * and finite ordered asset bounds. The helper's strict rejection comparisons
 * do not prove containment for NaNs; trace callers and asset validation. */
#line 800 "src/modules/uvmodel_rom.c"
s16 uvModelTestWorldPointInLodBounds(f32 x, f32 y, f32 z, Mtx4F *transform, uvModelLOD *lod) {
    Mtx4F inverse;
    Vec3F point;

    if (lod->unk8.unk0 == 10000000000.0f) {
        return -1;
    }

    point.x = x;
    point.y = y;
    point.z = z;

    if (sUvFmtxExports->uvMat4InvertAffineByCofactors(&inverse, transform) == 0) {
        return -1;
    }
    sUvFmtxExports->uvMat4TransformPoint(&inverse, &point, &point);
    if (uvModelContainsLocalPoint(point.x, point.y, point.z, &lod->unk8) != 0) {
        return 0;
    }
    return -1;
}
#line 819 "src/modules/uvmodel_rom.c"

#line 820 "src/modules/uvmodel_rom.c"
/* Reject the point on the first strict comparison outside a bound, in the
 * original X/Y/Z order. Equality passes for finite ordered bounds.
 * RE_ORIGINAL_QUIRK: a NaN coordinate takes neither rejection for its axis;
 * preserve these comparisons rather than replacing them with positive tests.
 * RE_UNKNOWN: finite-coordinate and ordered-bound caller/asset guarantees.
 * Trace original bound producers and callers before asserting containment. */
#line 821 "src/modules/uvmodel_rom.c"
s32 uvModelContainsLocalPoint(f32 x, f32 y, f32 z, uvModelLOD_inner *bounds) {
    if (x < bounds->unk0) {
        return FALSE;
    }
    if (bounds->unkC < x) {
        return FALSE;
    }
    if (y < bounds->unk4) {
        return FALSE;
    }
    if (bounds->unk10 < y) {
        return FALSE;
    }
    if (z < bounds->unk8) {
        return FALSE;
    }
    if (bounds->unk14 < z) {
        return FALSE;
    }
    return TRUE;
}
#line 841 "src/modules/uvmodel_rom.c"

#line 842 "src/modules/uvmodel_rom.c"
/* Classify the segment against the axis-aligned bounds and collect up
 * to two face intersections. Side IDs are signed axes: X=1, Y=2, Z=3.
 * RE_ORIGINAL_QUIRK: fully contained endpoints return three and side -1;
 * retain face order, inclusive comparisons and unchanged unused outputs. */
u8 uvModelIntersectSegmentWithBoundsFaces(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ,
                             UnkUVMD_24_Unk4 *bounds, f32 *firstFraction, f32 *secondFraction, s16 *firstSide, s16 *secondSide) {
    s32 hitCount;
    f32 *fractionOutputs[2];
    s16 *sideOutputs[2];
    s32 pad[2];
    f32 fraction;
    f32 segmentMaxX;
    f32 segmentMaxY;
    f32 segmentMaxZ;
    f32 segmentMinX;
    f32 segmentMinY;
    f32 segmentMinZ;
    f32 coordinate;
    f32 deltaZ;
    f32 deltaY;
    f32 deltaX;

    hitCount = 0;

    fractionOutputs[0] = firstFraction;
    fractionOutputs[1] = secondFraction;
    sideOutputs[0] = firstSide;
    sideOutputs[1] = secondSide;
    if (endX < startX) {
        segmentMaxX = startX;
        segmentMinX = endX;
    } else {
        segmentMaxX = endX;
        segmentMinX = startX;
    }
    if (endY < startY) {
        segmentMaxY = startY;
        segmentMinY = endY;
    } else {
        segmentMaxY = endY;
        segmentMinY = startY;
    }
    if (endZ < startZ) {
        segmentMaxZ = startZ;
        segmentMinZ = endZ;
    } else {
        // clang-format off
        segmentMaxZ = endZ; \
        segmentMinZ = startZ;
        // clang format on
    }

    if (segmentMaxX < bounds->unk0) {
        *sideOutputs[hitCount] = -1;
        return 0;
    }

    if (bounds->unkC < segmentMinX) {
        *sideOutputs[hitCount] = 1;
        return 0;
    }

    if (segmentMaxY < bounds->unk4) {
        *sideOutputs[hitCount] = -2;
        return 0;
    }

    if (bounds->unk10 < segmentMinY) {
        *sideOutputs[hitCount] = 2;
        return 0;
    }

    if (segmentMaxZ < bounds->unk8) {
        *sideOutputs[hitCount] = -3;
        return 0;
    }

    if (bounds->unk14 < segmentMinZ) {
        *sideOutputs[hitCount] = 3;
        return 0;
    }
    if ((segmentMaxX <= bounds->unkC) && (bounds->unk0 <= segmentMinX) && (segmentMaxY <= bounds->unk10) && (bounds->unk4 <= segmentMinY) && (segmentMaxZ <= bounds->unk14) && (bounds->unk8 <= segmentMinZ)) {
        *sideOutputs[hitCount] = -1;
        return 3;
    }

    deltaX = endX - startX;
    deltaY = endY - startY;
    deltaZ = endZ - startZ;

    if (segmentMinZ <= bounds->unk8) {
        if (deltaZ == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unk8 - startZ) / deltaZ;
        }
        coordinate = (fraction * deltaX) + startX;
        if ((bounds->unk0 <= coordinate) && (coordinate <= bounds->unkC)) {
            coordinate = (fraction * deltaY) + startY;
            if ((bounds->unk4 <= coordinate) && (coordinate <= bounds->unk10)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = -3;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    if (bounds->unk14 <= segmentMaxZ) {
        if (deltaZ == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unk14 - startZ) / deltaZ;
        }
        coordinate = (fraction * deltaX) + startX;
        if ((bounds->unk0 <= coordinate) && (coordinate <= bounds->unkC)) {
            coordinate = (fraction * deltaY) + startY;
            if ((bounds->unk4 <= coordinate) && (coordinate <= bounds->unk10)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = 3;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    if (segmentMinY <= bounds->unk4) {
        if (deltaY == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unk4 - startY) / deltaY;
        }
        coordinate = (fraction * deltaX) + startX;
        if ((bounds->unk0 <= coordinate) && (coordinate <= bounds->unkC)) {
            coordinate = (fraction * deltaZ) + startZ;
            if ((bounds->unk8 <= coordinate) && (coordinate <= bounds->unk14)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = -2;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    if (bounds->unk10 <= segmentMaxY) {
        if (deltaY == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unk10 - startY) / deltaY;
        }
        coordinate = (fraction * deltaX) + startX;
        if ((bounds->unk0 <= coordinate) && (coordinate <= bounds->unkC)) {
            coordinate = (fraction * deltaZ) + startZ;
            if ((bounds->unk8 <= coordinate) && (coordinate <= bounds->unk14)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = 2;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    if (segmentMinX <= bounds->unk0) {
        if (deltaX == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unk0 - startX) / deltaX;
        }
        coordinate = (fraction * deltaZ) + startZ;
        if ((bounds->unk8 <= coordinate) && (coordinate <= bounds->unk14)) {
            coordinate = (fraction * deltaY) + startY;
            if ((bounds->unk4 <= coordinate) && (coordinate <= bounds->unk10)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = -1;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    if (bounds->unkC <= segmentMaxX) {
        if (deltaX == 0.0f) {
            fraction = 0.0f;
        } else {
            fraction = (bounds->unkC - startX) / deltaX;
        }
        coordinate = (fraction * deltaZ) + startZ;
        if ((bounds->unk8 <= coordinate) && (coordinate <= bounds->unk14)) {
            coordinate = (fraction * deltaY) + startY;
            if ((bounds->unk4 <= coordinate) && (coordinate <= bounds->unk10)) {
                *fractionOutputs[hitCount] = fraction;
                *sideOutputs[hitCount] = 1;
                hitCount++;
                if (hitCount == 2) {
                    return 2;
                }
            }
        }
    }

    return hitCount;
}
#line 1050 "src/modules/uvmodel_rom.c"

#line 1051 "src/modules/uvmodel_rom.c"
/* Reset the model matrix-stack index to -1. */
void uvModelResetMatrixStack(void) {
    D_uvmodel_rom_00403130 = -1;
}
#line 1054 "src/modules/uvmodel_rom.c"

#line 1055 "src/modules/uvmodel_rom.c"
/* Return the address selected by the current matrix-stack index directly.
 * RE_UNKNOWN: whether callers ensure the index is within allocated storage.
 * Reset sets -1 and an over-capacity push retains its increment; trace stack
 * setup and balanced push/pop/get callers before assuming a valid matrix. */
#line 1056 "src/modules/uvmodel_rom.c"
Mtx4F* uvModelGetCurrentMatrix(void) {
    return &D_uvmodel_rom_00403160[D_uvmodel_rom_00403130];
}
#line 1058 "src/modules/uvmodel_rom.c"

#line 1059 "src/modules/uvmodel_rom.c"
/* Advance the matrix-stack index, copying at level zero or composing with
 * the preceding matrix below capacity.
 * RE_ORIGINAL_QUIRK: a rejected push retains the incremented index.
 * RE_UNKNOWN: original caller guarantees for balanced stack operations and
 * capacity; trace initialization and push/pop/get sequences before treating
 * a later getter as valid or changing this preserved overflow behavior. */
#line 1061 "src/modules/uvmodel_rom.c"
void uvModelPushMatrix(Mtx4F* src) {
    Mtx4F* destination;

    if (++D_uvmodel_rom_00403130 >= D_uvmodel_rom_00403140) {
        return;
    }
    if (D_uvmodel_rom_00403130 == 0) {
        destination = (Mtx4F*)D_uvmodel_rom_00403160 + D_uvmodel_rom_00403130;
        sUvFmtxExports->uvMat4FCopy(destination, src);
    } else {
        destination = (Mtx4F*)D_uvmodel_rom_00403160 + (D_uvmodel_rom_00403130);
        sUvFmtxExports->uvMat4Mul(destination, destination - 1, src);
    }
}
#line 1073 "src/modules/uvmodel_rom.c"

#line 1074 "src/modules/uvmodel_rom.c"
/* Decrement the matrix-stack index only when it is nonnegative. */
void uvModelPopMatrix(void) {
    if (D_uvmodel_rom_00403130 >= 0) {
        D_uvmodel_rom_00403130--;
    }
}
#line 1079 "src/modules/uvmodel_rom.c"

#line 1080 "src/modules/uvmodel_rom.c"
#line 1080 "src/modules/uvmodel_rom.c"

/* Visit every model group, LOD and graphics state, replacing matching texture IDs. */
#line 1081 "src/modules/uvmodel_rom.c"
void uvModelReplaceTextureId(ParsedUVMD* model, s32 oldTextureId, s32 newTextureId) {
    s32 groupIndex;
    s32 lodIndex;
    s32 stateIndex;
    uvModelLOD* lod;
    ParsedUVMD_1* group;
    s32 pad;

    for (groupIndex = 0; groupIndex < model->unk4; groupIndex++) {
        group = &model->unk0[groupIndex];
        for (lodIndex = 0; lodIndex < group->unk8; lodIndex++) {
            lod = &group->unk0[lodIndex];
            for (stateIndex = 0; stateIndex < lod->unk4; stateIndex++) {
                sUvGfxStateExports->uvGfxStateReplaceTextureId(&lod->stateTable[stateIndex], oldTextureId, newTextureId);
            }
        }
    }
}
#line 1099 "src/modules/uvmodel_rom.c"
#line 1098 "src/modules/uvmodel_rom.c"

#line 1099 "src/modules/uvmodel_rom.c"
#line 1099 "src/modules/uvmodel_rom.c"

/* Append pointers to graphics states matching the texture ID and return
 * the number written, preserving group/LOD/state traversal and write order.
 * RE_ORIGINAL_QUIRK: this routine has no output-capacity argument or check.
 * RE_UNKNOWN: whether callers provide enough output entries for every match.
 * Trace original callers and loaded-model state counts before assuming that
 * the supplied output pointer array has sufficient storage. */
#line 1101 "src/modules/uvmodel_rom.c"
s32 uvModelCollectStatesByTextureId(ParsedUVMD* model, uvGfxState** outStates, s32 textureId) {
    s32 groupIndex;
    s32 lodIndex;
    s32 stateIndex;
    s32 stateCount;
    ParsedUVMD_1* group;
    uvGfxState* state;
    uvModelLOD* lod;

    stateCount = 0;
    for (groupIndex = 0; groupIndex < model->unk4; groupIndex++) {
        group = &model->unk0[groupIndex];
        for (lodIndex = 0; lodIndex < group->unk8; lodIndex++) {
            lod = &group->unk0[lodIndex];
            for (stateIndex = 0; stateIndex < lod->unk4; stateIndex++) {
                state = &lod->stateTable[stateIndex];
                if (sUvGfxStateExports->uvGfxStateHasTextureId(state, textureId) != 0) {
                    outStates[stateCount++] = state;
                }
            }
        }
    }

    return stateCount;
}
#line 1126 "src/modules/uvmodel_rom.c"
#line 1124 "src/modules/uvmodel_rom.c"

#line 1125 "src/modules/uvmodel_rom.c"
/* For a loaded model with collision metadata, store its word at offset 0x38.
 * The word meaning remains unproven. */
void uvModelSetCollisionMetadataWord38(s32 id, s32 value) {
    ParsedUVMD* uvmd;

    uvmd = uvGetLoadedFile('UVMD', id);
    if (uvmd == NULL) {
        return;
    }
    if (uvmd->unk20 != NULL) {
        uvmd->unk20->unk38 = value;
    }
}
#line 1136 "src/modules/uvmodel_rom.c"
