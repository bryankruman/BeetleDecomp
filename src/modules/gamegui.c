// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvcback_rom.h"
#include "uvchannel_rom.h"
extern UvChannel_Exports *gUvChanExports;
extern UvCback_Exports *gUvCbckExports;
#include "module.h"
#include "global_exports.h"
/*__SEEDEXTERNS__*/
u16 uvGetFileInstanceCount(s32 tag, s32 fileId);
s32 uvGetFilesCount(s32 tag);
void *uvGetLoadedFile(s32 formFileTag, s32 fileId);
void gameGuiAccumulateLoadedTextureField1A();
extern void func_gamegui_00400194(s32);
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
void func_gamegui_00400194();
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
void func_gamegui_004021DC();
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
/* Register the original ten game-GUI callback addresses and the shared
 * debug-byte address after updating the allocation pointer. Preserve slot
 * order and the empty callback's separate identity.
 * RE_UNKNOWN: the table is an explicit 32-bit initializer storage view, not
 * a callable API declaration. Slot0x14's consumed operations are established
 * by original assembly; its historical source declaration and slot 0x08's
 * complete callback contract remain unresolved.
 * The caller owns writable export storage of the original size. */
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
/* When debug mode is enabled, retain the existing setup call, allocate/get
 * a child-group pointer via GUI70/74, copy its text via78 and append via08.
 * Invoke the three GUI sections and scene section in their original order.
 * RE_UNKNOWN: those surrounding callbacks retain raw-word source prototypes;
 * their original targets must settle full argument contracts. The root label
 * extent is unresolved; inspect original data boundaries before assuming30bytes. */
void gameGuiCreateDebugRoot(void) {
    void *rootNode;

    if (D_debugEnable != 0) {
        D_gamegui_00402C74 = 1;
        gameGuiInitializeSharedWidgetWhenEnabled();
        rootNode = ((LocalGuiExp_4000B0 *)gUvGuiExports)->getChildGroup((s16) ((LocalGuiExp_4000B0 *)gUvGuiExports)->allocateChildGroup());
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->copyChildGroupText(rootNode, (u8 *)&D_gamegui_00402450);
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->appendChild(&D_gamegui_00402C78, rootNode);
        func_gamegui_00400194((s32)rootNode);
        func_gamegui_00400370((s32)rootNode);
        func_gamegui_004014F8((s32)rootNode);
        gSceneExports->unk20((s32)rootNode);
    }
}
#line 95 "src/modules/gamegui.c"
#line 94 "src/modules/gamegui.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00400194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00400370.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004014F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401748.s")

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

void gameGuiSetSharedWord(s32 value) { /* Store the supplied word in D_gamegui_00402D04. RE_UNKNOWN: shared word role and use as callback/context data require original readers and initializer consumers. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004021DC.s")

#line 255 "src/modules/gamegui.c"
/* Read callback-list property six from the supplied channel identifier.
 * Register the original callback with no insert-before routine and priority 0x21. */
void gameGuiRegisterChannelCallback(s32 context) {
    CallbackList *channel;
    gUvChanExports->uvChannelGetProperties(context, 6, &channel, 0);
    gUvCbckExports->uvAddCallback(channel, func_gamegui_004021DC, 0, 0x21);
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

