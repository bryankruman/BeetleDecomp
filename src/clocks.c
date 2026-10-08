// SPDX-License-Identifier: AGPL-3.0-or-later
#include "os.h"
#include "uv_clocks.h"
#include "macros.h"

// .bss
u32 sCpuLastCount;
s32 sWrapCount; // Counts the times the counter is wrapped
uvClockState_t D_8002D948[3];
uvClockState_t D_8002D960[8];

/* Need to make these arrays because the compiler doesn't want to put them before the stubbed string */
static const f64 D_80021030[1] = { 93.875101696 };
static const f64 sCpuClockSpeed[1] = { 45751932.2845432162 };

uvClockState_t *uvGetClk(s32 clk_id) {
    if (clk_id >= 100) {
        return &D_8002D960[clk_id - 100];
    }
    if (clk_id >= 3) {
        return NULL;
    }
    return &D_8002D948[clk_id];
}

void uvClkInit(void) {
    sCpuLastCount = osGetCount();
    sWrapCount = 0;
}

void uvClkUpdate(void) {
    u32 currentCount = osGetCount();
    if (((u32) sCpuLastCount >= 0xF0000001U) && (currentCount < 0x10000000U)) {
        sWrapCount++;
    }
    sCpuLastCount = currentCount;
}

/*
 * Look up the selected clock, update the shared counter and add the original
 * wrap-count and current-counter contributions using the unchanged constants.
 * A null clock still returns zero and keeps its optional debug-print branch.
 * RE_UNKNOWN: valid caller clock indices, update-frequency guarantees and the
 * historical calibration source. Trace clock allocation/reset/update callers and
 * original constant producers before changing bounds or elapsed-time semantics.
 */
#line 39 "src/clocks.c"
f64 uvClkGetSec(s32 clockId) {
    uvClockState_t *clockState;
    f64 wrapContribution;
    f64 counterContribution;

    clockState = uvGetClk(clockId);
    if (clockState == NULL) {
#ifdef _ISPRINT
        _uvDebugPrintf("uvClkGetSec: unknown clock %d\n", clockId);
#endif
        return 0.0;
    }
    uvClkUpdate();
    wrapContribution = sWrapCount - clockState->prevWrapCount;
    wrapContribution *= D_80021030[0];
    counterContribution = ((f64) sCpuLastCount - clockState->prevLastCount) / sCpuClockSpeed[0];
    return wrapContribution + counterContribution;
}
#line 57 "src/clocks.c"

void uvClkReset(s32 clk_id) {
    uvClockState_t *clock;

    uvClkUpdate();
    clock = uvGetClk(clk_id);
    if (clock != NULL) {
        clock->prevLastCount = sCpuLastCount;
        clock->prevWrapCount = sWrapCount;
    } else {
        PRINTF("Null free head\n");
    }
}
