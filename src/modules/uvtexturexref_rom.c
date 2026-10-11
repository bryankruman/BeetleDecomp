// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

void __entrypoint_func_uvtexturexref_rom_400000(UvTexturexref_Exports *exports);
void uvParseFreeUVTP(void);
ParsedUVTP *uvParseUVTP(u8 *arg0);
ParsedUVTP *_uvParseUVTP(u8 *data);

s32 D_uvtexturexref_rom_00400200[] = { 0x00080000, __entrypoint_func_uvtexturexref_rom_400000, 0, 0 };

/* Publish the UVTP release and parse exports, in that order, after the allocation
 * hook. This entrypoint parses no texture-reference data and resets no resources.
 * RE_UNKNOWN: export storage, UVTP format and referenced texture ownership remain
 * contracts of the later parse/release callers and loader. */
#line 13 "src/modules/uvtexturexref_rom.c"
void __entrypoint_func_uvtexturexref_rom_400000(UvTexturexref_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseFreeUVTP = uvParseFreeUVTP;
    exports->uvParseUVTP = uvParseUVTP;
}
#line 18 "src/modules/uvtexturexref_rom.c"

/* Return without parsing or freeing an asset.
 * RE_UNKNOWN: the historical asset callback contract and ownership remain unresolved. */
#line 19 "src/modules/uvtexturexref_rom.c"
void uvParseFreeUVTP(void) {
}
#line 21 "src/modules/uvtexturexref_rom.c"

/*
 * Enumerate file entries and, for each COMM entry, copy its advertised bytes
 * to an aligned temporary block, parse that copy and free the temporary.
 * Release the file handle and return the last parsed result, or NULL if none.
 * RE_ORIGINAL_QUIRK: Repeated COMM entries replace the result without cleanup.
 * RE_UNKNOWN: Entry extents, copy/allocation outcomes and result ownership are
 * not checked here. The separately exported UVTP free callback remains empty.
 */
#line 22 "src/modules/uvtexturexref_rom.c"
ParsedUVTP *uvParseUVTP(u8 *fileData) {
    s32 fileId;
    ParsedUVTP *textureReferences;
    u32 blockSize;
    void *blockData;
    u32 tag;
    void *commCopy; // UVTP data

    textureReferences = NULL;
    fileId = uvFileReadHeader(fileData);
    tag = uvFileGetEntryTag(fileId, &blockSize, &blockData);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                commCopy = malloc8(blockSize);
                _uvMediaCopy(commCopy, blockData, blockSize);
                textureReferences = _uvParseUVTP(commCopy);
                _uvMemFree(commCopy);
                break;
            default:
                break;
        }

        tag = uvFileGetEntryTag(fileId, &blockSize, &blockData);
    }
    uvFileFree(fileId);
    return textureReferences;
}

/*
 * Read an unsigned-halfword pair count, allocate the 0x0C-byte record and two
 * halfword arrays, then consume interleaved values into the two arrays. Store
 * the count only after the original halfword-indexed loop completes.
 * RE_ORIGINAL_QUIRK: Record field 0x02 remains untouched, including when the
 * pair count is zero; all three allocations retain their original order.
 * RE_UNKNOWN: Input extent, allocation outcomes, meanings of the two indices
 * and eventual array/record ownership require callers and asset-format proof.
 */
#line 51 "src/modules/uvtexturexref_rom.c"
ParsedUVTP *_uvParseUVTP(u8 *inputCursor) {
    ParsedUVTP *textureReferences;
    u16 pairIndex;
    u16 pairCount;

    uvConsumeBytes(&pairCount, &inputCursor, sizeof(u16));
    textureReferences = _uvMemAllocAlign8(0xCU);
    textureReferences->unk4 = _uvMemAllocAlign8(pairCount * sizeof(u16));
    textureReferences->unk8 = _uvMemAllocAlign8(pairCount * sizeof(u16));
    for (pairIndex = 0; pairIndex < pairCount; pairIndex++) {
        uvConsumeBytes(&textureReferences->unk4[pairIndex], (u8 **) &inputCursor, sizeof(u16));
        uvConsumeBytes(&textureReferences->unk8[pairIndex], (u8 **) &inputCursor, sizeof(u16));
    }
    textureReferences->count = pairCount;
    return textureReferences;
}
