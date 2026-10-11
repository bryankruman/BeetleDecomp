// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "os.h"

#define PAD_TAG_START 0xC
#define MAX_FILES 10

static FormFileInfo sCurrentFiles[MAX_FILES];

void uvFileSetPadTagStart(s32);                               /* extern */

/*
 * Register the file in the first unused one of ten FORM slots, read its declared
 * size and type, and reset its entry cursor. Preserve the original header reads,
 * size-plus-eight expression and slot search order.
 * RE_ORIGINAL_QUIRK: retain the existing null-address store and -1 return when all
 * ten slots are occupied; exhaustion reachability and original failure handling
 * remain unresolved. RE_UNKNOWN: caller-provided header/payload extents, declared
 * size validity, slot ownership and lifetime. Resolve original file producers,
 * callers and release paths before adding validation or changing failure behavior.
 */
#line 12 "src/filesystem.c"
s32 uvFileReadHeader(u8* fileBytes) {
    FormFileInfo* freeSlot;
    s32 slotIndex;

    for (freeSlot = sCurrentFiles, slotIndex = 0; slotIndex < MAX_FILES; slotIndex++, freeSlot++) {
        if (freeSlot->fileData == NULL) {
            break;
        }
    }

    if (slotIndex == MAX_FILES) {
        *(volatile s32*)0 = 0;
        return -1;
    }

    freeSlot->fileData = fileBytes;
    freeSlot->fileSize = uvMemRead(&fileBytes[4], 4) + 8; // Read the file size from the header and add the first eight bytes.
    freeSlot->padType = uvMemRead(&fileBytes[8], 4);
    uvFileSetPadTagStart(slotIndex);
    return slotIndex;
}
#line 33 "src/filesystem.c"

/*
 * Release a valid FORM slot by clearing only its file-data pointer. Preserve
 * the other slot fields and ignore indices outside the ten-slot range.
 */
#line 34 "src/filesystem.c"
void uvFileFree(s32 id) {
    if ((id >= 0) && (id < 10)) {
        sCurrentFiles[id].fileData = NULL;
    }
}

/*
 * Return the FORM slot's file-data pointer. The slot index is used directly
 * without a bounds or registration check.
 */
#line 40 "src/filesystem.c"
u8* uvFileGetDataPtr(s32 id) {
    return sCurrentFiles[id].fileData;
}

/*
 * Return the stored FORM slot size directly; the slot index is not validated
 * here.
 */
#line 44 "src/filesystem.c"
s32 uvFileGetSize(s32 id) {
    return sCurrentFiles[id].fileSize;
}

/*
 * Return the stored FORM type word directly; the slot index is not validated
 * here.
 */
#line 48 "src/filesystem.c"
s32 uvFileGetPadType(s32 id) {
    return sCurrentFiles[id].padType;
}

/*
 * Read a tag, payload size and payload address from the current FORM entry,
 * advance the cursor by the declared size plus eight, and skip PAD entries.
 * Use a local size sink when the caller omits that output; preserve the separate
 * mandatory address output and the original initial cursor-limit test.
 * RE_UNKNOWN: valid file-index/address-output domains, full file/chunk capacities,
 * PAD-chain termination, declared-size arithmetic and cursor lifetimes. Resolve
 * original producers, callers and allocation bounds before claiming this reader
 * validates complete chunks or changing its output/failure contract.
 * RE_UNKNOWN: the historical purpose of the original unused pad declaration is
 * unresolved. Retain that declaration because its removal changes the observed
 * stack address of the ignored size sink; recover original source/layout evidence
 * before removing it from a matching build.
 */
#line 52 "src/filesystem.c"
u32 uvFileGetEntryTag(s32 fileIndex, u32* outPayloadSize, void** outPayloadAddress) {
    u32 entryTag;
    s32 pad; // Retain the original declaration: removing it moves the ignored size sink.
    u32 ignoredPayloadSize;


    if (outPayloadSize == NULL) {
        outPayloadSize = &ignoredPayloadSize;
    }
    if ((u32) sCurrentFiles[fileIndex].padTagStart >= (u32) sCurrentFiles[fileIndex].fileSize) {
        return 0U;
    }
    do {
        entryTag = uvMemRead(sCurrentFiles[fileIndex].padTagStart + sCurrentFiles[fileIndex].fileData, 4);
        *outPayloadSize = uvMemRead(sCurrentFiles[fileIndex].padTagStart + sCurrentFiles[fileIndex].fileData + 4, 4);
        *outPayloadAddress = sCurrentFiles[fileIndex].padTagStart + sCurrentFiles[fileIndex].fileData  + 8;

        sCurrentFiles[fileIndex].padTagStart += *outPayloadSize + 8;
    } while (entryTag == 'PAD ');
    return entryTag;
}
#line 73 "src/filesystem.c"

/*
 * Search from the FORM entry start for the requested tag and occurrence
 * threshold, then restore the original entry cursor on success or exhaustion.
 * Preserve the matching-only postincrement, signed candidate-tag word view and
 * every output from the underlying entry reader, including on failed searches.
 * RE_UNKNOWN: caller occurrence-index domain, required outputs on misses, valid
 * file indices, complete chunk capacities/termination and concurrent cursor
 * lifetimes. Resolve original callers, producers and failure consumers before
 * changing indexing, bounds, outputs or cursor ownership.
 */
#line 74 "src/filesystem.c"
u32 uvFileSearchTag(s32 fileIndex, u32* outPayloadSize, void** outPayloadAddress, s32 requestedTag, s32 occurrenceIndex) {
    s32 matchingOccurrenceCount;
    u32 entryTag;
    s32 candidateTagWord;
    u32 savedEntryCursor;

    matchingOccurrenceCount = 0;
    savedEntryCursor = sCurrentFiles[fileIndex].padTagStart;
    uvFileSetPadTagStart(fileIndex);

    while ((entryTag = uvFileGetEntryTag(fileIndex, outPayloadSize, outPayloadAddress)) != 0) {
        candidateTagWord = entryTag;
        if ((candidateTagWord == requestedTag) && (occurrenceIndex <= matchingOccurrenceCount++)) {
            break;
        }
    }
    sCurrentFiles[fileIndex].padTagStart = savedEntryCursor;
    return entryTag;
}
#line 93 "src/filesystem.c"

/*
 * Reset the FORM entry cursor to byte offset 0xC. The slot index is used
 * directly and no payload is read.
 */
#line 94 "src/filesystem.c"
void uvFileSetPadTagStart(s32 id) {
    sCurrentFiles[id].padTagStart = PAD_TAG_START;
}
