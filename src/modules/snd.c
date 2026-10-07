#include "common.h"
#include "module.h"
#include "global_exports.h"
#include "snd.h"

typedef struct UnkStruct_snd_004064C8_s {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;  /* inferred */
    /* 0x08 */ f32 sampleRate;  /* inferred */
    /* 0x0C */ f32 unkC;  /* inferred */
    /* 0x10 */ f32 unk10; /* inferred */
    /* 0x14 */ char pad14[8];
    /* 0x1C */ s32 unk1C; /* inferred */
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 soundId; /* inferred */
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;  /* inferred */
} UnkStruct_snd_004064C8; /* size = 0x28 */

typedef struct ReplayExports_s {
    u8 pad[0x28];
    s32 (*unk28)(s32, s32);
    f32 (*unk2C)(s32, s32);
} ReplayExports;

typedef struct UnkStruct_snd_00406198_s {
    /* 0x00 */ u8 *soundName;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ f32 sampleRate;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8 unk10; 
    /* 0x11 */ u8 unk11; 
    /* 0x12 */ u8 unk12; 
    /* 0x13 */ u8 unk13; 
    /* 0x14 */ u8 unk14; 
    /* 0x15 */ u8 unk15; 
    /* 0x16 */ u8 unk16; 
    /* 0x17 */ u8 unk17; 
    /* 0x18 */ u8 unk18;      /* inferred */
} UnkStruct_snd_00406198;     /* size = 0x1C */

typedef struct UnkStruct_0040619C_s {
    s32 data[8];
} UnkStruct_0040619C;

typedef enum SoundType_e {
    SOUND_TYPE_SFX,
    SOUND_TYPE_SPEECH,
    SOUND_TYPE_UI
} SoundType;


void sndResetAllManagedSlots(void);
void sndPlayManagedSpatialSound(void *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5,
                       UnkStruct_uvemitter_rom_004008CC *arg6);
s16 sndPlayManagedSound(UnkStruct_004005C8 *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4);
void sndPlaySound(s16 arg0, s32 arg1);
s16 sndStartSilentEmitter(u8 arg0);
s32 sndResetEmitterAndReturnInvalid(s16 arg0);
void sndUpdateEmitterParameters(s16 arg0, f32 arg1, f32 arg2, f32 arg3, UnkStruct_uvemitter_rom_004008CC *arg4);
s32 sndAnyEnabledReplayAxisBeyondThreshold(s32 arg0);
s32 sndAnyEnabledReplayInput(s32 arg0);
void sndEnableReplayInputSlot(s32 arg0);
void sndDisableReplayInputSlot(s32 arg0);
void sndSetReplayInputSlotCount(s32 arg0);
void sndUpdateLatchedMenuInputSounds(void);
void sndUpdateManagedEmittersAndListeners(void);
void sndSetMusic(u16 arg0);
void sndSetMusicState(u8 arg0);
void sndSetMusicVol(s32 arg0);
void sndSetSfxVol(s32 arg0);
void sndSetSpeechVol(s32 arg0);
f32 sndGetSfxVolumeScale(void);
f32 sndGetSpeechVolumeScale(void);
void sndSetControlWord(s32 arg0);
void sndResetManagedSlot(s16 arg0);
void sndStopEmitterAndRefreshReplacement(u8 arg0);
void sndStopAllAndRefreshReplacement(void);
u8 sndAllocateManagedSlot(UnkStruct_004005C8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s16 func_snd_00401800(UnkStruct_004005C8 *arg0, s16 arg1, s32 arg2, f32 arg3);
u8 func_snd_00401914(UnkStruct_004005C8 *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5,
                     Vec3F* arg6);
s32 sndIsHandleCurrent(UnkStruct_004005C8 *arg0);
u8 sndPrepareManagedSound(UnkStruct_004005C8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void sndReleaseHandle(UnkStruct_004005C8 *arg0);
void sndRequestHandlePlayback(UnkStruct_004005C8 *arg0);
void sndSetHandleRepeatPolicyByte(UnkStruct_004005C8 *arg0, u8 arg1);
void sndSetHandlePosition(UnkStruct_004005C8 *arg0, Vec3F* arg1);
void sndSetHandlePositionFromState(UnkStruct_004005C8 *arg0, UnkStruct_uvemitter_rom_004008CC *arg1);
void sndSetHandleVolume(UnkStruct_004005C8 *arg0, f32 arg1);
void sndSetHandlePitch(UnkStruct_004005C8 *arg0, f32 arg1);
void sndSetHandlePan(UnkStruct_004005C8 *arg0, f32 arg1);
void sndSetHandleSoundId(UnkStruct_004005C8 *arg0, u8 arg1);
s16 sndGetHandleSoundId(UnkStruct_004005C8 *arg0);
f32 sndGetHandleStoredVolume(UnkStruct_004005C8 *arg0);
f32 sndGetHandleStoredPitch(UnkStruct_004005C8 *arg0);
f32 sndGetHandleStoredPan(UnkStruct_004005C8 *arg0);
void sndScaleHandleStoredVolume(UnkStruct_004005C8 *arg0, f32 arg1);
void sndScaleHandleStoredPitch(UnkStruct_004005C8 *arg0, f32 arg1);
void sndSetHandleEmitterVolumeWord(UnkStruct_004005C8 *arg0, f32 arg1);
void sndSetHandleMetadataScalar04(UnkStruct_004005C8 *arg0, f32 arg1);
f32 sndGetSoundMetadataScalar0C(s32 arg0);
s32 sndGetSoundMetadataWord04(s32 arg0);
s32 sndGetSoundSampleRate(s32 arg0);
s32 sndGetSoundRepeatPolicy(s32 arg0);
u8 *sndGetSoundName(s32 arg0);
void sndVisitAssignedSoundNames(void);
void sndInitializeHandle(UnkStruct_004005C8 *arg0);
void sndApplyAudioRoutingTable(s32 arg0);
u8 sndIsSoundSuppressed(s32 arg0);
void sndClearSoundSuppression(s32 arg0);
void sndSetSoundSuppression(s32 arg0);
void sndSuppressAndStopSound(s32 arg0);
s32 sndGetHandleFlagsOrDefault(UnkStruct_004005C8 *arg0);
void sndStopSoundWithImmediateVolumeRamp(s32 arg0);
void sndRaiseSoundVolumeWithImmediateRamp(s32 arg0, f32 arg1);
void sndSetAudioOutputMode(u8 arg0);
void sndReservedCallback(void);
void sndClearAllSoundSuppression(void);
s32 sndPlaySharedHandleWithPlaybackValue(s16 arg0, s32 arg1, f32 arg2, s32 arg3);

// .bss
s32 B_snd_004063B0[2]; // unreferenced padding
u8 D_snd_004063B8[0x100];
u8 D_snd_004064B8[4];
s32 D_snd_004064BC;
s32 D_snd_004064C0;
s32 D_snd_004064C4; // UNUSED
UnkStruct_snd_004064C8 D_snd_004064C8[40];
UnkStruct_uvemitter_rom_004008CC D_snd_00406B08;
s32 D_snd_00406B44;
u8 D_snd_00406B48[0x10];
s32 D_snd_00406B58;
void *D_snd_00406B5C;
UnkStruct_004005C8 D_snd_00406B60;
s32 sStopUiSfxUpDownFlag;
s32 sStopUiSfxLeftRightFlag;
s32 sStopUiSfxConfirmFlag;
s32 sStopUiSfxCancelFlag;

// .data
#include "snd_info.h"

u8 D_snd_00406168 = 1;
f32 sVolScale[9] = { 0.0f, 0.125f, 0.25f, 0.375f, 0.5f, 0.625f, 0.75f, 0.875f, 1.0f };
u16 sCurrentMusicId = 0xFF;
u8 sMusicPlaying = FALSE;
UnkStruct_snd_00406198 *D_snd_00406198 = D_snd_00404610;

UnkStruct_0040619C D_snd_0040619C[8] = {
    { { 0, 0x640, 0x2666, -0x2666, 0x960, 0, 0, 0 } },
    { { 0x40, 0xE10, 0x2666, -0x2666, 0xE10, 0, 0, 0x5000 } },
    { { 0x290, 0x800, 0x4000, -0x4000, 0x960, 0, 0, 0 } },
    { { 0x2D0, 0x670, 0x2000, -0x2000, 0x1130, 0, 0, 0 } },
    { { 0xA20, 0x11A0, 0x4000, -0x4000, 0x12D4, 0, 0, 0x6000 } },
    { { 0xA60, 0xEE0, 0x2000, -0x2000, 0x1680, 0, 0, 0 } },
    { { 0xEE0, 0x10C0, 0x2000, -0x2000, 0x1770, 0, 0, 0 } },
    { { 0, 0x12B0, 0, 0, 0x1900, 0, 0, 0 } },
};
UnkStruct_0040619C D_snd_0040629C[8] = {
    { { 0, 0x640, 0x2666, -0x2666, 0x2EE0, 0, 0, 0 } },
    { { 0x40, 0xE10, 0x2666, -0x2666, 0x4650, 0, 0, 0x5000 } },
    { { 0x290, 0x800, 0x4000, -0x4000, 0x53FC, 0, 0, 0 } },
    { { 0x2D0, 0x670, 0x2000, -0x2000, 0x55F0, 0, 0, 0 } },
    { { 0xA20, 0x11A0, 0x4000, -0x4000, 0x5DCA, 0, 0, 0x6000 } },
    { { 0xA60, 0xEE0, 0x2000, -0x2000, 0x6DB0, 0, 0, 0 } },
    { { 0xEE0, 0x10C0, 0x2000, -0x2000, 0x7530, 0, 0, 0 } },
    { { 0, 0x12B0, 0, 0, 0x7D00, 0, 0, 0 } },
};

// extra rodata
const char sSndDebugString[] = { "UNUSED" };
const char sSndDebugString1[] = { "ACTIVE BUT NO MODEL" };
const char sSndDebugString2[] = { "UNUSED" };

// global exports
extern ReplayExports *gReplayExports;

void __entrypoint_func_snd_400000(Snd_Exports *exports);

void __entrypoint_func_snd_400000(Snd_Exports *arg0) {
    s32 soundType;
    s32 sfxCount;
    u8 *temp_v0;
    u8 i;
    s32 j;

    uvUpdateFileAllocPtr(arg0);
    arg0->sndGetHandleFlagsOrDefault = sndGetHandleFlagsOrDefault;
    arg0->sndStopSoundWithImmediateVolumeRamp = sndStopSoundWithImmediateVolumeRamp;
    arg0->sndPlayManagedSpatialSound = sndPlayManagedSpatialSound;
    arg0->sndPlayManagedSound = sndPlayManagedSound;
    arg0->sndPlaySharedHandleWithPlaybackValue = sndPlaySharedHandleWithPlaybackValue;
    arg0->sndPlaySound = sndPlaySound;
    arg0->sndStartSilentEmitter = sndStartSilentEmitter;
    arg0->sndResetEmitterAndReturnInvalid = sndResetEmitterAndReturnInvalid;
    arg0->sndUpdateEmitterParameters = sndUpdateEmitterParameters;
    arg0->sndEnableReplayInputSlot = sndEnableReplayInputSlot;
    arg0->sndDisableReplayInputSlot = sndDisableReplayInputSlot;
    arg0->sndResetAllManagedSlots = sndResetAllManagedSlots;
    arg0->sndSetControlWord = sndSetControlWord;
    arg0->sndStopEmitterAndRefreshReplacement = sndStopEmitterAndRefreshReplacement;
    arg0->sndGetHandleStoredPan = sndGetHandleStoredPan;
    arg0->sndStopAllAndRefreshReplacement = sndStopAllAndRefreshReplacement;
    arg0->sndScaleHandleStoredVolume = sndScaleHandleStoredVolume;
    arg0->sndAllocateManagedSlot = sndAllocateManagedSlot;
    arg0->sndRaiseSoundVolumeWithImmediateRamp = sndRaiseSoundVolumeWithImmediateRamp;
    arg0->sndScaleHandleStoredPitch = sndScaleHandleStoredPitch;
    arg0->func_snd_00401800 = func_snd_00401800;
    arg0->sndSetAudioOutputMode = sndSetAudioOutputMode;
    arg0->sndSetHandleEmitterVolumeWord = sndSetHandleEmitterVolumeWord;
    arg0->func_snd_00401914 = func_snd_00401914;
    arg0->sndReservedCallback = sndReservedCallback;
    arg0->sndSetHandleMetadataScalar04 = sndSetHandleMetadataScalar04;
    arg0->sndIsHandleCurrent = sndIsHandleCurrent;
    arg0->sndGetSoundMetadataScalar0C = sndGetSoundMetadataScalar0C;
    arg0->sndPrepareManagedSound = sndPrepareManagedSound;
    arg0->sndGetSoundMetadataWord04 = sndGetSoundMetadataWord04;
    arg0->sndReleaseHandle = sndReleaseHandle;
    arg0->sndGetSoundSampleRate = sndGetSoundSampleRate;
    arg0->sndRequestHandlePlayback = sndRequestHandlePlayback;
    arg0->sndGetSoundRepeatPolicy = sndGetSoundRepeatPolicy;
    arg0->sndGetSoundName = sndGetSoundName;
    arg0->sndSetReplayInputSlotCount = sndSetReplayInputSlotCount;
    arg0->sndUpdateLatchedMenuInputSounds = sndUpdateLatchedMenuInputSounds;
    arg0->sndUpdateManagedEmittersAndListeners = sndUpdateManagedEmittersAndListeners;
    arg0->sndSetHandleRepeatPolicyByte = sndSetHandleRepeatPolicyByte;
    arg0->sndSetMusic = sndSetMusic;
    arg0->sndSetHandlePosition = sndSetHandlePosition;
    arg0->sndVisitAssignedSoundNames = sndVisitAssignedSoundNames;
    arg0->sndSetMusicState = sndSetMusicState;
    arg0->sndSetHandlePositionFromState = sndSetHandlePositionFromState;
    arg0->sndInitializeHandle = sndInitializeHandle;
    arg0->sndSetMusicVol = sndSetMusicVol;
    arg0->sndSetHandleVolume = sndSetHandleVolume;
    arg0->sndApplyAudioRoutingTable = sndApplyAudioRoutingTable;
    arg0->sndSetSfxVol = sndSetSfxVol;
    arg0->sndSetHandlePitch = sndSetHandlePitch;
    arg0->sndIsSoundSuppressed = sndIsSoundSuppressed;
    arg0->sndSetSpeechVol = sndSetSpeechVol;
    arg0->sndSetHandlePan = sndSetHandlePan;
    arg0->sndClearSoundSuppression = sndClearSoundSuppression;
    arg0->sndGetSfxVolumeScale = sndGetSfxVolumeScale;
    arg0->sndSetHandleSoundId = sndSetHandleSoundId;
    arg0->sndClearAllSoundSuppression = sndClearAllSoundSuppression;
    arg0->sndGetSpeechVolumeScale = sndGetSpeechVolumeScale;
    arg0->sndGetHandleSoundId = sndGetHandleSoundId;
    arg0->sndSetSoundSuppression = sndSetSoundSuppression;
    arg0->sndGetHandleStoredVolume = sndGetHandleStoredVolume;
    arg0->sndSuppressAndStopSound = sndSuppressAndStopSound;
    arg0->sndGetHandleStoredPitch = sndGetHandleStoredPitch;

    for (i = 1; i < 40; i++) {
        sndResetManagedSlot(i);
    }
    D_snd_00406B48[0] = -1;
    gUvFmtxExports->uvMat4SetIdentity((Mtx4F *) &D_snd_00406B08);
    gUvEmitterExports->uvEmitterLoadSoundBank(0);
    gUvCmidiExports->uvaLoadBank(0);
    sndSetMusicVol(gGameSettings->optionsMusicVol);
    sndSetSfxVol(gGameSettings->optionsSfxVol);
    sndSetSpeechVol(gGameSettings->optionsSpeechVol);
    gUvEmitterExports->uvEmitterSetGroupVolume(2U, 1.0f);
    sfxCount = SFX_TOTAL;
    for (j = 0; j < sfxCount; j++) {
        temp_v0 = sndGetSoundName(j);
        if ((temp_v0[0] == 'V') && (temp_v0[1] == '_')) {
            soundType = SOUND_TYPE_SPEECH;
        } else if ((temp_v0[0] == 'S') && (temp_v0[1] == '_')) {
            soundType = SOUND_TYPE_UI;
        } else {
            soundType = SOUND_TYPE_SFX;
        }
        // S_DRIVE is the NPC horn honk.  This reroutes the sound to the proper
        // audio bus. It seems like these patches were added because there was 
        // no time left to update the soundName strings.
        if (j == S_DRIVE) {
            soundType = SOUND_TYPE_SFX;
        }
        // Patch for routing mislabeled Beetle Battle speech sounds
        if ((j == STEALERHIT) || (j == HEALTH_GOOD1) || (j == HEALTH_GOOD2) 
            || (j == HEALTH_BAD_B1) || (j == HEALTH_BAD_B2) 
            || (j == LASTLADYBUG) || (j == FOGWEAPON) || (j == SLOWDOWN) 
            || (j == INVERT) || (j == BATTLEEXPLODE1) 
            // !@bug: They forgot to add BATTLEEXPLODE2 and BATTLEEXPLODE3
            || (j == BATTLEEXPLODE1) || (j == BATTLEEXPLODE1)) {
            soundType = SOUND_TYPE_SPEECH;
        }
        gUvEmitterExports->uvEmitterSetSoundVolumeGroup(j, soundType);
    }
}

#line 293 "src/modules/snd.c"
/* Stop/reset assigned emitters and reset managed sound slots one through 39.
 * Preserve the original slot-zero reservation and teardown order. */
void sndResetAllManagedSlots(void) {
    u8 i;

    for (i = 1; i < 0x28; i++) {
        if (D_snd_004064C8[i].unk0 >= 0.0f) {
            gUvEmitterExports->uvEmitterStop(i);
            gUvEmitterExports->uvEmitterResetSlot(i);
        }
        sndResetManagedSlot(i);
    }
}
#line 304 "src/modules/snd.c"

#line 305 "src/modules/snd.c"
/* Prepare a managed spatial sound, apply the original distance props,
 * clamp volume, pitch and pan to their original ranges, set its position
 * from caller state, and request playback. Emitter 255 means allocation failure. */
void sndPlayManagedSpatialSound(void *handle, s16 soundId, s32 priority, f32 volume, f32 pitch, f32 pan,
                       UnkStruct_uvemitter_rom_004008CC *positionState) {
    u8 emitterId;

    emitterId = sndPrepareManagedSound(handle, (s32) soundId, priority, 0x30);
    if (emitterId == 0xFF) {
        return;
    }

    gUvEmitterExports->uvEmitterProps(emitterId, 1, 1.0f, 2, 250.0f, 0);
    if (volume < 0.0f) {
        volume = 0.0f;
    } else if (volume > 1.0f) {
        volume = 1.0f;
    }
    sndSetHandleVolume(handle, volume);
    if (pitch < 0.0001f) {
        pitch = 0.0001f;
    } else if (pitch > 2.0f) {
        pitch = 2.0f;
    }
    sndSetHandlePitch(handle, pitch);
    if (pan < -1.0f) {
        pan = -1.0f;
    } else if (pan > 1.0f) {
        pan = 1.0f;
    }
    sndSetHandlePan(handle, pan);
    sndSetHandlePositionFromState(handle, positionState);
    sndRequestHandlePlayback(handle);
}
#line 336 "src/modules/snd.c"

#line 337 "src/modules/snd.c"
/* Acquire/configure a managed sound, clamp normalized volume and pitch,
 * request playback and return its slot; return byte sentinel 255 on exhaustion. */
s16 sndPlayManagedSound(UnkStruct_004005C8 *handle, s16 soundId, s32 priority, f32 volume, f32 pitch) {
    f32 var_fv0;
    f32 var_fv0_2;
    f32 var_fv1;
    u8 temp_v0;

    temp_v0 = sndPrepareManagedSound(handle, (s32) soundId, priority, 0x30);
    if (temp_v0 == 0xFF) {
        return temp_v0;
    }
    if (volume < 0.0f) {
        volume = 0.0f;
    } else if (volume > 1.0f) {
        volume = 1.0f;
    }
    sndSetHandleVolume(handle, volume);
    if (pitch < 0.0001f) {
        pitch = 0.0001f;
    } else if (pitch > 2.0f) {
        pitch = 2.0f;
    }

    sndSetHandlePitch(handle, pitch);
    sndRequestHandlePlayback(handle);
    return handle->unk4;
}
#line 363 "src/modules/snd.c"

#line 364 "src/modules/snd.c"
/* Initialize the shared handle and prepare its sound, then set pitch
 * from the sample rate, scale volume and request playback with the caller value.
 * Preserve export-based initialization and emitter-255 failure return. */
s32 sndPlaySharedHandleWithPlaybackValue(s16 soundId, s32 priority, f32 volume, s32 playbackValue) {
    u8 emitterId;

    gSndExports->sndInitializeHandle(&D_snd_00406B60);
    emitterId = sndPrepareManagedSound(&D_snd_00406B60, (s32) soundId, priority, 0x30);
    if (emitterId == 0xFF) {
        return emitterId;
    }
    gUvEmitterExports->uvEmitterSetPitch(emitterId,
                                                   (f32) sndGetSoundSampleRate((s32) soundId) / 22050.0f);
    gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, sndGetSpeechVolumeScale() * volume);
    gUvEmitterExports->uvEmitterRequestPlaybackWithValue(emitterId, playbackValue);

    return emitterId;
}
#line 379 "src/modules/snd.c"

void sndPlaySound(s16 soundId, s32 vol) {
    u8 emitterId;

    emitterId = gUvEmitterExports->uvGetEmitter();
    gUvEmitterExports->uvEmitterSetVol(emitterId, vol);
    if (emitterId != 0xFF) {
        gUvEmitterExports->uvEmitterSetSoundId(emitterId, soundId);
        gUvEmitterExports->uvEmitterSetPitch(emitterId,
                                                       (f32) sndGetSoundSampleRate(soundId) / 22050.0f);
        gUvEmitterExports->uvEmitterProps(emitterId, 5, 0x30, 0);
        gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, sndGetSfxVolumeScale() * 0.6f);
        gUvEmitterExports->uvEmitterRequestPlayback(emitterId);
    }
}

#line 395 "src/modules/snd.c"
/* Acquire an emitter, assign the byte sound ID, set zero volume and request
 * playback. Return byte sentinel 255 if no emitter is available. */
s16 sndStartSilentEmitter(u8 soundId) {
    u8 emitterId;
    s32 acquired;

    acquired = gUvEmitterExports->uvGetEmitter();
    emitterId = acquired;
    if (acquired == 0xFF) {
        return 0xFF;
    }
    gUvEmitterExports->uvEmitterSetSoundId(emitterId, soundId);
    gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, 0.0f);
    gUvEmitterExports->uvEmitterRequestPlayback(emitterId);
    return emitterId;
}
#line 409 "src/modules/snd.c"

#line 410 "src/modules/snd.c"
/* Reset a nonsentinel emitter and return byte sentinel 255. */
s32 sndResetEmitterAndReturnInvalid(s16 emitterId) {
    if (emitterId != 0xFF) {
        gUvEmitterExports->uvEmitterResetSlot(emitterId);
    }
    return 0xFF;
}
#line 416 "src/modules/snd.c"

#line 417 "src/modules/snd.c"
/* For a nonsentinel emitter, set position from source state and clamp/store
 * volume, pitch and pan in the original order. */
void sndUpdateEmitterParameters(s16 emitterId, f32 pitch, f32 volume, f32 pan, UnkStruct_uvemitter_rom_004008CC *source) {
    if (emitterId == 0xFF) {
        return;
    }

    gUvEmitterExports->uvEmitterSetPositionFromState((u8) emitterId, source);
    if (volume < 0.0f) {
        volume = 0.0f;
    } else if (volume > 1.0f) {
        volume = 1.0f;
    }
    gUvEmitterExports->uvEmitterSetNormalizedVolume((u8) emitterId, volume);
    if (pitch < 0.0001f) {
        pitch = 0.0001f;
    } else if (pitch > 2.0f) {
        pitch = 2.0f;
    }
    gUvEmitterExports->uvEmitterSetPitch((u8) emitterId, pitch);
    if (pan < -1.0f) {
        pan = -1.0f;
    } else if (pan > 1.0f) {
        pan = 1.0f;
    }
    gUvEmitterExports->uvEmitterSetPan((u8) emitterId, pan);
}
#line 442 "src/modules/snd.c"

#line 443 "src/modules/snd.c"
/* Test enabled replay-input slots for an axis magnitude greater than
 * 0.7. Preserve the two separate axis queries and strict comparisons. */
s32 sndAnyEnabledReplayAxisBeyondThreshold(s32 axis) {
    s32 slot;

    for (slot = 0; slot < D_snd_00406168; slot++) {
        if ((D_snd_004064B8[slot] == 0)
            && ((0.7f < gReplayExports->unk2C(slot, axis)) || (gReplayExports->unk2C(slot, axis) < -0.7f))) {
            return TRUE;
        }
    }
    return FALSE;
}
#line 455 "src/modules/snd.c"

#line 456 "src/modules/snd.c"
/* Return true when an enabled input slot reports the selected replay input. */
s32 sndAnyEnabledReplayInput(s32 input) {
    s32 i;

    for (i = 0; i < D_snd_00406168; i++) {
        if ((D_snd_004064B8[i] == 0) && (gReplayExports->unk28(i, input))) {
            return TRUE;
        }
    }

    return FALSE;
}
#line 467 "src/modules/snd.c"

#line 468 "src/modules/snd.c"
/* Clear the selected slot exclusion flag. The original index is unchecked. */
void sndEnableReplayInputSlot(s32 slot) {
    D_snd_004064B8[slot] = 0;
}
#line 471 "src/modules/snd.c"

#line 472 "src/modules/snd.c"
/* Set the selected slot exclusion flag. The original index is unchecked. */
void sndDisableReplayInputSlot(s32 slot) {
    D_snd_004064B8[slot] = 1;
}
#line 475 "src/modules/snd.c"

#line 476 "src/modules/snd.c"
/* Store the replay input scan count without additional bounds checks. */
void sndSetReplayInputSlotCount(s32 count) {
    D_snd_00406168 = count;
}
#line 479 "src/modules/snd.c"

#line 480 "src/modules/snd.c"
/* Play one unsuppressed menu sound per latched vertical, horizontal,
 * confirm or cancel action, clearing each latch when its input is released.
 * Preserve the original sound IDs despite their historical name mismatch. */
void sndUpdateLatchedMenuInputSounds(void) {
    if ((sndAnyEnabledReplayAxisBeyondThreshold(1) != 0) || (sndAnyEnabledReplayInput(U_JPAD | D_JPAD) != 0)) {
        if (sStopUiSfxUpDownFlag == 0) {
            if (D_snd_004063B8[S_HORN] == 0) {
                // original "S_HORN" soundName is incorrect
                // this is actually S_UP (UI select xylophone)
                sndPlaySound(S_HORN, 0x7FFF);
            }
            sStopUiSfxUpDownFlag = 1;
        }
    } else {
        sStopUiSfxUpDownFlag = 0;
    }
    if ((sndAnyEnabledReplayAxisBeyondThreshold(0) != 0) || (sndAnyEnabledReplayInput(L_JPAD | R_JPAD) != 0)) {
        if (sStopUiSfxLeftRightFlag == 0) {
            if (D_snd_004063B8[S_JOY_LR] == 0) {
                sndPlaySound(S_JOY_LR, 0x7FFF);
            }
            sStopUiSfxLeftRightFlag = 1;
        }
    } else {
        sStopUiSfxLeftRightFlag = 0;
    }
    if (sndAnyEnabledReplayInput(A_BUTTON | START_BUTTON) != 0) {
        if (sStopUiSfxConfirmFlag == 0) {
            if (D_snd_004063B8[S_CONFIRM] == 0) {
                sndPlaySound(S_CONFIRM, 0x7FFF);
            }
            sStopUiSfxConfirmFlag = 1;
        }
    } else {
        sStopUiSfxConfirmFlag = 0;
    }
    if (sndAnyEnabledReplayInput(B_BUTTON) != 0) {
        if (sStopUiSfxCancelFlag == 0) {
            if (D_snd_004063B8[S_UP] == 0) {
                // original "S_UP" soundName is incorrect
                // this is actually the "Cancel" SFX
                sndPlaySound(S_UP, 0x7FFF);
            }
            sStopUiSfxCancelFlag = 1;
        }
    } else {
        sStopUiSfxCancelFlag = 0;
    }
}
#line 526 "src/modules/snd.c"

#line 527 "src/modules/snd.c"
/* Refresh managed emitters, apply pause/menu/replay volume policy,
 * update each active screen listener from its camera state and finish the
 * emitter update. Keep the original emitter-slot and screen-array limits. */
void sndUpdateManagedEmittersAndListeners(void) {
    UnkStruct_snd_004064C8 *slot;
    u8 index;
    s32 screenStates[6];
    s32 screenCount;

    screenCount = gScrnExports->unk14(screenStates);
    gUvChanExports->uvChannelGetProperties(0, 3, &D_snd_00406B08, 0);

    for (index = 1; index < 0x28; index++) {
        slot = &D_snd_004064C8[index];
        if (slot->unk0 < 0.0f) {
            continue;
        }
        if (gUvEmitterExports->uvEmitterIsActive(index) == 0) {
            if (slot->unk0 >= 0.0f) {
                sndStopEmitterAndRefreshReplacement(index);
            }
        } else {
            if (slot->unk26 != 0) {
                gUvEmitterExports->uvEmitterSetPositionFromState(index, &D_snd_00406B08);
            }
            if (slot->unk20 < D_snd_00406B48[0]) {
                D_snd_00406B48[0] = index;
            }
        }
    }
    if ((gGameSettings->pauseFlag != 0) || (gGameSettings->unk6E9C > 0)) {
        if (gGameSettings->pauseFlag != 0) {
            if (gGameSettings->optionsMusicVol >= 2) {
                sndSetMusicVol(1);
            }
            gUvEmitterExports->uvEmitterSetGroupVolume(0U, 0.0f);
            gUvEmitterExports->uvEmitterSetGroupVolume(1U, 0.0f);
        }
        sndUpdateLatchedMenuInputSounds();
    } else {
        sndSetMusicVol(gGameSettings->optionsMusicVol);
        sndSetSpeechVol(gGameSettings->optionsSpeechVol);
        if (gGameSettings->introReplayState != 0) {
            sndSetSfxVol(0);
        } else {
            sndSetSfxVol(gGameSettings->optionsSfxVol);
        }
        D_snd_00406B5C = uvGetLoadedModule('slct');
        if (D_snd_00406B5C != NULL) {
            sndUpdateLatchedMenuInputSounds();
        }
    }

    for (index = 0; index < screenCount; index++) {
        if (screenStates[index] != 0) {
            gUvEarExports->uvEarSetVectorsFromState(index, screenStates[index] + 0x1A8);
            gUvEarExports->uvEarUpdateVelocityHistory(index);
        }
    }

    gUvEmitterExports->uvEmitterUpdateAndQueueActiveVoices(screenCount);
    gUvEmitterExports->uvEmitterApplyQueuedVoicesAndRotateLists();
}
#line 587 "src/modules/snd.c"

void sndSetMusic(u16 musicId) {
    sCurrentMusicId = musicId;
}

void sndSetMusicState(u8 state) {
    switch (state) {
        case 0:
        case 3:
            sndApplyAudioRoutingTable(0);
            if (sMusicPlaying) {
                gUvCmidiExports->uvaSeqStop();
            }

            gUvCmidiExports->uvaSetSeq(sCurrentMusicId);
            gUvCmidiExports->uvaSeqPlay();
            sMusicPlaying = TRUE;
            break;
        case 2:
        case 1:
            if (sMusicPlaying) {
                gUvCmidiExports->uvaSeqStop();
                sMusicPlaying = FALSE;
            }
    }
}

void sndSetMusicVol(s32 volLevel) {
    f32 scaledVolume;

    scaledVolume = sVolScale[volLevel];
    gUvCmidiExports->uvaSeqSetVol(scaledVolume);
    gUvAudiomgrExports->uvAudioMgrSetSequenceVolume(scaledVolume);
}

void sndSetSfxVol(s32 volLevel) {
    gUvEmitterExports->uvEmitterSetGroupVolume(0U, sVolScale[volLevel]);
}

void sndSetSpeechVol(s32 volLevel) {
    gUvEmitterExports->uvEmitterSetGroupVolume(1U, sVolScale[volLevel]);
}

#line 630 "src/modules/snd.c"
/* Return the original unity multiplier used by sound-effect callers.
 * User volume selection is applied separately through group-volume controls. */
f32 sndGetSfxVolumeScale(void) {
    return 1.0f;
}
#line 633 "src/modules/snd.c"

#line 634 "src/modules/snd.c"
/* Return the original unity multiplier used by speech callers.
 * User volume selection is applied separately through group-volume controls. */
f32 sndGetSpeechVolumeScale(void) {
    return 1.0f;
}
#line 637 "src/modules/snd.c"

#line 638 "src/modules/snd.c"
/* Store the shared sound-control word. Its detailed role remains unproven. */
void sndSetControlWord(s32 value) {
    D_snd_004064BC = value;
}
#line 641 "src/modules/snd.c"

#line 642 "src/modules/snd.c"
/* Restore the original managed-slot defaults. Valid slots are one through 39;
 * invalid indices deliberately fault in the original code. */
void sndResetManagedSlot(s16 slot) {
    UnkStruct_snd_004064C8 *state;

    if ((slot <= 0) || (slot >= 0x28)) {
        *(s32 *) 0 = 0;
    }
    state = &D_snd_004064C8[slot];
    state->unk20 = 0;
    state->soundId = 0;
    state->unk1C = 0x18;
    state->unk26 = 1;
    state->unk27 = 1;
    state->sampleRate = 1.0f;
    state->unk10 = 1.0f;
    state->unk4 = 1.0f;
    state->unk0 = -1.0f;
    state->unkC = 0.0f;
}
#line 660 "src/modules/snd.c"

#line 661 "src/modules/snd.c"
/* Stop/reset the active emitter, then refresh the replacement slot from
 * managed priorities when replacement tracking is enabled. */
void sndStopEmitterAndRefreshReplacement(u8 emitterId) {
    u8 i;

    if (gUvEmitterExports->uvEmitterIsActive(emitterId) != 0) {
        gUvEmitterExports->uvEmitterStop(emitterId);
        gUvEmitterExports->uvEmitterResetSlot(emitterId);
    }
    i = 1;
    if (D_snd_00406B48[0] == 0xFF) {
        return;
    }

    while (i < 0x28) {
        if ((D_snd_004064C8[i].unk20 >= 0) && (D_snd_004064C8[i].unk20 < 99999.0f)) {
            D_snd_00406B48[0] = i;
            return;
        }
        i++;
    }

    D_snd_00406B48[0] = 0xFF;
}
#line 683 "src/modules/snd.c"

#line 684 "src/modules/snd.c"
/* Stop/reset emitter slots one through 39 using the original replacement scan. */
void sndStopAllAndRefreshReplacement(void) {
    s16 i;

    for (i = 1; i < 0x28; i++) {
        sndStopEmitterAndRefreshReplacement(i);
    }
}
#line 691 "src/modules/snd.c"

#line 692 "src/modules/snd.c"
/* Acquire an emitter, reserving slot zero. On exhaustion use the tracked
 * replacement only for a higher-priority request; initialize sound metadata
 * and stamp the handle generation so stale handles can be detected. */
u8 sndAllocateManagedSlot(UnkStruct_004005C8 *handle, s32 soundId, s32 priority, s32 flags) {
    u8 slot;

    slot = gUvEmitterExports->uvGetEmitter();
    if (slot == 0) {
        slot = gUvEmitterExports->uvGetEmitter();
        ;
    }

    if (slot == 0xFF) {
        if (D_snd_00406B48[0] == 0xFF) {
            return 0xFF;
        }
        if (D_snd_004064C8[D_snd_00406B48[0]].unk20 >= priority) {
            handle->unk4 = slot;
            return 0xFF;
        }
        slot = D_snd_00406B48[0];
    }

    sndResetManagedSlot(slot);
    D_snd_004064C8[slot].unk0 = D_snd_004064C0++;
    D_snd_004064C8[slot].soundId = soundId;
    D_snd_004064C8[slot].unk20 = priority;
    D_snd_004064C8[slot].sampleRate = sndGetSoundSampleRate(soundId) / 22050.0f;
    D_snd_004064C8[slot].unk4 = sndGetSoundMetadataScalar0C(soundId);
    D_snd_004064C8[slot].unk1C = flags;
    handle->unk4 = slot;
    handle->unk0 = D_snd_004064C8[slot].unk0;

    return slot;
}
#line 724 "src/modules/snd.c"

s16 func_snd_00401800(UnkStruct_004005C8 *arg0, s16 arg1, s32 arg2, f32 arg3) {
    f32 temp_fv1;
    f32 var_fv0;
    u8 temp_v0;

    temp_v0 = sndPrepareManagedSound(arg0, (s32) arg1, arg2, 0);
    if (temp_v0 == 0xFF) {
        return temp_v0;
    }

    gUvEmitterExports->uvEmitterProps((u8) temp_v0, 1, 0.0f, 2, 2000.0f, 0);

    sndSetHandleVolume(arg0, arg3);
    var_fv0 *= 0; // FAKE
    temp_fv1 = sndGetSoundSampleRate(arg1) / 22050.0f;
    var_fv0 = temp_fv1;
    if (var_fv0 < 0.0001f) {
        var_fv0 = 0.0001f;
    } else if (var_fv0 > 2.0f) {
        var_fv0 = 2.0f;
    }
    sndSetHandlePitch(arg0, var_fv0);
    sndRequestHandlePlayback(arg0);
    return arg0->unk4;
}

u8 func_snd_00401914(UnkStruct_004005C8 *arg0, s16 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5,
                     Vec3F* arg6) {
    f32 temp_fv1;
    f32 var_fv0;
    u8 temp_v0;

    temp_v0 = sndPrepareManagedSound(arg0, (s32) arg1, arg2, 8);
    if (temp_v0 == 0xFF) {
        return temp_v0;
    }
    gUvEmitterExports->uvEmitterProps(temp_v0, 2, arg5, 1, arg4, 0);
    sndSetHandlePosition(arg0, arg6);
    sndSetHandleVolume(arg0, arg3);

    var_fv0 *= 0; // FAKE
    temp_fv1 = sndGetSoundSampleRate(arg1) / 22050.0f;
    var_fv0 = temp_fv1;
    if (temp_fv1 < 0.0001f) {
        var_fv0 = 0.0001f;
    } else if (temp_fv1 > 2.0f) {
        var_fv0 = 2.0f;
    }
    sndSetHandlePitch(arg0, var_fv0);
    sndRequestHandlePlayback(arg0);
    return arg0->unk4;
}

#line 778 "src/modules/snd.c"
/* Check the emitter sentinel and managed generation stamp. The handle itself
 * must be nonnull; preserve the original diagnostic call for large indices. */
s32 sndIsHandleCurrent(UnkStruct_004005C8 *handle) {
    if (handle->unk4 == 0xFF) {
        return 0;
    }
    if (handle->unk4 >= 0xFF) {
        sndVisitAssignedSoundNames();
        return 0;
    }
    if (handle->unk0 == D_snd_004064C8[handle->unk4].unk0) {
        return 1;
    }

    return 0;
}
#line 792 "src/modules/snd.c"

#line 793 "src/modules/snd.c"
/* Acquire a current managed handle when needed and configure the emitter
 * from stored metadata. Preserve original repeat-policy/sentinel paths,
 * including null returning zero and the deliberate fault for slot zero. */
u8 sndPrepareManagedSound(UnkStruct_004005C8 *handle, s32 soundId, s32 priority, s32 flags) {
    if (handle == NULL) {
        return 0U;
    }
    if (handle->unk4 == 0) {
        *(s32 *) 0 = 0; // fault
    }
    if (sndIsHandleCurrent(handle) == 0) {
        if (sndAllocateManagedSlot(handle, soundId, priority, flags) == 0xFF) {
            return 0xFFU;
        }
    } else if (D_snd_004064C8[handle->unk4].unk27 == 0) {
        return handle->unk4;
    } else if (sndGetSoundRepeatPolicy(soundId) != 0) {
        return handle->unk4;
    }

    if (soundId >= 0xFF) {
        return 0xFFU;
    }

    gUvEmitterExports->uvEmitterSetSoundId(handle->unk4, (u8) D_snd_004064C8[handle->unk4].soundId);
    gUvEmitterExports->uvEmitterProps(handle->unk4, 5, D_snd_004064C8[handle->unk4].unk1C, 2,
                                                   1000.0f, 1, 0.0f, 0);
    gUvEmitterExports->uvEmitterSetNormalizedVolume(handle->unk4, D_snd_004064C8[handle->unk4].unk10);
    gUvEmitterExports->uvEmitterSetPan(handle->unk4, D_snd_004064C8[handle->unk4].unkC);
    gUvEmitterExports->uvEmitterSetPitch(handle->unk4, D_snd_004064C8[handle->unk4].sampleRate);
    gUvEmitterExports->uvEmitterSetVol(handle->unk4, D_snd_004064C8[handle->unk4].unk20);

    return handle->unk4;
}
#line 824 "src/modules/snd.c"

#line 825 "src/modules/snd.c"
/* For a current handle, stop its emitter and restore the invalid handle state. */
void sndReleaseHandle(UnkStruct_004005C8 *handle) {
    if (sndIsHandleCurrent(handle) != 0) {
        sndStopEmitterAndRefreshReplacement(handle->unk4);
        sndInitializeHandle(handle);
    }
}
#line 831 "src/modules/snd.c"

#line 832 "src/modules/snd.c"
/* Request emitter playback only when the managed handle generation is current. */
void sndRequestHandlePlayback(UnkStruct_004005C8 *handle) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterRequestPlayback(handle->unk4);
    }
}
#line 837 "src/modules/snd.c"

#line 838 "src/modules/snd.c"
/* Store the original repeat-policy byte at offset 0x27 for a current handle. */
void sndSetHandleRepeatPolicyByte(UnkStruct_004005C8 *handle, u8 policy) {
    if (sndIsHandleCurrent(handle) != 0) {
        D_snd_004064C8[handle->unk4].unk27 = policy;
    }
}
#line 843 "src/modules/snd.c"

#line 844 "src/modules/snd.c"
/* Set explicit emitter position for a current handle and clear source-state mode. */
void sndSetHandlePosition(UnkStruct_004005C8 *handle, Vec3F* position) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterSetPosition(handle->unk4, position);
        D_snd_004064C8[handle->unk4].unk26 = 0;
    }
}
#line 850 "src/modules/snd.c"

#line 851 "src/modules/snd.c"
/* Read emitter position from the supplied source state for a current handle
 * and clear its original source-state mode byte. */
void sndSetHandlePositionFromState(UnkStruct_004005C8 *handle, UnkStruct_uvemitter_rom_004008CC *source) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterSetPositionFromState(handle->unk4, source);
        D_snd_004064C8[handle->unk4].unk26 = 0;
    }
}
#line 857 "src/modules/snd.c"

#line 858 "src/modules/snd.c"
/* Set emitter normalized volume for a current handle; clamping is delegated
 * to the emitter interface. */
void sndSetHandleVolume(UnkStruct_004005C8 *handle, f32 volume) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterSetNormalizedVolume(handle->unk4, volume);
    }
}
#line 863 "src/modules/snd.c"

#line 864 "src/modules/snd.c"
/* For a current handle, clamp pitch to [0.0001, 2] and update its emitter. */
void sndSetHandlePitch(UnkStruct_004005C8 *handle, f32 pitch) {
    if (sndIsHandleCurrent(handle) != 0) {
        if (pitch < 0.0001f) {
            pitch = 0.0001f;
        } else if (pitch > 2.0f) {
            pitch = 2.0f;
        }
        gUvEmitterExports->uvEmitterSetPitch(handle->unk4, pitch);
    }
}
#line 874 "src/modules/snd.c"

#line 875 "src/modules/snd.c"
/* For a current handle, clamp pan to [-1, 1] and update its emitter. */
void sndSetHandlePan(UnkStruct_004005C8 *handle, f32 pan) {
    if (sndIsHandleCurrent(handle) != 0) {
        if (pan < -1.0f) {
            pan = -1.0f;
        } else if (pan > 1.0f) {
            pan = 1.0f;
        }
        gUvEmitterExports->uvEmitterSetPan(handle->unk4, pan);
    }
}
#line 885 "src/modules/snd.c"

#line 886 "src/modules/snd.c"
/* Assign the byte sound ID to the emitter of a current managed handle. */
void sndSetHandleSoundId(UnkStruct_004005C8 *handle, u8 soundId) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterSetSoundId(handle->unk4, soundId);
    }
}
#line 891 "src/modules/snd.c"

#line 892 "src/modules/snd.c"
/* Return -1 for null/all-ones handles, the managed sound ID for a current
 * handle, or zero for a stale handle. */
s16 sndGetHandleSoundId(UnkStruct_004005C8 *handle) {
    if ((handle == (UnkStruct_004005C8 *) -1) || (handle == NULL)) {
        return -1;
    }
    if (sndIsHandleCurrent(handle) != 0) {
        return D_snd_004064C8[handle->unk4].soundId;
    }
    return 0;
}
#line 901 "src/modules/snd.c"

#line 902 "src/modules/snd.c"
/* Return the managed stored volume field for a current handle, otherwise zero. */
f32 sndGetHandleStoredVolume(UnkStruct_004005C8 *handle) {
    if (sndIsHandleCurrent(handle) != 0) {
        return D_snd_004064C8[handle->unk4].unk10;
    }
    return 0.0f;
}
#line 908 "src/modules/snd.c"

#line 909 "src/modules/snd.c"
/* Return the managed stored pitch/sample-rate factor for a current handle,
 * otherwise zero. */
f32 sndGetHandleStoredPitch(UnkStruct_004005C8 *handle) {
    if (sndIsHandleCurrent(handle) != 0) {
        return D_snd_004064C8[handle->unk4].sampleRate;
    }
    return 0.0f;
}
#line 915 "src/modules/snd.c"

#line 916 "src/modules/snd.c"
/* Return the managed stored pan field for a current handle, otherwise -1. */
f32 sndGetHandleStoredPan(UnkStruct_004005C8 *handle) {
    if (sndIsHandleCurrent(handle) != 0) {
        return D_snd_004064C8[handle->unk4].unkC;
    }
    return -1.0f;
}
#line 922 "src/modules/snd.c"

#line 923 "src/modules/snd.c"
/* For a current handle, scale its stored volume, clamp to [0, 1] and apply
 * the result to the emitter. Preserve the original floating evaluation order. */
void sndScaleHandleStoredVolume(UnkStruct_004005C8 *handle, f32 factor) {
    UnkStruct_snd_004064C8 *temp_v0;
    f32 volume;

    if (sndIsHandleCurrent(handle) != 0) {
        volume = D_snd_004064C8[handle->unk4].unk10 * factor;
        if (volume < 0.0f) {
            volume = 0.0f;
        } else if (volume > 1.0f) {
            volume = 1.0f;
        }
        D_snd_004064C8[handle->unk4].unk10 = volume;
        gUvEmitterExports->uvEmitterSetNormalizedVolume(handle->unk4, volume);
    }
}
#line 938 "src/modules/snd.c"

#line 939 "src/modules/snd.c"
/* For a current handle, scale its stored pitch, clamp to [0.0001, 2] and
 * apply the result to the emitter. */
void sndScaleHandleStoredPitch(UnkStruct_004005C8 *handle, f32 factor) {
    UnkStruct_snd_004064C8 *state;
    f32 pitch;
    f32 var_fv1;

    if (sndIsHandleCurrent(handle) != 0) {
        state = &D_snd_004064C8[handle->unk4];
        pitch = state->sampleRate * factor;
        if (pitch < 0.0001f) {
            pitch = 0.0001f;
        } else if (pitch > 2.0f) {
            pitch = 2.0f;
        }
        state->sampleRate = pitch;
        gUvEmitterExports->uvEmitterSetPitch(handle->unk4, pitch);
    }
}
#line 956 "src/modules/snd.c"

#line 957 "src/modules/snd.c"
/* Convert the float to the original integer emitter-volume word for a
 * current handle. No new clamping is introduced. */
void sndSetHandleEmitterVolumeWord(UnkStruct_004005C8 *handle, f32 volumeWord) {
    if (sndIsHandleCurrent(handle) != 0) {
        gUvEmitterExports->uvEmitterSetVol(handle->unk4, (s32) volumeWord);
    }
}
#line 962 "src/modules/snd.c"

#line 963 "src/modules/snd.c"
/* Store the managed metadata scalar at offset four for a current handle;
 * this is distinct from the live emitter volume. */
void sndSetHandleMetadataScalar04(UnkStruct_004005C8 *handle, f32 value) {
    if (sndIsHandleCurrent(handle) != 0) {
        D_snd_004064C8[handle->unk4].unk4 = value;
    }
}
#line 968 "src/modules/snd.c"

#line 969 "src/modules/snd.c"
/* Return the sound-table scalar at offset 0xC with original unchecked indexing. */
f32 sndGetSoundMetadataScalar0C(s32 soundId) {
    return D_snd_00406198[soundId].unkC;
}
#line 972 "src/modules/snd.c"

#line 973 "src/modules/snd.c"
/* Return the sound-table word at offset four with original unchecked indexing. */
s32 sndGetSoundMetadataWord04(s32 soundId) {
    return D_snd_00406198[soundId].unk4;
}
#line 976 "src/modules/snd.c"

#line 977 "src/modules/snd.c"
/* Map the selected sound metadata to its stored sample-rate field.
 * Sound-table validity and index bounds remain caller-owned. */
s32 sndGetSoundSampleRate(s32 soundId) {
    return D_snd_00406198[soundId].sampleRate;
}
#line 980 "src/modules/snd.c"

#line 981 "src/modules/snd.c"
/* Return the sound-table repeat-policy value with original narrowing/indexing. */
s32 sndGetSoundRepeatPolicy(s32 soundId) {
    return (s32) D_snd_00406198[soundId].unk18;
}
#line 984 "src/modules/snd.c"

#line 985 "src/modules/snd.c"
/* Return the sound name for a nonnegative index or null for negative input.
 * The original routine has no upper-bound check. */
u8 *sndGetSoundName(s32 soundId) {
    if (soundId >= 0) {
        return D_snd_00406198[soundId].soundName;
    }
    return NULL;
}
#line 991 "src/modules/snd.c"

#line 992 "src/modules/snd.c"
/* Visit names of managed/active emitter sounds through the original accessor.
 * Preserve the original discarded return values and slot-zero reservation. */
void sndVisitAssignedSoundNames(void) {
    u8 i;
    u8 temp_v0_2;

    for (i = 1; i < 0x28; i++) {
        if (D_snd_004064C8[i].unk0 >= 0.0f) {
            sndGetSoundName((s32) D_snd_004064C8[i].soundId);
        }
        if (gUvEmitterExports->uvEmitterIsActive(i) != 0) {
            temp_v0_2 = gUvEmitterExports->uvEmitterGetSoundId(i);
            if (temp_v0_2 != 0xFF) {
                sndGetSoundName(temp_v0_2);
            }
        }
    }
}
#line 1008 "src/modules/snd.c"

#line 1009 "src/modules/snd.c"
/* Set the byte-invalid emitter sentinel and generation -1. A null handle
 * deliberately faults in the original code. */
void sndInitializeHandle(UnkStruct_004005C8 *handle) {
    if (handle == NULL) {
        *(s32 *) 0 = 0;
        return;
    }
    handle->unk4 = 0xFF;
    handle->unk0 = -1.0f;
}
#line 1017 "src/modules/snd.c"

#line 1018 "src/modules/snd.c"
/* Select the original routing table by mode and apply its eight-by-eight
 * values through the audio-manager interface. */
void sndApplyAudioRoutingTable(s32 mode) {
    s32 i;
    s32 j;
    UnkStruct_0040619C *table;

    if (mode == 1) {
        D_snd_00406B58 = mode;
        table = D_snd_0040629C;
    } else {
        D_snd_00406B58 = mode;
        table = D_snd_0040619C;
    }

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            gUvAudiomgrExports->uvAudioMgrSetEffectsMatrixParameter(i, j, table[i].data[j]);
        }
    }
}
#line 1037 "src/modules/snd.c"

#line 1038 "src/modules/snd.c"
/* Return the caller-indexed sound suppression byte without new bounds checks. */
u8 sndIsSoundSuppressed(s32 soundId) {
    return D_snd_004063B8[soundId];
}
#line 1041 "src/modules/snd.c"

#line 1042 "src/modules/snd.c"
/* Clear the caller-indexed sound suppression byte. */
void sndClearSoundSuppression(s32 soundId) {
    D_snd_004063B8[soundId] = 0;
}
#line 1045 "src/modules/snd.c"

#line 1046 "src/modules/snd.c"
/* Clear the original 255-entry sound suppression table. */
void sndClearAllSoundSuppression(void) {
    s32 i;

    for (i = 0; i < 0xFF; i++) {
        D_snd_004063B8[i] = 0;
    }
}
#line 1053 "src/modules/snd.c"

#line 1054 "src/modules/snd.c"
/* Set the caller-indexed sound suppression byte. */
void sndSetSoundSuppression(s32 soundId) {
    D_snd_004063B8[soundId] = 1;
}
#line 1057 "src/modules/snd.c"

#line 1058 "src/modules/snd.c"
/* Mark the sound suppressed, enumerate playing sounds and stop/reset its
 * matching managed or raw emitters. Preserve the original list and slot bounds. */
void sndSuppressAndStopSound(s32 soundId) {
    s32 count;
    s32 i;
    s32 j;
    s32 soundIds[32];
    s32 volumes[32];

    sndSetSoundSuppression(soundId);
    count = gUvEmitterExports->uvEmitterGetPlayingSoundsAndVolumes(soundIds, volumes);

    for (i = 0; i < count; i++) {
        if (soundId == soundIds[i]) {
            for (j = 1; j < 40; j++) {
                if (D_snd_004064C8[j].soundId == soundIds[i]) {
                    gUvEmitterExports->uvEmitterSetNormalizedVolume(j, 0.0f);
                    gUvEmitterExports->uvEmitterStop(j);
                    sndStopEmitterAndRefreshReplacement(j);
                } else {
                    if (gUvEmitterExports->uvEmitterGetSoundId(j) == soundIds[i]) {
                        gUvEmitterExports->uvEmitterSetNormalizedVolume(j, 0.0f);
                        gUvEmitterExports->uvEmitterStop(j);
                        gUvEmitterExports->uvEmitterResetSlot(j);
                    }
                }
            }
        }
    }
}
#line 1086 "src/modules/snd.c"

#line 1087 "src/modules/snd.c"
/* Return stored flags for a current handle or default 0x18 for null,
 * all-ones or stale handles. */
s32 sndGetHandleFlagsOrDefault(UnkStruct_004005C8 *handle) {
    if ((handle == (UnkStruct_004005C8 *) -1) || (handle == NULL)) {
        return 0x18;
    }
    if (sndIsHandleCurrent(handle) != 0) {
        return D_snd_004064C8[handle->unk4].unk1C;
    }
    return 0x18;
}
#line 1096 "src/modules/snd.c"

#line 1097 "src/modules/snd.c"
/* For the requested playing sound, lower each matching emitter volume
 * synchronously in 0.1 steps, then stop and reset it using the original
 * managed/unmanaged slot paths. This loop does not wait between steps. */
void sndStopSoundWithImmediateVolumeRamp(s32 soundId) {
    s32 playingIndex;
    s32 emitterId;
    s32 playingCount;
    s32 playingSounds[32];
    s32 playingVolumes[32];
    f32 volume;
    playingCount = gUvEmitterExports->uvEmitterGetPlayingSoundsAndVolumes(playingSounds, playingVolumes);
    for (playingIndex = 0; playingIndex < playingCount; playingIndex++) {
        if (soundId == playingSounds[playingIndex]) {
            for (emitterId = 1; emitterId < 40; emitterId++) {
                if (D_snd_004064C8[emitterId].soundId == playingSounds[playingIndex]) {
                    while (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) > 0.0f) {
                        volume = gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) - 0.1f;
                        if (volume < 0.0f) {
                            volume = 0.0f;
                        } else if (volume > 1.0f) {
                            volume = 1.0f;
                        }
                        gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, volume);
                    }

                    if (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) == 0.0f) {
                        gUvEmitterExports->uvEmitterStop(emitterId);
                        sndStopEmitterAndRefreshReplacement(emitterId);
                    }
                } else {
                    if (gUvEmitterExports->uvEmitterGetSoundId(emitterId) == playingSounds[playingIndex]) {
                        while (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) > 0.0f) {
                            volume = gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) - 0.1f;
                            if (volume < 0.0f) {
                                volume = 0.0f;
                            } else if (volume > 1.0f) {
                                volume = 1.0f;
                            }
                            gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, volume);
                        }
                        if (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) == 0.0f) {
                            gUvEmitterExports->uvEmitterStop(emitterId);
                            gUvEmitterExports->uvEmitterResetSlot(emitterId);
                        }
                    }
                }
            }
        }
    }
}
#line 1144 "src/modules/snd.c"

#line 1145 "src/modules/snd.c"
/* Raise matching playing emitters synchronously in 0.001 steps.
 * Preserve the original clamp to zero through one: a target above one
 * cannot be reached and would leave the original loop running indefinitely. */
void sndRaiseSoundVolumeWithImmediateRamp(s32 soundId, f32 targetVolume) {
    s32 playingCount;
    f32 volume;
    s32 playingIndex;
    s32 playingSounds[32];
    s32 playingVolumes[32];
    s32 emitterId;

    playingCount = gUvEmitterExports->uvEmitterGetPlayingSoundsAndVolumes(playingSounds, playingVolumes);
    for (playingIndex = 0; playingIndex < playingCount; playingIndex++) {
        if (soundId == playingSounds[playingIndex]) {
            for (emitterId = 1; emitterId < 40; emitterId++) {
                if (D_snd_004064C8[emitterId].soundId == playingSounds[playingIndex]) {
                    while (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) < targetVolume) {
                        volume = gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) + 0.001f;
                        if (volume < 0.0f) {
                            volume = 0.0f;
                        } else if (volume > 1.0f) {
                            volume = 1.0f;
                        }
                        gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, volume);
                    }
                } else {
                    if (gUvEmitterExports->uvEmitterGetSoundId(emitterId) == playingSounds[playingIndex]) {
                        while (gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) < targetVolume) {
                            volume = gUvEmitterExports->uvEmitterGetNormalizedVolume(emitterId) + 0.001f;
                            if (volume < 0.0f) {
                                volume = 0.0f;
                            } else if (volume > 1.0f) {
                                volume = 1.0f;
                            }
                            gUvEmitterExports->uvEmitterSetNormalizedVolume(emitterId, volume);
                        }
                    }
                }
            }
        }
    }
}
#line 1184 "src/modules/snd.c"

#line 1185 "src/modules/snd.c"
/* Map nonzero input to audio-manager mode one and zero to mode two. */
void sndSetAudioOutputMode(u8 enabled) {
    if (enabled) {
        gUvAudiomgrExports->uvAudioMgrSetOutputMode(1);
    } else {
        gUvAudiomgrExports->uvAudioMgrSetOutputMode(2);
    }
}
#line 1192 "src/modules/snd.c"

#line 1193 "src/modules/snd.c"
/* Original empty sound callback; retain its entry point. */
void sndReservedCallback(void) {
}
#line 1195 "src/modules/snd.c"

s32 D_0040639C[] = { 0x00FC0000, __entrypoint_func_snd_400000, 0, 0, 0 };