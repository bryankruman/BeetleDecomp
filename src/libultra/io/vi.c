/* Reset the existing VI contexts, select the TV mode, and apply the first field.
 * RE_ORIGINAL_QUIRK: the VI line-counter wait has no timeout.
 * RE_UNKNOWN: exact SDK release and original header provenance are unproved;
 * #ident below is retained stock provenance.
 * RE_UNKNOWN: vi[2] is an observed 96-byte access view, not a proved allocation extent.
 */
#line 1 "src/io/vi.c"
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/R4300.h"
#include "PR/rcp.h"
#include "PRinternal/viint.h"

// TODO: this comes from a header
#ident "$Revision: 1.17 $"

extern __OSViContext vi[2];
extern __OSViContext* __osViCurr;
extern __OSViContext* __osViNext;

void __osViInit(void) {
    bzero(vi, sizeof(vi));
    __osViCurr = &vi[0];
    __osViNext = &vi[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;
    __osViNext->framep = (void*)K0BASE;
    __osViCurr->framep = (void*)K0BASE;

    if (osTvType == OS_TV_TYPE_PAL) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == OS_TV_TYPE_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }

    __osViNext->state = VI_STATE_BLACK;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;

    while (IO_READ(VI_CURRENT_REG) > 10) { // RE_UNKNOWN: exact line-counter wait phase.
    }

    IO_WRITE(VI_CONTROL_REG, 0); // pixel size blank (no data, no sync)
    __osViSwapContext();
}
