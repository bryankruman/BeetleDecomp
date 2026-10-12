#line 1 "src/io/siacs.c"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"

#define SI_Q_BUF_LEN 1
extern OSMesg siAccessBuf[];
extern OSMesgQueue __osSiAccessQueue;
void __osSiCreateAccessQueue(void);
extern u32 __osSiAccessQueueEnabled;

/* Initialize and seed the retained SI access message queue.
 * RE_ORIGINAL_QUIRK: Set enabled before creating the queue; seed with a nonblocking send.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 9 "src/io/siacs.c"
void __osSiCreateAccessQueue(void) {
    __osSiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osSiAccessQueue, siAccessBuf, SI_Q_BUF_LEN);
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}

/* Initialize SI access queue on first use, then receive its token with blocking mode.
 * RE_ORIGINAL_QUIRK: Keep the original lazy initialization and blocking receive order.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 15 "src/io/siacs.c"
void __osSiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osSiAccessQueueEnabled) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&__osSiAccessQueue, &dummyMesg, OS_MESG_BLOCK);
}

/* Return the SI access token with nonblocking send.
 * RE_ORIGINAL_QUIRK: Ignore the nonblocking send return value as in the original.
 * RE_UNKNOWN: Retained storage bounds and extra ownership or reentrancy guarantees are not inferred.
 */
#line 23 "src/io/siacs.c"
void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
