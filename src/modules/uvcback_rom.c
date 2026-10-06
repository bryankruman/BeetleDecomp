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

void uvCallbackUnused(void) {
}

/*
 * Creates a callback list
 *
 * @param capacity Capacity of the callback list
 * @param routineArg Argument for the callback routine
 */
void *uvCreateCallbackList(s32 capacity) {
    CallbackList *callbackList;
    u32 size;

    size = (capacity * sizeof(CallbackEntry)) + sizeof(CallbackList);
    callbackList = _uvMemAllocAlign8(size);
    uvMemSet(callbackList, 0, size);
    callbackList->capacity = capacity;
    return callbackList;
}

/*
 * Free the a callback list
 *
 * @param ptr Callback list pointer
 */
void uvCallbackFree(void *ptr) {
    _uvMemFree(ptr);
}

/*
 * Executes all the callbacks from a callback list
 *
 * @param callbackList Callback List
 * @param routineArg Argument for the callback routine
 */
void uvExecuteCallbacks(CallbackList *callbackList, s32 routineArg) {
    s32 i;

    if (callbackList == NULL) {
        return;
    }

    for (i = 0; i < callbackList->capacity; i++) {
        if (callbackList->entries[i].callback != NULL) {
            callbackList->entries[i].callback(routineArg);
        }
    }
}

s32 uvAddCallback(CallbackList *callbackList, CallbackRoutine routine, CallbackRoutine arg2,
                  s32 priority) {
    s32 i;
    s32 j;
    CallbackEntry *entry;

    if (callbackList == NULL) {
        return -1;
    }

    if (callbackList->entries[callbackList->capacity - 1].callback != NULL) {
        return -1;
    }

    // Simple append
    if ((arg2 == NULL) && (priority == 0)) {
        for (i = 0; i < callbackList->capacity; i++) {
            if (callbackList->entries[i].callback == NULL) {
                callbackList->entries[i].callback = routine;
                callbackList->entries[i].priority = 0;
                break;
            }
        }
    } else if (arg2 != NULL) {
        for (i = 0; i < callbackList->capacity; i++) {
            entry = &callbackList->entries[i];
            if (arg2 == entry->callback) {
                for (j = callbackList->capacity - 2; j >= i; j--) {
                    callbackList->entries[j + 1] = callbackList->entries[j];
                }
                entry->callback = routine;
                entry->priority = 0;
            }
        }
    } else {
        // Add and sort entries by priority
        for (i = 0; i < callbackList->capacity; i++) {
            entry = &callbackList->entries[i];
            if ((priority < entry->priority) || (entry->callback == NULL)) {
                for (j = callbackList->capacity - 2; j >= i; j--) {
                    callbackList->entries[j + 1] = callbackList->entries[j];
                }
                entry->callback = routine;
                entry->priority = priority;
                break;
            }
        }
    }

    return 0;
}

/*
 * Removes a callback from a callback list
 *
 * @param callbackList Callback List
 * @param routine Callback routine
 *
 * @return 0 if success, -1 if the callback is NULL
 */
s32 uvRemoveCallback(CallbackList *callbackList, CallbackRoutine routine) {
    s32 i;
    s32 j;

    if (callbackList == NULL) {
        return -1;
    }
    for (i = 0; i < callbackList->capacity; i++) {
        CallbackEntry *entry = &callbackList->entries[i];
        if (routine == entry->callback) {
            for (j = i + 1; j < callbackList->capacity; j++) {
                callbackList->entries[j - 1] = callbackList->entries[j];
            }
            callbackList->entries[callbackList->capacity - 1].callback = NULL;
        }
    }

    return 0;
}

/*
 * Checks if a callback is inside the Callback List
 *
 * @param callbackList Callback List
 * @param routine Callback routine
 * @param priority Callback Priority
 *
 * @return >= 0 if the callback is found, -1 if the callback is NULL
 */
s32 uvContainsCallback(CallbackList *callbackList, CallbackRoutine routine, u8 priority) {
    s32 i;

    if (callbackList == NULL) {
        return -1;
    }

    for (i = 0; i < callbackList->capacity; i++) {
        CallbackEntry *temp = &callbackList->entries[i];
        if ((routine == callbackList->entries[i].callback)
            && (priority == callbackList->entries[i].priority)) {
            return TRUE;
        }
    }

    return FALSE;
}
