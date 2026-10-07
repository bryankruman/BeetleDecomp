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
    s32 registryIndex;
    s32 value04;
    u8 unk08[0xC];
    DynLinkedCollection *linkedCollection;
} DynLinkedNode;
struct DynLinkedCollection {
    s32 registryIndex;
    u16 active;
    u8 unk06[0x86];
    void **workRows;
    void *workBuffer;
    s32 count;
    DynLinkedNode *members[10];
    u8 unkC0[0xF688];
    s32 secondaryCount;
    void *secondaryMembers[20];
    u16 workCount;
    u16 valueF79E;
    u16 workFlag;
    u8 unkF7A2[2];
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
typedef struct {
    s32 registryIndex;
    u16 kind;
    u8 unk06[2];
    DynResetState *owner;
    void *intersectionRecord;
    u32 value10;
    f32 value14;
    f32 value18;
} DynAttachmentPrefix;
struct DynResetState {
    s32 registryIndex;
    u8 unk04[0x14];
    s32 attachmentCount;
    DynAttachmentPrefix *attachments[2];
    s32 dobjUpdateMode;
    s32 dobjHandle;
    s32 value2C;
    u8 unk30[0x11DC];
    s32 firstParameterCount;
    u8 unk1210[0xDC];
    Mtx4F matrix12EC;
    Mtx4F matrix132C;
    Mtx4F matrix136C;
    u8 unk13AC[0x40];
    Mtx4F matrix13EC;
    Mtx4F matrix142C;
    Vec3F vector146C;
    Vec3F vector1478;
    u32 flags1484;
    f32 value1488;
    f32 value148C;
    Vec3F translation1490;
    Vec3F vector149C;
    s32 value14A8;
    f32 value14AC;
    f32 value14B0;
    u8 unk14B4[8];
    Vec3F vector14BC;
    Vec3F vector14C8;
    u8 unk14D4[0xC];
    Vec3F vector14E0;
    Vec3F vector14EC;
    u8 unk14F8[0x34];
    Vec3F vector152C;
    Vec3F vector1538;
    u16 prepareFlag;
    u8 unk1546[0xE];
    void (*callback)(DynResetState *, void *);
    u8 unk1558[0x24];
    void *callbackContext;
};
/* Observed intersection export slots; unused entries remain opaque. */
typedef struct {
    void *unk00[8];
    void (*setTransformProperty)(void *, s32, Mtx4F *);
    u8 unk24[0x10];
    u32 (*getValue10)(void *);
    void (*setDobjHandle)(void *, s32);
    u8 unk3C[0x60];
    void (*copyRecord)(void *, void *);
} DynIsectExportPrefix;
extern DynIsectExportPrefix *D_uvdyn_rom_00411F7C;
/* The record value is compared as a positive scalar; its gameplay meaning
 * remains unresolved. Only the observed prefix is described here. */
typedef struct { u8 unk00[0x2C]; f32 value; } DynCandidateRecord;
typedef struct {
    DynCandidateRecord *record;
    s32 value;
    u16 value08;
    u16 result;
} DynCandidateRequest;
typedef struct {
    u8 unk00[0x24C];
    void (*callback)(DynCandidateRequest *, s32);
    u8 unk250[0x14];
    s32 callbackContext;
} DynCandidateCallbacks;

/* Prefix-only views of the observed intersection child list. The one-element
 * trailing array denotes the first pointer, not an inferred list capacity. */
typedef struct { u8 unk00[0x18]; u32 flags; } DynIsectChildFlags;
typedef struct { s32 count; DynIsectChildFlags *values[1]; } DynIsectChildList;
typedef struct { s32 unk00; s32 kind; DynIsectChildList children; } DynIsectValuePrefix;
typedef struct { u8 unk00[0x18]; DynIsectValuePrefix *valueRecord; } DynIsectRecordPrefix;
extern f32 D_uvdyn_rom_00411CBC;
extern f64 D_uvdyn_rom_00411CD8;
extern f64 D_uvdyn_rom_00411CE0;

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
    u8 unk130[4];
    f32 value134;
    u8 unk138[0x14];
    Vec3F vector14C;
    Vec3F vector158;
    Vec3F vector164;
    Vec3F vector170;
    Vec3F vector17C;
    Vec3F vector188;
    Vec3F vector194;
    u16 flag1A0;
    u16 copyFlag;
    u16 updateFlag;
} DynSecondaryState;

extern UvFVec_Rom_Exports *D_uvdyn_rom_00411F74;
typedef struct { Vec3F first; Vec3F second; } DynPointPair;
typedef struct { Vec3F center; f32 radius; } DynSphere;
typedef struct { u32 value; } DynCollectionWord;
/* Indexed collection views grounded in adjacent array offsets. The original
 * getters do not validate the combined collection index against these spans. */
typedef struct {
    u8 unk00[0xBBB4];
    u32 values[30];
    u16 rangeEnds[30];
    u16 kinds[30];
    DynCollectionWord words[30];
} DynIndexedCollectionFields;
typedef struct {
    u8 unk00[0x14];
    DynIndexedCollectionFields *collection;
    u8 unk18[0x12BA];
    u16 entryOffset;
    u8 unk12D4[6];
    u16 entryCount;
} DynIndexedNodeFields;

/* Parameter-bank fields observed by the indexed output helpers. Four slots
 * fit between adjacent arrays; valid counts still follow the original contract. */
typedef struct {
    u8 unk00[8];
    u32 value08;
    u32 value0C;
    u8 unk10[0x24];
    Vec3F vector34;
} DynParameterPayload;
typedef struct {
    u8 unk00[0x120C];
    s32 firstCount;
    u8 unk1210[4];
    u32 firstValues[4];
    u16 firstKinds[4];
    u32 firstKeys[4];
    Vec3F firstVectors[4];
    u8 unk126C[8];
    s32 secondCount;
    u32 secondValues[4];
    u16 secondKinds[4];
    u32 secondKeys[4];
    DynParameterPayload *secondPayloads[4];
} DynParameterBanks;
/* Prefix-only intersection callback inputs: array sizes are not established. */
typedef struct { u8 unk00[0xEE0]; u32 words[10]; u16 kinds[1]; } DynAttachmentCallbackValues;
typedef struct { u32 word; u16 kind; } DynAttachmentCallbackRequest;
typedef struct {
    u8 unk00[0xC];
    DynAttachmentCallbackValues *values;
    u8 unk10[0x244];
    void (*callback)(DynAttachmentCallbackRequest *, s32);
    u8 unk258[0x14];
    s32 callbackContext;
} DynAttachmentCallbackFields;

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
extern DynLinkedCollection *D_uvdyn_rom_00411EC8[];
extern DynLinkedCollection *D_uvdyn_rom_00411EF0[];
extern DynResetState *D_uvdyn_rom_00411DC0[];
extern u16 D_uvdyn_rom_00411F1A;
extern u16 D_uvdyn_rom_00411E68;
extern DynSecondaryState *D_uvdyn_rom_00411DF0[];
void uvDynAllocateRegisteredCollectionWorkBuffers(void);
void uvDynUpdateActiveCollections(void);
void uvDynSetGlobalScalarProperty(s32 property, f32 value);
f32 uvDynGetGlobalScalarProperty(s32 property);
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
s32 func_uvdyn_rom_004033F4(DynPointPair *points, DynSphere *sphere);
void uvDynBuildPointPairSphere(DynSphere *sphere, Vec3F *first, Vec3F *second, f32 extraRadius);
void uvDynInitNodeRegistry(void);
void func_uvdyn_rom_004035A0();
void uvDynUnregisterLinkedNodeState(DynResetState *state);
void uvDynPrepareRegisteredNodeState(void);
void uvDynPrepareLinkedNodeState(DynResetState *state);
void func_uvdyn_rom_00403A1C();
void func_uvdyn_rom_00403C38();
void func_uvdyn_rom_00403D90();
void func_uvdyn_rom_00403F98();
void func_uvdyn_rom_00404018(DynResetState *state, s32 property, Vec3F *output);
void func_uvdyn_rom_004041CC();
s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1);
void func_uvdyn_rom_004043E0(DynResetState *state, s32 property, Mtx4F *output);
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output);
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection);
void uvDynAddUniqueAttachment(DynResetState *state, DynAttachmentPrefix *attachment);
void uvDynScanAttachmentMembership(DynResetState *state, DynAttachmentPrefix *attachment);
DynAttachmentPrefix *uvDynGetAttachmentByIndex(DynResetState *state, s32 index);
void * func_uvdyn_rom_004046FC();
void uvDynSetDobjHandle(DynResetState *state, s32 handle);
void func_uvdyn_rom_00404834();
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvDynGetFirstParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector);
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second);
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second);
void uvDynGetSecondParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector, u32 *payloadValue08, u32 *payloadValue0C);
s32 uvDynGetIndexedCollectionEntry(DynIndexedNodeFields *state, u16 index, u32 *value, u16 *kind, DynCollectionWord *word);
u16 func_uvdyn_rom_00404C60(DynIndexedNodeFields *state, u16 index);
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
void uvDynUpdateNodeTranslationVector(DynResetState *state);
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
s32 uvDynTryAcceptLowerPositiveRecord(DynResetState *state, void *output, f32 *bestValue, DynCandidateRecord *candidate);
s32 func_uvdyn_rom_00409A48();
DynAttachmentPrefix *uvDynCreateAttachment(void);
void uvDynUnregisterAttachment(DynAttachmentPrefix *state);
void func_uvdyn_rom_00409BD4();
void func_uvdyn_rom_00409CE4(DynAttachmentPrefix *);
void func_uvdyn_rom_00409E18(DynAttachmentPrefix *, s32, f32);
f32 uvDynGetAttachmentScalarProperty(DynAttachmentPrefix *attachment, s32 property);
void uvDynSetAttachmentIntersection(DynAttachmentPrefix *attachment, void *intersectionRecord);
void func_uvdyn_rom_0040A188();
void func_uvdyn_rom_0040AFAC();
void func_uvdyn_rom_0040AFD8();
void uvDynInvokeAttachmentValueCallback(DynAttachmentCallbackFields *attachment, u16 index);
void func_uvdyn_rom_0040B08C();
s32 uvDynTryAcceptAttachmentRecord(DynCandidateCallbacks *attachment, void *output, f32 *bestValue, DynCandidateRecord *candidate, s32 value, u16 value08);
void func_uvdyn_rom_0040B838();
void func_uvdyn_rom_0040BAA0();
DynLinkedCollection *uvDynCreateCollection(void);
void uvDynDestroyCollection(DynLinkedCollection *collection);
void uvDynAllocateCollectionWorkBuffers(DynLinkedCollection *collection);
void uvDynUpdateCollection(DynLinkedCollection *collection);
void func_uvdyn_rom_0040BD14(DynLinkedCollection *collection, s32 property, f32 value);
f32 uvDynGetCollectionScalarProperty(DynLinkedCollection *collection, s32 property);
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
DynSecondaryState *uvDynCreateSecondaryState(void);
void uvDynUnregisterSecondaryState(DynSecondaryState *state);
void uvDynCopyRegisteredSecondaryCompanions(void);
void uvDynCopySecondaryCompanionFields(DynSecondaryState *state);
void func_uvdyn_rom_00411014(void *arg0, s32 arg1, f32 arg2);
f32 uvDynGetSecondaryScalarProperty(DynSecondaryState *state, s32 property);
void func_uvdyn_rom_00411148();
void func_uvdyn_rom_00411300();
void uvDynGetSecondaryVectorProperty(DynSecondaryState *state, s32 property, Vec3F *output);
void func_uvdyn_rom_00411454();
s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1);
void uvDynGetSecondaryMatrixProperty(DynSecondaryState *state, s32 property, Mtx4F *output);
void uvDynSetSecondaryCollection(DynSecondaryState *state, DynSecondaryCollection *collection);
void func_uvdyn_rom_004117C0();
void uvDynUpdateSecondaryStateOnce(DynSecondaryState *state, f32 value);
void uvDynResetSecondaryState(DynSecondaryState *state);
extern f32 D_uvdyn_rom_00411DB4;
extern u16 D_uvdyn_rom_00411EC0;
extern DynAttachmentPrefix *D_uvdyn_rom_00411E70[];
extern u16 D_uvdyn_rom_00411EC2;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/__entrypoint_func_uvdyn_rom_400000.s")

#line 383 "src/modules/uvdyn_rom.c"
/* Unload the ten modules imported by the dynamic-object module, preserving
 * the original order and the distinct lowercase isct / uppercase ISCT tags. */
void uvDynUnloadImportedModules(void) {
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
#line 395 "src/modules/uvdyn_rom.c"

#line 325 "src/modules/uvdyn_rom.c"
/* Allocate work buffers for every registered collection. Preserve the original
 * 16-bit index and reload the registry count after each allocation helper. */
void uvDynAllocateRegisteredCollectionWorkBuffers(void) {
    u16 index;
    for (index = 0; index < D_uvdyn_rom_00411F18; index++) {
        uvDynAllocateCollectionWorkBuffers(D_uvdyn_rom_00411EC8[index]);
    }
}
#line 326 "src/modules/uvdyn_rom.c"

#line 327 "src/modules/uvdyn_rom.c"
/* Update each active collection in registry order. Preserve the live registry
 * count and original 16-bit iteration because callees may change shared state. */
void uvDynUpdateActiveCollections(void) {
    u16 index;
    for (index = 0; index < D_uvdyn_rom_00411F1A; index++) {
        uvDynUpdateCollection(D_uvdyn_rom_00411EF0[index]);
    }
}
#line 328 "src/modules/uvdyn_rom.c"

#line 329 "src/modules/uvdyn_rom.c"
/* Store global scalar property zero; unsupported property numbers are ignored.
 * The scalar's gameplay meaning remains unresolved. */
void uvDynSetGlobalScalarProperty(s32 property, f32 value) {
    if (property == 0) {
        D_uvdyn_rom_00411DB4 = value;
    }
}
#line 334 "src/modules/uvdyn_rom.c"

#line 335 "src/modules/uvdyn_rom.c"
/* Return global scalar property zero, or -1 for an unsupported property.
 * The scalar's gameplay meaning remains unresolved. */
f32 uvDynGetGlobalScalarProperty(s32 property) {
    if (property == 0) {
        return D_uvdyn_rom_00411DB4;
    }
    return -1.0f;
}
#line 341 "src/modules/uvdyn_rom.c"

#line 342 "src/modules/uvdyn_rom.c"
/* Return the shared scalar's address for original consumers that retain its
 * live value rather than taking a scalar snapshot. */
f32 *uvDynGetGlobalScalarAddress(void) {
    return &D_uvdyn_rom_00411DB4;
}
#line 345 "src/modules/uvdyn_rom.c"

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

#line 329 "src/modules/uvdyn_rom.c"
/* Build a sphere centered at the point-pair midpoint, with radius equal to
 * half the separation plus extraRadius. Preserve the original vector-export
 * order and in-place output aliases; the original does not clamp extraRadius. */
void uvDynBuildPointPairSphere(DynSphere *sphere, Vec3F *first, Vec3F *second, f32 extraRadius) {
    D_uvdyn_rom_00411F74->uvVec3FSub(&sphere->center, second, first);
    D_uvdyn_rom_00411F74->uvVec3FScale(&sphere->center, &sphere->center, 0.5f);
    sphere->radius = D_uvdyn_rom_00411F74->uvVec3FLen(&sphere->center) + extraRadius;
    D_uvdyn_rom_00411F74->uvVec3FAdd(&sphere->center, first, &sphere->center);
}
#line 330 "src/modules/uvdyn_rom.c"

#line 331 "src/modules/uvdyn_rom.c"
/* Cache the shared scalar's address and clear the node-registry count.
 * This original initializer does not free or clear registry entries. */
void uvDynInitNodeRegistry(void) {
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411DE8 = 0;
}
#line 335 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004035A0.s")

#line 338 "src/modules/uvdyn_rom.c"
/* Clear linked-collection membership, remove the node from its registry and
 * repair later registry indices. Preserve separate 16-bit scan/shift indices and
 * live count reloads. This unregister routine does not free the node. */
void uvDynUnregisterLinkedNodeState(DynResetState *state) {
    u16 index;
    u16 shiftIndex;
    s32 count;
    uvDynSetLinkedCollection((DynLinkedNode *)state, NULL);
    count = D_uvdyn_rom_00411DE8;
    for (index = 0; index < count; index++) {
        if (state == D_uvdyn_rom_00411DC0[index]) {
            break;
        }
    }
    if (index != count) {
        D_uvdyn_rom_00411DE8--;
        for (shiftIndex = index; shiftIndex < D_uvdyn_rom_00411DE8; shiftIndex++) {
            D_uvdyn_rom_00411DC0[shiftIndex] = D_uvdyn_rom_00411DC0[shiftIndex + 1];
            D_uvdyn_rom_00411DC0[shiftIndex]->registryIndex = shiftIndex;
        }
    }
}
#line 339 "src/modules/uvdyn_rom.c"

#line 340 "src/modules/uvdyn_rom.c"
/* Prepare every registered node through the original state-copy/flag helper.
 * Keep the live count reload and original 16-bit registry index. */
void uvDynPrepareRegisteredNodeState(void) {
    u16 index;
    for (index = 0; index < D_uvdyn_rom_00411DE8; index++) {
        uvDynPrepareLinkedNodeState(D_uvdyn_rom_00411DC0[index]);
    }
}
#line 341 "src/modules/uvdyn_rom.c"

#line 342 "src/modules/uvdyn_rom.c"
/* Copy the node's original companion vectors/matrix, update each nonnull
 * attachment's intersection transform and invoke its original attachment helper.
 * Before the preparation flag equals one, set bit zero in the node and kind-zero
 * child records. Preserve original live counts, 16-bit indices and null checks;
 * nested intersection/value records still require the original valid-data contract.
 * The flag's broader gameplay meaning remains unresolved. */
void uvDynPrepareLinkedNodeState(DynResetState *state) {
    u16 attachmentIndex;
    u16 childIndex;
    DynAttachmentPrefix *attachment;
    DynIsectValuePrefix *record;
    DynIsectChildList *children;
    Mtx4F *transform;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector1478, &state->vector146C);
    transform = &state->matrix12EC;
    D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix132C, transform);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14C8, &state->vector14BC);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14EC, &state->vector14E0);
    if (state->prepareFlag != 1) {
        state->flags1484 |= 1;
    }
    for (attachmentIndex = 0; attachmentIndex < state->attachmentCount; attachmentIndex++) {
        attachment = state->attachments[attachmentIndex];
        if (attachment == NULL || attachment->intersectionRecord == NULL) {
            continue;
        }
        record = ((DynIsectRecordPrefix *)attachment->intersectionRecord)->valueRecord;
        D_uvdyn_rom_00411F7C->setTransformProperty(attachment->intersectionRecord, 3, transform);
        func_uvdyn_rom_00409CE4(attachment);
        if (state->prepareFlag == 1) {
            continue;
        }
        if (record->kind == 0) {
            children = &record->children;
            if (record->children.count != 0) {
                for (childIndex = 0; childIndex < children->count; childIndex++) {
                    children->values[childIndex]->flags |= 1;
                }
            }
        }
    }
    state->prepareFlag = 1;
}
#line 343 "src/modules/uvdyn_rom.c"

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

#line 283 "src/modules/uvdyn_rom.c"
/* Return the node's linked collection. The original requires a valid node. */
DynLinkedCollection *uvDynGetLinkedCollection(DynLinkedNode *node) {
    return node->linkedCollection;
}
#line 286 "src/modules/uvdyn_rom.c"

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

#line 291 "src/modules/uvdyn_rom.c"
/* Return the indexed attachment unless index is greater than the live count.
 * Preserve the original inclusive test and missing negative-index check; callers
 * must still supply a valid index. Null state is not supported by the original. */
DynAttachmentPrefix *uvDynGetAttachmentByIndex(DynResetState *state, s32 index) {
    if (state->attachmentCount < index) {
        return NULL;
    }
    return state->attachments[index];
}
#line 297 "src/modules/uvdyn_rom.c"

#line 298 "src/modules/uvdyn_rom.c"
/* Return the live attachment count, or zero for a null state. */
s32 uvDynGetAttachmentCount(DynResetState *state) {
    if (state == NULL) {
        return 0;
    }
    return state->attachmentCount;
}
#line 304 "src/modules/uvdyn_rom.c"

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

#line 321 "src/modules/uvdyn_rom.c"
/* Return the stored DOBJ handle; the original requires a valid state. */
s32 uvDynGetDobjHandle(DynResetState *state) {
    return state->dobjHandle;
}
#line 324 "src/modules/uvdyn_rom.c"

#line 325 "src/modules/uvdyn_rom.c"
/* Store the opaque signed word at 0x2C. The original requires a valid state;
 * a more specific gameplay meaning has not been established. */
void uvDynSetValue2C(DynResetState *state, s32 value) {
    state->value2C = value;
}
#line 328 "src/modules/uvdyn_rom.c"

#line 329 "src/modules/uvdyn_rom.c"
/* Return the opaque signed word at 0x2C from a valid state. */
s32 uvDynGetValue2C(DynResetState *state) {
    return state->value2C;
}
#line 332 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404834.s")

void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}

#line 338 "src/modules/uvdyn_rom.c"
/* Return the first parameter-bank count, or zero for a null state. This field
 * is the count consumed by the recovered first-bank indexed output helper. */
s32 uvDynGetFirstParameterCount(DynResetState *state) {
    if (state == NULL) {
        return 0;
    }
    return state->firstParameterCount;
}
#line 344 "src/modules/uvdyn_rom.c"

#line 345 "src/modules/uvdyn_rom.c"
/* Copy the indexed first-bank key/value, unsigned kind and vector into the
 * caller's outputs. Null state or index at/above the live count leaves every
 * output unchanged. Valid entries require the original four-slot count contract;
 * key/value/kind gameplay meanings remain unresolved. */
void uvDynGetFirstParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector) {
    if (state == NULL) {
        return;
    }
    if (index >= state->firstCount) {
        return;
    }
    *key = state->firstKeys[index];
    *value = state->firstValues[index];
    *kind = state->firstKinds[index];
    D_uvdyn_rom_00411F74->uvVec3FCopy(vector, &state->firstVectors[index]);
}
#line 346 "src/modules/uvdyn_rom.c"

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

#line 362 "src/modules/uvdyn_rom.c"
/* Copy the indexed second-bank key/value/kind and payload vector/words.
 * Null state or index at/above the live count leaves outputs unchanged. Preserve
 * the original payload reloads after the vector callback; payload validity and
 * the four-slot count contract remain the caller's responsibility. */
void uvDynGetSecondParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector, u32 *payloadValue08, u32 *payloadValue0C) {
    if (state == NULL) {
        return;
    }
    if (index >= state->secondCount) {
        return;
    }
    *key = state->secondKeys[index];
    *value = state->secondValues[index];
    *kind = state->secondKinds[index];
    D_uvdyn_rom_00411F74->uvVec3FCopy(vector, &state->secondPayloads[index]->vector34);
    *payloadValue08 = state->secondPayloads[index]->value08;
    *payloadValue0C = state->secondPayloads[index]->value0C;
}
#line 363 "src/modules/uvdyn_rom.c"

u16 func_uvdyn_rom_00404BA4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(u16 *)((u8 *)arg0 + 0x12DA);
}

#line 371 "src/modules/uvdyn_rom.c"
/* Copy the node-relative indexed collection value, unsigned kind and opaque
 * four-byte aggregate. Null state or index at/above its entry count returns zero
 * without changing outputs; success returns one. The combined collection index
 * wraps to sixteen bits and is not checked against the collection arrays.
 * Preserve the original cached collection pointer and aggregate-copy ABI. */
s32 uvDynGetIndexedCollectionEntry(DynIndexedNodeFields *state, u16 index, u32 *value, u16 *kind, DynCollectionWord *word) {
    u16 collectionIndex;
    DynIndexedCollectionFields *collection;
    if (state == NULL) {
        return 0;
    }
    if (index >= state->entryCount) {
        return 0;
    }
    collectionIndex = state->entryOffset + index;
    collection = state->collection;
    *value = collection->values[collectionIndex];
    *kind = collection->kinds[collectionIndex];
    *word = collection->words[collectionIndex];
    return 1;
}
#line 372 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404CE8.s")

#line 377 "src/modules/uvdyn_rom.c"
/* Invoke the optional reset callback, clear firstParameterCount, copy the observed
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
    state->firstParameterCount = 0;
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

#line 426 "src/modules/uvdyn_rom.c"
/* Update vector146C through the original matrix export unless value1488 is
 * strictly between the original double-precision thresholds -0.00001 and
 * 0.00001; within that interval, copy matrix12EC's translation. Preserve the
 * negated ordered predicate so NaNs take the original matrix-export path. */
void uvDynUpdateNodeTranslationVector(DynResetState *state) {
    if (!(state->value1488 < D_uvdyn_rom_00411CD8 && D_uvdyn_rom_00411CE0 < state->value1488)) {
        D_uvdyn_rom_00411F70->func_uvfmtx_rom_00401D0C(&state->matrix12EC, &state->vector146C, &state->vector152C);
    } else {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector146C, (Vec3F *)&state->matrix12EC.xw);
    }
}
#line 427 "src/modules/uvdyn_rom.c"

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

#line 448 "src/modules/uvdyn_rom.c"
/* Accept a lower positive record value unless the first attachment's callback
 * clears request.result. Return 1 after the original 88-byte intersection copy,
 * -1 for callback rejection, or 0 for an ineligible value. Reload the record value
 * after the callback without repeating the eligibility test, as in the original. */
s32 uvDynTryAcceptLowerPositiveRecord(DynResetState *state, void *output, f32 *bestValue, DynCandidateRecord *candidate) {
    void (*callback)(DynCandidateRequest *, s32);
    DynCandidateRequest request;
    if (candidate->value < *bestValue && 0.0f < candidate->value) {
        callback = ((DynCandidateCallbacks *)state->attachments[0])->callback;
        if (callback != NULL) {
            request.result = 1;
            request.record = candidate;
            request.value = -1;
            request.value08 = 0;
            callback(&request, ((DynCandidateCallbacks *)state->attachments[0])->callbackContext);
            if (request.result == 0) {
                return -1;
            }
        }
        *bestValue = candidate->value;
        D_uvdyn_rom_00411F7C->copyRecord(output, candidate);
        return 1;
    }
    return 0;
}
#line 449 "src/modules/uvdyn_rom.c"

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

#line 470 "src/modules/uvdyn_rom.c"
/* Allocate and zero the original 0x270-byte attachment, register its index,
 * then initialize property zero to one. The prefix type does not claim all fields;
 * allocation failure and registry capacity remain unchecked as in the original. */
DynAttachmentPrefix *uvDynCreateAttachment(void) {
    DynAttachmentPrefix *attachment;
    attachment = _uvMemAllocAlign8(0x270);
    uvMemSet(attachment, 0, 0x270);
    D_uvdyn_rom_00411E70[D_uvdyn_rom_00411EC0] = attachment;
    attachment->registryIndex = D_uvdyn_rom_00411EC0;
    D_uvdyn_rom_00411EC0++;
    func_uvdyn_rom_00409E18(attachment, 0, 1.0f);
    return attachment;
}
#line 471 "src/modules/uvdyn_rom.c"

#line 472 "src/modules/uvdyn_rom.c"
/* Set attachment property zero to zero, then remove it from the registry and
 * repair later indices. Preserve the original separate 16-bit scan/shift loops.
 * This routine does not free the attachment or clear every attachment link. */
void uvDynUnregisterAttachment(DynAttachmentPrefix *state) {
    u16 index;
    u16 shiftIndex;
    s32 count;
    func_uvdyn_rom_00409E18(state, 0, 0.0f);
    count = D_uvdyn_rom_00411EC0;
    for (index = 0; index < count; index++) {
        if (state == D_uvdyn_rom_00411E70[index]) {
            break;
        }
    }
    if (index != count) {
        D_uvdyn_rom_00411EC0--;
        for (shiftIndex = index; shiftIndex < D_uvdyn_rom_00411EC0; shiftIndex++) {
            D_uvdyn_rom_00411E70[shiftIndex] = D_uvdyn_rom_00411E70[shiftIndex + 1];
            D_uvdyn_rom_00411E70[shiftIndex]->registryIndex = shiftIndex;
        }
    }
}
#line 473 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00409BC0(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x23C) = 1;
}

s32 func_uvdyn_rom_00409BCC(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409E18.s")

#line 488 "src/modules/uvdyn_rom.c"
/* Return the attachment's unsigned kind or scalar fields 0x14/0x18.
 * Their gameplay meanings remain unresolved. Null attachments or unsupported
 * properties return -1; preserve the original unsigned kind conversion. */
f32 uvDynGetAttachmentScalarProperty(DynAttachmentPrefix *attachment, s32 property) {
    if (attachment == NULL) {
        return -1.0f;
    }
    switch (property) {
        case 0:
            return (u32)attachment->kind;
        case 1:
            return attachment->value14;
        case 2:
            return attachment->value18;
        default:
            return -1.0f;
    }
}
#line 489 "src/modules/uvdyn_rom.c"

#line 490 "src/modules/uvdyn_rom.c"
/* Replace the attachment's intersection link and refresh field 0x10 through
 * the original intersection export. For an owner in mode zero, propagate its
 * DOBJ handle. Null clears the cached word; an unchanged nonnull link is skipped.
 * The cached word's meaning remains unresolved. */
void uvDynSetAttachmentIntersection(DynAttachmentPrefix *attachment, void *intersectionRecord) {
    if (attachment->intersectionRecord != NULL && intersectionRecord == attachment->intersectionRecord) {
        return;
    }
    attachment->intersectionRecord = intersectionRecord;
    if (intersectionRecord != NULL) {
        attachment->value10 = D_uvdyn_rom_00411F7C->getValue10(intersectionRecord);
        if (attachment->owner != NULL && attachment->owner->dobjUpdateMode == 0) {
            D_uvdyn_rom_00411F7C->setDobjHandle(intersectionRecord, attachment->owner->dobjHandle);
        }
    } else {
        attachment->value10 = 0;
    }
}
#line 491 "src/modules/uvdyn_rom.c"

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

#line 512 "src/modules/uvdyn_rom.c"
/* If installed, invoke the attachment callback with the indexed intersection
 * word and unsigned kind in the original request layout, plus its opaque context
 * word. Preserve the cached callback and original unchecked index/data contract;
 * no narrower gameplay meaning is established for the request values. */
void uvDynInvokeAttachmentValueCallback(DynAttachmentCallbackFields *attachment, u16 index) {
    void (*callback)(DynAttachmentCallbackRequest *, s32);
    DynAttachmentCallbackRequest request;
    callback = attachment->callback;
    if (callback != NULL) {
        request.word = attachment->values->words[index];
        request.kind = attachment->values->kinds[index];
        callback(&request, attachment->callbackContext);
    }
}
#line 513 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_0040B070(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x240) = arg2;
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x258) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B08C.s")

#line 524 "src/modules/uvdyn_rom.c"
/* Accept a lower positive record value, allowing an attachment callback to
 * reject it when value is nonnegative. A negative value bypasses the callback.
 * Return 1 for the original 88-byte copy, -1 for rejection, otherwise 0. Preserve
 * callback mutations and the original post-callback value reload. */
s32 uvDynTryAcceptAttachmentRecord(DynCandidateCallbacks *attachment, void *output, f32 *bestValue, DynCandidateRecord *candidate, s32 value, u16 value08) {
    void (*callback)(DynCandidateRequest *, s32);
    DynCandidateRequest request;
    if (candidate->value < *bestValue && 0.0f < candidate->value) {
        if (value >= 0) {
            callback = attachment->callback;
            if (callback != NULL) {
                request.result = 1;
                request.record = candidate;
                request.value = value;
                request.value08 = value08;
                callback(&request, attachment->callbackContext);
                if (request.result == 0) {
                    return -1;
                }
            }
        }
        *bestValue = candidate->value;
        D_uvdyn_rom_00411F7C->copyRecord(output, candidate);
        return 1;
    }
    return 0;
}
#line 525 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B838.s")

void func_uvdyn_rom_0040BAA0(void) {
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411F18 = 0;
    D_uvdyn_rom_00411F1A = 0;
}

#line 534 "src/modules/uvdyn_rom.c"
/* Allocate and zero the original 0xF7A4-byte collection, append it to the
 * registry, and initialize properties zero and one. Preserve the original
 * unchecked allocation and registry-capacity contracts. */
DynLinkedCollection *uvDynCreateCollection(void) {
    DynLinkedCollection *collection;
    collection = _uvMemAllocAlign8(sizeof(DynLinkedCollection));
    uvMemSet(collection, 0, sizeof(DynLinkedCollection));
    D_uvdyn_rom_00411EC8[D_uvdyn_rom_00411F18] = collection;
    collection->registryIndex = D_uvdyn_rom_00411F18;
    D_uvdyn_rom_00411F18++;
    func_uvdyn_rom_0040BD14(collection, 0, 0.0f);
    func_uvdyn_rom_0040BD14(collection, 1, 0.0f);
    return collection;
}
#line 535 "src/modules/uvdyn_rom.c"

#line 536 "src/modules/uvdyn_rom.c"
/* Set collection property zero to zero, find its registry entry, free the
 * collection and compact later pointers/indices. An absent entry is not freed.
 * Preserve the original separate 16-bit loops and live count reloads. This routine
 * makes no explicit frees of the collection's separately allocated work buffers. */
void uvDynDestroyCollection(DynLinkedCollection *collection) {
    u16 index;
    u16 shiftIndex;
    s32 count;
    func_uvdyn_rom_0040BD14(collection, 0, 0.0f);
    count = D_uvdyn_rom_00411F18;
    for (index = 0; index < count; index++) {
        if (collection == D_uvdyn_rom_00411EC8[index]) {
            break;
        }
    }
    if (index != count) {
        _uvMemFree(collection);
        D_uvdyn_rom_00411F18--;
        for (shiftIndex = index; shiftIndex < D_uvdyn_rom_00411F18; shiftIndex++) {
            D_uvdyn_rom_00411EC8[shiftIndex] = D_uvdyn_rom_00411EC8[shiftIndex + 1];
            D_uvdyn_rom_00411EC8[shiftIndex]->registryIndex = shiftIndex;
        }
    }
}
#line 537 "src/modules/uvdyn_rom.c"

#line 538 "src/modules/uvdyn_rom.c"
/* Allocate the collection's two 80-byte work buffers and twenty zeroed
 * 80-byte rows, then set its work flag. The original does not check allocation
 * results or release previous buffers; callers must satisfy its init contract. */
void uvDynAllocateCollectionWorkBuffers(DynLinkedCollection *collection) {
    u16 index;
    collection->workCount = 0;
    collection->workBuffer = _uvMemAllocAlign8(0x50);
    collection->workRows = _uvMemAllocAlign8(0x50);
    for (index = 0; index < 20; index++) {
        collection->workRows[index] = _uvMemAllocAlign8(0x50);
        uvMemSet(collection->workRows[index], 0, 0x50);
    }
    collection->workFlag = 1;
}
#line 539 "src/modules/uvdyn_rom.c"

#line 540 "src/modules/uvdyn_rom.c"
/* Update member transforms, execute the original collection work helper,
 * then reset member state in the observed order. The middle helper remains
 * unrecovered; this existing C wrapper is naming/type cleanup, not new recovery. */
void uvDynUpdateCollection(DynLinkedCollection *collection) {
    uvDynUpdateCollectionMemberTransforms(collection);
    func_uvdyn_rom_0040C570(collection);
    uvDynResetCollectionMemberState(collection);
}
#line 545 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BD14.s")

#line 548 "src/modules/uvdyn_rom.c"
/* Return collection property zero (active state) or one (field 0xF79E),
 * converting the unsigned 16-bit field through u32 as in the original.
 * Null collections and unsupported properties return -1. */
f32 uvDynGetCollectionScalarProperty(DynLinkedCollection *collection, s32 property) {
    if (collection == NULL) {
        return -1.0f;
    }
    switch (property) {
        case 0:
            return (u32)collection->active;
        case 1:
            return (u32)collection->valueF79E;
        default:
            return -1.0f;
    }
}
#line 549 "src/modules/uvdyn_rom.c"

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
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411E68 = 0;
}

#line 589 "src/modules/uvdyn_rom.c"
/* Allocate and zero the original 0x1A8-byte secondary state, register it,
 * initialize matrices 0x18 and 0xD8 to identity and explicitly clear scalar 0x134.
 * Preserve the original unchecked allocation and registry-capacity contract. */
DynSecondaryState *uvDynCreateSecondaryState(void) {
    DynSecondaryState *state;
    state = _uvMemAllocAlign8(sizeof(DynSecondaryState));
    uvMemSet(state, 0, sizeof(DynSecondaryState));
    D_uvdyn_rom_00411DF0[D_uvdyn_rom_00411E68] = state;
    state->registryIndex = D_uvdyn_rom_00411E68;
    D_uvdyn_rom_00411E68++;
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&state->matrix18);
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&state->matrixD8);
    state->value134 = 0.0f;
    return state;
}
#line 590 "src/modules/uvdyn_rom.c"

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

#line 593 "src/modules/uvdyn_rom.c"
/* Copy companion fields for every registered secondary state. Preserve the
 * original 16-bit index and reload the registry count after each copy. */
void uvDynCopyRegisteredSecondaryCompanions(void) {
    u16 index;
    for (index = 0; index < D_uvdyn_rom_00411E68; index++) {
        uvDynCopySecondaryCompanionFields(D_uvdyn_rom_00411DF0[index]);
    }
}
#line 594 "src/modules/uvdyn_rom.c"

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

#line 616 "src/modules/uvdyn_rom.c"
/* Copy secondary vector properties 2, 7 and 8 through the vector export;
 * property 3 reads matrix18's translation components directly. A null state or
 * unsupported property leaves the output unchanged. */
void uvDynGetSecondaryVectorProperty(DynSecondaryState *state, s32 property, Vec3F *output) {
    if (state == NULL) {
        return;
    }
    switch (property) {
        case 2:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector194);
            break;
        case 3:
            output->x = state->matrix18.xw;
            output->y = state->matrix18.yw;
            output->z = state->matrix18.zw;
            break;
        case 7:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector14C);
            break;
        case 8:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector17C);
            break;
    }
}
#line 617 "src/modules/uvdyn_rom.c"

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

