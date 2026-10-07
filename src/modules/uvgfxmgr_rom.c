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
} GfxMgrSettings; /* size = 0x18 */

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
void func_uvgfxmgr_rom_00401DC4(void);
void *func_uvgfxmgr_rom_0040204C(void);
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

void __entrypoint_func_uvgfxmgr_rom_400000(UvGfxMgr_Exports *exports) {
    GfxMgrSettings *settings;
    s32 temp_lo;
    u32 sp54;
    u32 sp50;
    s32 *var_v1;
    s32 i;

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
    exports->func_uvgfxmgr_rom_00401DC4 = func_uvgfxmgr_rom_00401DC4;
    exports->uvGfxSetPrimColor = uvGfxSetPrimColor;
    exports->uvGfxEmitCoverageFill = uvGfxEmitCoverageFill;
    exports->func_uvgfxmgr_rom_0040204C = func_uvgfxmgr_rom_0040204C;
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
    uvMemAllocAt(sGfxTaskOutputBuffer, 0x2080, &sp54, &sp50);
    sGfxYieldData = malloc16(0xC00);
    settings = uvGetSystemProp(SYSTEM_PROPID_GFX_SETTINGS);
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

        for (i = 0; i < D_uvgfxmgr_rom_0040242C; i++) {
            if (settings->unk0[i] != 0) {
                sGfxFrameBuffers[i] = settings->unk0[i];
            } else {
                sGfxFrameBuffers[i] = 0;
            }
        }

        for (i = 0; i < 2; i++) {
            if (settings->unk1C[i] != 0) {
                sGfxDisplayListBase[i] = settings->unk1C[i];
            } else {
                sGfxDisplayListBase[i] = 0;
            }
        }
    }
    sGfxFrameBuffers[0] = 0x80200000 - (sScreenWidth * 2 * sScreenHeight);
    sGfxFrameBuffers[1] = 0x80200000;
    uvMemAllocAt((u32) sGfxFrameBuffers[0], sScreenWidth * 4 * sScreenHeight, &sp54, &sp50);
#ifdef NON_MATCHING
    uvCrashScreenInit(sGfxFrameBuffers[0]);
#endif
    if (D_uvgfxmgr_rom_00402440 == 0) {
        temp_lo = sScreenWidth * 2 * sScreenHeight;
        D_uvgfxmgr_rom_00402260 = 0x80400000 - temp_lo;
        uvMemAllocAt((u32) D_uvgfxmgr_rom_00402260, temp_lo, &sp54, &sp50);
    }
    for (i = 0; i < 2; i++) {
        if (sGfxDisplayListBase[i] == NULL) {
            sGfxDisplayListBase[0] = (Gfx *) 0x80300000;
            sGfxDisplayListBase[1] = (Gfx *) sGfxDisplayListBase[0] + D_uvgfxmgr_rom_0040244C;
            uvMemAllocAt(sGfxDisplayListBase[0], D_uvgfxmgr_rom_0040244C * 8, &sp54, &sp50);
            uvMemAllocAt(sGfxDisplayListBase[1], D_uvgfxmgr_rom_0040244C * 8, &sp54, &sp50);
        }
    }

    sUvCbackExports = uvLoadModule('CBCK');
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
    if ((u32) sGfxTaskOutputBuffer & 0xF) {
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
    } else if (osViGetCurrentFramebuffer() == sGfxFrameBuffers[0]) {
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

void uvGfxBegin(void) {
    void *frameBuffer;

    if (D_uvgfxmgr_rom_00402478 == 1) {
        frameBuffer = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        if (sGfxFrameBufferCallback != NULL) {
            sGfxFrameBufferCallback(frameBuffer, D_uvgfxmgr_rom_00402260);
            osWritebackDCache(frameBuffer, sScreenWidth * sScreenHeight * 2);
        }
        D_uvgfxmgr_rom_00402420[sGfxFrameBufferIndex] = uvClkGetSec(103);
        uvClkReset(103);
        func_80004958(0, 42);
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
    gSPSegment(sGfxDisplayListHead++, 0, 0);
    gDPPipeSync(sGfxDisplayListHead++);
    gDPSetColorImage(sGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sScreenWidth,
                     osVirtualToPhysical(sGfxDepthBuffer));
    gDPSetDepthImage(sGfxDisplayListHead++, osVirtualToPhysical(D_uvgfxmgr_rom_00402260));
    gDPPipeSync(sGfxDisplayListHead++);
    D_uvgfxmgr_rom_00402450 = 0;
    if (D_uvgfxmgr_rom_00402620 != 0) {
        sUvCbackExports->uvExecuteCallbacks(D_uvgfxmgr_rom_00402620, 0);
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
/* Store the caller word and return its previous shared value.
 * The word meaning and valid range remain caller-defined. */
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

void uvGfxEnd(void) {
    s32 pad;
    UvGfxStruct *temp_a3;
    s32 pad2[2];
    void *frameBuffer;

    gDPFullSync(sGfxDisplayListHead++);
    gSPEndDisplayList(sGfxDisplayListHead++);
    sGfxElementCount = sGfxDisplayListHead - sGfxDisplayListBase[sGfxDisplayListIndex];
    temp_a3 = &D_uvgfxmgr_rom_00402488[sGfxDisplayListIndex];
    if (D_uvgfxmgr_rom_00402264 == 1) {
        temp_a3->unkC = D_uvgfxmgr_rom_00402260;
    } else {
        temp_a3->unkC = sGfxFrameBuffers[sGfxFrameBufferIndex];
    }
    temp_a3->unk0 = 0;
    temp_a3->unk50 = &D_uvgfxmgr_rom_004025B8;
    temp_a3->unk54 = &D_uvgfxmgr_rom_00402268[sGfxFrameBufferIndex];
    temp_a3->unk8 = 0x53;
    temp_a3->task.t.type = M_GFXTASK;
    temp_a3->task.t.flags = 0;
    temp_a3->task.t.ucode_boot = (u64 *) rspBootTextStart;
    temp_a3->task.t.ucode_boot_size = rspBootTextEnd - rspBootTextStart;
    temp_a3->task.t.ucode_size = 0x1000;
    temp_a3->task.t.ucode_data_size = 0x800;
    temp_a3->task.t.dram_stack = sGfxDramStack;
    temp_a3->task.t.dram_stack_size = 0x400;
    temp_a3->task.t.data_ptr = (u64 *) sGfxDisplayListBase[sGfxDisplayListIndex];
    temp_a3->task.t.data_size = sGfxElementCount * sizeof(Gfx);
    temp_a3->task.t.yield_data_ptr = sGfxYieldData;
    temp_a3->task.t.yield_data_size = 0xC00;
    temp_a3->task.t.ucode = (u64 *) gspF3DEX2_fifoTextStart;
    temp_a3->task.t.ucode_data = gspF3DEX2_fifoDataStart;
    temp_a3->task.t.output_buff = sGfxTaskOutputBufferStart;
    temp_a3->task.t.output_buff_size = sGfxTaskOutputBufferEnd;
    func_80004958(0, 0x2B);
    if (D_uvgfxmgr_rom_00402618 != NULL) {
        D_uvgfxmgr_rom_00402618(sGfxFrameBuffers[sGfxFrameBufferIndex], D_uvgfxmgr_rom_00402260);
        osWritebackDCache((void *) sGfxFrameBuffers[sGfxFrameBufferIndex],
                          sScreenWidth * sScreenHeight * 2);
    }
    osWritebackDCacheAll();
    osSendMesg(_uvScGetCmdQ(gScheduler), temp_a3, 1);
    if (D_uvgfxmgr_rom_00402624 != 0) {
        sUvCbackExports->uvExecuteCallbacks(D_uvgfxmgr_rom_00402624, 0);
    }
    if (D_uvgfxmgr_rom_00402478 == 0) {
        if (D_uvgfxmgr_rom_0040247C != 0) {
            uvGfxWaitForMesg(0U);
        }
        D_uvgfxmgr_rom_0040247C = 1;
        frameBuffer = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        if (sGfxFrameBufferCallback != NULL) {
            sGfxFrameBufferCallback(frameBuffer, D_uvgfxmgr_rom_00402260);
            osWritebackDCache(frameBuffer, sScreenWidth * sScreenHeight * 2);
        }
        D_uvgfxmgr_rom_00402420[sGfxFrameBufferIndex] = (f32) uvClkGetSec(0x67);
        uvClkReset(0x67);
        func_80004958(0, 0x2A);
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

void uvGfxClipRect(uvGfxViewport *vp, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 var_a2;
    s32 var_a3;

    vp->x0 = arg1;
    vp->x1 = arg2;
    vp->y0 = arg3;
    vp->y1 = arg4;
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

    var_a2 = vp->unk2 - vp->unk0;
    var_a3 = vp->unk6 - vp->unk4;

    vp->vp.vp.vscale[0] = (var_a2 << 1);
    vp->vp.vp.vscale[1] = (var_a3 << 1);
    vp->vp.vp.vscale[2] = 0x1FF;
    vp->vp.vp.vscale[3] = 0;
    vp->vp.vp.vtrans[0] = (u16) ((vp->unk0 + (var_a2 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[1] = (u16) (((sScreenHeight - vp->unk4) - (var_a3 >> 1)) & 0xFFFF) << 2;
    vp->vp.vp.vtrans[2] = 0x1FF;
    vp->vp.vp.vtrans[3] = 0;
    sGfxClipX0 = vp->x0;
    sGfxClipX1 = vp->x1;
    sGfxClipY1 = vp->y0;
    sGfxClipY2 = vp->y1;
}

#line 459 "src/modules/uvgfxmgr_rom.c"
/* Configure and emit the next viewport, then advance the viewport cursor.
 * Preserve the original less-than-eleven guard and caller-owned index bounds. */
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

void func_uvgfxmgr_rom_00401DC4(void) {
    uvGfxViewport *vp;

    if ((D_uvgfxmgr_rom_00402260 != NULL) && (sGfxDepthBuffer != NULL)) {
        vp = &D_uvgfxmgr_rom_004022C8[D_uvgfxmgr_rom_00402450 - 1];

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
        gDPFillRectangle(sGfxDisplayListHead++, vp->x0, sScreenHeight - vp->y1, vp->x1,
                         sScreenHeight - vp->y0);
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetColorImage(sGfxDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sScreenWidth,
                         osVirtualToPhysical(sGfxDepthBuffer));
        gDPPipeSync(sGfxDisplayListHead++);
        gDPSetCycleType(sGfxDisplayListHead++, G_CYC_2CYCLE);
        gDPPipeSync(sGfxDisplayListHead++);
    }
}

void *func_uvgfxmgr_rom_0040204C(void) {
    return D_uvgfxmgr_rom_00402260;
}

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

void uvCopyFrameBuf(s32 arg0) {
    s32 var_a1;
    s32 var_a0;

    if ((arg0 >= 0) && (arg0 < 2)) {
        if (arg0 != 0) {
            var_a1 = sGfxFrameBuffers[sGfxFrameBufferIndex];
            var_a0 = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
        } else {
            var_a1 = sGfxFrameBuffers[D_uvgfxmgr_rom_00402464];
            var_a0 = sGfxFrameBuffers[sGfxFrameBufferIndex];
        }
        uvGfxWaitIfRequested();
        _uvMediaCopy((void *) var_a0, (void *) var_a1, sScreenWidth * sScreenHeight * 2);
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
