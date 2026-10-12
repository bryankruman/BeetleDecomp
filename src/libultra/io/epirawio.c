/*
 * Synchronize handle-selected PI timing when necessary, then write one word
 * through the handle base address combined with the device address.
 * RE_ORIGINAL_QUIRK: Repeated volatile status reads have no timeout.
 * RE_ORIGINAL_QUIRK: Keep pointer comparison, live field reloads, timing
 * write order, and the final retained current-handle update.
 * RE_UNKNOWN: Caller guarantees for handle domain and lifetime are unproved.
 * RE_UNKNOWN: Caller address, alignment, and pointer guarantees are unproved.
 */
#line 1 "src/io/epirawwrite.c"
#include "PRinternal/piint.h"
#include "PR/ultraerror.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osEPiRawWriteIo(OSPiHandle* pihandle, u32 devAddr, u32 data) {
    register u32 stat;
    register u32 domain;

#ifdef _DEBUG
    if (devAddr & 0x3) {
        __osError(ERR_OSPIRAWWRITEIO, 1, devAddr);
        return -1;
    }
#endif

    EPI_SYNC(pihandle, stat, domain);
    IO_WRITE(pihandle->baseAddress | devAddr, data);

    return 0;
}

/*
 * Synchronize handle-selected PI timing when necessary, then read one word
 * through the handle base address combined with the device address.
 * RE_ORIGINAL_QUIRK: Repeated volatile status reads have no timeout.
 * RE_ORIGINAL_QUIRK: Keep pointer comparison, live field reloads, timing
 * write order, and the final retained current-handle update.
 * RE_UNKNOWN: Caller guarantees for handle domain and lifetime are unproved.
 * RE_UNKNOWN: Caller address, alignment, and pointer guarantees are unproved.
 */
#line 1 "src/io/epirawread.c"
#include "PRinternal/piint.h"
#include "PR/ultraerror.h"
#include "assert.h"




















// Adjust line numbers to match assert
#if BUILD_VERSION < VERSION_J
#line 28
#endif

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

s32 __osEPiRawReadIo(OSPiHandle* pihandle, u32 devAddr, u32* data) {
    register u32 stat;
    register u32 domain;

#ifdef _DEBUG
    if (devAddr & 0x3) {
        __osError(ERR_OSPIRAWREADIO, 1, devAddr);
        return -1;
    }
#endif
    assert(data != NULL);

    EPI_SYNC(pihandle, stat, domain);
    *data = IO_READ(pihandle->baseAddress | devAddr);

    return 0;
}
