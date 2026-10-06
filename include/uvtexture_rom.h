#ifndef UVTEXTURE_ROM_H
#define UVTEXTURE_ROM_H

typedef struct UvTexture_Exports_s {
    /* 0x00 */ void (*func_uvtexture_rom_00400134)(void);               /* inferred */
    /* 0x04 */ u8 (*func_uvtexture_rom_00400164)(s32);                  /* inferred */
    /* 0x08 */ void *(*func_uvtexture_rom_004001C0)(s32, f32 *, f32 *); /* inferred */
    /* 0x0C */ void (*func_uvtexture_rom_00400244)(s32);                /* inferred */
    /* 0x10 */ s32 (*func_uvtexture_rom_00400500)(s32);                 /* inferred */
    /* 0x14 */ void (*func_uvtexture_rom_00400B7C)(void);               /* inferred */
    /* 0x18 */ s32 (*func_uvtexture_rom_00400B8C)(s32);                 /* inferred */
    /* 0x1C */ void (*uvTextureGetProps)(s32, ...);           /* inferred */
    /* 0x20 */ void *(*func_uvtexture_rom_00400C6C)(void);              /* inferred */
    /* 0x24 */ void *(*func_uvtexture_rom_00400CB0)(void);              /* inferred */
    /* 0x28 */ s32 *D_uvtexture_rom_00400D00;                           /* inferred */
} UvTexture_Exports;                                                    /* size = 0x2C */

#endif /* UVTEXTURE_ROM_H */
