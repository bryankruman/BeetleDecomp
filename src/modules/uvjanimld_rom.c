// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

UvParsedAN *func_uvjanimld_rom_00400050(u8 *arg0);
void uvJanimLdNoOpModuleCleanup(void);
void uvJAnimLoaderReleaseParsedAnimation(UvParsedAN* parsedAnimation);

void __entrypoint_func_uvjanimld_rom_400000(UvJanimLd_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvParseAnimationData = func_uvjanimld_rom_00400050;
    exports->stub = uvJanimLdNoOpModuleCleanup;
    exports->uvFreeParsedAnimationData = uvJAnimLoaderReleaseParsedAnimation;
}

#line 16 "src/modules/uvjanimld_rom.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void uvJanimLdNoOpModuleCleanup(void) {

}
#line 19 "src/modules/uvjanimld_rom.c"

// uvJanimParse
UvParsedAN *func_uvjanimld_rom_00400050(u8 *arg0) {
    UvParsedAN *spA4;
    UvParsedAN_2 *temp_v0_4;
    s32 var_a0;
    u32 sp98;
    void *sp94;
    void *sp90;
    s32 sp8C;
    s32 sp88;
    UvParsedAN_2 *var_s6;
    u32 var_v0;
    void *sp7C;
    s32 var_s3;
    u8 sp77;
    s32 s4, s7, v1;
    u16 sp66;

    var_s6 = NULL;
    sp8C = uvFileReadHeader(arg0);
    while ((var_v0 = uvFileReadBlock(sp8C, &sp98, &sp94, 1)) != 0) {
        switch (var_v0) {
            case 'COMM':
                sp90 = sp94;
                sp7C = sp94;
                spA4 = _uvMemAllocAlign8(sizeof(UvParsedAN));
                uvConsumeBytes(&spA4->unk0, (u8 **) &sp7C, sizeof(u16));
                uvConsumeBytes(&spA4->unk2, (u8 **) &sp7C, sizeof(u16));
                uvConsumeBytes(&spA4->unk4, (u8 **) &sp7C, sizeof(u16));
                uvConsumeBytes(spA4->unk8, (u8 **) &sp7C, sizeof(u8));
                uvConsumeBytes(&spA4->unk9, (u8 **) &sp7C, sizeof(u8));
                spA4->unk6 = spA4->unk2 / spA4->unk4;
                for (sp88 = 0; sp88 < spA4->unk9; sp88++) {
                    temp_v0_4 = _uvMemAllocAlign8(sizeof(UvParsedAN_2));
                    if (var_s6 != NULL) {
                        var_s6->unk0 = temp_v0_4;
                        var_s6 = temp_v0_4;
                    } else {
                        var_s6 = temp_v0_4;
                        spA4->unkC = temp_v0_4;
                    }
                    uvConsumeBytes(&var_s6->unk6, (u8 **) &sp7C, sizeof(u16));
                    uvConsumeBytes(&var_s6->unk4, (u8 **) &sp7C, sizeof(u16));
                    uvConsumeBytes(&sp77, (u8 **) &sp7C, sizeof(u8));
                    var_s6->unk10 = NULL;
                    var_s6->unk0 = NULL;
                    var_s6->unk18 = NULL;
                    var_s6->unk14 = NULL;
                    var_s6->unk8 = 0;
                    var_s6->unk1C = NULL;
                    var_s6->unkC = _uvMemAllocAlign8(var_s6->unk6 * sizeof(u16));
                    if (sp77 & 1) {
                        var_s6->unk18 = _uvMemAllocAlign8(var_s6->unk6 * sizeof(Quat));
                        var_s6->unk1C = _uvMemAllocAlign8(var_s6->unk6);
                    }
                    if (sp77 & 2) {
                        var_s6->unk10 = _uvMemAllocAlign8(var_s6->unk6 * sizeof(Vec3F));
                    }
                    if (sp77 & 4) {
                        var_s6->unk14 = _uvMemAllocAlign8(var_s6->unk6 * sizeof(Vec3F));
                    }
                    for (var_s3 = 0; var_s3 < var_s6->unk6; var_s3++) {
                        uvConsumeBytes(&sp66, (u8 **) &sp7C, sizeof(u16));
                        if (var_s6->unk1C != NULL) {
                            var_s6->unk1C[var_s3] = (sp66 & 0x8000) != 0;
                        }
                        v1 = (sp66 & 0x4000) != 0;
                        s4 = (sp66 & 0x2000) != 0;
                        s7 = (sp66 & 0x1000) != 0;
                        var_s6->unkC[var_s3] = sp66 & 0xFFF;
                        if (v1) {
                            uvConsumeBytes(&var_s6->unk18[var_s3].x, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk18[var_s3].y, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk18[var_s3].z, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk18[var_s3].w, (u8 **) &sp7C, sizeof(f32));
                        } else {
                            if (var_s6->unk18 != NULL) {
                                var_s6->unk18[var_s3].x = 0.0f;
                                var_s6->unk18[var_s3].y = 0.0f;
                                var_s6->unk18[var_s3].z = 0.0f;
                                var_s6->unk18[var_s3].w = 1.0f;
                            }
                        }
                        if (s4) {
                            uvConsumeBytes(&var_s6->unk10[var_s3].x, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk10[var_s3].y, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk10[var_s3].z, (u8 **) &sp7C, sizeof(f32));
                        } else {
                            if (var_s6->unk10 != NULL) {
                                var_s6->unk10[var_s3].x = 0.0f;
                                var_s6->unk10[var_s3].y = 0.0f;
                                var_s6->unk10[var_s3].z = 0.0f;
                            }
                        }
                        if (s7) {
                            uvConsumeBytes(&var_s6->unk14[var_s3].x, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk14[var_s3].y, (u8 **) &sp7C, sizeof(f32));
                            uvConsumeBytes(&var_s6->unk14[var_s3].z, (u8 **) &sp7C, sizeof(f32));
                        } else {
                            if (var_s6->unk14 != NULL) {
                                var_s6->unk14[var_s3].x = 1.0f;
                                var_s6->unk14[var_s3].y = 1.0f;
                                var_s6->unk14[var_s3].z = 1.0f;
                            }
                        }
                    }
                    if (var_s6->unk8 != NULL) {
                        for (var_a0 = 0, var_s3 = 0; var_a0 < spA4->unk2; var_a0++) {
                            while (var_a0 >= var_s6->unkC[var_s3 + 1] && (var_s3 + 1) < var_s6->unk6) {
                                var_s3++;
                            }
                            var_s6->unk8[var_a0] = var_s3;
                        }
                    }
                }
                _uvMemFree(sp90);
                break;
        }
    }
    uvFileFree(sp8C);
    return spA4;
}

#line 143 "src/modules/uvjanimld_rom.c"
/* Snapshot the linked animation nodes into a temporary pointer table
 * before releasing node payloads, nodes, the table and the parsed animation.
 * Preserve payload free order and the conditional paired free at offsets
 * 0x18/0x1C.
 * RE_UNKNOWN: node count, chain integrity and payload ownership are unchecked
 * contracts; unknown node fields keep their offset names. */
void uvJAnimLoaderReleaseParsedAnimation(UvParsedAN* parsedAnimation) {
    UvParsedAN_2** nodeTable;
    UvParsedAN* animation;
    UvParsedAN_2* node;
    s32 i;

    animation = parsedAnimation;
    nodeTable = _uvMemAllocAlign8(parsedAnimation->unk9 * 4);
    node = NULL;
    for (i = 0; i < animation->unk9; i++) {
        if (node != NULL) {
            node = node->unk0;
        } else {
            node = animation->unkC;
        }
        nodeTable[i] = node;
    }


    for (i = 0; i < animation->unk9; i++) {
        node = nodeTable[i];
        if (node->unk14 != NULL) {
            _uvMemFree( node->unk14);
        }
        if (node->unk10 != NULL) {
            _uvMemFree(node->unk10);
        }
        if (node->unk18 != NULL) {
            _uvMemFree(node->unk1C);
            _uvMemFree(node->unk18);
        }
        _uvMemFree(node->unkC);
        _uvMemFree(node);
    }


    _uvMemFree(nodeTable);

    _uvMemFree(parsedAnimation);
}
#line 183 "src/modules/uvjanimld_rom.c"

