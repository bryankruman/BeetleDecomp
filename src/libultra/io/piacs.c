#line 1 "src/io/piacs.c"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"

#define PI_Q_BUF_LEN 1
extern u32 __osPiAccessQueueEnabled;
extern OSMesg piAccessBuf[];
extern OSMesgQueue __osPiAccessQueue;
void __osPiCreateAccessQueue(void);

/* Initialize and seed the retained PI access message queue.
 * RE_ORIGINAL_QUIRK: Set enabled before creating the queue; seed with a nonblocking send.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 9 "src/io/piacs.c"
void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, piAccessBuf, PI_Q_BUF_LEN);
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

/* Initialize PI access queue on first use, then receive its token with blocking mode.
 * RE_ORIGINAL_QUIRK: Keep the original lazy initialization and blocking receive order.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 15 "src/io/piacs.c"
void __osPiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }
    osRecvMesg(&__osPiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

/* Return the PI access token with nonblocking send.
 * RE_ORIGINAL_QUIRK: Ignore the nonblocking send return value as in the original.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 23 "src/io/piacs.c"
void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
