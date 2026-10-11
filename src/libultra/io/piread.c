#include "PRinternal/piint.h"
#include "PR/ultraerror.h"
#include "PRinternal/piint.h"

/* Acquire PI access, perform one raw IO read, release access and return the
 * raw operation's status. The source's misalignment check is _DEBUG-only and
 * absent from this 64-byte release witness. RE_UNKNOWN: valid device addresses
 * and output-pointer ownership remain provider/caller contracts. */
#line 5 "src/libultra/io/piread.c"
s32 osPiReadIo(u32 devAddr, u32* data) {
    register s32 ret;

#ifdef _DEBUG
    if (devAddr & 0x3) {
        __osError(ERR_OSPIREADIO, 1, devAddr);
        return -1;
    }
#endif

    __osPiGetAccess();
    ret = osPiRawReadIo(devAddr, data);
    __osPiRelAccess();

    return ret;
}
