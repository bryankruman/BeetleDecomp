// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

typedef struct UnkUvEnvLd_Exports_s {
    char pad0[4];
    void (*unk4)(f32, f32, s32, s32);
} UnkUvEnvLd_Exports;

void __entrypoint_func_uvenvld_rom_400000(UvEnvLd_Exports *exports);
void func_uvenvld_rom_00400048(void);
ParsedUVEN *uvParseUVEN(u8 *data);
ParsedUVEN *_uvParseUVEN(void *arg0);
void uvEnvLdCleanup(ParsedUVEN *parsedUvEnv);

// .data
s32 D_uvenvld_rom_00400320[] = {0x000C0000, __entrypoint_func_uvenvld_rom_400000, 0, 0};

void __entrypoint_func_uvenvld_rom_400000(UvEnvLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVEN = uvParseUVEN;
    exports->func_uvenvld_rom_00400048 = func_uvenvld_rom_00400048;
    exports->uvEnvLdCleanup = uvEnvLdCleanup;
}

// stub
void func_uvenvld_rom_00400048(void) {
}

ParsedUVEN *uvParseUVEN(u8 *data) {
    s32 fileId;
    ParsedUVEN *parsedUvEnv;
    u32 sizeOut;
    void *blockData;
    u32 tag;
    void *dataPtr;

    parsedUvEnv = NULL;
    fileId = uvFileReadHeader(data);
    tag = uvFileReadBlock(fileId, &sizeOut, &blockData, FILE_NOT_COMPRESSED);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                dataPtr = blockData;
                parsedUvEnv = _uvParseUVEN(dataPtr);
                _uvMemFree(dataPtr);
                break;
            default:
                break;
        }
        tag = uvFileReadBlock(fileId, &sizeOut, &blockData, FILE_NOT_COMPRESSED);
    }
    uvFileFree(fileId);
    return parsedUvEnv;
}

// uvParseUVEN internal
ParsedUVEN *_uvParseUVEN(void *data) {
    s32 i;
    UnkUvEnvLd_Exports *uvEnvLd;
    ParsedUVEN *parsedUvEnv;

    parsedUvEnv = malloc8(sizeof(ParsedUVEN));
    uvConsumeBytes(parsedUvEnv, (u8 **) &data, sizeof(ParsedUVEN));
    parsedUvEnv->unk38 = 0;
    parsedUvEnv->unk5C = 0;
    if (parsedUvEnv->modelCount > 0) {
        parsedUvEnv->modelTable = malloc8(parsedUvEnv->modelCount * sizeof(uvEnvModel));
    } else {
        parsedUvEnv->modelTable = NULL;
    }
    for (i = 0; i < parsedUvEnv->modelCount; i++) {
        uvConsumeBytes(&parsedUvEnv->modelTable[i].modelId, (u8 **) &data, sizeof(u16));
        uvLoadFile('UVMD', parsedUvEnv->modelTable[i].modelId);
        uvConsumeBytes(&parsedUvEnv->modelTable[i].flag, (u8 **) &data, sizeof(u8));
    }
    if (parsedUvEnv->unk1D == 0) {
        parsedUvEnv->unk44 = NULL;
    } else {
        uvEnvLd = uvLoadModule('UENV');
        parsedUvEnv->unk44 = _uvMemAlloc(0x200, 8);
        //! @bug: Wrong export function
        uvEnvLd->unk4(parsedUvEnv->unk3C, parsedUvEnv->unk40, parsedUvEnv->unk44, parsedUvEnv);
        uvUnloadModule('UENV');
    }
    return parsedUvEnv;
}

void uvEnvLdCleanup(ParsedUVEN *parsedUvEnv) {
    void *temp_a1;
    s32 i;
    s32 var_s1;
    ParsedUVEN *uvEnv = parsedUvEnv;

    temp_a1 = uvEnv->unk44;
    if (temp_a1 != NULL) {
        _uvMemFree(temp_a1);
    }
    if (uvEnv->modelCount != 0) {
        for (i = 0; i < uvEnv->modelCount; i++) {
            uvUnloadFile('UVMD', uvEnv->modelTable[i].modelId);
        }
        _uvMemFree(uvEnv->modelTable);
    }
    _uvMemFree(uvEnv);
}
