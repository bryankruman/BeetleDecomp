#ifndef ENVSND_H
#define ENVSND_H

typedef struct UnkStruct_envsnd_0040005C_s {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;      /* inferred */
    /* 0x02 */ char pad2[2]; /* maybe part of unk1[3]? */
    /* 0x04 */ f32 unk4;     /* inferred */
    /* 0x08 */ char pad8[4];
    /* 0x0C */ Vec3F unkC;
    /* 0x18 */ f32 unk18; /* inferred */
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8 unk24;      /* inferred */
    /* 0x25 */ char pad25[3]; /* maybe part of unk24[4]? */
} UnkStruct_envsnd_0040005C;  /* size = 0x28 */

typedef struct UnkStruct_envsnd_00400250_unk4_s {
    char pad[0xC];
    s32 unkC;
} UnkStruct_envsnd_00400250_unk4;

typedef struct UnkStruct_envsnd_00400250_unk0_s {
    char pad[0x618];
    Vec3F unk618;
} UnkStruct_envsnd_00400250_unk0;

typedef struct UnkStruct_envsnd_00400250_s {
    UnkStruct_envsnd_00400250_unk0 *unk0;
    UnkStruct_envsnd_00400250_unk4 *unk4;
} UnkStruct_envsnd_00400250;

typedef struct EnvSnd_Exports_s {
    /* 0x00 */ void (*func_envsnd_00400054)(void);                             /* inferred */
    /* 0x04 */ void (*func_envsnd_0040005C)(s32, UnkStruct_envsnd_0040005C *); /* inferred */
    /* 0x08 */ void (*func_envsnd_00400250)(UnkStruct_envsnd_00400250 *);      /* inferred */
    /* 0x0C */ void (*func_envsnd_00400444)(s32, s32);                         /* inferred */
} EnvSnd_Exports;                                                              /* size = 0x10 */

#endif /* ENVSND_H */
