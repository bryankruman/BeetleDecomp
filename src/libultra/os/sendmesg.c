#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"

/* Append a message under the saved interrupt mask, waiting on a full queue
 * only for the blocking flag; other flags take the original failure path.
 * Wake one waiting receiver after insertion and restore the mask.
 * RE_UNKNOWN: queue storage/capacity and release-build flag domain;
 * preserve the distinct send/receive flag predicates. */
#line 5 "src/libultra/os/sendmesg.c"
s32 osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    register u32 saveMask;
    register s32 last;

#ifdef _DEBUG
    if ((flags != OS_MESG_NOBLOCK) && (flags != OS_MESG_BLOCK)) {
        __osError(ERR_OSSENDMESG, 1, flags);
        return -1;
    }
#endif

    saveMask = __osDisableInt();

    while (MQ_IS_FULL(mq)) {
        if (flags == OS_MESG_BLOCK) {
            __osRunningThread->state = OS_STATE_WAITING;
            __osEnqueueAndYield(&mq->fullqueue);
        } else {
            __osRestoreInt(saveMask);
            return -1;
        }
    }

    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = msg;
    mq->validCount++;

    if (mq->mtqueue->next != NULL) {
        osStartThread(__osPopThread(&mq->mtqueue));
    }

    __osRestoreInt(saveMask);
    return 0;
}
