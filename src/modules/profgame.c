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
    u8 opaque00[0x10];
    void (*slot10)(s32);
    void (*initializeSharedWidget)(void);
    u8 opaque18[4];
    void (*slot1C)(void (*)(void));
    u8 opaque20[8];
    u8 *sharedDebugByte;
} ProfgameGameGuiExports;
typedef struct {
    u8 opaque00[0x104];
    void *(*createBoundScalarRow)(void *, u8 *, s16, f32, f32, s32 *, void **);
} ProfgameMiscExports;
typedef struct {
    u8 opaque00[4];
    void *(*slot04)(s32, s32, u32);
    u8 opaque08[0xC];
    void (*slot14)(void *, ...);
    u8 opaque18[0xC];
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

/* Initializer-only views of observed word/halfword accesses.
 * RE_UNKNOWN: These views do not establish complete original declarations,
 * valid player counts, callback ownership, allocation failure or lifetimes. */
typedef struct { u32 words[3]; } ProfgameInitialWords;
typedef struct {
    s16 handle;
} ProfgameObjectPrefix;
typedef struct {
    u8 opaque00[0x28];
    ProfgameObjectPrefix *object28;
} ProfgamePlayerPrefix;
typedef struct {
    u8 opaque00[4];
    ProfgamePlayerPrefix *(*slot04)(s32, ProfgameInitialWords *);
} ProfgameUfoExports;
typedef struct {
    ProfgamePlayerPrefix *players[4];
    s32 playerCount;
    void *animationSlots[8];
    s32 objectSlots[8];
} ProfgameObservedState;
typedef struct { u8 opaque00[8]; void (*slot08)(s32, s32); } ProfgameTerraExports;
typedef struct { u8 opaque00[0x18]; void (*slot18)(s32, s32); } ProfgameEnvExports;
typedef struct { u8 opaque00[4]; void (*slot04)(s32, ProfgameObjectPrefix **); } ProfgameScreenExports;
typedef struct { u8 opaque00[0x1C]; void (*slot1C)(Mtx4F *); } ProfgameMatrixExports;
typedef struct { u8 opaque00[0x3C]; s32 (*slot3C)(void); } ProfgameDobjExports;
extern ProfgameUfoExports *D_profgame_004005F4;
extern ProfgameObservedState D_profgame_004005F8;
extern ProfgameInitialWords D_profgame_00400594;
extern f32 D_profgame_004005A0[];
extern f32 D_profgame_004005C0[];
extern ProfgameTerraExports *gUvTerraExports;
extern ProfgameEnvExports *gUvEnvExports;
extern ProfgameScreenExports *gScrnExports;
extern ProfgameMatrixExports *gUvFmtxExports;
extern ProfgameDobjExports *gUvDobjExports;
extern s32 gNumPlayers;
extern u8 func_profgame_004002E0[];
void func_profgame_004002D8(void);
void func_profgame_004003F8(void);
void profgameCreateProfileCarControls(void);

#line 2 "src/modules/profgame.c"
#line 2 "src/modules/profgame.c"
/* Publish the three original callbacks, load UFOV, and create the
 * requested player records using the copied three-word initializer. Pass
 * each freshly read signed object handle to TERR08(-1) and ENV18(8), then
 * hand the local object-pointer list to SCRN04 with the live player count.
 * Load CARA, register the existing controls callback, and initialize eight
 * object/animation slots with the original property sequence and matrix.
 * RE_ORIGINAL_QUIRK: Loop bounds reload shared state after callbacks; no
 * allocation or input-count checks are added. RE_UNKNOWN: Valid counts,
 * callback contracts, third animation argument meaning, matrix units, failure handling
 * and ownership/lifetimes require provider and caller evidence. */
void __entrypoint_func_profgame_400000(u32 *exports) {
    ProfgameObjectPrefix *playerObjects[4];
    Mtx4F transform;
    ProfgameInitialWords initialWords;
    s32 index;

    uvUpdateFileAllocPtr(exports);
    exports[0] = (u32)func_profgame_004002D8;
    exports[1] = (u32)func_profgame_004002E0;
    exports[2] = (u32)func_profgame_004003F8;
    initialWords = D_profgame_00400594;
    D_profgame_004005F4 = uvLoadModule(0x75666F76);
    D_profgame_004005F8.playerCount = gNumPlayers;
    for (index = 0; index < D_profgame_004005F8.playerCount; index++) {
        D_profgame_004005F8.players[index] = D_profgame_004005F4->slot04(index, &initialWords);
        playerObjects[index] = D_profgame_004005F8.players[index]->object28;
        gUvTerraExports->slot08(playerObjects[index]->handle, -1);
        gUvEnvExports->slot18(playerObjects[index]->handle, 8);
    }
    gScrnExports->slot04(gNumPlayers, playerObjects);
    D_profgame_0040064C = uvLoadModule(0x63617261);
    gGameGuiExports->slot1C(profgameCreateProfileCarControls);
    gGameGuiExports->slot10(0);
    gUvFmtxExports->slot1C(&transform);
    for (index = 0; index < 8; index++) {
        D_profgame_004005F8.objectSlots[index] = gUvDobjExports->slot3C();
        transform.xw = D_profgame_004005A0[index];
        transform.yw = D_profgame_004005C0[index];
        transform.zw = 0.0f;
        D_profgame_004005F8.animationSlots[index] = D_profgame_0040064C->slot04(
            0, D_profgame_004005F8.objectSlots[index], (u32)D_profgame_004005F8.players[0]->object28);
        D_profgame_0040064C->slot14(D_profgame_004005F8.animationSlots[index],
            2, 1, 5, 1, 6, 1, 7, 1, 9, 0, 15, &transform, 0);
    }
}
#line 3 "src/modules/profgame.c"

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

