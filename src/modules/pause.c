// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[4]; u8 left, right; } PauseLanguageLatch;
extern s16 D_pause_00405DF4;
/*__SEEDEXTERNS__*/
typedef struct { char pad[0xDC]; void (*unkDC)(void); void (*unkE0)(s32); } SndExp_00403E6C;
typedef struct { char pad[0x2C]; s16 (*unk2C)(s32); } ContExp_00403E6C;
typedef struct { char pad[0x20]; s32 unk20; } PauseObj_00403E6C;
extern void *gUvContExports;
extern s16 D_8002CC8A;
extern void pauseApplyAudioVolumeOptions(void);
typedef struct UvFont_Exports_004003B8_s {
    /* 0x00 */ void (*uvModuleCleanup)(void);
    /* 0x04 */ void (*uvSetFont)(s32);
    /* 0x08 */ void (*uvFontScale)(f64, f64);
    /* 0x0C */ void (*uvFontColor)(u8, u8, u8, u8);
    /* 0x10 */ s32 (*uvFontStrlLen)(s32);
    /* 0x14 */ s32 (*uvFontStr16WidthFont)(s32);
    /* 0x18 */ s32 (*uvFontWidth)(const char *);
    /* 0x1C */ s32 (*uvFontHeight)(void);
    /* 0x20 */ s32 (*uvFontPrintStr16)(s32, s32, s32, s32);
    /* 0x24 */ void (*uvFontPrintStr)(s32, s32, char *);
    /* 0x28 */ void (*uvFontGenDList)(void);
} UvFont_Exports_004003B8;
extern UvFont_Exports_004003B8 *gUvFontExports;
extern u8 D_pause_00405D48;
extern s32 D_pause_00405D44;
extern u8 gOptionsMap;
extern u8 D_pause_004054B4;
extern s32 D_pause_00405D3C;
extern s32 D_pause_00405D40;
extern s32 D_pause_00405D34;
extern f32 D_pause_00405D38;
extern u8 D_pause_00405BEC;
extern void *D_pause_00405E4C;
extern u8 D_pause_00405E58;
extern u8 D_pause_00405E60;
extern u8 D_pause_00405E68;
extern u8 D_pause_00405E70;
extern s32 gGameStateFlag;
typedef struct MenuNode_s { s32 unk0; void *unk4; void *unk8; } MenuNode;
typedef struct { u8 unk00[0xC]; s32 (*get)(s32, MenuNode *); } PauseLanguageInputExports;
extern MenuNode *D_pause_00405E50;
extern MenuNode D_pause_00405618;
extern MenuNode D_pause_00405674;
extern MenuNode D_pause_00405AA0;
extern MenuNode D_pause_004055BC;
extern MenuNode D_pause_00405950;
typedef struct { char pad0[0x34]; void (*unk34)(void *, s32, s32, s32, void *); } UnkStruct_pause_E44;
extern UnkStruct_pause_E44 *D_pause_00405E44;
typedef struct { s32 unk0; s32 unk4; void (*unk8)(s32); } UnkStruct_pause_E48;
extern UnkStruct_pause_E48 *D_pause_00405E48;
typedef struct { char pad0[0xF4]; void (*unkF4)(s32); } UnkStruct_pause_SndExports;
extern UnkStruct_pause_SndExports *gSndExports;
typedef struct { char pad0[0xC]; void (*setSharedByte)(s32); } UnkStruct_pause_ReplayExports;
extern UnkStruct_pause_ReplayExports *gReplayExports;
extern s32 gOptionsSpeechVol;
extern s32 gOptionsSfxVol;
extern s32 gOptionsMusicVol;
extern u8 gOptionsStereoMono;
extern u8 gOptionsSpeed;
extern u8 gOptionsDisplay;
extern s16 D_8002CC88;
extern s32 D_8002CD98;
extern s16 D_80025D76;
extern u8 D_80025E6A;
void pauseReleaseMenuAndSoundHandles();
void pauseActivateIndexedMenu();
void func_pause_00400258();
void pauseToggleByteOnNewMenuAction(void *arg0);
void pauseNavigateToLinkedNode();
void func_pause_00400544();
void pauseApplyAudioVolumeOptions();
void func_pause_00400750();
void pausePrepareNavigationAudio();
void func_pause_0040098C();
void pauseStoreSharedZeroTestInReplayByte();
void pauseOpenRestartConfirmation();
void pauseOpenContinueConfirmation();
void pauseOpenQuitConfirmation();
void pauseRequestLoadedRaceOrBattleState();
void pauseRequestSelectionState(void);
void func_pause_00400DB8();
void pauseConfigurePlayerDependentMenuFields();
void func_pause_00400EEC();
void func_pause_0040197C();
void func_pause_004020F0();
void func_pause_004021BC();
void pauseAdjustSpeechVolume();
void pauseAdjustSfxVolume();
void pauseAdjustMusicVolume();
void pauseApplyStereoMonoOption();
void pauseToggleSpeedOption();
void func_pause_004023A4();
void pauseAdjustMapOptionSkippingTwoPlayerModeOne();
void pauseToggleDisplayOption();
void pauseCycleLanguage(void);
void pauseApplyOptionsAndNormalizeTwoPlayerMap();
void pauseCopyOptionsToSaveData();
void pauseOpenNewTrackConfirmation();
void func_pause_00402630();
void pauseOpenConfirmationWithCancelSoundSuppressed(void);
void func_pause_004026A8();
void pauseDrawTexturedFractionBar();
void func_pause_00402854();
void func_pause_00402904();
void func_pause_00402914();
void func_pause_00402D78();
void pausePlayPendingSoundF6();
void func_pause_00403FD0();
void func_pause_00404150();
void func_pause_00404160();
void pauseDispatchActionEightOnce();
void func_pause_0040423C();
void pausePrepareAudioWithoutNavigationSounds();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/__entrypoint_func_pause_400000.s")

#line 118 "src/modules/pause.c"
/* Unload the menu dependency and clear its export pointer when loaded,
 * then release all three shared pause sound handles in order. */
void pauseReleaseMenuAndSoundHandles(void) {
    if (D_pause_00405E44 != 0) {
        uvUnloadModule(0x6D656E75);
        D_pause_00405E44 = 0;
    }
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))(&D_pause_00405E60);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))(&D_pause_00405E68);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))(&D_pause_00405E70);
}
#line 127 "src/modules/pause.c"

#line 128 "src/modules/pause.c"
/* Select the indexed pause-menu descriptor and its node, update the
 * player-dependent options and sound state, then set all six original
 * menu-refresh bytes. The caller owns the descriptor index bounds. */
void pauseActivateIndexedMenu(s32 menuIndex) {
    void *menuDescriptor;

    menuDescriptor = *(void **)((u8 *)&D_pause_00405BEC + menuIndex * 4);
    D_pause_00405E4C = menuDescriptor;
    D_pause_00405E50 = *(s32 *)((u8 *)menuDescriptor + 0x10);
    pauseConfigurePlayerDependentMenuFields();
    pausePrepareNavigationAudio();
    *(u8 *)((u8 *)&D_pause_00405E58 + 0) = 1;
    *(u8 *)((u8 *)&D_pause_00405E58 + 1) = 1;
    *(u8 *)((u8 *)&D_pause_00405E58 + 2) = 1;
    *(u8 *)((u8 *)&D_pause_00405E58 + 3) = 1;
    *(u8 *)((u8 *)&D_pause_00405E58 + 4) = 1;
    *(u8 *)((u8 *)&D_pause_00405E58 + 5) = 1;
}
#line 143 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400258.s")

/* RE_UNKNOWN: menu slot0x14 action and node/owner storage lifetime require the original MENU provider and draw/lifecycle callers; observed calls are described below. */
#line 147 "src/modules/pause.c"
/* Call the current node draw callback, render that node in mode one,
 * and generate the font display list in the original order. */
void pauseDrawCurrentMenuAndFontList(void) {
    (*(void (*)(void))(*(s32 *)((u8 *)&D_pause_00405D48 + (*(s16 *)((u8 *)D_pause_00405E50 + 0x12) << 2))))();
    (*((void (**)(MenuNode *, s32))((u8 *)D_pause_00405E44 + 0x14)))(D_pause_00405E50, 1);
    gUvFontExports->uvFontGenDList();
}
#line 152 "src/modules/pause.c"

#line 153 "src/modules/pause.c"
/* Query the current menu action and toggle the caller byte only on
 * a transition from no action to a nonzero action. Values above zero
 * become zero; the shared latch records every queried action. */
void pauseToggleByteOnNewMenuAction(void *optionByte)
{
  int action;
  unsigned int previousValue;
  u8 *option;
  option = (u8 *) (((u8 *) optionByte) + 0x0);
  action = (*((s32 (**)(s32, s32)) (((u8 *) D_pause_00405E44) + 0xC)))(0, D_pause_00405E50);
  if (D_pause_00405DF4 == 0)
  {
    if (action != 0)
    {
      previousValue = *option;
      *option = previousValue < 1;
    }
  }
  D_pause_00405DF4 = action;
}
#line 170 "src/modules/pause.c"

/* Observed node/owner prefixes only. RE_UNKNOWN: complete layouts, callback roles and linked-node ownership require original MENU accessors, registrations and lifecycle callers. */
typedef struct PauseExtNode_0040048C_s {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ struct PauseExtNode_0040048C_s *unk4;
    /* 0x08 */ void *unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
} PauseExtNode_0040048C;
typedef struct PauseOwnerExt_0040048C_s {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ s16 (*unk18)(void *);
} PauseOwnerExt_0040048C;
typedef struct PauseOwnerTarget_0040048C_s {
    /* 0x00 */ char pad0[0x4];
    /* 0x04 */ s16 unk4;
} PauseOwnerTarget_0040048C;
typedef struct UvGfxMgrExp_0040048C_s {
    /* 0x00 */ char pad0[0x74];
    /* 0x74 */ void (*unk74)(void);
} UvGfxMgrExp_0040048C;
extern UvGfxMgrExp_0040048C *gUvGfxMgrExports;

#line 196 "src/modules/pause.c"
/* When the current node has a link, run its exit callback, wait for
 * graphics, select the linked node and run its entry callback. Then
 * refresh the linked node owner through the original callback ABI. */
void pauseNavigateToLinkedNode(void)
{
  PauseExtNode_0040048C *linkedNode;
  if (((PauseExtNode_0040048C *) D_pause_00405E50)->unk4 != 0)
  {
    (*((void (**)(void)) (((u8 *) (&D_pause_00405D48)) + (((PauseExtNode_0040048C *) D_pause_00405E50)->unk16 << 2))))();
    gUvGfxMgrExports->unk74();
    linkedNode = (D_pause_00405E50 = ((PauseExtNode_0040048C *) D_pause_00405E50)->unk4);
    (*((void (**)(void)) (((u8 *) (&D_pause_00405D48)) + ((linkedNode->unk14 << 1) << 1))))();
    ((PauseOwnerTarget_0040048C *) ((PauseExtNode_0040048C *) D_pause_00405E50)->unk8)->unk4 = ((PauseOwnerExt_0040048C *) D_pause_00405E44)->unk18(((PauseExtNode_0040048C *) D_pause_00405E50)->unk8);
  }
}
#line 208 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400544.s")

#line 211 "src/modules/pause.c"
/* Apply the saved speech, sound-effect and music volume settings
 * through their respective sound exports, in that order. */
void pauseApplyAudioVolumeOptions(void) {
    (*(void (**)(s32))((u8 *)gSndExports + 0x44))(gOptionsSpeechVol);
    (*(void (**)(s32))((u8 *)gSndExports + 0x40))(gOptionsSfxVol);
    (*(void (**)(s32))((u8 *)gSndExports + 0x3C))(gOptionsMusicVol);
}
#line 216 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400750.s")

#line 219 "src/modules/pause.c"
/* Apply audio volume options, clear sound suppression, then suppress
 * the directional-menu sound 0xDB. Reset the original navigation word
 * and scalar to zero and one half. */
void pausePrepareNavigationAudio(void) {
    pauseApplyAudioVolumeOptions();
    (*(void (**)(void))((u8 *)gSndExports + 0xDC))();
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xDB);
    D_pause_00405D34 = 0;
    D_pause_00405D38 = 0.5f;
}
#line 226 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040098C.s")

#line 229 "src/modules/pause.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_pause_00400C6C(void) {
}
#line 231 "src/modules/pause.c"

#line 232 "src/modules/pause.c"
#line 232 "src/modules/pause.c"

/* Store (signed shared halfword D_80025D76 == 0) through REPLAY export 0x0C, the low-byte setter for D_replay_00401B7C. RE_UNKNOWN: both shared values' gameplay meaning and lifetime require original writers/readers and callback caller/domain evidence. */
void pauseStoreSharedZeroTestInReplayByte(void) {
    gReplayExports->setSharedByte(D_80025D76 == 0);
}
#line 236 "src/modules/pause.c"
#line 235 "src/modules/pause.c"

#line 233 "src/modules/pause.c"
/* Ask for confirmation before restarting the current race.
 * Save the previous menu for Back and initially select the second choice (No). */
void pauseOpenRestartConfirmation(void) {
    MenuNode *previous = D_pause_00405E50;
    D_pause_00405E50 = &D_pause_00405618;
    D_pause_00405E50->unk4 = previous;
    *(s16 *)((u8 *)D_pause_00405E50->unk8 + 4) = 1;
}
#line 234 "src/modules/pause.c"

#line 235 "src/modules/pause.c"
/* Ask for confirmation before trying again with a continue.
 * Save the previous menu for Back and initially select the second choice (No). */
void pauseOpenContinueConfirmation(void) {
    MenuNode *previous = D_pause_00405E50;
    D_pause_00405E50 = &D_pause_00405AA0;
    D_pause_00405E50->unk4 = previous;
    *(s16 *)((u8 *)D_pause_00405E50->unk8 + 4) = 1;
}
#line 236 "src/modules/pause.c"

#line 237 "src/modules/pause.c"
/* Ask for confirmation before quitting the game.
 * Save the previous menu for Back and initially select the second choice (No). */
void pauseOpenQuitConfirmation(void) {
    MenuNode *previous = D_pause_00405E50;
    D_pause_00405E50 = &D_pause_004055BC;
    D_pause_00405E50->unk4 = previous;
    *(s16 *)((u8 *)D_pause_00405E50->unk8 + 4) = 1;
}
#line 238 "src/modules/pause.c"

#line 239 "src/modules/pause.c"
/* Request state five and set the two race-resume flags when the race
 * module is loaded. Otherwise request state six when battle is loaded;
 * with neither module present, leave the game state unchanged. */
void pauseRequestLoadedRaceOrBattleState(void) {
    if (uvGetLoadedModule(0x72616365) != 0) {
        gGameStateFlag = 5;
        D_pause_00405D3C = 1;
        D_pause_00405D40 = 1;
    } else if (uvGetLoadedModule(0x6261746C) != 0) {
        gGameStateFlag = 6;
    }
}
#line 248 "src/modules/pause.c"

#line 249 "src/modules/pause.c"
/* Request selection game state 0xE through the existing shared state alias. The SELECTION enum in game.h establishes the destination. */
void pauseRequestSelectionState(void) {
    gGameStateFlag = 0xE;
}
#line 252 "src/modules/pause.c"
/* RE_UNKNOWN: shared selector0x6EAE and counted signed-short banks0x6EC0/0x6ED0 have unresolved table meanings, count bounds, complete backing extent and update lifetime; trace original settings/count writers and callers. Original SCENE04 clamps the signed selector to0..5; this wrapper stores its table value then requests state5. Readable C preserves the operations but base-address reuse/register selection still differs; historical typed access/source declarations or new compiler evidence is needed. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400DB8.s")

#line 255 "src/modules/pause.c"
/* Configure the original nested menu shorts from the shared mode
 * at 0x6F74. Mode two selects values two and seven and enables the
 * remaining field only for a positive word at 0x6F64; other modes use one/one/six. */
void pauseConfigurePlayerDependentMenuFields(void) {
    if (*(s32 *)((u8 *)gGameSettings + 0x6F74) == 2) {
        *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x2A) = 2;
        *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x18) = 7;
        if (*(s32 *)((u8 *)gGameSettings + 0x6F64) <= 0) {
            *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x16) = 0;
            return;
        }
        *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x16) = 1;
        return;
    }
    *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x2A) = 1;
    *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x16) = 1;
    *(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)&D_pause_004054B4 + 0x8) + 0x8) + 0x18) = 6;
}
#line 270 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400EEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040197C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004020F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004021BC.s")

#line 279 "src/modules/pause.c"
/* Pass the speech volume setting to the original option helper
 * with eight steps and audio channel 0. */
void pauseAdjustSpeechVolume(void) {
    D_pause_00405E44->unk34(&gOptionsSpeechVol, 8, 1, 0, D_pause_00405E50);
}
#line 282 "src/modules/pause.c"

#line 283 "src/modules/pause.c"
/* Pass the sfx volume setting to the original option helper
 * with eight steps and audio channel 1. */
void pauseAdjustSfxVolume(void) {
    D_pause_00405E44->unk34(&gOptionsSfxVol, 8, 1, 1, D_pause_00405E50);
}
#line 286 "src/modules/pause.c"

#line 287 "src/modules/pause.c"
/* Pass the music volume setting to the original option helper
 * with eight steps and audio channel 2. */
void pauseAdjustMusicVolume(void) {
    D_pause_00405E44->unk34(&gOptionsMusicVol, 8, 1, 2, D_pause_00405E50);
}
#line 290 "src/modules/pause.c"

#line 291 "src/modules/pause.c"
/* Adjust the stereo/mono setting through the pause helper and immediately
 * apply the resulting value to the sound module. */
void pauseApplyStereoMonoOption(void) {
    pauseToggleByteOnNewMenuAction(&gOptionsStereoMono);
    gSndExports->unkF4(gOptionsStereoMono);
}
#line 295 "src/modules/pause.c"

#line 296 "src/modules/pause.c"
/* Toggle the shared speed-option byte through the latched pause-menu
 * action helper. RE_UNKNOWN: the speed-option unit meaning remains unproven. */
void pauseToggleSpeedOption(void) {
    pauseToggleByteOnNewMenuAction(&gOptionsSpeed);
}
#line 299 "src/modules/pause.c"

#line 300 "src/modules/pause.c"
/* Toggle settings byte 0x17A through the existing latched menu-action helper. RE_UNKNOWN: this option meaning requires menu-label or consumer evidence; it is not the stereo byte at 0x178. */
void func_pause_004023A4(void) {
    pauseToggleByteOnNewMenuAction(&D_80025E6A);
}
#line 303 "src/modules/pause.c"

#line 304 "src/modules/pause.c"
/* Adjust the map option across zero through two. With exactly two
 * players, skip mode one by continuing from zero to two or from two
 * to zero. Retain the previous-value test and the original helper call. */
void pauseAdjustMapOptionSkippingTwoPlayerModeOne(void) {
    s32 previousMapMode = *(u8 *)((u8 *)gGameSettings + 0x17B);
    func_pause_00402854(&gOptionsMap, 0, 2);
    if (*(s32 *)((u8 *)gGameSettings + 0x24) == 2 &&
        *(u8 *)((u8 *)gGameSettings + 0x17B) == 1) {
        if (previousMapMode == 0) {
            *(u8 *)((u8 *)gGameSettings + 0x17B) = 2;
        } else if (previousMapMode == 2) {
            *(u8 *)((u8 *)gGameSettings + 0x17B) = 0;
        }
    }
}
#line 316 "src/modules/pause.c"

#line 317 "src/modules/pause.c"
/* Toggle the shared display-option byte through the original
 * pause-menu action latch; holding the action does not repeatedly toggle it. */
void pauseToggleDisplayOption(void) {
    pauseToggleByteOnNewMenuAction(&gOptionsDisplay);
}
#line 320 "src/modules/pause.c"

#line 321 "src/modules/pause.c"
/* Cycle the three language indices once per newly active left/right action.
 * Separate direction latches reset when their action is absent. Preserve the
 * original left decrement/right increment wrap and shared menu input gates. */
void pauseCycleLanguage(void) {
    s32 action = ((PauseLanguageInputExports *)D_pause_00405E44)->get(0, D_pause_00405E50);
    if (action == 1) {
        if (((PauseLanguageLatch *)&D_pause_00405E58)->left == 0) {
            ((PauseLanguageLatch *)&D_pause_00405E58)->left = 1;
            gGameSettings->currentLanguage -= 1;
            if (gGameSettings->currentLanguage < 0) gGameSettings->currentLanguage = 2;
        }
    } else ((PauseLanguageLatch *)&D_pause_00405E58)->left = 0;
    if (action == 2) {
        if (((PauseLanguageLatch *)&D_pause_00405E58)->right == 0) {
            ((PauseLanguageLatch *)&D_pause_00405E58)->right = 1;
            gGameSettings->currentLanguage += 1;
            if (gGameSettings->currentLanguage >= 3) gGameSettings->currentLanguage = 0;
        }
    } else ((PauseLanguageLatch *)&D_pause_00405E58)->right = 0;
}
#line 322 "src/modules/pause.c"

#line 323 "src/modules/pause.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_pause_00402548(void) {
}
#line 325 "src/modules/pause.c"

#line 326 "src/modules/pause.c"
/* Apply volume options and clear sound suppression. For exactly two
 * players, replace map mode one with mode two; leave other map modes
 * and player counts unchanged. */
void pauseApplyOptionsAndNormalizeTwoPlayerMap(void) {
    pauseApplyAudioVolumeOptions();
    (*(void (**)(void))((u8 *)gSndExports + 0xDC))();
    if (*(s32 *)((u8 *)gGameSettings + 0x24) == 2) {
        if (*(u8 *)((u8 *)gGameSettings + 0x17B) == 1) {
            *(u8 *)((u8 *)gGameSettings + 0x17B) = 2;
        }
    }
}
#line 335 "src/modules/pause.c"

#line 336 "src/modules/pause.c"
/* Copy music, sound-effect and speech volumes plus stereo, speed,
 * map and display options into the original save-data fields. Retain
 * word-sized volume writes and byte-sized option writes. */
void pauseCopyOptionsToSaveData(void) {
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D0) = gGameSettings->optionsMusicVol;
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D4) = gGameSettings->optionsSfxVol;
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D8) = gGameSettings->optionsSpeechVol;
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DC) = gGameSettings->optionsStereoMono;
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DD) = gGameSettings->optionsSpeed;
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DE) = gGameSettings->optionsMap;
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DF) = gGameSettings->optionsDisplay;
}
#line 345 "src/modules/pause.c"

#line 346 "src/modules/pause.c"
/* Ask for confirmation before choosing a new track.
 * Save the previous menu for Back and initially select the second choice (No). */
void pauseOpenNewTrackConfirmation(void) {
    MenuNode *previous = D_pause_00405E50;
    D_pause_00405E50 = &D_pause_00405950;
    D_pause_00405E50->unk4 = previous;
    *(s16 *)((u8 *)D_pause_00405E50->unk8 + 4) = 1;
}
#line 347 "src/modules/pause.c"

#line 348 "src/modules/pause.c"
/* Copy the current track word into settings byte 0x17F, retaining low-byte truncation, then request selection state 0xE. RE_UNKNOWN: the saved-track destination role needs its consumer evidence. */
void func_pause_00402630(void) {
    *(u8 *)((u8 *)gGameSettings + 0x17F) = *(s32 *)((u8 *)gGameSettings + 0x44);
    *(s32 *)((u8 *)gGameSettings + 0x8) = 0xE;
}
#line 352 "src/modules/pause.c"

#line 353 "src/modules/pause.c"
#line 353 "src/modules/pause.c"
/* Suppress cancel sound 0x0E, push the Yes/No menu and select No.
 * The previous menu is retained for Back; no unsupported action name is assumed. */
void pauseOpenConfirmationWithCancelSoundSuppressed(void) {
    MenuNode *previous;
    ((SndExp_00403E6C *)gSndExports)->unkE0(0xE);
    previous = D_pause_00405E50;
    D_pause_00405E50 = &D_pause_00405674;
    D_pause_00405E50->unk4 = previous;
    *(s16 *)((u8 *)D_pause_00405E50->unk8 + 4) = 1;
}
#line 363 "src/modules/pause.c"
#line 354 "src/modules/pause.c"

#line 355 "src/modules/pause.c"
/* Copy the current track word into settings byte 0x17E, retaining low-byte truncation, then request selection state 0xE. RE_UNKNOWN: the saved-track destination role needs its consumer evidence. */
void func_pause_004026A8(void) {
    *(u8 *)((u8 *)gGameSettings + 0x17E) = *(s32 *)((u8 *)gGameSettings + 0x44);
    *(s32 *)((u8 *)gGameSettings + 0x8) = 0xE;
}
#line 359 "src/modules/pause.c"

/* Draw two textured rectangles for the pause screen HUD bar. */
typedef struct {
    /* 0x00 */ char pad0[0x1C];
    /* 0x1C */ void (*unk1C)(s32, s32, s32 *, s32 *, s32);
} UvTextureExp_004026C4;
extern UvTextureExp_004026C4 *gUvTextureExports;
typedef struct {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ void (*unk14)(s32);
    /* 0x18 */ char pad18[0x44];
    /* 0x5C */ void (*unk5C)(s32, s32, s32, s32, f32, f32, f32, f32);
} UvGfxStateExp_004026C4;
extern UvGfxStateExp_004026C4 *gUvGfxStateExports;

#line 374 "src/modules/pause.c"
/* Draw texture 0x11 at the requested origin, then overlay texture
 * 0x12 with width and horizontal texture span scaled by value/maximum.
 * Preserve integer truncation, the two-pixel vertical offset and unchecked division. */
void pauseDrawTexturedFractionBar(s32 value, s32 maximum, s32 left, s32 bottom)
{
  s32 textureWidth;
  s32 textureHeight;
  f32 fraction;
  gUvGfxStateExports->unk14(0x11);
  gUvTextureExports->unk1C(0x11, 1, &textureWidth, &textureHeight, 0);
  gUvGfxStateExports->unk5C(left, (textureWidth + left) - 1, bottom, (textureHeight + bottom) - 1, 0.0f, 1.0f, 0.0f, 1.0f);
  gUvGfxStateExports->unk14(0x12);
  gUvTextureExports->unk1C(0x12, 1, &textureWidth, &textureHeight, 0);
  fraction = ((f32) value) / ((f32) maximum);
  gUvGfxStateExports->unk5C(left, (s32) (((f32) left) + (((f32) ((s32) (((f32) textureWidth) * fraction))) - 1.0f)), bottom + 2, (bottom + textureHeight) + 1, 0.0f, fraction, 0.0f, 1.f);
}
#line 387 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402854.s")

#line 390 "src/modules/pause.c"
/* Store one in the shared halfword used by pause-menu actions. RE_UNKNOWN: the action code meaning requires the consumer of D_8002CC88; the numeric value is preserved. */
void func_pause_00402904(void) {
    D_8002CC88 = 1;
}
#line 393 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402914.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402D78.s")

/* Tear-down: reset pause module, stop BGM, play SFX, re-enable controller, mark active. */
#line 399 "src/modules/pause.c"
/* Apply volumes, clear sound suppression and suppress sound 0xDB.
 * Clear the shared peripheral word, snapshot controller-zero peripheral
 * state and mark the current menu node for refresh. */
void pausePreparePeripheralMenu(void) {
    pauseApplyAudioVolumeOptions();
    ((SndExp_00403E6C *)gSndExports)->unkDC();
    ((SndExp_00403E6C *)gSndExports)->unkE0(0xDB);
    D_8002CC88 = 0;
    D_8002CC8A = ((ContExp_00403E6C *)gUvContExports)->unk2C(0);
    ((PauseObj_00403E6C *)D_pause_00405E50)->unk20 = 1;
}
#line 407 "src/modules/pause.c"

#line 408 "src/modules/pause.c"
/* Play pending sound 0xD7 with the original shared volume and center
 * pan, then clear its own pending flag. Preserve the handle and gate. */
void pausePlayPendingSoundD7(void) {
    if (D_pause_00405D3C != 0) {
        (*(void (**)(void *, s32, s32, f32, f32))((u8 *)gSndExports + 0x8))(&D_pause_00405E60, 0xD7, 0x7FFF, (*(f32 (**)(void))((u8 *)gSndExports + 0x4C))(), 0.5f);
        D_pause_00405D3C = 0;
    }
}
#line 414 "src/modules/pause.c"

#line 415 "src/modules/pause.c"
/* Play pending sound 0xF6 with the original shared volume and center
 * pan, then clear its own pending flag. Preserve the handle and gate. */
void pausePlayPendingSoundF6(void) {
    if (D_pause_00405D44 != 0) {
        (*(void (**)(void *, s32, s32, f32, f32))((u8 *)gSndExports + 0x8))(&D_pause_00405E70, 0xF6, 0x7FFF, (*(f32 (**)(void))((u8 *)gSndExports + 0x4C))(), 0.5f);
        D_pause_00405D44 = 0;
    }
}
#line 421 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00403FD0.s")

#line 424 "src/modules/pause.c"
/* Store eight in the shared halfword used by pause-menu actions. RE_UNKNOWN: the action code meaning requires the consumer of D_8002CC88; the numeric value is preserved. */
void func_pause_00404150(void) {
    D_8002CC88 = 8;
}
#line 427 "src/modules/pause.c"

#line 428 "src/modules/pause.c"
/* Clear settings halfwords 0x6F98 and 0x6F96 in original order, then pass eight to the stored export at offset 0x08. RE_UNKNOWN: these fields and callback action need producer/callee evidence. */
void func_pause_00404160(void) {
    *(s16 *)((u8 *)gGameSettings + 0x6F98) = 0;
    *(s16 *)((u8 *)gGameSettings + 0x6F96) = 0;
    D_pause_00405E48->unk8(8);
}
#line 433 "src/modules/pause.c"

#line 434 "src/modules/pause.c"
/* Dispatch the selected menu callback once while action eight is
 * held, using the shared byte as a latch. Clear the latch whenever
 * the menu action is not eight. */
void pauseDispatchActionEightOnce(void) {
    if ((*(s32 (*)(s32, s32))(*(s32 *)((u8 *)D_pause_00405E44 + 0x8)))(
            0, *(s32 *)((u8 *)D_pause_00405E50 + 0x8)) == 8) {
        if (D_pause_00405E58 == 0) {
            D_pause_00405E58 = 1;
            (*(void (*)(void))(*(s32 *)((u8 *)&D_pause_00405D48
                + (*(s16 *)((u8 *)*(s32 *)((u8 *)*(s32 *)((u8 *)D_pause_00405E50 + 0x8) + 0x8) + 0x4) << 2))))();
        }
    } else {
        D_pause_00405E58 = 0;
    }
}
#line 446 "src/modules/pause.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040423C.s")

#line 449 "src/modules/pause.c"
/* Apply volume options and clear suppression, then suppress the
 * directional-menu sound 0xDB and UI cancel sound 0x0E in that order. */
void pausePrepareAudioWithoutNavigationSounds(void) {
    pauseApplyAudioVolumeOptions();
    (*(void (**)(void))((u8 *)gSndExports + 0xDC))();
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xDB);
    (*(void (**)(s32))((u8 *)gSndExports + 0xE0))(0xE);
}
#line 455 "src/modules/pause.c"

