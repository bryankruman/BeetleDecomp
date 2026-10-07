// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { u8 unk00[0x14]; void (*forward)(s32, s32, s32); } AieditTdataForward;
typedef struct { u8 unk00[0x98]; f32 selected; u8 unk9C[4]; s32 parameter; } AieditForwardState;
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
void aieditForwardTrackDataSelection(s32 arg0);
void func_aiedit_00400234();
void func_aiedit_0040084C();
void aieditForwardTrackDataSelection();
void func_aiedit_0040098C();
void func_aiedit_004009E4();
void aieditRunTdataNoopCallback(s32 context);
void aieditRunTdataZeroCallback(s32 context);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/__entrypoint_func_aiedit_400000.s")

void func_aiedit_0040022C(void) {
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/func_aiedit_00400234.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/func_aiedit_0040084C.s")

void func_aiedit_0040093C(void) {
}

#line 42 "src/modules/aiedit.c"
/* Forward callback context, the truncated floating selection and the stored
 * parameter to track-data export 0x14 when that module is available. More
 * specific parameter meanings remain unknown; no bounds or value changes. */
void aieditForwardTrackDataSelection(s32 context) {
    AieditTdataForward *exports = (AieditTdataForward *)gTdataExports;
    if (exports != NULL) {
        exports->forward(context, (s32)D_aiedit_00400E68.selected, D_aiedit_00400E68.parameter);
    }
}
#line 43 "src/modules/aiedit.c"

void func_aiedit_0040098C(s32 arg0) {
    s32 sp1C;
    gUvChanExports->unk4(arg0, 6, &sp1C, 0);
    gUvCbckExports->unk10(sp1C, aieditForwardTrackDataSelection, 0, 0xC8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/aiedit/func_aiedit_004009E4.s")

#line 49 "src/modules/aiedit.c"
/* Forward to track-data export 0x1C, whose original implementation is a no-op.
 * Preserve the original ignored callback context and argument-home store. */
void aieditRunTdataNoopCallback(s32 context) {
    gTdataExports->unk1C();
}
#line 50 "src/modules/aiedit.c"

#line 51 "src/modules/aiedit.c"
/* Invoke track-data export 0x20, whose original implementation returns zero.
 * The callback ignores its context and does not use the query result. */
void aieditRunTdataZeroCallback(s32 context) {
    gTdataExports->unk20();
}
#line 52 "src/modules/aiedit.c"

