#ifndef UVLED_ROM_H
#define UVLED_ROM_H

typedef struct UvLed_Exports_s {
    /* 0x00 */ void (*func_uvled_rom_00400118)(void);           /* inferred */
    /* 0x04 */ void (*func_uvled_rom_00400148)(u8 *);           /* inferred */
    /* 0x08 */ void (*func_uvled_rom_004002E0)(s32);            /* inferred */
    /* 0x0C */ void (*func_uvled_rom_00400300)(s32);            /* inferred */
    /* 0x10 */ void (*func_uvled_rom_00400320)(s32);            /* inferred */
    /* 0x14 */ void (*func_uvled_rom_00400340)(s16, s16);       /* inferred */
    /* 0x18 */ void (*func_uvled_rom_0040035C)(f32, f32);       /* inferred */
    /* 0x1C */ void (*func_uvled_rom_00400410)(u8, u8, u8, u8); /* inferred */
    /* 0x20 */ void (*func_uvled_rom_00400DFC)(u8 *, s32, ...); /* inferred */
} UvLed_Exports;                                                /* size = 0x24 */

#endif /* UVLED_ROM_H */
