#ifndef UVBLIT_ROM_H
#define UVBLIT_ROM_H
#include "uvasset_types.h"
typedef struct UvBlit_Rom_Exports_s {
    /* 0x0 */ void (*uvBlitStub)(void);                       /* inferred */
    /* 0x4 */ ParsedUVBT* (*uvParseBlit)(u8 *);                    /* inferred */
    /* 0x8 */ void (*uvFreeBlit)(ParsedUVBT *);           /* inferred */
} UvBlit_Rom_Exports;                               /* size = 0xC */
#endif /* UVBLIT_ROM_H */
