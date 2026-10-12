/* Return the supplied thread's priority; NULL selects the running thread.
 * RE_ORIGINAL_QUIRK: the non-NULL argument is dereferenced without validation.
 */
#line 1 "src/libultra/os/getthreadpri.c"
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

OSPri osGetThreadPri(OSThread* thread) {
    if (thread == NULL) {
        thread = __osRunningThread;
    }

    return thread->priority;
}
