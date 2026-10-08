#ifndef UVTEXTURE_ROM_H
#define UVTEXTURE_ROM_H

typedef struct UvTexture_Exports_s {
    /* 0x00 */ void (*uvTextureModuleCleanup)(void);               /* inferred */
    /* 0x04 */ u8 (*uvTextureGetLoadedFlag27)(s32);                  /* inferred */
    /* 0x08 */ void *(*uvTextureGetLoadedSubrecord)(s32, f32 *, f32 *); /* inferred */
    /* 0x0C */ void (*uvTextureEmitDisplayListAndAnimatedTileSizes)(s32);                /* inferred */
    /* 0x10 */ s32 (*uvTextureApplyPackedState)(s32);                 /* inferred */
    /* 0x14 */ void (*uvTextureInvalidateBinding)(void);               /* inferred */
    /* 0x18 */ s32 (*uvTextureGetOtherBufferValue)(s32);                 /* inferred */
    /* 0x1C */ void (*uvTextureGetProps)(s32, ...);           /* inferred */
    /* 0x20 */ void *(*uvTextureGetOrAllocateScratch)(void);              /* inferred */
    /* 0x24 */ void *(*uvTextureGetScratch)(void);              /* inferred */
    /* 0x28 */ s32 *D_uvtexture_rom_00400D00;                           /* inferred */
} UvTexture_Exports;                                                    /* size = 0x2C */

#endif /* UVTEXTURE_ROM_H */
