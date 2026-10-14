// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#include "module.h"

extern u32 D_uvmath_rom_00400AF0;

//void uvUpdateFileAllocPtr(void*);
void __entrypoint_func_uvmathInitializeExports(UvMath_Exports* exports);
void uvMathNoOpModuleCleanup(void);
f32 uvSqrtF(f32 arg0);
f32 uvSinF(f32);
f32 uvCosF(f32);
f32 uvTanF(f32);
f32 uvLength2D(f32, f32);
f32 uvLength3D(f32, f32, f32);
f32 func_uvmath_rom_004006F8(f32, f32);

f32 uvArcSinClampedF(f32 value);
f32 uvArcCosWithEndpointToleranceF(f32 value);
s32 uvAbs(s32 value);
f32 uvFabs(f32 value);
void uvSrand(s32 seed);
f32 uvRandFLcg(void);
f32 uvMathGetCounterFraction(void);
s32 uvGetRandomState(void);
f32 uvClampF(f32 value, f32 maximum, f32 minimum);
f32 uvWrapAngleRadians(f32 angle);
f32 uvFoldAngleRadians(f32 angle);

#line 32 "src/modules/uvmath_rom.c"
/* Publish all nineteen math exports in the original assignment order,
 * preserving the reserved module-entrypoint prefix in this function's name.
 * Use active recovered function contracts; slots 0x38/0x48 retain their
 * existing raw address fields for the counter-fraction and angle-fold helpers.
 * RE_UNKNOWN: the wider consumer contracts of those neutral export fields
 * require remaining indirect callers; target identity is established here.
 * Replace the inactive draft's integer function placeholders with actual
 * function declarations. No math behavior or shared header ABI changes. */
void __entrypoint_func_uvmathInitializeExports(UvMath_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->unk0 = uvMathNoOpModuleCleanup;
    exports->uvAbs = uvAbs;
    exports->uvSqrtf = uvSqrtF;
    exports->uvFabs = uvFabs;
    exports->uvSinF = uvSinF;
    exports->uvSrand = uvSrand;
    exports->uvCosF = uvCosF;
    exports->uvRandFLcg = uvRandFLcg;
    exports->uvTanF = uvTanF;
    exports->unk38 = (void *) uvMathGetCounterFraction;
    exports->uvLength2D = uvLength2D;
    exports->uvGetRandSeed = uvGetRandomState;
    exports->uvLength3D = uvLength3D;
    exports->uvClampF = uvClampF;
    exports->uvArcSinF = uvArcSinClampedF;
    exports->uvNormalizeAngle = uvWrapAngleRadians;
    exports->uvArcCosF = uvArcCosWithEndpointToleranceF;
    exports->unk48 = (void *) uvFoldAngleRadians;
    exports->uvAtan2F = func_uvmath_rom_004006F8;
}
#line 33 "src/modules/uvmath_rom.c"

#line 61 "src/modules/uvmath_rom.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void uvMathNoOpModuleCleanup(void) {
}
#line 63 "src/modules/uvmath_rom.c"

/* Return zero for a negative input; otherwise forward the input to sqrtf,
 * including values for which the negative comparison is unordered. RE_UNKNOWN:
 * library exceptional-value behavior and the caller numerical domain remain
 * unchanged. */
#line 64 "src/modules/uvmath_rom.c"
f32 uvSqrtF(f32 arg0) {
    return arg0 < 0.0f ? 0.0f : sqrtf(arg0);
}
#line 67 "src/modules/uvmath_rom.c"

// Already matched but needs rodata migration
#line 69 "src/modules/uvmath_rom.c"
/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

/* Approximate sine of radians using the existing split-pi reduction and
 * double-precision polynomial. Tiny inputs return unchanged, preserving their
 * signed zero; the bit-defined magnitude gates and arithmetic order are kept.
 * RE_ORIGINAL_QUIRK: inputs outside the reduction domain return zero, except
 * NaN inputs return the existing finite scalar (0x4eff2000), not a quiet NaN.
 * RE_UNKNOWN: approximation error, unusual rounding modes, caller dependence
 * on exceptional inputs, and portability of the SDK float/int bit view.
 * Existing rodata owns these consumed views; no replacement storage is added.
 */
extern double D_uvmath_rom_00400A60[5];
extern double D_uvmath_rom_00400A88;
extern double D_uvmath_rom_00400A90;
extern double D_uvmath_rom_00400A98; /* first eight bytes only */
extern float D_uvmath_rom_00400AA4;

float uvSinF(float radians)

{
    double reducedRadians, squaredRadians, correctionPolynomial;
    double reductionMultiple;
    int halfTurnIndex;
    double approximateSine;
    int floatBits, magnitudeBits;


    floatBits = *(int *)&radians;
    magnitudeBits = (floatBits >> 22);
    magnitudeBits &= 0x1ff;

    /* magnitudeBits is exponent(radians) + 1 bit of mantissa */

    if ( magnitudeBits < 0xff )
    {
        /* |radians| < 1.5 */

        reducedRadians = radians;

        if ( magnitudeBits >= 0xe6 )
        {
            /* |radians| >= 2^(-12) */

            /* compute sin(radians) with a standard polynomial approximation */

            squaredRadians = reducedRadians*reducedRadians;

            correctionPolynomial = ((D_uvmath_rom_00400A60[4]*squaredRadians + D_uvmath_rom_00400A60[3])*squaredRadians + D_uvmath_rom_00400A60[2])*squaredRadians + D_uvmath_rom_00400A60[1];

            approximateSine = reducedRadians + (reducedRadians*squaredRadians)*correctionPolynomial;

            return ( (float)approximateSine );
        }

        return ( radians );
    }

    if ( magnitudeBits < 0x136 )
    {
        /* |radians| < 2^28 */

        reducedRadians = radians;

        /* reduce argument to +/- pi/2 */

        reductionMultiple = reducedRadians*D_uvmath_rom_00400A88;

        halfTurnIndex = (int)(((reductionMultiple) >= 0.0) ? ((reductionMultiple) + 0.5) : ((reductionMultiple) - 0.5));
        reductionMultiple = halfTurnIndex;

        reducedRadians = reducedRadians - reductionMultiple*D_uvmath_rom_00400A90;
        reducedRadians = reducedRadians - reductionMultiple*D_uvmath_rom_00400A98; /* reducedRadians = radians - halfTurnIndex*pi */

        /* compute sin(reducedRadians) as before, negating approximateSine if halfTurnIndex is odd
        */

        squaredRadians = reducedRadians*reducedRadians;

        correctionPolynomial = ((D_uvmath_rom_00400A60[4]*squaredRadians + D_uvmath_rom_00400A60[3])*squaredRadians + D_uvmath_rom_00400A60[2])*squaredRadians + D_uvmath_rom_00400A60[1];

        approximateSine = reducedRadians + (reducedRadians*squaredRadians)*correctionPolynomial;


        if ( (halfTurnIndex & 1) == 0 )
            return ( (float)approximateSine );

        return ( -(float)approximateSine );
    }

    if ( radians != radians )
    {
        /* Preserve the original finite scalar returned for a NaN input. */

        /* Original module has no errno-call path. */

        return ( D_uvmath_rom_00400AA4 );
    }

    /* just give up and return 0.0 */

    return ( 0.0f );
}
#line 70 "src/modules/uvmath_rom.c"

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

#line 89 "src/modules/uvmath_rom.c"
/* Compute arcsine through the original atan2 helper after clamping the
 * input to [-1, 1]. Preserve the alternate square-root expression for
 * magnitudes at least one half and its floating-point evaluation order. */
f32 uvArcSinClampedF(f32 value) {
    f32 distanceFromEndpoint;
    f32 magnitude;

    if (value > 1.0f) {
        magnitude = 1.0f;
        value = 1.0f;
    } else if (value < -1.0f) {
        magnitude = 1.0f;
        value = -1.0f;
    } else if (value > 0.0f) {
        magnitude = value;
    } else {
        magnitude = -value;
    }
    if (magnitude < 0.5f) {
        return func_uvmath_rom_004006F8(value, uvSqrtF(1.0f - (value * value)));
    }
    distanceFromEndpoint = 1.0f - magnitude;
    return func_uvmath_rom_004006F8(value, uvSqrtF((2.0f * distanceFromEndpoint) - SQ(distanceFromEndpoint)));
}
#line 110 "src/modules/uvmath_rom.c"

extern f32 D_uvmath_rom_00400AAC;
extern f32 D_uvmath_rom_00400AB0;

#line 114 "src/modules/uvmath_rom.c"
/* Return the original endpoint values within the shared tolerance;
 * otherwise compute arccosine through the half-angle identity.
 * RE_ORIGINAL_QUIRK: retain the unguarded domain outside those endpoint tests. */
f32 uvArcCosWithEndpointToleranceF(f32 value) {
    f32 onePlusValue;
    f32 endpointDistance;

    onePlusValue = value + 1.0f;
    if (onePlusValue > 0.0f) {
        endpointDistance = onePlusValue;
    } else {
        endpointDistance = -onePlusValue;
    }
    if (endpointDistance < D_uvmath_rom_00400AAC) {
        return D_uvmath_rom_00400AB0;
    }
    if (value > 1.0f) {
        endpointDistance = value - 1.0f;
    } else {
        endpointDistance = -(value - 1.0f);
    }
    if (endpointDistance < D_uvmath_rom_00400AAC) {
        return 0.0f;
    }
    return 2.0f * func_uvmath_rom_004006F8(uvSqrtF((1.0f - value) / onePlusValue), 1.0f);
}
#line 137 "src/modules/uvmath_rom.c"

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

#line 210 "src/modules/uvmath_rom.c"
/* Scale the low sixteen bits of the processor counter by the original
 * divisor. This is time-dependent sampling, not a seeded random sequence. */
f32 uvMathGetCounterFraction(void) {
    return (f32) (osGetCount() & 0xFFFF) / D_uvmath_rom_00400AC8;
}
#line 213 "src/modules/uvmath_rom.c"

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

/* Run the original subtraction and addition loops with the stored pi/full-turn
 * float words and inclusive endpoints. RE_UNKNOWN: caller values must permit
 * float progress; no nonfinite or excessive-magnitude guard exists. */
#line 236 "src/modules/uvmath_rom.c"
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
#line 256 "src/modules/uvmath_rom.c"
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

/* Wrap through uvWrapAngleRadians, then reflect values beyond the stored
 * positive or negative half-pi thresholds using the original pi words.
 * Preserve the exact threshold bits, which are not recomputed from pi.
 * RE_UNKNOWN: angle-domain/progress assumptions follow the wrapper; the
 * four-byte original tail remains excluded. */
#line 238 "src/modules/uvmath_rom.c"
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
#line 250 "src/modules/uvmath_rom.c"
#line 231 "src/modules/uvmath_rom.c"
