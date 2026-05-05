// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

s32 func_800015D4(s32, s32);
s32 uvGetModuleFileId(s32);
void uvUnloadModule(s32);
void _uvScInitClientList(void);
void uvSysInit(void);

#pragma GLOBAL_ASM("asm/us/nonmatchings/1050/func_80000450.s")

#ifdef NEEDS_RODATA
void uvSetGameState(s32 gameStateId) {
    s32 temp_v0;
    s32 var_s0;
    s32 pad;
    f32 temp_fs0;

    if (gUvGfxMgrExports != NULL) {
        gUvGfxMgrExports->unk74();
        if (gCurrentGameState != -1) {
            gGameExports->unkC(gCurrentGameState);
        }
        temp_v0 = func_800015D4('UVMO', uvGetModuleFileId('MIDI'));
        for (var_s0 = 0; var_s0 < temp_v0; var_s0++) {
            uvUnloadModule('MIDI');
        }

        temp_v0 = func_800015D4('UVMO', uvGetModuleFileId('EMIT'));
        for (var_s0 = 0; var_s0 < temp_v0; var_s0++) {
            uvUnloadModule('EMIT');
        }

        temp_v0 = func_800015D4('UVMO', uvGetModuleFileId('AMGR'));
        var_s0 = 0;
        for (var_s0 = 0; var_s0 < temp_v0; var_s0++) {
            uvUnloadModule('AMGR');
        }
        gUvContExports->unk6C();
        _uvScInitClientList();

        temp_fs0 = uvClkGetSec(0x6A);

        while (temp_fs0 + 0.2f < uvClkGetSec(0x6A)) {
        }

    }
    gCurrentGameState = gameStateId;
    gGameStateFlag = -1;
    uvSysInit();
    gSkidExports = 0;
    gSprayExports = 0;
    gGlareExports = 0;
    gAiExports = 0;
    gFlagExports = 0;
    gTdataExports = 0;
    gVolTestExports = 0;
    gBattleExports = 0;
    gPowerupExports = 0;
    gLetterExports = 0; // Ladybug pickups
    gWeaponExports = 0;
    gRainExports = 0;   // Snow effect in Mount Mayhem
    gRumbleExports = 0;
    gGameExports = uvLoadModule('game');
    gGameExports->unk8(gameStateId);
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/1050/uvSetGameState.s")
#endif

// Displays error message and loops forever when no controllers are connected
void uvShowNoController(void) {
    s32 i;
    s32 line;
    s32 s4;
    s32 s3;
    func_800019B8('UVFT', 1);
    while (1) {
        gUvFontExports->uvSetFont(5); // font ID
        gUvFontExports->uvFontColor(0, 100, 200, 255); // RGBA color
        gUvGfxMgrExports->func_uvgfxmgr_rom_004007F8();
        gUvGfxMgrExports->func_uvgfxmgr_rom_00401BD4(0, 0x13F, 0, 0xEF);  // bg size?
        gUvGfxMgrExports->func_uvgfxmgr_rom_00401788(0, 0, 0);            // black BG color

        for (line = 0; line < 4; line++) {
            // clang-format off
            gUvFontExports->uvFontPrintStr(160 - (gUvFontExports->uvFontWidth(gNoControllerStrings[line]) / 2), 150 - line * 20,
                              gNoControllerStrings[line]);
            // clang-format on
        }

        gUvFontExports->uvFontGenDList();
        gUvGfxMgrExports->func_uvgfxmgr_rom_00400B24();
    }
}
