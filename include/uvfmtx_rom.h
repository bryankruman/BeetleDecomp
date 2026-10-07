#ifndef UVMTX_ROM_H
#define UVMTX_ROM_H

typedef struct UvFMtx_Rom_Exports_s {
    /* 0x000 */ void (*uvFmtxModuleCleanup)();
    /* 0x004 */ void (*uvFmtxSetSharedAxes)(f32, f32, f32);
    /* 0x008 */ void (*func_uvfmtx_rom_00400370)(Mtx4F*, Mtx4F*);
    /* 0x00C */ void (*uvMat4FCopy)(Mtx4F*, Mtx4F*);
    /* 0x010 */ void (*uvMat4CopyLinear3x3)(Mtx4F*, Mtx4F*);
    /* 0x014 */ void (*uvMat4CopyL2F)(Mtx4F*, Mtx);
    /* 0x018 */ void (*uvMat4CopyF2L)(Mtx*, Mtx4F*);
    /* 0x01C */ void (*uvMat4SetIdentity)(Mtx4F*);
    /* 0x020 */ void (*uvMat4Mul)(Mtx4F*, Mtx4F*, Mtx4F*);
    /* 0x024 */ void (*func_uvfmtx_rom_00400FF8)(s32);
    /* 0x028 */ void (*uvMat4RotateAxis)(Mtx4F*, f32, char);
    /* 0x02C */ void (*uvMat4LocalTranslate)(Mtx4F*, f32, f32, f32);
    /* 0x030 */ void (*uvMat4Scale)(Mtx4F*, f32, f32, f32);
    /* 0x034 */ void (*uvMat4ComposeScaleRotateTranslate)(Mtx4F*, f32, f32, f32, f32, f32, f32, u8, u8, u8, f32, f32, f32);
    /* 0x038 */ void (*uvMat4InvertTranslationRotation)(Mtx4F*, Mtx4F*);
    /* 0x03C */ s32 (*func_uvfmtx_rom_00401790)(Mtx4F*, Mtx4F*);
    /* 0x040 */ void (*func_uvfmtx_rom_00401B88)(Mtx4F*, Mtx4F*);
    /* 0x044 */ void (*func_uvfmtx_rom_00401C3C)(Mtx4F*, Mtx4F*, f32, f32);
    /* 0x048 */ void (*uvMat4TransformPoint)(Mtx4F*, Vec3F*, Vec3F*);
    /* 0x04C */ void (*func_uvfmtx_rom_00401DA8)(Mtx4F*, Mtx4F*, Mtx4F*);
    /* 0x050 */ void (*func_uvfmtx_rom_00401F74)(Mtx4F*, f32, f32, f32, f32, f32, f32);
    /* 0x054 */ void (*func_uvfmtx_rom_00402038)(Mtx4F*, f32, f32, f32, f32, f32, f32);
    /* 0x058 */ void (*uvMat4SetOrtho)(Mtx4F*, f32, f32, f32, f32);
    /* 0x05C */ void (*func_uvfmtx_rom_004021E0)(Mtx4F*, f32, f32, f32, f32, f32, f32, f32, f32, f32);
    /* 0x060 */ void (*func_uvfmtx_rom_0040246C)(Mtx4F*, f32, f32, f32, f32);
    /* 0x064 */ void (*func_uvfmtx_rom_00402628)(Mtx4F*, Mtx4F*, f32, f32);
    /* 0x068 */ void (*uvGfxMtxViewLoad)(Mtx4F*, u16);
    /* 0x06C */ void (*uvMat4PushFloatMatrix)(Mtx4F*);
    /* 0x070 */ void (*uvGfxMtxFViewPop)(void);
    /* 0x074 */ void (*uvGfxMtxProjPushF)(Mtx4F*);
    /* 0x078 */ void (*uvGfxMtxCopySharedFloatMatrix)(Mtx4F*);
    /* 0x07C */ void (*func_uvfmtx_rom_004029DC)(Mtx4F*);
    /* 0x080 */ void (*func_uvfmtx_rom_00402B30)(Mtx4F*, f32, f32, f32);
    /* 0x084 */ void (*uvMat4SetTranslation)(Mtx4F*, f32, f32, f32);
    /* 0x088 */ void (*uvFmtxCopyVector)(Vec3F*, Vec3F*);
    /* 0x08C */ void (*uvFmtxCopyNegatedVector)(Vec3F*, Vec3F*);
    /* 0x090 */ void (*uvMat4GetYAxis)(Vec3F*, Mtx4F*);
    /* 0x094 */ void (*uvMat4GetNegatedYAxis)(Vec3F*, Mtx4F*);
    /* 0x098 */ void (*uvMat4GetZAxis)(Vec3F*, Mtx4F*);
    /* 0x09C */ void (*uvMat4GetNegatedZAxis)(Vec3F*, Mtx4F*);
    /* 0x0A0 */ void (*uvMat4GetYAxisAlias)(Vec3F*, Mtx4F*);
    /* 0x0A4 */ void (*uvMat4GetTranslation)(Vec3F*, Mtx4F*);
    /* 0x0A8 */ void (*uvMat4GetDirectionAngles)(Mtx4F*, f32*, f32*, f32*);
    /* 0x0AC */ void (*uvMat4GetTranslationAndDirectionAngles)(Mtx4F*, Vec3F*, Vec3F*);
    /* 0x0B0 */ void (*uvMat4TransformDirection)(Mtx4F*, Vec3F*, Vec3F*);
    /* 0x0B4 */ f32 (*uvMat4TransformPointAndW)(Mtx4F*, Vec3F*, Vec3F*);
    /* 0x0B8 */ void (*uvMat4TransformXY)(Mtx4F*, Vec3F*, Vec3F*);
    /* 0x0BC */ void (*func_uvfmtx_rom_00403290)(Mtx4F*, Mtx4F*, Mtx4F*);
    /* 0x0C0 */ void (*func_uvfmtx_rom_00403480)(Mtx4F*, Vec3F*, f32, f32, f32, f32);
    /* 0x0C4 */ void (*func_uvfmtx_rom_00403568)(Mtx4F*, Vec3F*, Mtx4F*, f32, f32);
    /* 0x0C8 */ void (*uvFmtxCopyAlternateSharedMatrix)(Mtx4F*);
} UvFMtx_Rom_Exports;
#endif /* UVMTX_ROM_H */
