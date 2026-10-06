#ifndef UVPFX_ROM_H
#define UVPFX_ROM_H

typedef struct UnkStruct_uvpfx_rom_00404FA0_unk28_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ char pad2[2];
    /* 0x04 */ s32 unk4; /* inferred */
    /* 0x08 */ s16 unk8; /* inferred */
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char pad16[2];
    /* 0x18 */ f32 unk18;
} UnkStruct_uvpfx_rom_00404FA0_unk28; /* size = 0x1C */

// Maybe it's part of UnkStruct_uvpfx_rom_00404FA0_unk28?
typedef struct UnkStruct_uvpfx_rom_00404FA0_unk2C_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ char pad2[2];
    /* 0x04 */ f32 unk4; /* inferred */
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ s16 unkE;
    /* 0x12 */ char pad12[2];
} UnkStruct_uvpfx_rom_00404FA0_unk2C; /* size = 0x14 */

typedef struct UnkStruct_uvpfx_rom_00404FA0_unk0_s {
    /* 0x00 */ char pad0[2];
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6; /* inferred */
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ char pad15[1];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20; /* inferred */
    /* 0x24 */ s16 unk24; /* inferred */
    /* 0x26 */ char pad26[2];
    /* 0x28 */ UnkStruct_uvpfx_rom_00404FA0_unk28 *unk28;
    /* 0x2C */ UnkStruct_uvpfx_rom_00404FA0_unk2C *unk2C;
    /* 0x30 */ s16 *unk30; /* inferred */
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} UnkStruct_uvpfx_rom_00404FA0_unk0; /* size = 0x3C */

typedef struct UnkStruct_uvpfx_rom_00404FA0_unk4_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32[5][6];
    /* 0x6E */ s16 unk6E;
    /* 0x70 */ Vec3F unk70;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ Mtx4F unk80;
    /* 0xC0 */ Vec3F unkC0;
    /* 0xCC */ f32 unkCC; /* inferred */
    /* 0xD0 */ f32 unkD0; /* inferred */
    /* 0xD4 */ f32 unkD4; /* inferred */
    /* 0xD8 */ f32 unkD8;
    /* 0xDC */ f32 unkDC;
    /* 0xE0 */ f32 unkE0;
    /* 0xE4 */ void (*unkE4)(s32);
    /* 0xE8 */ s32 unkE8;
} UnkStruct_uvpfx_rom_00404FA0_unk4; /* size = 0xEC */

typedef struct UnkStruct_uvpfx_rom_00404FA0_s {
    /* 0x0 */ UnkStruct_uvpfx_rom_00404FA0_unk0 *unk0;
    /* 0x4 */ UnkStruct_uvpfx_rom_00404FA0_unk4 *unk4;
    /* 0x8 */ Vec3F *unk8;      /* inferred */
} UnkStruct_uvpfx_rom_00404FA0; /* size = 0xC */

typedef struct UvPfx_Exports_s {
    /* 0x00 */ void (*func_uvpfx_rom_00401810)(void);               /* inferred */
    /* 0x04 */ void (*func_uvpfx_rom_00400264)(s32);                /* inferred */
    /* 0x08 */ s32 (*func_uvpfx_rom_004002BC)(s32);                 /* inferred */
    /* 0x0C */ s32 (*func_uvpfx_rom_00400398)(s32);                 /* inferred */
    /* 0x10 */ void (*func_uvpfx_rom_00400488)(s32, Mtx4F *);       /* inferred */
    /* 0x14 */ void (*func_uvpfx_rom_004004D0)(s32, ...);           /* inferred */
    /* 0x18 */ void (*func_uvpfx_rom_004012CC)(s32, ...);           /* inferred */
    /* 0x1C */ s32 (*func_uvpfx_rom_00401C6C)(s32);                 /* inferred */
    /* 0x20 */ void (*func_uvpfx_rom_00401D88)(f32);                /* inferred */
    /* 0x24 */ void (*func_uvpfx_rom_00401E7C)(s32);                /* inferred */
    /* 0x28 */ void (*func_uvpfx_rom_00402008)(s32);                /* inferred */
    /* 0x2C */ void (*func_uvpfx_rom_004020D4)(s32);                /* inferred */
    /* 0x30 */ void (*func_uvpfx_rom_0040211C)(s32);                /* inferred */
    /* 0x34 */ void (*func_uvpfx_rom_0040374C)(s32);                /* inferred */
    /* 0x38 */ void (*func_uvpfx_rom_0040381C)(s32, f32);           /* inferred */
    /* 0x3C */ void (*func_uvpfx_rom_00403848)(s32, s32, s16);      /* inferred */
    /* 0x40 */ UnkStruct_uvpfx_rom_00404FA0 **D_uvpfx_rom_00404FA0; /* inferred */
    /* 0x44 */ s32 *D_uvpfx_rom_00404FA4;                           /* inferred */
    /* 0x48 */ s32 *D_uvpfx_rom_00404FA8;                           /* inferred */
    /* 0x4C */ s32 *D_uvpfx_rom_00404FAC;                           /* inferred */
} UvPfx_Exports;                                                    /* size = 0x50 */

#endif /* UVPFX_ROM_H */
