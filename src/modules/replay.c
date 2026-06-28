// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern f32 D_replay_00401BA0;
void func_replay_0040018C();
void func_replay_00400230();
void func_replay_004002B4();
void func_replay_00400328();
void func_replay_00400748();
void func_replay_0040097C();
void func_replay_00400C50();
void func_replay_00400D84();
s32 func_replay_00400F2C();
s32 func_replay_00400FB0();
f32 func_replay_00400FE8(s32 arg0, s32 arg1);
void func_replay_0040100C();
void func_replay_0040148C();
void func_replay_0040162C();
void func_replay_004016E8();
void func_replay_00401840();
void func_replay_00401968();
extern u8 D_replay_00401B7C;
extern u8 D_replay_00401B78;
extern s32 D_replay_00401B98;
extern s32 D_replay_00401B9C;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/__entrypoint_func_replay_400000.s")

void func_replay_0040017C(void) {
}

void func_replay_00400184(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040018C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400230.s")

void func_replay_004002A8(s32 a0) {
    D_replay_00401B7C = (u8)a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_004002B4.s")

void func_replay_0040031C(void) {
    D_replay_00401B78 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400328.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400748.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040097C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400C50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400D84.s")

s32 func_replay_00400F2C(s32 a0, s32 a1) {
    u8 *p = (u8 *)&D_replay_00401B98 + a0 * 20;
    if (*(s32 *)p & a1 && !(*(s32 *)(p + 4) & a1)) {
        return 1;
    }
    return 0;
}

s32 func_replay_00400F78(s32 a0) {
    return *(s32*)((u8*)&D_replay_00401B98 + a0 * 20);
}

s32 func_replay_00400F94(s32 a0) {
    return *(s32*)((u8*)&D_replay_00401B9C + a0 * 20);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00400FB0.s")

f32 func_replay_00400FE8(s32 arg0, s32 arg1) {
    return *(f32 *)((u8 *)&D_replay_00401BA0 + (arg0 * 0x14) + (arg1 * 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040100C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040148C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_0040162C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_004016E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00401840.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/replay/func_replay_00401968.s")

