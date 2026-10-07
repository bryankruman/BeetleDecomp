#ifndef UVMODEL_ROM_H
#define UVMODEL_ROM_H

typedef struct UnkStruct_uvmodel_rom_00400608_s {
    Vec3F *unk0;
    u8 unk4;
} UnkStruct_uvmodel_rom_00400608;


typedef struct Arg6_Struct_s {
    /* 0x00 */ char pad0[5];
    /* 0x05 */ u8 unk5;
    /* 0x06 */ char pad6[0x12]; /* maybe part of unk5[0x13]? */
    /* 0x1C */ Vtx *unk18;
} Arg6_Struct; /* size = 0x20 */


typedef struct UvModel_Exports_s {
    /* 0x00 */ void (*uvModelCleanup)(void);                      /* inferred */
    /* 0x04 */ void (*uvModelReservedCallback0)(s32);                   /* inferred */
    /* 0x08 */ void (*uvModelReservedCallback1)(s32, s32);              /* inferred */
    /* 0x0C */ void (*uvModelReservedCallback2)(s32, s32, s32);         /* inferred */
    /* 0x10 */ s32 (*uvModelGetFirstStateWordAddress)(s32);                   /* inferred */
    /* 0x14 */ void (*uvModelGetPosm)(s32, s32, Mtx4F *);    /* inferred */
    /* 0x18 */ void (*uvModelGetProps)(s32, ...);             /* inferred */
    /* 0x1C */ u8 (*uvModelFindThresholdBand)(ParsedUVMD *, f32); /* inferred */
    /* 0x20 */ s16 (*func_uvmodel_rom_004006B4)(f32, f32, f32, f32, Mtx4F *, uvModelLOD *, ParsedUVMD *); /* inferred */
    /* 0x24 */ s16 (*func_uvmodel_rom_0040199C)(f32, f32, f32, f32, f32, f32, Mtx4F *, uvModelLOD *, ParsedUVMD *); /* inferred */
    /* 0x28 */ s16 (*uvModelTestWorldPointInLodBounds)(f32 x, f32 y, f32 z, Mtx4F *arg3, uvModelLOD *arg4); /* inferred */
    /* 0x2C */ s32 (*uvModelContainsLocalPoint)(f32, f32, f32, uvModelLOD_inner *); /* inferred */
    /* 0x30 */ u8 (*uvModelIntersectSegmentWithBoundsFaces)(f32, f32, f32, f32, f32, f32, UnkUVMD_24_Unk4 *, f32 *, f32 *, s16 *, s16 *); /* inferred */
    /* 0x34 */ void (*uvModelResetMatrixStack)(void);                     /* inferred */
    /* 0x38 */ Mtx4F *(*uvModelGetCurrentMatrix)(void);                   /* inferred */
    /* 0x3C */ void (*uvModelPushMatrix)(Mtx4F *);              /* inferred */
    /* 0x40 */ void (*uvModelPopMatrix)(void);                     /* inferred */
    /* 0x44 */ void (*uvModelReplaceTextureId)(ParsedUVMD *, s32, s32); /* inferred */
    /* 0x48 */ s32 (*uvModelCollectStatesByTextureId)(ParsedUVMD *, uvGfxState **, s32); /* inferred */
    /* 0x4C */ void (*uvModelSetCollisionMetadataWord38)(s32, s32);             /* inferred */
} UvModel_Exports;                                  /* size = 0x50 */

#endif /* UVMODEL_ROM_H */
