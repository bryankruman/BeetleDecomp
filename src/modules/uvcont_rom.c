// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern void func_uvcont_rom_00401720(void);
extern u8 D_uvcont_rom_00401AE4;
extern u16 D_uvcont_rom_004018B0;
extern u8 D_uvcont_rom_004018B6;
extern s32 D_uvcont_rom_00401AE8;
extern s32 D_uvcont_rom_00401B04;
extern u16 D_uvcont_rom_00401B08;
extern s32 D_uvcont_rom_00401B0C;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/__entrypoint_func_uvcont_rom_400000.s")

void func_uvcont_rom_004002B8(void) {
    func_uvcont_rom_00401720();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004002D8.s")

s32 func_uvcont_rom_00400604(s32 a0) {
    return ((s32)D_uvcont_rom_00401AE4 >> a0) & 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_0040061C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400640.s")

u16 func_uvcont_rom_00400678(s32 a0) {
    return *(u16 *)((u8 *)&D_uvcont_rom_004018B0 + a0 * 24);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004006E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_0040072C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400768.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_0040079C.s")

u8 func_uvcont_rom_00400800(s32 a0) {
    return (&D_uvcont_rom_004018B6)[a0 * 24];
}

void func_uvcont_rom_0040081C(s32 a0) {
    D_uvcont_rom_00401B04 = a0;
}

void func_uvcont_rom_00400828(s32 a0) {
    D_uvcont_rom_00401AE8 = a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400834.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400974.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004009F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400A98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400B5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400C90.s")

void func_uvcont_rom_00400D48(s32 a0, s32 a1) {
    D_uvcont_rom_00401B08 = a0;
    D_uvcont_rom_00401B0C = a1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400D5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400E4C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400F94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00400FDC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401024.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004011FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_0040128C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004013E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401478.s")

void func_uvcont_rom_00401518(s16 a0) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401520.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_004015D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401658.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401720.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvcont_rom/func_uvcont_rom_00401760.s")

void func_uvcont_rom_0040183C(s16 a0) {
}

