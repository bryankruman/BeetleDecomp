#ifndef UVDBG_ROM_H
#define UVDBG_ROM_H

typedef struct UvDbgRom_Exports_s {
    /* 0x00 */ void (*uvDbgModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ void (*uvDbgDispatchTimingOverlay)(u8, u8, u8);            /* inferred */
    /* 0x08 */ void (*uvDbgDispatchCounterOverlay)(s32, s32);              /* inferred */
    /* 0x0C */ void (*func_uvdbg_rom_00401DE8)(s32);                   /* inferred */
    /* 0x10 */ void (*func_uvdbg_rom_00402128)(void);                     /* inferred */
    /* 0x14 */ void (*func_uvdbg_rom_00402490)(void);                     /* inferred */
    /* 0x18 */ void (*uvDbgSetFontId)(s32);                  /* inferred */
    /* 0x1C */ void (*uvDbgResetDisplayFlags)(void);                     /* inferred */
    /* 0x20 */ void (*func_uvdbg_rom_00402A14)(s32);                  /* inferred */
    /* 0x24 */ void (*uvDbgDispatchMemoryOverlay)(u8, u8);               /* inferred */
    /* 0x28 */ void (*uvDbgDrawResourceStatistics)(void);                     /* inferred */
} UvDbgRom_Exports;                                 /* size = 0x2C */

#endif /* UVDBG_ROM_H */
