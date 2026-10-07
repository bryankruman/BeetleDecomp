#ifndef UVCONT_ROM_H
#define UVCONT_ROM_H


typedef struct UvPfsState_s {
    s32 fileSize;
    s32 gameCode;
    u32 companyCode;
    char extName[4];
    char gameName[18];
} UvPfsState;


typedef struct UvCont_Exports_s {
    /* 0x00 */ void (*uvControllerResetPeripheralsAndRumble)(void);
    /* 0x04 */ s32 (*uvIOUpdate)(void);
    /* 0x08 */ s32 (*uvControllerPlugged)(s32);
    /* 0x0C */ f32 (*uvControllerGetStick)(s32, s32);
    /* 0x10 */ s32 (*uvControllerHasButtons)(s32, s32);
    /* 0x14 */ u16 (*uvControllerGetButton)(s32);
    /* 0x18 */ s32 (*uvControllerButtonPress)(s32, s32);
    /* 0x1C */ s32 (*uvControllerButtonRelease)(s32, s32);
    /* 0x20 */ void (*uvControllerSetNormalizedState)(s32, u16, u16, f32, f32);
    /* 0x24 */ void (*uvControllerGetRawState)(s32, u16 *, u8 *, u8 *);
    /* 0x28 */ void (*uvControllerSetRawState)(s32, u16, u16, s8, s8);
    /* 0x2C */ u8 (*uvControllerGetPeriphState)(s32);
    /* 0x30 */ void (*uvControllerSetPakStateCallback)(void (*)(s32, u16, u8));
    /* 0x34 */ void (*uvSetContStatusCallback)(void (*)(s32, u8));
    /* 0x38 */ s32 (*uvControllerRepairPfs)(s32);
    /* 0x3C */ void (*uvControllerSetPakIdentity)(s32, s32);
    /* 0x40 */ s32 (*uvControllerReadPakFileMetadata)(s32, s32, UvPfsState *);
    /* 0x44 */ s32 (*uvControllerFindPakFile)(s32, s32, s32);
    /* 0x48 */ void (*uvControllerAllocatePakFile)(s32, u8 *, u8 *, s32, s32 *);
    /* 0x4C */ s32 (*uvControllerGetPakFileCounts)(s32, s32 *, s32 *);
    /* 0x50 */ s32 (*uvControllerGetPakFreeBytes)(s32, s32 *);
    /* 0x54 */ s32 (*uvControllerReadPakFileWithTemporaryBuffer)(s32, s32, s32, s32, u8 *);
    /* 0x58 */ s32 (*uvControllerWritePakAligned)(s32, s32, s32, s32, u8 *);
    /* 0x5C */ s32 (*uvControllerPakDeleteFile)(s32, s32);
    /* 0x60 */ s32 (*uvControllerStartRumblePak)(s32);
    /* 0x64 */ s32 (*uvControllerStopRumblePak)(s32);
    /* 0x68 */ s32 (*uvControllerReinitializeAndStopRumble)(s32);
    /* 0x6C */ void (*uvControllerReinitializeAndStopAllRumble)(void); /* inferred */
} UvCont_Exports;
#endif /* UVCONT_ROM_H */

