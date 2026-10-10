// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "libaudio.h"
#include "module.h"

#define AUDIO_DEFAULT_SAMPLE_RATE 0x5622
#define AUDIO_DEFAULT_MAX_VOICES 0x10
#define AUDIO_DEFAULT_DMA_BUF_COUNT 0x10
#define AUDIO_DEFAULT_DMA_BUF_SIZE 0x800
#define AUDIO_DEFAULT_CMD_LIST_COUNT 0x3E8
#define AUDIO_DEFAULT_MAX_UPDATES 0x100

typedef struct {
    ALLink node;
    u32 startAddr;
    u32 lastFrame;
    char *ptr;
} AMDMABuffer;

typedef struct {
    u8 initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;

typedef union {
    struct {
        short type;
    } gen;
    struct {
        short type;
        struct AudioInfo *info;
    } done;
    OSScMsg app;
} AudioMsg;

typedef struct AudioInfo {
    s16 *data;
    s16 frameSamples;
    OSScTask task;
    AudioMsg msg;
} AudioInfo; // size 0x80

typedef struct AMAudioMgr {
    Acmd *ACMDList[2];
    AudioInfo *audioInfo[3];
    OSThread thread;
    OSMesgQueue audioFrameMsgQ;
    OSMesg audioFrameMsgBuf[8];
    OSMesgQueue audioReplyMsgQ;
    OSMesg audioReplyMsgBuf[8];
    ALGlobals g;
} AMAudioMgr;

typedef struct AudioMgr_Settings_s {
    /* 0x00 */ u16 dmaBufCount;   /* inferred */
    /* 0x02 */ u16 dmaBufSize;    /* inferred */
    /* 0x04 */ u16 aCmdListCount; /* inferred */
    /* 0x06 */ char pad6[2];
    /* 0x08 */ s32 heapSize;       /* inferred */
    /* 0x0C */ void *heapBase;     /* inferred */
    /* 0x10 */ u16 maxVoices;  /* inferred */
    /* 0x12 */ u16 maxUpdates; /* inferred */
    /* 0x14 */ u16 unk14;      /* inferred */
    /* 0x16 */ char pad16[2];
    /* 0x18 */ u32 sampleRate; /* inferred */
    /* 0x1C */ u16 unk1C;      /* inferred */
    /* 0x1E */ u16 unk1E;      /* inferred */
    /* 0x20 */ char pad20[2];
} AudioMgr_Settings; /* size = 0x22 */

typedef struct UnkStruct_uvaudiomgr_rom_0040130C_s {
    char pad[0x8];
    s32 unk8[1];
} UnkStruct_uvaudiomgr_rom_0040130C;

extern s32 D_uvaudiomgr_rom_00401304;
extern s32 D_uvaudiomgr_rom_00405748;
extern s32 sAudioHeapSize;
extern AMDMABuffer *sAudioDmaBuffers;
extern AMAudioMgr sAudioMgrInfo;
extern UnkStruct_uvaudiomgr_rom_0040130C *D_uvaudiomgr_rom_0040130C;
extern s32 D_uvaudiomgr_rom_00401310;
extern s32 D_uvaudiomgr_rom_00405418;
extern OSMesgQueue D_uvaudiomgr_rom_004055F0;
extern void *D_uvaudiomgr_rom_00405608;
extern OSMesgQueue D_uvaudiomgr_rom_00405628;
extern void *D_uvaudiomgr_rom_00405640;
extern ALGlobals sAudioGlobals;
extern s32 D_uvaudiomgr_rom_004056CC;
extern OSMesgQueue D_uvaudiomgr_rom_004056D8;
extern void **D_uvaudiomgr_rom_004056F0;
extern OSMesgQueue D_uvaudiomgr_rom_004056F8;
extern void *D_uvaudiomgr_rom_00405710;
extern u16 sAudioDmaBufCount;
extern u16 D_uvaudiomgr_rom_00405716;
extern u16 sAudioDmaBufSize;
extern u16 sAudioCmdListCount;
extern u16 sAudioMaxVoices;
extern u16 sAudioMaxUpdates;
extern u32 sAudioSampleRate;
extern UvCback_Exports *sUvCbackExports_audiomgr;
extern OSIoMesg *D_uvaudiomgr_rom_004056D0;
extern void *sAudioHeapBase;
extern u16 D_uvaudiomgr_rom_0040577C;
extern s32 D_uvaudiomgr_rom_00405780;
extern void *D_uvaudiomgr_rom_00405784;
extern void *D_uvaudiomgr_rom_00405788;
extern s32 D_uvaudiomgr_rom_004056C4;
extern s32 D_uvaudiomgr_rom_004056C8;
extern OSScClient sSchedulerClient;
extern s32 D_uvaudiomgr_rom_00405430[];
extern u32 sAudioFrameCount;
extern OSSched *gScheduler;
extern s32 D_uvaudiomgr_rom_00401300;
extern AMDMAState sAudioDmaState;
extern u16 D_uvaudiomgr_rom_00405728; // unused
extern u16 D_uvaudiomgr_rom_00405730;
extern u16 D_uvaudiomgr_rom_00405732;
extern f32 D_uvaudiomgr_rom_00405734;
extern f32 D_uvaudiomgr_rom_00405738;
extern s32 D_uvaudiomgr_rom_0040573C;
extern ALSynConfig sAudioSynthConf;
extern f32 D_uvaudiomgr_rom_00405740;

s32 uvGetAudioHeapSize(void);
void uvCreateAudioMgr(ALSynConfig *arg0, s32 pri);
void uvAudioMgrCleanup(void);
void uvAudioMgrConfigureFrameSampleCounts(void);
void uvAudioMgrThreadFunc(void *arg0);
s32 uvAudioMgrHandleFrameMesg(AudioInfo *info, AudioInfo *previousInfo);
void uvAudioMgrHandleDoneMesg(s32 arg0);
s32 uvAudioMgrDma(s32 addr, s32 len, UNUSED void *state);
s32 (*uvAudioMgrDmaNew(AMDMAState **state))(s32, s32, void *);
void uvAudioMgrClearDma(void);
void uvAudioMgrReservedCallback0(void);
void uvAudioMgrReservedCallback1(void);
void *uvAudioMgrGetFrameCallbackList(s32 arg0);
void uvAudioMgrSetEffectsVolume(f32 arg0);
void uvAudioMgrGetEffectsVolume(f32 *arg0);
void uvAudioMgrSetSequenceVolume(f32 arg0);
void uvAudioMgrGetSequenceVolume(f32 *arg0);
void uvAudioMgrSetOutputMode(s32 arg0);
void uvAudioMgrGetOutputMode(s32 *arg0);
void uvAudioMgrSetSharedScalar40(f32 arg0);
void uvAudioMgrGetSharedScalar40(f32 *arg0);
s32 uvAudioMgrGetEffectsHeaderWord(void);
void uvAudioMgrSetEffectsMatrixParameter(s32 arg0, s32 arg1, s32 arg2);
s32 uvAudioMgrGetEffectsMatrixParameter(s32 arg0, s32 arg1);
void uvAudioMgrLatchShutdown(void);
void __entrypoint_func_uvaudiomgr_rom_40000c(UvAudioMgr_Exports *exports);

s32 uvGetAudioHeapSize(void) {
    return sAudioHeapSize;
}

void __entrypoint_func_uvaudiomgr_rom_40000c(UvAudioMgr_Exports *exports) { /* Publish seventeen audio exports, apply default-backed settings, initialize heap and DMA storage, start the audio manager and create the optional callback lists. RE_UNKNOWN: Settings ownership, full configuration layouts, allocation success, capacities and callback lifetime remain unproved. */
    AudioMgr_Settings *audioSettings;
    s32 heapBytes;

    uvUpdateFileAllocPtr(exports);
    exports->uvAudioMgrCleanup = uvAudioMgrCleanup;
    exports->uvAudioMgrGetOutputMode = uvAudioMgrGetOutputMode;
    exports->uvGetAudioHeapSize = uvGetAudioHeapSize;
    exports->uvAudioMgrSetSharedScalar40 = uvAudioMgrSetSharedScalar40;
    exports->uvAudioMgrReservedCallback0 = uvAudioMgrReservedCallback0;
    exports->uvAudioMgrGetSharedScalar40 = uvAudioMgrGetSharedScalar40;
    exports->uvAudioMgrReservedCallback1 = uvAudioMgrReservedCallback1;
    exports->uvAudioMgrGetEffectsHeaderWord = uvAudioMgrGetEffectsHeaderWord;
    exports->uvAudioMgrGetFrameCallbackList = uvAudioMgrGetFrameCallbackList;
    exports->uvAudioMgrSetEffectsMatrixParameter = uvAudioMgrSetEffectsMatrixParameter;
    exports->uvAudioMgrSetEffectsVolume = uvAudioMgrSetEffectsVolume;
    exports->uvAudioMgrGetEffectsMatrixParameter = uvAudioMgrGetEffectsMatrixParameter;
    exports->uvAudioMgrGetEffectsVolume = uvAudioMgrGetEffectsVolume;
    exports->uvAudioMgrLatchShutdown = uvAudioMgrLatchShutdown;
    exports->uvAudioMgrSetSequenceVolume = uvAudioMgrSetSequenceVolume;
    exports->uvAudioMgrGetSequenceVolume = uvAudioMgrGetSequenceVolume;
    exports->uvAudioMgrSetOutputMode = uvAudioMgrSetOutputMode;
    D_uvaudiomgr_rom_00405734 = 1.0f;
    D_uvaudiomgr_rom_00405738 = 1.0f;
    D_uvaudiomgr_rom_0040573C = 2;
    D_uvaudiomgr_rom_00405740 = 0.0f;
    audioSettings = uvGetSystemProp(SYSTEM_PROPID_AUDIOMGR_SETTINGS);
    if (audioSettings == NULL) { /* Each zero settings field also selects its own default in the nonnull path. */
        sAudioDmaBufCount = AUDIO_DEFAULT_DMA_BUF_COUNT;
        sAudioDmaBufSize = 0x800;
        sAudioCmdListCount = 0x3E8;
        sAudioMaxUpdates = 0x100;
        D_uvaudiomgr_rom_00405728 = 0x100;
        sAudioMaxVoices = AUDIO_DEFAULT_MAX_VOICES;
        sAudioSampleRate = AUDIO_DEFAULT_SAMPLE_RATE;
        D_uvaudiomgr_rom_00405730 = 0xA;
        D_uvaudiomgr_rom_00405732 = 0xA;
        sAudioHeapSize = 0;
        sAudioHeapBase = NULL;
    } else {
        if (audioSettings->dmaBufCount != 0) {
            sAudioDmaBufCount = audioSettings->dmaBufCount;
        } else {
            sAudioDmaBufCount = AUDIO_DEFAULT_DMA_BUF_COUNT;
        }
        if (audioSettings->dmaBufSize != 0) {
            sAudioDmaBufSize = audioSettings->dmaBufSize;
        } else {
            sAudioDmaBufSize = AUDIO_DEFAULT_DMA_BUF_SIZE;
        }
        if (audioSettings->aCmdListCount != 0) {
            sAudioCmdListCount = audioSettings->aCmdListCount;
        } else {
            sAudioCmdListCount = AUDIO_DEFAULT_CMD_LIST_COUNT;
        }
        if (audioSettings->maxUpdates != 0) {
            sAudioMaxUpdates = audioSettings->maxUpdates;
        } else {
            sAudioMaxUpdates = AUDIO_DEFAULT_MAX_UPDATES;
        }
        if (audioSettings->unk14 != 0) {
            D_uvaudiomgr_rom_00405728 = audioSettings->unk14;
        } else {
            D_uvaudiomgr_rom_00405728 = 0x100;
        }
        if (audioSettings->maxVoices != 0) {
            sAudioMaxVoices = audioSettings->maxVoices;
        } else {
            sAudioMaxVoices = AUDIO_DEFAULT_MAX_VOICES;
        }
        if (audioSettings->sampleRate != 0) {
            sAudioSampleRate = audioSettings->sampleRate;
        } else {
            sAudioSampleRate = AUDIO_DEFAULT_SAMPLE_RATE;
        }
        if (audioSettings->unk1C != 0) {
            D_uvaudiomgr_rom_00405730 = audioSettings->unk1C;
        } else {
            D_uvaudiomgr_rom_00405730 = 0xA;
        }
        if (audioSettings->unk1E != 0) {
            D_uvaudiomgr_rom_00405732 = audioSettings->unk1E;
        } else {
            D_uvaudiomgr_rom_00405732 = 0xA;
        }
        sAudioHeapSize = audioSettings->heapSize;
        sAudioHeapBase = audioSettings->heapBase;
    }
    uvAudioMgrConfigureFrameSampleCounts();
    if (sAudioHeapBase == NULL) { /* Only an absent heap base sets the original allocation flag; preserve supplied heap storage. */
        heapBytes = sAudioHeapSize;
        if (heapBytes == 0) { /* Keep the original size arithmetic, including its existing casts and unchecked overflow. */
            heapBytes = sAudioHeapSize =
                ((sAudioDmaBufCount) * (sAudioDmaBufSize)) + ((sAudioCmdListCount & 0xFFFF) * 0x10)
                + (D_uvaudiomgr_rom_004056CC * 0xC) + (sAudioMaxUpdates * 0x1C)
                + (sAudioMaxVoices * 0x214) + 0x322C;
        }
        D_uvaudiomgr_rom_0040577C |= 1;
        sAudioHeapBase = _uvMemAllocAlign8((u32) heapBytes);
    }

    D_uvaudiomgr_rom_00405716 = (u16) (s32) (sAudioDmaBufCount * 1.5); /* Preserve the double multiply, truncation and final halfword conversion. */
    sAudioDmaBuffers = _uvMemAllocAlign8(sAudioDmaBufCount * 0x14);
    uvMemSet(sAudioDmaBuffers, 0U, sAudioDmaBufCount * 0x14);
    D_uvaudiomgr_rom_004056D0 = _uvMemAllocAlign8(D_uvaudiomgr_rom_00405716 * 0x18);
    uvMemSet(D_uvaudiomgr_rom_004056D0, 0U, D_uvaudiomgr_rom_00405716 * 0x18);
    D_uvaudiomgr_rom_004056F0 = _uvMemAllocAlign8(D_uvaudiomgr_rom_00405716 * 4);
    uvMemSet(D_uvaudiomgr_rom_004056F0, 0U, D_uvaudiomgr_rom_00405716 * 4);
    uvMemSet(sAudioHeapBase, 0U, (u32) sAudioHeapSize); /* The original clears supplied heap storage too; no allocation-result checks are added. */
    alHeapInit((ALHeap *) &D_uvaudiomgr_rom_00405748, (u8 *) sAudioHeapBase,
               sAudioHeapSize);
    sAudioSynthConf.heap = (ALHeap *) &D_uvaudiomgr_rom_00405748;
    uvCreateAudioMgr(&sAudioSynthConf, 0x6E); /* Preserve manager creation before the following message send. */
    osSendMesg(&D_uvaudiomgr_rom_004056F8, NULL, 1);
    if (((s32) D_uvaudiomgr_rom_00405730 > 0) || ((s32) D_uvaudiomgr_rom_00405732 > 0)) { /* Either positive count triggers both list calls, even when the other count is zero. */
        sUvCbackExports_audiomgr = uvLoadModule('CBCK');
        D_uvaudiomgr_rom_00405784 =
            sUvCbackExports_audiomgr->uvCreateCallbackList(D_uvaudiomgr_rom_00405730);
        D_uvaudiomgr_rom_00405788 =
            sUvCbackExports_audiomgr->uvCreateCallbackList(D_uvaudiomgr_rom_00405732);
    }
}

void uvCreateAudioMgr(ALSynConfig *synthConfig, s32 threadPriority) { /* Configure the audio synthesizer, link and allocate DMA buffers, allocate command and frame buffers, create four message queues, then create and start thread 3. RE_UNKNOWN: Heap ownership, allocation success, full configuration and buffer layouts, and the supported DMA count domain remain unproved. */
    s32 bufferIndex;

    synthConfig->maxVVoices = sAudioMaxVoices;
    synthConfig->maxPVoices = sAudioMaxVoices;
    synthConfig->maxUpdates = sAudioMaxUpdates;
    synthConfig->dmaproc = NULL;
    synthConfig->maxFXbusses = 8;
    synthConfig->fxType = 6;
    synthConfig->outputRate = 0;

    // Preserve the original check after storing effect type 6; do not fold the branch.
    if (synthConfig->fxType == 6) {
        synthConfig->params = &D_uvaudiomgr_rom_00401310;
    }

    synthConfig->dmaproc = &uvAudioMgrDmaNew;
    synthConfig->outputRate = osAiSetFrequency(sAudioSampleRate); /* Preserve the frequency call return as the configured output rate. */
    alInit(&sAudioGlobals, synthConfig);
    D_uvaudiomgr_rom_0040130C = alSynGetFXRef(&sAudioGlobals.drvr, 0, 0);
    sAudioDmaBuffers->node.prev = NULL;
    sAudioDmaBuffers->node.next = NULL;

    for (bufferIndex = 0; bufferIndex < sAudioDmaBufCount - 1; bufferIndex++) { /* Keep the fresh DMA count and heap reads around each link and allocation call. */
        alLink(&sAudioDmaBuffers[bufferIndex + 1].node, &sAudioDmaBuffers[bufferIndex].node);
        sAudioDmaBuffers[bufferIndex].ptr = alHeapDBAlloc(NULL, 0, synthConfig->heap, 1, sAudioDmaBufSize);
    }

    sAudioDmaBuffers[bufferIndex].ptr = alHeapDBAlloc(NULL, 0, synthConfig->heap, 1, (s32) sAudioDmaBufSize); /* The tail allocation remains unconditional even when the preceding loop does not run. */

    for (bufferIndex = 0; bufferIndex < 2; bufferIndex++) { /* Allocate two command buffers using the existing count times eight expression. */
        sAudioMgrInfo.ACMDList[bufferIndex] =
            alHeapDBAlloc(NULL, 0, synthConfig->heap, 1, sAudioCmdListCount * 8);
    }

    for (bufferIndex = 0; bufferIndex < 3; bufferIndex++) { /* Each frame block is 0x80 bytes; retain its completion type, self-pointer and separate sample allocation. */
        sAudioMgrInfo.audioInfo[bufferIndex] = alHeapDBAlloc(NULL, 0, synthConfig->heap, 1, 0x80);
        sAudioMgrInfo.audioInfo[bufferIndex]->msg.done.type = 2;
        sAudioMgrInfo.audioInfo[bufferIndex]->msg.done.info = sAudioMgrInfo.audioInfo[bufferIndex];
        sAudioMgrInfo.audioInfo[bufferIndex]->data =
            alHeapDBAlloc(NULL, 0, synthConfig->heap, 1, D_uvaudiomgr_rom_004056CC * 4);
    }

    osCreateMesgQueue(&D_uvaudiomgr_rom_00405628, &D_uvaudiomgr_rom_00405640, 8);
    osCreateMesgQueue(&D_uvaudiomgr_rom_004055F0, &D_uvaudiomgr_rom_00405608, 8);
    osCreateMesgQueue(&D_uvaudiomgr_rom_004056D8, D_uvaudiomgr_rom_004056F0,
                      (s32) D_uvaudiomgr_rom_00405716);
    osCreateMesgQueue(&D_uvaudiomgr_rom_004056F8, &D_uvaudiomgr_rom_00405710, 1);
    osCreateThread(&sAudioMgrInfo.thread, 3, uvAudioMgrThreadFunc, NULL, &D_uvaudiomgr_rom_00405418, threadPriority);
    osStartThread(&sAudioMgrInfo.thread); /* All four queue creations and the caller-priority thread creation precede the start call. */
}

#line 332 "src/modules/uvaudiomgr_rom.c"
/* Destroy the audio thread, close synthesis, release owned heap/DMA storage
 * and callback lists, unload callbacks and latch shutdown in original order. */
void uvAudioMgrCleanup(void) {
    osDestroyThread(&sAudioMgrInfo.thread);
    alClose(&sAudioGlobals);
    if (D_uvaudiomgr_rom_0040577C & 1) {
        _uvMemFree(sAudioHeapBase);
    }
    _uvMemFree(sAudioDmaBuffers);
    _uvMemFree(D_uvaudiomgr_rom_004056D0);
    _uvMemFree(D_uvaudiomgr_rom_004056F0);
    sUvCbackExports_audiomgr->uvCallbackFree(D_uvaudiomgr_rom_00405784);
    sUvCbackExports_audiomgr->uvCallbackFree(D_uvaudiomgr_rom_00405788);
    uvUnloadModule('CBCK');
    D_uvaudiomgr_rom_00405780 = 1;
}
#line 346 "src/modules/uvaudiomgr_rom.c"

#line 347 "src/modules/uvaudiomgr_rom.c"
/* Derive PAL/NTSC frame sample counts from the actual audio frequency,
 * round upward to sixteen and retain the original minimum/maximum margins.
 * The original routine assumes a supported television mode. */
void uvAudioMgrConfigureFrameSampleCounts(void) {
    s32 frequency;
    f32 samplesPerFrame;
    s32 unused;

    frequency = osAiSetFrequency(sAudioSampleRate);
    switch (osTvType) { /* irregular */
        case OS_TV_PAL:
            samplesPerFrame = ((f32) frequency * 1) / 50.0f;
            break;
        case OS_TV_NTSC:
        case OS_TV_MPAL:
            samplesPerFrame = ((f32) frequency * 1) / 60.0f;
            break;
        default:
            break;
    }

    D_uvaudiomgr_rom_004056C8 = samplesPerFrame;

    if (D_uvaudiomgr_rom_004056C8 < samplesPerFrame) {
        D_uvaudiomgr_rom_004056C8++;
    }
    if (D_uvaudiomgr_rom_004056C8 & 0xF) {
        D_uvaudiomgr_rom_004056C8 = (D_uvaudiomgr_rom_004056C8 & ~0xF) + 0x10;
    }

    D_uvaudiomgr_rom_004056C4 = D_uvaudiomgr_rom_004056C8 - 0x10;
    D_uvaudiomgr_rom_004056CC = D_uvaudiomgr_rom_004056C8 + 0x110;
}
#line 377 "src/modules/uvaudiomgr_rom.c"

void uvAudioMgrThreadFunc(void *arg0) {
    s32 temp_s0;
    s32 var_s1;
    AudioMsg *msg;

    s32 done;
    done = FALSE;
    msg = NULL;
    var_s1 = 0;
    osRecvMesg(&D_uvaudiomgr_rom_004056F8, (OSMesg*)&msg, 1);

    _uvScAddClient(gScheduler, &sSchedulerClient, &D_uvaudiomgr_rom_004055F0);

    while (!done) {
        if (var_s1) { }
        osRecvMesg(&D_uvaudiomgr_rom_004055F0, (OSMesg*)&msg, 1);
        if (D_uvaudiomgr_rom_00405780 == 0) {
            uvScRecordTraceEvent(0U, 0x29);
            switch (msg->gen.type) { /* irregular */
                case 4:
                    break;
                case 1:
                    temp_s0 = uvAudioMgrHandleFrameMesg(
                        D_uvaudiomgr_rom_00405430[(u32) sAudioFrameCount % 3U], var_s1);
                    if (D_uvaudiomgr_rom_00405784 != NULL) {
                        sUvCbackExports_audiomgr->uvExecuteCallbacks(
                            (CallbackList *) D_uvaudiomgr_rom_00405784, 0);
                    }
                    if (temp_s0 != 0) {
                        osRecvMesg(&D_uvaudiomgr_rom_00405628, (OSMesg*)&msg, 1);
                        uvAudioMgrHandleDoneMesg(msg->done.info);
                        var_s1 = msg->done.info;
                    }
                    if (D_uvaudiomgr_rom_00405788 != NULL) {
                        sUvCbackExports_audiomgr->uvExecuteCallbacks(
                            (CallbackList *) D_uvaudiomgr_rom_00405788, 0);
                    }
                    break;
                case 10:
                    done = TRUE;
                    break;
            }
        }
    }

    alClose(&sAudioGlobals);
}

s32 uvAudioMgrHandleFrameMesg(AudioInfo *info, AudioInfo *previousInfo) {
    u32 audioPtr;
    Acmd *sp38;
    s32 cmdLen;
    s32 pad;

    uvProfilerSetAllPaused(1);
    uvAudioMgrClearDma();
    audioPtr = osVirtualToPhysical(info->data);
    if (previousInfo != NULL) {
        osAiSetNextBuffer(previousInfo->data, previousInfo->frameSamples * 4);
    }
    info->frameSamples = ((D_uvaudiomgr_rom_004056C8 - (osAiGetLength() >> 2)) + 0x110) & 0xFFF0;
    if (info->frameSamples < D_uvaudiomgr_rom_004056C4) {
        info->frameSamples = (s16) D_uvaudiomgr_rom_004056C4;
    }
    if (D_uvaudiomgr_rom_004056CC < info->frameSamples) {
        info->frameSamples = (s16) D_uvaudiomgr_rom_004056CC;
    }
    if (audioPtr == 0) {
        PANIC; // fault
    }

    func_8000D7F0(&D_uvaudiomgr_rom_00405748);
    sp38 = alAudioFrame(sAudioMgrInfo.ACMDList[D_uvaudiomgr_rom_00401304], &cmdLen,
                        (s16 *) audioPtr, (s32) info->frameSamples);
    func_8000D7F0(&D_uvaudiomgr_rom_00405748);
    if (cmdLen == 0) {
        return 0;
    }
    info->task.next = NULL;
    info->task.msgQ = &D_uvaudiomgr_rom_00405628;
    info->task.msg = &info->msg;
    info->task.flags = 1;
    info->task.list.t.data_ptr = (u64 *) sAudioMgrInfo.ACMDList[D_uvaudiomgr_rom_00401304];
    info->task.list.t.data_size =
        (sp38 - sAudioMgrInfo.ACMDList[D_uvaudiomgr_rom_00401304]) * sizeof(Acmd);
    info->task.list.t.type = 2;
    info->task.list.t.ucode_boot = (u64 *) rspBootTextStart;
    info->task.list.t.ucode_boot_size =
        (u64 *) ((u32) gspF3DEX2_fifoTextStart - (u32) rspBootTextStart);
    info->task.list.t.flags = 0;
    info->task.list.t.ucode = (u64 *) aspMainTextStart;
    info->task.list.t.ucode_data = (u64 *) aspMainDataStart;
    info->task.list.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    info->task.list.t.yield_data_ptr = NULL;
    info->task.list.t.yield_data_size = 0;
    info->task.list.t.dram_stack_size = 0;
    info->task.list.t.dram_stack = NULL;
    uvScRecordTraceEvent(0U, 0x2C);
    uvProfilerSetAllPaused(0);
    osSendMesg(_uvScGetCmdQ(gScheduler), &info->task, 1);
    D_uvaudiomgr_rom_00401304 ^= 1;
    return 1;
}

// stubbed
void uvAudioMgrHandleDoneMesg(s32 arg0) {
}

s32 uvAudioMgrDma(s32 addr, s32 len, UNUSED void *state) {
    void *foundBuffer;
    AMDMABuffer *dmaPtr;
    AMDMABuffer *lastDmaPtr;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;

    dmaPtr = sAudioDmaState.firstUsed;
    lastDmaPtr = NULL;

    addrEnd = addr + len;

    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + sAudioDmaBufSize;
        if ((u32) addr < dmaPtr->startAddr) {
            break;
        }

        if (buffEnd >= addrEnd) {
            dmaPtr->lastFrame = sAudioFrameCount;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *) dmaPtr->node.next;
    }

    dmaPtr = sAudioDmaState.firstFree;

    sAudioDmaState.firstFree = (AMDMABuffer *) dmaPtr->node.next;
    alUnlink(&dmaPtr->node);
    if (lastDmaPtr != NULL) {
        alLink(&dmaPtr->node, &lastDmaPtr->node);
    } else if (sAudioDmaState.firstUsed != NULL) {
        lastDmaPtr = sAudioDmaState.firstUsed;
        sAudioDmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = &lastDmaPtr->node;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = &dmaPtr->node;
    } else {
        sAudioDmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }

    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = sAudioFrameCount;
    osPiStartDma((OSIoMesg *) &D_uvaudiomgr_rom_004056D0[D_uvaudiomgr_rom_00401300++], OS_MESG_PRI_HIGH,
                 OS_READ, addr, foundBuffer, sAudioDmaBufSize, &D_uvaudiomgr_rom_004056D8);
    return osVirtualToPhysical(foundBuffer) + delta;
}

s32 (*uvAudioMgrDmaNew(AMDMAState **state))(s32, s32, void *) {
    if (sAudioDmaState.initialized == 0) {
        sAudioDmaState.firstUsed = NULL;
        sAudioDmaState.firstFree = sAudioDmaBuffers;
        sAudioDmaState.initialized = 1;
    }
    *state = &sAudioDmaState;
    return uvAudioMgrDma;
}

void uvAudioMgrClearDma(void) {
    AMDMABuffer *dmaPtr;
    void *ioMesg;
    AMDMABuffer *nextPtr;
    s32 i;

    ioMesg = NULL;
    for (i = 0; i < D_uvaudiomgr_rom_00401300; i++) {
        osRecvMesg(&D_uvaudiomgr_rom_004056D8, &ioMesg, 0);
    }
    dmaPtr = sAudioDmaState.firstUsed;
    while (dmaPtr != NULL) {
        nextPtr = (AMDMABuffer *)dmaPtr->node.next;
        if (dmaPtr->lastFrame + 2 < sAudioFrameCount) {
            if (dmaPtr == sAudioDmaState.firstUsed) {
                sAudioDmaState.firstUsed = (AMDMABuffer *) dmaPtr->node.next;
            }
            alUnlink(&dmaPtr->node);
            if (sAudioDmaState.firstFree != NULL) {
                alLink(&dmaPtr->node, &sAudioDmaState.firstFree->node);
            } else {
                sAudioDmaState.firstFree = dmaPtr;
                dmaPtr->node.next = NULL;
                dmaPtr->node.prev = NULL;
            }
        }
        dmaPtr = (AMDMABuffer *) nextPtr;
    }
    D_uvaudiomgr_rom_00401300 = 0;
    sAudioFrameCount += 1;
}

#line 584 "src/modules/uvaudiomgr_rom.c"
/* Original empty audio-manager callback; retain its entry point. */
void uvAudioMgrReservedCallback0(void) {
}
#line 586 "src/modules/uvaudiomgr_rom.c"

#line 587 "src/modules/uvaudiomgr_rom.c"
/* Original second empty audio-manager callback; retain its entry point. */
void uvAudioMgrReservedCallback1(void) {
}
#line 589 "src/modules/uvaudiomgr_rom.c"

#line 590 "src/modules/uvaudiomgr_rom.c"
/* Return pre-frame list one, post-frame list two, or null for other IDs. */
void *uvAudioMgrGetFrameCallbackList(s32 listId) {
    switch (listId) { /* irregular */
        case 1:
            return D_uvaudiomgr_rom_00405784;
        case 2:
            return D_uvaudiomgr_rom_00405788;
        default:
            return NULL;
    }
}
#line 600 "src/modules/uvaudiomgr_rom.c"

#line 601 "src/modules/uvaudiomgr_rom.c"
/* Store shared effects volume. RE_UNKNOWN: accepted range/units need original callers and audio consumers. */
void uvAudioMgrSetEffectsVolume(f32 volume) {
    D_uvaudiomgr_rom_00405734 = volume;
}
#line 604 "src/modules/uvaudiomgr_rom.c"

#line 605 "src/modules/uvaudiomgr_rom.c"
/* Copy the shared effects-volume scalar to caller storage. */
void uvAudioMgrGetEffectsVolume(f32 *volume) {
    *volume = D_uvaudiomgr_rom_00405734;
}
#line 608 "src/modules/uvaudiomgr_rom.c"

#line 609 "src/modules/uvaudiomgr_rom.c"
/* Store shared sequence volume. RE_UNKNOWN: accepted range/units need original callers and audio consumers. */
void uvAudioMgrSetSequenceVolume(f32 volume) {
    D_uvaudiomgr_rom_00405738 = volume;
}
#line 612 "src/modules/uvaudiomgr_rom.c"

#line 613 "src/modules/uvaudiomgr_rom.c"
/* Copy the shared sequence-volume scalar to caller storage. */
void uvAudioMgrGetSequenceVolume(f32 *volume) {
    *volume = D_uvaudiomgr_rom_00405738;
}
#line 616 "src/modules/uvaudiomgr_rom.c"

#line 617 "src/modules/uvaudiomgr_rom.c"
/* Store the shared audio output mode without additional validation. */
void uvAudioMgrSetOutputMode(s32 mode) {
    D_uvaudiomgr_rom_0040573C = mode;
}
#line 620 "src/modules/uvaudiomgr_rom.c"

#line 621 "src/modules/uvaudiomgr_rom.c"
/* Copy the shared audio output mode to caller storage. */
void uvAudioMgrGetOutputMode(s32 *mode) {
    *mode = D_uvaudiomgr_rom_0040573C;
}
#line 624 "src/modules/uvaudiomgr_rom.c"

#line 625 "src/modules/uvaudiomgr_rom.c"
/* Store audio-manager scalar 0x40. Its detailed role remains unproven. */
void uvAudioMgrSetSharedScalar40(f32 value) {
    D_uvaudiomgr_rom_00405740 = value;
}
#line 628 "src/modules/uvaudiomgr_rom.c"

#line 629 "src/modules/uvaudiomgr_rom.c"
/* Copy audio-manager scalar 0x40 to caller storage. */
void uvAudioMgrGetSharedScalar40(f32 *value) {
    *value = D_uvaudiomgr_rom_00405740;
}
#line 632 "src/modules/uvaudiomgr_rom.c"

#line 633 "src/modules/uvaudiomgr_rom.c"
/* Return the first word of the current synthesizer effects object. */
s32 uvAudioMgrGetEffectsHeaderWord(void) {
    s32 *effectsWords = (s32 *) D_uvaudiomgr_rom_0040130C;
    return *effectsWords;
}
#line 637 "src/modules/uvaudiomgr_rom.c"

#line 638 "src/modules/uvaudiomgr_rom.c"
/* For row and column in [0, 8), set the corresponding synthesizer
 * effects parameter numbered row * 8 + column + 2. */
void uvAudioMgrSetEffectsMatrixParameter(s32 row, s32 column, s32 value) {
    if ((row >= 0) && (row < 8) && (column >= 0) && (column < 8)) {
        alSynSetFXParam(&sAudioGlobals.drvr, D_uvaudiomgr_rom_0040130C,
                        (s16) ((row * 8) + column + 2), &value);
    }
}
#line 644 "src/modules/uvaudiomgr_rom.c"

#line 645 "src/modules/uvaudiomgr_rom.c"
/* Return the stored eight-by-eight effects value, or -1 for invalid indices. */
s32 uvAudioMgrGetEffectsMatrixParameter(s32 row, s32 column) {
    UnkStruct_uvaudiomgr_rom_0040130C *effects = D_uvaudiomgr_rom_0040130C;
    if ((row >= 0) && (row < 8) && (column >= 0) && (column < 8)) {
        return ((UnkStruct_uvaudiomgr_rom_0040130C *) ((u8 *) effects + (row << 4 << 1)))->unk8[column];
    }
    return -1;
}
#line 652 "src/modules/uvaudiomgr_rom.c"

#line 653 "src/modules/uvaudiomgr_rom.c"
/* Set the original shutdown latch so the audio thread stops processing frames. */
void uvAudioMgrLatchShutdown(void) {
    D_uvaudiomgr_rom_00405780 = 1;
}
#line 656 "src/modules/uvaudiomgr_rom.c"
