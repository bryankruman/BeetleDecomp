#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"

/* Initialize both waiting-thread queues to the existing tail sentinel and
 * attach the caller's message array and capacity to an empty ring. Capacity
 * rejection exists only in the retained _DEBUG branch. RE_UNKNOWN:
 * release-build caller capacity, storage extent and queue lifetime;
 * preserve the build distinction. */
#line 5 "src/libultra/os/createmesgqueue.c"
void osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 msgCount) {

#ifdef _DEBUG
    if (msgCount <= 0) {
        __osError(ERR_OSCREATEMESGQUEUE, 1, msgCount);
        return;
    }
#endif

    mq->mtqueue = (OSThread*)&__osThreadTail.next;
    mq->fullqueue = (OSThread*)&__osThreadTail.next;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = msgCount;
    mq->msg = msg;
}
