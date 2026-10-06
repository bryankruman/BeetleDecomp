#ifndef UVENV_ROM_H
#define UVENV_ROM_H

typedef struct UvEnv_Exports_s {
    /* 0x00 */ void (*func_uvenv_rom_004001B4)(void);                      /* inferred */
    /* 0x04 */ void (*func_uvenv_rom_00400220)(f32, f32, u16 *, ParsedUVEN *); /* inferred */
    /* 0x08 */ void (*uvEnvProps)(s32, ...);              /* inferred */
    /* 0x0C */ void (*uvEnvGetProps)(s32, ...);              /* inferred */
    /* 0x10 */ void (*func_uvenv_rom_00401F7C)(s32, s32, s32);        /* inferred */
    /* 0x14 */ void (*func_uvenv_rom_00401FE0)(s32);                  /* inferred */
    /* 0x18 */ void (*func_uvenv_rom_00402DD8)(s32, s32);             /* inferred */
    /* 0x1C */ void (*func_uvenv_rom_00402E68)(s32, s32);             /* inferred */
    /* 0x20 */ void (*func_uvenv_rom_00402F00)(s32, s32, s32, f32);   /* inferred */
    /* 0x24 */ s32 (*func_uvenv_rom_00403AFC)(s32);                   /* inferred */
    /* 0x28 */ s32 *unk28;                          /* inferred */
    /* 0x2C */ s32 *unk2C;                          /* inferred */
} UvEnv_Exports;                                    /* size = 0x30 */

#endif /* UVENV_ROM_H */
