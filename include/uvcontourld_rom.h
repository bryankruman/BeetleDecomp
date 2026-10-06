#ifndef UVCONTOURLD_ROM_H
#define UVCONTOURLD_ROM_H

typedef struct UvContourLd_Exports_s {
    /* 0x0 */ void (*func_uvcontourld_rom_00400058)(void);                       /* inferred */
    /* 0x4 */ ParsedUVCT *(*uvParseUVCT)(u8 *);            /* inferred */
    /* 0x8 */ void (*func_uvcontourld_rom_00400A74)(ParsedUVCT *);           /* inferred */
} UvContourLd_Exports;                              /* size = 0xC */

#endif /* UVCONTOURLD_ROM_H */
