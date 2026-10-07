#ifndef UVDOBJ_ROM_H
#define UVDOBJ_ROM_H
typedef struct UvDobj_Exports_s {
    /* 0x00 */ void (*uvDobjModuleCleanup)(void);                                    /* inferred */
    /* 0x04 */ void (*uvDobjSetSharedQueryIndexPair)(s32, s32);                                /* inferred */
    /* 0x08 */ s32 (*func_uvdobj_rom_00400558)(s32, s32, s32);                            /* inferred */
    /* 0x0C */ void (*uvDobjRegisterChannelCallback)(s32);                                     /* inferred */
    /* 0x10 */ void (*uvDobjSetLoadedModel)(s32, s32);                                /* inferred */
    /* 0x14 */ void (*uvDobjModel)(s32, s32);                                /* inferred */
    /* 0x18 */ u16 (*uvDobjGetModel)(s32);                                      /* inferred */
    /* 0x1C */ void (*uvDobjProps)(s32, ...);                                /* inferred */
    /* 0x20 */ void (*uvDobjGetProp)(s32, ...);                                /* inferred */
    /* 0x24 */ void (*uvDobjPosm)(s32, s32, Mtx4F *);                       /* inferred */
    /* 0x28 */ void (*uvDobjGetPosm)(s32, s32, Mtx4F *);                       /* inferred */
    /* 0x2C */ void (*uvDobjSetFlags)(s32, s32);                                /* inferred */
    /* 0x30 */ void (*uvDobjSetFlagBits)(s32, s32);                                /* inferred */
    /* 0x34 */ u8 (*uvDobjGetFlags)(s32);                                       /* inferred */
    /* 0x38 */ void (*uvDobjClearFlagBits)(s32, s32);                                /* inferred */
    /* 0x3C */ s32 (*uvDobjCreate)(void);                                     /* inferred */
    /* 0x40 */ void (*uvDobjClearModelAndStateByte)(s32);                                     /* inferred */
    /* 0x44 */ void (*uvDobjSetReciprocalScalar)(s32, f32);                                /* inferred */
    /* 0x48 */ s32 (*uvDobjFindObjectContainingWorldPoint)(f32, f32, f32);                            /* inferred */
    /* 0x4C */ s32 (*uvDobjCollectCapsuleOverlaps)(f32, f32, f32, f32, f32, f32, f32, s32 *); /* inferred */
    /* 0x50 */ s32 (*func_uvdobj_rom_00402420)(f32, f32, f32, f32, s32 **, f32 **,
                                               Vec3F **); /* inferred */
    /* 0x54 */ s32 (*func_uvdobj_rom_00402870)(f32, f32, f32, f32, f32, f32, s32 **, f32 **,
                                               Vec3F **);            /* inferred */
    /* 0x58 */ s32 (*uvDobjWriteJointMatricesFromQuaternions)(s32, Quat *, u8 *);   /* inferred */
    /* 0x5C */ void (*uvDobjReplaceLightColorRecord)(s32, s32, s32, s32); /* inferred */
    /* 0x60 */ u16 (*uvDobjGetQueryArray)(s32 **);              /* inferred */
    /* 0x64 */ s32 *D_uvdobj_rom_004039B0;                           /* inferred */
} UvDobj_Exports;                                                    /* size = 0x68 */
#endif /* UVDOBJ_ROM_H */
