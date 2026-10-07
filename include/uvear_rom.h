#ifndef UVEAR_ROM_H
#define UVEAR_ROM_H
typedef struct UnkStruct_uvear_rom_00400854_s {
    /* 0x00 */ Vec3F vec;
    /* 0x0C */ Vec3F unkC;  /* inferred */
    /* 0x18 */ f32 unk18;   /* inferred */
    /* 0x1C */ f32 unk1C;   /* inferred */
    /* 0x20 */ f32 unk20;   /* inferred */
    /* 0x24 */ f32 unk24;   /* inferred */
    /* 0x28 */ f32 unk28;   /* inferred */
    /* 0x2C */ f32 unk2C;   /* inferred */
    /* 0x30 */ Vec3F unk30; /* inferred */
    /* 0x3C */ char pad3C[4];
    /* 0x40 */ f64 unk40;      /* inferred */
} UnkStruct_uvear_rom_0040085; /* size = 0x48 */

typedef struct UvEar_Rom_Exports_s {
    /* 0x00 */ void (*uvEarModuleCleanup)(void);                               /* inferred */
    /* 0x04 */ void (*uvEarSetPosition)(u16, Vec3F);                         /* inferred */
    /* 0x08 */ void (*uvEarGetPosition)(u16, Vec3F *);                       /* inferred */
    /* 0x0C */ void (*uvEarSetSecondaryVector)(u16, Vec3F);                         /* inferred */
    /* 0x10 */ void (*uvEarGetSecondaryVector)(u16, Vec3F *);                       /* inferred */
    /* 0x14 */ void (*uvEarSetVectorsFromState)(u16, UnkStruct_uvear_rom_0040085 *); /* inferred */
    /* 0x18 */ void (*uvEarSetVelocity)(u16, Vec3F);                         /* inferred */
    /* 0x1C */ void (*uvEarGetVelocity)(u16, Vec3F *);                       /* inferred */
    /* 0x20 */ void (*uvEarUpdateVelocityHistory)(u16);                                /* inferred */
    /* 0x24 */ s32 (*uvEarFindNearestSlot)(s32, Vec3F *);                        /* inferred */
} UvEar_Rom_Exports;                                                                /* size = 0x28 */
#endif /* UVEAR_ROM_H */
