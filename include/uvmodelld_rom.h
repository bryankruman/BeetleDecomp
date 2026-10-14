#ifndef UVMODELLD_ROM_H
#define UVMODELLD_ROM_H
#include "uvasset_types.h"
/* Export slots only; original ASM retains module data and dependency storage. */
typedef struct UvModelLd_Exports_s {
    /* 0x0 */ void (*uvModelLoaderCleanup)();                       /* inferred */
    /* 0x4 */ ParsedUVMD *(*uvModelLoaderParseCommonBlocks)(u8 *);            /* inferred */
    /* 0x8 */ void (*uvModelLoaderReleaseRenderResources)(ParsedUVMD *);           /* inferred */
} UvModelLd_Exports;                                /* size = 0xC */

#endif /* UVMODELLD_ROM_H */
