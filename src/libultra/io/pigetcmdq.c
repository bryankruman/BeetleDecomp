/* Return the existing PI manager command queue only while that manager is active. */
#line 1 "src/io/pigetcmdq.c"
#include "PR/os_internal.h"
#include "PRinternal/piint.h"

OSMesgQueue* osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return NULL;
    } else {
        return __osPiDevMgr.cmdQueue;
    }
}
