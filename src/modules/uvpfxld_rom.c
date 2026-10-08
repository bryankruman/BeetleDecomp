// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern s32 D_uvpfxld_rom_00400EC0;
void uvPfxLoaderCleanup();
void func_uvpfxld_rom_004000DC();
void func_uvpfxld_rom_004002DC();
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
void uvPfxLoaderCopyIntoSharedWordBuffer();
extern s32 D_uvpfxld_rom_00400EC8;
extern UvPfx_Exports *D_uvpfxld_rom_004012F4;
void uvPfxLoaderApplySharedResourceWord(s32 *sourceWord);
void func_uvpfxld_rom_00400CD0();
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

/* Read and dispatch original COMM/TEXT/PIID/PHDR/PDAT particle blocks.
 * UPFX export slots 0x40/0x44/0x48 provide the descriptor-array pointer,
 * capacity and active-count words. Advance the shared active count once per
 * signed configured count while below capacity, publish it, release the reader
 * and return the shared configuration pointer reloaded after that release.
 * RE_ORIGINAL_QUIRK: unrecognized nonzero tags skip this routine's block
 * consumer and free. The original-matching reader allocates nonzero blocks;
 * reader release only clears its file slot. Preserve the observed path.
 * RE_UNKNOWN: original particle asset chunk set/order and COMMON-before-use
 * guarantee, count/capacity domains and returned configuration ownership.
 * Trace original assets and loader callers/allocation lifetimes before adding
 * validation or claiming the unrecognized-tag allocation path is reachable.
 * RE_UNKNOWN: historical declaration/storage organization of actual reader
 * size/data locals. Readable C has identical operations and relocations but
 * different stack homes; retain original assembly without fabricated padding. */
#line 21 "src/modules/uvpfxld_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004000DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_004002DC.s")

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
/* Copy 2*shared-count bytes to the pointer stored at loader+0x30 from the
 * supplied source. RE_UNKNOWN: count units, source/device address and destination
 * extent/alignment need original configuration/buffer producers and media-copy callers. */
void uvPfxLoaderCopyIntoSharedWordBuffer(void *sourceWords) {
    _uvMediaCopy(*(s32 *)((u8 *)D_uvpfxld_rom_00400EE4 + 0x30), sourceWords, D_uvpfxld_rom_00400EC0 * 2);
}
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

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfxld_rom/func_uvpfxld_rom_00400CD0.s")

