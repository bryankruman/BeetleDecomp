#ifndef UVASSET_TYPES_H
#define UVASSET_TYPES_H
typedef struct UnkSobjDraw {
    u16 modelId;
    Mtx* unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u16 unk14;
    u16 unk16;
} UnkSobjDraw;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
} Unk80225FBC_0x28_UnkC; // size = 0x10

typedef struct {
    uvGfxState unk0;
    Unk80225FBC_0x28_UnkC* unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    char pad[0x14];
} Unk80225FBC_0x28;

typedef struct {
    Vtx* vtxTable;
    u16 vtxCount;
    u16 pad6;
    Unk80225FBC_0x28* unk8;
    u16 unkC;
    u16 padE;
    struct UnkSobjDraw* unk10;
    u16 unk14;
    u16 pad16;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} ParsedUVCT; // size = 0x28

typedef struct uvUnkTileStruct {
    Mtx4F unk0;
    ParsedUVCT* unk40;
    char pad44[0x48];
} uvUnkTileStruct; // size = 0x48

typedef struct uvUnkTeraStruct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} uvUnkTeraStruct; // size = 0x18

typedef struct ParsedUVTR {
    uvUnkTeraStruct unk0;
    u8 unk18;
    u8 unk19;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    uvUnkTileStruct* unk28;
} ParsedUVTR; // size = 0x2C


typedef struct UnkUVMD_6 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} UnkUVMD_6; // size = 0x6

typedef struct UnkUVMD_24_Unk4 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} UnkUVMD_24_Unk4;

typedef struct UnkUVMD_24 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 pad3[0x1];
    UnkUVMD_24_Unk4 unk4;
    u16 unk1C;
    UnkUVMD_6* unk20;
} UnkUVMD_24;

typedef struct uvModelPart {
    void* stateTable;
    u8 stateCount;
    u8 unk5;
    u8 unk6;
    UnkUVMD_24* unk8;
    u8 unkC;
    u8 lighting;
} uvModelPart; // size = 0x10

typedef struct uvModelLOD {
    uvModelPart* partTable;
    u8 partCount;
    u8 billboard;
} uvModelLOD; // size = 0x8

#define UVMD_ATTR_TRANSPARENT 1
#define UVMD_ATTR_UNKNOWN 2

typedef struct ParsedUVMD {
    char pad[0x14];
    f32 unk14;
    Vtx* vtxTable;
    u16 vtxCount;

} ParsedUVMD; // size = 0x28
typedef struct UnkUVTX_1C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
} UnkUVTX_1C; // size = 0x1C

typedef struct ParsedUVTX {
    void *unk0;
    Gfx *unk4;
    u16 size;
    u16 padA;
    u8 data[1];
    u8 unkD;
    char pad[0x4];
    u16 unk12;
    u16 unk14;
    s32 pad18;
    u16 width;
    u16 height;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    f32 unk28;
    u8* unk2C;
} ParsedUVTX;

#endif /* UVASSET_TYPES_H */
