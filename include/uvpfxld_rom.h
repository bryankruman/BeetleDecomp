#ifndef UVPFXLD_ROM_H
#define UVPFXLD_ROM_H
#include "uvpfx_rom.h"
/* Export slots only; original ASM retains module data and dependency storage. */

typedef struct UvPfxLd_Exports_s {
    /* 0x0 */ void (*uvPfxLoaderCleanup)(void);                       /* inferred */
    /* 0x4 */ void *(*uvPfxLoaderParseChunkStream)(u8 *);                  /* inferred */
    /* 0x8 */ void (*uvPfxLoaderReleaseConfiguration)(UnkStruct_uvpfx_rom_00404FA0_unk0 *); /* inferred */
} UvPfxLd_Exports;                                  /* size = 0xC */

#endif /* UVPFXLD_ROM_H */
