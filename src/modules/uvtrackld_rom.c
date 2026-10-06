// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

void func_uvtrackld_rom_00400048(void);
void *uvParseUVTT(u8 *data);
void uvParseFreeUVTT(ParsedUVTT *parsedUVTT);
void __entrypoint_func_uvtrackld_rom_400000(UvTrackLd_Exports *exports);

s32 D_uvtrackld_rom_00400220[] = { 0x000C0000, __entrypoint_func_uvtrackld_rom_400000, 0, 0 };

void __entrypoint_func_uvtrackld_rom_400000(UvTrackLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVTT = uvParseUVTT;
    exports->func_uvtrackld_rom_00400048 = func_uvtrackld_rom_00400048;
    exports->uvParseFreeUVTT = uvParseFreeUVTT;
}

void func_uvtrackld_rom_00400048(void) {
}

void *uvParseUVTT(u8 *data) {
    u32 tag;
    u32 blockSize;
    void *blockData;
    void *var_s0;
    ParsedUVTT *parsedUVTT;
    u8 *sp48;
    s32 fileId;

    parsedUVTT = malloc8(sizeof(ParsedUVTT));
    parsedUVTT->unk0 = 0;
    parsedUVTT->unk4 = 0;
    fileId = uvFileReadHeader(data);
    while (tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1)) {
        switch (tag) {
            case 'PNTS':
                var_s0 = sp48 = blockData;
                uvConsumeBytes(&parsedUVTT->unk0, &sp48, sizeof(int));
                parsedUVTT->unk8 = malloc8(parsedUVTT->unk0 * 0x38);
                uvConsumeBytes(parsedUVTT->unk8, &sp48, parsedUVTT->unk0 * 0x38);
                _uvMemFree(var_s0);
                break;
            case 'LNKS':
                var_s0 = sp48 = blockData;
                uvConsumeBytes(&parsedUVTT->unk4, &sp48, sizeof(int));
                parsedUVTT->unkC = malloc8(parsedUVTT->unk4 * 8);
                uvConsumeBytes(parsedUVTT->unkC, &sp48, parsedUVTT->unk4 * 8);
                _uvMemFree(var_s0);
                break;
        }
    }
    uvFileFree(fileId);
    return parsedUVTT;
}

void uvParseFreeUVTT(ParsedUVTT *parsedUVTT) {
    _uvMemFree(parsedUVTT->unkC);
    _uvMemFree(parsedUVTT->unk8);
    _uvMemFree(parsedUVTT);
}
