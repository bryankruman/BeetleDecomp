// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

extern UvFMtx_Rom_Exports *D_uvmodelld_rom_00400EE0;
extern UvLights_Exports *D_uvmodelld_rom_00400EE4;
ParsedUVMD *func_uvmodelld_rom_00400258(void *); /* extern */

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/__entrypoint_func_uvmodelld_rom_400000.s")

void func_uvmodelld_rom_0040006C(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('LGHT');
}

// uvParseUVMD
ParsedUVMD *func_uvmodelld_rom_0040009C(u8 *arg0) {
    s32 fileId;
    s32 parsedUvModel;
    u32 blockSize;
    void *blockData;
    u32 tag;
    s32 ptr;

    parsedUvModel = 0;
    fileId = uvFileReadHeader(arg0);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                ptr = blockData;
                parsedUvModel = func_uvmodelld_rom_00400258(ptr);
                _uvMemFree(ptr);
                break;
            default:
                break;
        }

        tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    }
    uvFileFree(fileId);
    return parsedUvModel;
}

void func_uvmodelld_rom_00400158(s32 *arg0, u16 arg1, u16 arg2) {
    // clang-format off
    if (arg2) { \
        arg0[0] = (((((arg1 & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10) \
                  | (((((arg1 & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((arg1 & 0x1F) * 2) & 0xFF) \
                  | 0x06000000; \
        arg0[1] = ((((((arg2 & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10) \
                   | (((((arg2 & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((arg2 & 0x1F) * 2) & 0xFF)); \
    } else {
        arg0[0] = (((((arg1 & 0x7C00) >> 0xA) * 2) & 0xFF) << 0x10)
                  | (((((arg1 & 0x3E0) >> 5) * 2) & 0xFF) << 8) | (((arg1 & 0x1F) * 2) & 0xFF)
                  | 0x05000000;
        arg0[1] = 0;
    }
    // clang-format on
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/func_uvmodelld_rom_00400258.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvmodelld_rom/func_uvmodelld_rom_00400D38.s")
