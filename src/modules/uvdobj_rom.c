// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_uvdobj_rom_004039EC;
extern s32 D_uvdobj_rom_004039F0;
extern void *D_uvdobj_rom_004039B4;
extern s32 D_uvdobj_rom_004039B8;
extern u16 D_uvdobj_rom_004039BC;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/__entrypoint_func_uvdobj_rom_400000.s")

void func_uvdobj_rom_00400544(s32 a0, s32 a1) {
    D_uvdobj_rom_004039EC = a0;
    D_uvdobj_rom_004039F0 = a1;
}

s32 func_uvdobj_rom_00400558(s16 a0, s16 a1, s16 a2) {
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_0040056C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004005C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400770.s")

u16 func_uvdobj_rom_00400A00(s32 a0) {
    return *(u16 *)((u8 *)D_uvdobj_rom_004039B4 + a0 * 0x30);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400A20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400C7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400D5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00400FF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401074.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004010B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004011CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401210.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401240.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401598.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004015C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401ABC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00401F14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00402138.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00402420.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00402870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00402D68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_00403054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004032DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_0040359C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_0040368C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdobj_rom/func_uvdobj_rom_004038C4.s")

u16 func_uvdobj_rom_00403954(s32 *a0) {
    *a0 = D_uvdobj_rom_004039B8;
    return D_uvdobj_rom_004039BC;
}

