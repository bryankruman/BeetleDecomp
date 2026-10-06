#ifndef UVTRACKLD_ROM_H
#define UVTRACKLD_ROM_H

#include "uvasset_types.h"
typedef struct UvTrackLd_Exports_s {
    /* 0x0 */ void (*func_uvtrackld_rom_00400048)();                       /* inferred */
    /* 0x4 */ void *(*uvParseUVTT)(u8 *);                  /* inferred */
    /* 0x8 */ void (*uvParseFreeUVTT)(ParsedUVTT *);           /* inferred */
} UvTrackLd_Exports;                                /* size = 0xC */


#endif /* UVTRACKLD_ROM_H */
