// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/*__SEEDEXTERNS__*/
typedef struct UvGeom_Exports {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ void (*setColor)(f32, f32, f32, f32);
    /* 0x10 */ void (*fillRectangle)(s32, s32, s32, s32);
} UvGeom_Exports;
extern UvGeom_Exports *gUvGeomExports;
typedef struct ScrnGeomList {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 count;
    /* 0x04 */ u8 pad4[0x22];
    /* 0x26 */ s16 x0;
    /* 0x28 */ s16 x1;
    /* 0x2A */ s16 y0;
    /* 0x2C */ s16 y1;
} ScrnGeomList;
#include "uvgfxmgr_rom.h"
typedef struct { u8 prefix[0x12]; s16 selected; f32 first, second, third; } ScrnDrawState;
extern ScrnDrawState D_scrn_004006C8;
extern ScrnGeomList D_scrn_004004C0;
extern UvGfxMgr_Exports *gUvGfxMgrExports;

extern s32 D_scrn_004006E8;
extern s16 D_scrn_004006DA;
/* Initializer-only storage view: each field is an original 32-bit address,
 * not an inferred callable export interface. Opaque assembly declarations
 * below identify linker code-label addresses only: no data object or function
 * signature is inferred, and these addresses are never dereferenced here.
 * RE_UNKNOWN: replace each opaque label declaration with a grounded function
 * prototype when its implementation and actual caller ABI are recovered. */
typedef struct {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 unknownCallback04Address;
    /* 0x08 */ u32 resetSelectionAddress;
    /* 0x0C */ u32 unknownCallback0CAddress;
    /* 0x10 */ u32 drawSelectedGeometryAddress;
    /* 0x14 */ u32 unknownCallback14Address;
    /* 0x18 */ u32 drawStateAddress;
    /* 0x1C */ u32 submissionDisabledAddress;
} ScrnExportAddresses;
void func_scrn_00400094(void);
void scrnResetSelection(void);
void scrnDrawSelectedGeometry(void);
extern u8 func_scrn_0040009C[];
extern u8 func_scrn_0040027C[];
extern u8 func_scrn_00400474[];

#line 52 "src/modules/scrn.c"
/* Register the six original screen callback addresses and two shared-state
 * addresses after updating the allocation pointer. Preserve the initial slot
 * 0x14 store before slots 0x00 through 0x10, then clear the selection halfword
 * and three fill-color components. The submission-disable word is exported
 * but is not reset here. Preserve the empty callback's separate identity.
 * RE_UNKNOWN: callback contracts at slots 0x04/0C/14, caller-owned export
 * storage capacity/lifetime and shared-state initialization/reload ownership
 * require the original targets, table consumers and module-loader callers. */
void __entrypoint_func_scrnInitializeModuleExports(ScrnExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->unknownCallback14Address = (u32) func_scrn_00400474;
    exports->emptyCallbackAddress = (u32) func_scrn_00400094;
    exports->unknownCallback04Address = (u32) func_scrn_0040009C;
    exports->resetSelectionAddress = (u32) scrnResetSelection;
    exports->unknownCallback0CAddress = (u32) func_scrn_0040027C;
    exports->drawSelectedGeometryAddress = (u32) scrnDrawSelectedGeometry;
    exports->drawStateAddress = (u32) &D_scrn_004006C8;
    exports->submissionDisabledAddress = (u32) &D_scrn_004006E8;
    D_scrn_004006C8.selected = 0;
    D_scrn_004006C8.first = 0.0f;
    D_scrn_004006C8.second = 0.0f;
    D_scrn_004006C8.third = 0.0f;
}
#line 53 "src/modules/scrn.c"

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
#line 41 "src/modules/scrn.c"
/* Unless disabled, forward signed-short coordinates to GEOM10's fullword fill.
 * Preserve 8-byte advances/count reloads. RE_UNKNOWN: record/index/capacity
 * and alias/lifetime domains need original list writers and every caller. */
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
            gUvGeomExports->fillRectangle(record->x0, record->y0, record->x1, record->y1);
            index += 1;
            record = (ScrnGeomList *)((u8 *)record + 8);
        } while (index < list->count);
    }
}
#line 61 "src/modules/scrn.c"
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

#line 63 "src/modules/scrn.c"
/* Copy shared words using the signed count at shared-state offset0x10;
 * reload that count after every destination store and return its final value.
 * RE_UNKNOWN: shared-word roles, complete source storage, destination capacity
 * and permitted alias domain. Trace original state writers and exported slot14
 * callers before caching the count or inferring a fixed-size public array. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scrn/func_scrn_00400474.s")
#line 64 "src/modules/scrn.c"

