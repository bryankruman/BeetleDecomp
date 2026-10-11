// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 prefix[8]; void (*update)(s32); } AieditObjectUpdateExports;
typedef struct { u8 prefix[0x30]; void (*update)(s32, s32, f32); } AieditTdataUpdateExports;
extern AieditObjectUpdateExports *D_aiedit_00400E64;

typedef struct { u8 unk00[0x14]; void (*forward)(s32, s32, s32); } AieditTdataForward;
typedef struct { s32 objects[4]; u8 records[0x80]; s32 count, mode; f32 selected; u8 unk9C[4]; s32 parameter; u8 unkA4[8]; f32 scalar; } AieditForwardState;
extern AieditForwardState D_aiedit_00400E68;
typedef struct {
    char pad[0x4];
    void (*unk4)(s32, s32, void *, s32);
} AieditChanExports;
typedef struct {
    char pad[0x10];
    void (*unk10)(s32, void (*)(s32), s32, s32);
} AieditCbckExports;
typedef struct {
    char pad[0x1C];
    void (*unk1C)(void);
    s32 (*unk20)(void);
} AieditTdataExports;
extern AieditChanExports *gUvChanExports;
extern AieditCbckExports *gUvCbckExports;
extern AieditTdataExports *gTdataExports;
void aieditInvokeTrackDataRefreshCallback(s32 arg0);
void func_aiedit_00400234();
void aieditUpdateObjectsAndInvokeTrackDataCallback(void);
void aieditInvokeTrackDataRefreshCallback();
void aieditRegisterTrackDataRefreshCallback();
void func_aiedit_004009E4();
void aieditRunTdataNoopCallback(s32 context);
void aieditRunTdataZeroCallback(s32 context);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/__entrypoint_func_aiedit_400000.s")

#line 36 "src/modules/aiedit.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_aiedit_0040022C(void) {
}
#line 38 "src/modules/aiedit.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/func_aiedit_00400234.s")

#line 41 "src/modules/aiedit.c"




#line 45 "src/modules/aiedit.c"
/* Update each editor item through the object module in mode one or
 * the original record helper otherwise, reloading count/mode after callbacks.
 * If track data exists and scalar is nonzero, invoke export 0x30.
 * The original export table binds the empty func_tdata_00401344.
 * RE_UNKNOWN: original argument contract. The target's current C declaration
 * uses three s32 arguments, while this caller supplies its third as f32;
 * an empty target does not establish the intended prototype. Reconcile original
 * caller argument setup before changing types or assigning meanings.
 * The empty target establishes no track-data update from these arguments. */
void aieditUpdateObjectsAndInvokeTrackDataCallback(void) {
    s32 index = 0;
    if (D_aiedit_00400E68.count > 0) {
        do {
            if (D_aiedit_00400E68.mode == 1) D_aiedit_00400E64->update(D_aiedit_00400E68.objects[index]);
            else func_aiedit_00400234((u8 *)&D_aiedit_00400E68 + (index << 5) + 0x10);
            index++;
        } while (index < D_aiedit_00400E68.count);
    }
    if (gTdataExports != NULL && D_aiedit_00400E68.scalar != 0.0f) {
        ((AieditTdataUpdateExports *)gTdataExports)->update((s32)D_aiedit_00400E68.selected, D_aiedit_00400E68.parameter, D_aiedit_00400E68.scalar);
    }
}
#line 58 "src/modules/aiedit.c"
#line 42 "src/modules/aiedit.c"

#line 43 "src/modules/aiedit.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_aiedit_0040093C(void) {
}
#line 45 "src/modules/aiedit.c"

#line 42 "src/modules/aiedit.c"



#line 45 "src/modules/aiedit.c"
/* Invoke track-data export 0x14 when loaded. The original export table
 * binds tdataRefreshSharedData(void), which forwards to the shared helper.
 * RE_UNKNOWN: the preserved caller view supplies context, truncated selection
 * and parameter, while the bound target takes no arguments and ignores them.
 * Reconcile original callback/caller argument setup before changing this
 * fixed call form or treating the three supplied words as refresh inputs. */
void aieditInvokeTrackDataRefreshCallback(s32 context) {
    AieditTdataForward *exports = (AieditTdataForward *)gTdataExports;
    if (exports != NULL) {
        exports->forward(context, (s32)D_aiedit_00400E68.selected, D_aiedit_00400E68.parameter);
    }
}
#line 51 "src/modules/aiedit.c"
#line 43 "src/modules/aiedit.c"

#line 44 "src/modules/aiedit.c"
/* Request channel property 6 into the local callback-list word, then register
 * the track-data refresh callback with context zero and priority 0xC8.
 * RE_ORIGINAL_QUIRK: the local output has no initializer or post-query NULL check.
 * RE_UNKNOWN: the channel provider must write a valid callback-list value; list
 * and callback lifetime, channel validity and registration failure remain unproved. */
#line 46 "src/modules/aiedit.c"
void aieditRegisterTrackDataRefreshCallback(s32 channel) {
    s32 callbackList;
    gUvChanExports->unk4(channel, 6, &callbackList, 0);
    gUvCbckExports->unk10(callbackList, aieditInvokeTrackDataRefreshCallback, 0, 0xC8);
}
#line 51 "src/modules/aiedit.c"
#line 49 "src/modules/aiedit.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/func_aiedit_004009E4.s")

#line 49 "src/modules/aiedit.c"
/* Ignore the incoming context and call track-data export 0x1C with no arguments.
 * The reviewed export table binds the currently empty func_tdata_004008C4.
 * RE_UNKNOWN: why this callback is scheduled and the track-data provider lifetime
 * remain unresolved; an empty provider does not authorize removing the call. */
#line 51 "src/modules/aiedit.c"
void aieditRunTdataNoopCallback(s32 context) {
    gTdataExports->unk1C();
}
#line 54 "src/modules/aiedit.c"
#line 50 "src/modules/aiedit.c"

#line 51 "src/modules/aiedit.c"
/* Ignore the incoming context and call track-data export 0x20 with no arguments,
 * discarding its result. The reviewed provider func_tdata_004009A8 returns zero.
 * RE_UNKNOWN: callback purpose and track-data provider lifetime remain unresolved.
 * Preserve the discarded return and the original separate callback identity. */
#line 53 "src/modules/aiedit.c"
void aieditRunTdataZeroCallback(s32 context) {
    gTdataExports->unk20();
}
#line 56 "src/modules/aiedit.c"
#line 52 "src/modules/aiedit.c"

