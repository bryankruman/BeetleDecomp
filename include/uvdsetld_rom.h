#ifndef UVDSETLD_ROM_H
#define UVDSETLD_ROM_H
typedef struct UnkStruct_uvdsetld_rom_00400050_s {
    u8 tagByte1;
    u8 tagByte2;
    u8 tagByte3;
    u8 tagByte4;
    s32 size;
} UnkStruct_uvdsetld_rom_00400050;

typedef struct UvDSetLd_Rom_Exports_s {
    /* 0x0 */ void (*uvDataSetLoaderCleanup)(void);                       /* inferred */
    /* 0x4 */ u8 *(*uvDataSetLoadReferences)(u8 *);                    /* inferred */
    /* 0x8 */ void (*uvDataSetUnloadReferences)(void *);                 /* inferred */
} UvDSetLd_Rom_Exports;                             /* size = 0xC */
#endif /* UVDSETLD_ROM_H */
