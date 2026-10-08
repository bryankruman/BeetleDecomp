// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

ParsedUVBT* _uvParseUVBT(u8 *); /* extern */
ParsedUVBT* uvParseBlit(u8 *data);
void uvBlitStub(void);
void uvFreeBlit(ParsedUVBT *uvbt);

void __entrypoint_func_uvblit_rom_400000(UvBlit_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseBlit = uvParseBlit;
    exports->uvBlitStub = uvBlitStub;
    exports->uvFreeBlit = uvFreeBlit;
}

void uvBlitStub(void) {
}

ParsedUVBT* uvParseBlit(u8 *ptr) {
    s32 fileId;
    u32 tag;
    u32 size;
    void *data;
    void* dataPtr;
    ParsedUVBT* parsedBlit;

    fileId = uvFileReadHeader(ptr);
    tag = uvFileReadBlock(fileId, &size, &data, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                dataPtr = data;
                parsedBlit = _uvParseUVBT(dataPtr);
                _uvMemFree(dataPtr);
                break;
            default:
                break;
        }

        tag = uvFileReadBlock(fileId, &size, &data, 1);
    }
    uvFileFree(fileId);
    return parsedBlit;
}

#line 47 "src/modules/uvblit_rom.c"

ParsedUVBT *_uvParseUVBT(u8 *inputCursor) {
    s32 bitmapDataAddress; // pointer?
    u16 bitmapFormat;
    u16 bitDepth;
    u16 imageWidth;
    u16 sp94;
    u16 imageHeight;
    u16 bitmapWidth;
    u16 bitmapHeight;
    s8 partialLastRow; // var_s3
    s8 partialLastColumn; // var_s4
    s32 bitmapColumn;
    u64 headerWordScratch;
    s32 bitmapRow;
    ParsedUVBT *parsedBitmap;
    s32 bitmapColumns;
    s32 bitmapRows;
    Bitmap *bitmap;
    s32 temp;

    partialLastRow = 0;
    partialLastColumn = 0;

    _uvMediaCopy(&headerWordScratch, inputCursor, 4);
    headerWordScratch >>= 32;
    bitmapFormat = (headerWordScratch & 0xFFFF0000) >> 16;
    bitDepth = headerWordScratch;
    inputCursor += 4;

    _uvMediaCopy(&headerWordScratch, inputCursor, 4);
    headerWordScratch >>= 32;
    imageWidth = (headerWordScratch & 0xFFFF0000) >> 16;
    sp94 = headerWordScratch;
    inputCursor += 4;

    _uvMediaCopy(&headerWordScratch, inputCursor, 4);
    headerWordScratch >>= 32;
    imageHeight = (headerWordScratch & 0xFFFF0000) >> 16;
    bitmapWidth = headerWordScratch;
    inputCursor += 4;

    _uvMediaCopy(&headerWordScratch, inputCursor, 4);
    headerWordScratch >>= 32;
    temp = ((headerWordScratch & 0xFFFF0000) >> 16) & 0xFFFF;
    bitmapHeight = temp & 0xFFFF;
    inputCursor += 2;
    if (imageHeight < bitmapHeight) {
        bitmapHeight = imageHeight;
    }

    parsedBitmap = _uvMemAllocAlign8(sizeof(ParsedUVBT));
    parsedBitmap->bmfmt = bitmapFormat;
    parsedBitmap->bitdepth = bitDepth;
    parsedBitmap->width = imageWidth;
    parsedBitmap->height = imageHeight;
    parsedBitmap->unkA = bitmapWidth;
    parsedBitmap->texelHeight = bitmapHeight;

    temp = (sp94 * imageHeight * bitDepth) / 8;
    parsedBitmap->buf = _uvMemAlloc(temp, 8);
    uvConsumeBytes((void *) parsedBitmap->buf, &inputCursor, temp);

    bitmapColumns = imageWidth / bitmapWidth;
    bitmapRows = imageHeight / bitmapHeight;
    if (imageWidth % bitmapWidth) {
        bitmapColumns++;
        partialLastColumn = 1;
    }
    if (imageHeight % bitmapHeight) {
        bitmapRows++;
        partialLastRow = 1;
    }
    parsedBitmap->nbitmaps = bitmapColumns * bitmapRows;
    parsedBitmap->bitmap = _uvMemAllocAlign8(parsedBitmap->nbitmaps * sizeof(Bitmap));

    bitmapDataAddress = parsedBitmap->buf;
    for (bitmapRow = 0; bitmapRow < bitmapRows; bitmapRow++) {
        for (bitmapColumn = 0; bitmapColumn < bitmapColumns; bitmapColumn++) {
            bitmap = &parsedBitmap->bitmap[bitmapColumn + bitmapRow * bitmapColumns];
            temp = bitmapRow + 1;
            if (partialLastRow && bitmapRows == temp) {
                bitmap->actualHeight = imageHeight % bitmapHeight;
            } else {
                bitmap->actualHeight = bitmapHeight;
            }
            temp = bitmapColumn + 1;
            if (partialLastColumn && bitmapColumns == temp) {
                bitmap->width = imageWidth - (bitmapWidth * (bitmapColumns - 1));
            } else {
                bitmap->width = bitmapWidth;
            }
            bitmap->LUToffset = 0;
            bitmap->t = bitmap->LUToffset;
            bitmap->s = bitmap->LUToffset;
            bitmap->width_img = bitmapWidth;
            bitmap->buf = bitmapDataAddress;
            bitmapDataAddress += (bitmap->actualHeight * bitmapWidth * bitDepth) / 8;
        }
    }
    return parsedBitmap;
}
#line 148 "src/modules/uvblit_rom.c"

void uvFreeBlit(ParsedUVBT *uvbt) {
    _uvMemFree(uvbt->buf);
    _uvMemFree(uvbt->bitmap);
    _uvMemFree(uvbt);
}
