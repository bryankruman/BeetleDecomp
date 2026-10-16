// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* Partial export-table view grounded in the original GUI initializer.
 * Unused spans preserve verified slot offsets; they are not object padding.
 * RE_UNKNOWN: complete export type and remaining slot contracts are unproven. */
typedef struct MiscGuiCreatorExports {
    u8 unused00[0x40];
    s16 (*allocateCompactText)(void);                       /* 0x40 */
    void *(*getCompactText)(s16);                           /* 0x44 */
    void (*copyCompactText)(void *, u8 *);                  /* 0x48 */
    u8 unused4C[0x14];
    void (*attachCenteredUpperChild)(void *, void *);       /* 0x60 */
    u8 unused64[4];
    void (*attachValueWidget)(void *, void *);              /* 0x68 */
    u8 unused6C[0x3C];
    void (*appendCompactTextRow)(void *, void *);           /* 0xA8 */
    u8 unusedAC[0xC];
    s16 (*allocateScalarWidget)(void);                      /* 0xB8 */
    u8 unusedBC[4];
    void *(*getScalarWidget)(s16);                          /* 0xC0 */
    void (*copyScalarWidgetText)(void *, u8 *);              /* 0xC4 */
    u8 unusedC8[0xC];
    void (*configureScalarWidget)(void *, f32, f32, f32, s32 *); /* 0xD4 */
    void (*setScalarWidgetKind)(void *, s16);                /* 0xD8 */
    u8 unusedDC[0x10];
    s16 (*allocateValueWidget)(void);                       /* 0xEC */
    u8 unusedF0[4];
    void *(*getValueWidget)(s16);                           /* 0xF4 */
    u8 unusedF8[4];
    void (*setValueWidgetLabels)(void *, u8 *, u8 *);        /* 0xFC */
    void (*configureValueWidget)(void *, s32, f32, f32, f32, f32 *); /* 0x100 */
    u8 unused104[0x10];
    void (*setField62Props)(void *, ...);                   /* 0x114 */
} MiscGuiCreatorExports;

/* Only the table prefix and last-bound address are established here.
 * RE_UNKNOWN: interior record fields, bound units and full table size. */
typedef struct MiscGuiCurveTablePrefix {
    s32 count;
    f32 firstBound;
} MiscGuiCurveTablePrefix;
/* Original GUI slots 0x40/44/48/5C/A8. The consumed property selector is
 * signed16; text and row arguments are addresses, not scalar identifiers.
 * RE_UNKNOWN: historical caller declaration widths, unused slots and the
 * complete table contract. This view describes verified target consumption. */
typedef struct {
    u8 unused00[0x40];
    s16 (*allocateCompactText)(void);
    void *(*getCompactText)(s16);
    void (*copyCompactText)(void *, u8 *);
    u8 unused4C[0x10];
    void (*setPropertyWords)(void *, s16, s32);
    u8 unused60[0x48];
    void (*appendCompactTextRow)(void *, void *);
} MiscGuiChildExports;
extern void *gUvGuiExports;
typedef struct { u8 unk00[8]; f32 u, v; } MiscTextureFields;
typedef struct { u8 unk00[4]; MiscTextureFields *first, *second; } MiscTextureFile;
extern f32 D_misc_0040428C;
extern f32 D_misc_004042A4;
extern f32 D_misc_004042B0;
extern f32 D_misc_004042EC;
#include "module.h"

/* Consumed provider and plane views for matrix, hierarchy and crossing helpers.
 * RE_UNKNOWN: Complete historical declarations and provider storage contracts
 * remain unproved; the plane view describes only the consumed 32-byte prefix. */
extern UvQuat_Exports *gUvQuatExports;
extern UvModel_Exports *gUvModelExports;
typedef struct {
    Vec3F unk0;
    Vec3F unkC;
    f32 unk18;
    s32 unk1C;
} MiscPlaneRadiusView;
void miscInterpolateTranslationAndQuaternionMatrix(Mtx4F* output, Mtx4F* first, Mtx4F* second, f32 fraction);
void miscBuildThreeAngleMatrix(Mtx4F *matrix, f32 firstAngle, f32 secondAngle, f32 thirdAngle);
void miscBuildTranslationAndThreeAngleMatrix(Mtx4F* matrix, f32 x, f32 y, f32 z, f32 firstAngle, f32 secondAngle, f32 thirdAngle);
s32 miscCopyObjectHierarchyMatrices(Mtx4F* output, s32 dobj, s32 firstNode, s32 capacity);
s32 miscMeasurePlanarSegmentCircleFraction(f32 startX, f32 startY, f32 endX, f32 endY, f32 centerX, f32 centerY, f32 radius,
                       f32 *fractionOut);
f32 miscEvaluateRadiusGatedPlaneCrossing(MiscPlaneRadiusView* plane, Vec3F* firstPoint, Vec3F* secondPoint);
void * miscCreateGuiCurveValueRow(void * parent, u8* label, u8* firstText, u8* secondText, UvGrphStruct* curve, f32* valueSource, void ** widgetOutput);
f32 miscEvaluateClampedSineAngle(f32 sine);
s32 miscDrawPackedNibbleLine(u8* pixels, u8 color, s16 startX, s16 startY, s16 endX, s16 endY, s16 width, s16 height);
/* Original retained readonly operands; these declarations allocate no storage.
 * RE_UNKNOWN: Complete provider and caller contracts remain unproved. */
extern const f32 D_misc_004042A8;
extern const f32 D_misc_004042AC;
extern const f64 D_misc_004042F0;
extern const char D_misc_00404210[16];
void uvProfilerQueryStatistics(s32, ...);
/* Consumed terrain slots only; provider failure/list lifetime remain unknown. */
typedef struct {
    u8 unused00[0x14];
    void (*sampleHeight)(s32, u32, f32, f32, f32 *, void *);
    u8 unused18[0x10];
    u32 (*findCells)(s32, f32, f32, s32 *);
} MiscTerrainQueryExports;
extern MiscTerrainQueryExports *gUvTerraExports;
#line 61 "src/modules/misc.c"

void func_misc_00400AD0();
void func_misc_00401080();
void func_misc_004012E4();
f32 miscClampFloat(f32 value, f32 upper, f32 lower);
f32 miscFoldAngleDegrees(f32 angle);
f32 miscWrapAngleDegrees(f32 angle);
f32 miscWrapAngleRadians(f32 arg0);
f32 miscFoldAngleRadians(f32 arg0);
f32 func_misc_004016CC(f32, f32);
f32 miscVec2LengthSquared(f32 *vector);
f32 miscVec2Length(f32 *vector);
void miscVec2Normalize(f32 *output, f32 *input);
void miscVec2AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta);
f32 miscVec2Dot(f32 *first, f32 *second);
void miscVec2Add(f32 *output, f32 *first, f32 *second);
void miscVec2Subtract(f32 *output, f32 *first, f32 *second);
void miscVec2Scale(f32 *output, f32 scale, f32 *input);
void miscVec2TransformInPlace();
void miscVec2Copy(f32 *output, f32 *input);
void miscVec2ReflectScaled(f32 *output, f32 *normal, f32 *input, f32 coefficient);
void func_misc_004019FC();
void miscVec3Add(f32 *output, f32 *first, f32 *second);
void miscVec3Subtract(f32 *output, f32 *first, f32 *second);
void miscVec3Scale(f32 *output, f32 scale, f32 *input);
void miscVec3TransformInPlace(f32 *vector, f32 matrix[4][4]);
void miscVec3Copy(f32 *output, f32 *input);
void miscVec4AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta);
void func_misc_00401FA0();
void func_misc_0040213C();
void func_misc_0040234C();
void func_misc_00402528();
void miscGetMatrixDirectionAngles(Mtx4F *matrix, f32 *first, f32 *second, f32 *third);
f32 func_misc_00402730(f32 pointX, f32 pointY, f32 startX, f32 startY, f32 endX, s32 endYInteger, f32* lengthOut, f32* signedFactorOut, f32* distanceOut);
void func_misc_00402874(s32 terrainId, f32 x, f32 y, f32 heightLimit, f32* lowerOut, f32* upperOut);
void miscSetTextureAxisValue(s32 fileId, const char *selector, f32 value);
void func_misc_00402A5C();
void func_misc_00402BFC(Vec3F* vector, Vec3F* normal, f32 coefficient);
void func_misc_00402D48();
void miscVec3Interpolate(f32 *output, f32 *first, f32 *second, f32 fraction);
f32 func_misc_00402EFC(f32 target, f32 current, f32 rate, f32 distanceCap);
void miscVec3ApproachNonlinearPreserveLength(Vec3F *target, Vec3F *current, f32 rate, f32 distanceCap);
void func_misc_00403110();
void *miscLoadFileModule(void);
void miscUnloadFileModule(void);
void func_misc_00403348();
void func_misc_00403650(s32 labelAddress, s32 profiler, s32 y);
void func_misc_00403748();
void *miscCreateGuiBoundScalarRow(void *parent, u8 *label, s16 valueKind, f32 lowerBound, f32 upperBound, s32 *valueSource, void **widgetOutput);
void func_misc_00403A5C();
void *miscCreateGuiTextRow(void *parent, u8 *text, s32 property);
void func_misc_00403CD8();
void func_misc_00403D8C();
f32 miscRandomFloatLcg(void);
extern s32 D_misc_00404300;
extern f32 D_misc_004042F8;
#include "gbi.h"
#include "module.h"
#include "global_exports.h"

typedef struct UnkStruct_misc_004006A0_s {
    /* 0x00 */ f32 unk0;                            /* inferred */
    /* 0x04 */ f32 unk4;                            /* inferred */
    /* 0x08 */ f32 unk8;                            /* inferred */
    /* 0x0C */ f32 unkC;                            /* inferred */
    /* 0x10 */ f32 unk10;                           /* inferred */
    /* 0x14 */ f32 unk14;                           /* inferred */
    /* 0x18 */ f32 unk18;                           /* inferred */
    /* 0x1C */ f32 unk1C;                           /* inferred */
    /* 0x20 */ f32 unk20;                           /* inferred */
    /* 0x24 */ f32 unk24;                           /* inferred */
    /* 0x28 */ f32 unk28;                           /* inferred */
    /* 0x2C */ f32 unk2C;                           /* inferred */
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkStruct_misc_004006A0;                          /* size = 0x3C */

extern f32 D_80025D70;


void miscRebuildOrthonormalBasisFromDirection(Vec3F *arg0, UnkStruct_misc_004006A0 *arg1);
void miscCartesianToSpherical(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5);
void miscSphericalToCartesian(f32 radius, f32 azimuth, f32 elevation, f32* x, f32* y, f32* z);
void miscBuildRotationMatrixFromAngles(Mtx4F *mtx, f32 arg1, f32 arg2, f32 arg3);
/* Export addresses only: declarations repeat existing definitions.
 * RE_UNKNOWN: these declarations do not establish complete callable ABIs. */
void miscBusyWaitSeconds(f32 delay);
f32 miscApproachProportional(f32 target, f32 current, f32 rate);
f32 miscApproachLinear(f32 target, f32 current, f32 speed);
void miscVec3ApproachPreserveLength(Vec3F* target, Vec3F* current, f32 rate);
void miscApproachTransformTranslation(UnkStruct_misc_004006A0* target, UnkStruct_misc_004006A0* current, f32 rate);
void miscVec3ToSpherical(Vec3F vector, f32* radius, f32* azimuth, f32* elevation);
void miscSphericalToVec3(f32 radius, f32 azimuth, f32 elevation, f32* output);
f32 miscTangent(f32 angle);
f32 miscArcCosine(f32 cosine);
void miscExtractTranslationAndDirectionAngles(UnkStruct_misc_004006A0* basis, f32* translationX, f32* translationY, f32* translationZ, f32* firstAngle, f32* middleAngle, f32* lastAngle);
void miscSetTranslationAndRotation(f32 x, f32 y, f32 z, f32 zAngle, f32 xAngle, f32 yAngle, Mtx4F* matrix);
void func_misc_00401078(void);
s32 miscGetMaskedFlagTransition(s32 previous, s32 current, s32 mask);
void func_misc_00400390(void);
f32 miscEvaluateVectorDotThroughClampedHelper(Vec3F *first, Vec3F *second);
void miscSeedRandomLcg(s32 seed);
#line 146 "src/modules/misc.c"
/* Register the MISC module's 73 export addresses after updating its
 * allocation pointer. Preserve the original store order, including slot zero.
 * RE_UNKNOWN: complete public export ABI and table ownership are unproven;
 * the word table describes address storage, not callable function types. */
void __entrypoint_func_misc_400000(u32 *exports) {
    uvUpdateFileAllocPtr(exports);
    exports[0x4 / 4] = (u32)miscBusyWaitSeconds;
    exports[0x8 / 4] = (u32)miscApproachProportional;
    exports[0xC / 4] = (u32)miscApproachLinear;
    exports[0x10 / 4] = (u32)miscVec3ApproachPreserveLength;
    exports[0x14 / 4] = (u32)miscApproachTransformTranslation;
    exports[0x18 / 4] = (u32)miscRebuildOrthonormalBasisFromDirection;
    exports[0x1C / 4] = (u32)miscVec3ToSpherical;
    exports[0x20 / 4] = (u32)miscSphericalToVec3;
    exports[0x24 / 4] = (u32)miscCartesianToSpherical;
    exports[0xA0 / 4] = (u32)miscVec3Subtract;
    exports[0xA4 / 4] = (u32)miscVec3Scale;
    exports[0xA8 / 4] = (u32)miscVec3TransformInPlace;
    exports[0xAC / 4] = (u32)miscVec3Copy;
    exports[0xB0 / 4] = (u32)miscVec4AddScaled;
    exports[0xB4 / 4] = (u32)func_misc_00401FA0;
    exports[0xB8 / 4] = (u32)func_misc_0040213C;
    exports[0xBC / 4] = (u32)func_misc_0040234C;
    exports[0xC0 / 4] = (u32)func_misc_00402528;
    exports[0xC4 / 4] = (u32)miscGetMatrixDirectionAngles;
    exports[0x28 / 4] = (u32)miscSphericalToCartesian;
    exports[0x2C / 4] = (u32)miscTangent;
    exports[0x30 / 4] = (u32)func_misc_00400AD0;
    exports[0x34 / 4] = (u32)miscArcCosine;
    exports[0xC8 / 4] = (u32)func_misc_00402730;
    exports[0x38 / 4] = (u32)miscBuildRotationMatrixFromAngles;
    exports[0xCC / 4] = (u32)func_misc_00402874;
    exports[0x3C / 4] = (u32)miscExtractTranslationAndDirectionAngles;
    exports[0xD0 / 4] = (u32)miscSetTextureAxisValue;
    exports[0x40 / 4] = (u32)miscSetTranslationAndRotation;
    exports[0xD4 / 4] = (u32)func_misc_00402A5C;
    exports[0x44 / 4] = (u32)func_misc_00401078;
    exports[0xD8 / 4] = (u32)func_misc_00402BFC;
    exports[0x48 / 4] = (u32)func_misc_00401080;
    exports[0xDC / 4] = (u32)func_misc_00402D48;
    exports[0x4C / 4] = (u32)miscGetMaskedFlagTransition;
    exports[0xE0 / 4] = (u32)miscVec3Interpolate;
    exports[0xE4 / 4] = (u32)func_misc_00402EFC;
    exports[0xE8 / 4] = (u32)miscVec3ApproachNonlinearPreserveLength;
    exports[0xEC / 4] = (u32)func_misc_00403110;
    exports[0x0 / 4] = (u32)func_misc_00400390;
    exports[0x50 / 4] = (u32)func_misc_004012E4;
    exports[0x54 / 4] = (u32)miscClampFloat;
    exports[0x58 / 4] = (u32)miscFoldAngleDegrees;
    exports[0x5C / 4] = (u32)miscWrapAngleDegrees;
    exports[0x60 / 4] = (u32)miscWrapAngleRadians;
    exports[0xF0 / 4] = (u32)miscLoadFileModule;
    exports[0x64 / 4] = (u32)miscFoldAngleRadians;
    exports[0xF4 / 4] = (u32)miscUnloadFileModule;
    exports[0x68 / 4] = (u32)func_misc_004016CC;
    exports[0xF8 / 4] = (u32)func_misc_00403348;
    exports[0x6C / 4] = (u32)miscVec2LengthSquared;
    exports[0xFC / 4] = (u32)func_misc_00403650;
    exports[0x70 / 4] = (u32)miscVec2Length;
    exports[0x100 / 4] = (u32)func_misc_00403748;
    exports[0x74 / 4] = (u32)miscVec2Normalize;
    exports[0x104 / 4] = (u32)miscCreateGuiBoundScalarRow;
    exports[0x108 / 4] = (u32)func_misc_00403A5C;
    exports[0x10C / 4] = (u32)miscCreateGuiTextRow;
    exports[0x110 / 4] = (u32)miscEvaluateVectorDotThroughClampedHelper;
    exports[0x114 / 4] = (u32)func_misc_00403CD8;
    exports[0x78 / 4] = (u32)miscVec2AddScaled;
    exports[0x7C / 4] = (u32)miscVec2Dot;
    exports[0x80 / 4] = (u32)miscVec2Add;
    exports[0x84 / 4] = (u32)miscVec2Subtract;
    exports[0x118 / 4] = (u32)func_misc_00403D8C;
    exports[0x88 / 4] = (u32)miscVec2Scale;
    exports[0x11C / 4] = (u32)miscSeedRandomLcg;
    exports[0x8C / 4] = (u32)miscVec2TransformInPlace;
    exports[0x120 / 4] = (u32)miscRandomFloatLcg;
    exports[0x90 / 4] = (u32)miscVec2Copy;
    exports[0x94 / 4] = (u32)miscVec2ReflectScaled;
    exports[0x98 / 4] = (u32)func_misc_004019FC;
    exports[0x9C / 4] = (u32)miscVec3Add;
}
#line 147 "src/modules/misc.c"

#line 135 "src/modules/misc.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_misc_00400390(void) {

}
#line 138 "src/modules/misc.c"

#line 96 "src/modules/misc.c"
/* Spin until clock zero reaches its initial seconds value plus the requested
 * delay, using the inherited double-precision deadline and repeated clock
 * updates. RE_UNKNOWN: clock calibration and forward progress determine
 * completion; there is no yield, timeout or input-domain guard. */
#line 98 "src/modules/misc.c"
void miscBusyWaitSeconds(f32 delay) {
    f64 deadline;
    deadline = uvClkGetSec(0) + delay;
    while (uvClkGetSec(0) < deadline) {
    }
}
#line 104 "src/modules/misc.c"
#line 104 "src/modules/misc.c"

// .rodata
extern f32 D_misc_00404220;
#line 107 "src/modules/misc.c"
/* Approach the target proportionally to distance, rate and the shared frame
 * interval. Snap within the original tolerance or when the step would overshoot. */
f32 miscApproachProportional(f32 target, f32 current, f32 rate) {
    f32 step;
    f32 distance;
    f32 difference;
    f32 magnitude;

    if (current < target) {
        difference = target - current;
        magnitude = difference;
    } else {
        difference = target - current;
        magnitude = -difference;
    }
    if (magnitude < D_misc_00404220) {
        return target;
    }
    step = rate * difference * D_80025D70;
    if (difference > 0.0f) {
        distance = difference;
    } else {
        distance = -difference;
    }
    if (step > 0.0f) {
        magnitude = step;
    } else {
        magnitude = -step;
    }
    if (distance < magnitude) {
        current = target;
    } else {
        current = current + step;
    }
    return current;
}
#line 143 "src/modules/misc.c"

// .rodata
extern f32 D_misc_00404224;
#line 146 "src/modules/misc.c"
/* Approach the target by speed times the shared frame interval. Preserve
 * ordered comparisons, near-target tolerance and the original overshoot clamp. */
f32 miscApproachLinear(f32 target, f32 current, f32 speed) {
    f32 step;
    f32 distance;
    f32 difference;
    f32 magnitude;

    if (current < target) {
        difference = target - current;
        magnitude = difference;
    } else {
        difference = target - current;
        magnitude = -difference;
    }
    if (magnitude < D_misc_00404224) {
        return target;
    }
    if (difference > 0) {
        step = speed * D_80025D70;
    } else {
        step = -speed * D_80025D70;
    }
    if (difference > 0.0f) {
        distance = difference;
    } else {
        distance = -difference;
    }
    if (step > 0.0f) {
        magnitude = step;
    } else {
        magnitude = -step;
    }
    if (distance < magnitude) {
        current = target;
    } else {
        current = current + step;
    }
    return current;
}
#line 186 "src/modules/misc.c"

#line 187 "src/modules/misc.c"
/* Approach each component proportionally, then restore the original magnitude.
 * Preserve sequential component updates and both zero-length early returns. */
void miscVec3ApproachPreserveLength(Vec3F* target, Vec3F* current, f32 rate) {
    f32 originalLength;
    f32 currentLength;
    f32 scale;

    originalLength = gUvFvecExports->uvVec3FLen(current);
    if (originalLength == 0.0f) {
        return;
    }

    current->x = miscApproachProportional(target->x, current->x, rate);
    current->y = miscApproachProportional(target->y, current->y, rate);
    current->z = miscApproachProportional(target->z, current->z, rate);

    currentLength = gUvFvecExports->uvVec3FLen(current);
    if (currentLength == 0.0f) {
        return;
    }

    scale = originalLength / currentLength;
    current->x *= scale;
    current->y *= scale;
    current->z *= scale;
}
#line 211 "src/modules/misc.c"


#line 213 "src/modules/misc.c"
/* Approach the three translation fields at offsets 0x30, 0x34 and 0x38.
 * Rotation/basis fields are preserved. The original scalar helper owns tolerance. */
void miscApproachTransformTranslation(UnkStruct_misc_004006A0* target, UnkStruct_misc_004006A0* current, f32 rate) {
    current->unk30 = miscApproachProportional(target->unk30, current->unk30, rate);
    current->unk34 = miscApproachProportional(target->unk34, current->unk34, rate);
    current->unk38 = miscApproachProportional(target->unk38, current->unk38, rate);
}
#line 218 "src/modules/misc.c"

#line 219 "src/modules/misc.c"
/* Normalize the direction in place and rebuild the three perpendicular
 * basis rows using the previous first row as the reference. Degenerate inputs
 * retain the original vector-normalization behavior; translation is untouched. */
void miscRebuildOrthonormalBasisFromDirection(Vec3F* direction, UnkStruct_misc_004006A0* basis) {
    Vec3F forward;
    Vec3F reference;
    Vec3F perpendicular;

    gUvFvecExports->uvVec3FNormalize(direction, direction);
    gUvFvecExports->uvVec3FCopy(&forward, direction);
    reference.x = basis->unk0;
    reference.y = basis->unk4;
    reference.z = basis->unk8;
    gUvFvecExports->uvVec3FCross(&perpendicular, &forward, (Vec3F* ) &reference);
    gUvFvecExports->uvVec3FNormalize(&perpendicular, &perpendicular);
    gUvFvecExports->uvVec3FCross((Vec3F* ) &reference, &perpendicular, &forward);
    gUvFvecExports->uvVec3FNormalize((Vec3F* ) &reference, (Vec3F* ) &reference);
    basis->unk0 = reference.x;
    basis->unk4 = reference.y;
    basis->unk8 = reference.z;
    basis->unk10 = perpendicular.x;
    basis->unk14 = perpendicular.y;
    basis->unk18 = perpendicular.z;
    basis->unk20 = forward.x;
    basis->unk24 = forward.y;
    basis->unk28 = forward.z;
    basis->unkC = 0.0f;
    basis->unk1C = 0.0f;
    basis->unk2C = 0.0f;
}
#line 246 "src/modules/misc.c"

#line 247 "src/modules/misc.c"
/*
 * Forward the by-value vector components and the three output pointers to the
 * scalar Cartesian-to-spherical helper in their original argument order.
 * RE_UNKNOWN: Radius/angle units, zero-vector behavior and writable output
 * aliasing guarantees belong to the scalar helper and its callers.
 */
#line 249 "src/modules/misc.c"
void miscVec3ToSpherical(Vec3F vector, f32* radius, f32* azimuth, f32* elevation) {
    miscCartesianToSpherical(vector.x, vector.y, vector.z, radius, azimuth, elevation);
}
#line 250 "src/modules/misc.c"

#line 251 "src/modules/misc.c"
/* Convert spherical coordinates into three adjacent output components.
 * The shared trigonometry library determines the original angle units. */
void miscSphericalToVec3(f32 radius, f32 azimuth, f32 elevation, f32* output) {
    miscSphericalToCartesian(radius, azimuth, elevation, output, output + 1, output + 2);
}
#line 254 "src/modules/misc.c"

#line 255 "src/modules/misc.c"
/* Convert Cartesian components into radius, azimuth and elevation.
 * A zero radius produces two zero angles; preserve both square-root calls and
 * the original atan2 argument normalization. */
void miscCartesianToSpherical(f32 x, f32 y, f32 z, f32* radius, f32* azimuth, f32* elevation) {
    f32 unusedScalar;
    f32 unusedAngle;
    s32 unusedWord;
    f32 horizontalLength;

    horizontalLength = gUvMathExports->uvSqrtf(SQ(x) + SQ(y));
    *radius = gUvMathExports->uvSqrtf(SQ(x) + SQ(y) + SQ(z));
    if (*radius == 0.0f) {
        *azimuth = 0.0f;
        *elevation = 0.0f;
        return;
    }
    *azimuth = gUvMathExports->uvAtan2F(y / *radius, x / *radius);
    *elevation = gUvMathExports->uvAtan2F(z / *radius, horizontalLength / *radius);
}
#line 271 "src/modules/misc.c"

#line 272 "src/modules/misc.c"
/* Convert radius, azimuth and elevation to X/Y/Z, preserving the original
 * cosine/sine call sequence and multiplication/store order. */
void miscSphericalToCartesian(f32 radius, f32 azimuth, f32 elevation, f32* x, f32* y, f32* z) {
    f32 cosElevation;

    cosElevation =  gUvMathExports->uvCosF(elevation);
    *x = gUvMathExports->uvCosF(azimuth) * (radius * cosElevation);
    *y = gUvMathExports->uvSinF(azimuth) * (radius * cosElevation);
    *z = gUvMathExports->uvSinF(elevation) * radius;
}
#line 280 "src/modules/misc.c"

#line 281 "src/modules/misc.c"
/* Call the math provider sine first and cosine second, then divide the two
 * returned floats. RE_UNKNOWN: provider lifetime, argument domain and
 * zero-cosine behavior require provider and caller contracts; no denominator
 * check is added. */
#line 282 "src/modules/misc.c"
f32 miscTangent(f32 angle) {
    f32 cosine;
    f32 sine;
    sine = gUvMathExports->uvSinF(angle);
    cosine = gUvMathExports->uvCosF(angle);
    return sine / cosine;
}
#line 289 "src/modules/misc.c"
#line 288 "src/modules/misc.c"


#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00400AD0.s")

extern f32 D_misc_00404234;

#line 294 "src/modules/misc.c"
/* Compute inverse cosine after the original [-1, 1] clamp, preserving the
 * special zero-input constant and the shared math library's angle units. */
f32 miscArcCosine(f32 cosine) { /* Compute an angle from clamped cosine through the square-root and angle providers. RE_QUIRK: zero takes the retained readonly constant shortcut before clamping. RE_UNKNOWN: nonfinite-input contract and provider behavior at edge values. */
    if (cosine == 0.0f) {
        return D_misc_00404234;
    }
    if (cosine < -1.0f) {
        cosine = -1.0f;
    } else if (cosine > 1.0f) {
        cosine = 1.0f;
    }
    return gUvMathExports->uvAtan2F(gUvMathExports->uvSqrtf(1 - (cosine * cosine)), cosine);
}
#line 307 "src/modules/misc.c"

// Mtx rotate
#line 309 "src/modules/misc.c"
/* Build the original homogeneous rotation matrix from three angles.
 * The temporary vector holds sin(x), cos(y), sin(y), preserving the original
 * evaluation order and rotation convention. */
void miscBuildRotationMatrixFromAngles(Mtx4F* matrix, f32 angleX, f32 angleY, f32 angleZ) {
    f32 sinZ;
    f32 cosZ;
    Vec3F trigComponents;
    f32 sinYTimesSinX;
    f32 sinYTimesCosX;
    f32 cosX;

    sinZ = gUvMathExports->uvSinF(angleZ);
    cosZ = gUvMathExports->uvCosF(angleZ);
    trigComponents.z = gUvMathExports->uvSinF(angleY);
    trigComponents.y = gUvMathExports->uvCosF(angleY);
    trigComponents.x = gUvMathExports->uvSinF(angleX);
    cosX = gUvMathExports->uvCosF(angleX);
    sinYTimesSinX = trigComponents.z * trigComponents.x;
    matrix->m[0][0] = (cosZ * cosX) - (sinZ * sinYTimesSinX);
    sinYTimesCosX = trigComponents.z * cosX;
    matrix->m[0][1] = (cosZ * trigComponents.x) + (sinZ * sinYTimesCosX);
    matrix->m[0][3] = 0.0f;
    matrix->m[0][2] = -sinZ * trigComponents.y;
    matrix->m[1][0] = -trigComponents.y * trigComponents.x;
    matrix->m[1][1] = trigComponents.y * cosX;
    matrix->m[1][2] = trigComponents.z;
    matrix->m[2][0] = (sinZ * cosX) + (cosZ * sinYTimesSinX);
    matrix->m[2][1] = (sinZ * trigComponents.x) - (cosZ * sinYTimesCosX);
    matrix->m[2][2] = cosZ * trigComponents.y;
    matrix->m[3][3] = 1.0f;
    matrix->m[1][3] = 0.0f;
    matrix->m[2][3] = 0.0f;
    matrix->m[3][0] = 0.0f;
    matrix->m[3][1] = 0.0f;
    matrix->m[3][2] = 0.0f;
}
#line 342 "src/modules/misc.c"

extern f32 D_misc_00404238;
extern f32 D_misc_0040423C;
extern f32 D_misc_00404240;

#line 347 "src/modules/misc.c"
/* Extract translation and three direction angles from the original
 * basis layout. Near the shared singularity threshold, use the original
 * fixed middle angle and zero the other two angles. */
void miscExtractTranslationAndDirectionAngles(UnkStruct_misc_004006A0* basis, f32* translationX, f32* translationY, f32* translationZ, f32* firstAngle, f32* middleAngle, f32* lastAngle) {
    f32 horizontalLength;
    f32 unusedScalar;
    f32 middleComponent;

    middleComponent = basis->unk18;
    horizontalLength = gUvMathExports->uvSqrtf(SQ(basis->unk14) + SQ(basis->unk10));
    if (ABS_2(horizontalLength) < D_misc_00404238) {
        if (middleComponent < 0.0f) {
            *middleAngle = D_misc_0040423C;
        } else {
            *middleAngle = D_misc_00404240;
        }
        *firstAngle = 0.0f;
        *lastAngle = 0.0f;
    } else {
        f32 atanSecond;
        f32 atanFirst;

        *middleAngle = gUvMathExports->uvAtan2F(middleComponent, horizontalLength);
        atanSecond = basis->unk14 / horizontalLength;
        atanFirst = -basis->unk10 / horizontalLength;
        *firstAngle = gUvMathExports->uvAtan2F(atanFirst, atanSecond);
        atanSecond = basis->unk28 / horizontalLength;
        atanFirst = -basis->unk8 / horizontalLength;
        *lastAngle = gUvMathExports->uvAtan2F(atanFirst, atanSecond);
    }
    *translationX = basis->unk30;
    *translationY = basis->unk34;
    *translationZ = basis->unk38;
}
#line 378 "src/modules/misc.c"

#line 379 "src/modules/misc.c"
/* Start with identity, rotate around Z then X then Y, and set translation.
 * Preserve the original axis identifiers and rotation composition order. */
void miscSetTranslationAndRotation(f32 x, f32 y, f32 z, f32 zAngle, f32 xAngle, f32 yAngle, Mtx4F* matrix) {
    gUvFmtxExports->uvMat4SetIdentity(matrix);
    gUvFmtxExports->uvMat4RotateAxis(matrix, zAngle, 0x7A);
    gUvFmtxExports->uvMat4RotateAxis(matrix, xAngle, 0x78);
    gUvFmtxExports->uvMat4RotateAxis(matrix, yAngle, 0x79);
    matrix->m[3][0] = x;
    matrix->m[3][1] = y;
    matrix->m[3][2] = z;
}
#line 388 "src/modules/misc.c"

#line 389 "src/modules/misc.c"
/* The current body stores integer zero through a null pointer.
 * RE_UNKNOWN: deliberate trap intent, caller/export reachability and runtime
 * contract. No C/header caller was found; this does not prove unreachable
 * behavior. Preserve the body pending original assembly/caller evidence. */
void func_misc_00401078(void) {
    *(s32*)0 = 0;
}
#line 392 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00401080.s")

#line 395 "src/modules/misc.c"
/* Return +1 when any masked bit becomes nonzero from an all-zero masked value,
 * -1 for the reverse, otherwise zero. This tests aggregate masked presence,
 * not individual bit changes; a zero mask returns zero. RE_UNKNOWN: flag
 * meanings and caller mask domains remain unspecified. */
#line 397 "src/modules/misc.c"
s32 miscGetMaskedFlagTransition(s32 previous, s32 current, s32 mask) {
    if ((current & mask) && !(previous & mask)) {
        return 1;
    }
    if (!(current & mask) && (previous & mask)) {
        return -1;
    }
    return 0;
}
#line 406 "src/modules/misc.c"
#line 404 "src/modules/misc.c"

/* RE_UNKNOWN: valid blend-weight/input domains, matrix/quaternion frame convention and partial-overlap guarantees; trace original export callers and matrix/quaternion producers before changing interpolation or alias handling. */
/* Blend translation and provider-derived quaternions, then publish the affine matrix fields.
 * RE_UNKNOWN: Interpolation domain, quaternion convention, overlap and provider failure/storage contracts require callers and original providers. */
#line 406 "src/modules/misc.c"
void miscInterpolateTranslationAndQuaternionMatrix(Mtx4F* output, Mtx4F* first, Mtx4F* second, f32 fraction) {
    f32 temp_fv0;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    Quat sp50;
    Quat sp40;
    Quat sp30;

    temp_fv0 = (1.0 - fraction);
    sp68 =  (temp_fv0 * first->m[3][0]) + (second->m[3][0] * fraction);
    sp64 = (temp_fv0 * first->m[3][1]) + (second->m[3][1] * fraction);
    sp60 = (temp_fv0 * first->m[3][2]) + (second->m[3][2] * fraction);
    gUvQuatExports->uvQuatFromRotationMatrix(&sp40, first);
    gUvQuatExports->uvQuatFromRotationMatrix(&sp30, second);
    gUvQuatExports->uvQuatBlendNormalized(&sp50, &sp40, &sp30, fraction);
    gUvFmtxExports->uvMat4SetNormalizedQuaternionRotation(output, sp50.x, sp50.y, sp50.z, sp50.w);
    output->m[0][3] = 0.0f;
    output->m[1][3] = 0.0f;
    output->m[2][3] = 0.0f;
    output->m[3][0] = sp68;
    output->m[3][1] = sp64;
    output->m[3][2] = sp60;
    output->m[3][3] = 1.0f;
}
#line 407 "src/modules/misc.c"

#line 408 "src/modules/misc.c"
/* Compare against the upper argument first, then the lower argument, returning
 * the original value if neither comparison succeeds. Preserve this
 * upper-before-lower argument order and behavior for reversed bounds or
 * unordered comparisons. RE_UNKNOWN: callers must establish the intended bound
 * and floating-point domains. */
#line 410 "src/modules/misc.c"
f32 miscClampFloat(f32 value, f32 upper, f32 lower) {
    if (upper < value) {
        return upper;
    }
    if (value < lower) {
        return lower;
    }
    return value;
}
#line 419 "src/modules/misc.c"
#line 417 "src/modules/misc.c"

#line 414 "src/modules/misc.c"
/* Wrap a degree angle, then fold it into [-90, 90] without changing its sine.
 * Preserve the original comparisons and endpoint choices. */
f32 miscFoldAngleDegrees(f32 angle) { /* Reduce by repeated 360-degree turns, then mirror values beyond +/-90 degrees. RE_QUIRK: strict boundaries and repeated floating-point loops are preserved; extreme magnitudes or infinities can prevent loop progress. RE_UNKNOWN: permitted input magnitude and nonfinite-input contract. */
    f32 wrapped;

    wrapped = angle;
    if (angle > 180.0f) {
        do {
            wrapped -= 360.0f;
        } while (wrapped > 180.0f);
    }
    if (wrapped < -180.0f) {
        do {
            wrapped += 360.0f;
        } while (wrapped < -180.0f);
    }
    if (wrapped > 90.0f) {
        return 180.0f - wrapped;
    }
    if (wrapped < -90.0f) {
        return -180.0f - wrapped;
    }
    return wrapped;
}
#line 415 "src/modules/misc.c"

#line 416 "src/modules/misc.c"
/* Repeatedly subtract or add 360 to bring progressing values into the
 * inclusive -180 to +180 interval, keeping the original subtraction loop
 * before the addition loop. RE_UNKNOWN: finite/progress assumptions belong to
 * callers; infinities or floats too large to change can loop forever, while
 * NaN passes through the comparisons. */
#line 418 "src/modules/misc.c"
f32 miscWrapAngleDegrees(f32 angle) {
    f32 wrapped;

    wrapped = angle;
    if (angle > 180.0f) {
        do {
            wrapped -= 360.0f;
        } while (wrapped > 180.0f);
    }
    if (wrapped < -180.0f) {
        do {
            wrapped += 360.0f;
        } while (wrapped < -180.0f);
    }
    return wrapped;
}
#line 434 "src/modules/misc.c"
#line 417 "src/modules/misc.c"

#line 418 "src/modules/misc.c"
/* Wrap radians into the original [-pi, pi] interval by repeated full turns.
 * Keep separate original float constants and their load order; no remainder
 * approximation or altered handling of non-finite inputs is introduced. */
extern f32 D_misc_00404260;
extern f32 D_misc_00404264;
extern f32 D_misc_00404268;
extern f32 D_misc_0040426C;

/* Apply the two inherited loops using the original positive/negative pi and
 * full-turn float words, with endpoints included. RE_UNKNOWN: callers must
 * supply values for which repeated float addition or subtraction progresses;
 * no nonfinite or magnitude guard is present. */
#line 426 "src/modules/misc.c"
f32 miscWrapAngleRadians(f32 angle) {
    f32 wrapped;
    f32 lowerBound;
    f32 fullTurn;

    wrapped = angle;
    if (D_misc_00404260 < angle) {
        do {
            wrapped -= D_misc_00404264;
        } while (D_misc_00404260 < wrapped);
    }
    lowerBound = D_misc_00404268;
    fullTurn = D_misc_0040426C;
    if (wrapped < lowerBound) {
        do {
            wrapped += fullTurn;
        } while (wrapped < lowerBound);
    }
    return wrapped;
}
#line 446 "src/modules/misc.c"
#line 419 "src/modules/misc.c"

#line 420 "src/modules/misc.c"
/* Wrap radians to [-pi, pi], then reflect into [-pi/2, pi/2].
 * These half-pi bounds use the original 0x3FC90FDB/0xBFC90FDB words;
 * the related uvFoldAngleRadians routine has distinct one-ULP-lower bounds. */
extern f32 D_misc_00404270;
extern f32 D_misc_00404274;
extern f32 D_misc_00404278;
extern f32 D_misc_0040427C;
extern f32 D_misc_00404280;
extern f32 D_misc_00404284;

f32 miscFoldAngleRadians(f32 angle) { /* Reduce and mirror the angle using the original readonly thresholds and turn values. RE_QUIRK: distinct readonly loads, strict comparisons and repeated floating-point loops are preserved; extreme magnitudes or infinities can prevent loop progress. RE_UNKNOWN: permitted input magnitude and nonfinite-input contract. */
    f32 wrapped;
    f32 fullTurn;

    wrapped = angle;
    if (D_misc_00404270 < angle) {
        do {
            wrapped -= D_misc_00404274;
        } while (D_misc_00404270 < wrapped);
    }
    fullTurn = D_misc_00404278;
    if (wrapped < D_misc_0040427C) {
        do {
            wrapped += fullTurn;
        } while (wrapped < D_misc_0040427C);
    }
    if (D_misc_00404280 < wrapped) {
        return D_misc_00404270 - wrapped;
    }
    if (wrapped < D_misc_00404284) {
        return D_misc_0040427C - wrapped;
    }
    return wrapped;
}
#line 421 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_004016CC.s")

#line 424 "src/modules/misc.c"
/* Return a two-component vector's squared length. */
f32 miscVec2LengthSquared(f32 *vector) { /* Sum the two squared components in the original expression order. RE_UNKNOWN: Input finiteness and overflow behavior are caller constraints, not checked here. */ return vector[0]*vector[0] + vector[1]*vector[1]; }
#line 425 "src/modules/misc.c"

#line 426 "src/modules/misc.c"
/* Return the Euclidean length of a two-component vector. */
f32 miscVec2Length(f32 *vector) { /* Pass the two-component squared sum to the original square-root provider. RE_UNKNOWN: Provider behavior for nonfinite or overflowed sums remains unproved. */
    return gUvMathExports->uvSqrtf(miscVec2LengthSquared(vector));
}
#line 427 "src/modules/misc.c"

#line 428 "src/modules/misc.c"
/* Normalize a two-component vector using its reciprocal length. Lengths
 * below the original threshold produce two zero components. Preserve the
 * ordered comparison and sequential stores, including aliased-pointer behavior. */
void miscVec2Normalize(f32 *output, f32 *input) { /* Write zero for lengths strictly below the retained threshold; otherwise multiply each component by the reciprocal length. RE_QUIRK: Equality takes the reciprocal path. RE_UNKNOWN: Nonfinite inputs and partially overlapping buffers are not validated. */
    f32 length = miscVec2Length(input);
    f32 reciprocal;
    if (length < D_misc_0040428C) {
        output[0] = 0.0f;
        output[1] = 0.0f;
    } else {
        reciprocal = 1.0f / length;
        output[0] = input[0] * reciprocal;
        output[1] = input[1] * reciprocal;
    }
}
#line 429 "src/modules/misc.c"

#line 430 "src/modules/misc.c"
/* Add a scaled delta to the base vector, preserving component-store order. */
void miscVec2AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta) { /* Write base plus delta times scale, first component then second. RE_UNKNOWN: Partially overlapping input/output buffers require a caller contract. */
    output[0] = base[0] + delta[0] * scale;
    output[1] = base[1] + delta[1] * scale;
}
#line 437 "src/modules/misc.c"

#line 438 "src/modules/misc.c"
/* Return the two-component dot product with the original floating-point order. */
f32 miscVec2Dot(f32 *first, f32 *second) { /* Return the two ordered component products and their sum. RE_UNKNOWN: Input finiteness and overflow behavior are not validated. */
    return first[0] * second[0] + first[1] * second[1];
}
#line 443 "src/modules/misc.c"

#line 444 "src/modules/misc.c"
/* Add two two-component vectors in X/Y order. */
void miscVec2Add(f32 *output, f32 *first, f32 *second) { /* Write the two component sums in index order. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = first[0] + second[0];
    output[1] = first[1] + second[1];
}
#line 449 "src/modules/misc.c"

#line 450 "src/modules/misc.c"
/* Subtract the second two-component vector from the first in X/Y order. */
void miscVec2Subtract(f32 *output, f32 *first, f32 *second) { /* Write first minus second component by component. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = first[0] - second[0];
    output[1] = first[1] - second[1];
}
#line 454 "src/modules/misc.c"

#line 455 "src/modules/misc.c"
/* Scale a two-component vector, preserving the original load/store order. */
void miscVec2Scale(f32 *output, f32 scale, f32 *input) { /* Write the two input components multiplied by scale. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
}
#line 459 "src/modules/misc.c"

#line 460 "src/modules/misc.c"
/* Transform the vector in place by the matrix's upper-left 2x2 block.
 * Preserve the original multiplication order and cache both input components. */
void miscVec2TransformInPlace(f32 *vector, f32 matrix[4][4]) { /* Snapshot x/y and apply only the upper-left two-by-two matrix entries in the original grouping. RE_QUIRK: Translation is not applied. RE_UNKNOWN: Matrix convention and matrix/vector overlap require caller evidence. */
    f32 x = vector[0];
    f32 y = vector[1];
    vector[0] = x * matrix[0][0] + matrix[1][0] * y;
    vector[1] = x * matrix[0][1] + matrix[1][1] * y;
}
#line 461 "src/modules/misc.c"

#line 462 "src/modules/misc.c"
/* Copy the X/Y components; retain the original behavior for aliased pointers. */
void miscVec2Copy(f32 *output, f32 *input) { /* Copy component zero before component one. RE_UNKNOWN: This is not a general overlapping-memory copy contract. */
    output[0] = input[0];
    output[1] = input[1];
}
#line 466 "src/modules/misc.c"

#line 467 "src/modules/misc.c"
/* Subtract normal * dot(normal, input) * (1 + coefficient) from the input.
 * With a unit normal, coefficient one gives ordinary reflection and zero
 * removes the normal component. Preserve the original two-component scratch. */
void miscVec2ReflectScaled(f32 *output, f32 *normal, f32 *input, f32 coefficient) { /* Subtract normal times dot(normal,input) times one plus coefficient from the input. RE_UNKNOWN: Unit-normal, coefficient-domain and overlapping-buffer contracts remain unproved; no normalization is added. */
    f32 scaledNormal[2];
    miscVec2Scale(scaledNormal, miscVec2Dot(normal, input) * (1.0f + coefficient), normal);
    miscVec2Subtract(output, input, scaledNormal);
}
#line 468 "src/modules/misc.c"
/* RE_ORIGINAL_QUIRK: original overlapping vertical-segment path reads an unwritten intercept stack word. RE_UNKNOWN: caller reachability/input limits; trace original export callers before changing collinear behavior. */
/* Reject separated endpoint bounds, solve the planar crossing, orient a normal
 * against the first start point, and return a clamped fraction along the first line.
 * RE_UNKNOWN: caller restrictions for parallel/degenerate lines and whether the
 * coarse bounds test is intended to establish membership in both segments.
 * The working coordinate and vertical sentinel are reused in successive phases. */
s32 miscFindPlanarCrossingAndNormal(f32 startX, f32 startY, f32 endX, f32 endY, f32 otherStartX, f32 otherStartY, f32 otherEndX, f32 otherEndY,
                       f32 *fractionOut, Vec3F *normalOut) {
    f32 firstMinX;
    f32 firstMinY;
    f32 firstMaxX;
    f32 firstMaxY;
    f32 firstDeltaY;
    f32 firstDeltaX;
    f32 otherDeltaY;
    f32 otherDeltaX;
    f32 firstSlope;
    f32 secondSlopeOrProjection;
    f32 firstIntercept;
    f32 otherIntercept;
    f32 otherLength;
    f32 unusedTemporary0;
    f32 projectedCrossingDistance;
    f32 workingCoordinate;
    f32 verticalSentinelOrCrossingY;
    f32 unusedTemporary1;
    f32 crossingFraction;
    s32 unusedPadding;

    // RE_UNKNOWN: Degenerate/parallel-path caller reachability remains unproved.
    firstDeltaY = endY - startY;
    firstMinX = firstMaxX = startX;
    firstMaxY = startY;
    firstMinY = startY;
    if (endX < startX) {
        firstMinX = endX;
    } else {
        firstMaxX = endX;
    }
    if (endY < startY) {
        firstMinY = endY;
    } else {
        firstMaxY = endY;
    }
    workingCoordinate = otherEndY;
    if (((((otherStartY < firstMinY) && (otherEndY < firstMinY)) || ((firstMaxY < otherStartY) && (firstMaxY < workingCoordinate)))
         || ((otherStartX < firstMinX) && (otherEndX < firstMinX)))
        || ((firstMaxX < otherStartX) && (firstMaxX < otherEndX))) {
        return 0;
    }
    firstDeltaX = endX - startX;
    firstDeltaY = endY - startY;
    if (firstDeltaX == 0.0) {
        verticalSentinelOrCrossingY = 2140143600.0f;
        firstSlope = verticalSentinelOrCrossingY;
    } else {
        verticalSentinelOrCrossingY = 2140143600.0f;
        firstSlope = firstDeltaY / firstDeltaX;
        firstIntercept = endY - (firstSlope * endX);
    }
    otherDeltaY = otherEndY - otherStartY;
    otherDeltaX = otherEndX - otherStartX;
    if (otherDeltaX == 0.0) {
        secondSlopeOrProjection = verticalSentinelOrCrossingY;
    } else {
        secondSlopeOrProjection = otherDeltaY / otherDeltaX;
        otherIntercept = otherEndY - (secondSlopeOrProjection * otherEndX);
    }
    if (firstSlope == verticalSentinelOrCrossingY) {
        workingCoordinate = startX;
        verticalSentinelOrCrossingY = (secondSlopeOrProjection * workingCoordinate) + otherIntercept;
    } else if (secondSlopeOrProjection == verticalSentinelOrCrossingY) {
        workingCoordinate = otherStartX;
        verticalSentinelOrCrossingY = (firstSlope * workingCoordinate) + firstIntercept;
    } else {
        workingCoordinate = (firstIntercept - otherIntercept) / (secondSlopeOrProjection - firstSlope);
        verticalSentinelOrCrossingY = (firstSlope * workingCoordinate) + firstIntercept;
    }
    if ((((verticalSentinelOrCrossingY < firstMinY) || (firstMaxY < verticalSentinelOrCrossingY)) || (workingCoordinate < firstMinX)) || (firstMaxX < workingCoordinate)) {
        return 0;
    }
    otherLength = gUvMathExports->uvSqrtf(SQ(otherDeltaY) + SQ(otherDeltaX));
    if (((startY - otherStartY) * otherDeltaX) < ((startX - otherStartX) * otherDeltaY)) {
        normalOut->x = otherDeltaY / otherLength;
        normalOut->y = (-otherDeltaX) / otherLength;
        normalOut->z = 0.0f;
    } else {
        normalOut->x = (-otherDeltaY) / otherLength;
        normalOut->y = otherDeltaX / otherLength;
        normalOut->z = 0.0f;
    }
    projectedCrossingDistance = ((workingCoordinate - startX) * normalOut->x) + ((verticalSentinelOrCrossingY - startY) * normalOut->y);
    secondSlopeOrProjection = ((endX - startX) * normalOut->x) + ((endY - startY) * normalOut->y);
    if (secondSlopeOrProjection != 0.0) {
        crossingFraction = projectedCrossingDistance / secondSlopeOrProjection;
    } else {
        return 0;
    }
    if (crossingFraction < 0) {
        crossingFraction = 0;
    } else if (crossingFraction > 1.0f) {
        crossingFraction = 1.0f;
    }
    *fractionOut = crossingFraction;
    return 1;
}
#line 470 "src/modules/misc.c"

#line 471 "src/modules/misc.c"
/* Add two three-component vectors in X/Y/Z order. */
void miscVec3Add(f32 *output, f32 *first, f32 *second) { /* Write three component sums in index order. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = first[0] + second[0];
    output[1] = first[1] + second[1];
    output[2] = first[2] + second[2];
}
#line 476 "src/modules/misc.c"

#line 477 "src/modules/misc.c"
/* Subtract the second three-component vector from the first in X/Y/Z order. */
void miscVec3Subtract(f32 *output, f32 *first, f32 *second) { /* Write first minus second for three components in index order. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = first[0] - second[0];
    output[1] = first[1] - second[1];
    output[2] = first[2] - second[2];
}
#line 482 "src/modules/misc.c"

#line 483 "src/modules/misc.c"
/* Scale a three-component vector, preserving the original load/store order. */
void miscVec3Scale(f32 *output, f32 scale, f32 *input) { /* Write three components multiplied by scale in index order. RE_UNKNOWN: Partially overlapping buffers require caller evidence. */
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
    output[2] = input[2] * scale;
}
#line 488 "src/modules/misc.c"

#line 489 "src/modules/misc.c"
/* Transform three components in place using the upper-left matrix block.
 * Cache all input components and preserve the original multiplication/addition order. */
void miscVec3TransformInPlace(f32 *vector, f32 matrix[4][4]) { /* Snapshot x/y/z and apply only the three-by-three matrix entries with the original product grouping. RE_QUIRK: Translation is not applied. RE_UNKNOWN: Matrix convention and matrix/vector overlap require caller evidence. */
    f32 x = vector[0];
    f32 y = vector[1];
    f32 z = vector[2];
    vector[0] = x * matrix[0][0] + y * matrix[1][0] + matrix[2][0] * z;
    vector[1] = x * matrix[0][1] + y * matrix[1][1] + matrix[2][1] * z;
    vector[2] = x * matrix[0][2] + y * matrix[1][2] + matrix[2][2] * z;
}
#line 490 "src/modules/misc.c"

#line 491 "src/modules/misc.c"
/* Copy the X/Y/Z components; retain the original behavior for aliased pointers. */
void miscVec3Copy(f32 *output, f32 *input) { /* Copy the three components in increasing index order. RE_UNKNOWN: Partially overlapping buffers are not a general memory-copy guarantee. */
    output[0] = input[0];
    output[1] = input[1];
    output[2] = input[2];
}
#line 496 "src/modules/misc.c"

#line 497 "src/modules/misc.c"
/* Add a scaled four-component delta to the base vector in component order.
 * The original sequential loads/stores also define aliased-pointer behavior. */
void miscVec4AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta) { /* Write base plus delta times scale for all four components in index order. RE_UNKNOWN: Fourth-component meaning and partially overlapping buffers require caller evidence. */
    output[0] = base[0] + delta[0] * scale;
    output[1] = base[1] + delta[1] * scale;
    output[2] = base[2] + delta[2] * scale;
    output[3] = base[3] + delta[3] * scale;
}
#line 498 "src/modules/misc.c"

/* Offset the first/third angles, negate the second, and combine half-angle
 * sine/cosine products into the quaternion's four components.
 * RE_UNKNOWN: caller axis order, angle convention and required input range. */
void miscBuildQuaternionFromThreeAngles(f32 x, f32 y, f32 z, Quat *quat) {
    f32 secondCosThirdSin;
    f32 secondCos;
    f32 secondCosThirdCos;
    f32 firstHalfAngleOrCosine;
    f32 secondSin;
    f32 thirdSin;
    f32 firstSin;
    f32 thirdCos;
    f32 secondSinThirdSin;
    f32 unusedPadding;
    f32 secondHalfAngleOrProduct;

    firstHalfAngleOrCosine = (x + 1.5707963f) * 0.5f;
    firstSin = gUvMathExports->uvSinF(firstHalfAngleOrCosine);
    firstHalfAngleOrCosine = gUvMathExports->uvCosF(firstHalfAngleOrCosine);
    secondHalfAngleOrProduct = -y * 0.5f;
    secondSin = gUvMathExports->uvSinF(secondHalfAngleOrProduct);
    secondCos = gUvMathExports->uvCosF(secondHalfAngleOrProduct);

    thirdSin = gUvMathExports->uvSinF(((z - 3.1415927f) * 0.5f));
    thirdCos = gUvMathExports->uvCosF(((z - 3.1415927f) * 0.5f));
    secondSinThirdSin = secondSin * thirdSin;
    secondHalfAngleOrProduct = secondSin * thirdCos;
    secondCosThirdCos = secondCos * thirdCos;
    secondCosThirdSin = secondCos * thirdSin;

    quat->x = (firstHalfAngleOrCosine * secondCosThirdCos) + (firstSin * secondSinThirdSin);
    quat->y = (firstHalfAngleOrCosine * secondCosThirdSin) - (firstSin * secondHalfAngleOrProduct);
    quat->z = (firstHalfAngleOrCosine * secondHalfAngleOrProduct) + (firstSin * secondCosThirdSin);
    quat->w = (-firstHalfAngleOrCosine * secondSinThirdSin) + (firstSin * secondCosThirdCos);
}
#line 500 "src/modules/misc.c"

/* Build the three-angle matrix while preserving exact-zero shortcuts and interleaved stores.
 * RE_UNKNOWN: Angle convention, matrix overlap and retained one-iteration scaffold require original callers/compiler evidence. */
#line 501 "src/modules/misc.c"
void miscBuildThreeAngleMatrix(Mtx4F *matrix, f32 firstAngle, f32 secondAngle, f32 thirdAngle) {
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fa1;
    f32 var_fs1;
    f32 var_ft5;
    f32 var_fv1;
    f32 var_fs2;
    f32 var_fs3;

    if (firstAngle == 0.0f) {
        var_fs2 = 1.0f;
        var_fs3 = 0.0f;
    } else {
        var_fs3 = gUvMathExports->uvSinF(firstAngle);
        var_fs2 = gUvMathExports->uvCosF(firstAngle);
    }
    if (secondAngle == 0.0f) {
        var_fa1 = 1.0f;
        var_fs1 = 0.0f;
    } else {
        do {
            var_fs1 = gUvMathExports->uvSinF(secondAngle);
        } while (0); // RE_UNKNOWN: Retained upstream compiler scaffold; historical intent unproved.
        var_fa1 = gUvMathExports->uvCosF(secondAngle);
    }
    if (thirdAngle == 0.0f) {
        var_fa0 = 1.0f;
        var_fv1 = 0.0f;
        var_ft4 = 0.0f;
        var_ft5 = var_fs1;
    } else {
        var_fv1 = gUvMathExports->uvSinF(thirdAngle);
        var_fa0 = gUvMathExports->uvCosF(thirdAngle);
        var_ft4 = var_fv1 * var_fs1;
        var_ft5 = var_fa0 * var_fs1;
    }
    matrix->m[3][0] = 0.0f;
    matrix->m[3][1] = 0.0f;
    matrix->m[1][2] = var_fs1;
    matrix->m[3][2] = 0.0f;
    matrix->m[0][3] = 0.0f;
    matrix->m[1][3] = 0.0f;
    matrix->m[2][3] = 0.0f;
    matrix->m[0][0] = (var_fa0 * var_fs2) - (var_ft4 * var_fs3);
    matrix->m[1][0] = -var_fa1 * var_fs3;
    matrix->m[2][0] = (var_fv1 * var_fs2) + (var_ft5 * var_fs3);
    matrix->m[0][1] = (var_fa0 * var_fs3) + (var_ft4 * var_fs2);
    matrix->m[1][1] = var_fa1 * var_fs2;
    matrix->m[2][1] = (var_fv1 * var_fs3) - (var_ft5 * var_fs2);
    matrix->m[0][2] = -var_fv1 * var_fa1;
    matrix->m[2][2] = var_fa0 * var_fa1;
    matrix->m[3][3] = 1.0f;
}
#line 502 "src/modules/misc.c"
/* RE_UNKNOWN: quaternion normalization/frame convention, cached-adjustment intent, shared flag reset/lifetime/reentrancy and overlap guarantees; trace original quaternion producers, flag writers and callers before changing the cache or transform. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_0040234C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402528.s")

#line 507 "src/modules/misc.c"
/* Store three provider results in order: (-m10,m11), then
 * (m12,sqrt(m10*m10+m11*m11)), then (-m02,m22). Preserve each store before
 * subsequent matrix reads. RE_UNKNOWN: angle convention, provider lifetime and
 * output/input aliasing guarantees need callers; the retained private provider
 * is not replaced with a guessed atan2 contract. */
#line 509 "src/modules/misc.c"
void miscGetMatrixDirectionAngles(Mtx4F *matrix, f32 *first, f32 *second, f32 *third) {
    *first = func_misc_004016CC(-matrix->m[1][0], matrix->m[1][1]);
    *second = func_misc_004016CC(matrix->m[1][2], gUvMathExports->uvSqrtf(matrix->m[1][0] * matrix->m[1][0] + matrix->m[1][1] * matrix->m[1][1]));
    *third = func_misc_004016CC(-matrix->m[0][2], matrix->m[2][2]);
}
#line 514 "src/modules/misc.c"
#line 508 "src/modules/misc.c"

/* Publish segment length, signed factor and absolute projected distance using the original sixth integer input.
 * RE_ORIGINAL_QUIRK: The sixth input remains s32, including its conversions in the floating-point expressions.
 * RE_UNKNOWN: The sixth parameter integer ABI, degenerate domains and output aliasing require original callers/provider evidence. */
#line 509 "src/modules/misc.c"
f32 miscMeasurePlanarSegmentProjection(f32 pointX, f32 pointY, f32 startX, f32 startY, f32 endX, s32 endYInteger, f32* lengthOut, f32* signedFactorOut, f32* distanceOut) {
    f32 longitudinalFactor;
    f32 segmentLengthSquared;

    *lengthOut = gUvMathExports->uvLength2D(endX - startX, (endYInteger - startY));
    segmentLengthSquared = SQ(*lengthOut);
    if (D_misc_004042A4 < segmentLengthSquared) {
        longitudinalFactor = (((startY - pointY) * (startY - endYInteger)) - ((startX - pointX) * (endX - startX))) / segmentLengthSquared;
        *signedFactorOut = (((startY - pointY) * (endX - startX)) - ((startX - pointX) * (endYInteger - startY))) / segmentLengthSquared;;
        if ((*signedFactorOut * *lengthOut) > 0.0f) {
            *distanceOut = *signedFactorOut * *lengthOut;
        } else {
            *distanceOut = -(*signedFactorOut * *lengthOut);
        }
    } else {
        longitudinalFactor = 1.0f;
        *signedFactorOut = 1.0f;
        *distanceOut = 1.0f;
    }
    return longitudinalFactor;
}
#line 510 "src/modules/misc.c"

/* Visit the terrain result list and update the two height outputs in the original branch order.
 * RE_QUIRK: The upper output is updated only in the else-if branch after the lower-output comparison.
 * RE_UNKNOWN: Terrain list lifetime, count limits, output ownership and provider failure behavior require original callers/providers. */
#line 511 "src/modules/misc.c"
void miscUpdateTerrainHeightLimits(s32 terrainId, f32 x, f32 y, f32 heightLimit, f32* lowerOut, f32* upperOut) {
    char unusedStackStorage[0x8];
    s32* cellList;
    s32 i;
    s32 cellCount;
    s32 sampleStatus;
    f32 sampledHeight;

    *lowerOut = D_misc_004042A8;
    *upperOut = D_misc_004042AC;
    // RE_UNKNOWN: Terrain list-output ABI requires original provider/caller confirmation.
    cellCount = gUvTerraExports->findCells(terrainId, x, y, (void*)&cellList);
    if (cellCount == 0) {
        return;
    }

    i = 0;
    if (cellCount > 0) {
        do {
            gUvTerraExports->sampleHeight(terrainId, cellList[i], x, y, &sampledHeight, &sampleStatus);
            if (sampledHeight <= heightLimit) {
                if (*lowerOut < sampledHeight) {
                    *lowerOut = sampledHeight;
                } else if (sampledHeight < *upperOut) {
                    *upperOut = sampledHeight;
                }
            }
        } while (++i != cellCount);
    }
}
#line 512 "src/modules/misc.c"

#line 513 "src/modules/misc.c"
/* Set a loaded texture parameter chosen by selector bytes 1 and 0:
 * byte 1 equal to character 1 selects the first record, otherwise the second;
 * byte 0 equal to u selects offset 8, otherwise offset 12. Missing files or
 * selected records skip the write. Selector reads are conditional on those
 * preceding lookups and are not preceded by pointer/length checks here.
 * RE_UNKNOWN: whether all original callers guarantee two readable selector
 * bytes and which other encodings are intended. Trace caller storage and
 * original selector data before claiming a validated two-character string
 * contract or adding validation. */
#line 518 "src/modules/misc.c"
void miscSetTextureAxisValue(s32 fileId, const char *selector, f32 value) {
    MiscTextureFile *file = uvGetLoadedFile('UVTX', fileId);
    MiscTextureFields *fields;
    if (file != NULL) {
        if (selector[1] == '1') fields = file->first;
        else fields = file->second;
        if (fields != NULL) {
            if (selector[0] == 'u') fields->u = value;
            else fields->v = value;
        }
    }
}
#line 514 "src/modules/misc.c"

/* Build the rotation matrix and install the three supplied translation components.
 * RE_UNKNOWN: Angle convention, input domains and output storage require original callers/providers. */
#line 515 "src/modules/misc.c"
void miscBuildTranslationAndThreeAngleMatrix(Mtx4F* matrix, f32 x, f32 y, f32 z, f32 firstAngle, f32 secondAngle, f32 thirdAngle) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 temp_fv0;
    temp_fs0 = gUvMathExports->uvSinF(thirdAngle);
    temp_fs1 = gUvMathExports->uvCosF(thirdAngle);
    sp3C = gUvMathExports->uvSinF(secondAngle);
    sp38 = gUvMathExports->uvCosF(secondAngle);
    sp34 = gUvMathExports->uvSinF(firstAngle);
    temp_fv0 = gUvMathExports->uvCosF(firstAngle);
    matrix->m[0][0] = (temp_fs1 * temp_fv0) - (temp_fs0 * (sp3C * sp34));
    matrix->m[0][1] = (temp_fs1 * sp34) + (temp_fs0 * (sp3C * temp_fv0));
    matrix->m[0][2] = -temp_fs0 * sp38;
    matrix->m[0][3] = 0.0f;
    matrix->m[1][0] = -sp38 * sp34;
    matrix->m[1][1] = sp38 * temp_fv0;
    matrix->m[1][2] = sp3C;
    matrix->m[1][3] = 0.0f;
    matrix->m[2][0] = (temp_fs0 * temp_fv0) + (temp_fs1 * (sp3C * sp34));
    matrix->m[2][1] = (temp_fs0 * sp34) - (temp_fs1 * (sp3C * temp_fv0));
    matrix->m[2][2] = temp_fs1 * sp38;
    matrix->m[2][3] = 0.0f;
    matrix->m[3][0] = x;
    matrix->m[3][1] = y;
    matrix->m[3][2] = z;
    matrix->m[3][3] = 1.0f;
}
#line 516 "src/modules/misc.c"

/* Adjust the normalized direction along the normal, then restore its scaled original length.
 * RE_UNKNOWN: Normal normalization, coefficient units and source/normal overlap require original callers/providers. */
#line 517 "src/modules/misc.c"
void miscAdjustDirectionAlongNormalPreservingScaledLength(Vec3F* vector, Vec3F* normal, f32 coefficient) {
    f32 normalAdjustment;
    Vec3F* direction;
    f32 originalLength;
    f32 adjustedDot;
    Vec3F normalizedInput;

    originalLength = gUvFvecExports->uvVec3FLen(vector);
    if ((originalLength < D_misc_004042B0)) {
        return;
    }
    gUvFvecExports->uvVec3FNormalize(&normalizedInput, vector);
    adjustedDot = gUvFvecExports->uvVec3FDot(&normalizedInput, normal);
    if (adjustedDot > 0.0f) {
        adjustedDot = -adjustedDot;
    }

    direction = &normalizedInput;
    normalAdjustment = (-2.0f * adjustedDot);
    vector->x = direction->x + (normalAdjustment * normal->x);
    vector->y = direction->y + (normalAdjustment * normal->y);
    vector->z = direction->z + (normalAdjustment * normal->z);
    gUvFvecExports->uvVec3FNormalize(vector, vector);
    coefficient *= originalLength;
    vector->x *= coefficient;
    vector->y *= coefficient;
    vector->z *= coefficient;
}
#line 518 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402D48.s")

#line 521 "src/modules/misc.c"
/* Write three components in order as fraction*second + first*(1-fraction). Do
 * not clamp the fraction or normalize the result. RE_UNKNOWN: all three spans
 * must be valid, and overlapping output writes may change later input reads;
 * caller alias and interpolation domains are unproven. */
#line 523 "src/modules/misc.c"
void miscVec3Interpolate(f32 *output, f32 *first, f32 *second, f32 fraction) {
    f32 complement = 1.0f - fraction;
    output[0] = fraction * second[0] + first[0] * complement;
    output[1] = fraction * second[1] + first[1] * complement;
    output[2] = fraction * second[2] + first[2] * complement;
}
#line 529 "src/modules/misc.c"
#line 522 "src/modules/misc.c"

/* Approach the target using the shared scale word and the original nonlinear distance cap.
 * RE_UNKNOWN: Shared scale meaning, valid rate/cap domains and FP behavior require original writers/callers. */
#line 523 "src/modules/misc.c"
f32 miscApproachWithScaledDistanceCap(f32 target, f32 current, f32 rate, f32 distanceCap) {
    f32 stepDelta;
    f32 absoluteDelta;
    f32 delta;
    f32 magnitudeScratch;

    if (current < target) {
        delta = target - current;
        magnitudeScratch = delta;
    } else {
        delta = target - current;
        magnitudeScratch = -delta;
    }
    if (magnitudeScratch < D_misc_004042EC) {
        return target;
    }
    if (delta > 0.0f) {
        stepDelta = delta;
    } else {
        stepDelta = -delta;
    }
    if ((distanceCap > 0) && (distanceCap < stepDelta)) {
        stepDelta = distanceCap;
    }
    stepDelta *= ((rate * delta) * D_80025D70);
    if (delta > 0.0f) {
        absoluteDelta = delta;
    } else {
        absoluteDelta = -delta;
    }

    if (stepDelta > 0.0f) {
        magnitudeScratch = stepDelta;
    } else {
        magnitudeScratch = -stepDelta;
    }
    if (absoluteDelta < magnitudeScratch) {
        current = target;
    } else {
        current = current + stepDelta;
    }
    return current;
}
#line 524 "src/modules/misc.c"

#line 525 "src/modules/misc.c"
/* Apply the original distance-weighted scalar approach to each component, then
 * restore the original vector magnitude. Zero-length vectors remain unchanged. */
void miscVec3ApproachNonlinearPreserveLength(Vec3F *target, Vec3F *current, f32 rate, f32 distanceCap) {
    f32 originalLength;
    f32 currentLength;
    f32 scale;
    originalLength = gUvFvecExports->uvVec3FLen(current);
    if (originalLength == 0.0f) {
        return;
    }
    current->x = func_misc_00402EFC(target->x, current->x, rate, distanceCap);
    current->y = func_misc_00402EFC(target->y, current->y, rate, distanceCap);
    current->z = func_misc_00402EFC(target->z, current->z, rate, distanceCap);
    currentLength = gUvFvecExports->uvVec3FLen(current);
    if (currentLength == 0.0f) {
        return;
    }
    scale = originalLength / currentLength;
    current->x *= scale;
    current->y *= scale;
    current->z *= scale;
}
#line 526 "src/modules/misc.c"

/* Traverse the model hierarchy matrix stack and copy the selected object matrices to the output.
 * RE_UNKNOWN: Output capacity, hierarchy validity, matrix-stack limits and provider failure behavior require original callers/providers. */
#line 527 "src/modules/misc.c"
s32 miscCopyObjectHierarchyMatrices(Mtx4F* output, s32 dobj, s32 firstNode, s32 capacity) {
    s32 var_s5;
    s32 j;
    s32 var_s1;
    s32 model;
    s32 i;
    s32 sp98;
    s32 sp94;
    s32 var_s4;
    Mtx4F sp50;

    model = gUvDobjExports->uvDobjGetModel(dobj);
    gUvModelExports->uvModelGetProps(model, 4, &sp94, 0);
    gUvModelExports->uvModelResetMatrixStack();
    var_s5 = -1;
    var_s4 = 0;
    for (i = 0; i < sp94; i++) {
        gUvModelExports->uvModelGetProps(model, 7, i, &sp98, 0);
        if (var_s5 >= sp98) {
            var_s1 = (var_s5 - sp98) + 1;
        } else {
            var_s1 = 0;
        }
        var_s5 = sp98;
        for (j = 0; j < var_s1; j++) {
            gUvModelExports->uvModelPopMatrix();
        }
        gUvDobjExports->uvDobjGetPosm(dobj, i, &sp50);
        gUvModelExports->uvModelPushMatrix(&sp50);

        if (i >= firstNode) {
            if (var_s4 >= capacity) {
                return var_s4;
            }
            gUvFmtxExports->uvMat4FCopy((u32)output + (var_s4 * sizeof(Mtx4F)), gUvModelExports->uvModelGetCurrentMatrix());
            var_s4++;
        }
    }
    return var_s4;
}
#line 528 "src/modules/misc.c"

#line 529 "src/modules/misc.c"
/* Load the original filr (file ROM) module using its four-character identifier. */
#line 530 "src/modules/misc.c"
/* Load and return the original filr module export table. Editor callers use
 * the returned pointer; declaring this helper void loses that C contract. */
void *miscLoadFileModule(void) {
    return uvLoadModule('filr');
}
#line 533 "src/modules/misc.c"
#line 532 "src/modules/misc.c"

#line 533 "src/modules/misc.c"
/* Unload the original filr (file ROM) module using its four-character identifier. */
void miscUnloadFileModule(void) {
    uvUnloadModule('filr');
}
#line 536 "src/modules/misc.c"

/* Test the planar segment against a circle and publish the original interval-fraction result.
 * RE_UNKNOWN: Radius/input domains, endpoint conventions and output aliasing require original callers. */
#line 537 "src/modules/misc.c"
s32 miscMeasurePlanarSegmentCircleFraction(f32 startX, f32 startY, f32 endX, f32 endY, f32 centerX, f32 centerY, f32 radius,
                       f32 *fractionOut) {
    u8 sp4F;
    u8 sp4E;
    f32 temp_ft5;
    f32 sp44;
    f32 temp_fa0_3;
    f32 temp_fv1_5;
    f32 ft4;
    f32 temp_fv0;
    f32 sp30;
    f32 fa1;
    f32 tmp;

    sp4F = 0;
    sp4E = 0;
    temp_ft5 = 0;
    if (gUvMathExports->uvSqrtf(SQ(startX - centerX) + SQ(startY - centerY)) < radius) {
        sp4F = 1;
    }

    if (gUvMathExports->uvSqrtf(SQ(endX - centerX) + SQ(endY - centerY)) < radius) {
        sp4E = 1;
    }
    if (sp4F && sp4E) {
        *fractionOut = 1.0f;
        return 1;
    }
    temp_ft5 = endX - startX;
    sp44 = endY - startY;
    fa1 = SQ(temp_ft5) + SQ(sp44);
    if (fa1 == 0) {
        *fractionOut = 0;
        return 0;
    }
    tmp = ((startX - centerX) * temp_ft5) + (sp44 * (startY - centerY));
    ft4 = 2.0f * tmp;
    sp44 = (SQ(startX - centerX)) + (SQ(startY - centerY));
    sp30 = SQ(ft4) - ((4.0f * fa1) * (sp44 - (radius * radius)));

    if (SQ(ft4) < ((4.0f * fa1) * (((SQ(startX - centerX)) + (SQ(startY - centerY))) - SQ(radius)))) {
        *fractionOut = 0.0f;
        return 0;
    }
    temp_fv0 = gUvMathExports->uvSqrtf(sp30);
    sp4F = 0;
    sp4E = 0;
    temp_fa0_3 = ((-ft4) - temp_fv0) / (2.0f * fa1);
    if ((temp_fa0_3 >= 0.0f) && (temp_fa0_3 <= 1.0f)) {
        sp4F = 1;
    }
    temp_fv1_5 = ((-ft4) + temp_fv0) / (2.0f * fa1);
    if ((temp_fv1_5 >= 0.0f) && (temp_fv1_5 <= 1.0f)) {
        sp4E = 1;
    }
    if (sp4F && sp4E) {
        if (temp_fv1_5 < temp_fa0_3) {
            *fractionOut = temp_fa0_3 - temp_fv1_5;
        } else {
            *fractionOut = temp_fv1_5 - temp_fa0_3;
        }
        return 1;
    }
    if (sp4F) {
        *fractionOut = 1.0f - temp_fa0_3;
        return 1;
    }
    if (sp4E) {
        *fractionOut = temp_fv1_5;
        return 1;
    }
    *fractionOut = 0.0f;
    return 0;
}
#line 538 "src/modules/misc.c"

/* Read the profiler duration, format the label/value and draw the original font display list.
 * RE_UNKNOWN: Label storage/length, profiler selector contract and font callback lifetimes require original callers/providers. */
#line 539 "src/modules/misc.c"
void miscDrawProfilerMilliseconds(s32 labelAddress, s32 profiler, s32 y) {
    f64 durationSeconds;
    u8 text[130];

    uvProfilerQueryStatistics(profiler, 3, &durationSeconds, 0);
    sprintf(text, D_misc_00404210, labelAddress, (f32)(f64)(durationSeconds * D_misc_004042F0));
    gUvFontExports->uvSetFont(3);
    gUvFontExports->uvFontColor(255, 0, 0, 255);
    gUvFontExports->uvFontScale(1.0, 1.0);
    gUvFontExports->uvFontPrintStr(160, y, text);
    gUvFontExports->uvFontGenDList();
}
#line 540 "src/modules/misc.c"

/* Test the radius and plane-side conditions, then return the original signed crossing ratio.
 * RE_UNKNOWN: Only the consumed 32-byte view is represented; radius units, direction convention and overlap require original callers. */
#line 541 "src/modules/misc.c"
f32 miscEvaluateRadiusGatedPlaneCrossing(MiscPlaneRadiusView* plane, Vec3F* firstPoint, Vec3F* secondPoint) {
    Vec3F sp3C;
    Vec3F sp30;
    f32 temp_fa0;
    f32 sp28;
    s32 var_v0;
    s32 var_v1;

    gUvFvecExports->uvVec3FSub(&sp3C, &plane->unk0, firstPoint);
    if (SQ(plane->unk18) < gUvFvecExports->uvVec3FLenSquared(&sp3C)) {
        return 0.0f;
    }
    gUvFvecExports->uvVec3FSub(&sp30, &plane->unk0, secondPoint);
    sp28 = gUvFvecExports->uvVec3FDot(&plane->unkC, &sp3C);
    temp_fa0 = gUvFvecExports->uvVec3FDot(&plane->unkC, &sp30);
    if (sp28 >= 0) {
        var_v1 = 1;
    } else {
        var_v1 = -1;
    }

    if (temp_fa0 >= 0) {
        var_v0 = 1;
    } else {
        var_v0 = -1;
    }
    if (var_v0 == var_v1) {
        return 0.0f;
    }
    if ((sp28 < 0.0f) && (plane->unk1C == 0)) {
        return 0.0f;
    }
    if (sp28 >= 0) {
        var_v0 = 1;
    } else {
        var_v0 = -1;
    }
    return var_v0 * (temp_fa0 / (sp28 - temp_fa0));
}
#line 542 "src/modules/misc.c"

#line 543 "src/modules/misc.c"
/* Create and append a compact label row, allocate its scalar widget, then
 * configure the original bounds/source and attach the centered upper child.
 * Flag two in the signed kind short selects integer conversion; other kinds
 * read the source as a float. Return the row and optionally expose its widget.
 * RE_ORIGINAL_QUIRK: allocation results remain unchecked, and label copies
 * retain the original fixed-width reads rather than NUL-string handling.
 * RE_UNKNOWN: remaining kind bits, bound units and value-source ownership/
 * lifetime. The source address is forwarded to widget configuration; trace
 * original widget consumers, caller storage and teardown before assigning
 * ownership or deciding how long that storage must remain readable. */
#line 552 "src/modules/misc.c"
void *miscCreateGuiBoundScalarRow(void *parent, u8 *label, s16 valueKind, f32 lowerBound, f32 upperBound, s32 *valueSource, void **widgetOutput) {
    void *row;
    f32 initialValue;
    void *allocatedRow;
    void *widget;

    allocatedRow = ((MiscGuiCreatorExports *)gUvGuiExports)->getCompactText(((MiscGuiCreatorExports *)gUvGuiExports)->allocateCompactText());
    row = allocatedRow;
    ((MiscGuiCreatorExports *)gUvGuiExports)->copyCompactText(allocatedRow, label);
    ((MiscGuiCreatorExports *)gUvGuiExports)->appendCompactTextRow(parent, row);
    widget = ((MiscGuiCreatorExports *)gUvGuiExports)->getScalarWidget(((MiscGuiCreatorExports *)gUvGuiExports)->allocateScalarWidget());
    ((MiscGuiCreatorExports *)gUvGuiExports)->setScalarWidgetKind(widget, valueKind);
    if (valueSource != NULL) {
        if ((*(s16 *)((u8 *)widget + 0x20)) & 2) {
            initialValue = (f32)*valueSource;
        } else {
            initialValue = *(f32 *)valueSource;
        }
    } else {
        initialValue = 0.0f;
    }
    ((MiscGuiCreatorExports *)gUvGuiExports)->configureScalarWidget(widget, lowerBound, upperBound, initialValue, valueSource);
    ((MiscGuiCreatorExports *)gUvGuiExports)->copyScalarWidgetText(widget, label);
    ((MiscGuiCreatorExports *)gUvGuiExports)->attachCenteredUpperChild(row, widget);
    if (widgetOutput != NULL) {
        *widgetOutput = widget;
    }
    return row;
}
#line 544 "src/modules/misc.c"

/* Append a compact label row, configure its curve-backed value widget and optionally expose that widget.
 * RE_UNKNOWN: Curve count/bounds, value-source storage/lifetime, allocation failure and remaining widget selectors require original callers/providers. */
#line 545 "src/modules/misc.c"
void * miscCreateGuiCurveValueRow(void * parent, u8* label, u8* firstText, u8* secondText, UvGrphStruct* curve, f32* valueSource, void ** widgetOutput) {
    void * row;
    void * widget;
    f32 initialValue;

    if (valueSource != NULL) {
        initialValue = *valueSource;
    } else {
        initialValue = 0.0f;
    }
    row = ((MiscGuiCreatorExports *)gUvGuiExports)->getCompactText(((MiscGuiCreatorExports *)gUvGuiExports)->allocateCompactText());
    ((MiscGuiCreatorExports *)gUvGuiExports)->copyCompactText(row, label);
    ((MiscGuiCreatorExports *)gUvGuiExports)->appendCompactTextRow(parent, row);
    widget = ((MiscGuiCreatorExports *)gUvGuiExports)->getValueWidget(((MiscGuiCreatorExports *)gUvGuiExports)->allocateValueWidget());
    ((MiscGuiCreatorExports *)gUvGuiExports)->attachValueWidget(row, widget);
    ((MiscGuiCreatorExports *)gUvGuiExports)->setValueWidgetLabels(widget, secondText, firstText);
    ((MiscGuiCreatorExports *)gUvGuiExports)->setField62Props(widget, 1, 0, 0);
    ((MiscGuiCreatorExports *)gUvGuiExports)->configureValueWidget(widget, (s32)curve, curve->arr->unk0, curve->arr[curve->count - 1].unk0, initialValue, valueSource);
    if (widgetOutput != NULL) {
        *widgetOutput = widget;
    }
    return row;
}
#line 546 "src/modules/misc.c"

#line 547 "src/modules/misc.c"

#line 548 "src/modules/misc.c"
/* Allocate/get a compact-text row through original GUI slots0x40/44, copy
 * twelve bytes through slot0x48, append through0xA8 and set property3 through
 * slot0x5C. The property selector is consumed as signed16 by its target.
 * RE_UNKNOWN: caller text extent and pool/parent validity are not established
 * by this wrapper. Check original callers and pool allocation before rewrite. */
void *miscCreateGuiTextRow(void *parent, u8 *text, s32 property) {
    void *node;
    node = ((MiscGuiChildExports *)gUvGuiExports)->getCompactText(((MiscGuiChildExports *)gUvGuiExports)->allocateCompactText());
    ((MiscGuiChildExports *)gUvGuiExports)->copyCompactText(node, text);
    ((MiscGuiChildExports *)gUvGuiExports)->appendCompactTextRow(parent, node);
    ((MiscGuiChildExports *)gUvGuiExports)->setPropertyWords(node, 3, property);
    return node;
}
#line 556 "src/modules/misc.c"
#line 548 "src/modules/misc.c"

#line 549 "src/modules/misc.c"
/* Evaluate the clamped scalar helper on the three-component dot product.
 * Original native F0 returns unchanged and Motion66E4 consumes that result.
 * RE_UNKNOWN: historical declarations, intended input lengths, normalization
 * guarantees and result units need original caller/provider evidence. This
 * focused f32 return preserves the observed native result; it does not prove
 * the complete historical module ABI or establish a unit-vector precondition. */
#line 553 "src/modules/misc.c"
f32 miscEvaluateVectorDotThroughClampedHelper(Vec3F *first, Vec3F *second) {
    return miscArcCosine(gUvFvecExports->uvVec3FDot(first, second));
}
#line 552 "src/modules/misc.c"

/* Clamp the sine input and evaluate the original atan2/square-root expression.
 * RE_ORIGINAL_QUIRK: The exact-zero shortcut and clamp comparisons are retained, including their NaN bypass.
 * RE_UNKNOWN: NaN/input domains and approximation/angle convention require original callers/providers. */
#line 553 "src/modules/misc.c"
f32 miscEvaluateClampedSineAngle(f32 sine) {
    if (sine == 0) {
        return 0;
    }

    if (sine < -1.f) {
        sine = -1.f;
    } else if (sine > 1.f) {
        sine = 1.f;
    }

    return gUvMathExports->uvAtan2F(sine, gUvMathExports->uvSqrtf(1 - SQ(sine)));
}
#line 554 "src/modules/misc.c"

/* Clamp the endpoints and draw into packed nibbles using the original signed-short stepping.
 * RE_ORIGINAL_QUIRK: Each endpoint is clamped independently; nibble parity and short truncations are retained.
 * RE_UNKNOWN: Buffer extent, odd-width layout, signed overflow and retained empty conditional require original callers/compiler evidence. */
#line 555 "src/modules/misc.c"
s32 miscDrawPackedNibbleLine(u8* pixels, u8 color, s16 startX, s16 startY, s16 endX, s16 endY, s16 width, s16 height) {
    s16 var_s2;
    s16 var_t4;
    s16 var_v0;
    s16 var_v1;
    s32 var_a1;
    s32 var_t0;
    s16 s0;
    u8* var_s1;
    u8* tmp;

    var_s2 = width >> 1;
    var_v0 = width - 1;
    var_v1 = height - 1;
    if (((startX < 0) && (endX < 0)) || ((var_v0 < startX) && (var_v0 < endX))) {
        return 0;
    }
    if (((startY < 0) && (endY < 0)) || ((((var_v1 < startY))) && (var_v1 < endY))) {
        return 0;
    }
    var_a1 = 1;
    if (startX < 0) {
        startX = 0;
    } else if (var_v0 < startX) {
        startX = var_v0;
    }
    var_t0 = 1;
    if (startY < 0) {
        startY = 0;
    } else if (var_v1 < startY) {
        startY = var_v1;
    }
    if (endX < 0) {
        endX = 0;
    } else if (var_v0 < endX) {
        endX = var_v0;
    }
    if (endY < 0) {
        endY = 0;
    } else if (var_v1 < endY) {
        endY = var_v1;
    }
    var_v0 = endX - startX;
    var_v1 = endY - startY;
    var_s1 = (s16) ((startY * var_s2) + (startX >> 1)) + pixels;
    if (var_v0 < 0) {
        var_t0 = -1;
        var_v0 = var_v0 * -1;
    }
    if (var_v1 < 0) {
        var_a1 = -1;
        var_v1 = var_v1 * -1;
    }
    if (startX & 1) {
        *var_s1 = (*var_s1 & 0xF0) | (color & 0xF);
    } else {
        *var_s1 = (*var_s1 & 0xF) | (color & 0xF0);
    }
    if (var_v0 < var_v1) {
        var_t4 = (var_v0 * 2) - var_v1;
        s0 = (var_v0 - var_v1) * 2;
        while (var_v1--) {
            startY += var_a1;
            if (var_t4 > 0) {
                startX += var_t0;
                var_t4 += s0;
            } else {
                var_t4 += (s16)(var_v0 * 2);
            }
            if (startX & 1) {
                var_s1 = (s16) ((startY * var_s2) + (startX >> 1)) + pixels;
                *var_s1 = (*var_s1 & 0xF0) | (color & 0xF);
            } else {
                var_s1 = (s16) ((startY * var_s2) + (startX >> 1)) + pixels;
                *var_s1 = (*var_s1 & 0xF) | (color & 0xF0);
            }
        }
    } else {
        var_t4 = (var_v1 * 2) - var_v0;
        s0 = (var_v1 - var_v0) * 2;
        while (var_v0--) {
            // RE_UNKNOWN: Retained upstream compiler scaffold; historical intent unproved.
            if (!var_a1) {}

            startX += var_t0;
            if (var_t4 > 0) {
                startY += var_a1;
                var_t4 += s0;
            } else {
                var_t4 += (s16)(var_v1 * 2);
            }
            if (startX & 1) {
                var_s1 = (s16) ((startY * var_s2) + (startX >> 1)) + pixels;
                *var_s1 = (*var_s1 & 0xF0) | (color & 0xF);
            } else {
                var_s1 = (s16) ((startY * var_s2) + (startX >> 1)) + pixels;
                *var_s1 = (*var_s1 & 0xF) | (color & 0xF0);
            }
        }
    }
    return 1;
}
#line 556 "src/modules/misc.c"

#line 557 "src/modules/misc.c"
/* Replace the shared generator word with the supplied seed bits; no validation
 * or other state initialization occurs. RE_UNKNOWN: seed policy and
 * synchronization between users of the shared state require callers. */
#line 558 "src/modules/misc.c"
void miscSeedRandomLcg(s32 seed) {
    D_misc_00404300 = seed;
}
#line 561 "src/modules/misc.c"
#line 560 "src/modules/misc.c"

#line 561 "src/modules/misc.c"
/* Advance the shared word modulo 2^32 with multiplier 0x41C64E6D and increment
 * 0x3039, extract bits 16..30 and divide by the original 32767.0f word. Both
 * zero and one are possible outputs. RE_UNKNOWN: seeding, synchronization and
 * statistical suitability are caller concerns; the native four-byte tail is
 * not part of this body. */
#line 563 "src/modules/misc.c"
f32 miscRandomFloatLcg(void) {
    u32 sample;
    D_misc_00404300 = (u32)D_misc_00404300 * 0x41C64E6Du + 0x3039u;
    sample = ((u32)D_misc_00404300 >> 16) & 0x7FFFu;
    return sample / D_misc_004042F8;
}
#line 569 "src/modules/misc.c"
#line 562 "src/modules/misc.c"
