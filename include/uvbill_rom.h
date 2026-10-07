#ifndef UVBILL_ROM_H
#define UVBILL_ROM_H
typedef struct UvBill_Exports_s {
    /* 0x0 */ void (*uvBillDestroy)(void);
    /* 0x4 */ void (*uvBillboardAttachChannelCallback)(s32);
    /* 0x8 */ s32 (*func_uvbill_rom_004010B8)(f32, f32, f32, f32, f32, f32, s32, s32 **, f32 **,
                                              Vec3F **);
    /* 0xC */ s32 (*uvBillboardIntersectsSphere)(s32, f32, f32, f32, f32);
    /* 0x10 */ s32 (*uvBillboardQuerySphere)(f32, f32, f32, f32, s32, s32 **);
    /* 0x14 */ void (*uvBillSetTransMtx)(s32, Mtx4F *);
    /* 0x18 */ void (*uvBillProps)(s32, ...);
    /* 0x1C */ s32 (*uvBillInit)(void);
    /* 0x20 */ void (*uvBillboardRelease)(s32);
} UvBill_Exports;

#endif /* UVBILL_ROM_H*/
