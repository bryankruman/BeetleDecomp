// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

ParsedUVTR* func_uvterrald_rom_00400120(void*);             /* extern */

extern UvFMtx_Rom_Exports* D_uvterrald_rom_00400A90;

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterrald_rom/__entrypoint_func_uvterrald_rom_400000.s")

void func_uvterrald_rom_0040006C(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('TERR');
}

// parseUVTR
s32 func_uvterrald_rom_0040009C(u8* arg0) {
    s32 fileId;
    u32 size;
    void* data;
    void* uvtrData;
    ParsedUVTR* uvtr;

    uvtr = 0;
    fileId = uvFileReadHeader(arg0);
    if (uvFileSearchTag(fileId, &size, &data, 'COMM', 0) != 0) {
        uvtrData = malloc8(size);
        _uvMediaCopy(uvtrData, data, size);
        uvtr = func_uvterrald_rom_00400120(uvtrData);
        _uvMemFree(uvtrData);
    }
    uvFileFree(fileId);
    return uvtr;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvterrald_rom/func_uvterrald_rom_00400120.s")

void func_uvterrald_rom_004008C8(ParsedUVTR *arg0) {
    s32 temp_lo;
    s32 j;
    s32 i;
    s32 temp_s1;
    s32 temp_s4;
    void *temp_a0;
    uvUnkTileStruct *temp_s2;
    ParsedUVCT *temp_v0;
    uvUnkTileStruct *temp_v0_2;
    ParsedUVTR* s6 = arg0;

    temp_lo = s6->unk18 * s6->unk19;
    if (s6->unk2C != 0) {
        i = 0;
        if (temp_lo > 0) {
            do {
                temp_v0 = s6->unk28[i].unk40;
                temp_s2 = s6->unk28 + i;
                if (temp_v0 == NULL) {
                    continue;
                }

                temp_s4 = temp_v0->unk14;
                if (temp_s2 == NULL) {
                    continue;
                }

                j = 0;
                temp_s1 = temp_v0->unkC;
                if (temp_s1 > 0) {
                    do {
                        Unk80225FBC_0x28* v0 = &temp_s2->unk40->unk8[j];
                        _uvMemFree(v0->unk38);
                    } while (++j != temp_s1);
                }

                j = 0;
                if (temp_s4 > 0) {
                    do {
                        struct UnkSobjDraw* v0 = &temp_s2->unk40->unk10[j];
                        _uvMemFree(v0->unk48);
                    } while (++j != temp_s4);
                }
            } while (++i != temp_lo);
        }
    }

    i = 0;
    if (temp_lo > 0) {
        do {
            temp_v0_2 = &s6->unk28[i];
            if (temp_v0_2->unk40 != 0) {
                // FAKE
                if (1) {
                    uvUnloadFile('UVCT', temp_v0_2->unk44);
                }
            }
        } while (++i != temp_lo);
    }

    _uvMemFree(s6->unk28);
    _uvMemFree(arg0);
}
