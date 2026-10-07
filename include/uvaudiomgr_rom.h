#ifndef UVAUDIOMGR_ROM_H
#define UVAUDIOMGR_ROM_H
typedef struct UvAudioMgr_Exports_s {
    /* 0x00 */ void (*uvAudioMgrCleanup)(void);          /* inferred */
    /* 0x04 */ s32 (*uvGetAudioHeapSize)(void);           /* inferred */
    /* 0x08 */ void (*uvAudioMgrReservedCallback0)(void);          /* inferred */
    /* 0x0C */ void (*uvAudioMgrReservedCallback1)(void);          /* inferred */
    /* 0x10 */ void *(*uvAudioMgrGetFrameCallbackList)(s32);          /* inferred */
    /* 0x14 */ void (*uvAudioMgrSetEffectsVolume)(f32);           /* inferred */
    /* 0x18 */ void (*uvAudioMgrGetEffectsVolume)(f32 *);         /* inferred */
    /* 0x1C */ void (*uvAudioMgrSetSequenceVolume)(f32);           /* inferred */
    /* 0x20 */ void (*uvAudioMgrGetSequenceVolume)(f32 *);         /* inferred */
    /* 0x24 */ void (*uvAudioMgrSetOutputMode)(s32);           /* inferred */
    /* 0x28 */ void (*uvAudioMgrGetOutputMode)(s32 *);         /* inferred */
    /* 0x2C */ void (*uvAudioMgrSetSharedScalar40)(f32);           /* inferred */
    /* 0x30 */ void (*uvAudioMgrGetSharedScalar40)(f32 *);         /* inferred */
    /* 0x34 */ s32 (*uvAudioMgrGetEffectsHeaderWord)(void);           /* inferred */
    /* 0x38 */ void (*uvAudioMgrSetEffectsMatrixParameter)(s32, s32, s32); /* inferred */
    /* 0x3C */ s32 (*uvAudioMgrGetEffectsMatrixParameter)(s32, s32);       /* inferred */
    /* 0x40 */ void (*uvAudioMgrLatchShutdown)(void);          /* inferred */
} UvAudioMgr_Exports;                                               /* size = 0x44 */
#endif /* UVAUDIOMGR_ROM_H */
