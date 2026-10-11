// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

ParsedUVTR* func_uvterrald_rom_00400120(void*);             /* extern */

extern UvFMtx_Rom_Exports* D_uvterrald_rom_00400A90;

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterrald_rom/__entrypoint_func_uvterrald_rom_400000.s")

#line 12 "src/modules/uvterrald_rom.c"
/* Unload FMTX and TERR dependencies in their original order. */
void uvTerrainLoaderCleanup(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('TERR');
}
#line 16 "src/modules/uvterrald_rom.c"

// parseUVTR
#line 18 "src/modules/uvterrald_rom.c"
/* Locate the terrain COMM block, copy it into temporary aligned
 * storage, parse the copy and release both the copy and file reader.
 * Return the parsed terrain pointer through the existing word ABI. */
s32 uvTerraLoaderParseCommonBlock(u8* fileData) {
    s32 fileId;
    u32 size;
    void* data;
    void* commonBlock;
    ParsedUVTR* terrain;

    terrain = 0;
    fileId = uvFileReadHeader(fileData);
    if (uvFileSearchTag(fileId, &size, &data, 'COMM', 0) != 0) {
        commonBlock = malloc8(size);
        _uvMediaCopy(commonBlock, data, size);
        terrain = func_uvterrald_rom_00400120(commonBlock);
        _uvMemFree(commonBlock);
    }
    uvFileFree(fileId);
    return terrain;
}
#line 36 "src/modules/uvterrald_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterrald_rom/func_uvterrald_rom_00400120.s")

/*
 * Use the two byte-sized grid dimensions to visit the terrain tile array.
 * When field 0x2C is nonzero, free each non-NULL tile configuration's two
 * child-allocation lists using its halfword counts. In a separate pass unload
 * UVCT for every non-NULL tile configuration, then free the grid and root.
 * RE_ORIGINAL_QUIRK: Preserve the redundant tile-pointer NULL test, repeated
 * configuration loads, do/while continue increments and inherited if(1) shim.
 * The two child-list passes are skipped entirely when field 0x2C is zero.
 * RE_UNKNOWN: Grid/count extents, shared child allocations, UVCT reference
 * ownership and repeated cleanup are unchecked caller/loader obligations.
 */
#line 39 "src/modules/uvterrald_rom.c"
void func_uvterrald_rom_004008C8(ParsedUVTR *terrainRecord) {
    s32 tileCount;
    s32 j;
    s32 i;
    s32 firstChildCount;
    s32 secondChildCount;
    void *temp_a0;
    uvUnkTileStruct *tile;
    ParsedUVCT *tileConfig;
    uvUnkTileStruct *tileToUnload;
    ParsedUVTR* terrain = terrainRecord;

    tileCount = terrain->unk18 * terrain->unk19;
    if (terrain->unk2C != 0) {
        i = 0;
        if (tileCount > 0) {
            do {
                tileConfig = terrain->unk28[i].unk40;
                tile = terrain->unk28 + i;
                if (tileConfig == NULL) {
                    continue;
                }

                secondChildCount = tileConfig->unk14;
                if (tile == NULL) {
                    continue;
                }

                j = 0;
                firstChildCount = tileConfig->unkC;
                if (firstChildCount > 0) {
                    do {
                        Unk80225FBC_0x28* v0 = &tile->unk40->unk8[j];
                        _uvMemFree(v0->unk38);
                    } while (++j != firstChildCount);
                }

                j = 0;
                if (secondChildCount > 0) {
                    do {
                        struct UnkSobjDraw* v0 = &tile->unk40->unk10[j];
                        _uvMemFree(v0->unk48);
                    } while (++j != secondChildCount);
                }
            } while (++i != tileCount);
        }
    }

    i = 0;
    if (tileCount > 0) {
        do {
            tileToUnload = &terrain->unk28[i];
            if (tileToUnload->unk40 != 0) {
                // FAKE
                if (1) {
                    uvUnloadFile('UVCT', tileToUnload->unk44);
                }
            }
        } while (++i != tileCount);
    }

    _uvMemFree(terrain->unk28);
    _uvMemFree(terrainRecord);
}
