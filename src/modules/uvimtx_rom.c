// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#define IMTX_STACK_SIZE 100

// RE_UNKNOWN: these partial GMGR/CBCK export views need complete original initializer, provider and caller evidence before assigning full historical declarations.
typedef struct UnkStruct_00400764_s {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void (*unk10)(s32, void (*)(s32), s32, s32); /* inferred */
    /* 0x14 */ void (*unk14)(s32, s32);
} UnkStruct_00400764;                               /* size = 0x18 */

typedef struct UnkStruct_00400760_s {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ Gfx **(*unk8)(void);                    /* inferred */
    /* 0x0C */ char padC[4];
    /* 0x10 */ s32 (*unk10)(s32);
} UnkStruct_00400760;                               /* size = 0x14 */

extern UnkStruct_00400760 *sUvGfxMgrExports_imtx;
extern UnkStruct_00400764 *sUvCbckExports;
extern void *D_uvimtx_rom_00400774;
extern s32 sRspMatricesCount[];
extern s32 sNonLoadedMatricesCount[];
extern s32 sUnusedArray1[];
extern s32 sUnusedArray2[];
extern s16 sIMtxTick;
extern s16 sIMtxStackIdx;
extern s16 sIMtxStackSize;
extern Mtx* sMatrixStack[];

void __entrypoint_func_uvimtx_rom_400000(UvImtx_Rom_Exports *arg0);
void uvIMtxModuleCleanup(void);
void uvIMtxStackInit(s32 arg0);
void uvIMtxStackInit(s32 arg0);
void uvIMtxCopy(Mtx *dst, Mtx src);
void uvIMtxSetIdentity(Mtx *m);
void uvImtxStub(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvIMtxCopyTransposedOffDiagonal3x3(uvMtx *dst, uvMtx src);
void uvIMtxLoadModelview(Mtx mtx);
void uvGfxMtxViewPop(void);
void uvIMtxLoadProjection(Mtx mtx);
Mtx *uvIMtxPush(Mtx arg0, u16 arg16);
void uvIMtxSubmitMatrix(Mtx *arg0, u16 arg1);
void uvIMtxSubmitMatrix(Mtx *arg0, u16 arg1);
s32 uvIMtxGetOtherBufferValue(s32 arg0);

void __entrypoint_func_uvimtx_rom_400000(UvImtx_Rom_Exports* arg0) {
    s16* stackSize;

    uvUpdateFileAllocPtr((s32) arg0);
    arg0->uvIMtxModuleCleanup = uvIMtxModuleCleanup;
    arg0->uvIMtxGetOtherBufferValue = uvIMtxGetOtherBufferValue;
    arg0->uvIMtxCopy = uvIMtxCopy;
    arg0->uvIMtxSetIdentity = uvIMtxSetIdentity;
    arg0->uvImtxStub = uvImtxStub;
    arg0->uvIMtxCopyTransposedOffDiagonal3x3 = uvIMtxCopyTransposedOffDiagonal3x3;
    arg0->uvIMtxLoadModelview = uvIMtxLoadModelview;
    arg0->uvGfxMtxViewPop = uvGfxMtxViewPop;
    arg0->uvIMtxLoadProjection = uvIMtxLoadProjection;
    arg0->uvIMtxPush = uvIMtxPush;
    arg0->uvIMtxSubmitMatrix = uvIMtxSubmitMatrix;
    stackSize = uvGetSystemProp(8);
    if (stackSize == NULL) {
        sIMtxStackSize = IMTX_STACK_SIZE;
    } else {
        if (*stackSize != 0) {
            sIMtxStackSize = *stackSize;
        } else {
            sIMtxStackSize = IMTX_STACK_SIZE;
        }
    }
    sUvGfxMgrExports_imtx = uvLoadModule('GMGR');
    sUvCbckExports = uvLoadModule('CBCK');

    // Request two buffers using the signed stack count * sizeof(Mtx), passing 16 to each allocator call. RE_UNKNOWN: valid count domains, allocator outcomes, actual extents/lifetimes and callback scheduling need property writers, allocation and frame consumers.
    *sMatrixStack = _uvMemAlloc(sIMtxStackSize * sizeof(Mtx), 4 * 4);
    D_uvimtx_rom_00400774 = _uvMemAlloc(sIMtxStackSize * sizeof(Mtx), 4 * 4);
    sUvCbckExports->unk10(sUvGfxMgrExports_imtx->unk10(1), uvIMtxStackInit, 0, 0);
}


#line 84 "src/modules/uvimtx_rom.c"
/* Free both matrix buffers, remove the stack-reset callback and unload
 * graphics-manager and callback modules in original order. */
void uvIMtxModuleCleanup(void) {
    _uvMemFree(*sMatrixStack);
    _uvMemFree(D_uvimtx_rom_00400774);
    sUvCbckExports->unk14(sUvGfxMgrExports_imtx->unk10(1), &uvIMtxStackInit);
    uvUnloadModule('GMGR');
    uvUnloadModule('CBCK');
}
#line 91 "src/modules/uvimtx_rom.c"

#line 92 "src/modules/uvimtx_rom.c"
/* Select the other matrix-buffer bank, clear its submission counters
 * and reset the stack cursor. Preserve the unused callback argument. */
void uvIMtxStackInit(s32 unusedCallbackValue) {
    sIMtxTick ^= 1;
    sRspMatricesCount[sIMtxTick] = 0;
    sNonLoadedMatricesCount[sIMtxTick] = 0;
    sIMtxStackIdx = 0;
}
#line 98 "src/modules/uvimtx_rom.c"

#line 99 "src/modules/uvimtx_rom.c"

/* Copy all sixteen original packed words from the by-value matrix in row
 * order. Preserve the by-value source ABI and interleaved loads/stores,
 * rather than substituting a pointer or memory-copy call.
 * RE_UNKNOWN: destination validity and native caller overlap guarantees need
 * the original call sites; this leaf does not establish an allocation bound. */
void uvIMtxCopy(Mtx* dst, Mtx src) {
    dst->m[0][0] = src.m[0][0];
    dst->m[0][1] = src.m[0][1];
    dst->m[0][2] = src.m[0][2];
    dst->m[0][3] = src.m[0][3];
    dst->m[1][0] = src.m[1][0];
    dst->m[1][1] = src.m[1][1];
    dst->m[1][2] = src.m[1][2];
    dst->m[1][3] = src.m[1][3];
    dst->m[2][0] = src.m[2][0];
    dst->m[2][1] = src.m[2][1];
    dst->m[2][2] = src.m[2][2];
    dst->m[2][3] = src.m[2][3];
    dst->m[3][0] = src.m[3][0];
    dst->m[3][1] = src.m[3][1];
    dst->m[3][2] = src.m[3][2];
    dst->m[3][3] = src.m[3][3];
}
#line 117 "src/modules/uvimtx_rom.c"

void uvIMtxSetIdentity(Mtx* output) { /* Write the original sixteen packed words in order. RE_UNKNOWN: writable span, alignment/lifetime and historical packed-layout declaration need original callers and storage producers. */
    output->m[0][0] = 0x10000;
    output->m[0][1] = 0;
    output->m[0][2] = 1;
    output->m[0][3] = 0;
    output->m[1][1] = 0x10000;
    output->m[1][0] = 0;
    output->m[1][3] = 1;
    output->m[1][2] = 0;
    output->m[2][0] = 0;
    output->m[2][1] = 0;
    output->m[2][2] = 0;
    output->m[2][3] = 0;
    output->m[3][0] = 0;
    output->m[3][1] = 0;
    output->m[3][2] = 0;
    output->m[3][3] = 0;
}

void uvImtxStub(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

}

#line 141 "src/modules/uvimtx_rom.c"

/* Copy only the six off-diagonal entries of the upper 3x3 area from the
 * by-value fixed-point matrix. Transpose integer and fractional halfwords
 * separately; diagonal entries and the fourth row/column remain untouched.
 * RE_ORIGINAL_QUIRK: when destination equals the by-value argument's address,
 * stores are redirected to a local matrix. The later copy-back test compares
 * that chosen output with the argument address, rather than the destination.
 * Preserve both original tests and the partial local matrix initialization.
 * RE_UNKNOWN: original caller alias guarantees, intended partial-matrix use,
 * and whether the special address equality is reachable require native callers.
 * Do not treat the helper as a full transpose or invent a repaired copy-back. */
void uvIMtxCopyTransposedOffDiagonal3x3(uvMtx* dst, uvMtx src) {
    uvMtx* sourceAddress = &src;
    uvMtx* output = dst;
    Mtx temporaryMatrix;

    if (dst == sourceAddress) {
        output = (uvMtx*)&temporaryMatrix;
    }

    output->u.i[0][1] = src.u.i[1][0];
    output->u.i[0][2] = src.u.i[2][0];
    output->u.i[1][0] = src.u.i[0][1];
    output->u.i[1][2] = src.u.i[2][1];
    output->u.i[2][0] = src.u.i[0][2];
    output->u.i[2][1] = src.u.i[1][2];
    output->u.f[0][1] = src.u.f[1][0];
    output->u.f[0][2] = src.u.f[2][0];
    output->u.f[1][0] = src.u.f[0][1];
    output->u.f[1][2] = src.u.f[2][1];
    output->u.f[2][0] = src.u.f[0][2];
    output->u.f[2][1] = src.u.f[1][2];

    if (sourceAddress == output) {
        uvIMtxCopy((Mtx*)dst, temporaryMatrix);
    }
}
#line 167 "src/modules/uvimtx_rom.c"

#line 168 "src/modules/uvimtx_rom.c"
/* Copy the supplied fixed-point matrix into the original stack and
 * submit it with the model-view load flags. Preserve ignored push failure. */
void uvIMtxLoadModelview(Mtx mtx) {
    uvIMtxPush(mtx, G_MTX_LOAD);
}
#line 171 "src/modules/uvimtx_rom.c"

void uvGfxMtxViewPop(void) {
    Gfx** displayList; /* Obtain the shared cursor and append the original model-view pop command. RE_UNKNOWN: writable command span, provider lifetime and valid pop depth need command allocation, frame scheduling and original callers. */

    displayList = sUvGfxMgrExports_imtx->unk8();

    gSPPopMatrix((*displayList)++, G_MTX_MODELVIEW);
}

#line 180 "src/modules/uvimtx_rom.c"
/* Copy the supplied fixed-point matrix into the original stack and
 * submit it with projection/load flags. Preserve ignored push failure. */
void uvIMtxLoadProjection(Mtx mtx) {
    uvIMtxPush(mtx, G_MTX_PROJECTION | G_MTX_LOAD);
}
#line 183 "src/modules/uvimtx_rom.c"

#line 184 "src/modules/uvimtx_rom.c"
/* Copy the supplied fixed-point matrix into the active stack bank,
 * submit it with caller flags and return its retained address. A full
 * stack returns null without copying, incrementing or emitting commands. */
Mtx* uvIMtxPush(Mtx matrix, u16 flags) {
    Mtx* stackMatrix;
    // Stack is full
    if (sIMtxStackIdx >= sIMtxStackSize) {
        return NULL;
    }

    stackMatrix = &sMatrixStack[sIMtxTick][sIMtxStackIdx];
    uvIMtxCopy(stackMatrix, matrix);
    sIMtxStackIdx++;
    uvIMtxSubmitMatrix(stackMatrix, flags);
    return stackMatrix;
}
#line 197 "src/modules/uvimtx_rom.c"

#line 198 "src/modules/uvimtx_rom.c"
/* Append the original RSP matrix command and update the active-buffer
 * total and non-load counters. RE_UNKNOWN: matrix lifetime / flag domain; trace callers and RSP use. */
void uvIMtxSubmitMatrix(Mtx* mtx, u16 params) {
    Gfx** displayList;

    displayList = sUvGfxMgrExports_imtx->unk8();
    gSPMatrix(displayList[0]++, VIRTUAL_TO_PHYSICAL2(mtx), params);
    if (!(params & G_MTX_LOAD)) {
        sNonLoadedMatricesCount[sIMtxTick]++;
    }
    sRspMatricesCount[sIMtxTick]++;
}
#line 208 "src/modules/uvimtx_rom.c"

#line 209 "src/modules/uvimtx_rom.c"
/* Return the selected original adjacent-state value using the negated
 * buffer index. Keep this expression until contiguous global layout is audited;
 * unknown kinds return zero. */
s32 uvIMtxGetOtherBufferValue(s32 kind) {
    switch (kind) {
    case 0:
        return sUnusedArray1[0 - sIMtxTick];
    case 1:
        return sUnusedArray2[0 - sIMtxTick];
    default:
        return 0;
    }
}
#line 219 "src/modules/uvimtx_rom.c"
