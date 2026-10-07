#ifndef UVLED_ROM_H
#define UVLED_ROM_H

typedef struct UvLed_Exports_s {
    /* 0x00 */ void (*uvLedModuleCleanup)(void);           /* inferred */
    /* 0x04 */ void (*uvLedDrawTextString)(u8 *);           /* inferred */
    /* 0x08 */ void (*uvLedDrawDecimalInteger)(s32);            /* inferred */
    /* 0x0C */ void (*uvLedDrawBinaryInteger)(s32);            /* inferred */
    /* 0x10 */ void (*uvLedDrawHexInteger)(s32);            /* inferred */
    /* 0x14 */ void (*uvLedSetSharedShortPair)(s16, s16);       /* inferred */
    /* 0x18 */ void (*uvLedSetPositionAndCellCoordinates)(f32, f32);       /* inferred */
    /* 0x1C */ void (*uvLedSetVertexColors)(u8, u8, u8, u8); /* inferred */
    /* 0x20 */ void (*uvLedDrawFormattedWordArguments)(u8 *, s32, ...); /* inferred */
} UvLed_Exports;                                                /* size = 0x24 */

#endif /* UVLED_ROM_H */
