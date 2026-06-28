// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern void *D_results_00407718;
extern s16 D_results_00407568[];
extern s32 D_results_00407508[4][6];
extern s32 D_results_004075A8;
extern s32 D_results_004075AC;
extern s32 D_results_004075BC;
extern s32 D_results_004075C0;
void func_results_0040659C(s32, void *);
void func_results_004001B8();
void func_results_004002BC();
void func_results_00400AC8();
void func_results_00401390();
void func_results_004013BC();
void func_results_00401B00();
void func_results_00402B9C();
void func_results_00403284();
void func_results_00404474();
void func_results_00404D20();
void func_results_00405608();
void func_results_00405DE8();
void func_results_00405E18();
void func_results_00405ED8();
void func_results_00405F94();
void func_results_004060F0();
void func_results_00406184();
void func_results_0040620C();
void func_results_00406338();
void func_results_004064C4();
s16 func_results_00406528();
s32 func_results_00406550();
void func_results_0040659C();
void func_results_004066E8();
void func_results_00406710();
void func_results_00406738();
void func_results_004067CC();
void func_results_004067F4();
extern s32 D_results_004074F8[];
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/__entrypoint_func_results_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004001B8.s")

s32 func_results_004002A8(s32 a0) {
    return D_results_004074F8[a0];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004002BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00400AC8.s")

void func_results_00401390(void) {
    if (gGameSettings->introReplayState == 0) {
        gGameSettings->introReplayState = 1;
        gGameSettings->gameStateFlag = 5;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004013BC.s")

void func_results_00401AF8(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00401B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00402B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00403284.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00404474.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00404D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405608.s")

void func_results_00405DE8(void) {
    (*(void (**)(s32))((u8 *)D_results_00407718 + 0x3C))(0x64);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405ED8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405F94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004060F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00406184.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_0040620C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00406338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004064C4.s")

s16 func_results_00406528(s32 a0) {
    if (a0 < 0 || a0 >= 8) {
        a0 = 7;
    }
    return D_results_00407568[a0];
}

s32 func_results_00406550(s32 a0, s32 a1) {
    if (a0 < 0 || a0 >= 4) {
        a0 = 3;
    }
    if (a1 < 0 || a1 >= 6) {
        a1 = 5;
    }
    return D_results_00407508[a0][a1];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_0040659C.s")

void func_results_004066E8(void) {
    func_results_0040659C(0xEB, &D_results_004075A8);
}

void func_results_00406710(void) {
    func_results_0040659C(0xEC, &D_results_004075AC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00406738.s")

void func_results_004067CC(void) {
    func_results_0040659C(0xF4, &D_results_004075BC);
}

void func_results_004067F4(void) {
    func_results_0040659C(0xF5, &D_results_004075C0);
}

