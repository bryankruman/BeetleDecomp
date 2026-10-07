// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern UvJanim_Exports *gUvJanimExports;
extern f32 D_80025D70;
typedef struct { s32 animation; f32 rate; } VictoryAnimationSource;
typedef struct { u8 unk00[0x10]; s32 handle; u8 unk14[4]; f32 progress; } VictoryAnimationState;
extern VictoryAnimationSource *D_victory_00401238;
extern VictoryAnimationState D_victory_00401218;
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
    gUvEmitterExports->uvEmitterStop(D_victory_00401250);
    gUvEmitterExports->uvEmitterStop(D_victory_00401251);
}
#line 9 "src/modules/victory.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_004003B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400494.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_004005F8.s")

#line 16 "src/modules/victory.c"
/* Advance the victory joint-animation fraction by rate times frame delta,
 * clamp only above one and forward the original handle/animation/fraction. */
void victoryAdvanceJointAnimation(void) {
    D_victory_00401218.progress += D_victory_00401238->rate * D_80025D70;
    if (D_victory_00401218.progress > 1.0f) D_victory_00401218.progress = 1.0f;
    gUvJanimExports->uvJanimApplyAnimation(D_victory_00401218.handle, D_victory_00401238->animation, D_victory_00401218.progress);
}
#line 17 "src/modules/victory.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_0040084C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400970.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/victory/func_victory_00400D28.s")

