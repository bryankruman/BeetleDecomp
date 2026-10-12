// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
/* RE_UNKNOWN: observed widths/offsets only; unk field meanings unresolved. ASM owns storage. */
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
#include "uvpfx_rom.h"
#include "uvtseq_rom.h"
typedef struct PfxLoaderSecondaryView_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ char pad2[2];
    /* 0x04 */ void* unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ char pad16[2];
    /* 0x18 */ f32 unk18;
} PfxLoaderSecondaryView;
typedef struct PfxLoaderCommonView_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ char pad15[1];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char pad26[2];
    /* 0x28 */ PfxLoaderSecondaryView *unk28;
    /* 0x2C */ UnkStruct_uvpfx_rom_00404FA0_unk2C *unk2C;
    /* 0x30 */ s16 *unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} PfxLoaderCommonView;
typedef struct UVPXData_s {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
} UVPXData;
void uvPfxLoaderSetConfigShortFromWord(void *);
extern f32 D_uvpfxld_rom_00400EA8[4];
extern UvFMtx_Rom_Exports *D_uvpfxld_rom_004012E8;
extern UvTSeq_Exports *D_uvpfxld_rom_004012EC;
extern UvFVec_Rom_Exports *D_uvpfxld_rom_004012F0;
/* Original readonly float words at module offsets 0xE90 and 0xE94. */
extern f32 D_uvpfxld_rom_00400E90;
extern f32 D_uvpfxld_rom_00400E94;
#line 3 "src/modules/uvpfxld_rom.c"
extern s32 D_uvpfxld_rom_00400EC0;
void uvPfxLoaderCleanup();
void *uvPfxLoaderParseChunkStream(u8 *);
void uvPfxLoaderBuildCommonParticleRecords(UVPXData *);
#include "uvfvec_rom.h"
#include "uvfmtx_rom.h"
#include "uvpfx_rom.h"
/* Observed PHDR input fields; the native reader consumes at least 24 bytes. */
typedef struct {
    s32 vectorCount;
    f32 defaultStateScalar;
    s32 value08;
    f32 reciprocalSource;
    s32 secondaryKind;
    s32 copyItemCount;
} PfxLoaderHeaderFields;
/* Prefix view of the original 0x3C-byte COMMON allocation. The omitted
 * fields retain their unknown meanings; no allocation capacity is inferred. */
typedef struct {
    s16 particleCount;
    u8 unk02[0xE];
    s16 vectorCount;
    u8 unk12[0x1A];
    UnkStruct_uvpfx_rom_00404FA0_unk2C *secondary;
    s16 *sharedWordBuffer;
} PfxLoaderHeaderConfig;
extern s32 D_uvpfxld_rom_00400EB8;
extern s32 D_uvpfxld_rom_00400EBC;
extern s32 D_uvpfxld_rom_00400EC4;
extern UnkStruct_uvpfx_rom_00404FA0 *D_uvpfxld_rom_00400EE0;
extern UnkStruct_uvpfx_rom_00404FA0_unk4 *D_uvpfxld_rom_00400EE8[];
void uvPfxLoaderApplyHeaderConfiguration(PfxLoaderHeaderFields *header);
void uvPfxLoaderCopyIntoSharedWordBuffer(void *);
extern s32 D_uvpfxld_rom_00400EC8;
extern UvPfx_Exports *D_uvpfxld_rom_004012F4;
void uvPfxLoaderApplySharedResourceWord(s32 *sourceWord);
void uvPfxLoaderReleaseConfiguration(UnkStruct_uvpfx_rom_00404FA0_unk0 *);
extern void *D_uvpfxld_rom_00400EE4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/__entrypoint_func_uvpfxld_rom_400000.s")

#line 14 "src/modules/uvpfxld_rom.c"
/* Unload TSEQ, FMTX, FVEC and UPFX dependencies in their original order. */
void uvPfxLoaderCleanup(void) {
    uvUnloadModule('TSEQ');
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('UPFX');
}
#line 20 "src/modules/uvpfxld_rom.c"

/* Dispatch COMM/TEXT/PIID/PHDR/PDAT blocks through the existing loader helpers.
 * Publish the bounded active-count increments and reload the shared result
 * after reader release. RE_ORIGINAL_QUIRK: unknown nonzero blocks skip this
 * routine's consumer and free. RE_UNKNOWN: valid chunk order and ownership. */
#line 21 "src/modules/uvpfxld_rom.c"
void *uvPfxLoaderParseChunkStream(u8 *chunkStream) {
    void *blockData;
    s32 reader;
    s32 particleIndex;
    u32 blockBytes;
    void *readBlockData;
    u32 blockTag;

    D_uvpfxld_rom_00400EB8 = *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA8;
    D_uvpfxld_rom_00400EBC = *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA4;
    D_uvpfxld_rom_00400EE0 = *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA0;
    reader = uvFileReadHeader(chunkStream);
    while (blockTag = uvFileReadBlock(reader, &blockBytes, &readBlockData, 1)) {
        switch (blockTag) {
            case 'COMM':
                blockData = readBlockData;
                uvPfxLoaderBuildCommonParticleRecords(blockData);
                _uvMemFree(blockData);
                break;
            case 'TEXT':
                blockData = readBlockData;
                uvPfxLoaderApplySharedResourceWord(blockData);
                _uvMemFree(blockData);
                break;
            case 'PIID':
                blockData = readBlockData;
                uvPfxLoaderSetConfigShortFromWord(blockData);
                _uvMemFree(blockData);
                break;
            case 'PHDR':
                blockData = readBlockData;
                uvPfxLoaderApplyHeaderConfiguration(blockData);
                _uvMemFree(blockData);
                break;
            case 'PDAT':
                blockData = readBlockData;
                uvPfxLoaderCopyIntoSharedWordBuffer(blockData);
                _uvMemFree(blockData);
                break;
        }
    }

    for (particleIndex = 0; particleIndex < ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk0; particleIndex++) {
        if (D_uvpfxld_rom_00400EB8 < D_uvpfxld_rom_00400EBC) {
            D_uvpfxld_rom_00400EB8++;
        }
    }
    *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA8 = D_uvpfxld_rom_00400EB8;
    uvFileFree(reader);
    return D_uvpfxld_rom_00400EE4;
}
#line 22 "src/modules/uvpfxld_rom.c"

/* Allocate and publish shared/per-particle records, then apply original UPFX
 * properties and FMTX/FVEC initialization with unchanged float promotions.
 * RE_ORIGINAL_QUIRK: capacity failure frees only the shared record without
 * clearing its pointer or releasing earlier published particles. The kind-2
 * path leaves shared+0x30 untouched; another path allocates count*4 bytes then
 * copies 16 bytes unconditionally. RE_UNKNOWN: asset domains and ownership.
 * Unused compiler declarations temp_v0_2, temp_a0, temp_v0 and temp are
 * preserved; their intended source roles remain unknown. */
#line 23 "src/modules/uvpfxld_rom.c"
void uvPfxLoaderBuildCommonParticleRecords(UVPXData *properties) {
    UnkStruct_uvpfx_rom_00404FA0_unk4 *temp_v0_2;
    s16 *temp_a0;
    s16 *temp_v0;
    s32 particleIndex;
    s32 temp;

    D_uvpfxld_rom_00400EC8 = properties->unk14;
    D_uvpfxld_rom_00400EE4 = _uvMemAllocAlign8(sizeof(UnkStruct_uvpfx_rom_00404FA0_unk0));
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk0 = properties->unk8;

    for (particleIndex = 0; particleIndex < ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk0; particleIndex++) {
        if ((D_uvpfxld_rom_00400EB8 + particleIndex) < D_uvpfxld_rom_00400EBC) {
            /* Publish per-particle and shared records. */
            D_uvpfxld_rom_00400EE8[particleIndex] = _uvMemAllocAlign8(sizeof(UnkStruct_uvpfx_rom_00404FA0_unk4));
            D_uvpfxld_rom_00400EE0[D_uvpfxld_rom_00400EB8 + particleIndex].unk4 = D_uvpfxld_rom_00400EE8[particleIndex];
            D_uvpfxld_rom_00400EE0[D_uvpfxld_rom_00400EB8 + particleIndex].unk0 =
                (UnkStruct_uvpfx_rom_00404FA0_unk0 *) D_uvpfxld_rom_00400EE4;
            continue;
        }
        _uvMemFree(D_uvpfxld_rom_00400EE4);
        return;
    }
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk1E = 3;
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk34 = 1.0f;
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk24 = properties->unk18;
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk6 = properties->unk4;
    if (((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk24 == 0) {
        properties->unk30 = 1.0f;
    }
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unkC = 0x1F560000;
    ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk8 = 0xA00000;
    if (properties->unk0 == 0) {
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk4 = 2;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk2C = _uvMemAllocAlign8(0x10U);
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28 = NULL;
    } else {
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk4 = 1;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk2C = NULL;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk30 = 0;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28 = _uvMemAllocAlign8(0x1CU);
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk10 = properties->unk38;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk0 = properties->unk3C;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk18 = properties->unk34;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk8 = 4;
        ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk4 =
            _uvMemAllocAlign8(((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk0 * 4);
        _uvMediaCopy(((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk4, D_uvpfxld_rom_00400EA8,
                     sizeof(f32) * ARRAY_COUNT(D_uvpfxld_rom_00400EA8));
        D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(
            D_uvpfxld_rom_00400EB8, 0x4027, properties->unk2C, 0x4029, properties->unk30, 0x4026, properties->unk50,
            properties->unk54, properties->unk58, properties->unk5C, 0x1019, 300.0f, 0x1003, properties->unk1C, properties->unk20,
            properties->unk24, 0);
    }
    D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(
        D_uvpfxld_rom_00400EB8, 0x1022, 20.0f, 0x1023, properties->unk28, 0x1005, properties->unk40, properties->unk44,
        properties->unk48, properties->unk4C, 0x1008, 0xFFF, 0x1013, 0xFF, 0);
    for (particleIndex = 0; particleIndex < ((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk0; particleIndex++) {
        if ((D_uvpfxld_rom_00400EB8 + particleIndex) < D_uvpfxld_rom_00400EBC) {
            D_uvpfxld_rom_00400EE8[particleIndex]->unk28 = 0xFF;
            if (D_uvpfxld_rom_00400EC8 == 2) {
                D_uvpfxld_rom_00400EE8[particleIndex]->unk2A = 2;
            } else {
                D_uvpfxld_rom_00400EE8[particleIndex]->unk2A = 1;
            }
            D_uvpfxld_rom_00400EE8[particleIndex]->unk2C = 0xFFF;
            D_uvpfxld_rom_00400EE8[particleIndex]->unk4 = 0.0f;
            if (properties->unkC == 1) {
                D_uvpfxld_rom_00400EE8[particleIndex]->unk10 = D_uvpfxld_rom_00400E90;
            } else {
                D_uvpfxld_rom_00400EE8[particleIndex]->unk10 = properties->unk10;
            }
            D_uvpfxld_rom_00400EE8[particleIndex]->unkC = D_uvpfxld_rom_00400E94;
            D_uvpfxld_rom_00400EE8[particleIndex]->unk24 = 0;
            D_uvpfxld_rom_00400EE8[particleIndex]->unk6E = 0;
            D_uvpfxld_rom_00400EE8[particleIndex]->unkE4 = 0;
            D_uvpfxld_rom_004012E8->uvMat4SetIdentity(&D_uvpfxld_rom_00400EE8[particleIndex]->unk80);
            D_uvpfxld_rom_004012F0->uvVec3FSet(&D_uvpfxld_rom_00400EE8[particleIndex]->unkC0, 0.0f, 0.0f, 0.0f);
            D_uvpfxld_rom_004012F0->uvVec3FSet((Vec3F *)&D_uvpfxld_rom_00400EE8[particleIndex]->unkCC, 0.0f, 0.0f, 0.0f);
            D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(D_uvpfxld_rom_00400EB8 + particleIndex, 0x1007, 1.0f,
                                                            0x1020, 0, 0x1019, 300.0f, 0x1003,
                                                            properties->unk1C, properties->unk20, properties->unk24, 0);
            if (properties->unk0 == 1) {
                D_uvpfxld_rom_00400EE8[particleIndex]->unk22 = -1;
                D_uvpfxld_rom_00400EE8[particleIndex]->unk14 = 0 /*.0f*/;
                D_uvpfxld_rom_00400EE8[particleIndex]->unk18 = 0.5f;
                D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(
                    D_uvpfxld_rom_00400EB8 + particleIndex, 0x4033, properties->unk60, properties->unk64, properties->unk68, 0);
                D_uvpfxld_rom_00400EE0[D_uvpfxld_rom_00400EB8 + particleIndex].unk8 =
                    _uvMemAllocAlign8(((PfxLoaderCommonView *)D_uvpfxld_rom_00400EE4)->unk28->unk0 * 0xC);
            }
        }
    }
}
#line 24 "src/modules/uvpfxld_rom.c"
#line 24 "src/modules/uvpfxld_rom.c"

#line 25 "src/modules/uvpfxld_rom.c"

/* Apply the original PHDR block to shared loader configuration and each
 * configured particle. Allocate the two-byte item buffer, preserve short
 * narrowing and reciprocal arithmetic, and allocate Vec3F storage only for
 * secondary kind 9. A nonzero state scalar keeps its original value.
 * RE_UNKNOWN: physical scalar units, value08/secondary-kind meanings and
 * caller guarantees for reciprocalSource, counts and block ordering. Trace
 * original PHDR assets and the COMMON producer before changing arithmetic,
 * bounds or initialization. The COMMON allocation and particle-state table
 * must already exist on this path; their lifetime/aliasing contracts remain
 * unresolved. Preserve reloads across original allocations and mutations. */
void uvPfxLoaderApplyHeaderConfiguration(PfxLoaderHeaderFields *header) {
    s32 index;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *particleState;

    D_uvpfxld_rom_00400EC0 = header->copyItemCount;
    D_uvpfxld_rom_00400EC4 = header->secondaryKind;
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->sharedWordBuffer =
        _uvMemAllocAlign8(header->copyItemCount * 2);
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->vectorCount = header->vectorCount;
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->secondary->unk0 = header->secondaryKind;
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->secondary->unk8 = header->value08;
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->secondary->unkC = header->defaultStateScalar;
    ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->secondary->unk4 = 1.0f / header->reciprocalSource;
    for (index = 0; index < ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->particleCount; index++) {
        if (D_uvpfxld_rom_00400EB8 + index < D_uvpfxld_rom_00400EBC) {
            particleState = D_uvpfxld_rom_00400EE8[index];
            if (particleState->unk10 == 0.0f) {
                particleState->unk10 = header->defaultStateScalar;
            }
            if (header->secondaryKind == 9) {
                D_uvpfxld_rom_00400EE0[D_uvpfxld_rom_00400EB8 + index].unk8 =
                    _uvMemAllocAlign8(((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->vectorCount * sizeof(Vec3F));
            } else {
                D_uvpfxld_rom_00400EE0[D_uvpfxld_rom_00400EB8 + index].unk8 = NULL;
            }
        }
    }
}
#line 26 "src/modules/uvpfxld_rom.c"

#line 27 "src/modules/uvpfxld_rom.c"
/* Copy sharedCount*2 bytes to the address stored at shared configuration offset
 * 0x30. The reviewed header-configuration producer allocates the same count*2
 * byte size; this wrapper independently reads the current shared count and pointer.
 * RE_UNKNOWN: valid signed counts, overflow, capacity, producer-before-copy order
 * and source/destination lifetime are unproved. Preserve the raw destination word
 * and arithmetic; the historical word-buffer name does not establish element type. */
#line 30 "src/modules/uvpfxld_rom.c"
void uvPfxLoaderCopyIntoSharedWordBuffer(void *sourceWords) {
    _uvMediaCopy(*(s32 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x30), sourceWords, D_uvpfxld_rom_00400EC0 * 2);
}
#line 33 "src/modules/uvpfxld_rom.c"
#line 30 "src/modules/uvpfxld_rom.c"

#line 31 "src/modules/uvpfxld_rom.c"

/* Apply one caller-word snapshot to every configured particle. The original
 * shared selector chooses property 0x1008 (UVTX-ID path) or 0x1013 (TSEQ path).
 * Preserve the signed count and shared selector/base/export reloads across
 * each variadic setter, including any original callbacks/module calls.
 * RE_UNKNOWN: valid configured count/base IDs, meaning of the selector mode
 * and caller-word resource/lifetime guarantees. Trace loader configuration,
 * particle allocation and original callback callers before adding validation
 * or interpreting the mode. The complete historical pointer declaration is
 * unknown; this view describes the observed aligned 32-bit input-word read. */
void uvPfxLoaderApplySharedResourceWord(s32 *sourceWord) {
    s32 index;
    s32 resourceWord;

    resourceWord = *sourceWord;
    for (index = 0; index < ((PfxLoaderHeaderConfig *)D_uvpfxld_rom_00400EE4)->particleCount; index++) {
        if (D_uvpfxld_rom_00400EC8 == 0) {
            D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(
                D_uvpfxld_rom_00400EB8 + index, 0x1008, resourceWord, 0);
        } else {
            D_uvpfxld_rom_004012F4->func_uvpfx_rom_004004D0(
                D_uvpfxld_rom_00400EB8 + index, 0x1013, resourceWord, 0);
        }
    }
}
#line 32 "src/modules/uvpfxld_rom.c"

#line 33 "src/modules/uvpfxld_rom.c"
/* Read the supplied word and narrow it into loader short+2. RE_UNKNOWN: source
 * and loader storage/lifetime need original configuration producers and callers. */
void uvPfxLoaderSetConfigShortFromWord(void *sourceWord) {
    *(s16 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x2) = *(s32 *)sourceWord;
}
#line 36 "src/modules/uvpfxld_rom.c"

/* Remove every descriptor belonging to the supplied configuration, shifting
 * the remaining descriptor words after each removal. Publish the final count,
 * then free the original nested buffers and shared configuration in order.
 * RE_UNKNOWN: alias lifetimes and allocation-failure guarantees remain held. */
#line 37 "src/modules/uvpfxld_rom.c"
void uvPfxLoaderReleaseConfiguration(UnkStruct_uvpfx_rom_00404FA0_unk0 *configuration) {
    s32 descriptorIndex;
    s32 shiftIndex;

    D_uvpfxld_rom_00400EB8 = *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA8;
    D_uvpfxld_rom_00400EE0 = *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA0;

    for (descriptorIndex = 0; descriptorIndex < D_uvpfxld_rom_00400EB8; descriptorIndex++) {
        if (configuration == D_uvpfxld_rom_00400EE0[descriptorIndex].unk0) {
            if (D_uvpfxld_rom_00400EE0[descriptorIndex].unk8 != NULL) {
                _uvMemFree(D_uvpfxld_rom_00400EE0[descriptorIndex].unk8);
            }
            _uvMemFree(D_uvpfxld_rom_00400EE0[descriptorIndex].unk4);
            if (D_uvpfxld_rom_00400EB8 >= 2) {
                D_uvpfxld_rom_00400EB8--;
                for (shiftIndex = descriptorIndex; shiftIndex < D_uvpfxld_rom_00400EB8; shiftIndex++) {
                    D_uvpfxld_rom_00400EE0[shiftIndex].unk0 = D_uvpfxld_rom_00400EE0[shiftIndex + 1].unk0;
                    D_uvpfxld_rom_00400EE0[shiftIndex].unk4 = D_uvpfxld_rom_00400EE0[shiftIndex + 1].unk4;
                    D_uvpfxld_rom_00400EE0[shiftIndex].unk8 = D_uvpfxld_rom_00400EE0[shiftIndex + 1].unk8;
                }
                descriptorIndex--;
            } else {
                D_uvpfxld_rom_00400EB8 = 0;
            }
        }
    }

    *D_uvpfxld_rom_004012F4->D_uvpfx_rom_00404FA8 = D_uvpfxld_rom_00400EB8;
    if (configuration->unk2C != NULL) {
        _uvMemFree(configuration->unk2C);
    }
    if (configuration->unk28 != NULL) {
        void *secondaryValues = ((PfxLoaderSecondaryView *)configuration->unk28)->unk4;
        if (secondaryValues != NULL) {
            _uvMemFree(secondaryValues);
        }
        _uvMemFree(configuration->unk28);
    }
    if (configuration->unk30 != NULL) {
        _uvMemFree(configuration->unk30);
    }
    _uvMemFree(configuration);
}
#line 38 "src/modules/uvpfxld_rom.c"

