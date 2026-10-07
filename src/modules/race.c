// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
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
void func_race_00400920();
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
void func_race_00403268();
void func_race_00403358();
s32 func_race_0040348C();
void raceCreateModuleGui(void);
void func_race_004035C8();
void func_race_0040367C();
void func_race_004036C8();
void raceMarkMatchingEntries(s32 value);
void func_race_00403734();
void func_race_004037DC();
void func_race_004038B0();
void func_race_00403B6C();
void func_race_00404044();
void func_race_00404194();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/__entrypoint_func_race_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00400920.s")

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

void func_race_00403268(void) {
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404710, D_race_00404AA0, 0x96);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404718, D_race_00404AA4, 0x8C);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404724, D_race_00404AA8, 0x82);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404730, D_race_00404AAC, 0x78);
    (*(void (**)(void *, s32, s32))((u8 *)gMiscExports + 0xFC))((u8 *)&D_race_00404740, D_race_00404AB0, 0x6E);
    if (gAiExports != 0) {
        (*(void (**)(void))((u8 *)gAiExports + 0x10))();
    }
}

void func_race_00403350(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00403358.s")

s32 func_race_0040348C(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= *(s32 *)((u8 *)&D_race_004049F0 + 0x10))) {
        return 0;
    }
    return *(s32 *)((u8 *)&D_race_004049F0 + arg0 * 4);
}

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

void func_race_0040367C(s32 arg0) {
    uvLoadFile(0x55564D44, arg0);
    (*(void (**)(s32, void *))((u8 *)gUvModelExports + 0x4C))(arg0, func_race_004037DC);
}

void func_race_004036C8(s32 a0, s32 a1, s32 a2) {
    D_race_004049E4 = a0;
    D_race_004049E8 = (s32 *)a1;
    D_race_004049EC = a2;
}

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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/race/func_race_00404044.s")

void func_race_00404194(void) {
    (*(void (**)(s32))((u8 *)D_race_00404A04 + 0x20))(D_race_004049F0);
}

