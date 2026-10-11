#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"

/* Make a waiting/stopped thread runnable using its existing queue
 * relationship, then dispatch if no thread is running or yield when the run
 * queue has higher priority. Restore the saved interrupt mask on return.
 * RE_UNKNOWN: allowed release-build input states and queue invariants;
 * preserve the conditional debug error path and scheduler handoff order. */
#line 5 "src/libultra/os/startthread.c"
void osStartThread(OSThread* t) {
    register u32 saveMask = __osDisableInt();

    switch (t->state) {
        case OS_STATE_WAITING:
            t->state = OS_STATE_RUNNABLE;
            __osEnqueueThread(&__osRunQueue, t);
            break;
        case OS_STATE_STOPPED:
            if (t->queue == NULL || t->queue == &__osRunQueue) {
                t->state = OS_STATE_RUNNABLE;
                __osEnqueueThread(&__osRunQueue, t);
            } else {
                t->state = OS_STATE_WAITING;
                __osEnqueueThread(t->queue, t);
                __osEnqueueThread(&__osRunQueue, __osPopThread(t->queue));
            }
            break;
#ifdef _DEBUG
        default:
            __osError(ERR_OSSTARTTHREAD, 0);
            __osRestoreInt(saveMask);
            return;
#endif
    }

    if (__osRunningThread == NULL) {
        __osDispatchThread();
    } else if (__osRunningThread->priority < __osRunQueue->priority) {
        __osRunningThread->state = OS_STATE_RUNNABLE;
        __osEnqueueAndYield(&__osRunQueue);
    }

    __osRestoreInt(saveMask);
}
