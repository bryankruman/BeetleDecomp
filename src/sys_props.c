// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stdarg.h"

// Apparently With prop 8 you can set the Imtx stack size, see modules/uvimtx_rom.c
static s32 sSystemProps[SYSTEM_PROP_COUNT];

/*
 * Store the supplied promoted 32-bit value at property-ID-minus-one, then read
 * the next signed property ID from the same argument list. Zero terminates; IDs
 * 23 or greater stop before consuming a value. Keep every original check and
 * variadic word width, including the absence of a lower-bound check.
 * RE_UNKNOWN: valid caller ID domains, complete argument-list termination,
 * property value kinds, pointed-object capacities and ownership/lifetimes.
 * Trace original setters, indirect/kernel callers and each property consumer
 * before adding bounds, retyping values or changing termination behavior.
 */
#line 8 "src/sys_props.c"
void uvSystemProps(s32 propertyId, ...) {
    va_list propertyArguments;

    va_start(propertyArguments, propertyId);
    while (propertyId != 0) {
        // Stop on the signed property ID limit; no lower-bound check is added.
        if (propertyId >= 23) {
            break;
        }
        sSystemProps[propertyId - 1] = va_arg(propertyArguments, s32);
        propertyId = va_arg(propertyArguments, s32);
    }

    va_end(propertyArguments);
}
#line 23 "src/sys_props.c"

/*
 * Return the existing stored word at property-ID-minus-one through the original
 * pointer return declaration. The accessor does not validate the ID locally.
 * RE_UNKNOWN: intended caller ID domain and each stored word's original value
 * kind, pointed-object extent, ownership and lifetime. Trace original setters,
 * indirect callers and individual consumers before changing the pointer/word
 * ABI, adding bounds or assuming a complete settings-record layout.
 */
#line 24 "src/sys_props.c"
void* uvGetSystemProp(s32 propertyId) {
    return sSystemProps[propertyId - 1];
}
#line 27 "src/sys_props.c"
