#ifndef UVTEXTURELD_ROM_H
#define UVTEXTURELD_ROM_H

typedef struct UnkStruct_uvtextureld_rom_00400A40_s {
    /* 0x00 */ void* unk0;          
    /* 0x04 */ void* unk4;          
    /* 0x08 */ void* unk8;          
    /* 0x0C */ void* unkC;          
    /* 0x10 */ char pad10[4];
    /* 0x14 */ s32 unk14;           
    /* 0x18 */ u16 unk18;           
    /* 0x1A */ char pad1A[6];                       /* maybe part of unk18[4]? */
    /* 0x20 */ u8 unk20;            
    /* 0x21 */ char pad21[3];                       /* maybe part of unk20[4]? */
} UnkStruct_uvtextureld_rom_00400A40;               /* size = 0x24 */


typedef struct UvTextureLd_Exports_s {
    /* 0x0 */ void (*func_uvtextureld_rom_004000C4)(void);      
    /* 0x4 */ ParsedUVTX* (*uvParseUVTX)(u8 *);   
    /* 0x8 */ void (*func_uvtextureld_rom_00400A40)(UnkStruct_uvtextureld_rom_00400A40 *); /* inferred */
} UvTextureLd_Exports;                              /* size = 0xC */


#endif /* UVTEXTURELD_ROM_H */
