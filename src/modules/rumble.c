// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

void rumbleNoOpModuleCleanup(void);
void rumbleMergeQuantizedPatternValues(s32 controllerIndex, f32 patternLevel, f32 requestedActiveValue, f32 requestedDelayValue);
void rumbleUpdateControllerPatterns(void);

// .bss
s32 D_unused_rumble_00400450[2];
f32 D_rumble_00400458[4][8]; // Positive active values are eligible after the corresponding delay becomes negative.
f32 D_rumble_004004D8[4][8]; // Delay values decrease each enabled update; active values decrease only once delay is negative.
s32 D_rumble_00400558[4]; // Decremented every update; an inhibited controller requests reinitialization below zero and resets this to 30.
u8 D_rumble_00400568[4]; // Twelve-step pattern cursor, advanced before the enabled controller's motor lookup.

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
    exports->rumbleMergeQuantizedPatternValues = rumbleMergeQuantizedPatternValues;
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

#line 37 "src/modules/rumble.c"

/* Scale the supplied pattern level by seven, truncate to an integer and clamp
 * the resulting slot to 0..7. For an already-positive active value, retain the
 * smaller ordered delay value; otherwise replace its delay. Merge the active value
 * using the original ordered comparison, retaining the explicit self-stores.
 * RE_UNKNOWN: controller-index bounds, finite/representable level domain,
 * active/delay value units and alias/reentry guarantees. Trace original callers
 * and the shared update-step producer before changing conversions, comparisons,
 * table bounds or translating these values into elapsed time. */
void rumbleMergeQuantizedPatternValues(s32 controllerIndex, f32 patternLevel, f32 requestedActiveValue, f32 requestedDelayValue) {
    s32 patternIndex;

    patternLevel *= 7.0f;
    patternIndex = patternLevel;
    if (patternIndex < 0) {
        patternIndex = 0;
    } else if (patternIndex >= 8) {
        patternIndex = 7;
    }
    if (D_rumble_00400458[controllerIndex][patternIndex] > 0.0f) {
        if (D_rumble_004004D8[controllerIndex][patternIndex] < requestedDelayValue) {
            D_rumble_004004D8[controllerIndex][patternIndex] = D_rumble_004004D8[controllerIndex][patternIndex];
        } else {
            D_rumble_004004D8[controllerIndex][patternIndex] = requestedDelayValue;
        }
    } else {
        D_rumble_004004D8[controllerIndex][patternIndex] = requestedDelayValue;
    }
    if (requestedActiveValue < D_rumble_00400458[controllerIndex][patternIndex]) {
        D_rumble_00400458[controllerIndex][patternIndex] = D_rumble_00400458[controllerIndex][patternIndex];
        return;
    }
    D_rumble_00400458[controllerIndex][patternIndex] = requestedActiveValue;
}
#line 62 "src/modules/rumble.c"

#line 63 "src/modules/rumble.c"
#line 63 "src/modules/rumble.c"

/* Update four motor outputs from eight slots and a twelve-step byte pattern.
 * Inhibited controllers clear both value tables, request a motor stop and request
 * reinitialization after the update-count countdown becomes negative. Otherwise advance the
 * pattern cursor first, decrement every delay by the shared step and decrement
 * the active value only after its updated delay is negative. Choose the highest
 * eligible slot; slot zero is the all-zero fallback when no slot is eligible.
 * RE_UNKNOWN: shared step units/domain, extra inhibit field and per-controller
 * enable-byte lifecycle, plus callback/reentry guarantees. Trace original
 * settings writers, slot-request callers and motor callers before assigning
 * time units, replacing the float comparisons or changing update ordering. */
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
#line 113 "src/modules/rumble.c"
#line 108 "src/modules/rumble.c"

s32 D_00400440[] = { 0x000C0000, __entrypoint_func_rumble_400000, 0, 0 };