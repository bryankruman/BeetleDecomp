#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

/**
 * Starts to read the values for SI device status and type which are connected to the controller port and joyport
 * connector.
 */
/* Request status under SI access; only a changed command writes and waits before the read DMA. RE_UNKNOWN: original shared-storage extents remain unproved; retained assembly keeps ownership. */ s32 osContStartQuery(OSMesgQueue* mq) {
    s32 ret = 0;

    __osSiGetAccess();

    if (__osContLastCmd != CONT_CMD_REQUEST_STATUS) {
        __osPackRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    __osContLastCmd = CONT_CMD_REQUEST_STATUS;
    __osSiRelAccess();
    return ret;
}

/**
 * Returns the values from osContStartQuery to status. Both functions must be paired for use.
 */
/* Decode the completed query through the original helper; the local pattern result is discarded. */ void osContGetQuery(OSContStatus* data) {
    u8 pattern;
    __osContGetInitData(&pattern, data);
}
