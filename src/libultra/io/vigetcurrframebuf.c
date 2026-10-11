#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PRinternal/viint.h"

/* Read the current video context's framebuffer while interrupts are
 * disabled, then restore the saved mask and return the pointer. Manager
 * validation remains _DEBUG-only. RE_UNKNOWN: pointed-to storage lifetime
 * and concurrent consumers; this reads the current context, not the pending
 * one. */
#line 5 "src/libultra/io/vigetcurrframebuf.c"
void* osViGetCurrentFramebuffer(void) {
    register u32 saveMask;
    void* framep;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVIGETCURRENTFRAMEBUFFER, 0);
        return NULL;
    }
#endif

    saveMask = __osDisableInt();
    framep = __osViCurr->framep;
    __osRestoreInt(saveMask);
    return framep;
}
