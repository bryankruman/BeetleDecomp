// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00; u8 first; u8 unk02; u8 second; } CarAudioVoiceIds;
typedef struct { u8 unk00[8]; CarAudioVoiceIds *voices; } CarAudioDualVoice;
extern f32 D_caraudio_00403EF4;
#include "module.h"
extern Snd_Exports *gSndExports;
extern UvFMtx_Rom_Exports *gUvFmtxExports;
#include "module.h"
#include "global_exports.h"
/*__SEEDEXTERNS__*/
extern f32 D_caraudio_004040C0[];
extern f32 D_caraudio_00404254;
void carAudioModuleCleanup();
void func_caraudio_004003B0();
void func_caraudio_00400550();
void func_caraudio_00400758();
void func_caraudio_0040090C();
void func_caraudio_00400DB4();
void func_caraudio_004010A4();
void func_caraudio_004015B8();
void func_caraudio_00401698();
void func_caraudio_0040171C();
void func_caraudio_00401A08();
void func_caraudio_00401F24();
void carAudioSetHandlePositionAndPitch(UnkStruct_004005C8 *handle, UnkStruct_uvemitter_rom_004008CC *positionState, f32 pitch);
void carAudioReleaseHandle();
void func_caraudio_00402070();
void func_caraudio_0040218C();
void func_caraudio_004022BC();
void func_caraudio_004027A8();
void func_caraudio_004029F8();
void func_caraudio_00402B20();
void carAudioUpdateDualEmitterVolume(CarAudioDualVoice *state);
void func_caraudio_00402CA4();
void func_caraudio_00402E00();
void carAudioStartFixedPositionSound(s32 arg0);
void func_caraudio_004031E0();
void func_caraudio_0040336C();
void func_caraudio_0040397C();
extern u8 D_caraudio_004041E0[];
extern s32 gCurrentTrack;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/__entrypoint_func_caraudio_400000.s")

#line 45 "src/modules/caraudio.c"
/* Run the original sound cleanup hook and unload the motion module
 * in the original order. */
void carAudioModuleCleanup(void) {
    gSndExports->sndStopAllAndRefreshReplacement();
    uvUnloadModule('motn');
}
#line 49 "src/modules/caraudio.c"

#line 50 "src/modules/caraudio.c"
/* Allocate 0x50 bytes; initialize matrix at 0x10 and store sourceRecordAddress at 0xC.
 * handleSlotIndex selects stride-8 handles. RE_UNKNOWN: source extent/lifetime and index
 * bounds need callers/0x3B0. Preserve repeated halfword 0x1C stores at 0x6 and allocation behavior. */
#line 53 "src/modules/caraudio.c"

void *carAudioAllocateState(s32 sourceRecordAddress, s32 handleSlotIndex)
{
  void *state = _uvMemAllocAlign8(0x50);
  (*((void (**)(void *)) (((u8 *) gUvFmtxExports) + 0x1C)))(((u8 *) state) + 0x10);
  *((s16 *) (((u8 *) state) + 0x6)) = 0x1C;
  *((s32 *) (((u8 *) state) + 0xC)) = sourceRecordAddress;
  *((s16 *) (((u8 *) state) + 0x6)) = 0x1C;
  func_caraudio_004003B0(state, handleSlotIndex);
  return state;
}
#line 63 "src/modules/caraudio.c"
#line 60 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004003B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400550.s")

#line 65 "src/modules/caraudio.c"
/* Use source-record word 0x1EC as the unchecked shared-scalar index,
 * then run the original audio update and dual-emitter scalar update.
 * RE_UNKNOWN: index bounds, source extent/lifetime and selector meaning need original writers/callers. */
void carAudioUpdateSharedScalarAndEmitters(void *state) {
    D_caraudio_00404254 = D_caraudio_004040C0[*(s32 *)(*(s32 *)((u8 *)state + 0xC) + 0x1EC)];
    func_caraudio_00402B20(*(s32 *)((u8 *)state + 0x14), state);
    carAudioUpdateDualEmitterVolume(state);
}
#line 70 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400758.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040090C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00400DB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004010A4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004015B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040171C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401A08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00401F24.s")

#line 86 "src/modules/caraudio.c"
#line 86 "src/modules/caraudio.c"
/* Copy source-state position through sound slot 0x80, then apply pitch at 0x88.
 * Managed-handle checks and pitch clamping remain in the sound implementation. */
void carAudioSetHandlePositionAndPitch(UnkStruct_004005C8 *handle, UnkStruct_uvemitter_rom_004008CC *positionState, f32 pitch) {
    gSndExports->sndSetHandlePositionFromState(handle, positionState);
    gSndExports->sndSetHandlePitch(handle, pitch);
}
#line 93 "src/modules/caraudio.c"
#line 92 "src/modules/caraudio.c"
#line 87 "src/modules/caraudio.c"

/* Forward the caller's managed sound handle unchanged to SND export 0x70. */
#line 89 "src/modules/caraudio.c"
#line 89 "src/modules/caraudio.c"
/* Release the managed sound handle through original sound export 0x70.
 * For a current handle, the sound module stops its emitter and resets the handle. */
void carAudioReleaseHandle(UnkStruct_004005C8 *handle) {
    gSndExports->sndReleaseHandle(handle);
}
#line 95 "src/modules/caraudio.c"
#line 94 "src/modules/caraudio.c"
#line 92 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402070.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040218C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004022BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004027A8.s")

#line 101 "src/modules/caraudio.c"
/* Test four source words at 0x2D0..0x2DC; return one on first nonzero, else zero.
 * Preserve the original unchecked state/source dereferences and short-circuit order.
 * RE_UNKNOWN: valid state/source extent/lifetime and word meanings need original producers/callers. */
s32 carAudioHasAnySourceSlot(void *state) {
    s32 *slots;

    slots = (s32 *)((u8 *)*(s32 **)((u8 *)state + 0x4) + 0x2D0);
    if (slots[0] != 0) {
        return 1;
    }
    if (slots[1] != 0) {
        return 1;
    }
    if (slots[2] != 0) {
        return 1;
    }
    if (slots[3] != 0) {
        return 1;
    }
    return 0;
}
#line 119 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004029F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402B20.s")

#line 124 "src/modules/caraudio.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_caraudio_00402C08(void) {
}
#line 126 "src/modules/caraudio.c"

#line 127 "src/modules/caraudio.c"
#line 127 "src/modules/caraudio.c"
/* Apply the original computed volume to both stored emitter IDs.
 * Preserve multiplication order and the two normalized-volume calls. */
void carAudioUpdateDualEmitterVolume(CarAudioDualVoice *state) {
    f32 volume = gSndExports->sndGetSfxVolumeScale() * (D_caraudio_00404254 * D_caraudio_00403EF4);
    gUvEmitterExports->uvEmitterSetNormalizedVolume(state->voices->first, volume);
    gUvEmitterExports->uvEmitterSetNormalizedVolume(state->voices->second, volume);
}
#line 134 "src/modules/caraudio.c"
#line 128 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402CA4.s")

#line 131 "src/modules/caraudio.c"
/* Clear the flag byte using the supplied signed slot without a range check.
 * RE_UNKNOWN: valid slot domain and flag-table extent need original callers and data layout. */
void carAudioClearSlotFlag(s32 slot) {
    D_caraudio_004041E0[slot] = 0;
}
#line 134 "src/modules/caraudio.c"

#line 135 "src/modules/caraudio.c"
/* Return the shared current-track value. */
s32 carAudioGetCurrentTrack(void) {
    return gCurrentTrack;
}
#line 138 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_00402E00.s")

#line 141 "src/modules/caraudio.c"
/* Prepare sound selector 0x1D at fixed XYZ; reject returned managed-slot byte 0xFF.
 * Sound slot 0x80 copies matrix translation; the local matrix is not retained.
 * RE_UNKNOWN: gameplay identity and shared-handle setup need assets/callers. */
extern f32 D_caraudio_00403F00;
extern f32 D_caraudio_00403F04;
extern f32 D_caraudio_00403F08;
extern UnkStruct_004005C8 D_caraudio_00404300;

#line 149 "src/modules/caraudio.c"

void carAudioStartFixedPositionSound(s32 unused) {
    u8 preparedSlotId;
    Mtx4F soundTransform;

    gUvFmtxExports->uvMat4SetIdentity(&soundTransform);
    soundTransform.m[3][0] = D_caraudio_00403F00;
    soundTransform.m[3][1] = D_caraudio_00403F04;
    soundTransform.m[3][2] = 284.0f;
    preparedSlotId = gSndExports->sndPrepareManagedSound(&D_caraudio_00404300, 0x1D, 0xBB8, 0);
    if (preparedSlotId != 0xFF) {
        gSndExports->sndSetHandleRepeatPolicyByte(&D_caraudio_00404300, 0U);
        gSndExports->sndSetHandlePositionFromState(&D_caraudio_00404300, (UnkStruct_uvemitter_rom_004008CC *) &soundTransform);
        gSndExports->sndSetHandleVolume(&D_caraudio_00404300, gSndExports->sndGetSfxVolumeScale() * D_caraudio_00403F08);
        gSndExports->sndSetHandlePitch(&D_caraudio_00404300, 0.5f);
        gSndExports->sndRequestHandlePlayback(&D_caraudio_00404300);
    }
}
#line 166 "src/modules/caraudio.c"
#line 142 "src/modules/caraudio.c"

extern void *D_caraudio_00404228;
typedef struct CarAudioCommand { s32 kind, value4, soundHandlingEnabled, valueC; u8 soundId; u8 gap11[3]; f32 volume; struct CarAudioCommand *next; } CarAudioCommand;

#line 146 "src/modules/caraudio.c"
/* Prepend kind zero; soundHandlingEnabled gates soundId/volume (SND 0x6C/0x84).
 * Original loader zeroes the head in fresh caud-image BSS before entry. RE_UNKNOWN:
 * value4/valueC roles, caller capacity and reset/freeing; trace callers and VOLT 0x0C. */
#line 149 "src/modules/caraudio.c"

void carAudioPrependCommand(s32 value4, s32 soundHandlingEnabled, s32 valueC, u8 soundId, f32 volume) {
    CarAudioCommand *node = _uvMemAllocAlign8(sizeof(CarAudioCommand));
    node->kind = 0;
    node->value4 = value4;
    node->soundHandlingEnabled = soundHandlingEnabled;
    node->valueC = valueC;
    node->soundId = soundId;
    node->volume = volume;
    node->next = D_caraudio_00404228;
    D_caraudio_00404228 = node;
}
#line 160 "src/modules/caraudio.c"
#line 159 "src/modules/caraudio.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004031E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040336C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040397C.s")

extern u8 D_caraudio_00404230[];

void func_caraudio_00403A2C(void *arg0, s32 arg1)
{
  s32 *entry;
  s32 emitter;
  emitter = 8;
  if (arg1 < 4)
  {
    entry = (s32 *) (&D_caraudio_00404230[arg1 * emitter]);
    emitter = ((((((((((((*((s32 *) (((u8 *) arg0) + 0x8))) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
 entry[1] = arg1; entry[0] = emitter;
    (*((void (**)(s32, s32)) (((u8 *) gUvFmtxExports) + 0xC)))(emitter + 0x10, (*((s32 *) (((u8 *) arg0) + 0xC))) + 0x1A8);
  }
}

