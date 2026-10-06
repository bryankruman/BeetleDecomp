#ifndef UVENVLD_ROM_H
#define UVENVLD_ROM_H

typedef struct UvEnvLd_Exports_s {
    /* 0x0 */ void (*func_uvenvld_rom_00400048)(void);                       /* inferred */
    /* 0x4 */ ParsedUVEN* (*uvParseUVEN)(u8* data);                    /* inferred */
    /* 0x8 */ void (*uvEnvLdCleanup)(ParsedUVEN *);           /* inferred */
} UvEnvLd_Exports;                                  /* size = 0xC */

#endif /* UVENVLD_ROM_H */
