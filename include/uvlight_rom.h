#ifndef UVLIGHT_ROM_H
#define UVLIGHT_ROM_H

typedef struct UnkStruct_uvlight_rom_00401758_s {
    /* 0x00 */ f32 unk0[3];
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24; /* inferred */
    /* 0x28 */ s32 unk28; /* inferred */
    /* 0x2C */ s32 unk2C; /* inferred */
    /* 0x30 */ s32 refCount;
} UnkStruct_uvlight_rom_00401758; /* size = 0x34 */

typedef struct UvLights_Exports_s {
    /* 0x00 */ void (*func_uvlight_rom_004004D8)(void);                            /* inferred */
    /* 0x04 */ void (*func_uvlight_rom_004008D4)(s32);                             /* inferred */
    /* 0x08 */ s32 (*func_uvlight_rom_00400B64)(void);                             /* inferred */
    /* 0x0C */ void (*func_uvlight_rom_00400C60)(s32, f32, f32, f32);              /* inferred */
    /* 0x10 */ void (*func_uvlight_rom_00400D90)(s32, s32, f32, f32, f32);         /* inferred */
    /* 0x14 */ void (*func_uvlight_rom_00400EDC)(s32, s32, Vec3F *);               /* inferred */
    /* 0x18 */ void (*func_uvlight_rom_00400FB8)(Vec3F *, f32 *, f32 *);           /* inferred */
    /* 0x1C */ s32 (*func_uvlight_rom_004011D0)(void);                             /* inferred */
    /* 0x20 */ void (*func_uvlight_rom_0040120C)(s32);                             /* inferred */
    /* 0x24 */ UnkStruct_uvlight_rom_00401758 *(*func_uvlight_rom_0040131C)(s32);  /* inferred */
    /* 0x28 */ s32 (*func_uvlight_rom_00401340)(UnkStruct_uvlight_rom_00401758 *); /* inferred */
    /* 0x2C */ void (*func_uvlight_rom_00401624)(s32);                             /* inferred */
    /* 0x30 */ void (*func_uvlight_rom_0040167C)(s32);                             /* inferred */
} UvLights_Exports;                                                                /* size = 0x34 */

#endif /* UVLIGHT_ROM_H */
