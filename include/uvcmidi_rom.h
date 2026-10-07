#ifndef UVCMIDI_ROM_H
#define UVCMIDI_ROM_H

typedef struct UvCMidi_Exports_s {
    /* 0x00 */ void (*uvaCleanup)(void);
    /* 0x04 */ void (*uvaLoadBank)(s32);
    /* 0x08 */ void (*uvaSetSeq)(s32);
    /* 0x0C */ void (*uvaSeqPlay)(void);
    /* 0x10 */ void (*uvaSeqSetPosition)(u32);
    /* 0x14 */ void (*uvaSeqSetTempo)(f32);
    /* 0x18 */ f32 (*uvaSeqGetTempo)(void);
    /* 0x1C */ void (*uvaSeqGetTicks)(void);
    /* 0x20 */ void (*uvaVisitSequenceElapsedSeconds)(void);
    /* 0x24 */ void (*uvaSeqGetState)(void);
    /* 0x28 */ void (*uvaSeqSetVol)(f32);
    /* 0x2C */ void (*uvaSeqStop)(void);
    /* 0x30 */ f32 (*uvaGetChannelPriority)(u8);
    /* 0x34 */ void (*uvaSetChannelPriority)(u8, u8);
    /* 0x38 */ void (*uvaSendChannelController10)(u8, u8);
    /* 0x3C */ f32 (*uvaGetChannelEffectsMix)(u8);
    /* 0x40 */ void (*uvaSetChannelEffectsMix)(u8, u8);
    /* 0x44 */ void (*uvaSendChannelEffectsMix)(u8, u8);
    /* 0x48 */ f32 (*uvaGetChannelPan)(u8);
    /* 0x4C */ void (*uvaSetChannelPan)(u8, s32);
    /* 0x50 */ void (*uvaSendChannelPan)(u8, s32);
    /* 0x54 */ f32 (*uvaGetChannelProgram)(u8);
    /* 0x58 */ void (*uvaSetChannelProgram)(u8, s32);
    /* 0x5C */ void (*uvaSendChannelProgram)(u8, s32);
    /* 0x60 */ f32 (*uvaGetChannelVolume)(u8);
    /* 0x64 */ void (*uvaSetChannelVolume)(u8, u8);
    /* 0x68 */ void (*uvaSendChannelVolume)(u8, u8);
    /* 0x6C */ void (*uvaSendMidiMessage)(u8, u8, u8);
    /* 0x70 */ void (*uvaSendNoteOn)(u8, u8, u8);
    /* 0x74 */ void (*uvaSendNoteOff)(u8, u8, u8);
    /* 0x78 */ void (*uvaCollectAllocatedVoicePhases)(u8 *, s32, s32 *);
    /* 0x7C */ ALVoiceState *(*uvaGetFreeVoiceList)(void);
    /* 0x80 */ void (*uvaGetAllocatedVoiceList)(ALVoiceState **, ALVoiceState **);
    /* 0x84 */ s32 (*uvaGetInitialVoicePoolAddress)(void);
    /* 0x88 */ void (*uvaCollectVoicePoolPhases)(u8 *);
    /* 0x8C */ ALSeqPlayer *(*uvaGetSeqPlayer)(void);
    /* 0x90 */ s16 (*uvaGetSeqCount)(void);
} UvCMidi_Exports;
#endif /* UVCMIDI_ROM_H */
