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
void func_gamegui_004023BC();
extern void func_gamegui_00400194(s32);
extern void func_gamegui_00400370(s32);
extern void func_gamegui_004014F8(s32);
extern void func_gamegui_00401E7C(void);
extern s32 D_gamegui_00402450;
extern s32 D_gamegui_00402C74;
typedef struct {
    /* 0x00 */ char pad0[0x8];
    /* 0x08 */ void (*unk8)(void *, s32);
    /* 0x0C */ char padC[0x64];
    /* 0x70 */ s32 (*unk70)(void);
    /* 0x74 */ s32 (*unk74)(s32);
    /* 0x78 */ void (*unk78)(s32, s32 *);
} LocalGuiExp_4000B0;
typedef struct {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ void (*unk20)(s32);
} SceneExp_4000B0;
extern SceneExp_4000B0 *gSceneExports;
typedef struct { char pad0[0xC]; void (*unkC)(void *); char pad10[0x18]; void (*unk28)(void *, s32, s32); } GameguiGuiExports;
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
void func_gamegui_00401D94();
void gameGuiStopAndDisableEmitters();
void gameGuiLatchAudioShutdown();
void gameGuiRequestStateFiveWithoutMultiplayerAi();
void gameGuiRequestStateSixAtLeastTwoPlayers();
void func_gamegui_00401E7C();
void gameGuiResetSelectionAndDebugFont();
void func_gamegui_00402030();
void gameGuiRequestStateNineWithChoiceFlag();
void func_gamegui_00402074();
void func_gamegui_00402088();
void gameGuiRequestStateThree();
void gameGuiRequestStateFour();
void gameGuiRequestInitialIntroTrack();
void gameGuiRequestStateSevenTrack33();
void func_gamegui_00402130();
void func_gamegui_00402144();
void func_gamegui_00402158();
void func_gamegui_0040216C();
void func_gamegui_00402180();
void gameGuiToggleReplayAndRestartCurrentState();
void func_gamegui_004021DC();
void gameGuiRegisterChannelSixCallback(s32 context);
u8 func_gamegui_004023B0();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/__entrypoint_func_gamegui_400000.s")

void func_gamegui_004000A8(void) {
}

/* Initializes the game GUI: creates a GUI object, loads a resource, registers it, and sets up sub-systems. */
#line 79 "src/modules/gamegui.c"
/* When debug mode is enabled, mark the GUI active, create and bind
 * its configured root node, then attach the original three GUI sections
 * and scene section in order. Leave all state untouched when debug is disabled. */
void gameGuiCreateDebugRoot(void) {
    s32 rootNode;

    if (D_debugEnable != 0) {
        D_gamegui_00402C74 = 1;
        func_gamegui_00401E7C();
        rootNode = ((LocalGuiExp_4000B0 *)gUvGuiExports)->unk74((s16) ((LocalGuiExp_4000B0 *)gUvGuiExports)->unk70());
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->unk78(rootNode, &D_gamegui_00402450);
        ((LocalGuiExp_4000B0 *)gUvGuiExports)->unk8(&D_gamegui_00402C78, rootNode);
        func_gamegui_00400194(rootNode);
        func_gamegui_00400370(rootNode);
        func_gamegui_004014F8(rootNode);
        gSceneExports->unk20(rootNode);
    }
}
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
/* Restore the stored music ID and music state zero unless the
 * linked node mode short equals one. The node owns the linked record. */
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

void func_gamegui_00401D94(s32 arg0) {
    gUvCmidiExports->uvaSeqStop();
}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401E7C.s")

#line 169 "src/modules/gamegui.c"
/* Pass selection -1 and mode three to the original GUI helper,
 * then select debug font three. Preserve the original GUI state object. */
void gameGuiResetSelectionAndDebugFont(void) {
    gUvGuiExports->unk28(&D_gamegui_00402C78, -1, 3);
    gUvDebugExports->uvDbgSetFontId(3);
}
#line 173 "src/modules/gamegui.c"

void func_gamegui_00402030(s32 arg0) {
    D_gamegui_00402D04 = arg0;
}

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

void func_gamegui_00402074(s32 arg0) {
    gGameSettings[0].newGameState = 8;
}

void func_gamegui_00402088(s32 arg0) {
    gGameSettings[0].newGameState = 0xB;
}

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

void func_gamegui_00402130(s32 arg0) {
    gGameSettings[0].newGameState = 0xA;
}

void func_gamegui_00402144(s32 arg0) {
    gGameSettings[0].newGameState = 0xC;
}

void func_gamegui_00402158(s32 arg0) {
    gGameSettings[0].newGameState = 0xD;
}

void func_gamegui_0040216C(s32 arg0) {
    gGameSettings[0].newGameState = 0xE;
}

void func_gamegui_00402180(s32 arg0) {
    gGameSettings[0].newGameState = 0xF;
}

void func_gamegui_00402194(void) {
}

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

void func_gamegui_004021D4(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004021DC.s")

#line 255 "src/modules/gamegui.c"
/* Obtain channel 6 and install the original callback at priority 0x21.
 * Preserve the callback context and the original unchecked channel contract. */
void gameGuiRegisterChannelSixCallback(s32 context) {
    CallbackList *channel;
    gUvChanExports->uvChannelGetProperties(context, 6, &channel, 0);
    gUvCbckExports->uvAddCallback(channel, func_gamegui_004021DC, 0, 0x21);
}
#line 256 "src/modules/gamegui.c"

u8 func_gamegui_004023B0(void) {
    return D_gamegui_00402C68;
}

void func_gamegui_004023BC(s32 arg0)
{
  u16 new_var2;
  s32 var_s0;
  s32 temp_s3;
  s32 var_s1;
  void *temp_v0;
  var_s1 = 0;
  temp_s3 = uvGetFilesCount(0x55565458);
  var_s0 = 0;
  if (temp_s3 > 0)
  {
    do
    {
      if (uvGetFileInstanceCount(0x55565458, var_s0) > 0)
      {
        temp_v0 = uvGetLoadedFile(0x55565458, var_s0);
        new_var2 = *((u16 *) (((u8 *) temp_v0) + 0x1A));
        var_s1 += new_var2;
      }
      var_s0 += 1;
    }
    while (var_s0 < temp_s3);
  }
}

