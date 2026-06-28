// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern void *D_uvpfxld_rom_00400EE4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/__entrypoint_func_uvpfxld_rom_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400094.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004000DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004002DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400994.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400B98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400BD4.s")

void func_uvpfxld_rom_00400CBC(void *a0) {
    *(s16 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x2) = *(s32 *)a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400CD0.s")

