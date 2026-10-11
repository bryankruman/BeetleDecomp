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

/* Publish the eight quaternion operations, then load MATH followed by FMTX
 * and save both provider pointers. This body resets no quaternion records.
 * RE_UNKNOWN: repeated initialization, load failure and provider/reference lifetime
 * remain unproved. Preserve the existing publication/load order and #line. */
#line 21 "src/modules/uvquat_rom.c"
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
#line 4 "src/modules/uvquat_rom.c"

/* Unload MATH followed by FMTX, without clearing either stored export pointer.
 * RE_UNKNOWN: reference counts, outstanding calls and repeated cleanup behavior
 * belong to the module loader/callers; no guard or pointer reset is added. */
#line 5 "src/modules/uvquat_rom.c"
void uvQuatModuleCleanup(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('FMTX');
}
#line 9 "src/modules/uvquat_rom.c"

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

#line 64 "src/modules/uvquat_rom.c"

void uvQuatFromEuler(Quat *quat, f32 x, f32 y, f32 z) {
    f32 cosYTimesSinZ;
    f32 cosAdjustedY;
    f32 cosYTimesCosZ;
    f32 xTerm; /* Adjusted x half-angle, then its cosine. */
    f32 sinAdjustedY;
    f32 sinAdjustedZ;
    f32 sinAdjustedX;
    f32 cosAdjustedZ;
    f32 sinYTimesSinZ;
    f32 pad;
    f32 yTerm; /* Negative y half-angle, then sinAdjustedY*cosAdjustedZ. */

    xTerm = (x + 1.5707963f) * 0.5f;
    sinAdjustedX = D_uvquat_rom_00400B50->uvSinF(xTerm);
    xTerm = D_uvquat_rom_00400B50->uvCosF(xTerm);
    yTerm = -y * 0.5f;
    sinAdjustedY = D_uvquat_rom_00400B50->uvSinF(yTerm);
    cosAdjustedY = D_uvquat_rom_00400B50->uvCosF(yTerm);

    sinAdjustedZ = D_uvquat_rom_00400B50->uvSinF(((z - 3.1415927f) * 0.5f));
    cosAdjustedZ = D_uvquat_rom_00400B50->uvCosF(((z - 3.1415927f) * 0.5f));
    sinYTimesSinZ = sinAdjustedY * sinAdjustedZ;
    yTerm = sinAdjustedY * cosAdjustedZ;
    cosYTimesCosZ = cosAdjustedY * cosAdjustedZ;
    cosYTimesSinZ = cosAdjustedY * sinAdjustedZ;

    quat->x = (xTerm * cosYTimesCosZ) + (sinAdjustedX * sinYTimesSinZ);
    quat->y = (xTerm * cosYTimesSinZ) - (sinAdjustedX * yTerm);
    quat->z = (xTerm * yTerm) + (sinAdjustedX * cosYTimesSinZ);
    quat->w = (-xTerm * sinYTimesSinZ) + (sinAdjustedX * cosYTimesCosZ);
}
#line 96 "src/modules/uvquat_rom.c"

#line 97 "src/modules/uvquat_rom.c"
#line 97 "src/modules/uvquat_rom.c"

/* Build the original homogeneous quaternion matrix and postmultiply by
 * the cached matrix, initialized once with angles -1.5707964f,0,3.1415927f.
 * Preserve the original component convention and operation order.
 * RE_UNKNOWN: the source/destination frames and physical purpose of this
 * fixed rotation. Trace original QUAT export0x0C callers and matrix consumers
 * before assigning an axis-conversion convention. */
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
        D_uvquat_rom_00400B54->uvMat4SetRotationFromThreeAngles(&D_uvquat_rom_00400B58, -1.5707964f, 0.0f, 3.1415927f);
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
#line 147 "src/modules/uvquat_rom.c"
#line 144 "src/modules/uvquat_rom.c"

static s32 unused[] = { 0x00200000, &__entrypoint_func_uvquat_rom_400000, 0 };

#line 147 "src/modules/uvquat_rom.c"
#line 147 "src/modules/uvquat_rom.c"

/* Compute the original quaternion angular derivative plus its norm
 * correction scaled by 0.99/interval. This routine does not normalize or
 * integrate the quaternion itself.
 * RE_UNKNOWN: whether callers guarantee a nonzero interval. The original
 * division has no zero guard; trace original export-slot callers before
 * treating that input requirement as a proven caller guarantee. */
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
#line 161 "src/modules/uvquat_rom.c"
#line 158 "src/modules/uvquat_rom.c"

void uvQuatMultiply(Quat *output, Quat *first, Quat *second) {
    Quat product; /* Compute all four components locally before copying. RE_UNKNOWN: component conventions, normalization and valid input domains need original assets and export 0x14 callers. */

    product.x = ((first->w * second->x) + (first->x * second->w) + (first->y * second->z)) - (second->y * first->z);
    product.y = ((first->w * second->y) + (first->y * second->w) + (first->z * second->x)) - (second->z * first->x);
    product.z = ((first->w * second->z) + (first->z * second->w) + (first->x * second->y)) - (second->x * first->y);
    product.w = (((first->w * second->w) - (first->x * second->x)) - (first->y * second->y)) - (second->x * first->z); /* RE_ORIGINAL_QUIRK: native scalar term subtracts second.x * first.z; RE_UNKNOWN: its intended formula needs historical sources and original producers/callers. Preserve it. */
    uvQuatCopy(output, &product); /* RE_UNKNOWN: output storage extent, lifetime and permitted aliases need original allocation and caller contracts. */
}

void uvQuatCopy(Quat *destination, Quat *source) { /* Preserve interleaved component loads/stores. RE_UNKNOWN: partial-overlap rules, storage extents/lifetimes and historical declarations need original allocators and export 0x18 callers. */
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
    destination->w = source->w;
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
