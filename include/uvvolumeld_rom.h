// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef UVVOLUMELD_ROM_H
#define UVVOLUMELD_ROM_H

typedef struct UnkStruct_UvVolumeLd_rom_00400050_inner_1_s {
    char pad[0x1C];
} UnkStruct_UvVolumeLd_rom_00400050_inner_1;

typedef struct UnkStruct_UvVolumeLd_rom_00400050_inner_2_s {
    char pad[0xC];
} UnkStruct_UvVolumeLd_rom_00400050_inner_2;

typedef struct UnkStruct_UvVolumeLd_rom_00400050_inner_s {
    s32 unk0;
    UnkStruct_UvVolumeLd_rom_00400050_inner_1* unk4;
    UnkStruct_UvVolumeLd_rom_00400050_inner_2 unk8;
    s32 unk14;
} UnkStruct_UvVolumeLd_rom_00400050_inner;

typedef struct UnkStruct_UvVolumeLd_rom_00400050_s {
    s32 unk0; // Count of unk4 to follow
    UnkStruct_UvVolumeLd_rom_00400050_inner* unk4;
} UnkStruct_UvVolumeLd_rom_00400050;


typedef struct UvVolumeLd_Rom_Exports_s {
    void (*uvVolumeLoaderCleanup)(void);
    void* (*uvVolumeLoadResource)(u8* arg0);
    void (*uvVolumeFreeResource)(UnkStruct_UvVolumeLd_rom_00400050* arg0);
} UvVolumeLd_Rom_Exports;
#endif /* UVVOLUMELD_ROM_H */
