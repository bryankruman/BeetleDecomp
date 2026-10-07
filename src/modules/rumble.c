// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void rumbleNoOpModuleCleanup(void);
void func_rumble_00400050(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void rumbleUpdateControllerPatterns(void);

// .bss
s32 D_unused_rumble_00400450[2];
f32 D_rumble_00400458[4][8];
f32 D_rumble_004004D8[4][8];
s32 D_rumble_00400558[4];
u8 D_rumble_00400568[4];

// .data
u8 D_rumble_004003E0[8][12] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, { 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 },
    { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};

void __entrypoint_func_rumble_400000(Rumble_Exports *exports);

void __entrypoint_func_rumble_400000(Rumble_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->rumbleNoOpModuleCleanup = rumbleNoOpModuleCleanup;
    exports->func_rumble_00400050 = func_rumble_00400050;
    exports->rumbleUpdateControllerPatterns = rumbleUpdateControllerPatterns;
}

#line 34 "src/modules/rumble.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void rumbleNoOpModuleCleanup(void) {
}
#line 36 "src/modules/rumble.c"

void func_rumble_00400050(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 idx;

    arg1 *= 7.0f;
    idx = arg1;
    if (idx < 0) {
        idx = 0;
    } else if (idx >= 8) {
        idx = 7;
    }
    if (D_rumble_00400458[arg0][idx] > 0.0f) {
        if (D_rumble_004004D8[arg0][idx] < arg3) {
            D_rumble_004004D8[arg0][idx] = D_rumble_004004D8[arg0][idx];
        } else {
            D_rumble_004004D8[arg0][idx] = arg3;
        }
    } else {
        D_rumble_004004D8[arg0][idx] = arg3;
    }
    if (arg2 < D_rumble_00400458[arg0][idx]) {
        D_rumble_00400458[arg0][idx] = D_rumble_00400458[arg0][idx];
        return;
    }
    D_rumble_00400458[arg0][idx] = arg2;
}

#line 63 "src/modules/rumble.c"
/* Update four controller rumble outputs from eight timed patterns.
 * When inhibited, clear pattern timing, stop rumble and periodically
 * reinitialize the controller; otherwise advance the twelve-step pattern
 * and use the highest eligible pattern index. RE_UNKNOWN: the additional
 * shared inhibit field and per-controller enable words retain their original roles. */
void rumbleUpdateControllerPatterns(void) {
    s32 stopRumble;
    s32 selectedPattern;
    s32 controllerIndex;
    s32 patternIndex;

    for (controllerIndex = 0; controllerIndex < 4; controllerIndex++) {
        D_rumble_00400558[controllerIndex]--;
    }

    stopRumble = gGameSettings->pauseFlag || gGameSettings->unk6E9C || gGameSettings->introReplayState
                 || ((gGameSettings->currentGameState != RACE) && (gGameSettings->currentGameState != BATTLE));

    for (controllerIndex = 0; controllerIndex < 4; controllerIndex++) {
        if ((stopRumble) || ((gGameSettings->unk98[controllerIndex] == 0))) {
            for (patternIndex = 0; patternIndex < 8; patternIndex++) {
                D_rumble_00400458[controllerIndex][patternIndex] = 0.0f;
                D_rumble_004004D8[controllerIndex][patternIndex] = 0.0f;
            }

            gUvContExports->uvControllerStopRumblePak(controllerIndex);
            if (D_rumble_00400558[controllerIndex] < 0) {
                gUvContExports->uvControllerReinitializeAndStopRumble(controllerIndex);
                D_rumble_00400558[controllerIndex] = 0x1E;
            }
            continue;
        }
        D_rumble_00400568[controllerIndex] = ((s32) (D_rumble_00400568[controllerIndex] + 1) % 12);
        selectedPattern = 0;
        for (patternIndex = 0; patternIndex < 8; patternIndex++) {
            D_rumble_004004D8[controllerIndex][patternIndex] -= gGameSettings->unk80;
            if (D_rumble_004004D8[controllerIndex][patternIndex] < 0.0f) {
                D_rumble_00400458[controllerIndex][patternIndex] -= gGameSettings->unk80;
            }
            if ((D_rumble_00400458[controllerIndex][patternIndex] > 0.0f) && (D_rumble_004004D8[controllerIndex][patternIndex] < 0.0f)) {
                selectedPattern = patternIndex;
            }
        }
        if (D_rumble_004003E0[selectedPattern][D_rumble_00400568[controllerIndex]] != 0) {
            gUvContExports->uvControllerStartRumblePak(controllerIndex);
        } else {
            gUvContExports->uvControllerStopRumblePak(controllerIndex);
        }
    }
}
#line 108 "src/modules/rumble.c"

s32 D_00400440[] = { 0x000C0000, __entrypoint_func_rumble_400000, 0, 0 };