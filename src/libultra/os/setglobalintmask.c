/* Disable interrupts while adding the requested global-mask bits, then restore the saved interrupt state. */
#line 1 "src/os/setglobalintmask.c"
#include "PR/os_internal.h"

void __osSetGlobalIntMask(OSHWIntr mask) {
    register u32 saveMask = __osDisableInt();

    __OSGlobalIntMask |= mask;

    __osRestoreInt(saveMask);
}
