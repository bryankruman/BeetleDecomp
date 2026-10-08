// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports);
void uvTexAnimModuleCleanup(void);
void uvTexAnimCollectLoadedAnimationRecords(void);
void uvTexAnimReleaseSharedArray(void);
void uvTexAnimAdvanceLoadedAnimationCoordinates(s32 arg0);
void func_uvtexanim_rom_00400640(UnkUVTX_1C *arg0, ...);

UvGfxMgr_Exports* D_uvtexanim_rom_00400980;
UvCback_Exports* D_uvtexanim_rom_00400984;
void* D_uvtexanim_rom_00400988;
UnkUVTX_1C** D_uvtexanim_rom_0040098C;
s32 D_uvtexanim_rom_00400990;
u8 D_uvtexanim_rom_00400994;

s32 D_uvtexanim_rom_00400970[] = {0x00100000, __entrypoint_func_uvtexanim_rom_400000, 0, 0};

void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvTexAnimModuleCleanup = uvTexAnimModuleCleanup;
    exports->uvTexAnimCollectLoadedAnimationRecords = uvTexAnimCollectLoadedAnimationRecords;
    exports->uvTexAnimReleaseSharedArray = uvTexAnimReleaseSharedArray;
    exports->func_uvtexanim_rom_00400640 = func_uvtexanim_rom_00400640;
#ifdef __sgi
    #line 24
#endif
    D_uvtexanim_rom_00400980 = uvLoadModule('GMGR');
    D_uvtexanim_rom_00400984 = uvLoadModule('CBCK');
    D_uvtexanim_rom_00400988 = uvLoadModule('TEXT');
    D_uvtexanim_rom_0040098C = NULL;
    D_uvtexanim_rom_00400990 = 0;
    D_uvtexanim_rom_00400984->uvAddCallback(D_uvtexanim_rom_00400980->uvGfxGetCallbackList(1), (s32) uvTexAnimAdvanceLoadedAnimationCoordinates, 0, 0);
}

#line 39 "src/modules/uvtexanim_rom.c"
/* Unload GMGR, CBCK and TEXT dependencies in their original order. */
void uvTexAnimModuleCleanup(void) {
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
    uvUnloadModule('TEXT');
}
#line 44 "src/modules/uvtexanim_rom.c"

#line 45 "src/modules/uvtexanim_rom.c"
/* Count and collect both animation-record pointers exposed by loaded
 * textures. An existing collection or zero records returns immediately;
 * preserve the original allocation and shared pause reset behavior. */
#line 48 "src/modules/uvtexanim_rom.c"

void uvTexAnimCollectLoadedAnimationRecords(void) {
    s32 filesCount;
    s32 textureFileId;
    ParsedUVTX* texture;

    if (D_uvtexanim_rom_0040098C != NULL) {
        return;
    }

    filesCount = uvGetFilesCount('UVTX');
    D_uvtexanim_rom_00400990 = 0;
    for (textureFileId = 0; textureFileId < filesCount; textureFileId++) {
        if (uvGetFileInstanceCount('UVTX', textureFileId) != 0) {
            texture = uvGetLoadedFile('UVTX', textureFileId);
            if (texture != NULL) {
                if (texture->unk4 != 0) {
                    D_uvtexanim_rom_00400990++;
                }
                if (texture->size.as_s32 != 0) {
                    D_uvtexanim_rom_00400990++;
                }
            }
        }
    }
    if (D_uvtexanim_rom_00400990 == 0) {
        return;
    }

    D_uvtexanim_rom_0040098C = _uvMemAllocAlign8(D_uvtexanim_rom_00400990 * 4);
    D_uvtexanim_rom_00400990 = 0;

    for (textureFileId = 0; textureFileId < filesCount; textureFileId++) {
        if (uvGetFileInstanceCount('UVTX', textureFileId) != 0) {
            texture = uvGetLoadedFile('UVTX', textureFileId);
            if (texture != NULL) {
                if (texture->unk4 != 0) {
                    // TODO: What's happening here?
                    D_uvtexanim_rom_0040098C[D_uvtexanim_rom_00400990] = (void*)texture->unk4;
                    D_uvtexanim_rom_00400990 += 1;
                }
                if (texture->size.as_s32 != 0) {
                    D_uvtexanim_rom_0040098C[D_uvtexanim_rom_00400990] = (void*)texture->size.as_s32;
                    D_uvtexanim_rom_00400990 += 1;
                }
            }
        }
    }
    D_uvtexanim_rom_00400994 = 0;
}
#line 97 "src/modules/uvtexanim_rom.c"
#line 94 "src/modules/uvtexanim_rom.c"

#line 95 "src/modules/uvtexanim_rom.c"
/* Free the shared animation array when present, then clear its pointer
 * and associated count in the original order. */
void uvTexAnimReleaseSharedArray(void) {
    if (D_uvtexanim_rom_0040098C != NULL) {
        _uvMemFree(D_uvtexanim_rom_0040098C);
    }
    D_uvtexanim_rom_0040098C = NULL;
    D_uvtexanim_rom_00400990 = 0;
}
#line 102 "src/modules/uvtexanim_rom.c"

#line 103 "src/modules/uvtexanim_rom.c"
/* Advance each enabled record by the shared graphics scalar. Each
 * coordinate retains its original wrap, stop, bounce or hold mode;
 * either stop-mode endpoint clears the shared record enable flag. */
#line 106 "src/modules/uvtexanim_rom.c"

void uvTexAnimAdvanceLoadedAnimationCoordinates(s32 unusedUpdateValue) {
    f32 graphicsScalar;
    s32 animationIndex;
    UnkUVTX_1C *animation;

    graphicsScalar = D_uvtexanim_rom_00400980->uvGfxMgrGetScalarOverrideOrCurrent();
    if ((u8) D_uvtexanim_rom_00400994 == 1) {
        return;
    }

    for (animationIndex = 0; animationIndex < D_uvtexanim_rom_00400990; animationIndex++) {
        animation = D_uvtexanim_rom_0040098C[animationIndex];
        if (animation->unk1A == 0) {
            continue;
        }
        if (animation->unk18 != 3) {
            animation->unk10 += (animation->unk8 * graphicsScalar);
        }
        if (animation->unk18 == 0) {
            if (animation->unk8 > 0.0f) {
                if (animation->unk10 >= 1.0f) {
                    animation->unk10 -= 1.0f;
                }
            }
            if (animation->unk8 < 0.0f) {
                if (animation->unk10 <= 0) {
                    animation->unk10 += 1.0f;
                }
            }
        } else if (animation->unk18 == 2) {
            if (animation->unk10 >= 1.0f) {
                animation->unk10 = 0.999f;
                animation->unk8 =  -animation->unk8;
            } else if (animation->unk10 <= 0) {
                animation->unk10 = 0.001f;
                animation->unk8 = -animation->unk8;
            }
        } else if (animation->unk18 == 1) {
            if ((animation->unk8 > 0.0f) && (animation->unk10 >= 1.0f)) {
                animation->unk10 = 1.0f;
                animation->unk1A = 0U;
            }
            if ((animation->unk8 < 0.0f) && (animation->unk10 <= 0)) {
                animation->unk10 = 0;
                animation->unk1A = 0U;
            }
        }
        if (animation->unk19 != 3) {
            animation->unk14 += animation->unkC * graphicsScalar;
        }
        if (animation->unk19 == 0) {
            if (animation->unkC > 0.0f) {
                if (animation->unk14 >= 1.0f) {
                    animation->unk14 -= 1.0f;
                }
            }
            if (animation->unkC < 0.0f) {
                if (animation->unk14 <= 0) {
                    animation->unk14 += 1.0f;
                }
            }
        } else if (animation->unk19 == 2) {
            if (animation->unk14 >= 1.0f) {
                animation->unk14 = 0.999f;
                animation->unkC =  -animation->unkC;
            } else if (animation->unk14 <= 0) {
                animation->unk14 =  0.001f;
                animation->unkC = -animation->unkC;
            }
        } else if (animation->unk19 == 1) {
            if ((animation->unkC > 0.0f) && (animation->unk14 >= 1.0f)) {
                animation->unk14 = 1.0f;
                animation->unk1A = 0U;
            }
            if ((animation->unkC < 0.0f) && (animation->unk14 <= 0)) {
                animation->unk14 = 0;
                animation->unk1A = 0U;
            }
        }
    }
}
#line 187 "src/modules/uvtexanim_rom.c"
#line 184 "src/modules/uvtexanim_rom.c"

void func_uvtexanim_rom_00400640(UnkUVTX_1C *arg0, ...) {
    s32 var_a2;
    s16 temp_a0;
    va_list args;
    UnkUVTX_1C* v0;

    v0 = arg0;

    va_start(args, arg0);
    while (TRUE) {
        temp_a0 = va_arg(args, u16*);
        switch (temp_a0) {
            default:
                return;
            case 1:
                D_uvtexanim_rom_00400994 = (s16)va_arg(args, s32);
                break;
            case 2:
                v0->unk0 = va_arg(args, f64);
                v0->unk4 = va_arg(args, f64);
                break;
            case 3:
                v0->unk8 = va_arg(args, f64);
                v0->unkC = va_arg(args, f64);
                break;
            case 5:
                var_a2 = FALSE;
                v0->unk10 = va_arg(args, f64);
                v0->unk14 = va_arg(args, f64);
                if (v0->unk10 > 1.0f) {
                    v0->unk10 = 1.0f;
                    var_a2 = TRUE;
                }
                if (v0->unk10 < 0.0f) {
                    var_a2 = TRUE;
                    v0->unk10 = 0.0f;
                }
                if (v0->unk14 > 1.0f) {
                    v0->unk14 = 1.0f;
                    var_a2 = TRUE;
                }
                if (v0->unk14 < 0.0f) {
                    var_a2 = TRUE;
                    v0->unk14 = 0.0f;
                }
                if (var_a2) {
                    break;
                }
                break;
            case 4:
                v0->unk1A = va_arg(args, s32);
                break;
            case 6:
                v0->unk18 = va_arg(args, s32);
                v0->unk19 = va_arg(args, s32);
                break;
            case 0:
                return;
        }
    }
}