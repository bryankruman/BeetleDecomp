/* Reject a busy serial interface, then write one caller-selected device word.
 * RE_UNKNOWN: Device-address validity remains a caller responsibility. */
#line 1 "src/io/sirawwrite.c"
#include "PR/os_internal.h"
#include "PRinternal/siint.h"
#include "assert.h"








































// Adjust line numbers to match assert
#if BUILD_VERSION < VERSION_J
#line 46
#endif

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osSiRawWriteIo(u32 devAddr, u32 data) {
    assert((devAddr & 0x3) == 0);

    if (__osSiDeviceBusy()) {
        return -1;
    }

    IO_WRITE(devAddr, data);
    return 0;
}
