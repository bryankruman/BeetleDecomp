/* Controller reads use the existing SI access lock and shared PIF packet storage. */
#line 1 "src/io/contreaddata.c"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PRinternal/controller.h"
#include "PRinternal/siint.h"

void __osPackReadData(void);

/* Start a button/stick read under the existing SI access lock.
 * RE_ORIGINAL_QUIRK: the write-DMA status is superseded by the read-DMA status;
 * the request is rebuilt only when the shared last-command byte differs. */
#line 8 "src/io/contreaddata.c"
s32 osContStartReadData(OSMesgQueue* mq) {
    s32 ret = 0;

    __osSiGetAccess();

    if (__osContLastCmd != CONT_CMD_READ_BUTTON) {
        __osPackReadData();
        ret = __osSiRawStartDma(OS_WRITE, __osContPifRam.ramarray);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }

    ret = __osSiRawStartDma(OS_READ, __osContPifRam.ramarray);
    __osContLastCmd = CONT_CMD_READ_BUTTON;
    __osSiRelAccess();

    return ret;
}

/* Decode each configured controller response into the caller's pad records.
 * RE_ORIGINAL_QUIRK: a channel error updates errno but preserves prior input fields.
 * RE_UNKNOWN: callers must provide the output capacity; this routine checks none. */
#line 26 "src/io/contreaddata.c"
void osContGetReadData(OSContPad* data) {
    u8* ptr = (u8*)__osContPifRam.ramarray;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat*)ptr;
        data->errno = CHNL_ERR(readformat);

        if (data->errno != 0) {
            continue;
        }

        data->button = readformat.button;
        data->stick_x = readformat.stick_x;
        data->stick_y = readformat.stick_y;
    }
}

/* Format button/stick commands in the existing shared PIF packet.
 * RE_ORIGINAL_QUIRK: the controller-count byte is reread at each loop condition;
 * packet storage also has existing player-input aliases. No new storage is added.
 * RE_UNKNOWN: the routine does not validate the controller count against capacity. */
#line 45 "src/io/contreaddata.c"
void __osPackReadData(void) {
    u8* ptr = (u8*)__osContPifRam.ramarray;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < ARRLEN(__osContPifRam.ramarray); i++) {
        __osContPifRam.ramarray[i] = 0;
    }

    __osContPifRam.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;

    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContReadFormat*)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }

    *ptr = CONT_CMD_END;
}
