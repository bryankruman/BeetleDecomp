// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

static UvLights_Exports *sLightsExport;

void __entrypoint_func_uvcontourld_rom_400000(UvContourLd_Exports *exports);
void uvContourLoaderCleanup(void);
ParsedUVCT *uvParseUVCT(u8 *arg0);
void uvContourWritePackedTriangles(Gfx *gdl, u16 arg1, u16 arg2);
ParsedUVCT *_uvParseUVCT(u8 *arg0);
void uvContourLoaderReleaseParsedContour(ParsedUVCT *uvct);

s32 D_uvcontourld_rom_00400C30[] = {0x000C0000, __entrypoint_func_uvcontourld_rom_400000, 0, 0};

void __entrypoint_func_uvcontourld_rom_400000(UvContourLd_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseUVCT = uvParseUVCT;
    exports->uvContourLoaderCleanup = uvContourLoaderCleanup;
    exports->uvContourLoaderReleaseParsedContour = uvContourLoaderReleaseParsedContour;
#ifdef __sgi
#line 18
#endif
    sLightsExport = uvLoadModule('LGHT');
}

#line 22 "src/modules/uvcontourld_rom.c"
/* Unload the contour loader's LGHT dependency.
 * RE_UNKNOWN: initialized module lifetime remains a caller contract. */
void uvContourLoaderCleanup(void) {
    uvUnloadModule('LGHT');
}
#line 25 "src/modules/uvcontourld_rom.c"

ParsedUVCT *uvParseUVCT(u8 *arg0) {
    s32 fileId;
    ParsedUVCT *uvct;
    u32 blockSize;
    void *blockData;
    u32 tag;
    u8 *dataPtr;

    uvct = NULL;
    fileId = uvFileReadHeader(arg0);
    tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    while (tag != 0) {
        switch (tag) {
            case 'COMM':
                dataPtr = blockData;
                uvct = _uvParseUVCT(dataPtr);
                _uvMemFree(dataPtr);
                break;
            default:
                break;
        }
        tag = uvFileReadBlock(fileId, &blockSize, &blockData, 1);
    }
    uvFileFree(fileId);
    return uvct;
}

#line 53 "src/modules/uvcontourld_rom.c"
/* Decode three five-bit vertex indices from each packed word. Emit
 * two triangles when the second word is nonzero, otherwise one. Preserve
 * the original zero-word sentinel rather than treating it as a triangle. */
void uvContourWritePackedTriangles(Gfx *gdl, u16 firstTriangle, u16 secondTriangle) {
    if (secondTriangle) {
        gSP2Triangles(gdl, (firstTriangle & 0x7C00) >> 0xA, (firstTriangle & 0x3E0) >> 5, (firstTriangle & 0x1F), 0,
                      (secondTriangle & 0x7C00) >> 0xA, (secondTriangle & 0x3E0) >> 5, (secondTriangle & 0x1F), 0);
    } else {
        gSP1Triangle(gdl, (firstTriangle & 0x7C00) >> 0xA, (firstTriangle & 0x3E0) >> 5, (firstTriangle & 0x1F), 0);
    }
}
#line 61 "src/modules/uvcontourld_rom.c"

ParsedUVCT *_uvParseUVCT(u8 *arg0) {
    Vtx *sp114;
    ParsedUVMD *uvmd;
    Vtx *sp10C;
    Unk80225FBC_0x28_UnkC *sp108;
    Unk80225FBC_0x28 *sp104;
    s32 l;
    UnkSobjDraw *spFC;
    ParsedUVCT *temp_v0;
    Unk80225FBC_0x28 *var_s5;
    UnkSobjDraw *temp_s0;
    Vtx *t;
    u16 spEA;
    u16 spE8;
    u16 spE6;
    u16 var_s3_2;
    Gfx *temp_s2;
    s32 i; // spDC
    s32 j;
    s32 k;
    s32 temp_a0;
    u8 spCF;
    u8 spCE;
    u16 spCC;
    u16 spCA;
    u16 spC8;
    u16 spC6;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    UnkStruct_uvlight_rom_00401758 sp84;
    s32 sp80;

    uvConsumeBytes(&spCC, (u8 **) &arg0, sizeof(u16));
    uvConsumeBytes(&spEA, (u8 **) &arg0, sizeof(u16));
    uvConsumeBytes(&spE6, (u8 **) &arg0, sizeof(u16));
    uvConsumeBytes(&spE8, (u8 **) &arg0, sizeof(u16));
    uvConsumeBytes(&spBC, (u8 **) &arg0, sizeof(s32));
    uvConsumeBytes(&spC0, (u8 **) &arg0, sizeof(s32));
    uvConsumeBytes(&spB8, (u8 **) &arg0, sizeof(s32));
    sp10C = _uvMemAlloc(spCC * sizeof(Vtx), 8);
    sp114 = sp10C;

    sp80 = 0;
    sp108 = _uvMemAllocAlign8(spEA * 8);
    _uvMediaCopy(sp108, arg0, spEA * 8);
    arg0 += spEA * 8;
    if (spE6 != 0) {
        spFC = _uvMemAllocAlign8(spE6 * sizeof(UnkSobjDraw));
    }
    for (i = 0; i < spE6; i++) {
        temp_s0 = &spFC[i];
        uvConsumeBytes(&spCF, (u8 **) &arg0, sizeof(u8));
        temp_s0->unk4 = _uvMemAllocAlign8(spCF * sizeof(Mtx4F));
        uvConsumeBytes(temp_s0->unk4, (u8 **) &arg0, spCF * sizeof(Mtx4F));
        temp_s0->unk2 = spCF;
        temp_s0->unk38 = 0;
        uvConsumeBytes(&temp_s0->modelId, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&temp_s0->unk8, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&temp_s0->unkC, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&temp_s0->unk10, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&temp_s0->unk14, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&temp_s0->unk18, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&temp_s0->unk1A, (u8 **) &arg0, sizeof(u16));
        temp_s0->unk30 = spBC;
        temp_s0->unk34 = spC0;
        uvmd = uvLoadFile('UVMD', temp_s0->modelId);
        if (uvmd->unk5 & 0x76) {
            temp_s0->unk40 = 1;
        } else {
            temp_s0->unk40 = 0;
        }
        temp_s0->unk3C = 1000000.0f;
        temp_s0->unk1C = 0;
    }
    sp104 = _uvMemAllocAlign8(spE8 * sizeof(Unk80225FBC_0x28));
    for (i = 0; i < spE8; i++) {
        var_s5 = &sp104[i];
        var_s5->unk0 = NULL;
        uvConsumeBytes(&var_s5->texture, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&sp84.unk2C, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&sp84.unk28, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&sp84.unk24, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&var_s5->unkE, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&var_s5->unk12, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&var_s5->unk10, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&var_s5->unk14, (u8 **) &arg0, sizeof(u16));
        if ((var_s5->texture & 0xFFF) != 0xFFF) {
            uvLoadFile('UVTX', (var_s5->texture & 0xFFF));
        }
        if (var_s5->texture & 0x40000) {
            var_s5->unkC = sLightsExport->uvLightAcquireMatchingColorRecord(&sp84);
        } else {
            var_s5->unkC = -1;
        }
        uvConsumeBytes(&spCA, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&spC8, (u8 **) &arg0, sizeof(u16));
        _uvMediaCopy(sp114, arg0, (s16) var_s5->unkE * 0x10);
        var_s5->unk0 = sp114;
        arg0 += var_s5->unkE * 0x10;
        sp80 += var_s5->unkE;
        var_s5->unk34 = 0.0f;

        for (j = 0; j < var_s5->unkE; j++) {
            if (var_s5->unk34 < sp114[j].v.ob[2]) {
                var_s5->unk34 = sp114[j].v.ob[2];
            }
        }
        var_s5->unk34 /= spC0;
        temp_s2 = _uvMemAlloc(spC8 * sizeof(Gfx), 8);
        l = 0;
        var_s3_2 = 0;
        for (k = 0; k < spCA; k++) {
            uvConsumeBytes(&spC6, (u8 **) &arg0, sizeof(u16));
            if (spC6 & 0x8000) {
                if (var_s3_2 == 0) {
                    var_s3_2 = spC6;
                } else {
                    uvContourWritePackedTriangles(&temp_s2[l], var_s3_2, spC6);
                    l++;
                    var_s3_2 = 0;
                }
                continue;
            }
            if (var_s3_2 != 0) {
                uvContourWritePackedTriangles(&temp_s2[l], var_s3_2, 0);
                l++;
                var_s3_2 = 0;
            }
            uvConsumeBytes(&spCE, (u8 **) &arg0, 1U);
            t = &sp114[spC6 & 0x1FFF];
            temp_a0 = (((s32) (spC6 & 0x6000) >> 0xA) | ((s32) (spCE & 0xE0) >> 5));
            gSPVertex(&temp_s2[l], OS_PHYSICAL_TO_K0(t), temp_a0 + 1, spCE & 0x1F);
            l++;
        }

        sp114 = &sp10C[sp80];
        if (var_s3_2 != 0) {
            uvContourWritePackedTriangles(&temp_s2[l], var_s3_2, 0);
            l++;
        }
        gSPEndDisplayList(&temp_s2[l]);
        l++;

        var_s5->unk8 = temp_s2;
        uvConsumeBytes(&spC6, (u8 **) &arg0, sizeof(u16));
        var_s5->unk18 = &sp108[spC6];
        uvConsumeBytes(&spC6, (u8 **) &arg0, sizeof(u16));
        var_s5->unk1C = spC6;
        uvConsumeBytes(&var_s5->unk1E, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&var_s5->unk20, (u8 **) &arg0, sizeof(u16));
        uvConsumeBytes(&var_s5->unk24, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&var_s5->unk28, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&var_s5->unk2C, (u8 **) &arg0, sizeof(s32));
        uvConsumeBytes(&var_s5->unk30, (u8 **) &arg0, sizeof(s32));
        var_s5->unk34 = 1000000.0f;
    }
    temp_v0 = _uvMemAllocAlign8(sizeof(ParsedUVCT));
    temp_v0->vtxTable = sp10C;
    temp_v0->vtxCount = spCC;
    temp_v0->unk8 = sp104;
    temp_v0->unkC = spE8;
    temp_v0->unk10 = spFC;
    temp_v0->unk14 = spE6;
    uvConsumeBytes(&temp_v0->unk18, (u8 **) &arg0, sizeof(s32));
    uvConsumeBytes(&temp_v0->unk1C, (u8 **) &arg0, sizeof(s32));
    uvConsumeBytes(&temp_v0->unk20, (u8 **) &arg0, sizeof(s32));
    uvConsumeBytes(&temp_v0->unk24, (u8 **) &arg0, sizeof(s32));
    temp_v0->unk2C = spBC;
    temp_v0->unk30 = spC0;
    temp_v0->unk28 = spB8;
    return temp_v0;
}

#line 236 "src/modules/uvcontourld_rom.c"
/* Release parsed contour vertices, referenced UVTX/UVMD files, model
 * payloads, texture payloads and light records before freeing the contour.
 * Retain low-12-bit texture identifiers, 0xFFF/0xFFFF sentinels and free the
 * shared offset-0x18 texture allocation only for the first texture record.
 * RE_UNKNOWN: remaining payload meanings and sharing contracts are unproved;
 * no additional ownership or allocation checks are introduced. */
void uvContourLoaderReleaseParsedContour(ParsedUVCT *uvct) {
    s32 i;
    struct UnkSobjDraw *modelRecord;
    s32 textureId;
    s32 modelId;
    ParsedUVCT *contour = uvct;

    _uvMemFree(contour->vtxTable);

    for (i = 0; i < contour->unkC; i++) {
        Unk80225FBC_0x28 *textureToUnload = &contour->unk8[i];
        textureId = (textureToUnload->texture & 0xFFF);
        if (textureId != 0xFFF) {
            uvUnloadFile('UVTX', textureId);
        }
    }

    for (i = 0; i < contour->unk14; i++) {
        modelRecord = &contour->unk10[i];
        modelId = modelRecord->modelId;
        if (modelId != 0xFFFF) {
            uvUnloadFile('UVMD', modelRecord->modelId);
        }
        _uvMemFree(modelRecord->unk4);
    }
    if (contour->unk14 != 0) {
        _uvMemFree(contour->unk10);
    }

    for (i = 0; i < contour->unkC; i++) {
        Unk80225FBC_0x28 *textureToRelease = &contour->unk8[i];
        if (i == 0) {
            _uvMemFree(textureToRelease->unk18);
        }
        _uvMemFree(textureToRelease->unk8);
        if (textureToRelease->unkC != 0xFFFF) {
            sLightsExport->uvLightReleaseRecord(textureToRelease->unkC);
        }
    }
    if (contour->unkC != 0) {
        _uvMemFree(contour->unk8);
    }
    _uvMemFree(contour);
}
#line 280 "src/modules/uvcontourld_rom.c"
