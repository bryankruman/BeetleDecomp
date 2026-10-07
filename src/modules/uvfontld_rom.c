// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

extern ParsedUVFT* D_uvfontld_rom_004003DC;

void __entrypoint_func_uvfontld_rom_400000(UvFontLd_Exports* exports);
void uvFontLoaderCleanup(void);
ParsedUVFT* uvFontLoadResource(u8* data);
void uvFontFreeResource(ParsedUVFT* arg0);

void __entrypoint_func_uvfontld_rom_400000(UvFontLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvFontLoadResource = uvFontLoadResource;
    exports->uvFontLoaderCleanup = uvFontLoaderCleanup;
    exports->uvFontFreeResource = uvFontFreeResource;
}

#line 19 "src/modules/uvfontld_rom.c"
/* Original empty loader cleanup hook; resource release is performed
 * by the corresponding per-resource destructor. */
void uvFontLoaderCleanup(void) {

}
#line 22 "src/modules/uvfontld_rom.c"

#line 23 "src/modules/uvfontld_rom.c"
/* Parse STRG, FRMT, BITM and IMAG blocks, terminate the stored text, and
 * resolve bitmap image indices to allocated image pointers. Preserve the
 * original shared result pointer and valid-asset block/count/index contracts. */
ParsedUVFT* uvFontLoadResource(u8* data) {
    s32 fileId;
    u32 blockBytes;
    s32* blockData;
    s32 i;
    u32 tag;
    s32 bitmapCount;
    s32 formatWords[2];

    D_uvfontld_rom_004003DC = (ParsedUVFT*)_uvMemAllocAlign8(sizeof(ParsedUVFT));
    D_uvfontld_rom_004003DC->unk4 = 0;
    fileId = uvFileReadHeader(data);
    while ((tag = uvFileReadBlock(fileId, &blockBytes, (void**)&blockData, 1)) != NULL) {
        switch (tag) {
        case 'STRG':
            D_uvfontld_rom_004003DC->str = _uvMemAllocAlign8(blockBytes + 1);
            _uvMediaCopy((void*)D_uvfontld_rom_004003DC->str, blockData, blockBytes);
            D_uvfontld_rom_004003DC->str[blockBytes] = '\0';
            _uvMemFree(blockData);
            break;
        case 'FRMT':
            _uvMediaCopy(formatWords, blockData, blockBytes);
            D_uvfontld_rom_004003DC->bmfmt = formatWords[0];
            D_uvfontld_rom_004003DC->bmsiz = formatWords[1];
            _uvMemFree(blockData);
            break;
        case 'BITM':
            bitmapCount = blockBytes / sizeof(Bitmap);
            D_uvfontld_rom_004003DC->bitmap = (void*)blockData;
            break;
        case 'IMAG':
            D_uvfontld_rom_004003DC->imag[D_uvfontld_rom_004003DC->unk4] = _uvMemAlloc(blockBytes, 8U);
            _uvMediaCopy(D_uvfontld_rom_004003DC->imag[D_uvfontld_rom_004003DC->unk4], blockData, blockBytes);
            _uvMemFree(blockData);
            D_uvfontld_rom_004003DC->unk4++;
            break;
        default:

            break;
        }
    }
    uvFileFree(fileId);
    D_uvfontld_rom_004003DC->str[bitmapCount] = '\0';

    // update indexes to pointers allocated above
    for (i = 0; i < bitmapCount; i++) {
        D_uvfontld_rom_004003DC->bitmap[i].buf = D_uvfontld_rom_004003DC->imag[(u32)D_uvfontld_rom_004003DC->bitmap[i].buf];
    }
    return D_uvfontld_rom_004003DC;
}
#line 73 "src/modules/uvfontld_rom.c"

#line 74 "src/modules/uvfontld_rom.c"
/* Free each font image, the string, bitmap table and font object in
 * original order. The resource must be a valid completed load. */
void uvFontFreeResource(ParsedUVFT* font) {
    ParsedUVFT* resource = font;
    s32 i;

    for (i = 0; i < resource->unk4; i++) {
        _uvMemFree(resource->imag[i]);
    }

    _uvMemFree(resource->str);
    _uvMemFree(resource->bitmap);
    _uvMemFree(resource);
}
#line 86 "src/modules/uvfontld_rom.c"
