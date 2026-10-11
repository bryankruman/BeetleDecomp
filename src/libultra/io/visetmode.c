#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "assert.h"
#include "PRinternal/viint.h"









































// TODO: this comes from a header
#ident "$Revision: 1.17 $"

/* Store the next mode pointer, replace the context state with MODE_UPDATED,
 * and copy that mode's control word while interrupts are disabled.
 * RE_ORIGINAL_QUIRK: the state is assigned, not ORed with old pending
 * flags. RE_UNKNOWN: mode lifetime and caller update ordering; NULL/manager
 * checks remain _DEBUG-only. */
#line 49 "src/libultra/io/visetmode.c"
void osViSetMode(OSViMode* modep) {
    register u32 saveMask;

#ifdef _DEBUG
    if (!__osViDevMgr.active) {
        __osError(ERR_OSVISETMODE, 0);
        return;
    }

    assert(modep != NULL);
#endif

    saveMask = __osDisableInt();

    __osViNext->modep = modep;
    __osViNext->state = VI_STATE_MODE_UPDATED;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
