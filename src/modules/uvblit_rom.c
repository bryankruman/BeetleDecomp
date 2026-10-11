// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

ParsedUVBT* _uvParseUVBT(u8 *); /* extern */
ParsedUVBT* uvParseBlit(u8 *data);
void uvBlitStub(void);
void uvFreeBlit(ParsedUVBT *uvbt);

/* Update the allocation pointer, then publish parse, stub and free callbacks
 * in original slot order. RE_UNKNOWN: asset ownership, export-table lifetime and
 * repeated initialization require module consumers. */
#line 10 "src/modules/uvblit_rom.c"
void __entrypoint_func_uvblit_rom_400000(UvBlit_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseBlit = uvParseBlit;
    exports->uvBlitStub = uvBlitStub;
    exports->uvFreeBlit = uvFreeBlit;
}
#line 16 "src/modules/uvblit_rom.c"

/* Return without performing an operation.
 * RE_UNKNOWN: the historical callback purpose and any intended future work are unresolved. */
#line 17 "src/modules/uvblit_rom.c"
void uvBlitStub(void) {
}
#line 19 "src/modules/uvblit_rom.c"

/*
 * Visit bitmap-file blocks with decode flag 1. For each COMM block, call the
 * existing bitmap parser and free the block; release the file handle at end.
 * RE_ORIGINAL_QUIRK: The result local is not initialized. A file without COMM
 * returns that uninitialized value; repeated COMM blocks replace prior results
 * without releasing them. Preserve this behavior rather than inserting NULL.
 * RE_UNKNOWN: Required chunk presence, input extents and ignored-block/result
 * ownership must be established by callers and the file provider.
 */
#line 20 "src/modules/uvblit_rom.c"
ParsedUVBT* uvParseBlit(u8 *fileData) {
    s32 fileId;
    u32 tag;
    u32 blockSize;
    void *blockData;
    void* commBlock;
    ParsedUVBT* bitmap;

    fileId = uvFileReadHeader(fileData);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                commBlock = blockData;
                bitmap = _uvParseUVBT(commBlock);
                _uvMemFree(commBlock);
                break;
            default:
                break;
        }

        tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    }
    uvFileFree(fileId);
    return bitmap;
}

#line 47 "src/modules/uvblit_rom.c"

#line 48 "src/modules/uvblit_rom.c"

ParsedUVBT *_uvParseUVBT(u8 *inputCursor) {
    s32 bitmapDataAddress; // pointer?
    u16 bitmapFormat;
    u16 bitDepth;
    u16 imageWidth;
    u16 storedImageWidth; /* Offset 0x06: all 100 original assets store rounded tile-column width. RE_UNKNOWN: modified-input validation and historical format contract. */
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
    storedImageWidth = headerWordScratch;
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

    temp = (storedImageWidth * imageHeight * bitDepth) / 8;
    parsedBitmap->buf = _uvMemAlloc(temp, 8);
    uvConsumeBytes((void *) parsedBitmap->buf, &inputCursor, temp);

    bitmapColumns = imageWidth / bitmapWidth; /* Original assets have nonzero divisors; RE_ORIGINAL_QUIRK: these divisions have no local input checks. */
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
#line 149 "src/modules/uvblit_rom.c"
#line 148 "src/modules/uvblit_rom.c"

/*
 * Free the bitmap pixel buffer, bitmap-descriptor array and root record in
 * that order. No pointer, count or shared-buffer checks are performed.
 * RE_UNKNOWN: Complete construction and exclusive ownership of all three
 * allocations require the parser and callers; repeated cleanup is unchecked.
 */
#line 149 "src/modules/uvblit_rom.c"
void uvFreeBlit(ParsedUVBT *bitmapRecord) {
    _uvMemFree(bitmapRecord->buf);
    _uvMemFree(bitmapRecord->bitmap);
    _uvMemFree(bitmapRecord);
}
