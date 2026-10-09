// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include <PR/sched.h>
#include "stdarg.h"
#define TASK_OUTPUT_BUFFER_SIZE 0x2000

typedef struct UvGfxStruct_s {
    /* 0x00 */ s32 unk0; /* inferred */
    /* 0x04 */ char pad4[4];
    /* 0x08 */ s32 unk8;           /* inferred */
    /* 0x0C */ void *unkC;         /* inferred */
    /* 0x10 */ OSTask task;        /* inferred */
    /* 0x50 */ OSMesgQueue *unk50; /* inferred */
    /* 0x54 */ void *unk54;        /* inferred */
} UvGfxStruct;                     /* size = 0x58 */

typedef struct uvGfxViewport_s {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 x0; // left?
    /* 0xA */ s16 x1; // right?
    /* 0xC */ s16 y0; // top?
    /* 0xE */ s16 y1; // bottom?
    /* 0x10 */ Vp vp;
} uvGfxViewport;

typedef struct GfxMgrSettings_s {
    /* 0x00 */ s32 unk0[1];      /* inferred */
    /* 0x04 */ char pad4[8];     /* maybe part of unk0[3]? */
    /* 0x0C */ u16 unkC;         /* inferred */
    /* 0x0E */ u16 unkE;         /* inferred */
    /* 0x10 */ u16 screenWidth;  /* inferred */
    /* 0x12 */ u16 screenHeight; /* inferred */
    /* 0x14 */ u16 unk14;        /* inferred */
    /* 0x16 */ u16 unk16;        /* inferred */
    s32 unk18;
    s32 unk1C[1];
} GfxMgrSettings; /* RE_UNKNOWN: partial view; native reads words at 0x1C/0x20. Full historical extent and array capacities need producer proof. */

void uvGfxWaitIfRequested(void);

extern OSSched *gScheduler;

void __entrypoint_func_uvgfxmgr_rom_400000(UvGfxMgr_Exports *arg0);
void uvGfxModuleCleanup(void);
void uvGfxBegin(void);
Gfx **uvGetDisplayListHead(void);
void uvGfxDisplayList(Gfx *dl);
s32 uvGfxGetCallbackList(s32 arg0);
void (*func_uvgfxmgr_rom_00400AF0(void (*arg0)(void *, void *)))(void *, void *);
s32 uvGfxMgrExchangeSharedWord(s32 arg0);
void func_uvgfxmgr_rom_00400B18(s32 arg0);
void uvGfxEnd(void);
void uvGfxWaitForMesg(u16 arg0);
void uvGfxWaitForMesg(u16 arg0);
void func_uvgfxmgr_rom_00400F58(s32 arg0);
s32 uvGfxPollTaskCompletion(void);
void uvGfxMgrSetScalarOverride(f32 arg0);
f32 uvGfxMgrGetScalarOverrideOrCurrent(void);
void uvGfxEnableGamma(s32 enable);
void uvGfxSetPrimColorF(f32 red, f32 green, f32 blue, f32 alpha);
void uvGfxSetPrimColor(s8 red, s8 green, s8 blue, s8 alpha);
void uvGfxSetEnvColorF(f32 red, f32 green, f32 blue, f32 alpha);
void uvGfxSetEnvColor(s8 r, s8 g, s8 b, s8 a);
void uvGfxSetConvert(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5);
void uvGfxFillRect(u8 red, u8 green, u8 alpha);
void uvGfxClearScreen(void);
void uvGfxClipRect(uvGfxViewport *vp, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void uvGfxAppendViewport(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvGfxApplyViewport(s32 vp_id);
void uvGfxApplyViewport(s32); /* extern */
void uvGfxPersp(s16 persp);
void uvGfxClearDepthImageViewport(void);
void *uvGfxGetDepthImageBuffer(void);
s32 uvGfxGetCurrentFramebuffer(void);
s32 uvGfxGetAlternateFramebuffer(void);
void uvGfxWaitIfRequested(void);
void uvGfxWaitIfRequested(void);
void uvCopyFrameBuf(s32 arg0);
void uvSetScreenHeight(s32 height);
void uvSetScreenWidth(s32 arg0);
s32 uvGetScreenHeight(void);
s32 uvGetScreenWidth(void);
void uvGfxEmitCoverageFill(void);
void uvGfxSetDepthSource(s32 usePrimitiveDepth);
void uvGfxPrimDepth(s32 z);

// .data
void *D_uvgfxmgr_rom_00402260 = NULL;
s32 D_uvgfxmgr_rom_00402264 = 0;
s32 D_uvgfxmgr_rom_00402268[4] = { 0, 0, 0, 0 };
Gfx D_uvgfxmgr_rom_00402278[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetBlendColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsDPSetPrimDepth(-1, -1),
    gsDPSetDepthSource(G_ZS_PRIM),
    gsDPSetRenderMode(G_RM_VISCVG, G_RM_VISCVG2),
    gsDPFillRectangle(0, 0, 319, 239),
    gsSPEndDisplayList(),
};

s32 D_uvgfxmgr_rom_004022B8[] = { 0x00980000, __entrypoint_func_uvgfxmgr_rom_400000 };

// .bss
s32 sGfxYieldData;
s32 sGfxDramStack;
uvGfxViewport D_uvgfxmgr_rom_004022C8[10];
s16 sGfxClipX0;
s16 sGfxClipX1;
s16 sGfxClipY1;
s16 sGfxClipY2;
void *sGfxTaskOutputBuffer;
u64 *sGfxTaskOutputBufferStart;
s32 sGfxTaskOutputBufferEnd;
Gfx *sGfxDisplayListHead;
f32 D_uvgfxmgr_rom_00402420[3];
u16 D_uvgfxmgr_rom_0040242C;
void *sGfxFrameBuffers[3];
void *sGfxDepthBuffer;
u16 D_uvgfxmgr_rom_00402440;
u16 sScreenWidth;
u16 sScreenHeight;
u16 D_uvgfxmgr_rom_00402446;
u16 D_uvgfxmgr_rom_00402448;
s32 D_uvgfxmgr_rom_0040244C;
s32 D_uvgfxmgr_rom_00402450;
s32 D_uvgfxmgr_rom_00402454; // unreferenced padding
Gfx *sGfxDisplayListBase[2];
u16 D_uvgfxmgr_rom_00402460;
u16 sGfxDisplayListIndex;
u16 D_uvgfxmgr_rom_00402464;
u16 sGfxFrameBufferIndex;
s32 sGfxElementCount;
s32 D_uvgfxmgr_rom_0040246C; // unreferenced padding
s32 D_uvgfxmgr_rom_00402470[2];
s32 D_uvgfxmgr_rom_00402478;
s32 D_uvgfxmgr_rom_0040247C;
f32 D_uvgfxmgr_rom_00402480;
void *D_uvgfxmgr_rom_00402484;
UvGfxStruct D_uvgfxmgr_rom_00402488[3];
OSMesg D_uvgfxmgr_rom_00402590[10];
OSMesgQueue D_uvgfxmgr_rom_004025B8;
OSMesg D_uvgfxmgr_rom_004025D0[10];
OSMesgQueue D_uvgfxmgr_rom_004025F8;
OSScClient D_uvgfxmgr_rom_00402610;
void (*D_uvgfxmgr_rom_00402618)(s32, s32);
void (*sGfxFrameBufferCallback)(void *, void *);
CallbackList *D_uvgfxmgr_rom_00402620;
CallbackList *D_uvgfxmgr_rom_00402624;
static UvCback_Exports *sUvCbackExports;

#ifdef NON_MATCHING
#include "../crash_screen.c"
#endif

/* Publish graphics exports, reserve frame/task buffers, create callback lists and establish initial display state. */
#line 160 "src/modules/uvgfxmgr_rom.c"
void __entrypoint_func_uvgfxmgr_rom_400000(UvGfxMgr_Exports *exports) {
    GfxMgrSettings *settings;
    s32 frameByteCount;
    u32 reservationPrefixBytes;
    u32 reservationSuffixBytes;
    s32 *historicalUnusedPointer; /* RE_UNKNOWN: retain unused local storage; historical declaration form is unproved. */
    s32 bufferIndex;

    uvUpdateFileAllocPtr(exports);
    exports->uvGfxBegin = uvGfxBegin;
    exports->uvGetDisplayListHead = uvGetDisplayListHead;
    exports->uvGfxDisplayList = uvGfxDisplayList;
    exports->uvGfxGetCallbackList = uvGfxGetCallbackList;
    exports->func_uvgfxmgr_rom_00400AF0 = func_uvgfxmgr_rom_00400AF0;
    exports->uvGfxMgrExchangeSharedWord = uvGfxMgrExchangeSharedWord;
    exports->func_uvgfxmgr_rom_00400B18 = func_uvgfxmgr_rom_00400B18;
    exports->uvGfxEnd = uvGfxEnd;
    exports->uvGfxWaitForMesg = uvGfxWaitForMesg;
    exports->uvGfxModuleCleanup = uvGfxModuleCleanup;
    exports->func_uvgfxmgr_rom_00400F58 = func_uvgfxmgr_rom_00400F58;
    exports->uvGfxFillRect = uvGfxFillRect;
    exports->uvGfxPollTaskCompletion = uvGfxPollTaskCompletion;
    exports->uvCopyFrameBuf = uvCopyFrameBuf;
    exports->uvGfxClearScreen = uvGfxClearScreen;
    exports->uvGfxMgrSetScalarOverride = uvGfxMgrSetScalarOverride;
    exports->uvSetScreenHeight = uvSetScreenHeight;
    exports->uvGfxAppendViewport = uvGfxAppendViewport;
    exports->uvGfxMgrGetScalarOverrideOrCurrent = uvGfxMgrGetScalarOverrideOrCurrent;
    exports->uvSetScreenWidth = uvSetScreenWidth;
    exports->uvGfxApplyViewport = uvGfxApplyViewport;
    exports->uvGfxEnableGamma = uvGfxEnableGamma;
    exports->uvGetScreenHeight = uvGetScreenHeight;
    exports->uvGfxPersp = uvGfxPersp;
    exports->uvGfxSetPrimColorF = uvGfxSetPrimColorF;
    exports->uvGetScreenWidth = uvGetScreenWidth;
    exports->uvGfxClearDepthImageViewport = uvGfxClearDepthImageViewport;
    exports->uvGfxSetPrimColor = uvGfxSetPrimColor;
    exports->uvGfxEmitCoverageFill = uvGfxEmitCoverageFill;
    exports->uvGfxGetDepthImageBuffer = uvGfxGetDepthImageBuffer;
    exports->uvGfxSetEnvColorF = uvGfxSetEnvColorF;
    exports->uvGfxSetDepthSource = uvGfxSetDepthSource;
    exports->uvGfxGetCurrentFramebuffer = uvGfxGetCurrentFramebuffer;
    exports->uvGfxSetEnvColor = uvGfxSetEnvColor;
    exports->uvGfxPrimDepth = uvGfxPrimDepth;
    exports->uvGfxGetAlternateFramebuffer = uvGfxGetAlternateFramebuffer;
    exports->uvGfxSetConvert = uvGfxSetConvert;
    exports->uvGfxWaitIfRequested = uvGfxWaitIfRequested;
#ifdef __sgi
#line 1
#endif

    sGfxDramStack = malloc16(0x400);
    sGfxTaskOutputBuffer = 0x800FDF80;
    uvMemAllocAt(sGfxTaskOutputBuffer, 0x2080, &reservationPrefixBytes, &reservationSuffixBytes);
    sGfxYieldData = malloc16(0xC00);
    settings = uvGetSystemProp(SYSTEM_PROPID_GFX_SETTINGS); /* RE_UNKNOWN: settings extent/counts and storage ownership need producer proof; preserve the current partial view. */
    if (settings == NULL) {
        sScreenWidth = SCREEN_WIDTH;
        sScreenHeight = SCREEN_HEIGHT;
        D_uvgfxmgr_rom_00402446 = 0xA;
        D_uvgfxmgr_rom_00402448 = 0xA;
        D_uvgfxmgr_rom_0040242C = 2;
        sGfxFrameBuffers[0] = 0;
        sGfxFrameBuffers[1] = 0;
        D_uvgfxmgr_rom_00402440 = 0;
        D_uvgfxmgr_rom_0040244C = 0x1068;
        sGfxDisplayListBase[0] = NULL;
        sGfxDisplayListBase[1] = NULL;
    } else {
        if (settings->screenWidth != 0) {
            sScreenWidth = settings->screenWidth;
        } else {
            sScreenWidth = 0x140;
        }
        if (settings->screenHeight != 0) {
            sScreenHeight = settings->screenHeight;
        } else {
            sScreenHeight = 0xF0;
        }
        if (settings->unk14 != 0) {
            D_uvgfxmgr_rom_00402446 = settings->unk14;
        } else {
            D_uvgfxmgr_rom_00402446 = 0xA;
        }
        if (settings->unk16 != 0) {
            D_uvgfxmgr_rom_00402448 = settings->unk16;
        } else {
            D_uvgfxmgr_rom_00402448 = 0xA;
        }
        if (settings->unkE != 0) {
            D_uvgfxmgr_rom_0040242C = settings->unkE;
        } else {
            D_uvgfxmgr_rom_0040242C = 2;
        }
        if (settings->unkC != 0) {
            D_uvgfxmgr_rom_00402440 = settings->unkC;
        } else {
            D_uvgfxmgr_rom_00402440 = 0;
        }
        if (settings->unk18 != 0) {
            D_uvgfxmgr_rom_0040244C = settings->unk18;
        } else {
            D_uvgfxmgr_rom_0040244C = 0x1068;
        }

        for (bufferIndex = 0; bufferIndex < D_uvgfxmgr_rom_0040242C; bufferIndex++) {
            if (settings->unk0[bufferIndex] != 0) {
                sGfxFrameBuffers[bufferIndex] = settings->unk0[bufferIndex];
            } else {
                sGfxFrameBuffers[bufferIndex] = 0;
            }
        }

        for (bufferIndex = 0; bufferIndex < 2; bufferIndex++) {
            if (settings->unk1C[bufferIndex] != 0) {
                sGfxDisplayListBase[bufferIndex] = settings->unk1C[bufferIndex];
            } else {
                sGfxDisplayListBase[bufferIndex] = 0;
            }
        }
    }
    sGfxFrameBuffers[0] = 0x80200000 - (sScreenWidth * 2 * sScreenHeight); /* RE_ORIGINAL_QUIRK: replace the first two configured framebuffers unconditionally; preserve remaining configured entries. */
    sGfxFrameBuffers[1] = 0x80200000;
    uvMemAllocAt((u32) sGfxFrameBuffers[0], sScreenWidth * 4 * sScreenHeight, &reservationPrefixBytes, &reservationSuffixBytes); /* RE_UNKNOWN: counts, dimension arithmetic, allocation success and buffer capacities need caller/allocator proof; results stay ignored. */
#ifdef NON_MATCHING
    uvCrashScreenInit(sGfxFrameBuffers[0]);
#endif
    if (D_uvgfxmgr_rom_00402440 == 0) {
        frameByteCount = sScreenWidth * 2 * sScreenHeight;
        D_uvgfxmgr_rom_00402260 = 0x80400000 - frameByteCount;
        uvMemAllocAt((u32) D_uvgfxmgr_rom_00402260, frameByteCount, &reservationPrefixBytes, &reservationSuffixBytes);
    }
    for (bufferIndex = 0; bufferIndex < 2; bufferIndex++) {
        if (sGfxDisplayListBase[bufferIndex] == NULL) { /* RE_ORIGINAL_QUIRK: either absent base replaces and reserves both display lists; keep the repeated test. */
            sGfxDisplayListBase[0] = (Gfx *) 0x80300000;
            sGfxDisplayListBase[1] = (Gfx *) sGfxDisplayListBase[0] + D_uvgfxmgr_rom_0040244C;
            uvMemAllocAt(sGfxDisplayListBase[0], D_uvgfxmgr_rom_0040244C * 8, &reservationPrefixBytes, &reservationSuffixBytes);
            uvMemAllocAt(sGfxDisplayListBase[1], D_uvgfxmgr_rom_0040244C * 8, &reservationPrefixBytes, &reservationSuffixBytes);
        }
    }

    sUvCbackExports = uvLoadModule('CBCK'); /* CBCK slots 0x04/0x0C create/dispatch lists; RE_UNKNOWN: import failure and callback mutation/lifetimes remain unproved. */
    D_uvgfxmgr_rom_00402620 = sUvCbackExports->uvCreateCallbackList(D_uvgfxmgr_rom_00402446);
    D_uvgfxmgr_rom_00402624 = sUvCbackExports->uvCreateCallbackList(D_uvgfxmgr_rom_00402448);
    sGfxDisplayListIndex = 0;
    D_uvgfxmgr_rom_00402460 = 1;
    sGfxDisplayListHead = sGfxDisplayListBase[sGfxDisplayListIndex];
    D_uvgfxmgr_rom_00402484 = &D_uvgfxmgr_rom_00402488[sGfxDisplayListIndex];
    D_uvgfxmgr_rom_00402470[0] = 0;
    D_uvgfxmgr_rom_00402470[1] = 0;
    D_uvgfxmgr_rom_00402478 = 0;
    D_uvgfxmgr_rom_00402420[2] = 0.0f;
    D_uvgfxmgr_rom_00402420[1] = D_uvgfxmgr_rom_00402420[2];
    D_uvgfxmgr_rom_00402420[0] = D_uvgfxmgr_rom_00402420[2];
    osCreateMesgQueue(&D_uvgfxmgr_rom_004025B8, D_uvgfxmgr_rom_00402590, 10);
    osCreateMesgQueue(&D_uvgfxmgr_rom_004025F8, D_uvgfxmgr_rom_004025D0, 10);
    _uvScAddClient((OSSched *) gScheduler, &D_uvgfxmgr_rom_00402610, &D_uvgfxmgr_rom_004025F8);
    if ((u32) sGfxTaskOutputBuffer & 0xF) { /* Preserve the original conditional +8 adjustment and end-pointer calculation; no alignment repair is inferred. */
        sGfxTaskOutputBufferStart = (u32) sGfxTaskOutputBuffer + 8;
    } else {
        sGfxTaskOutputBufferStart = (u32) sGfxTaskOutputBuffer;
    }
    sGfxTaskOutputBufferEnd = (u32) sGfxTaskOutputBufferStart + 0x2080;
    if (osViGetCurrentFramebuffer() == (void *) 0x100000) {
        uvMemSet(sGfxFrameBuffers[1], 0U, sScreenWidth * 2 * sScreenHeight);
        osViBlack(FALSE);
        osViSwapBuffer(sGfxFrameBuffers[1]);
        sGfxFrameBufferIndex = 0;
        D_uvgfxmgr_rom_00402464 = 1;
    } else if (osViGetCurrentFramebuffer() == sGfxFrameBuffers[0]) { /* Keep the second VI query; RE_UNKNOWN: concurrent display/buffer ownership needs scheduler/caller proof. */
        sGfxFrameBufferIndex = 1;
        D_uvgfxmgr_rom_00402464 = 0;
    } else {
        sGfxFrameBufferIndex = 0;
        D_uvgfxmgr_rom_00402464 = 1;
    }
    sGfxDepthBuffer = sGfxFrameBuffers[sGfxFrameBufferIndex];
    D_uvgfxmgr_rom_00402264 = 0;
}

void uvGfxModuleCleanup(void) {
    uvGfxWaitIfRequested();
    sUvCbackExports->uvCallbackFree(D_uvgfxmgr_rom_00402620);
    sUvCbackExports->uvCallbackFree(D_uvgfxmgr_rom_00402624);
    uvUnloadModule('CBCK');
}

/* Optionally rotate frame/display-list state, emit initial image commands and dispatch begin callbacks. */
#line 139 "src/modules/uvgfxmgr_rom.c"
void uvGfxBegin(void) {
    void *callbackFrameBuffer;

    if (D_uvgfxmgr_rom_00402478 == 1) { /* Only mode 1 rotates here; RE_UNKNOWN: other mode values and buffer/index domains need setter/caller proof. */
        callbackFrameBuffer = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        if (sGfxFrameBufferCallback != NULL) {
            sGfxFrameBufferCallback(callbackFrameBuffer, D_uvgfxmgr_rom_00402260); /* Keep the captured buffer across the callback, then reload dimensions; RE_UNKNOWN: callback mutation/lifetime remains unproved. */
            osWritebackDCache(callbackFrameBuffer, sScreenWidth * sScreenHeight * 2);
        }
        D_uvgfxmgr_rom_00402420[sGfxFrameBufferIndex] = uvClkGetSec(103);
        uvClkReset(103);
        uvScRecordTraceEvent(0, 42);
        D_uvgfxmgr_rom_00402460 = sGfxDisplayListIndex++;
        if (sGfxDisplayListIndex >= 2) {
            sGfxDisplayListIndex = 0;
        }
        D_uvgfxmgr_rom_00402464 = sGfxFrameBufferIndex++;

        if (sGfxFrameBufferIndex >= D_uvgfxmgr_rom_0040242C) {
            sGfxFrameBufferIndex = 0;
        }
        D_uvgfxmgr_rom_00402470[sGfxDisplayListIndex] = 1;
        D_uvgfxmgr_rom_00402484 = &D_uvgfxmgr_rom_00402488[sGfxDisplayListIndex];
        sGfxDepthBuffer = sGfxFrameBuffers[sGfxFrameBufferIndex];
        sGfxDisplayListHead = sGfxDisplayListBase[sGfxDisplayListIndex];
    }
    gSPSegment(sGfxDisplayListHead++, 0, 0); /* RE_UNKNOWN: display-list capacity and asynchronous buffer ownership need allocation/scheduler/caller proof. */
    gDPPipeSync(sGfxDisplayListHead++);
    gDPSetColorImage(sGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sScreenWidth,
                     osVirtualToPhysical(sGfxDepthBuffer));
    gDPSetDepthImage(sGfxDisplayListHead++, osVirtualToPhysical(D_uvgfxmgr_rom_00402260));
    gDPPipeSync(sGfxDisplayListHead++);
    D_uvgfxmgr_rom_00402450 = 0;
    if (D_uvgfxmgr_rom_00402620 != 0) {
        sUvCbackExports->uvExecuteCallbacks(D_uvgfxmgr_rom_00402620, 0); /* Dispatch after command publication; callback-list count is reloaded by the original provider. */
    }
}

Gfx **uvGetDisplayListHead(void) {
    return &sGfxDisplayListHead;
}

void uvGfxDisplayList(Gfx *dl) {
    gSPDisplayList(sGfxDisplayListHead++, dl);
}

#line 185 "src/modules/uvgfxmgr_rom.c"
/* Return graphics callback list one or two, or zero for an unsupported selector. */
s32 uvGfxGetCallbackList(s32 selector) {
    switch (selector) { /* irregular */
        case 1:
            return D_uvgfxmgr_rom_00402620;
        case 2:
            return D_uvgfxmgr_rom_00402624;
        default:
            return 0;
    }
}
#line 195 "src/modules/uvgfxmgr_rom.c"

void (*func_uvgfxmgr_rom_00400AF0(void (*arg0)(void *, void *)))(void *, void *) {
    void (*temp_v0)(void *, void *);

    temp_v0 = sGfxFrameBufferCallback;
    sGfxFrameBufferCallback = arg0;
    return temp_v0;
}

#line 204 "src/modules/uvgfxmgr_rom.c"
/* Exchange the shared word used by graphics submission as an optional callback address.
 * RE_UNKNOWN: historical callback signature, registration/lifetime need original setter users and invoker. */
s32 uvGfxMgrExchangeSharedWord(s32 value) {
    s32 previous;

    previous = D_uvgfxmgr_rom_00402618;
    D_uvgfxmgr_rom_00402618 = value;
    return previous;
}
#line 211 "src/modules/uvgfxmgr_rom.c"

void func_uvgfxmgr_rom_00400B18(s32 arg0) {
    D_uvgfxmgr_rom_00402264 = arg0;
}

/* Finish the display list, populate and submit its graphics task, dispatch callbacks and optionally rotate buffers. */
#line 216 "src/modules/uvgfxmgr_rom.c"
void uvGfxEnd(void) {
    s32 historicalUnusedPad; /* RE_UNKNOWN: retain unused pad locals; historical declarations are unproved. */
    UvGfxStruct *taskRecord;
    s32 historicalUnusedPadWords[2];
    void *callbackFrameBuffer;

    gDPFullSync(sGfxDisplayListHead++);
    gSPEndDisplayList(sGfxDisplayListHead++);
    sGfxElementCount = sGfxDisplayListHead - sGfxDisplayListBase[sGfxDisplayListIndex];
    taskRecord = &D_uvgfxmgr_rom_00402488[sGfxDisplayListIndex]; /* RE_UNKNOWN: task/view extent, display-list capacity and index domains need producer/caller proof. */
    if (D_uvgfxmgr_rom_00402264 == 1) {
        taskRecord->unkC = D_uvgfxmgr_rom_00402260;
    } else {
        taskRecord->unkC = sGfxFrameBuffers[sGfxFrameBufferIndex];
    }
    taskRecord->unk0 = 0;
    taskRecord->unk50 = &D_uvgfxmgr_rom_004025B8;
    taskRecord->unk54 = &D_uvgfxmgr_rom_00402268[sGfxFrameBufferIndex];
    taskRecord->unk8 = 0x53; /* RE_UNKNOWN: full historical task structure/conventions remain unproved; preserve wrapper fields and flags. */
    taskRecord->task.t.type = M_GFXTASK;
    taskRecord->task.t.flags = 0;
    taskRecord->task.t.ucode_boot = (u64 *) rspBootTextStart;
    taskRecord->task.t.ucode_boot_size = rspBootTextEnd - rspBootTextStart;
    taskRecord->task.t.ucode_size = 0x1000;
    taskRecord->task.t.ucode_data_size = 0x800;
    taskRecord->task.t.dram_stack = sGfxDramStack;
    taskRecord->task.t.dram_stack_size = 0x400;
    taskRecord->task.t.data_ptr = (u64 *) sGfxDisplayListBase[sGfxDisplayListIndex];
    taskRecord->task.t.data_size = sGfxElementCount * sizeof(Gfx);
    taskRecord->task.t.yield_data_ptr = sGfxYieldData;
    taskRecord->task.t.yield_data_size = 0xC00;
    taskRecord->task.t.ucode = (u64 *) gspF3DEX2_fifoTextStart;
    taskRecord->task.t.ucode_data = gspF3DEX2_fifoDataStart;
    taskRecord->task.t.output_buff = sGfxTaskOutputBufferStart;
    taskRecord->task.t.output_buff_size = sGfxTaskOutputBufferEnd;
    uvScRecordTraceEvent(0, 0x2B);
    if (D_uvgfxmgr_rom_00402618 != NULL) {
        D_uvgfxmgr_rom_00402618(sGfxFrameBuffers[sGfxFrameBufferIndex], D_uvgfxmgr_rom_00402260); /* Reload index/buffer/dimensions after this callback; RE_UNKNOWN: mutation/reentry and storage lifetime remain unproved. */
        osWritebackDCache((void *) sGfxFrameBuffers[sGfxFrameBufferIndex],
                          sScreenWidth * sScreenHeight * 2);
    }
    osWritebackDCacheAll();
    osSendMesg(_uvScGetCmdQ(gScheduler), taskRecord, 1); /* Blocking submission follows the full cache flush; RE_UNKNOWN: scheduler/completion ownership and failure domains need caller proof. */
    if (D_uvgfxmgr_rom_00402624 != 0) {
        sUvCbackExports->uvExecuteCallbacks(D_uvgfxmgr_rom_00402624, 0);
    }
    if (D_uvgfxmgr_rom_00402478 == 0) { /* Only mode 0 waits/rotates here; preserve the begin/end mode split and callback sequence. */
        if (D_uvgfxmgr_rom_0040247C != 0) {
            uvGfxWaitForMesg(0U);
        }
        D_uvgfxmgr_rom_0040247C = 1;
        callbackFrameBuffer = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        if (sGfxFrameBufferCallback != NULL) {
            sGfxFrameBufferCallback(callbackFrameBuffer, D_uvgfxmgr_rom_00402260); /* This callback keeps its captured buffer for the flush while dimensions are freshly reloaded. */
            osWritebackDCache(callbackFrameBuffer, sScreenWidth * sScreenHeight * 2);
        }
        D_uvgfxmgr_rom_00402420[sGfxFrameBufferIndex] = (f32) uvClkGetSec(0x67);
        uvClkReset(0x67);
        uvScRecordTraceEvent(0, 0x2A);
        D_uvgfxmgr_rom_00402460 = sGfxDisplayListIndex++;
        if (sGfxDisplayListIndex >= 2) {
            sGfxDisplayListIndex = 0;
        }
        D_uvgfxmgr_rom_00402464 = sGfxFrameBufferIndex++;
        if (sGfxFrameBufferIndex >= (s32) D_uvgfxmgr_rom_0040242C) {
            sGfxFrameBufferIndex = 0;
        }
        sGfxDepthBuffer = sGfxFrameBuffers[sGfxFrameBufferIndex];
        sGfxDisplayListHead = sGfxDisplayListBase[sGfxDisplayListIndex];
    }
}

void uvGfxWaitForMesg(u16 arg0) {
    if (!arg0) {
        osRecvMesg(&D_uvgfxmgr_rom_004025B8, NULL, OS_MESG_BLOCK);
    }
}

void func_uvgfxmgr_rom_00400F58(s32 arg0) {
    D_uvgfxmgr_rom_00402478 = arg0;
}

#line 298 "src/modules/uvgfxmgr_rom.c"
/* Poll the current task completion queue without blocking, clear its pending
 * flag on a received message and record the poll. Return whether it is complete. */
s32 uvGfxPollTaskCompletion(void) {
    if ((D_uvgfxmgr_rom_00402470[D_uvgfxmgr_rom_00402460] != 0)
        && (osRecvMesg(&D_uvgfxmgr_rom_004025B8, NULL, 0) == 0)) {
        D_uvgfxmgr_rom_00402470[D_uvgfxmgr_rom_00402460] = 0;
    }
    D_uvgfxmgr_rom_0040247C = 1;
    return D_uvgfxmgr_rom_00402470[D_uvgfxmgr_rom_00402460] == 0;
}
#line 306 "src/modules/uvgfxmgr_rom.c"

#line 307 "src/modules/uvgfxmgr_rom.c"
/* Store the shared graphics scalar override; only positive values are
 * selected by its getter. The scalar unit remains unproven. */
void uvGfxMgrSetScalarOverride(f32 value) {
    D_uvgfxmgr_rom_00402480 = value;
}
#line 310 "src/modules/uvgfxmgr_rom.c"

#line 311 "src/modules/uvgfxmgr_rom.c"
/* Return a positive shared override or the current indexed graphics
 * scalar. Preserve the original zero, negative and unordered comparisons. */
f32 uvGfxMgrGetScalarOverrideOrCurrent(void) {
    if (D_uvgfxmgr_rom_00402480 > 0.0f) {
        return D_uvgfxmgr_rom_00402480;
    }
    return D_uvgfxmgr_rom_00402420[D_uvgfxmgr_rom_00402460];
}
#line 317 "src/modules/uvgfxmgr_rom.c"

void uvGfxEnableGamma(s32 enable) {
    if (enable) {
        osViSetSpecialFeatures(OS_VI_GAMMA_ON);
        return;
    }
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
}

void uvGfxSetPrimColorF(f32 red, f32 green, f32 blue, f32 alpha) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    gDPPipeSync(sGfxDisplayListHead++);
    r = red * 255.0f;
    g = green * 255.0f;
    b = blue * 255.0f;
    a = alpha * 255.0f;
    gDPSetPrimColor(sGfxDisplayListHead++, 0, 0, r & 0xFF, g & 0xFF, (s32) b & 0xFF, a & 0xFF);

    gDPSetFillColor(sGfxDisplayListHead++,
                    GPACK_RGBA5551(r & 0xFF, g & 0xFF, (s32) b & 0xFF, a & 0xFF) << 16
                        | GPACK_RGBA5551(r & 0xFF, g & 0xFF, (s32) b & 0xFF, a & 0xFF));
}

void uvGfxSetPrimColor(s8 red, s8 green, s8 blue, s8 alpha) {
    gDPSetPrimColor(sGfxDisplayListHead++, 0, 0, red, green, blue, alpha);
    gDPSetFillColor(sGfxDisplayListHead++, GPACK_RGBA5551(red, green, blue, alpha) << 16
                                               | GPACK_RGBA5551(red, green, blue, alpha));
}

void uvGfxSetEnvColorF(f32 red, f32 green, f32 blue, f32 alpha) {
    u32 r;
    u32 g;
    u32 b;
    u32 a;
    r = red * 255.0f;
    g = green * 255.0f;
    b = blue * 255.0f;
    a = alpha * 255.0f;
    gDPSetEnvColor(sGfxDisplayListHead++, r & 0xff, g & 0xff, b & 0xff, a & 0xff);
}

void uvGfxSetEnvColor(s8 r, s8 g, s8 b, s8 a) {
    gDPSetEnvColor(sGfxDisplayListHead++, r, g, b, a);
}

void uvGfxSetConvert(s32 arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    gDPSetConvert(sGfxDisplayListHead++, arg0, arg1, arg2, arg3, arg4, arg5);
}

void uvGfxFillRect(u8 red, u8 green, u8 alpha) {
    gDPPipeSync(sGfxDisplayListHead++);

    gDPSetCycleType(sGfxDisplayListHead++, G_CYC_FILL);
    gDPSetFillColor(sGfxDisplayListHead++,
                    GPACK_RGBA5551(red, green, alpha, 1) << 16 | GPACK_RGBA5551(red, green, alpha, 1));
    gDPFillRectangle(sGfxDisplayListHead++, sGfxClipX0, sScreenHeight - sGfxClipY2, sGfxClipX1,
                     sScreenHeight - sGfxClipY1);
    gDPPipeSync(sGfxDisplayListHead++);
    gDPSetCycleType(sGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPSetFillColor(sGfxDisplayListHead++, 0x10001);
}

void uvGfxClearScreen(void) {
    gDPPipeSync(sGfxDisplayListHead++);
    gDPSetCycleType(sGfxDisplayListHead++, G_CYC_FILL);
    gDPSetFillColor(sGfxDisplayListHead++, 0);
    gDPFillRectangle(sGfxDisplayListHead++, 0, sScreenWidth, 0, sScreenHeight);
    gDPPipeSync(sGfxDisplayListHead++);
    gDPSetCycleType(sGfxDisplayListHead++, G_CYC_2CYCLE);
    gDPSetFillColor(sGfxDisplayListHead++, 0x10001);
}

#line 393 "src/modules/uvgfxmgr_rom.c"

void uvGfxClipRect(uvGfxViewport *vp, s32 firstXBound, s32 secondXBound, s32 firstYBound, s32 secondYBound) {
    s32 horizontalSpan;
    s32 verticalSpan;

    vp->x0 = firstXBound;
    vp->x1 = secondXBound;
    vp->y0 = firstYBound;
    vp->y1 = secondYBound;
    if (vp->x0 < 0) {
        vp->x0 = 0;
    } else if (vp->x0 > sScreenWidth) {
        vp->x0 = sScreenWidth;
    }

    if (vp->x1 < 0) {
        vp->x1 = 0;
    } else if (vp->x1 > sScreenWidth) {
        vp->x1 = sScreenWidth;
    }

    if (vp->y1 < 0) {
        vp->y1 = 0;
    } else if (vp->y1 > sScreenHeight) {
        vp->y1 = sScreenHeight;
    }

    if (vp->y0 < 0) {
        vp->y0 = 0;
    } else if (vp->y0 > sScreenHeight) {
        vp->y0 = sScreenHeight;
    }

    vp->unk0 = vp->x0;
    if (vp->unk0 < 0) {
        vp->unk0 = 0;
    }
    vp->unk2 = vp->x1;
    if (vp->unk2 > sScreenWidth - 1) {
        vp->unk2 = sScreenWidth - 1;
    }
    vp->unk4 = vp->y0;
    if (vp->unk4 < 0) {
        vp->unk4 = 0;
    }
    vp->unk6 = vp->y1;
    if (vp->unk6 > sScreenHeight - 1) {
        vp->unk6 = sScreenHeight - 1;
    }

    horizontalSpan = vp->unk2 - vp->unk0;
    verticalSpan = vp->unk6 - vp->unk4;

    vp->vp.vp.vscale[0] = (horizontalSpan << 1);
    vp->vp.vp.vscale[1] = (verticalSpan << 1);
    vp->vp.vp.vscale[2] = 0x1FF;
    vp->vp.vp.vscale[3] = 0;
    vp->vp.vp.vtrans[0] = (u16) ((vp->unk0 + (horizontalSpan >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[1] = (u16) (((sScreenHeight - vp->unk4) - (verticalSpan >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[2] = 0x1FF;
    vp->vp.vp.vtrans[3] = 0;
    sGfxClipX0 = vp->x0;
    sGfxClipX1 = vp->x1;
    sGfxClipY1 = vp->y0;
    sGfxClipY2 = vp->y1;
}
#line 458 "src/modules/uvgfxmgr_rom.c"

#line 459 "src/modules/uvgfxmgr_rom.c"
/* Emit a viewport and advance the cursor only when its stored index is below eleven.
 * RE_UNKNOWN: nonnegative index/backing extent need original cursor producers and callers. */
void uvGfxAppendViewport(s32 left, s32 right, s32 bottom, s32 top) {
    uvGfxViewport *viewport;

    viewport = &D_uvgfxmgr_rom_004022C8[D_uvgfxmgr_rom_00402450];
    if (D_uvgfxmgr_rom_00402450 < 0xB) {
        uvGfxClipRect(viewport, left, right, bottom, top);
        uvGfxApplyViewport(D_uvgfxmgr_rom_00402450);
        D_uvgfxmgr_rom_00402450 += 1;
    }
}
#line 469 "src/modules/uvgfxmgr_rom.c"

#line 470 "src/modules/uvgfxmgr_rom.c"
/* Emit the viewport and scissor commands, then cache the clip rectangle.
 * Preserve the original screen-height Y conversion and unchecked viewport ID. */
void uvGfxApplyViewport(s32 vp_id) {
    uvGfxViewport *vp;
    vp = &D_uvgfxmgr_rom_004022C8[vp_id];

    gSPViewport(sGfxDisplayListHead++, OS_PHYSICAL_TO_K0(&vp->vp));
    gDPSetScissor(sGfxDisplayListHead++, G_SC_NON_INTERLACE, vp->x0, sScreenHeight - vp->y1, vp->x1,
                  sScreenHeight - vp->y0);
    sGfxClipX0 = vp->x0;
    sGfxClipX1 = vp->x1;
    sGfxClipY1 = vp->y0;
    sGfxClipY2 = vp->y1;
}
#line 482 "src/modules/uvgfxmgr_rom.c"

void uvGfxPersp(s16 persp) {
    gSPPerspNormalize(sGfxDisplayListHead++, persp);
}

#line 487 "src/modules/uvgfxmgr_rom.c"
/* Fill the current viewport of the depth-image buffer with 0xFFFC,
 * then restore the original color-image target and two-cycle mode. */
void uvGfxClearDepthImageViewport(void) {
    uvGfxViewport *viewport;

    if ((D_uvgfxmgr_rom_00402260 != NULL) && (sGfxDepthBuffer != NULL)) {
        viewport = &D_uvgfxmgr_rom_004022C8[D_uvgfxmgr_rom_00402450 - 1];

        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetRenderMode(sGfxDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetCycleType(sGfxDisplayListHead++, G_CYC_FILL);
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetFillColor(sGfxDisplayListHead++, 0xFFFCFFFC);
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetColorImage(sGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sScreenWidth,
                         osVirtualToPhysical(D_uvgfxmgr_rom_00402260));
        gDPPipeSync(sGfxDisplayListHead++);
        gDPFillRectangle(sGfxDisplayListHead++, viewport->x0, sScreenHeight - viewport->y1, viewport->x1,
                         sScreenHeight - viewport->y0);
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetColorImage(sGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sScreenWidth,
                         osVirtualToPhysical(sGfxDepthBuffer));
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetCycleType(sGfxDisplayListHead++, G_CYC_2CYCLE);
        gDPPipeSync(sGfxDisplayListHead++);
    }
}
#line 513 "src/modules/uvgfxmgr_rom.c"

#line 514 "src/modules/uvgfxmgr_rom.c"
/* Return the buffer installed by this module as the RDP depth image.
 * This is also temporarily used as a color-image target by depth passes. */
void *uvGfxGetDepthImageBuffer(void) {
    return D_uvgfxmgr_rom_00402260;
}
#line 517 "src/modules/uvgfxmgr_rom.c"

#line 518 "src/modules/uvgfxmgr_rom.c"
/* Return the framebuffer selected by the current framebuffer index. */
s32 uvGfxGetCurrentFramebuffer(void) {
    return sGfxFrameBuffers[sGfxFrameBufferIndex];
}
#line 521 "src/modules/uvgfxmgr_rom.c"

#line 522 "src/modules/uvgfxmgr_rom.c"
/* Return the framebuffer selected by the alternate shared index. Its
 * producer/consumer timing retains the original graphics-manager contract. */
s32 uvGfxGetAlternateFramebuffer(void) {
    return sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
}
#line 525 "src/modules/uvgfxmgr_rom.c"

#line 526 "src/modules/uvgfxmgr_rom.c"
/* When the shared wait-request flag is set, wait through the original
 * graphics-message helper and clear the flag afterward. */
void uvGfxWaitIfRequested(void) {
    if (D_uvgfxmgr_rom_0040247C != 0) {
        uvGfxWaitForMesg(0);
        D_uvgfxmgr_rom_0040247C = 0;
    }
}
#line 532 "src/modules/uvgfxmgr_rom.c"

/* Copy between current and alternate framebuffers for selectors 0/1, preserving the optional completion wait. */
#line 533 "src/modules/uvgfxmgr_rom.c"
void uvCopyFrameBuf(s32 copyDirection) {
    s32 sourceBufferAddress; /* RE_UNKNOWN: retain integer-held pointer words; historical types, overlap and storage extents need caller proof. */
    s32 destinationBufferAddress;

    if ((copyDirection >= 0) && (copyDirection < 2)) {
        if (copyDirection != 0) {
            sourceBufferAddress = sGfxFrameBuffers[sGfxFrameBufferIndex];
            destinationBufferAddress = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        } else {
            sourceBufferAddress = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
            destinationBufferAddress = sGfxFrameBuffers[sGfxFrameBufferIndex];
        }
        uvGfxWaitIfRequested(); /* Capture both addresses before waiting, then reload dimensions; RE_UNKNOWN: buffer ownership/lifetime needs caller proof. */
        _uvMediaCopy((void *) destinationBufferAddress, (void *) sourceBufferAddress, sScreenWidth * sScreenHeight * 2);
        osWritebackDCacheAll();
    }
}

void uvSetScreenHeight(s32 height) {
    sScreenHeight = height;
}

void uvSetScreenWidth(s32 width) {
    sScreenWidth = width;
}

s32 uvGetScreenHeight(void) {
    return sScreenHeight;
}

s32 uvGetScreenWidth(void) {
    return sScreenWidth;
}

#line 567 "src/modules/uvgfxmgr_rom.c"
/* Append the shared visibility-coverage display list, including its original
 * fixed 320-by-240 fill rectangle and primitive-depth render state. */
void uvGfxEmitCoverageFill(void) {
    gSPDisplayList(sGfxDisplayListHead++, D_uvgfxmgr_rom_00402278);
}
#line 570 "src/modules/uvgfxmgr_rom.c"

void uvGfxSetDepthSource(s32 usePrimitiveDepth) {
    gDPSetDepthSource(sGfxDisplayListHead++, usePrimitiveDepth ? G_ZS_PRIM : G_ZS_PIXEL);
}

void uvGfxPrimDepth(s32 z) {
    gDPSetPrimDepth(sGfxDisplayListHead++, z, 0);
}
