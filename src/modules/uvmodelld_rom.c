// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

extern UvLights_Exports *D_uvmodelld_rom_00400EE0;
extern UvFMtx_Rom_Exports *D_uvmodelld_rom_00400EE4;
ParsedUVMD *func_uvmodelld_rom_00400258(void *); /* extern */

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/__entrypoint_func_uvmodelld_rom_400000.s")

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

/* Original COMM parser: read model totals and an optional 60-byte record,
 * allocate the combined vertex/state/command/part/LOD/matrix storage, then parse
 * the nested records. Preserve signed per-state vertex counts, pointer/count
 * reloads, paired color tokens and the final display-list terminators. The
 * original LGHT slot 0x28 consumes only the three supplied color words.
 * RE_ORIGINAL_QUIRK: the complete 36-byte stack header is copied before its
 * runtime table pointers are assigned. Some copied words and alignment bytes
 * have no preceding assignment here; the optional record also receives only
 * a byte at offset 0x28 before its next word at 0x2C. No zero-filled storage or
 * reachable use of the untouched bytes is established.
 * RE_UNKNOWN: valid header/per-part/per-LOD count relationships, command and
 * vertex capacities, block length and allocation-failure guarantees. Establish
 * the UVMD asset format and original caller domain before changing bounds or
 * allocation arithmetic. Optional-field meanings/units and recursive
 * UVMD/UVPX/UVTX/light ownership and cleanup remain unresolved; trace original
 * consumers and resource-release paths.
 * RE_UNKNOWN: exact source pointer lifetimes and permitted aliasing needed to
 * recover native field-pointer walks and floating load/store timing. The draft
 * is parked at 2592 bytes versus native 2784, with different full relocation
 * offsets. Preserve the original assembly until those contracts and complete
 * instruction/relocation identity are proved; matching helper counts alone
 * do not establish equivalent effects. */
#line 62 "src/modules/uvmodelld_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/func_uvmodelld_rom_00400258.s")
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
