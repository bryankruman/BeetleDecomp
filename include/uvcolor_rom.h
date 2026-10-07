#ifndef UVCOLOR_ROM_H
#define UVCOLOR_ROM_H
typedef struct UvColor_Exports_s {
    /* 0x00 */ void (*uvColorModuleCleanup)(void);
    /* 0x04 */ void (*uvColorApplyStoredChannelTriple)(s32, f32, f32, f32);
    /* 0x08 */ void (*uvColorScaleLoadedAssetColors)(s32);
    /* 0x0C */ void (*uvColorSetStoredChannelTriple)(s32, f32, f32, f32);
    /* 0x10 */ void (*uvColorTransformLoadedModelVertices)(s32, f32, f32, f32, f32);
} UvColor_Exports;
#endif /* UVCOLOR_ROM_H */
