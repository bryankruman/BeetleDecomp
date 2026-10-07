#ifndef UVFONTLD_ROM_H
#define UVFONTLD_ROM_H
typedef struct UvFontLd_Exports_s {
    /* 0x0 */ void (*uvFontLoaderCleanup)(void);                       /* inferred */
    /* 0x4 */ ParsedUVFT *(*uvFontLoadResource)(u8 *);            /* inferred */
    /* 0x8 */ void (*uvFontFreeResource)(ParsedUVFT *);           /* inferred */
} UvFontLd_Exports;                                 /* size = 0xC */
#endif /* UVFONTLD_ROM_H */
