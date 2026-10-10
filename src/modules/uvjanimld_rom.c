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
/* Parse COMM blocks into linked animation nodes and optional quaternion,
 * offset-0x10 vector and offset-0x14 vector arrays, preserving entry flags
 * and default component stores. RE_UNKNOWN: historical field meanings,
 * complete input format and caller/storage lifetimes remain unproved. */
#line 21 "src/modules/uvjanimld_rom.c"
UvParsedAN *func_uvjanimld_rom_00400050(u8 *fileData) {
    UvParsedAN *animation; /* RE_ORIGINAL_QUIRK: no COMM leaves this result uninitialized; RE_UNKNOWN: permitted block sequence. */
    UvParsedAN_2 *newNode;
    s32 lookupIndex;
    u32 blockBytes; /* RE_UNKNOWN: stream bounds and provider failure contracts. */
    void *blockData;
    void *commBlock;
    s32 fileId;
    s32 nodeIndex;
    UvParsedAN_2 *tailNode;
    u32 blockTag;
    void *cursor;
    s32 entryIndex;
    u8 channelFlags;
    s32 hasVector10Entry, hasVector14Entry, hasQuaternionEntry;
    u16 packedEntry;

    tailNode = NULL; /* RE_ORIGINAL_QUIRK: the tail persists across COMM blocks. */
    fileId = uvFileReadHeader(fileData);
    while ((blockTag = uvFileReadBlock(fileId, &blockBytes, &blockData, 1)) != 0) {
        switch (blockTag) {
            case 'COMM':
                commBlock = blockData;
                cursor = blockData;
                animation = _uvMemAllocAlign8(sizeof(UvParsedAN)); /* RE_UNKNOWN: allocation failure and partial-result ownership. */
                uvConsumeBytes(&animation->unk0, (u8 **) &cursor, sizeof(u16));
                uvConsumeBytes(&animation->unk2, (u8 **) &cursor, sizeof(u16));
                uvConsumeBytes(&animation->unk4, (u8 **) &cursor, sizeof(u16));
                uvConsumeBytes(animation->unk8, (u8 **) &cursor, sizeof(u8));
                uvConsumeBytes(&animation->unk9, (u8 **) &cursor, sizeof(u8));
                animation->unk6 = animation->unk2 / animation->unk4; /* RE_UNKNOWN: divisor validity; retain native divide/trap behavior. */
                for (nodeIndex = 0; nodeIndex < animation->unk9; nodeIndex++) {
                    newNode = _uvMemAllocAlign8(sizeof(UvParsedAN_2));
                    if (tailNode != NULL) {
                        tailNode->unk0 = newNode;
                        tailNode = newNode;
                    } else {
                        tailNode = newNode;
                        animation->unkC = newNode;
                    }
                    uvConsumeBytes(&tailNode->unk6, (u8 **) &cursor, sizeof(u16));
                    uvConsumeBytes(&tailNode->unk4, (u8 **) &cursor, sizeof(u16));
                    uvConsumeBytes(&channelFlags, (u8 **) &cursor, sizeof(u8));
                    tailNode->unk10 = NULL;
                    tailNode->unk0 = NULL;
                    tailNode->unk18 = NULL;
                    tailNode->unk14 = NULL;
                    tailNode->unk8 = 0;
                    tailNode->unk1C = NULL;
                    tailNode->unkC = _uvMemAllocAlign8(tailNode->unk6 * sizeof(u16));
                    if (channelFlags & 1) {
                        tailNode->unk18 = _uvMemAllocAlign8(tailNode->unk6 * sizeof(Quat));
                        tailNode->unk1C = _uvMemAllocAlign8(tailNode->unk6);
                    }
                    if (channelFlags & 2) {
                        tailNode->unk10 = _uvMemAllocAlign8(tailNode->unk6 * sizeof(Vec3F));
                    }
                    if (channelFlags & 4) {
                        tailNode->unk14 = _uvMemAllocAlign8(tailNode->unk6 * sizeof(Vec3F));
                    }
                    for (entryIndex = 0; entryIndex < tailNode->unk6; entryIndex++) {
                        uvConsumeBytes(&packedEntry, (u8 **) &cursor, sizeof(u16));
                        if (tailNode->unk1C != NULL) {
                            tailNode->unk1C[entryIndex] = (packedEntry & 0x8000) != 0;
                        }
                        hasQuaternionEntry = (packedEntry & 0x4000) != 0;
                        hasVector10Entry = (packedEntry & 0x2000) != 0;
                        hasVector14Entry = (packedEntry & 0x1000) != 0;
                        tailNode->unkC[entryIndex] = packedEntry & 0xFFF;
                        if (hasQuaternionEntry) { /* RE_UNKNOWN: entry bits must agree with allocated channel arrays. */
                            uvConsumeBytes(&tailNode->unk18[entryIndex].x, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk18[entryIndex].y, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk18[entryIndex].z, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk18[entryIndex].w, (u8 **) &cursor, sizeof(f32));
                        } else {
                            if (tailNode->unk18 != NULL) {
                                tailNode->unk18[entryIndex].x = 0.0f;
                                tailNode->unk18[entryIndex].y = 0.0f;
                                tailNode->unk18[entryIndex].z = 0.0f;
                                tailNode->unk18[entryIndex].w = 1.0f;
                            }
                        }
                        if (hasVector10Entry) {
                            uvConsumeBytes(&tailNode->unk10[entryIndex].x, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk10[entryIndex].y, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk10[entryIndex].z, (u8 **) &cursor, sizeof(f32));
                        } else {
                            if (tailNode->unk10 != NULL) {
                                tailNode->unk10[entryIndex].x = 0.0f;
                                tailNode->unk10[entryIndex].y = 0.0f;
                                tailNode->unk10[entryIndex].z = 0.0f;
                            }
                        }
                        if (hasVector14Entry) {
                            uvConsumeBytes(&tailNode->unk14[entryIndex].x, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk14[entryIndex].y, (u8 **) &cursor, sizeof(f32));
                            uvConsumeBytes(&tailNode->unk14[entryIndex].z, (u8 **) &cursor, sizeof(f32));
                        } else {
                            if (tailNode->unk14 != NULL) {
                                tailNode->unk14[entryIndex].x = 1.0f;
                                tailNode->unk14[entryIndex].y = 1.0f;
                                tailNode->unk14[entryIndex].z = 1.0f;
                            }
                        }
                    }
                    if (tailNode->unk8 != NULL) { /* RE_ORIGINAL_QUIRK: +8 was cleared above; RE_UNKNOWN: reachability. */
                        for (lookupIndex = 0, entryIndex = 0; lookupIndex < animation->unk2; lookupIndex++) {
                            while (lookupIndex >= tailNode->unkC[entryIndex + 1] && (entryIndex + 1) < tailNode->unk6) { /* RE_ORIGINAL_QUIRK: read precedes bounds test; RE_UNKNOWN: sentinel/capacity. */
                                entryIndex++;
                            }
                            tailNode->unk8[lookupIndex] = entryIndex;
                        }
                    }
                }
                _uvMemFree(commBlock); /* RE_UNKNOWN: ownership of ignored block payloads. */
                break;
        }
    }
    uvFileFree(fileId);
    return animation;
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

