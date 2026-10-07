// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

void _uvMemAllocInit(void);
void uvFillAppStackPrefix(s32);
void uvFillFreeBlockPayloads(s32);
void* _uvMemAlloc(u32 size, u32 alignment);

MemBlock* gMemBlockHead;
extern MemBlock gMemBlock[0x79912];

// .data
s32 D_8001F7A0 = 0;
s32 D_8001F7A4 = 0;
s32 D_8001F7A8 = 0;
s32 D_8001F7AC = 0;
s32 D_8001F7B0 = 0;
s32 D_8001F7B4 = 0;
s32 D_8001F7B8 = 0;
s32 D_8001F7BC = 0;
s32 D_8001F7C0 = 0;
s32 D_8001F7C4 = 0;

extern u8 D_8001F7D0;
extern s32 gClearAllocatedMemory;
extern s32 D_8002F7DC;
extern u8 gAppThreadStack[];


void _uvMemAllocInitStartUp(void) {
    _uvMemAllocInit();
    if ((gClearAllocatedMemory) || (D_8001F7D0 != 0)) {
        uvFillFreeBlockPayloads(D_8001F7D0);
        uvFillAppStackPrefix(D_8001F7D0);
    }
}

void _uvMemAllocInit(void) {
    gMemBlockHead = gMemBlock;
    gMemBlockHead->next = NULL;
    gMemBlockHead->size = ((u32) 0x80400000 - (u32)gMemBlock);
    D_8001F7A0 = 1;
    D_8001F7A4 = 1;
}

UNUSED void _uvMemUnusedDbgFunc(void) {
    MemBlock *block;

    block = gMemBlockHead;
    while (block != NULL) {
        block = block->next;
    }
}

#line 55 "src/mem_allocator.c"
/* Fill from gAppThreadStack to 0x30 bytes below this function's stack-local
 * address, preserving the original self-address calculation and frame margin.
 * RE_UNKNOWN: required active-thread/frame relationship and the margin's
 * contract; resolve from original thread setup and call frames before
 * changing the range or treating this as a portable stack-clearing routine. */
void uvFillAppStackPrefix(s32 fillValue) {
    void* stackMarker;

    stackMarker = &((s32*)&stackMarker)[-12];
    uvMemSet(gAppThreadStack, fillValue, ((u8*)&stackMarker - (u8*)&gAppThreadStack) - 0x30);
}
#line 61 "src/mem_allocator.c"

#line 62 "src/mem_allocator.c"
/* Fill each free-list block after its eight-byte MemBlock header with the
 * low byte of fillValue. Preserve both byte masks and the original size
 * calculation, leaving the linked-list metadata intact. */
void uvFillFreeBlockPayloads(s32 fillValue) {
    MemBlock* block;

    for (block = gMemBlockHead; block != NULL; block = block->next) {
        uvMemSet(block + 1, fillValue & 0xFF & 0xFF, block->size - 8);
    }
}
#line 69 "src/mem_allocator.c"

#line 70 "src/mem_allocator.c"
/* Insert a released block into the address-ordered free list and merge
 * contiguous neighbors, preserving each original branch and counter update.
 * RE_UNKNOWN: original source form of the next-neighbor size calculation;
 * retain its existing FAKE comma expression for binary matching until
 * an equivalent natural expression is independently proven. */
void uvInsertFreeBlockCoalesced(MemBlock* releasedBlock) {
    MemBlock* nextBlock;
    MemBlock* previousBlock;
    s32 releasedSize;

    previousBlock = NULL;
    releasedSize = releasedBlock->size;
    if (gMemBlockHead == NULL) {
        gMemBlockHead = releasedBlock;
        D_8001F7A0 += 1;
        return;
    }

    /* Locate the two free-list neighbors around the released block. */
    nextBlock = gMemBlockHead;
    while (nextBlock != NULL && nextBlock < releasedBlock) {
        previousBlock = nextBlock;
        nextBlock = nextBlock->next;
    }

    if (previousBlock != NULL) {
        if ((u32)releasedBlock == ( (u32) previousBlock + (u32)previousBlock->size)) {
            if ((u32)nextBlock == ((u32)releasedBlock + (u32)releasedSize)) {
                previousBlock->size += releasedSize;
                previousBlock->size = previousBlock->size + nextBlock->size;
                previousBlock->next = nextBlock->next;
                D_8001F7A0 -= 1;
                return;
            }
        }
    }
    if (previousBlock != NULL) {
        if ((u32)releasedBlock == ((u32)previousBlock + (u32)previousBlock->size)) {
            previousBlock->size += releasedSize;
            return;
        }
    }
    if ((u32)nextBlock == ((u32)releasedBlock + releasedSize)) {
        releasedBlock->next = nextBlock->next;

        releasedBlock->size = (0, releasedSize) + nextBlock->size; // FAKE
        if (previousBlock != NULL) {
            previousBlock->next = releasedBlock;
            return;
        }
        gMemBlockHead = releasedBlock;
        return;
    }
    /* Neither neighbor is contiguous: link a new free-list node. */
    releasedBlock->next = nextBlock;
    if (previousBlock != NULL) {
        previousBlock->next = releasedBlock;
    } else {
        gMemBlockHead = releasedBlock;
    }
    D_8001F7A0++;
    if ((u32) D_8001F7A4 < (u32) D_8001F7A0) {
        D_8001F7A4 = D_8001F7A0;
    }
}
#line 128 "src/mem_allocator.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/mem_allocator/uvMemAllocAt.s")

// called at start of every GameState transition during gameplay
#line 132 "src/mem_allocator.c"
/* Reset the allocator free list and the existing accounting counters.
 * If forced or either fill control is enabled, fill free payloads and
 * the app-stack prefix using the configured byte. uvSysInit calls this
 * before rebuilding the file and module tables during runtime reinitialization.
 * RE_UNKNOWN: exact semantics of all reset counters and the documented
 * graphics effects of the fill controls; resolve their original consumers
 * and runtime traces before assigning further meanings. */
void uvResetAllocatorWithOptionalFill(s32 forceFill) {
    _uvMemAllocInit();
    D_8001F7A0 = 1;
    D_8001F7A4 = 1;
    D_8001F7A8 = 0;
    D_8001F7AC = 0;
    D_8001F7B0 = 0;
    D_8001F7B4 = 0;
    D_8001F7B8 = 0;
    D_8001F7BC = 0;
    /* Preserve the original three independent fill controls. */
    if ((forceFill != 0) || (gClearAllocatedMemory) || (D_8001F7D0 != 0)) {
        uvFillFreeBlockPayloads((s32) D_8001F7D0);
        uvFillAppStackPrefix((s32) D_8001F7D0);
    }
}
#line 149 "src/mem_allocator.c"


void *_uvMemAllocAlign8(u32 size) {
    return _uvMemAlloc(size, 8U);
}

void* _uvMemAlloc(u32 size, u32 alignment) {
    u32 sp44;
    s32 var_t1;
    s32 var_a0;
    MemBlock* temp_a0;
    MemBlock* var_t0;
    MemBlock* var_t3;
    MemBlock* var_v0;
    s32 temp_v1;
    MemBlock* sp24;
    s32 var_t2;

    sp44 = size;

    var_t1 = -1;
    var_t2 = FALSE;
    var_t0 = NULL;
    var_t3 = NULL;
    if (((s32)size <= 0) || ((s32)size >= 0x800000)) {
        return NULL;
    }
    size = ALIGN8(size);
    D_8001F7B8 = 0;

    for (var_v0 = gMemBlockHead; var_v0 != NULL; var_v0 = var_v0->next) {

        var_a0 = alignment - ((u32) &var_v0->size & (alignment - 1));
        if (alignment == var_a0) {
            temp_v1 = 0;
        } else {
            temp_v1 = var_a0;
        }
        if ((temp_v1 + size) < var_v0->size) {
            var_t1 = var_v0->size;
            var_t3 = var_t0;
            var_t2 = TRUE;
            sp24 = var_v0;
            break;
        }
        var_t0 = var_v0;
        D_8001F7B8 += 1;
    }
    D_8001F7BC += D_8001F7B8;
    if ((!var_t2) || (var_t1 < size) || (var_t1 == -1)) {
        D_8002F7DC = 1;
        return NULL;
    }

    temp_v1 = alignment - ((s32) &sp24->size & (alignment - 1));
    if (alignment == temp_v1) {
        var_a0 = 0;
    } else {
        var_a0 = temp_v1;
    }
    size += var_a0;
    if (var_t3 == NULL) {
        gMemBlockHead = sp24->next;
    } else {
        var_t3->next = sp24->next;
    }

    temp_a0 = (void *) ((u8 *) sp24 + size);
    D_8001F7A0--;
    if ((size + 8) < sp24->size) {
        temp_a0->next = NULL;
        temp_a0->size = sp24->size - size;
        var_t1 = size;
        uvInsertFreeBlockCoalesced(temp_a0);
    }
    sp24 = (void *) ((u8 *) sp24 + var_a0);
    sp24->next = (var_t1 / 4) | ((var_a0 >> 2) << 0x14);
    D_8001F7B0 += D_8001F7A0;
    D_8001F7A8++;
    if (gClearAllocatedMemory) {
        uvMemSet(&sp24->size, 0, sp44);
    }
    return &sp24->size;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/mem_allocator/_uvMemFree.s")

void _uvMemUnusedDbgFunc1(void) {
    MemBlock* block;
    s32 size;
    u32 var_a0;
    u32 var_v1;
    s32 blockSize;


    for (blockSize = 0, var_v1 = 0, var_a0 = -1, block = gMemBlockHead; block != NULL; block = block->next, blockSize += size) {
        size = block->size;
        if (size < var_a0) {
            var_a0 = size;
        }

        if (var_v1 < size) {
            var_v1 = size;
        }
    }
}

s32 _uvMemGetBlocksSize(void) {
    MemBlock* block;
    s32 blocksSize;

    block = gMemBlockHead;
    blocksSize = 0;

    while (block != NULL) {
        blocksSize += block->size;
        block = block->next;
    }

    return blocksSize;
}

void* _uvMemAllocAlign16(u32 size) {
   return _uvMemAlloc(size, 0x10U);
}

void uvMemFree(void *ptr) {
    _uvMemFree(ptr);
}
