// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvmath_rom.h"
extern UvMath_Exports *gUvMathExports;
extern f32 D_flag_00401660,D_flag_00401664;
extern void *D_flag_00401728;
typedef struct UnkCbckExports_s {
    char pad[0x10];
    void (*unk10)(s32, void *, s32, s32);
} UnkCbckExports;
typedef struct UnkChanExports_s {
    char pad[0x4];
    void (*unk4)(s32, s32, void *, s32);
} UnkChanExports;
extern UnkCbckExports *gUvCbckExports;
extern UnkChanExports *gUvChanExports;
void func_flag_00400080();
void func_flag_004004A4();
void flagAdjustPositionByDistanceBands(Vec3F *target, Vec3F *position, f32 scale);
void func_flag_004006BC();
void func_flag_004008F4();
void func_flag_00400D10();
void func_flag_00400D54();
void func_flag_00401198();
void func_flag_004012FC();
void func_flag_00401354();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/__entrypoint_func_flag_400000.s")

void func_flag_00400078(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00400080.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004004A4.s")

#line 37 "src/modules/flag.c"
/* Adjust the position along its displacement from the target using two original
 * scale-dependent distance bands. Preserve both strict squared-radius tests,
 * the distinct inward/outward fractions and the original unordered behavior. */
void flagAdjustPositionByDistanceBands(Vec3F *target, Vec3F *position, f32 scale) {
    f32 upperRadius,lowerRadius,dx,dy,dz,lengthSquared;
    f32 upperLength,upperFraction,lowerLength,lowerFraction;
    upperRadius = scale * D_flag_00401660;
    lowerRadius = scale * D_flag_00401664;
    dx = target->x - position->x;
    dy = target->y - position->y;
    dz = target->z - position->z;
    lengthSquared = (dx * dx) + (dy * dy) + (dz * dz);
    if ((upperRadius * upperRadius) < lengthSquared) {
        upperLength = gUvMathExports->uvSqrtf(lengthSquared);
        upperFraction = (upperLength - upperRadius) / upperLength;
        dx *= upperFraction;
        dy *= upperFraction;
        dz *= upperFraction;
        position->x += dx;
        position->y += dy;
        position->z += dz;
        return;
    }
    if ((lowerRadius * lowerRadius) < lengthSquared) {
        lowerLength = gUvMathExports->uvSqrtf(lengthSquared);
        lowerFraction = (lowerRadius - lowerLength) / lowerLength;
        dx *= lowerFraction;
        dy *= lowerFraction;
        dz *= lowerFraction;
        position->x += dx;
        position->y += dy;
        position->z += dz;
    }
}
#line 38 "src/modules/flag.c"

void func_flag_004006B4(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004006BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_004008F4.s")

void func_flag_00400D10(void) {
    void *s0;

    s0 = D_flag_00401728;
    if (s0 != NULL) {
        do {
            func_flag_004008F4(s0);
            s0 = *(void **)((u8 *)s0 + 0x48);
        } while (s0 != NULL);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00400D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00401198.s")

void func_flag_004012FC(s32 a0) {
    s32 sp1C;

    gUvChanExports->unk4(a0, 6, &sp1C, 0);
    gUvCbckExports->unk10(sp1C, func_flag_00401198, 0, 0x3D);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00401354.s")

