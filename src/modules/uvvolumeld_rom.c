// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void uvVolumeLoaderCleanup(void);
void* uvVolumeLoadResource(u8* arg0);
void uvVolumeFreeResource(UnkStruct_UvVolumeLd_rom_00400050 *arg0);

void __entrypoint_func_uvvolumeld_rom_400000(UvVolumeLd_Rom_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvVolumeLoadResource = uvVolumeLoadResource;
    exports->uvVolumeLoaderCleanup = uvVolumeLoaderCleanup;
    exports->uvVolumeFreeResource = uvVolumeFreeResource;
}

#line 16 "src/modules/uvvolumeld_rom.c"
/* Original empty loader cleanup hook; resource release is performed
 * by the corresponding per-resource destructor. */
void uvVolumeLoaderCleanup(void) {

}
#line 19 "src/modules/uvvolumeld_rom.c"

#line 20 "src/modules/uvvolumeld_rom.c"
/* Parse VOBJ blocks into the original volume/plane arrays and bounding
 * values. Preserve allocation order and the valid-asset count/size contract. */
void* uvVolumeLoadResource(u8* data) {
    s32 fileId;
    u32 blockBytes;
    void* blockData;
    UnkStruct_UvVolumeLd_rom_00400050_inner* volume;
    UnkStruct_UvVolumeLd_rom_00400050* resource;
    u32 tag;
    void* cursor;
    void* blockStart;
    s32 i; // var_s2

    resource = _uvMemAllocAlign8(8);
    resource->unk0 = 0;
    resource->unk4 = NULL;
    fileId = uvFileReadHeader(data);
    while ((tag = uvFileReadBlock(fileId, &blockBytes, &blockData, 1)) != 0) {
        switch (tag) {
        case 'VOBJ':
            cursor = blockStart = blockData;
            uvConsumeBytes(&resource->unk0, (u8** ) &cursor, sizeof(resource->unk0));
            resource->unk4 = _uvMemAllocAlign8(resource->unk0 * sizeof(resource->unk4[0]));

            for (i = 0; i < resource->unk0; i++) {
                volume = &resource->unk4[i];
                uvConsumeBytes(&volume->unk0, (u8** ) &cursor, sizeof(volume->unk0));
                volume->unk4 = _uvMemAllocAlign8(volume->unk0 * sizeof(volume->unk4[0]));
                uvConsumeBytes(volume->unk4, (u8** ) &cursor, volume->unk0 * sizeof(volume->unk4[0]));
                uvConsumeBytes(&volume->unk8, (u8** ) &cursor, sizeof(volume->unk8));
                uvConsumeBytes(&volume->unk14, (u8** ) &cursor, sizeof(volume->unk14));
            }

            _uvMemFree(blockStart);
            break;
        default:
            break;
        }
    }
    uvFileFree(fileId);
    return resource;
}
#line 60 "src/modules/uvvolumeld_rom.c"

#line 61 "src/modules/uvvolumeld_rom.c"
/* Free every volume plane array, the volume table and resource in
 * original order. The caller supplies a valid loaded resource. */
void uvVolumeFreeResource(UnkStruct_UvVolumeLd_rom_00400050* resource) {
    s32 index;

    for (index = 0; index < resource->unk0; index++) {
        _uvMemFree(resource->unk4[index].unk4);
    }
    _uvMemFree(resource->unk4);
    _uvMemFree(resource);
}
#line 70 "src/modules/uvvolumeld_rom.c"
