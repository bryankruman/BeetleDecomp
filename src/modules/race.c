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
typedef struct { u8 prefix[0x14]; void (*reset)(void); u8 gap18[0x10]; u8 *root; } RaceGameGuiExports;
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
void raceForwardSharedHandle();
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400CC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400EB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_004011BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401B3C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00401E04.s")

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

void func_race_00403350(void) {
}

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
/* Reset the game GUI, allocate and look up an original 0x5C-byte pool
 * slot, set its fixed-length 30-byte label and attach it under the stored
 * parent. Forward the resulting node to camera, optional AI and track
 * modules in the original order; retain the pool allocation contract. */
void raceCreateModuleGui(void) {
    void *parent;
    void *node;
    parent = gGameGuiExports->root + 0x10;
    gGameGuiExports->reset();
    node = gUvGuiExports->getPoolSlot(gUvGuiExports->allocatePoolSlot());
    gUvGuiExports->setLabelBytes(node, D_race_0040474C);
    gUvGuiExports->attach(parent, node);
    gCamExports->attach(node);
    if (gAiExports != NULL) ((RaceAiGuiExports *)gAiExports)->attach(node);
    ((RaceTrackGuiExports *)D_race_00404A04)->attach(node);
}
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
 * parameter used by the race module. Ownership stays with the caller. */
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
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD4, 0x7FFF, gSndExports->func_snd_004014C4(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    case 1:
        if (D_race_00404888 != 0) {
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD5, 0x7FFF, gSndExports->func_snd_004014C4(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    case 2:
        if (D_race_00404888 != 0) {
            gSndExports->sndPlayManagedSound(&D_race_00404A90, 0xD6, 0x7FFF, gSndExports->func_snd_004014C4(), 0.5f);
            D_race_00404888 = 0;
        }
        break;
    }
}
#line 130 "src/modules/race.c"

#line 131 "src/modules/race.c"
/* Forward the shared race handle through export 0x20. Detailed handle
 * meaning and ownership remain with that module. */
void raceForwardSharedHandle(void) {
    (*(void (**)(s32))((u8 *)D_race_00404A04 + 0x20))(D_race_004049F0);
}
#line 134 "src/modules/race.c"

