// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stdarg.h"

typedef enum ProfilerState_e {
    PROF_STATE_INT,
    PROF_STATE_NON_INT
} ProfilerState;

#define MAX_PROFILER_ENTRIES 40

typedef struct ProfilerEntry_s {
    /* 0x00 */ f64 unk0;                            /* inferred */
    /* 0x08 */ f64 unk8;
    /* 0x10 */ f64 unk10;
    /* 0x18 */ f64 unk18;                           /* inferred */
    /* 0x20 */ char* label;                           /* inferred */
    /* 0x24 */ s32 unk24;                           /* inferred */
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;                            /* inferred */
    /* 0x2A */ char pad2A[6];                       /* maybe part of unk29[7]? */
} ProfilerEntry;                               /* size = 0x30 */

// .data
u32 D_8001F770 = 1;
UNUSED s32 D_8001F774 = 0;
UNUSED s32 D_8001F778 = 0;
UNUSED s32 D_8001F77C = 0;
s32 gDebugProfilingState = PROF_STATE_INT;

// .bss
ProfilerEntry sProfilerEntries[MAX_PROFILER_ENTRIES];
s32 D_8002D930;

void uvProfilerSetPaused(s32, s32);                          /* extern */
void uvProfilerResetEntry(s32);                               /* extern */
void uvProfilerQueryStatistics(s32, ...);

s32 uvProfilerCreate(char* label) {
    ProfilerEntry* profilerEntry;
    s32 var_v1;
    s32 i;

    for (i = 0; i < MAX_PROFILER_ENTRIES; i++) {
        profilerEntry = &sProfilerEntries[i];
        if (profilerEntry->unk29 == 0) {
            profilerEntry->unk29 = 1;
            profilerEntry->label = label;
            return i;
        }
    }
    return -1;
}

void uvProfilerReset(s32 id) {
    uvProfilerResetEntry(id);
}

#line 59 "src/profiler.c"
/* Begin timing an unpaused profiler entry when profiling is enabled.
 * State 2 saves/disables interrupts on the outer begin and counts nested
 * begins; other enabled states only record the clock reading.
 * RE_UNKNOWN: complete numeric profiling-state configuration and caller
 * begin/end balancing contract; trace original settings and nested callers. */
void uvProfilerBegin(s32 entryId) {
    if (gDebugProfilingState == 0) {
        return;
    }

    if (sProfilerEntries[entryId].unk28 == 0) {
        sProfilerEntries[entryId].unk29 = 1;
        /* Preserve the original numeric state-2 interrupt-mask path. */
        if (gDebugProfilingState == 2) {
            if (D_8001F770 == 1) {
                D_8001F770 = osSetIntMask(OS_IM_NONE);
                D_8002D930 = 0;
            } else {
                D_8002D930++;
            }
        }
        sProfilerEntries[entryId].unk8 = uvClkGetSec(0x6B);

    }
}
#line 79 "src/profiler.c"

#line 80 "src/profiler.c"
/* End timing when enabled: unwind the shared interrupt-mask state first,
 * then record the elapsed value, count and accumulated time for an active
 * unpaused entry. Preserve the existing empty missing-start diagnostic branch.
 * RE_UNKNOWN: required pairing across nested and paused entries; resolve
 * original call sequences before changing the shared interrupt bookkeeping. */
void uvProfilerEnd(s32 entryId) {
    f64 endSec;
    f64 elapsedSec;
    f64 unusedTemporary;

    if (gDebugProfilingState == 0) {
        return;
    }

    endSec = uvClkGetSec(0x6B);
    if (D_8002D930 > 0) {
        D_8002D930 -= 1;
    } else if (D_8001F770 != 1) {
        osSetIntMask(D_8001F770);
        D_8001F770 = 1;
    }
    if (sProfilerEntries[entryId].unk28 == 0) {
        if (sProfilerEntries[entryId].unk8 == -1.0) {
            if (sProfilerEntries[entryId].label != NULL) {
            }
        } else {
            elapsedSec = endSec - sProfilerEntries[entryId].unk8;
            sProfilerEntries[entryId].unk8 = -1.0;
            sProfilerEntries[entryId].unk0 = elapsedSec;
            sProfilerEntries[entryId].unk24 += 1;
            sProfilerEntries[entryId].unk18 += elapsedSec;
        }
    }
}
#line 109 "src/profiler.c"

#line 110 "src/profiler.c"
/* Add a signed adjustment to the profiler entry count used by the statistics
 * query as the accumulated-time divisor. Preserve the unrestricted adjustment.
 * RE_UNKNOWN: caller reasons for changing this count independently of timing;
 * trace original references before imposing sample-count constraints. */
void uvProfilerAdjustSampleCount(s32 entryId, s32 countDelta) {
    sProfilerEntries[entryId].unk24 += countDelta;
}
#line 113 "src/profiler.c"

void uvProfilerResetEntry(s32 id) {
    sProfilerEntries[id].unk24 = 0;
    sProfilerEntries[id].unk28 = 0;
    sProfilerEntries[id].unk29 = 0;
    sProfilerEntries[id].label = NULL;
    sProfilerEntries[id].unk18 = 0.0;
    sProfilerEntries[id].unk0 = 0.0;
    sProfilerEntries[id].unk10 = 0.0;
    sProfilerEntries[id].unk8 = -1.0;
}

#line 125 "src/profiler.c"
/* Read variadic property/output-pointer pairs: 1 returns accumulated time
 * divided by count (zero when count is zero), 2 accumulated time, 3 the
 * latest elapsed time, and 4 the count as a u32. Property 0 or an unknown
 * code terminates the query. Preserve the existing argument types/order.
 * RE_UNKNOWN: complete external request protocol and valid entry IDs;
 * resolve original callers before changing termination or validation. */
void uvProfilerQueryStatistics(s32 entryId, ...) {
    ProfilerEntry *entry;
    f64 *averageOut;
    u32 property;
    s32* unusedPointer;
    va_list properties;

    entry = &sProfilerEntries[entryId];
    va_start(properties, entryId);
    while (TRUE) {
        property = va_arg(properties, int);
        switch (property) {
            case 0:
                break;
            case 1:
                averageOut = va_arg(properties, double*);
                if (entry->unk24 != 0) {
                    *averageOut = entry->unk18 / (f64) entry->unk24;
                } else {
                    *averageOut  = 0.0;
                }
                continue;
            case 2:
                *va_arg(properties, double*) = entry->unk18;
                continue;
            case 3:
                *va_arg(properties, double*) = entry->unk0;
                continue;
            case 4:
                *va_arg(properties, u32*) = entry->unk24;
               continue;
        }
        break;
    }
}
#line 160 "src/profiler.c"

void uvProfilerInit(void) {
    s32 i;

    if (D_8001F770 != 1) {
        osSetIntMask(D_8001F770);
        D_8001F770 = 1;
        D_8002D930 = 0;
    }
    for (i = 0; i < MAX_PROFILER_ENTRIES; i++) {
        uvProfilerResetEntry(i);
    }
    uvClkReset(0x6B);
}

void func_80001038(s32 id) {

}

#line 179 "src/profiler.c"
/* Pause an active timing interval by saving its pause time; resume by
 * advancing the start time by the paused duration. Store the requested
 * pause state even when no interval is active.
 * RE_UNKNOWN: caller input range; comparisons use the full s32 argument
 * while the stored pause field is u8. Trace callers before normalizing it. */
void uvProfilerSetPaused(s32 entryId, s32 paused) {
    f64 nowSec;
    s32 pad;

    if (sProfilerEntries[entryId].unk8 != -1.0) {
        if ((paused != 0) && (sProfilerEntries[entryId].unk28 == 0)) {
            nowSec = uvClkGetSec(0x6B);
            sProfilerEntries[entryId].unk10 = nowSec;

        }
        if ((paused == 0) && (sProfilerEntries[entryId].unk28 != 0)) {
            nowSec = uvClkGetSec(0x6B);
            sProfilerEntries[entryId].unk8 += nowSec - sProfilerEntries[entryId].unk10;
        }
    }
    sProfilerEntries[entryId].unk28 = paused;
}
#line 196 "src/profiler.c"

void func_80001104(void) {
}

#line 200 "src/profiler.c"
/* Apply the existing pause/resume helper to all forty profiler entries in
 * ascending order. Audio-manager processing brackets its work with this
 * helper, excluding that interval from active profiler timings. */
void uvProfilerSetAllPaused(s32 paused) {
    s32 entryId;

    for (entryId = 0; entryId < MAX_PROFILER_ENTRIES; entryId++) {
        uvProfilerSetPaused(entryId, paused);
    }
}
#line 207 "src/profiler.c"
