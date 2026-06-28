// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s8 D_selection_00421CF3;
extern s8 D_selection_00421CFB;
extern s8 D_selection_00421D03;
extern s8 D_selection_00421D0B;
extern s8 D_selection_00421DF4;
extern s8 D_selection_00421DF5;
extern s8 D_selection_00421DF6;
extern s8 D_selection_00421DF7;
typedef struct { char pad0[0xF4]; void (*unkF4)(u8); } UnkSndExports_sel;
typedef struct { char pad0[8]; void (*unk8)(s16); } UnkUvSprtExports_sel;
typedef struct { char pad0[0x7C]; s16 (*unk7C)(void); } UnkUvEmitterExports_sel;
extern UnkSndExports_sel *gSndExports;
extern UnkUvSprtExports_sel *gUvSprtExports;
extern UnkUvEmitterExports_sel *gUvEmitterExports;
extern u8 gOptionsStereoMono;
extern u8 gOptionsSpeed;
extern u8 gOptionsMap;
extern u8 gOptionsDisplay;
extern u8 D_80025E6A;
extern s32 gNumPlayers;
extern s32 gNumAiCars;
extern u8 gTransmissionType;
extern s32 D_80025E70;
extern s16 D_selection_00420DF0;
extern s16 D_selection_00420DFC;
extern s16 D_selection_00420DF8;
extern s32 D_selection_00421CE0;
extern void *D_selection_00421D1C;
extern s32 D_selection_00421D28;
extern s32 D_selection_00420E18;
extern s32 D_selection_00420E1C;
extern s32 D_selection_0041FC80;
extern s32 D_selection_0041FF2C;
extern s32 D_selection_0041FD74;
extern s32 D_selection_0041F770;
extern s32 D_selection_00420104;
extern s32 D_selection_0041FED0;
extern s32 D_selection_0041F94C;
extern s32 D_selection_0041FB58;
extern s32 D_selection_0041F994;
extern s32 D_selection_0041F904;
extern s32 D_selection_0041FE04;
extern s32 D_selection_0041FFE4;
extern s32 D_selection_00420218;
extern s32 D_selection_00420074;
extern s32 D_selection_0041F728;
extern s32 D_selection_00420260;
extern s32 D_selection_00420E90;
extern s32 D_selection_00420E84;
extern s32 D_selection_00420E74;
extern s32 D_selection_00420E78;
extern s32 D_selection_00420E70;
extern s32 D_selection_0041F5B4;
extern s32 D_selection_00421BA0;
extern s8 D_selection_00420DE8;
extern s16 D_selection_00420DEC;
extern s16 D_8002CC84;
extern s32 gCheatBattleNumLadybugs;
extern s32 gCheatBattleLadybugColor;
extern s32 gCheatBattleHealth;
extern s32 gCheatBattlePowerups;
extern s32 gCheatBattleTimeLimit;
extern s32 gCheatBattleRadar;
extern s32 gCheatBattleDamage;
extern s32 gCheatBattleMysteryBoxMode;
extern s32 gCheatTimeAttackBonusBoxes;
extern s32 gCheatBreakables;
extern s32 gCheatEnvironment;
extern s32 gCheatCars;
extern s32 gCheatPlayer2Handicap;
extern s32 gCheatColorChange;
extern s32 gCheatFieldOfView;
extern s32 gCheatHornSfxId;
extern s32 gCheatTrackMusic;
extern s32 gCheatHandbreakPower;
void func_selection_004000E4();
void func_selection_004003DC();
void func_selection_00400580();
void func_selection_004008B0();
void func_selection_00401570();
void func_selection_004015D4();
void func_selection_004016CC();
void func_selection_004017E0();
void func_selection_0040189C();
void func_selection_00401964();
void func_selection_00401A38();
void func_selection_00401B1C();
void func_selection_00401BF4();
void func_selection_00401D04();
void func_selection_00401FB0();
void func_selection_00402254();
void func_selection_00402588();
void func_selection_00402994();
void func_selection_00402D84();
void func_selection_00402E34();
void func_selection_00402E98();
void func_selection_00402F30();
void func_selection_00402F80();
void func_selection_00402FE4();
void func_selection_00403050();
void func_selection_004030E4();
void func_selection_0040319C();
void func_selection_004031E8();
void func_selection_00403220();
void func_selection_00403254();
void func_selection_00403284();
void func_selection_004032BC();
void func_selection_004032EC();
void func_selection_00403338();
void func_selection_0040372C();
void func_selection_004037F4();
void func_selection_0040382C();
void func_selection_00403868();
void func_selection_004038A4();
void func_selection_004038E0();
void func_selection_0040390C();
void func_selection_00403938();
void func_selection_004039B0();
void func_selection_00403A38();
void func_selection_00403A64();
void func_selection_00403A9C();
void func_selection_00403AC8();
void func_selection_00403B40();
void func_selection_00403B6C();
void func_selection_00403BAC();
void func_selection_00403BEC();
void func_selection_00403C2C();
void func_selection_00403CA8();
void func_selection_00403D24();
void func_selection_00403DA0();
void func_selection_00403DE0();
void func_selection_00403E04();
void func_selection_00403E28();
void func_selection_00403E54();
void func_selection_00403E78();
void func_selection_0040437C();
void func_selection_004045F4();
void func_selection_00404620();
void func_selection_0040464C();
void func_selection_00404678();
void func_selection_004046A4();
void func_selection_004046D0();
void func_selection_004046FC();
void func_selection_00404728();
void func_selection_00404754();
void func_selection_00404780();
void func_selection_004047AC();
void func_selection_004047D8();
void func_selection_00404804();
void func_selection_00404830();
void func_selection_0040485C();
void func_selection_00404888();
void func_selection_004048D8();
void func_selection_00404A8C();
void func_selection_00404ACC();
void func_selection_00404AF8();
void func_selection_00404B2C();
void func_selection_00404C24();
void func_selection_00405078();
void func_selection_00405140();
void func_selection_00405644();
void func_selection_00405CB0();
void func_selection_00405E38();
void func_selection_00405F48();
void func_selection_004060D4();
void func_selection_0040611C();
void func_selection_0040626C();
void func_selection_004062F8();
void func_selection_00406924();
void func_selection_00406DC4();
void func_selection_00406F80();
void func_selection_0040705C();
void func_selection_004078D4();
void func_selection_00407AF8();
void func_selection_004080D0();
void func_selection_004081B4();
void func_selection_00408304();
void func_selection_004083DC();
void func_selection_0040884C();
void func_selection_00408B24();
void func_selection_00408BEC();
void func_selection_004092F0();
void func_selection_004099A0();
void func_selection_00409C94();
void func_selection_00409EA4();
void func_selection_00409FC8();
void func_selection_0040A104();
void func_selection_0040A5E0();
void func_selection_0040A778();
void func_selection_0040A820();
void func_selection_0040B070();
void func_selection_0040B144();
void func_selection_0040B458();
void func_selection_0040B534();
void func_selection_0040B608();
void func_selection_0040B724();
void func_selection_0040B74C();
void func_selection_0040BB14();
void func_selection_0040BEC8();
void func_selection_0040BFD0();
void func_selection_0040BFFC();
void func_selection_0040C454();
void func_selection_0040C96C();
void func_selection_0040CA50();
void func_selection_0040CAB8();
void func_selection_0040CAE8();
void func_selection_0040CB18();
void func_selection_0040CB50();
void func_selection_0040CB74();
void func_selection_0040CB9C();
void func_selection_0040CBC4();
void func_selection_0040CBEC();
void func_selection_0040D134();
void func_selection_0040D234();
void func_selection_0040D25C();
void func_selection_0040D280();
void func_selection_0040D488();
void func_selection_0040D514();
void func_selection_0040D844();
void func_selection_0040D8B4();
void func_selection_0040D98C();
void func_selection_0040D9F8();
void func_selection_0040F0F8();
void func_selection_0040F248();
void func_selection_0040F294();
void func_selection_0040F430();
void func_selection_0040F4BC();
void func_selection_0040F64C();
void func_selection_0040F6E0();
void func_selection_0040F704();
void func_selection_0040F9EC();
void func_selection_0040FDB4();
void func_selection_004103CC();
void func_selection_0041057C();
void func_selection_00410614();
void func_selection_0041088C();
void func_selection_00410AA8();
void func_selection_00410BD0();
void func_selection_00410D20();
void func_selection_00410E78();
void func_selection_00411038();
void func_selection_004111B8();
void func_selection_00411204();
void func_selection_00411250();
void func_selection_0041129C();
void func_selection_004112D8();
void func_selection_00411324();
void func_selection_00411370();
void func_selection_004113BC();
void func_selection_00411408();
void func_selection_00411454();
void func_selection_004114A0();
void func_selection_004114DC();
void func_selection_00411528();
void func_selection_00411574();
void func_selection_004115C0();
void func_selection_0041162C();
void func_selection_004116E0();
void func_selection_00411870();
void func_selection_00411B9C();
void func_selection_00411F40();
void func_selection_004133E0();
void func_selection_00413418();
void func_selection_004134F4();
void func_selection_0041351C();
void func_selection_00413568();
void func_selection_00413594();
void func_selection_004136CC();
void func_selection_0041378C();
void func_selection_004137D0();
void func_selection_00413A88();
void func_selection_00413DE0();
void func_selection_00413E1C();
void func_selection_00413E48();
void func_selection_00413FC4();
void func_selection_004146C8();
void func_selection_00414CF4();
void func_selection_00415040();
void func_selection_0041532C();
void func_selection_004155A0();
void func_selection_004158DC();
void func_selection_004159FC();
void func_selection_00415A34();
void func_selection_00415AA0();
void func_selection_00415AD0();
void func_selection_00415B90();
void func_selection_00415BB8();
void func_selection_00415BE0();
void func_selection_00415C78();
void func_selection_00415CA0();
void func_selection_00415D48();
void func_selection_00415D9C();
void func_selection_00415DC4();
void func_selection_00415DEC();
void func_selection_00415E80();
void func_selection_00415EF4();
void func_selection_00415FB4();
void func_selection_00416028();
void func_selection_004162D4();
void func_selection_0041639C();
void func_selection_004166CC();
void func_selection_00416794();
void func_selection_004168C4();
void func_selection_00416A50();
void func_selection_00416ABC();
void func_selection_00416D94();
void func_selection_00416E78();
void func_selection_00416F28();
void func_selection_00416F54();
void func_selection_00416FF4();
void func_selection_00417240();
void func_selection_00417268();
void func_selection_004172B4();
void func_selection_004177A8();
void func_selection_004181D0();
void func_selection_0041844C();
void func_selection_00418800();
void func_selection_00418E98();
void func_selection_00419038();
void func_selection_00419084();
void func_selection_00419194();
void func_selection_00419384();
void func_selection_00419AA4();
void func_selection_00419B78();
void func_selection_00419B9C();
void func_selection_00419BC8();
void func_selection_00419D54();
void func_selection_00419FB8();
void func_selection_0041A0CC();
void func_selection_0041A210();
void func_selection_0041A244();
void func_selection_0041A5BC();
void func_selection_0041A7D0();
void func_selection_0041A960();
f32 func_selection_0041ABC8(s32 arg0, s32 arg1, s32 arg2);
void func_selection_0041ABFC();
void func_selection_0041B11C();
void func_selection_0041B15C();
void func_selection_0041B19C();
void func_selection_0041B28C();
void func_selection_0041B370();
extern s32 D_selection_00420E28;
extern s32 D_selection_0041F794;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/__entrypoint_func_selection_400000.s")

void func_selection_004000DC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004000E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004003DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00400580.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004008B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004015D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004016CC.s")

void func_selection_004017C8(void) {
}

void func_selection_004017D0(void) {
}

void func_selection_004017D8(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004017E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040189C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401964.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401A38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401B1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401BF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401D04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00401FB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402254.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402588.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402994.s")

void func_selection_00402D7C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402D84.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402E34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402E98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402F30.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402F80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00402FE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403050.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004030E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040319C.s")

void func_selection_004031E8(void) {
    func_selection_00415CA0(3);
    D_selection_00421CE0 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F904);
}

void func_selection_00403220(void) {
    D_selection_00421CE0 = 1;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FED0);
}

void func_selection_00403254(void) {
    D_selection_00421CE0 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F94C);
}

void func_selection_00403284(void) {
    func_selection_00415EF4();
    D_selection_00421CE0 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F994);
}

void func_selection_004032BC(void) {
    D_selection_00421CE0 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FB58);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004032EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403338.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040372C.s")

void func_selection_004037F4(void) {
    func_selection_00415DEC(0);
    gGameSettings->unk180 = 0;
    gGameSettings->unk184 = 3;
    func_selection_004038E0();
}

void func_selection_0040382C(void) {
    func_selection_00415DEC(1);
    gGameSettings->unk180 = 1;
    gGameSettings->unk184 = 4;
    func_selection_004038E0();
}

void func_selection_00403868(void) {
    func_selection_00415DEC(2);
    gGameSettings->unk180 = 2;
    gGameSettings->unk184 = 5;
    func_selection_004038E0();
}

void func_selection_004038A4(void) {
    func_selection_00415DEC(3);
    gGameSettings->unk180 = 3;
    gGameSettings->unk184 = 6;
    func_selection_004038E0();
}

void func_selection_004038E0(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FC80);
}

void func_selection_0040390C(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FF2C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403938.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004039B0.s")

void func_selection_00403A38(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FD74);
}

void func_selection_00403A64(void) {
    func_selection_00415CA0(4);
    D_selection_00421CE0 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FE04);
}

void func_selection_00403A9C(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F770);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403AC8.s")

void func_selection_00403B40(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_00420104);
}

void func_selection_00403B6C(void) {
    gNumPlayers = 2;
    func_selection_00415FB4(0);
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FFE4);
}

void func_selection_00403BAC(void) {
    gNumPlayers = 3;
    func_selection_00415FB4(1);
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FFE4);
}

void func_selection_00403BEC(void) {
    gNumPlayers = 4;
    func_selection_00415FB4(2);
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041FFE4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403C2C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403CA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403D24.s")

void func_selection_00403DA0(void) {
    func_selection_0040189C(&gOptionsStereoMono);
    gSndExports->unkF4(gOptionsStereoMono);
}

void func_selection_00403DE0(void) {
    func_selection_0040189C(&gOptionsSpeed);
}

void func_selection_00403E04(void) {
    func_selection_0040189C(&D_80025E6A);
}

void func_selection_00403E28(void) {
    func_selection_00401B1C(&gOptionsMap, 0, 2);
}

void func_selection_00403E54(void) {
    func_selection_0040189C(&gOptionsDisplay);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00403E78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040437C.s")

void func_selection_004045F4(void) {
    func_selection_00401964(&gCheatBattleNumLadybugs, 0, 7);
}

void func_selection_00404620(void) {
    func_selection_00401964(&gCheatBattleLadybugColor, 0, 3);
}

void func_selection_0040464C(void) {
    func_selection_00401964(&gCheatBattleHealth, 0, 3);
}

void func_selection_00404678(void) {
    func_selection_00401964(&gCheatBattlePowerups, 0, 8);
}

void func_selection_004046A4(void) {
    func_selection_00401964(&gCheatBattleTimeLimit, 0, 6);
}

void func_selection_004046D0(void) {
    func_selection_00401964(&gCheatBattleRadar, 0, 1);
}

void func_selection_004046FC(void) {
    func_selection_00401964(&gCheatBattleDamage, 0, 3);
}

void func_selection_00404728(void) {
    func_selection_00401964(&gCheatBattleMysteryBoxMode, 0, 3);
}

void func_selection_00404754(void) {
    func_selection_00401B1C(&gCheatTimeAttackBonusBoxes, 0, 1);
}

void func_selection_00404780(void) {
    func_selection_00401B1C(&gCheatBreakables, 0, 2);
}

void func_selection_004047AC(void) {
    func_selection_00401B1C(&gCheatEnvironment, 0, 2);
}

void func_selection_004047D8(void) {
    func_selection_00401B1C(&gCheatCars, 0, 6);
}

void func_selection_00404804(void) {
    func_selection_00401B1C(&gCheatPlayer2Handicap, 0, 4);
}

void func_selection_00404830(void) {
    func_selection_00401B1C(&gCheatColorChange, 0, 1);
}

void func_selection_0040485C(void) {
    func_selection_00401B1C(&gCheatFieldOfView, 0, 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00404888.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004048D8.s")

void func_selection_00404A8C(void) {
    func_selection_00401B1C(&gCheatHornSfxId, 0, gUvEmitterExports->unk7C());
}

void func_selection_00404ACC(void) {
    func_selection_00401B1C(&gCheatTrackMusic, 0, 1);
}

void func_selection_00404AF8(void) {
    func_selection_00401B1C(&gCheatHandbreakPower, 0, 2);
}

void func_selection_00404B24(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00404B2C.s")

void func_selection_00404C1C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00404C24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405078.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405140.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405644.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00405F48.s")

void func_selection_004060D4(void) {
    func_selection_0040189C((u8*)gGameSettings + (s32)D_selection_00420DF0 * 6 + 0x13C);
}

void func_selection_00406114(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040611C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040626C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004062F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406924.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406DC4.s")

void func_selection_00406F78(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00406F80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040705C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004078D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00407AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004080D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004081B4.s")

void func_selection_004082FC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00408304.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004083DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040884C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00408B24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00408BEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004092F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004099A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00409C94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00409EA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00409FC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A104.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A5E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A778.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040A820.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B070.s")

void func_selection_0040B13C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B144.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B458.s")

void func_selection_0040B52C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B534.s")

void func_selection_0040B600(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B608.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040B74C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040BB14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040BEC8.s")

void func_selection_0040BFD0(void) {
    func_selection_00401964(&D_80025E70, 0, 2);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040BFFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040C454.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040C96C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040CA50.s")

void func_selection_0040CAB8(void) {
    func_selection_00415E80(0);
    gNumAiCars = 7;
    func_selection_00403A38();
}

void func_selection_0040CAE8(void) {
    func_selection_00415E80(1);
    gNumAiCars = 1;
    func_selection_00403A38();
}

void func_selection_0040CB18(void) {
    func_selection_00415E80(2);
    gGameSettings->numAiCars = 0;
    gGameSettings->unk6F74 = 5;
    func_selection_004039B0();
}

void func_selection_0040CB50(void) {
    D_80025E70 = 0;
    func_selection_004039B0();
}

void func_selection_0040CB74(void) {
    D_80025E70 = 1;
    func_selection_004039B0();
}

void func_selection_0040CB9C(void) {
    D_80025E70 = 2;
    func_selection_004039B0();
}

void func_selection_0040CBC4(void) {
    D_80025E70 = 3;
    func_selection_004039B0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040CBEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D134.s")

void func_selection_0040D234(void) {
    ((u8*)&gTransmissionType)[D_selection_00420DF0 * 6] = 1;
}

void func_selection_0040D25C(void) {
    ((u8*)&gTransmissionType)[D_selection_00420DF0 * 6] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D280.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D488.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D514.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D844.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D8B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D98C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040D9F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F0F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F248.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F430.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F4BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F64C.s")

void func_selection_0040F6E0(void) {
    func_selection_0040F4BC(D_selection_00420DF0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F704.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040F9EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0040FDB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004103CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041057C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410614.s")

void func_selection_00410864(s16 a0, s16 a1) {
}

void func_selection_00410870(s16 a0, s16 a1) {
}

void func_selection_0041087C(void) {
}

void func_selection_00410884(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041088C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410AA8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410BD0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410D20.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00410E78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004111B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411204.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411250.s")

void func_selection_0041129C(s32 arg0) {
    func_selection_00410BD0(0x74, 0x80, 0x81);
    func_selection_00410E78(0x74, 0x81, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004112D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411324.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411370.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004113BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411408.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411454.s")

void func_selection_004114A0(s32 arg0) {
    func_selection_00410BD0(0xCA, 0xCD, 0x82);
    func_selection_00411038(0xCD, 0x82, arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004114DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411528.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411574.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004115C0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041162C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004116E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411870.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411B9C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00411F40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004133E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413418.s")

void func_selection_004134F4(void) {
    D_selection_00420DFC = 1;
    func_selection_004017E0();
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041351C.s")

void func_selection_00413568(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_00420218);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004136CC.s")

void func_selection_0041378C(void) {
    D_selection_00420DE8 = 2;
    D_selection_00420DEC = 0;
    D_8002CC84 = 0;
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F770);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004137D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413A88.s")

void func_selection_00413DE0(void) {
    gUvSprtExports->unk8(D_selection_00420DF8);
    D_selection_00420DF8 = -1;
}

void func_selection_00413E1C(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_00420074);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413E48.s")

void func_selection_00413FA4(void) {
}

void func_selection_00413FAC(void) {
}

void func_selection_00413FB4(void) {
}

void func_selection_00413FBC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00413FC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004146C8.s")

void func_selection_00414CEC(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00414CF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041532C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004155A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004158DC.s")

void func_selection_004159FC(void) {
    func_selection_00402E34();
    D_selection_00420DFC = 1;
    func_selection_00402E98(&D_selection_00420074);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415A34.s")

void func_selection_00415AA0(void) {
    if (gGameSettings->pad178[5] != 0) {
        gGameSettings->gameStateFlag = 2;
        return;
    }
    gGameSettings->gameStateFlag = 3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415AD0.s")

void func_selection_00415B90(void) {
    func_selection_00415AD0(0xBC, &D_selection_00420E90);
}

void func_selection_00415BB8(void) {
    func_selection_00415AD0(0xE4, &D_selection_00420E84);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415BE0.s")

void func_selection_00415C78(void) {
    func_selection_00415AD0(0x7B, &D_selection_00420E74);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415CA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415D48.s")

void func_selection_00415D9C(void) {
    func_selection_00415AD0(0xB5, &D_selection_00420E78);
}

void func_selection_00415DC4(void) {
    func_selection_00415AD0(0xB6, &D_selection_00420E70);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415DEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415E80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415EF4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00415FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416028.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004162D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041639C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004166CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416794.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004168C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416A50.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416ABC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416D94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416E78.s")

void func_selection_00416F28(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F728);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416F54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00416FF4.s")

void func_selection_00417240(void) {
    D_selection_00420E18 = *(s16*)((u8*)*(void**)((u8*)D_selection_00421D1C + 8) + 4);
    D_selection_00420E1C = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00417268.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004172B4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004177A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_004181D0.s")

void func_selection_0041843C(void) {
    D_selection_00420E28 = -1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041844C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00418800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00418E98.s")

void func_selection_00419020(void) {
    *(s16 *)((u8 *)&D_selection_0041F794 + 0x16) = 1;
    *(s16 *)((u8 *)&D_selection_0041F794 + 0x2A) = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419038.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419384.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419AA4.s")

void func_selection_00419B78(void) {
    D_selection_00421D28 = 0;
    func_selection_004017E0();
}

void func_selection_00419B9C(void) {
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_0041F5B4);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419BC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_00419FB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A0CC.s")

void func_selection_0041A208(void) {
}

void func_selection_0041A210(void) {
    func_selection_00415D9C();
    func_selection_00402E34();
    func_selection_00402E98(&D_selection_00420260);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A244.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A5BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A7D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041A960.s")

f32 func_selection_0041ABC8(s32 arg0, s32 arg1, s32 arg2) {
    return (f32) ((arg0 * 0x3C) + arg1) + ((f32) arg2 / 100.0f);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041ABFC.s")

void func_selection_0041B11C(void) {
    gGameSettings->unk174 = 1;
    gGameSettings->pad178[1] = 1;
    func_selection_00402E98(*(s32*)((u8*)D_selection_00421D1C + 4));
}

void func_selection_0041B15C(void) {
    gGameSettings->unk174 = 2;
    gGameSettings->pad178[1] = 1;
    func_selection_00402E98(*(s32*)((u8*)D_selection_00421D1C + 4));
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041B19C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041B28C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/selection/func_selection_0041B370.s")

