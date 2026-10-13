/* Select the Controller Pak bank used by subsequent block operations.
 * RE_UNKNOWN: Exact game SDK release is unproved.
 */
#line 1
#include "PR/os_internal.h"
#include "PRinternal/controller.h"

#if BUILD_VERSION >= VERSION_J
s32 __osPfsSelectBank(OSPfs* pfs, u8 bank) {
    u8 temp[BLOCKSIZE];
    int i;
    s32 ret = 0;

    for (i = 0; i < BLOCKSIZE; i++) {
        temp[i] = bank;
    }

    ret = __osContRamWrite(pfs->queue, pfs->channel, CONT_BLOCK_DETECT, temp, FALSE);

    if (ret == 0) {
        pfs->activebank = bank;
    }

    return ret;
}
#endif
