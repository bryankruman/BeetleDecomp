// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

#define IMTX_STACK_SIZE 100

// Todo replace these structs with the actual exports of uvcback_rom and uvgfxmgr_rom
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
void func_uvimtx_rom_00400338(uvMtx *dst, uvMtx src);
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
    arg0->func_uvimtx_rom_00400338 = func_uvimtx_rom_00400338;
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

    // Create two 4x4 dynamic matrices
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

void uvIMtxStackInit(s32 arg0) {
    sIMtxTick ^= 1;
    sRspMatricesCount[sIMtxTick] = 0;
    sNonLoadedMatricesCount[sIMtxTick] = 0;
    sIMtxStackIdx = 0;
}

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

void uvIMtxSetIdentity(Mtx* m) {
    m->m[0][0] = 0x10000;
    m->m[0][1] = 0;
    m->m[0][2] = 1;
    m->m[0][3] = 0;
    m->m[1][1] = 0x10000;
    m->m[1][0] = 0;
    m->m[1][3] = 1;
    m->m[1][2] = 0;
    m->m[2][0] = 0;
    m->m[2][1] = 0;
    m->m[2][2] = 0;
    m->m[2][3] = 0;
    m->m[3][0] = 0;
    m->m[3][1] = 0;
    m->m[3][2] = 0;
    m->m[3][3] = 0;
}

void uvImtxStub(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {

}

void func_uvimtx_rom_00400338(uvMtx* dst, uvMtx src) {
    uvMtx* srcPtr = &src;
    uvMtx* dstPtr = dst;
    Mtx stack;

    if (dst == srcPtr) {
        dstPtr = (uvMtx*)&stack;
    }

    dstPtr->u.i[0][1] = src.u.i[1][0];
    dstPtr->u.i[0][2] = src.u.i[2][0];
    dstPtr->u.i[1][0] = src.u.i[0][1];
    dstPtr->u.i[1][2] = src.u.i[2][1];
    dstPtr->u.i[2][0] = src.u.i[0][2];
    dstPtr->u.i[2][1] = src.u.i[1][2];
    dstPtr->u.f[0][1] = src.u.f[1][0];
    dstPtr->u.f[0][2] = src.u.f[2][0];
    dstPtr->u.f[1][0] = src.u.f[0][1];
    dstPtr->u.f[1][2] = src.u.f[2][1];
    dstPtr->u.f[2][0] = src.u.f[0][2];
    dstPtr->u.f[2][1] = src.u.f[1][2];

    if (srcPtr == dstPtr) {
        uvIMtxCopy((Mtx*)dst, stack);
    }
}

#line 168 "src/modules/uvimtx_rom.c"
/* Copy the supplied fixed-point matrix into the original stack and
 * submit it with the model-view load flags. Preserve ignored push failure. */
void uvIMtxLoadModelview(Mtx mtx) {
    uvIMtxPush(mtx, G_MTX_LOAD);
}
#line 171 "src/modules/uvimtx_rom.c"

void uvGfxMtxViewPop(void) {
    Gfx** gdlh;

    gdlh = sUvGfxMgrExports_imtx->unk8();

    gSPPopMatrix((*gdlh)++, G_MTX_MODELVIEW);
}

#line 180 "src/modules/uvimtx_rom.c"
/* Copy the supplied fixed-point matrix into the original stack and
 * submit it with projection/load flags. Preserve ignored push failure. */
void uvIMtxLoadProjection(Mtx mtx) {
    uvIMtxPush(mtx, G_MTX_PROJECTION | G_MTX_LOAD);
}
#line 183 "src/modules/uvimtx_rom.c"

Mtx* uvIMtxPush(Mtx mtx, u16 params) {
    Mtx* stackMatrix;
    // Stack is full
    if (sIMtxStackIdx >= sIMtxStackSize) {
        return NULL;
    }

    stackMatrix = &sMatrixStack[sIMtxTick][sIMtxStackIdx];
    uvIMtxCopy(stackMatrix, mtx);
    sIMtxStackIdx++;
    uvIMtxSubmitMatrix(stackMatrix, params);
    return stackMatrix;
}

#line 198 "src/modules/uvimtx_rom.c"
/* Append the original RSP matrix command and update the active-buffer
 * total and non-load counters. Matrix lifetime and flags remain caller-owned. */
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
