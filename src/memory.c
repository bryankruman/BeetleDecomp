// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

/*
 * Copy bytes directly when the source has address bit 31 set. Otherwise keep
 * the original 4,096-byte device-transfer chunks, alignment checks, leading-word
 * reads and DMA-before-leading-copy ordering. Names describe actual cursors,
 * counts and low source-address bits; no transfer or failure behavior changes.
 * RE_ORIGINAL_QUIRK: an odd device address, destination address or byte count
 * stores zero bytes at addresses 1 and 2 and returns. The unaligned-destination remainder
 * check tests equality, retaining its unsigned subtraction even when the requested
 * count is smaller than the leading-byte count. Do not silently change either path.
 * RE_UNKNOWN: original fault intent, valid device regions and transfer/count
 * domains, source/destination capacities and overlap, caller reachability and DMA
 * failure/lifetime guarantees. Trace original callers and the actual DMA/device
 * providers before replacing checks, adding bounds, initializing or moving data.
 */
#line 4 "src/memory.c"
void _uvMediaCopy(void* destination, void* sourceAddress, u32 byteCount) {
    s32 byteIndex;
    u8 *alignedDestination;
    s32 leadingByteCount;
    u8 *sourceCursor;
    u8 leadingBytes[16];
    u8 *destinationCursor;
    s32 sourceWordOffset;
    s32 wordAlignedSourceAddress;

    destinationCursor = destination;
    sourceCursor = sourceAddress;
    if ((u32)sourceCursor & 0x80000000) {
        for (byteIndex = 0; (u32)byteIndex < byteCount; byteIndex++) {
            destinationCursor[byteIndex] = sourceCursor[byteIndex];
        }
        return;
    }

    while (byteCount > 0x1000) {
        _uvMediaCopy(destinationCursor, sourceCursor, 0x1000);
        byteCount -= 0x1000;
        destinationCursor += 0x1000;
        sourceCursor += 0x1000;
    }

    if (byteCount != 0) {
        if (((s32)sourceCursor | (s32) destinationCursor | byteCount) & 1) {
            // RE_ORIGINAL_QUIRK: odd device-transfer inputs zero addresses 1 and 2.
            // RE_UNKNOWN: original fault intent and reachable callers need evidence.
            // Preserve the actual stores and return without inventing an error API.
            *(u16*)(1) = 0;
            return;
        }
        if ((s32)destinationCursor & 7) {
            alignedDestination = (u8*)((s32)(destinationCursor + 7) & ~7);
            leadingByteCount = alignedDestination - destinationCursor;
            sourceWordOffset = (u32)sourceCursor & 2;

            if ((byteCount != (u32)leadingByteCount) != 0) {
                _uvDMA(alignedDestination, sourceCursor + leadingByteCount, byteCount - leadingByteCount);
            }
            wordAlignedSourceAddress = sourceCursor - sourceWordOffset;

            osPiReadIo(wordAlignedSourceAddress, (u32*)&leadingBytes[0]);
            osPiReadIo(wordAlignedSourceAddress + 4, (u32*)&leadingBytes[4]);
            if (sourceWordOffset) {
                osPiReadIo(wordAlignedSourceAddress + 8, (u32*)&leadingBytes[8]);
            }
            for (byteIndex = 0; byteIndex < leadingByteCount && byteIndex < byteCount; byteIndex++) {
                destinationCursor[byteIndex] = leadingBytes[byteIndex + sourceWordOffset];
            }

        } else {
            _uvDMA(destinationCursor, sourceCursor, byteCount);
        }
    }
}
#line 62 "src/memory.c"

/* Fill exactly nbytes successive destination bytes with the low eight bits
 * of value; a zero count performs no store. RE_UNKNOWN: destination capacity,
 * validity and overlap with externally accessed storage require callers. */
#line 63 "src/memory.c"
void uvMemSet(void* vAddr, u8 value, u32 nbytes) {
    u32 count;
    u8* dest;

    count = 0;
    if (nbytes != 0) {
        dest = vAddr;
        do {
            count += 1;
            *dest++ = value;
        } while (count < nbytes);
    }
}

/*
 * Read 1, 2, 4 or 8 bytes in the original big-endian assembly order; unsupported
 * sizes return zero. Preserve all original shifts, promotions and byte reads.
 * The device-address path first calls the existing transfer helper into its
 * original signed 64-bit scratch, then recursively uses the direct-address path.
 * RE_ORIGINAL_QUIRK: the 8-byte case sign-extends the 32-bit contribution from
 * byte 4 shifted left by 24 before ORing it into the 64-bit value. Preserve that
 * actual native high-word effect rather than silently adding unsigned promotion.
 * RE_UNKNOWN: caller capacities/address domains, intended read/promotion contract,
 * device transfer initialization/failure and reachable odd-count paths.
 * Audit original callers and transfer/device consumers before changing widths,
 * signed arithmetic, scratch initialization, validation or failure handling.
 */
#line 77 "src/memory.c"
u64 uvMemRead(void* sourceAddress, u32 byteCount) {
    u64 value;
    u64 shiftedBytes;
    s64 deviceReadScratch;
    u8* sourceBytes;

    sourceBytes = sourceAddress;
    if ((byteCount != 1) && (byteCount != 2) && (byteCount != 4) && (byteCount != 8)) {
        value = 0;
    } else if ((s32) sourceAddress & 0x80000000) {
        value = sourceBytes[0];
        if (byteCount >= 2U) {
            shiftedBytes = value << 8;
            value = shiftedBytes | sourceBytes[1];
        }
        if (byteCount >= 3U) {
            shiftedBytes = value << 16;
            value = shiftedBytes | (sourceBytes[2] << 8) | sourceBytes[3];
        }
        if (byteCount >= 5U) {
            shiftedBytes = value << 32;
            value = shiftedBytes | (sourceBytes[4] << 0x18) | (sourceBytes[5] << 0x10) | (sourceBytes[6] << 8) | sourceBytes[7];
        }
    } else {
        _uvMediaCopy(&deviceReadScratch, sourceAddress, byteCount);
        value = uvMemRead(&deviceReadScratch, byteCount);
    }
    return value;
}
#line 106 "src/memory.c"
