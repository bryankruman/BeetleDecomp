#ifndef UVEMITTER_ROM_H
#define UVEMITTER_ROM_H

typedef struct UnkStruct_uvemitter_rom_004008CC_s {
    char pad[0x30];
    Vec3F unk30;
} UnkStruct_uvemitter_rom_004008CC;

typedef struct Unkstruct_uvemitter_rom_00400970_s {
    /* 0x00 */ Mtx4F unk0;          /* inferred */
    /* 0x40 */ char pad40[0x80];    /* maybe part of unk0[3]? */
    /* 0xC0 */ f32 unkC0;           /* inferred */
    /* 0xC4 */ char padC4[0xC];     /* maybe part of unkC0[4]? */
    /* 0xD0 */ f32 unkD0;           /* inferred */
    /* 0xD4 */ char padD4[0xC];     /* maybe part of unkD0[4]? */
    /* 0xE0 */ f32 unkE0;           /* inferred */
} Unkstruct_uvemitter_rom_00400970; /* size = 0xE4 */

typedef struct UvEmitter_Exports_s {
    /* 0x00 */ void (*uvEmitterModuleCleanup)(void);
    /* 0x04 */ u8 (*uvGetEmitter)(void);
    /* 0x08 */ void (*uvEmitterResetSlot)(u8);
    /* 0x0C */ void (*uvEmitterSetSoundId)(u8, u8);
    /* 0x10 */ u8 (*uvEmitterGetSoundId)(u8);
    /* 0x14 */ void (*uvEmitterSetPosition)(u8, Vec3F *);
    /* 0x18 */ void (*uvEmitterSetPositionFromState)(u8, UnkStruct_uvemitter_rom_004008CC *);
    /* 0x1C */ void (*uvEmitterGetPosition)(u8, Vec3F *);
    /* 0x20 */ void (*uvEmitterWritePositionState)(u8, Unkstruct_uvemitter_rom_00400970 *);
    /* 0x24 */ void (*uvEmitterSetVelocity)(u8, Vec3F);
    /* 0x28 */ void (*uvEmitterGetVelocity)(u8, Vec3F *);
    /* 0x2C */ void (*uvEmitterSetLineSegment)(u8, Vec3F, Vec3F);
    /* 0x30 */ void (*uvEmitterSetNormalizedVolume)(u8, f32);
    /* 0x34 */ f32 (*uvEmitterGetNormalizedVolume)(u8);
    /* 0x38 */ void (*uvEmitterSetPan)(u8, f32);
    /* 0x3C */ f32 (*uvEmitterGetPan)(u8);
    /* 0x40 */ void (*uvEmitterSetPitch)(u8, f32);
    /* 0x44 */ f32 (*uvEmitterGetPitch)(u8);
    /* 0x48 */ void (*uvEmitterSetMix)(u8, f32);
    /* 0x4C */ void (*uvEmitterSetVol)(u8, s32);
    /* 0x50 */ void (*uvEmitterProps)(u8, ...);
    /* 0x54 */ void (*uvEmitterRequestPlayback)(u8);
    /* 0x58 */ void (*uvEmitterRequestPlaybackWithValue)(u8, s32);
    /* 0x5C */ void (*uvEmitterStop)(u8);
    /* 0x60 */ void (*uvEmitterStopAssignedWhenRequested)(u8);
    /* 0x64 */ void (*uvEmitterUpdateAndQueueActiveVoices)(s32);
    /* 0x68 */ void (*uvEmitterApplyQueuedVoicesAndRotateLists)(void);
    /* 0x6C */ void (*uvEmitterLoadSoundBank)(s32);
    /* 0x70 */ s32 (*uvEmitterIsActive)(u8);
    /* 0x74 */ s32 (*uvEmitterGetPlaybackRequest)(u8);
    /* 0x78 */ s32 (*uvEmitterGetPlayingSoundsAndVolumes)(s32 *, s32 *);
    /* 0x7C */ s16 (*uvEmitterGetBankInstrumentCount)(void);
    /* 0x80 */ void (*uvEmitterStopAllAndDisable)(void);
    /* 0x84 */ void (*uvEmitterReservedCallback)(void);
    /* 0x88 */ void (*uvEmitterSetQuietSoundList)(u8 *);
    /* 0x8C */ void (*uvEmitterSetSoundVolumeGroup)(u8, u8);
    /* 0x90 */ u8 (*uvEmitterGetSoundVolumeGroup)(u8);
    /* 0x94 */ void (*uvEmitterSetGroupVolume)(u8, f32);
} UvEmitter_Exports;

#endif /* UVEMITTER_ROM_H */
