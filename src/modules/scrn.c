// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/*__SEEDEXTERNS__*/
typedef struct UvGeom_Exports {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ void (*setColor)(f32, f32, f32, f32);
    /* 0x10 */ void (*unk10)(s16, s16, s16, s16);
} UvGeom_Exports;
extern UvGeom_Exports *gUvGeomExports;
typedef struct ScrnGeomList {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 count;
    /* 0x04 */ u8 pad4[0x22];
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
} ScrnGeomList;
#include "uvgfxmgr_rom.h"
typedef struct { u8 prefix[0x12]; s16 selected; f32 first, second, third; } ScrnDrawState;
extern ScrnDrawState D_scrn_004006C8;
extern ScrnGeomList D_scrn_004004C0;
extern UvGfxMgr_Exports *gUvGfxMgrExports;

extern s32 D_scrn_004006E8;
extern s16 D_scrn_004006DA;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/__entrypoint_func_scrn_400000.s")

void func_scrn_00400094(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_0040009C.s")

void func_scrn_004001DC(void) {
    D_scrn_004006DA = 0;
}

/* Submit screen geometry elements to the UV geometry export manager. */
void func_scrn_004001E8(ScrnGeomList *arg0) {
    s32 var_s1;
    ScrnGeomList *var_s0;

    if (D_scrn_004006E8 != 0) {
        return;
    }
    var_s1 = 0;
    var_s0 = arg0;
    if (arg0->count > 0) {
        do {
            gUvGeomExports->unk10(var_s0->unk26, var_s0->unk2A, var_s0->unk28, var_s0->unk2C);
            var_s1 += 1;
            var_s0 = (ScrnGeomList *)((u8 *)var_s0 + 8);
        } while (var_s1 < arg0->count);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_0040027C.s")

#line 61 "src/modules/scrn.c"
/* Select the original 0x46-byte screen geometry record, set its fill
 * color with alpha one and append a full-screen viewport. Submit the base
 * geometry when selected halfword 0x4 is nonzero, then submit the selected
 * record. Preserve the shared selection and geometry capacity contracts. */
void scrnDrawSelectedGeometry(void) {
    ScrnGeomList *selected;
    s32 height;
    s32 width;
    selected = (ScrnGeomList *)((u8 *)&D_scrn_004004C0 + D_scrn_004006C8.selected * 0x46);
    gUvGeomExports->setColor(D_scrn_004006C8.first, D_scrn_004006C8.second, D_scrn_004006C8.third, 1.0f);
    width = gUvGfxMgrExports->uvGetScreenWidth();
    height = gUvGfxMgrExports->uvGetScreenHeight();
    gUvGfxMgrExports->uvGfxAppendViewport(0, width, 0, height);
    if (*(s16 *)((u8 *)selected + 4) != 0) func_scrn_004001E8(&D_scrn_004004C0);
    func_scrn_004001E8(selected);
}
#line 62 "src/modules/scrn.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_00400474.s")

