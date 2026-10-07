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
    void (*powerupReleaseObjectPoolAndModel)(void);
    void (*powerupCreateObjectAtPosition)(s32, Vec3F *);
    UnkStruct_Powerup_004003C0 *(*powerupGetDescriptorOrDefault)(s32);
} Powerup_Exports;

#endif /* BAR_POWERUP_H */
