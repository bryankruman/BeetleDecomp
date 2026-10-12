/* Snapshot the accumulated time and current counter with interrupts masked,
 * then add the unsigned counter delta after restoring the previous mask.
 * RE_ORIGINAL_QUIRK: subtraction wraps as u32; the return addition is u64.
 * RE_UNKNOWN: no new timing-unit or counter-wrap guarantees are inferred here.
 */
#line 1 "src/libultra/os/gettime.c"
#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/osint.h"
#include "PRinternal/viint.h"

OSTime osGetTime(void) {
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSGETTIME, 0);
        return 0;
    }
#endif

    saveMask = __osDisableInt();
    tmptime = osGetCount();
    elapseCount = tmptime - __osBaseCounter;
    currentCount = __osCurrentTime;
    __osRestoreInt(saveMask);
    return currentCount + elapseCount;
}
