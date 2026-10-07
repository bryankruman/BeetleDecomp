#ifndef UVCHANNEL_ROM_H
#define UVCHANNEL_ROM_H
typedef struct UvChannel_Exports_s {
    /* 0x00 */ void (*uvChannelModuleCleanup)(void);                      /* inferred */
    /* 0x04 */ void (*uvChannelGetProperties)(s32, ...);              /* inferred */
    /* 0x08 */ void (*uvChannelSetProperties)(s32, ...);              /* inferred */
    /* 0x0C */ void (*uvChannelSetFlags)(s32, s32);              /* inferred */
    /* 0x10 */ void (*uvChannelSetFrustum)(s32, f32, f32, f32, f32, f32, f32); /* inferred */
    /* 0x14 */ void (*uvChannelSetViewport)(s32, s32, s32, s32, s32); /* inferred */
    /* 0x18 */ void (*uvChannelSetBoundaryCallback)(s32, s32, CallbackRoutine);        /* inferred */
    /* 0x1C */ s32 (*func_uvchannel_rom_00400CCC)(void);                      /* inferred */
    /* 0x20 */ void (*uvChannelRelease)(s32);                  /* inferred */
    /* 0x24 */ void (*uvChannelRender)(s32);                  /* inferred */
    /* 0x28 */ void (*uvChannelSetViewMatrix)(s32, Mtx4F*);          /* inferred */
    /* 0x2C */ s32 (*func_uvchannel_rom_004014E8)(s32, f32, f32, f32, f32); /* inferred */
} UvChannel_Exports;                                 /* size = 0x30 */
#endif /* UVCHANNEL_ROM_H */
