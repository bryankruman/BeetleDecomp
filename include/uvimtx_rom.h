#ifndef UVIMTX_ROM_H
#define UVIMTX_ROM_H
typedef struct UvImtx_Rom_Exports_s {
    /* 0x00 */ void (*uvIMtxModuleCleanup)();                      /* inferred */
    /* 0x04 */ void (*uvIMtxCopy)(Mtx*, Mtx);             /* inferred */
    /* 0x08 */ void (*uvIMtxSetIdentity)(Mtx*);                  /* inferred */
    /* 0x0C */ void (*uvImtxStub)(s32, s32, s32, s32);    /* inferred */
    /* 0x10 */ void (*func_uvimtx_rom_00400338)(uvMtx*, uvMtx);        /* inferred */
    /* 0x14 */ void (*uvIMtxLoadModelview)(Mtx);                  /* inferred */
    /* 0x18 */ void (*uvGfxMtxViewPop)(void);                     /* inferred */
    /* 0x1C */ void (*uvIMtxLoadProjection)(Mtx);                  /* inferred */
    /* 0x20 */ Mtx* (*uvIMtxPush)(Mtx, u16);             /* inferred */
    /* 0x24 */ void (*uvIMtxSubmitMatrix)(Mtx*, u16);            /* inferred */
    /* 0x28 */ s32 (*uvIMtxGetOtherBufferValue)(s32);                   /* inferred */
} UvImtx_Rom_Exports;                               /* size = 0x2C */   
#endif /* UVIMTX_ROM_H */

