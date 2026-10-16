// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* Original GUI84 appends to the first free one of 12 child slots; GUI94/98
 * allocate/access the 0x170-stride pool, and GUI9C copies exactly 30 input bytes.
 * RE_UNKNOWN: historical formal widths, full record extents and lifetime rules.
 * Resolve original pool declarations, producers and all dispatch readers before
 * expanding this observed export prefix into a complete interface. */
typedef struct GameGuiRacePanelGuiExports {
    u8 unused00[0x84];
    void (*appendTextList)(void *, void *);
    u8 unused88[0xC];
    s16 (*allocateTextList)(void);
    void *(*getTextList)(s16);
    void (*copyTextListText)(void *, u8 *);
} GameGuiRacePanelGuiExports;
/* Original MISC104 accepts a bound word address and an optional widget output;
 * MISC10C forwards its third word to GUI property3. RE_UNKNOWN: property3's
 * complete dispatch ABI and ownership of the bound storage and returned rows. */
typedef struct GameGuiRacePanelMiscExports {
    u8 unused00[0x104];
    void *(*createBoundScalarRow)(void *, u8 *, s16, f32, f32, s32 *, void **);
    u8 unused108[4];
    void *(*createTextRowWithPropertyWord)(void *, u8 *, s32);
} GameGuiRacePanelMiscExports;
extern GameGuiRacePanelMiscExports *gMiscExports;
extern s32 gNumPlayers, gNumAiCars, gDebugAiRecord, gDebugSteerAssist;
extern u8 D_gamegui_0040246C[], D_gamegui_00402474[], D_gamegui_00402480[];
extern u8 D_gamegui_00402484[], D_gamegui_00402490[], D_gamegui_004024A0[];
extern u8 D_gamegui_004024AC[];
#line 3 "src/modules/gamegui.c"
extern u32 D_gamegui_00402BD0[], D_gamegui_00402BE0[];
#include "uvcback_rom.h"
#include "uvchannel_rom.h"
extern UvChannel_Exports *gUvChanExports;
extern UvCback_Exports *gUvCbckExports;
#include "module.h"
#include "global_exports.h"
/* Selective gamegui00370 consumed slots; not complete export allocations.
 * Raw optional-module slot words are passed as value-source addresses.
 * RE_UNKNOWN: historical full types, storage extents and provider lifetimes. */
typedef struct GameGuiDebugOptionGuiExports {
    u8 unused00[0x5C];
    void (*setPropertyWord)(void *, s16, s32);
    u8 unused60[0x24];
    void (*appendTextList)(void *, void *);
    u8 unused88[0xC];
    s16 (*allocateTextList)(void);
    void *(*getTextList)(s16);
    void (*copyTextListText)(void *, u8 *);
    u8 unusedA0[0x30];
    void (*setCallbackWord)(void *, s32);
    u8 unusedD4[0x10];
    void (*setTextTableWord)(void *, s32);
} GameGuiDebugOptionGuiExports;
typedef struct { u8 unused00[0x24]; u32 valueSourceAddress24, valueSourceAddress28; } GameGuiDebugPlayerSlots;
typedef struct { u8 unused00[0xB0]; u32 valueSourceAddressB0, valueSourceAddressB4; } GameGuiDebugTerrainSlots;
typedef struct { u8 unused00[0x14]; u32 valueSourceAddress14; } GameGuiDebugSkidSlots;
typedef struct { u8 unused00[0x24]; u32 valueSourceAddress24; } GameGuiDebugRainSlots;
typedef struct { u8 unused00[0x18]; u32 valueSourceAddress18; } GameGuiDebugFlagSlots;
typedef struct { u8 unused00[0x1C]; u32 valueSourceAddress1C; } GameGuiDebugScrnSlots;
extern UvEnv_Exports *gUvEnvExports;
extern GameGuiDebugTerrainSlots *gUvTerraExports;
extern s32 gNumOpenCars, gNumOpenTracks, gNumOpenMtracks, gNumOpenTourns;
extern s32 gDebugProfilingState, gDebugOptsMinDt, gDebugOptsCarSelect;
extern s32 gOptionsMusicVol, gOptionsSfxVol;
extern s32 D_gamegui_00402D10, D_gamegui_00402D14;
extern void *D_gamegui_00402D18, *D_gamegui_00402D1C, *D_gamegui_00402D20;
extern u8 D_gamegui_00402580[];
extern u8 D_gamegui_00402584[];
extern u8 D_gamegui_00402590[];
extern u8 D_gamegui_0040259C[];
extern u8 D_gamegui_004025AC[];
extern u8 D_gamegui_004025B8[];
extern u8 D_gamegui_004025C4[];
extern u8 D_gamegui_004025D0[];
extern u8 D_gamegui_00402694[];
extern u8 D_gamegui_004026AC[];
extern u8 D_gamegui_004026B8[];
extern u8 D_gamegui_004026C8[];
extern u8 D_gamegui_004026D4[];
extern u8 D_gamegui_004026E0[];
extern u8 D_gamegui_004026F0[];
extern u8 D_gamegui_00402710[];
extern u8 D_gamegui_0040272C[];
extern u8 D_gamegui_00402738[];
extern u8 D_gamegui_00402740[];
extern u8 D_gamegui_0040274C[];
extern u8 D_gamegui_00402754[];
extern u8 D_gamegui_00402760[];
extern u8 D_gamegui_0040276C[];
extern u8 D_gamegui_00402774[];
extern u8 D_gamegui_00402778[];
extern u8 D_gamegui_004027A0[];
extern u8 D_gamegui_004027AC[];
extern u8 D_gamegui_004027D0[];
extern u8 D_gamegui_00402898[];
extern u8 D_gamegui_0040289C[];
extern u8 D_gamegui_004028A4[];
extern u8 D_gamegui_004028B0[];
extern u8 D_gamegui_004028B8[];
extern u8 D_gamegui_004028C4[];
extern u8 D_gamegui_004028CC[];
extern u8 D_gamegui_004028D8[];
extern u8 D_gamegui_004028E0[];
extern u8 D_gamegui_004028E8[];
extern u8 D_gamegui_004028F4[];
extern u8 D_gamegui_00402900[];
extern u8 D_gamegui_0040290C[];
extern u8 D_gamegui_00402918[];
extern u8 D_gamegui_00402924[];
extern u8 D_gamegui_00402930[];
extern u8 D_gamegui_0040293C[];
extern u8 D_gamegui_00402948[];
extern u8 D_gamegui_00402950[];
extern u8 D_gamegui_00402958[];
extern u8 D_gamegui_00402960[];
extern u8 D_gamegui_0040296C[];
extern u8 D_gamegui_00402974[];
extern u8 D_gamegui_00402984[];
extern u8 D_gamegui_0040298C[];
extern u8 D_gamegui_00402994[];
extern u8 D_gamegui_0040299C[];
extern u8 D_gamegui_004029AC[];
extern u8 D_gamegui_004029B8[];
extern u8 D_gamegui_004029C0[];
extern u8 D_gamegui_004029CC[];
extern u8 D_gamegui_004029D8[];
extern u8 D_gamegui_004029E4[];
extern u8 D_gamegui_004029F0[];
extern u8 D_gamegui_004029F8[];
extern u8 D_gamegui_00402A00[];
extern u8 D_gamegui_00402A08[];
extern u8 D_gamegui_00402A10[];
extern s32 D_gamegui_00402AB0;
extern s32 D_gamegui_00402AB4;
extern f32 D_gamegui_00402ABC;
extern u8 D_gamegui_00402AC0[];
extern u8 D_gamegui_00402AD0[];
extern u8 D_gamegui_00402ADC[];
extern u8 D_gamegui_00402AEC[];
extern u8 D_gamegui_00402AFC[];
extern u8 D_gamegui_00402B10[];
extern u8 D_gamegui_00402B20[];
extern u8 D_gamegui_00402B60[];
extern u8 D_gamegui_00402B6C[];
extern u8 D_gamegui_00402B78[];
extern u8 D_gamegui_00402B84[];
extern u8 D_gamegui_00402B90[];
extern u8 D_gamegui_00402B98[];

/* Original address aliases and readonly bound; declarations allocate no storage. */
extern s32 gDebugAbortMode;
extern s32 gDebugAiDbgState;
extern s32 gDebugDefaultMaterial;
extern s32 gDebugDisableGoodFramera;
extern s32 gDebugDispAntialias;
extern s32 gDebugDispMasks;
extern s32 gDebugDispMipmap;
extern s32 gDebugDispTxtDetail;
extern s32 gDebugDispTxtFilter;
extern s32 gDebugDispTxtPersp;
extern s32 gDebugDispViDither;
extern s32 gDebugDispViDivot;
extern s32 gDebugDispViGamDith;
extern s32 gDebugDispViGamma;
extern s32 gDebugFrateDisp;
extern s32 gDebugHudState;
extern s32 gDebugInfLapsFlag;
extern f32 gDebugMxSpeed;
extern s32 gDebugNumMaxTxts;
extern s32 gDebugOptsCarShadow;
extern s32 gDebugOptsDrawingOff;
extern s32 gDebugOptsFrameRate;
extern s32 gDebugOptsGlare;
extern s32 gDebugOptsLosCheckOff;
extern s32 gDebugRecordIntro;
extern s32 gDebugOptsVelCam;
extern f32 gDebugPlyrLead;
extern s32 gDebugSuspensionFlag;
extern s32 gDebugTileSort;
extern const f32 D_gamegui_00402A9C;
#line 10 "src/modules/gamegui.c"
/*__SEEDEXTERNS__*/
u16 uvGetFileInstanceCount(s32 tag, s32 fileId);
s32 uvGetFilesCount(s32 tag);
void *uvGetLoadedFile(s32 formFileTag, s32 fileId);
void gameGuiAccumulateLoadedTextureField1A();
extern void gameGuiAddRaceAndBattleControls(s32);
extern void func_gamegui_00400370(s32);
extern void func_gamegui_004014F8(s32);
extern void gameGuiInitializeSharedWidgetWhenEnabled(void);
extern s32 D_gamegui_00402450;
extern s32 D_gamegui_00402C74;
extern void *D_gamegui_00402D0C;
/* Original GUI04 initializes container fields after six helper calls; GUI1C
 * sets child-container bounds; GUI24 consumes a signed low16 selector and
 * stores its payload in an original word/byte field.
 * RE_UNKNOWN: historical source prototypes and complete property meanings.
 * Inspect original property tables and all field readers before expanding
 * this minimal target-consumption view into a complete export table. */
typedef struct GameGuiInitializerExports {
    u8 unused00[4];
    void (*initializeContainer)(void *);
    u8 unused08[0x14];
    void (*setChildContainerBounds)(void *, s16, s16, s16, s16);
    u8 unused20[4];
    void (*setContainerProperty)(void *, s16, s32);
} GameGuiInitializerExports;
/* Original GUI08/70/74/78 are append, signed-index allocation/access
 * and fixed-width text copy. Getter consumes low16; allocator returns a signed
 * index. RE_UNKNOWN: historical caller declaration widths, unused slots and
 * full root lifecycle. This view records verified target consumption. */
typedef struct {
    u8 unused00[8];
    void (*appendChild)(void *, void *);
    u8 unused0C[0x64];
    s16 (*allocateChildGroup)(void);
    void *(*getChildGroup)(s16);
    void (*copyChildGroupText)(void *, u8 *);
} LocalGuiExp_4000B0;
typedef struct {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ void (*unk20)(s32);
} SceneExp_4000B0;
extern SceneExp_4000B0 *gSceneExports;
/* GUI28 consumes the signed low16 display-data and palette IDs.
 * RE_UNKNOWN: historical caller declaration widths. GUI0C and unused slots
 * retain the existing caller view. Exact caller proof gates this correction. */
typedef struct { u8 unused00[0xC]; void (*unkC)(void *); u8 unused10[0x18]; void (*loadDisplayDataAndPalette)(void *, s16, s16); } GameguiGuiExports;
extern GameguiGuiExports *gUvGuiExports;
extern s32 D_debugEnable;
extern u8 D_gamegui_00402C68;
extern u8 D_gamegui_00402C78;
extern s32 D_gamegui_00402D04;
extern u16 D_gamegui_00402D16;
extern s32 D_gamegui_00402D28;
void gameGuiAddRaceAndBattleControls(s32 parentWord);
void func_gamegui_00400370();
void func_gamegui_004014F8();
void func_gamegui_00401748();
void gameGuiRenderMenuOrFontList();
void gameGuiSetDebugByteWhenEnabled();
void func_gamegui_00401AF8();
void gameGuiRestoreMusicUnlessModeOne();
void gameGuiStopMidiSequence();
void gameGuiStopAndDisableEmitters();
void gameGuiLatchAudioShutdown();
void gameGuiRequestStateFiveWithoutMultiplayerAi();
void gameGuiRequestStateSixAtLeastTwoPlayers();
void gameGuiInitializeSharedWidgetWhenEnabled(void);
void gameGuiLoadPaletteThreeAndSelectDebugFont();
void gameGuiSetSharedWord();
void gameGuiRequestStateNineWithChoiceFlag();
void gameGuiRequestStateEight();
void gameGuiRequestStateEleven();
void gameGuiRequestStateThree();
void gameGuiRequestStateFour();
void gameGuiRequestInitialIntroTrack();
void gameGuiRequestStateSevenTrack33();
void gameGuiRequestStateTen();
void gameGuiRequestStateTwelve();
void gameGuiRequestStateThirteen();
void gameGuiRequestStateFourteen();
void gameGuiRequestStateFifteen();
void gameGuiToggleReplayAndRestartCurrentState();
void gameGuiApplyDitherAndVideoSettings(s32 unusedCallbackValue);
void gameGuiRegisterChannelCallback(s32 context);
u8 gameGuiGetDebugByte();
/* Initializer storage view: these are original 32-bit addresses, not
 * invented callable declarations. Original slot 0x14 initializes the shared
 * widget conditionally and consumes no incoming machine argument.
 * RE_UNKNOWN: historical source declarations and callback 0x08's contract. */
typedef struct GameGuiExportAddresses_s {
    /* 0x00 */ u32 emptyCallbackAddress;
    /* 0x04 */ u32 createDebugRootAddress;
    /* 0x08 */ u32 unknownCallback08Address;
    /* 0x0C */ u32 renderMenuOrFontListAddress;
    /* 0x10 */ u32 setDebugByteAddress;
    /* 0x14 */ u32 initializeSharedWidgetAddress;
    /* 0x18 */ u32 loadPaletteAndSelectFontAddress;
    /* 0x1C */ u32 storeSharedWordAddress;
    /* 0x20 */ u32 registerChannelCallbackAddress;
    /* 0x24 */ u32 getDebugByteAddress;
    /* 0x28 */ u32 debugByteAddress;
} GameGuiExportAddresses;

void func_gamegui_004000A8(void);
void gameGuiCreateDebugRoot(void);

#line 93 "src/modules/gamegui.c"
/*
 * Update the allocation pointer and publish ten original callback addresses
 * at offsets 0x00 through 0x24, then the shared debug-byte address at 0x28.
 * The table stores 32-bit addresses; publication does not invoke the callbacks
 * or initialize the shared debug byte and widget state.
 * RE_UNKNOWN: The full writable export extent/lifetime and callback 0x08 ABI
 * remain loader/consumer obligations. Preserve the separate empty callback and
 * all original slot bindings without assigning new callable signatures.
 */
#line 101 "src/modules/gamegui.c"
void __entrypoint_func_gameGuiInitializeModuleExports(GameGuiExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32) func_gamegui_004000A8;
    exports->createDebugRootAddress = (u32) gameGuiCreateDebugRoot;
    exports->unknownCallback08Address = (u32) func_gamegui_00401748;
    exports->renderMenuOrFontListAddress = (u32) gameGuiRenderMenuOrFontList;
    exports->setDebugByteAddress = (u32) gameGuiSetDebugByteWhenEnabled;
    exports->initializeSharedWidgetAddress = (u32) gameGuiInitializeSharedWidgetWhenEnabled;
    exports->loadPaletteAndSelectFontAddress = (u32) gameGuiLoadPaletteThreeAndSelectDebugFont;
    exports->storeSharedWordAddress = (u32) gameGuiSetSharedWord;
    exports->registerChannelCallbackAddress = (u32) gameGuiRegisterChannelCallback;
    exports->getDebugByteAddress = (u32) gameGuiGetDebugByte;
    exports->debugByteAddress = (u32) &D_gamegui_00402C68;
}
#line 94 "src/modules/gamegui.c"

#line 75 "src/modules/gamegui.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_gamegui_004000A8(void) {
}
#line 77 "src/modules/gamegui.c"

/* Initializes the game GUI: creates a GUI object, loads a resource, registers it, and sets up sub-systems. */
#line 79 "src/modules/gamegui.c"

#line 80 "src/modules/gamegui.c"
/*
 * Do nothing when debugging is disabled. Otherwise mark the shared debug state,
 * initialize the shared widget, narrow the allocated child-group handle to s16,
 * resolve it, copy its text and append it to the shared list. Build the three
 * control groups before passing the same root to the scene callback.
 * RE_UNKNOWN: Allocation failure, root ownership and the opaque control/scene
 * callback contracts remain with their providers; no validation is added.
 */
#line 86 "src/modules/gamegui.c"
void gameGuiCreateDebugRoot(void) {
    void *rootNode;

    if (D_debugEnable != 0) {
        D_gamegui_00402C74 = 1;
        gameGuiInitializeSharedWidgetWhenEnabled();
        rootNode = ((LocalGuiExp_4000B0 *)gUvGuiExports)->getChildGroup((s16) ((LocalGuiExp_4000B0 *)gUvGuiExports)->allocateChildGroup());
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->copyChildGroupText(rootNode, (u8 *)&D_gamegui_00402450);
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->appendChild(&D_gamegui_00402C78, rootNode);
        gameGuiAddRaceAndBattleControls((s32)rootNode);
        func_gamegui_00400370((s32)rootNode);
        func_gamegui_004014F8((s32)rootNode);
        gSceneExports->unk20((s32)rootNode);
    }
}
#line 95 "src/modules/gamegui.c"
#line 94 "src/modules/gamegui.c"

/* Append the original race text-list panel, bind player/AI counts and the AI-record/
 * steering-assist words, then append the play and battle rows with their original
 * code-address property words. Preserve export reloads and the reused widget-output
 * address; the returned widget itself is not read here. GUI9C reads exactly 30 bytes
 * starting at the original race-label address, including bytes after its NUL.
 * RE_ORIGINAL_QUIRK: the allocator continues with index50 after scanning50 entries,
 * and this caller does not check the returned index; exhaustion reachability is unknown.
 * RE_UNKNOWN: historical parent/label/record extents and declaration widths, pool
 * occupancy guarantees, bound-storage/row lifetimes and property3's callback dispatch
 * contract. Trace original allocation/teardown, label boundaries and GUI property3
 * readers before changing validation, ownership or the raw-word action declarations. */
#line 95 "src/modules/gamegui.c"
void gameGuiAddRaceAndBattleControls(s32 parentWord) {
    void *racePanel;
    void *widget;

    racePanel = ((GameGuiRacePanelGuiExports *)gUvGuiExports)->getTextList(
        (s16)((GameGuiRacePanelGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiRacePanelGuiExports *)gUvGuiExports)->copyTextListText(racePanel, D_gamegui_0040246C);
    ((GameGuiRacePanelGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, racePanel);
    gMiscExports->createBoundScalarRow(racePanel, D_gamegui_00402474, 0x12,
        1.0f, 4.0f, &gNumPlayers, &widget);
    gMiscExports->createBoundScalarRow(racePanel, D_gamegui_00402480, 0x12,
        0.0f, 7.0f, &gNumAiCars, &widget);
    gMiscExports->createBoundScalarRow(racePanel, D_gamegui_00402484, 0x12,
        0.0f, 1.0f, &gDebugAiRecord, &widget);
    gMiscExports->createBoundScalarRow(racePanel, D_gamegui_00402490, 0x12,
        0.0f, 1.0f, &gDebugSteerAssist, &widget);
    gMiscExports->createTextRowWithPropertyWord(racePanel, D_gamegui_004024A0,
        (s32)gameGuiRequestStateFiveWithoutMultiplayerAi);
    gMiscExports->createTextRowWithPropertyWord(racePanel, D_gamegui_004024AC,
        (s32)gameGuiRequestStateSixAtLeastTwoPlayers);
}
#line 96 "src/modules/gamegui.c"

/* Build the dbg, opts, disp and dsbl text-list panels in their original order,
 * bind shared setting addresses to scalar widgets, and attach action/address
 * properties. Optional module flags are added only when their exports exist.
 * The accepted MISC provider selects integer sources when kind & 0x2; other
 * kinds read the same source address as f32. Preserve all bounds and call order.
 * RE_ORIGINAL_QUIRK: row/widget allocation is unchecked; accepted providers
 * retain fixed-width label reads, including bytes beyond a label's first NUL.
 * RE_UNKNOWN: remaining kind bits, complete label/table extents, allocation
 * capacity, callback dispatch contracts, optional flag meanings, and bound
 * storage/module lifetime remain provider and caller obligations. Export-word
 * casts describe addresses passed here, not inferred allocations or ownership.
 * The scoped linker alias preserves the original caller/export name. */
#line 355 "src/modules/gamegui.c"
void gameGuiBuildDebugOptionsPanels(s32 parentWord) {
    void *menuOption;
    void *slider;
    char stackLayoutPad[0x4];
    GameGuiDebugPlayerSlots *player;

    player = uvGetLoadedModule('plyr');
    menuOption = ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->getTextList(((GameGuiDebugOptionGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->copyTextListText(menuOption, D_gamegui_00402580);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, menuOption);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402584, 0x12, 1.0f, 12.0f, &gNumOpenCars,
                                     &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402590, 0x12, 1.0f, 7.0f, &gNumOpenTracks,
                                     &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040259C, 0x12, 1.0f, 9.0f, &gNumOpenMtracks,
                                     &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004025AC, 0x12, 1.0f, 4.0f, &gNumOpenTourns,
                                     &slider);
    D_gamegui_00402D20 = gMiscExports->createBoundScalarRow(
        menuOption, D_gamegui_004025B8, 0x12, 0.0f,
        (f32) (gUvEmitterExports->uvEmitterGetBankInstrumentCount() - 1), &D_gamegui_00402D10, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setCallbackWord(slider, (s32) &func_gamegui_00401AF8);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setPropertyWord(
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004025C4, 0x12, 0.0f,
                                         (f32) (gUvCmidiExports->uvaGetSeqCount() - 1),
                                         &D_gamegui_00402D14, &slider),
        3, (s32)gameGuiRestoreMusicUnlessModeOne);
    gMiscExports->createTextRowWithPropertyWord(menuOption, D_gamegui_004025D0, (s32)gameGuiAccumulateLoadedTextureField1A);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402694, 2, 0, 15.0f,
                                     &gGameSettings[0].debugState, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B20);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026AC, 0x12, 0.0f, 2.0f,
                                     &gDebugFrateDisp, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B60);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026B8, 0x12, 0.0f, 1.0f,
                                     &gDebugDefaultMaterial, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026C8, 0x12, 0.0f, 1.0f,
                                     &gDebugAbortMode, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026D4, 0x11, 0.0f, D_gamegui_00402A9C,
                                     (s32 *)&gDebugPlyrLead, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026E0, 0x11, 0.1f, 300.0f,
                                     (s32 *)&gDebugMxSpeed, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004026F0, 0x12, 0.0f, 3.0f,
                                     &gDebugHudState, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B10);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402710, 0x12, 0.0f, 2.0f,
                                     &gDebugAiDbgState, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B6C);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040272C, 0x12, 0.0f, 2.0f,
                                     &gDebugProfilingState, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B78);
    menuOption = ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->getTextList(((GameGuiDebugOptionGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->copyTextListText(menuOption, D_gamegui_00402738);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, menuOption);
    if (player != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402740, 0x11, 0.0f, 1.0f,
                                         (s32 *)player->valueSourceAddress28, &slider);
    }
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040274C, 0x11, 0.01f, 1.0f,
                                     &gDebugOptsMinDt, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402754, 0x12, 0.0f, 1.0f,
                                     &gDebugInfLapsFlag, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402760, 0x12, 1.0f, 500.0f,
                                     &gDebugNumMaxTxts, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040276C, 2, 0, 8.0f, &gOptionsMusicVol,
                                     &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402774, 2, 0, 8.0f, &gOptionsSfxVol,
                                     &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402778, 0x12, 0.0f, 1.0f,
                                     &gDebugSuspensionFlag, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004027A0, 0x12, 0.0f, 2.0f,
                                     &gDebugTileSort, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B84);
    gMiscExports->createTextRowWithPropertyWord(menuOption, D_gamegui_004027AC, (s32)gameGuiToggleReplayAndRestartCurrentState);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004027D0, 0x12, 0.0f, 1.0f,
                                     &gDebugRecordIntro, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B90);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402898, 0x12, 0.0f, 11.0f,
                                     &gDebugOptsCarSelect, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402B98);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040289C, 0x12, 0.0f, 1.0f,
                                     &gDebugOptsCarShadow, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028A4, 0x12, 0.0f, 1.0f,
                                     &gDebugOptsLosCheckOff, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028B0, 0x12, 0.0f, 1.0f,
                                     &gDebugOptsVelCam, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028B8, 0x12, 0.0f, 1.0f,
                                     &gDebugOptsDrawingOff, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028C4, 0x12, 0.0f, 1.0f,
                                     &gDebugOptsGlare, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028CC, 0x12, 0.0f, 4.0f,
                                     &gDebugOptsFrameRate, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402AFC);
    menuOption = ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->getTextList(((GameGuiDebugOptionGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->copyTextListText(menuOption, D_gamegui_004028D8);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, menuOption);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028E0, 0x12, 0, 1,
                                     &gDebugDispMasks, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028E8, 0x12, 0.0f, 1.0f,
                                     &gDebugDispViGamma, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004028F4, 0x12, 0.0f, 1.0f,
                                     &gDebugDispViGamDith, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402900, 0x12, 0.0f, 1.0f,
                                     &gDebugDispViDivot, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040290C, 0x12, 0.0f, 1.0f,
                                     &gDebugDispViDither, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402918, 0x12, 0.0f, 1.0f,
                                     &gDebugDispAntialias, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402924, 0x12, 0.0f, 3.0f,
                                     &gDebugDispTxtFilter, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402AC0);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402930, 0x12, 0.0f, 2.0f,
                                     &gDebugDispTxtPersp, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402AD0);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040293C, 0x12, 0.0f, 3.0f,
                                     &gDebugDispTxtDetail, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402ADC);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402948, 0x12, 0.0f, 3.0f,
                                     &gDebugDispMipmap, &slider);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->setTextTableWord(slider, (s32) &D_gamegui_00402AEC);
    D_gamegui_00402D18 = gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402950, 2, 0.0f, 2.0f,
                                                          &D_gamegui_00402AB0, &slider);
    D_gamegui_00402D1C = gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402958, 2, 0.0f, 2.0f,
                                                          &D_gamegui_00402AB4, &slider);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402960, 0x11, -1.0f, 1.0f,
                                     (s32 *)&D_gamegui_00402ABC, &slider);
    menuOption = ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->getTextList(((GameGuiDebugOptionGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->copyTextListText(menuOption, D_gamegui_0040296C);
    ((GameGuiDebugOptionGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, menuOption);
    gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402974, 0x12, 0.0f, 1.0f,
                                     &gDebugDisableGoodFramera, &slider);
    gMiscExports->createTextRowWithPropertyWord(menuOption, D_gamegui_00402984, (s32)gameGuiStopMidiSequence);
    gMiscExports->createTextRowWithPropertyWord(menuOption, D_gamegui_0040298C, (s32)gameGuiStopAndDisableEmitters);
    gMiscExports->createTextRowWithPropertyWord(menuOption, D_gamegui_00402994, (s32)gameGuiLatchAudioShutdown);
    if (gUvPfxExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_0040299C, 0x12, 0.0f, 1.0f,
                                         gUvPfxExports->D_uvpfx_rom_00404FAC, &slider);
    }
    if (gUvDobjExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029AC, 0x12, 0.0f, 1.0f,
                                         gUvDobjExports->D_uvdobj_rom_004039B0, &slider);
    }
    if (gUvEnvExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029B8, 0x12, 0.0f, 1.0f,
                                         gUvEnvExports->unk28, &slider);
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029C0, 0x12, 0.0f, 1.0f,
                                         gUvEnvExports->unk2C, &slider);
    }
    if (gUvTerraExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029CC, 0x12, 0.0f, 1.0f,
                                         (s32 *)gUvTerraExports->valueSourceAddressB0, &slider);
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029D8, 0x12, 0.0f, 1.0f,
                                         (s32 *)gUvTerraExports->valueSourceAddressB4, &slider);
    }
    if (gUvGfxStateExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029E4, 0x12, 0.0f, 1.0f,
                                         gUvGfxStateExports->unk78, &slider);
    }
    if (gSkidExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029F0, 0x12, 0.0f, 1.0f,
                                         (s32 *)((GameGuiDebugSkidSlots *)gSkidExports)->valueSourceAddress14, &slider);
    }
    if (gRainExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_004029F8, 0x12, 0.0f, 1.0f,
                                         (s32 *)((GameGuiDebugRainSlots *)gRainExports)->valueSourceAddress24, &slider);
    }
    if (gScrnExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402A00, 0x12, 0.0f, 1.0f,
                                         (s32 *)((GameGuiDebugScrnSlots *)gScrnExports)->valueSourceAddress1C, &slider);
    }
    if (player != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402A08, 0x12, 0.0f, 1.0f,
                                         (s32 *)player->valueSourceAddress24, &slider);
    }
    if (gFlagExports != NULL) {
        gMiscExports->createBoundScalarRow(menuOption, D_gamegui_00402A10, 0x12, 0.0f, 1.0f,
                                         (s32 *)((GameGuiDebugFlagSlots *)gFlagExports)->valueSourceAddress18, &slider);
    }
}
#line 98 "src/modules/gamegui.c"
/*
 * Append a text-list panel and its thirteen state-action rows in original order.
 * Reuse the first two rows' code-address property word and retain their returned
 * addresses in the original shared words. Reload provider tables after calls.
 * Original GUI exports 0x84, 0x94, 0x98 and 0x9C establish append, signed-index
 * allocation/access, and an exact 30-byte copy that continues after NUL.
 * MISC export 0x10C forwards the unchanged third word to GUI property 3.
 * RE_ORIGINAL_QUIRK: the allocator uses index 50 after scanning 50 active
 * entries; this caller does not check exhaustion. Reachability is unresolved.
 * RE_UNKNOWN: historical parent/shared-word types, complete label and pool
 * extents, occupancy/alias/lifetime guarantees, and property 3's action-dispatch
 * ABI. Resolve original allocations, label boundaries, teardown and all property
 * readers before changing bounds, ownership or code-address declarations.
 *
 *
 *
 *
 *
 */
#line 99 "src/modules/gamegui.c"
extern u8 D_gamegui_00402A18[];
extern u8 D_gamegui_00402A20[];
extern u8 D_gamegui_00402A28[];
extern u8 D_gamegui_00402A30[];
extern u8 D_gamegui_00402A34[];
extern u8 D_gamegui_00402A3C[];
extern u8 D_gamegui_00402A44[];
extern u8 D_gamegui_00402A4C[];
extern u8 D_gamegui_00402A54[];
extern u8 D_gamegui_00402A60[];
extern u8 D_gamegui_00402A68[];
extern u8 D_gamegui_00402A78[];
extern u8 D_gamegui_00402A84[];
extern u8 D_gamegui_00402A90[];
extern s32 D_gamegui_00402D24;
/* Add 13 labelled state-action rows and retain the two choice-row handles.
 * The accepted MISC helper stores each callback word as text-row property 3.
 * RE_UNKNOWN: row capacity, allocation failure and callback lifetime are unproved.
 * Preserve direct callback expressions and the original row/call order. */
#line 99 "src/modules/gamegui.c"
void gameGuiAddStateActionRows(s32 parentWord) {
    void *actionPanel;

    actionPanel = ((GameGuiRacePanelGuiExports *)gUvGuiExports)->getTextList(
        (s16)((GameGuiRacePanelGuiExports *)gUvGuiExports)->allocateTextList());
    ((GameGuiRacePanelGuiExports *)gUvGuiExports)->copyTextListText(actionPanel, D_gamegui_00402A18);
    ((GameGuiRacePanelGuiExports *)gUvGuiExports)->appendTextList((void *)parentWord, actionPanel);
    D_gamegui_00402D24 =
        (s32)gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A20, (s32)gameGuiRequestStateNineWithChoiceFlag);
    D_gamegui_00402D28 =
        (s32)gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A28, (s32)gameGuiRequestStateNineWithChoiceFlag);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A30, (s32)gameGuiRequestStateEight);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A34, (s32)gameGuiRequestInitialIntroTrack);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A3C, (s32)gameGuiRequestStateThree);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A44, (s32)gameGuiRequestStateFour);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A4C, (s32)gameGuiRequestStateSevenTrack33);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A54, (s32)gameGuiRequestStateTen);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A60, (s32)gameGuiRequestStateEleven);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A68, (s32)gameGuiRequestStateTwelve);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A78, (s32)gameGuiRequestStateThirteen);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A84, (s32)gameGuiRequestStateFourteen);
    gMiscExports->createTextRowWithPropertyWord(actionPanel, D_gamegui_00402A90, (s32)gameGuiRequestStateFifteen);
}
#line 100 "src/modules/gamegui.c"
/*
 * Scan four controllers for both masks 0x20 and 0x10; on the first match,
 * load the GUI, display-list editor and font resources when needed, then set
 * GUI property 16 and the shared controller word if the GUI load succeeded.
 * Preserve the scan break on that first match even when the load failed.
 * Independently process press masks 0x800 then 0x400 using the current mode:
 * update the enabled byte, initialize the shared widget, invoke the stored
 * raw code address or create the debug root, and clear the shared GUI short.
 * The second action sees the first action's changes. When enabled, store
 * byte 1 at the root container's offset 0x8A and run its input/child traversal.
 * Preserve provider and callback reloads, unexpected-mode behavior and the
 * original unsigned comparison of the memory-query result against 150000.
 * RE_ORIGINAL_QUIRK: GUI availability gates the initial property call, but
 * later enabled paths add no load-result check. Original failure-domain and
 * callback-validity guarantees remain unresolved; no reachable fault is proven.
 * RE_UNKNOWN: historical state/container extents and formals, input-controller
 * validity, module/resource occupancy and lifetime, callback registrations,
 * formals/return and inherited-register expectations, complete mode/property
 * meanings and aliases. Resolve original allocations, producers, registered
 * targets, all mode/property readers and failure paths before changing bounds,
 * validation, ownership, callback ABI or initialization.
 */
#line 101 "src/modules/gamegui.c"
/* Consumed fields of the existing shared state; no allocation is declared.
 * RE_UNKNOWN: full object extent, controller validity and callback lifetime. */
typedef struct GameGuiDebugStatePrefix {
    u8 enabled;
    u8 opaque01[0xB];
    s32 mode;
    u8 opaque10[0x84];
    u8 inputController;
    u8 opaque95[7];
    u32 sharedCallbackAddress;
} GameGuiDebugStatePrefix;
/* Caller views of the accepted GUI input/byte/shared-short slots. */
typedef struct GameGuiControllerGuiExports {
    u8 opaque00[0x20];
    s32 (*updateContainerInput)(void *);
    u8 opaque24[8];
    void (*setElementByte8A)(void *, u8);
    u8 opaque30[4];
    void (*setSharedShort)(s16);
} GameGuiControllerGuiExports;
extern s32 D_80025D7C;
/* Select the first controller holding both masks, then process the two
 * debug-menu actions and update the active shared GUI container.
 * RE_ORIGINAL_QUIRK: both action tests run in order; the second observes changes
 * made by the first. The low-memory paths return before later input handling.
 * RE_UNKNOWN: modes outside 0..2, module/allocation failure and the registered
 * callback's full ABI. Its code word is called without supplied arguments. */
#line 101 "src/modules/gamegui.c"
void gameGuiHandleDebugControllerInput(void) {
    s32 controllerIndex;

    if (D_debugEnable == 0) {
        return;
    }

    for (controllerIndex = 0; controllerIndex < 4; controllerIndex++) {
        if ((gUvContExports->uvControllerHasButtons(controllerIndex, 0x20) != 0)
            && (gUvContExports->uvControllerHasButtons(controllerIndex, 0x10) != 0)) {
            if (gUvGuiExports == NULL) {
                if ((u32) _uvMemGetBlocksSize() < 150000) {
                    return;
                }
                gUvGuiExports = uvLoadModule('ugui');
                D_gamegui_00402D0C = uvLoadModule('dled');
                uvLoadFile('UVFT', 3);
            }
            if (gUvGuiExports != NULL) {
                ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(&D_gamegui_00402C78, 0x10, controllerIndex);
                D_80025D7C = controllerIndex;
            }
            break;
        }
    }
    if ((gUvContExports->uvControllerButtonPress((u8) ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->inputController, 0x800) != 0)
        && (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->sharedCallbackAddress != 0)) {
        switch (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode) {
            case 0:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
                break;
            case 1:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
                break;
            case 2:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 0;
                break;
        }
        if (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled != 0) {
            if ((gUvGuiExports == NULL) && ((u32) _uvMemGetBlocksSize() < 0x249F0)) {
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 0;
                return;
            }
            gameGuiInitializeSharedWidgetWhenEnabled();
            ((void (*)())((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->sharedCallbackAddress)();
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
            ((GameGuiControllerGuiExports *)gUvGuiExports)->setSharedShort(0);
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode = 2;
        } else {
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode = 0;
        }
    }
    if (gUvContExports->uvControllerButtonPress((u8) ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->inputController, 0x400) != 0) {
        switch (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode) {
            case 0:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
                break;
            case 1:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 0;
                break;
            case 2:
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
                break;
        }
        if (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled != 0) {
            if ((gUvGuiExports == NULL) && ((u32) _uvMemGetBlocksSize() < 0x249F0)) {
                ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 0;
                return;
            }
            gameGuiInitializeSharedWidgetWhenEnabled();
            gameGuiCreateDebugRoot();
            ((GameGuiControllerGuiExports *)gUvGuiExports)->setSharedShort(0);
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode = 1;
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled = 1;
        } else {
            ((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->mode = 0;
        }
    }
    if (((GameGuiDebugStatePrefix *)&D_gamegui_00402C68)->enabled != 0) {
            ((GameGuiControllerGuiExports *)gUvGuiExports)->setElementByte8A(&D_gamegui_00402C78, 1);
            ((GameGuiControllerGuiExports *)gUvGuiExports)->updateContainerInput(&D_gamegui_00402C78);
    }
}
#line 102 "src/modules/gamegui.c"

#line 103 "src/modules/gamegui.c"
/* Render the shared GUI menu when enabled; otherwise generate the
 * font display list. Preserve the early return after menu rendering. */
void gameGuiRenderMenuOrFontList(void) {
    if (D_gamegui_00402C68 != 0) {
        gUvGuiExports->unkC(&D_gamegui_00402C78);
        return;
    }
    gUvFontExports->uvFontGenDList();
}
#line 110 "src/modules/gamegui.c"

#line 111 "src/modules/gamegui.c"
/* Narrow/store the game-GUI debug byte only when debugging is enabled. */
void gameGuiSetDebugByteWhenEnabled(s32 value) {
    if (D_debugEnable != 0) {
        D_gamegui_00402C68 = (u8)value;
    }
}
#line 116 "src/modules/gamegui.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401AF8.s")

typedef struct
{
  char pad0[0x1E];
  s16 unk1E;
} Inner_00401D34;
typedef struct
{
  char pad0[0x28];
  Inner_00401D34 *unk28;
} Outer_00401D34;

#line 130 "src/modules/gamegui.c"
/* Restore the stored music ID and music state zero unless the linked
 * record short at 0x1E equals one.
 * RE_UNKNOWN: the short's broader role and ownership/lifetime of node->unk28.
 * This wrapper only reads the pointer; trace original record creation,
 * replacement and release paths before assigning an ownership contract. */
void gameGuiRestoreMusicUnlessModeOne(Outer_00401D34 *node)
{
  Inner_00401D34 *linkedRecord;
  linkedRecord = node->unk28;
  if (linkedRecord->unk1E != 1)
  {
    gSndExports->sndSetMusic(D_gamegui_00402D16);
    gSndExports->sndSetMusicState(0);
  }
}
#line 140 "src/modules/gamegui.c"

#line 141 "src/modules/gamegui.c"
/* Stop the current MIDI sequence through the original audio export.
 * Preserve the unused callback value and calling convention. */
void gameGuiStopMidiSequence(s32 callbackValue) {
    gUvCmidiExports->uvaSeqStop();
}
#line 144 "src/modules/gamegui.c"

#line 145 "src/modules/gamegui.c"
/* Stop all emitters and disable emission through the original callback ABI. */
void gameGuiStopAndDisableEmitters(s32 callbackValue) {
    gUvEmitterExports->uvEmitterStopAllAndDisable();
}
#line 148 "src/modules/gamegui.c"

#line 149 "src/modules/gamegui.c"
/* Latch audio-manager shutdown through the original callback ABI. */
void gameGuiLatchAudioShutdown(s32 callbackValue) {
    gUvAudiomgrExports->uvAudioMgrLatchShutdown();
}
#line 152 "src/modules/gamegui.c"

#line 153 "src/modules/gamegui.c"
/* Request game state five and clear the AI-car count only when at
 * least two players are selected. Preserve the callback parameter ABI. */
void gameGuiRequestStateFiveWithoutMultiplayerAi(s32 callbackValue) {
    if (gGameSettings[0].numPlayers >= 2) {
        gGameSettings[0].numAiCars = 0;
    }
    gGameSettings[0].newGameState = 5;
}
#line 159 "src/modules/gamegui.c"

#line 160 "src/modules/gamegui.c"
/* Raise player count to two only when smaller and request game state six.
 * Preserve the unused callback parameter and original state transition. */
void gameGuiRequestStateSixAtLeastTwoPlayers(s32 callbackValue) {
    if (gGameSettings[0].numPlayers < 2) {
        gGameSettings[0].numPlayers = 2;
    }
    gGameSettings[0].newGameState = 6;
}
#line 166 "src/modules/gamegui.c"

#line 167 "src/modules/gamegui.c"
/* When settings word 0x18C is nonzero, initialize the shared GUI widget.
 * Snapshot settings word 0x8C before all callbacks. If GUI is absent, load
 * original modules ugui/dled and font asset 3 in order; retain the existing
 * GUI table when already loaded. Initialize widget D_gamegui_00402C78, set its rectangle
 * and five original property pairs, select palette/font 3, then clear the
 * shared debug byte and word+0xC. Reload exports for every original callback.
 * RE_UNKNOWN: settings words 0x18C/0x8C meanings, property payload semantics,
 * complete shared-state/widget allocation and resource ownership/lifetime.
 * Trace original writers, GUI property tables and loader/teardown paths before
 * replacing the neutral field views or inferring additional validation. */
void gameGuiInitializeSharedWidgetWhenEnabled(void) {
    s32 propertyWord;
    void *widget;
    u8 *sharedState;

    propertyWord = gGameSettings[0].unk8C;
    if (gGameSettings[0].unk18C != 0) {
        if (gUvGuiExports == NULL) {
            gUvGuiExports = uvLoadModule(0x75677569);
            D_gamegui_00402D0C = uvLoadModule(0x646C6564);
            uvLoadFile(0x55564654, 3);
        }
        widget = &D_gamegui_00402C78;
        ((GameGuiInitializerExports *)gUvGuiExports)->initializeContainer(widget);
        ((GameGuiInitializerExports *)gUvGuiExports)->setChildContainerBounds(widget, 0x17, 0x128, 0x11, 0xDE);
        ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(widget, 1, 0x8000);
        ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(widget, 2, 0x4000);
        ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(widget, 0x11, 0);
        ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(widget, 0x12, 1);
        ((GameGuiInitializerExports *)gUvGuiExports)->setContainerProperty(widget, 0x10, propertyWord);
        gameGuiLoadPaletteThreeAndSelectDebugFont();
        sharedState = &D_gamegui_00402C68;
        *sharedState = 0;
        *(s32 *)(sharedState + 0xC) = 0;
    }
}
#line 168 "src/modules/gamegui.c"

#line 169 "src/modules/gamegui.c"

#line 170 "src/modules/gamegui.c"
/* Call original GUI0x28 with display-data ID-1 and palette ID3, then select
 * debug font3. Its target stores those IDs, skips the display-data load for-1,
 * loads palette3 and marks the GUI record ready; no selection reset is shown.
 * RE_UNKNOWN: palette3's asset meaning and the complete GUI lifecycle. Resolve
 * through the original palette loader/data and callers before stronger naming. */
void gameGuiLoadPaletteThreeAndSelectDebugFont(void) {
    gUvGuiExports->loadDisplayDataAndPalette(&D_gamegui_00402C78, -1, 3);
    gUvDebugExports->uvDbgSetFontId(3);
}
#line 174 "src/modules/gamegui.c"
#line 173 "src/modules/gamegui.c"

#line 174 "src/modules/gamegui.c"

void gameGuiSetSharedWord(s32 value) { /* Store the raw word later invoked as a code address by GAMEGUI export 0x08. RE_UNKNOWN: historical callback formals/return, registration validity and lifetime; inspect all original registrations and targets before declaring a typed callback API. */
    D_gamegui_00402D04 = value;
}
#line 177 "src/modules/gamegui.c"

#line 178 "src/modules/gamegui.c"
/* Set the shared choice word to one only when the callback value
 * matches the stored choice, otherwise clear it. Then request game
 * state nine through the existing callback parameter ABI. */
void gameGuiRequestStateNineWithChoiceFlag(s32 choice) {
    if (choice == D_gamegui_00402D28) {
        *(s32 *)&gGameSettings[0].padE0[0] = 1;
    } else {
        *(s32 *)&gGameSettings[0].padE0[0] = 0;
    }
    gGameSettings[0].newGameState = 9;
}
#line 186 "src/modules/gamegui.c"

#line 187 "src/modules/gamegui.c"

void gameGuiRequestStateEight(s32 callbackValue) { /* Request new game state 8; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 8;
}
#line 190 "src/modules/gamegui.c"

#line 191 "src/modules/gamegui.c"

void gameGuiRequestStateEleven(s32 callbackValue) { /* Request new game state 11; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xB;
}
#line 194 "src/modules/gamegui.c"

#line 195 "src/modules/gamegui.c"
/* Request game state three and set shared mode word 0xC to two. */
void gameGuiRequestStateThree(s32 callbackValue) {
    gGameSettings[0].newGameState = 3;
    gGameSettings[0].unkC = 2;
}
#line 199 "src/modules/gamegui.c"

#line 200 "src/modules/gamegui.c"
/* Request game state four and set shared mode word 0xC to two. */
void gameGuiRequestStateFour(s32 callbackValue) {
    gGameSettings[0].newGameState = 4;
    gGameSettings[0].unkC = 2;
}
#line 204 "src/modules/gamegui.c"

#line 205 "src/modules/gamegui.c"
/* Request game state two on track 27, reset intro progress, set
 * the shared mode word and enable intro playback. Preserve the unused
 * callback value and original field-write order. */
void gameGuiRequestInitialIntroTrack(s32 callbackValue) {
    gGameSettings[0].newGameState = 2;
    gGameSettings[0].currentTrack = 0x1B;
    gGameSettings[0].finishedIntroCount = 0;
    gGameSettings[0].unkC = 1;
    gGameSettings[0].playIntroFlag = 1;
}
#line 212 "src/modules/gamegui.c"

#line 213 "src/modules/gamegui.c"
/* Request game state seven and track 33 through the original callback ABI. */
void gameGuiRequestStateSevenTrack33(s32 callbackValue) {
    gGameSettings[0].newGameState = 7;
    gGameSettings[0].currentTrack = 0x21;
}
#line 217 "src/modules/gamegui.c"

#line 218 "src/modules/gamegui.c"

void gameGuiRequestStateTen(s32 callbackValue) { /* Request new game state 10; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xA;
}
#line 221 "src/modules/gamegui.c"

#line 222 "src/modules/gamegui.c"

void gameGuiRequestStateTwelve(s32 callbackValue) { /* Request new game state 12; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xC;
}
#line 225 "src/modules/gamegui.c"

#line 226 "src/modules/gamegui.c"

void gameGuiRequestStateThirteen(s32 callbackValue) { /* Request new game state 13; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xD;
}
#line 229 "src/modules/gamegui.c"

#line 230 "src/modules/gamegui.c"

void gameGuiRequestStateFourteen(s32 callbackValue) { /* Request new game state 14; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xE;
}
#line 233 "src/modules/gamegui.c"

#line 234 "src/modules/gamegui.c"

void gameGuiRequestStateFifteen(s32 callbackValue) { /* Request new game state 15; retain the unused s32 callback argument. */
    gGameSettings[0].newGameState = 0xF;
}
#line 237 "src/modules/gamegui.c"

#line 238 "src/modules/gamegui.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_gamegui_00402194(void) {
}
#line 240 "src/modules/gamegui.c"

#line 241 "src/modules/gamegui.c"
/* Clear intro/replay state when set; otherwise set it to one and
 * request the current game state again. Preserve the callback ABI. */
void gameGuiToggleReplayAndRestartCurrentState(s32 callbackValue) {
    if (gGameSettings[0].introReplayState != 0) {
        gGameSettings[0].introReplayState = 0;
        return;
    }
    gGameSettings[0].introReplayState = 1;
    gGameSettings[0].newGameState = gGameSettings[0].currentGameState;
}
#line 249 "src/modules/gamegui.c"

#line 250 "src/modules/gamegui.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_gamegui_004021D4(void) {
}
#line 252 "src/modules/gamegui.c"

#line 253 "src/modules/gamegui.c"
/* Emit pipe sync plus color/alpha-dither commands, reset the two shared graphics words,
 * then apply the original video-interface feature choices. RE_UNKNOWN: dither selector
 * domains, display-list capacity/lifetime and the rendering meaning of shared word50's
 * 0x400000 bit need original settings producers, graphics consumers and frame callers.
 * The original callback homes but does not read its incoming word; its historical
 * source declaration remains unresolved. Preserve settings reloads across callbacks. */
void gameGuiApplyDitherAndVideoSettings(s32 unusedCallbackValue) {
    Gfx **displayListHead;
    u32 videoFeatures;

    displayListHead = gUvGfxMgrExports->uvGetDisplayListHead();
    gDPPipeSync((*displayListHead)++);
    gDPSetColorDither((*displayListHead)++, D_gamegui_00402BD0[gGameSettings[0].unk4C]);
    gDPSetAlphaDither((*displayListHead)++, D_gamegui_00402BE0[gGameSettings[0].unk48]);
    gUvGfxStateExports->uvGfxSetSharedStateWord4C(-1);
    if (gGameSettings[0].dbgDispAntialias == 0) {
        gUvGfxStateExports->uvGfxSetSharedStateWord50(0x400000);
    }

    videoFeatures = gGameSettings[0].dbgDispViGamma ? OS_VI_GAMMA_ON : OS_VI_GAMMA_OFF;
    if (gGameSettings[0].dbgDispViGamDith != 0) {
        videoFeatures |= OS_VI_GAMMA_DITHER_ON;
    } else {
        videoFeatures |= OS_VI_GAMMA_DITHER_OFF;
    }
    if (gGameSettings[0].dbgDispViDither != 0) {
        videoFeatures |= OS_VI_DITHER_FILTER_ON;
    } else {
        videoFeatures |= OS_VI_DITHER_FILTER_OFF;
    }
    if (gGameSettings[0].dbgDispViDivot != 0) {
        videoFeatures |= OS_VI_DIVOT_ON;
    } else {
        videoFeatures |= OS_VI_DIVOT_OFF;
    }
    osViSetSpecialFeatures(videoFeatures);
}
#line 254 "src/modules/gamegui.c"

#line 255 "src/modules/gamegui.c"
/*
 * Request property 6 from the supplied channel, using the local callback-list
 * output and trailing zero, then register gameGuiApplyDitherAndVideoSettings
 * with a zero insertion argument and priority 0x21.
 * RE_ORIGINAL_QUIRK: The local output is not initialized here and no lookup
 * status or NULL check precedes registration.
 * RE_UNKNOWN: Property 6 must fill a live callback list for this channel;
 * list capacity, registration failure, callback lifetime and teardown ordering
 * require the channel/callback providers and all registration callers.
 */
#line 257 "src/modules/gamegui.c"
void gameGuiRegisterChannelCallback(s32 channelId) {
    CallbackList *callbackList;
    gUvChanExports->uvChannelGetProperties(channelId, 6, &callbackList, 0);
    gUvCbckExports->uvAddCallback(callbackList, gameGuiApplyDitherAndVideoSettings, 0, 0x21);
}
#line 256 "src/modules/gamegui.c"

#line 257 "src/modules/gamegui.c"
/* Return the shared GAMEGUI debug byte without changing it or applying
 * the settings gate used by its setter. The original module initializer
 * publishes this getter at slot 0x24 and the byte address at slot 0x28. */
u8 gameGuiGetDebugByte(void) {
    return D_gamegui_00402C68;
}
#line 260 "src/modules/gamegui.c"

#line 261 "src/modules/gamegui.c"

/* Visit loaded UVTX files and accumulate their unsigned field at offset
 * 0x1A. The original homes the incoming word but does not use it in the
 * scan. The local aggregate is neither returned nor stored here; preserve
 * the file-manager calls and original loop. RE_UNKNOWN: field 0x1A meaning,
 * valid asset extent and the discarded total's intended role. Trace original
 * UVTX producers and callers before treating this as a size/resource
 * statistic or adding an observable result. */
void gameGuiAccumulateLoadedTextureField1A(s32 unusedWord) {
    u16 field1AValue;
    s32 fileId;
    s32 fileCount;
    s32 totalField1A;
    void *loadedFile;

    totalField1A = 0;
    fileCount = uvGetFilesCount(0x55565458);
    fileId = 0;
    if (fileCount > 0) {
        do {
            if (uvGetFileInstanceCount(0x55565458, fileId) > 0) {
                loadedFile = uvGetLoadedFile(0x55565458, fileId);
                field1AValue = *((u16 *) (((u8 *) loadedFile) + 0x1A));
                totalField1A += field1AValue;
            }
            fileId += 1;
        } while (fileId < fileCount);
    }
}
#line 286 "src/modules/gamegui.c"

