// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvfmtx_rom.h"
#include "uvgfxmgr_rom.h"
#include "uvstring_rom.h"

typedef struct {
    f64 unk0;
    s32 unk8;
    u8 padC[4];
} Entry;

typedef struct {
    Entry entry[30];
} Unk802B92A0;

typedef struct UnkStruct_00402FB8_s {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} UnkStruct_00402FB8;

typedef struct UnusedDebugStrings1_s {
    const char *dbgStrings[6];
} UnusedDebugStrings1;

typedef struct KernelDbgInfo_s {
    u8 *code;
    s32 codeSize;
    s32 form0Size;
    s32 formFilesSize;
    s32 unk10;
    s32 unk14;
} KernelDbgInfo;

typedef struct UnkStruct_00402F34_s {
    const char *unk0;
    const char *unk4;
    const char *unk8;
    const char *unkC[2];
    const char *unk14;
    const char *unk18;
} UnkStruct_00402F34;

typedef struct UnkStruct_UvDbg_Rom_00402128_s {
    s32 unk0;
    s32 unk4;
    s32 audioHeapSize;
    s32 unkC[2];
    s32 unk14;
    s32 unk18;
} UnkStruct_UvDbg_Rom_00402128;

// .bss
extern UvFMtx_Rom_Exports *D_uvdbg_rom_00402FF4;
extern UvGfxMgr_Exports *D_uvdbg_rom_00402FE8;
extern UvString_Exports *D_uvdbg_rom_00402FDC;
extern UvGeom_Exports *D_uvdbg_rom_00402FEC;
extern UvChannel_Exports *D_uvdbg_rom_00402FF8;
extern UvCback_Exports *D_uvdbg_rom_00402FFC;
extern f32 D_uvdbg_rom_00402F70;
extern f32 D_uvdbg_rom_00402F74;
extern f32 D_uvdbg_rom_00402F78;
extern f32 D_uvdbg_rom_00402F7C;
extern f32 D_uvdbg_rom_00402F80;
extern f32 D_uvdbg_rom_00402F84;
extern f32 D_uvdbg_rom_00402F88;
extern f32 D_uvdbg_rom_00402F8C;
extern f32 D_uvdbg_rom_00402F90;
extern f32 D_uvdbg_rom_00402F94;
extern f32 D_uvdbg_rom_00402F98;
extern f32 D_uvdbg_rom_00402F9C;
extern f32 D_uvdbg_rom_00402FA0;
extern f32 D_uvdbg_rom_00402FA4;
extern f32 D_uvdbg_rom_00402FA8;
extern f32 D_uvdbg_rom_00402FAC;
extern f32 D_uvdbg_rom_00402FB0;
extern f32 D_uvdbg_rom_00402FB4;
extern UvFont_Exports *D_uvdbg_rom_00402FD8;
extern UvGfxState_Rom_Exports *D_uvdbg_rom_00402FE4;
extern UvAudioMgr_Exports* D_uvdbg_rom_00402FE0;
extern UnkStruct_00402FB8 D_uvdbg_rom_00402FB8[2];
extern UvCont_Exports*D_uvdbg_rom_00402FF0;

// External variables
extern u8 gMemBlock[];
extern Unk802B92A0 D_8002E440[];
extern Unk802B92A0 D_8002DAE0[];
extern s32 D_8002EDB8[];
extern f64 D_8002EDD0[];
extern s32 D_8002EDA0[];
extern s32 *gModuleNameTags;

void __entrypoint_func_uvdbg_rom_400318(UvDbgRom_Exports *);
void func_uvdbg_rom_004014E4(void);
void uvDbgStampProfileSlot00(s32 arg0);
void uvDbgStampProfileSlot01(s32 arg0);
void uvDbgStampProfileSlot02(s32 arg0);
void uvDbgStampProfileSlot03(s32 arg0);
void uvDbgStampProfileSlot04(s32 arg0);
void uvDbgStampProfileSlot05(s32 arg0);
void uvDbgStampProfileSlot06(s32 arg0);
void uvDbgStampProfileSlot07(s32 arg0);
void uvDbgStampProfileSlot08(s32 arg0);
void uvDbgStampProfileSlot09(s32 arg0);
void uvDbgStampProfileSlot10(s32 arg0);
void uvDbgStampProfileSlot11(s32 arg0);
void uvDbgStampProfileSlot12(s32 arg0);
void uvDbgStampProfileSlot13(s32 arg0);
void uvDbgStampProfileSlot14(s32 arg0);
void uvDbgStampProfileSlot15(s32 arg0);
void uvDbgStampProfileSlot16(s32 arg0);
void uvDbgStampProfileSlot17(s32 arg0);
void uvDbgModuleCleanup(void);
f64 uvDbgGetAdjacentFrameInterval(void);
f64 uvDbgGetTaskCompletionInterval(void);
f64 uvDbgGetTask29To2CInterval(void);
f64 uvDbgGetSecondaryTask29To2CInterval(void);
f64 uvDbgGetSecondaryTask2ATo2BInterval(void);
void uvDbgDrawTimeIntervalBar(f32 arg0, f32 arg1, s16 arg2, u8 arg3, u8 arg4, u8 arg5);
void func_uvdbg_rom_00400D74(s32 arg0);
void func_uvdbg_rom_00400E74(u8 arg0, u8 arg1);
void uvDbgReservedMemoryCallback(u8 arg0);
void uvDbgReservedModeCallback(u8 arg0, u8 arg1);
void uvDbgPrintGraphicsCounterRow(const char *arg0, s32 arg1, s32 *arg2, s32 arg3);
void uvDbgDrawSelectedGraphicsCounters(s32 arg0);
void uvDbgReservedCounterCallback(void);
void func_uvdbg_rom_004014E4(void);
void uvDbgReservedTimingCallback(void);
void func_uvdbg_rom_004017A8(s32 arg0, s32 arg1, u16 arg2, u8 arg3, u8 arg4, u8 arg5);
void uvDbgDrawDefaultTaskIntervals(void);
void uvDbgDrawTimingOverlay(u8 arg0);
void uvDbgDispatchTimingOverlay(u8 arg0, u8 arg1, u8 arg2);
void uvDbgDispatchCounterOverlay(s32 arg0, s32 arg1);
void func_uvdbg_rom_00401DE8(s32 arg0);
void func_uvdbg_rom_00402128(void);
void func_uvdbg_rom_00402490(void);
void uvDbgClearWordByIndex(s32 arg0);
void uvDbgPrintScalarRow(const char *arg0, f32 arg1, s32 *arg2);
void func_uvdbg_rom_0040262C(void);
void uvDbgSetFontId(s32 arg0);
void uvDbgResetDisplayFlags(void);
void func_uvdbg_rom_00402A14(s32 arg0);
void uvDbgDispatchMemoryOverlay(u8 arg0, u8 arg1);
void uvDbgDrawResourceStatistics(void);

//.data
s32 D_uvdbg_rom_00402F30 = 0;

static const char sDevStr[] = { "start: %f  (%d)   finish: %f (%d)\n" };

void func_uvdbg_rom_004017A8(s32 arg0, s32 arg1, u16 arg2, u8 arg3, u8 arg4, u8 arg5);

#line 156 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 0.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot00(s32 unused) {
    D_uvdbg_rom_00402F70 = (f32) uvClkGetSec(0);
}
#line 159 "src/modules/uvdbg_rom.c"

#line 160 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 1.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot01(s32 unused) {
    D_uvdbg_rom_00402F74 = (f32) uvClkGetSec(0);
}
#line 163 "src/modules/uvdbg_rom.c"

#line 164 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 2.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot02(s32 unused) {
    D_uvdbg_rom_00402F78 = (f32) uvClkGetSec(0);
}
#line 167 "src/modules/uvdbg_rom.c"

#line 168 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 3.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot03(s32 unused) {
    D_uvdbg_rom_00402F7C = (f32) uvClkGetSec(0);
}
#line 171 "src/modules/uvdbg_rom.c"

#line 172 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 4.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot04(s32 unused) {
    D_uvdbg_rom_00402F80 = (f32) uvClkGetSec(0);
}
#line 175 "src/modules/uvdbg_rom.c"

#line 176 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 5.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot05(s32 unused) {
    D_uvdbg_rom_00402F84 = (f32) uvClkGetSec(0);
}
#line 179 "src/modules/uvdbg_rom.c"

#line 180 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 6.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot06(s32 unused) {
    D_uvdbg_rom_00402F88 = (f32) uvClkGetSec(0);
}
#line 183 "src/modules/uvdbg_rom.c"

#line 184 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 7.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot07(s32 unused) {
    D_uvdbg_rom_00402F8C = (f32) uvClkGetSec(0);
}
#line 187 "src/modules/uvdbg_rom.c"

#line 188 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 8.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot08(s32 unused) {
    D_uvdbg_rom_00402F90 = (f32) uvClkGetSec(0);
}
#line 191 "src/modules/uvdbg_rom.c"

#line 192 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 9.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot09(s32 unused) {
    D_uvdbg_rom_00402F94 = (f32) uvClkGetSec(0);
}
#line 195 "src/modules/uvdbg_rom.c"

#line 196 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 10.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot10(s32 unused) {
    D_uvdbg_rom_00402F98 = (f32) uvClkGetSec(0);
}
#line 199 "src/modules/uvdbg_rom.c"

#line 200 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 11.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot11(s32 unused) {
    D_uvdbg_rom_00402F9C = (f32) uvClkGetSec(0);
}
#line 203 "src/modules/uvdbg_rom.c"

#line 204 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 12.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot12(s32 unused) {
    D_uvdbg_rom_00402FA0 = (f32) uvClkGetSec(0);
}
#line 207 "src/modules/uvdbg_rom.c"

#line 208 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 13.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot13(s32 unused) {
    D_uvdbg_rom_00402FA4 = (f32) uvClkGetSec(0);
}
#line 211 "src/modules/uvdbg_rom.c"

#line 212 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 14.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot14(s32 unused) {
    D_uvdbg_rom_00402FA8 = (f32) uvClkGetSec(0);
}
#line 215 "src/modules/uvdbg_rom.c"

#line 216 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 15.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot15(s32 unused) {
    D_uvdbg_rom_00402FAC = (f32) uvClkGetSec(0);
}
#line 219 "src/modules/uvdbg_rom.c"

#line 220 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 16.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot16(s32 unused) {
    D_uvdbg_rom_00402FB0 = (f32) uvClkGetSec(0);
}
#line 223 "src/modules/uvdbg_rom.c"

#line 224 "src/modules/uvdbg_rom.c"
/* Store clock-zero seconds, narrowed to float, in profiling timestamp slot 17.
 * The incoming argument is unused; the slot purpose is not guessed. */
void uvDbgStampProfileSlot17(s32 unused) {
    D_uvdbg_rom_00402FB4 = (f32) uvClkGetSec(0);
}
#line 227 "src/modules/uvdbg_rom.c"

void __entrypoint_func_uvdbg_rom_400318(UvDbgRom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvDbgModuleCleanup = uvDbgModuleCleanup;
    exports->uvDbgDrawResourceStatistics = uvDbgDrawResourceStatistics;
    exports->uvDbgDispatchTimingOverlay = uvDbgDispatchTimingOverlay;
    exports->uvDbgDispatchCounterOverlay = uvDbgDispatchCounterOverlay;
    exports->func_uvdbg_rom_00401DE8 = func_uvdbg_rom_00401DE8;
    exports->func_uvdbg_rom_00402128 = func_uvdbg_rom_00402128;
    exports->func_uvdbg_rom_00402490 = func_uvdbg_rom_00402490;
    exports->uvDbgSetFontId = uvDbgSetFontId;
    exports->uvDbgResetDisplayFlags = uvDbgResetDisplayFlags;
    exports->func_uvdbg_rom_00402A14 = func_uvdbg_rom_00402A14;
    exports->uvDbgDispatchMemoryOverlay = uvDbgDispatchMemoryOverlay;
    #line 1
    D_uvdbg_rom_00402FD8 = uvLoadModule('FONT');
    D_uvdbg_rom_00402FDC = uvLoadModule('STRG');
    D_uvdbg_rom_00402FE0 = uvLoadModule('AMGR');
    D_uvdbg_rom_00402FE4 = uvLoadModule('STAT');
    D_uvdbg_rom_00402FE8 = uvLoadModule('GMGR');
    D_uvdbg_rom_00402FEC = uvLoadModule('GEOM');
    D_uvdbg_rom_00402FF0 = uvLoadModule('CONT');
    D_uvdbg_rom_00402FF4 = uvLoadModule('FMTX');
    D_uvdbg_rom_00402FF8 = uvLoadModule('CHAN');
    D_uvdbg_rom_00402FFC = uvLoadModule('CBCK');
    uvClkReset(0);
}

#line 255 "src/modules/uvdbg_rom.c"
/* Unload the ten original debug-module dependencies in their original order. */
void uvDbgModuleCleanup(void) {
    uvUnloadModule('FONT');
    uvUnloadModule('STRG');
    uvUnloadModule('AMGR');
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('DGEO');
    uvUnloadModule('CONT');
    uvUnloadModule('FMTX');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
}
#line 267 "src/modules/uvdbg_rom.c"

#line 268 "src/modules/uvdbg_rom.c"
/* Return the difference of the two original scheduler ring timestamps
 * selected relative to the current five-slot index. */
f64 uvDbgGetAdjacentFrameInterval(void) {
    s32 slot;

    slot = (s32) (gSchedRingIdx + 1) % 5;
    return D_8002EDD0[(s32) (slot + 1) % 5] - D_8002EDD0[slot];
}
#line 274 "src/modules/uvdbg_rom.c"

#line 275 "src/modules/uvdbg_rom.c"
/* Scan older scheduler slots in the first event table, starting at event
 * 0x2A and ending when 0x2B and 0x30 have been seen. Return elapsed time
 * or zero when the original event pair/group is incomplete. */
f64 uvDbgGetTaskCompletionInterval(void) {
    s32 ringIndex;
    s32 temp_hi;
    s32 j;
    s32 started;
    s32 completionFlags;
    s32 i;
    f64 startTime;
    ringIndex = gSchedRingIdx;
    for (i = ((s32) (ringIndex + 1)) % 5, started = 0, completionFlags = 0; i != ringIndex; i = (i + 1) % 5) {
        for (j = 0; j < D_8002EDB8[i]; j++) {
            Entry *event = &(D_8002E440 + i)->entry[j];
            if (!started) {
                if (event->unk8 == 0x2A) {
                    started = 1;
                    startTime = event->unk0;
                }
                continue;
            }
            if (started) {
                if (event->unk8 == 0x2B) {
                    completionFlags |= 1;
                }
                if (event->unk8 == 0x30) {
                    completionFlags |= 2;
                }
            }
            if (completionFlags == 3) {
                return event->unk0 - startTime;
            }
        }
    }

    return 0;
}
#line 310 "src/modules/uvdbg_rom.c"

#line 311 "src/modules/uvdbg_rom.c"
/* Scan older scheduler slots in the first event table, starting at event
 * 0x29 and ending when 0x2C have been seen. Return elapsed time
 * or zero when the original event pair/group is incomplete. */
f64 uvDbgGetTask29To2CInterval(void) {
    s32 ringIndex;
    s32 temp_hi;
    s32 j;
    s32 started;
    s32 completionFlags;
    s32 i;
    f64 startTime;
    ringIndex = gSchedRingIdx;
    for (i = ((s32) (ringIndex + 1)) % 5, started = 0, completionFlags = 0; i != ringIndex; i = (i + 1) % 5) {
        for (j = 0; j < D_8002EDB8[i]; j++) {
            Entry *event = &(D_8002E440 + i)->entry[j];
            if (!started) {
                if (event->unk8 == 0x29) {
                    started = 1;
                    startTime = event->unk0;
                }
                continue;
            }

            if (started && event->unk8 == 0x2C) {
                completionFlags |= 1;
            }

            if (completionFlags == 1) {
                return event->unk0 - startTime;
            }
        }
    }

    return 0;
}
#line 343 "src/modules/uvdbg_rom.c"

#line 344 "src/modules/uvdbg_rom.c"
/* Scan older scheduler slots in the second event table, starting at event
 * 0x29 and ending when 0x2C have been seen. Return elapsed time
 * or zero when the original event pair/group is incomplete. */
f64 uvDbgGetSecondaryTask29To2CInterval(void) {
    s32 ringIndex;
    s32 temp_hi;
    s32 j;
    s32 started;
    s32 completionFlags;
    s32 i;
    f64 startTime;

    ringIndex = gSchedRingIdx;
    i = ((s32) (ringIndex + 1)) % 5;
    startTime = 0;
    started = 0;

    for (; i != ringIndex; i = (i + 1) % 5) {
        for (j = 0; j < D_8002EDA0[i]; j++) {
            Entry *event = &(D_8002DAE0 + i)->entry[j];
            if (!started) {
                if (event->unk8 == 0x29) {
                    started = 1;
                    startTime = event->unk0;
                }
                continue;
            }

            if (started) {
                if (event->unk8 == 0x2C) {
                    return event->unk0 - startTime;
                }
            }
        }
    }

    return 0.0;
}
#line 379 "src/modules/uvdbg_rom.c"

#line 380 "src/modules/uvdbg_rom.c"
/* Scan older scheduler slots in the second event table, starting at event
 * 0x2A and ending when 0x2B have been seen. Return elapsed time
 * or zero when the original event pair/group is incomplete. */
f64 uvDbgGetSecondaryTask2ATo2BInterval(void) {
    s32 ringIndex;
    s32 temp_hi;
    s32 j;
    s32 started;
    s32 completionFlags;
    s32 i;
    f64 startTime;

    ringIndex = gSchedRingIdx;
    i = ((s32) (ringIndex + 1)) % 5;
    startTime = 0;
    started = 0;

    for (; i != ringIndex; i = (i + 1) % 5) {
        for (j = 0; j < D_8002EDA0[i]; j++) {
            Entry *event = &(D_8002DAE0 + i)->entry[j];
            if (!started) {
                if (event->unk8 == 0x2A) {
                    started = 1;
                    startTime = event->unk0;
                }
                continue;
            }

            if (started) {
                if (event->unk8 == 0x2B) {
                    return event->unk0 - startTime;
                }
            }
        }
    }

    return 0.0;
}
#line 415 "src/modules/uvdbg_rom.c"

#line 416 "src/modules/uvdbg_rom.c"
/* Map the time interval to a two-pixel-high bar, reject reversed/offscreen
 * intervals and clip its right edge. Preserve original narrowing and final
 * one-pixel widening for equal endpoints. */
void uvDbgDrawTimeIntervalBar(f32 startTime, f32 endTime, s16 y, u8 red, u8 green, u8 blue) {
    s16 bottom;
    s16 right;
    s16 left;

    bottom = y + 2;
    right = (s32) ((endTime * 1000.0f * 2) + 26.0f);
    if (startTime < 0.0f) {
        return;
    }

    left = (s32) ((startTime * 1000.0f * 2) + 26.0f);
    if (right < left) {
        return;
    }

    if (D_uvdbg_rom_00402FE8->uvGetScreenWidth() < left) {
        return;
    }

    if (right >= D_uvdbg_rom_00402FE8->uvGetScreenWidth()) {
        right = D_uvdbg_rom_00402FE8->uvGetScreenWidth() - 1;
    }

    if (left == right) {
        right = left + 1;
    }

    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(left, y, right, bottom);
}
#line 447 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_00400D74(s32 arg0) {
    UNUSED char pad[40];
    char dest[40];

    D_uvdbg_rom_00402FD8->uvSetFont(D_uvdbg_rom_00402F30);
    D_uvdbg_rom_00402FD8->uvFontColor(0xFF, 0, 0, 0xFF);
    D_uvdbg_rom_00402FE4->uvGfxStatePush();
    D_uvdbg_rom_00402FE4->uvGfxStateSetFlags(0xFFF);
    D_uvdbg_rom_00402FE4->uvGfxClearCurrentStateBits(0x80F00000);

    D_uvdbg_rom_00402FDC->uvSprintf(dest - 8, "MEM  %d", _uvMemGetBlocksSize());
    D_uvdbg_rom_00402FD8->uvFontPrintStr(0x28, 0xC8, dest - 8);
    D_uvdbg_rom_00402FE4->uvGfxStatePop();
}

void func_uvdbg_rom_00400E74(u8 arg0, u8 arg1) {
    s32 pad;
    s16 sp8A;
    s16 sp88;
    f64 var_fs0;
    char sp30[70];

    sp88 = 0x46;
    if (arg1 == 1) {
        var_fs0 = 1000.0;
    } else {
        var_fs0 = 1000000.0;
        ;
    }
    D_uvdbg_rom_00402FD8->uvSetFont(D_uvdbg_rom_00402F30);
    D_uvdbg_rom_00402FD8->uvFontColor(0xFF, 0xFF, 0, 0xFF);
    D_uvdbg_rom_00402FE4->uvGfxStatePush();
    D_uvdbg_rom_00402FE4->uvGfxStateSetFlags(0xFFF);
    D_uvdbg_rom_00402FE4->uvGfxClearCurrentStateBits(0x80F00000);

    if (arg0 & 1) {
        D_uvdbg_rom_00402FDC->uvSprintf(sp30 - 8, "RET  %d",
                                        (s32) (uvDbgGetAdjacentFrameInterval() * var_fs0));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(0x19, 0x46, sp30 - 8);
        sp88 = D_uvdbg_rom_00402FD8->uvFontHeight() + 0x49;
    }
    if (arg0 & 2) {
        D_uvdbg_rom_00402FDC->uvSprintf(sp30 - 8, "GFX  %d",
                                        (s32) (uvDbgGetTaskCompletionInterval() * var_fs0));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(0x19, sp88, sp30 - 8);
        sp88 += D_uvdbg_rom_00402FD8->uvFontHeight() + 3;
    }
    if (arg0 & 4) {
        D_uvdbg_rom_00402FDC->uvSprintf(sp30 - 8, "CPU  %d",
                                        (s32) (uvDbgGetSecondaryTask2ATo2BInterval() * var_fs0));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(0x19, sp88, sp30 - 8);
        D_uvdbg_rom_00402FD8->uvFontHeight();
    }
    sp8A = 0x5F;
    sp88 = 0x46;
    if (arg0 & 8) {
        D_uvdbg_rom_00402FDC->uvSprintf(sp30 - 8, "AUD  %d",
                                        (s32) (uvDbgGetTask29To2CInterval() * var_fs0));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(sp8A, 0x46, sp30 - 8);
        sp88 = D_uvdbg_rom_00402FD8->uvFontHeight() + 0x49;
    }
    if (arg0 & 0x10) {
        D_uvdbg_rom_00402FDC->uvSprintf(sp30 - 8, "ACPU %d",
                                        (s32) (uvDbgGetSecondaryTask29To2CInterval() * var_fs0));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(sp8A, sp88, sp30 - 8);
        D_uvdbg_rom_00402FD8->uvFontHeight();
    }
    if (&sp8A)
        ; // Fake: Put sp8A on the stack
    D_uvdbg_rom_00402FE4->uvGfxStatePop();
}

#line 520 "src/modules/uvdbg_rom.c"
/* Original empty debug callback; retain its arguments and entry point. */
void uvDbgReservedMemoryCallback(u8 arg0) {
}
#line 522 "src/modules/uvdbg_rom.c"

#line 523 "src/modules/uvdbg_rom.c"
/* Original empty debug callback; retain its arguments and entry point. */
void uvDbgReservedModeCallback(u8 arg0, u8 arg1) {
}
#line 525 "src/modules/uvdbg_rom.c"

#line 526 "src/modules/uvdbg_rom.c"
/* Format and print the selected graphics counter, optionally normalized by
 * the measured task interval, then advance the caller-owned row coordinate.
 * Preserve the original formatting, font-height spacing and empty address check. */
void uvDbgPrintGraphicsCounterRow(const char *label, s32 counterId, s32 *rowY, s32 normalize) {
    char text[80];
    f64 interval;
    s32 sp20;
    s32 value;
    s32 normalizedX;

    interval = uvDbgGetTaskCompletionInterval();
    value = D_uvdbg_rom_00402FE4->func_uvgfxstate_rom_004029B8(counterId);
    D_uvdbg_rom_00402FDC->uvSprintf(text, "%4.4s %+6.0d", label, value);
    D_uvdbg_rom_00402FD8->uvFontPrintStr(0x19, *rowY, text);
    if ((interval != 0.0) && (normalize != 0)) {
        normalizedX = 0x7D;
        D_uvdbg_rom_00402FDC->uvSprintf(text, "%+6.0d", (s32) ((f64) value / interval));
        D_uvdbg_rom_00402FD8->uvFontPrintStr(normalizedX, *rowY, text);
    }
    if (&normalizedX)
        ;
    *rowY = (D_uvdbg_rom_00402FD8->uvFontHeight() + 3) + *rowY;
}
#line 546 "src/modules/uvdbg_rom.c"

#line 547 "src/modules/uvdbg_rom.c"
/* Print graphics counters selected by bits zero through eight; bit 0x200
 * requests normalization. Preserve graphics-state push/pop and original rows. */
void uvDbgDrawSelectedGraphicsCounters(s32 flags) {
    s32 rowY;

    rowY = 0x6E;
    D_uvdbg_rom_00402FD8->uvFontColor(0xFF, 0xFF, 0, 0xFF);
    D_uvdbg_rom_00402FE4->uvGfxStatePush();
    D_uvdbg_rom_00402FE4->uvGfxStateSetFlags(0xFFF);
    D_uvdbg_rom_00402FE4->uvGfxClearCurrentStateBits(0x80F00000);
    if (flags & 1) {
        uvDbgPrintGraphicsCounterRow("VXFM", 0, &rowY, flags & 0x200);
    }
    if (flags & 2) {
        uvDbgPrintGraphicsCounterRow("TRI ", 1, &rowY, flags & 0x200);
    }
    if (flags & 4) {
        uvDbgPrintGraphicsCounterRow("MLD ", 2, &rowY, flags & 0x200);
    }
    if (flags & 8) {
        uvDbgPrintGraphicsCounterRow("MMU ", 3, &rowY, flags & 0x200);
    }
    if (flags & 0x10) {
        uvDbgPrintGraphicsCounterRow("TXL ", 4, &rowY, flags & 0x200);
    }
    if (flags & 0x20) {
        uvDbgPrintGraphicsCounterRow("GFX ", 5, &rowY, flags & 0x200);
    }
    if (flags & 0x40) {
        uvDbgPrintGraphicsCounterRow("VCL ", 6, &rowY, flags & 0x200);
    }
    if (flags & 0x80) {
        uvDbgPrintGraphicsCounterRow("VTX ", 7, &rowY, flags & 0x200);
    }
    if (flags & 0x100) {
        uvDbgPrintGraphicsCounterRow("SYNC", 8, &rowY, flags & 0x200);
    }
    D_uvdbg_rom_00402FE4->uvGfxStatePop();
}
#line 584 "src/modules/uvdbg_rom.c"

static const char unused0[] = "frame time %f\n";
static const char unused1[] = "started at %f\n";
static const char unused2[] = "finished at %f\n";
static const char unused3[] = "\n\n";

// Individual string globals
const char gStr_StaticCode[] = "static code";
const char gStr_FrameBuffers[] = "frame buffers";
const char gStr_AudioHeap[] = "audio heap";
const char gStr_Modules[] = "modules";
const char gStr_Data[] = "data";
const char gStr_Unknown[] = "unknown";
const char gStr_Free[] = "free";

const char gStr_Unknown1[] = "unknown";
const char gStr_StaticCode1[] = "static code";
const char gStr_Filemap[] = "filemap";
const char gStr_Filesys[] = "filesys";
const char gStr_Free8[] = "free 8";
const char gStr_Free16[] = "free 16";

#line 606 "src/modules/uvdbg_rom.c"
/* Original empty debug callback; retain its arguments and entry point. */
void uvDbgReservedCounterCallback(void) {
}
#line 608 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_004014E4(void) {
    s32 s0;
    s32 temp;

    D_uvdbg_rom_00402FE4->uvGfxStatePush();
    D_uvdbg_rom_00402FE4->uvGfxStateSetFlags(0xFFF);
    D_uvdbg_rom_00402FE4->uvGfxClearCurrentStateBits(0x80F00000);

    s0 = 0x1A;
    temp = 0x3A;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.0f, 0.0f, 0.0f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0x5C;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.2f, 0.2f, 0.2f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0x7E;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.0f, 0.0f, 0.0f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0x9E;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.2f, 0.2f, 0.2f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0xC0;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.0f, 0.0f, 0.0f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0xE2;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.2f, 0.2f, 0.2f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0x102;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.0f, 0.0f, 0.0f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    s0 = temp;
    temp = 0x124;
    D_uvdbg_rom_00402FE8->uvGfxSetPrimColorF(0.2f, 0.2f, 0.2f, 1.0f);
    D_uvdbg_rom_00402FEC->uvVtxRect(s0, 0x2D, temp, 0x3F);

    D_uvdbg_rom_00402FE4->uvGfxStatePop();
}

#line 660 "src/modules/uvdbg_rom.c"
/* Original empty debug callback; retain its arguments and entry point. */
void uvDbgReservedTimingCallback(void) {
}
#line 662 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_004017A8(s32 arg0, s32 arg1, u16 arg2, u8 arg3, u8 arg4, u8 arg5) {
    int idx;
    int hi;
    Entry *sp4C;
    s32 sp48;
    s32 sp44;
    s32 *sp38;
    s32 sp40;
    s32 sp3C;
    s32 sp34;
    s32 sp30;
    f64 sp28;
    f64 sp20;

    idx = gSchedRingIdx;
    hi = (idx + 1) % 5;
    sp44 = hi;
    sp28 = D_8002EDD0[sp44];
    if (arg0 == 0) {
        sp38 = D_8002EDA0;
    } else {
        sp38 = D_8002EDB8;
    }

    if (arg1 == 0x29) {
        sp34 = 0x29;
        sp30 = 0x2C;
    } else {
        sp34 = 0x2A;
        sp30 = 0x2B;
    }

    sp48 = -1;
    sp3C = 0;
    for (;;) {
        sp48 += 1;
        if (sp48 > sp38[sp44]) {
            sp3C += 1;
            sp48 = 0;
            sp44 = (sp44 + 1) % 5;
        }
        if (sp3C >= 5) {
            break;
        }
        if (arg0 == 0) {
            sp4C = &D_8002DAE0[sp44].entry[sp48];
        } else {
            sp4C = &D_8002E440[sp44].entry[sp48];
        }
        if (sp4C->unk8 == sp34) {
            break;
        }
        if (sp4C->unk8 == sp30) {
            uvDbgDrawTimeIntervalBar(0.0f, (f32) (sp4C->unk0 - sp28), arg2, arg3, arg4, arg5);
            break;
        }
    }

    sp48 = -1;
    sp3C = 0;
    sp40 = -1;
    sp44 = hi;

    for (;;) {
        sp48 += 1;
        if (sp48 > sp38[sp44]) {
            sp3C += 1;
            sp48 = 0;
            sp44 = (sp44 + 1) % 5;
        }
        if (sp3C >= 4) {
            break;
        }
        if (arg0 == 0) {
            sp4C = &D_8002DAE0[sp44].entry[sp48];
        } else {
            sp4C = &D_8002E440[sp44].entry[sp48];
        }
        if (sp40 != sp34) {
            if (sp4C->unk8 == sp34) {
                sp40 = sp34;
                sp20 = sp4C->unk0;
            }
        } else if (sp4C->unk8 != sp30) {
        } else {
            uvDbgDrawTimeIntervalBar((f32) (sp20 - sp28), (f32) (sp4C->unk0 - sp28), arg2, arg3, arg4,
                                    arg5);
            sp40 = -1;
        }
    }
}

#line 755 "src/modules/uvdbg_rom.c"
/* Draw the four original task-event interval bars with their original
 * event IDs, row positions and RGB colors. */
void uvDbgDrawDefaultTaskIntervals(void) {
    func_uvdbg_rom_004017A8(0, 0x2A, 0x3C, 0, 0, 0xFF);
    func_uvdbg_rom_004017A8(0, 0x29, 0x37, 0xFF, 0, 0xFF);
    func_uvdbg_rom_004017A8(1, 0x2A, 0x32, 0, 0xFF, 0);
    func_uvdbg_rom_004017A8(1, 0x29, 0x2D, 0xFF, 0, 0);
}
#line 761 "src/modules/uvdbg_rom.c"

#line 762 "src/modules/uvdbg_rom.c"
/* Set screen-space orthographic matrices and viewport, draw timing rows
 * and task bars inside the original graphics-state scope. */
void uvDbgDrawTimingOverlay(u8 unused) {
    Mtx4F view;
    Mtx4F projection;

    D_uvdbg_rom_00402FF4->uvMat4SetOrtho(&projection, 0.0f, D_uvdbg_rom_00402FE8->uvGetScreenWidth(), 0.0f,
                                        D_uvdbg_rom_00402FE8->uvGetScreenHeight());
    D_uvdbg_rom_00402FF4->uvGfxMtxProjPushF(&projection);
    D_uvdbg_rom_00402FF4->uvMat4SetIdentity(&view);
    D_uvdbg_rom_00402FF4->uvGfxMtxLoadProjectionWithQuarterTurn(&view);
    D_uvdbg_rom_00402FE8->uvGfxAppendViewport(0, D_uvdbg_rom_00402FE8->uvGetScreenWidth() - 1, 0,
                                                     D_uvdbg_rom_00402FE8->uvGetScreenHeight() - 1);
    func_uvdbg_rom_004014E4();
    D_uvdbg_rom_00402FE4->uvGfxStatePush();
    D_uvdbg_rom_00402FE4->uvGfxStateSetFlags(0xFFF);
    D_uvdbg_rom_00402FE4->uvGfxClearCurrentStateBits(0xF00000);
    uvDbgReservedTimingCallback();
    uvDbgDrawDefaultTaskIntervals();
    D_uvdbg_rom_00402FE4->uvGfxStatePop();
}
#line 781 "src/modules/uvdbg_rom.c"

#line 782 "src/modules/uvdbg_rom.c"
/* Dispatch debug mode one to the timing overlay and mode two to the
 * original alternate display; other modes call the reserved callback. */
void uvDbgDispatchTimingOverlay(u8 context, u8 mode, u8 flags) {
    if (mode == 1) {
        uvDbgDrawTimingOverlay(context);
    } else if (mode == 2) {
        func_uvdbg_rom_00400E74(context, flags);
    } else {
        uvDbgReservedModeCallback(context, flags);
    }
}
#line 791 "src/modules/uvdbg_rom.c"

#line 792 "src/modules/uvdbg_rom.c"
/* For nonzero flags, mode two draws selected graphics counters and mode
 * three invokes the original reserved counter callback. */
void uvDbgDispatchCounterOverlay(s32 flags, s32 mode) {
    if ((flags != 0) && (mode != 1)) {
        if (mode == 2) {
            uvDbgDrawSelectedGraphicsCounters(flags);
            return;
        }
        if (mode == 3) {
            uvDbgReservedCounterCallback();
        }
    }
}
#line 803 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_00401DE8(s32 arg0) {
    f32 temp_fs0;
    f32 temp_fv0;
    f32 var_fs1;
    f32 var_fs2;
    s32 vram;
    s32 tagPtr;
    s32 formFileId;
    s32 formFileEntryId;
    s32 var_v0;

    // Why IDO?
    // 0 is fs4
    // 0.0f is fs3
    var_fs2 = 0;
    var_fs1 = 0;
    D_uvdbg_rom_00402FE8->uvGfxEnd();
    while (D_uvdbg_rom_00402FF0->uvIOUpdate() != 0) {
        temp_fs0 = D_uvdbg_rom_00402FF0->uvControllerGetStick(arg0, 0);
        temp_fv0 = D_uvdbg_rom_00402FF0->uvControllerGetStick(arg0, 1);
        var_fs2 += temp_fs0 * FABS(temp_fs0) * 0.05f;
        var_fs1 += temp_fv0 * FABS(temp_fv0) * 0.2f;
        if ((2.0f * (f32) D_uvdbg_rom_00402FE8->uvGetScreenWidth() * 0.0625f) < var_fs2) {
            var_fs2 = 0;
            var_fs1++;
        }
        if (var_fs2 < 0) {
            var_fs2 = 2.0f * D_uvdbg_rom_00402FE8->uvGetScreenWidth() * 0.0625f;
            var_fs1 -= 1.0f;
        }
        if (var_fs1 < 0.0f) {
            var_fs1 = 0;
        }
        if ((4194304 / (2.0f * D_uvdbg_rom_00402FE8->uvGetScreenWidth())) < var_fs1) {
            var_fs1 = 4194304.0f / (2.0f * D_uvdbg_rom_00402FE8->uvGetScreenWidth());
        }
        vram = ((D_uvdbg_rom_00402FE8->uvGetScreenWidth() * (s32) var_fs1 * 2) + ((s32) var_fs2 * 0x10)
                + 0x8000003F)
               & ~0x3F;
        osViSwapBuffer(vram + 0xFFFECDC0);
        if ((D_uvdbg_rom_00402FF0->uvControllerButtonPress(arg0, Z_TRIG) != 0)
            || (D_uvdbg_rom_00402FF0->uvControllerButtonPress(arg0, START_BUTTON) != 0)) {
            break;
        }

        if (D_uvdbg_rom_00402FF0->uvControllerHasButtons(arg0, 0x8000) != 0) {
            func_8000226C(&tagPtr, &formFileEntryId, &formFileId, vram); // Get form file by vram
            var_v0 = 0;
            while (var_v0 != 2) {
                var_v0++;
            }
        }
    }

    D_uvdbg_rom_00402FE8->uvGfxBegin();
}

UnkStruct_00402F34 D_uvdbg_rom_00402F34 = {
    gStr_StaticCode, gStr_FrameBuffers, gStr_AudioHeap, { gStr_Modules, gStr_Data },
    gStr_Unknown,    gStr_Free,
};

UnusedDebugStrings1 D_uvdbg_rom_00402F50 = { { gStr_Unknown1, gStr_StaticCode1, gStr_Filemap,
                                               gStr_Filesys, gStr_Free8, gStr_Free16 } };

s32 unused[] = { 0x002C0000, &__entrypoint_func_uvdbg_rom_400318 };

void func_uvdbg_rom_00402128(void) {
    int v0;
    UnkStruct_00402F34 sp1F8;
    UnkStruct_UvDbg_Rom_00402128 sp1DC;
    s32 sp114[0x32];
    s32 sp4C[0x32];
    s32 i; // var_s0
    s32 sp44;
    s32 sp40;

    sp1F8 = D_uvdbg_rom_00402F34;
    sp1DC.unk0 = gMemBlock - main_VRAM;
    sp1DC.unk4 =
        D_uvdbg_rom_00402FE8->uvGetScreenWidth() * D_uvdbg_rom_00402FE8->uvGetScreenHeight() * 6;
    sp1DC.audioHeapSize = D_uvdbg_rom_00402FE0->uvGetAudioHeapSize();
    sp1DC.unkC[0] = sp1DC.unkC[1] = sp1DC.unk14 = 0;

    sp1DC.unk18 = _uvMemGetBlocksSize();
    func_8000218C(sp114, sp4C, &sp44, 0x32);

    for (i = 0; i < sp44; i++) {
        if (sp114[i] == 'UVMO') {
            sp1DC.unkC[0] += sp4C[i];
        } else {
            sp1DC.unkC[1] += sp4C[i];
        }
    }

    sp1DC.unkC[0] = (sp1DC.unkC[0] - sp1DC.audioHeapSize) - sp1DC.unk4;
    sp1DC.unk14 =
        osMemSize - sp1DC.unk0 - sp1DC.unk4 - sp1DC.audioHeapSize - sp1DC.unkC[0] - sp1DC.unkC[1] - sp1DC.unk18;

    for (i = 0; i < 7; i++) {
    }

    for (i = 0; i < sp44; i++) {
        if (sp114[i]) {
        }
    }

    sp40 = uvGetFilesCount('UVMO');
    for (i = 0; i < sp40; i++) {
        v0 = uvGetUnusedFileInfo('UVMO', i);
        if (gModuleNameTags[i] == 'AMGR') {
            v0 -= sp1DC.audioHeapSize;
        }
        if (gModuleNameTags[i] == 'GMGR') {
            v0 -= sp1DC.audioHeapSize;
        }
        if (v0) {
        }
    }
}

void func_uvdbg_rom_00402490(void) {
    s32 pad2;
    UnusedDebugStrings1 dbgStrings;
    s32 info[6];
    char spD0[0xC4];
    s32 spEC;
    char pad[0xBC];
    s32 i;
    s32 pad24;
    s32 sp24;
    s32 sp20;

    dbgStrings = D_uvdbg_rom_00402F50;
    // code
    info[0] = main_ROM_START;
    // codeSize
    info[1] = FORM0_ROM_START - main_ROM_START;
    
    // file table size
    info[2] = gModuleFilesSize;

    // form files size
    info[3] = gFormFilesSize;
    info[4] = (u8 *) 0x800000 - gRomEnd;
    info[5] = (u8 *) 0x01000000 - gRomEnd;

    i = 0;
    while (i < 6) {
        i++;
    }

    func_80002088(&spEC, &sp24, &sp20, 0x32);
    for (i = 0; i < sp20; i++) {
    }
}

#line 961 "src/modules/uvdbg_rom.c"
/* Clear the selected shared debug word when nonzero. Preserve the original
 * linear word indexing and caller-owned bounds. */
void uvDbgClearWordByIndex(s32 index) {
    s32 *word;

    word = index + (s32 *) D_uvdbg_rom_00402FB8;
    if (*word != 0) {
        *word = 0;
    }
}
#line 969 "src/modules/uvdbg_rom.c"

#line 970 "src/modules/uvdbg_rom.c"
/* Format a label and scalar to two decimal places, print the row and move
 * the caller-owned Y coordinate upward by ten pixels. */
void uvDbgPrintScalarRow(const char *label, f32 value, s32 *rowY) {
    s32 pad;
    char text[250];

    sprintf(text, "%12.12s : %5.2f", label, (f64) value);
    D_uvdbg_rom_00402FD8->uvFontPrintStr(0x1E, *rowY, text);
    *rowY -= 0xA;
}
#line 978 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_0040262C(void) {
    s32 sp2C;

    sp2C = 0xC8;
    D_uvdbg_rom_00402FD8->uvSetFont(D_uvdbg_rom_00402F30);
    D_uvdbg_rom_00402FD8->uvFontColor(0xFF, 0xFF, 0, 0xFF);
    uvDbgPrintScalarRow("PRE", (D_uvdbg_rom_00402F74 - D_uvdbg_rom_00402F70) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("ENV", (D_uvdbg_rom_00402F78 - D_uvdbg_rom_00402F74) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("TERRA", (D_uvdbg_rom_00402F7C - D_uvdbg_rom_00402F78) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("TILEFAR", (D_uvdbg_rom_00402F80 - D_uvdbg_rom_00402F7C) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("DOBJ", (D_uvdbg_rom_00402F84 - D_uvdbg_rom_00402F80) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("FX", (D_uvdbg_rom_00402F88 - D_uvdbg_rom_00402F84) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("DOBJ1", (D_uvdbg_rom_00402F8C - D_uvdbg_rom_00402F88) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("FOG", (D_uvdbg_rom_00402F90 - D_uvdbg_rom_00402F8C) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("SORT1", (D_uvdbg_rom_00402F94 - D_uvdbg_rom_00402F90) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("FOGOVER", (D_uvdbg_rom_00402F98 - D_uvdbg_rom_00402F94) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("PFX", (D_uvdbg_rom_00402F9C - D_uvdbg_rom_00402F98) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("TILENEAR", (D_uvdbg_rom_00402FA0 - D_uvdbg_rom_00402F9C) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("DOBJ2", (D_uvdbg_rom_00402FA4 - D_uvdbg_rom_00402FA0) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("SORT2", (D_uvdbg_rom_00402FA8 - D_uvdbg_rom_00402FA4) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("SHADOW", (D_uvdbg_rom_00402FAC - D_uvdbg_rom_00402FA8) * 1000.0f, &sp2C);
    uvDbgPrintScalarRow("DOBJCLOSE", (D_uvdbg_rom_00402FB0 - D_uvdbg_rom_00402FAC) * 1000.0f,
                            &sp2C);
    uvDbgPrintScalarRow("POST", (D_uvdbg_rom_00402FB4 - D_uvdbg_rom_00402FB0) * 1000.0f, &sp2C);
}

#line 1005 "src/modules/uvdbg_rom.c"
/* Store the font ID used by debug overlays. */
void uvDbgSetFontId(s32 fontId) {
    D_uvdbg_rom_00402F30 = fontId;
}
#line 1008 "src/modules/uvdbg_rom.c"

#line 1009 "src/modules/uvdbg_rom.c"
/* Set the four display words in both original debug records to one. */
void uvDbgResetDisplayFlags(void) {
    int i;
    for (i = 0; i < 2; i++) {
        D_uvdbg_rom_00402FB8[i].unk4 = 1;
        D_uvdbg_rom_00402FB8[i].unk8 = 1;
        D_uvdbg_rom_00402FB8[i].unkC = 1;
        D_uvdbg_rom_00402FB8[i].unk0 = 1;
    }
}
#line 1018 "src/modules/uvdbg_rom.c"

void func_uvdbg_rom_00402A14(s32 arg0) {
    s32 sp24;

    D_uvdbg_rom_00402FF8->uvChannelGetProperties(arg0, 6, &sp24, 0);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot00, 0, 1);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot01, 0, 0x13);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot02, 0, 0x15);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot03, 0, 0x29);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot04, 0, 0x2E);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot05, 0, 0x3D);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot06, 0, 0x42);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot07, 0, 0x51);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot08, 0, 0x53);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot09, 0, 0x56);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot10, 0, 0x58);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot11, 0, 0x5B);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot12, 0, 0x65);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot13, 0, 0x6F);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot14, 0, 0x74);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot15, 0, 0x83);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot16, 0, 0x97);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgStampProfileSlot17, 0, 0xFE);
    D_uvdbg_rom_00402FFC->uvAddCallback(sp24, uvDbgClearWordByIndex, 0, 0xFF);
}

#line 1044 "src/modules/uvdbg_rom.c"
/* Mode two draws the original memory overlay; other modes call its reserved
 * callback. Preserve the original byte argument forwarding. */
void uvDbgDispatchMemoryOverlay(u8 context, u8 mode) {
    if (mode == 2) {
        func_uvdbg_rom_00400D74(context);
    } else {
        uvDbgReservedMemoryCallback(context);
    }
}
#line 1051 "src/modules/uvdbg_rom.c"

#line 1052 "src/modules/uvdbg_rom.c"
/* Forward to the original resource-statistics routine. */
void uvDbgDrawResourceStatistics(void) {
    func_uvdbg_rom_0040262C();
}
#line 1055 "src/modules/uvdbg_rom.c"
