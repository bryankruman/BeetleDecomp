// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"
typedef struct { char pad0[0xC]; void (*unkC)(void *); char pad10[0x18]; void (*unk28)(void *, s32, s32); } GameguiGuiExports;
extern GameguiGuiExports *gUvGuiExports;
typedef struct { char pad[0x34]; void (*unk34)(u16); void (*unk38)(s32); } GameguiSndExports;
extern GameguiSndExports *gSndExports;
typedef struct { char pad[0x2C]; void (*unk2C)(void); } GameguiCmidiExports;
extern GameguiCmidiExports *gUvCmidiExports;
typedef struct { char pad[0x80]; void (*unk80)(void); } GameguiEmitterExports;
extern GameguiEmitterExports *gUvEmitterExports;
typedef struct { char pad[0x40]; void (*unk40)(void); } GameguiAudiomgrExports;
extern GameguiAudiomgrExports *gUvAudiomgrExports;
typedef struct { char pad[0x18]; void (*unk18)(s32); } GameguiDebugExports;
extern GameguiDebugExports *gUvDebugExports;
extern s32 D_debugEnable;
extern u8 D_gamegui_00402C68;
extern u8 D_gamegui_00402C78;
extern s32 D_gamegui_00402D04;
extern u16 D_gamegui_00402D16;
extern s32 D_gamegui_00402D28;
void func_gamegui_004000B0();
void func_gamegui_00400194();
void func_gamegui_00400370();
void func_gamegui_004014F8();
void func_gamegui_00401748();
void func_gamegui_00401A7C();
void func_gamegui_00401AD8();
void func_gamegui_00401AF8();
void func_gamegui_00401D34();
void func_gamegui_00401D94();
void func_gamegui_00401DC4();
void func_gamegui_00401DF4();
void func_gamegui_00401E24();
void func_gamegui_00401E50();
void func_gamegui_00401E7C();
void func_gamegui_00401FE0();
void func_gamegui_00402030();
void func_gamegui_0040203C();
void func_gamegui_00402074();
void func_gamegui_00402088();
void func_gamegui_0040209C();
void func_gamegui_004020BC();
void func_gamegui_004020DC();
void func_gamegui_00402110();
void func_gamegui_00402130();
void func_gamegui_00402144();
void func_gamegui_00402158();
void func_gamegui_0040216C();
void func_gamegui_00402180();
void func_gamegui_0040219C();
void func_gamegui_004021DC();
void func_gamegui_00402358();
u8 func_gamegui_004023B0();
void func_gamegui_004023BC();
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/__entrypoint_func_gamegui_400000.s")

void func_gamegui_004000A8(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004000B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00400194.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00400370.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004014F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401748.s")

void func_gamegui_00401A7C(void) {
    if (D_gamegui_00402C68 != 0) {
        gUvGuiExports->unkC(&D_gamegui_00402C78);
        return;
    }
    gUvFontExports->uvFontGenDList();
}

void func_gamegui_00401AD8(s32 arg0) {
    if (D_debugEnable != 0) {
        D_gamegui_00402C68 = (u8)arg0;
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401AF8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401D34.s")

void func_gamegui_00401D94(s32 arg0) {
    gUvCmidiExports->unk2C();
}

void func_gamegui_00401DC4(s32 arg0) {
    gUvEmitterExports->unk80();
}

void func_gamegui_00401DF4(s32 arg0) {
    gUvAudiomgrExports->unk40();
}

void func_gamegui_00401E24(s32 arg0) {
    if (gGameSettings[0].numPlayers >= 2) {
        gGameSettings[0].numAiCars = 0;
    }
    gGameSettings[0].gameStateFlag = 5;
}

void func_gamegui_00401E50(s32 arg0) {
    if (gGameSettings[0].numPlayers < 2) {
        gGameSettings[0].numPlayers = 2;
    }
    gGameSettings[0].gameStateFlag = 6;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00401E7C.s")

void func_gamegui_00401FE0(void) {
    gUvGuiExports->unk28(&D_gamegui_00402C78, -1, 3);
    gUvDebugExports->unk18(3);
}

void func_gamegui_00402030(s32 arg0) {
    D_gamegui_00402D04 = arg0;
}

void func_gamegui_0040203C(s32 arg0) {
    if (arg0 == D_gamegui_00402D28) {
        *(s32 *)&gGameSettings[0].padE0[0] = 1;
    } else {
        *(s32 *)&gGameSettings[0].padE0[0] = 0;
    }
    gGameSettings[0].gameStateFlag = 9;
}

void func_gamegui_00402074(s32 arg0) {
    gGameStateFlag = 8;
}

void func_gamegui_00402088(s32 arg0) {
    gGameStateFlag = 0xB;
}

void func_gamegui_0040209C(s32 arg0) {
    gGameSettings[0].gameStateFlag = 3;
    gGameSettings[0].unkC = 2;
}

void func_gamegui_004020BC(s32 arg0) {
    gGameSettings[0].gameStateFlag = 4;
    gGameSettings[0].unkC = 2;
}

void func_gamegui_004020DC(s32 arg0) {
    gGameSettings[0].gameStateFlag = 2;
    gGameSettings[0].currentTrack = 0x1B;
    gGameSettings[0].finishedIntroCount = 0;
    gGameSettings[0].unkC = 1;
    gGameSettings[0].pad178[5] = 1;
}

void func_gamegui_00402110(s32 arg0) {
    gGameSettings[0].gameStateFlag = 7;
    gGameSettings[0].currentTrack = 0x21;
}

void func_gamegui_00402130(s32 arg0) {
    gGameStateFlag = 0xA;
}

void func_gamegui_00402144(s32 arg0) {
    gGameStateFlag = 0xC;
}

void func_gamegui_00402158(s32 arg0) {
    gGameStateFlag = 0xD;
}

void func_gamegui_0040216C(s32 arg0) {
    gGameStateFlag = 0xE;
}

void func_gamegui_00402180(s32 arg0) {
    gGameStateFlag = 0xF;
}

void func_gamegui_00402194(void) {
}

void func_gamegui_0040219C(s32 arg0) {
    if (gGameSettings[0].introReplayState != 0) {
        gGameSettings[0].introReplayState = 0;
        return;
    }
    gGameSettings[0].introReplayState = 1;
    gGameSettings[0].gameStateFlag = gGameSettings[0].currentGameState;
}

void func_gamegui_004021D4(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004021DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_00402358.s")

u8 func_gamegui_004023B0(void) {
    return D_gamegui_00402C68;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/gamegui/func_gamegui_004023BC.s")

