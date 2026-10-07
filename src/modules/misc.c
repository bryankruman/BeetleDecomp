// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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
void func_misc_004029DC();
void func_misc_00402A5C();
void func_misc_00402BFC();
void func_misc_00402D48();
void miscVec3Interpolate(f32 *output, f32 *first, f32 *second, f32 fraction);
void func_misc_00402EFC();
void func_misc_00403000();
void func_misc_00403110();
void func_misc_00403300();
void func_misc_00403324();
void func_misc_00403348();
void func_misc_00403650();
void func_misc_00403748();
void func_misc_004038D8();
void func_misc_00403A5C();
void func_misc_00403BEC();
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


void func_misc_0040070C(Vec3F *arg0, UnkStruct_misc_004006A0 *arg1);
void func_misc_004008B4(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5);
void func_misc_004009B0(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5);
void func_misc_00400CA8(Mtx4F *mtx, f32 arg1, f32 arg2, f32 arg3);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/__entrypoint_func_misc_400000.s")

void func_misc_00400390(void) {

}

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
f32 func_misc_00400400(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_ft4;
    f32 var_fa1;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;

    if (arg1 < arg0) {
        var_fv0 = arg0 - arg1;
        var_fv1 = var_fv0;
    } else {
        var_fv0 = arg0 - arg1;
        var_fv1 = -var_fv0;
    }
    if (var_fv1 < D_misc_00404220) {
        return arg0;
    }
    temp_ft4 = arg2 * var_fv0 * D_80025D70;
    if (var_fv0 > 0.0f) {
        var_ft5 = var_fv0;
    } else {
        var_ft5 = -var_fv0;
    }
    if (temp_ft4 > 0.0f) {
        var_fv1 = temp_ft4;
    } else {
        var_fv1 = -temp_ft4;
    }
    if (var_ft5 < var_fv1) {
        arg1 = arg0;
    } else {
        arg1 = arg1 + temp_ft4;
    }
    return arg1;
}

// .rodata
extern f32 D_misc_00404224;
f32 func_misc_004004B8(f32 arg0, f32 arg1, f32 arg2) {
    f32 var_fa1;
    f32 var_ft4;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fv1_2;

    if (arg1 < arg0) {
        var_fv0 = arg0 - arg1;
        var_fv1 = var_fv0;
    } else {
        var_fv0 = arg0 - arg1;
        var_fv1 = -var_fv0;
    }
    if (var_fv1 < D_misc_00404224) {
        return arg0;
    }
    if (var_fv0 > 0) {
        var_ft4 = arg2 * D_80025D70;
    } else {
        var_ft4 = -arg2 * D_80025D70;
    }
    if (var_fv0 > 0.0f) {
        var_ft5 = var_fv0;
    } else {
        var_ft5 = -var_fv0;
    }
    if (var_ft4 > 0.0f) {
        var_fv1 = var_ft4;
    } else {
        var_fv1 = -var_ft4;
    }
    if (var_ft5 < var_fv1) {
        arg1 = arg0;
    } else {
        arg1 = arg1 + var_ft4;
    }
    return arg1;
}

void func_misc_004005A0(Vec3F* arg0, Vec3F* arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;

    temp_fv0 = gUvFvecExports->uvVec3FLen(arg1);
    if (temp_fv0 == 0.0f) {
        return;
    }

    arg1->x = func_misc_00400400(arg0->x, arg1->x, arg2);
    arg1->y = func_misc_00400400(arg0->y, arg1->y, arg2);
    arg1->z = func_misc_00400400(arg0->z, arg1->z, arg2);

    temp_fv0_2 = gUvFvecExports->uvVec3FLen(arg1);
    if (temp_fv0_2 == 0.0f) {
        return;
    }

    temp_fv1 = temp_fv0 / temp_fv0_2;
    arg1->x *= temp_fv1;
    arg1->y *= temp_fv1;
    arg1->z *= temp_fv1;
}


void func_misc_004006A0(UnkStruct_misc_004006A0* arg0, UnkStruct_misc_004006A0* arg1, f32 arg2) {
    arg1->unk30 = func_misc_00400400(arg0->unk30, arg1->unk30, arg2);
    arg1->unk34 = func_misc_00400400(arg0->unk34, arg1->unk34, arg2);
    arg1->unk38 = func_misc_00400400(arg0->unk38, arg1->unk38, arg2);
}

void func_misc_0040070C(Vec3F* arg0, UnkStruct_misc_004006A0* arg1) {
    Vec3F sp3C;
    Vec3F sp30;
    Vec3F sp24;

    gUvFvecExports->uvVec3FNormalize(arg0, arg0);
    gUvFvecExports->uvVec3FCopy(&sp3C, arg0);
    sp30.x = arg1->unk0;
    sp30.y = arg1->unk4;
    sp30.z = arg1->unk8;
    gUvFvecExports->uvVec3FCross(&sp24, &sp3C, (Vec3F* ) &sp30);
    gUvFvecExports->uvVec3FNormalize(&sp24, &sp24);
    gUvFvecExports->uvVec3FCross((Vec3F* ) &sp30, &sp24, &sp3C);
    gUvFvecExports->uvVec3FNormalize((Vec3F* ) &sp30, (Vec3F* ) &sp30);
    arg1->unk0 = sp30.x;
    arg1->unk4 = sp30.y;
    arg1->unk8 = sp30.z;
    arg1->unk10 = sp24.x;
    arg1->unk14 = sp24.y;
    arg1->unk18 = sp24.z;
    arg1->unk20 = sp3C.x;
    arg1->unk24 = sp3C.y;
    arg1->unk28 = sp3C.z;
    arg1->unkC = 0.0f;
    arg1->unk1C = 0.0f;
    arg1->unk2C = 0.0f;
}

void func_misc_00400844(Vec3F arg0, f32* arg3, f32* arg4, f32* arg5) {
    func_misc_004008B4(arg0.x, arg0.y, arg0.z, arg3, arg4, arg5);
}

void func_misc_00400884(f32 arg0, f32 arg1, f32 arg2, f32* arg3) {
    func_misc_004009B0(arg0, arg1, arg2, arg3, arg3 + 1, arg3 + 2);
}

void func_misc_004008B4(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 sp1C;
    f32 temp_fa0;
    s32 pad;
    f32 sp20;

    sp20 = gUvMathExports->uvSqrtf(SQ(arg0) + SQ(arg1));
    *arg3 = gUvMathExports->uvSqrtf(SQ(arg0) + SQ(arg1) + SQ(arg2));
    if (*arg3 == 0.0f) {
        *arg4 = 0.0f;
        *arg5 = 0.0f;
        return;
    }
    *arg4 = gUvMathExports->uvAtan2F(arg1 / *arg3, arg0 / *arg3);
    *arg5 = gUvMathExports->uvAtan2F(arg2 / *arg3, sp20 / *arg3);
}

void func_misc_004009B0(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 cosf;

    cosf =  gUvMathExports->uvCosF(arg2);
    *arg3 = gUvMathExports->uvCosF(arg1) * (arg0 * cosf);
    *arg4 = gUvMathExports->uvSinF(arg1) * (arg0 * cosf);
    *arg5 = gUvMathExports->uvSinF(arg2) * arg0;
}

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
void func_misc_00400CA8(Mtx4F* mtx, f32 x, f32 y, f32 z) {
    f32 temp_fs0;
    f32 temp_fs1;
    Vec3F sp34;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;

    temp_fs0 = gUvMathExports->uvSinF(z);
    temp_fs1 = gUvMathExports->uvCosF(z);
    sp34.z = gUvMathExports->uvSinF(y);
    sp34.y = gUvMathExports->uvCosF(y);
    sp34.x = gUvMathExports->uvSinF(x);
    temp_fv0 = gUvMathExports->uvCosF(x);
    temp_ft4 = sp34.z * sp34.x;
    mtx->m[0][0] = (temp_fs1 * temp_fv0) - (temp_fs0 * temp_ft4);
    temp_ft5 = sp34.z * temp_fv0;
    mtx->m[0][1] = (temp_fs1 * sp34.x) + (temp_fs0 * temp_ft5);
    mtx->m[0][3] = 0.0f;
    mtx->m[0][2] = -temp_fs0 * sp34.y;
    mtx->m[1][0] = -sp34.y * sp34.x;
    mtx->m[1][1] = sp34.y * temp_fv0;
    mtx->m[1][2] = sp34.z;
    mtx->m[2][0] = (temp_fs0 * temp_fv0) + (temp_fs1 * temp_ft4);
    mtx->m[2][1] = (temp_fs0 * sp34.x) - (temp_fs1 * temp_ft5);
    mtx->m[2][2] = temp_fs1 * sp34.y;
    mtx->m[3][3] = 1.0f;
    mtx->m[1][3] = 0.0f;
    mtx->m[2][3] = 0.0f;
    mtx->m[3][0] = 0.0f;
    mtx->m[3][1] = 0.0f;
    mtx->m[3][2] = 0.0f;
}

extern f32 D_misc_00404238;
extern f32 D_misc_0040423C;
extern f32 D_misc_00404240;

void func_misc_00400E38(UnkStruct_misc_004006A0* arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6) {
    f32 len;
    f32 var_fv1;
    f32 sp2C;

    sp2C = arg0->unk18;
    len = gUvMathExports->uvSqrtf(SQ(arg0->unk14) + SQ(arg0->unk10));
    if (ABS_2(len) < D_misc_00404238) {
        if (sp2C < 0.0f) {
            *arg5 = D_misc_0040423C;
        } else {
            *arg5 = D_misc_00404240;
        }
        *arg4 = 0.0f;
        *arg6 = 0.0f;
    } else {
        f32 fa2;
        f32 fa1;

        *arg5 = gUvMathExports->uvAtan2F(sp2C, len);
        fa2 = arg0->unk14 / len;
        fa1 = -arg0->unk10 / len;
        *arg4 = gUvMathExports->uvAtan2F(fa1, fa2);
        fa2 = arg0->unk28 / len;
        fa1 = -arg0->unk8 / len;
        *arg6 = gUvMathExports->uvAtan2F(fa1, fa2);
    }
    *arg1 = arg0->unk30;
    *arg2 = arg0->unk34;
    *arg3 = arg0->unk38;
}

void func_misc_00400FB8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F* arg6) {
    gUvFmtxExports->uvMat4SetIdentity(arg6);
    gUvFmtxExports->uvMat4RotateAxis(arg6, arg3, 0x7A);
    gUvFmtxExports->uvMat4RotateAxis(arg6, arg4, 0x78);
    gUvFmtxExports->uvMat4RotateAxis(arg6, arg5, 0x79);
    arg6->m[3][0] = arg0;
    arg6->m[3][1] = arg1;
    arg6->m[3][2] = arg2;
}

void func_misc_00401078(void) {
    *(s32*)0 = 0;
}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_004029DC.s")

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403110.s")

void func_misc_00403300(void) {
    uvLoadModule('filr');
}

void func_misc_00403324(void) {
    uvUnloadModule('filr');
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403348.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403650.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403748.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_004038D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403A5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/misc/func_misc_00403BEC.s")

void func_misc_00403CA4(Vec3F *arg0, Vec3F *arg1) {
f32 miscArcCosine(f32 cosine);
}

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
