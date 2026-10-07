// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_uvpfxld_rom_00400EC0;
void uvPfxLoaderCleanup();
void func_uvpfxld_rom_004000DC();
void func_uvpfxld_rom_004002DC();
void func_uvpfxld_rom_00400994();
void uvPfxLoaderCopyIntoSharedWordBuffer();
void func_uvpfxld_rom_00400BD4();
void func_uvpfxld_rom_00400CD0();
extern void *D_uvpfxld_rom_00400EE4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/__entrypoint_func_uvpfxld_rom_400000.s")

#line 14 "src/modules/uvpfxld_rom.c"
/* Unload TSEQ, FMTX, FVEC and UPFX dependencies in their original order. */
void uvPfxLoaderCleanup(void) {
    uvUnloadModule('TSEQ');
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('UPFX');
}
#line 20 "src/modules/uvpfxld_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004000DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004002DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400994.s")

#line 27 "src/modules/uvpfxld_rom.c"
/* Copy twice the configured item count from caller media/source storage
 * into the shared loader buffer at offset 0x30. Preserve the media-copy
 * alignment, device-address and size contracts. */
void uvPfxLoaderCopyIntoSharedWordBuffer(void *sourceWords) {
    _uvMediaCopy(*(s32 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x30), sourceWords, D_uvpfxld_rom_00400EC0 * 2);
}
#line 30 "src/modules/uvpfxld_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400BD4.s")

#line 33 "src/modules/uvpfxld_rom.c"
/* Narrow the caller word into the shared loader configuration short
 * at byte offset two. Preserve signed-short storage and unchecked ownership. */
void uvPfxLoaderSetConfigShortFromWord(void *sourceWord) {
    *(s16 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x2) = *(s32 *)sourceWord;
}
#line 36 "src/modules/uvpfxld_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400CD0.s")

