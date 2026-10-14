// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "stdarg.h"
#include "module.h"

typedef struct UnkStruct_00400C14_1_s {
    void *(*unk0)(s32, s32);
    s32 unk4;
    f32 unk8;
    u8 unkC;
} UnkStruct_00400C14_1;

typedef struct UnkStruct_00400C14_s {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    UnkStruct_00400C14_1 *unkC;
    u16 unk10;
} UnkStruct_00400C14;

typedef struct UnkStruct_00400C04_s {
    s32 pad0;
    void *(*unk4)(s32, s32, s32, s32);
} UnkStruct_00400C04;

typedef struct UnkStruct_00400C08_s {
    char pad[0x10];
    void *(*unk10)(s32);
} UnkStruct_00400C08;

typedef struct UnkStruct_00400C00_s {
    s32 pad0;
    char pad4[0xC];
    void *(*unk10)(s32, s32, s32, s32);
    char pad14[0x4];
    void *(*unk18)(s32, s32, u8);
} UnkStruct_00400C00;

void uvSortGraphicsCallbackStub(s32 arg0);
void uvSortModuleCleanup(void);
s32 uvSortAllocateGroupForTag(u8 arg0);
void uvSortGroupCallbackStub(s32 arg0);
void uvSortAttachChannelCallbacks(s32 arg0);
void uvSortResetCallbackCounts(s32 arg0);
void uvSortRunCurrentGroupCallbacks(s32 arg0);
void uvSortAppendCallback(s32 arg0, void *(*arg1)(s32, s32), s32 arg2, f32 arg3);
void uvSortBuildCallbackOrder(UnkStruct_00400C14 *arg0);
void uvSortSetGroupOptions(s32 arg0, ...);
void uvUnloadModule(s32 tag); /* extern */

void __entrypoint_func_uvsort_rom_400000(UvSort_Exports *exports);

UnkStruct_00400C00 *D_uvsort_rom_00400C00;
UnkStruct_00400C04 *D_uvsort_rom_00400C04;
UnkStruct_00400C08 *D_uvsort_rom_00400C08;
s32 D_uvsort_rom_00400C0C;
s32 D_uvsort_rom_00400C10;
UnkStruct_00400C14 *D_uvsort_rom_00400C14;
s32 D_uvsort_rom_00400C18;
s32 D_uvsort_rom_00400C1C;
extern s32 D_uvsort_rom_00400BF0[];


void __entrypoint_func_uvsort_rom_400000(UvSort_Exports *exports) { /* Publish six exports, allocate group/callback storage and register the graphics stub. RE_UNKNOWN: import/export lifetime and historical ABI need original loader/callers. */
    s32 allocationGroupCount;
    s32 groupIndex;
    s32 *settings;

    uvUpdateFileAllocPtr(exports);
    exports->uvSortSetGroupOptions = uvSortSetGroupOptions;
    exports->uvSortModuleCleanup = uvSortModuleCleanup;
    exports->uvSortAllocateGroupForTag = uvSortAllocateGroupForTag;
    exports->uvSortGroupCallbackStub = uvSortGroupCallbackStub;
    exports->uvSortAttachChannelCallbacks = uvSortAttachChannelCallbacks;
    // clang-format off
    exports->uvSortAppendCallback = uvSortAppendCallback; D_uvsort_rom_00400C04 = uvLoadModule('CHAN');
    // clang-format on
    D_uvsort_rom_00400C00 = uvLoadModule('CBCK');
    D_uvsort_rom_00400C08 = uvLoadModule('GMGR');
    settings = uvGetSystemProp(0x10); /* Defaults are 4 groups and 50 callbacks; nonzero settings words are copied literally. RE_UNKNOWN: two-word extent and signed size/count domains need original settings producers. */
    if (settings == NULL) {
        allocationGroupCount = D_uvsort_rom_00400C10 = 4;
        D_uvsort_rom_00400C0C = 0x32;
    } else {
        if (settings[0] != 0) {
            D_uvsort_rom_00400C10 = settings[0];
        } else {
            D_uvsort_rom_00400C10 = 4;
        }
        allocationGroupCount = D_uvsort_rom_00400C10;
        if (settings[1] != 0) {
            D_uvsort_rom_00400C0C = settings[1];
        } else {
            D_uvsort_rom_00400C0C = 0x32;
        }
    }

    if (D_uvsort_rom_00400C0C) { // FAKE. RE_UNKNOWN: historical empty conditional/compiler purpose needs original source evidence; preserve it.
    }

    D_uvsort_rom_00400C14 = _uvMemAllocAlign8(allocationGroupCount * 0x14); /* Allocate using the captured count, then traverse the reloaded global count. RE_UNKNOWN: failure, capacity and reinitialization ownership need original allocator/lifecycle callers. */
    for (groupIndex = 0; groupIndex < D_uvsort_rom_00400C10; groupIndex++) {
        D_uvsort_rom_00400C14[groupIndex].unkC = _uvMemAllocAlign8(D_uvsort_rom_00400C0C * 0x10); /* Fresh capacity and group-base reads precede the partial +0x0C/+0x09/+0x0B writes. RE_UNKNOWN: aliasing and remaining-field validity need original producers/consumers. */
        D_uvsort_rom_00400C14[groupIndex].unk9 = 0;
        D_uvsort_rom_00400C14[groupIndex].unkB = 0xFF;
    }

    D_uvsort_rom_00400C04->unk4(0, 0xD, (s32) &D_uvsort_rom_00400C1C, 0); /* CHAN property 13 writes its count only for valid channel 0. RE_UNKNOWN: startup/channel validity and prior +0x1C state need original callers/setup. */
    D_uvsort_rom_00400C00->unk10(D_uvsort_rom_00400C08->unk10(1), (s32) uvSortGraphicsCallbackStub, 0, 0); /* GMGR list 1 is passed to CBCK slot 0x10; registration status is ignored. RE_UNKNOWN: list capacity/storage and failure handling need original list producers/callers. */
}


#line 116 "src/modules/uvsort_rom.c"
/* Original empty graphics callback. Its incoming callback context is
 * intentionally unused. */
void uvSortGraphicsCallbackStub(s32 context) {
}
#line 118 "src/modules/uvsort_rom.c"

#line 119 "src/modules/uvsort_rom.c"
/* Free each original sort-entry buffer and its table, then unload and clear
 * the channel, callback and graphics dependency pointers in original order. */
void uvSortModuleCleanup(void) {
    s32 groupIndex;


    for (groupIndex = 0; groupIndex < D_uvsort_rom_00400C10; groupIndex++) {
        _uvMemFree(D_uvsort_rom_00400C14[groupIndex].unkC);
    }
    _uvMemFree(D_uvsort_rom_00400C14);
    uvUnloadModule('CHAN');
    D_uvsort_rom_00400C04 = 0;
    uvUnloadModule('CBCK');
    D_uvsort_rom_00400C00 = 0;
    uvUnloadModule('GMGR');
    D_uvsort_rom_00400C08 = 0;
}
#line 134 "src/modules/uvsort_rom.c"

#line 135 "src/modules/uvsort_rom.c"

/* Allocate the first unused SORT group, record its byte tag, insert its
 * index into tag order and attach original callbacks for tracked channels.
 * Return -1 on an encountered existing tag or when no group is available.
 * RE_ORIGINAL_QUIRK: the scan stops at the first unused entry, before checking
 * later entries for the same tag; this is not a complete uniqueness search.
 * RE_UNKNOWN: caller tag uniqueness, group/callback capacity and channel-bit
 * domain. Trace original group allocators and callback consumers before adding
 * validation, changing failure behavior or describing tags as unique IDs. */
s32 uvSortAllocateGroupForTag(u8 tag) {
    s32 scanIndex;
    u8 allocatedGroupIndex;
    u8 orderedGroupIndex;
    s32 shiftIndex;
    s32 channelPropertyValue;

    allocatedGroupIndex = 0xFF;
    for (scanIndex = 0; scanIndex < D_uvsort_rom_00400C10; scanIndex++) {
        if (D_uvsort_rom_00400C14[scanIndex].unk9 == 0) {
            D_uvsort_rom_00400C14[scanIndex].unk9 = 1;
            D_uvsort_rom_00400C14[scanIndex].unk8 = tag;
            D_uvsort_rom_00400C14[scanIndex].unk0 = 0.0f;
            D_uvsort_rom_00400C14[scanIndex].unk4 = 0.0f;
            D_uvsort_rom_00400C14[scanIndex].unkA = 0;
            allocatedGroupIndex = scanIndex;
            break;
        }

        if (tag == D_uvsort_rom_00400C14[scanIndex].unk8) {
            return -1;
        }
    }

    if (allocatedGroupIndex == 0xFF) {
        return -1;
    }
    for (scanIndex = 0; scanIndex < D_uvsort_rom_00400C10; scanIndex++) {
        orderedGroupIndex = D_uvsort_rom_00400C14[scanIndex].unkB;
        if ((orderedGroupIndex == 0xFF) || (tag < D_uvsort_rom_00400C14[orderedGroupIndex].unk8)) {
            for (shiftIndex = D_uvsort_rom_00400C10 - 2; shiftIndex >= scanIndex; shiftIndex--) {
                D_uvsort_rom_00400C14[shiftIndex + 1].unkB = D_uvsort_rom_00400C14[shiftIndex].unkB;
            }
            D_uvsort_rom_00400C14[scanIndex].unkB = allocatedGroupIndex;
            break;
        }
    }

    for (scanIndex = 0; scanIndex < D_uvsort_rom_00400C1C; scanIndex++) {
        if ((D_uvsort_rom_00400C18 << scanIndex) & 1) {
            D_uvsort_rom_00400C04->unk4(scanIndex, 6, &channelPropertyValue, 0);
            if (D_uvsort_rom_00400C00->unk18(channelPropertyValue, uvSortRunCurrentGroupCallbacks, tag) != 0) {
                continue;
            }
            D_uvsort_rom_00400C00->unk10(channelPropertyValue, uvSortRunCurrentGroupCallbacks, 0, tag);
        }
    }

    return allocatedGroupIndex;
}
#line 185 "src/modules/uvsort_rom.c"

#line 186 "src/modules/uvsort_rom.c"
/* Original empty exported group callback. Preserve its unused
 * incoming 32-bit context. */
void uvSortGroupCallbackStub(s32 context) {
}
#line 188 "src/modules/uvsort_rom.c"

#line 189 "src/modules/uvsort_rom.c"
/* Register reset and missing active-group callbacks using channel
 * property 6, then set its channel bit. RE_UNKNOWN: channel-shift domain
 * and callback-list capacity/lifetime need original setup and callers. */
void uvSortAttachChannelCallbacks(s32 channel) {
    s32 callbackList;
    s32 groupIndex;


    D_uvsort_rom_00400C04->unk4(channel, 6, &callbackList, 0);
    D_uvsort_rom_00400C00->unk10(callbackList, uvSortResetCallbackCounts, 0, 1);
    for (groupIndex = 0; groupIndex < D_uvsort_rom_00400C10; groupIndex++) {
        if (D_uvsort_rom_00400C14[groupIndex].unk9 != 0) {
            if (D_uvsort_rom_00400C00->unk18(callbackList, uvSortRunCurrentGroupCallbacks, D_uvsort_rom_00400C14[groupIndex].unk8) != NULL) {
                continue;
            }
            D_uvsort_rom_00400C00->unk10(callbackList, uvSortRunCurrentGroupCallbacks, 0, D_uvsort_rom_00400C14[groupIndex].unk8);
        }
    }
    D_uvsort_rom_00400C18 |= 1 << channel;
}
#line 206 "src/modules/uvsort_rom.c"

#line 207 "src/modules/uvsort_rom.c"
/* Reset the current group cursor and every group callback count. The
 * callback context is unused in the original implementation. */
void uvSortResetCallbackCounts(s32 context) {
    s32 i;

    D_uvsort_rom_00400BF0[0] = 0;
    for (i = 0; i < D_uvsort_rom_00400C10; i++) {
        D_uvsort_rom_00400C14[i].unk10 = 0;
    }
}
#line 215 "src/modules/uvsort_rom.c"

#line 216 "src/modules/uvsort_rom.c"
/* Unless the group cursor is -1, resolve its group, order its callback
 * indices and invoke each stored callback/context pair. Advance the cursor
 * afterward, preserving the original shared-state sequencing. */
void uvSortRunCurrentGroupCallbacks(s32 context) {
    UnkStruct_00400C14 *group;
    UnkStruct_00400C14_1 *callbacks;
    UnkStruct_00400C14_1 *entry;
    UnkStruct_00400C14_1 *selected;
    s32 i;

    if (D_uvsort_rom_00400BF0[0] != -1) {
        group = &D_uvsort_rom_00400C14[D_uvsort_rom_00400C14[D_uvsort_rom_00400BF0[0]].unkB];
        uvSortBuildCallbackOrder(group);
        callbacks = group->unkC;
        for (i = 0, entry = callbacks; i < group->unk10; i++, entry++) {
            selected = &callbacks[entry->unkC];
            selected->unk0(context, selected->unk4);
        }
        D_uvsort_rom_00400BF0[0]++;
    }
}
#line 234 "src/modules/uvsort_rom.c"

#line 235 "src/modules/uvsort_rom.c"
/* Append callback/context/key when count!=configured capacity and clear
 * cached-order bit. RE_UNKNOWN: group index, count/capacity/backing
 * correspondence need original setup/reset/append callers; retain equality-only guard. */
void uvSortAppendCallback(s32 groupIndex, void *(*callback)(s32, s32), s32 context, f32 key) {
    UnkStruct_00400C14 *group;
    UnkStruct_00400C14_1 *entry;

    group = &D_uvsort_rom_00400C14[groupIndex];
    entry = &group->unkC[group->unk10];
    if (D_uvsort_rom_00400C0C != group->unk10) {
        entry->unk0 = callback;
        entry->unk4 = context;
        entry->unk8 = key;
        group->unkA &= 0xFFFD;
        group->unk10 += 1;
    }
}
#line 249 "src/modules/uvsort_rom.c"

#line 250 "src/modules/uvsort_rom.c"
/* Cache insertion order (flag one) or descending-key indices (flag two marks cached).
 * RE_ORIGINAL_QUIRK: zero negates to zero; two zero keys can repeat one callback index.
 * Restore all negative keys to positive, including inputs; the runner invokes every recorded index.
 * RE_UNKNOWN: caller key-domain/finite guarantees and safety of the -1000000 selection floor. */
void uvSortBuildCallbackOrder(UnkStruct_00400C14 *group) {
    s32 i;
    s32 j;
    f32 key;
    s32 count;
    UnkStruct_00400C14_1 *entries;

    entries = group->unkC;
    count = group->unk10;

    if (group->unkA & 2) {
        return;
    }

    if (group->unkA & 1) {
        for (i = 0; i < count; i++) {
            entries[i].unkC = i;
        }
        group->unkA |= 2;
        return;
    }

    for (i = 0; i < count; i++) {
        key = -1000000.0f;
        for (j = 0; j < count; j++) {
            if (key < entries[j].unk8) {
                entries[i].unkC = j;
                key = entries[j].unk8;
            }
        }
        entries[entries[i].unkC].unk8 = -entries[entries[i].unkC].unk8;
    }

    for (i = 0; i < count; i++) {
        key = entries[i].unk8;
        if (key < 0.0f) {
            entries[i].unk8 = -key;
        }
    }

    group->unkA |= 2;
}
#line 292 "src/modules/uvsort_rom.c"

#line 293 "src/modules/uvsort_rom.c"
/* Consume zero-terminated option/value pairs; option 1 sets
 * insertion-order mode and unknown tags consume no value. RE_UNKNOWN: group
 * index and promoted-word stream extent/termination need original option callers. */
void uvSortSetGroupOptions(s32 groupIndex, ...) {
    va_list args;
    s32 option;


    va_start(args, groupIndex);

    while (option = va_arg(args, s32)) {
        if (option != 1) {
            continue;
        }

        if (va_arg(args, s32)) {
            D_uvsort_rom_00400C14[groupIndex].unkA |= 1;
        } else {
            D_uvsort_rom_00400C14[groupIndex].unkA &= ~1;
        }
    }
}
#line 312 "src/modules/uvsort_rom.c"
