/* PI timing snapshot reconstructed from retained native behavior. */
#include "PR/os_internal.h"
#include "PRinternal/piint.h"

/* RE_UNKNOWN: only timing/domain bytes5..9 are interpreted. The other115
 * bytes of each raw120-byte owner and its nominal SDK identity remain unknown. */
typedef struct PiTimingSnapshotStorage {
    u8 unknownPrefix[5];
    u8 latency;
    u8 pageSize;
    u8 releaseDuration;
    u8 pulse;
    u8 domain;
    u8 unknownTail[110];
} PiTimingSnapshotStorage;

extern PiTimingSnapshotStorage D_80030F30;
extern PiTimingSnapshotStorage D_80030FA8;

#define PI_TIMING_REGISTER(byteOffset) \
    (*(volatile u32 *)(0xA4600000u + (byteOffset)))

GLOBAL_ASM("asm/nonmatchings/libultra/io/pi_domain_timing/osCreatePiManager.s")

/* Snapshot both PI domains into retained records; do not write hardware. */
#line 99 "src/libultra/io/pi_domain_timing.c"
void snapshotPiDomainTiming(void) {
    PiTimingSnapshotStorage* domain1Snapshot;
    PiTimingSnapshotStorage* domain2Snapshot;

    domain1Snapshot = &D_80030F30;
    domain1Snapshot->latency = PI_TIMING_REGISTER(0x14);
    domain1Snapshot->pulse = PI_TIMING_REGISTER(0x18);
    domain1Snapshot->pageSize = PI_TIMING_REGISTER(0x1C);
    domain1Snapshot->releaseDuration = PI_TIMING_REGISTER(0x20);
    domain1Snapshot->domain = 0;
    domain2Snapshot = &D_80030FA8;
    domain2Snapshot->latency = PI_TIMING_REGISTER(0x24);
    domain2Snapshot->pulse = PI_TIMING_REGISTER(0x28);
    domain2Snapshot->pageSize = PI_TIMING_REGISTER(0x2C);
    domain2Snapshot->releaseDuration = PI_TIMING_REGISTER(0x30);
    domain2Snapshot->domain = 1;
}
