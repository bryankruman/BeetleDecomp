// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_race_004049E4;
extern s32 *D_race_004049E8;
extern s32 D_race_004049EC;
extern u8 D_race_004049C4[];
extern s32 D_race_004049F0;
extern void *D_race_00404A04;
void func_race_00400920();
void func_race_00400AB4();
void func_race_00400CC0();
void func_race_00400EB0();
void func_race_004011BC();
void func_race_00401B3C();
void func_race_00401E04();
void func_race_004024D0();
void func_race_004026D0();
void func_race_00402864();
void func_race_00402AAC();
void func_race_00402CE0();
void func_race_00402E98();
void func_race_004030D0();
void func_race_00403268();
void func_race_00403358();
s32 func_race_0040348C();
void func_race_004034C4();
void func_race_004035C8();
void func_race_0040367C();
void func_race_004036C8();
void func_race_004036E4();
void func_race_00403734();
void func_race_004037DC();
void func_race_004038B0();
void func_race_00403B6C();
void func_race_00404044();
void func_race_00404194();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/__entrypoint_func_race_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400AB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004011BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401E04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004024D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004026D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402E98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004030D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403268.s")

void func_race_00403350(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403358.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_0040348C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004034C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004035C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_0040367C.s")

void func_race_004036C8(s32 a0, s32 a1, s32 a2) {
    D_race_004049E4 = a0;
    D_race_004049E8 = (s32 *)a1;
    D_race_004049EC = a2;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004036E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004037DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004038B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403B6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00404044.s")

void func_race_00404194(void) {
    (*(void (**)(s32))((u8 *)D_race_00404A04 + 0x20))(D_race_004049F0);
}

