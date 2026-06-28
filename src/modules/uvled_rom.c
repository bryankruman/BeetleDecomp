// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
void func_uvled_rom_004004C8(s32 arg0, s32 arg1);
extern s16 D_uvled_rom_00401660;
extern s16 D_uvled_rom_00401662;
void func_uvled_rom_00400118();
void func_uvled_rom_00400148();
void func_uvled_rom_004002E0();
void func_uvled_rom_00400300();
void func_uvled_rom_00400320();
void func_uvled_rom_00400340();
void func_uvled_rom_0040035C();
void func_uvled_rom_00400410();
void func_uvled_rom_004004C8();
void func_uvled_rom_004007A4();
void func_uvled_rom_00400B2C();
void func_uvled_rom_00400C04();
void func_uvled_rom_00400DFC();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/__entrypoint_func_uvled_rom_400000.s")

void func_uvled_rom_00400118(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('GMGR');
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400148.s")

void func_uvled_rom_004002E0(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 0xA);
}

void func_uvled_rom_00400300(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 2);
}

void func_uvled_rom_00400320(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400340.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_0040035C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400410.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_004004C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_004007A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400B2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvled_rom/func_uvled_rom_00400DFC.s")

