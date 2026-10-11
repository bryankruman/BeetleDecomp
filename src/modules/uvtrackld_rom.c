// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

void uvTrackLoaderReservedCallback(void);
void *uvParseUVTT(u8 *data);
void uvParseFreeUVTT(ParsedUVTT *parsedUVTT);
void __entrypoint_func_uvtrackld_rom_400000(UvTrackLd_Exports *exports);

s32 D_uvtrackld_rom_00400220[] = { 0x000C0000, __entrypoint_func_uvtrackld_rom_400000, 0, 0 };

void __entrypoint_func_uvtrackld_rom_400000(UvTrackLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVTT = uvParseUVTT;
    exports->uvTrackLoaderReservedCallback = uvTrackLoaderReservedCallback;
    exports->uvParseFreeUVTT = uvParseFreeUVTT;
}

#line 20 "src/modules/uvtrackld_rom.c"
/* Original empty track-loader callback; retain its entry point. */
void uvTrackLoaderReservedCallback(void) {
}
#line 22 "src/modules/uvtrackld_rom.c"

/*
 * Allocate a track record and clear its two counts. PNTS reads a signed word
 * count and copies count times 0x38 bytes into a new array; LNKS similarly
 * copies count times 8 bytes. Free each recognized block and the file handle.
 * RE_ORIGINAL_QUIRK: Pointer fields 0x08/0x0C remain uninitialized unless their
 * chunks occur. Repeated chunks overwrite arrays without freeing the old ones.
 * RE_UNKNOWN: Chunk presence/order, signed counts, size overflow, input extent
 * and allocation outcomes require asset/provider proof; no repair is added.
 */
#line 23 "src/modules/uvtrackld_rom.c"
void *uvParseUVTT(u8 *fileData) {
    u32 tag;
    u32 blockSize;
    void *blockData;
    void *blockAllocation;
    ParsedUVTT *trackRecord;
    u8 *blockCursor;
    s32 fileId;

    trackRecord = malloc8(sizeof(ParsedUVTT));
    trackRecord->unk0 = 0;
    trackRecord->unk4 = 0;
    fileId = uvFileReadHeader(fileData);
    while (tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1)) {
        switch (tag) {
            case 'PNTS':
                blockAllocation = blockCursor = blockData;
                uvConsumeBytes(&trackRecord->unk0, &blockCursor, sizeof(int));
                trackRecord->unk8 = malloc8(trackRecord->unk0 * 0x38);
                uvConsumeBytes(trackRecord->unk8, &blockCursor, trackRecord->unk0 * 0x38);
                _uvMemFree(blockAllocation);
                break;
            case 'LNKS':
                blockAllocation = blockCursor = blockData;
                uvConsumeBytes(&trackRecord->unk4, &blockCursor, sizeof(int));
                trackRecord->unkC = malloc8(trackRecord->unk4 * 8);
                uvConsumeBytes(trackRecord->unkC, &blockCursor, trackRecord->unk4 * 8);
                _uvMemFree(blockAllocation);
                break;
        }
    }
    uvFileFree(fileId);
    return trackRecord;
}

/*
 * Free the field-0x0C link array, field-0x08 point array and record in that
 * order, without pointer or count checks.
 * RE_ORIGINAL_QUIRK: The parser leaves an array pointer uninitialized when its
 * chunk is absent. This destructor still passes both fields to the allocator.
 * RE_UNKNOWN: Complete initialization and exclusive ownership must be ensured
 * by callers; allocator behavior for absent or invalid pointers is not proved.
 */
#line 58 "src/modules/uvtrackld_rom.c"
void uvParseFreeUVTT(ParsedUVTT *trackRecord) {
    _uvMemFree(trackRecord->unkC);
    _uvMemFree(trackRecord->unk8);
    _uvMemFree(trackRecord);
}
