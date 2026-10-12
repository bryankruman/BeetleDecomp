/* Return the existing current video-context pointer without copying its storage. */
#line 1 "src/io/vigetcurrcontext.c"
#include "PR/os_internal.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

__OSViContext* __osViGetCurrentContext(void) {
    return __osViCurr;
}
