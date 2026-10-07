// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#include "module.h"

extern u32 D_uvmath_rom_00400AF0;

//void uvUpdateFileAllocPtr(void*);
void __entrypoint_func_uvmath_rom_400000(UvMath_Exports* exports);
void func_uvmath_rom_00400108(void);
f32 uvSqrtF(f32 arg0);
f32 uvSinF(f32);
f32 uvCosF(f32);
f32 uvTanF(f32);
f32 uvLength2D(f32, f32);
f32 uvLength3D(f32, f32, f32);
f32 func_uvmath_rom_004006F8(f32, f32);

// Needs bss migration?
#if FALSE
extern s32 func_uvmath_rom_00400544;
extern s32 func_uvmath_rom_00400630;
extern s32 func_uvmath_rom_004006F8;
extern s32 uvAbs;
extern s32 uvFabs;
extern s32 uvSrand;
extern s32 uvRandFLcg;
extern s32 func_uvmath_rom_004008E4;
extern s32 uvGetRandomState;
extern s32 uvClampF;
extern s32 uvWrapAngleRadians;
extern s32 uvFoldAngleRadians;

void __entrypoint_func_uvmath_rom_400000(UvMath_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->unk0 = func_uvmath_rom_00400108;
    exports->unk28 = &uvAbs;
    exports->uvSqrtf = uvSqrtF;
    exports->unk2C = &uvFabs;
    exports->uvSinF = &uvSinF;
    exports->unk30 = &uvSrand;
    exports->uvCosF = &uvCosF;
    exports->unk34 = &uvRandFLcg;
    exports->uvTanF = &uvTanF;
    exports->unk38 = &func_uvmath_rom_004008E4;
    exports->uvLength2D = &uvLength2D;
    exports->unk3C = &uvGetRandomState;
    exports->uvLength3D = &uvLength3D;
    exports->unk40 = &uvClampF;
    exports->unk1C = &func_uvmath_rom_00400544;
    exports->unk44 = &uvWrapAngleRadians;
    exports->unk20 = &func_uvmath_rom_00400630;
    exports->unk48 = &uvFoldAngleRadians;
    exports->uvAtan2F = &func_uvmath_rom_004006F8;
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmath_rom/__entrypoint_func_uvmath_rom_400000.s")
#endif

void func_uvmath_rom_00400108(void) {
}

f32 uvSqrtF(f32 arg0) {
    return arg0 < 0.0f ? 0.0f : sqrtf(arg0);
}

// Already matched but needs rodata migration
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmath_rom/uvSinF.s")

// Already matched but needs rodata migration
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmath_rom/uvCosF.s")

// uvTanF
#line 75 "src/modules/uvmath_rom.c"
/* Compute tangent as the original sine/cosine ratio; retain its singularities. */
f32 uvTanF(f32 x) {
    return uvSinF(x) / uvCosF(x);
}
#line 78 "src/modules/uvmath_rom.c"

// uvLength2D
#line 80 "src/modules/uvmath_rom.c"
/* Compute the Euclidean length of two components through the shared square root. */
f32 uvLength2D(f32 x, f32 y) {
   return uvSqrtF(SQ(x) + SQ(y));
}
#line 83 "src/modules/uvmath_rom.c"

// uvLength3D
#line 85 "src/modules/uvmath_rom.c"
/* Compute the Euclidean length of three components in original addition order. */
f32 uvLength3D(f32 x, f32 y, f32 z) {
    return uvSqrtF(SQ(x) + SQ(y) + SQ(z));
}
#line 88 "src/modules/uvmath_rom.c"

f32 func_uvmath_rom_00400544(f32 arg0) {
    f32 temp_fv0;
    f32 var_fv1;

    if (arg0 > 1.0f) {
        var_fv1 = 1.0f;
        arg0 = 1.0f;
    } else if (arg0 < -1.0f) {
        var_fv1 = 1.0f;
        arg0 = -1.0f;
    } else if (arg0 > 0.0f) {
        var_fv1 = arg0;
    } else {
        var_fv1 = -arg0;
    }
    if (var_fv1 < 0.5f) {
        return func_uvmath_rom_004006F8(arg0, uvSqrtF(1.0f - (arg0 * arg0)));
    }
    temp_fv0 = 1.0f - var_fv1;
    return func_uvmath_rom_004006F8(arg0, uvSqrtF((2.0f * temp_fv0) - SQ(temp_fv0)));
}

extern f32 D_uvmath_rom_00400AAC;
extern f32 D_uvmath_rom_00400AB0;

f32 func_uvmath_rom_00400630(f32 arg0) {
    f32 temp_fv1;
    f32 var_f0;

    temp_fv1 = arg0 + 1.0f;
    if (temp_fv1 > 0.0f) {
        var_f0 = temp_fv1;
    } else {
        var_f0 = -temp_fv1;
    }
    if (var_f0 < D_uvmath_rom_00400AAC) {
        return D_uvmath_rom_00400AB0;
    }
    if (arg0 > 1.0f) {
        var_f0 = arg0 - 1.0f;
    } else {
        var_f0 = -(arg0 - 1.0f);
    }
    if (var_f0 < D_uvmath_rom_00400AAC) {
        return 0.0f;
    }
    return 2.0f * func_uvmath_rom_004006F8(uvSqrtF((1.0f - arg0) / temp_fv1), 1.0f);
}

// uvAtan2F
#ifdef NEEDS_RODATA
f32 func_uvmath_rom_004006F8(f32 y, f32 x) {
    s32 flag;
    f32 ret;
    f32 absY;
    f32 absX;
    f32 tmp;
    f32 absdiff;

    if ((x == 0.0f) && (y == 0.0f)) {
        return 0.0f;
    }
    absX = FABS(x);
    absY = FABS(y);
    flag = 0;
    if (absX < absY) {
        tmp = absX;
        absX = absY;
        absY = tmp;
        flag = 1;
    }
    tmp = (absY / absX);
    absdiff = FABS(absY - absX);
    ret = (PW_PI_4 * (absY / absX)) + (0.309f * absdiff * tmp);

    tmp = 0; // fake store to prevent emitting additional mov instr.
    if (x >= 0.0f) {
        if (flag) {
            ret = PW_PI_2 - ret;
        }
    } else if (flag) {
        ret = PW_PI_2 + ret;
    } else {
        ret = PW_PI - ret;
    }

    if (y >= 0.0f) {
        return ret;
    } else {
        return -ret;
    }
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmath_rom/func_uvmath_rom_004006F8.s")
#endif

// uvAbs
#line 186 "src/modules/uvmath_rom.c"
/* Return the signed integer absolute value. Preserve the original arithmetic
 * and caller requirement that the negative value be representable. */
s32 uvAbs(s32 x) {
    return x < 0 ? -x : x;
}
#line 189 "src/modules/uvmath_rom.c"

// uvFabs
#line 191 "src/modules/uvmath_rom.c"
/* Return the comparison-based floating absolute value. Preserve signed zero
 * and unordered comparisons instead of substituting a different intrinsic. */
f32 uvFabs(f32 x) {
    return x < 0.0f ? -x : x;
}
#line 194 "src/modules/uvmath_rom.c"

// uvSrand
#line 196 "src/modules/uvmath_rom.c"
/* Set the shared linear-congruential pseudorandom generator state. */
void uvSrand(s32 seed) {
    D_uvmath_rom_00400AF0 = seed;
}
#line 199 "src/modules/uvmath_rom.c"

// uvRandFLcg
#line 201 "src/modules/uvmath_rom.c"
/* Advance the unsigned 32-bit linear-congruential state and return the
 * selected 15 bits divided by 32768, in the range zero inclusive to one exclusive. */
f32 uvRandFLcg(void) {
    u32 sample;
    D_uvmath_rom_00400AF0 = (D_uvmath_rom_00400AF0 * 1103515245) + 12345;
    sample = (D_uvmath_rom_00400AF0 >> 16) & 0x7FFF;
    return (f32)sample / 0x8000;
}
#line 207 "src/modules/uvmath_rom.c"

extern f32 D_uvmath_rom_00400AC8;

f32 func_uvmath_rom_004008E4(void) {
    return (f32) (osGetCount() & 0xFFFF) / D_uvmath_rom_00400AC8;
}

#line 214 "src/modules/uvmath_rom.c"
/* Return the current shared pseudorandom state without advancing it. */
s32 uvGetRandomState(void) {
    return D_uvmath_rom_00400AF0;
}
#line 217 "src/modules/uvmath_rom.c"

#line 218 "src/modules/uvmath_rom.c"
/* Clamp a value between caller-supplied lower and upper bounds in original
 * comparison order. Unordered inputs preserve the original return behavior. */
f32 uvClampF(f32 value, f32 maximum, f32 minimum) {
    if (maximum < value) {
        return maximum;
    }
    if (value < minimum) {
        return minimum;
    }
    return value;
}
#line 227 "src/modules/uvmath_rom.c"

// Matched but eeds rodata migration
#line 229 "src/modules/uvmath_rom.c"
/* Wrap radians into the original [-pi, pi] interval by repeated full turns.
 * Retain the original float words and lower-bound/full-turn load order. */
extern f32 D_uvmath_rom_00400ACC;
extern f32 D_uvmath_rom_00400AD0;
extern f32 D_uvmath_rom_00400AD4;
extern f32 D_uvmath_rom_00400AD8;

f32 uvWrapAngleRadians(f32 angle) {
    f32 wrapped;
    f32 lowerBound;
    f32 fullTurn;

    wrapped = angle;
    if (D_uvmath_rom_00400ACC < angle) {
        do {
            wrapped -= D_uvmath_rom_00400AD0;
        } while (D_uvmath_rom_00400ACC < wrapped);
    }
    lowerBound = D_uvmath_rom_00400AD4;
    fullTurn = D_uvmath_rom_00400AD8;
    if (wrapped < lowerBound) {
        do {
            wrapped += fullTurn;
        } while (wrapped < lowerBound);
    }
    return wrapped;
}
#line 230 "src/modules/uvmath_rom.c"

// Matched but eeds rodata migration
#line 230 "src/modules/uvmath_rom.c"
/* Wrap a radian angle, then fold it around the original half-pi bounds
 * without changing its sine. Preserve the ROM's exact float constants. */
f32 uvWrapAngleRadians(f32 angle);                     /* extern */
extern f32 D_uvmath_rom_00400ADC;
extern f32 D_uvmath_rom_00400AE0;
extern f32 D_uvmath_rom_00400AE4;
extern f32 D_uvmath_rom_00400AE8;

f32 uvFoldAngleRadians(f32 angle) {
    f32 wrapped;

    wrapped = uvWrapAngleRadians(angle);
    if (D_uvmath_rom_00400ADC < wrapped) {
        return D_uvmath_rom_00400AE0 - wrapped;
    }
    if (wrapped < D_uvmath_rom_00400AE4) {
        return D_uvmath_rom_00400AE8 - wrapped;
    }
    return wrapped;
}
#line 231 "src/modules/uvmath_rom.c"
