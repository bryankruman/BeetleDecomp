// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

extern UvFMtx_Rom_Exports *D_uvmodelld_rom_00400EE0;
extern UvLights_Exports *D_uvmodelld_rom_00400EE4;
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
 * no common block was found, after releasing the file reader. */
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/func_uvmodelld_rom_00400258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/func_uvmodelld_rom_00400D38.s")
