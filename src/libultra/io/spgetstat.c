/* Return a fresh read of the RSP status register. */
#line 1 "src/io/spgetstat.c"
#include "PR/os_internal.h"
#include "PR/rcp.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

u32 __osSpGetStatus(void) {
    return IO_READ(SP_STATUS_REG);
}
