/* Native-matched SDK routine using existing O32 declarations and storage.
 * Native evidence: kernel-stopthread-vtop-originals-7460.json.
 * Existing public declarations and storage remain unchanged.
 */
#include "PR/os_internal.h"
#include "PRinternal/osint.h"

/* The historical address-named slot declaration
 * is retained unchanged. */
extern OSThread *D_80020A50;

/* Translate either unsigned direct-map segment by clearing its upper three
 * address bits; send every other address to the existing TLB probe.
 * RE_ORIGINAL_QUIRK: retain the separate [0x80000000,0xA0000000) and
 * [0xA0000000,0xC0000000) tests and return the probe's result unchanged.
 * RE_UNKNOWN: this wrapper does not establish TLB mapping lifetime or define
 * the probe's failure result. Callers must interpret that result themselves.
 */
u32 osVirtualToPhysical(void *virtualAddress) {
    if ((u32)virtualAddress >= 0x80000000U &&
        (u32)virtualAddress < 0xA0000000U) {
        return (u32)virtualAddress & 0x1FFFFFFFU;
    }
    if ((u32)virtualAddress >= 0xA0000000U &&
        (u32)virtualAddress < 0xC0000000U) {
        return (u32)virtualAddress & 0x1FFFFFFFU;
    }
    return __osProbeTLB(virtualAddress);
}
