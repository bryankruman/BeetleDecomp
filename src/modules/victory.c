// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern Snd_Exports *gSndExports;
extern UvEmitter_Exports *gUvEmitterExports;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/__entrypoint_func_victory_400000.s")

#line 8 "src/modules/victory.c"
/* Stop both victory sound handles and both associated emitter voices. */
extern UnkStruct_004005C8 D_victory_00401240;
extern UnkStruct_004005C8 D_victory_00401248;
extern u8 D_victory_00401250;
extern u8 D_victory_00401251;

void victoryStopSoundsAndEmitters(void) {
    gSndExports->func_snd_00401CDC(&D_victory_00401240);
    gSndExports->func_snd_00401CDC(&D_victory_00401248);
    gUvEmitterExports->func_uvemitter_rom_004010CC(D_victory_00401250);
    gUvEmitterExports->func_uvemitter_rom_004010CC(D_victory_00401251);
}
#line 9 "src/modules/victory.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_004003B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_004005F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_004007C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_0040084C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400970.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400D28.s")

