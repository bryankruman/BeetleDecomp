// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvled_rom_400000(UvLed_Exports *exports);
void func_uvled_rom_00400118(void);
void func_uvled_rom_00400148(u8 *arg0);
void func_uvled_rom_004002E0(s32 arg0);
void func_uvled_rom_00400300(s32 arg0);
void func_uvled_rom_00400320(s32 arg0);
void func_uvled_rom_00400340(s16 arg0, s16 arg1);
void func_uvled_rom_0040035C(f32 arg0, f32 arg1);
void func_uvled_rom_00400410(u8 r, u8 g, u8 b, u8 a);
void func_uvled_rom_004004C8(s32 arg0, u16 arg1);
void func_uvled_rom_004007A4(f32 arg0);
void func_uvled_rom_00400B2C(u16 arg0);
void func_uvled_rom_00400C04(u8 arg0);
void func_uvled_rom_00400DFC(u8 *fmt, s32 arg1, ...);

u16 D_uvled_rom_004011B0[0x32] = {
    0xFC0, 0x840, 0,    0x40,   0x2000, 0x500, 0x3F,  6,     0x6D,  0x4F,  0x56,  0x5B,  0x7B,
    0xE,   0x7F,  0x5F, 0x3000, 0,      0x600, 0x41,  0x180, 0,     0,     0x7E,  0x47B, 0x39,
    0x1B0, 0x79,  0x78, 0x239,  0x76,   0x809, 0x27,  0xE00, 0x31,  0x4B6, 0x2B6, 0x3F,  0x7C,
    0x23F, 0x27C, 0x5B, 0x808,  0x37,   0x286, 0x336, 0x780, 0x580, 0x509, 0,
};

u8 D_uvled_rom_00401214[0x14] = {
    0x3F, 6,    0x6D, 0x4F, 0x56, 0x5B, 0x7B, 0xE, 0x7F, 0x5F,
    0x7E, 0x73, 0x39, 0x67, 0x79, 0x78, 0,    0,   0,    0,
};

Vtx D_uvled_rom_00401228[14] = {
    { { { 2, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 8, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 2, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Vtx D_uvled_rom_00401308[15] = {
    { { { 0, 0xD, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0, 1, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 1, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 9, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 1, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 0xA, 0xD, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 9, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 1, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 5, 6, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 7, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 5, 8, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Vtx D_uvled_rom_004013F8[1] = { { { { 6, 0xE, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } } };
Vtx D_uvled_rom_00401408[8] = {
    { { { 4, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0xC, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 0xA, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 0xA, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 2, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 4, 4, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
    { { { 6, 4, 0 }, 0, { 0, 0 }, { 0, 0xFF, 0, 0xFF } } },
};

Gfx D_uvled_rom_00401488[] = {
    gsSPVertex(D_uvled_rom_00401228, 14, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401498[] = {
    gsSPVertex(D_uvled_rom_00401308, 15, 0),
    gsSPVertex(D_uvled_rom_004013F8, 1, 15),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014B0[] = {
    gsSPVertex(D_uvled_rom_00401408, 8, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014C0[] = {
    gsSP1Triangle(10, 11, 1, 0),
    gsSP1Triangle(10, 1, 0, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014D8[] = {
    gsSP1Triangle(11, 8, 2, 0),
    gsSP1Triangle(11, 2, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004014F0[] = {
    gsSP1Triangle(8, 12, 4, 0),
    gsSP1Triangle(8, 4, 3, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401508[] = {
    gsSP1Triangle(12, 13, 5, 0),
    gsSP1Triangle(12, 5, 4, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401520[] = {
    gsSP1Triangle(13, 9, 6, 0),
    gsSP1Triangle(13, 6, 5, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401538[] = {
    gsSP1Triangle(9, 10, 0, 0),
    gsSP1Triangle(9, 0, 7, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401550[] = {
    gsSP1Triangle(6, 9, 7, 0), gsSP1Triangle(2, 6, 7, 0), gsSP1Triangle(2, 3, 6, 0),
    gsSP1Triangle(2, 8, 3, 0), gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401578[] = {
    gsSP1Triangle(0, 9, 11, 0),
    gsSP1Triangle(0, 11, 7, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401590[] = {
    gsSP1Triangle(2, 9, 11, 0),
    gsSP1Triangle(2, 11, 1, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015A8[] = {
    gsSP1Triangle(4, 11, 9, 0),
    gsSP1Triangle(4, 9, 3, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015C0[] = {
    gsSP1Triangle(6, 11, 9, 0),
    gsSP1Triangle(6, 9, 5, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015D8[] = {
    gsSP1Triangle(12, 13, 15, 0),
    gsSP1Triangle(12, 15, 14, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_004015F0[] = {
    gsSP1Triangle(0, 2, 1, 0),
    gsSP1Triangle(0, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx D_uvled_rom_00401608[] = {
    gsSP1Triangle(4, 5, 7, 0),
    gsSP1Triangle(4, 7, 6, 0),
    gsSPEndDisplayList(),
};

Gfx *D_uvled_rom_00401620[0xE] = {
    D_uvled_rom_004014C0, D_uvled_rom_004014D8, D_uvled_rom_004014F0, D_uvled_rom_00401508,
    D_uvled_rom_00401520, D_uvled_rom_00401538, D_uvled_rom_00401550, D_uvled_rom_00401578,
    D_uvled_rom_00401590, D_uvled_rom_004015A8, D_uvled_rom_004015C0, D_uvled_rom_004015D8,
    D_uvled_rom_004015F0, D_uvled_rom_00401608,
};

s32 D_uvled_rom_00401658[] = { 0x00240000, __entrypoint_func_uvled_rom_400000 };

// .bss
s16 D_uvled_rom_00401660;
s16 D_uvled_rom_00401662;
f32 D_uvled_rom_00401664;
f32 D_uvled_rom_00401668;
s16 D_uvled_rom_0040166C;
s16 D_uvled_rom_0040166E;
s32 D_uvled_rom_00401670;
UvFMtx_Rom_Exports *D_uvled_rom_00401674;
UvGfxMgr_Exports *D_uvled_rom_00401678;

void __entrypoint_func_uvled_rom_400000(UvLed_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_uvled_rom_00400118 = func_uvled_rom_00400118;
    exports->func_uvled_rom_00400148 = func_uvled_rom_00400148;
    exports->func_uvled_rom_004002E0 = func_uvled_rom_004002E0;
    exports->func_uvled_rom_00400300 = func_uvled_rom_00400300;
    exports->func_uvled_rom_00400320 = func_uvled_rom_00400320;
    exports->func_uvled_rom_00400340 = func_uvled_rom_00400340;
    exports->func_uvled_rom_0040035C = func_uvled_rom_0040035C;
    exports->func_uvled_rom_00400410 = func_uvled_rom_00400410;
    exports->func_uvled_rom_00400DFC = func_uvled_rom_00400DFC;
#line 200
    D_uvled_rom_00401674 = uvLoadModule('FMTX');
    D_uvled_rom_00401678 = uvLoadModule('GMGR');
    D_uvled_rom_00401664 = 0.0f;
    D_uvled_rom_00401668 = 0.0f;
    D_uvled_rom_0040166C = 0xC;
    D_uvled_rom_0040166E = 0x10;
    D_uvled_rom_00401660 = 0;
    D_uvled_rom_00401662 = D_uvled_rom_00401678->uvGetScreenHeight() - D_uvled_rom_0040166E;
    D_uvled_rom_00401670 = 0;
}

void func_uvled_rom_00400118(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('GMGR');
}

void func_uvled_rom_00400148(u8 *arg0) {
    Mtx4F sp88;
    Mtx4F sp48;
    u16 i;
    u8 c;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&sp88, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&sp88);
    D_uvled_rom_00401674->uvMat4SetIdentity(&sp48);
    sp48.m[0][0] = D_uvled_rom_00401664;
    sp48.m[1][1] = D_uvled_rom_00401668;
    sp48.m[3][0] = D_uvled_rom_00401660;
    sp48.m[3][1] = D_uvled_rom_00401662;

    i = 0;
    while (c = arg0[i]) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp48, 2U);
        func_uvled_rom_00400C04(c);
        sp48.m[3][0] += D_uvled_rom_0040166C;
        i++;
    }
}

void func_uvled_rom_004002E0(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 0xA);
}

void func_uvled_rom_00400300(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 2);
}

void func_uvled_rom_00400320(s32 arg0) {
    func_uvled_rom_004004C8(arg0, 0x10);
}

void func_uvled_rom_00400340(s16 arg0, s16 arg1) {
    D_uvled_rom_00401660 = arg0;
    D_uvled_rom_00401662 = arg1;
}

void func_uvled_rom_0040035C(f32 arg0, f32 arg1) {
    D_uvled_rom_00401664 = (arg0 / 10.0);
    D_uvled_rom_00401668 = (arg1 / 14.0);
    D_uvled_rom_0040166C = ((D_uvled_rom_00401664 + 0.25) * 10);
    D_uvled_rom_0040166E = ((D_uvled_rom_00401668 + 0.25) * 14);
}

void func_uvled_rom_00400410(u8 r, u8 g, u8 b, u8 a) {
    s32 i;

    for (i = 0; i < 0x26; i++) {
        D_uvled_rom_00401228[i].v.cn[0] = r;
        D_uvled_rom_00401228[i].v.cn[1] = g;
        D_uvled_rom_00401228[i].v.cn[2] = b;
        D_uvled_rom_00401228[i].v.cn[3] = a;
    }
}

void func_uvled_rom_004004C8(s32 arg0, u16 arg1) {
    Mtx4F spA8;
    Mtx4F sp68;
    u16 temp_hi;
    s32 i;
    u16 sp5E;
    u16 var_v1;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&spA8, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&spA8);
    D_uvled_rom_00401674->uvMat4SetIdentity(&sp68);
    sp68.m[0][0] = D_uvled_rom_00401664;
    sp68.m[1][1] = D_uvled_rom_00401668;
    if (arg0 < 0) {
        sp5E = TRUE;
        arg0 = -arg0;
    } else {
        sp5E = FALSE;
    }

    var_v1 = 0;
    i = 1;
    if (arg0 != 0) {
        while (arg0 >= i) {
            var_v1++;
            i *= arg1;
        }

    } else {
        var_v1 = 1;
    }

    sp68.m[3][0] = (D_uvled_rom_00401660 + ((var_v1 + sp5E) * D_uvled_rom_0040166C));
    sp68.m[3][1] = D_uvled_rom_00401662;
    for (i = 0; i < var_v1; i++) {
        temp_hi = arg0 % arg1;
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp68, 2U);
        func_uvled_rom_00400B2C(temp_hi);
        sp68.m[3][0] -= D_uvled_rom_0040166C;
        arg0 = (arg0 - temp_hi) / arg1;
    }
    if (sp5E) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp68, 2U);
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401550);
    }
    D_uvled_rom_00401660 += D_uvled_rom_0040166C * var_v1;
}

void func_uvled_rom_004007A4(f32 arg0) {
    Mtx4F spC0;
    Mtx4F sp80;
    f32 var_fs0;
    u16 temp_hi;
    s32 i;
    u16 sp72;
    s32 var_s3;
    u16 var_v0;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&spC0, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&spC0);
    D_uvled_rom_00401674->uvMat4SetIdentity(&sp80);
    sp80.m[0][0] = D_uvled_rom_00401664;
    sp80.m[1][1] = D_uvled_rom_00401668;
    if (arg0 < 0.0f) {
        sp72 = TRUE;
        arg0 = -arg0;
    } else {
        sp72 = FALSE;
    }
    var_v0 = 0;
    i = 1;
    var_s3 = arg0;
    if (var_s3 != 0) {
        while (var_s3 >= i) {
            var_v0++;
            i *= 10;
        }
    } else {
        var_v0 = 1;
    }

    sp80.m[3][0] = (D_uvled_rom_00401660 + ((var_v0 + sp72 + 2) * D_uvled_rom_0040166C));
    sp80.m[3][1] = D_uvled_rom_00401662;

    var_fs0 = arg0 - var_s3;
    for (i = 0; i < 2; i++) {
        var_fs0 *= 10.0f;
        temp_hi = (s32) var_fs0;
        var_fs0 -= temp_hi;
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp80, 2U);
        func_uvled_rom_00400B2C(temp_hi);
        sp80.m[3][0] -= (f32) D_uvled_rom_0040166C;
    }

    for (i = 0; i < var_v0; i++) {
        temp_hi = (var_s3 % 10);
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp80, 2U);
        func_uvled_rom_00400B2C(temp_hi);
        sp80.m[3][0] -= D_uvled_rom_0040166C;
        var_s3 = (var_s3 - (temp_hi)) / 10;
    }
    if (sp72) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp80, 2U);
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401550);
    }
    D_uvled_rom_00401660 += D_uvled_rom_0040166C * var_v0;
}

void func_uvled_rom_00400B2C(u16 arg0) {
    u8 temp_s2;
    u8 i;

    temp_s2 = D_uvled_rom_00401214[arg0];
    if (D_uvled_rom_00401670 != 1) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401488);
    }
    for (i = 0; i < 7; i++) {
        if ((1 << i) & temp_s2) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
}

void func_uvled_rom_00400C04(u8 arg0) {
    u16 i;
    u16 temp_s3;

    if (arg0 >= 0x61) {
        arg0 -= 32;
    }
    if ((arg0 < 0x2A) || (arg0 >= 0x5B)) {
        return;
    }

    arg0 -= 0x2A;
    temp_s3 = D_uvled_rom_004011B0[arg0];
    if (D_uvled_rom_00401670 != 1) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401488);
    }

    for (i = 0; i < 7; i++) {
        if ((1 << i) & temp_s3) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
    if (D_uvled_rom_00401670 != 2) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401498);
    }

    for (i = 7; i < 12; i++) {
        if ((1 << i) & temp_s3) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
    if (D_uvled_rom_00401670 != 3) {
        D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_004014B0);
    }

    for (i = 12; i < 14; i++) {
        if ((1 << i) & temp_s3) {
            D_uvled_rom_00401678->uvGfxDisplayList(D_uvled_rom_00401620[i]);
        }
    }
}

void func_uvled_rom_00400DFC(u8 *fmt, s32 arg1, ...) {
    s32 *spB4;
    s32 idx;
    s32 base;
    char ch;
    Mtx4F spB0;
    Mtx4F sp70;
    u8 *sp24;
    s32 sp20;

    D_uvled_rom_00401670 = 0;
    D_uvled_rom_00401674->uvMat4SetOrtho(&spB0, 0.0f, D_uvled_rom_00401678->uvGetScreenWidth(), 0.0f,
                                        D_uvled_rom_00401678->uvGetScreenHeight());
    D_uvled_rom_00401674->uvGfxMtxProjPushF(&spB0);
    D_uvled_rom_00401674->uvMat4SetIdentity(&sp70);
    spB4 = &arg1;
    sp70.m[0][0] = D_uvled_rom_00401664;
    sp70.m[1][1] = D_uvled_rom_00401668;
    sp70.m[3][0] = D_uvled_rom_00401660;
    sp70.m[3][1] = D_uvled_rom_00401662;

    idx = 0;
    ch = fmt[idx];
    while (ch != 0) {
        D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp70, 2U);
        if (ch == '%') {
            idx++;
            ch = fmt[idx];
            base = 0;
            if (ch == 'x') {
                base = 16;
            } else if (ch == 'd') {
                base = 10;
            } else if (ch == 'b') {
                base = 2;
            } else if (ch == 'f') {
            } else if (ch == 's') {
                sp24 = (u8 *) *spB4;
                sp20 = 0;
                sp70.m[0][0] = D_uvled_rom_00401664;
                sp70.m[1][1] = D_uvled_rom_00401668;
                while (sp24[sp20] != 0) {
                    D_uvled_rom_00401674->uvGfxMtxViewLoad(&sp70, 2U);
                    sp70.m[3][0] += D_uvled_rom_0040166C;
                    func_uvled_rom_00400C04(sp24[sp20]);
                    sp20 += 1;
                }
                sp70.m[3][0] -= D_uvled_rom_0040166C;
            }
            if (base != 0) {
                D_uvled_rom_00401660 = (sp70.m[3][0] - D_uvled_rom_0040166C);
                D_uvled_rom_00401662 = sp70.m[3][1];
                func_uvled_rom_004004C8(*spB4, base);
                sp70.m[3][0] = D_uvled_rom_00401660;
                sp70.m[3][1] = D_uvled_rom_00401662;
            }
            spB4 += 1;
        } else if (ch == '\n') {
            sp70.m[3][0] = -D_uvled_rom_0040166C;
            sp70.m[3][1] -= D_uvled_rom_0040166E;
            D_uvled_rom_00401662 += D_uvled_rom_0040166E;
        } else {
            func_uvled_rom_00400C04(ch);
        }

        idx += 1;
        ch = fmt[idx];
        sp70.m[3][0] += D_uvled_rom_0040166C;
    }
    D_uvled_rom_00401660 = sp70.m[3][0];
    D_uvled_rom_00401662 = sp70.m[3][1];
}
