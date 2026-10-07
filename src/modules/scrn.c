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

#line 31 "src/modules/scrn.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_scrn_00400094(void) {
}
#line 33 "src/modules/scrn.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_0040009C.s")

#line 36 "src/modules/scrn.c"
/* Reset the original shared screen-selection halfword to zero. */
void scrnResetSelection(void) {
    D_scrn_004006DA = 0;
}
#line 39 "src/modules/scrn.c"

/* Submit screen geometry elements to the UV geometry export manager. */
#line 41 "src/modules/scrn.c"
/* Unless submission is disabled, emit each rectangle through the
 * geometry library using its original coordinate order. Records advance
 * eight bytes and the count is reloaded after every callback. */
void scrnSubmitGeometryRectangles(ScrnGeomList *list) {
    s32 index;
    ScrnGeomList *record;

    if (D_scrn_004006E8 != 0) {
        return;
    }
    index = 0;
    record = list;
    if (list->count > 0) {
        do {
            gUvGeomExports->unk10(record->unk26, record->unk2A, record->unk28, record->unk2C);
            index += 1;
            record = (ScrnGeomList *)((u8 *)record + 8);
        } while (index < list->count);
    }
}
#line 58 "src/modules/scrn.c"

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
    if (*(s16 *)((u8 *)selected + 4) != 0) scrnSubmitGeometryRectangles(&D_scrn_004004C0);
    scrnSubmitGeometryRectangles(selected);
}
#line 62 "src/modules/scrn.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_00400474.s")

