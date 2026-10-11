#include "PR/os_internal.h"
#include "PR/sptask.h"
#include "PR/rcp.h"


/* Read processor status and return YIELDED only when that status bit is
 * set. When the yield-request bit is also present, OR the result into the
 * task flags and clear DP_WAIT. RE_ORIGINAL_QUIRK: task flags are not
 * updated without the request bit, even if the returned status reports
 * yielded. RE_UNKNOWN: caller task ownership and status-sampling protocol. */
#line 6 "src/libultra/io/sptaskyielded.c"
OSYieldResult osSpTaskYielded(OSTask* tp) {
    u32 status;
    OSYieldResult result;

    status = __osSpGetStatus();
    result = (status & SP_STATUS_YIELDED) ? OS_TASK_YIELDED : 0;

    if (status & SP_STATUS_YIELD) {
        tp->t.flags |= result;
        tp->t.flags &= ~(OS_TASK_DP_WAIT);
    }

    return result;
}
