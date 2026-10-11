// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void __entrypoint_func_uvdsetld_rom_400000(UvDSetLd_Rom_Exports* exports);
void uvDataSetVisitReferences(UnkStruct_uvdsetld_rom_00400050* arg0, void (*routine)(s32, s32));
void uvDataSetLoaderCleanup(void);
void uvDataSetVisitReferences(UnkStruct_uvdsetld_rom_00400050* arg0, void (*routine)(s32, s32));
void uvDataSetVisitReferences(UnkStruct_uvdsetld_rom_00400050* arg0, void (*routine)(s32, s32));
void uvDataSetVisitFileBlocks(u8* filePtr, void (*routine)(s32, s32));
u8 *uvDataSetLoadReferences(u8 *arg0);
void uvDataSetUnloadReferences(void* arg0);

/* Publish dataset reference-load, module-cleanup and reference-unload exports
 * after the allocation hook. This entrypoint loads no referenced dataset itself.
 * RE_UNKNOWN: writable export storage, referenced-resource ownership and repeat
 * initialization belong to the loader and later resource operations. */
#line 14 "src/modules/uvdsetld_rom.c"
void __entrypoint_func_uvdsetld_rom_400000(UvDSetLd_Rom_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvDataSetLoadReferences = uvDataSetLoadReferences;
    exports->uvDataSetLoaderCleanup = uvDataSetLoaderCleanup;
    exports->uvDataSetUnloadReferences = uvDataSetUnloadReferences;
}
#line 20 "src/modules/uvdsetld_rom.c"

#line 21 "src/modules/uvdsetld_rom.c"
/* Original empty loader cleanup hook; resource release is performed
 * by the corresponding per-resource destructor. */
void uvDataSetLoaderCleanup(void) {

}
#line 24 "src/modules/uvdsetld_rom.c"

#line 25 "src/modules/uvdsetld_rom.c"
/* Visit zero-terminated tag/count/file-ID groups and temporarily load
 * non-UVMO modules around callbacks. RE_UNKNOWN: stream extent/termination
 * and callback/dependency lifetime need original assets, loaders and callers. */
void uvDataSetVisitReferences(UnkStruct_uvdsetld_rom_00400050* data, void (*routine)(s32, s32)) {
    s32 i;
    s32 tag;
    u16 fileId;
    u16 count;
    u16* cursor;

    tag = data->tagByte4 | (data->tagByte1 << 0x18) | (data->tagByte2 << 0x10) | (data->tagByte3 << 8);
    cursor = (u16*)&data->size;

    while (tag != 0) {
        if (tag != 'UVMO') {
            uvLoadModule(tag);
        }

        count = *cursor;
        i = 0;
        cursor++;

        while (i < count) {
            fileId = *cursor;
            cursor++;
            routine(tag, fileId);
            i++;
        }

        if (tag != 'UVMO') {
            uvUnloadModule(tag);
        }

        tag = ((UnkStruct_uvdsetld_rom_00400050 *)cursor)->tagByte4 |
            (((UnkStruct_uvdsetld_rom_00400050 *)cursor)->tagByte1 << 0x18) |
            (((UnkStruct_uvdsetld_rom_00400050 *)cursor)->tagByte2 << 0x10) |
            (((UnkStruct_uvdsetld_rom_00400050 *)cursor)->tagByte3 << 0x8);

        cursor += 2;
    }
}
#line 63 "src/modules/uvdsetld_rom.c"

#line 64 "src/modules/uvdsetld_rom.c"
/* Read each COMM block, visit its resource references, free that block
 * and finally release the FORM reader. Unknown tags retain original handling. */
void uvDataSetVisitFileBlocks(u8* filePtr, void (*routine)(s32, s32)) {
    s32 fileId;
    u32 tag;
    u32 size;
    void* data;
    void* blockStart;

    fileId = uvFileReadHeader(filePtr);
    tag = uvFileReadBlock(fileId, &size, &data, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                blockStart = data;
                uvDataSetVisitReferences((UnkStruct_uvdsetld_rom_00400050* ) blockStart, routine);
                _uvMemFree(blockStart);
                break;
            default:
                break;
        }

        tag = uvFileReadBlock(fileId, &size, &data, 1);
    }
    uvFileFree(fileId);
}
#line 88 "src/modules/uvdsetld_rom.c"

#line 89 "src/modules/uvdsetld_rom.c"
/* Load each resource referenced by the data-set file and return the
 * original file pointer. Individual references retain their loader ownership. */
u8 *uvDataSetLoadReferences(u8 *data) {
    uvDataSetVisitFileBlocks(data, (void (*)(s32, s32)) uvLoadFile);
    return data;
}
#line 93 "src/modules/uvdsetld_rom.c"

#line 94 "src/modules/uvdsetld_rom.c"
/* Unload every resource referenced by the data-set file through the
 * same original block visitor. */
void uvDataSetUnloadReferences(void* data) {
    uvDataSetVisitFileBlocks(data, uvUnloadFile);
}
#line 97 "src/modules/uvdsetld_rom.c"
