// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* Original provider-backed export prefixes; skipped slots remain opaque.
 * RE_UNKNOWN: full export layouts and historical caller declaration widths
 * require complete original provider/caller proof beyond these used slots. */
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
} DemoGuiMenuExports;
typedef struct {
    u8 opaque00[0x14];
    void (*initializeSharedWidget)(void);
    u8 opaque18[0x10];
    u8 *sharedDebugByte;
} DemoGameGuiMenuExports;
typedef struct {
    u8 opaque00[0x104];
    void *(*createBoundScalarRow)(void *, u8 *, s16, f32, f32, s32 *, void **);
} DemoMiscMenuExports;
typedef struct {
    u8 opaque00[0x34];
    void (*createThreeRangeControls)(s32);
} DemoReplayMenuExports;
typedef struct {
    u8 opaque00[0x14];
    void (*emptyCallback14)(s32);
} DemoAiMenuExports;
extern DemoGuiMenuExports *gUvGuiExports;
extern DemoGameGuiMenuExports *gGameGuiExports;
extern DemoMiscMenuExports *gMiscExports;
extern DemoReplayMenuExports *gReplayExports;
extern DemoAiMenuExports *gAiExports;
extern u8 D_demo_00401DCC[], D_demo_00401DD4[];
extern u8 D_demo_00401DDC[], D_demo_00401DE8[];
extern f32 D_demo_00402238, D_demo_00402234;

#line 3 "src/modules/demo.c"
/*__SEEDEXTERNS__*/
typedef struct {
    /* 0x00 */ char pad[0xC];
    /* 0x0C */ void (*unkC)(f32, f32, f32, f32);
} UvGeomExp_00400910;
extern UvGeomExp_00400910 *gUvGeomExports;
typedef struct {
    /* 0x00 */ char pad00[0xC];
    /* 0x0C */ void (*unkC)(s32);
    /* 0x10 */ void (*unk10)(s32);
    /* 0x14 */ void (*unk14)(s32);
    /* 0x18 */ char pad18[0x38];
    /* 0x50 */ void (*unk50)(void);
    /* 0x54 */ void (*unk54)(void);
    /* 0x58 */ char pad58[0x4];
    /* 0x5C */ void (*unk5C)(s32, s32, s32, s32, f32, f32, f32, f32);
} UvGfxStateExp_00400910;
extern UvGfxStateExp_00400910 *gUvGfxStateExports;
extern s32 D_demo_00402270;
extern s32 gNumAiCars;
extern void *gSceneExports;
extern void *D_demo_00402274;
void demoRestoreRaceSelection();
void func_demo_00400290();
void func_demo_0040041C();
void func_demo_00400538();
void demoCreateReplayControlGroup();
void func_demo_00400BC4();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/__entrypoint_func_demo_400000.s")

#line 33 "src/modules/demo.c"
/* Restore the saved AI-car count, obtain track zero from the scene export
 * and clear the tournament selection. Preserve the original export lookup. */
void demoRestoreRaceSelection(void) {
    gNumAiCars = D_demo_00402270;
    gGameSettings->currentTrack = ((s32 (*)(s32))((s32 *)gSceneExports)[1])(0);
    gGameSettings->currentTournament = 0;
}
#line 38 "src/modules/demo.c"
/*
 * RE_UNKNOWN: shared threshold/step units, replay masks 0x1000/0x8000 and
 * AI-tail/camera/collection storage/alias/lifetime guarantees. Trace original
 * setup, record/step writers and downstream copied-word readers. Original
 * callbacks copy tail word 0x14 to camera 0x1E8, write 13 at 0x1EC and pass tail
 * word 4 through CAM tag19 to 0x214; tag0 terminates. Preserve ordered f32
 * comparison, independent AI checks and every callback/global-reload order.
 * RE_ORIGINAL_QUIRK: the original returned AI tail is dereferenced unchecked;
 * empty-tail reachability requires caller/setup proof, not a new player bug.
 * Readable recovery remains parked: 396 original versus 404 candidate bytes,
 * 87 differing words and relocation mismatches, including generated global
 * address lifetimes. Require complete instruction/module/ROM proof before
 * replacing ASM; no storage/layout or physical meanings inferred to match.
 */
#line 39 "src/modules/demo.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_0040041C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400538.s")

/* Set up the graphics state and draw a full-screen demo overlay rectangle. */
#line 46 "src/modules/demo.c"
/* Push graphics state, select the original modes and texture, draw a black
 * rectangle with supplied alpha at X 22..297/Y 16..223, then pop state. */
void demoDrawBlackOverlay(f32 alpha) {
    gUvGfxStateExports->unk50();
    gUvGfxStateExports->unkC(0x04820FFF);
    gUvGfxStateExports->unk10(0x9B7C0000);
    gUvGeomExports->unkC(0.0f, 0.0f, 0.0f, alpha);
    gUvGfxStateExports->unk14(0xFFF);
    gUvGfxStateExports->unk5C(0x16, 0x129, 0x10, 0xDF, 0.0f, 2.0f, 0.0f, 2.0f);
    gUvGfxStateExports->unk54();
}
#line 55 "src/modules/demo.c"

#line 56 "src/modules/demo.c"

/* Create the original "demo" group and text list, add float-bound
 * "playtime" and "loddist" rows with flags 0x11 and bounds 0..500, then
 * append the replay provider's three range controls. Snapshot the shared
 * host address before initialization and retain the optional AI slot14 call.
 * That original AI callback only homes its incoming word; its intended ABI and
 * purpose remain RE_UNKNOWN pending original callers and lifecycle proof.
 * MISC104 selects float storage for these flags; the s32 pointer casts expose
 * the same four-byte value addresses through its shared integer/float API.
 * RE_ORIGINAL_QUIRK: pool/attachment exhaustion is unchecked here.
 * RE_UNKNOWN: bound-value units, callback mutation, host/value lifetime and
 * exhaustion reachability need original readers/writers, entry callers and
 * active-slot producers. GUI text copies read 30 bytes; the complete readable
 * label windows need original object/layout proof, not inferred capacities. */
void demoCreateReplayControlGroup(void) {
    void *host;
    void *group;
    void *textList;

    host = gGameGuiExports->sharedDebugByte + 0x10;
    gGameGuiExports->initializeSharedWidget();
    group = gUvGuiExports->getChildGroup(gUvGuiExports->allocateChildGroup());
    gUvGuiExports->copyChildGroupText(group, D_demo_00401DCC);
    gUvGuiExports->appendChildRow(host, group);
    textList = gUvGuiExports->getTextList(gUvGuiExports->allocateTextList());
    gUvGuiExports->copyTextListText(textList, D_demo_00401DD4);
    gUvGuiExports->attachTextList(group, textList);
    gMiscExports->createBoundScalarRow(textList, D_demo_00401DDC,
        0x11, 0.0f, 500.0f, (s32 *)&D_demo_00402238, NULL);
    gMiscExports->createBoundScalarRow(textList, D_demo_00401DE8,
        0x11, 0.0f, 500.0f, (s32 *)&D_demo_00402234, NULL);
    gReplayExports->createThreeRangeControls((s32)group);
    if (gAiExports != NULL) {
        gAiExports->emptyCallback14((s32)group);
    }
}
#line 57 "src/modules/demo.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/demo/func_demo_00400BC4.s")

