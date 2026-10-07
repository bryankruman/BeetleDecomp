// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "os_internal.h"
#include "stdarg.h"

void uvProfilerInit(void);          /* extern */
void func_800011A8(void);          /* extern */
void _uvMemAllocInitStartUp(void); /* extern */
void uvResetAllocatorWithOptionalFill(s32);           /* extern */
void uvModuleInit(void);           /* extern */
void uvSetVideoMode(void);         /* extern */
void _uvScInitClientList(void);    /* extern */
void Thread_Kernel(void *);        /* extern */
s32 uvFindModuleTagBeforeAddress(u32 arg0, s32 *arg1);
void func_800051B4(void *);                 /* extern */
void func_80005284(void *);                 /* extern */
void func_80007190(s32, s32 *, s32 *, s32); /* extern */
void uvGameInit(void *);                 /* extern */

// .bss
// TODO: Why are these threads stack are so small?
u8 gFaultThreadStack[0x10];
OSMesgQueue gFaultMesgQ;
OSMesg gFaultMesgBuf[2];
OSThread gFaultThread;
s32 D_8002F750[30];
u8 gThreadKernelStack[0x10]; // kernel thread stack
s32 gClearAllocatedMemory;
s32 D_8002F7DC;
OSIoMesg D_8002F7E0;
OSMesg gPiDmaBuf[2];
OSMesgQueue gPiDmaQ;
OSMesg gSiContBuf[3];
OSMesgQueue gSiContQ;
OSMesg gPiMgrCmdBuf[28];
OSMesgQueue gPiMgrCmdQ;
s32 D_8002F8C8;
OSThread gAppThread;
OSThread gKernelThread;
OSContStatus gContStatus;

// .data
u8 D_8001F7D0[4] = { 0, 0, 0, 0 };

s32 D_8001F7D4 = 0;
s32 D_8001F7D8 = 0;
s32 gCartDMATransferFlag = 1;

u16 D_8001F7E0[0x10] = {
    0xF6DE, 0x2492, 0xE54E, 0xE59E, 0xB792, 0xF39E, 0xF3DE, 0xE492,
    0xF7DE, 0xF792, 0xF7DA, 0x93DE, 0xF24E, 0x27DE, 0xF3CE, 0xF3C8,
};

u16 D_8001F800[14] = {
    0xF6DE, 0xB6DE, 0xE924, 0, 0xF6DE, 0xF348, 0, 0xBFDA, 0xF3CE, 0xBFDA, 0xF6DE, 0xF7EA, 0xB524, 0,
};

// external variables
extern s32 D_8001F630;
extern s32 *gModuleExportsSize;
extern u8 gAppThreadStack[];

void uvDebugDrawScaledGlyph(s32 arg0, s32 arg1, s32 arg2, u16 arg3, u16 arg4);

void uvSysInit(void) {
    // init for power up
    if (gCartDMATransferFlag != 0) {
        _uvMemAllocInitStartUp();
        uvSetVideoMode();
        uvClkInit();
        uvProfilerInit();
        uvLoadFormFiles();
        uvModuleInit();
        gCartDMATransferFlag = 0;

        // Always false
        if (D_8002F8C8) {
            *(volatile s32 *) 0 = 0;
        }
        // init during game
    } else {
        _uvScInitClientList();
        uvResetAllocatorWithOptionalFill(0);
        uvLoadFormFiles();
        uvModuleInit();
        uvProfilerInit();
    }
}

static void unusedFunction() {
}

void uvWaitForMesg(u8 msg) {
    if (!msg) {
        osRecvMesg(&gPiDmaQ, NULL, 1);
    }
}

void bootproc(void *arg0) {
    u32 devAddr;
    s32 i;
    u32 threadEntry[16];

    osInitialize();
    osAiSetFrequency(0x5622U);
#ifdef ISPRINT
    ISViewer_Init();
#endif
    devAddr = 0xFFB000;
    for (i = 0; i < 16; i++, devAddr += 4) {
        osPiRawReadIo(devAddr, &threadEntry[i]);
    }
    osCreateThread(&gKernelThread, 1, Thread_Kernel, threadEntry, gThreadKernelStack, 12);
    osStartThread(&gKernelThread);
}

#line 117 "src/main.c"
/* Draw a 5-by-7 bordered glyph as 2-by-2 pixel blocks into both original
 * 320-pixel-wide raw framebuffers. Interior bits are consumed from bit 15
 * through bit 1; preserve signed pixel stores and literal buffer addresses.
 * RE_UNKNOWN: caller coordinate bounds and buffer ownership/selection require
 * display setup and caller evidence; this routine performs no clipping. */
void uvDebugDrawScaledGlyph(s32 x, s32 y, s32 glyphBits, u16 foreground, u16 background) {
    u16 pixelColor;
    s16 *framebufferA;
    s32 unusedWord0;
    s32 unusedWord1;
    s32 glyphRow; // row
    s32 glyphColumn; // column
    s32 pixelRow; // out "scaled pixel" row
    s32 pixelColumn; // out "scaled pixel" column
    s32 glyphBitIndex;
    s16 *framebufferB;
    s32 unusedWord2;
    s32 unusedWord3;

    glyphBitIndex = 0;
    for (glyphRow = 0; glyphRow < 7; glyphRow++) {
        for (glyphColumn = 0; glyphColumn < 5; glyphColumn++) {
            if ((glyphColumn == 0) || (glyphRow == 0) || (glyphColumn == 4) || (glyphRow == 6)) {
                // Border color
                pixelColor = background;
            } else {
                if ((glyphBits & (1 << (15 - glyphBitIndex)))) {
                    pixelColor = foreground;
                } else {
                    pixelColor = background;
                }
                glyphBitIndex++;
            }

            // Framebuffers have to use raw values otherwise addiu instructions are used
            framebufferA = 0x80200000;
            framebufferB = 0x801DA800;

            // Expand each glyph cell to a two-by-two block; both buffers use width 320.
            // Keep the original nested loop order and raw pixel writes.
            for (pixelColumn = 0; pixelColumn < 2; pixelColumn++) {
                for (pixelRow = 0; pixelRow < 2; pixelRow++) {
                    s32 index = (pixelColumn + (glyphColumn * 2 + x)) + ((pixelRow + (glyphRow * 2 + y)) * 320);
                    framebufferA[index] = pixelColor;
                    framebufferB[index] = pixelColor;
                }
            }
        }
    }
}
#line 162 "src/main.c"

#line 163 "src/main.c"
/* Draw the indexed glyph from the original sixteen-entry hexadecimal glyph
 * table with caller colors. RE_UNKNOWN: callers must supply an index in
 * zero through fifteen; no bounds check is added. */
void uvDebugDrawHexDigit(s32 x, s32 y, s32 digit, u16 foreground, u16 background) {
    uvDebugDrawScaledGlyph(x, y, D_8001F7E0[digit], foreground, background);
}
#line 166 "src/main.c"

#line 167 "src/main.c"
/* Render the first thirteen entries of the original fixed glyph sequence
 * using white foreground and background word one. A zero entry resets X and
 * advances Y by sixteen; preserve the ten-pixel pre-increment and signed
 * coordinate narrowing. RE_UNKNOWN: the sequence text and its display
 * trigger require caller/data interpretation; no fault-specific role assumed. */
void uvDebugDrawFixedGlyphSequence(s32 startX, s32 y) {
    s16 x;
    s16 glyphIndex;

    x = startX;
    for (glyphIndex = 0; glyphIndex < 13; glyphIndex++) {
        x += 0xA;
        if (D_8001F800[glyphIndex] == 0) {
            x = startX;
            y += 0x10;
        } else {
            uvDebugDrawScaledGlyph(x, (s16) y, D_8001F800[glyphIndex], 0xFFFFU, 1U);
        }
    }
}
#line 182 "src/main.c"

#line 183 "src/main.c"
/* Draw eight hexadecimal digits from most significant nibble to least,
 * spaced ten pixels apart with the original signed coordinate narrowing
 * and white foreground and background word one. */
void uvDebugDrawHexWord(u32 value, s32 x, s32 y) {
    s16 digitIndex;

    for (digitIndex = 0; digitIndex < 8; digitIndex++) {
        uvDebugDrawHexDigit((s16) ((digitIndex * 0xA) + x), (s16) y, (value >> (0x1C - (digitIndex * 4))) & 0xF, 0xFFFFU,
                      1U);
    }
}
#line 191 "src/main.c"

#line 192 "src/main.c"
/* Draw the nearest preceding loaded module's tag, when found, then draw
 * address minus its base minus its export-table size. Otherwise add the
 * original main-image display bias. Write back the data cache after drawing.
 * RE_UNKNOWN: the resolver checks no upper module extent; address ownership
 * and fallback-bias meaning need original layout/caller evidence. */
void uvDebugDrawResolvedAddress(s32 address, s32 y) {
    u32 moduleTag;
    s32 moduleFileId;

    moduleTag = uvFindModuleTagBeforeAddress(address, &moduleFileId);
    if (moduleTag != 0) {
        int unusedWord;
        uvDebugDrawHexWord(moduleTag, 0x14, y);
        address -= (s32) uvGetLoadedModule(moduleTag);
        address -= gModuleExportsSize[moduleFileId];
    } else {
        address += 0x7FFFFBB0;
    }
    uvDebugDrawHexWord(address, 0x78, y);
    osWritebackDCacheAll();
}
#line 208 "src/main.c"

#line 209 "src/main.c"
/* Draw the current address, then scan instruction words forward below
 * 0x80400000 for saved-return-address restores and stack-pointer adjustments.
 * Stop at a negative stack adjustment, return-address save or exception
 * return; recursively draw a nonzero recovered return address minus four.
 * Preserve the thirteen-call depth limit and first-level saved-address
 * fallback. RE_UNKNOWN: code/stack validity, the saved fallback producer and
 * complete instruction coverage require caller/exception-path evidence;
 * this original opcode heuristic is not a complete stack unwinder. */
UNUSED void uvDebugDrawStackTrace(s32 address, u8 *stackCursor, s32 y) {
    s32 opcodePrefix;
    s32 unusedWord;
    s32 *instruction;
    u8 *unusedByteCursor;
    s32 returnAddress;
    static s32 D_8001F81C = 0;
    s32 expectedInstruction;

    if (D_8001F81C >= 0xD) {
        return;
    }
    returnAddress = 0;
    uvDebugDrawResolvedAddress(address, y);

    for (instruction = address; (u32) instruction < 0x80400000; instruction++) {
        opcodePrefix = (*instruction & 0xFFFF0000);
        if (opcodePrefix == 0x8FBF0000) {
            returnAddress = *(u32 *) ((s16) (*instruction & 0xFFFF) + stackCursor);
        }
        if (opcodePrefix == 0x27BD0000) {
            if ((s16) (*instruction & 0xFFFF) < 0) {
                break;
            }
            stackCursor += (s16) (*instruction & 0xFFFF);
        }
        if (opcodePrefix == 0xAFBF0000) {
            break;
        }

        if ((*instruction == (expectedInstruction = 0x03E00008)) && (D_8001F81C == 0) && (!returnAddress)) {
            returnAddress = D_8002F750[0];
        }

        if ((*instruction == (expectedInstruction = 0x42000018))) {
            break;
        }
    }
    if (returnAddress != 0) {
        D_8001F81C++;
        uvDebugDrawStackTrace(returnAddress - 4, stackCursor, y + 0x10);
        D_8001F81C--;
    }
}
#line 253 "src/main.c"

void Thread_Fault(void *arg0) {
    s32 pad;
    OSMesg mesg = NULL;
    OSThread *thread;

    osCreateMesgQueue(&gFaultMesgQ, gFaultMesgBuf, OS_MESG_BLOCK);
    osSetEventMesg(OS_EVENT_FAULT, &gFaultMesgQ, (void *) 0x10);
    while (TRUE) {
        osRecvMesg(&gFaultMesgQ, &mesg, OS_MESG_BLOCK);
        thread = __osGetActiveQueue();
        if (thread->state != OS_STATE_STOPPED) {
            osStopThread(thread);
        }
        D_8001F7D8 = thread->id;
        D_8001F7D4 = 1;
    }
}

void Thread_App(void *arg0) {
    uvGameInit(arg0);
}

void Thread_Kernel(void *entry) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &gPiMgrCmdQ, gPiMgrCmdBuf, ARRAY_COUNT(gPiMgrCmdBuf));
    osCreateMesgQueue(&gPiDmaQ, gPiDmaBuf, 1);
    osCreateThread(&gFaultThread, 0, Thread_Fault, NULL, gFaultThreadStack, 0xFA);
    osStartThread(&gFaultThread);
    osCreateThread(&gAppThread, 6, Thread_App, entry, &gAppThreadStack[D_8001F630 - 16], 0xA);
    osStartThread(&gAppThread);
    osSetThreadPri(NULL, 0);
    while (TRUE) {
    }
}

void _uvDebugPrintf(char *fmt, ...) {
#ifdef ISPRINT
    va_list arglist;
    va_start(arglist, fmt);
    osSyncPrintf(fmt, arglist);
    va_end(arglist);
#endif
}

void _uvDMA(void *vAddr, u32 devAddr, u32 nbytes) {
    if ((!((s32) vAddr % 8)) && (!((s32) devAddr % 2)) && (nbytes < 0x400001U)) {
        if (nbytes & 1) {
            nbytes = (nbytes + 1) & ~1;
        }
        osWritebackDCache(vAddr, (s32) nbytes);
        osPiStartDma(&D_8002F7E0, 0, 0, devAddr, vAddr, nbytes, &gPiDmaQ);
        osInvalDCache(vAddr, (s32) nbytes);
        uvWaitForMesg(0);
    }
}

static u8 sContBitPattern = FALSE;
u8 uvContMesgInit(OSMesgQueue **siContQ, OSContStatus **contStatus) {
    OSMesg mesgBuf[2];
    OSMesgQueue mq;
    OSTimer timer;
    OSMesg mesg;

    *contStatus = &gContStatus;
    if (!sContBitPattern) {
        osCreateMesgQueue(&mq, mesgBuf, ARRAY_COUNT(mesgBuf));
        osSetTimer(&timer, 0x2710, 0, &mq, mesgBuf);
        osRecvMesg(&mq, &mesg, OS_MESG_BLOCK);
        osCreateMesgQueue(&gSiContQ, gSiContBuf, ARRAY_COUNT(gSiContBuf));
        osSetEventMesg(OS_EVENT_SI, &gSiContQ, (void *) 0x33333333);
        osContInit(&gSiContQ, &sContBitPattern, *contStatus);
    }
    *siContQ = &gSiContQ;
    return sContBitPattern;
}

void func_80005570(void) {
}
