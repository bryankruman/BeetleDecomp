/* Compute Controller Pak inode and identification checksums.
 * RE_UNKNOWN: Exact game SDK release is unproved.
 */
#line 1
#include "PRinternal/macros.h"
#include "PR/os_internal.h"
#include "PR/os_version.h"
#include "PRinternal/controller.h"
#include "PR/rmon.h"

#if BUILD_VERSION >= VERSION_J
extern __OSInode __osPfsInodeCache ALIGNED(0x8);
extern s32 __osPfsInodeCacheChannel;
extern u8 __osPfsInodeCacheBank;
#endif
#line 12
/* Sum inode bytes modulo 65536; the J-or-later branch truncates after the loop. */
u16 __osSumcalc(u8* ptr, int length) {
    int i;
    u32 sum = 0;
    u8* tmp = ptr;

    for (i = 0; i < length; i++) {
        sum += *tmp++;
#if BUILD_VERSION < VERSION_J
        sum = sum & 0xFFFF;
#endif
    }

#if BUILD_VERSION >= VERSION_J
    return sum & 0xFFFF;
#else
    return sum;
#endif
}

#line 31
/* Compute the normal and inverted pack-ID checksums over the first 28 bytes. */
s32 __osIdCheckSum(u16* ptr, u16* csum, u16* icsum) {
    u16 data = 0;
    u32 j;

    *csum = *icsum = 0;

    for (j = 0; j < ((sizeof(__OSPackId) - sizeof(u32)) / sizeof(u8)); j += 2) {
        data = *(u16*)((u32)ptr + j);
        *csum += data;
        *icsum += ~data;
    }

    return 0;
}

