// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

/* Observed callback/context pairs; unused slots remain opaque. */
typedef struct {
    u8 unk00[0x1558];
    void (*callback1558)(void *, s32);
    u8 unk155C[4];
    void (*callback1560)(void *, s32);
    u8 unk1564[4];
    void (*callback1568)(void *, s32);
    u8 unk156C[4];
    void (*callback1570)(s32, s32);
    void (*callback1574)(void *, s32);
    u8 unk1578[8];
    s32 context1580;
    u8 unk1584[4];
    s32 context1588;
    u8 unk158C[4];
    s32 context1590;
    u8 unk1594[4];
    s32 context1598;
    s32 context159C;
} DynStateCallbacks;


/* Prefix views grounded in collection indexing and link updates. */
typedef struct DynLinkedCollection DynLinkedCollection;
typedef struct DynLinkedNode {
    u8 unk00[4];
    s32 value04;
    u8 unk08[0xC];
    DynLinkedCollection *linkedCollection;
} DynLinkedNode;
struct DynLinkedCollection {
    u8 unk00[0x94];
    s32 count;
    DynLinkedNode *members[10];
};
typedef struct {
    u8 unk00[0xF748];
    s32 count;
    void *members[20];
} DynSecondaryCollection;


#include "uvfvec_rom.h"

#include "uvfmtx_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
extern UvDobj_Exports *D_uvdyn_rom_00411F84;

typedef struct DynResetState DynResetState;
typedef struct { u8 unk00[8]; DynResetState *owner; void *intersectionRecord; } DynAttachmentPrefix;
struct DynResetState {
    u8 unk00[0x18];
    s32 attachmentCount;
    DynAttachmentPrefix *attachments[2];
    s32 dobjUpdateMode;
    s32 dobjHandle;
    u8 unk2C[0x11E0];
    s32 value120C;
    u8 unk1210[0xDC];
    Mtx4F matrix12EC;
    Mtx4F matrix132C;
    Mtx4F matrix136C;
    u8 unk13AC[0xC0];
    Vec3F vector146C;
    Vec3F vector1478;
    u8 unk1484[8];
    f32 value148C;
    Vec3F translation1490;
    u8 unk149C[0xC];
    s32 value14A8;
    f32 value14AC;
    f32 value14B0;
    u8 unk14B4[8];
    Vec3F vector14BC;
    Vec3F vector14C8;
    u8 unk14D4[0xC];
    Vec3F vector14E0;
    Vec3F vector14EC;
    u8 unk14F8[0x5C];
    void (*callback)(DynResetState *, void *);
    u8 unk1558[0x24];
    void *callbackContext;
};
/* Only the intersection export at 0x20 is used by this prefix view. */
typedef struct {
    void *unk00[8];
    void (*setTransformProperty)(void *, s32, Mtx4F *);
    u8 unk24[0x14];
    void (*setDobjHandle)(void *, s32);
} DynIsectExportPrefix;
extern DynIsectExportPrefix *D_uvdyn_rom_00411F7C;
extern f32 D_uvdyn_rom_00411CBC;

extern UvFMtx_Rom_Exports *D_uvdyn_rom_00411F70;
/* Prefix fields observed in the secondary-state copy/reset routine. */
typedef struct {
    s32 registryIndex;
    u16 kind;
    u8 unk06[2];
    DynSecondaryCollection *collection;
    s32 value0C;
    u8 unk10[8];
    Mtx4F matrix18;
    Mtx4F matrix58;
    Mtx4F matrix98;
    Mtx4F matrixD8;
    Vec3F vector118;
    Vec3F vector124;
    u8 unk130[0x1C];
    Vec3F vector14C;
    Vec3F vector158;
    Vec3F vector164;
    Vec3F vector170;
    Vec3F vector17C;
    Vec3F vector188;
    u8 unk194[0xC];
    u16 flag1A0;
    u16 copyFlag;
    u16 updateFlag;
} DynSecondaryState;

extern UvFVec_Rom_Exports *D_uvdyn_rom_00411F74;
/* Prefix view: field meanings beyond observed copy/flag behavior are unknown. */
typedef struct {
    u8 unk00[0x12B6];
    u16 parameterFlag;
    f32 value12B8;
    f32 value12BC;
    Vec3F vector12C0;
    u8 unk12CC[0x10];
    Vec3F vector12DC;
    f32 value12E8;
} DynVectorFields;
typedef struct { Vec3F vector; f32 scalar; } DynVectorScalar;
typedef struct { s32 value; s32 unk04; s16 unk08; u16 result; } DynCallbackRequest;
typedef struct {
    u8 unk00[0x156C];
    void (*callback)(DynCallbackRequest *, void *);
    u8 unk1570[0x24];
    void *callbackContext;
} DynCallbackPrefix;

extern s32 D_uvdyn_rom_00411BDC[];
extern s32 D_uvdyn_rom_00411D48[];
extern void *D_uvdyn_rom_00411B1C;
extern f32 *D_uvdyn_rom_00411DB8;
extern u16 D_uvdyn_rom_00411DE8;
extern u16 D_uvdyn_rom_00411F18;
extern u16 D_uvdyn_rom_00411F1A;
extern u16 D_uvdyn_rom_00411E68;
extern DynSecondaryState *D_uvdyn_rom_00411DF0[];
void func_uvdyn_rom_004005F4();
void func_uvdyn_rom_00400664();
void func_uvdyn_rom_004006D4(s32 arg0, f32 arg1);
f32 func_uvdyn_rom_004006EC(s32 arg0);
void func_uvdyn_rom_0040071C();
void uvDynComposeRelativeTransform(Mtx4F *output, Mtx4F *first, Mtx4F *second);
void func_uvdyn_rom_00400A14(Mtx4F *, Mtx4F *, Vec3F *, Vec3F *, Vec3F *, Vec3F *, Vec3F *, f32);
void func_uvdyn_rom_00400C08();
void func_uvdyn_rom_00400E40();
void func_uvdyn_rom_00401014();
void func_uvdyn_rom_00401D54();
void func_uvdyn_rom_0040232C();
void func_uvdyn_rom_00402BD4();
void func_uvdyn_rom_00402E38();
void func_uvdyn_rom_00403294();
void func_uvdyn_rom_004033F4();
void func_uvdyn_rom_004034C8();
void func_uvdyn_rom_00403574();
void func_uvdyn_rom_004035A0();
void func_uvdyn_rom_00403724();
void func_uvdyn_rom_004037F0();
void func_uvdyn_rom_00403860();
void func_uvdyn_rom_00403A1C();
void func_uvdyn_rom_00403C38();
void func_uvdyn_rom_00403D90();
void func_uvdyn_rom_00403F98();
void func_uvdyn_rom_00404018();
void func_uvdyn_rom_004041CC();
s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1);
void func_uvdyn_rom_004043E0();
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output);
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection);
void uvDynAddUniqueAttachment(DynResetState *state, DynAttachmentPrefix *attachment);
void uvDynScanAttachmentMembership(DynResetState *state, DynAttachmentPrefix *attachment);
s32 func_uvdyn_rom_004046B4();
void * func_uvdyn_rom_004046FC();
void uvDynSetDobjHandle(DynResetState *state, s32 handle);
void func_uvdyn_rom_00404834();
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_uvdyn_rom_0040495C();
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second);
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second);
void func_uvdyn_rom_00404AF0();
void func_uvdyn_rom_00404BC0();
void func_uvdyn_rom_00404C60();
void func_uvdyn_rom_00404CE8();
void uvDynResetLinkedNodeState(DynResetState *state);
void uvDynInvokeStateCallback1574(DynStateCallbacks *state);
void uvDynInvokeStateCallback1558(DynStateCallbacks *state);
void uvDynInvokeStateCallback1568(DynStateCallbacks *state);
u16 uvDynInvokeValueCallback(DynCallbackPrefix *record, s32 value);
void uvDynInvokeStateCallback1560(DynStateCallbacks *state);
void uvDynInvokeValueCallback1570(DynStateCallbacks *state, s32 value);
void func_uvdyn_rom_00405040();
void func_uvdyn_rom_004050EC();
void func_uvdyn_rom_00407594();
void func_uvdyn_rom_0040771C();
void func_uvdyn_rom_004079B8();
void func_uvdyn_rom_00407C04();
void func_uvdyn_rom_00407C98();
void func_uvdyn_rom_00407DF0();
void func_uvdyn_rom_004088EC();
void func_uvdyn_rom_00408ACC();
void func_uvdyn_rom_00408DC8();
void func_uvdyn_rom_00409010();
void func_uvdyn_rom_00409318();
void uvDynApplyTranslatedDobjTransform(DynResetState *state);
void func_uvdyn_rom_0040954C();
void func_uvdyn_rom_0040981C();
void func_uvdyn_rom_00409960();
s32 func_uvdyn_rom_00409A48();
void func_uvdyn_rom_00409A7C();
void func_uvdyn_rom_00409AF0();
void func_uvdyn_rom_00409BD4();
void func_uvdyn_rom_00409CE4();
void func_uvdyn_rom_00409E18();
void func_uvdyn_rom_0040A05C();
void func_uvdyn_rom_0040A0D8();
void func_uvdyn_rom_0040A188();
void func_uvdyn_rom_0040AFAC();
void func_uvdyn_rom_0040AFD8();
void func_uvdyn_rom_0040B00C();
void func_uvdyn_rom_0040B08C();
void func_uvdyn_rom_0040B75C();
void func_uvdyn_rom_0040B838();
void func_uvdyn_rom_0040BAA0();
void func_uvdyn_rom_0040BAD4();
void func_uvdyn_rom_0040BB5C();
void func_uvdyn_rom_0040BC48();
void func_uvdyn_rom_0040BCE4();
void func_uvdyn_rom_0040BD14();
void func_uvdyn_rom_0040BFD8();
void uvDynInsertUniqueLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node);
void uvDynRemoveLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node);
void uvDynAppendUniqueSecondaryValue(DynSecondaryCollection *collection, void *value);
void uvDynRemoveSecondaryValue(DynSecondaryCollection *collection, void *value);
void uvDynUpdateCollectionMemberTransforms(DynLinkedCollection *collection);
void uvDynResetCollectionMemberState(DynLinkedCollection *collection);
void func_uvdyn_rom_0040C464();
void func_uvdyn_rom_0040C570();
void func_uvdyn_rom_0040E4E8();
void func_uvdyn_rom_0040E8E8();
void func_uvdyn_rom_0040F78C();
void func_uvdyn_rom_0040FC88();
void func_uvdyn_rom_00410250();
void func_uvdyn_rom_004107FC();
void func_uvdyn_rom_00410A88();
void func_uvdyn_rom_00410AEC();
void func_uvdyn_rom_00410C40();
void func_uvdyn_rom_00410D54();
void func_uvdyn_rom_00410D80();
void uvDynUnregisterSecondaryState(DynSecondaryState *state);
void func_uvdyn_rom_00410EF0();
void uvDynCopySecondaryCompanionFields(DynSecondaryState *state);
void func_uvdyn_rom_00411014(void *arg0, s32 arg1, f32 arg2);
f32 uvDynGetSecondaryScalarProperty(DynSecondaryState *state, s32 property);
void func_uvdyn_rom_00411148();
void func_uvdyn_rom_00411300();
void func_uvdyn_rom_0041138C();
void func_uvdyn_rom_00411454();
s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1);
void uvDynGetSecondaryMatrixProperty(DynSecondaryState *state, s32 property, Mtx4F *output);
void uvDynSetSecondaryCollection(DynSecondaryState *state, DynSecondaryCollection *collection);
void func_uvdyn_rom_004117C0();
void uvDynUpdateSecondaryStateOnce(DynSecondaryState *state, f32 value);
void uvDynResetSecondaryState(DynSecondaryState *state);
extern f32 D_uvdyn_rom_00411DB4;
extern u16 D_uvdyn_rom_00411EC0;
extern u16 D_uvdyn_rom_00411EC2;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/__entrypoint_func_uvdyn_rom_400000.s")

void func_uvdyn_rom_00400564(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x46564543);
    uvUnloadModule(0x51554154);
    uvUnloadModule(0x4D415448);
    uvUnloadModule(0x69736374);
    uvUnloadModule(0x444F424A);
    uvUnloadModule(0x54455252);
    uvUnloadModule(0x49534354);
    uvUnloadModule(0x4D4F444C);
    uvUnloadModule(0x51455259);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004005F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400664.s")

void func_uvdyn_rom_004006D4(s32 arg0, f32 arg1) {
    if (arg0 == 0) {
        D_uvdyn_rom_00411DB4 = arg1;
    }
}

f32 func_uvdyn_rom_004006EC(s32 arg0) {
    if (arg0 == 0) {
        return D_uvdyn_rom_00411DB4;
    }
    return -1.0f;
}

f32 *func_uvdyn_rom_00400710(void) {
    return &D_uvdyn_rom_00411DB4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040071C.s")

#line 307 "src/modules/uvdyn_rom.c"
/* Invert the second matrix's translation/rotation into output, then multiply
 * first by that result using the original matrix-export order. Output is reused
 * as the second multiplication input, preserving the supported in-place call. */
void uvDynComposeRelativeTransform(Mtx4F *output, Mtx4F *first, Mtx4F *second) {
    D_uvdyn_rom_00411F70->uvMat4InvertTranslationRotation(output, second);
    D_uvdyn_rom_00411F70->uvMat4Mul(output, first, output);
}
#line 308 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040232C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004034C8.s")

void func_uvdyn_rom_00403574(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411DE8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004035A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004037F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403A1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403C38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004041CC.s")

s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1) {
    s32 sp4;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg1) {                                 /* irregular */
    case 6:
        sp4 = arg0 + 0x12EC;
        break;
    case 16:
        sp4 = arg0 + 0x142C;
        break;
    case 15:
        sp4 = arg0 + 0x13EC;
        break;
    }
    return sp4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004043E0.s")

void func_uvdyn_rom_004044D0(void *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x14B8) = arg1;
}

#line 279 "src/modules/uvdyn_rom.c"
/* Copy the vector at 0x12DC and scalar at 0x12E8 into the output. Null
 * records leave output unchanged; the values have no established gameplay names. */
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output) {
    if (record != NULL) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&output->vector, &record->vector12DC);
        output->scalar = record->value12E8;
    }
}
#line 280 "src/modules/uvdyn_rom.c"

#line 281 "src/modules/uvdyn_rom.c"
/* Change the node's linked collection, removing its old membership first.
 * A nonnull destination whose count equals ten is rejected before checking for
 * an unchanged link. Null clears the link; original count invariants are required. */
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection) {
    if (collection != NULL && collection->count == 10) {
        return;
    }
    if (node->linkedCollection != NULL) {
        if (collection == node->linkedCollection) {
            return;
        }
        uvDynRemoveLinkedNode(node->linkedCollection, node);
    }
    node->linkedCollection = collection;
    if (collection != NULL) {
        uvDynInsertUniqueLinkedNode(collection, node);
    }
}
#line 282 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_004045A8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x14);
}

#line 287 "src/modules/uvdyn_rom.c"
/* Add a unique nonnull attachment unless count equals two, set its owner,
 * and in mode zero propagate the DOBJ handle to its intersection record.
 * The previous-owner helper only scans: original code does not remove old
 * membership. Preserve that behavior and the original valid-count contract. */
void uvDynAddUniqueAttachment(DynResetState *state, DynAttachmentPrefix *attachment) {
    u16 index;
    if (attachment == NULL) {
        return;
    }
    for (index = 0; index < state->attachmentCount; index++) {
        if (attachment == state->attachments[index]) {
            return;
        }
    }
    if (state->attachmentCount == 2) {
        return;
    }
    state->attachments[state->attachmentCount] = attachment;
    state->attachmentCount++;
    if (attachment->owner != NULL) {
        uvDynScanAttachmentMembership(attachment->owner, attachment);
    }
    attachment->owner = state;
    if (attachment->intersectionRecord != NULL && state->dobjUpdateMode == 0) {
        D_uvdyn_rom_00411F7C->setDobjHandle(attachment->intersectionRecord, state->dobjHandle);
    }
}
#line 288 "src/modules/uvdyn_rom.c"

#line 289 "src/modules/uvdyn_rom.c"
/* Preserve the original non-mutating membership scan and early return.
 * This routine neither removes the attachment nor changes its owner, even
 * though the original add routine calls it for a previous owner. */
void uvDynScanAttachmentMembership(DynResetState *state, DynAttachmentPrefix *attachment) {
    u16 index;
    if (state != NULL) {
        for (index = 0; index < state->attachmentCount; index++) {
            if (attachment == state->attachments[index]) {
                return;
            }
        }
    }
}
#line 290 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_004046B4(void *arg0, s32 arg1) {
    if (*(s32 *)((u8 *)arg0 + 0x18) < arg1) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x1C);
}

s32 func_uvdyn_rom_004046E0(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x18);
}

void *func_uvdyn_rom_004046FC(void *arg0, s32 arg1) {
    if (*(s32 *)((u8 *)arg0 + 0x38) < arg1) {
        return NULL;
    }
    return (void *)((u8 *)arg0 + arg1 * 0x170 + 0x3AC);
}

s32 func_uvdyn_rom_00404734(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x38);
}

#line 319 "src/modules/uvdyn_rom.c"
/* Store the DOBJ handle. In mode zero, read DOBJ property seven into the
 * original scalar pair and propagate the handle to nonnull attachment
 * intersection records. Preserve 16-bit iteration and live count reloads. */
void uvDynSetDobjHandle(DynResetState *state, s32 handle) {
    u16 index;
    DynAttachmentPrefix *attachment;
    state->dobjHandle = handle;
    if (state->dobjUpdateMode == 0) {
        D_uvdyn_rom_00411F84->uvDobjGetProp(handle, 7, &state->value14AC, 0);
        state->value14B0 = state->value14AC;
        for (index = 0; index < state->attachmentCount; index++) {
            attachment = state->attachments[index];
            if (attachment->intersectionRecord != NULL) {
                D_uvdyn_rom_00411F7C->setDobjHandle(attachment->intersectionRecord, handle);
            }
        }
    }
}
#line 320 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_0040481C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x28);
}

void func_uvdyn_rom_00404824(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x2C) = arg1;
}

s32 func_uvdyn_rom_0040482C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x2C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404834.s")

void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}

s32 func_uvdyn_rom_00404940(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x120C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040495C.s")

#line 347 "src/modules/uvdyn_rom.c"
/* Enable the parameter flag, copy the input vector and store the two scalar
 * parameters at their original offsets. The original requires a valid record. */
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second) {
    record->parameterFlag = 1;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&record->vector12C0, vector);
    record->value12B8 = first;
    record->value12BC = second;
}
#line 348 "src/modules/uvdyn_rom.c"

#line 349 "src/modules/uvdyn_rom.c"
/* Return the original parameter flag. Only when nonzero, copy the vector
 * and two scalars; reload the flag after the external copy as the original does. */
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second) {
    u16 flag;
    flag = record->parameterFlag;
    if (flag != 0) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(vector, &record->vector12C0);
        *first = record->value12B8;
        *second = record->value12BC;
        flag = record->parameterFlag;
    }
    return flag;
}
#line 350 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00404ACC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12B6) = 0;
}

s32 func_uvdyn_rom_00404AD4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x1274);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404AF0.s")

u16 func_uvdyn_rom_00404BA4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(u16 *)((u8 *)arg0 + 0x12DA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404CE8.s")

#line 377 "src/modules/uvdyn_rom.c"
/* Invoke the optional reset callback, clear value120C, copy the observed
 * vector pairs and matrix, and update each attachment's intersection transform
 * using property three. Finish with the original scalar and -1 sentinel.
 * Preserve the 16-bit attachment loop and unknown gameplay field meanings. */
void uvDynResetLinkedNodeState(DynResetState *state) {
    u16 index;
    void (*callback)(DynResetState *, void *);
    callback = state->callback;
    if (callback != NULL) {
        callback(state, state->callbackContext);
    }
    state->value120C = 0;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14EC, &state->vector14E0);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14C8, &state->vector14BC);
    for (index = 0; index < state->attachmentCount; index++) {
        D_uvdyn_rom_00411F7C->setTransformProperty(state->attachments[index]->intersectionRecord, 3, &state->matrix12EC);
    }
    D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix132C, &state->matrix12EC);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector1478, &state->vector146C);
    state->value148C = D_uvdyn_rom_00411CBC;
    state->value14A8 = -1;
}
#line 378 "src/modules/uvdyn_rom.c"

#line 379 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1574 with this state and the opaque context word
 * at 0x159C. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1574(DynStateCallbacks *state) {
    void (*callback)(void *, s32);
    callback = state->callback1574;
    if (callback != NULL) {
        callback(state, state->context159C);
    }
}
#line 385 "src/modules/uvdyn_rom.c"

#line 386 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1558 with this state and the opaque context word
 * at 0x1580. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1558(DynStateCallbacks *state) {
    void (*callback)(void *, s32);
    callback = state->callback1558;
    if (callback != NULL) {
        callback(state, state->context1580);
    }
}
#line 392 "src/modules/uvdyn_rom.c"

#line 393 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1568 with this state and the opaque context word
 * at 0x1590. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1568(DynStateCallbacks *state) {
    void (*callback)(void *, s32);
    callback = state->callback1568;
    if (callback != NULL) {
        callback(state, state->context1590);
    }
}
#line 399 "src/modules/uvdyn_rom.c"

#line 400 "src/modules/uvdyn_rom.c"
/* Invoke the optional value callback with the original 12-byte request:
 * value, -1, zero and an initial result of one. Return its 16-bit result,
 * or one when absent. Cache the callback once before initializing the request. */
u16 uvDynInvokeValueCallback(DynCallbackPrefix *record, s32 value) {
    void (*callback)(DynCallbackRequest *, void *);
    DynCallbackRequest request;
    callback = record->callback;
    if (callback != NULL) {
        request.result = 1;
        request.value = value;
        request.unk04 = -1;
        request.unk08 = 0;
        callback(&request, record->callbackContext);
        return request.result;
    }
    return 1;
}
#line 401 "src/modules/uvdyn_rom.c"

#line 402 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1560 with this state and the opaque context word
 * at 0x1588. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1560(DynStateCallbacks *state) {
    void (*callback)(void *, s32);
    callback = state->callback1560;
    if (callback != NULL) {
        callback(state, state->context1588);
    }
}
#line 408 "src/modules/uvdyn_rom.c"

#line 409 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1570 with the supplied value and the opaque context
 * word at 0x1598. The state itself is not passed; an absent callback has no effect. */
void uvDynInvokeValueCallback1570(DynStateCallbacks *state, s32 value) {
    void (*callback)(s32, s32);
    callback = state->callback1570;
    if (callback != NULL) {
        callback(value, state->context1598);
    }
}
#line 415 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00405040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040771C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004079B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004088EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409318.s")

#line 442 "src/modules/uvdyn_rom.c"
/* Copy the base matrix, apply the local translation at 0x1490, and send the
 * temporary matrix to part zero of the DOBJ handle. The entrypoint imports
 * DOBJ at D_uvdyn_rom_00411F84; this is not the separate MODL import. */
void uvDynApplyTranslatedDobjTransform(DynResetState *state) {
    Mtx4F translated;
    D_uvdyn_rom_00411F70->uvMat4FCopy(&translated, &state->matrix12EC);
    D_uvdyn_rom_00411F70->uvMat4LocalTranslate(&translated,
        state->translation1490.x, state->translation1490.y, state->translation1490.z);
    D_uvdyn_rom_00411F84->uvDobjPosm(state->dobjHandle, 0, &translated);
}
#line 443 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040954C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040981C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409960.s")

u16 func_uvdyn_rom_00409A40(void *arg0) {
    return *(u16 *)((u8 *)arg0 + 0x12D6);
}

s32 func_uvdyn_rom_00409A48(void *arg0)
{
  int new_var;
  s32 new_var3;
  u8 *new_var2;
 do { } while (0);
  new_var2 = ((u8 *) arg0) + 0x14;
  new_var3 = *((s32 *) new_var2);
  return (new_var3 + ((*((u16 *) (((u8 *) arg0) + 0x12CE))) * 0x28)) + ((long) (new_var = 0x6EC0));
}

void func_uvdyn_rom_00409A68(void) {
    D_uvdyn_rom_00411EC0 = 0;
    D_uvdyn_rom_00411EC2 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409AF0.s")

void func_uvdyn_rom_00409BC0(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x23C) = 1;
}

s32 func_uvdyn_rom_00409BCC(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A05C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A0D8.s")

s32 func_uvdyn_rom_0040A180(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A188.s")

void func_uvdyn_rom_0040AFAC(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x244);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x25C));
    }
}

void func_uvdyn_rom_0040AFD8(void *arg0, s32 arg1) {
    void (*fp)(s32, s32) = *(void (**)(s32, s32))((u8 *)arg0 + 0x248);
    if (fp != NULL) {
        fp(arg1, *(s32 *)((u8 *)arg0 + 0x260));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B00C.s")

void func_uvdyn_rom_0040B070(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x240) = arg2;
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x258) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B75C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B838.s")

void func_uvdyn_rom_0040BAA0(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411F18 = 0;
    D_uvdyn_rom_00411F1A = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BAD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BC48.s")

void func_uvdyn_rom_0040BCE4(void *arg0) {
    uvDynUpdateCollectionMemberTransforms(arg0);
    func_uvdyn_rom_0040C570(arg0);
    uvDynResetCollectionMemberState(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BD14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BFD8.s")

#line 550 "src/modules/uvdyn_rom.c"
/* Insert a unique node before the first member whose value04 is not -1,
 * or append if none qualifies. Preserve member order while shifting the tail.
 * value04's gameplay meaning is unknown. This helper has no capacity check;
 * the association setter rejects a destination count of ten. */
void uvDynInsertUniqueLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 insertionIndex;
    s32 index;
    insertionIndex = collection->count;
    for (index = 0; index < collection->count; index++) {
        if (node == collection->members[index]) {
            return;
        }
        if (insertionIndex == collection->count && collection->members[index]->value04 != -1) {
            insertionIndex = index;
        }
    }
    for (index = collection->count - 1; index >= insertionIndex; index--) {
        collection->members[index + 1] = collection->members[index];
    }
    collection->members[insertionIndex] = node;
    collection->count++;
}
#line 551 "src/modules/uvdyn_rom.c"

#line 552 "src/modules/uvdyn_rom.c"
/* Remove the first matching node and compact the remaining members.
 * Both scans use the original 16-bit index; the shifting loop reloads the count.
 * An absent node leaves the collection unchanged. */
void uvDynRemoveLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 foundIndex;
    u16 index;
    foundIndex = -1;
    for (index = 0; index < collection->count; index++) {
        if (node == collection->members[index]) {
            foundIndex = index;
            break;
        }
    }
    if (foundIndex != -1) {
        for (index = foundIndex; index < collection->count - 1; index++) {
            collection->members[index] = collection->members[index + 1];
        }
        collection->count--;
    }
}
#line 553 "src/modules/uvdyn_rom.c"

#line 554 "src/modules/uvdyn_rom.c"
/* Append a unique opaque secondary value unless the count equals twenty.
 * Preserve the original 16-bit scan and equality-only capacity guard; the
 * surrounding object's full size and the values' gameplay meaning are unknown. */
void uvDynAppendUniqueSecondaryValue(DynSecondaryCollection *collection, void *value) {
    u16 index;
    for (index = 0; index < collection->count; index++) {
        if (value == collection->members[index]) {
            return;
        }
    }
    if (collection->count == 20) {
        return;
    }
    collection->members[collection->count] = value;
    collection->count++;
}
#line 555 "src/modules/uvdyn_rom.c"

#line 556 "src/modules/uvdyn_rom.c"
/* Remove the first matching secondary value and compact the remaining list.
 * Preserve original 16-bit indices and live count reloads while shifting.
 * A missing value leaves the collection unchanged. */
void uvDynRemoveSecondaryValue(DynSecondaryCollection *collection, void *value) {
    s32 foundIndex;
    u16 index;
    foundIndex = -1;
    for (index = 0; index < collection->count; index++) {
        if (value == collection->members[index]) {
            foundIndex = index;
            break;
        }
    }
    if (foundIndex != -1) {
        for (index = foundIndex; index < collection->count - 1; index++) {
            collection->members[index] = collection->members[index + 1];
        }
        collection->count--;
    }
}
#line 557 "src/modules/uvdyn_rom.c"

#line 558 "src/modules/uvdyn_rom.c"
/* Rebuild each linked node's matrix at 0x136C and run its original follow-up
 * update. Then rebuild each secondary member's matrix at 0x98 and pass the
 * shared scalar to its update routine. Preserve 16-bit indices and count reloads;
 * the follow-up routines' broader gameplay meanings remain unresolved. */
void uvDynUpdateCollectionMemberTransforms(DynLinkedCollection *collection) {
    DynResetState *node;
    DynSecondaryState *secondary;
    u16 index;
    for (index = 0; index < collection->count; index++) {
        node = (DynResetState *)collection->members[index];
        uvDynComposeRelativeTransform(&node->matrix136C, &node->matrix12EC, &node->matrix132C);
        uvDynApplyTranslatedDobjTransform(node);
    }
    for (index = 0; index < ((DynSecondaryCollection *)collection)->count; index++) {
        secondary = ((DynSecondaryCollection *)collection)->members[index];
        uvDynComposeRelativeTransform(&secondary->matrix98, &secondary->matrix18, &secondary->matrix58);
        uvDynUpdateSecondaryStateOnce(secondary, *D_uvdyn_rom_00411DB8);
    }
}
#line 559 "src/modules/uvdyn_rom.c"

#line 560 "src/modules/uvdyn_rom.c"
/* Run the original per-member state reset for each linked node, then each
 * secondary value. Both collections are views of the same containing object;
 * the original 16-bit loops re-read their counts after each external call. */
void uvDynResetCollectionMemberState(DynLinkedCollection *collection) {
    u16 index;
    for (index = 0; index < collection->count; index++) {
        uvDynResetLinkedNodeState((DynResetState *)collection->members[index]);
    }
    for (index = 0; index < ((DynSecondaryCollection *)collection)->count; index++) {
        uvDynResetSecondaryState(((DynSecondaryCollection *)collection)->members[index]);
    }
}
#line 561 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E8E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040F78C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040FC88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004107FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410C40.s")

void func_uvdyn_rom_00410D54(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411E68 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410D80.s")

#line 591 "src/modules/uvdyn_rom.c"
/* Clear collection membership, find this state in the global registry, and
 * compact later pointers while repairing their registry indices. Preserve
 * separate original 16-bit scan and shift indices. This routine does not free
 * the state; an absent registry entry leaves the registry unchanged. */
void uvDynUnregisterSecondaryState(DynSecondaryState *state) {
    u16 index;
    u16 shiftIndex;
    s32 count;
    uvDynSetSecondaryCollection(state, NULL);
    count = D_uvdyn_rom_00411E68;
    for (index = 0; index < count; index++) {
        if (state == D_uvdyn_rom_00411DF0[index]) {
            break;
        }
    }
    if (index != count) {
        D_uvdyn_rom_00411E68--;
        for (shiftIndex = index; shiftIndex < D_uvdyn_rom_00411E68; shiftIndex++) {
            D_uvdyn_rom_00411DF0[shiftIndex] = D_uvdyn_rom_00411DF0[shiftIndex + 1];
            D_uvdyn_rom_00411DF0[shiftIndex]->registryIndex = shiftIndex;
        }
    }
}
#line 592 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410EF0.s")

#line 595 "src/modules/uvdyn_rom.c"
/* Copy the four original vector pairs and matrix into companion fields in
 * the observed order, then set the 16-bit flag at 0x1A0 to one. This copy is
 * unconditional; the flag's remaining consumers are not yet fully recovered. */
void uvDynCopySecondaryCompanionFields(DynSecondaryState *state) {
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector124, &state->vector118);
    D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix58, &state->matrix18);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector158, &state->vector14C);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector170, &state->vector164);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector188, &state->vector17C);
    state->flag1A0 = 1;
}
#line 596 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00411014(void *arg0, s32 arg1, f32 arg2) {
    if (arg0 != NULL) {
        switch (arg1) {                             /* irregular */
        case 0:
            (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) arg2;
            return;
        case 9:
            (*(s16 *)((u8 *)arg0 + 0x4)) = (s16) (u32) arg2;
            break;
        }
    }
}

#line 610 "src/modules/uvdyn_rom.c"
/* Property zero converts the signed value at 0x0C to float; property nine
 * converts the unsigned 16-bit kind. Null or unsupported properties return -1.
 * More specific meanings of the value and kind remain unresolved. */
f32 uvDynGetSecondaryScalarProperty(DynSecondaryState *state, s32 property) {
    if (state == NULL) {
        return -1.0f;
    }
    switch (property) {
        case 0:
            return state->value0C;
        case 9:
            return (u32)state->kind;
        default:
            return -1.0f;
    }
}
#line 611 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0041138C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411454.s")

s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1) {
    s32 sp4;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg1) {                                 /* irregular */
    case 3:
        sp4 = arg0 + 0x18;
        break;
    case 4:
        sp4 = arg0 + 0xD8;
        break;
    case 5:
        sp4 = arg0 + 0x98;
        break;
    }
    return sp4;
}

#line 640 "src/modules/uvdyn_rom.c"
/* Copy the selected secondary-state matrix: property three selects 0x18,
 * four selects 0xD8 and five selects 0x98. Null states or unsupported properties
 * leave output unchanged; the original requires a valid output when copying. */
void uvDynGetSecondaryMatrixProperty(DynSecondaryState *state, s32 property, Mtx4F *output) {
    if (state != NULL) {
        switch (property) {
            case 3:
                D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix18);
                break;
            case 4:
                D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrixD8);
                break;
            case 5:
                D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix98);
                break;
        }
    }
}
#line 641 "src/modules/uvdyn_rom.c"

#line 642 "src/modules/uvdyn_rom.c"
/* Reassign secondary collection membership, removing the old membership
 * before adding the new one. Null clears the link. A destination count equal
 * to twenty is rejected before the unchanged-link test, as in the original. */
void uvDynSetSecondaryCollection(DynSecondaryState *state, DynSecondaryCollection *collection) {
    if (collection != NULL && collection->count == 20) {
        return;
    }
    if (state->collection != NULL) {
        if (collection == state->collection) {
            return;
        }
        uvDynRemoveSecondaryValue(state->collection, state);
    }
    state->collection = collection;
    if (collection != NULL) {
        uvDynAppendUniqueSecondaryValue(collection, state);
    }
}
#line 643 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_004117B8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004117C0.s")

s32 func_uvdyn_rom_004118C8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x10);
}

#line 654 "src/modules/uvdyn_rom.c"
/* Skip an already updated state. When the copy flag is set and kind is one,
 * run the original matrix/vector update with the supplied scalar. Mark the
 * state updated even when that call is skipped; reset clears the flag.
 * The kind and update scalar's broader gameplay meanings remain unresolved. */
void uvDynUpdateSecondaryStateOnce(DynSecondaryState *state, f32 value) {
    if (state->updateFlag == 0) {
        if (state->copyFlag != 0) {
            if (state->kind == 1) {
                func_uvdyn_rom_00400A14(&state->matrix18, &state->matrix58,
                    &state->vector14C, &state->vector164, &state->vector17C,
                    &state->vector170, &state->vector188, value);
            }
        }
        state->updateFlag = 1;
    }
}
#line 655 "src/modules/uvdyn_rom.c"

#line 656 "src/modules/uvdyn_rom.c"
/* When the copy flag is set, copy the original four vector pairs and matrix
 * into their companion fields in the observed order. Clear both 16-bit flags
 * afterward. More specific gameplay meanings are not yet established. */
void uvDynResetSecondaryState(DynSecondaryState *state) {
    if (state->copyFlag != 0) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector188, &state->vector17C);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector158, &state->vector14C);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector170, &state->vector164);
        D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix58, &state->matrix18);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector124, &state->vector118);
    }
    state->copyFlag = 0;
    state->updateFlag = 0;
}
#line 657 "src/modules/uvdyn_rom.c"

