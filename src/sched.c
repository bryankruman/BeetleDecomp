// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "os.h"
#include <PR/sched.h>

typedef struct UnkStruct_8022B6CC {
    s32 unk0;
    s32 unk4;
} UnkStruct_8022B6CC_t;

typedef struct UnkStruct_8002DAE0_inner_s {
    double clockSec;
    u32 unk8;
    u32 unkC;
} UnkStruct_8002DAE0_inner;

typedef struct UnkStruct_8002DAE0_s {
    UnkStruct_8002DAE0_inner vals[30];
} UnkStruct_8002DAE0;

#define VIDEO_MSG 666
#define RSP_DONE_MSG 667
#define RDP_DONE_MSG 668
#define PRE_NMI_MSG 669

extern OSViMode D_8024B7D0[];
extern s32 D_802B9C58;
extern OSScTask *D_8002EE00[];
extern OSScTask *D_8002EDF8;
extern u8 D_8002F250;
extern u8 gSchedRspStatus;
extern u8 gSchedRdpStatus;
extern u8 D_8002F253;
extern u8 D_8002F254;
extern u8 D_8002F255;
extern u8 D_8002F256;
extern u8 D_8002F257;
extern u8 D_8002F258;
extern s32 D_8002F25C;
extern s32 D_8002F260;
extern s32 D_8002F264;
extern s32 D_8002F268;
extern s32 gNmiAsserted;
extern OSSched *gScheduler;
extern s32 gSchedRingIdx;
extern s32 D_8001F7C0;
extern s32 D_8001F7C4;
extern OSScTask *D_8002EE08;
extern s32 D_8002F26C;
extern OSMesgQueue D_8002EE10;
extern OSMesg D_8002EE28[];
extern s32 gSchedStack[];
extern OSSched D_8002F278[];
extern OSSched *gScheduler;
extern f64 D_8002EDD0[];
extern s32 D_8001F7C0;
extern s32 D_8002EDA0[];
extern s32 D_8002EDB8[];

extern UnkStruct_8002DAE0 D_8002DAE0[];
extern UnkStruct_8002DAE0 D_8002E440[];

void _uvScMain(void *);
void func_800048DC(void);
void _uvScRunGfx(void);
void uvScRecordTraceEvent(u8, s32);
void uvScAdvanceTraceRing(void);
void _uvScCreateScheduler(OSSched *sc, void *stack, s32 priority, u8 mode, u8 numFields);
void _uvScHandleRetrace(void);
void _uvScHandleRSP(void);
void _uvScHandleRDP(void);
void _uvScHandleNMI(void);

/*
 * Create the auxiliary ten-message queue and choose the PAL, NTSC or MPAL LAN1
 * mode from osTvType, falling back to PAL. Install the static scheduler and
 * start it with priority 0x7F and one field per retrace event.
 */
#line 74 "src/sched.c"
void uvSetVideoMode(void) {
    s32 viMode;
    OSSched *temp;

    osCreateMesgQueue(&D_8002EE10, D_8002EE28, 0xA);

    switch (osTvType) {
        case OS_TV_PAL:
            viMode = OS_VI_PAL_LAN1;
            break;
        case OS_TV_NTSC:
            viMode = OS_VI_NTSC_LAN1;
            break;
        case OS_TV_MPAL:
            viMode = OS_VI_MPAL_LAN1;
            break;
        default:
            viMode = OS_VI_PAL_LAN1;
            break;
    }

    temp = gScheduler = D_8002F278;
    _uvScCreateScheduler(temp, gSchedStack, 0x7F, viMode, 1);
}

#line 99 "src/sched.c"
/* Drain the scheduler interrupt queue without blocking, then clear the
 * tracked audio/graphics task pointers, RSP/RDP state and timeout counters.
 * RE_UNKNOWN: required scheduler lifecycle or synchronization at entry;
 * trace original callers before using this reset while tasks are active. */
void uvScDrainInterruptsAndResetTaskState(void) {
    OSMesg discardedMessage;
    int zeroState;
    while (osRecvMesg(&gScheduler->interruptQ, &discardedMessage, OS_MESG_NOBLOCK) != -1) {
    }

    zeroState = D_8002F257 = 0;
    D_8002F258 = zeroState;
    D_8002EE00[1] = D_8002EDF8 = NULL;
    D_8002EE00[0] = NULL;
    gSchedRspStatus = gSchedRdpStatus = D_8002F254 = D_8002F253 = 0;
}
#line 111 "src/sched.c"

/*
 * Complete the current graphics slot only outside NMI, after RSP graphics, RDP
 * work and yielded-state handling have finished. Send the blocking completion
 * message before setting the byte-sized display delay and retiring the slot.
 * Preserve delay truncation and the separate immediate versus deferred
 * framebuffer swaps, including swap suppression.
 */
#line 112 "src/sched.c"
void _uvScDoneGfx(void) {
    OSScTask *temp_a3;

    temp_a3 = D_8002EE00[D_8002F256];
    if (!gNmiAsserted) {
        if (temp_a3 == NULL) {
            func_800048DC();
            return;
        }
        if ((D_8002F254 == 0) && (gSchedRspStatus != 0x67) && (gSchedRdpStatus == 0)) {
            uvScRecordTraceEvent(FALSE, 0x32);
            osSendMesg(temp_a3->msgQ, temp_a3->msg, 1);
            if (D_8001F7C4 < D_8001F7C0) {
                D_8002F250 = (D_8001F7C0 - D_8001F7C4) + 1;
            } else {
                D_8002F250 = 1;
                if (D_8002F26C == 0) {
                    osViSwapBuffer(temp_a3->framebuffer);
                }
            }
            D_8002EE08 = D_8002EE00[D_8002F256];
            D_8002EE00[D_8002F256] = NULL;
        }
    }
}

/*
 * For an outstanding audio task, record completion, send its blocking
 * notification unless NMI is asserted, then clear the audio pointer. Attempt
 * to resume the current graphics slot even during NMI; its own start gate
 * decides whether a yielded task may continue.
 */
#line 138 "src/sched.c"
void _uvScDoneAud(void) {
    if (D_8002EDF8 != NULL) {
        uvScRecordTraceEvent(TRUE, 0x2C);
        if (!gNmiAsserted) {
            osSendMesg(D_8002EDF8->msgQ, D_8002EDF8->msg, 1);
        }
        D_8002EDF8 = NULL;
        if (D_8002EE00[D_8002F256] != NULL) {
            _uvScRunGfx();
        }
    }
}

/*
 * Start a queued audio task only before NMI: set the RSP state to audio,
 * record its start, write back the data cache, then load and start the task.
 * Preserve that operation order and the live global task-pointer reads.
 */
#line 151 "src/sched.c"
void _uvScRunAud(void) {
    if ((!gNmiAsserted) && (D_8002EDF8 != NULL)) {
        gSchedRspStatus = 0x61;
        uvScRecordTraceEvent(TRUE, 0x29);
        osWritebackDCacheAll();
        osSpTaskLoad(&D_8002EDF8->list);
        osSpTaskStartGo(&D_8002EDF8->list);
    }
}

/*
 * Start or resume the current graphics slot only when the RSP is not already
 * running graphics and current/next framebuffers agree. A yielded task may
 * resume during NMI or existing RDP graphics work. Count a new task and mark
 * RDP busy only on its first start; record the event before clearing both
 * yield flags and loading the task.
 */
#line 161 "src/sched.c"
void _uvScRunGfx(void) {
    OSScTask *scTask;

    scTask = D_8002EE00[D_8002F256];
    if (((gNmiAsserted == 0) || (D_8002F254 != 0)) && (scTask != NULL) && (gSchedRspStatus != 'g')
        && ((D_8002F254 != 0) || (gSchedRdpStatus != 'g'))) {
        if (osViGetCurrentFramebuffer() == osViGetNextFramebuffer()) {
            gSchedRspStatus = 'g';
            if (D_8002F254 == 0) {
                D_8002F25C += 1;
                gSchedRdpStatus = 'g';
            }
            uvScRecordTraceEvent(TRUE, 0x2A);
            D_8002F254 = D_8002F253 = 0;
            osWritebackDCacheAll();
            osSpTaskLoad(&scTask->list);
            osSpTaskStartGo(&scTask->list);
        }
    }
}

/*
 * Write the original 0x2902 SP status control word, then enqueue nonblocking
 * synthetic RSP/RDP completion messages for each nonzero tracked state. The
 * handler does not itself clear those states and preserves ignored queue-send
 * failures.
 */
#line 182 "src/sched.c"
void _uvScDlistRecover(void) {
    // _uvDebugPrintf("Recovered from a bad display list\n");

    IO_WRITE(SP_STATUS_REG, 0x2902);
    if (gSchedRspStatus != 0) {
        osSendMesg(&gScheduler->interruptQ, (void *) RSP_DONE_MSG, 0);
    }
    if (gSchedRdpStatus != 0) {
        osSendMesg(&gScheduler->interruptQ, (void *) RDP_DONE_MSG, 0);
    }
}

/*
 * Reset the private task, pacing and trace state; initialize scheduler queues
 * and task-list fields; configure VI and SP/DP/pre-NMI notifications; then
 * start scheduler thread four at the supplied priority. Reset the trace clock
 * after thread startup. Preserve the literal initial framebuffer pointer,
 * list-tail addresses and inherited empty matching conditional.
 */
#line 194 "src/sched.c"
void _uvScCreateScheduler(OSSched *sc, void *stack, s32 priority, u8 mode, u8 numFields) {

    gScheduler = sc;
    D_8002EE00[1] = 0;
    D_8002EE00[0] = 0;
    D_8002EDF8 = 0;
    D_8002F250 = 0;
    gSchedRspStatus = 0;
    gSchedRdpStatus = 0;
    D_8002F253 = 0;
    D_8002F254 = 0;
    D_8002F255 = 0;
    D_8002F256 = 0;
    D_8002F257 = 0;
    D_8002F258 = 0;
    D_8002F25C = 0;
    gSchedRingIdx = 0;
    D_8002F260 = 0;
    gNmiAsserted = FALSE;
    D_8002F264 = 1;
    D_8002F268 = 1;

    if ((sc && sc) != 0) {
    } // fakematch

    sc->clientList = 0;
    sc->curRSPTask = 0;
    sc->curRDPTask = 0;
    sc->frameCount = 0;
    sc->audioListHead = 0;
    sc->gfxListHead = 0;
    sc->audioListTail = (OSScTask *) &sc->audioListHead;
    sc->gfxListTail = (OSScTask *) &sc->gfxListHead;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;
    sc->prenmiMsg.type = OS_SC_PRE_NMI_MSG;

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    osViBlack(TRUE);
    osViSwapBuffer((void *) 0x100000);
    osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_GAMMA_DITHER_ON);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg) RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg) RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg) PRE_NMI_MSG);
    osViSetEvent(&sc->interruptQ, (OSMesg) VIDEO_MSG, (u32) numFields);

    osCreateThread(&sc->thread, 4, _uvScMain, (void *) sc, stack, priority);
    osStartThread(&sc->thread);

    uvClkReset(0x69);
    uvScAdvanceTraceRing();
}

/*
 * Clear the global scheduler client-list head without notifying, unlinking or
 * freeing the former clients.
 */
#line 249 "src/sched.c"
void _uvScInitClientList(void) {
    gScheduler->clientList = NULL;
}

/*
 * Prepend the caller-owned client to this scheduler and store its message
 * queue. Preserve the unchecked insertion; no allocation, duplicate test or
 * synchronization is performed here.
 */
#line 253 "src/sched.c"
void _uvScAddClient(OSSched *sc, OSScClient *client, OSMesgQueue *mq) {
    client->msgQ = mq;
    client->next = sc->clientList;
    sc->clientList = (OSScClient *) client;
}

/*
 * Search by client pointer and unlink a matching non-head client.
 * RE_ORIGINAL_QUIRK: the initial predecessor link points to the local
 * traversal variable, so removing the head leaves sc->clientList unchanged.
 * Preserve that native behavior and the unused public entrypoint.
 */
#line 259 "src/sched.c"
UNUSED void _uvScRemoveClient(OSSched *sc, OSScClient *c) {
    OSScClient *client;
    OSScClient **prevNext;


    for (client = sc->clientList, prevNext = &client; client != NULL; client = client->next) {
        if (client == c) {
            *prevNext = c->next;
            return;
        }
        prevNext = &client->next;
    }
}

/*
 * Return the address of the supplied scheduler command queue through the
 * original s32 result type. Preserve the existing 32-bit pointer-return
 * representation and ABI.
 */
#line 273 "src/sched.c"
s32 _uvScGetCmdQ(OSSched *s) {
    return &s->cmdQ;
}

/*
 * Block on the global scheduler interrupt queue and dispatch retrace, RSP-
 * done, RDP-done and pre-NMI messages forever. The thread argument is unused;
 * unrecognized messages are silently ignored.
 */
#line 277 "src/sched.c"
void _uvScMain(void *arg0) {
    OSMesg msg;
    msg = NULL;

    while (1) {
        osRecvMesg(&gScheduler->interruptQ, &msg, 1);

        switch ((int) msg) {
            case VIDEO_MSG:
                _uvScHandleRetrace();
                break;
            case RSP_DONE_MSG:
                _uvScHandleRSP();
                break;
            case RDP_DONE_MSG:
                _uvScHandleRDP();
                break;
            case PRE_NMI_MSG:
                _uvScHandleNMI();
                break;
            default:
                //_uvDebugPrintf("unknown sched interrupt mesg: 0x%x\n", msg);
                break;
        }
    }
}

/*
 * Update clocks even after NMI. Otherwise advance byte-sized RSP/RDP
 * watchdogs, recover at 51 RSP retraces or an RDP lead above 50, pace the two
 * graphics slots and drain queued tasks. Prioritize audio by yielding
 * graphics; active audio, recovery and a repeated yield request return before
 * client notification. RE_ORIGINAL_QUIRK: command receipt can overwrite either
 * graphics slot or the single audio slot without a fullness check; client
 * notifications are nonblocking and their failures are ignored.
 */
#line 304 "src/sched.c"
void _uvScHandleRetrace(void) {
    OSScTask *sp34;
    OSScClient *var_s0;
    char pad[0x4];

    sp34 = NULL;
    uvClkUpdate();
    if (!gNmiAsserted) {
        D_8002F264 = 1;
        if (gSchedRspStatus != 0) {
            D_8002F258 += 1;
        } else {
            D_8002F258 = 0;
        }
        if (gSchedRdpStatus != 0) {
            D_8002F257 += 1;
        } else {
            D_8002F257 = 0;
        }
        if ((s32) D_8002F258 >= 0x33) {
            func_800048DC();
            _uvScDlistRecover();
            return;
        }
        if ((D_8002F258 + 50) < (s32) D_8002F257) {
            D_8002F257 = 0;
            func_800048DC();
            osSendMesg(&gScheduler->interruptQ, (void *) 0x29C, 0);
            return;
        }
        D_8001F7C4 += 1;
        if (gSchedRspStatus == 'a') {
            return;
        }

        if (D_8002F250) {
            if (D_8002F250 == 2) {
                if (D_8002F26C == 0) {
                    osViSwapBuffer(D_8002EE08->framebuffer);
                }
                D_8002EE08 = NULL;
            }

            if (!(--D_8002F250)) {
                uvScAdvanceTraceRing();
                D_8002F256 ^= 1;
                D_8001F7C4 = 0;
            }
        }

        while (osRecvMesg(&gScheduler->cmdQ, (OSMesg)&sp34, 0) != -1) {
            if (sp34 == NULL) {
                break;
            }

            if (sp34->list.t.type == 1) {
                D_8002EE00[D_8002F255] = (OSScTask *) sp34;
                D_8002F255 ^= 1;
            } else if (sp34->list.t.type == 2) {
                D_8002EDF8 = (OSScTask *) sp34;
            }
        }
        if (D_8002EDF8 != NULL) {
            if (gSchedRspStatus == 'g') {
                if (D_8002F253 != 0) {
                    _uvScDlistRecover();
                    return;
                }
                D_8002F253 = 1;
                uvScRecordTraceEvent(TRUE, 0x31);
                osSpTaskYield();
            } else {
                _uvScRunAud();
            }
        } else if (D_8002EE00[D_8002F256] != NULL) {
            _uvScRunGfx();
        }
        var_s0 = gScheduler->clientList;
        while (var_s0 != NULL) {
            osSendMesg(var_s0->msgQ, gScheduler, 0);
            var_s0 = var_s0->next;
        }
    }
}

/*
 * Ignore an already-idle RSP. Otherwise clear its watchdog and state, complete
 * audio immediately, or resolve a pending graphics yield before starting
 * queued audio. During NMI, discard queued audio and resume successfully
 * yielded graphics. Finally test the live RSP/RDP states before completing
 * graphics.
 */
#line 389 "src/sched.c"
void _uvScHandleRSP(void) {
    if (gSchedRspStatus != 0) {
        D_8002F258 = 0;
        if (gSchedRspStatus == 'a') {
            gSchedRspStatus = 0;
            _uvScDoneAud();
            return;
        }
        gSchedRspStatus = 0;
        if (D_8002F253 != 0) {
            if (osSpTaskYielded(&D_8002EE00[D_8002F256]->list) != 0) {
                D_8002F254 = 1;
                uvScRecordTraceEvent(TRUE, 0x2D);
                if (gNmiAsserted) {
                    D_8002EDF8 = NULL;
                    D_8002F253 = 0;
                    _uvScRunGfx();
                    return;
                }
            } else {
                uvScRecordTraceEvent(TRUE, 0x2B);
            }
            D_8002F253 = 0;
            if (D_8002EDF8 != NULL) {
                _uvScRunAud();
            }
        } else {
            uvScRecordTraceEvent(TRUE, 0x2B);
        }
        if ((gSchedRspStatus != 'g') && (gSchedRdpStatus == 0)) {
            _uvScDoneGfx();
        }
    }
}

/*
 * Clear the RDP state and watchdog, record completion, then attempt graphics
 * completion only when RSP graphics is inactive and no yielded graphics state
 * remains.
 */
#line 424 "src/sched.c"
void _uvScHandleRDP(void) {
    gSchedRdpStatus = 0;
    D_8002F257 = 0;
    uvScRecordTraceEvent(TRUE, 0x30);
    if ((gSchedRspStatus != 'g') && (D_8002F254 == 0)) {
        _uvScDoneGfx();
    }
}

/*
 * Latch NMI and black the display before looking up the already-loaded CONT
 * module. If present, call its callback at header offset 0x68 without loading
 * a new module. RE_UNKNOWN: the callback slot meaning and validity contract
 * beyond this observed NMI call; no callback-NULL guard is added.
 */
#line 433 "src/sched.c"
void _uvScHandleNMI(void) {
    UnkStruct_8002D1A4 *temp_v0;

    gNmiAsserted = TRUE;
    osViBlack(TRUE);
    temp_v0 = uvGetLoadedModule('CONT');
    if (temp_v0 != NULL) {
        temp_v0->unk68();
    }
}

#line 444 "src/sched.c"
/* Store the control tested by scheduler trace-event recording. Preserve
 * its s32 value; any nonzero value enables the existing recording path. */
void uvScSetTraceEnabled(s32 enabled) {
    D_8002F268 = enabled;
}
#line 447 "src/sched.c"

/*
 * Retain the original empty one-argument entrypoint, including the native
 * argument-home store. RE_UNKNOWN: exported purpose and external callers; the
 * empty body does not establish a more specific clean name.
 */
#line 448 "src/sched.c"
void func_800048D4(s32 arg0) {
}

/*
 * Retain the empty hook called for a missing graphics task and scheduler
 * watchdog recovery. RE_UNKNOWN: intended diagnostic or recovery action and
 * any callers outside this source; do not invent side effects or rename it
 * from the observed calls alone.
 */
#line 451 "src/sched.c"
void func_800048DC(void) {
}

#line 454 "src/sched.c"
/* Advance the five-slot trace ring with wraparound, record its clock-0x69
 * start time and reset both event-stream counts in the selected slot.
 * Scheduler creation and completed display intervals call this helper. */
void uvScAdvanceTraceRing(void) {
    if (++gSchedRingIdx >= 5) {
        gSchedRingIdx = 0;
    }
    D_8002EDD0[gSchedRingIdx] = uvClkGetSec(0x69);
    D_8002EDB8[gSchedRingIdx] = 0;
    D_8002EDA0[gSchedRingIdx] = 0;
}
#line 462 "src/sched.c"

#line 463 "src/sched.c"
/* When tracing is enabled and both stream counts are below thirty, append
 * to the selected stream in the current ring slot. Record clock-0x69 time,
 * event code and the packed RSP/RDP/yield state without altering its layout.
 * RE_UNKNOWN: complete event-code and two-stream consumer protocol; the
 * secondary stream includes both audio and graphics scheduler events.
 * Resolve trace-display readers before assigning stream-specific meanings. */
void uvScRecordTraceEvent(u8 secondaryStream, s32 eventCode) {
    UnkStruct_8002DAE0_inner *event;
    u32 ringIndex;

    if (D_8002F268) {
        ringIndex = gSchedRingIdx;
        if ((D_8002EDA0[ringIndex] < 0x1E) && (D_8002EDB8[ringIndex] < 0x1E)) {
            if (!secondaryStream) {
                event = D_8002DAE0[ringIndex].vals;
                event = &event[D_8002EDA0[ringIndex]++];
            } else {
                event = D_8002E440[ringIndex].vals;
                event = &event[D_8002EDB8[ringIndex]++];
            }
            event->clockSec = uvClkGetSec(0x69);
            event->unk8 = eventCode;
            event->unkC =
                (gSchedRspStatus << 0x18) | (gSchedRdpStatus << 0x10) | (D_8002F253 << 1) | D_8002F254;
        }
    }
}
#line 484 "src/sched.c"

#line 485 "src/sched.c"
/* Set the retrace-count threshold used by graphics completion to calculate
 * a remaining display delay relative to the current retrace counter.
 * RE_UNKNOWN: accepted range and higher-level frame-pacing policy; trace
 * original setters before clamping or reinterpreting the signed threshold. */
void uvScSetFrameRetraceThreshold(s32 retraceThreshold) {
    D_8001F7C0 = retraceThreshold;
}
#line 488 "src/sched.c"

#line 489 "src/sched.c"
/* Return the recorded-time difference between ring slots one and two
 * positions after the current slot, modulo five. These are the oldest
 * consecutive slots after the ring has filled.
 * RE_UNKNOWN: caller warm-up requirements before all timestamps exist;
 * resolve consumers before treating the result as a valid frame duration. */
f64 uvScGetOldestTraceInterval(void) {
    int olderSlot;
    int newerSlot;
    olderSlot = (gSchedRingIdx + 1) % 5;
    newerSlot = (gSchedRingIdx + 2) % 5;
    return D_8002EDD0[newerSlot] - D_8002EDD0[olderSlot];
}
#line 496 "src/sched.c"

/*
 * Retain the empty three-argument entrypoint and all three native argument-
 * home stores. RE_UNKNOWN: original purpose and external callers; preserve its
 * existing identity and signature.
 */
#line 497 "src/sched.c"
void func_80004B1C(s32 arg0, s32 arg1, s32 arg2) {
}

#line 500 "src/sched.c"
/* Store the control that suppresses both scheduler framebuffer-swap paths
 * when nonzero. Preserve the original s32 control value.
 * RE_UNKNOWN: callers and lifecycle of suppression; trace original
 * references before changing the display policy. */
void uvScSetBufferSwapSuppressed(s32 suppressed) {
    D_8002F26C = suppressed;
}
#line 503 "src/sched.c"
