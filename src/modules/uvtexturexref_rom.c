// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

void __entrypoint_func_uvtexturexref_rom_400000(UvTexturexref_Exports *exports);
void uvParseFreeUVTP(void);
ParsedUVTP *uvParseUVTP(u8 *arg0);
ParsedUVTP *_uvParseUVTP(u8 *data);

s32 D_uvtexturexref_rom_00400200[] = { 0x00080000, __entrypoint_func_uvtexturexref_rom_400000, 0, 0 };

void __entrypoint_func_uvtexturexref_rom_400000(UvTexturexref_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseFreeUVTP = uvParseFreeUVTP;
    exports->uvParseUVTP = uvParseUVTP;
}

void uvParseFreeUVTP(void) {
}

ParsedUVTP *uvParseUVTP(u8 *data) {
    s32 fileId;
    ParsedUVTP *parsedUVTP;
    u32 blockSize;
    void *blockData;
    u32 tag;
    void *uvtpData; // UVTP data

    parsedUVTP = NULL;
    fileId = uvFileReadHeader(data);
    tag = uvFileGetEntryTag(fileId, &blockSize, &blockData);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                uvtpData = malloc8(blockSize);
                _uvMediaCopy(uvtpData, blockData, blockSize);
                parsedUVTP = _uvParseUVTP(uvtpData);
                _uvMemFree(uvtpData);
                break;
            default:
                break;
        }

        tag = uvFileGetEntryTag(fileId, &blockSize, &blockData);
    }
    uvFileFree(fileId);
    return parsedUVTP;
}

ParsedUVTP *_uvParseUVTP(u8 *data) {
    ParsedUVTP *parsedUVTP;
    u16 i;
    u16 count;

    uvConsumeBytes(&count, &data, sizeof(u16));
    parsedUVTP = _uvMemAllocAlign8(0xCU);
    parsedUVTP->unk4 = _uvMemAllocAlign8(count * sizeof(u16));
    parsedUVTP->unk8 = _uvMemAllocAlign8(count * sizeof(u16));
    for (i = 0; i < count; i++) {
        uvConsumeBytes(&parsedUVTP->unk4[i], (u8 **) &data, sizeof(u16));
        uvConsumeBytes(&parsedUVTP->unk8[i], (u8 **) &data, sizeof(u16));
    }
    parsedUVTP->count = count;
    return parsedUVTP;
}
