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
    /* 0x00 */ void (*func_uvcont_rom_004002B8)(void);
    /* 0x04 */ s32 (*uvIOUpdate)(void);
    /* 0x08 */ s32 (*uvControllerPlugged)(s32);
    /* 0x0C */ f32 (*uvControllerGetStick)(s32, s32);
    /* 0x10 */ s32 (*func_uvcont_rom_00400640)(s32, s32);
    /* 0x14 */ u16 (*uvControllerGetButton)(s32);
    /* 0x18 */ s32 (*uvControllerButtonPress)(s32, s32);
    /* 0x1C */ s32 (*uvControllerButtonRelease)(s32, s32);
    /* 0x20 */ void (*func_uvcont_rom_0040072C)(s32, u16, u16, f32, f32);
    /* 0x24 */ void (*func_uvcont_rom_00400768)(s32, u16 *, u8 *, u8 *);
    /* 0x28 */ void (*func_uvcont_rom_0040079C)(s32, u16, u16, s8, s8);
    /* 0x2C */ u8 (*uvControllerGetPeriphState)(s32);
    /* 0x30 */ void (*uvControllerSetPakStateCallback)(void (*)(s32, u16, u8));
    /* 0x34 */ void (*uvSetContStatusCallback)(void (*)(s32, u8));
    /* 0x38 */ s32 (*uvControllerRepairPfs)(s32);
    /* 0x3C */ void (*func_uvcont_rom_00400D48)(s32, s32);
    /* 0x40 */ s32 (*func_uvcont_rom_00400D5C)(s32, s32, UvPfsState *);
    /* 0x44 */ s32 (*func_uvcont_rom_00400E4C)(s32, s32, s32);
    /* 0x48 */ void (*func_uvcont_rom_00400EF0)(s32, u8 *, u8 *, s32, s32 *);
    /* 0x4C */ s32 (*func_uvcont_rom_00400F94)(s32, s32 *, s32 *);
    /* 0x50 */ s32 (*func_uvcont_rom_00400FDC)(s32, s32 *);
    /* 0x54 */ s32 (*func_uvcont_rom_00401024)(s32, s32, s32, s32, u8 *);
    /* 0x58 */ void (*func_uvcont_rom_00401148)(s32, s32, s32, s32, u8 *);
    /* 0x5C */ s32 (*uvControllerPakDeleteFile)(s32, s32);
    /* 0x60 */ s32 (*uvControllerStartRumblePak)(s32);
    /* 0x64 */ s32 (*uvControllerStopRumblePak)(s32);
    /* 0x68 */ s32 (*func_uvcont_rom_00401658)(s32);
    /* 0x6C */ void (*func_uvcont_rom_00401720)(void); /* inferred */
} UvCont_Exports;
#endif /* UVCONT_ROM_H */

