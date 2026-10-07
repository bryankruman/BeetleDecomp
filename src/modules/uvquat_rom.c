// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvquat_rom_400000(UvQuat_Exports *exports);
void uvQuatModuleCleanup(void);
void uvQuatFromRotationMatrix(Quat *arg0, Mtx4F *arg1);
void uvQuatFromEuler(Quat *arg0, f32 arg1, f32 arg2, f32 arg3);
void uvQuatToAdjustedRotationMatrix(Mtx4F *arg0, Quat *arg1);
void uvQuatComputeAngularDerivative(Quat *arg0, Quat *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void uvQuatMultiply(Quat *arg0, Quat *arg1, Quat *arg2);
void uvQuatCopy(Quat *arg0, Quat *arg1);
void uvQuatCopy(Quat *arg0, Quat *arg1);
void uvQuatBlendNormalized(Quat *arg0, Quat *arg1, Quat *arg2, f32 arg3);

// .bss
extern UvMath_Exports *D_uvquat_rom_00400B50;
extern UvFMtx_Rom_Exports *D_uvquat_rom_00400B54;
extern Mtx4F D_uvquat_rom_00400B58;

void __entrypoint_func_uvquat_rom_400000(UvQuat_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvQuatModuleCleanup = uvQuatModuleCleanup;
    exports->uvQuatFromRotationMatrix = uvQuatFromRotationMatrix;
    exports->uvQuatFromEuler = uvQuatFromEuler;
    exports->uvQuatToAdjustedRotationMatrix = uvQuatToAdjustedRotationMatrix;
    exports->uvQuatComputeAngularDerivative = uvQuatComputeAngularDerivative;
    exports->uvQuatMultiply = uvQuatMultiply;
    exports->uvQuatCopy = uvQuatCopy;
    exports->uvQuatBlendNormalized = uvQuatBlendNormalized;
#line 1
    D_uvquat_rom_00400B50 = uvLoadModule('MATH');
    D_uvquat_rom_00400B54 = uvLoadModule('FMTX');
}

void uvQuatModuleCleanup(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('FMTX');
}

#line 10 "src/modules/uvquat_rom.c"
/* Convert the 3x3 rotation block to a quaternion using the trace path
 * or largest diagonal component. Preserve original signs, addition order
 * and caller-owned rotation-matrix validity. */
void uvQuatFromRotationMatrix(Quat* quat, Mtx4F* matrix) {
    f32 trace;
    f32 firstTwoDiagonal;
    f32 root;
    f32 inverseTwiceRoot;
    s32 largestDiagonal;

    firstTwoDiagonal = matrix->m[1][1] + matrix->m[0][0];
    trace = matrix->m[2][2] + firstTwoDiagonal;
    if (trace >= 0.0f) {
        root = D_uvquat_rom_00400B50->uvSqrtf(trace + 1.0f);
        inverseTwiceRoot = 0.5f / root;
        quat->w = root * 0.5f;
        quat->x = (matrix->m[2][1] - matrix->m[1][2]) * inverseTwiceRoot;
        quat->y = (matrix->m[0][2] - matrix->m[2][0]) * inverseTwiceRoot;
        quat->z = (matrix->m[1][0] - matrix->m[0][1]) * inverseTwiceRoot;
        return;
    }
    largestDiagonal = 0;
    if (matrix->m[0][0] < matrix->m[1][1]) {
        largestDiagonal = 1;
    }
    if (matrix->m[largestDiagonal][largestDiagonal] < matrix->m[2][2]) {
        largestDiagonal = 2;
    }

    switch (largestDiagonal) {                               /* irregular */
    case 0:
        root = D_uvquat_rom_00400B50->uvSqrtf((matrix->m[0][0] - (matrix->m[1][1] + matrix->m[2][2])) + 1.0f);
        inverseTwiceRoot = 0.5f / root;
        quat->x = root * 0.5f;
        quat->y = (matrix->m[0][1] + matrix->m[1][0]) * inverseTwiceRoot;
        quat->z = (matrix->m[2][0] + matrix->m[0][2]) * inverseTwiceRoot;
        quat->w = (matrix->m[2][1] - matrix->m[1][2]) * inverseTwiceRoot;
        break;
    case 1:
        root = D_uvquat_rom_00400B50->uvSqrtf((matrix->m[1][1] - (matrix->m[2][2] + matrix->m[0][0])) + 1.0f);
        inverseTwiceRoot = 0.5f / root;
        quat->y = root * 0.5f;
        quat->z = (matrix->m[1][2] + matrix->m[2][1]) * inverseTwiceRoot;
        quat->x = (matrix->m[0][1] + matrix->m[1][0]) * inverseTwiceRoot;
        quat->w = (matrix->m[0][2] - matrix->m[2][0]) * inverseTwiceRoot;
        break;
    case 2:
        root = D_uvquat_rom_00400B50->uvSqrtf((matrix->m[2][2] - firstTwoDiagonal) + 1.0f);
        inverseTwiceRoot = 0.5f / root;
        quat->z = root * 0.5f;
        quat->x = (matrix->m[2][0] + matrix->m[0][2]) * inverseTwiceRoot;
        quat->y = (matrix->m[1][2] + matrix->m[2][1]) * inverseTwiceRoot;
        quat->w = (matrix->m[1][0] - matrix->m[0][1]) * inverseTwiceRoot;
        break;
    }
}
#line 63 "src/modules/uvquat_rom.c"

void uvQuatFromEuler(Quat *quat, f32 x, f32 y, f32 z) {
    f32 temp_ft4;
    f32 sp58;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 sp4C;
    f32 sp48;
    f32 temp_fs1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 pad;
    f32 temp_fa0;

    temp_fs0 = (x + 1.5707963f) * 0.5f;
    temp_fs1 = D_uvquat_rom_00400B50->uvSinF(temp_fs0);
    temp_fs0 = D_uvquat_rom_00400B50->uvCosF(temp_fs0);
    temp_fa0 = -y * 0.5f;
    sp4C = D_uvquat_rom_00400B50->uvSinF(temp_fa0);
    sp58 = D_uvquat_rom_00400B50->uvCosF(temp_fa0);

    sp48 = D_uvquat_rom_00400B50->uvSinF(((z - 3.1415927f) * 0.5f));
    temp_fv0 = D_uvquat_rom_00400B50->uvCosF(((z - 3.1415927f) * 0.5f));
    temp_fv1 = sp4C * sp48;
    temp_fa0 = sp4C * temp_fv0;
    temp_fa1 = sp58 * temp_fv0;
    temp_ft4 = sp58 * sp48;

    quat->x = (temp_fs0 * temp_fa1) + (temp_fs1 * temp_fv1);
    quat->y = (temp_fs0 * temp_ft4) - (temp_fs1 * temp_fa0);
    quat->z = (temp_fs0 * temp_fa0) + (temp_fs1 * temp_ft4);
    quat->w = (-temp_fs0 * temp_fv1) + (temp_fs1 * temp_fa1);
}

#line 97 "src/modules/uvquat_rom.c"
/* Build the original homogeneous quaternion matrix and postmultiply
 * by the cached coordinate adjustment. Initialize that adjustment once;
 * preserve the original component convention and operation order. */
void uvQuatToAdjustedRotationMatrix(Mtx4F *matrix, Quat *quat) {
    f32 xx;
    f32 yy;
    f32 zz;
    f32 ww;
    f32 wx;
    f32 yx;
    f32 zy;
    f32 wy;
    f32 zx;
    f32 wz;
    static s32 firstTime = FALSE;

    if (!firstTime) {
        firstTime = TRUE;
        D_uvquat_rom_00400B54->func_uvfmtx_rom_00402B30(&D_uvquat_rom_00400B58, -1.5707964f, 0.0f, 3.1415927f);
    }

    xx = SQ(quat->x);
    yy = SQ(quat->y);
    zz = SQ(quat->z);
    ww = SQ(quat->w);
    yx = quat->y * quat->x;
    zx = quat->z * quat->x;
    wx = quat->w * quat->x;
    zy = quat->z * quat->y;
    wy = quat->w * quat->y;
    wz = quat->w * quat->z;

    matrix->m[0][0] = ((xx + yy) - zz) - ww;
    matrix->m[0][1] = 2.0f * (zy + wx);
    matrix->m[0][2] = 2.0f * (wy - zx);
    matrix->m[0][3] = 0.0f;
    matrix->m[1][0] = 2.0f * (zy - wx);
    matrix->m[1][1] = ((xx - yy) + zz) - ww;
    matrix->m[1][2] = 2.0f * (wz + yx);
    matrix->m[1][3] = 0.0f;
    matrix->m[2][0] = 2.0f * (zx + wy);
    matrix->m[2][1] = 2.0f * (wz - yx);
    matrix->m[2][2] = ((xx - yy) - zz) + ww;
    matrix->m[2][3] = 0.0f;
    matrix->m[3][0] = 0.0f;
    matrix->m[3][1] = 0.0f;
    matrix->m[3][2] = 0.0f;
    matrix->m[3][3] = 1.0f;
    D_uvquat_rom_00400B54->uvMat4Mul(matrix, matrix, &D_uvquat_rom_00400B58);
}
#line 144 "src/modules/uvquat_rom.c"

static s32 unused[] = { 0x00200000, &__entrypoint_func_uvquat_rom_400000, 0 };

#line 147 "src/modules/uvquat_rom.c"
/* Compute the original quaternion angular derivative plus its norm
 * correction scaled by 0.99/interval. The caller supplies a nonzero interval;
 * this routine does not normalize or integrate the quaternion itself. */
void uvQuatComputeAngularDerivative(Quat *output, Quat *input, f32 angularX, f32 angularY, f32 angularZ, f32 interval) {
    f32 normCorrection;

    normCorrection = (1.0f - (SQ(input->w) + (SQ(input->x) + SQ(input->y) + SQ(input->z)))) * (0.99f / interval);
    output->x = (input->x * normCorrection) + (-0.5f * ((input->y * angularZ) + (input->z * angularY) + (input->w * angularX)));
    output->y =
        (input->y * normCorrection) + (0.5f * (((input->x * angularZ) - (input->w * angularY)) + (input->z * angularX)));
    output->z =
        (input->z * normCorrection) + (0.5f * (((input->w * angularZ) + (input->x * angularY)) - (input->y * angularX)));
    output->w = (input->w * normCorrection) + (0.5f * ((-input->z * angularZ) + (input->y * angularY) + (input->x * angularX)));
}
#line 158 "src/modules/uvquat_rom.c"

void uvQuatMultiply(Quat *dest, Quat *q1, Quat *q2) {
    Quat quat;

    quat.x = ((q1->w * q2->x) + (q1->x * q2->w) + (q1->y * q2->z)) - (q2->y * q1->z);
    quat.y = ((q1->w * q2->y) + (q1->y * q2->w) + (q1->z * q2->x)) - (q2->z * q1->x);
    quat.z = ((q1->w * q2->z) + (q1->z * q2->w) + (q1->x * q2->y)) - (q2->x * q1->y);
    quat.w = (((q1->w * q2->w) - (q1->x * q2->x)) - (q1->y * q2->y)) - (q2->x * q1->z);
    uvQuatCopy(dest, &quat);
}

void uvQuatCopy(Quat *q1, Quat *q2) {
    q1->x = q2->x;
    q1->y = q2->y;
    q1->z = q2->z;
    q1->w = q2->w;
}

#line 176 "src/modules/uvquat_rom.c"
/* Blend along the quaternion hemisphere chosen by the dot-product
 * sign, then normalize unless the result has zero length. Preserve the
 * original unclamped weight and floating-point operation order. */
void uvQuatBlendNormalized(Quat *output, Quat *first, Quat *second, f32 weight) {
    f32 lengthOrFirstWeight;
    f32 dot;

    dot = ((second->w * first->w) + ((first->x * second->x) + (first->y * second->y) + (first->z * second->z)));
    lengthOrFirstWeight = (1.0f - weight);
    if (dot < 0) {
        weight = -weight;
    }

    output->x = (f32) ((second->x * weight) + (first->x * lengthOrFirstWeight));
    output->y = (f32) ((second->y * weight) + (first->y * lengthOrFirstWeight));
    output->z = (f32) ((second->z * weight) + (first->z * lengthOrFirstWeight));
    output->w = (f32) ((second->w * weight) + (first->w * lengthOrFirstWeight));

    lengthOrFirstWeight = D_uvquat_rom_00400B50->uvSqrtf(SQ(output->w) + (SQ(output->x) + SQ(output->y) + SQ(output->z)));
    if (lengthOrFirstWeight == 0.0f) {
        return;
    }

    output->x /= lengthOrFirstWeight;
    output->y /= lengthOrFirstWeight;
    output->z /= lengthOrFirstWeight;
    output->w /= lengthOrFirstWeight;
}
#line 201 "src/modules/uvquat_rom.c"
