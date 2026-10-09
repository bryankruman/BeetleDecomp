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

/* Initialize both indexed handles and prepare the shared sound handle;
 * only the first indexed handle is gated by gNumPlayers == 1. Preserve
 * callback reloads and each stored-halfword test against 255.
 * RE_ORIGINAL_QUIRK: the shared handle is prepared without a preceding reset.
 * RE_UNKNOWN: index bounds, all table/object extents and lifetimes, callback
 * replacement, historical formal/local declarations and tiny volume purpose
 * remain unresolved. Two grounded C drafts both compile to 416 bytes with
 * all ordered object relocations exact, but 13 stack words differ: frame
 * 40 versus 48 bytes, native homes 0x20/0x24 versus draft 0x24/0x28.
 * Retain ASM; no recovery or extra readability credit is claimed. */
#line 61 "src/modules/caraudio.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_004003B0.s")

/* Snapshot the inner audio-state pointer, then process/reset/recreate each
 * indexed sound handle; only the first handle is gated by gNumPlayers == 1.
 * Reload the outer slot index and sound exports after each callback, and
 * preserve the stored halfword reads before the original 255 tests.
 * RE_UNKNOWN: index bounds, source/handle extents and lifetimes, callback
 * replacement/alias domains and historical declarations remain unresolved.
 * The first natural C draft compiles to 440 bytes with all ordered object
 * relocation records exact, but 16 instruction words swap the binding and
 * inner-state saved-register roles. Retain ASM pending full byte recovery;
 * no recovery or additional readability credit is claimed. */
#line 63 "src/modules/caraudio.c"
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

/* Copy screen-record matrices into matching registry entries, then run
 * the original setting/motion-word gates and ordered audio helpers.
 * RE_ORIGINAL_QUIRK: SCRN slot 0x14 copies an unchecked live count into local
 * output; neither its provider nor this caller establishes a capacity bound.
 * RE_UNKNOWN: the shared SCRN header returns a pointer although native uses
 * a signed count word. Original local capacity, source/registry extents,
 * signed identifier domains, pointer overflow, callback replacement/lifetimes,
 * setting 0x86's meaning and historical direct-helper declarations need proof.
 * The first natural draft preserves audited effects but compiles to 428
 * versus 436 bytes with 101 differing instruction words and different
 * complete 25-record object relocation lists. Output starts at 0x50 versus
 * native 0x4C; register/loop setup and final gate block placement differ.
 * Retain ASM and old declarations; no staged C/types/prototypes are accepted
 * and no recovery or additional readability credit is claimed. */
#line 71 "src/modules/caraudio.c"
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

/* Check the first enabled matching low-byte ID in banks 0x41DC/0x41E8
 * then 0x41D8/0x41E4. Release and initialize its stride-eight sound handle,
 * reload sound exports between calls, then clear its flag and store ID 0xFF.
 * RE_ORIGINAL_QUIRK: explicit initialize follows release even though release
 * initializes a current identity; first-bank success skips the second bank.
 * RE_UNKNOWN: caller slot bounds, stored-ID meanings, table extents and
 * provider/handle lifetime guarantees need original producers and callers.
 * Historical formal/local storage remains unproved: the byte-formal draft
 * has 15 stack/frame-only differences (304 bytes, all ordered records exact).
 * The explicit word-to-byte draft has 75 differences (300/304 bytes) and
 * differing relocation sites; no omitted callback effect was identified.
 * Retain original assembly until complete instructions/records match. */
#line 95 "src/modules/caraudio.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/caraudio/func_caraudio_0040218C.s")

/* Resolve all four CARANIM material records before sequential signed16 code
 * tests. Priority is 4, then 5/6 (5 on track 7, otherwise 2), followed by
 * 12, 3, 2, 8, 9, 7, 10, 11, 1, then zero. CARANIM slot2C remaps
 * sentinel/shared-gate IDs to zero, then returns base + index * 0x1C.
 * RE_ORIGINAL_QUIRK: the first record's code-5 test appears twice in native.
 * RE_UNKNOWN: actual caller ID/record extent guarantees, material/code meanings,
 * record ownership/lifetime and historical local organization need original
 * material producers/callers. Drafts are 1252/1256 versus 1260 native bytes;
 * both have 162 differing words. Common-code registers, equality operand
 * order and branch/return lowering differ. All 17 record sites/identities
 * agree; downstream getter symbol values move with the shorter draft.
 * No supported missing callback, code width or priority effect was found.
 * Retain original assembly until complete instructions/records match. */
#line 97 "src/modules/caraudio.c"
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

/* For signed slotIndex <4, store [destination word, slotIndex] in the
 * original 8-byte slot, then copy 64 bytes from the word loaded at
 * binding+0xC, plus0x1A8, to destination word+0x10 through FMTX slot0xC.
 * Load the source word after slot writes; no lower-bound guard exists.
 * RE_UNKNOWN: historical formal types/expression, negative-index validity,
 * slot capacity/consumers and referenced storage lifetimes need evidence.
 * The inherited all-one masks remain until an exact clean reconstruction;
 * the reused word is first a stride, then an address, not an emitter ID. */
#line 168 "src/modules/caraudio.c"
void func_caraudio_00403A2C(void *binding, s32 slotIndex)
{
  s32 *slotWords;
  s32 strideOrDestinationWord;
  strideOrDestinationWord = 8;
  if (slotIndex < 4)
  {
    slotWords = (s32 *) (&D_caraudio_00404230[slotIndex * strideOrDestinationWord]);
    strideOrDestinationWord = ((((((((((((*((s32 *) (((u8 *) binding) + 0x8))) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
 slotWords[1] = slotIndex; slotWords[0] = strideOrDestinationWord;
    (*((void (**)(s32, s32)) (((u8 *) gUvFmtxExports) + 0xC)))(strideOrDestinationWord + 0x10, (*((s32 *) (((u8 *) binding) + 0xC))) + 0x1A8);
  }
}

