#ifndef UVFX_ROM_H
#define UVFX_ROM_H

typedef struct UvFx_Exports_s {
    /* 0x00 */ void (*func_uvfx_rom_00400224)(void);                      /* inferred */
    /* 0x04 */ void (*func_uvfx_rom_004001CC)(s32);                   /* inferred */
    /* 0x08 */ u8 (*func_uvfx_rom_0040033C)(s32);                     /* inferred */
    /* 0x0C */ void (*func_uvfx_rom_0040037C)(s32, Mtx4F *);          /* inferred */
    /* 0x10 */ void (*uvFxProps)(s32, ...);             /* inferred */
    /* 0x14 */ s32 (*uvFxModel)(s32, s32);              /* inferred */
    /* 0x18 */ s32 (*func_uvfx_rom_0040104C)(s32);                   /* inferred */
} UvFx_Exports;                                     /* size = 0x1C */

#endif /* UVFX_ROM_H */
