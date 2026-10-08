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

/*
 * Allocate from the first free-list block passing the original strict size-plus-
 * alignment test. Retain the preceding node, unlink the chosen block, optionally
 * return its trailing remainder to the coalescing list, and encode the original
 * allocation extent and alignment adjustment in the reused header word. Clear
 * only the unrounded requested payload size when the existing control is enabled.
 * Preserve every accounting update, signed size gate, mask, strict comparison,
 * raw address cast and packed-word expression.
 * RE_UNKNOWN: caller guarantees for alignment values and address arithmetic,
 * complete heap/list bounds and block lifecycle, packed-header consumers, and
 * accounting-counter meanings. Trace original allocator callers, free/decode
 * paths and heap initialization before adding validation, changing header types,
 * assigning further counter meanings or claiming portable allocation semantics.
 */
#line 155 "src/mem_allocator.c"
void* _uvMemAlloc(u32 size, u32 alignment) {
    u32 requestedSize;
    s32 allocationExtent;
    s32 alignmentAdjustment;
    MemBlock* remainderBlock;
    MemBlock* previousBlock;
    MemBlock* selectedPreviousBlock;
    MemBlock* block;
    s32 paddingCandidate;
    MemBlock* selectedBlock;
    s32 blockFound;
    /* Retain the unrounded request for the optional payload clear. */
    requestedSize = size;

    allocationExtent = -1;
    blockFound = FALSE;
    previousBlock = NULL;
    selectedPreviousBlock = NULL;
    if (((s32)size <= 0) || ((s32)size >= 0x800000)) {
        return NULL;
    }
    size = ALIGN8(size);
    D_8001F7B8 = 0;

    for (block = gMemBlockHead; block != NULL; block = block->next) {
        /* Choose the first free block that passes the original strict fit test. */
        alignmentAdjustment = alignment - ((u32) &block->size & (alignment - 1));
        if (alignment == alignmentAdjustment) {
            paddingCandidate = 0;
        } else {
            paddingCandidate = alignmentAdjustment;
        }
        if ((paddingCandidate + size) < block->size) {
            allocationExtent = block->size;
            selectedPreviousBlock = previousBlock;
            blockFound = TRUE;
            selectedBlock = block;
            break;
        }
        previousBlock = block;
        D_8001F7B8 += 1;
    }
    D_8001F7BC += D_8001F7B8;
    if ((!blockFound) || (allocationExtent < size) || (allocationExtent == -1)) {
        D_8002F7DC = 1;
        return NULL;
    }

    paddingCandidate = alignment - ((s32) &selectedBlock->size & (alignment - 1));
    if (alignment == paddingCandidate) {
        alignmentAdjustment = 0;
    } else {
        alignmentAdjustment = paddingCandidate;
    }
    size += alignmentAdjustment;
    if (selectedPreviousBlock == NULL) {
        gMemBlockHead = selectedBlock->next;
    } else {
        selectedPreviousBlock->next = selectedBlock->next;
    }

    remainderBlock = (void *) ((u8 *) selectedBlock + size);
    D_8001F7A0--;
    if ((size + 8) < selectedBlock->size) {
        remainderBlock->next = NULL;
        remainderBlock->size = selectedBlock->size - size;
        allocationExtent = size;
        uvInsertFreeBlockCoalesced(remainderBlock);
    }
    selectedBlock = (void *) ((u8 *) selectedBlock + alignmentAdjustment);
    selectedBlock->next = (allocationExtent / 4) | ((alignmentAdjustment >> 2) << 0x14);
    D_8001F7B0 += D_8001F7A0;
    D_8001F7A8++;
    if (gClearAllocatedMemory) {
        uvMemSet(&selectedBlock->size, 0, requestedSize);
    }
    return &selectedBlock->size;
}
#line 233 "src/mem_allocator.c"

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
