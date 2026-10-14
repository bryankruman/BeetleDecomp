// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#include "uvmodelld_rom.h"
void uvModelLoaderCleanup(void);
ParsedUVMD *uvModelLoaderParseCommonBlocks(u8 *);
void uvModelLoaderReleaseRenderResources(ParsedUVMD *);
ParsedUVMD *uvModelLoaderParsePackedModel(u8 *);

extern UvLights_Exports *D_uvmodelld_rom_00400EE0;
extern UvFMtx_Rom_Exports *D_uvmodelld_rom_00400EE4;
ParsedUVMD *func_uvmodelld_rom_00400258(void *); /* extern */


#line 21 "src/modules/uvmodelld_rom.c"
/*
 * Publish parse, cleanup and render-resource release exports, then load LGHT followed by
 * FMTX. RE_UNKNOWN: dependency-load failure, repeated initialization and lifetime contracts.
 */
#line 21 "src/modules/uvmodelld_rom.c"
void __entrypoint_func_uvmodelld_rom_400000(UvModelLd_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvModelLoaderParseCommonBlocks = uvModelLoaderParseCommonBlocks;
    exports->uvModelLoaderCleanup = uvModelLoaderCleanup;
    exports->uvModelLoaderReleaseRenderResources = uvModelLoaderReleaseRenderResources;
#ifdef __sgi
    #line 22
#endif
    D_uvmodelld_rom_00400EE0 = uvLoadModule('LGHT');
    // ! unused export
    D_uvmodelld_rom_00400EE4 = uvLoadModule('FMTX');
}

#line 11 "src/modules/uvmodelld_rom.c"
/* Unload FMTX and LGHT dependencies in their original order. */
void uvModelLoaderCleanup(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('LGHT');
}
#line 15 "src/modules/uvmodelld_rom.c"

// uvParseUVMD
#line 17 "src/modules/uvmodelld_rom.c"
/* Read a model FORM file, parse each COMM block and free its temporary
 * block storage. Return the most recently parsed model, or zero when
 * no common block was found, after releasing the file reader.
 * RE_UNKNOWN: whether valid UVMD files permit multiple COMM blocks. Each
 * result replaces the local return value without releasing the prior result
 * here; establish the file-format and parser ownership contract first. */
ParsedUVMD *uvModelLoaderParseCommonBlocks(u8 *fileData) {
    s32 fileId;
    s32 parsedModel;
    u32 blockSize;
    void *blockData;
    u32 tag;
    s32 commonBlock;

    parsedModel = 0;
    fileId = uvFileReadHeader(fileData);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                commonBlock = blockData;
                parsedModel = func_uvmodelld_rom_00400258(commonBlock);
                _uvMemFree(commonBlock);
                break;
            default:
                break;
        }

        tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    }
    uvFileFree(fileId);
    return parsedModel;
}
#line 44 "src/modules/uvmodelld_rom.c"

#line 45 "src/modules/uvmodelld_rom.c"
/* Expand two packed 5-bit RGB colors into the original two command
 * words. A zero second color selects command five and a zero second
 * word; otherwise command six carries both expanded colors. */
void uvModelLoaderPackColorCommandWords(s32 *commandWords, u16 firstColor, u16 secondColor) {
    // clang-format off
    if (secondColor) { \
        commandWords[0] = (((((firstColor & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10) \
                  | (((((firstColor & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((firstColor & 0x1F) * 2) & 0xFF) \
                  | 0x06000000; \
        commandWords[1] = ((((((secondColor & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10) \
                   | (((((secondColor & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((secondColor & 0x1F) * 2) & 0xFF)); \
    } else {
        commandWords[0] = (((((firstColor & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10)
                  | (((((firstColor & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((firstColor & 0x1F) * 2) & 0xFF)
                  | 0x05000000;
        commandWords[1] = 0;
    }
    // clang-format on
}
#line 61 "src/modules/uvmodelld_rom.c"








#define PHYSICAL_TO_K0(x) (void *)(((u8*)(x)+0x80000000))
#line 86 "src/modules/uvmodelld_rom.c"
/*
 * Parse packed model metadata into combined vertex, part, LOD, state, command and matrix
 * storage; acquire optional model/PFX references, textures and lights. RE_ORIGINAL_QUIRK:
 * retain unchecked allocations, partial header/optional-record initialization and three-word
 * light input, signed count arithmetic, empty branches and the final u64 pointer cast.
 * RE_UNKNOWN: input extent, count/capacity relationships, optional property units, failure
 * handling and recursive asset/light ownership.
 *
 * Encoded tokens and reserved Gfx slots are different counts. Pair color tokens; flush a
 * pending color before a vertex command or at loop end, then append the end command.
 * RE_UNKNOWN: the asset invariant ensuring all emitted commands fit the reserved slots; byte-
 * balance decrements do not enforce capacity.
 *
 * Fill only the three packed-color words at 0x24, 0x28 and 0x2C: the accepted
 * uvLightAcquireMatchingColorRecord provider reads only those caller fields, copies the
 * values into owned records and retains no caller pointer. Its -2 sentinel and -1 capacity
 * result are stored unchanged; valid capacity/result use remains a caller contract.
 */
#line 86 "src/modules/uvmodelld_rom.c"
ParsedUVMD *uvModelLoaderParsePackedModel(u8 *inputCursor) {
    s16 optionalReferenceId;
    s32 partIndex;
    s32 lodIndex;
    s32 stateIndex;
    s32 allocationBytesOrTokenIndex; /* Matching source shares allocation bytes and encoded-command index. */
    ParsedUVMD_1 *parts;
    ParsedUVMD *model;
    Vtx *vertexCursor;
    s32 partBytesOrVertexCountMinusOne; /* Matching source shares part-record bytes and packed vertex-count field. */
    uvGfxState *stateRecords;
    char stackLayoutPad[0xC]; /* RE_UNKNOWN: matching-source stack-layout padding; historical source intent unproved. */
    UnkStruct_uvlight_rom_00401758 lightRecord;
    u16 encodedCommandCount;
    u16 commandSlotCount; /* Matching source shares total-command and per-state command counts. */
    u16 totalStateCount;
    u16 packedCommandToken;
    u16 pendingColorToken;
    u8 vertexCommandByte;
    u8 lodUsesFlag08000000;
    s32 consumedVertexCount;
    uvModelLOD *lods;
    u8 *recordCursor;
    u8 *stateAndCommandCursor;
    u32 remainingAllocationBytes;
    s32 geometryBytesOrMatrixBytes; /* Matching source shares geometry bytes and final matrix-copy bytes. */
    ParsedUVMD header;
    Gfx *workPointerOrMatrixBytes; /* Matching source shares matrix-byte count, record bases and Gfx cursor; retain pointer/integer use. */
    s32 vertexBytesOrCommandIndex; /* Matching source shares vertex-table bytes and output-command index. */
    u8 *assetsStart;
    u8 consumedUnknownByte0; /* RE_UNKNOWN: consumed unused byte; asset meaning and original source intent unproved. */
    u8 consumedUnknownByte1; /* RE_UNKNOWN: consumed unused byte; asset meaning and original source intent unproved. */
    s32 textureId;

    uvConsumeBytes(&header.unk4, &inputCursor, sizeof(u8));
    uvConsumeBytes(&header.unk6, &inputCursor, sizeof(u8));
    uvConsumeBytes(&header.unk5, &inputCursor, sizeof(u8));
    uvConsumeBytes(&header.unk7, &inputCursor, sizeof(u8));
    uvConsumeBytes(&header.vtxCount, &inputCursor, sizeof(u16));
    uvConsumeBytes(&totalStateCount, &inputCursor, sizeof(u16));
    uvConsumeBytes(&commandSlotCount, &inputCursor, sizeof(u16));
    if (header.unk5 & 0x80) {
        header.unk20 = _uvMemAllocAlign8(sizeof(ParsedUVMD_3C));
        uvConsumeBytes(&header.unk20->unk0, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk4, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk8, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unkC, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk10, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk14, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk18, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk1C, &inputCursor, sizeof(f32));
        uvConsumeBytes(&header.unk20->unk20, &inputCursor, sizeof(s32));
        uvConsumeBytes(&header.unk20->unk24, &inputCursor, sizeof(s32));
        uvConsumeBytes(&optionalReferenceId, &inputCursor, sizeof(s16));
        header.unk20->unk2C = (s32) optionalReferenceId;
        uvConsumeBytes(&optionalReferenceId, &inputCursor, sizeof(s16));
        header.unk20->unk30 = (s32) optionalReferenceId;
        uvConsumeBytes(&optionalReferenceId, &inputCursor, sizeof(s16));
        header.unk20->unk34 = (s32) optionalReferenceId;
        uvConsumeBytes(&header.unk20->unk28, &inputCursor, sizeof(u8));
        if ((header.unk20->unk30 == -1) && (header.unk20->unk34 == -1) && (header.unk20->unk2C == -1)) {
            header.unk20->unk4 = 1000.0f;
        }
        header.unk20->unk0 *= 0.44704f;
        header.unk20->unk4 *= 0.44704f;
        header.unk20->unkC *= 0.44704f;
        header.unk20->unk10 *= 0.44704f;
        header.unk20->unk18 *= 0.01745329f;
        header.unk20->unk1C *= 0.0390419f;
        header.unk20->unk38 = 0;
        if (header.unk20->unk2C != -1) {
            uvLoadFile('UVMD', header.unk20->unk2C);
        }
        if (header.unk20->unk30 != -1) {
            uvLoadFile('UVMD', header.unk20->unk30);
        }
        if (header.unk20->unk34 != -1) {
            uvLoadFile('UVPX', header.unk20->unk34);
        }
    } else {
        header.unk20 = NULL;
    }
    uvConsumeBytes(&header.unkC, &inputCursor, sizeof(f32));
    uvConsumeBytes(&header.unk10, &inputCursor, sizeof(f32));
    uvConsumeBytes(&header.unk14, &inputCursor, sizeof(f32));

    /* ASSET PACKAGE STRUCTURE

        assetsStart - asset block start

        vertexCursor (Vtx table)
        uvGfxState + Gfx (RE_UNKNOWN: exact state/command layout)
        ParsedUVMD
        ParsedUVMD_1s
        uvModelLODs
        Mtx4Fs
    */

    vertexBytesOrCommandIndex = header.vtxCount * sizeof(Vtx);
    partBytesOrVertexCountMinusOne = header.unk4 * sizeof(ParsedUVMD_1);
    workPointerOrMatrixBytes = header.unk6 * sizeof(Mtx4F);
    geometryBytesOrMatrixBytes = vertexBytesOrCommandIndex + (commandSlotCount * sizeof(Gfx)) + (totalStateCount * sizeof(uvGfxState));
    allocationBytesOrTokenIndex = geometryBytesOrMatrixBytes + (u32)workPointerOrMatrixBytes + partBytesOrVertexCountMinusOne + (header.unk4 * header.unk6 * sizeof(uvModelLOD));
    remainingAllocationBytes = allocationBytesOrTokenIndex + sizeof(ParsedUVMD);
    assetsStart = _uvMemAlloc(remainingAllocationBytes, 8);
    if (allocationBytesOrTokenIndex) {
    }
    if (partBytesOrVertexCountMinusOne) {
    }
    if (workPointerOrMatrixBytes) {
    }
    recordCursor = assetsStart + geometryBytesOrMatrixBytes;
    stateAndCommandCursor = assetsStart;
    recordCursor += sizeof(ParsedUVMD);

    if (header.unk6) {
    }

    model = (void*)(assetsStart + geometryBytesOrMatrixBytes);
    remainingAllocationBytes -= sizeof(ParsedUVMD);
    *model = header;

    stateAndCommandCursor += vertexBytesOrCommandIndex;
    remainingAllocationBytes -= vertexBytesOrCommandIndex;
    geometryBytesOrMatrixBytes -= vertexBytesOrCommandIndex;

    model->vtxTable = (Vtx*)assetsStart;
    consumedVertexCount = 0;

    vertexCursor = (Vtx*)assetsStart;

    workPointerOrMatrixBytes = (Gfx*)recordCursor;
    remainingAllocationBytes -= partBytesOrVertexCountMinusOne;
    recordCursor += partBytesOrVertexCountMinusOne;
    parts = model->unk0 = workPointerOrMatrixBytes;
    for (partIndex = 0; partIndex < model->unk4; partIndex++) {
        uvConsumeBytes(&parts[partIndex].unk8, &inputCursor, sizeof(u8));
        uvConsumeBytes(&parts[partIndex].unk9, &inputCursor, sizeof(u8));
        uvConsumeBytes(&parts[partIndex].unk4, &inputCursor, sizeof(f32));
        parts[partIndex].unk4 = SQ(parts[partIndex].unk4);
        // clang-format off
        workPointerOrMatrixBytes = recordCursor;\
        recordCursor += parts[partIndex].unk8 * 0x2C;\
        remainingAllocationBytes -= parts[partIndex].unk8 * 0x2C;
        // clang-format on
        lods = parts[partIndex].unk0 = workPointerOrMatrixBytes;
        for (lodIndex = 0; lodIndex < parts[partIndex].unk8; lodIndex++) {
            lodUsesFlag08000000 = 0;
            uvConsumeBytes(&lods[lodIndex].unk5, &inputCursor, sizeof(u8));
            uvConsumeBytes(&lods[lodIndex].unk6, &inputCursor, sizeof(u8));
            uvConsumeBytes(&lods[lodIndex].unk7, &inputCursor, sizeof(u8));
            uvConsumeBytes(&lods[lodIndex].unk8, &inputCursor, sizeof(uvModelLOD_inner));
            lods[lodIndex].unk8.unk0 *= model->unk10;
            lods[lodIndex].unk8.unkC *= model->unk10;
            lods[lodIndex].unk8.unk4 *= model->unk10;
            lods[lodIndex].unk8.unk10 *= model->unk10;
            lods[lodIndex].unk8.unk8 *= model->unk10;
            lods[lodIndex].unk8.unk14 *= model->unk10;
            uvConsumeBytes(&consumedUnknownByte0, &inputCursor, 1);
            uvConsumeBytes(&consumedUnknownByte1, &inputCursor, 1);
            uvConsumeBytes(&lods[lodIndex].unk4, &inputCursor, 1);

            if (lods[lodIndex].unk4 != 0) {
                // clang-format off
                remainingAllocationBytes -= lods[lodIndex].unk4 * sizeof(uvGfxState); \
                geometryBytesOrMatrixBytes -= lods[lodIndex].unk4 * sizeof(uvGfxState);
                // clang-format on
                lods[lodIndex].stateTable = stateRecords = (void*)stateAndCommandCursor;
                stateAndCommandCursor += lods[lodIndex].unk4 * sizeof(uvGfxState);
            } else {
                lods[lodIndex].stateTable = stateRecords = NULL;
            }

            for (stateIndex = 0; stateIndex < lods[lodIndex].unk4; stateIndex++) {
                uvConsumeBytes(&stateRecords[stateIndex].state, &inputCursor, sizeof(s32));
                uvConsumeBytes(&lightRecord.unk2C, &inputCursor, sizeof(s32));
                uvConsumeBytes(&lightRecord.unk28, &inputCursor, sizeof(s32));
                uvConsumeBytes(&lightRecord.unk24, &inputCursor, sizeof(s32));
                uvConsumeBytes(&stateRecords[stateIndex].unkE, &inputCursor, sizeof(s16));
                uvConsumeBytes(&stateRecords[stateIndex].unk12, &inputCursor, sizeof(s16));
                uvConsumeBytes(&stateRecords[stateIndex].unk10, &inputCursor, sizeof(s16));
                uvConsumeBytes(&stateRecords[stateIndex].unk14, &inputCursor, sizeof(s16));
                uvConsumeBytes(&encodedCommandCount, &inputCursor, sizeof(u16));
                uvConsumeBytes(&commandSlotCount, &inputCursor, sizeof(u16));
                textureId = stateRecords[stateIndex].state & 0xFFF;
                if (textureId != 0xFFF) {
                    uvLoadFile('UVTX', textureId);
                }
                if (stateRecords[stateIndex].state & 0x40000) {
                    // Acquire the LGHT record through the existing export slot 0x28.
                    stateRecords[stateIndex].unkC = D_uvmodelld_rom_00400EE0->uvLightAcquireMatchingColorRecord(&lightRecord);
                } else {
                    stateRecords[stateIndex].unkC = -1;
                }
                if (stateRecords[stateIndex].state & 0x08000000) {
                    lodUsesFlag08000000 = 1;
                }
                stateRecords[stateIndex].unk0 = (s32) vertexCursor;
                _uvMediaCopy(vertexCursor, inputCursor, stateRecords[stateIndex].unkE * sizeof(Vtx));
                inputCursor = inputCursor + stateRecords[stateIndex].unkE * sizeof(Vtx);
                consumedVertexCount += stateRecords[stateIndex].unkE;
                workPointerOrMatrixBytes = (void*)stateAndCommandCursor;
                // clang-format off
                remainingAllocationBytes -= commandSlotCount * sizeof(Gfx); \
                geometryBytesOrMatrixBytes -= commandSlotCount * sizeof(Gfx);
                // clang-format on
                stateAndCommandCursor += commandSlotCount * sizeof(Gfx);
                stateRecords[stateIndex].displayList = PHYSICAL_TO_K0(workPointerOrMatrixBytes);
                pendingColorToken = 0;
                for (allocationBytesOrTokenIndex = 0, vertexBytesOrCommandIndex = 0; allocationBytesOrTokenIndex < encodedCommandCount; allocationBytesOrTokenIndex++) {
                    uvConsumeBytes(&packedCommandToken, &inputCursor, sizeof(u16));
                    if (vertexBytesOrCommandIndex) {
                    }
                    if (packedCommandToken & 0x8000) {
                        if (pendingColorToken == 0) {
                            pendingColorToken = packedCommandToken;
                        } else {
                            uvModelLoaderPackColorCommandWords((s32 *)&workPointerOrMatrixBytes[vertexBytesOrCommandIndex], pendingColorToken, packedCommandToken);
                            pendingColorToken = 0;
                            vertexBytesOrCommandIndex++;
                        }
                    } else {
                        if (pendingColorToken != 0) {
                            uvModelLoaderPackColorCommandWords((s32 *)&workPointerOrMatrixBytes[vertexBytesOrCommandIndex], pendingColorToken, 0);
                            pendingColorToken = 0;
                            vertexBytesOrCommandIndex++;
                        }
                        uvConsumeBytes(&vertexCommandByte, &inputCursor, 1);
                        partBytesOrVertexCountMinusOne = ((s32) (packedCommandToken & 0x6000) >> 0xA) | ((s32) (vertexCommandByte & 0xE0) >> 5);
                        gSPVertex(&workPointerOrMatrixBytes[vertexBytesOrCommandIndex], PHYSICAL_TO_K0(vertexCursor + ((packedCommandToken & 0x1FFF))),
                                  partBytesOrVertexCountMinusOne + 1, vertexCommandByte & 0x1F);
                        vertexBytesOrCommandIndex++;
                    }
                }
                vertexCursor = &model->vtxTable[consumedVertexCount];
                if (pendingColorToken != 0) {
                    uvModelLoaderPackColorCommandWords((s32 *)&workPointerOrMatrixBytes[vertexBytesOrCommandIndex], pendingColorToken, 0);
                    vertexBytesOrCommandIndex++;
                }
                gSPEndDisplayList(&workPointerOrMatrixBytes[vertexBytesOrCommandIndex]);
                vertexBytesOrCommandIndex++;
            }
            lods[lodIndex].unk20 = lodUsesFlag08000000;
        }
    }
    model->unk8 = (void*)recordCursor;
    geometryBytesOrMatrixBytes = model->unk6 * sizeof(Mtx4F);
    // RE_ORIGINAL_QUIRK: matching-source u64 cast; historical source intent unknown.
    uvConsumeBytes((void *) (u64) model->unk8, &inputCursor, geometryBytesOrMatrixBytes);

    return model;
}
#undef PHYSICAL_TO_K0
#line 63 "src/modules/uvmodelld_rom.c"

/* Unload each referenced UVTX and light state, then free the vertex allocation.
 * RE_UNKNOWN: ownership of optional/recursive model records is not established;
 * this routine does not prove that every model-owned allocation is released. */
#line 64 "src/modules/uvmodelld_rom.c"
void uvModelLoaderReleaseRenderResources(ParsedUVMD *modelArgument) {
    ParsedUVMD *model;
    ParsedUVMD_1 *part;
    s32 lodIndex;
    s32 stateIndex;
    s32 partIndex;
    uvGfxState *gfxState;
    uvModelLOD *lod;
    s32 textureIndex;

    model = modelArgument;
    for (partIndex = 0; partIndex < model->unk4; partIndex++) {
        part = &model->unk0[partIndex];
        for (lodIndex = 0; lodIndex < part->unk8; lodIndex++) {
            lod = &part->unk0[lodIndex];
            for (stateIndex = 0; stateIndex < lod->unk4; stateIndex++) {
                gfxState = &lod->stateTable[stateIndex];
                textureIndex = (gfxState->state & 0xFFF);
                if (textureIndex != 0xFFF) {
                    uvUnloadFile(0x55565458, textureIndex);
                }
                if (gfxState->unkC != -1) {
                    D_uvmodelld_rom_00400EE0->uvLightReleaseRecord(gfxState->unkC);
                }
            }
        }
    }

    _uvMemFree(model->vtxTable);
}
#line 65 "src/modules/uvmodelld_rom.c"
