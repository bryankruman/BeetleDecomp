// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "file_manager.h"
#include "mem_allocator.h"
/* Original address storage only; unresolved callback is an opaque code label.
 * RE_UNKNOWN: its callable prototype requires original implementation/caller proof. */
typedef struct { u32 emptyCallbackAddress, unknownCallbackAddress; } AirecExportAddresses;
void func_airec_00400108(void);
extern u8 func_airec_00400110[];
/* Original helper consumes one writable table address; result is unused. */
void func_airec_00400000(void *);
extern s32 D_airec_00400B6C;
typedef struct { s32 count; struct { u32 value; f32 ratio; } pairs[20]; } AirecPairBuffer;
typedef struct { u8 unk00[0x18]; void (*set)(s32, s32); } AirecTdataExports;
extern void *gTdataExports;
extern s32 D_airec_00400868, D_airec_00400968, D_airec_00400A68, D_airec_004007F0, D_airec_004007FC, D_airec_00400808, D_airec_00400B68, D_airec_00400B64;
void func_airec_00400524(AirecPairBuffer *, void *);
void airecNoOpWithoutTrackData(void);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/airec/func_airec_00400000.s")

#line 21 "src/modules/airec.c"
/* Register the original two addresses, store the 500-record limit and
 * allocate twelve bytes per record, then initialize the three original
 * tables through helper 0x000000 in order. Keep the allocator result word
 * and original unchecked allocation behavior.
 * RE_UNKNOWN: full record/table layout, allocation-failure reachability,
 * ownership/reinitialization policy and remaining callback contracts. Trace
 * original helper 0x000000, buffer consumers and module lifecycle callers
 * before assigning field meanings, changing capacity or adding recovery. */
void __entrypoint_func_airecInitializeModuleState(AirecExportAddresses *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->emptyCallbackAddress = (u32)func_airec_00400108;
    exports->unknownCallbackAddress = (u32)func_airec_00400110;
    D_airec_00400B6C = 500;
    D_airec_00400B64 = (s32)_uvMemAllocAlign8(D_airec_00400B6C * 12);
    func_airec_00400000(&D_airec_00400868);
    func_airec_00400000(&D_airec_00400968);
    func_airec_00400000(&D_airec_00400A68);
}
#line 22 "src/modules/airec.c"

#line 13 "src/modules/airec.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_airec_00400108(void) {
}
#line 15 "src/modules/airec.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/airec/func_airec_00400110.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/airec/func_airec_0040046C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/airec/func_airec_00400524.s")

#line 22 "src/modules/airec.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_airec_00400598(void) {
}
#line 24 "src/modules/airec.c"

#line 18 "src/modules/airec.c"
/* Legacy record-count loop; no per-record operation remains in the original. */
void airecRunLegacyCountLoop(void *context, int *record_count) {
    int index;
    for (index = 0; index < *record_count; index++) {
    }
}
#line 19 "src/modules/airec.c"

#line 20 "src/modules/airec.c"
/* Convert three recorded tables into 20-pair buffers, preserve the legacy
 * count-only passes, then forward the saved values to track-data export 0x18.
 * Missing track-data uses the original fallback. Pair value words stay opaque. */
void airecProcessRecordedTables(void) {
    AirecPairBuffer first;
    AirecPairBuffer second;
    AirecPairBuffer third;
    func_airec_00400524(&first, &D_airec_00400868);
    func_airec_00400524(&second, &D_airec_00400968);
    func_airec_00400524(&third, &D_airec_00400A68);
    airecRunLegacyCountLoop(&D_airec_004007F0, &first.count);
    airecRunLegacyCountLoop(&D_airec_004007FC, &second.count);
    airecRunLegacyCountLoop(&D_airec_00400808, &third.count);
    if (gTdataExports != NULL) ((AirecTdataExports *)gTdataExports)->set(D_airec_00400B68, D_airec_00400B64);
    else airecNoOpWithoutTrackData();
}
#line 21 "src/modules/airec.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/airec/func_airec_00400678.s")

#line 24 "src/modules/airec.c"
/* Original no-op fallback in airecProcessRecordedTables when gTdataExports is
 * NULL. No recorded tables are handed to the track-data module in this branch.
 * RE_UNKNOWN: any external callback role or intended missing-module policy. */
void airecNoOpWithoutTrackData(void) {
}
#line 26 "src/modules/airec.c"

