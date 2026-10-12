// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

/* Consumed original export slots only; storage stays in the original modules.
 * MISC 0x104 takes fixed f32 bounds and a raw word address, not varargs. */
typedef struct {
    u8 opaque00[8];
    void (*appendChildRow)(void *, void *);
    u8 opaque0C[0x64];
    s16 (*allocateChildGroup)(void);
    void *(*getChildGroup)(s16);
    void (*copyChildGroupText)(void *, u8 *);
    u8 opaque7C[8];
    void (*attachTextList)(void *, void *);
    u8 opaque88[0xC];
    s16 (*allocateTextList)(void);
    void *(*getTextList)(s16);
    void (*copyTextListText)(void *, u8 *);
} VictoryGuiMenuExports;
typedef struct {
    u8 opaque00[0x14];
    void (*initializeSharedWidget)(void);
    u8 opaque18[0x10];
    u8 *sharedDebugByte;
} VictoryGameGuiMenuExports;
typedef struct {
    u8 opaque00[0x104];
    void *(*createBoundScalarRow)(void *, u8 *, s16, f32, f32, s32 *, void **);
} VictoryMiscMenuExports;
extern VictoryGuiMenuExports *gUvGuiExports;
extern VictoryGameGuiMenuExports *gGameGuiExports;
extern VictoryMiscMenuExports *gMiscExports;
extern u8 D_victory_004010A0[], D_victory_004010A8[], D_victory_004010AC[];
extern u8 D_victory_004010B4[], D_victory_004010BC[], D_victory_004010C4[];
extern u8 D_victory_004010CC[], D_victory_004010D4[], D_victory_004010DC[];
extern u8 D_victory_004010E4[], D_victory_004010EC[], D_victory_004010F4[];
extern f32 D_victory_0040111C, D_victory_00401120, D_victory_00401124;
extern f32 D_victory_004011DC;
#line 3 "src/modules/victory.c"
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

/* Release the two sound handles first, then stop the two byte-sized emitter IDs,
 * retaining the original sound/emitter call and field-load order.
 * RE_ORIGINAL_QUIRK: no validity or sentinel checks and no local resets occur.
 * RE_UNKNOWN: provider ownership, repeated-stop behavior and ID lifetime require
 * caller and sound/emitter contracts before changing cleanup behavior. */
#line 14 "src/modules/victory.c"
void victoryStopSoundsAndEmitters(void) {
    gSndExports->sndReleaseHandle(&D_victory_00401240);
    gSndExports->sndReleaseHandle(&D_victory_00401248);
    gUvEmitterExports->uvEmitterStop(D_victory_00401250);
    gUvEmitterExports->uvEmitterStop(D_victory_00401251);
}
#line 20 "src/modules/victory.c"
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

/* Build the victory debug panel with camera and animation control groups.
 * Bind the original nine scalar controls in their original order.
 * RE_ORIGINAL_QUIRK: capture the host before initialization; keep unchecked
 * allocations and reload the current value-record pointer for each binding.
 * RE_UNKNOWN: the complete value-record type, selector 0x11 semantics and
 * widget ownership. Raw word addresses retain the provider's storage view. */
void victoryCreateCameraAnimationDebugControls(void) {
    void *host;
    void *panel;
    void *controlGroup;
    void *scalarWidget;

    host = gGameGuiExports->sharedDebugByte + 0x10;
    gGameGuiExports->initializeSharedWidget();
    panel = gUvGuiExports->getChildGroup(gUvGuiExports->allocateChildGroup());
    gUvGuiExports->copyChildGroupText(panel, D_victory_004010A0);
    gUvGuiExports->appendChildRow(host, panel);

    controlGroup = gUvGuiExports->getTextList(gUvGuiExports->allocateTextList());
    gUvGuiExports->copyTextListText(controlGroup, D_victory_004010A8);
    gUvGuiExports->attachTextList(panel, controlGroup);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010AC,
        0x11, 0.0f, D_victory_0040111C,
        (s32 *)((u8 *)D_victory_00401238 + 0x08), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010B4,
        0x11, 0.0f, D_victory_00401120,
        (s32 *)((u8 *)D_victory_00401238 + 0x0C), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010BC,
        0x11, 0.0f, D_victory_00401124,
        (s32 *)((u8 *)D_victory_00401238 + 0x10), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010C4,
        0x11, 0.0f, 15.0f,
        (s32 *)((u8 *)D_victory_00401238 + 0x14), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010CC,
        0x11, -10.0f, 10.0f,
        (s32 *)((u8 *)D_victory_00401238 + 0x18), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010D4,
        0x11, -10.0f, 10.0f,
        (s32 *)((u8 *)D_victory_00401238 + 0x1C), &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010DC,
        0x11, -10.0f, 10.0f,
        (s32 *)((u8 *)D_victory_00401238 + 0x20), &scalarWidget);

    controlGroup = gUvGuiExports->getTextList(gUvGuiExports->allocateTextList());
    gUvGuiExports->copyTextListText(controlGroup, D_victory_004010E4);
    gUvGuiExports->attachTextList(panel, controlGroup);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010EC,
        0x11, -5.0f, 5.0f, (s32 *)&D_victory_004011DC, &scalarWidget);
    gMiscExports->createBoundScalarRow(controlGroup, D_victory_004010F4,
        0x11, 0.0f, 3.0f,
        (s32 *)((u8 *)D_victory_00401238 + 0x04), &scalarWidget);
}
#line 21 "src/modules/victory.c"

#line 22 "src/modules/victory.c"
/* Consume the original pending victory sound for kinds zero through three.
 * Preserve tournament-unlock voice gates, per-kind volume constants and both
 * final emitter handles; invalid kinds leave every pending flag unchanged. */
void victoryPlayPendingSoundsByKind(s32 kind) {
    switch (kind) {
    case 0:
        if (D_victory_004011E4 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->sndGetSfxVolumeScale() * D_victory_00401128);
            if (gNumOpenTourns == 2) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDD,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0.5f);
            }
            D_victory_004011E4 = 0;
            return;
        }
        return;
    case 1:
        if (D_victory_004011E8 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->sndGetSfxVolumeScale() * D_victory_0040112C);
            if (gNumOpenTourns == 3) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDC,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0.5f);
            }
            D_victory_004011E8 = 0;
            return;
        }
        break;
    case 2:
        if (D_victory_004011EC != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF1,0x7FFF,gSndExports->sndGetSfxVolumeScale() * D_victory_00401130);
            if (gNumOpenTourns == 4) {
                gSndExports->sndPlayManagedSound(&D_victory_00401240,0xDE,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0.5f);
            }
            D_victory_004011EC = 0;
            return;
        }
        break;
    case 3:
        if (D_victory_004011F0 != 0) {
            gSndExports->func_snd_00401800(&D_victory_00401248,0xF2,0x7FFF,gSndExports->sndGetSfxVolumeScale() * D_victory_00401134);
            gSndExports->sndPlayManagedSound(&D_victory_00401240,0xA1,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0.5f);
            D_victory_00401250 = gSndExports->sndPlaySharedHandleWithPlaybackValue(0xD0,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0x37B1D0);
            D_victory_00401251 = gSndExports->sndPlaySharedHandleWithPlaybackValue(0xF9,0x7FFF,gSndExports->sndGetSpeechVolumeScale(),0x51F090);
            D_victory_004011F0 = 0;
        }
        break;
    }
}
#line 23 "src/modules/victory.c"

