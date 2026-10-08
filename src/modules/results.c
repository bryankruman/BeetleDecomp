// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/*__SEEDEXTERNS__*/
typedef struct {
    /* 0x00 */ char pad0[0x08];
    /* 0x08 */ void (*playManagedSound)(void *, s16, s32, f32, f32);
    /* 0x0C */ void (*unkC)(s16, s32, f32, s32);
    /* 0x10 */ char pad10[0x34];
    /* 0x44 */ void (*unk44)(s32);
    /* 0x48 */ char pad48[0x04];
    /* 0x4C */ f32 (*getSpeechVolumeScale)(void);
    /* 0x50 */ char pad50[0x7C];
    /* 0xCC */ void (*unkCC)(void *);
} SndExp_0040659C; /* Observed slots; managed-playback status is discarded. RE_UNKNOWN: complete historical export/storage declarations need original registrations and producers. */
extern f32 D_80025D6C;
extern f32 D_results_004072AC;
extern f32 D_results_004076F0;
extern s32 D_results_004075B8;
extern s32 gOptionsSpeechVol;
extern void *gSndExports;
extern void *gUvEmitterExports;
extern u8 D_results_00407720;
extern u8 D_results_00407728;
extern u8 D_results_00407730;
extern u8 D_results_00407738;
extern u8 D_results_00407740;
extern u8 D_results_00407748;
extern u8 D_results_00407750;
extern u8 D_results_00407751;
extern u8 D_8002CB9A;
extern u8 D_8002CD98;
extern void *D_results_00407718;
extern s16 D_results_00407568[];
extern s32 D_results_00407508[4][6];
extern s32 D_results_004075A8;
extern s32 D_results_004075AC;
extern s32 D_results_004075BC;
extern s32 D_results_004075C0;
void resultsReleaseSoundsAndStopEmitters();
void func_results_004002BC();
void func_results_00400AC8();
void resultsRequestReplayStateOnce();
void func_results_004013BC();
void func_results_00401B00();
void func_results_00402B9C();
void func_results_00403284();
void func_results_00404474();
void func_results_00404D20();
void func_results_00405608();
void resultsCallMenuCallbackWith100();
void func_results_00405E18();
void func_results_00405ED8();
void func_results_00405F94();
void func_results_00406184();
void func_results_0040620C();
void resultsUpdateFourBestCounters(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s16 resultsGetMappedShortOrFallback();
s32 resultsGetMappedWordOrFallback();
void resultsPlayPendingNewContinueVoice();
void resultsPlayPendingNewArenaVoice();
void resultsPlayPendingFirstPlaceVoice();
void resultsPlayPendingCheatMenuVoice();
void resultsPlayPendingNewCheatVoice();
extern s32 D_results_004074F8[];
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/__entrypoint_func_results_400000.s")

#line 67 "src/modules/results.c"
/* Release all six original managed sound handles, then stop the
 * two stored emitter slots. Retain handle order and byte-sized emitter IDs. */
void resultsReleaseSoundsAndStopEmitters(void) {
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407720);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407728);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407730);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407738);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407740);
    (*(void (**)(void *))((u8 *)gSndExports + 0x70))((u8 *)&D_results_00407748);
    (*(void (**)(s32))((u8 *)gUvEmitterExports + 0x5C))(*(u8 *)&D_results_00407750);
    (*(void (**)(s32))((u8 *)gUvEmitterExports + 0x5C))(*(u8 *)&D_results_00407751);
}
#line 77 "src/modules/results.c"

#line 78 "src/modules/results.c"
/* Return the caller-indexed word from the original results table without a new bounds check. RE_UNKNOWN: the table value meaning and valid index range require caller/data evidence. */
s32 resultsGetIndexedTableWord(s32 index) {
    return D_results_004074F8[index];
}
#line 81 "src/modules/results.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004002BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00400AC8.s")

#line 86 "src/modules/results.c"
/* When intro/replay state is zero, set it to one and request game state
 * five. Further calls leave both state fields unchanged. */
void resultsRequestReplayStateOnce(void) {
    if (gGameSettings->introReplayState == 0) {
        gGameSettings->introReplayState = 1;
        gGameSettings->newGameState = 5;
    }
}
#line 92 "src/modules/results.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_004013BC.s")

#line 95 "src/modules/results.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_results_00401AF8(void) {
}
#line 97 "src/modules/results.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00401B00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00402B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00403284.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00404474.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00404D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405608.s")

#line 110 "src/modules/results.c"
/* Pass integer 100 to menu export 0x3C. RE_UNKNOWN: the action and argument units require the original menu slot0x3C target and its callers; the original results initializer proves the stored provider is MENU. */
void resultsCallMenuCallbackWith100(void) {
    (*(void (**)(s32))((u8 *)D_results_00407718 + 0x3C))(0x64);
}
#line 113 "src/modules/results.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405ED8.s")
/*
 * Map the current full-word track handle through SCENE slot0x0C (first of six
 * matches, or ambiguous0), then scan five floats backward in a 100-byte record.
 * Preserve ordered comparisons, backward float/name shifts and the original
 * final four-read/four-write name groups; final settings-base traversal ends
 * at the distinct D_80025D00 address marker, reading name bytes at +0x150.
 * Return insertion slot0..5; five performs no insertion. Equality and NaN do
 * not select a slot. No external sort invariant or physical units are proved.
 * RE_UNKNOWN: complete record/settings/marker declarations, storage allocation,
 * persistence, alias domains and valid table lifecycle. Resolve original record
 * producers, name/track writers and every persistence/result caller.
 * Readable C parked:348 native bytes versus516,100 differing words and unequal
 * full relocation records. The native endpoint is restored, but the compiler
 * expands the explicit grouped copy into remainder/unrolled loops; natural
 * instruction equivalence and full packed-module/ROM proof are still required.
 */
#line 118 "src/modules/results.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00405F94.s")

/* Find the rank position of arg0 against 5 threshold floats in the track's time table at D_8002CD98. */
typedef struct SceneExp_004060F0_s {
    char pad0[0xC];
    s32 (*unkC)(s32);
} SceneExp_004060F0;
typedef struct TrackEntry_004060F0_s {
    char pad0[0x50];
    f32 unk50;
} TrackEntry_004060F0;
extern SceneExp_004060F0 *gSceneExports;
extern s32 gCurrentTrack;

#line 132 "src/modules/results.c"
/* Compare the supplied time against the five stored times for the
 * scene-mapped track. Scan backward and retain the lowest one-based
 * rank whose stored time is strictly greater; return zero when none qualify. */
s32 resultsFindStrictTimeRank(f32 time)
{
  s32 zeroRank;
  s32 rank;
  s32 recordIndex;
  TrackEntry_004060F0 *record;
  int trackOffset;
  zeroRank = 0;
  rank = zeroRank;
  trackOffset = gSceneExports->unkC(gCurrentTrack) * 0x64;
  record = (TrackEntry_004060F0 *) ((((u8 *) (&D_8002CD98)) + trackOffset) + 0x10);
  recordIndex = 4;
  do
  {
    if (time < record->unk50)
    {
      rank = recordIndex + 1;
    }
    recordIndex -= 1;
    record = (TrackEntry_004060F0 *) (((char *) record) - 4);
  }
  while (recordIndex >= 0);
  return rank;
}
#line 156 "src/modules/results.c"
/* RE_UNKNOWN: counted float slots at 0x6EE0/0x6F00 and shared scalar 0xEC have unresolved meanings, units, count bounds, full backing layout and alias/lifetime; trace original count/storage writers and result callers. Native ordered comparisons gate division by the positive observed/shared ratio. The readable draft preserves every arithmetic/load/store/control effect, but compiler base-address reuse differs; retain original assembly until historical typed access views or new source/compiler evidence resolves it. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_00406184.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/results/func_results_0040620C.s")

/* Draws a grid of tiles with alternating flags across a region, used in the results screen. */
typedef struct UvGfxStateExp_00406338_s {
    /* 0x00 */ void (*unk0)(void);
    /* 0x04 */ void (*unk4)(u32);
    /* 0x08 */ void (*unk8)(void *, s32);
    /* 0x0C */ void (*unkC)(s32);
    /* 0x10 */ void (*unk10)(s32);
    /* 0x14 */ void (*unk14)(s32);
    /* 0x18 */ void (*unk18)(void *, s32);
    /* 0x1C */ void (*unk1C)(void *, s32);
    /* 0x20 */ void (*unk20)(void *, s32);
    /* 0x24 */ void (*unk24)(void *, s32, s32);
    /* 0x28 */ s32  (*unk28)(void *, s32);
    /* 0x2C */ void (*unk2C)(s32);
    /* 0x30 */ void (*unk30)(s32);
    /* 0x34 */ void (*unk34)(void *);
    /* 0x38 */ void (*unk38)(void *);
    /* 0x3C */ void (*unk3C)(void);
    /* 0x40 */ void (*unk40)(s32);
    /* 0x44 */ void (*unk44)(f32, f32);
    /* 0x48 */ void (*unk48)(f32 *, f32 *);
    /* 0x4C */ void (*unk4C)(s32, s32);
    /* 0x50 */ void (*unk50)(void);
    /* 0x54 */ void (*unk54)(void);
    /* 0x58 */ void (*unk58)(void);
    /* 0x5C */ void (*unk5C)(s32, s32, s32, s32, f32, f32, f32, f32);
} UvGfxStateExp_00406338;
extern UvGfxStateExp_00406338 *gUvGfxStateExports;

#line 190 "src/modules/results.c"
/* Draw eight adjacent 32-by-32 tiles using texture 0x16. Alternate
 * both texture directions on every tile, optionally starting with
 * reversed horizontal coordinates, and restore the pushed graphics state. */
void resultsDrawAlternatingTextureStrip(s32 left, s32 bottom, s32 flipHorizontal)
{
  s32 tileLeft;
  s32 drawnWidth;
  s32 tileRight;
  s32 textureLeft;
  s32 textureRight;
  s32 textureBottom;
  s32 textureTop;
  textureLeft = 0;
  textureRight = 1;
  textureBottom = 0;
  textureTop = 1;
  if (flipHorizontal != 0)
  {
    textureLeft = 1;
    textureRight = 0;
  }
  gUvGfxStateExports->unk50();
  gUvGfxStateExports->unkC(0x04800000);
  gUvGfxStateExports->unk10(0x1A600000);
  gUvGfxStateExports->unk14(0x16);
  tileLeft = left;
  tileRight = left + ((unsigned int) 0x1F);
 drawnWidth = 0; tileRight = left + ((unsigned int) 0x1F); do { gUvGfxStateExports->unk5C(tileLeft, tileRight, bottom, bottom + 0x1F, textureLeft, (f32) textureRight, textureBottom, (f32) textureTop);
    drawnWidth += 0x20;
    tileLeft += 0x20;
    tileRight += 0x20;
    textureLeft = textureLeft == 0;
    textureRight = textureRight == 0;
    textureBottom = textureBottom == 0;
    textureTop = textureTop == 0;
  }
  while (drawnWidth != 0x100);
  gUvGfxStateExports->unk54();
}
#line 226 "src/modules/results.c"

#line 227 "src/modules/results.c"
/* Replace each of the four saved counters only when the supplied
 * value is greater. Updating the second counter also clears its
 * associated shared short. Preserve independent comparisons and store order. */
void resultsUpdateFourBestCounters(s32 first, s32 second, s32 third, s32 fourth) {
    if (*(s32 *)((u8 *)&D_8002CD98 + 0x258) < first) {
        *(s32 *)((u8 *)&D_8002CD98 + 0x258) = first;
    }
    if (*(s32 *)((u8 *)&D_8002CD98 + 0x25C) < second) {
        D_8002CB9A = 0;
        *(s32 *)((u8 *)&D_8002CD98 + 0x25C) = second;
    }
    if (*(s32 *)((u8 *)&D_8002CD98 + 0x260) < third) {
        *(s32 *)((u8 *)&D_8002CD98 + 0x260) = third;
    }
    if (*(s32 *)((u8 *)&D_8002CD98 + 0x264) < fourth) {
        *(s32 *)((u8 *)&D_8002CD98 + 0x264) = fourth;
    }
}
#line 242 "src/modules/results.c"

#line 243 "src/modules/results.c"
/* Map indices zero through seven to the original signed short table;
 * any out-of-range index selects fallback entry seven. */
s16 resultsGetMappedShortOrFallback(s32 index) {
    if (index < 0 || index >= 8) {
        index = 7;
    }
    return D_results_00407568[index];
}
#line 249 "src/modules/results.c"

#line 250 "src/modules/results.c"
/* Look up the original four-by-six result table. Invalid row selects
 * row three and invalid column selects column five independently. */
s32 resultsGetMappedWordOrFallback(s32 row, s32 column) {
    if (row < 0 || row >= 4) {
        row = 3;
    }
    if (column < 0 || column >= 6) {
        column = 5;
    }
    return D_results_00407508[row][column];
}
#line 259 "src/modules/results.c"

#line 260 "src/modules/results.c"

/* Use the original 2.0f spacing and speech-volume scale; immediate playback receives fixed pitch 0.5f. */
#line 261 "src/modules/results.c"
/* With speech enabled and pending nonzero, play after the original 2.0f
 * interval or schedule its converted remaining delay; update time and clear pending.
 * RE_UNKNOWN: clock/delay units and handle/flag lifetimes need original producers/callers. */
void resultsPlayPendingVoiceWithSpacing(s16 soundId, s32 *pending) {
    s64 soundHandle;
    f32 delay;

    ((SndExp_0040659C *)gSndExports)->unkCC(&soundHandle);
    if (gOptionsSpeechVol == 0) {
        return;
    }
    ((SndExp_0040659C *)gSndExports)->unk44(gOptionsSpeechVol);
    delay = 2.0f - (D_80025D6C - D_results_004076F0);
    if (*pending != 0) {
        if (delay < 0.0f) {
            delay = 0.0f;
            ((SndExp_0040659C *)gSndExports)->playManagedSound(&soundHandle, soundId, 0x7FFF, ((SndExp_0040659C *)gSndExports)->getSpeechVolumeScale(), 0.5f);
        } else {
            ((SndExp_0040659C *)gSndExports)->unkC(soundId, 0x7FFF, ((SndExp_0040659C *)gSndExports)->getSpeechVolumeScale(), (s32) (delay * D_results_004072AC));
        }
        D_results_004076F0 = D_80025D6C + delay;
        *pending = 0;
    }
}
#line 285 "src/modules/results.c"
#line 282 "src/modules/results.c"

#line 283 "src/modules/results.c"
/* Pass voice 0xEB and its pending flag to the result voice-spacing helper. */
void resultsPlayPendingNewContinueVoice(void) {
    resultsPlayPendingVoiceWithSpacing(0xEB, &D_results_004075A8);
}
#line 286 "src/modules/results.c"

#line 287 "src/modules/results.c"
/* Pass voice 0xEC and its pending flag to the result voice-spacing helper. */
void resultsPlayPendingNewArenaVoice(void) {
    resultsPlayPendingVoiceWithSpacing(0xEC, &D_results_004075AC);
}
#line 290 "src/modules/results.c"

#line 291 "src/modules/results.c"
/* With speech enabled, play voice 0xCF through the stored result
 * sound handle when its pending flag is set. Apply speech volume
 * before testing the flag, and clear the flag only after playback is requested. */
void resultsPlayPendingFirstPlaceVoice(void) {
    if (gOptionsSpeechVol != 0) {
        (*(void (*)(s32))(*(s32 *)((u8 *)gSndExports + 0x44)))(gOptionsSpeechVol);
        if (D_results_004075B8 != 0) {
            (*(void (*)(void *, s32, s32, f32, f32))(*(s32 *)((u8 *)gSndExports + 0x8)))(
                (u8 *)&D_results_00407748, 0xCF, 0x7FFF,
                (*(f32 (*)(void))(*(s32 *)((u8 *)gSndExports + 0x4C)))(),
                0.5f);
            D_results_004075B8 = 0;
        }
    }
}
#line 303 "src/modules/results.c"

#line 304 "src/modules/results.c"
/* Pass voice 0xF4 and its pending flag to the existing result
 * voice-spacing helper. The helper owns speech gating and flag clearing. */
void resultsPlayPendingCheatMenuVoice(void) {
    resultsPlayPendingVoiceWithSpacing(0xF4, &D_results_004075BC);
}
#line 307 "src/modules/results.c"

#line 308 "src/modules/results.c"
/* Pass voice 0xF5 and its pending flag to the existing result
 * voice-spacing helper. Preserve its scheduling and pending-flag contract. */
void resultsPlayPendingNewCheatVoice(void) {
    resultsPlayPendingVoiceWithSpacing(0xF5, &D_results_004075C0);
}
#line 311 "src/modules/results.c"

