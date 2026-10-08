// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"




void uvMat4ApplySharedInverseTranslation(Mtx4F *m1, Mtx4F *m2);
void uvUnloadModule(s32 tag); /* extern */
void uvFmtxModuleCleanup(void);
void uvFmtxSetSharedAxes(f32 arg0, f32 arg1, f32 arg2);
void uvMat4ApplySharedInverseTranslation(Mtx4F *dst, Mtx4F *m2);
void uvMat4ApplySharedInverseTranslation(Mtx4F *m1, Mtx4F *m2);
void uvMat4FCopy(Mtx4F *dst, Mtx4F *src);
void uvMat4FCopy(Mtx4F *dst, Mtx4F *src);
void uvMat4CopyLinear3x3(Mtx4F *dst, Mtx4F *src);
void uvMat4CopyLinear3x3(Mtx4F *dst, Mtx4F *src);
void uvMat4CopyL2F(Mtx4F *dst, Mtx src);
void uvMat4CopyF2L(Mtx *dst, Mtx4F *src);
void uvMat4SetIdentity(Mtx4F *dst);
void uvMat4SetIdentity(Mtx4F *m);
void uvMat4Mul(Mtx4F *dst, Mtx4F *src2, Mtx4F *src1);
void func_uvfmtx_rom_00400FF8(s32 arg0);
void uvMat4RotateAxis(Mtx4F *dst, float angle, char axis);
void uvMat4LocalTranslate(Mtx4F *m, f32 arg1, f32 arg2, f32 arg3);
void uvMat4Scale(Mtx4F *m, f32 arg1, f32 arg2, f32 arg3);

void uvMat4ComposeScaleRotateTranslate(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              u8 arg7, u8 arg8, u8 arg9, f32 arg10, f32 arg11, f32 arg12);
void uvMat4InvertTranslationRotation(Mtx4F *dst, Mtx4F *mat2);
s32 uvMat4InvertAffineByCofactors(Mtx4F *arg0, Mtx4F *arg1);
void uvMat4TransposeLinear3x3PreservingRest(Mtx4F *arg0, Mtx4F *arg1);
void uvMat4CopyWithReciprocalAndLinearScale(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void uvMat4CopyWithReciprocalAndLinearScale(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void uvMat4TransformPoint(Mtx4F *src, Vec3F *dst, Vec3F *vec2);
void uvMat4BuildFacingBasisBetweenTransforms(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void uvMat4BuildFacingBasisBetweenTransforms(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void func_uvfmtx_rom_00401F74(Mtx4F *dst, float left, float right, float top, float bottom, float near,
                              float far);
void uvMat4BuildOrthographicProjection(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void uvMat4SetOrtho(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvMat4BuildLookAtFromCoordinates(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7, f32 arg8, f32 arg9);
void uvMat4SetNormalizedQuaternionRotation(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvMat4SetNormalizedAxisRotationFromSinCos(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void uvGfxMtxViewLoad(Mtx4F *mtxF, u16 params);
void uvMat4PushFloatMatrix(Mtx4F *mtxF);
void uvGfxMtxFViewPop(void);
void uvGfxMtxProjPushF(Mtx4F *mtxF);
void uvGfxMtxCopySharedFloatMatrix(Mtx4F *arg0);
void uvGfxMtxLoadProjectionWithQuarterTurn(Mtx4F *arg0);
void uvMat4SetRotationFromThreeAngles(Mtx4F *mP, f32 arg1, f32 arg2, f32 arg3);
void uvMat4SetTranslation(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3);
void uvFmtxCopyVector(Vec3F *arg0, Vec3F *arg1);
void uvFmtxCopyNegatedVector(Vec3F *arg0, Vec3F *arg1);
void uvMat4GetYAxis(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetNegatedYAxis(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetZAxis(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetNegatedZAxis(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetYAxisAlias(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetTranslation(Vec3F *arg0, Mtx4F *arg1);
void uvMat4GetDirectionAngles(Mtx4F *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void uvMat4GetTranslationAndDirectionAngles(Mtx4F *arg0, Vec3F *arg1, Vec3F *arg2);
void uvMat4TransformDirection(Mtx4F *arg0, Vec3F *arg1, Vec3F *arg2);
f32 uvMat4TransformPointAndW(Mtx4F *arg0, Vec3F *arg1, Vec3F *arg2);
void uvMat4TransformXY(Mtx4F *arg0, Vec3F *arg1, Vec3F *arg2);
void uvMat4MultiplyLinear3x3(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void uvMat4ApplyQuaternionRotationAboutPivot(Mtx4F *arg0, Vec3F *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void uvMat4ApplyAxisRotationAboutPivot(Mtx4F *arg0, Vec3F *arg1, Mtx4F *arg2, f32 arg3, f32 arg4);
void uvFmtxCopyAlternateSharedMatrix(Mtx4F *arg0);
void __entrypoint_func_uvfmtx_rom_400000(UvFMtx_Rom_Exports* exports);

// .data
s32 D_uvfmtx_rom_00403670[] = {0x00CC0000, __entrypoint_func_uvfmtx_rom_400000, 0, 0};

// .bss
static UvMath_Exports *sUvMathExports;
static UvFVec_Rom_Exports *sUvFvecExports;
static UvImtx_Rom_Exports *sUvImtxExports;
Mtx4F D_uvfmtx_rom_00403690;
Mtx4F D_uvfmtx_rom_004036D0;
Mtx4F D_uvfmtx_rom_00403710;
static f32 sXAxis;
static f32 sYAxis;
static f32 sZAxis;

void __entrypoint_func_uvfmtx_rom_400000(UvFMtx_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvFmtxSetSharedAxes = uvFmtxSetSharedAxes;
    exports->uvMat4ApplySharedInverseTranslation = uvMat4ApplySharedInverseTranslation;
    exports->uvMat4FCopy = uvMat4FCopy;
    exports->uvMat4CopyLinear3x3 = uvMat4CopyLinear3x3;
    exports->uvMat4CopyL2F = uvMat4CopyL2F;
    exports->uvMat4CopyF2L = uvMat4CopyF2L;
    exports->uvMat4SetIdentity = uvMat4SetIdentity;
    exports->uvMat4Mul = uvMat4Mul;
    exports->func_uvfmtx_rom_00400FF8 = func_uvfmtx_rom_00400FF8;
    exports->uvFmtxModuleCleanup = uvFmtxModuleCleanup;
    exports->func_uvfmtx_rom_00401F74 = func_uvfmtx_rom_00401F74;
    exports->uvMat4BuildOrthographicProjection = uvMat4BuildOrthographicProjection;
    exports->uvMat4GetYAxisAlias = uvMat4GetYAxisAlias;
    exports->uvMat4SetOrtho = uvMat4SetOrtho;
    exports->uvMat4GetTranslation = uvMat4GetTranslation;
    exports->uvMat4BuildLookAtFromCoordinates = uvMat4BuildLookAtFromCoordinates;
    exports->uvMat4GetDirectionAngles = uvMat4GetDirectionAngles;
    exports->uvMat4SetNormalizedQuaternionRotation = uvMat4SetNormalizedQuaternionRotation;
    exports->uvMat4GetTranslationAndDirectionAngles = uvMat4GetTranslationAndDirectionAngles;
    exports->uvMat4SetNormalizedAxisRotationFromSinCos = uvMat4SetNormalizedAxisRotationFromSinCos;
    exports->uvMat4TransformDirection = uvMat4TransformDirection;
    exports->uvGfxMtxViewLoad = uvGfxMtxViewLoad;
    exports->uvMat4TransformPointAndW = uvMat4TransformPointAndW;
    exports->uvMat4PushFloatMatrix = uvMat4PushFloatMatrix;
    exports->uvMat4TransformXY = uvMat4TransformXY;
    exports->uvGfxMtxFViewPop = uvGfxMtxFViewPop;
    exports->uvMat4MultiplyLinear3x3 = uvMat4MultiplyLinear3x3;
    exports->uvGfxMtxProjPushF = uvGfxMtxProjPushF;
    exports->uvMat4ApplyQuaternionRotationAboutPivot = uvMat4ApplyQuaternionRotationAboutPivot;
    exports->uvMat4ApplyAxisRotationAboutPivot = uvMat4ApplyAxisRotationAboutPivot;
    exports->uvMat4RotateAxis = uvMat4RotateAxis;
    exports->uvMat4LocalTranslate = uvMat4LocalTranslate;
    exports->uvMat4Scale = uvMat4Scale;
    exports->uvGfxMtxCopySharedFloatMatrix = uvGfxMtxCopySharedFloatMatrix;
    exports->uvMat4ComposeScaleRotateTranslate = uvMat4ComposeScaleRotateTranslate;
    exports->uvGfxMtxLoadProjectionWithQuarterTurn = uvGfxMtxLoadProjectionWithQuarterTurn;
    exports->uvFmtxCopyAlternateSharedMatrix = uvFmtxCopyAlternateSharedMatrix;
    exports->uvMat4InvertTranslationRotation = uvMat4InvertTranslationRotation;
    exports->uvMat4SetRotationFromThreeAngles = uvMat4SetRotationFromThreeAngles;
    exports->uvMat4InvertAffineByCofactors = uvMat4InvertAffineByCofactors;
    exports->uvMat4SetTranslation = uvMat4SetTranslation;
    exports->uvMat4TransposeLinear3x3PreservingRest = uvMat4TransposeLinear3x3PreservingRest;
    exports->uvFmtxCopyVector = uvFmtxCopyVector;
    exports->uvMat4CopyWithReciprocalAndLinearScale = uvMat4CopyWithReciprocalAndLinearScale;
    exports->uvFmtxCopyNegatedVector = uvFmtxCopyNegatedVector;
    exports->uvMat4TransformPoint = uvMat4TransformPoint;
    exports->uvMat4GetYAxis = uvMat4GetYAxis;
    exports->uvMat4BuildFacingBasisBetweenTransforms = uvMat4BuildFacingBasisBetweenTransforms;
    exports->uvMat4GetNegatedYAxis = uvMat4GetNegatedYAxis;
    exports->uvMat4GetZAxis = uvMat4GetZAxis;
    exports->uvMat4GetNegatedZAxis = uvMat4GetNegatedZAxis;
#ifdef __sgi
    #line 1
#endif
    sUvMathExports = uvLoadModule('MATH');
    sUvFvecExports = uvLoadModule('FVEC');
    sUvImtxExports = uvLoadModule('IMTX');
    uvMat4SetIdentity(&D_uvfmtx_rom_004036D0);
    uvMat4SetIdentity(&D_uvfmtx_rom_00403690);
    uvMat4SetIdentity(&D_uvfmtx_rom_00403710);
    sZAxis = 0.0f;
    sYAxis = sZAxis;
    sXAxis = sYAxis;
}

#line 154 "src/modules/uvfmtx_rom.c"
/* Unload the shared math, floating-vector and integer-matrix dependencies. */
void uvFmtxModuleCleanup(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('FVEC');
    uvUnloadModule('IMTX');
}
#line 159 "src/modules/uvfmtx_rom.c"

#line 160 "src/modules/uvfmtx_rom.c"
/* Store the three shared matrix-axis values without changing their units. */
void uvFmtxSetSharedAxes(f32 x, f32 y, f32 z) {
    sXAxis = x;
    sYAxis = y;
    sZAxis = z;
}
#line 165 "src/modules/uvfmtx_rom.c"

#line 166 "src/modules/uvfmtx_rom.c"
/* Apply the negative shared translation to every homogeneous row.
 * For distinct matrices, also copy the unchanged fourth column. */
void uvMat4ApplySharedInverseTranslation(Mtx4F *dst, Mtx4F *source) {
    dst->m[0][0] = source->m[0][0] + (source->m[0][3] * -sXAxis);
    dst->m[0][1] = source->m[0][1] + (source->m[0][3] * -sYAxis);
    dst->m[0][2] = source->m[0][2] + (source->m[0][3] * -sZAxis);
    dst->m[1][0] = source->m[1][0] + (source->m[1][3] * -sXAxis);
    dst->m[1][1] = source->m[1][1] + (source->m[1][3] * -sYAxis);
    dst->m[1][2] = source->m[1][2] + (source->m[1][3] * -sZAxis);
    dst->m[2][0] = source->m[2][0] + (source->m[2][3] * -sXAxis);
    dst->m[2][1] = source->m[2][1] + (source->m[2][3] * -sYAxis);
    dst->m[2][2] = source->m[2][2] + (source->m[2][3] * -sZAxis);
    dst->m[3][0] = source->m[3][0] + (source->m[3][3] * -sXAxis);
    dst->m[3][1] = source->m[3][1] + (source->m[3][3] * -sYAxis);
    dst->m[3][2] = source->m[3][2] + (source->m[3][3] * -sZAxis);
    if (dst != source) {
        dst->m[0][3] = source->m[0][3];
        dst->m[1][3] = source->m[1][3];
        dst->m[2][3] = source->m[2][3];
        dst->m[3][3] = source->m[3][3];
    }
}
#line 186 "src/modules/uvfmtx_rom.c"

#line 187 "src/modules/uvfmtx_rom.c"
/* Copy all sixteen floating-point matrix elements in the original
 * row order. A destination equal to source retains all values. */
void uvMat4FCopy(Mtx4F *destination, Mtx4F *source) {
    destination->m[0][0] = source->m[0][0];
    destination->m[0][1] = source->m[0][1];
    destination->m[0][2] = source->m[0][2];
    destination->m[0][3] = source->m[0][3];
    destination->m[1][0] = source->m[1][0];
    destination->m[1][1] = source->m[1][1];
    destination->m[1][2] = source->m[1][2];
    destination->m[1][3] = source->m[1][3];
    destination->m[2][0] = source->m[2][0];
    destination->m[2][1] = source->m[2][1];
    destination->m[2][2] = source->m[2][2];
    destination->m[2][3] = source->m[2][3];
    destination->m[3][0] = source->m[3][0];
    destination->m[3][1] = source->m[3][1];
    destination->m[3][2] = source->m[3][2];
    destination->m[3][3] = source->m[3][3];
}
#line 205 "src/modules/uvfmtx_rom.c"

#line 206 "src/modules/uvfmtx_rom.c"
/* Copy only the nine linear 3-by-3 matrix components. Translation and the
 * fourth column retain their previous destination values. */
void uvMat4CopyLinear3x3(Mtx4F *dst, Mtx4F *src) {
    dst->m[0][0] = src->m[0][0];
    dst->m[0][1] = src->m[0][1];
    dst->m[0][2] = src->m[0][2];
    dst->m[1][0] = src->m[1][0];
    dst->m[1][1] = src->m[1][1];
    dst->m[1][2] = src->m[1][2];
    dst->m[2][0] = src->m[2][0];
    dst->m[2][1] = src->m[2][1];
    dst->m[2][2] = src->m[2][2];
}
#line 217 "src/modules/uvfmtx_rom.c"

#line 218 "src/modules/uvfmtx_rom.c"
/* Convert the by-value fixed-point matrix into floating-point storage.
 * RE_ORIGINAL_QUIRK: original-equivalent instructions select a temporary
 * when destination equals the source argument address, then test the
 * changed write pointer against that source address. Both paths skip the
 * final copy-back; preserve this redundant alias path and the by-value ABI.
 * RE_UNKNOWN: no named active C caller was found; remaining assembly or
 * opaque module-export callers have not been audited for runtime impact. */
#line 225 "src/modules/uvfmtx_rom.c"

void uvMat4CopyL2F(Mtx4F *destination, Mtx source) {
    Mtx4F *writeTarget = destination;
    s32 pad;
    Mtx4F temporaryMatrix;

    if (writeTarget == (Mtx4F *) &source) {
        writeTarget = &temporaryMatrix;
    }
    writeTarget->m[0][0] = L2F(source, 0, 0);
    writeTarget->m[0][1] = L2F(source, 0, 1);
    writeTarget->m[0][2] = L2F(source, 0, 2);
    writeTarget->m[0][3] = L2F(source, 0, 3);
    writeTarget->m[1][0] = L2F(source, 1, 0);
    writeTarget->m[1][1] = L2F(source, 1, 1);
    writeTarget->m[1][2] = L2F(source, 1, 2);
    writeTarget->m[1][3] = L2F(source, 1, 3);
    writeTarget->m[2][0] = L2F(source, 2, 0);
    writeTarget->m[2][1] = L2F(source, 2, 1);
    writeTarget->m[2][2] = L2F(source, 2, 2);
    writeTarget->m[2][3] = L2F(source, 2, 3);
    writeTarget->m[3][0] = L2F(source, 3, 0);
    writeTarget->m[3][1] = L2F(source, 3, 1);
    writeTarget->m[3][2] = L2F(source, 3, 2);
    writeTarget->m[3][3] = L2F(source, 3, 3);

    if (writeTarget == (Mtx4F *) &source) {
        uvMat4FCopy(destination, &temporaryMatrix);
    }
}
#line 254 "src/modules/uvfmtx_rom.c"
#line 247 "src/modules/uvfmtx_rom.c"

#line 248 "src/modules/uvfmtx_rom.c"
/* Convert float entries to the original split fixed-point representation.
 * RE_ORIGINAL_QUIRK: exact source/destination equality selects a temporary,
 * but the final test compares that changed write pointer against source.
 * Under ordinary caller stack ownership, aliasing therefore skips copy-back
 * and leaves caller storage unchanged. Preserve this original behavior.
 * RE_UNKNOWN: the four observed active C callers use separate storage;
 * remaining assembly and opaque export callers may have other contracts. */
#line 255 "src/modules/uvfmtx_rom.c"

void uvMat4CopyF2L(Mtx *destination, Mtx4F *source) {
    Mtx_u *writeTarget;
    Mtx temporaryMatrix;
    s32 xx;
    s32 yx;
    s32 zx;
    s32 wx;
    s32 xy;
    s32 yy;
    s32 zy;
    s32 wy;
    s32 xz;
    s32 yz;
    s32 zz;
    s32 wz;
    s32 xw;
    s32 yw;
    s32 zw;
    s32 ww;

    writeTarget = (Mtx_u *) destination;
    if ((Mtx4F *) writeTarget == source) {
        writeTarget = (Mtx_u *) &temporaryMatrix;
    }
    xx = (s32) ((source->m[0][0] * 65536.0f) + 0.5f);
    writeTarget->i[0][0] = xx >> 0x10;
    writeTarget->f[0][0] = xx & 0xFFFF;
    yx = (s32) ((source->m[0][1] * 65536.0f) + 0.5f);
    writeTarget->i[0][1] = yx >> 0x10;
    writeTarget->f[0][1] = yx & 0xFFFF;
    zx = (s32) ((source->m[0][2] * 65536.0f) + 0.5f);
    writeTarget->i[0][2] = zx >> 0x10;
    writeTarget->f[0][2] = zx & 0xFFFF;
    wx = (s32) ((source->m[0][3] * 65536.0f) + 0.5f);
    writeTarget->i[0][3] = wx >> 0x10;
    writeTarget->f[0][3] = wx & 0xFFFF;
    xy = (s32) ((source->m[1][0] * 65536.0f) + 0.5f);
    writeTarget->i[1][0] = xy >> 0x10;
    writeTarget->f[1][0] = xy & 0xFFFF;
    yy = (s32) ((source->m[1][1] * 65536.0f) + 0.5f);
    writeTarget->i[1][1] = yy >> 0x10;
    writeTarget->f[1][1] = yy & 0xFFFF;
    zy = (s32) ((source->m[1][2] * 65536.0f) + 0.5f);
    writeTarget->i[1][2] = zy >> 0x10;
    writeTarget->f[1][2] = zy & 0xFFFF;
    wy = (s32) ((source->m[1][3] * 65536.0f) + 0.5f);
    writeTarget->i[1][3] = wy >> 0x10;
    writeTarget->f[1][3] = wy & 0xFFFF;
    xz = (s32) ((source->m[2][0] * 65536.0f) + 0.5f);
    writeTarget->i[2][0] = xz >> 0x10;
    writeTarget->f[2][0] = xz & 0xFFFF;
    yz = (s32) ((source->m[2][1] * 65536.0f) + 0.5f);
    writeTarget->i[2][1] = yz >> 0x10;
    writeTarget->f[2][1] = yz & 0xFFFF;
    zz = (s32) ((source->m[2][2] * 65536.0f) + 0.5f);
    writeTarget->i[2][2] = zz >> 0x10;
    writeTarget->f[2][2] = zz & 0xFFFF;
    wz = (s32) ((source->m[2][3] * 65536.0f) + 0.5f);
    writeTarget->i[2][3] = wz >> 0x10;
    writeTarget->f[2][3] = wz & 0xFFFF;

    // Debug code from PilotWings 64
#ifdef UV_DEBUG
    if (source->m[3][0] > 32767.0f) {
        writeTarget->i[3][0] = 0x7FFF;
        _uvDebugPrintf("s+12 overfow: %f\n", source->m[3][0]);
        *(s16 *) 1 = 0;
    } else if (source->m[3][0] < -32767.0f) {
        *(s16 *) &writeTarget->i[3][0] = -0x8000;
        _uvDebugPrintf("s+12 overfow: %f\n", source->m[3][0]);
        *(s16 *) 1 = 0;
    } else {
        xw = (s32) ((source->m[3][0] * 65536.0f) + 0.5f);
        writeTarget->i[3][0] = xw >> 0x10;
        writeTarget->f[3][0] = xw & 0xFFFF;
    }

    if (source->m[3][1] > 32767.0f) {
        writeTarget->i[3][1] = 0x7FFF;
        _uvDebugPrintf("s+13 overfow: %f\n", source->m[3][1]);
        *(s16 *) 1 = 0;
    } else if (source->m[3][1] < -32767.0f) {
        *(s16 *) &writeTarget->i[3][1] = -0x8000;
        _uvDebugPrintf("s+13 overfow: %f\n", source->m[3][1]);
        *(s16 *) 1 = 0;
    } else {
        yw = (s32) ((source->m[3][1] * 65536.0f) + 0.5f);
        writeTarget->i[3][1] = yw >> 0x10;
        writeTarget->f[3][1] = yw & 0xFFFF;
    }

    if (source->m[3][2] > 32767.0f) {
        writeTarget->i[3][2] = 0x7FFF;
        _uvDebugPrintf("s+14 overfow: %f\n", source->m[3][2]);
        *(s16 *) 1 = 0;
    } else if (source->m[3][2] < -32767.0f) {
        *(s16 *) &writeTarget->i[3][2] = -0x8000;
        _uvDebugPrintf("s+14 overfow: %f\n", source->m[3][2]);
        *(s16 *) 1 = 0;
    } else {
        zw = (s32) ((source->m[3][2] * 65536.0f) + 0.5f);
        writeTarget->i[3][2] = zw >> 0x10;
        writeTarget->f[3][2] = zw & 0xFFFF;
    }
#else
    xw = (s32) ((source->m[3][0] * 65536.0f) + 0.5f);
    writeTarget->i[3][0] = xw >> 0x10;
    writeTarget->f[3][0] = xw & 0xFFFF;

    yw = (s32) ((source->m[3][1] * 65536.0f) + 0.5f);
    writeTarget->i[3][1] = yw >> 0x10;
    writeTarget->f[3][1] = yw & 0xFFFF;

    zw = (s32) ((source->m[3][2] * 65536.0f) + 0.5f);
    writeTarget->i[3][2] = zw >> 0x10;
    writeTarget->f[3][2] = zw & 0xFFFF;
#endif
    ww = (s32) ((source->m[3][3] * 65536.0f) + 0.5f);
    writeTarget->i[3][3] = ww >> 0x10;
    writeTarget->f[3][3] = ww & 0xFFFF;
    if ((Mtx4F *) writeTarget == source) {
        sUvImtxExports->uvIMtxCopy(destination, temporaryMatrix);
    }
}
#line 379 "src/modules/uvfmtx_rom.c"
#line 372 "src/modules/uvfmtx_rom.c"

void uvMat4SetIdentity(Mtx4F *dst) {
    dst->m[0][0] = 1.0f;
    dst->m[0][1] = 0.0f;
    dst->m[0][2] = 0.0f;
    dst->m[0][3] = 0.0f;
    dst->m[1][0] = 0.0f;
    dst->m[1][1] = 1.0f;
    dst->m[1][2] = 0.0f;
    dst->m[1][3] = 0.0f;
    dst->m[2][0] = 0.0f;
    dst->m[2][1] = 0.0f;
    dst->m[2][2] = 1.0f;
    dst->m[2][3] = 0.0f;
    dst->m[3][0] = 0.0f;
    dst->m[3][1] = 0.0f;
    dst->m[3][2] = 0.0f;
    dst->m[3][3] = 1.0f;
}

#line 392 "src/modules/uvfmtx_rom.c"
/* Multiply left by right into destination, preserving the established
 * public argument order: right precedes left. Use the temporary when
 * either source is the destination and preserve each dot-product order. */
void uvMat4Mul(Mtx4F *destination, Mtx4F *right, Mtx4F *left) {
    float unused1, unused2; // stack
    Mtx4F *writeMatrix;
    Mtx4F product;

    writeMatrix = destination;
    if (right == destination || left == destination) {
        writeMatrix = &product;
    }
    writeMatrix->m[0][0] = left->m[0][0] * right->m[0][0] + left->m[0][1] * right->m[1][0]
                    + left->m[0][2] * right->m[2][0] + left->m[0][3] * right->m[3][0];
    writeMatrix->m[0][1] = left->m[0][0] * right->m[0][1] + left->m[0][1] * right->m[1][1]
                    + left->m[0][2] * right->m[2][1] + left->m[0][3] * right->m[3][1];
    writeMatrix->m[0][2] = left->m[0][0] * right->m[0][2] + left->m[0][1] * right->m[1][2]
                    + left->m[0][2] * right->m[2][2] + left->m[0][3] * right->m[3][2];
    writeMatrix->m[0][3] = left->m[0][0] * right->m[0][3] + left->m[0][1] * right->m[1][3]
                    + left->m[0][2] * right->m[2][3] + left->m[0][3] * right->m[3][3];
    writeMatrix->m[1][0] = left->m[1][0] * right->m[0][0] + left->m[1][1] * right->m[1][0]
                    + left->m[1][2] * right->m[2][0] + left->m[1][3] * right->m[3][0];
    writeMatrix->m[1][1] = left->m[1][0] * right->m[0][1] + left->m[1][1] * right->m[1][1]
                    + left->m[1][2] * right->m[2][1] + left->m[1][3] * right->m[3][1];
    writeMatrix->m[1][2] = left->m[1][0] * right->m[0][2] + left->m[1][1] * right->m[1][2]
                    + left->m[1][2] * right->m[2][2] + left->m[1][3] * right->m[3][2];
    writeMatrix->m[1][3] = left->m[1][0] * right->m[0][3] + left->m[1][1] * right->m[1][3]
                    + left->m[1][2] * right->m[2][3] + left->m[1][3] * right->m[3][3];
    writeMatrix->m[2][0] = left->m[2][0] * right->m[0][0] + left->m[2][1] * right->m[1][0]
                    + left->m[2][2] * right->m[2][0] + left->m[2][3] * right->m[3][0];
    writeMatrix->m[2][1] = left->m[2][0] * right->m[0][1] + left->m[2][1] * right->m[1][1]
                    + left->m[2][2] * right->m[2][1] + left->m[2][3] * right->m[3][1];
    writeMatrix->m[2][2] = left->m[2][0] * right->m[0][2] + left->m[2][1] * right->m[1][2]
                    + left->m[2][2] * right->m[2][2] + left->m[2][3] * right->m[3][2];
    writeMatrix->m[2][3] = left->m[2][0] * right->m[0][3] + left->m[2][1] * right->m[1][3]
                    + left->m[2][2] * right->m[2][3] + left->m[2][3] * right->m[3][3];
    writeMatrix->m[3][0] = left->m[3][0] * right->m[0][0] + left->m[3][1] * right->m[1][0]
                    + left->m[3][2] * right->m[2][0] + left->m[3][3] * right->m[3][0];
    writeMatrix->m[3][1] = left->m[3][0] * right->m[0][1] + left->m[3][1] * right->m[1][1]
                    + left->m[3][2] * right->m[2][1] + left->m[3][3] * right->m[3][1];
    writeMatrix->m[3][2] = left->m[3][0] * right->m[0][2] + left->m[3][1] * right->m[1][2]
                    + left->m[3][2] * right->m[2][2] + left->m[3][3] * right->m[3][2];
    writeMatrix->m[3][3] = left->m[3][0] * right->m[0][3] + left->m[3][1] * right->m[1][3]
                    + left->m[3][2] * right->m[2][3] + left->m[3][3] * right->m[3][3];
    if (right == destination || left == destination) {
        uvMat4FCopy(destination, &product);
    }
}
#line 437 "src/modules/uvfmtx_rom.c"

#line 438 "src/modules/uvfmtx_rom.c"
/* Original no-op exported at uvfmtx_rom export slot 0x24. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_uvfmtx_rom_00400FF8(s32 arg0) {
}
#line 440 "src/modules/uvfmtx_rom.c"

#line 441 "src/modules/uvfmtx_rom.c"
/* Rotate the matrix in place around a lowercase x, y or z axis,
 * using the original row combinations and angle in radians. A zero
 * angle or unrecognized axis leaves the matrix unchanged. The temporary
 * preserves every source row until its replacement has been computed. */
void uvMat4RotateAxis(Mtx4F *matrix, float angle, char axis) {
    float sine;
    float cosine;
    float unused1;
    float unused2;
    Mtx4F rotated;

    if (angle != 0.0f) {
        sine = sUvMathExports->uvSinF(angle);
        cosine = sUvMathExports->uvCosF(angle);
        switch (axis) {
            case 'x':
                rotated.m[0][0] = matrix->m[0][0];
                rotated.m[0][1] = matrix->m[0][1];
                rotated.m[0][2] = matrix->m[0][2];
                rotated.m[0][3] = matrix->m[0][3];
                rotated.m[1][0] = (cosine * matrix->m[1][0]) + (sine * matrix->m[2][0]);
                rotated.m[1][1] = (cosine * matrix->m[1][1]) + (sine * matrix->m[2][1]);
                rotated.m[1][2] = (cosine * matrix->m[1][2]) + (sine * matrix->m[2][2]);
                rotated.m[1][3] = (cosine * matrix->m[1][3]) + (sine * matrix->m[2][3]);
                rotated.m[2][0] = (cosine * matrix->m[2][0]) - (sine * matrix->m[1][0]);
                rotated.m[2][1] = (cosine * matrix->m[2][1]) - (sine * matrix->m[1][1]);
                rotated.m[2][2] = (cosine * matrix->m[2][2]) - (sine * matrix->m[1][2]);
                rotated.m[2][3] = (cosine * matrix->m[2][3]) - (sine * matrix->m[1][3]);
                rotated.m[3][0] = matrix->m[3][0];
                rotated.m[3][1] = matrix->m[3][1];
                rotated.m[3][2] = matrix->m[3][2];
                rotated.m[3][3] = matrix->m[3][3];
                goto copy;
            case 'y':
                rotated.m[0][0] = (cosine * matrix->m[0][0]) - (sine * matrix->m[2][0]);
                rotated.m[0][1] = (cosine * matrix->m[0][1]) - (sine * matrix->m[2][1]);
                rotated.m[0][2] = (cosine * matrix->m[0][2]) - (sine * matrix->m[2][2]);
                rotated.m[0][3] = (cosine * matrix->m[0][3]) - (sine * matrix->m[2][3]);
                rotated.m[1][0] = matrix->m[1][0];
                rotated.m[1][1] = matrix->m[1][1];
                rotated.m[1][2] = matrix->m[1][2];
                rotated.m[1][3] = matrix->m[1][3];
                rotated.m[2][0] = (sine * matrix->m[0][0]) + (cosine * matrix->m[2][0]);
                rotated.m[2][1] = (sine * matrix->m[0][1]) + (cosine * matrix->m[2][1]);
                rotated.m[2][2] = (sine * matrix->m[0][2]) + (cosine * matrix->m[2][2]);
                rotated.m[2][3] = (sine * matrix->m[0][3]) + (cosine * matrix->m[2][3]);
                rotated.m[3][0] = matrix->m[3][0];
                rotated.m[3][1] = matrix->m[3][1];
                rotated.m[3][2] = matrix->m[3][2];
                rotated.m[3][3] = matrix->m[3][3];
                goto copy;
            case 'z':
                rotated.m[0][0] = (cosine * matrix->m[0][0]) + (sine * matrix->m[1][0]);
                rotated.m[0][1] = (cosine * matrix->m[0][1]) + (sine * matrix->m[1][1]);
                rotated.m[0][2] = (cosine * matrix->m[0][2]) + (sine * matrix->m[1][2]);
                rotated.m[0][3] = (cosine * matrix->m[0][3]) + (sine * matrix->m[1][3]);
                rotated.m[1][0] = (cosine * matrix->m[1][0]) - (sine * matrix->m[0][0]);
                rotated.m[1][1] = (cosine * matrix->m[1][1]) - (sine * matrix->m[0][1]);
                rotated.m[1][2] = (cosine * matrix->m[1][2]) - (sine * matrix->m[0][2]);
                rotated.m[1][3] = (cosine * matrix->m[1][3]) - (sine * matrix->m[0][3]);
                rotated.m[2][0] = matrix->m[2][0];
                rotated.m[2][1] = matrix->m[2][1];
                rotated.m[2][2] = matrix->m[2][2];
                rotated.m[2][3] = matrix->m[2][3];
                rotated.m[3][0] = matrix->m[3][0];
                rotated.m[3][1] = matrix->m[3][1];
                rotated.m[3][2] = matrix->m[3][2];
                rotated.m[3][3] = matrix->m[3][3];
            copy: // New engine, new evil code...
                uvMat4FCopy(matrix, &rotated);
                break;
        }
    }
}
#line 511 "src/modules/uvfmtx_rom.c"

#line 512 "src/modules/uvfmtx_rom.c"
/* Transform the local displacement by the first three matrix rows
 * and add it to the translation row, including its fourth component.
 * Cache all four results before storing and preserve floating-point order. */
void uvMat4LocalTranslate(Mtx4F* matrix, f32 x, f32 y, f32 z) {
    f32 translatedX;
    f32 translatedY;
    f32 translatedZ;
    f32 translatedW;

    translatedX = (x * matrix->m[0][0]) + (y * matrix->m[1][0]) + (z * matrix->m[2][0]) + matrix->m[3][0];
    translatedY = (x * matrix->m[0][1]) + (y * matrix->m[1][1]) + (z * matrix->m[2][1]) + matrix->m[3][1];
    translatedZ = (x * matrix->m[0][2]) + (y * matrix->m[1][2]) + (z * matrix->m[2][2]) + matrix->m[3][2];
    translatedW = (x * matrix->m[0][3]) + (y * matrix->m[1][3]) + (z * matrix->m[2][3]) + matrix->m[3][3];

    matrix->m[3][0] = translatedX;
    matrix->m[3][1] = translatedY;
    matrix->m[3][2] = translatedZ;
    matrix->m[3][3] = translatedW;
}
#line 528 "src/modules/uvfmtx_rom.c"

#line 529 "src/modules/uvfmtx_rom.c"
/* Scale each of the first three matrix rows by its axis factor,
 * including the fourth column, while retaining the translation row. */
void uvMat4Scale(Mtx4F *matrix, f32 scaleX, f32 scaleY, f32 scaleZ) {
    matrix->m[0][0] *= scaleX;
    matrix->m[0][1] *= scaleX;
    matrix->m[0][2] *= scaleX;
    matrix->m[0][3] *= scaleX;
    matrix->m[1][0] *= scaleY;
    matrix->m[1][1] *= scaleY;
    matrix->m[1][2] *= scaleY;
    matrix->m[1][3] *= scaleY;
    matrix->m[2][0] *= scaleZ;
    matrix->m[2][1] *= scaleZ;
    matrix->m[2][2] *= scaleZ;
    matrix->m[2][3] *= scaleZ;
}
#line 543 "src/modules/uvfmtx_rom.c"

#line 544 "src/modules/uvfmtx_rom.c"
/* Apply scale, three ordered caller-selected axis rotations, then local
 * translation through the original shared matrix helpers. */
void uvMat4ComposeScaleRotateTranslate(Mtx4F *matrix, f32 x, f32 y, f32 z, f32 angle1, f32 angle2, f32 angle3,
                              u8 axis1, u8 axis2, u8 axis3, f32 scaleX, f32 scaleY, f32 scaleZ) {
    uvMat4Scale(matrix, scaleX, scaleY, scaleZ);
    uvMat4RotateAxis(matrix, angle1, axis1);
    uvMat4RotateAxis(matrix, angle2, axis2);
    uvMat4RotateAxis(matrix, angle3, axis3);
    uvMat4LocalTranslate(matrix, x, y, z);
}
#line 552 "src/modules/uvfmtx_rom.c"

#line 553 "src/modules/uvfmtx_rom.c"
/* Transpose the linear three-by-three portion and apply the negated
 * source translation through that transpose before copying the result.
 * RE_UNKNOWN: callers must provide the rotation/translation form for this
 * shortcut to represent a full inverse; scale and shear are not inverted. */
void uvMat4InvertTranslationRotation(Mtx4F *destination, Mtx4F *source) {
    Mtx4F inverse;
    s32 row;
    s32 column;

    uvMat4FCopy(&inverse, source);

    for (row = 0; row < 3; row++) {
        for (column = 0; column < row; column++) {
            inverse.m[row][column] = source->m[column][row];
            inverse.m[column][row] = source->m[row][column];
        }
    }

    inverse.m[3][0] = 0.0f;
    inverse.m[3][1] = 0.0f;
    inverse.m[3][2] = 0.0f;
    uvMat4LocalTranslate(&inverse, -source->m[3][0], -source->m[3][1], -source->m[3][2]);
    uvMat4FCopy(destination, &inverse);
}
#line 573 "src/modules/uvfmtx_rom.c"

#line 574 "src/modules/uvfmtx_rom.c"
/* Invert the linear 3x3 block using signed determinant sums and derive
 * the inverse translation. Return zero for the original determinant
 * failure tests; retain the original floating-point evaluation order. */
s32 uvMat4InvertAffineByCofactors(Mtx4F* destination, Mtx4F* source) {
    f64 determinantTerm;
    f64 positiveTerms;
    f64 negativeTerms;
    f32 inverseDeterminant;
    s32 pad[2];

    negativeTerms = 0.0;
    positiveTerms = 0.0;
    determinantTerm = ((source->m[0][0] * source->m[1][1]) * source->m[2][2]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = ((source->m[0][1] * source->m[1][2]) * source->m[2][0]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = ((source->m[0][2] * source->m[1][0]) * source->m[2][1]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = ((-source->m[0][2] * source->m[1][1]) * source->m[2][0]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = ((-source->m[0][1] * source->m[1][0]) * source->m[2][2]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = ((-source->m[0][0] * source->m[1][2]) * source->m[2][1]);
    if (determinantTerm >= 0.0) {
        positiveTerms += determinantTerm;
    } else {
        negativeTerms += determinantTerm;
    }
    determinantTerm = positiveTerms + negativeTerms;
    if ((determinantTerm == 0) || (positiveTerms == negativeTerms)) {
        return 0;
    }
    inverseDeterminant = 1.0 / determinantTerm;
    destination->m[0][0] = ((source->m[1][1] * source->m[2][2]) - (source->m[1][2] * source->m[2][1])) * inverseDeterminant;
    destination->m[1][0] = -((source->m[1][0] * source->m[2][2]) - (source->m[1][2] * source->m[2][0])) * inverseDeterminant;
    destination->m[2][0] = ((source->m[1][0] * source->m[2][1]) - (source->m[1][1] * source->m[2][0])) * inverseDeterminant;
    destination->m[0][1] = -((source->m[0][1] * source->m[2][2]) - (source->m[0][2] * source->m[2][1])) * inverseDeterminant;
    destination->m[1][1] = ((source->m[0][0] * source->m[2][2]) - (source->m[0][2] * source->m[2][0])) * inverseDeterminant;
    destination->m[2][1] = -((source->m[0][0] * source->m[2][1]) - (source->m[0][1] * source->m[2][0])) * inverseDeterminant;
    destination->m[0][2] = ((source->m[0][1] * source->m[1][2]) - (source->m[0][2] * source->m[1][1])) * inverseDeterminant;
    destination->m[1][2] = -((source->m[0][0] * source->m[1][2]) - (source->m[0][2] * source->m[1][0])) * inverseDeterminant;
    destination->m[2][2] = ((source->m[0][0] * source->m[1][1]) - (source->m[0][1] * source->m[1][0])) * inverseDeterminant;
    destination->m[3][0] = -(((source->m[3][0] * destination->m[0][0]) + (source->m[3][1] * destination->m[1][0]) + (source->m[3][2] * destination->m[2][0])));
    destination->m[3][1] = -(((source->m[3][0] * destination->m[0][1]) + (source->m[3][1] * destination->m[1][1]) + (source->m[3][2] * destination->m[2][1])));
    destination->m[3][2] = -(((source->m[3][0] * destination->m[0][2]) + (source->m[3][1] * destination->m[1][2]) + (source->m[3][2] * destination->m[2][2])));
    destination->m[2][3] = 0.0f;
    destination->m[1][3] = 0.0f;
    destination->m[0][3] = 0.0f;
    destination->m[3][3] = 1.0f;
    return 1;
}
#line 642 "src/modules/uvfmtx_rom.c"

#line 643 "src/modules/uvfmtx_rom.c"
/* Transpose only the linear 3x3 block and copy the remaining entries.
 * Use a temporary matrix for an in-place request. */
void uvMat4TransposeLinear3x3PreservingRest(Mtx4F *destination, Mtx4F *source) {
    s32 pad;
    Mtx4F *output;
    Mtx4F temporary;

    output = destination;
    if (source == destination) {
        output = &temporary;
    }
    output->m[0][0] = source->m[0][0];
    output->m[0][3] = source->m[0][3];
    output->m[1][1] = source->m[1][1];
    output->m[1][3] = source->m[1][3];
    output->m[2][2] = source->m[2][2];
    output->m[2][3] = source->m[2][3];
    output->m[3][0] = source->m[3][0];
    output->m[3][1] = source->m[3][1];
    output->m[3][2] = source->m[3][2];
    output->m[3][3] = source->m[3][3];
    output->m[0][1] = source->m[1][0];
    output->m[0][2] = source->m[2][0];
    output->m[1][0] = source->m[0][1];
    output->m[1][2] = source->m[2][1];
    output->m[2][0] = source->m[0][2];
    output->m[2][1] = source->m[1][2];
    if (output == &temporary) {
        uvMat4FCopy(destination, &temporary);
    }
}
#line 672 "src/modules/uvfmtx_rom.c"

void uvMat4CopyWithReciprocalAndLinearScale(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);

#line 675 "src/modules/uvfmtx_rom.c"

/* Copy all 16 elements in the original interleaved load/store order. Scale
 * the 3-by-3 block by linearMultiplier * (1.0f / divisor), the first three
 * elements of row 3 by 1.0f / divisor, and copy column 3 unchanged.
 * Preserve expression grouping and the inherited empty conditional scaffold.
 * RE_UNKNOWN: the historical source form behind that scaffold, valid divisor
 * and floating-point input domains, complete matrix spans and alias/lifetime
 * guarantees need original callers, parameter producers and source/compiler
 * evidence. No nonzero-divisor guarantee is established here. */
#line 675 "src/modules/uvfmtx_rom.c"
void uvMat4CopyWithReciprocalAndLinearScale(Mtx4F *outMatrix, Mtx4F *sourceMatrix, f32 divisor, f32 linearMultiplier) {
    if (divisor)
        ; // FAKE
    outMatrix->m[0][0] = sourceMatrix->m[0][0] * (linearMultiplier * ((1.0f / divisor)));
    outMatrix->m[0][1] = sourceMatrix->m[0][1] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[0][2] = sourceMatrix->m[0][2] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[0][3] = sourceMatrix->m[0][3];
    outMatrix->m[1][0] = sourceMatrix->m[1][0] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[1][1] = sourceMatrix->m[1][1] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[1][2] = sourceMatrix->m[1][2] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[1][3] = sourceMatrix->m[1][3];
    outMatrix->m[2][0] = sourceMatrix->m[2][0] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[2][1] = sourceMatrix->m[2][1] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[2][2] = sourceMatrix->m[2][2] * (linearMultiplier * (1.0f / divisor));
    outMatrix->m[2][3] = sourceMatrix->m[2][3];
    outMatrix->m[3][0] = sourceMatrix->m[3][0] * (1.0f / divisor);
    outMatrix->m[3][1] = sourceMatrix->m[3][1] * (1.0f / divisor);
    outMatrix->m[3][2] = sourceMatrix->m[3][2] * (1.0f / divisor);
    outMatrix->m[3][3] = sourceMatrix->m[3][3];
}
#line 695 "src/modules/uvfmtx_rom.c"

void uvMat4BuildFacingBasisBetweenTransforms(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);

#line 698 "src/modules/uvfmtx_rom.c"
/* Transform a three-component point including translation. Read all input
 * components first so the original in-place behavior is preserved. */
void uvMat4TransformPoint(Mtx4F *matrix, Vec3F *dst, Vec3F *input) {
    float x = input->x;
    float y = input->y;
    float z = input->z;
    dst->x = x * matrix->m[0][0] + y * matrix->m[1][0] + z * matrix->m[2][0] + matrix->m[3][0];
    dst->y = x * matrix->m[0][1] + y * matrix->m[1][1] + z * matrix->m[2][1] + matrix->m[3][1];
    dst->z = x * matrix->m[0][2] + y * matrix->m[1][2] + z * matrix->m[2][2] + matrix->m[3][2];
}
#line 706 "src/modules/uvfmtx_rom.c"

#line 707 "src/modules/uvfmtx_rom.c"
/* Build a normalized basis from the two transform positions and the
 * origin transform third axis. Preserve the planar first-axis fallback
 * and leave the destination untouched for coincident positions. */
void uvMat4BuildFacingBasisBetweenTransforms(Mtx4F *destination, Mtx4F *targetTransform, Mtx4F *originTransform) {
    Vec3F direction;
    Vec3F thirdAxis;
    Vec3F firstAxis;

    direction.x = targetTransform->m[3][0] - originTransform->m[3][0];
    direction.y = targetTransform->m[3][1] - originTransform->m[3][1];
    direction.z = targetTransform->m[3][2] - originTransform->m[3][2];
    if (sUvFvecExports->uvVec3FNormalize((Vec3F *) &direction, (Vec3F *) &direction) != 0) {
        thirdAxis.x = originTransform->m[2][0];
        thirdAxis.y = originTransform->m[2][1];
        thirdAxis.z = originTransform->m[2][2];
        sUvFvecExports->uvVec3FCross(&firstAxis, (Vec3F *) &direction, (Vec3F *) &thirdAxis);
        if (sUvFvecExports->uvVec3FNormalize(&firstAxis, &firstAxis) == 0) {
            firstAxis.x = originTransform->m[0][0];
            firstAxis.y = originTransform->m[0][1];
            firstAxis.z = 0.0f;
            sUvFvecExports->uvVec3FNormalize(&firstAxis, &firstAxis);
        }
        sUvFvecExports->uvVec3FCross((Vec3F *) &thirdAxis, &firstAxis, (Vec3F *) &direction);
        sUvFvecExports->uvVec3FNormalize((Vec3F *) &thirdAxis, (Vec3F *) &thirdAxis);
        destination->m[0][0] = (f32) firstAxis.x;
        destination->m[0][1] = firstAxis.y;
        destination->m[0][2] = firstAxis.z;
        destination->m[1][0] = direction.x;
        destination->m[1][1] = direction.y;
        destination->m[1][2] = direction.z;
        destination->m[2][0] = thirdAxis.x;
        destination->m[2][1] = thirdAxis.y;
        destination->m[2][2] = thirdAxis.z;
        destination->m[3][0] = originTransform->m[3][0];
        destination->m[3][1] = originTransform->m[3][1];
        destination->m[3][2] = originTransform->m[3][2];
        destination->m[0][3] = 0.0f;
        destination->m[1][3] = 0.0f;
        destination->m[2][3] = 0.0f;
        destination->m[3][3] = 1.0f;
    }
}
#line 746 "src/modules/uvfmtx_rom.c"

void func_uvfmtx_rom_00401F74(Mtx4F *dst, float left, float right, float top, float bottom, float near,
                              float far) {
    dst->m[0][0] = (2.0f * near) / (right - left);
    dst->m[1][1] = (2.0f * near) / (bottom - top);
    dst->m[2][0] = (right + left) / (right - left);
    dst->m[2][1] = (bottom + top) / (bottom - top);
    dst->m[2][2] = -(far + near) / (far - near);
    dst->m[2][3] = -1.0f;
    dst->m[3][2] = -((2.0f * near) * far) / (far - near);
    if (0) {
    } // fakematch
    dst->m[0][1] = dst->m[0][2] = dst->m[0][3] = dst->m[1][0] = dst->m[1][2] = dst->m[1][3] =
        dst->m[3][0] = dst->m[3][1] = dst->m[3][3] = 0.0f;
}

#line 762 "src/modules/uvfmtx_rom.c"
/* Build the original orthographic projection from the six clip planes,
 * including its bottom-minus-top Y convention and depth sign. */
void uvMat4BuildOrthographicProjection(Mtx4F *destination, f32 left, f32 right, f32 top, f32 bottom, f32 nearPlane, f32 farPlane) {
    f32 nearValue;
    Mtx4F *output;
    output = destination;
    output->m[0][0] = 2.0f / (right - left);
    output->m[1][1] = 2.0f / (bottom - top);
    nearValue = nearPlane;
    output->m[2][2] = (-2.0f) / (farPlane - nearValue);
    output->m[3][0] = (-(right + left)) / (right - left);
    output->m[3][1] = (-(bottom + top)) / (bottom - top);
    output->m[3][2] = (-(farPlane + nearValue)) / (farPlane - nearValue);
    output->m[0][1] = 0.0f;
    output->m[0][2] = 0.0f;
    output->m[0][3] = 0.0f;
    output->m[1][0] = 0.0f;
    output->m[1][2] = 0.0f;
    output->m[1][3] = 0.0f;
    output->m[2][0] = 0.0f;
    output->m[2][1] = 0.0f;
    output->m[2][3] = 0.0f;
    output->m[3][3] = 1.0f;
}
#line 784 "src/modules/uvfmtx_rom.c"

#line 785 "src/modules/uvfmtx_rom.c"

void uvMat4SetOrtho(Mtx4F *matrix, f32 firstXBound, f32 secondXBound, f32 firstYBound, f32 secondYBound) {
    matrix->m[0][0] = 2.0f / (secondXBound - firstXBound);
    matrix->m[1][1] = 2.0f / (secondYBound - firstYBound);
    matrix->m[2][2] = -1.0f;
    matrix->m[3][0] = -(secondXBound + firstXBound) / (secondXBound - firstXBound);
    matrix->m[3][1] = -(secondYBound + firstYBound) / (secondYBound - firstYBound);

    matrix->m[0][1] = 0.0f;
    matrix->m[0][2] = 0.0f;
    matrix->m[0][3] = 0.0f;
    matrix->m[1][0] = 0.0f;
    matrix->m[1][2] = 0.0f;
    matrix->m[1][3] = 0.0f;
    matrix->m[2][0] = 0.0f;
    matrix->m[2][1] = 0.0f;
    matrix->m[2][3] = 0.0f;
    matrix->m[3][2] = 0.0f;
    matrix->m[3][3] = 1.0f;
    uvMat4RotateAxis(matrix, 1.5707963f, 0x78);
}
#line 805 "src/modules/uvfmtx_rom.c"

#line 806 "src/modules/uvfmtx_rom.c"
/* Build a look-at transform from eye, target and up-vector coordinates.
 * Retain the original normalization order and unguarded degenerate-input
 * behavior so floating-point results remain unchanged. */
void uvMat4BuildLookAtFromCoordinates(Mtx4F *destination, f32 eyeX, f32 eyeY, f32 eyeZ, f32 targetX, f32 targetY, f32 targetZ,
                              f32 upX, f32 upY, f32 upZ) {
    f32 backX;
    f32 backY;
    f32 backZ;
    f32 rightX;
    f32 rightY;
    f32 rightZ;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 inverseLength;

    backX = targetX - eyeX;
    backY = targetY - eyeY;
    backZ = targetZ - eyeZ;
    inverseLength = -1.0f / sqrtf(SQ(backX) + SQ(backY) + SQ(backZ));
    backX *= inverseLength;
    backY *= inverseLength;
    backZ *= inverseLength;

    rightX = (upY * backZ) - (upZ * backY);
    rightY = (upZ * backX) - (upX * backZ);
    rightZ = (upX * backY) - (upY * backX);

    inverseLength = 1.0f / sqrtf(SQ(rightX) + SQ(rightY) + SQ(rightZ));
    rightX *= inverseLength;
    rightY *= inverseLength;
    rightZ *= inverseLength;

    upX = (backY * rightZ) - (backZ * rightY);
    upY = (backZ * rightX) - (backX * rightZ);
    upZ = (backX * rightY) - (backY * rightX);

    inverseLength = 1.0f / sqrtf(SQ(upX) + SQ(upY) + SQ(upZ));
    upX *= inverseLength;
    upY *= inverseLength;
    upZ *= inverseLength;

    destination->m[0][0] = rightX;
    destination->m[1][0] = rightY;
    destination->m[2][0] = rightZ;
    destination->m[3][0] = -((eyeX * rightX) + (eyeY * rightY) + (eyeZ * rightZ));
    destination->m[0][1] = upX;
    destination->m[1][1] = upY;
    destination->m[2][1] = upZ;
    destination->m[3][1] = -((eyeX * upX) + (eyeY * upY) + (eyeZ * upZ));
    destination->m[0][2] = backX;
    destination->m[1][2] = backY;
    destination->m[2][2] = backZ;
    destination->m[3][2] = -((eyeX * backX) + (eyeY * backY) + (eyeZ * backZ));
    destination->m[0][3] = 0;
    destination->m[1][3] = 0;
    destination->m[2][3] = 0;
    destination->m[3][3] = 1.0f;
}
#line 861 "src/modules/uvfmtx_rom.c"

// temp-less function
#line 863 "src/modules/uvfmtx_rom.c"
/* Write and normalize the linear 3x3 rotation rows from quaternion
 * components x, y, z and w. Other matrix entries remain untouched. */
void uvMat4SetNormalizedQuaternionRotation(Mtx4F *destination, f32 quaternionX, f32 quaternionY, f32 quaternionZ, f32 quaternionW) {
    destination->m[0][0] = 1.0f - (2.0f * (SQ(quaternionY) + SQ(quaternionZ)));
    destination->m[0][1] = 2.0f * ((quaternionX * quaternionY) - (quaternionZ * quaternionW));
    destination->m[0][2] = 2.0f * ((quaternionZ * quaternionX) + (quaternionY * quaternionW));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &destination->m[0][0], (Vec3F *) &destination->m[0][0]);
    destination->m[1][0] = 2.0f * ((quaternionX * quaternionY) + (quaternionZ * quaternionW));
    destination->m[1][1] = 1.0f - (2.0f * (SQ(quaternionZ) + (quaternionX * quaternionX)));
    destination->m[1][2] = 2.0f * ((quaternionY * quaternionZ) - (quaternionX * quaternionW));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &destination->m[1][0], (Vec3F *) &destination->m[1][0]);
    destination->m[2][0] = 2.0f * ((quaternionZ * quaternionX) - (quaternionY * quaternionW));
    destination->m[2][1] = 2.0f * ((quaternionY * quaternionZ) + (quaternionX * quaternionW));
    destination->m[2][2] = 1.0f - (2.0f * (SQ(quaternionY) + (quaternionX * quaternionX)));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &destination->m[2][0], (Vec3F *) &destination->m[2][0]);
}
#line 877 "src/modules/uvfmtx_rom.c"

#line 878 "src/modules/uvfmtx_rom.c"
/* Build and normalize the linear rotation rows from the source first
 * row as axis and the caller sine/cosine values. Preserve the original
 * arithmetic order and leave the remaining matrix entries unchanged. */
void uvMat4SetNormalizedAxisRotationFromSinCos(Mtx4F *destination, Mtx4F *axisTransform, f32 sine, f32 cosine) {
    f32 oneMinusCosine;
    Vec3F axisProducts;
    Vec3F scaledAxis;

    oneMinusCosine = (1.0f - cosine);
    axisProducts.z = axisTransform->m[0][1] * (axisTransform->m[0][0] * oneMinusCosine);
    axisProducts.y = axisTransform->m[0][2] * (axisTransform->m[0][1] * oneMinusCosine);
    axisProducts.x = axisTransform->m[0][0] * (axisTransform->m[0][2] * oneMinusCosine);
    sUvFvecExports->uvVec3FScale(&scaledAxis, (Vec3F *) axisTransform, sine);
    destination->m[0][0] = (SQ(axisTransform->m[0][0]) * oneMinusCosine) + cosine;
    destination->m[0][1] = axisProducts.z - scaledAxis.z;
    destination->m[0][2] = axisProducts.x + scaledAxis.y;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) destination->m[0], (Vec3F *) destination->m[0]);
    destination->m[1][0] = axisProducts.z + scaledAxis.z;
    destination->m[1][1] = (SQ(axisTransform->m[0][1]) * oneMinusCosine) + cosine;
    destination->m[1][2] = axisProducts.y - scaledAxis.x;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) destination->m[1], (Vec3F *) destination->m[1]);
    destination->m[2][0] = axisProducts.x - scaledAxis.y;
    destination->m[2][1] = axisProducts.y + scaledAxis.x;
    destination->m[2][2] = (SQ(axisTransform->m[0][2]) * oneMinusCosine) + cosine;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) destination->m[2], (Vec3F *) destination->m[2]);
}
#line 901 "src/modules/uvfmtx_rom.c"

#line 902 "src/modules/uvfmtx_rom.c"

/* Convert the floating matrix, then pass the fixed matrix by value to the
 * original IMTX stack provider with the low 16 flag bits. Preserve the
 * ignored return value when the provider rejects its stack-index comparison.
 * RE_UNKNOWN: valid conversion inputs, matrix spans, stack/buffer indices,
 * capacity, historical flag meanings and backing-storage lifetime through
 * RSP consumption require original callers, parameter producers and
 * allocation/frame scheduling. Caller expectations for rejection and
 * source/storage aliases remain unresolved. */
#line 902 "src/modules/uvfmtx_rom.c"
void uvGfxMtxViewLoad(Mtx4F *matrix, u16 matrixFlags) {
    Mtx fixedMatrix;

    uvMat4CopyF2L(&fixedMatrix, matrix);
    sUvImtxExports->uvIMtxPush(fixedMatrix, matrixFlags);
}
#line 908 "src/modules/uvfmtx_rom.c"

#line 909 "src/modules/uvfmtx_rom.c"
/* Convert the float matrix to the original fixed-point representation and
 * push/load it through the integer-matrix dependency. */
void uvMat4PushFloatMatrix(Mtx4F *mtxF) {
    Mtx mtx;

    uvMat4CopyF2L(&mtx, mtxF);
    sUvImtxExports->uvIMtxPush(mtx, G_MTX_PUSH | G_MTX_LOAD);
}
#line 915 "src/modules/uvfmtx_rom.c"

void uvGfxMtxFViewPop(void) {
    sUvImtxExports->uvGfxMtxViewPop();
}

#line 920 "src/modules/uvfmtx_rom.c"

/* Copy into shared matrix 0x4036D0, multiply into 0x403710 using 0x4036D0
 * and 0x403690 in the original argument order, then convert and pass the
 * fixed matrix by value to IMTX projection loading. That provider forwards
 * flags 6 to the stack provider; preserve the unchecked submission result.
 * RE_UNKNOWN: projection conventions, historical flag meanings, conversion
 * inputs, matrix spans, shared-storage aliases/lifetimes and valid stack/
 * buffer domains require original callers, shared-matrix producers and
 * allocation/frame scheduling. Caller expectations for rejection are unknown. */
#line 920 "src/modules/uvfmtx_rom.c"
void uvGfxMtxProjPushF(Mtx4F *matrix) {
    Mtx fixedMatrix;

    uvMat4FCopy(&D_uvfmtx_rom_004036D0, matrix);
    uvMat4Mul(&D_uvfmtx_rom_00403710, &D_uvfmtx_rom_004036D0, &D_uvfmtx_rom_00403690);
    uvMat4CopyF2L(&fixedMatrix, &D_uvfmtx_rom_00403710);
    sUvImtxExports->uvIMtxLoadProjection(fixedMatrix);
}
#line 928 "src/modules/uvfmtx_rom.c"

#line 929 "src/modules/uvfmtx_rom.c"
/* Copy the shared floating matrix at 0x00403690 to caller storage. */
void uvGfxMtxCopySharedFloatMatrix(Mtx4F *destination) {
    uvMat4FCopy(destination, &D_uvfmtx_rom_00403690);
}
#line 932 "src/modules/uvfmtx_rom.c"

#line 933 "src/modules/uvfmtx_rom.c"
/* Copy the supplied transform, apply the original -pi/2 X rotation,
 * combine it with the shared projection matrix and load the fixed-point
 * projection followed by an identity modelview matrix. */
void uvGfxMtxLoadProjectionWithQuarterTurn(Mtx4F *transform) {
    Mtx fixedMatrix;
    Mtx4F quarterTurn;

    uvMat4FCopy(&D_uvfmtx_rom_00403690, transform);
    uvMat4SetIdentity(&quarterTurn);
    uvMat4RotateAxis(&quarterTurn, -1.5707963f, 0x78);
    uvMat4Mul(&D_uvfmtx_rom_00403690, &quarterTurn, &D_uvfmtx_rom_00403690);
    uvMat4Mul(&D_uvfmtx_rom_00403710, &D_uvfmtx_rom_004036D0, &D_uvfmtx_rom_00403690);
    uvMat4CopyF2L(&fixedMatrix, &D_uvfmtx_rom_00403710);
    sUvImtxExports->uvIMtxLoadProjection(fixedMatrix);
    sUvImtxExports->uvIMtxSetIdentity(&fixedMatrix);
    sUvImtxExports->uvIMtxLoadModelview(fixedMatrix);
}
#line 947 "src/modules/uvfmtx_rom.c"

#line 948 "src/modules/uvfmtx_rom.c"

/* Build the original matrix from three ordered sine/cosine pairs. For each
 * exact zero input, retain the original zero/one assignments and skipped
 * callbacks. The third zero-input path assigns zero products and sineSecond
 * directly; preserve that path, callback reloads and all f32 associations.
 * Retain the inherited do/while-zero source scaffold.
 * RE_UNKNOWN: historical angle/axis conventions and source form, valid input
 * and matrix-storage domains, aliases and module/callback lifetimes require
 * original callers, parameter producers and source/module-management evidence.
 * Observed callback bindings do not establish caller range guarantees. */
#line 948 "src/modules/uvfmtx_rom.c"
void uvMat4SetRotationFromThreeAngles(Mtx4F *matrix, f32 firstAngle, f32 secondAngle, f32 thirdAngle) {
    f32 cosineThird;
    f32 sineThirdTimesSineSecond;
    f32 cosineSecond;
    f32 sineSecond;
    f32 cosineThirdTimesSineSecond;
    f32 sineThird;
    f32 cosineFirst;
    f32 sineFirst;

    if (firstAngle == 0.0f) {
        cosineFirst = 1.0f;
        sineFirst = 0.0f;
    } else {
        sineFirst = sUvMathExports->uvSinF(firstAngle);
        cosineFirst = sUvMathExports->uvCosF(firstAngle);
    }
    if (secondAngle == 0.0f) {
        cosineSecond = 1.0f;
        sineSecond = 0.0f;
    } else {
        do {
            sineSecond = sUvMathExports->uvSinF(secondAngle);
        } while (0); // FAKE
        cosineSecond = sUvMathExports->uvCosF(secondAngle);
    }
    if (thirdAngle == 0.0f) {
        cosineThird = 1.0f;
        sineThird = 0.0f;
        sineThirdTimesSineSecond = 0.0f;
        cosineThirdTimesSineSecond = sineSecond;
    } else {
        sineThird = sUvMathExports->uvSinF(thirdAngle);
        cosineThird = sUvMathExports->uvCosF(thirdAngle);
        sineThirdTimesSineSecond = sineThird * sineSecond;
        cosineThirdTimesSineSecond = cosineThird * sineSecond;
    }
    matrix->m[3][0] = 0.0f;
    matrix->m[3][1] = 0.0f;
    matrix->m[1][2] = sineSecond;
    matrix->m[3][2] = 0.0f;
    matrix->m[0][3] = 0.0f;
    matrix->m[1][3] = 0.0f;
    matrix->m[2][3] = 0.0f;
    matrix->m[0][0] = (cosineThird * cosineFirst) - (sineThirdTimesSineSecond * sineFirst);
    matrix->m[1][0] = -cosineSecond * sineFirst;
    matrix->m[2][0] = (sineThird * cosineFirst) + (cosineThirdTimesSineSecond * sineFirst);
    matrix->m[0][1] = (cosineThird * sineFirst) + (sineThirdTimesSineSecond * cosineFirst);
    matrix->m[1][1] = cosineSecond * cosineFirst;
    matrix->m[2][1] = (sineThird * sineFirst) - (cosineThirdTimesSineSecond * cosineFirst);
    matrix->m[0][2] = -sineThird * cosineSecond;
    matrix->m[2][2] = cosineThird * cosineSecond;
    matrix->m[3][3] = 1.0f;
}
#line 1002 "src/modules/uvfmtx_rom.c"

#line 1003 "src/modules/uvfmtx_rom.c"
/* Set the three translation-row components without changing its fourth word. */
void uvMat4SetTranslation(Mtx4F *matrix, f32 x, f32 y, f32 z) {
    sUvFvecExports->uvVec3FSet((Vec3F *) matrix->m[3], x, y, z);
}
#line 1006 "src/modules/uvfmtx_rom.c"

#line 1007 "src/modules/uvfmtx_rom.c"
/* Copy three components through the shared vector helper. */
void uvFmtxCopyVector(Vec3F *output, Vec3F *input) {
    sUvFvecExports->uvVec3FCopy(output, input);
}
#line 1010 "src/modules/uvfmtx_rom.c"

#line 1011 "src/modules/uvfmtx_rom.c"
/* Copy three components, then negate the copied vector in place. */
void uvFmtxCopyNegatedVector(Vec3F *output, Vec3F *input) {
    sUvFvecExports->uvVec3FCopy(output, input);
    sUvFvecExports->uvVec3FNegate(output, output);
}
#line 1015 "src/modules/uvfmtx_rom.c"

#line 1016 "src/modules/uvfmtx_rom.c"
/* Copy the first three components of matrix row one to the output vector. */
void uvMat4GetYAxis(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[1]);
}
#line 1019 "src/modules/uvfmtx_rom.c"

#line 1020 "src/modules/uvfmtx_rom.c"
/* Copy and negate the first three components of matrix row one. */
void uvMat4GetNegatedYAxis(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[1]);
    sUvFvecExports->uvVec3FNegate(output, output);
}
#line 1024 "src/modules/uvfmtx_rom.c"

#line 1025 "src/modules/uvfmtx_rom.c"
/* Copy the first three components of matrix row two to the output vector. */
void uvMat4GetZAxis(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[2]);
}
#line 1028 "src/modules/uvfmtx_rom.c"

#line 1029 "src/modules/uvfmtx_rom.c"
/* Copy and negate the first three components of matrix row two. */
void uvMat4GetNegatedZAxis(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[2]);
    sUvFvecExports->uvVec3FNegate(output, output);
}
#line 1033 "src/modules/uvfmtx_rom.c"

#line 1034 "src/modules/uvfmtx_rom.c"
/* Preserve the original second entry point that copies matrix row one.
 * Do not merge this export with the other Y-axis accessor. */
void uvMat4GetYAxisAlias(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[1]);
}
#line 1037 "src/modules/uvfmtx_rom.c"

#line 1038 "src/modules/uvfmtx_rom.c"
/* Copy the first three translation-row components to the output vector. */
void uvMat4GetTranslation(Vec3F *output, Mtx4F *matrix) {
    sUvFvecExports->uvVec3FCopy(output, (Vec3F *) matrix->m[3]);
}
#line 1041 "src/modules/uvfmtx_rom.c"

#line 1042 "src/modules/uvfmtx_rom.c"
/* Extract the original three direction angles through shared atan2/square
 * root helpers. Preserve the exact component choices and addition order. */
void uvMat4GetDirectionAngles(Mtx4F *matrix, f32 *first, f32 *second, f32 *third) {
    *first = sUvMathExports->uvAtan2F(-matrix->m[1][0], matrix->m[1][1]);
    *second =
        sUvMathExports->uvAtan2F(matrix->m[1][2], sUvMathExports->uvSqrtf(SQ(matrix->m[1][0]) + SQ(matrix->m[1][1])));
    *third = sUvMathExports->uvAtan2F(-matrix->m[0][2], matrix->m[2][2]);
}
#line 1051 "src/modules/uvfmtx_rom.c"

#line 1052 "src/modules/uvfmtx_rom.c"
/* Extract the original three direction angles and translation vector.
 * Keep its square-sum order, which differs from the scalar-output accessor. */
#line 1054 "src/modules/uvfmtx_rom.c"

void uvMat4GetTranslationAndDirectionAngles(Mtx4F *matrix, Vec3F *translation, Vec3F *angles) {
    f32 rowOneY;
    f32 rowOneX;

    angles->x = sUvMathExports->uvAtan2F(-matrix->m[1][0], matrix->m[1][1]);
    rowOneX = matrix->m[1][0];
    rowOneY = matrix->m[1][1];
    angles->y = sUvMathExports->uvAtan2F(matrix->m[1][2], sUvMathExports->uvSqrtf(SQ(rowOneY) + SQ(rowOneX)));
    angles->z = sUvMathExports->uvAtan2F(-matrix->m[0][2], matrix->m[2][2]);
    translation->x = matrix->m[3][0];
    translation->y = matrix->m[3][1];
    translation->z = matrix->m[3][2];
}
#line 1067 "src/modules/uvfmtx_rom.c"
#line 1065 "src/modules/uvfmtx_rom.c"

#line 1066 "src/modules/uvfmtx_rom.c"
/* Transform three components through the linear matrix portion, omitting
 * translation. Preserve the original multiplication/addition order. */
void uvMat4TransformDirection(Mtx4F *matrix, Vec3F *output, Vec3F *input) {
    f32 x;
    f32 y;
    f32 z;

    x = input->x;
    y = input->y;
    z = input->z;
    output->x = ((x * matrix->m[0][0]) + (y * matrix->m[1][0])) + (matrix->m[2][0] * z);
    output->y = ((x * matrix->m[0][1]) + (y * matrix->m[1][1])) + (matrix->m[2][1] * z);
    output->z = ((x * matrix->m[0][2]) + (y * matrix->m[1][2])) + (matrix->m[2][2] * z);
}
#line 1078 "src/modules/uvfmtx_rom.c"

#line 1079 "src/modules/uvfmtx_rom.c"
/* Write the transformed XYZ point and return its homogeneous W component.
 * Preserve input caching, translation and the original operation order. */
f32 uvMat4TransformPointAndW(Mtx4F *matrix, Vec3F *output, Vec3F *input) {
    f32 y;
    f32 z;
    f32 x;

    x = input->x;
    y = input->y;
    z = input->z;
    output->x = ((x * matrix->m[0][0]) + (y * matrix->m[1][0]) + (z * matrix->m[2][0])) + matrix->m[3][0];
    output->y = ((x * matrix->m[0][1]) + (y * matrix->m[1][1]) + (z * matrix->m[2][1])) + matrix->m[3][1];
    output->z = ((x * matrix->m[0][2]) + (y * matrix->m[1][2]) + (z * matrix->m[2][2])) + matrix->m[3][2];
    return ((x * matrix->m[0][3]) + (y * matrix->m[1][3]) + (z * matrix->m[2][3])) + matrix->m[3][3];
}
#line 1092 "src/modules/uvfmtx_rom.c"

#line 1093 "src/modules/uvfmtx_rom.c"
/* Transform input XY through the two-dimensional linear matrix portion,
 * write output Z as zero and leave translation unused. */
void uvMat4TransformXY(Mtx4F *matrix, Vec3F *output, Vec3F *input) {
    f32 x;
    f32 y;

    x = input->x;
    y = input->y;
    output->x = (x * matrix->m[0][0]) + (matrix->m[1][0] * y);
    output->y = (x * matrix->m[0][1]) + (matrix->m[1][1] * y);
    output->z = 0.0f;
}
#line 1103 "src/modules/uvfmtx_rom.c"

#line 1104 "src/modules/uvfmtx_rom.c"
/* Write the linear 3x3 product of the second source by the first source.
 * Use a temporary matrix when either source aliases the destination;
 * do not modify translation or homogeneous entries. */
void uvMat4MultiplyLinear3x3(Mtx4F *destination, Mtx4F *firstSource, Mtx4F *secondSource) {
    s32 pad[2];
    Mtx4F *output;
    Mtx4F temporary;

    output = destination;
    if ((firstSource == destination) || (secondSource == destination)) {
        output = &temporary;
    }
    output->m[0][0] = ((secondSource->m[0][0] * firstSource->m[0][0]) + (secondSource->m[0][1] * firstSource->m[1][0]))
                      + (secondSource->m[0][2] * firstSource->m[2][0]);
    output->m[0][1] = ((secondSource->m[0][0] * firstSource->m[0][1]) + (secondSource->m[0][1] * firstSource->m[1][1]))
                      + (secondSource->m[0][2] * firstSource->m[2][1]);
    output->m[0][2] = ((secondSource->m[0][0] * firstSource->m[0][2]) + (secondSource->m[0][1] * firstSource->m[1][2]))
                      + (secondSource->m[0][2] * firstSource->m[2][2]);
    output->m[1][0] = ((secondSource->m[1][0] * firstSource->m[0][0]) + (secondSource->m[1][1] * firstSource->m[1][0]))
                      + (secondSource->m[1][2] * firstSource->m[2][0]);
    output->m[1][1] = ((secondSource->m[1][0] * firstSource->m[0][1]) + (secondSource->m[1][1] * firstSource->m[1][1]))
                      + (secondSource->m[1][2] * firstSource->m[2][1]);
    output->m[1][2] = ((secondSource->m[1][0] * firstSource->m[0][2]) + (secondSource->m[1][1] * firstSource->m[1][2]))
                      + (secondSource->m[1][2] * firstSource->m[2][2]);
    output->m[2][0] = ((secondSource->m[2][0] * firstSource->m[0][0]) + (secondSource->m[2][1] * firstSource->m[1][0]))
                      + (secondSource->m[2][2] * firstSource->m[2][0]);
    output->m[2][1] = ((secondSource->m[2][0] * firstSource->m[0][1]) + (secondSource->m[2][1] * firstSource->m[1][1]))
                      + (secondSource->m[2][2] * firstSource->m[2][1]);
    output->m[2][2] = ((secondSource->m[2][0] * firstSource->m[0][2]) + (secondSource->m[2][1] * firstSource->m[1][2]))
                      + (secondSource->m[2][2] * firstSource->m[2][2]);
    if ((firstSource == destination) || (secondSource == destination)) {
        uvMat4CopyLinear3x3(destination, &temporary);
    }
}
#line 1135 "src/modules/uvfmtx_rom.c"

#line 1136 "src/modules/uvfmtx_rom.c"
/* Apply the transposed quaternion rotation to the linear block, then
 * adjust translation so the supplied local pivot keeps its original
 * transformed position. */
void uvMat4ApplyQuaternionRotationAboutPivot(Mtx4F *transform, Vec3F *pivot, f32 quaternionX, f32 quaternionY, f32 quaternionZ, f32 quaternionW) {
    Mtx4F transposedRotation;
    Mtx4F rotation;
    Vec3F originalWorldPivot;
    Vec3F rotatedWorldPivot;

    sUvFvecExports->uvVec3FCopy(&rotatedWorldPivot, pivot);
    uvMat4TransformPoint(transform, &originalWorldPivot, &rotatedWorldPivot);
    uvMat4SetNormalizedQuaternionRotation(&rotation, quaternionX, quaternionY, quaternionZ, quaternionW);
    uvMat4TransposeLinear3x3PreservingRest(&transposedRotation, &rotation);
    uvMat4MultiplyLinear3x3(&transposedRotation, transform, &transposedRotation);
    uvMat4CopyLinear3x3(transform, &transposedRotation);
    uvMat4TransformPoint(transform, &rotatedWorldPivot, &rotatedWorldPivot);
    sUvFvecExports->uvVec3FSub(&originalWorldPivot, &originalWorldPivot, &rotatedWorldPivot);
    sUvFvecExports->uvVec3FAdd((Vec3F *) transform->m[3], (Vec3F *) transform->m[3], &originalWorldPivot);
}
#line 1152 "src/modules/uvfmtx_rom.c"

#line 1153 "src/modules/uvfmtx_rom.c"
/* Build rotation from the axis transform and caller sine/cosine, apply
 * its transpose to the linear block and adjust translation to keep
 * the supplied local pivot at the same transformed position. */
void uvMat4ApplyAxisRotationAboutPivot(Mtx4F *transform, Vec3F *pivot, Mtx4F *axisTransform, f32 sine, f32 cosine) {
    Mtx4F transposedRotation;
    Mtx4F rotation;
    Vec3F originalWorldPivot;
    Vec3F rotatedWorldPivot;

    sUvFvecExports->uvVec3FCopy(&rotatedWorldPivot, pivot);
    uvMat4TransformPoint(transform, &originalWorldPivot, &rotatedWorldPivot);
    uvMat4SetNormalizedAxisRotationFromSinCos(&rotation, axisTransform, sine, cosine);
    uvMat4TransposeLinear3x3PreservingRest(&transposedRotation, &rotation);
    uvMat4MultiplyLinear3x3(&transposedRotation, transform, &transposedRotation);
    uvMat4CopyLinear3x3(transform, &transposedRotation);
    uvMat4TransformPoint(transform, &rotatedWorldPivot, &rotatedWorldPivot);
    sUvFvecExports->uvVec3FSub(&originalWorldPivot, &originalWorldPivot, &rotatedWorldPivot);
    sUvFvecExports->uvVec3FAdd((Vec3F *) transform->m[3], (Vec3F *) transform->m[3], &originalWorldPivot);
}
#line 1169 "src/modules/uvfmtx_rom.c"

#line 1170 "src/modules/uvfmtx_rom.c"
/* Copy the alternate shared matrix at 0x00403710 to caller storage. */
void uvFmtxCopyAlternateSharedMatrix(Mtx4F *destination) {
    uvMat4FCopy(destination, &D_uvfmtx_rom_00403710);
}
#line 1173 "src/modules/uvfmtx_rom.c"
