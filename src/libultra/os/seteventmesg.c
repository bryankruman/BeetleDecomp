#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"


// Only eight events?
__OSEventState __osEventStateTab[8] ALIGNED(0x8);

/* Associate the supplied queue and message with the indexed event while
 * interrupts are disabled, then restore the mask. The event-range check
 * remains _DEBUG-only. RE_UNKNOWN: valid release-build event indices, queue
 * lifetime and replacement ordering. */
#line 10 "src/libultra/os/seteventmesg.c"
void osSetEventMesg(OSEvent event, OSMesgQueue* mq, OSMesg msg) {
    register u32 saveMask;
    __OSEventState* es;

#ifdef _DEBUG
    if (event >= OS_NUM_EVENTS) {
        __osError(ERR_OSSETEVENTMESG, 1, event);
        return;
    }
#endif

    saveMask = __osDisableInt();

    es = &__osEventStateTab[event];

    es->messageQueue = mq;
    es->message = msg;

    __osRestoreInt(saveMask);
}
