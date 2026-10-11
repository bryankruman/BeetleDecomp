// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvcback_rom_400000(UvCback_Exports *exports);
void uvCallbackUnused(void);
void *uvCreateCallbackList(s32 count);
void uvCallbackFree(void *ptr);
void uvExecuteCallbacks(CallbackList *callbackList, s32 arg1);
s32 uvAddCallback(CallbackList *callbackList, CallbackRoutine routine, CallbackRoutine arg2, s32 arg3);
s32 uvRemoveCallback(CallbackList *callbackList, CallbackRoutine arg1);
s32 uvContainsCallback(CallbackList *callbackList, CallbackRoutine arg1, u8 arg2);

// .data
s32 D_uvcback_rom_00400440[] = { 0x001C0000, __entrypoint_func_uvcback_rom_400000, 0, 0 };

/* Publish the seven original callback-list operations after the allocation hook,
 * retaining their store order. This entrypoint creates no callback list itself.
 * RE_UNKNOWN: export storage and callback/list lifetime belong to the loader and
 * users of these operations; publishing the free export does not free a list. */
#line 17 "src/modules/uvcback_rom.c"
void __entrypoint_func_uvcback_rom_400000(UvCback_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvRemoveCallback = uvRemoveCallback;
    exports->uvCallbackUnused = uvCallbackUnused;
    exports->uvContainsCallback = uvContainsCallback;
    exports->uvCreateCallbackList = uvCreateCallbackList;
    exports->uvCallbackFree = uvCallbackFree;
    exports->uvExecuteCallbacks = uvExecuteCallbacks;
    exports->uvAddCallback = uvAddCallback;
}
#line 27 "src/modules/uvcback_rom.c"

/* Return without performing a callback operation.
 * RE_UNKNOWN: the historical callback purpose remains unresolved. */
#line 28 "src/modules/uvcback_rom.c"
void uvCallbackUnused(void) {
}
#line 30 "src/modules/uvcback_rom.c"

/*
 * Allocate and clear a four-byte header plus capacity eight-byte entries.
 *
 * @param capacity Signed entry count; the original stores it unchanged.
 * RE_UNKNOWN: valid count/range and allocation-failure contracts need callers.
 */
void *uvCreateCallbackList(s32 capacity) {
    CallbackList *callbackList;
    u32 allocationBytes; /* RE_UNKNOWN: signed capacity/size domains, allocation success and list ownership/lifetime need original callers and allocator failure paths. */

    allocationBytes = (capacity * sizeof(CallbackEntry)) + sizeof(CallbackList);
    callbackList = _uvMemAllocAlign8(allocationBytes);
    uvMemSet(callbackList, 0, allocationBytes); /* Preserve clearing the returned pointer before publishing capacity, without adding a null-result gate. */
    callbackList->capacity = capacity;
    return callbackList;
}

/* Forward the supplied pointer directly to the original memory-free service.
 * This body does not unlink callbacks, traverse a list or clear the caller's pointer.
 * RE_UNKNOWN: allocation ownership, outstanding callback references and NULL
 * handling must be supplied by the allocator/callers before this wrapper is used. */
#line 53 "src/modules/uvcback_rom.c"
void uvCallbackFree(void *ptr) {
    _uvMemFree(ptr);
}
#line 56 "src/modules/uvcback_rom.c"

/*
 * Walk callback slots in order, skipping null routines.
 *
 * @param callbackList List whose capacity is reloaded after callback calls.
 * @param routineArg Unchanged 32-bit word forwarded to each called routine.
 */
void uvExecuteCallbacks(CallbackList *callbackList, s32 routineArg) {
    s32 entryIndex; /* RE_UNKNOWN: capacity/storage validity, mutation, reentrancy and list lifetime need actual callbacks and lifecycle callers. */

    if (callbackList == NULL) {
        return;
    }

    for (entryIndex = 0; entryIndex < callbackList->capacity; entryIndex++) { /* Preserve the live capacity reload after callback calls. */
        if (callbackList->entries[entryIndex].callback != NULL) {
            callbackList->entries[entryIndex].callback(routineArg);
        }
    }
}

#line 77 "src/modules/uvcback_rom.c"
/* Insert a callback before a requested callback, in ascending priority
 * order, or at the first free slot for priority zero. Return -1 for a
 * null/full list. RE_ORIGINAL_QUIRK: the insert-before scan does not break
 * after insertion; preserve its original treatment of repeated matches. */
s32 uvAddCallback(CallbackList *callbackList, CallbackRoutine routine, CallbackRoutine insertBefore,
                  s32 priority) {
    s32 index;
    s32 shiftIndex;
    CallbackEntry *entry;

    if (callbackList == NULL) {
        return -1;
    }

    if (callbackList->entries[callbackList->capacity - 1].callback != NULL) {
        return -1;
    }

    // Simple append
    if ((insertBefore == NULL) && (priority == 0)) {
        for (index = 0; index < callbackList->capacity; index++) {
            if (callbackList->entries[index].callback == NULL) {
                callbackList->entries[index].callback = routine;
                callbackList->entries[index].priority = 0;
                break;
            }
        }
    } else if (insertBefore != NULL) {
        for (index = 0; index < callbackList->capacity; index++) {
            entry = &callbackList->entries[index];
            if (insertBefore == entry->callback) {
                for (shiftIndex = callbackList->capacity - 2; shiftIndex >= index; shiftIndex--) {
                    callbackList->entries[shiftIndex + 1] = callbackList->entries[shiftIndex];
                }
                entry->callback = routine;
                entry->priority = 0;
            }
        }
    } else {
        // Add and sort entries by priority
        for (index = 0; index < callbackList->capacity; index++) {
            entry = &callbackList->entries[index];
            if ((priority < entry->priority) || (entry->callback == NULL)) {
                for (shiftIndex = callbackList->capacity - 2; shiftIndex >= index; shiftIndex--) {
                    callbackList->entries[shiftIndex + 1] = callbackList->entries[shiftIndex];
                }
                entry->callback = routine;
                entry->priority = priority;
                break;
            }
        }
    }

    return 0;
}
#line 128 "src/modules/uvcback_rom.c"

/*
 * Removes a callback from a callback list
 *
 * @param callbackList Callback List
 * @param routine Callback routine
 *
 * @return 0 if success, -1 if the callback is NULL
 */
#line 137 "src/modules/uvcback_rom.c"
/* Remove matching callback entries by shifting later entries left and
 * clearing the final callback pointer. RE_ORIGINAL_QUIRK: retain the
 * continuing forward scan, final priority bytes and success when absent. */
s32 uvRemoveCallback(CallbackList *callbackList, CallbackRoutine routine) {
    s32 index;
    s32 shiftIndex;

    if (callbackList == NULL) {
        return -1;
    }
    for (index = 0; index < callbackList->capacity; index++) {
        CallbackEntry *entry = &callbackList->entries[index];
        if (routine == entry->callback) {
            for (shiftIndex = index + 1; shiftIndex < callbackList->capacity; shiftIndex++) {
                callbackList->entries[shiftIndex - 1] = callbackList->entries[shiftIndex];
            }
            callbackList->entries[callbackList->capacity - 1].callback = NULL;
        }
    }

    return 0;
}
#line 156 "src/modules/uvcback_rom.c"

/*
 * Checks if a callback is inside the Callback List
 *
 * @param callbackList Callback List
 * @param routine Callback routine
 * @param priority Callback Priority
 *
 * @return >= 0 if the callback is found, -1 if the callback is NULL
 */
#line 166 "src/modules/uvcback_rom.c"
/* Return true only when both callback routine and stored priority match.
 * A null list returns -1; an absent match returns false. Preserve the
 * unsigned-byte priority parameter and established export name. */
s32 uvContainsCallback(CallbackList *callbackList, CallbackRoutine routine, u8 priority) {
    s32 index;

    if (callbackList == NULL) {
        return -1;
    }

    for (index = 0; index < callbackList->capacity; index++) {
        CallbackEntry *entry = &callbackList->entries[index];
        if ((routine == callbackList->entries[index].callback)
            && (priority == callbackList->entries[index].priority)) {
            return TRUE;
        }
    }

    return FALSE;
}
#line 183 "src/modules/uvcback_rom.c"
