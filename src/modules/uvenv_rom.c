// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 *D_uvenv_rom_00403C08;
extern s32 D_uvenv_rom_00403C0C;
void func_uvenv_rom_00400220();
void func_uvenv_rom_00400450();
void func_uvenv_rom_00401954();
void func_uvenv_rom_00401FE0();
void func_uvenv_rom_0040205C();
void func_uvenv_rom_0040253C();
void func_uvenv_rom_00402DD8();
void func_uvenv_rom_00402E68();
void func_uvenv_rom_00402F00();
s32 func_uvenv_rom_00403AFC();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/__entrypoint_func_uvenv_rom_400000.s")

void func_uvenv_rom_004001B4(void) {
    _uvMemFree(D_uvenv_rom_00403C08);
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x53544154);
    uvUnloadModule(0x474D4752);
    uvUnloadModule(0x4348414E);
    uvUnloadModule(0x4342434B);
    uvUnloadModule(0x4D4F444C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00400220.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00400450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00401954.s")

typedef struct {
    u8 pad0[0x38];
    s32 unk38;
    u8 pad3C[0x20];
    s32 unk5C;
} AutoS_00401F7C_temp_v0;

void func_uvenv_rom_00401F7C(s32 arg0, s32 arg1, s32 arg2) {
    AutoS_00401F7C_temp_v0 *temp_v0;

    temp_v0 = uvGetLoadedFile(0x5556454E, arg0);
    if (temp_v0 != NULL) {
        switch (arg1) {                             /* irregular */
        case 0:
            temp_v0->unk38 = arg2;
            return;
        case 1:
            temp_v0->unk5C = arg2;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00401FE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_0040205C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_0040253C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00402DD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00402E68.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvenv_rom/func_uvenv_rom_00402F00.s")

s32 func_uvenv_rom_00403AFC(s32 arg0) {
    if (D_uvenv_rom_00403C0C < arg0) {
        return -1;
    }
    return D_uvenv_rom_00403C08[arg0];
}

