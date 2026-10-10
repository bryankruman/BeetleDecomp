// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "os.h"

void uvTexSeqLd_stub(void);
void* uvParseUVTS(u8* arg0);
void* _uvParseUVTS(u8* arg0);
void uvFreeUVTS(void *arg0);
s32 uvGetFirstFrameTexture(s32 arg0);
void __entrypoint_func_uvtseqld_rom_400000(UvtSeqLd_Rom_Exports* exports);

//.data
s32 D_uvtseqld_rom_00400310[] = {0x00100000, __entrypoint_func_uvtseqld_rom_400000, 0, 0};

// .bss
static s32 sDontLoadFrameTexture;

void __entrypoint_func_uvtseqld_rom_400000(UvtSeqLd_Rom_Exports *exports) { /* Update the allocation pointer and publish four loader callbacks through the incoming export table. */
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVTS = uvParseUVTS;
    exports->uvTexSeqLd_stub = uvTexSeqLd_stub;
    exports->uvFreeUVTS = uvFreeUVTS;
    exports->uvGetFirstFrameTexture = uvGetFirstFrameTexture;
/* RE_UNKNOWN: Export-table ownership and repeated initialization are unproved; preserve callback identities and store order. */ }

void uvTexSeqLd_stub(void) { /* Return without performing a field access or call. */

/* RE_UNKNOWN: The historical purpose of this exported empty hook is unproved; retain its current void interface. */ }

void* uvParseUVTS(u8* fileData) { /* Read file blocks until the zero tag, parse each COMM block, free that block buffer and return the last parsed sequence after releasing the file handle. */
    s32 fileId;
    ParsedUVTS* parsedSequence;
    u32 blockSize;
    void* blockData;
    u32 blockTag;
    void* ownedBlockData;

    parsedSequence = NULL;
    fileId = uvFileReadHeader(fileData);

    while ((blockTag = uvFileReadBlock(fileId, &blockSize, &blockData, 1)) != 0) {
        switch (blockTag) {
            case 'COMM':
                ownedBlockData = blockData;
                parsedSequence = _uvParseUVTS(ownedBlockData);
                _uvMemFree(ownedBlockData);
                break;
        }
    }

    uvFileFree(fileId);
    return parsedSequence;
/* RE_UNKNOWN: Stream bounds, multiple COMM blocks and non-COMM buffer ownership are unproved. Preserve the initial null result, original block loop and last-result behavior. */ }

void* _uvParseUVTS(u8* cursor) { /* Consume texture-load and frame-count bytes, allocate and fill the frame table, optionally request each UVTX file, then allocate and fill the parsed sequence header. */
    u16 frameIndex;
    u8 frameCount;
    u8 loadFrameTextures;
    uvSeqFrame* frameTable;
    ParsedUVTS* sequenceData;

    uvConsumeBytes(&loadFrameTextures, &cursor, sizeof(u8));
    uvConsumeBytes(&frameCount, &cursor, sizeof(u8));
    frameTable = _uvMemAllocAlign8(frameCount * sizeof(uvSeqFrame));
    for (frameIndex = 0; frameIndex < frameCount; frameIndex++) {
        uvConsumeBytes(&frameTable[frameIndex].texture, &cursor, sizeof(u16));
        uvConsumeBytes(&frameTable[frameIndex].frameTime, &cursor, sizeof(f32));
        frameTable[frameIndex].unk2 = 0xFF;
        if ((loadFrameTextures) && (!sDontLoadFrameTexture)) {
            uvLoadFile('UVTX', frameTable[frameIndex].texture);
        }
    }
    sequenceData = _uvMemAllocAlign8(sizeof(ParsedUVTS));
    uvConsumeBytes(&sequenceData->mode, &cursor, sizeof(u8));
    uvConsumeBytes(&sequenceData->reverse, &cursor, sizeof(u8));
    uvConsumeBytes(&sequenceData->frameRate, &cursor, sizeof(f32));
    sequenceData->frameTable = frameTable;
    sequenceData->frameCount = frameCount;
    return sequenceData;
/* RE_UNKNOWN: Input length, allocation failure and frame-table ownership are unproved. Keep the unsigned 16-bit index, byte count, field-consumption order, 255 marker and fresh global suppression-flag reads. */ }


void uvFreeUVTS(void *sequenceData) { /* Pass the supplied pointer to the memory-free routine; this body does not traverse the frame table. */
    _uvMemFree(sequenceData);
/* RE_UNKNOWN: The frame table has a separate allocation; its ownership and release lifecycle are unproved. Preserve this single-pointer free. */ }

s32 uvGetFirstFrameTexture(s32 sequenceFileId) { /* Return 4095 when file data is absent. Otherwise set texture-load suppression around parsing, read the first texture and free the parsed header before returning. */
    u8* fileData;
    ParsedUVTS* parsedSequence;
    s32 firstTexture;

    fileData = uvGetFileData('UVTS', sequenceFileId);
    if (fileData == NULL) {
        return 0xFFF;
    }

    sDontLoadFrameTexture = TRUE;
    parsedSequence = uvParseUVTS(fileData);
    sDontLoadFrameTexture = FALSE;
    firstTexture = parsedSequence->frameTable->texture;
    uvFreeUVTS(parsedSequence);
    return firstTexture;
/* RE_UNKNOWN: Parsing failure, empty frame tables, nested suppression users and frame-table ownership are unproved. Preserve both global flag writes and the unchecked first-frame read. */ }
