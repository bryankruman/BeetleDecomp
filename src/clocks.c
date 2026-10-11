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

/* Select the secondary clock array for signed IDs at least 100; otherwise
 * reject IDs at least three and index the primary array. Preserve the absence
 * of a negative-ID guard and secondary upper bound. RE_UNKNOWN: callers must
 * establish valid indices and clock storage ownership. */
#line 16 "src/clocks.c"
uvClockState_t *uvGetClk(s32 clk_id) {
    if (clk_id >= 100) {
        return &D_8002D960[clk_id - 100];
    }
    if (clk_id >= 3) {
        return NULL;
    }
    return &D_8002D948[clk_id];
}

/* Seed the last CPU count from osGetCount and clear the wrap counter.
 * RE_UNKNOWN: ordering against readers and the permitted initialization phase
 * remain caller responsibilities; this function adds no synchronization. */
#line 26 "src/clocks.c"
void uvClkInit(void) {
    sCpuLastCount = osGetCount();
    sWrapCount = 0;
}

/* Sample the CPU count once. Increment the wrap counter only when the prior
 * unsigned count is at least 0xF0000001 and the new count is below 0x10000000,
 * then store the new count. RE_UNKNOWN: this heuristic's sampling interval and
 * synchronization requirements are not established by the function. */
#line 31 "src/clocks.c"
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

/* Update the shared count sample, select the requested clock, and copy the
 * last-count and wrap snapshots when lookup succeeds. Preserve the source's
 * diagnostic-only failure branch. RE_UNKNOWN: valid ID bounds and concurrent
 * readers require caller evidence. */
#line 58 "src/clocks.c"
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
