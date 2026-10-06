#ifndef BAR_POWERUP_H
#define BAR_POWERUP_H

typedef struct UnkStruct_Powerup_004003C0_s {
    s32 unk0;
    f32 unk4;
    f32 red;
    f32 green;
    f32 blue;
} UnkStruct_Powerup_004003C0;

typedef struct Powerup_Exports_s {
    void (*func_powerup_004000F0)(void);
    void (*func_powerup_00400180)(s32, Vec3F *);
    UnkStruct_Powerup_004003C0 *(*func_powerup_00400330)(s32);
} Powerup_Exports;

#endif /* BAR_POWERUP_H */
