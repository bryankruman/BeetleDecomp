#include "PR/os_internal.h"
#include "PR/rcp.h"

/* Request signal-processor yield by writing the existing status bit.
 * RE_UNKNOWN: which running task observes the request and when completion
 * is acknowledged; this routine does not wait for or report a completed
 * yield. */
#line 4 "src/libultra/io/sptaskyield.c"
void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}
