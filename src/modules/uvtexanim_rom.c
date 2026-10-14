// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "stdarg.h"

void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports);
void uvTexAnimModuleCleanup(void);
void uvTexAnimCollectLoadedAnimationRecords(void);
void uvTexAnimReleaseSharedArray(void);
void uvTexAnimAdvanceLoadedAnimationCoordinates(s32 arg0);
void uvTexAnimSetTaggedProperties(UnkUVTX_1C *arg0, ...);

UvGfxMgr_Exports* D_uvtexanim_rom_00400980;
UvCback_Exports* D_uvtexanim_rom_00400984;
void* D_uvtexanim_rom_00400988;
UnkUVTX_1C** D_uvtexanim_rom_0040098C;
s32 D_uvtexanim_rom_00400990;
u8 D_uvtexanim_rom_00400994;

s32 D_uvtexanim_rom_00400970[] = {0x00100000, __entrypoint_func_uvtexanim_rom_400000, 0, 0};

/*
 * Install four texture-animation exports, load GMGR, CBCK and TEXT, clear
 * the shared array pointer/count, and register the animation-coordinate
 * callback on graphics list 1 with both user words zero.
 * RE_ORIGINAL_QUIRK: Preserve the conditional line directive, initialization
 * order and integer cast of the callback address. This body does not remove
 * an earlier registration or release an earlier shared array.
 * RE_UNKNOWN: Import failure, duplicate registration, array ownership and
 * callback/provider lifetime require the texture-animation lifecycle.
 */
#line 22 "src/modules/uvtexanim_rom.c"
void __entrypoint_func_uvtexanim_rom_400000(UvTexAnim_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvTexAnimModuleCleanup = uvTexAnimModuleCleanup;
    exports->uvTexAnimCollectLoadedAnimationRecords = uvTexAnimCollectLoadedAnimationRecords;
    exports->uvTexAnimReleaseSharedArray = uvTexAnimReleaseSharedArray;
    exports->uvTexAnimSetTaggedProperties = uvTexAnimSetTaggedProperties;
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
/* Collect both borrowed animation pointers in two passes; preserve allocation/pause reset.
 * Existing collections and zero counts return; RE_ORIGINAL_QUIRK: no pointer deduplication.
 * RE_UNKNOWN: loaded-set stability, allocation success and borrowed-record lifetime. */
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
/* Free only the pointer array, then clear its pointer/count in original order;
 * no animation record is freed here; texture destruction frees those records. */
void uvTexAnimReleaseSharedArray(void) {
    if (D_uvtexanim_rom_0040098C != NULL) {
        _uvMemFree(D_uvtexanim_rom_0040098C);
    }
    D_uvtexanim_rom_0040098C = NULL;
    D_uvtexanim_rom_00400990 = 0;
}
#line 102 "src/modules/uvtexanim_rom.c"

#line 103 "src/modules/uvtexanim_rom.c"
/* Visit every collected pointer, advancing enabled records by the shared graphics scalar.
 * RE_ORIGINAL_QUIRK: aliases are revisited; a stop-mode endpoint clears the shared enable flag.
 * Preserve each coordinate's original wrap, stop, bounce or hold mode. */
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

#line 185 "src/modules/uvtexanim_rom.c"

/* Apply a variadic sequence of texture-animation property tags. Tags update
 * the shared pause byte or record float/byte fields; tag 5 clamps both stored
 * coordinates with the original ordered comparisons and write sequence.
 * RE_UNKNOWN: historical selector argument type (the existing C reads u16*),
 * complete record/argument domains, coordinate units and caller termination.
 * Preserve the observed signed low-16 tag decoding and double-to-float values;
 * trace native callers before changing argument types or field meanings. */
#line 185 "src/modules/uvtexanim_rom.c"
void uvTexAnimSetTaggedProperties(UnkUVTX_1C *inputAnimation, ...) {
    s32 coordinatesClamped;
    s16 propertyTag;
    va_list arguments;
    UnkUVTX_1C* animation;

    animation = inputAnimation;

    va_start(arguments, inputAnimation);
    while (TRUE) {
        propertyTag = va_arg(arguments, u16*);
        switch (propertyTag) {
            default:
                return;
            case 1:
                D_uvtexanim_rom_00400994 = (s16)va_arg(arguments, s32);
                break;
            case 2:
                animation->unk0 = va_arg(arguments, f64);
                animation->unk4 = va_arg(arguments, f64);
                break;
            case 3:
                animation->unk8 = va_arg(arguments, f64);
                animation->unkC = va_arg(arguments, f64);
                break;
            case 5:
                coordinatesClamped = FALSE;
                animation->unk10 = va_arg(arguments, f64);
                animation->unk14 = va_arg(arguments, f64);
                if (animation->unk10 > 1.0f) {
                    animation->unk10 = 1.0f;
                    coordinatesClamped = TRUE;
                }
                if (animation->unk10 < 0.0f) {
                    coordinatesClamped = TRUE;
                    animation->unk10 = 0.0f;
                }
                if (animation->unk14 > 1.0f) {
                    animation->unk14 = 1.0f;
                    coordinatesClamped = TRUE;
                }
                if (animation->unk14 < 0.0f) {
                    coordinatesClamped = TRUE;
                    animation->unk14 = 0.0f;
                }
                if (coordinatesClamped) {
                    break;
                }
                break;
            case 4:
                animation->unk1A = va_arg(arguments, s32);
                break;
            case 6:
                animation->unk18 = va_arg(arguments, s32);
                animation->unk19 = va_arg(arguments, s32);
                break;
            case 0:
                return;
        }
    }
}
#line 246 "src/modules/uvtexanim_rom.c"