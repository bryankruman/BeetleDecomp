/* Disable interrupts while clearing the requested global-mask bits outside OS_IM_RCP, then restore the saved interrupt state. */
#line 1 "src/os/resetglobalintmask.c"
#include "PR/os_internal.h"

void __osResetGlobalIntMask(OSHWIntr mask) {
    register u32 saveMask = __osDisableInt();

    __OSGlobalIntMask &= ~(mask & ~OS_IM_RCP);

    __osRestoreInt(saveMask);
}
