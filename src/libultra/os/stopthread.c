/* Native-matched SDK routine using existing O32 declarations and storage.
 * Native evidence: kernel-stopthread-vtop-originals-7460.json.
 * Existing public declarations and storage remain unchanged.
 */
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

/* The address-named slot aliases existing __osRunningThread storage
 * in the linker script. */
extern OSThread *D_80020A50;

/* Stop the selected thread while interrupts are disabled. A null argument
 * selects the running-thread case. Runnable or waiting threads are marked
 * stopped and removed from their recorded queue; the running case marks the
 * retained running-thread slot stopped and yields without enqueueing it.
 * RE_ORIGINAL_QUIRK: other state values perform no state or queue operation;
 * the saved interrupt mask is restored after every returning case.
 * RE_UNKNOWN: callers must establish thread lifetime, queue membership, and
 * the running-thread slot's validity. The historical SDK revision and its
 * debug-only argument checks are not established by this native body.
 */
void osStopThread(OSThread *thread) {
    register u32 savedInterruptMask;
    register u16 state;

    savedInterruptMask = __osDisableInt();
    state = thread == NULL ? OS_STATE_RUNNING : thread->state;
    switch (state) {
        case OS_STATE_RUNNING:
            D_80020A50->state = OS_STATE_STOPPED;
            __osEnqueueAndYield(NULL);
            break;
        case OS_STATE_RUNNABLE:
        case OS_STATE_WAITING:
            thread->state = OS_STATE_STOPPED;
            __osDequeueThread(thread->queue, thread);
            break;
    }
    __osRestoreInt(savedInterruptMask);
}

