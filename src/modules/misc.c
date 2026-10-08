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
#include "module.h"

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
void func_misc_00402730();
void func_misc_00402874();
void miscSetTextureAxisValue(s32 fileId, const char *selector, f32 value);
void func_misc_00402A5C();
void func_misc_00402BFC();
void func_misc_00402D48();
void miscVec3Interpolate(f32 *output, f32 *first, f32 *second, f32 fraction);
f32 func_misc_00402EFC(f32, f32, f32, f32);
void miscVec3ApproachNonlinearPreserveLength(Vec3F *target, Vec3F *current, f32 rate, f32 distanceCap);
void func_misc_00403110();
void *miscLoadFileModule(void);
void miscUnloadFileModule(void);
void func_misc_00403348();
void func_misc_00403650();
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
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/__entrypoint_func_misc_400000.s")

#line 135 "src/modules/misc.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_misc_00400390(void) {

}
#line 138 "src/modules/misc.c"

#line 96 "src/modules/misc.c"
/* Busy-wait on clock zero until the double-precision seconds deadline.
 * Preserve the original clock calls and float-to-double delay arithmetic. */
void miscBusyWaitSeconds(f32 delay) {
    f64 deadline;
    deadline = uvClkGetSec(0) + delay;
    while (uvClkGetSec(0) < deadline) {
    }
}
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
/* Convert a three-component vector to radius, azimuth and elevation by
 * forwarding its components to the original Cartesian conversion helper. */
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
/* Return sine divided by cosine, preserving the original two-call order. */
f32 miscTangent(f32 angle) {
    f32 cosine;
    f32 sine;
    sine = gUvMathExports->uvSinF(angle);
    cosine = gUvMathExports->uvCosF(angle);
    return sine / cosine;
}
#line 288 "src/modules/misc.c"


#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00400AD0.s")

extern f32 D_misc_00404234;

#line 294 "src/modules/misc.c"
/* Compute inverse cosine after the original [-1, 1] clamp, preserving the
 * special zero-input constant and the shared math library's angle units. */
f32 miscArcCosine(f32 cosine) {
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
/* Report +1 when masked bits change from none to some, -1 from some to none,
 * and zero otherwise. Changes between two nonzero masked values count as zero. */
s32 miscGetMaskedFlagTransition(s32 previous, s32 current, s32 mask) {
    if ((current & mask) && !(previous & mask)) {
        return 1;
    }
    if (!(current & mask) && (previous & mask)) {
        return -1;
    }
    return 0;
}
#line 404 "src/modules/misc.c"

/* RE_UNKNOWN: valid blend-weight/input domains, matrix/quaternion frame convention and partial-overlap guarantees; trace original export callers and matrix/quaternion producers before changing interpolation or alias handling. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_004012E4.s")

#line 408 "src/modules/misc.c"
/* Clamp to the upper bound first, then the lower bound. Preserve this order
 * even when a caller supplies inverted bounds or non-finite values. */
f32 miscClampFloat(f32 value, f32 upper, f32 lower) {
    if (upper < value) {
        return upper;
    }
    if (value < lower) {
        return lower;
    }
    return value;
}
#line 417 "src/modules/misc.c"

#line 414 "src/modules/misc.c"
/* Wrap a degree angle, then fold it into [-90, 90] without changing its sine.
 * Preserve the original comparisons and endpoint choices. */
f32 miscFoldAngleDegrees(f32 angle) {
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
/* Wrap a degree angle into [-180, 180], preserving both endpoints and the
 * original repeated-add/subtract behavior. */
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
#line 417 "src/modules/misc.c"

#line 418 "src/modules/misc.c"
/* Wrap radians into the original [-pi, pi] interval by repeated full turns.
 * Keep separate original float constants and their load order; no remainder
 * approximation or altered handling of non-finite inputs is introduced. */
extern f32 D_misc_00404260;
extern f32 D_misc_00404264;
extern f32 D_misc_00404268;
extern f32 D_misc_0040426C;

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

f32 miscFoldAngleRadians(f32 angle) {
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
f32 miscVec2LengthSquared(f32 *vector) { return vector[0]*vector[0] + vector[1]*vector[1]; }
#line 425 "src/modules/misc.c"

#line 426 "src/modules/misc.c"
/* Return the Euclidean length of a two-component vector. */
f32 miscVec2Length(f32 *vector) {
    return gUvMathExports->uvSqrtf(miscVec2LengthSquared(vector));
}
#line 427 "src/modules/misc.c"

#line 428 "src/modules/misc.c"
/* Normalize a two-component vector using its reciprocal length. Lengths
 * below the original threshold produce two zero components. Preserve the
 * ordered comparison and sequential stores, including aliased-pointer behavior. */
void miscVec2Normalize(f32 *output, f32 *input) {
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
void miscVec2AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta) {
    output[0] = base[0] + delta[0] * scale;
    output[1] = base[1] + delta[1] * scale;
}
#line 437 "src/modules/misc.c"

#line 438 "src/modules/misc.c"
/* Return the two-component dot product with the original floating-point order. */
f32 miscVec2Dot(f32 *first, f32 *second) {
    return first[0] * second[0] + first[1] * second[1];
}
#line 443 "src/modules/misc.c"

#line 444 "src/modules/misc.c"
/* Add two two-component vectors in X/Y order. */
void miscVec2Add(f32 *output, f32 *first, f32 *second) {
    output[0] = first[0] + second[0];
    output[1] = first[1] + second[1];
}
#line 449 "src/modules/misc.c"

#line 450 "src/modules/misc.c"
/* Subtract the second two-component vector from the first in X/Y order. */
void miscVec2Subtract(f32 *output, f32 *first, f32 *second) {
    output[0] = first[0] - second[0];
    output[1] = first[1] - second[1];
}
#line 454 "src/modules/misc.c"

#line 455 "src/modules/misc.c"
/* Scale a two-component vector, preserving the original load/store order. */
void miscVec2Scale(f32 *output, f32 scale, f32 *input) {
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
}
#line 459 "src/modules/misc.c"

#line 460 "src/modules/misc.c"
/* Transform the vector in place by the matrix's upper-left 2x2 block.
 * Preserve the original multiplication order and cache both input components. */
void miscVec2TransformInPlace(f32 *vector, f32 matrix[4][4]) {
    f32 x = vector[0];
    f32 y = vector[1];
    vector[0] = x * matrix[0][0] + matrix[1][0] * y;
    vector[1] = x * matrix[0][1] + matrix[1][1] * y;
}
#line 461 "src/modules/misc.c"

#line 462 "src/modules/misc.c"
/* Copy the X/Y components; retain the original behavior for aliased pointers. */
void miscVec2Copy(f32 *output, f32 *input) {
    output[0] = input[0];
    output[1] = input[1];
}
#line 466 "src/modules/misc.c"

#line 467 "src/modules/misc.c"
/* Subtract normal * dot(normal, input) * (1 + coefficient) from the input.
 * With a unit normal, coefficient one gives ordinary reflection and zero
 * removes the normal component. Preserve the original two-component scratch. */
void miscVec2ReflectScaled(f32 *output, f32 *normal, f32 *input, f32 coefficient) {
    f32 scaledNormal[2];
    miscVec2Scale(scaledNormal, miscVec2Dot(normal, input) * (1.0f + coefficient), normal);
    miscVec2Subtract(output, input, scaledNormal);
}
#line 468 "src/modules/misc.c"
/* RE_ORIGINAL_QUIRK: original overlapping vertical-segment path reads an unwritten intercept stack word. RE_UNKNOWN: caller reachability/input limits; trace original export callers before changing collinear behavior. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_004019FC.s")

#line 471 "src/modules/misc.c"
/* Add two three-component vectors in X/Y/Z order. */
void miscVec3Add(f32 *output, f32 *first, f32 *second) {
    output[0] = first[0] + second[0];
    output[1] = first[1] + second[1];
    output[2] = first[2] + second[2];
}
#line 476 "src/modules/misc.c"

#line 477 "src/modules/misc.c"
/* Subtract the second three-component vector from the first in X/Y/Z order. */
void miscVec3Subtract(f32 *output, f32 *first, f32 *second) {
    output[0] = first[0] - second[0];
    output[1] = first[1] - second[1];
    output[2] = first[2] - second[2];
}
#line 482 "src/modules/misc.c"

#line 483 "src/modules/misc.c"
/* Scale a three-component vector, preserving the original load/store order. */
void miscVec3Scale(f32 *output, f32 scale, f32 *input) {
    output[0] = input[0] * scale;
    output[1] = input[1] * scale;
    output[2] = input[2] * scale;
}
#line 488 "src/modules/misc.c"

#line 489 "src/modules/misc.c"
/* Transform three components in place using the upper-left matrix block.
 * Cache all input components and preserve the original multiplication/addition order. */
void miscVec3TransformInPlace(f32 *vector, f32 matrix[4][4]) {
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
void miscVec3Copy(f32 *output, f32 *input) {
    output[0] = input[0];
    output[1] = input[1];
    output[2] = input[2];
}
#line 496 "src/modules/misc.c"

#line 497 "src/modules/misc.c"
/* Add a scaled four-component delta to the base vector in component order.
 * The original sequential loads/stores also define aliased-pointer behavior. */
void miscVec4AddScaled(f32 *output, f32 *base, f32 scale, f32 *delta) {
    output[0] = base[0] + delta[0] * scale;
    output[1] = base[1] + delta[1] * scale;
    output[2] = base[2] + delta[2] * scale;
    output[3] = base[3] + delta[3] * scale;
}
#line 498 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00401FA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_0040213C.s")
/* RE_UNKNOWN: quaternion normalization/frame convention, cached-adjustment intent, shared flag reset/lifetime/reentrancy and overlap guarantees; trace original quaternion producers, flag writers and callers before changing the cache or transform. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_0040234C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402528.s")

#line 507 "src/modules/misc.c"
/* Extract three direction angles from the original matrix components.
 * The shared angle helper and math library determine the original angle units. */
void miscGetMatrixDirectionAngles(Mtx4F *matrix, f32 *first, f32 *second, f32 *third) {
    *first = func_misc_004016CC(-matrix->m[1][0], matrix->m[1][1]);
    *second = func_misc_004016CC(matrix->m[1][2], gUvMathExports->uvSqrtf(matrix->m[1][0] * matrix->m[1][0] + matrix->m[1][1] * matrix->m[1][1]));
    *third = func_misc_004016CC(-matrix->m[0][2], matrix->m[2][2]);
}
#line 508 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402730.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402874.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402BFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402D48.s")

#line 521 "src/modules/misc.c"
/* Interpolate three components with the original complement, product and sum
 * order. The fraction is not clamped; callers may intentionally extrapolate. */
void miscVec3Interpolate(f32 *output, f32 *first, f32 *second, f32 fraction) {
    f32 complement = 1.0f - fraction;
    output[0] = fraction * second[0] + first[0] * complement;
    output[1] = fraction * second[1] + first[1] * complement;
    output[2] = fraction * second[2] + first[2] * complement;
}
#line 522 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00402EFC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403110.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403348.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403650.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403748.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403A5C.s")

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
/* Evaluate the original clamped arccosine helper on the vector dot product
 * and discard its result, preserving the existing void return and both calls.
 * RE_UNKNOWN: intended input lengths, whether callers normalize these vectors,
 * and why this wrapper discards the result. This body does not establish a
 * unit-vector precondition. Inspect original callers and both math targets
 * before interpreting the result as an angle or removing the calls. */
#line 553 "src/modules/misc.c"
void miscEvaluateVectorAngleDiscardResult(Vec3F *first, Vec3F *second) {
    miscArcCosine(gUvFvecExports->uvVec3FDot(first, second));
}
#line 552 "src/modules/misc.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403D8C.s")

#line 557 "src/modules/misc.c"
/* Set the complete 32-bit seed used by the shared linear congruential generator. */
void miscSeedRandomLcg(s32 seed) {
    D_misc_00404300 = seed;
}
#line 560 "src/modules/misc.c"

#line 561 "src/modules/misc.c"
/* Advance the original 32-bit linear congruential generator, select its upper
 * 15 bits and divide by the original float scale. Keep unsigned wrap/conversion. */
f32 miscRandomFloatLcg(void) {
    u32 sample;
    D_misc_00404300 = (u32)D_misc_00404300 * 0x41C64E6Du + 0x3039u;
    sample = ((u32)D_misc_00404300 >> 16) & 0x7FFFu;
    return sample / D_misc_004042F8;
}
#line 562 "src/modules/misc.c"
