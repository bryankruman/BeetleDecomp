// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ufogame/__entrypoint_func_ufogame_400000.s")

#line 4 "src/modules/ufogame.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ufogame_004001FC(void) {
}
#line 6 "src/modules/ufogame.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/ufogame/func_ufogame_00400204.s")

#line 9 "src/modules/ufogame.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_ufogame_00400314(void) {
}
#line 11 "src/modules/ufogame.c"

#include "common.h"
#include "module.h"
#include "uvgui_rom.h"
/* Consumed N64 export prefixes only; no allocated storage or full extent claim.
 * RE_UNKNOWN: unnamed slots/shared-state extents and provider lifetimes remain
 * unresolved. Opaque widget pointer views retain the proven o32 pointer ABI. */
typedef struct {
    u8 unused00[0x14];
    void (*initializeSharedWidget)(void);
    u8 unused18[0x10];
    u8 *sharedDebugByte;
} UfoGameGuiExports;
typedef struct {
    u8 unused00[0x08];
    void (*appendChild)(s32 *, s32);                  /* 0x08 */
    u8 unused0C[0x34];
    s16 (*allocateCompactText)(void);                 /* 0x40 */
    void *(*getCompactText)(s16);                     /* 0x44 */
    void (*copyCompactText)(s32, u8 *);               /* 0x48 */
    u8 unused4C[0x14];
    void (*attachUpperChild)(void *, void *);          /* 0x60 */
    u8 unused64[0x0C];
    s16 (*allocateChildGroup)(void);                  /* 0x70 */
    void *(*getChildGroup)(s16);                      /* 0x74 */
    void (*copyChildGroupText)(void *, u8 *);          /* 0x78 */
    u8 unused7C[0x08];
    void (*appendMenuOption)(void *, void *);          /* 0x84 */
    u8 unused88[0x0C];
    s16 (*allocateTextList)(void);                    /* 0x94 */
    void *(*getTextList)(s16);                        /* 0x98 */
    void (*copyTextListText)(void *, u8 *);           /* 0x9C */
    u8 unusedA0[0x08];
    void (*appendCompactTextRow)(void *, s32);        /* 0xA8 */
    u8 unusedAC[0x0C];
    s16 (*allocateScalarWidget)(void);               /* 0xB8 */
    u8 unusedBC[0x04];
    void *(*getScalarWidget)(s16);                    /* 0xC0 */
    void (*copyScalarWidgetText)(void *, u8 *);       /* 0xC4 */
    u8 unusedC8[0x0C];
    void (*configureScalarWidget)(Inner28 *, f32, f32, f32, s32 *); /* 0xD4 */
    void (*setScalarWidgetKind)(void *, s16);         /* 0xD8 */
} UfoGameWidgetExports;
typedef struct {
    u8 unused00[0x14];
    void (*callback14)(s32); /* Proven func_ai_00403F4C(s32), currently empty. */
} UfoGameAiExports;
extern void *gGameGuiExports, *gUvGuiExports, *gAiExports;
extern u8 D_ufogame_00400550[], D_ufogame_00400554[];
extern u8 D_ufogame_0040055C[], D_ufogame_00400564[];

#line 12 "src/modules/ufogame.c"
/* Build the debug panel through the original GUI export ABI. */
/* Append the original UFO/camera/test rows and the unbound "test slider" to the
 * shared GAMEGUI child list, then pass the same panel to optional AI slot14.
 * RE_ORIGINAL_QUIRK: every pool result is narrowed to signed16 and used without
 * an exhaustion check; the scalar widget receives a null bound-word pointer.
 * RE_UNKNOWN: full shared-state/pool extents, fixed-width label-read domains,
 * widget lifetime and the optional AI callback's wider role remain unresolved.
 * Its proven AI slot14 provider accepts one s32 and is currently empty; preserve
 * the original call and raw N64 panel address rather than omit it. */
void ufogameBuildCameraDebugPanel(void) {
    void *parentList;
    void *panel;
    void *cameraList;
    void *testRow;
    void *slider;
    s16 poolIndex;

    parentList = ((UfoGameGuiExports *)gGameGuiExports)->sharedDebugByte + 0x10;
    ((UfoGameGuiExports *)gGameGuiExports)->initializeSharedWidget();
    poolIndex = ((UfoGameWidgetExports *)gUvGuiExports)->allocateChildGroup();
    panel = ((UfoGameWidgetExports *)gUvGuiExports)->getChildGroup(poolIndex);
    ((UfoGameWidgetExports *)gUvGuiExports)->copyChildGroupText(panel, D_ufogame_00400550);
    ((UfoGameWidgetExports *)gUvGuiExports)->appendChild(parentList, (s32)panel);
    poolIndex = ((UfoGameWidgetExports *)gUvGuiExports)->allocateTextList();
    cameraList = ((UfoGameWidgetExports *)gUvGuiExports)->getTextList(poolIndex);
    ((UfoGameWidgetExports *)gUvGuiExports)->copyTextListText(cameraList, D_ufogame_00400554);
    ((UfoGameWidgetExports *)gUvGuiExports)->appendMenuOption(panel, cameraList);
    poolIndex = ((UfoGameWidgetExports *)gUvGuiExports)->allocateCompactText();
    testRow = ((UfoGameWidgetExports *)gUvGuiExports)->getCompactText(poolIndex);
    ((UfoGameWidgetExports *)gUvGuiExports)->copyCompactText((s32)testRow, D_ufogame_0040055C);
    ((UfoGameWidgetExports *)gUvGuiExports)->appendCompactTextRow(cameraList, (s32)testRow);
    poolIndex = ((UfoGameWidgetExports *)gUvGuiExports)->allocateScalarWidget();
    slider = ((UfoGameWidgetExports *)gUvGuiExports)->getScalarWidget(poolIndex);
    ((UfoGameWidgetExports *)gUvGuiExports)->setScalarWidgetKind(slider, 0x11);
    ((UfoGameWidgetExports *)gUvGuiExports)->copyScalarWidgetText(slider, D_ufogame_00400564);
    ((UfoGameWidgetExports *)gUvGuiExports)->configureScalarWidget(slider, 15.0f, 120.0f, 40.0f, NULL);
    ((UfoGameWidgetExports *)gUvGuiExports)->attachUpperChild(testRow, slider);
    if (gAiExports != NULL) {
        ((UfoGameAiExports *)gAiExports)->callback14((s32)panel);
    }
}
#line 13 "src/modules/ufogame.c"

