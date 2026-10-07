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
void flagUpdateRegisteredRecords();
void func_flag_00400D54();
void func_flag_00401198();
void flagAttachUpdateCallbackToChannel();
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

#line 46 "src/modules/flag.c"
/* Apply the original per-record helper to every registered flag record
 * in list order. Read the next link after each helper call so any original
 * link changes remain observable.
 * RE_UNKNOWN: The internal behavior of the per-record assembly helper remains unrecovered. */
void flagUpdateRegisteredRecords(void) {
    void *record;

    record = D_flag_00401728;
    if (record != NULL) {
        do {
            func_flag_004008F4(record);
            record = *(void **)((u8 *)record + 0x48);
        } while (record != NULL);
    }
}
#line 57 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00400D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00401198.s")

#line 62 "src/modules/flag.c"
/* Query channel property six and attach the original flag update
 * callback at priority 61, preserving the callback host contract. */
void flagAttachUpdateCallbackToChannel(s32 channel) {
    s32 callbackHost;

    gUvChanExports->unk4(channel, 6, &callbackHost, 0);
    gUvCbckExports->unk10(callbackHost, func_flag_00401198, 0, 0x3D);
}
#line 68 "src/modules/flag.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/flag/func_flag_00401354.s")

