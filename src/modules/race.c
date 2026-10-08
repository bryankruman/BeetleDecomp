// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
extern UnkStruct_004005C8 D_race_00404A30;
extern UnkStruct_004005C8 D_race_00404A38;
extern UnkStruct_004005C8 D_race_00404A40;
extern UnkStruct_004005C8 D_race_00404A48;
extern UnkStruct_004005C8 D_race_00404A50;
extern UnkStruct_004005C8 D_race_00404A58;
extern UnkStruct_004005C8 D_race_00404A60;
extern UnkStruct_004005C8 D_race_00404A68;
extern UnkStruct_004005C8 D_race_00404A70;
extern UnkStruct_004005C8 D_race_00404A78;
extern UnkStruct_004005C8 D_race_00404A80;
extern UnkStruct_004005C8 D_race_00404A88;
extern UnkStruct_004005C8 D_race_00404A98;
extern s8 D_80025D88,D_80025D89,D_80025D8A,D_80025D8B;
#include "module.h"
extern Snd_Exports *gSndExports;
extern s32 D_race_00404888;
extern UnkStruct_004005C8 D_race_00404A90;
/* Original GAMEGUI slot 0x14 configures the shared widget when settings word 0x18C
 * is nonzero; original GAMEGUI slot 0x28 exports the debug-byte address. The widget
 * used below begins 16 bytes after that address. This prefix models only
 * those original slots, not the complete shared-state allocation.
 * RE_UNKNOWN: the historical source typedef and meaning of settings word 0x18C.
 * Trace original settings writers and the widget initializer before rewrite. */
typedef struct { u8 prefix[0x14]; void (*initializeSharedGui)(void); u8 gap18[0x10]; u8 *debugByteAddress; } RaceGameGuiExports;
typedef struct { u8 prefix[8]; void (*attach)(void *, void *); u8 gap0C[0x64]; s16 (*allocatePoolSlot)(void); void *(*getPoolSlot)(s16); void (*setLabelBytes)(void *, u8 *); } RaceGuiExports;
typedef struct { u8 prefix[0x2C]; void (*attach)(void *); } RaceCameraGuiExports;
typedef struct { u8 prefix[0x14]; void (*attach)(void *); } RaceAiGuiExports;
typedef struct { u8 prefix[0x10]; void (*attach)(void *); } RaceTrackGuiExports;
extern RaceGameGuiExports *gGameGuiExports;
extern RaceGuiExports *gUvGuiExports;
extern RaceCameraGuiExports *gCamExports;
extern u8 D_race_0040474C[0x1E];

/*__SEEDEXTERNS__*/
extern void *gUvModelExports;
extern void *gMiscExports;
extern void *gAiExports;
extern u8 D_race_00404710;
extern u8 D_race_00404718;
extern u8 D_race_00404724;
extern u8 D_race_00404730;
extern u8 D_race_00404740;
extern s32 D_race_00404AA0;
extern s32 D_race_00404AA4;
extern s32 D_race_00404AA8;
extern s32 D_race_00404AAC;
extern s32 D_race_00404AB0;
extern s32 D_race_004049E4;
extern s32 *D_race_004049E8;
extern s32 D_race_004049EC;
extern u8 D_race_004049C4[];
extern s32 D_race_004049F0;
extern void *D_race_00404A04;
void raceReleaseManagedSoundsAndClearBytes(void);
void func_race_00400AB4();
void func_race_00400CC0();
void func_race_00400EB0();
void func_race_004011BC();
void func_race_00401B3C();
void func_race_00401E04();
void func_race_004024D0();
void func_race_004026D0();
void func_race_00402864();
void func_race_00402AAC();
void func_race_00402CE0();
void func_race_00402E98();
void func_race_004030D0();
void raceDrawStatusFields();
void func_race_00403358();
s32 raceGetIndexedValue();
void raceCreateModuleGui(void);
void func_race_004035C8();
void raceLoadModelAndRegisterCallback();
void raceSetEntryTable();
void raceMarkMatchingEntries(s32 value);
void func_race_00403734();
void func_race_004037DC();
void func_race_004038B0();
void func_race_00403B6C();
void racePlayPendingSoundByKind(s32 kind);
void raceReleaseFirstPlayerSoundHandle();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/__entrypoint_func_race_400000.s")

#line 82 "src/modules/race.c"
/* Release the fourteen original managed race sound handles in fixed order,
 * then clear the four shared bytes at 0x80025D88 through 0x80025D8B.
 * Preserve every call rather than assuming the adjacent handles form an array. */
void raceReleaseManagedSoundsAndClearBytes(void) {
    gSndExports->sndReleaseHandle(&D_race_00404A30);
    gSndExports->sndReleaseHandle(&D_race_00404A38);
    gSndExports->sndReleaseHandle(&D_race_00404A40);
    gSndExports->sndReleaseHandle(&D_race_00404A48);
    gSndExports->sndReleaseHandle(&D_race_00404A50);
    gSndExports->sndReleaseHandle(&D_race_00404A58);
    gSndExports->sndReleaseHandle(&D_race_00404A60);
    gSndExports->sndReleaseHandle(&D_race_00404A68);
    gSndExports->sndReleaseHandle(&D_race_00404A70);
    gSndExports->sndReleaseHandle(&D_race_00404A78);
    gSndExports->sndReleaseHandle(&D_race_00404A80);
    gSndExports->sndReleaseHandle(&D_race_00404A88);
    gSndExports->sndReleaseHandle(&D_race_00404A90);
    gSndExports->sndReleaseHandle(&D_race_00404A98);
    D_80025D88 = 0;
    D_80025D89 = 0;
    D_80025D8A = 0;
    D_80025D8B = 0;
}
#line 83 "src/modules/race.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400AB4.s")

/* Original pause pass checks signed settings halfwords 0x9C/0x86/0x88 and
 * player gates 0x58/0x1D; REPLAY 0x0C stores a shared byte, not pauseFlag.
 * While paused, PAUS 0x08 dispatches state; CARAUDIO 0x0C processes each player
 * before PLYR 0x20 releases its word-0x14 indexed sound handle. Preserve reloads.
 * RE_UNKNOWN: gate/state domains, table capacity and player/handle lifetime
 * need original writers/callers. Clean C is unmatched; retain original ASM. */
#line 86 "src/modules/race.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004011BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401E04.s")

/* Update shared scalars, then run CARANIM 0x08 on each entry's word-4
 * pointer; reload entry, its word-0x0C state pointer and state word 0x140.
 * AI 0x28 consumes no arguments. REPLAY masks 0/0x9000 and 1/0x9000 flank
 * a saved-count/live-count comparison; success stores gate/state 3, calls
 * REPLAY 0x10, then writes scalar 5. Preserve those calls and reloads.
 * RE_UNKNOWN: scalar units, gate/state meanings, count domain/capacity and
 * state/table ownership/scheduling need original producers/callers. Clean C
 * remains unmatched; retain assembly pending full byte/relocation proof. */
#line 96 "src/modules/race.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004024D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004026D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402864.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402AAC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00402E98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004030D0.s")

#line 91 "src/modules/race.c"
/* Submit five race status fields at their original Y positions, then
 * run the optional AI status callback. Preserve callback order. */
void raceDrawStatusFields(void) {
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404710, D_race_00404AA0, 0x96);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404718, D_race_00404AA4, 0x8C);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404724, D_race_00404AA8, 0x82);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404730, D_race_00404AAC, 0x78);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404740, D_race_00404AB0, 0x6E);
    if (gAiExports != 0) {
        (*(void (**)(void))((u8 *)gAiExports + 0x10))();
    }
}
#line 101 "src/modules/race.c"

#line 102 "src/modules/race.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_race_00403350(void) {
}
#line 104 "src/modules/race.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403358.s")

#line 107 "src/modules/race.c"
/* Return the indexed shared word when the signed index is nonnegative
 * and below the stored count at offset 0x10, otherwise return zero. */
s32 raceGetIndexedValue(s32 index) {
    if ((index < 0) || (index >= *(s32 *)((u8 *)&D_race_004049F0 + 0x10))) {
        return 0;
    }
    return *(s32 *)((u8 *)&D_race_004049F0 + index * 4);
}
#line 113 "src/modules/race.c"

#line 114 "src/modules/race.c"

#line 115 "src/modules/race.c"
/* Select the shared GAMEGUI widget at debug-byte address+0x10 before the
 * original GAMEGUI14 initialization call, then allocate and label a child
 * group and attach it. Forward the child to camera, optional AI and track
 * callbacks in the original order. GAMEGUI14 conditionally loads/configures
 * shared GUI resources, selects palette/font3 and clears shared state; it
 * consumes no incoming argument in the original machine instructions.
 * RE_UNKNOWN: the complete shared-state/widget layout and settings word18C
 * gate meaning. Inspect original data spans and all flag writers; do not
 * reinterpret export28 as a separately allocated root-object pointer. */
void raceCreateModuleGui(void) {
    void *parent;
    void *node;
    parent = gGameGuiExports->debugByteAddress + 0x10;
    gGameGuiExports->initializeSharedGui();
    node = gUvGuiExports->getPoolSlot(gUvGuiExports->allocatePoolSlot());
    gUvGuiExports->setLabelBytes(node, D_race_0040474C);
    gUvGuiExports->attach(parent, node);
    gCamExports->attach(node);
    if (gAiExports != NULL) ((RaceAiGuiExports *)gAiExports)->attach(node);
    ((RaceTrackGuiExports *)D_race_00404A04)->attach(node);
}
#line 127 "src/modules/race.c"
#line 115 "src/modules/race.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004035C8.s")

#line 118 "src/modules/race.c"
/* Load the model and register the original race callback with its
 * model export. Preserve the original load/status contract. */
void raceLoadModelAndRegisterCallback(s32 modelId) {
    uvLoadFile(0x55564D44, modelId);
    (*(void (**)(s32, void *))((u8 *)gUvModelExports + 0x4C))(modelId, func_race_004037DC);
}
#line 122 "src/modules/race.c"

#line 123 "src/modules/race.c"
/* Store the shared entry count, value-array address and opaque third
 * parameter used by the race module.
 * RE_UNKNOWN: ownership/lifetime of the retained value array. Trace original
 * setters, table users and teardown paths around D_race_004049E8; storing
 * the supplied address alone does not establish caller ownership. */
void raceSetEntryTable(s32 count, s32 valuesAddress, s32 parameter) {
    D_race_004049E4 = count;
    D_race_004049E8 = (s32 *)valuesAddress;
    D_race_004049EC = parameter;
}
#line 128 "src/modules/race.c"

#line 119 "src/modules/race.c"
/* Set the parallel byte flag for every matching race entry. Keep all other
 * flags unchanged and preserve the original empty/nonpositive-count behavior. */
void raceMarkMatchingEntries(s32 value) {
    s32 index;
    for (index = 0; index < D_race_004049E4; index++) {
        if (D_race_004049E8[index] == value) {
            D_race_004049C4[index] = 1;
        }
    }
}
#line 120 "src/modules/race.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403734.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004037DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004038B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403B6C.s")

#line 129 "src/modules/race.c"
/* Consume the pending race sound request for kinds 0, 1 and 2.
 * Select the original sound IDs and shared sound level; other kinds leave
 * the pending flag unchanged. The specific in-game cue meanings are unproven. */
void racePlayPendingSoundByKind(s32 kind) {
    switch (kind) {
    case 0:
        if (D_race_00404888 != 0) {
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD4, 0x7FFF, gSndExports->sndGetSpeechVolumeScale(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    case 1:
        if (D_race_00404888 != 0) {
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD5, 0x7FFF, gSndExports->sndGetSpeechVolumeScale(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    case 2:
        if (D_race_00404888 != 0) {
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD6, 0x7FFF, gSndExports->sndGetSpeechVolumeScale(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    }
}
#line 130 "src/modules/race.c"

#line 131 "src/modules/race.c"
/* Pass the first stored player to PLYR 0x20, releasing its word-0x14 indexed sound handle.
 * RE_UNKNOWN: nonnull player, valid handle index and lifetime need original callers/PLYR producers. */
#line 133 "src/modules/race.c"

void raceReleaseFirstPlayerSoundHandle(void) {
    (*(void (**)(s32))((u8 *)D_race_00404A04 + 0x20))(D_race_004049F0);
}
#line 136 "src/modules/race.c"
#line 134 "src/modules/race.c"

