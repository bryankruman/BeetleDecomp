// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

static UvLights_Exports *sLightsExport;

void __entrypoint_func_uvcontourld_rom_400000(UvContourLd_Exports *exports);
void uvContourLoaderCleanup(void);
ParsedUVCT *uvParseUVCT(u8 *arg0);
void uvContourWritePackedTriangles(Gfx *gdl, u16 arg1, u16 arg2);
ParsedUVCT *_uvParseUVCT(u8 *arg0);
void uvContourLoaderReleaseParsedContour(ParsedUVCT *uvct);

s32 D_uvcontourld_rom_00400C30[] = {0x000C0000, __entrypoint_func_uvcontourld_rom_400000, 0, 0};

/* Publish contour parse, module-cleanup and parsed-resource release exports,
 * then load and save LGHT. No contour is parsed or configuration reset here.
 * RE_UNKNOWN: writable export storage, load failure and retained light-provider
 * ownership remain loader/caller contracts. Preserve the conditional #line. */
#line 17 "src/modules/uvcontourld_rom.c"
void __entrypoint_func_uvcontourld_rom_400000(UvContourLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVCT = uvParseUVCT;
    exports->uvContourLoaderCleanup = uvContourLoaderCleanup;
    exports->uvContourLoaderReleaseParsedContour = uvContourLoaderReleaseParsedContour;
#ifdef __sgi
#line 18
#endif
    sLightsExport = uvLoadModule('LGHT');
}
#line 21 "src/modules/uvcontourld_rom.c"

#line 22 "src/modules/uvcontourld_rom.c"
/* Unload the contour loader's LGHT dependency.
 * RE_UNKNOWN: initialized module lifetime remains a caller contract. */
void uvContourLoaderCleanup(void) {
    uvUnloadModule('LGHT');
}
#line 25 "src/modules/uvcontourld_rom.c"

/* Scan file blocks and decode each COMM block through the original parser.
 * Free each consumed COMM block and the file reader; return the last parsed
 * contour, or NULL if no COMM block was found. Preserve other-tag handling.
 * RE_UNKNOWN: valid block order/duplicate COMM tags and allocation-failure
 * contracts. Trace original UVCT asset writers and callers before adding
 * checks or assigning ownership of overwritten parser results. */
#line 26 "src/modules/uvcontourld_rom.c"
ParsedUVCT *uvParseUVCT(u8 *fileData) {
    s32 fileId;
    ParsedUVCT *parsedContour;
    u32 blockSize;
    void *blockData;
    u32 tag;
    u8 *commonBlock;

    parsedContour = NULL;
    fileId = uvFileReadHeader(fileData);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                commonBlock = blockData;
                parsedContour = _uvParseUVCT(commonBlock);
                _uvMemFree(commonBlock);
                break;
            default:
                break;
        }
        tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    }
    uvFileFree(fileId);
    return parsedContour;
}
#line 52 "src/modules/uvcontourld_rom.c"

#line 53 "src/modules/uvcontourld_rom.c"
/* Decode three five-bit vertex indices from each packed word. Emit
 * two triangles when the second word is nonzero, otherwise one. Preserve
 * the original zero-word sentinel rather than treating it as a triangle. */
void uvContourWritePackedTriangles(Gfx *gdl, u16 firstTriangle, u16 secondTriangle) {
    if (secondTriangle) {
        gSP2Triangles(gdl, (firstTriangle & 0x7C00) >> 0xA, (firstTriangle & 0x3E0) >> 5, (firstTriangle & 0x1F), 0,
                      (secondTriangle & 0x7C00) >> 0xA, (secondTriangle & 0x3E0) >> 5, (secondTriangle & 0x1F), 0);
    } else {
        gSP1Triangle(gdl, (firstTriangle & 0x7C00) >> 0xA, (firstTriangle & 0x3E0) >> 5, (firstTriangle & 0x1F), 0);
    }
}
#line 61 "src/modules/uvcontourld_rom.c"

/* Decode the contour stream into vertex, model, render-record and display-list storage.
 * Preserve packed command decoding, partial light input and existing zero-model publication.
 * RE_UNKNOWN: stream lengths, count/index limits, allocation failure, shared-storage lifetime,
 * metadata meanings and historical record declarations need original assets/caller proof. */
#line 62 "src/modules/uvcontourld_rom.c"
ParsedUVCT *_uvParseUVCT(u8 *streamCursor) {
    Vtx *currentVertexBlock;
    ParsedUVMD *modelResource;
    Vtx *vertexBase;
    Unk80225FBC_0x28_UnkC *sharedRecords;
    Unk80225FBC_0x28 *renderRecords;
    s32 displayListIndex;
    UnkSobjDraw *modelRecords; /* RE_ORIGINAL_QUIRK: native 0x40033C skips the sole
     * SP+0xFC pointer store when model count is zero; 0x4009E4/0x4009E8 still
     * copy that stack word to parsed-contour offset 0x10. RE_UNKNOWN: valid
     * zero-model UVCT assets and whether callers use that pointer at count zero.
     * Trace original assets/callers before assigning a default or changing behavior. */
#line 70 "src/modules/uvcontourld_rom.c"
    ParsedUVCT *parsedContour;
    Unk80225FBC_0x28 *renderRecord;
    UnkSobjDraw *modelRecord;
    Vtx *vertexBlock;
    u16 sharedRecordCount;
    u16 renderRecordCount;
    u16 modelCount;
    u16 pendingTriangle;
    Gfx *displayList;
    s32 recordIndex; // spDC
    s32 vertexIndex;
    s32 commandIndex;
    s32 encodedVertexCountMinusOne;
    u8 matrixCount;
    u8 vertexCommandByte;
    u16 totalVertexCount;
    u16 commandCount;
    u16 displayListEntryCount;
    u16 streamWord;
    f32 metadata30;
    f32 metadata2C;
    f32 metadata28;
    UnkStruct_uvlight_rom_00401758 lightRecord;
    s32 consumedVertexCount;

    uvConsumeBytes(&totalVertexCount, (u8 **) &streamCursor, sizeof(u16));
    uvConsumeBytes(&sharedRecordCount, (u8 **) &streamCursor, sizeof(u16));
    uvConsumeBytes(&modelCount, (u8 **) &streamCursor, sizeof(u16));
    uvConsumeBytes(&renderRecordCount, (u8 **) &streamCursor, sizeof(u16));
    uvConsumeBytes(&metadata2C, (u8 **) &streamCursor, sizeof(s32));
    uvConsumeBytes(&metadata30, (u8 **) &streamCursor, sizeof(s32));
    uvConsumeBytes(&metadata28, (u8 **) &streamCursor, sizeof(s32));
    vertexBase = _uvMemAlloc(totalVertexCount * sizeof(Vtx), 8);
    currentVertexBlock = vertexBase;

    consumedVertexCount = 0;
    sharedRecords = _uvMemAllocAlign8(sharedRecordCount * 8);
    _uvMediaCopy(sharedRecords, streamCursor, sharedRecordCount * 8); /* Copy the shared eight-byte records without interpreting their fields. */
    streamCursor += sharedRecordCount * 8;
    if (modelCount != 0) {
        modelRecords = _uvMemAllocAlign8(modelCount * sizeof(UnkSobjDraw));
    }
    for (recordIndex = 0; recordIndex < modelCount; recordIndex++) {
        modelRecord = &modelRecords[recordIndex];
        uvConsumeBytes(&matrixCount, (u8 **) &streamCursor, sizeof(u8));
        modelRecord->unk4 = _uvMemAllocAlign8(matrixCount * sizeof(Mtx4F));
        uvConsumeBytes(modelRecord->unk4, (u8 **) &streamCursor, matrixCount * sizeof(Mtx4F));
        modelRecord->unk2 = matrixCount;
        modelRecord->unk38 = 0;
        uvConsumeBytes(&modelRecord->modelId, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&modelRecord->unk8, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&modelRecord->unkC, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&modelRecord->unk10, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&modelRecord->unk14, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&modelRecord->unk18, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&modelRecord->unk1A, (u8 **) &streamCursor, sizeof(u16));
        modelRecord->unk30 = metadata2C;
        modelRecord->unk34 = metadata30;
        modelResource = uvLoadFile('UVMD', modelRecord->modelId);
        if (modelResource->unk5 & 0x76) {
            modelRecord->unk40 = 1;
        } else {
            modelRecord->unk40 = 0;
        }
        modelRecord->unk3C = 1000000.0f;
        modelRecord->unk1C = 0;
    }
    renderRecords = _uvMemAllocAlign8(renderRecordCount * sizeof(Unk80225FBC_0x28));
    for (recordIndex = 0; recordIndex < renderRecordCount; recordIndex++) {
        renderRecord = &renderRecords[recordIndex];
        renderRecord->unk0 = NULL;
        uvConsumeBytes(&renderRecord->texture, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&lightRecord.unk2C, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&lightRecord.unk28, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&lightRecord.unk24, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&renderRecord->unkE, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&renderRecord->unk12, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&renderRecord->unk10, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&renderRecord->unk14, (u8 **) &streamCursor, sizeof(u16));
        if ((renderRecord->texture & 0xFFF) != 0xFFF) {
            uvLoadFile('UVTX', (renderRecord->texture & 0xFFF));
        }
        if (renderRecord->texture & 0x40000) {
            renderRecord->unkC = sLightsExport->uvLightAcquireMatchingColorRecord(&lightRecord); /* LGHT slot 0x28 consumes the three initialized words at 0x24/0x28/0x2C. */
        } else {
            renderRecord->unkC = -1;
        }
        uvConsumeBytes(&commandCount, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&displayListEntryCount, (u8 **) &streamCursor, sizeof(u16));
        _uvMediaCopy(currentVertexBlock, streamCursor, (s16) renderRecord->unkE * 0x10); /* Preserve the signed count and all following cursor/count arithmetic. */
        renderRecord->unk0 = currentVertexBlock;
        streamCursor += renderRecord->unkE * 0x10;
        consumedVertexCount += renderRecord->unkE;
        renderRecord->unk34 = 0.0f;

        for (vertexIndex = 0; vertexIndex < renderRecord->unkE; vertexIndex++) {
            if (renderRecord->unk34 < currentVertexBlock[vertexIndex].v.ob[2]) {
                renderRecord->unk34 = currentVertexBlock[vertexIndex].v.ob[2];
            }
        }
        renderRecord->unk34 /= metadata30; /* RE_ORIGINAL_QUIRK: retain this scan/divide before the later 1000000.0f overwrite. */
        displayList = _uvMemAlloc(displayListEntryCount * sizeof(Gfx), 8);
        displayListIndex = 0;
        pendingTriangle = 0;
        for (commandIndex = 0; commandIndex < commandCount; commandIndex++) {
            uvConsumeBytes(&streamWord, (u8 **) &streamCursor, sizeof(u16));
            if (streamWord & 0x8000) {
                if (pendingTriangle == 0) {
                    pendingTriangle = streamWord;
                } else {
                    uvContourWritePackedTriangles(&displayList[displayListIndex], pendingTriangle, streamWord);
                    displayListIndex++;
                    pendingTriangle = 0;
                }
                continue;
            }
            if (pendingTriangle != 0) {
                uvContourWritePackedTriangles(&displayList[displayListIndex], pendingTriangle, 0);
                displayListIndex++;
                pendingTriangle = 0;
            }
            uvConsumeBytes(&vertexCommandByte, (u8 **) &streamCursor, 1U);
            vertexBlock = &currentVertexBlock[streamWord & 0x1FFF];
            encodedVertexCountMinusOne = (((s32) (streamWord & 0x6000) >> 0xA) | ((s32) (vertexCommandByte & 0xE0) >> 5));
            gSPVertex(&displayList[displayListIndex], OS_PHYSICAL_TO_K0(vertexBlock), encodedVertexCountMinusOne + 1, vertexCommandByte & 0x1F); /* RE_UNKNOWN: stream index bounds and allocated command capacity need asset proof. */
            displayListIndex++;
        }

        currentVertexBlock = &vertexBase[consumedVertexCount];
        if (pendingTriangle != 0) {
            uvContourWritePackedTriangles(&displayList[displayListIndex], pendingTriangle, 0);
            displayListIndex++;
        }
        gSPEndDisplayList(&displayList[displayListIndex]);
        displayListIndex++;

        renderRecord->unk8 = displayList;
        uvConsumeBytes(&streamWord, (u8 **) &streamCursor, sizeof(u16));
        renderRecord->unk18 = &sharedRecords[streamWord];
        uvConsumeBytes(&streamWord, (u8 **) &streamCursor, sizeof(u16));
        renderRecord->unk1C = streamWord;
        uvConsumeBytes(&renderRecord->unk1E, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&renderRecord->unk20, (u8 **) &streamCursor, sizeof(u16));
        uvConsumeBytes(&renderRecord->unk24, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&renderRecord->unk28, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&renderRecord->unk2C, (u8 **) &streamCursor, sizeof(s32));
        uvConsumeBytes(&renderRecord->unk30, (u8 **) &streamCursor, sizeof(s32));
        renderRecord->unk34 = 1000000.0f;
    }
    parsedContour = _uvMemAllocAlign8(sizeof(ParsedUVCT));
    parsedContour->vtxTable = vertexBase;
    parsedContour->vtxCount = totalVertexCount;
    parsedContour->unk8 = renderRecords;
    parsedContour->unkC = renderRecordCount;
    parsedContour->unk10 = modelRecords;
    parsedContour->unk14 = modelCount;
    uvConsumeBytes(&parsedContour->unk18, (u8 **) &streamCursor, sizeof(s32));
    uvConsumeBytes(&parsedContour->unk1C, (u8 **) &streamCursor, sizeof(s32));
    uvConsumeBytes(&parsedContour->unk20, (u8 **) &streamCursor, sizeof(s32));
    uvConsumeBytes(&parsedContour->unk24, (u8 **) &streamCursor, sizeof(s32));
    parsedContour->unk2C = metadata2C;
    parsedContour->unk30 = metadata30;
    parsedContour->unk28 = metadata28;
    return parsedContour;
}

#line 236 "src/modules/uvcontourld_rom.c"
/* Release parsed contour vertices, referenced UVTX/UVMD files, model
 * payloads, texture payloads and light records before freeing the contour.
 * Retain low-12-bit texture identifiers, 0xFFF/0xFFFF sentinels and free the
 * shared offset-0x18 texture allocation only for the first texture record.
 * RE_UNKNOWN: remaining payload meanings and sharing contracts are unproved;
 * no additional ownership or allocation checks are introduced. */
void uvContourLoaderReleaseParsedContour(ParsedUVCT *uvct) {
    s32 i;
    struct UnkSobjDraw *modelRecord;
    s32 textureId;
    s32 modelId;
    ParsedUVCT *contour = uvct;

    _uvMemFree(contour->vtxTable);

    for (i = 0; i < contour->unkC; i++) {
        Unk80225FBC_0x28 *textureToUnload = &contour->unk8[i];
        textureId = (textureToUnload->texture & 0xFFF);
        if (textureId != 0xFFF) {
            uvUnloadFile('UVTX', textureId);
        }
    }

    for (i = 0; i < contour->unk14; i++) {
        modelRecord = &contour->unk10[i];
        modelId = modelRecord->modelId;
        if (modelId != 0xFFFF) {
            uvUnloadFile('UVMD', modelRecord->modelId);
        }
        _uvMemFree(modelRecord->unk4);
    }
    if (contour->unk14 != 0) {
        _uvMemFree(contour->unk10);
    }

    for (i = 0; i < contour->unkC; i++) {
        Unk80225FBC_0x28 *textureToRelease = &contour->unk8[i];
        if (i == 0) {
            _uvMemFree(textureToRelease->unk18);
        }
        _uvMemFree(textureToRelease->unk8);
        if (textureToRelease->unkC != 0xFFFF) {
            sLightsExport->uvLightReleaseRecord(textureToRelease->unkC);
        }
    }
    if (contour->unkC != 0) {
        _uvMemFree(contour->unk8);
    }
    _uvMemFree(contour);
}
#line 280 "src/modules/uvcontourld_rom.c"
