/* Disk helper bodies retain the qualified public-SDK-derived expressions.
 * RE_UNKNOWN: exact SDK release and full nominal storage ownership are unproved.
 * RE_UNKNOWN: historical C storage class is unproved; these project-internal
 * names use ordinary external linkage for real retained-ASM callers.
 * These caller-facing views do not establish all indirect return consumers.
 * RE_UNKNOWN: caller synchronization/lifetime, arbitrary queue-state validity,
 * and meanings of fields or bits beyond the reviewed consumed views remain open. */
#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PRinternal/osint.h"
#include "PRinternal/piint.h"
#include "PRinternal/macros.h"

extern OSPiHandle *D_80033524;
extern u32 D_800209E0;
extern OSMesgQueue *D_80030EE0;
extern OSMesg D_80030EE4;
extern OSThread *D_80020A48;
extern volatile u32 D_A5000510;
extern s32 osEPiRawStartDma(OSPiHandle *, s32, u32, void *, u32);



void kernelDiskResetBufferManagerAndNotify(void);
void kernelDiskPostPiEvent(void);

GLOBAL_ASM("asm/nonmatchings/libultra/io/disk_interrupt_helpers/func_80009DF0.s")

/* Reset and restore disk buffer-manager control, then attempt PI notification.
 * Clear the PI interrupt and re-enable its mask after the notification attempt. */
#line 176 "src/libultra/io/disk_interrupt_helpers.c"
void kernelDiskResetBufferManagerAndNotify(void) {
    __OSTranxInfo *info = &D_80033524->transferInfo;
    u32 pi_stat;
    
    WAIT_ON_IOBUSY(pi_stat);
    IO_WRITE(LEO_BM_CTL, info->bmCtlShadow | LEO_BM_CTL_RESET);
    WAIT_ON_IOBUSY(pi_stat);
    IO_WRITE(LEO_BM_CTL, info->bmCtlShadow);
    kernelDiskPostPiEvent();
    IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
    D_800209E0 |= OS_IM_PI;
}

/* Post the configured PI event when its queue exists and has space; otherwise
 * return without posting. Move one waiting receiver to the run queue, if present. */
#line 189 "src/libultra/io/disk_interrupt_helpers.c"
void kernelDiskPostPiEvent(void) {
    OSMesgQueue *mq = D_80030EE0;
    s32 last;
    
    if (mq == NULL || MQ_IS_FULL(mq)) {
        return;
    }

    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = D_80030EE4;
    mq->validCount++;
    
    if (mq->mtqueue->next != NULL) {
        __osEnqueueThread(&D_80020A48, __osPopThread(&mq->mtqueue));
    }
}

