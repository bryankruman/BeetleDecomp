/* Preserve the original readonly prefix through native ASM ownership.
 * The later assembly function hosts the original suffix for layout only;
 * tools/moduleReadonlyLayout.py validates and regenerates both spans. */
#pragma GLOBAL_ASM("asm/us/data/modules/uvdyn_rom.rodata-prefix.s")
#line 1 "src/modules/uvdyn_rom.c"
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
#include "uvmath_rom.h"
#include "uvasset_types.h"
extern UvMath_Exports *D_uvdyn_rom_00411F80;
extern UvDobj_Exports *D_uvdyn_rom_00411F84;

typedef struct { Vec3F center; f32 radius; } DynSphere;
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
    s32 value04;
    u8 unk08[0x10];
    s32 attachmentCount;
    DynAttachmentPrefix *attachments[2];
    s32 dobjUpdateMode;
    s32 dobjHandle;
    s32 value2C;
    u8 unk30[0x11DC];
    s32 firstParameterCount;
    u16 flag1210;
    u8 unk1212[0xA4];
    u16 parameterFlag;
    u8 unk12B8[0x24];
    DynSphere sphere12DC;
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
    f32 value14B4;
    s32 value14B8;
    Vec3F vector14BC;
    Vec3F vector14C8;
    u8 unk14D4[0xC];
    Vec3F vector14E0;
    Vec3F vector14EC;
    u8 unk14F8[0x34];
    Vec3F vector152C;
    Vec3F vector1538;
    u16 prepareFlag;
    u8 unk1546[6];
    u16 flag154C;
    u8 unk154E[6];
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
    u8 unk3C[4];
    void (*setQueryRecordBank)(u16, void *, void *, void *);
    u8 unk44[0x58];
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
/* Kind-one value view used by attachment delta preparation. Other kinds
 * retain the separate child-list prefix and are not interpreted here. */
typedef struct { u8 unk00[4]; s32 kind; u8 unk08[0x10]; Vec3F vector18; } DynIsectKindOneValue;
typedef struct { Vec3F first; Vec3F delta; f32 length; } DynAttachmentDeltaFields;
typedef struct DynAttachmentUpdateState DynAttachmentUpdateState;
struct DynAttachmentUpdateState {
    u8 unk00[8];
    DynResetState *owner;
    DynIsectRecordPrefix *intersectionRecord;
    u8 unk10[0xC];
    DynAttachmentDeltaFields vectors;
    u8 unk38[0x208];
    void (*callback)(DynAttachmentUpdateState *, s32);
    u8 unk244[0x14];
    s32 callbackContext;
};

/* Separate invocation views retain each observed callback ABI and context slot. */
typedef struct {
    u8 unk00[0x244];
    void (*callback244)(void *, s32);
    void (*callback248)(s32, s32);
    u8 unk24C[0x10];
    s32 context25C;
    s32 context260;
} DynAttachmentCallbackSlots;

extern f32 D_uvdyn_rom_00411D00;
/* Adjacent original arrays establish 220 slots of 0x78-byte records and
 * two 220-word result banks. This selector keeps the original unchecked index. */
typedef struct { u8 bytes[0x78]; } DynIntersectionQueryRecord;
typedef struct {
    u8 unk00[0xC0];
    DynIntersectionQueryRecord records[220];
    u32 firstWords[220];
    u32 secondWords[220];
} DynIntersectionQueryBanks;

/* Prefix-only variable-count vector sequences. The trailing one-element
 * arrays describe the first slot, not an established storage capacity. */
typedef struct { Vec3F first; Vec3F second; u8 unk18[4]; } DynIsectVectorPairRecord;
typedef struct {
    s32 count;
    u8 unk04[0x50];
    DynIsectVectorPairRecord records[1];
} DynIsectVectorPairList;
typedef struct { u8 unk00[0x1C]; Vec3F vectors[1]; } DynAttachmentVectorSequence;


extern f32 D_uvdyn_rom_00411CBC;
extern f64 D_uvdyn_rom_00411CD8;
extern f64 D_uvdyn_rom_00411CE0;
extern f64 D_uvdyn_rom_00411D38;
extern f64 D_uvdyn_rom_00411D40;
extern f64 D_uvdyn_rom_00411D68;
extern f64 D_uvdyn_rom_00411D70;
extern f64 D_uvdyn_rom_00411D78;
extern f64 D_uvdyn_rom_00411D80;

extern UvFMtx_Rom_Exports *D_uvdyn_rom_00411F70;
/* Prefix fields observed in the secondary-state copy/reset routine. */
typedef struct {
    s32 registryIndex;
    u16 kind;
    u8 unk06[2];
    DynSecondaryCollection *collection;
    s32 value0C;
    s32 dobjHandle;
    s32 lodIndex;
    Mtx4F matrix18;
    Mtx4F matrix58;
    Mtx4F matrix98;
    Mtx4F matrixD8;
    Vec3F vector118;
    Vec3F vector124;
    u8 unk130[4];
    f32 value134;
    f32 radius138;
    DynSphere sphere13C;
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
void uvDynSolveFactoredSystemInPlace(f32 **matrix, s32 count, s32 *permutation, f32 *values);
void func_uvdyn_rom_00402E38();
void func_uvdyn_rom_00403294();
s32 func_uvdyn_rom_004033F4(DynPointPair *points, DynSphere *sphere);
void uvDynBuildPointPairSphere(DynSphere *sphere, Vec3F *first, Vec3F *second, f32 extraRadius);
void uvDynInitNodeRegistry(void);
DynResetState *uvDynCreateLinkedNodeState(void);
void uvDynUnregisterLinkedNodeState(DynResetState *state);
void uvDynPrepareRegisteredNodeState(void);
void uvDynPrepareLinkedNodeState(DynResetState *state);
void func_uvdyn_rom_00403A1C(DynResetState *, s32, f32);
f32 uvDynGetNodeScalarProperty(DynResetState *state, s32 property);
void func_uvdyn_rom_00403D90(DynResetState *, s32, Vec3F);
void func_uvdyn_rom_00403F98();
void uvDynGetNodeVectorProperty(DynResetState *state, s32 property, Vec3F *output);
void uvDynSetNodeMatrixProperty(DynResetState *, s32, Mtx4F *);
s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1);
void uvDynGetNodeMatrixProperty(DynResetState *state, s32 property, Mtx4F *output);
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output);
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection);
void uvDynAddUniqueAttachment(DynResetState *state, DynAttachmentPrefix *attachment);
void uvDynScanAttachmentMembership(DynResetState *state, DynAttachmentPrefix *attachment);
DynAttachmentPrefix *uvDynGetAttachmentByIndex(DynResetState *state, s32 index);
void * uvDynGetNestedRecord();
void uvDynSetDobjHandle(DynResetState *state, s32 handle);
void func_uvdyn_rom_00404834();
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void uvDynGetFirstParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector);
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second);
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second);
void uvDynGetSecondParameterEntry(DynParameterBanks *state, u16 index, u32 *key, u32 *value, u16 *kind, Vec3F *vector, u32 *payloadValue08, u32 *payloadValue0C);
s32 uvDynGetIndexedCollectionEntry(DynIndexedNodeFields *state, u16 index, u32 *value, u16 *kind, DynCollectionWord *word);
u16 uvDynGetIndexedRangeLength(DynIndexedNodeFields *state, u16 index);
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
s32 uvDynGetLinkedRecordAddress();
DynAttachmentPrefix *uvDynCreateAttachment(void);
void uvDynUnregisterAttachment(DynAttachmentPrefix *state);
void uvDynUpdateAttachmentDelta(DynAttachmentUpdateState *attachment);
void uvDynRefreshAttachmentVectors(DynAttachmentPrefix *);
void func_uvdyn_rom_00409E18(DynAttachmentPrefix *, s32, f32);
f32 uvDynGetAttachmentScalarProperty(DynAttachmentPrefix *attachment, s32 property);
void uvDynSetAttachmentIntersection(DynAttachmentPrefix *attachment, void *intersectionRecord);
void func_uvdyn_rom_0040A188();
void uvDynInvokeAttachmentCallback244(DynAttachmentCallbackSlots *attachment);
void uvDynInvokeAttachmentValueCallback248(DynAttachmentCallbackSlots *attachment, s32 value);
void uvDynInvokeAttachmentValueCallback(DynAttachmentCallbackFields *attachment, u16 index);
void func_uvdyn_rom_0040B08C();
s32 uvDynTryAcceptAttachmentRecord(DynCandidateCallbacks *attachment, void *output, f32 *bestValue, DynCandidateRecord *candidate, s32 value, u16 value08);
void func_uvdyn_rom_0040B838();
void uvDynBindGlobalScalarAndResetCounts();
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
void uvDynBuildCollectionMemberSpheres(DynLinkedCollection *);
void func_uvdyn_rom_0040C570();
void func_uvdyn_rom_0040E4E8();
void func_uvdyn_rom_0040E8E8();
void func_uvdyn_rom_0040F78C();
void func_uvdyn_rom_0040FC88();
void func_uvdyn_rom_00410250();
void func_uvdyn_rom_004107FC();
void uvDynSetIndexedQueryRecordBank(DynIntersectionQueryBanks *, u16, u16);
void func_uvdyn_rom_00410AEC();
void func_uvdyn_rom_00410C40();
void uvDynBindGlobalScalarAndClearFlag();
DynSecondaryState *uvDynCreateSecondaryState(void);
void uvDynUnregisterSecondaryState(DynSecondaryState *state);
void uvDynCopyRegisteredSecondaryCompanions(void);
void uvDynCopySecondaryCompanionFields(DynSecondaryState *state);
void uvDynSetSecondaryScalarProperty(DynSecondaryState *state, s32 property, f32 value);
f32 uvDynGetSecondaryScalarProperty(DynSecondaryState *state, s32 property);
void uvDynSetSecondaryVectorProperty(DynSecondaryState *state, s32 property, Vec3F vector);
void func_uvdyn_rom_00411300();
void uvDynGetSecondaryVectorProperty(DynSecondaryState *state, s32 property, Vec3F *output);
void uvDynSetSecondaryMatrixProperty(DynSecondaryState *, s32, Mtx4F *);
s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1);
void uvDynGetSecondaryMatrixProperty(DynSecondaryState *state, s32 property, Mtx4F *output);
void uvDynSetSecondaryCollection(DynSecondaryState *state, DynSecondaryCollection *collection);
void uvDynSetSecondaryModelLod(DynSecondaryState *, s32, s32);
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

/* Original ranked-vector wrapper: sum/normalize the second vector bank,
 * use (0,0,1) only for reported normalization failure, then rank scalar/dot
 * inputs through direct0x400E40 before delegating to direct0x401014.
 * Original scratch comprises two f32[3] banks and two Vec3F-pointer[3] banks,
 * not four copied vectors: E40's capacity is3-startIndex and this caller
 * supplies startIndex0/count0. Only the selected prefix is initialized.
 * Each native zero/nonzero-dot branch reads its scalar after the FP compare;
 * an exact zero uses priority1, while unordered dots take native division.
 * RE_UNKNOWN: vector frame, scalar units, matrix alias/input domains and
 * complete historical source declarations. Trace original caller buffers
 * and helper0x401014 consumers before assigning physical/ownership names.
 * RE_UNKNOWN: original local organization and constant lifetimes. Typed C
 * retains the observed operations and helper argument bits, but still differs
 * in frame/spill layout and scheduling after the bounded native-read trial;
 * original declarations or new contract evidence is needed for matching. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400C08.s")
#line 312 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040232C.s")

#line 321 "src/modules/uvdyn_rom.c"
/* Apply the recorded row permutation and forward substitution, skipping the
 * initial zero right-hand side, then solve the upper triangular factor backward.
 * Matrix rows and permutation indices are zero-based. The caller supplies a
 * valid factorization with nonzero diagonal entries; values is overwritten. */
void uvDynSolveFactoredSystemInPlace(f32 **matrix, s32 count, s32 *permutation, f32 *values) {
    s32 row, column, pivot, first = 0;
    f32 sum;
    for (row = 0; row < count; row++) {
        pivot = permutation[row];
        sum = values[pivot];
        values[pivot] = values[row];
        if (first != 0) {
            for (column = first - 1; column <= row - 1; column++) {
                sum -= matrix[row][column] * values[column];
            }
        } else if (sum != 0.0f) {
            first = row + 1;
        }
        values[row] = sum;
    }
    for (row = count - 1; row >= 0; row--) {
        sum = values[row];
        for (column = row + 1; column < count; column++) {
            sum -= matrix[row][column] * values[column];
        }
        values[row] = sum / matrix[row][row];
    }
}
#line 322 "src/modules/uvdyn_rom.c"

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

#line 336 "src/modules/uvdyn_rom.c"
/* Allocate and register a zeroed 0x15A0-byte node, then initialize the original
 * scalar/vector properties, three matrices and state flags in order. Preserve
 * the original unchecked allocation and registry-capacity contract. The prefix
 * type describes observed fields without claiming the full object layout. */
DynResetState *uvDynCreateLinkedNodeState(void) {
    DynResetState *state;
    Vec3F vector;
    state = _uvMemAllocAlign8(0x15A0);
    uvMemSet(state, 0, 0x15A0);
    D_uvdyn_rom_00411DC0[D_uvdyn_rom_00411DE8] = state;
    state->registryIndex = D_uvdyn_rom_00411DE8;
    D_uvdyn_rom_00411DE8++;
    func_uvdyn_rom_00403A1C(state, 2, 1.0f);
    func_uvdyn_rom_00403A1C(state, 10, 0.02f);
    vector.x = 1.0f;
    vector.y = 1.0f;
    vector.z = 1.0f;
    func_uvdyn_rom_00403D90(state, 5, vector);
    vector.x = 0.0f;
    vector.y = 0.0f;
    vector.z = 0.0f;
    func_uvdyn_rom_00403D90(state, 4, vector);
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&state->matrix12EC);
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&state->matrix13EC);
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&state->matrix142C);
    state->parameterFlag = 0;
    state->flag154C = 0;
    state->flag1210 = 1;
    state->value04 = -1;
    state->value1488 = 0.0f;
    func_uvdyn_rom_00403A1C(state, 14, -1.0f);
    state->value14B8 = 0;
    return state;
}
#line 337 "src/modules/uvdyn_rom.c"

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
        uvDynRefreshAttachmentVectors(attachment);
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

/* Set scalar properties through original15-entry table D_uvdyn_rom_00411AE0.
 * Supported selectors are0/2/9/10/11/12/13/14; null nodes and other selectors
 * return without mutation. Selector2 stores1528/1524/1520 in that order.
 * Selector0 converts to signed32 at0x24; when zero, iterate attachments1C
 * using count18 and publish state word28 through actual lowercase-isct38.
 * That export targets0x400B90 and stores the word at intersection-record08.
 * Selectors11/12 use native unsigned32 float conversion then low16 stores
 * at154C/1210; selectors13/14 signed conversion stores04/10. Others store
 * f32 at14AC/12B0. Retain low16 iteration and post-call count/provider reads.
 * RE_UNKNOWN: physical property meanings/units, supported float input domains,
 * complete attachment capacity and caller guarantees. Trace original constants,
 * setters/getters and callers before adding validation or naming quantities.
 * RE_UNKNOWN: historical source/local organization. Readable C preserves these
 * effects and types but uses different live count/attachment registers, shifting
 * subsequent temporary allocations. Native table ownership also remains here;
 * retain original assembly until complete code and readonly proofs succeed. */
#line 344 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403A1C.s")

#line 346 "src/modules/uvdyn_rom.c"
/* Read a scalar property with the original numeric conversion to float.
 * Null nodes and unsupported properties return -1.0f.
 * RE_UNKNOWN: property meanings and units beyond these observed field widths;
 * trace the matching setter, property constants and callers before naming
 * the unresolved fields or changing conversions. Node lifetime/ownership and
 * whether -1.0f is distinguished from a stored negative value are also
 * unproved; trace registry ownership and caller result checks before assuming
 * either contract. */
f32 uvDynGetNodeScalarProperty(DynResetState *state, s32 property) {
    if (state == NULL) {
        return -1.0f;
    }
    switch (property) {
        case 2: return *(f32 *)((u8 *)state + 0x1524);
        case 0: return state->dobjUpdateMode;
        case 8: return state->value14A8;
        case 9: return state->value14AC;
        case 11: return state->flag154C;
        case 10: return *(f32 *)((u8 *)state + 0x12B0);
        case 12: return state->flag1210;
        case 13: return state->value04;
        case 14: return *(s32 *)((u8 *)state + 0x10);
        case 23: return *(u16 *)((u8 *)state + 0x151C);
        case 24: return *(f32 *)((u8 *)state + 0x30);
        case 26: return *(u16 *)((u8 *)state + 0x12B4);
        case 27: return state->registryIndex;
        default: return -1.0f;
    }
}
#line 347 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s")

/* Original node-vector address selector. Null state returns zero. The native
 * table maps properties 2/3/5 to zero and 4/6/7/17/18 to field addresses
 * 0x1490/0x131C/0x149C/0x14BC/0x14E0, respectively.
 * RE_ORIGINAL_QUIRK: with nonnull state, properties 8 through 16 and selectors
 * outside 2 through 18 reach the load from stack+4 without any preceding store
 * to that local in this invocation. Preserve the native path; do not invent a
 * default pointer or assume a confirmed player-visible failure.
 * RE_UNKNOWN: whether original callers can select those paths and what storage
 * precedes the call. Trace the exported selector's direct/indirect callers and
 * property domains before proposing a separate runtime correction.
 * RE_UNKNOWN: vector-property meanings, coordinate frames, lifetime/ownership
 * and allowed aliases. Trace returned-address consumers before semantic naming. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403F98.s")
#line 351 "src/modules/uvdyn_rom.c"

#line 352 "src/modules/uvdyn_rom.c"

/* Copy the original selected node vector into output. Property 19 instead
 * applies the native FMTX direction transform to vector14BC through matrix12EC.
 * A null state or unsupported property leaves output untouched.
 * RE_UNKNOWN: physical meanings/units and coordinate frames of the numbered
 * properties, supported input/output alias domains, and caller output capacity.
 * Trace original property producers and export callers before adding those
 * contracts; this view uses only the established Vec3F field/copy widths. */
void uvDynGetNodeVectorProperty(DynResetState *state, s32 property, Vec3F *output) {
    if (state != NULL) {
        switch (property) {
        case 3:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector152C);
            break;
        case 5:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector1538);
            break;
        case 6:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, (Vec3F *)&state->matrix12EC.xw);
            break;
        case 7:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector149C);
            break;
        case 17:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector14BC);
            break;
        case 19:
            D_uvdyn_rom_00411F70->uvMat4TransformDirection(&state->matrix12EC,
                output, &state->vector14BC);
            break;
        case 18:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector14E0);
            break;
        case 20:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector14C8);
            break;
        case 21:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->vector14EC);
            break;
        case 4:
            D_uvdyn_rom_00411F74->uvVec3FCopy(output, &state->translation1490);
            break;
        }
    }
}
#line 353 "src/modules/uvdyn_rom.c"

#line 354 "src/modules/uvdyn_rom.c"
/* Matrix properties 6, 16 and 15 update the node's related transform caches.
 * Property 6 also clears the orientation translation, rebuilds the relative
 * transform and applies the translated DOBJ transform. Each supported property
 * refreshes the node translation vector; null and unsupported properties do nothing. */
void uvDynSetNodeMatrixProperty(DynResetState *state, s32 property, Mtx4F *input) {
    if (state == NULL) {
        return;
    }
    switch (property) {
        case 6:
            D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix12EC, input);
            uvDynUpdateNodeTranslationVector(state);
            D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix13EC, input);
            state->matrix13EC.xw = 0.0f;
            state->matrix13EC.yw = 0.0f;
            state->matrix13EC.zw = 0.0f;
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&state->matrix142C, &state->matrix13EC);
            uvDynComposeRelativeTransform(&state->matrix136C, &state->matrix12EC, &state->matrix132C);
            uvDynApplyTranslatedDobjTransform(state);
            break;
        case 16:
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix142C, input);
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&state->matrix13EC, &state->matrix142C);
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix12EC, &state->matrix13EC);
            uvDynUpdateNodeTranslationVector(state);
            break;
        case 15:
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix13EC, input);
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&state->matrix142C, input);
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix12EC, input);
            uvDynUpdateNodeTranslationVector(state);
            break;
    }
}
#line 355 "src/modules/uvdyn_rom.c"

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

#line 376 "src/modules/uvdyn_rom.c"
/* Copy the selected existing node matrix into output through FMTX slot0x0C.
 * Properties6,16,15,22,25 select offsets12EC,142C,13EC,132C,136C.
 * Null state or an unsupported property leaves output unchanged.
 * RE_UNKNOWN: public property-enum names and the coordinate-space
 * convention of each stored matrix; trace writers and actual consumers
 * before assigning world/local/view labels. Preserve unchecked output. */
void uvDynGetNodeMatrixProperty(DynResetState *state, s32 property, Mtx4F *output) {
    if (state == NULL) {
        return;
    }
    switch (property) {
        case 6:
            D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix12EC);
            break;
        case 16:
            D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix142C);
            break;
        case 15:
            D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix13EC);
            break;
        case 22:
            D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix132C);
            break;
        case 25:
            D_uvdyn_rom_00411F70->uvMat4FCopy(output, &state->matrix136C);
            break;
    }
}
#line 377 "src/modules/uvdyn_rom.c"

#line 378 "src/modules/uvdyn_rom.c"
/* Store the opaque value at 0x14B8; null state is an original no-op. */
void uvDynSetValue14B8(DynResetState *state, s32 value) {
    if (state == NULL) {
        return;
    }
    state->value14B8 = value;
}
#line 384 "src/modules/uvdyn_rom.c"

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

#line 305 "src/modules/uvdyn_rom.c"
/* Return the selected 0x170-byte nested record at state offset 0x3AC.
 * Preserve the original inclusive upper check and lack of negative-index
 * or null-state validation; callers must establish a valid slot. */
void *uvDynGetNestedRecord(void *state, s32 index) {
    if (*(s32 *)((u8 *)state + 0x38) < index) {
        return NULL;
    }
    return (void *)((u8 *)state + index * 0x170 + 0x3AC);
}
#line 311 "src/modules/uvdyn_rom.c"

#line 312 "src/modules/uvdyn_rom.c"
/* Return zero for a null dynamic state, otherwise its original nested
 * record count at offset 0x38. */
s32 uvDynGetNestedRecordCount(void *state) {
    if (state == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)state + 0x38);
}
#line 318 "src/modules/uvdyn_rom.c"

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

#line 335 "src/modules/uvdyn_rom.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
#line 337 "src/modules/uvdyn_rom.c"

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

#line 351 "src/modules/uvdyn_rom.c"
/* Clear the vector-parameter flag in a valid node state. */
void uvDynClearParameterFlag(DynResetState *state) {
    state->parameterFlag = 0;
}
#line 354 "src/modules/uvdyn_rom.c"

#line 355 "src/modules/uvdyn_rom.c"
/* Return the second parameter-bank count, or zero for a null state. */
s32 uvDynGetSecondParameterCount(DynParameterBanks *state) {
    if (state == NULL) {
        return 0;
    }
    return state->secondCount;
}
#line 361 "src/modules/uvdyn_rom.c"

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

#line 364 "src/modules/uvdyn_rom.c"
/* Return the indexed entry count, or zero for a null state. */
u16 uvDynGetIndexedEntryCount(DynIndexedNodeFields *state) {
    if (state == NULL) {
        return 0;
    }
    return state->entryCount;
}
#line 370 "src/modules/uvdyn_rom.c"

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

#line 373 "src/modules/uvdyn_rom.c"
/* Return the inclusive first range length or the difference between adjacent
 * range endpoints, truncated to u16. Null state returns zero; the original
 * indexed collection bounds remain the caller's responsibility. */
u16 uvDynGetIndexedRangeLength(DynIndexedNodeFields *state, u16 index) {
    u16 result;
    if (state == NULL) return 0;
    if (index == 0 && state->entryOffset == 0) result = state->collection->rangeEnds[0] + 1;
    else result = state->collection->rangeEnds[state->entryOffset + index] - state->collection->rangeEnds[state->entryOffset + index - 1];
    return result;
}
#line 374 "src/modules/uvdyn_rom.c"

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

/* Original positive-projection displacement wrapper: ISCT slot 0x94 may flip
 * record.vector34 using state.vector1478 and the attachment's signed terrain
 * index. Only ordered positive dot products continue to the vector-pair query.
 * The native query input is 28 bytes with word18=1; its output copy is 88 bytes.
 * Success scales by output.value2C, updates both translation/vector storage,
 * calls 0x408DC8, and propagates the explicit integer result from 0x408ACC.
 * Failure uses the separate 0.1f fallback and returns 1; other projections
 * return 0. Native readonly multipliers remain original external objects.
 * RE_UNKNOWN: vector frame/units, record-vector normalization, word18's full
 * mode-dependent representation, and supported record-kind/query combinations.
 * Trace original record/input producers and ISCT query-mode setters to resolve
 * these; word18 has other observed word/pointer uses in the query providers.
 * RE_UNKNOWN: complete attachment/storage ownership and allowed alias domains.
 * Trace original attachment and state producers before adding ownership claims.
 * RE_UNKNOWN: original local declarations and expression lifetimes. The bounded
 * typed trial retains call/branch positions and relocation targets but differs
 * in 17 stack-local addresses and one floating-add operand order. New original
 * declaration/dataflow evidence is needed; do not replace this ASM with draft C. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040771C.s")
#line 423 "src/modules/uvdyn_rom.c"

/* Original node vector-pair query/record adjustment wrapper. The first query
 * uses the original range halfwords and vector pair at 0x146C/0x1478. When
 * value04 is -1, query flag 8 runs only after a zero initial result, then flag 1
 * runs unconditionally within that gate. Kind 4, or kind 1 with texture byte 4,
 * selects the scalar 0x148C blend/copy and vector 0x149C update, followed by
 * callback 0x1560/context 0x1588. A retained nonzero result invokes callback
 * 0x156C/context 0x1594 with the output address as its request word. The later
 * flag at 0x12B6 selects aliased cross/cross/normalize operations on vector34.
 * Native 10AEC always rebinds query ranges before the return.
 * RE_ORIGINAL_QUIRK: results are stored as halfwords, but only the low byte is
 * returned. The normalization result is ignored. Preserve these operations.
 * RE_UNKNOWN: sentinel/kind/result meanings, vector frame/units, scalar roles,
 * valid ranges, full output storage/aliasing, callback effects and historical
 * input declarations. Trace native callers, query producers and callback
 * registrations before assigning physical roles or strengthening validation.
 * The clean recovery is parked: provider operations/call positions and
 * ordered relocations agree, but stack homes and local result organization
 * differ. The zero-result gate uses BEQZ/NOP instead of native BEQZL/halfword
 * reload; after the callback it retains/narrows the return in a register.
 * Do not invent padding or force temporary registers. */
#line 424 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004079B8.s")

#line 426 "src/modules/uvdyn_rom.c"
/* Update vector146C through the original matrix export unless value1488 is
 * strictly between the original double-precision thresholds -0.00001 and
 * 0.00001; within that interval, copy matrix12EC's translation. Preserve the
 * negated ordered predicate so NaNs take the original matrix-export path. */
void uvDynUpdateNodeTranslationVector(DynResetState *state) {
    if (!(state->value1488 < D_uvdyn_rom_00411CD8 && D_uvdyn_rom_00411CE0 < state->value1488)) {
        D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix12EC, &state->vector146C, &state->vector152C);
    } else {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector146C, (Vec3F *)&state->matrix12EC.xw);
    }
}
#line 427 "src/modules/uvdyn_rom.c"

/* Original node-update wrapper: FVEC0x0C length -> ISCT0x80 shared scalar,
 * direct0x4050EC update -> low16 result at0x12B4, then scalar reset to -1.
 * Result2 copies matrix132C to12EC, refreshes the node vector, copies only
 * the linear3x3 to13EC, transposes only that linear3x3 to142C, initializes
 * matrix136C, stores result3, then calls callback155C(state,word1584) if set.
 * RE_UNKNOWN: returned-code meanings, vector14BC units, four forwarded-word
 * meanings and callback/context registration/lifetime. Trace original50EC
 * callers/result paths and state/callback producers before assigning them.
 * RE_UNKNOWN: original C local organization. Two readable candidates preserve
 * every instruction operation/register/branch/call and relocation identity,
 * but differ in frame64/72 and pointer/home offsets; original declarations
 * or new source-contract evidence is needed, not artificial stack padding. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C98.s")
#line 429 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004088EC.s")

/* Original node vector-pair query followed by a record-vector offset update.
 * Native F78C uses the pair at 0x146C/0x1478 and range halfwords in the order
 * 0x12D2/0x12DA/0x12D0/0x12D8. When value04 is -1, query flag 8 runs only
 * after a zero initial result, then flag 1 runs inside that sentinel gate.
 * Kind 4, or kind 1 with texture byte 4, stores kind 4 and scalar 0x148C=1,
 * copies point14 to vector 0x149C, then invokes callback 0x1560. Otherwise,
 * a successful flag-1 query forces the retained result to 1. A nonzero
 * retained result invokes callback 0x156C with the output address as its word.
 * Native 10AEC rebinds ranges before the final zero-result return. A nonzero
 * result runs isct slot 0x94, then optional aliased cross/cross/normalize
 * operations under halfword 0x12B6. FVEC subtract/scale/add forms point14
 * minus the first query vector plus 0.1f times vector34, then adds that result
 * to the matrix vector at 0x131C before the first query vector at 0x146C.
 * RE_ORIGINAL_QUIRK: retained results narrow to u16; the flag-1 return gates
 * record handling without replacing that result directly. Facing and
 * normalization returns are ignored. Preserve range reset and alias order.
 * RE_UNKNOWN: sentinel/kind/result meanings, vector frames/units, scalar and
 * 0.1-factor roles, valid ranges, complete output storage/aliasing, callback
 * effects and historical input declarations. Trace original callers, query
 * producers and callback registrations before assigning physical roles or
 * adding validation. The clean recovery remains unaccepted: its stack/result
 * homes and final return organization differ, shifting instruction and
 * relocation positions. Recover genuine source-local lifetimes/control flow;
 * do not invent padding or force temporary registers. */
#line 434 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408DC8.s")

/* Append attachment query-index/kind/pointer entries, then collect each
 * newly appended attachment's DOBJ sphere query into shared workspace.
 * Original imports bind QERY slots 0x28/0x30 to the selector parser and
 * array override, and DOBJ slots 0x04/0x50 to the shared index-pair setter
 * and four-float sphere query with three output pointers.
 * RE_ORIGINAL_QUIRK: native 0x4090F8 stores the newly appended entry count
 * as a word at SP+0x7C, and 0x4092E8 returns its low16 via LHU SP+0x7E.
 * The separately initialized/incremented u16 at SP+0x6E is not the return
 * source. Preserve the actual return; no uninitialized-return claim is valid.
 * RE_UNKNOWN: starting counter and caller allocation bounds. Native entry
 * count at work+0xF744 stops only at equality with 30; hit count at +0xF746
 * sets remaining capacity as 120-count. Trace work allocation/reset writers
 * and attachmentCount producers before changing limits or assuming safety.
 * RE_UNKNOWN: entry-kind 3 and query-index word meanings, shared query-state
 * ownership/reentrancy and output storage aliases. Original cleanup installs
 * fixed NULL/zero override, selector-1 value zero and DOBJ pair -1/-1 rather
 * than restoring saved values. Trace original call/configuration lifetimes.
 * RE_UNKNOWN: historical independent loop-local declarations and source
 * organization. Readable C remains unmatched; retain original assembly. */
#line 438 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409010.s")

/* Original transform/vector update wrapper. Count at 0x18 is tested only
 * against zero, so negative counts enter. FVEC slot 0x0C computes the length
 * of vector 0x14BC for ISCT slot 0x80; native 50EC receives the original four
 * forwarded 32-bit words, scalar and trailing mode 1. Its result is narrowed
 * at 0x12B4; the shared scalar is reset to -1 before that result is reloaded.
 * Result 2 copies the supplied matrix and two vectors, refreshes the linear
 * matrix pair and DOBJ transform, then calls native 7C98 with mode 0.
 * Every path clears the original halfword at 0x151C.
 * RE_UNKNOWN: result-code meanings, vector frames/units, scalar units,
 * forwarded-word interpretation, and input/state aliases and lifetimes.
 * Trace native 50EC/7C98 callers, result checks and state producers before
 * assigning physical roles or strengthening the exact-zero input guard.
 * RE_UNKNOWN: historical C declarations and local organization. The bounded
 * draft matches every operation, register and call/branch position but uses
 * an 80-byte frame versus the original 72, shifting argument homes and three
 * saved pointer slots. Preserve assembly until original source/ABI evidence
 * supports a matching recovery; do not invent stack padding or unused locals. */
#line 440 "src/modules/uvdyn_rom.c"
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

#line 454 "src/modules/uvdyn_rom.c"
/* Return the original integer address formed from the state link at
 * 0x14, the unsigned selector at 0x12CE, 0x28-byte stride and offset 0x6EC0.
 * Preserve the 32-bit target address representation and unchecked selector. */
s32 uvDynGetLinkedRecordAddress(void *state)
{
  int recordOffset;
  s32 linkedBase;
  u8 *baseAddress;
  baseAddress = ((u8 *) state) + 0x14;
  linkedBase = *((s32 *) baseAddress);
  return (linkedBase + ((*((u16 *) (((u8 *) state) + 0x12CE))) * 0x28)) + ((long) (recordOffset = 0x6EC0));
}
#line 464 "src/modules/uvdyn_rom.c"

#line 465 "src/modules/uvdyn_rom.c"
/* Clear both original shared short counters in order. */
void uvDynClearSharedPairCounters(void) {
    D_uvdyn_rom_00411EC0 = 0;
    D_uvdyn_rom_00411EC2 = 0;
}
#line 469 "src/modules/uvdyn_rom.c"

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

#line 478 "src/modules/uvdyn_rom.c"
/* Return the owner of a valid attachment; an unattached owner may be null. */
DynResetState *uvDynGetAttachmentOwner(DynAttachmentPrefix *attachment) {
    return attachment->owner;
}
#line 481 "src/modules/uvdyn_rom.c"

#line 482 "src/modules/uvdyn_rom.c"
/* Refresh the attachment and its intersection transform. For a kind-one
 * value record, store vector1C minus the record vector, cache its original
 * length, and normalize the delta only above the original threshold. Invoke
 * the optional attachment callback afterward for every kind. Preserve the
 * original valid-owner/intersection preconditions and live field reloads. */
void uvDynUpdateAttachmentDelta(DynAttachmentUpdateState *attachment) {
    DynAttachmentDeltaFields *vectors;
    Vec3F *delta;
    uvDynRefreshAttachmentVectors((DynAttachmentPrefix *)attachment);
    D_uvdyn_rom_00411F7C->setTransformProperty(attachment->intersectionRecord, 3, &attachment->owner->matrix12EC);
    if (((DynIsectKindOneValue *)attachment->intersectionRecord->valueRecord)->kind == 1) {
        vectors = &attachment->vectors;
        D_uvdyn_rom_00411F74->uvVec3FSub(&attachment->vectors.delta, &vectors->first, &((DynIsectKindOneValue *)attachment->intersectionRecord->valueRecord)->vector18);
        delta = &vectors->delta;
        vectors->length = D_uvdyn_rom_00411F74->uvVec3FLen(delta);
        if (D_uvdyn_rom_00411D00 < vectors->length) {
            D_uvdyn_rom_00411F74->uvVec3FScale(delta, delta, 1.0f / vectors->length);
        }
    }
    if (attachment->callback != NULL) {
        attachment->callback(attachment, attachment->callbackContext);
    }
}
#line 483 "src/modules/uvdyn_rom.c"

#line 484 "src/modules/uvdyn_rom.c"
/* Refresh attachment vectors from the intersection value record. Kind zero
 * copies each 28-byte record's two vectors into consecutive attachment vectors,
 * preserving 16-bit iteration and live count reloads after export callbacks.
 * Kind one copies only its single vector. Other kinds leave vectors unchanged;
 * the original requires valid intersection pointers and adequate storage. */
void uvDynRefreshAttachmentVectors(DynAttachmentPrefix *attachment) {
    DynIsectValuePrefix *value;
    DynIsectVectorPairList *list;
    u16 index;
    value = ((DynIsectRecordPrefix *)attachment->intersectionRecord)->valueRecord;
    switch (value->kind) {
        case 0:
            list = (DynIsectVectorPairList *)&value->children;
            for (index = 0; index < list->count; index++) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachment)->vectors[index * 2], &list->records[index].first);
                D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachment)->vectors[index * 2 + 1], &list->records[index].second);
            }
            break;
        case 1:
            D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachment)->vectors[0], &((DynIsectKindOneValue *)value)->vector18);
            break;
    }
}
#line 485 "src/modules/uvdyn_rom.c"

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

#line 492 "src/modules/uvdyn_rom.c"
/* Return the intersection record of a valid attachment; the record may be null. */
void *uvDynGetAttachmentIntersection(DynAttachmentPrefix *attachment) {
    return attachment->intersectionRecord;
}
#line 495 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A188.s")

#line 498 "src/modules/uvdyn_rom.c"
/* Invoke attachment callback slot 0x244 with the attachment and its paired
 * context at 0x25C. A missing callback is an original no-op. */
void uvDynInvokeAttachmentCallback244(DynAttachmentCallbackSlots *attachment) {
    void (*callback)(void *, s32) = attachment->callback244;
    if (callback != NULL) {
        callback(attachment, attachment->context25C);
    }
}
#line 504 "src/modules/uvdyn_rom.c"

#line 505 "src/modules/uvdyn_rom.c"
/* Invoke attachment callback slot 0x248 with the supplied opaque value and
 * its paired context at 0x260. Keep this distinct from the pointer callback ABI. */
void uvDynInvokeAttachmentValueCallback248(DynAttachmentCallbackSlots *attachment, s32 value) {
    void (*callback)(s32, s32) = attachment->callback248;
    if (callback != NULL) {
        callback(value, attachment->context260);
    }
}
#line 511 "src/modules/uvdyn_rom.c"

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

#line 514 "src/modules/uvdyn_rom.c"
/* For a nonnull state, store the indexed pair in original parallel word
 * regions at 0x240 and 0x258. Index bounds and field meanings remain with
 * callers; the original routine does not validate either region. */
void uvDynSetPairedRecordWords(void *state, s32 index, s32 first, s32 second) {
    if (state == NULL) {
        return;
    }
    *(s32 *)((u8 *)state + index * 4 + 0x240) = first;
    *(s32 *)((u8 *)state + index * 4 + 0x258) = second;
}
#line 521 "src/modules/uvdyn_rom.c"

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

#line 526 "src/modules/uvdyn_rom.c"
/* RE_ORIGINAL_QUIRK: two original FVEC copies initialize the 12-byte values
 * at SP+0x4C/SP+0x58 before the first ISCT slot 0xA8 call, but this caller
 * does not assign the adjacent SP+0x64 input word. The actual provider
 * 0x4048DC directly reads input+0x18 for flag bits 8/1; flag bit 2 invokes
 * 0x4014FC, which forwards that word to 0x401558. Only the fallback query
 * assigns zero. This proves original read/store timing, not a missing
 * historical C initializer or a confirmed player-visible bug.
 * RE_UNKNOWN: caller flags, prior scratch provenance and downstream paths.
 * Trace original flag writers, attachment producers and each invoked helper
 * before changing initialization or assigning gameplay consequences.
 * RE_UNKNOWN: valid pair/endpoint domains and vector-bank capacity. The fifth
 * argument is read as u16: zero/nonzero selects source offsets 0x5C/0x68,
 * whereas cached indexing uses the full u16 times 12 after pairIndex*0x18.
 * Trace original callers and allocations before adding bounds checks.
 * RE_ORIGINAL_QUIRK: a successful fallback stores output+0x2C times twice
 * the seventh f32 argument before the strict comparison against that argument
 * plus native f32 0x411D14 (bits 0x3727C5AC). A rejected comparison therefore
 * can still update the scalar output pointer; preserve that store timing.
 * RE_UNKNOWN: vector frames/units, projection normalization and output storage
 * lifetimes/aliasing. Successful ISCT A8 also stores its input address into
 * output word0; here the input is local SP+0x4C storage. Trace actual callers'
 * output retention/dereferences before relying on that address after return.
 * Readable C remains unmatched: native 616 bytes versus compiled 572.
 * Provider slots, operation order and observed argument widths agree; exact
 * historical local/parameter declarations remain unresolved. */
#line 540 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B838.s")
#line 527 "src/modules/uvdyn_rom.c"

#line 528 "src/modules/uvdyn_rom.c"
/* Bind the shared scalar address and clear both original dynamics
 * registration counters. Existing collection storage is left untouched. */
void uvDynBindGlobalScalarAndResetCounts(void) {
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411F18 = 0;
    D_uvdyn_rom_00411F1A = 0;
}
#line 533 "src/modules/uvdyn_rom.c"

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

#line 562 "src/modules/uvdyn_rom.c"
/* Build enclosing spheres from each member's previous/current translations.
 * Node spheres use the greater of the old and new extra-radius values; preserve
 * the original ordered comparison and retain value04 == -1 while clearing other
 * values. Secondary spheres use their stored radius. Reload both collection
 * counts after calls and keep the original 16-bit iteration. */
void uvDynBuildCollectionMemberSpheres(DynLinkedCollection *collection) {
    u16 index;
    DynResetState *state;
    DynSecondaryState *secondary;
    for (index = 0; index < collection->count; index++) {
        state = (DynResetState *)collection->members[index];
        state->value14B4 = state->value14B0;
        state->value14B0 = state->value14AC;
        if (state->value14B4 < state->value14AC) {
            state->value14B4 = state->value14AC;
        }
        uvDynBuildPointPairSphere(&state->sphere12DC, (Vec3F *)&state->matrix132C.xw, (Vec3F *)&state->matrix12EC.xw, state->value14B4);
        if (state->value04 != -1) {
            state->value04 = 0;
        }
    }
    for (index = 0; index < collection->secondaryCount; index++) {
        secondary = collection->secondaryMembers[index];
        uvDynBuildPointPairSphere(&secondary->sphere13C, (Vec3F *)&secondary->matrix58.xw, (Vec3F *)&secondary->matrix18.xw, secondary->radius138);
    }
}
#line 563 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E8E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040F78C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040FC88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410250.s")

/* Original terrain sphere-query append wrapper. Record and secondary counts
 * are unsigned halfwords at 0xF73C/0xF73E. Install QERY overrides at the current
 * 120-byte/40-byte record slots, call TERR slot 0x44 with flags 6 and the four
 * sphere floats, then add QERY's secondary count before any record-word copy.
 * TERR returns four array addresses; only the first and fourth are copied,
 * in that order. Reload the original record count after both copies, publish
 * it through D_uvdyn_rom_00411FA0, reset the overrides and selector 1 to fixed
 * values, then publish or clear lowercase isct slot 0x40's four shared words.
 * RE_ORIGINAL_QUIRK: neither starting count is checked. A negative signed
 * remaining capacity (220 minus record count) can narrow to u16 for copying;
 * the secondary count also wraps through its original halfword store.
 * RE_UNKNOWN: caller count/allocation guarantees, selector-1 meaning, sphere
 * frame/units, output-array aliasing/lifetime and shared-count global role.
 * Trace workspace producers, TERR/QERY consumers and original callers before
 * changing bounds or ownership. The clean draft remains unaccepted: native
 * local organization yields different frame homes and copy-count scheduling.
 * Recover matching historical C organization without padding or dummy locals. */
#line 576 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004107FC.s")

#line 578 "src/modules/uvdyn_rom.c"
/* Select the indexed opaque 120-byte intersection record and corresponding
 * word outputs through the lowercase isct module's query-bank setter. Pass the
 * opaque 16-bit value unchanged; the original does not check index or pointers. */
void uvDynSetIndexedQueryRecordBank(DynIntersectionQueryBanks *banks, u16 index, u16 value) {
    D_uvdyn_rom_00411F7C->setQueryRecordBank(value, &banks->records[index], &banks->firstWords[index], &banks->secondWords[index]);
}
#line 579 "src/modules/uvdyn_rom.c"

/* Publish ranges through lowercase-isct slot0x44, the original parameter-bank
 * setter at0x400BC4. First table0x72A6 uses buffers0x730C/0xB95C; second
 * table0xBC2A uses buffers0xBD1C/0xF55C. Start index zero selects zero;
 * otherwise load table[start], with end from table[start+count].
 * Nonempty first range selects mode1. Nonempty second selects mode2 when
 * the first exists, else mode1; both empty publish the empty first range.
 * RE_UNKNOWN: native table producers/valid index-count domains, complete
 * allocation, buffer ownership and bank protocol. All four incoming words
 * are consumed through low16 views; fullword homes do not prove the complete
 * historical C prototype. Trace original callers and table writers before
 * changing bounds, arithmetic organization, storage lifetime or units.
 * RE_UNKNOWN: historical parameter-home/pointer organization. The readable
 * draft agrees on provider, effects and widths but caches firstCount across
 * the first call and combines index/count offsets differently. Keep original
 * assembly until a grounded source contract resolves instruction differences. */
#line 580 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410C40.s")

#line 584 "src/modules/uvdyn_rom.c"
/* Store the shared scalar address and clear the accompanying state word. */
void uvDynBindGlobalScalarAndClearFlag(void) {
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411E68 = 0;
}
#line 588 "src/modules/uvdyn_rom.c"

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

#line 597 "src/modules/uvdyn_rom.c"
/* Scalar property zero converts to the opaque signed value at 0x0C;
 * property nine converts through the original unsigned-word/signed-halfword
 * sequence into the 16-bit kind. Null and unsupported properties do nothing. */
void uvDynSetSecondaryScalarProperty(DynSecondaryState *state, s32 property, f32 value) {
    if (state != NULL) {
        switch (property) {
            case 0:
                state->value0C = (s32)value;
                return;
            case 9:
                state->kind = (s16)(u32)value;
                break;
        }
    }
}
#line 609 "src/modules/uvdyn_rom.c"

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

#line 612 "src/modules/uvdyn_rom.c"
/* Set secondary vector properties 2, 3, 7 and 8 from a vector passed by value.
 * Property 2 stores vector194, caches its length at 0x134 and runs the original
 * matrix export. Property 3 updates translation and the related vector cache;
 * the strict double-threshold predicate preserves its original NaN path.
 * Properties 7 and 8 only change kind-zero states; other cases do nothing. */
void uvDynSetSecondaryVectorProperty(DynSecondaryState *state, s32 property, Vec3F vector) {
    if (state == NULL) {
        return;
    }
    switch (property) {
        case 2:
            D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector194, &vector);
            state->value134 = D_uvdyn_rom_00411F74->uvVec3FLen(&state->vector194);
            D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            break;
        case 3:
            state->matrix18.xw = vector.x;
            state->matrix18.yw = vector.y;
            state->matrix18.zw = vector.z;
            if (!(state->value134 < D_uvdyn_rom_00411D38 && D_uvdyn_rom_00411D40 < state->value134)) {
                D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            } else {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector118, &vector);

            }
            break;
        case 7:
            if (state->kind == 0) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14C, &vector);
            }
            break;
        case 8:
            if (state->kind == 0) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector17C, &vector);
            }
            break;
    }
}
#line 613 "src/modules/uvdyn_rom.c"

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

#line 618 "src/modules/uvdyn_rom.c"
/* Matrix properties 3 and 4 synchronize the secondary transform pair,
 * refresh vector118 and set the copy flag. Property 4 uses a temporary matrix
 * for the exported conversion. Preserve strict double near-zero comparisons:
 * NaN takes the exported vector-update path. Null/unsupported properties do nothing. */
void uvDynSetSecondaryMatrixProperty(DynSecondaryState *state, s32 property, Mtx4F *input) {
    Mtx4F temporary;
    if (state == NULL) {
        return;
    }
    switch (property) {
        case 3:
            D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix18, input);
            if (!(state->value134 < D_uvdyn_rom_00411D68 && D_uvdyn_rom_00411D70 < state->value134)) {
                D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            } else {
                state->vector118.x = state->matrix18.xw;
                state->vector118.y = state->matrix18.yw;
                state->vector118.z = state->matrix18.zw;
            }
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&state->matrixD8, &state->matrix18);
            state->copyFlag = 1;
            break;
        case 4:
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrixD8, input);
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&temporary, &state->matrixD8);
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix18, &temporary);
            if (!(state->value134 < D_uvdyn_rom_00411D78 && D_uvdyn_rom_00411D80 < state->value134)) {
                D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            } else {
                state->vector118.x = state->matrix18.xw;
                state->vector118.y = state->matrix18.yw;
                state->vector118.z = state->matrix18.zw;
            }
            state->copyFlag = 1;
            break;
    }
}
#line 619 "src/modules/uvdyn_rom.c"

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

#line 644 "src/modules/uvdyn_rom.c"
/* Return this secondary state's linked collection. The original requires
 * a valid state and may return null when no collection is linked. */
DynSecondaryCollection *uvDynGetSecondaryCollection(DynSecondaryState *state) {
    return state->collection;
}
#line 647 "src/modules/uvdyn_rom.c"

#line 648 "src/modules/uvdyn_rom.c"
/* Store the DOBJ handle and model level-of-detail index, look up the loaded
 * UVMD model, and cache the larger length of its two LOD vector triplets as the
 * secondary sphere radius. Preserve reloads after the first square-root export,
 * the ordered comparison and the original valid-model/index preconditions. */
void uvDynSetSecondaryModelLod(DynSecondaryState *state, s32 dobjHandle, s32 lodIndex) {
    ParsedUVMD *model;
    u16 modelId;
    uvModelLOD_inner *bounds;
    f32 secondRadius;
    state->dobjHandle = dobjHandle;
    state->lodIndex = lodIndex;
    modelId = D_uvdyn_rom_00411F84->uvDobjGetModel(dobjHandle);
    model = uvGetLoadedFile(0x55564D44, modelId);
    bounds = &model->unk0->unk0[lodIndex].unk8;
    state->radius138 = D_uvdyn_rom_00411F80->uvSqrtf((bounds->unk0 * bounds->unk0 + bounds->unk4 * bounds->unk4) + bounds->unk8 * bounds->unk8);
    secondRadius = D_uvdyn_rom_00411F80->uvSqrtf((bounds->unkC * bounds->unkC + bounds->unk10 * bounds->unk10) + bounds->unk14 * bounds->unk14);
    if (state->radius138 < secondRadius) {
        state->radius138 = secondRadius;
    }
}
#line 649 "src/modules/uvdyn_rom.c"

#line 650 "src/modules/uvdyn_rom.c"
/* Return the stored secondary-state DOBJ handle from a valid state. */
s32 uvDynGetSecondaryDobjHandle(DynSecondaryState *state) {
    return state->dobjHandle;
}
#line 653 "src/modules/uvdyn_rom.c"

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

