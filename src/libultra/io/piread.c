#include "PRinternal/piint.h"
#include "PR/ultraerror.h"
#include "PRinternal/piint.h"

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
