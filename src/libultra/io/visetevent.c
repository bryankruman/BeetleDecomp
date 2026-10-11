#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "assert.h"
#include "PRinternal/viint.h"












































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

/* Store the queue, message and retrace count in the next video context
 * while interrupts are disabled. Manager and NULL checks remain
 * _DEBUG-only. RE_UNKNOWN: queue lifetime and zero/out-of-range
 * retrace-count behavior; preserve the existing assignment and destination
 * field width. */
#line 52 "src/libultra/io/visetevent.c"
void osViSetEvent(OSMesgQueue* mq, OSMesg m, u32 retraceCount) {
    register u32 saveMask;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVISETEVENT, 0);
        return;
    }

    assert(mq != NULL);
#endif

    saveMask = __osDisableInt();

    __osViNext->msgq = mq;
    __osViNext->msg = m;
    __osViNext->retraceCount = retraceCount;
    __osRestoreInt(saveMask);
}
