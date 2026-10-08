#ifndef UVVATTR_ROM_H
#define UVVATTR_ROM_H
#include "stdarg.h"
typedef struct UvVAttr_Exports_s {
    /* 0x00 */ void (*uvVattrUnloadTextureModule)(void);                      /* inferred */
    /* 0x04 */ void (*uvVattrGetPackedVertexAttributes)(u32, u32, ...);         /* inferred */
    /* 0x08 */ void (*uvVattrSetPackedVertexAttributes)(u32, s32, ...);         /* inferred */
    /* 0x0C */ s32 (*func_uvvattr_rom_00400514)(s32 capacity, s32 *vertexHandles, s32 flags, ...); /* Original A3 home starts promoted-word arguments. */
    /* 0x10 */ void (*uvVattrGetTerrainTriangleVertexHandles)(s32, u32, s32 *, s32 *, s32 *); /* inferred */
} UvVAttr_Exports;                                  /* size = 0x14 */
#endif /* UVVATTR_ROM_H */
