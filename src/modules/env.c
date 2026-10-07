// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_env_00400848[];
extern s32 D_env_00400870;
extern void *D_env_0040087C;
void func_env_00400100();

void func_env_004001F4();
void func_env_0040033C();
void func_env_00400380();
void func_env_00400758();
void func_env_004007A4();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/__entrypoint_func_env_400000.s")

void func_env_004000AC(void) {
}

typedef struct {
    s32 unk0;
    f32 unk4;
    void * unk8;
} AutoS_004000B4_temp_v0;

extern void *D_env_00400878;

void func_env_004000B4(s32 arg0, f32 arg1) {
    AutoS_004000B4_temp_v0 *temp_v0;

    temp_v0 = _uvMemAllocAlign8(0xCU);
    temp_v0->unk8 = (void *) D_env_00400878;
    D_env_00400878 = temp_v0;
    temp_v0->unk0 = arg0;
    temp_v0->unk4 = arg1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_00400100.s")

#line 38 "src/modules/env.c"
/* Allocate and prepend a 20-byte environment record. The three values and flags
 * remain opaque until their consumers establish a more specific meaning. */
typedef struct EnvRecord_00400190 {
    s32 values[3];
    u8 flags;
    u8 padD[3];
    struct EnvRecord_00400190 *next;
} EnvRecord_00400190;
extern EnvRecord_00400190 *D_env_00400874;
void envPrependRecord(s32 first, s32 second, s32 third, u8 flags) {
    EnvRecord_00400190 *record;
    record = _uvMemAllocAlign8(sizeof(EnvRecord_00400190));
    record->values[0] = first;
    record->values[1] = second;
    record->values[2] = third;
    record->flags = flags;
    record->next = D_env_00400874;
    D_env_00400874 = record;
}
#line 39 "src/modules/env.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_004001F4.s")

void func_env_0040033C(s32 arg0) {
    if (D_env_00400870 < 0xA && arg0 != 0) {
        D_env_00400848[D_env_00400870] = arg0;
        D_env_00400870 += 1;
    }
}

void func_env_00400378(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_00400380.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_00400758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/env/func_env_004007A4.s")

