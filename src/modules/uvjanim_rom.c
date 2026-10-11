// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvquat_rom.h"

#define alloca(size) __builtin_alloca(size)

/*
 * D_uvjanim_rom_00401760 = uvLoadModule(0x4D415448, arg0);
 * D_uvjanim_rom_00401764 = uvLoadModule(0x4D4F444C);
 * D_uvjanim_rom_00401768 = uvLoadModule(0x444F424A);
 * D_uvjanim_rom_0040176C = uvLoadModule(0x464D5458);
 * D_uvjanim_rom_00401770 = uvLoadModule(0x51554154)
 */

typedef struct UnkModelExports_s {
    char pad[0x14];
    void (*unk14)(s32, s32, Mtx4F *);
} UnkModelExports;

extern UvQuat_Exports *D_uvjanim_rom_00401770;
extern UvDobj_Exports *D_uvjanim_rom_00401768;
extern UnkModelExports *D_uvjanim_rom_00401764;
extern UvFMtx_Rom_Exports *D_uvjanim_rom_0040176C;
extern UvMath_Exports *D_uvjanim_rom_00401760;

void uvJanimModuleCleanup(void);
void uvJanimCopyPose(UnkStruct_UvJanim_rom_00400144 *arg0,
                               UnkStruct_UvJanim_rom_00400144 *arg1);
void uvJanimApplyPose(s32 arg0, UnkStruct_UvJanim_rom_00400144 *arg1);
void uvJanimApplyAnimation(s32 arg0, s32 arg1, f32 arg2);
void uvJanimSamplePoseAtNormalizedTime(UnkStruct_UvJanim_rom_00400144 *arg0, s32 arg1, f32 arg2);
void uvJanimApplyAnimationGrid(s32 arg0, s32 arg1, f32 arg2, f32 arg3);
void uvJanimSamplePoseAcrossTwoNormalizedAxes(UnkStruct_UvJanim_rom_00400144 *arg0, s32 arg1, f32 arg2, f32 arg3);
void uvJanimWriteJointMatrices(s32 arg0, UnkStruct_uvjanim_rom_00401704 *arg1);
void uvJanimSamplePoseAtNormalizedTime(UnkStruct_UvJanim_rom_00400144 *, s32, f32); /* extern */
void uvJanimMergeWeightedPoseChannels(UnkStruct_UvJanim_rom_00400144 *arg0,
                               UnkStruct_UvJanim_rom_00400144 *arg1,
                               UnkStruct_UvJanim_rom_00400144 *arg2, f32 arg3);

void __entrypoint_func_uvjanim_rom_400000(UvJanim_Exports *exports);

/*
 * Install the nine joint-animation exports, then load MATH, MODL, DOBJ,
 * FMTX and QUAT into the five retained provider slots. No pose or animation
 * record is created or reset here.
 * RE_ORIGINAL_QUIRK: Preserve the export order, existing line directive and
 * the original public function names and all nine export assignments.
 * RE_UNKNOWN: Export-table validity, import failure, repeat initialization and
 * provider reference lifetime require the loader and joint-animation callers.
 */
#line 43 "src/modules/uvjanim_rom.c"
void __entrypoint_func_uvjanim_rom_400000(UvJanim_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->uvJanimModuleCleanup = uvJanimModuleCleanup;
    exports->uvJanimCopyPose = uvJanimCopyPose;
    exports->uvJanimApplyPose = uvJanimApplyPose;
    exports->uvJanimMergeWeightedPoseChannels = uvJanimMergeWeightedPoseChannels;
    exports->uvJanimApplyAnimation = uvJanimApplyAnimation;
    exports->uvJanimSamplePoseAtNormalizedTime = uvJanimSamplePoseAtNormalizedTime;
    exports->uvJanimApplyAnimationGrid = uvJanimApplyAnimationGrid;
    exports->uvJanimSamplePoseAcrossTwoNormalizedAxes = uvJanimSamplePoseAcrossTwoNormalizedAxes;
    exports->uvJanimWriteJointMatrices = uvJanimWriteJointMatrices;
#line 45
    D_uvjanim_rom_00401760 = uvLoadModule('MATH');
    D_uvjanim_rom_00401764 = uvLoadModule('MODL');
    D_uvjanim_rom_00401768 = uvLoadModule('DOBJ');
    D_uvjanim_rom_0040176C = uvLoadModule('FMTX');
    D_uvjanim_rom_00401770 = uvLoadModule('QUAT');
}

#line 52 "src/modules/uvjanim_rom.c"
/* Unload math, model, dynamic-object, matrix and quaternion modules
 * in the original order. */
void uvJanimModuleCleanup(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('DOBJ');
    uvUnloadModule('FMTX');
    uvUnloadModule('QUAT');
}
#line 59 "src/modules/uvjanim_rom.c"

#line 60 "src/modules/uvjanim_rom.c"
/* Copy enabled channels and IDs when the u16 member at 0x12 covers the
 * u8 count at 0x10. RE_UNKNOWN: writable extents, aliases and lifetimes
 * need original allocation/resource producers and full caller contracts. */
void uvJanimCopyPose(UnkStruct_UvJanim_rom_00400144 *destination,
                               UnkStruct_UvJanim_rom_00400144 *source) {
    if (destination->unk12 >= source->unk10) {
        if (source->unk0 != NULL) {
            if ((destination->unk0 != NULL) && (source->unk11 & 1)) {
                _uvMediaCopy(destination->unk0, source->unk0, source->unk10 * 0x10);
            }
        }
        if (source->unk4 != NULL) {
            if ((destination->unk4 != NULL) && (source->unk11 & 2)) {
                _uvMediaCopy(destination->unk4, source->unk4, source->unk10 * 0xC);
            }
        }
        if (source->unk8 != NULL) {
            if ((destination->unk8 != NULL) && (source->unk11 & 4)) {
                _uvMediaCopy(destination->unk8, source->unk8, source->unk10 * 0xC);
            }
        }
        if (source->unkC != NULL) {
            if (destination->unkC != NULL) {
                _uvMediaCopy(destination->unkC, source->unkC, (u32) source->unk10);
            }
        }
        destination->unk11 = source->unk11; /* RE_ORIGINAL_QUIRK: native publishes source flags/count even when an optional copy was skipped. RE_UNKNOWN: caller reachability needs proof. */
        destination->unk10 = source->unk10;
    }
}
#line 87 "src/modules/uvjanim_rom.c"

#line 88 "src/modules/uvjanim_rom.c"
/* Apply enabled pose channels in joint order; the vector at pose offset
 * 0x08 feeds native FMTX slot 0x30 matrix scaling. RE_UNKNOWN: joint
 * validity, channel extents, aliases/lifetimes and conventions need callers. */
void uvJanimApplyPose(s32 objectId, UnkStruct_UvJanim_rom_00400144 *pose) {
    Mtx4F matrix;
    s32 i; // s4
    Quat *rotations;
    s32 modelId;
    Vec3F *translations;
    Vec3F *scales;
    s32 count;

    modelId = D_uvjanim_rom_00401768->uvDobjGetModel(objectId);
    rotations = pose->unk0;
    translations = pose->unk4;
    scales = pose->unk8;
    count = pose->unk10;

    for (i = 0; i < count; i++) {
        D_uvjanim_rom_00401764->unk14(modelId, pose->unkC[i], &matrix);
        if ((pose->unk11 & 1) && (rotations != NULL)) {
            D_uvjanim_rom_0040176C->uvMat4SetNormalizedQuaternionRotation(&matrix, rotations->x, rotations->y, rotations->z, rotations->w);
            rotations++;
        }

        if ((pose->unk11 & 2) && (translations != NULL)) {
            matrix.m[3][0] += translations->x;
            matrix.m[3][1] += translations->y;
            matrix.m[3][2] += translations->z;
            translations++;
        }
        if ((pose->unk11 & 4) && (scales != NULL)) {
            D_uvjanim_rom_0040176C->uvMat4Scale(&matrix, scales->x, scales->y, scales->z);
            scales++;
        }

        D_uvjanim_rom_00401768->uvDobjPosm(objectId, pose->unkC[i], &matrix);
    }
}
#line 130 "src/modules/uvjanim_rom.c"

void uvJanimMergeWeightedPoseChannels(UnkStruct_UvJanim_rom_00400144 *destination,
                               UnkStruct_UvJanim_rom_00400144 *firstPose,
                               UnkStruct_UvJanim_rom_00400144 *secondPose, f32 inputSecondWeight) {
    Vec3F *unusedVector0; /* RE_UNKNOWN: original pose declarations and unused locals need historical sources; retain the current compatible view. */
    f32 secondWeight;
    s32 outputCount;
    s32 firstIndex;
    s32 secondIndex;
    s32 firstRemaining;
    s32 secondRemaining;
    Vec3F *unusedVector1;
    Vec3F *unusedVector2;
    Vec3F *secondVector;
    Vec3F *outputVector;
    Vec3F *firstVector;
    f32 firstWeight;
    Quat *outputQuaternion;
    Quat *firstQuaternion;
    Quat *secondQuaternion;

    outputCount = 0; /* Merge enabled channels by byte joint IDs. RE_UNKNOWN: sortedness, cross-channel ID agreement, backing extents and lifetimes need original pose producers and full callers. */
    if (inputSecondWeight > 1.0f) {
        secondWeight = 1.0f;
    } else {
        secondWeight = inputSecondWeight;
    }
    if (secondWeight < 0.0f) {
        secondWeight = 0.0f;
    }
    firstWeight = 1.0f - secondWeight; /* RE_ORIGINAL_QUIRK: NaN bypasses both clamps; unmatched IDs whose weight is not positive are consumed without output. RE_UNKNOWN: caller reachability needs proof. */
    destination->unk11 = 0; /* RE_UNKNOWN: source/destination alias rules need original allocation and caller contracts; preserve live field reloads after this clear. */
    if (destination->unk4 != NULL) {
        if (firstPose->unk4 != NULL) {
            if (secondPose->unk4 != NULL) {
                outputVector = destination->unk4;
                firstVector = firstPose->unk4;
                secondVector = secondPose->unk4;
                if (firstPose->unk11 & secondPose->unk11 & 2) {
                    firstRemaining = firstPose->unk10;
                    secondIndex = 0;
                    firstIndex = 0;
                    secondRemaining = secondPose->unk10;
                    while (((firstRemaining != 0) || (secondRemaining != 0)) && (outputCount < destination->unk12)) {
                        if ((firstRemaining != 0) && (secondRemaining != 0)
                            && (firstPose->unkC[firstIndex] == secondPose->unkC[secondIndex])) {
                            outputVector->x = ((secondVector->x * secondWeight) + (firstVector->x * firstWeight));
                            outputVector->y = ((secondVector->y * secondWeight) + (firstVector->y * firstWeight));
                            outputVector->z = ((secondVector->z * secondWeight) + (firstVector->z * firstWeight));
                            outputVector++;
                            firstRemaining--;
                            firstVector++;
                            secondIndex++;
                            secondRemaining--;
                            secondVector++;
                            destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            firstIndex++;
                        } else if ((secondRemaining != 0)
                                   && ((firstRemaining == 0)
                                       || ((s32) secondPose->unkC[secondIndex] < (s32) firstPose->unkC[firstIndex]))) {
                            secondRemaining--;
                            if (secondWeight > 0.0f) {
                                outputVector->x = secondVector->x;
                                outputVector->y = secondVector->y;
                                outputVector->z = secondVector->z;
                                outputVector++;
                                destination->unkC[outputCount++] = secondPose->unkC[secondIndex];
                            }
                            secondIndex++;
                            secondVector++;
                        } else if ((firstRemaining != 0)
                                   && ((secondRemaining == 0)
                                       || ((s32) firstPose->unkC[firstIndex] < (s32) secondPose->unkC[secondIndex]))) {
                            firstRemaining--;
                            if (firstWeight > 0.0f) {
                                outputVector->x = firstVector->x;
                                outputVector->y = firstVector->y;
                                outputVector->z = firstVector->z;
                                outputVector++;
                                destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            }

                            firstIndex++;
                            firstVector++;
                        }
                    }
                    destination->unk11 |= 2;
                }
            }
        }
    }
    if (destination->unk8 != NULL) { /* Preserve independent vector traversal at offset 0x08 and shared ID writes; the u16 limit at 0x12 is not proof of writable capacity. RE_UNKNOWN: actual extents need producers. */
        if (firstPose->unk8 != NULL) {
            if (secondPose->unk8 != NULL) {
                outputVector = destination->unk8;
                firstVector = firstPose->unk8;
                secondVector = secondPose->unk8;
                if (firstPose->unk11 & secondPose->unk11 & 4) {
                    firstRemaining = firstPose->unk10;
                    secondIndex = 0;
                    firstIndex = 0;
                    outputCount = 0;
                    secondRemaining = secondPose->unk10;
                    while (((firstRemaining != 0) || (secondRemaining != 0)) && (outputCount < destination->unk12)) {
                        if ((firstRemaining != 0) && (secondRemaining != 0)
                            && (firstPose->unkC[firstIndex] == secondPose->unkC[secondIndex])) {
                            outputVector->x = ((secondVector->x * secondWeight) + (firstVector->x * firstWeight));
                            outputVector->y = ((secondVector->y * secondWeight) + (firstVector->y * firstWeight));
                            outputVector->z = ((secondVector->z * secondWeight) + (firstVector->z * firstWeight));
                            outputVector++;
                            firstRemaining--;
                            firstVector++;
                            secondIndex++;
                            secondRemaining--;
                            secondVector++;
                            destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            firstIndex++;
                        } else if ((secondRemaining != 0)
                                   && ((firstRemaining == 0) || (secondPose->unkC[secondIndex] < firstPose->unkC[firstIndex]))) {
                            secondRemaining--;
                            if (secondWeight > 0.0f) {
                                outputVector->x = secondVector->x;
                                outputVector->y = secondVector->y;
                                outputVector->z = secondVector->z;
                                outputVector++;
                                destination->unkC[outputCount++] = secondPose->unkC[secondIndex];
                            }
                            secondIndex++;
                            secondVector++;
                        } else if ((firstRemaining != 0)
                                   && ((secondRemaining == 0) || (firstPose->unkC[firstIndex] < secondPose->unkC[secondIndex]))) {
                            firstRemaining -= 1;
                            if (firstWeight > 0.0f) {
                                outputVector->x = firstVector->x;
                                outputVector->y = firstVector->y;
                                outputVector->z = firstVector->z;
                                outputVector++;
                                destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            }
                            firstIndex++;
                            firstVector++;
                        }
                    }
                    destination->unk11 |= 4;
                }
            }
        }
    }
    if (destination->unk0 != NULL) { /* Matching IDs call the native quaternion blend; unmatched entries copy directly. RE_UNKNOWN: valid weight/rotation domains and conventions need assets and callers. */
        if (firstPose->unk0 != NULL) {
            if (secondPose->unk0 != NULL) {
                outputQuaternion = destination->unk0;
                firstQuaternion = firstPose->unk0;
                secondQuaternion = secondPose->unk0;
                if (firstPose->unk11 & secondPose->unk11 & 1) {
                    firstRemaining = firstPose->unk10;
                    secondIndex = 0;
                    firstIndex = 0;
                    outputCount = 0;
                    secondRemaining = secondPose->unk10;
                    while (((firstRemaining != 0) || (secondRemaining != 0)) && (outputCount < destination->unk12)) {
                        if ((firstRemaining != 0) && (secondRemaining != 0)
                            && (firstPose->unkC[firstIndex] == secondPose->unkC[secondIndex])) {
                            D_uvjanim_rom_00401770->uvQuatBlendNormalized(outputQuaternion, firstQuaternion, secondQuaternion,
                                                                             secondWeight);
                            outputQuaternion++;
                            firstQuaternion++;
                            secondQuaternion++;
                            firstRemaining--;
                            secondRemaining--;
                            secondIndex++;
                            destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            firstIndex++;
                        } else if ((secondRemaining != 0)
                                   && ((firstRemaining == 0)
                                       || ((s32) secondPose->unkC[secondIndex] < (s32) firstPose->unkC[firstIndex]))) {
                            secondRemaining -= 1;
                            if (secondWeight > 0.0f) {
                                outputQuaternion->x = secondQuaternion->x;
                                outputQuaternion->y = secondQuaternion->y;
                                outputQuaternion->z = secondQuaternion->z;
                                outputQuaternion->w = secondQuaternion->w;
                                outputQuaternion++;
                                destination->unkC[outputCount++] = secondPose->unkC[secondIndex];
                            }
                            secondIndex++;
                            secondQuaternion++;
                        } else if ((firstRemaining != 0)
                                   && ((secondRemaining == 0)
                                       || ((s32) firstPose->unkC[firstIndex] < (s32) secondPose->unkC[secondIndex]))) {
                            firstRemaining -= 1;
                            if (firstWeight > 0.0f) {
                                outputQuaternion->x = firstQuaternion->x;
                                outputQuaternion->y = firstQuaternion->y;
                                outputQuaternion->z = firstQuaternion->z;
                                outputQuaternion->w = firstQuaternion->w;
                                outputQuaternion++;
                                destination->unkC[outputCount++] = firstPose->unkC[firstIndex];
                            }
                            firstIndex++;
                            firstQuaternion++;
                        }
                    }
                    destination->unk11 |= 1;
                }
            }
        }
    }
    destination->unk10 = outputCount; /* RE_ORIGINAL_QUIRK: native publishes only the low byte of the last executed channel count; RE_UNKNOWN: producer bounds and cross-channel agreement need proof. */
}

#line 341 "src/modules/uvjanim_rom.c"
/* Allocate temporary pose channels for a loaded animation, evaluate
 * its supplied position and apply the pose. Missing animations do nothing. */
void uvJanimApplyAnimation(s32 objectId, s32 animationId, f32 position) {
    UnkStruct_UvJanim_rom_00400144 pose;
    UvParsedAN *animation;

    animation = uvGetLoadedFile('UVAN', animationId);
    if (animation != NULL) {
        pose.unk0 = alloca(sizeof(Quat) * animation->unk9);
        pose.unk4 = alloca(sizeof(Vec3F) * animation->unk9);
        pose.unk8 = alloca(sizeof(Vec3F) * animation->unk9);
        pose.unkC = alloca(sizeof(u8) * animation->unk9);
        pose.unk12 = animation->unk9;
        pose.unk10 = 0;
        pose.unk11 = 7;
        uvJanimSamplePoseAtNormalizedTime(&pose, animationId, position);
        uvJanimApplyPose(objectId, (UnkStruct_UvJanim_rom_00400144 *) &pose);
    }
}
#line 358 "src/modules/uvjanim_rom.c"

#line 359 "src/modules/uvjanim_rom.c"
/* Resolve each joint track surrounding the normalized animation time,
 * interpolate quaternion/translation/scale channels and emit joint IDs.
 * Preserve optional quaternion normalization, defaults and time wrapping. */
void uvJanimSamplePoseAtNormalizedTime(UnkStruct_UvJanim_rom_00400144 *pose, s32 animationId, f32 normalizedTime) {
    Quat *rotationStorage;
    Quat *outRotation;
    Vec3F *outTranslation;
    Vec3F *outScale;
    UvParsedAN_2 *track;
    s32 followingKey;
    UvParsedAN *parsedAnimationData;
    s32 firstKey;
    s32 secondKey;
    f32 spanOrLength;
    s32 followingKeyTime;
    f32 inverseQuaternionLength;
    f32 firstKeyTime;
    f32 firstWeight;
    f32 secondWeight;
    f32 secondKeyTime;
    s32 pad;
    s32 penultimateKey;
    s32 searchLow;
    s32 searchHigh;
    s32 searchMid;
    s32 foundInterval;
    u16 keyCount;
    u8 *outJointIds;
    Vec3F *secondVector;
    Vec3F *firstVector;
    Quat *secondQuaternion;
    Quat *firstQuaternion;

    parsedAnimationData = uvGetLoadedFile('UVAN', animationId);
    if (parsedAnimationData == NULL) {
        return;
    }

    pose->unk11 = 0;
    spanOrLength = (parsedAnimationData->unk2 - 1);
    if (normalizedTime < 0.0f) {
        normalizedTime = (normalizedTime + 1.0f) - (f32) (s32) normalizedTime;
    }
    if (normalizedTime > 1.0f) {
        normalizedTime -= (f32) (s32) normalizedTime;
    }
    pose->unk11 = parsedAnimationData->unk8[0];
    normalizedTime *= spanOrLength;
    pose->unk10 = 0;
    track = parsedAnimationData->unkC;

    outJointIds = pose->unkC;
    outRotation = pose->unk0;

    outTranslation = pose->unk4;
    outScale = pose->unk8;
    while (track != NULL) {
        keyCount = track->unk6;
        rotationStorage = pose->unk0;
        if (parsedAnimationData->unk2 == keyCount) {
            firstKey = (s32) normalizedTime;
        } else {
            foundInterval = 0;
            searchLow = 0;
            penultimateKey = keyCount - 2;
            if (track->unk8 != NULL) {
                firstKey = track->unk8[(s32) normalizedTime];
            } else {
                searchHigh = penultimateKey;
                while ((searchHigh >= searchLow) && (!foundInterval)) {
                    searchMid = (s32) (searchLow + searchHigh) / 2;
                    followingKeyTime = track->unkC[searchMid + 1];
                    if (((s32) normalizedTime >= track->unkC[searchMid]) && ((s32) normalizedTime < followingKeyTime)) {
                        foundInterval = TRUE;
                    } else if ((s32) normalizedTime < track->unkC[searchMid]) {
                        searchHigh = searchMid - 1;
                    } else {
                        searchLow = searchMid + 1;
                    }
                }

                if (foundInterval) {
                    firstKey = searchMid;
                } else {
                    firstKey = penultimateKey;
                }
            }
        }
        followingKey = firstKey + 1;
        if ((u32)followingKey == keyCount) {
            secondKey = keyCount - 1;
        } else {
            secondKey = followingKey;
        }
        firstKeyTime = track->unkC[firstKey];
        secondKeyTime = track->unkC[secondKey];
        if (secondKeyTime == firstKeyTime) {
            firstWeight = 1.0f;
            secondWeight = 0.0f;
        } else {
            firstWeight = (secondKeyTime - normalizedTime) * (1.0f / (secondKeyTime - firstKeyTime));
            secondWeight = 1.0f - firstWeight;
        }
        if ((track->unk18 != 0) && (rotationStorage != NULL)) {
            firstQuaternion = &track->unk18[firstKey];
            secondQuaternion = &track->unk18[secondKey];
            outRotation->x = (secondQuaternion->x * secondWeight) + (firstQuaternion->x * firstWeight);
            outRotation->y = (secondQuaternion->y * secondWeight) + (firstQuaternion->y * firstWeight);
            outRotation->z = (secondQuaternion->z * secondWeight) + (firstQuaternion->z * firstWeight);
            outRotation->w = (secondQuaternion->w * secondWeight) + (firstQuaternion->w * firstWeight);
            if (track->unk1C[firstKey] != 0) {
                spanOrLength = D_uvjanim_rom_00401760->uvSqrtf(
                    SQ(outRotation->w) + (SQ(outRotation->x) + SQ(outRotation->y) + SQ(outRotation->z)));
                if (spanOrLength != 0.0f) {
                    inverseQuaternionLength = 1.0f / spanOrLength;
                    outRotation->x *= inverseQuaternionLength;
                    outRotation->y *= inverseQuaternionLength;
                    outRotation->z *= inverseQuaternionLength;
                    outRotation->w *= inverseQuaternionLength;
                }
            }
        } else if (rotationStorage != NULL) {
            outRotation->x = 0.0f;
            outRotation->y = 0.0f;
            outRotation->z = 0.0f;
            outRotation->w = 1.0f;
        }
        if ((track->unk10 != 0) && (pose->unk4 != NULL)) {
            firstVector = &track->unk10[firstKey];
            secondVector = &track->unk10[secondKey];
            outTranslation->x = (secondVector->x * secondWeight) + (firstVector->x * firstWeight);
            outTranslation->y = (secondVector->y * secondWeight) + (firstVector->y * firstWeight);
            outTranslation->z = (secondVector->z * secondWeight) + (firstVector->z * firstWeight);
        } else if (pose->unk4 != NULL) {
            outTranslation->x = 0.0f;
            outTranslation->y = 0.0f;
            outTranslation->z = 0.0f;
        }
        if ((track->unk14 != 0) && (pose->unk8 != NULL)) {
            firstVector = &track->unk14[firstKey];
            secondVector = &track->unk14[secondKey];
            outScale->x = (secondVector->x * secondWeight) + (firstVector->x * firstWeight);
            outScale->y = (secondVector->y * secondWeight) + (firstVector->y * firstWeight);
            outScale->z = (secondVector->z * secondWeight) + (firstVector->z * firstWeight);
        } else if (pose->unk8 != NULL) {
            outScale->x = 1.0f;
            outScale->y = 1.0f;
            outScale->z = 1.0f;
        }
        *outJointIds++ = track->unk4;
        outRotation++;
        outTranslation++;
        outScale++;
        pose->unk10++;
        track = track->unk0;
    }
}
#line 513 "src/modules/uvjanim_rom.c"

#line 514 "src/modules/uvjanim_rom.c"
/* Allocate temporary pose channels, evaluate the animation using its
 * two supplied coordinates, then apply it. Missing animations do nothing. */
void uvJanimApplyAnimationGrid(s32 objectId, s32 animationId, f32 first, f32 second) {
    UnkStruct_UvJanim_rom_00400144 pose;
    UvParsedAN *animation;

    animation = uvGetLoadedFile('UVAN', animationId);
    if (animation == NULL) {
        return;
    }

    pose.unk0 = __builtin_alloca(sizeof(Quat) * animation->unk9);
    pose.unk4 = __builtin_alloca(sizeof(Vec3F) * animation->unk9);
    pose.unk8 = __builtin_alloca(sizeof(Vec3F) * animation->unk9);
    pose.unkC = __builtin_alloca(sizeof(u8) * animation->unk9);
    pose.unk12 = animation->unk9;
    pose.unk10 = 0;
    pose.unk11 = 7;
    uvJanimSamplePoseAcrossTwoNormalizedAxes(&pose, animationId, first, second);
    uvJanimApplyPose(objectId, (UnkStruct_UvJanim_rom_00400144 *) &pose);
}
#line 533 "src/modules/uvjanim_rom.c"

// uvJanimPoseGrid
#line 535 "src/modules/uvjanim_rom.c"
/* Flatten the two normalized input coordinates into neighboring row
 * samples of the animation and blend their poses by the row fraction.
 * Preserve stack-allocated channel arrays and the single-frame fallback. */
void uvJanimSamplePoseAcrossTwoNormalizedAxes(UnkStruct_UvJanim_rom_00400144 *pose, s32 animationId, f32 columnPosition, f32 rowPosition) {
    UnkStruct_UvJanim_rom_00400144 firstPose;
    UnkStruct_UvJanim_rom_00400144 secondPose;
    f32 firstSample;
    f32 secondSample;
    UvParsedAN *animation;
    s32 pad;
    s32 secondRow;
    s32 firstRow;

    animation = uvGetLoadedFile('UVAN', animationId);
    if (animation == NULL) {
        return;
    }
    firstPose.unk0 = alloca(sizeof(Quat) * animation->unk9);
    firstPose.unk4 = alloca(sizeof(Vec3F) * animation->unk9);
    firstPose.unk8 = alloca(sizeof(Vec3F) * animation->unk9);
    firstPose.unkC = alloca(sizeof(u8) * animation->unk9);
    firstPose.unk12 = animation->unk9;
    firstPose.unk10 = 0;
    firstPose.unk11 = 7;
    secondPose.unk0 = alloca(sizeof(Quat) * animation->unk9);
    secondPose.unk4 = alloca(sizeof(Vec3F) * animation->unk9);
    secondPose.unk8 = alloca(sizeof(Vec3F) * animation->unk9);
    secondPose.unkC = alloca(sizeof(u8) * animation->unk9);
    secondPose.unk12 = animation->unk9;
    secondPose.unk10 = 0;
    secondPose.unk11 = 7;

    if (columnPosition < 0.0f) {
        columnPosition = (columnPosition + 1.0f) - (s32) columnPosition;
    }
    if (columnPosition > 1.0f) {
        columnPosition -= (s32) columnPosition;
    }
    if (rowPosition < 0.0f) {
        rowPosition = (rowPosition + 1.0f) - (s32) rowPosition;
    }
    if (rowPosition > 1.0f) {
        rowPosition -= (s32) rowPosition;
    }

    firstRow = animation->unk6;
    columnPosition *= firstRow - 1;
    rowPosition *= animation->unk4 - 1;
    firstRow = (s32) rowPosition;
    if (firstRow > animation->unk4 - 1) {
        firstRow = animation->unk4 - 1;
        secondRow = animation->unk4 - 1;
    } else {
        if (firstRow < animation->unk4 - 1) {
            secondRow = firstRow + 1;
        } else {
            secondRow = firstRow;
        }
    }
    firstSample = (f32) (animation->unk6 * firstRow) + columnPosition;
    secondSample = (f32) (animation->unk6 * secondRow) + columnPosition;

    if (animation->unk2 < 2) {
        uvJanimSamplePoseAtNormalizedTime(pose, animationId, 0.0f);
        return;
    }

    uvJanimSamplePoseAtNormalizedTime((UnkStruct_UvJanim_rom_00400144 *) &firstPose, animationId,
                              firstSample / (animation->unk2 - 1));
    uvJanimSamplePoseAtNormalizedTime((UnkStruct_UvJanim_rom_00400144 *) &secondPose, animationId,
                              secondSample / (animation->unk2 - 1));
    uvJanimMergeWeightedPoseChannels(pose, &firstPose, &secondPose, rowPosition - (s32) rowPosition);
}
#line 605 "src/modules/uvjanim_rom.c"

#line 606 "src/modules/uvjanim_rom.c"
/* Extract joint quaternions and joint IDs from the object matrices
 * into the supplied pose arrays, then store the returned count. */
void uvJanimWriteJointMatrices(s32 objectId, UnkStruct_uvjanim_rom_00401704 *pose) {
    s32 rotations;
    s32 jointIds;

    rotations = pose->unk0;
    jointIds = pose->unkC;
    pose->unk10 = D_uvjanim_rom_00401768->uvDobjExtractJointQuaternionsFromMatrices(objectId, rotations, jointIds);
}
#line 614 "src/modules/uvjanim_rom.c"

