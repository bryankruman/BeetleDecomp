#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/viint.h"

/* Read the next video context's framebuffer while interrupts are disabled,
 * then restore the saved mask and return the pointer. Manager validation
 * remains _DEBUG-only. RE_UNKNOWN: pending-buffer lifetime and when the
 * context becomes current. */
#line 5 "src/libultra/io/vigetnextframebuf.c"
void* osViGetNextFramebuffer(void) {
    register u32 saveMask;
    void* framep;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVIGETNEXTFRAMEBUFFER, 0);
        return NULL;
    }
#endif

    saveMask = __osDisableInt();
    framep = __osViNext->framep;
    __osRestoreInt(saveMask);
    return framep;
}
