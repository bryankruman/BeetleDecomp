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

void __entrypoint_func_uvtseqld_rom_400000(UvtSeqLd_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVTS = uvParseUVTS;
    exports->uvTexSeqLd_stub = uvTexSeqLd_stub;
    exports->uvFreeUVTS = uvFreeUVTS;
    exports->uvGetFirstFrameTexture = uvGetFirstFrameTexture;
}

void uvTexSeqLd_stub(void) {

}

void* uvParseUVTS(u8* data) {
    s32 fileId;
    ParsedUVTS* uvts;
    u32 blockSize;
    void* blockData;
    u32 tag;
    void* dataPtr;

    uvts = NULL;
    fileId = uvFileReadHeader(data);

    while ((tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1)) != 0) {
        switch (tag) {
            case 'COMM':
                dataPtr = blockData;
                uvts = _uvParseUVTS(dataPtr);
                _uvMemFree(dataPtr);
                break;
        }
    }

    uvFileFree(fileId);
    return uvts;
}

void* _uvParseUVTS(u8* data) {
    u16 i;
    u8 frameCount;
    u8 loadFramesTexture;
    uvSeqFrame* frameTable;
    ParsedUVTS* uvts;

    uvConsumeBytes(&loadFramesTexture, &data, sizeof(u8));
    uvConsumeBytes(&frameCount, &data, sizeof(u8));
    frameTable = _uvMemAllocAlign8(frameCount * sizeof(uvSeqFrame));
    for (i = 0; i < frameCount; i++) {
        uvConsumeBytes(&frameTable[i].texture, &data, sizeof(u16));
        uvConsumeBytes(&frameTable[i].frameTime, &data, sizeof(f32));
        frameTable[i].unk2 = 0xFF;
        if ((loadFramesTexture) && (!sDontLoadFrameTexture)) {
            uvLoadFile('UVTX', frameTable[i].texture);
        }
    }
    uvts = _uvMemAllocAlign8(sizeof(ParsedUVTS));
    uvConsumeBytes(&uvts->mode, &data, sizeof(u8));
    uvConsumeBytes(&uvts->reverse, &data, sizeof(u8));
    uvConsumeBytes(&uvts->frameRate, &data, sizeof(f32));
    uvts->frameTable = frameTable;
    uvts->frameCount = frameCount;
    return uvts;
}


void uvFreeUVTS(void *ptr) {
    _uvMemFree(ptr);
}

s32 uvGetFirstFrameTexture(s32 fileId) {
    u8* data;
    ParsedUVTS* uvts;
    s32 texture;

    data = uvGetFileData('UVTS', fileId);
    if (data == NULL) {
        return 0xFFF;
    }

    sDontLoadFrameTexture = TRUE;
    uvts = uvParseUVTS(data);
    sDontLoadFrameTexture = FALSE;
    texture = uvts->frameTable->texture;
    uvFreeUVTS(uvts);
    return texture;
}
