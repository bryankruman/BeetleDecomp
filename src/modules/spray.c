// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
typedef struct { u8 unk00[0xC0]; u32 phase; u8 unkC4[8]; f32 time; u8 unkD0; u8 flagD1; } SprayEffectState;
extern f32 D_80025D6C;
extern Snd_Exports *gSndExports;
extern UnkStruct_004005C8 D_spray_00401768;
extern s32 D_spray_004010B0;
void uvUnloadFile(s32 formFileTag, s32 fileId);
typedef struct UnkCbckExports_s { char pad[0x10]; void (*unk10)(s32, void *, s32, s32); } UnkCbckExports;
typedef struct UnkChanExports_s { char pad[0x4]; void (*unk4)(s32, s32, void *, s32); } UnkChanExports;
extern UnkCbckExports *gUvCbckExports;
extern UnkChanExports *gUvChanExports;
void func_spray_0040055C(s32 arg0);
void sprayModuleCleanup();
void sprayRegisterChannelCallback();
void func_spray_00400138();
void spraySetActivationState(SprayEffectState *state, u8 enabled);
void func_spray_004002A8();
void func_spray_0040055C();
void func_spray_0040064C();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/__entrypoint_func_spray_400000.s")

#line 24 "src/modules/spray.c"
/* Unload the two original spray textures, 0x7C followed by 0x7B. */
void sprayModuleCleanup(void) {
    uvUnloadFile(0x55565458, 0x7C);
    uvUnloadFile(0x55565458, 0x7B);
}
#line 28 "src/modules/spray.c"

#line 29 "src/modules/spray.c"
/* Find channel property six and register the original spray callback
 * with null context and priority 0xC8. */
void sprayRegisterChannelCallback(s32 channel) {
    s32 callbackList;
    gUvChanExports->unk4(channel, 6, &callbackList, 0);
    gUvCbckExports->unk10(callbackList, func_spray_0040055C, 0, 0xC8);
}
#line 34 "src/modules/spray.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_00400138.s")

#line 37 "src/modules/spray.c"
/* Preserve the original activation branch: enabled states >= 2 capture
 * the shared clock; otherwise clear byte D1. Stop the shared sound and mark
 * the module active. The full C0/D1 field meanings remain unestablished. */
void spraySetActivationState(SprayEffectState *state, u8 enabled) {
    if (enabled && state->phase >= 2U) {
        state->time = D_80025D6C;
    } else {
        state->flagD1 = 0;
    }
    gSndExports->sndReleaseHandle(&D_spray_00401768);
    D_spray_004010B0 = 1;
}
#line 38 "src/modules/spray.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_004002A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040055C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040064C.s")

