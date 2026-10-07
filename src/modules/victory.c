// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern f32 D_victory_00401128,D_victory_0040112C,D_victory_00401130,D_victory_00401134;
extern s32 D_victory_004011E4,D_victory_004011E8,D_victory_004011EC,D_victory_004011F0,gNumOpenTourns;
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
    gSndExports->sndReleaseHandle(&D_victory_00401240);
    gSndExports->sndReleaseHandle(&D_victory_00401248);
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

#line 22 "src/modules/victory.c"
/* Consume the original pending victory sound for kinds zero through three.
 * Preserve tournament-unlock voice gates, per-kind volume constants and both
 * final emitter handles; invalid kinds leave every pending flag unchanged. */
void victoryPlayPendingSoundsByKind(s32 kind) {
    switch (kind) {
    case 0:
        if (D_victory_004011E4 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->func_snd_004014B4() * D_victory_00401128);
            if (gNumOpenTourns == 2) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDD,0x7FFF,gSndExports->func_snd_004014C4(),0.5f);
            }
            D_victory_004011E4 = 0;
            return;
        }
        return;
    case 1:
        if (D_victory_004011E8 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->func_snd_004014B4() * D_victory_0040112C);
            if (gNumOpenTourns == 3) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDC,0x7FFF,gSndExports->func_snd_004014C4(),0.5f);
            }
            D_victory_004011E8 = 0;
            return;
        }
        break;
    case 2:
        if (D_victory_004011EC != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->func_snd_004014B4() * D_victory_00401130);
            if (gNumOpenTourns == 4) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDE,0x7FFF,gSndExports->func_snd_004014C4(),0.5f);
            }
            D_victory_004011EC = 0;
            return;
        }
        break;
    case 3:
        if (D_victory_004011F0 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF2,0x7FFF,gSndExports->func_snd_004014B4() * D_victory_00401134);
            gSndExports->sndPlayManagedSound(&D_victory_00401240,0xA1,0x7FFF,gSndExports->func_snd_004014C4(),0.5f);
            D_victory_00401250 = gSndExports->func_snd_00400854(0xD0,0x7FFF,gSndExports->func_snd_004014C4(),0x37B1D0);
            D_victory_00401251 = gSndExports->func_snd_00400854(0xF9,0x7FFF,gSndExports->func_snd_004014C4(),0x51F090);
            D_victory_004011F0 = 0;
        }
        break;
    }
}
#line 23 "src/modules/victory.c"

