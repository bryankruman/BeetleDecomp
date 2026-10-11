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
 * with no insert-before callback and priority 0xC8. */
void sprayRegisterChannelCallback(s32 channel) {
    s32 callbackList;
    gUvChanExports->unk4(channel, 6, &callbackList, 0);
    gUvCbckExports->unk10(callbackList, func_spray_0040055C, 0, 0xC8);
}
#line 34 "src/modules/spray.c"

/* Acquire the first zero-D1 record in the native eight-step, 0xD4-stride walk;
 * return null at the adjacent shared sound-state label. Reset the original
 * fields, store the selector low byte, then optionally initialize that sound
 * handle, read SND48's scalar and call SND08 with sound44, priority7FFF,
 * the returned scalar times D1050 and pitch0.5. Clear the setup request after
 * that callback returns, regardless of its result; retain record identity.
 * RE_UNKNOWN: selector/field policies, record/shared-handle reuse, ownership,
 * callback mutation and lifetime guarantees need original writers, consumers
 * and teardown. The fixed native walk does not establish all caller domains.
 * A readable draft is 252 versus 264 native bytes, with 65 differing words.
 * Frame 48 becomes 40 and the preserved record home moves 32 to 36; the compiler
 * reuses the endpoint address for the first handle call instead of reloading
 * its original label. All observed field resets, call inputs/order and flag
 * store remain represented, but 22/18 complete relocation records differ.
 * Historical source declarations/local organization remain unknown; keep
 * original assembly until every instruction and relocation matches. */
#line 35 "src/modules/spray.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_00400138.s")

#line 37 "src/modules/spray.c"
/*
 * When the low enabled byte is nonzero and the unsigned phase is at least 2,
 * copy the shared time into state offset 0xCC; otherwise clear byte 0xD1.
 * Always release the shared sound handle next and finally store 1 to the
 * shared word. The successful branch retains byte 0xD1 rather than setting it.
 * RE_UNKNOWN: The phase protocol and shared word/flag meanings remain opaque.
 */
#line 40 "src/modules/spray.c"
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
/* RE_UNKNOWN: complete spray record layout, byte D1/state C0 meaning, initialization, storage bounds, callback/resource lifetime and historical local storage. Original callback saves/restores fog around a fixed-stride pointer walk ending at the adjacent sound-state label; trace original initializer, record writers, registration and drawing helper before strengthening semantic names, bounds or safety guarantees. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040055C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/spray/func_spray_0040064C.s")

