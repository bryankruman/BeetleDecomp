// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_caranim_004066A0;
extern s32 D_caranim_00407228;
extern s32 gOptionsLanguage;
extern s32 D_caranim_00407348;
extern s32 D_caranim_00406830;
extern s32 D_caranim_00407178;
extern s32 gDebugDefaultMaterial;
extern void func_caranim_004007B0(void *);
extern void func_caranim_00400B08(void *);
void func_caranim_00400308();
void func_caranim_004003AC();
void func_caranim_00400788();
void func_caranim_004007B0();
void func_caranim_00400B08();
void func_caranim_00400C8C();
void func_caranim_00401420();
void func_caranim_004014A4();
void func_caranim_004014DC();
void func_caranim_00401564();
void func_caranim_00401AD0();
void * func_caranim_00401BC8();
void func_caranim_00401C04();
void func_caranim_00401C54();
void func_caranim_00401D6C();
void func_caranim_00402FD4();
void func_caranim_004033F4();
void func_caranim_0040358C();
void func_caranim_0040371C();
void func_caranim_004039E0();
void func_caranim_00403A80();
void func_caranim_00403BDC();
void func_caranim_00404074();
void func_caranim_00404224();
void func_caranim_004042C4();
void func_caranim_00404568();
void func_caranim_00404A40();
void func_caranim_00404ACC();
void func_caranim_00404CA0();
void func_caranim_00405194();
void func_caranim_00405220();
void func_caranim_00405304();
void func_caranim_004054B4();
void func_caranim_00405910();
void func_caranim_00405B24();
void func_caranim_00405B7C();
void func_caranim_00405DE4();
s32 func_caranim_00405FE8(s32 arg0);
void func_caranim_0040603C();
s32 func_caranim_00406094();
void func_caranim_004060EC();
void func_caranim_00406158();
extern s32 D_caranim_00407368;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/__entrypoint_func_caranim_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400308.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004003AC.s")

void func_caranim_00400788(void *a0) {
    func_caranim_004007B0(a0);
    func_caranim_00400B08(a0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004007B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400B08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401420.s")

void func_caranim_00401494(void *a0, s32 a1) {
    *(u8 *)((u8 *)a0 + 0x24) = a1;
}

void func_caranim_0040149C(void *a0, s32 a1) {
    *(u8 *)((u8 *)a0 + 0x25) = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004014DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401564.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401AD0.s")

void *func_caranim_00401BC8(s32 a0) {
    if (a0 == 0xFFF) {
        a0 = 0;
    }
    if (gDebugDefaultMaterial != 0) {
        a0 = 0;
    }
    return (void *)((u8 *)&D_caranim_00406830 + a0 * 0x1C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401C54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00401D6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00402FD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040358C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040371C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004039E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403A80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00403BDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404224.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004042C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404568.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404A40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00404CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004054B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405910.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405B24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405B7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00405DE4.s")

s32 func_caranim_00405FE8(s32 arg0) {
    if (arg0 < -1 || arg0 >= 0x15) {
        return (s32)&D_caranim_004066A0;
    }
    return *(s32 *)((u8 *)&D_caranim_00407228 + (gOptionsLanguage * 0x54 + arg0 * 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_0040603C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00406094.s")

s32 func_caranim_004060E0(void) {
    return D_caranim_00407368;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_004060EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caranim/func_caranim_00406158.s")

