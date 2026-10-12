/* Mark the running thread runnable, yield through the existing run queue,
 * and restore the saved interrupt mask when this thread resumes.
 * RE_ORIGINAL_QUIRK: preserve the state write before enqueue-and-yield.
 */
#line 1 "src/libultra/os/yieldthread.c"
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

void osYieldThread(void) {
    register u32 saveMask = __osDisableInt();

    __osRunningThread->state = OS_STATE_RUNNABLE;
    __osEnqueueAndYield(&__osRunQueue);
    __osRestoreInt(saveMask);
}
