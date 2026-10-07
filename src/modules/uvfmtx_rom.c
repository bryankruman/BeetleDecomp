// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"




void func_uvfmtx_rom_00400370(Mtx4F *m1, Mtx4F *m2);
void uvUnloadModule(s32 tag); /* extern */
void uvFmtxModuleCleanup(void);
void func_uvfmtx_rom_0040034C(f32 arg0, f32 arg1, f32 arg2);
void func_uvfmtx_rom_00400370(Mtx4F *dst, Mtx4F *m2);
void func_uvfmtx_rom_00400370(Mtx4F *m1, Mtx4F *m2);
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
s32 func_uvfmtx_rom_00401790(Mtx4F *arg0, Mtx4F *arg1);
void func_uvfmtx_rom_00401B88(Mtx4F *arg0, Mtx4F *arg1);
void func_uvfmtx_rom_00401C3C(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void func_uvfmtx_rom_00401C3C(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void uvMat4TransformPoint(Mtx4F *src, Vec3F *dst, Vec3F *vec2);
void func_uvfmtx_rom_00401DA8(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void func_uvfmtx_rom_00401DA8(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void func_uvfmtx_rom_00401F74(Mtx4F *dst, float left, float right, float top, float bottom, float near,
                              float far);
void func_uvfmtx_rom_00402038(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void uvMat4SetOrtho(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_uvfmtx_rom_004021E0(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7, f32 arg8, f32 arg9);
void func_uvfmtx_rom_0040246C(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_uvfmtx_rom_00402628(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);
void uvGfxMtxViewLoad(Mtx4F *mtxF, u16 params);
void uvMat4PushFloatMatrix(Mtx4F *mtxF);
void uvGfxMtxFViewPop(void);
void uvGfxMtxProjPushF(Mtx4F *mtxF);
void func_uvfmtx_rom_004029B8(Mtx4F *arg0);
void func_uvfmtx_rom_004029DC(Mtx4F *arg0);
void func_uvfmtx_rom_00402B30(Mtx4F *mP, f32 arg1, f32 arg2, f32 arg3);
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
void func_uvfmtx_rom_00403290(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);
void func_uvfmtx_rom_00403480(Mtx4F *arg0, Vec3F *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_uvfmtx_rom_00403568(Mtx4F *arg0, Vec3F *arg1, Mtx4F *arg2, f32 arg3, f32 arg4);
void func_uvfmtx_rom_00403648(Mtx4F *arg0);
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
    exports->func_uvfmtx_rom_0040034C = func_uvfmtx_rom_0040034C;
    exports->func_uvfmtx_rom_00400370 = func_uvfmtx_rom_00400370;
    exports->uvMat4FCopy = uvMat4FCopy;
    exports->uvMat4CopyLinear3x3 = uvMat4CopyLinear3x3;
    exports->uvMat4CopyL2F = uvMat4CopyL2F;
    exports->uvMat4CopyF2L = uvMat4CopyF2L;
    exports->uvMat4SetIdentity = uvMat4SetIdentity;
    exports->uvMat4Mul = uvMat4Mul;
    exports->func_uvfmtx_rom_00400FF8 = func_uvfmtx_rom_00400FF8;
    exports->uvFmtxModuleCleanup = uvFmtxModuleCleanup;
    exports->func_uvfmtx_rom_00401F74 = func_uvfmtx_rom_00401F74;
    exports->func_uvfmtx_rom_00402038 = func_uvfmtx_rom_00402038;
    exports->uvMat4GetYAxisAlias = uvMat4GetYAxisAlias;
    exports->uvMat4SetOrtho = uvMat4SetOrtho;
    exports->uvMat4GetTranslation = uvMat4GetTranslation;
    exports->func_uvfmtx_rom_004021E0 = func_uvfmtx_rom_004021E0;
    exports->uvMat4GetDirectionAngles = uvMat4GetDirectionAngles;
    exports->func_uvfmtx_rom_0040246C = func_uvfmtx_rom_0040246C;
    exports->uvMat4GetTranslationAndDirectionAngles = uvMat4GetTranslationAndDirectionAngles;
    exports->func_uvfmtx_rom_00402628 = func_uvfmtx_rom_00402628;
    exports->uvMat4TransformDirection = uvMat4TransformDirection;
    exports->uvGfxMtxViewLoad = uvGfxMtxViewLoad;
    exports->uvMat4TransformPointAndW = uvMat4TransformPointAndW;
    exports->uvMat4PushFloatMatrix = uvMat4PushFloatMatrix;
    exports->uvMat4TransformXY = uvMat4TransformXY;
    exports->uvGfxMtxFViewPop = uvGfxMtxFViewPop;
    exports->func_uvfmtx_rom_00403290 = func_uvfmtx_rom_00403290;
    exports->uvGfxMtxProjPushF = uvGfxMtxProjPushF;
    exports->func_uvfmtx_rom_00403480 = func_uvfmtx_rom_00403480;
    exports->func_uvfmtx_rom_00403568 = func_uvfmtx_rom_00403568;
    exports->uvMat4RotateAxis = uvMat4RotateAxis;
    exports->uvMat4LocalTranslate = uvMat4LocalTranslate;
    exports->uvMat4Scale = uvMat4Scale;
    exports->func_uvfmtx_rom_004029B8 = func_uvfmtx_rom_004029B8;
    exports->uvMat4ComposeScaleRotateTranslate = uvMat4ComposeScaleRotateTranslate;
    exports->func_uvfmtx_rom_004029DC = func_uvfmtx_rom_004029DC;
    exports->func_uvfmtx_rom_00403648 = func_uvfmtx_rom_00403648;
    exports->uvMat4InvertTranslationRotation = uvMat4InvertTranslationRotation;
    exports->func_uvfmtx_rom_00402B30 = func_uvfmtx_rom_00402B30;
    exports->func_uvfmtx_rom_00401790 = func_uvfmtx_rom_00401790;
    exports->uvMat4SetTranslation = uvMat4SetTranslation;
    exports->func_uvfmtx_rom_00401B88 = func_uvfmtx_rom_00401B88;
    exports->uvFmtxCopyVector = uvFmtxCopyVector;
    exports->func_uvfmtx_rom_00401C3C = func_uvfmtx_rom_00401C3C;
    exports->uvFmtxCopyNegatedVector = uvFmtxCopyNegatedVector;
    exports->uvMat4TransformPoint = uvMat4TransformPoint;
    exports->uvMat4GetYAxis = uvMat4GetYAxis;
    exports->func_uvfmtx_rom_00401DA8 = func_uvfmtx_rom_00401DA8;
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

void func_uvfmtx_rom_0040034C(f32 x, f32 y, f32 z) {
    sXAxis = x;
    sYAxis = y;
    sZAxis = z;
}

void func_uvfmtx_rom_00400370(Mtx4F *dst, Mtx4F *m2) {
    dst->m[0][0] = m2->m[0][0] + (m2->m[0][3] * -sXAxis);
    dst->m[0][1] = m2->m[0][1] + (m2->m[0][3] * -sYAxis);
    dst->m[0][2] = m2->m[0][2] + (m2->m[0][3] * -sZAxis);
    dst->m[1][0] = m2->m[1][0] + (m2->m[1][3] * -sXAxis);
    dst->m[1][1] = m2->m[1][1] + (m2->m[1][3] * -sYAxis);
    dst->m[1][2] = m2->m[1][2] + (m2->m[1][3] * -sZAxis);
    dst->m[2][0] = m2->m[2][0] + (m2->m[2][3] * -sXAxis);
    dst->m[2][1] = m2->m[2][1] + (m2->m[2][3] * -sYAxis);
    dst->m[2][2] = m2->m[2][2] + (m2->m[2][3] * -sZAxis);
    dst->m[3][0] = m2->m[3][0] + (m2->m[3][3] * -sXAxis);
    dst->m[3][1] = m2->m[3][1] + (m2->m[3][3] * -sYAxis);
    dst->m[3][2] = m2->m[3][2] + (m2->m[3][3] * -sZAxis);
    if (dst != m2) {
        dst->m[0][3] = m2->m[0][3];
        dst->m[1][3] = m2->m[1][3];
        dst->m[2][3] = m2->m[2][3];
        dst->m[3][3] = m2->m[3][3];
    }
}

void uvMat4FCopy(Mtx4F *dst, Mtx4F *src) {
    dst->m[0][0] = src->m[0][0];
    dst->m[0][1] = src->m[0][1];
    dst->m[0][2] = src->m[0][2];
    dst->m[0][3] = src->m[0][3];
    dst->m[1][0] = src->m[1][0];
    dst->m[1][1] = src->m[1][1];
    dst->m[1][2] = src->m[1][2];
    dst->m[1][3] = src->m[1][3];
    dst->m[2][0] = src->m[2][0];
    dst->m[2][1] = src->m[2][1];
    dst->m[2][2] = src->m[2][2];
    dst->m[2][3] = src->m[2][3];
    dst->m[3][0] = src->m[3][0];
    dst->m[3][1] = src->m[3][1];
    dst->m[3][2] = src->m[3][2];
    dst->m[3][3] = src->m[3][3];
}

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

void uvMat4CopyL2F(Mtx4F *dst, Mtx src) {
    Mtx4F *dst2 = dst;
    s32 pad;
    Mtx4F sp18;

    if (dst2 == (Mtx4F *) &src) {
        dst2 = &sp18;
    }
    dst2->m[0][0] = L2F(src, 0, 0);
    dst2->m[0][1] = L2F(src, 0, 1);
    dst2->m[0][2] = L2F(src, 0, 2);
    dst2->m[0][3] = L2F(src, 0, 3);
    dst2->m[1][0] = L2F(src, 1, 0);
    dst2->m[1][1] = L2F(src, 1, 1);
    dst2->m[1][2] = L2F(src, 1, 2);
    dst2->m[1][3] = L2F(src, 1, 3);
    dst2->m[2][0] = L2F(src, 2, 0);
    dst2->m[2][1] = L2F(src, 2, 1);
    dst2->m[2][2] = L2F(src, 2, 2);
    dst2->m[2][3] = L2F(src, 2, 3);
    dst2->m[3][0] = L2F(src, 3, 0);
    dst2->m[3][1] = L2F(src, 3, 1);
    dst2->m[3][2] = L2F(src, 3, 2);
    dst2->m[3][3] = L2F(src, 3, 3);

    if (dst2 == (Mtx4F *) &src) {
        uvMat4FCopy(dst, &sp18);
    }
}

void uvMat4CopyF2L(Mtx *dst, Mtx4F *src) {
    Mtx_u *dst2;
    Mtx spA0;
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

    dst2 = (Mtx_u *) dst;
    if ((Mtx4F *) dst2 == src) {
        dst2 = (Mtx_u *) &spA0;
    }
    xx = (s32) ((src->m[0][0] * 65536.0f) + 0.5f);
    dst2->i[0][0] = xx >> 0x10;
    dst2->f[0][0] = xx & 0xFFFF;
    yx = (s32) ((src->m[0][1] * 65536.0f) + 0.5f);
    dst2->i[0][1] = yx >> 0x10;
    dst2->f[0][1] = yx & 0xFFFF;
    zx = (s32) ((src->m[0][2] * 65536.0f) + 0.5f);
    dst2->i[0][2] = zx >> 0x10;
    dst2->f[0][2] = zx & 0xFFFF;
    wx = (s32) ((src->m[0][3] * 65536.0f) + 0.5f);
    dst2->i[0][3] = wx >> 0x10;
    dst2->f[0][3] = wx & 0xFFFF;
    xy = (s32) ((src->m[1][0] * 65536.0f) + 0.5f);
    dst2->i[1][0] = xy >> 0x10;
    dst2->f[1][0] = xy & 0xFFFF;
    yy = (s32) ((src->m[1][1] * 65536.0f) + 0.5f);
    dst2->i[1][1] = yy >> 0x10;
    dst2->f[1][1] = yy & 0xFFFF;
    zy = (s32) ((src->m[1][2] * 65536.0f) + 0.5f);
    dst2->i[1][2] = zy >> 0x10;
    dst2->f[1][2] = zy & 0xFFFF;
    wy = (s32) ((src->m[1][3] * 65536.0f) + 0.5f);
    dst2->i[1][3] = wy >> 0x10;
    dst2->f[1][3] = wy & 0xFFFF;
    xz = (s32) ((src->m[2][0] * 65536.0f) + 0.5f);
    dst2->i[2][0] = xz >> 0x10;
    dst2->f[2][0] = xz & 0xFFFF;
    yz = (s32) ((src->m[2][1] * 65536.0f) + 0.5f);
    dst2->i[2][1] = yz >> 0x10;
    dst2->f[2][1] = yz & 0xFFFF;
    zz = (s32) ((src->m[2][2] * 65536.0f) + 0.5f);
    dst2->i[2][2] = zz >> 0x10;
    dst2->f[2][2] = zz & 0xFFFF;
    wz = (s32) ((src->m[2][3] * 65536.0f) + 0.5f);
    dst2->i[2][3] = wz >> 0x10;
    dst2->f[2][3] = wz & 0xFFFF;

    // Debug code from PilotWings 64
#ifdef UV_DEBUG
    if (src->m[3][0] > 32767.0f) {
        dst2->i[3][0] = 0x7FFF;
        _uvDebugPrintf("s+12 overfow: %f\n", src->m[3][0]);
        *(s16 *) 1 = 0;
    } else if (src->m[3][0] < -32767.0f) {
        *(s16 *) &dst2->i[3][0] = -0x8000;
        _uvDebugPrintf("s+12 overfow: %f\n", src->m[3][0]);
        *(s16 *) 1 = 0;
    } else {
        xw = (s32) ((src->m[3][0] * 65536.0f) + 0.5f);
        dst2->i[3][0] = xw >> 0x10;
        dst2->f[3][0] = xw & 0xFFFF;
    }

    if (src->m[3][1] > 32767.0f) {
        dst2->i[3][1] = 0x7FFF;
        _uvDebugPrintf("s+13 overfow: %f\n", src->m[3][1]);
        *(s16 *) 1 = 0;
    } else if (src->m[3][1] < -32767.0f) {
        *(s16 *) &dst2->i[3][1] = -0x8000;
        _uvDebugPrintf("s+13 overfow: %f\n", src->m[3][1]);
        *(s16 *) 1 = 0;
    } else {
        yw = (s32) ((src->m[3][1] * 65536.0f) + 0.5f);
        dst2->i[3][1] = yw >> 0x10;
        dst2->f[3][1] = yw & 0xFFFF;
    }

    if (src->m[3][2] > 32767.0f) {
        dst2->i[3][2] = 0x7FFF;
        _uvDebugPrintf("s+14 overfow: %f\n", src->m[3][2]);
        *(s16 *) 1 = 0;
    } else if (src->m[3][2] < -32767.0f) {
        *(s16 *) &dst2->i[3][2] = -0x8000;
        _uvDebugPrintf("s+14 overfow: %f\n", src->m[3][2]);
        *(s16 *) 1 = 0;
    } else {
        zw = (s32) ((src->m[3][2] * 65536.0f) + 0.5f);
        dst2->i[3][2] = zw >> 0x10;
        dst2->f[3][2] = zw & 0xFFFF;
    }
#else
    xw = (s32) ((src->m[3][0] * 65536.0f) + 0.5f);
    dst2->i[3][0] = xw >> 0x10;
    dst2->f[3][0] = xw & 0xFFFF;

    yw = (s32) ((src->m[3][1] * 65536.0f) + 0.5f);
    dst2->i[3][1] = yw >> 0x10;
    dst2->f[3][1] = yw & 0xFFFF;

    zw = (s32) ((src->m[3][2] * 65536.0f) + 0.5f);
    dst2->i[3][2] = zw >> 0x10;
    dst2->f[3][2] = zw & 0xFFFF;
#endif
    ww = (s32) ((src->m[3][3] * 65536.0f) + 0.5f);
    dst2->i[3][3] = ww >> 0x10;
    dst2->f[3][3] = ww & 0xFFFF;
    if ((Mtx4F *) dst2 == src) {
        sUvImtxExports->uvIMtxCopy(dst, spA0);
    }
}

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

void uvMat4Mul(Mtx4F *dst, Mtx4F *src2, Mtx4F *src1) {
    float unused1, unused2; // stack
    Mtx4F *pdst;
    Mtx4F temp;

    pdst = dst;
    if (src2 == dst || src1 == dst) {
        pdst = &temp;
    }
    pdst->m[0][0] = src1->m[0][0] * src2->m[0][0] + src1->m[0][1] * src2->m[1][0]
                    + src1->m[0][2] * src2->m[2][0] + src1->m[0][3] * src2->m[3][0];
    pdst->m[0][1] = src1->m[0][0] * src2->m[0][1] + src1->m[0][1] * src2->m[1][1]
                    + src1->m[0][2] * src2->m[2][1] + src1->m[0][3] * src2->m[3][1];
    pdst->m[0][2] = src1->m[0][0] * src2->m[0][2] + src1->m[0][1] * src2->m[1][2]
                    + src1->m[0][2] * src2->m[2][2] + src1->m[0][3] * src2->m[3][2];
    pdst->m[0][3] = src1->m[0][0] * src2->m[0][3] + src1->m[0][1] * src2->m[1][3]
                    + src1->m[0][2] * src2->m[2][3] + src1->m[0][3] * src2->m[3][3];
    pdst->m[1][0] = src1->m[1][0] * src2->m[0][0] + src1->m[1][1] * src2->m[1][0]
                    + src1->m[1][2] * src2->m[2][0] + src1->m[1][3] * src2->m[3][0];
    pdst->m[1][1] = src1->m[1][0] * src2->m[0][1] + src1->m[1][1] * src2->m[1][1]
                    + src1->m[1][2] * src2->m[2][1] + src1->m[1][3] * src2->m[3][1];
    pdst->m[1][2] = src1->m[1][0] * src2->m[0][2] + src1->m[1][1] * src2->m[1][2]
                    + src1->m[1][2] * src2->m[2][2] + src1->m[1][3] * src2->m[3][2];
    pdst->m[1][3] = src1->m[1][0] * src2->m[0][3] + src1->m[1][1] * src2->m[1][3]
                    + src1->m[1][2] * src2->m[2][3] + src1->m[1][3] * src2->m[3][3];
    pdst->m[2][0] = src1->m[2][0] * src2->m[0][0] + src1->m[2][1] * src2->m[1][0]
                    + src1->m[2][2] * src2->m[2][0] + src1->m[2][3] * src2->m[3][0];
    pdst->m[2][1] = src1->m[2][0] * src2->m[0][1] + src1->m[2][1] * src2->m[1][1]
                    + src1->m[2][2] * src2->m[2][1] + src1->m[2][3] * src2->m[3][1];
    pdst->m[2][2] = src1->m[2][0] * src2->m[0][2] + src1->m[2][1] * src2->m[1][2]
                    + src1->m[2][2] * src2->m[2][2] + src1->m[2][3] * src2->m[3][2];
    pdst->m[2][3] = src1->m[2][0] * src2->m[0][3] + src1->m[2][1] * src2->m[1][3]
                    + src1->m[2][2] * src2->m[2][3] + src1->m[2][3] * src2->m[3][3];
    pdst->m[3][0] = src1->m[3][0] * src2->m[0][0] + src1->m[3][1] * src2->m[1][0]
                    + src1->m[3][2] * src2->m[2][0] + src1->m[3][3] * src2->m[3][0];
    pdst->m[3][1] = src1->m[3][0] * src2->m[0][1] + src1->m[3][1] * src2->m[1][1]
                    + src1->m[3][2] * src2->m[2][1] + src1->m[3][3] * src2->m[3][1];
    pdst->m[3][2] = src1->m[3][0] * src2->m[0][2] + src1->m[3][1] * src2->m[1][2]
                    + src1->m[3][2] * src2->m[2][2] + src1->m[3][3] * src2->m[3][2];
    pdst->m[3][3] = src1->m[3][0] * src2->m[0][3] + src1->m[3][1] * src2->m[1][3]
                    + src1->m[3][2] * src2->m[2][3] + src1->m[3][3] * src2->m[3][3];
    if (src2 == dst || src1 == dst) {
        uvMat4FCopy(dst, &temp);
    }
}

void func_uvfmtx_rom_00400FF8(s32 arg0) {
}

void uvMat4RotateAxis(Mtx4F *dst, float angle, char axis) {
    float sp6C;
    float fv0;
    float unused1;
    float unused2;
    Mtx4F temp;

    if (angle != 0.0f) {
        sp6C = sUvMathExports->uvSinF(angle);
        fv0 = sUvMathExports->uvCosF(angle);
        switch (axis) {
            case 'x':
                temp.m[0][0] = dst->m[0][0];
                temp.m[0][1] = dst->m[0][1];
                temp.m[0][2] = dst->m[0][2];
                temp.m[0][3] = dst->m[0][3];
                temp.m[1][0] = (fv0 * dst->m[1][0]) + (sp6C * dst->m[2][0]);
                temp.m[1][1] = (fv0 * dst->m[1][1]) + (sp6C * dst->m[2][1]);
                temp.m[1][2] = (fv0 * dst->m[1][2]) + (sp6C * dst->m[2][2]);
                temp.m[1][3] = (fv0 * dst->m[1][3]) + (sp6C * dst->m[2][3]);
                temp.m[2][0] = (fv0 * dst->m[2][0]) - (sp6C * dst->m[1][0]);
                temp.m[2][1] = (fv0 * dst->m[2][1]) - (sp6C * dst->m[1][1]);
                temp.m[2][2] = (fv0 * dst->m[2][2]) - (sp6C * dst->m[1][2]);
                temp.m[2][3] = (fv0 * dst->m[2][3]) - (sp6C * dst->m[1][3]);
                temp.m[3][0] = dst->m[3][0];
                temp.m[3][1] = dst->m[3][1];
                temp.m[3][2] = dst->m[3][2];
                temp.m[3][3] = dst->m[3][3];
                goto copy;
            case 'y':
                temp.m[0][0] = (fv0 * dst->m[0][0]) - (sp6C * dst->m[2][0]);
                temp.m[0][1] = (fv0 * dst->m[0][1]) - (sp6C * dst->m[2][1]);
                temp.m[0][2] = (fv0 * dst->m[0][2]) - (sp6C * dst->m[2][2]);
                temp.m[0][3] = (fv0 * dst->m[0][3]) - (sp6C * dst->m[2][3]);
                temp.m[1][0] = dst->m[1][0];
                temp.m[1][1] = dst->m[1][1];
                temp.m[1][2] = dst->m[1][2];
                temp.m[1][3] = dst->m[1][3];
                temp.m[2][0] = (sp6C * dst->m[0][0]) + (fv0 * dst->m[2][0]);
                temp.m[2][1] = (sp6C * dst->m[0][1]) + (fv0 * dst->m[2][1]);
                temp.m[2][2] = (sp6C * dst->m[0][2]) + (fv0 * dst->m[2][2]);
                temp.m[2][3] = (sp6C * dst->m[0][3]) + (fv0 * dst->m[2][3]);
                temp.m[3][0] = dst->m[3][0];
                temp.m[3][1] = dst->m[3][1];
                temp.m[3][2] = dst->m[3][2];
                temp.m[3][3] = dst->m[3][3];
                goto copy;
            case 'z':
                temp.m[0][0] = (fv0 * dst->m[0][0]) + (sp6C * dst->m[1][0]);
                temp.m[0][1] = (fv0 * dst->m[0][1]) + (sp6C * dst->m[1][1]);
                temp.m[0][2] = (fv0 * dst->m[0][2]) + (sp6C * dst->m[1][2]);
                temp.m[0][3] = (fv0 * dst->m[0][3]) + (sp6C * dst->m[1][3]);
                temp.m[1][0] = (fv0 * dst->m[1][0]) - (sp6C * dst->m[0][0]);
                temp.m[1][1] = (fv0 * dst->m[1][1]) - (sp6C * dst->m[0][1]);
                temp.m[1][2] = (fv0 * dst->m[1][2]) - (sp6C * dst->m[0][2]);
                temp.m[1][3] = (fv0 * dst->m[1][3]) - (sp6C * dst->m[0][3]);
                temp.m[2][0] = dst->m[2][0];
                temp.m[2][1] = dst->m[2][1];
                temp.m[2][2] = dst->m[2][2];
                temp.m[2][3] = dst->m[2][3];
                temp.m[3][0] = dst->m[3][0];
                temp.m[3][1] = dst->m[3][1];
                temp.m[3][2] = dst->m[3][2];
                temp.m[3][3] = dst->m[3][3];
            copy: // New engine, new evil code...
                uvMat4FCopy(dst, &temp);
                break;
        }
    }
}

void uvMat4LocalTranslate(Mtx4F* m, f32 x, f32 y, f32 z) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_ft4;
    f32 temp_ft0;

    temp_fv0 = (x * m->m[0][0]) + (y * m->m[1][0]) + (z * m->m[2][0]) + m->m[3][0];
    temp_fv1 = (x * m->m[0][1]) + (y * m->m[1][1]) + (z * m->m[2][1]) + m->m[3][1];
    temp_ft4 = (x * m->m[0][2]) + (y * m->m[1][2]) + (z * m->m[2][2]) + m->m[3][2];
    temp_ft0 = (x * m->m[0][3]) + (y * m->m[1][3]) + (z * m->m[2][3]) + m->m[3][3];

    m->m[3][0] = temp_fv0;
    m->m[3][1] = temp_fv1;
    m->m[3][2] = temp_ft4;
    m->m[3][3] = temp_ft0;
}

void uvMat4Scale(Mtx4F *m, f32 scaleX, f32 scaleY, f32 scaleZ) {
    m->m[0][0] *= scaleX;
    m->m[0][1] *= scaleX;
    m->m[0][2] *= scaleX;
    m->m[0][3] *= scaleX;
    m->m[1][0] *= scaleY;
    m->m[1][1] *= scaleY;
    m->m[1][2] *= scaleY;
    m->m[1][3] *= scaleY;
    m->m[2][0] *= scaleZ;
    m->m[2][1] *= scaleZ;
    m->m[2][2] *= scaleZ;
    m->m[2][3] *= scaleZ;
}

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

void uvMat4InvertTranslationRotation(Mtx4F *dst, Mtx4F *mat2) {
    Mtx4F sp50;
    s32 i;
    s32 j;

    uvMat4FCopy(&sp50, mat2);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < i; j++) {
            sp50.m[i][j] = mat2->m[j][i];
            sp50.m[j][i] = mat2->m[i][j];
        }
    }

    sp50.m[3][0] = 0.0f;
    sp50.m[3][1] = 0.0f;
    sp50.m[3][2] = 0.0f;
    uvMat4LocalTranslate(&sp50, -mat2->m[3][0], -mat2->m[3][1], -mat2->m[3][2]);
    uvMat4FCopy(dst, &sp50);
}

s32 func_uvfmtx_rom_00401790(Mtx4F* arg0, Mtx4F* arg1) {
    f64 temp_fv0;
    f64 var_fa0;
    f64 var_fv1;
    f32 temp_fa0;
    s32 pad[2];

    var_fv1 = 0.0;
    var_fa0 = 0.0;
    temp_fv0 = ((arg1->m[0][0] * arg1->m[1][1]) * arg1->m[2][2]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = ((arg1->m[0][1] * arg1->m[1][2]) * arg1->m[2][0]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = ((arg1->m[0][2] * arg1->m[1][0]) * arg1->m[2][1]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = ((-arg1->m[0][2] * arg1->m[1][1]) * arg1->m[2][0]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = ((-arg1->m[0][1] * arg1->m[1][0]) * arg1->m[2][2]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = ((-arg1->m[0][0] * arg1->m[1][2]) * arg1->m[2][1]);
    if (temp_fv0 >= 0.0) {
        var_fa0 += temp_fv0;
    } else {
        var_fv1 += temp_fv0;
    }
    temp_fv0 = var_fa0 + var_fv1;
    if ((temp_fv0 == 0) || (var_fa0 == var_fv1)) {
        return 0;
    }
    temp_fa0 = 1.0 / temp_fv0;
    arg0->m[0][0] = ((arg1->m[1][1] * arg1->m[2][2]) - (arg1->m[1][2] * arg1->m[2][1])) * temp_fa0;
    arg0->m[1][0] = -((arg1->m[1][0] * arg1->m[2][2]) - (arg1->m[1][2] * arg1->m[2][0])) * temp_fa0;
    arg0->m[2][0] = ((arg1->m[1][0] * arg1->m[2][1]) - (arg1->m[1][1] * arg1->m[2][0])) * temp_fa0;
    arg0->m[0][1] = -((arg1->m[0][1] * arg1->m[2][2]) - (arg1->m[0][2] * arg1->m[2][1])) * temp_fa0;
    arg0->m[1][1] = ((arg1->m[0][0] * arg1->m[2][2]) - (arg1->m[0][2] * arg1->m[2][0])) * temp_fa0;
    arg0->m[2][1] = -((arg1->m[0][0] * arg1->m[2][1]) - (arg1->m[0][1] * arg1->m[2][0])) * temp_fa0;
    arg0->m[0][2] = ((arg1->m[0][1] * arg1->m[1][2]) - (arg1->m[0][2] * arg1->m[1][1])) * temp_fa0;
    arg0->m[1][2] = -((arg1->m[0][0] * arg1->m[1][2]) - (arg1->m[0][2] * arg1->m[1][0])) * temp_fa0;
    arg0->m[2][2] = ((arg1->m[0][0] * arg1->m[1][1]) - (arg1->m[0][1] * arg1->m[1][0])) * temp_fa0;
    arg0->m[3][0] = -(((arg1->m[3][0] * arg0->m[0][0]) + (arg1->m[3][1] * arg0->m[1][0]) + (arg1->m[3][2] * arg0->m[2][0])));
    arg0->m[3][1] = -(((arg1->m[3][0] * arg0->m[0][1]) + (arg1->m[3][1] * arg0->m[1][1]) + (arg1->m[3][2] * arg0->m[2][1])));
    arg0->m[3][2] = -(((arg1->m[3][0] * arg0->m[0][2]) + (arg1->m[3][1] * arg0->m[1][2]) + (arg1->m[3][2] * arg0->m[2][2])));
    arg0->m[2][3] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[0][3] = 0.0f;
    arg0->m[3][3] = 1.0f;
    return 1;
}

void func_uvfmtx_rom_00401B88(Mtx4F *arg0, Mtx4F *arg1) {
    s32 pad;
    Mtx4F *var_v0;
    Mtx4F sp18;

    var_v0 = arg0;
    if (arg1 == arg0) {
        var_v0 = &sp18;
    }
    var_v0->m[0][0] = arg1->m[0][0];
    var_v0->m[0][3] = arg1->m[0][3];
    var_v0->m[1][1] = arg1->m[1][1];
    var_v0->m[1][3] = arg1->m[1][3];
    var_v0->m[2][2] = arg1->m[2][2];
    var_v0->m[2][3] = arg1->m[2][3];
    var_v0->m[3][0] = arg1->m[3][0];
    var_v0->m[3][1] = arg1->m[3][1];
    var_v0->m[3][2] = arg1->m[3][2];
    var_v0->m[3][3] = arg1->m[3][3];
    var_v0->m[0][1] = arg1->m[1][0];
    var_v0->m[0][2] = arg1->m[2][0];
    var_v0->m[1][0] = arg1->m[0][1];
    var_v0->m[1][2] = arg1->m[2][1];
    var_v0->m[2][0] = arg1->m[0][2];
    var_v0->m[2][1] = arg1->m[1][2];
    if (var_v0 == &sp18) {
        uvMat4FCopy(arg0, &sp18);
    }
}

void func_uvfmtx_rom_00401C3C(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3);

void func_uvfmtx_rom_00401C3C(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3) {
    if (arg2)
        ; // FAKE
    arg0->m[0][0] = arg1->m[0][0] * (arg3 * ((1.0f / arg2)));
    arg0->m[0][1] = arg1->m[0][1] * (arg3 * (1.0f / arg2));
    arg0->m[0][2] = arg1->m[0][2] * (arg3 * (1.0f / arg2));
    arg0->m[0][3] = arg1->m[0][3];
    arg0->m[1][0] = arg1->m[1][0] * (arg3 * (1.0f / arg2));
    arg0->m[1][1] = arg1->m[1][1] * (arg3 * (1.0f / arg2));
    arg0->m[1][2] = arg1->m[1][2] * (arg3 * (1.0f / arg2));
    arg0->m[1][3] = arg1->m[1][3];
    arg0->m[2][0] = arg1->m[2][0] * (arg3 * (1.0f / arg2));
    arg0->m[2][1] = arg1->m[2][1] * (arg3 * (1.0f / arg2));
    arg0->m[2][2] = arg1->m[2][2] * (arg3 * (1.0f / arg2));
    arg0->m[2][3] = arg1->m[2][3];
    arg0->m[3][0] = arg1->m[3][0] * (1.0f / arg2);
    arg0->m[3][1] = arg1->m[3][1] * (1.0f / arg2);
    arg0->m[3][2] = arg1->m[3][2] * (1.0f / arg2);
    arg0->m[3][3] = arg1->m[3][3];
}

void func_uvfmtx_rom_00401DA8(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2);

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

void func_uvfmtx_rom_00401DA8(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2) {
    Vec3F sp44;
    Vec3F sp38;
    Vec3F sp2C;

    sp44.x = arg1->m[3][0] - arg2->m[3][0];
    sp44.y = arg1->m[3][1] - arg2->m[3][1];
    sp44.z = arg1->m[3][2] - arg2->m[3][2];
    if (sUvFvecExports->uvVec3FNormalize((Vec3F *) &sp44, (Vec3F *) &sp44) != 0) {
        sp38.x = arg2->m[2][0];
        sp38.y = arg2->m[2][1];
        sp38.z = arg2->m[2][2];
        sUvFvecExports->uvVec3FCross(&sp2C, (Vec3F *) &sp44, (Vec3F *) &sp38);
        if (sUvFvecExports->uvVec3FNormalize(&sp2C, &sp2C) == 0) {
            sp2C.x = arg2->m[0][0];
            sp2C.y = arg2->m[0][1];
            sp2C.z = 0.0f;
            sUvFvecExports->uvVec3FNormalize(&sp2C, &sp2C);
        }
        sUvFvecExports->uvVec3FCross((Vec3F *) &sp38, &sp2C, (Vec3F *) &sp44);
        sUvFvecExports->uvVec3FNormalize((Vec3F *) &sp38, (Vec3F *) &sp38);
        arg0->m[0][0] = (f32) sp2C.x;
        arg0->m[0][1] = sp2C.y;
        arg0->m[0][2] = sp2C.z;
        arg0->m[1][0] = sp44.x;
        arg0->m[1][1] = sp44.y;
        arg0->m[1][2] = sp44.z;
        arg0->m[2][0] = sp38.x;
        arg0->m[2][1] = sp38.y;
        arg0->m[2][2] = sp38.z;
        arg0->m[3][0] = arg2->m[3][0];
        arg0->m[3][1] = arg2->m[3][1];
        arg0->m[3][2] = arg2->m[3][2];
        arg0->m[0][3] = 0.0f;
        arg0->m[1][3] = 0.0f;
        arg0->m[2][3] = 0.0f;
        arg0->m[3][3] = 1.0f;
    }
}

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

void func_uvfmtx_rom_00402038(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 temp_fv1;
    Mtx4F *new_var;
    new_var = arg0;
    new_var->m[0][0] = 2.0f / (arg2 - arg1);
    new_var->m[1][1] = 2.0f / (arg4 - arg3);
    temp_fv1 = arg5;
    new_var->m[2][2] = (-2.0f) / (arg6 - temp_fv1);
    new_var->m[3][0] = (-(arg2 + arg1)) / (arg2 - arg1);
    new_var->m[3][1] = (-(arg4 + arg3)) / (arg4 - arg3);
    new_var->m[3][2] = (-(arg6 + temp_fv1)) / (arg6 - temp_fv1);
    new_var->m[0][1] = 0.0f;
    new_var->m[0][2] = 0.0f;
    new_var->m[0][3] = 0.0f;
    new_var->m[1][0] = 0.0f;
    new_var->m[1][2] = 0.0f;
    new_var->m[1][3] = 0.0f;
    new_var->m[2][0] = 0.0f;
    new_var->m[2][1] = 0.0f;
    new_var->m[2][3] = 0.0f;
    new_var->m[3][3] = 1.0f;
}

void uvMat4SetOrtho(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg0->m[0][0] = 2.0f / (arg2 - arg1);
    arg0->m[1][1] = 2.0f / (arg4 - arg3);
    arg0->m[2][2] = -1.0f;
    arg0->m[3][0] = -(arg2 + arg1) / (arg2 - arg1);
    arg0->m[3][1] = -(arg4 + arg3) / (arg4 - arg3);

    arg0->m[0][1] = 0.0f;
    arg0->m[0][2] = 0.0f;
    arg0->m[0][3] = 0.0f;
    arg0->m[1][0] = 0.0f;
    arg0->m[1][2] = 0.0f;
    arg0->m[1][3] = 0.0f;
    arg0->m[2][0] = 0.0f;
    arg0->m[2][1] = 0.0f;
    arg0->m[2][3] = 0.0f;
    arg0->m[3][2] = 0.0f;
    arg0->m[3][3] = 1.0f;
    uvMat4RotateAxis(arg0, 1.5707963f, 0x78);
}

void func_uvfmtx_rom_004021E0(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7, f32 arg8, f32 arg9) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs5;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv1;

    temp_fs0 = arg4 - arg1;
    temp_fs1 = arg5 - arg2;
    temp_fs2 = arg6 - arg3;
    temp_fv1 = -1.0f / sqrtf(SQ(temp_fs0) + SQ(temp_fs1) + SQ(temp_fs2));
    temp_fs0 *= temp_fv1;
    temp_fs1 *= temp_fv1;
    temp_fs2 *= temp_fv1;

    temp_fs3 = (arg8 * temp_fs2) - (arg9 * temp_fs1);
    temp_fs4 = (arg9 * temp_fs0) - (arg7 * temp_fs2);
    temp_fs5 = (arg7 * temp_fs1) - (arg8 * temp_fs0);

    temp_fv1 = 1.0f / sqrtf(SQ(temp_fs3) + SQ(temp_fs4) + SQ(temp_fs5));
    temp_fs3 *= temp_fv1;
    temp_fs4 *= temp_fv1;
    temp_fs5 *= temp_fv1;

    arg7 = (temp_fs1 * temp_fs5) - (temp_fs2 * temp_fs4);
    arg8 = (temp_fs2 * temp_fs3) - (temp_fs0 * temp_fs5);
    arg9 = (temp_fs0 * temp_fs4) - (temp_fs1 * temp_fs3);

    temp_fv1 = 1.0f / sqrtf(SQ(arg7) + SQ(arg8) + SQ(arg9));
    arg7 *= temp_fv1;
    arg8 *= temp_fv1;
    arg9 *= temp_fv1;

    arg0->m[0][0] = temp_fs3;
    arg0->m[1][0] = temp_fs4;
    arg0->m[2][0] = temp_fs5;
    arg0->m[3][0] = -((arg1 * temp_fs3) + (arg2 * temp_fs4) + (arg3 * temp_fs5));
    arg0->m[0][1] = arg7;
    arg0->m[1][1] = arg8;
    arg0->m[2][1] = arg9;
    arg0->m[3][1] = -((arg1 * arg7) + (arg2 * arg8) + (arg3 * arg9));
    arg0->m[0][2] = temp_fs0;
    arg0->m[1][2] = temp_fs1;
    arg0->m[2][2] = temp_fs2;
    arg0->m[3][2] = -((arg1 * temp_fs0) + (arg2 * temp_fs1) + (arg3 * temp_fs2));
    arg0->m[0][3] = 0;
    arg0->m[1][3] = 0;
    arg0->m[2][3] = 0;
    arg0->m[3][3] = 1.0f;
}

// temp-less function
void func_uvfmtx_rom_0040246C(Mtx4F *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    arg0->m[0][0] = 1.0f - (2.0f * (SQ(arg2) + SQ(arg3)));
    arg0->m[0][1] = 2.0f * ((arg1 * arg2) - (arg3 * arg4));
    arg0->m[0][2] = 2.0f * ((arg3 * arg1) + (arg2 * arg4));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &arg0->m[0][0], (Vec3F *) &arg0->m[0][0]);
    arg0->m[1][0] = 2.0f * ((arg1 * arg2) + (arg3 * arg4));
    arg0->m[1][1] = 1.0f - (2.0f * (SQ(arg3) + (arg1 * arg1)));
    arg0->m[1][2] = 2.0f * ((arg2 * arg3) - (arg1 * arg4));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &arg0->m[1][0], (Vec3F *) &arg0->m[1][0]);
    arg0->m[2][0] = 2.0f * ((arg3 * arg1) - (arg2 * arg4));
    arg0->m[2][1] = 2.0f * ((arg2 * arg3) + (arg1 * arg4));
    arg0->m[2][2] = 1.0f - (2.0f * (SQ(arg2) + (arg1 * arg1)));
    sUvFvecExports->uvVec3FNormalize((Vec3F *) &arg0->m[2][0], (Vec3F *) &arg0->m[2][0]);
}

void func_uvfmtx_rom_00402628(Mtx4F *arg0, Mtx4F *arg1, f32 arg2, f32 arg3) {
    f32 temp_fv0;
    Vec3F sp40;
    Vec3F sp34;

    temp_fv0 = (1.0f - arg3);
    sp40.z = arg1->m[0][1] * (arg1->m[0][0] * temp_fv0);
    sp40.y = arg1->m[0][2] * (arg1->m[0][1] * temp_fv0);
    sp40.x = arg1->m[0][0] * (arg1->m[0][2] * temp_fv0);
    sUvFvecExports->uvVec3FScale(&sp34, (Vec3F *) arg1, arg2);
    arg0->m[0][0] = (SQ(arg1->m[0][0]) * temp_fv0) + arg3;
    arg0->m[0][1] = sp40.z - sp34.z;
    arg0->m[0][2] = sp40.x + sp34.y;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) arg0->m[0], (Vec3F *) arg0->m[0]);
    arg0->m[1][0] = sp40.z + sp34.z;
    arg0->m[1][1] = (SQ(arg1->m[0][1]) * temp_fv0) + arg3;
    arg0->m[1][2] = sp40.y - sp34.x;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) arg0->m[1], (Vec3F *) arg0->m[1]);
    arg0->m[2][0] = sp40.x - sp34.y;
    arg0->m[2][1] = sp40.y + sp34.x;
    arg0->m[2][2] = (SQ(arg1->m[0][2]) * temp_fv0) + arg3;
    sUvFvecExports->uvVec3FNormalize((Vec3F *) arg0->m[2], (Vec3F *) arg0->m[2]);
}

void uvGfxMtxViewLoad(Mtx4F *mtxF, u16 params) {
    Mtx mtx;

    uvMat4CopyF2L(&mtx, mtxF);
    sUvImtxExports->uvIMtxPush(mtx, params);
}

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

void uvGfxMtxProjPushF(Mtx4F *mtxF) {
    Mtx mtx;

    uvMat4FCopy(&D_uvfmtx_rom_004036D0, mtxF);
    uvMat4Mul(&D_uvfmtx_rom_00403710, &D_uvfmtx_rom_004036D0, &D_uvfmtx_rom_00403690);
    uvMat4CopyF2L(&mtx, &D_uvfmtx_rom_00403710);
    sUvImtxExports->func_uvimtx_rom_004004D8(mtx);
}

void func_uvfmtx_rom_004029B8(Mtx4F *arg0) {
    uvMat4FCopy(arg0, &D_uvfmtx_rom_00403690);
}

void func_uvfmtx_rom_004029DC(Mtx4F *arg0) {
    Mtx sp88;
    Mtx4F sp48;

    uvMat4FCopy(&D_uvfmtx_rom_00403690, arg0);
    uvMat4SetIdentity(&sp48);
    uvMat4RotateAxis(&sp48, -1.5707963f, 0x78);
    uvMat4Mul(&D_uvfmtx_rom_00403690, &sp48, &D_uvfmtx_rom_00403690);
    uvMat4Mul(&D_uvfmtx_rom_00403710, &D_uvfmtx_rom_004036D0, &D_uvfmtx_rom_00403690);
    uvMat4CopyF2L(&sp88, &D_uvfmtx_rom_00403710);
    sUvImtxExports->func_uvimtx_rom_004004D8(sp88);
    sUvImtxExports->uvIMtxSetIdentity(&sp88);
    sUvImtxExports->func_uvimtx_rom_00400410(sp88);
}

void func_uvfmtx_rom_00402B30(Mtx4F *mP, f32 arg1, f32 arg2, f32 arg3) {
    f32 var_fa0;
    f32 var_ft4;
    f32 var_fa1;
    f32 var_fs1;
    f32 var_ft5;
    f32 var_fv1;
    f32 var_fs2;
    f32 var_fs3;

    if (arg1 == 0.0f) {
        var_fs2 = 1.0f;
        var_fs3 = 0.0f;
    } else {
        var_fs3 = sUvMathExports->uvSinF(arg1);
        var_fs2 = sUvMathExports->uvCosF(arg1);
    }
    if (arg2 == 0.0f) {
        var_fa1 = 1.0f;
        var_fs1 = 0.0f;
    } else {
        do {
            var_fs1 = sUvMathExports->uvSinF(arg2);
        } while (0); // FAKE
        var_fa1 = sUvMathExports->uvCosF(arg2);
    }
    if (arg3 == 0.0f) {
        var_fa0 = 1.0f;
        var_fv1 = 0.0f;
        var_ft4 = 0.0f;
        var_ft5 = var_fs1;
    } else {
        var_fv1 = sUvMathExports->uvSinF(arg3);
        var_fa0 = sUvMathExports->uvCosF(arg3);
        var_ft4 = var_fv1 * var_fs1;
        var_ft5 = var_fa0 * var_fs1;
    }
    mP->m[3][0] = 0.0f;
    mP->m[3][1] = 0.0f;
    mP->m[1][2] = var_fs1;
    mP->m[3][2] = 0.0f;
    mP->m[0][3] = 0.0f;
    mP->m[1][3] = 0.0f;
    mP->m[2][3] = 0.0f;
    mP->m[0][0] = (var_fa0 * var_fs2) - (var_ft4 * var_fs3);
    mP->m[1][0] = -var_fa1 * var_fs3;
    mP->m[2][0] = (var_fv1 * var_fs2) + (var_ft5 * var_fs3);
    mP->m[0][1] = (var_fa0 * var_fs3) + (var_ft4 * var_fs2);
    mP->m[1][1] = var_fa1 * var_fs2;
    mP->m[2][1] = (var_fv1 * var_fs3) - (var_ft5 * var_fs2);
    mP->m[0][2] = -var_fv1 * var_fa1;
    mP->m[2][2] = var_fa0 * var_fa1;
    mP->m[3][3] = 1.0f;
}

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
void uvMat4GetTranslationAndDirectionAngles(Mtx4F *matrix, Vec3F *translation, Vec3F *angles) {
    f32 temp_fa1;
    f32 temp_fv1;

    angles->x = sUvMathExports->uvAtan2F(-matrix->m[1][0], matrix->m[1][1]);
    temp_fv1 = matrix->m[1][0];
    temp_fa1 = matrix->m[1][1];
    angles->y = sUvMathExports->uvAtan2F(matrix->m[1][2], sUvMathExports->uvSqrtf(SQ(temp_fa1) + SQ(temp_fv1)));
    angles->z = sUvMathExports->uvAtan2F(-matrix->m[0][2], matrix->m[2][2]);
    translation->x = matrix->m[3][0];
    translation->y = matrix->m[3][1];
    translation->z = matrix->m[3][2];
}
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

void func_uvfmtx_rom_00403290(Mtx4F *arg0, Mtx4F *arg1, Mtx4F *arg2) {
    s32 pad[2];
    Mtx4F *var_v0;
    Mtx4F sp1C;

    var_v0 = arg0;
    if ((arg1 == arg0) || (arg2 == arg0)) {
        var_v0 = &sp1C;
    }
    var_v0->m[0][0] = ((arg2->m[0][0] * arg1->m[0][0]) + (arg2->m[0][1] * arg1->m[1][0]))
                      + (arg2->m[0][2] * arg1->m[2][0]);
    var_v0->m[0][1] = ((arg2->m[0][0] * arg1->m[0][1]) + (arg2->m[0][1] * arg1->m[1][1]))
                      + (arg2->m[0][2] * arg1->m[2][1]);
    var_v0->m[0][2] = ((arg2->m[0][0] * arg1->m[0][2]) + (arg2->m[0][1] * arg1->m[1][2]))
                      + (arg2->m[0][2] * arg1->m[2][2]);
    var_v0->m[1][0] = ((arg2->m[1][0] * arg1->m[0][0]) + (arg2->m[1][1] * arg1->m[1][0]))
                      + (arg2->m[1][2] * arg1->m[2][0]);
    var_v0->m[1][1] = ((arg2->m[1][0] * arg1->m[0][1]) + (arg2->m[1][1] * arg1->m[1][1]))
                      + (arg2->m[1][2] * arg1->m[2][1]);
    var_v0->m[1][2] = ((arg2->m[1][0] * arg1->m[0][2]) + (arg2->m[1][1] * arg1->m[1][2]))
                      + (arg2->m[1][2] * arg1->m[2][2]);
    var_v0->m[2][0] = ((arg2->m[2][0] * arg1->m[0][0]) + (arg2->m[2][1] * arg1->m[1][0]))
                      + (arg2->m[2][2] * arg1->m[2][0]);
    var_v0->m[2][1] = ((arg2->m[2][0] * arg1->m[0][1]) + (arg2->m[2][1] * arg1->m[1][1]))
                      + (arg2->m[2][2] * arg1->m[2][1]);
    var_v0->m[2][2] = ((arg2->m[2][0] * arg1->m[0][2]) + (arg2->m[2][1] * arg1->m[1][2]))
                      + (arg2->m[2][2] * arg1->m[2][2]);
    if ((arg1 == arg0) || (arg2 == arg0)) {
        uvMat4CopyLinear3x3(arg0, &sp1C);
    }
}

void func_uvfmtx_rom_00403480(Mtx4F *arg0, Vec3F *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    Mtx4F sp88;
    Mtx4F sp48;
    Vec3F sp3C;
    Vec3F sp30;

    sUvFvecExports->uvVec3FCopy(&sp30, arg1);
    uvMat4TransformPoint(arg0, &sp3C, &sp30);
    func_uvfmtx_rom_0040246C(&sp48, arg2, arg3, arg4, arg5);
    func_uvfmtx_rom_00401B88(&sp88, &sp48);
    func_uvfmtx_rom_00403290(&sp88, arg0, &sp88);
    uvMat4CopyLinear3x3(arg0, &sp88);
    uvMat4TransformPoint(arg0, &sp30, &sp30);
    sUvFvecExports->uvVec3FSub(&sp3C, &sp3C, &sp30);
    sUvFvecExports->uvVec3FAdd((Vec3F *) arg0->m[3], (Vec3F *) arg0->m[3], &sp3C);
}

void func_uvfmtx_rom_00403568(Mtx4F *arg0, Vec3F *arg1, Mtx4F *arg2, f32 arg3, f32 arg4) {
    Mtx4F sp80;
    Mtx4F sp40;
    Vec3F sp34;
    Vec3F sp28;

    sUvFvecExports->uvVec3FCopy(&sp28, arg1);
    uvMat4TransformPoint(arg0, &sp34, &sp28);
    func_uvfmtx_rom_00402628(&sp40, arg2, arg3, arg4);
    func_uvfmtx_rom_00401B88(&sp80, &sp40);
    func_uvfmtx_rom_00403290(&sp80, arg0, &sp80);
    uvMat4CopyLinear3x3(arg0, &sp80);
    uvMat4TransformPoint(arg0, &sp28, &sp28);
    sUvFvecExports->uvVec3FSub(&sp34, &sp34, &sp28);
    sUvFvecExports->uvVec3FAdd((Vec3F *) arg0->m[3], (Vec3F *) arg0->m[3], &sp34);
}

void func_uvfmtx_rom_00403648(Mtx4F *arg0) {
    uvMat4FCopy(arg0, &D_uvfmtx_rom_00403710);
}
