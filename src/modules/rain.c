// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { char pad0[0x70]; void (*unk70)(void *); } UnkRainSndExports;
extern UnkRainSndExports *gSndExports;
extern u8 D_rain_004016B8[8];
void func_rain_00400000();
void func_rain_0040010C();
void func_rain_00400140();
void func_rain_00400390(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3);
void func_rain_004003D4();
void func_rain_00400678();
void func_rain_004008FC();
void func_rain_00400B2C();
void func_rain_00400D48();
void func_rain_00400F98();
void func_rain_00401068();
void func_rain_00401200();
void func_rain_00401304();
void func_rain_00401478();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/__entrypoint_func_rain_400054.s")

void func_rain_0040010C(void) {
    gSndExports->unk70(D_rain_004016B8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400140.s")

void func_rain_00400388(void *arg0, s32 arg1) {
    *(u8 *)((u8 *)arg0 + 0x12D4) = arg1;
}

void func_rain_00400390(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3) {
    if ((*arg0 < arg1) && (arg3 >= 0.0f)) {
        *arg2 = arg3;
        *arg0 = arg1;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_004003D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400678.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_004008FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400D48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00400F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401068.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401200.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401304.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void * unk18;
} AutoS_00401404_temp_v0;

extern void *D_rain_004016C0;

void func_rain_00401404(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    AutoS_00401404_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0x1CU);
    temp_v0->unk0 = 1;
    temp_v0->unk4 = arg0;
    temp_v0->unk8 = arg3;
    temp_v0->unkC = arg1;
    temp_v0->unk10 = arg4;
    temp_v0->unk14 = arg2;
    temp_v0->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = temp_v0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/rain/func_rain_00401478.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    void * unk18;
} AutoS_0040157C_temp_v0;

extern void *D_rain_004016C0;

void func_rain_0040157C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    AutoS_0040157C_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0x1CU);
    temp_v0->unk0 = 0;
    temp_v0->unk4 = arg0;
    temp_v0->unk8 = arg1;
    temp_v0->unkC = arg3;
    temp_v0->unk10 = arg2;
    temp_v0->unk14 = arg4;
    temp_v0->unk18 = (void *) D_rain_004016C0;
    D_rain_004016C0 = temp_v0;
}

