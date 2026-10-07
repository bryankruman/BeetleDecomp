// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

typedef struct Emitter_s {
    /* 0x00 */ Vec3F unk0;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ Vec3F unk24;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 vol;
    /* 0x38 */ u8 soundId;
    /* 0x39 */ char pad39[7]; /* maybe part of soundId[8]? */
    /* 0x40 */ f64 unk40;
    /* 0x48 */ Vec3F unk48;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 far;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 playPitch;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 playVolume;
    /* 0x80 */ u8 playVoice;
    /* 0x81 */ u8 playPan;
    /* 0x82 */ s8 playMix;
    /* 0x83 */ u8 unk83;
    /* 0x84 */ s32 unk84; /* inferred */
    /* 0x88 */ u8 active; // Active
} Emitter; /* size = 0x8C */

typedef struct EmitterSettings_s {
    /* 0x00 */ u16 unk0; /* inferred */
    /* 0x02 */ u16 unk2; /* inferred */
    /* 0x04 */ u16 unk4; /* inferred */
    /* 0x06 */ char pad6[2];
    /* 0x08 */ u32 unk8;   /* inferred */
    /* 0x0C */ void *unkC; /* inferred */
} EmitterSettings;         /* size = 0x10 */

extern EmitterSettings *D_uvemitter_rom_00402BF4;

void uvEmitterModuleCleanup(void);
void uvEmitterInit(Emitter *obj);
u8 uvGetEmitter(void);
void uvEmitterResetSlot(u8 arg0);
void uvEmitterSetSoundId(u8 arg0, u8 arg1);
u8 uvEmitterGetSoundId(u8 arg0);
void uvEmitterSetPosition(u8 arg0, Vec3F *arg1);
void uvEmitterSetPositionFromState(u8 arg0, UnkStruct_uvemitter_rom_004008CC *arg1);
void uvEmitterGetPosition(u8 arg0, Vec3F *arg1);
void uvEmitterWritePositionState(u8 arg0, Unkstruct_uvemitter_rom_00400970 *arg1);
void uvEmitterSetVelocity(u8 arg0, Vec3F arg1);
void uvEmitterGetVelocity(u8 arg0, Vec3F *arg1);
void uvEmitterSetLineSegment(u8 arg0, Vec3F arg1, Vec3F arg4);
void uvEmitterSetNormalizedVolume(u8 arg0, f32 arg1);
f32 uvEmitterGetNormalizedVolume(u8 arg0);
void uvEmitterSetPan(u8 arg0, f32 arg1);
f32 uvEmitterGetPan(u8 arg0);
void uvEmitterSetPitch(u8 arg0, f32 arg1);
f32 uvEmitterGetPitch(u8 arg0);
void uvEmitterSetMix(u8 arg0, f32 arg1);
void uvEmitterSetVol(u8 arg0, s32 arg1);
void uvEmitterProps(u8 objId, ...);
void uvEmitterRequestPlayback(u8 arg0);
void uvEmitterRequestPlaybackWithValue(u8 arg0, s32 arg1);
void uvEmitterStop(u8 arg0);
void uvEmitterStopAssignedWhenRequested(u8 arg0);
void uvEmitterUpdateAndQueueActiveVoices(s32 arg0);
void func_uvemitter_rom_0040156C(u8 arg0, s16 arg1);
s32 uvEmitterHandleVoiceCompletion(Emitter *arg0);
void uvEmitterInsertVoiceByPlaybackPriority(u8 arg0);
void uvEmitterReleaseVoiceAndMaybeRestart(u8 arg0);
void uvEmitterApplyQueuedVoicesAndRotateLists(void);
void _uvaStartVoice(Emitter *arg0);
void _uvaUpdateVoice(Emitter *arg0);
void _uvaStopVoice(Emitter *arg0);
void uvEmitterLoadSoundBank(s32 arg0);
f32 uvEmitterGetLineDistanceSquared(Vec3F arg0, Emitter *arg3, Vec3F *arg4);
s32 uvEmitterIsActive(u8 arg0);
s32 uvEmitterGetPlaybackRequest(u8 arg0);
s32 uvEmitterGetPlayingSoundsAndVolumes(s32 *arg0, s32 *arg1);
s16 uvEmitterGetBankInstrumentCount(void);
f32 uvEmitterComputeDopplerRatio(Vec3F arg0, Vec3F arg3, Vec3F arg6, f32 arg9);
void uvEmitterStopAllAndDisable(void);
void uvEmitterReservedCallback(void);
void uvEmitterSetQuietSoundList(u8 *arg0);
void uvEmitterSetSoundVolumeGroup(u8 arg0, u8 arg1);
u8 uvEmitterGetSoundVolumeGroup(u8 arg0);
void uvEmitterSetGroupVolume(u8 arg0, f32 arg1);

extern u8 *D_uvemitter_rom_00402A78;
extern s32 D_uvemitter_rom_00402A84;
extern ALSndPlayer *D_uvemitter_rom_00402A10;
extern u8 *D_uvemitter_rom_00402A74;
extern ALBankFile *D_uvemitter_rom_00402BB8;
extern s16 *sVoiceTable;
extern void *D_uvemitter_rom_00402BDC;
extern u16 D_uvemitter_rom_00402BF8;
extern u16 sMaxVoices;
extern u16 D_uvemitter_rom_00402BD0;
extern Emitter *D_uvemitter_rom_00402B94;
extern UvMath_Exports *sMathExports;
extern UvFVec_Rom_Exports *sFvecExports;
extern UvFMtx_Rom_Exports *sFMtxExports;
extern UvAudioMgr_Exports *sAudioMgrExports;
extern UvEar_Rom_Exports *sUvEarExports;
extern f32 D_uvemitter_rom_00402A00;
extern s32 D_uvemitter_rom_00402C08[];
extern s32 D_uvemitter_rom_00403004;
extern s32 D_uvemitter_rom_00402B98;
extern s32 D_uvemitter_rom_00402BC4;
extern f32 D_uvemitter_rom_00402BC8;
extern f32 D_uvemitter_rom_00402BCC;
extern f64 D_uvemitter_rom_00402C00;
extern f32 D_uvemitter_rom_00402A04;
extern u8 D_uvemitter_rom_00402A88[];
extern f32 D_uvemitter_rom_00402B88[];
extern u8 *D_uvemitter_rom_00403008;
extern u8 *D_uvemitter_rom_00402A7C;
extern s32 D_uvemitter_rom_00402A80;
extern ALBank *D_uvemitter_rom_00402BB4;
extern ALInstrument *D_uvemitter_rom_00402BBC;
extern ALSndpConfig D_uvemitter_rom_00402BA8;
extern u16 D_uvemitter_rom_00402BD4;
extern u32 D_uvemitter_rom_00402BD8;
extern EmitterSettings *D_uvemitter_rom_00402BF4;

void __entrypoint_func_uvemitter_rom_400000(UvEmitter_Exports *exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->uvGetEmitter = uvGetEmitter;
    exports->uvEmitterResetSlot = uvEmitterResetSlot;
    exports->uvEmitterSetSoundId = uvEmitterSetSoundId;
    exports->uvEmitterGetSoundId = uvEmitterGetSoundId;
    exports->uvEmitterSetPosition = uvEmitterSetPosition;
    exports->uvEmitterSetPositionFromState = uvEmitterSetPositionFromState;
    exports->uvEmitterGetPosition = uvEmitterGetPosition;
    exports->uvEmitterWritePositionState = uvEmitterWritePositionState;
    exports->uvEmitterSetVelocity = uvEmitterSetVelocity;
    exports->uvEmitterModuleCleanup = uvEmitterModuleCleanup;
    exports->uvEmitterGetVelocity = uvEmitterGetVelocity;
    exports->uvEmitterProps = uvEmitterProps;
    exports->uvEmitterSetLineSegment = uvEmitterSetLineSegment;
    exports->uvEmitterGetPlayingSoundsAndVolumes = uvEmitterGetPlayingSoundsAndVolumes;
    exports->uvEmitterRequestPlayback = uvEmitterRequestPlayback;
    exports->uvEmitterSetNormalizedVolume = uvEmitterSetNormalizedVolume;
    exports->uvEmitterGetBankInstrumentCount = uvEmitterGetBankInstrumentCount;
    exports->uvEmitterRequestPlaybackWithValue = uvEmitterRequestPlaybackWithValue;
    exports->uvEmitterGetNormalizedVolume = uvEmitterGetNormalizedVolume;
    exports->uvEmitterStopAllAndDisable = uvEmitterStopAllAndDisable;
    exports->uvEmitterStop = uvEmitterStop;
    exports->uvEmitterSetPan = uvEmitterSetPan;
    exports->uvEmitterReservedCallback = uvEmitterReservedCallback;
    exports->uvEmitterStopAssignedWhenRequested = uvEmitterStopAssignedWhenRequested;
    exports->uvEmitterGetPan = uvEmitterGetPan;
    exports->uvEmitterSetQuietSoundList = uvEmitterSetQuietSoundList;
    exports->uvEmitterUpdateAndQueueActiveVoices = uvEmitterUpdateAndQueueActiveVoices;
    exports->uvEmitterSetPitch = uvEmitterSetPitch;
    exports->uvEmitterSetSoundVolumeGroup = uvEmitterSetSoundVolumeGroup;
    exports->uvEmitterApplyQueuedVoicesAndRotateLists = uvEmitterApplyQueuedVoicesAndRotateLists;
    exports->uvEmitterGetPitch = uvEmitterGetPitch;
    exports->uvEmitterGetSoundVolumeGroup = uvEmitterGetSoundVolumeGroup;
    exports->uvEmitterLoadSoundBank = uvEmitterLoadSoundBank;
    exports->uvEmitterSetMix = uvEmitterSetMix;
    exports->uvEmitterSetGroupVolume = uvEmitterSetGroupVolume;
    exports->uvEmitterIsActive = uvEmitterIsActive;
    exports->uvEmitterSetVol = uvEmitterSetVol;
    exports->uvEmitterGetPlaybackRequest = uvEmitterGetPlaybackRequest;

    D_uvemitter_rom_00402BF4 = uvGetSystemProp(4);
    if (D_uvemitter_rom_00402BF4 == NULL) {
        D_uvemitter_rom_00402BD0 = 0xA;
        sMaxVoices = 0x100;
        D_uvemitter_rom_00402BD8 = 0;
        D_uvemitter_rom_00402BDC = NULL;
    } else {
        if (D_uvemitter_rom_00402BF4->unk0 != 0) {
            D_uvemitter_rom_00402BD0 = D_uvemitter_rom_00402BF4->unk0;
        } else {
            D_uvemitter_rom_00402BD0 = 0xA;
        }
        if (D_uvemitter_rom_00402BF4->unk2 != 0) {
            sMaxVoices = D_uvemitter_rom_00402BF4->unk2;
        } else {
            sMaxVoices = 0x10;
        }
        if (D_uvemitter_rom_00402BF4->unk4 != 0) {
            D_uvemitter_rom_00402BD4 = D_uvemitter_rom_00402BF4->unk4;
        } else {
            D_uvemitter_rom_00402BD4 = 0x100;
        }
        D_uvemitter_rom_00402BD8 = D_uvemitter_rom_00402BF4->unk8;
        D_uvemitter_rom_00402BDC = D_uvemitter_rom_00402BF4->unkC;
    }
    if (D_uvemitter_rom_00402BD8 == 0) {
        if (D_uvemitter_rom_00402BD8 == 0) {
            D_uvemitter_rom_00402BD8 =
                (D_uvemitter_rom_00402BD4 * 0x1C) + (sMaxVoices * 0x30) + 0x64;
        }
        D_uvemitter_rom_00402BF8 |= 1;
        D_uvemitter_rom_00402BDC = _uvMemAllocAlign8(D_uvemitter_rom_00402BD8);
    }
    sMathExports = uvLoadModule('MATH');
    sFvecExports = uvLoadModule('FVEC');
    sFMtxExports = uvLoadModule('FMTX');
    sAudioMgrExports = uvLoadModule('AMGR');
    sUvEarExports = uvLoadModule('AEAR');
    D_uvemitter_rom_00402A74 = _uvMemAlloc(sMaxVoices * 3, 0x10U);
    uvMemSet(D_uvemitter_rom_00402A74, 0U, sMaxVoices * 3);
    D_uvemitter_rom_00402A7C = &D_uvemitter_rom_00402A74[sMaxVoices];
    D_uvemitter_rom_00402A78 = (sMaxVoices * 2) + D_uvemitter_rom_00402A74;
    D_uvemitter_rom_00402B94 = _uvMemAlloc(D_uvemitter_rom_00402BD0 * 0x90, 0x10U);
    uvMemSet(D_uvemitter_rom_00402B94, 0U, D_uvemitter_rom_00402BD0 * 0x90);

    for (i = 0; i < D_uvemitter_rom_00402BD0; i++) {
        uvEmitterInit(&D_uvemitter_rom_00402B94[i]);
        D_uvemitter_rom_00402C08[i] = 1;
    }

    for (i = 0; i < sMaxVoices; i++) {
        D_uvemitter_rom_00402A74[i] = 0xFF;
        D_uvemitter_rom_00402A7C[i] = 0xFF;
    }

    D_uvemitter_rom_00402A80 = 0;
    uvMemSet(D_uvemitter_rom_00402BDC, 0U, D_uvemitter_rom_00402BD8);
    alHeapInit((ALHeap *) &D_uvemitter_rom_00402B98, (u8 *) D_uvemitter_rom_00402BDC,
               (s32) D_uvemitter_rom_00402BD8);
    D_uvemitter_rom_00402BA8.maxSounds = (s32) sMaxVoices;
    D_uvemitter_rom_00402BA8.maxEvents = D_uvemitter_rom_00402BD4;
    D_uvemitter_rom_00402BA8.heap = (ALHeap *) &D_uvemitter_rom_00402B98;
    alSndpNew(D_uvemitter_rom_00402A10, &D_uvemitter_rom_00402BA8);
    uvClkReset(0x6A);
    D_uvemitter_rom_00402C00 = uvClkGetSec(0x6A);
}

#line 247 "src/modules/uvemitter_rom.c"
/* Stop all voices, destroy the sound player, free owned voice/bank/emitter
 * arrays and unload the five dependencies. Only free the audio heap when owned. */
void uvEmitterModuleCleanup(void) {
    uvEmitterStopAllAndDisable();
    alSndpDelete(D_uvemitter_rom_00402A10);
    _uvMemFree(sVoiceTable);
    _uvMemFree(D_uvemitter_rom_00402BB8);
    _uvMemFree(D_uvemitter_rom_00402B94);
    _uvMemFree(D_uvemitter_rom_00402A74);
    if (D_uvemitter_rom_00402BF8 & 1) {
        _uvMemFree(D_uvemitter_rom_00402BDC);
    }
    uvUnloadModule('MATH');
    uvUnloadModule('FVEC');
    uvUnloadModule('FMTX');
    uvUnloadModule('AMGR');
    uvUnloadModule('AEAR');
}
#line 263 "src/modules/uvemitter_rom.c"

void uvEmitterInit(Emitter *obj) {
    obj->playVoice = sMaxVoices + 1;
    obj->unk78 = 0;
    obj->playVolume = 0x7FFF;
    obj->playPan = 0x40;
    obj->playMix = 0;
    obj->unk83 = 0;
    obj->active = 0;
    obj->soundId = -1;
    obj->vol = 0;
    obj->unk64 = 0;
    obj->unk84 = 0;
    obj->unk58 = 0;
    obj->playPitch = 1.0f;
    obj->unk30 = 1.0f;
    obj->unk68 = 1.0f;
    obj->unk54 = 1.0f;
    obj->unk0.x = 0.0f;
    obj->unk0.y = 0.0f;
    obj->unk0.z = 0.0f;
    obj->unkC = 0.0f;
    obj->unk10 = 0.0f;
    obj->unk14 = 0.0f;
    obj->unk18 = 0.0f;
    obj->unk1C = 0.0f;
    obj->unk20 = 0.0f;
    obj->unk24.x = 0.0f;
    obj->unk24.y = 0.0f;
    obj->unk24.z = 0.0f;
    obj->unk48.x = 0.0f;
    obj->unk48.y = 0.0f;
    obj->unk48.z = 0.0f;
    obj->unk6C = 0.0f;
    obj->unk70 = 0.0f;
    obj->unk5C = 0.0f;
    obj->far = 1000.0f;
    obj->unk40 = -1.0;
}

u8 uvGetEmitter(void) {
    u8 i;

    for (i = 0; i < D_uvemitter_rom_00402BD0; i++) {
        if (D_uvemitter_rom_00402B94[i].active == 0) {
            D_uvemitter_rom_00402B94[i].active = 1;
            return i;
        }
    }
    return 0xFF;
}

#line 315 "src/modules/uvemitter_rom.c"
/* For an in-range byte index, stop its voice and restore emitter defaults. */
void uvEmitterResetSlot(u8 emitterId) {
    Emitter *emitter;

    if (emitterId < D_uvemitter_rom_00402BD0) {
        emitter = &D_uvemitter_rom_00402B94[emitterId];
        _uvaStopVoice(emitter);
        uvEmitterInit(emitter);
    }
}
#line 324 "src/modules/uvemitter_rom.c"

#line 325 "src/modules/uvemitter_rom.c"
/* Stop the previous voice and assign the byte sound ID. Sentinel 0xFF
 * first resets the slot; preserve the original second stop call afterward. */
void uvEmitterSetSoundId(u8 emitterId, u8 soundId) {
    Emitter *emitter;

    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        if (soundId == 0xFF) {
            uvEmitterResetSlot(emitterId);
        }
        emitter = &D_uvemitter_rom_00402B94[emitterId];
        _uvaStopVoice(emitter);
        emitter->soundId = soundId;
    }
}
#line 337 "src/modules/uvemitter_rom.c"

#line 338 "src/modules/uvemitter_rom.c"
/* Return the sound ID or 0xFF for an out-of-range byte index. */
u8 uvEmitterGetSoundId(u8 emitterId) {
    if (emitterId >= (s32) D_uvemitter_rom_00402BD0) {
        return 0xFFU;
    }
    return D_uvemitter_rom_00402B94[emitterId].soundId;
}
#line 344 "src/modules/uvemitter_rom.c"

#line 345 "src/modules/uvemitter_rom.c"
/* Copy the source position into an in-range emitter. */
void uvEmitterSetPosition(u8 emitterId, Vec3F *position) {
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402B94[emitterId].unk0 = *position;
    }
}
#line 350 "src/modules/uvemitter_rom.c"

#line 351 "src/modules/uvemitter_rom.c"
/* Read the source state vector at offset 0x30 and set emitter position. */
void uvEmitterSetPositionFromState(u8 emitterId, UnkStruct_uvemitter_rom_004008CC *state) {
    Vec3F position;

    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        position.x = state->unk30.x;
        position.y = state->unk30.y;
        position.z = state->unk30.z;
        uvEmitterSetPosition((u8) emitterId, (Vec3F *) &position);
    }
}
#line 361 "src/modules/uvemitter_rom.c"

#line 362 "src/modules/uvemitter_rom.c"
/* Copy an in-range emitter position to the output; invalid IDs leave it alone. */
void uvEmitterGetPosition(u8 emitterId, Vec3F *position) {
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        *position = D_uvemitter_rom_00402B94[emitterId].unk0;
    }
}
#line 367 "src/modules/uvemitter_rom.c"

#line 368 "src/modules/uvemitter_rom.c"
/* Initialize the output matrix and write the three position fields.
 * Preserve the original output layout; this is not a contiguous Vec3F store. */
void uvEmitterWritePositionState(u8 emitterId, Unkstruct_uvemitter_rom_00400970 *state) {
    if (emitterId < D_uvemitter_rom_00402BD0) {
        sFMtxExports->uvMat4SetIdentity(&state->unk0);
        state->unkC0 = D_uvemitter_rom_00402B94[emitterId].unk0.x;
        state->unkD0 = D_uvemitter_rom_00402B94[emitterId].unk0.y;
        state->unkE0 = D_uvemitter_rom_00402B94[emitterId].unk0.z;
    }
}
#line 376 "src/modules/uvemitter_rom.c"

#line 377 "src/modules/uvemitter_rom.c"
/* Store explicit velocity by value and disable automatic position-derived
 * velocity for this in-range emitter. */
void uvEmitterSetVelocity(u8 emitterId, Vec3F velocity) {
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402C08[emitterId] = 0;
        D_uvemitter_rom_00402B94[emitterId].unk24 = velocity;
    }
}
#line 383 "src/modules/uvemitter_rom.c"

#line 384 "src/modules/uvemitter_rom.c"
/* Copy the current velocity of an in-range emitter to the output. */
void uvEmitterGetVelocity(u8 emitterId, Vec3F *velocity) {
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        *velocity = D_uvemitter_rom_00402B94[emitterId].unk24;
    }
}
#line 389 "src/modules/uvemitter_rom.c"

#line 390 "src/modules/uvemitter_rom.c"
/* Copy segment endpoints and store the normalized start-to-end direction.
 * A zero-length segment leaves the old direction untouched. */
void uvEmitterSetLineSegment(u8 emitterId, Vec3F start, Vec3F end) {
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    Emitter *emitter;
    f32 length;

    emitter = &D_uvemitter_rom_00402B94[emitterId];
    if (!(emitterId < D_uvemitter_rom_00402BD0)) {
        return;
    }

    sFvecExports->uvVec3FCopy(&emitter->unk0, (Vec3F *) &start);
    sFvecExports->uvVec3FCopy((Vec3F *) &emitter->unkC, (Vec3F *) &end);
    diffX = emitter->unkC - emitter->unk0.x;
    diffY = emitter->unk10 - emitter->unk0.y;
    diffZ = emitter->unk14 - emitter->unk0.z;
    length = sMathExports->uvSqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
    if (length != 0.0f) {
        emitter->unk18 = diffX / length;
        emitter->unk1C = diffY / length;
        emitter->unk20 = diffZ / length;
    }
}
#line 414 "src/modules/uvemitter_rom.c"

#line 415 "src/modules/uvemitter_rom.c"
/* Clamp the volume factor to [0, 1], then store it for an in-range emitter.
 * Preserve original comparison behavior for non-finite values. */
void uvEmitterSetNormalizedVolume(u8 emitterId, f32 volume) {
    if (volume < 0.0f) {
        volume = 0.0f;
    }
    if (volume > 1.0f) {
        volume = 1.0f;
    }
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402B94[emitterId].unk30 = volume;
    }
}
#line 426 "src/modules/uvemitter_rom.c"

#line 427 "src/modules/uvemitter_rom.c"
/* Return the stored volume factor, or zero for an out-of-range byte index. */
f32 uvEmitterGetNormalizedVolume(u8 emitterId) {
    if (emitterId >= (s32) D_uvemitter_rom_00402BD0) {
        return 0.0f;
    }
    return D_uvemitter_rom_00402B94[emitterId].unk30;
}
#line 433 "src/modules/uvemitter_rom.c"

#line 434 "src/modules/uvemitter_rom.c"
/* Clamp manual pan to [-1, 1] and store it for an in-range emitter. */
void uvEmitterSetPan(u8 emitterId, f32 pan) {
    if (pan < -1.0f) {
        pan = -1.0f;
    }
    if (pan > 1.0f) {
        pan = 1.0f;
    }
    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402B94[emitterId].unk6C = pan;
    }
}
#line 445 "src/modules/uvemitter_rom.c"

#line 446 "src/modules/uvemitter_rom.c"
/* Return manual pan. The caller must supply a valid emitter index;
 * unlike the corresponding setter, this getter has no bounds check. */
f32 uvEmitterGetPan(u8 emitterId) {
    return D_uvemitter_rom_00402B94[emitterId].unk6C;
}
#line 449 "src/modules/uvemitter_rom.c"

#line 450 "src/modules/uvemitter_rom.c"
/* For a valid emitter, replace nonpositive pitch with the original minimum
 * and clamp values above two. Preserve ordered comparisons. */
void uvEmitterSetPitch(u8 emitterId, f32 pitch) {
    if (!(emitterId < (s32) D_uvemitter_rom_00402BD0)) {
        return;
    }

    if (pitch <= 0.0f) {
        pitch = D_uvemitter_rom_00402A00;
    }
    if (pitch > 2.0f) {
        pitch = 2.0f;
    }
    D_uvemitter_rom_00402B94[emitterId].unk68 = pitch;
}
#line 463 "src/modules/uvemitter_rom.c"

#line 464 "src/modules/uvemitter_rom.c"
/* Return the stored pitch factor without checking the caller-owned index. */
f32 uvEmitterGetPitch(u8 emitterId) {
    return D_uvemitter_rom_00402B94[emitterId].unk68;
}
#line 467 "src/modules/uvemitter_rom.c"

#line 468 "src/modules/uvemitter_rom.c"
/* Clamp the explicit audio mix factor to [0, 1] and store it in range. */
void uvEmitterSetMix(u8 emitterId, f32 mix) {
    if (mix < 0.0f) {
        mix = 0.0f;
    }
    if (mix > 1.0f) {
        mix = 1.0f;
    }
    if (emitterId < D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402B94[emitterId].unk70 = mix;
    }
}
#line 479 "src/modules/uvemitter_rom.c"

void uvEmitterSetVol(u8 playVoice, s32 vol) {
    if (vol < 0) {
        vol = 0;
    }
    if (vol >= 0x8000) {
        vol = 0x7FFF;
    }
    if (playVoice < D_uvemitter_rom_00402BD0) {
        D_uvemitter_rom_00402B94[playVoice].vol = vol;
    }
}

void uvEmitterProps(u8 objId, ...) {
    f32 temp_fv0;
    va_list args;
    Emitter *obj;
    s32 prop;

    if ((objId >= D_uvemitter_rom_00402BD0) || (objId == 0xFF)) {
        return;
    }

    if (args) {
    }
    obj = &D_uvemitter_rom_00402B94[objId];
    // passing an object that undergoes default argument promotion to 'va_start'
    // has undefined behavior (e.g. u8, u16, f32)
#if defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"
#endif
    va_start(args, objId);
#if defined(__clang__)
#pragma GCC diagnostic pop
#endif

    while (TRUE) {
        prop = va_arg(args, s32);
        switch (prop) { /* irregular */
            case 0:
                return;
            case 1:
                temp_fv0 = va_arg(args, f64);
                obj->unk5C = SQ(temp_fv0);
                break;
            case 2:
                temp_fv0 = va_arg(args, f64);
                obj->far = SQ(temp_fv0);
                break;
            case 5:
                obj->unk64 = va_arg(args, s32);
                break;
            default:
                return;
        }
    }
}

#line 538 "src/modules/uvemitter_rom.c"
/* When globally enabled and the sound ID is valid, set playback request 0x10. */
void uvEmitterRequestPlayback(u8 emitterId) {
    Emitter *temp_v0;

    if ((D_uvemitter_rom_00403004 == 0) && (emitterId < (s32) D_uvemitter_rom_00402BD0)) {
        if (D_uvemitter_rom_00402B94[emitterId].soundId != 0xFF) {
            D_uvemitter_rom_00402B94[emitterId].unk84 = 0x10;
        }
    }
}
#line 547 "src/modules/uvemitter_rom.c"

#line 548 "src/modules/uvemitter_rom.c"
/* When globally enabled and the emitter is in range, set request 0x20
 * and its associated integer. The integer meaning remains unproven. */
void uvEmitterRequestPlaybackWithValue(u8 emitterId, s32 requestValue) {
    if ((D_uvemitter_rom_00403004 == 0) && (emitterId < (s32) D_uvemitter_rom_00402BD0)) {
        D_uvemitter_rom_00402B94[emitterId].unk84 = 0x20;
        D_uvemitter_rom_00402B94[emitterId].unk58 = requestValue;
    }
}
#line 554 "src/modules/uvemitter_rom.c"

#line 555 "src/modules/uvemitter_rom.c"
/* Stop the in-range voice and clear its request. Flag 0x20 also resets
 * the emitter to defaults. */
void uvEmitterStop(u8 emitterId) {
    Emitter *emitter;

    if (emitterId < (s32) D_uvemitter_rom_00402BD0) {
        emitter = &D_uvemitter_rom_00402B94[emitterId];
        _uvaStopVoice(emitter);
        emitter->unk84 = 0;
        if (emitter->unk64 & 0x20) {
            uvEmitterInit(emitter);
        }
    }
}
#line 567 "src/modules/uvemitter_rom.c"

#line 568 "src/modules/uvemitter_rom.c"
/* Walk assigned sound slots; a nonzero argument marks flag 0x20 and stops
 * each one. The original count accumulator is not returned. */
void uvEmitterStopAssignedWhenRequested(u8 resetAssigned) {
    u8 i;
    s32 shouldReset = resetAssigned;

    for (resetAssigned = 0, i = 0; i < D_uvemitter_rom_00402BD0; i++) {
        if (D_uvemitter_rom_00402B94[i].soundId == 0xFF) {
            continue;
        }

        if (shouldReset) {
            D_uvemitter_rom_00402B94[i].unk64 |= 0x20;
            uvEmitterStop(i);
        }
        resetAssigned++;
    }
}
#line 584 "src/modules/uvemitter_rom.c"

#line 585 "src/modules/uvemitter_rom.c"
/* Refresh shared audio settings, update active emitter positions and
 * velocities once per timestamp, then stop, restart or queue voices
 * under the original state and timeout rules. */
void uvEmitterUpdateAndQueueActiveVoices(s32 listenerSelection) {
    Emitter *emitter;
    f32 elapsedSeconds;
    s32 i;
    Vec3F position;
    Vec3F velocity;

    sFvecExports->uvVec3FSet(&position, 0.0f, 0.0f, 0.0f);
    sFvecExports->uvVec3FSet(&velocity, 0.0f, 0.0f, 0.0f);
    sAudioMgrExports->uvAudioMgrGetOutputMode(&D_uvemitter_rom_00402BC4);
    sAudioMgrExports->uvAudioMgrGetEffectsVolume(&D_uvemitter_rom_00402BC8);
    sAudioMgrExports->uvAudioMgrGetSharedScalar40(&D_uvemitter_rom_00402BCC);
    func_8000D7F0(&D_uvemitter_rom_00402B98);
    for (i = 0; i < D_uvemitter_rom_00402BD0; i++) {
        emitter = &D_uvemitter_rom_00402B94[i];
        D_uvemitter_rom_00402C00 = uvClkGetSec(0x6A);
        if (D_uvemitter_rom_00402C00 == emitter->unk40) {
            continue;
        }

        if ((emitter->active == 1)
            && (((emitter->unk78 == 1)) || (emitter->unk78 == 2) || (emitter->unk78 == 8) || ((emitter->unk84 == 0x10))
                || (emitter->unk84 == 0x20))) {
            if (emitter->unk78 == 2) {
                emitter->unk83++;
            }
            if ((emitter->unk78 == 8) || (emitter->unk84 == 0x10)) {
                sFvecExports->uvVec3FCopy(&position, &emitter->unk0);
                if (D_uvemitter_rom_00402C08[i] != 0) {
                    elapsedSeconds = (f32) (D_uvemitter_rom_00402C00 - emitter->unk40);
                    sFvecExports->uvVec3FSub(&velocity, &position, &emitter->unk48);
                    sFvecExports->uvVec3FScale(&velocity, &velocity, 1.0f / elapsedSeconds);
                } else {
                    sFvecExports->uvVec3FCopy(&velocity, &emitter->unk24);
                }
                sFvecExports->uvVec3FCopy(&emitter->unk48, &position);
                sFvecExports->uvVec3FCopy(&emitter->unk24, &velocity);
            }
            func_uvemitter_rom_0040156C(i, listenerSelection);
            if ((emitter->playVolume == 0) || ((emitter->unk78 == 2) && ((s32) emitter->unk83 >= 5))) {
                if (emitter->unk64 & 0x10) {
                    uvEmitterStop(i);
                } else {
                    uvEmitterStop(i);
                    uvEmitterRequestPlayback(i);
                }
            } else if (uvEmitterHandleVoiceCompletion(emitter) == 0) {
                uvEmitterInsertVoiceByPlaybackPriority(i);
            }
        }
        emitter->unk40 = D_uvemitter_rom_00402C00;
    }
}
#line 638 "src/modules/uvemitter_rom.c"

void func_uvemitter_rom_0040156C(u8 arg0, s16 arg1) {
    s32 var_v1;
    f32 var_fa1;
    f32 var_ft4;
    f32 var_fa0;
    Vec3F sp8C;
    Vec3F sp80;
    Vec3F sp74;
    Vec3F sp68;
    f32 sp64;
    s32 sp48;
    Emitter *obj;
    s32 sp58;
    s32 i;

    sp64 = 1.0f;
    obj = &D_uvemitter_rom_00402B94[arg0];
    sp58 = obj->unk64;
    if (sp58 & 8) {
        if (arg1 == 0) {
            *(s32 *) 0 = 0; // fault
        }

        sp48 = sUvEarExports->uvEarFindNearestSlot(arg1, &obj->unk0);
        sUvEarExports->uvEarGetPosition(sp48, &sp8C);
        sUvEarExports->uvEarGetSecondaryVector(sp48, &sp80);
        sUvEarExports->uvEarGetVelocity(sp48, &sp74);
        if (sp58 & 2) {
            var_ft4 = uvEmitterGetLineDistanceSquared(sp8C, obj, &sp68);
        } else if (sp58 & 1) {
            /* Empty */
        } else {
            sp68.x = sp8C.x - obj->unk0.x;
            sp68.y = sp8C.y - obj->unk0.y;
            sp68.z = sp8C.z - obj->unk0.z;
            var_ft4 = SQ(sp68.x) + SQ(sp68.y) + SQ(sp68.z);
            sp64 = obj->unk54;
            if ((sp58 & 0x40) && (var_ft4 > 0.0f)) {
                sp64 *= uvEmitterComputeDopplerRatio(sp68, sp74, obj->unk24, 330.0f);
            }
        }
        if (obj->far < var_ft4) {
            obj->playPan = 0x40;
            obj->playVolume = 0;
            obj->playPitch = obj->unk68;
            return;
        }
        if (var_ft4 <= obj->unk5C) {
            var_fa1 = D_uvemitter_rom_00402B94[arg0].unk30;
        } else {
            var_fa1 = (obj->unk30 * (obj->far - var_ft4)) / (obj->far - obj->unk5C);
        }
        if ((D_uvemitter_rom_00402BC4 != 1) && (var_ft4 != 0.0f)) {
            var_fa0 = sFvecExports->uvVec3FScalarProj((Vec3F *) &sp68, &sp80);
            if (var_ft4 < obj->unk5C) {
                var_fa0 *= (var_ft4 / obj->unk5C);
            }

            var_v1 = (s32) ((1.0f - var_fa0) * 64.0f);
            if (var_v1 == 0x80) {
                var_v1 = 0x7F;
            }
        } else {
            var_v1 = 0x40;
        }
    } else {
        var_fa1 = obj->unk30;
        if (D_uvemitter_rom_00402BC4 != 1) {
            var_v1 = (s32) ((obj->unk6C + 1.0f) * 64.0f);
            if (var_v1 == 0x80) {
                var_v1 = 0x7F;
            }
        } else {
            var_v1 = 0x40;
        }
    }
    if (sp58 & 4) {
        obj->playMix = (s8) (s32) (D_uvemitter_rom_00402BCC * 127.0f);
    } else {
        obj->playMix = (s8) (s32) (obj->unk70 * 127.0f);
    }
    obj->playPitch = obj->unk68 * sp64;
    obj->playPan = (s8) var_v1;

    obj->playVolume = (s32) (D_uvemitter_rom_00402B88[D_uvemitter_rom_00402A88[obj->soundId]] * var_fa1
                        * D_uvemitter_rom_00402BC8 * D_uvemitter_rom_00402A04);

    if (D_uvemitter_rom_00403008 == NULL) {
        return;
    }

    for (i = 0; D_uvemitter_rom_00403008[i] != 0xFF; i++) {
        if (D_uvemitter_rom_00403008[i] == obj->soundId) {
            break;
        }
    }

    if (D_uvemitter_rom_00403008[i] != 0xFF) {
        obj->playVolume = 3;
    }
}

#line 741 "src/modules/uvemitter_rom.c"
/* For playback state eight, inspect the underlying sound-player state.
 * Completed flag-0x10 voices reset/finish; others request another start.
 * Preserve the original fault for an invalid sound-player target. */
s32 uvEmitterHandleVoiceCompletion(Emitter *emitter) {
    s32 unused;

    if (emitter->unk78 == 8) {
        alSndpSetSound(D_uvemitter_rom_00402A10, emitter->playVoice);
        if (D_uvemitter_rom_00402A10->target == -1) {
            *(s32 *) 0 = 0; // fault
        }
        if (alSndpGetState(D_uvemitter_rom_00402A10) == 0) {
            if (emitter->unk64 & 0x10) {
                emitter->playVoice = sMaxVoices + 1;
                emitter->unk78 = 0;
                if (emitter->unk64 & 0x20) {
                    uvEmitterInit(emitter);
                }
                return 1;
            }

            emitter->playVoice = sMaxVoices + 1;
            emitter->unk78 = 0;
            emitter->unk83 = 0;
            emitter->unk84 = 0x10;
            return 0;
        }
    }
    return 0;
}
#line 768 "src/modules/uvemitter_rom.c"

#line 769 "src/modules/uvemitter_rom.c"
/* Insert the emitter into the descending playback-priority queue.
 * Release the lowest-priority voice when full, retain the original
 * equal-priority order and update the existing voice-to-emitter mapping. */
void uvEmitterInsertVoiceByPlaybackPriority(u8 emitterId) {
    Emitter *emitter;
    Emitter *queuedEmitter;
    s32 i;
    s32 inserted;
    s32 priority;
    s32 j;
    s32 queuedPriority;

    emitter = &D_uvemitter_rom_00402B94[emitterId];

    if (sMaxVoices < D_uvemitter_rom_00402A80) {
        *(s32 *) 0 = 0; // fault
    }

    priority = emitter->playVolume + emitter->vol;
    if (emitter->playVolume == 0) {
        priority = 0;
    }
    i = 0;
    inserted = FALSE;
    while ((i < D_uvemitter_rom_00402A80) && !(inserted)) {
        queuedEmitter = &D_uvemitter_rom_00402B94[D_uvemitter_rom_00402A74[i]];
        queuedPriority = queuedEmitter->playVolume + queuedEmitter->vol;
        if (queuedPriority < priority) {
            inserted = TRUE;
            if (D_uvemitter_rom_00402A80 == sMaxVoices) {
                uvEmitterReleaseVoiceAndMaybeRestart(D_uvemitter_rom_00402A74[D_uvemitter_rom_00402A80 - 1]);
                D_uvemitter_rom_00402A80--;
            }

            for (j = D_uvemitter_rom_00402A80; j > i; j--) {
                D_uvemitter_rom_00402A74[j] = D_uvemitter_rom_00402A74[j - 1];
            }

            D_uvemitter_rom_00402A74[i] = emitterId;
            D_uvemitter_rom_00402A80++;
            if (emitter->playVoice != (sMaxVoices + 1)) {
                D_uvemitter_rom_00402A7C[emitter->playVoice] = emitterId;
            }
        }
        i++;
    }
    if (inserted == 0) {
        if (i == sMaxVoices) {
            uvEmitterReleaseVoiceAndMaybeRestart(emitterId);
            return;
        }
        D_uvemitter_rom_00402A74[i] = emitterId;
        D_uvemitter_rom_00402A80++;
        if ((sMaxVoices + 1) != D_uvemitter_rom_00402B94[emitterId].playVoice) {
            D_uvemitter_rom_00402A7C[D_uvemitter_rom_00402B94[emitterId].playVoice] = emitterId;
        }
    }
}
#line 824 "src/modules/uvemitter_rom.c"

#line 825 "src/modules/uvemitter_rom.c"
/* Release the voice-to-emitter mapping when assigned. Flag 0x10 stops
 * the emitter; other emitters stop their voice and request playback again. */
void uvEmitterReleaseVoiceAndMaybeRestart(u8 emitterId) {
    Emitter *emitter;

    emitter = &D_uvemitter_rom_00402B94[emitterId];
    if (emitter->playVoice != (sMaxVoices + 1)) {
        D_uvemitter_rom_00402A7C[emitter->playVoice] = 0xFF;
    }
    if (emitter->unk64 & 0x10) {
        uvEmitterStop(emitterId);
        return;
    }
    _uvaStopVoice(emitter);
    uvEmitterRequestPlayback(emitterId);
}
#line 839 "src/modules/uvemitter_rom.c"

#line 840 "src/modules/uvemitter_rom.c"
/* Start, check or update each queued voice according to its original
 * state. Copy the submitted queue to the previous queue, clear the
 * pending and voice-mapping arrays and reset the pending count. */
void uvEmitterApplyQueuedVoicesAndRotateLists(void) {
    Emitter *emitter;
    u8 emitterId;
    s32 i;
    s32 j;

    for (i = 0; i < D_uvemitter_rom_00402A80; i++) {
        emitterId = D_uvemitter_rom_00402A74[i];
        emitter = &D_uvemitter_rom_00402B94[emitterId];
        switch (emitter->unk78) {
            case 0:
                for (j = 0; D_uvemitter_rom_00402A7C[j] != 0xFF && j < sMaxVoices - 1;
                     j++) {
                }
                D_uvemitter_rom_00402A7C[j] = emitterId;
                emitter->playVoice = j;
                _uvaStartVoice(emitter);
                break;
            case 1:
                _uvaStartVoice(emitter);
                break;
            case 2:
                alSndpSetSound(D_uvemitter_rom_00402A10, sVoiceTable[emitter->playVoice]);
                if (D_uvemitter_rom_00402A10->target == -1) {
                    *(s32 *) 0 = 0; // fault
                }
                if (alSndpGetState(D_uvemitter_rom_00402A10) == 1) {
                    emitter->unk78 = 8;
                    emitter->unk83 = 0;
                }
                break;
            case 8:
                _uvaUpdateVoice(emitter);
                break;
        }
    }

    i = 0;
    D_uvemitter_rom_00402A84 = D_uvemitter_rom_00402A80;
    for (; i < sMaxVoices; i++) {
        *(D_uvemitter_rom_00402A78 + i) = D_uvemitter_rom_00402A74[i];
        D_uvemitter_rom_00402A74[i] = 0xFF;
        D_uvemitter_rom_00402A7C[i] = 0xFF;
    }
    D_uvemitter_rom_00402A80 = 0;
}
#line 886 "src/modules/uvemitter_rom.c"

void _uvaStartVoice(Emitter *arg0) {
    ALSound *temp_a1;
    ALInstrument *temp_a0;

    alSndpSetSound(D_uvemitter_rom_00402A10, sVoiceTable[arg0->playVoice]);
    if (D_uvemitter_rom_00402A10->target == -1) {
        *(s32 *) 0 = 0;
    }
    if (alSndpGetState(D_uvemitter_rom_00402A10) != 0) {
        arg0->unk78 = 1;
        alSndpStop(D_uvemitter_rom_00402A10);
        return;
    }
    alSndpDeallocate(D_uvemitter_rom_00402A10, sVoiceTable[arg0->playVoice]);
    if ((s32) arg0->soundId >= D_uvemitter_rom_00402BB4->instCount) {
        *(s32 *) 0 = 0;
    }

    temp_a0 = D_uvemitter_rom_00402BB4->instArray[arg0->soundId];
    temp_a1 = temp_a0->soundArray[0];
    if (temp_a1 == NULL) {
        *(s32 *) 0 = 0;
    }
    sVoiceTable[arg0->playVoice] = alSndpAllocate(D_uvemitter_rom_00402A10, temp_a1);
    alSndpSetSound(D_uvemitter_rom_00402A10, sVoiceTable[arg0->playVoice]);
    if (D_uvemitter_rom_00402A10->target == -1) {
        *(s32 *) 0 = 0;
    }
    if (sVoiceTable[arg0->playVoice] >= 0) {
        _uvaUpdateVoice(arg0);
        if (arg0->unk84 == 0x20) {
            alSndpPlayAt(D_uvemitter_rom_00402A10, arg0->unk58);
        } else {
            alSndpPlay(D_uvemitter_rom_00402A10);
        }
        arg0->unk78 = 2;
        arg0->unk84 = 0;
    }
}

void _uvaUpdateVoice(Emitter *emitter) {
    if (emitter->playVoice >= sMaxVoices) {
        *(s32 *) 0 = 0;
    }
    if (sVoiceTable[emitter->playVoice] < 0) {
        *(s32 *) 0 = 0;
    }
    if (emitter->playPan >= 0x80) {
        *(s32 *) 0 = 0;
    }
    alSndpSetSound(D_uvemitter_rom_00402A10, sVoiceTable[emitter->playVoice]);
    if (D_uvemitter_rom_00402A10->target == -1) {
        *(s32 *) 0 = 0;
    }
    
    alSndpSetVol(D_uvemitter_rom_00402A10, emitter->playVolume);
    alSndpSetPitch(D_uvemitter_rom_00402A10, emitter->playPitch);
    alSndpSetFXMix(D_uvemitter_rom_00402A10, emitter->playMix);
    alSndpSetPan(D_uvemitter_rom_00402A10, emitter->playPan);
}

void _uvaStopVoice(Emitter *arg0) {
    u16 temp_v0;
    u8 temp_v1;

    if (arg0->unk78 != 0) {
        if (arg0->playVoice < sMaxVoices) {
            alSndpSetSound(D_uvemitter_rom_00402A10, sVoiceTable[arg0->playVoice]);
            if (D_uvemitter_rom_00402A10->target == -1) {
                *(s32 *) 0 = 0;
            }
            if (alSndpGetState(D_uvemitter_rom_00402A10) == 1) {
                alSndpSetVol(D_uvemitter_rom_00402A10, 0);
            }
            alSndpStop(D_uvemitter_rom_00402A10);
        }
        arg0->playVoice = sMaxVoices + 1;
        arg0->unk78 = 0;
        arg0->unk83 = 0;
    }
}

#line 969 "src/modules/uvemitter_rom.c"
/* Read UVSX .CTL/.TBL blocks, copy and relocate the control bank, select
 * its first instrument and allocate sound-player voices. The original valid
 * bank/tag/allocation assumptions are caller-owned. */
void uvEmitterLoadSoundBank(s32 fileId) {
    void *controlData;
    void *tableData;
    u32 controlSize;
    ALSound *firstSound;
    s32 file;
    s32 voiceIndex;
    s32 var_s2;

    file = uvFileReadHeader(uvGetFileData('UVSX', fileId));
    uvFileSearchTag(file, &controlSize, &controlData, '.CTL', 0);
    uvFileSearchTag(file, NULL, &tableData, '.TBL', 0);
    uvFileFree(file);
    D_uvemitter_rom_00402BB8 = _uvMemAlloc(controlSize + 0x3E8, 0x10U);
    _uvMediaCopy(D_uvemitter_rom_00402BB8, controlData, controlSize);
    alBnkfNew(D_uvemitter_rom_00402BB8, (u8 *) tableData);
    D_uvemitter_rom_00402BB4 = D_uvemitter_rom_00402BB8->bankArray[0];
    D_uvemitter_rom_00402BBC = D_uvemitter_rom_00402BB4->instArray[0];
    sVoiceTable = _uvMemAlloc(D_uvemitter_rom_00402A10->maxSounds * 2, 0x10U);
    firstSound = D_uvemitter_rom_00402BBC->soundArray[0];
    for (voiceIndex = 0; voiceIndex < D_uvemitter_rom_00402A10->maxSounds; voiceIndex++) {
        sVoiceTable[voiceIndex] = alSndpAllocate(D_uvemitter_rom_00402A10, firstSound);
    }
}
#line 993 "src/modules/uvemitter_rom.c"

#line 994 "src/modules/uvemitter_rom.c"
/* Return squared distance from the supplied point to the emitter segment
 * and write the closest-point displacement. Preserve endpoint tests and
 * projection order; the stored segment direction is expected normalized. */
f32 uvEmitterGetLineDistanceSquared(Vec3F point, Emitter *emitter, Vec3F *displacement) {
    f32 endProjection;
    f32 closestZ;
    f32 closestY;
    f32 distanceSquared;
    f32 closestX;

    displacement->x = emitter->unk0.x - point.x;
    displacement->y = emitter->unk0.y - point.y;
    displacement->z = emitter->unk0.z - point.z;
    if (sFvecExports->uvVec3FDot(displacement, (Vec3F *) &emitter->unk18) >= 0.0f) {
        distanceSquared = SQ(displacement->z) + (SQ(displacement->x) + SQ(displacement->y));
    } else {
        displacement->x = emitter->unkC - point.x;
        displacement->y = emitter->unk10 - point.y;
        displacement->z = emitter->unk14 - point.z;
        endProjection = sFvecExports->uvVec3FDot(displacement, (Vec3F *) &emitter->unk18);
        if (endProjection < 0.0f) {
            distanceSquared = SQ(displacement->z) + (SQ(displacement->x) + SQ(displacement->y));
        } else {
            closestX = (emitter->unkC - (endProjection * emitter->unk18));
            closestY = emitter->unk10 - (endProjection * emitter->unk1C);
            closestZ = emitter->unk14 - (endProjection * emitter->unk20);
            displacement->x = closestX - point.x;
            displacement->y = closestY - point.y;
            displacement->z = closestZ - point.z;
            distanceSquared = SQ(displacement->z) + (SQ(displacement->x) + SQ(displacement->y));
        }
    }
    return distanceSquared;
}
#line 1025 "src/modules/uvemitter_rom.c"

#line 1026 "src/modules/uvemitter_rom.c"
/* Return whether the caller-selected emitter has a nonzero active byte.
 * The original routine does not validate its index. */
s32 uvEmitterIsActive(u8 emitterId) {
    if (D_uvemitter_rom_00402B94[emitterId].active == 0) {
        return 0;
    }
    return 1;
}
#line 1032 "src/modules/uvemitter_rom.c"

#line 1033 "src/modules/uvemitter_rom.c"
/* Return the original request/state word at offset 0x84 without an index check. */
s32 uvEmitterGetPlaybackRequest(u8 emitterId) {
    return D_uvemitter_rom_00402B94[emitterId].unk84;
}
#line 1036 "src/modules/uvemitter_rom.c"

#line 1037 "src/modules/uvemitter_rom.c"
/* Copy active voice-list sound IDs and playback volumes to optional outputs,
 * then return their count. Output capacity and voice-map validity are caller-owned. */
s32 uvEmitterGetPlayingSoundsAndVolumes(s32 *soundIds, s32 *volumes) {
    Emitter *emitter;
    s32 i;

    for (i = 0; i < D_uvemitter_rom_00402A84; i++) {
        emitter = &D_uvemitter_rom_00402B94[D_uvemitter_rom_00402A78[i]];
        if (soundIds != 0) {
            soundIds[i] = (s32) emitter->soundId;
        }
        if (volumes != 0) {
            volumes[i] = emitter->playVolume;
        }
    }
    return D_uvemitter_rom_00402A84;
}
#line 1052 "src/modules/uvemitter_rom.c"

#line 1053 "src/modules/uvemitter_rom.c"
/* Return the loaded bank instrument count; the original requires a loaded bank. */
s16 uvEmitterGetBankInstrumentCount(void) {
    return D_uvemitter_rom_00402BB4->instCount;
}
#line 1056 "src/modules/uvemitter_rom.c"

#line 1057 "src/modules/uvemitter_rom.c"
/* Normalize the displacement and scale it by propagation speed, then divide
 * distances to listener and emitter velocity. A zero denominator returns one. */
f32 uvEmitterComputeDopplerRatio(Vec3F displacement, Vec3F listenerVelocity, Vec3F emitterVelocity, f32 speed) {
    Vec3F propagation;
    Vec3F emitterDifference;
    Vec3F listenerDifference;
    f32 denominator;
    f32 numerator;
    f32 ratio;

    sFvecExports->uvVec3FCopy(&propagation, (Vec3F *) &displacement);
    sFvecExports->uvVec3FNormalize(&propagation, &propagation);
    sFvecExports->uvVec3FScale(&propagation, &propagation, speed);
    sFvecExports->uvVec3FSub(&listenerDifference, &propagation, (Vec3F *) &listenerVelocity);
    numerator = sFvecExports->uvVec3FLen(&listenerDifference);
    sFvecExports->uvVec3FSub(&emitterDifference, &propagation, (Vec3F *) &emitterVelocity);
    denominator = sFvecExports->uvVec3FLen(&emitterDifference);
    ratio = (denominator == 0) ? 1.0f : numerator / denominator;

    return ratio;
}
#line 1076 "src/modules/uvemitter_rom.c"

#line 1077 "src/modules/uvemitter_rom.c"
/* Stop every emitter voice and disable future playback requests. */
void uvEmitterStopAllAndDisable(void) {
    s32 i;
    for (i = 0; i < D_uvemitter_rom_00402BD0; i++) {
        _uvaStopVoice(&D_uvemitter_rom_00402B94[i]);
    }
    D_uvemitter_rom_00403004 = 1;
}
#line 1084 "src/modules/uvemitter_rom.c"

#line 1085 "src/modules/uvemitter_rom.c"
/* Original empty exported callback; retain the reserved entry point. */
void uvEmitterReservedCallback(void) {
}
#line 1087 "src/modules/uvemitter_rom.c"

#line 1088 "src/modules/uvemitter_rom.c"
/* Store the caller-owned 0xFF-terminated list whose sounds use playback
 * volume three. Lifetime and sentinel termination remain caller-owned. */
void uvEmitterSetQuietSoundList(u8 *soundIds) {
    D_uvemitter_rom_00403008 = soundIds;
}
#line 1091 "src/modules/uvemitter_rom.c"

#line 1092 "src/modules/uvemitter_rom.c"
/* Map the byte sound ID to a volume-group byte without additional bounds checks. */
void uvEmitterSetSoundVolumeGroup(u8 soundId, u8 group) {
    D_uvemitter_rom_00402A88[soundId] = group;
}
#line 1095 "src/modules/uvemitter_rom.c"

#line 1096 "src/modules/uvemitter_rom.c"
/* Return the volume-group byte for the caller-supplied sound ID. */
u8 uvEmitterGetSoundVolumeGroup(u8 soundId) {
    return D_uvemitter_rom_00402A88[soundId];
}
#line 1099 "src/modules/uvemitter_rom.c"

#line 1100 "src/modules/uvemitter_rom.c"
/* Store a group volume factor without clamping or validating its byte index. */
void uvEmitterSetGroupVolume(u8 group, f32 volume) {
    D_uvemitter_rom_00402B88[group] = volume;
}
#line 1103 "src/modules/uvemitter_rom.c"
