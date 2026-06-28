// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 gGameStateFlag;
typedef struct MenuNode_s { s32 unk0; void *unk4; void *unk8; } MenuNode;
extern MenuNode *D_pause_00405E50;
extern MenuNode D_pause_00405618;
extern MenuNode D_pause_00405AA0;
extern MenuNode D_pause_004055BC;
extern MenuNode D_pause_00405950;
typedef struct { char pad0[0x34]; void (*unk34)(void *, s32, s32, s32, void *); } UnkStruct_pause_E44;
extern UnkStruct_pause_E44 *D_pause_00405E44;
typedef struct { s32 unk0; s32 unk4; void (*unk8)(s32); } UnkStruct_pause_E48;
extern UnkStruct_pause_E48 *D_pause_00405E48;
typedef struct { char pad0[0xF4]; void (*unkF4)(s32); } UnkStruct_pause_SndExports;
extern UnkStruct_pause_SndExports *gSndExports;
typedef struct { char pad0[0xC]; void (*unkC)(s32); } UnkStruct_pause_ReplayExports;
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
void func_pause_00400164();
void func_pause_004001F0();
void func_pause_00400258();
void func_pause_004003B8();
void func_pause_00400428();
void func_pause_0040048C();
void func_pause_00400544();
void func_pause_004006E4();
void func_pause_00400750();
void func_pause_0040092C();
void func_pause_0040098C();
void func_pause_00400C74();
void func_pause_00400CB0();
void func_pause_00400CE0();
void func_pause_00400D10();
void func_pause_00400D40();
void func_pause_00400DA8(void);
void func_pause_00400DB8();
void func_pause_00400E48();
void func_pause_00400EEC();
void func_pause_0040197C();
void func_pause_004020F0();
void func_pause_004021BC();
void func_pause_00402268();
void func_pause_004022B0();
void func_pause_004022F8();
void func_pause_00402340();
void func_pause_00402380();
void func_pause_004023A4();
void func_pause_004023C8();
void func_pause_0040244C();
void func_pause_00402470();
void func_pause_00402550();
void func_pause_004025B4();
void func_pause_00402600();
void func_pause_00402630();
void func_pause_0040264C();
void func_pause_004026A8();
void func_pause_004026C4();
void func_pause_00402854();
void func_pause_00402904();
void func_pause_00402914();
void func_pause_00402D78();
void func_pause_00403E6C();
void func_pause_00403EF0();
void func_pause_00403F60();
void func_pause_00403FD0();
void func_pause_00404150();
void func_pause_00404160();
void func_pause_004041A0();
void func_pause_0040423C();
void func_pause_00404574();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/__entrypoint_func_pause_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400164.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004001F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004003B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400428.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040048C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400544.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004006E4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040092C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040098C.s")

void func_pause_00400C6C(void) {
}

void func_pause_00400C74(void) {
    gReplayExports->unkC(D_80025D76 == 0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400CB0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400CE0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400D10.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400D40.s")

void func_pause_00400DA8(void) {
    gGameStateFlag = 0xE;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400DB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400E48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00400EEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040197C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004020F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004021BC.s")

void func_pause_00402268(void) {
    D_pause_00405E44->unk34(&gOptionsSpeechVol, 8, 1, 0, D_pause_00405E50);
}

void func_pause_004022B0(void) {
    D_pause_00405E44->unk34(&gOptionsSfxVol, 8, 1, 1, D_pause_00405E50);
}

void func_pause_004022F8(void) {
    D_pause_00405E44->unk34(&gOptionsMusicVol, 8, 1, 2, D_pause_00405E50);
}

void func_pause_00402340(void) {
    func_pause_00400428(&gOptionsStereoMono);
    gSndExports->unkF4(gOptionsStereoMono);
}

void func_pause_00402380(void) {
    func_pause_00400428(&gOptionsSpeed);
}

void func_pause_004023A4(void) {
    func_pause_00400428(&D_80025E6A);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004023C8.s")

void func_pause_0040244C(void) {
    func_pause_00400428(&gOptionsDisplay);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402470.s")

void func_pause_00402548(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402550.s")

void func_pause_004025B4(void) {
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D0) = gGameSettings->optionsMusicVol;
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D4) = gGameSettings->optionsSfxVol;
    *(s32 *)((u8 *)&D_8002CD98 + 0x2D8) = gGameSettings->optionsSpeechVol;
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DC) = gGameSettings->pad178[0];
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DD) = gGameSettings->pad178[1];
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DE) = gGameSettings->pad178[3];
    *(u8 *)((u8 *)&D_8002CD98 + 0x2DF) = gGameSettings->pad178[4];
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402600.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402630.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040264C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004026A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004026C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402854.s")

void func_pause_00402904(void) {
    D_8002CC88 = 1;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402914.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00402D78.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00403E6C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00403EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00403F60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00403FD0.s")

void func_pause_00404150(void) {
    D_8002CC88 = 8;
}

void func_pause_00404160(void) {
    *(s16 *)((u8 *)gGameSettings + 0x6F98) = 0;
    *(s16 *)((u8 *)gGameSettings + 0x6F96) = 0;
    D_pause_00405E48->unk8(8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_004041A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_0040423C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/pause/func_pause_00404574.s")

