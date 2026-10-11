#include "PR/os_internal.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

/* Set or clear the next context's BLACK state bit according to the u8
 * argument while interrupts are disabled, then restore the mask.
 * RE_UNKNOWN: when the pending state becomes visible and required manager
 * lifecycle; preserve the argument's existing width and truth test. */
#line 7 "src/libultra/io/viblack.c"
void osViBlack(u8 active) {
    register u32 saveMask = __osDisableInt();

    if (active) {
        __osViNext->state |= VI_STATE_BLACK;
    } else {
        __osViNext->state &= ~VI_STATE_BLACK;
    }

    __osRestoreInt(saveMask);
}
