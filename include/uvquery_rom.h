#ifndef UVQUERY_ROM_H
#define UVQUERY_ROM_H

typedef struct query_28_s {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;                            /* inferred */
    /* 0x08 */ Vec3F unk8;                          /* inferred */
    /* 0x14 */ Vec3F unk14;                         /* inferred */
    /* 0x20 */ f32 unk20;                           /* inferred */
    /* 0x24 */ f32 unk24;                           /* inferred */
} query_28;                                         /* size = 0x28 */

typedef struct query_78_s {
    /* 0x00 */ Vec3F unk0;
    /* 0x0C */ Vec3F unkC;                            /* inferred */
    /* 0x18 */ Vec3F unk18;                           /* inferred */
    /* 0x24 */ Vec3F unk24;                           /* inferred */
    /* 0x30 */ Mtx4F unk30;                         /* inferred */
    /* 0x70 */ s32 unk70;                           /* inferred */
    /* 0x74 */ s32 unk74;                           /* inferred */
} query_78;                                         /* size = 0x78 */
    

typedef struct UvQuery_Exports_s {
    /* 0x00 */ void (*func_uvquery_rom_004001AC)(void);            
    /* 0x04 */ f32* (*uvQueryGetFloatValues)(void);             
    /* 0x08 */ s32* (*uvQueryGetIntValues)(void);             
    /* 0x0C */ Vec3F* (*uvQueryGetFloatVectors)(void);             
    /* 0x10 */ s32 (*func_uvquery_rom_00400224)(void);            
    /* 0x14 */ s32* (*func_uvquery_rom_00400270)(void);           
    /* 0x18 */ s32* (*func_uvquery_rom_0040027C)(void);           
    /* 0x1C */ s32 (*func_uvquery_rom_00400288)(void);            
    /* 0x20 */ void (*uvQueryDoSorting)(void);           
    /* 0x24 */ query_78* (*func_uvquery_rom_004004CC)(void);            
    /* 0x28 */ void (*uvQueryProps)(s32, ...);   
    /* 0x2C */ void (*uvQueryGetProps)(s32, ...);   
    /* 0x30 */ void (*func_uvquery_rom_004005C0)(f32*, s32);  
    /* 0x34 */ void (*func_uvquery_rom_004005D4)(s32, u16);   
    /* 0x38 */ query_28* (*func_uvquery_rom_004005EC)(void);            
    /* 0x3C */ s32* (*func_uvquery_rom_004005F8)(void);           
    /* 0x40 */ s32 (*func_uvquery_rom_00400604)(void);            
    /* 0x44 */ u16 (*func_uvquery_rom_00400610)(void);            
} UvQuery_Exports;                                   /* size = 0x48 */

#endif /* UVQUERY_ROM_H*/
