/* Return the first pointer-sized word of retained D_80020A54 storage for
 * the existing OSThread-pointer consumers. This access-only declaration does
 * not allocate storage or change the remaining eight owned bytes.
 * RE_ORIGINAL_QUIRK: retain the legacy exported name; the accessed word is
 * distinct from __osActiveQueue at the accepted 0x80020A4C alias.
 * RE_UNKNOWN: exception-publication condition and intended pointer role,
 * lifetime/null behavior, and the remaining eight bytes of this data owner. */
#line 1 "src/os/getactivequeue.c"
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

extern OSThread *D_80020A54;
#line 4 "src/os/getactivequeue.c"
OSThread* __osGetActiveQueue(void) {
    return D_80020A54;
}
