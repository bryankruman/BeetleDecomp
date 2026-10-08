// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

/* Focused original export prefixes; skipped slots are deliberately opaque.
 * RE_UNKNOWN: complete export/storage layouts and historical declaration
 * widths require the original providers and all callers, not these views. */
typedef struct {
    u8 opaque00[8];
    void (*appendChildRow)(void *, void *);
    u8 opaque0C[0x64];
    s16 (*allocateChildGroup)(void);
    void *(*getChildGroup)(s16);
    void (*copyChildGroupText)(void *, u8 *);
    u8 opaque7C[8];
    void (*attachTextList)(void *, void *);
    u8 opaque88[0xC];
    s16 (*allocateTextList)(void);
    void *(*getTextList)(s16);
    void (*copyTextListText)(void *, u8 *);
} ProfgameGuiExports;
typedef struct {
    u8 opaque00[0x14];
    void (*initializeSharedWidget)(void);
    u8 opaque18[0x10];
    u8 *sharedDebugByte;
} ProfgameGameGuiExports;
typedef struct {
    u8 opaque00[0x104];
    void *(*createBoundScalarRow)(void *, u8 *, s16, f32, f32, s32 *, void **);
} ProfgameMiscExports;
typedef struct {
    u8 opaque00[0x24];
    void (*appendCarAnimationControls)(void *);
} ProfgameCaranimExports;
extern ProfgameGuiExports *gUvGuiExports;
extern ProfgameGameGuiExports *gGameGuiExports;
extern ProfgameMiscExports *gMiscExports;
extern ProfgameCaranimExports *D_profgame_0040064C;
extern u8 D_profgame_00400570[];
extern u8 D_profgame_0040057C[];
extern u8 D_profgame_00400584[];
extern s32 D_profgame_00400590;

#line 2 "src/modules/profgame.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/profgame/__entrypoint_func_profgame_400000.s")

#line 4 "src/modules/profgame.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_profgame_004002D8(void) {
}
#line 6 "src/modules/profgame.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/profgame/func_profgame_004002E0.s")

#line 9 "src/modules/profgame.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_profgame_004003F8(void) {
}
#line 11 "src/modules/profgame.c"

#line 12 "src/modules/profgame.c"

/* Build the original "profile car" group, its "profile" text list and
 * "NUM CARS" bound scalar row, then append the car-animation controls.
 * Snapshot the shared-byte address plus 0x10 before shared-widget initialization
 * and reload export pointers across callbacks. Preserve signed-low16 pool IDs,
 * flags 0x12, bounds 0..8 and the original shared value/output addresses.
 * RE_ORIGINAL_QUIRK: allocation results and child-attachment capacity are not
 * checked here. RE_UNKNOWN: entry/exhaustion reachability, callback mutation and
 * host/storage lifetime need original callers, active-slot writers and shared
 * storage producers. The GUI label copies read 30 bytes; the original label
 * objects' full readable windows and bound-word lifecycle need original layout
 * and reader/writer proof before adding bounds or assigning numeric units. */
void profgameCreateProfileCarControls(void) {
    void *host;
    void *group;
    void *textList;
    void *valueWidget;

    host = gGameGuiExports->sharedDebugByte + 0x10;
    gGameGuiExports->initializeSharedWidget();
    group = gUvGuiExports->getChildGroup(gUvGuiExports->allocateChildGroup());
    gUvGuiExports->copyChildGroupText(group, D_profgame_00400570);
    gUvGuiExports->appendChildRow(host, group);
    textList = gUvGuiExports->getTextList(gUvGuiExports->allocateTextList());
    gUvGuiExports->copyTextListText(textList, D_profgame_0040057C);
    gUvGuiExports->attachTextList(group, textList);
    gMiscExports->createBoundScalarRow(textList, D_profgame_00400584,
        0x12, 0.0f, 8.0f, &D_profgame_00400590, &valueWidget);
    D_profgame_0040064C->appendCarAnimationControls(group);
}
#line 13 "src/modules/profgame.c"

