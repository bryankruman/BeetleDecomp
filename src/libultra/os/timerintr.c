#line 1 "src/os/timerintr.c"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

extern OSTime __osCurrentTime;
extern u32 __osBaseCounter;
extern u32 __osViIntrCount;
extern u32 __osTimerCounter;
extern OSTimer __osBaseTimer;
extern OSTimer* __osTimerList;

#ifndef _FINALROM
extern OSMesgQueue __osProfTimerQ;
extern OSProf* __osProfileList;
extern OSProf* __osProfileListEnd;
extern u32 __osProfileOverflowBin;
#endif

/* Retain the original initializer as assembly; only the following three routines are C.
 * RE_ORIGINAL_QUIRK: Preserve shared-HI stores and the explicit __osCurrentTime+4 operand.
 * RE_UNKNOWN: No additional storage extent or lifetime guarantee is inferred.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/os/timerintr/__osTimerServicesInit.s")

/* Account unsigned elapsed counter ticks, remove expired timers, send optional messages, and reinsert periodic timers.
 * RE_ORIGINAL_QUIRK: Subtract counters as u32 before the u64 comparison; retain unlink/send/reinsert order.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 29 "src/os/timerintr.c"
void __osTimerInterrupt(void) {
    OSTimer* t;
    u32 count;
    u32 elapsed_cycles;

#ifndef _FINALROM
    u32 pc;
    s32 offset;
    OSProf* prof = __osProfileList;
#endif

    if (__osTimerList->next == __osTimerList) {
        return;
    }
    for (;;) {
        t = __osTimerList->next;

        if (t == __osTimerList) {
            __osSetCompare(0);
            __osTimerCounter = 0;
            break;
        }

        count = osGetCount();
        elapsed_cycles = count - __osTimerCounter;
        __osTimerCounter = count;

        if (elapsed_cycles < t->value) {
            t->value -= elapsed_cycles;
            __osSetTimerIntr(t->value);
            break;
        }

        t->prev->next = t->next;
        t->next->prev = t->prev;
        t->next = NULL;
        t->prev = NULL;

        if (t->mq != NULL) {
#ifdef _FINALROM
            osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
        }
#else
            if (t->mq != &__osProfTimerQ) {
                osSendMesg(t->mq, t->msg, OS_MESG_NOBLOCK);
            } else {
                pc = __osRunQueue->context.pc;
                for (prof = __osProfileList; prof < __osProfileListEnd; prof++) {
                    offset = pc - (u32)prof->text_start;

                    if (offset >= 0) {
                        if ((s32)prof->text_end - (s32)pc > 0) {
                            (*(u16*)(u32)((offset >> 2) + prof->histo_base))++;
                            goto __ProfDone;
                        }
                    }
                }

                __osProfileOverflowBin++;
            }
        }
#endif

    __ProfDone:

        if (t->interval != 0) {
            t->value = t->interval;
            __osInsertTimer(t);
        }
    }
}

/* Mask interrupts, snapshot the counter, program compare from the low32 bits of the u64 sum, then restore the mask.
 * RE_ORIGINAL_QUIRK: VERSION_I has no later 468 minimum; compare receives the low32 bits of the sum.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 101 "src/os/timerintr.c"
void __osSetTimerIntr(OSTime tim) {
    OSTime NewTime;
    u32 savedMask;

#if BUILD_VERSION >= VERSION_K
    if (tim < 468) {
        tim = 468;
    }
#endif

    savedMask = __osDisableInt();
    __osTimerCounter = osGetCount();
    NewTime = __osTimerCounter + tim;
    __osSetCompare(NewTime);
    __osRestoreInt(savedMask);
}

/* Insert into the relative-delay timer list with interrupts masked; equal delays insert before the existing node.
 * RE_ORIGINAL_QUIRK: Use strict greater-than for traversal; equal delays precede the existing node.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 118 "src/os/timerintr.c"
OSTime __osInsertTimer(OSTimer* t) {
    OSTimer* timep;
    OSTime tim;
    u32 savedMask = __osDisableInt();

    timep = __osTimerList->next;
    tim = t->value;
    for (; timep != __osTimerList && tim > timep->value; timep = timep->next) {
        tim -= timep->value;
    }

    t->value = tim;

    if (timep != __osTimerList) {
        timep->value -= tim;
    }

    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    __osRestoreInt(savedMask);
    return tim;
}
