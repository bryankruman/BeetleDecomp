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
void *uvDynGetNodePropertyAddress(void *state, s32 property);
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
/* Sphere-query views: fields used here are grounded in the retained 10250
 * accesses; unused spans preserve the successful trial layout. Opaque spans and callback names do not establish gameplay units. */
typedef struct {
    s32 registryIndex;
    s32 associationCount;
    void *associations[2];
    s32 querySelector;
    u8 opaque14[0x14];
    s32 dobjHandle;
    u8 opaque2C[0x12B0];
    DynSphere sphere12DC;
    u8 opaque12EC[0x30];
    Vec3F center131C;
    u8 opaque1328[0x18C];
    f32 radius14B4;
} DynSphereQueryNode;
typedef struct {
    u8 opaque00[0x10];
    s32 dobjHandle;
    u8 opaque14[0x34];
    Vec3F center48;
    u8 opaque54[0xE4];
    f32 radius138;
    DynSphere sphere13C;
} DynSphereQuerySecondary;
typedef struct {
    u8 opaque00[0x94];
    s32 nodeCount;
    DynSphereQueryNode *nodes[10];
    u8 opaqueC0[0x7120];
    u32 segmentObjectIds[50];
    u16 segmentRangeEnds[50];
    DynIntersectionQueryRecord segmentRecords[150];
    void *segmentResultPointers[150];
    u32 sphereObjectIds[30];
    u16 sphereRangeEnds[30];
    u16 sphereKinds[30];
    void *sphereOwners[30];
    DynIntersectionQueryRecord sphereRecords[120];
    void *sphereResultPointers[120];
    u8 opaqueF73C[4];
    u16 segmentObjectCount;
    u16 segmentResultCount;
    u16 sphereObjectCount;
    u16 sphereResultCount;
    s32 secondaryCount;
    DynSphereQuerySecondary *secondary[20];
} DynSphereQueryCollection;
/* These slot ABIs are observed directly at the original indirect calls.
 * The DOBJ view casts the already declared import; it adds no storage. */
typedef struct {
    void *slot00;
    void (*selectQueryObject)(s32, s32);
    u8 opaque08[0x24];
    void (*setObjectFlags)(s32, s32);
    void *slot30;
    s32 (*getObjectFlags)(s32);
    u8 opaque38[0x14];
    void *slot4C;
    s32 (*querySphere)(f32, f32, f32, f32, void ***, void **, void **);
} DynQueryDobjExports;
typedef struct {
    u8 opaque00[0xC];
    s32 (*testSpheres)(f32, f32, f32, f32, f32, f32, f32, f32);
} DynQuerySphereExports;
typedef struct {
    u8 opaque00[0x28];
    void (*setQueryModes)(s32, s32, s32, s32);
    void *slot2C;
    void (*setQueryRecordBuffer)(void *, s32);
} DynQueryRecordExports;
extern DynQuerySphereExports *D_uvdyn_rom_00411F8C;
extern DynQueryRecordExports *D_uvdyn_rom_00411F94;
extern s32 D_uvdyn_rom_00411F9C;

#line 450 "src/modules/uvdyn_rom.c"
u16 func_uvdyn_rom_00410250(DynSphereQueryCollection *, s32, DynSphere *, u8, void *);
u16 uvDynAppendSphereQueryCandidates(DynSphereQueryCollection *, s32, DynSphere *, u8, void *);
#line 451 "src/modules/uvdyn_rom.c"
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

/* Call the unload entry with the ten literal module IDs in the original order;
 * ignore each return value. The body does not clear the cached export words.
 * RE_UNKNOWN: Reference-count behavior, users retaining exports and legal
 * unload timing are not established here. */
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

/* Walk the registered collection pointers using a halfword index and reload
 * the global halfword count after each work-buffer allocation call.
 * RE_UNKNOWN: Registry capacity, pointer validity and count mutation across
 * those calls are unchecked. */
#line 325 "src/modules/uvdyn_rom.c"
/* Allocate work buffers for every registered collection. Preserve the original
 * 16-bit index and reload the registry count after each allocation helper. */
void uvDynAllocateRegisteredCollectionWorkBuffers(void) {
    u16 registeredCollectionIndex;
    for (registeredCollectionIndex = 0; registeredCollectionIndex < D_uvdyn_rom_00411F18; registeredCollectionIndex++) {
        uvDynAllocateCollectionWorkBuffers(D_uvdyn_rom_00411EC8[registeredCollectionIndex]);
    }
}
#line 326 "src/modules/uvdyn_rom.c"

/* Walk the active collection pointers using a halfword index and reload the
 * global halfword count after every collection update. RE_UNKNOWN: Registry
 * capacity and callback-driven membership changes are unchecked; the loop
 * takes no count snapshot. */
#line 327 "src/modules/uvdyn_rom.c"
/* Update each active collection in registry order. Preserve the live registry
 * count and original 16-bit iteration because callees may change shared state. */
void uvDynUpdateActiveCollections(void) {
    u16 activeCollectionIndex;
    for (activeCollectionIndex = 0; activeCollectionIndex < D_uvdyn_rom_00411F1A; activeCollectionIndex++) {
        uvDynUpdateCollection(D_uvdyn_rom_00411EF0[activeCollectionIndex]);
    }
}
#line 328 "src/modules/uvdyn_rom.c"

/* Selector0 writes the shared scalar word; other selectors perform no store.
 * RE_UNKNOWN: The scalar units and supported caller selector domain are
 * unproved. */
#line 329 "src/modules/uvdyn_rom.c"
/* Store global scalar property zero; unsupported property numbers are ignored.
 * The scalar's gameplay meaning remains unresolved. */
void uvDynSetGlobalScalarProperty(s32 propertySelector, f32 storedScalar) {
    if (propertySelector == 0) {
        D_uvdyn_rom_00411DB4 = storedScalar;
    }
}
#line 334 "src/modules/uvdyn_rom.c"

/* Selector0 returns the shared scalar; other selectors return -1.0f.
 * RE_UNKNOWN: The scalar units and interpretation of the fallback value are
 * unproved. */
#line 335 "src/modules/uvdyn_rom.c"
/* Return global scalar property zero, or -1 for an unsupported property.
 * The scalar's gameplay meaning remains unresolved. */
f32 uvDynGetGlobalScalarProperty(s32 propertySelector) {
    if (propertySelector == 0) {
        return D_uvdyn_rom_00411DB4;
    }
    return -1.0f;
}
#line 341 "src/modules/uvdyn_rom.c"

/* Return the address of the same shared scalar used by the selector0 setter
 * and getter. RE_UNKNOWN: The returned address permits external mutation; its
 * producer and lifecycle are not established here. */
#line 342 "src/modules/uvdyn_rom.c"
/* Return the shared scalar's address for original consumers that retain its
 * live value rather than taking a scalar snapshot. */
f32 *uvDynGetGlobalScalarAddress(void) {
    return &D_uvdyn_rom_00411DB4;
}
#line 345 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040071C.s")

/* RE_UNKNOWN: Valid matrix domains and caller overlap are not established.
 * The imported inverse helper transposes the linear component and adjusts
 * translation; its name does not establish a general matrix inverse. The
 * original reloads FMTX before the multiply and passes output again as its
 * third argument, so preserve that ordered, in-place composition. */
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
/* Apply the recorded row permutation, forward substitution and backward
 * triangular solve in place, preserving zero-based indices and overwrite order.
 * RE_UNKNOWN: permutation bounds and nonzero factor diagonals; trace original
 * factorization producers and callers before asserting valid-input guarantees. */
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

/* Original two-sphere update: compute center distance through MATH slot 0x04
 * and return zero when incomingRadius + distance <= targetRadius. Otherwise
 * freeze (targetRadius + incomingRadius + distance) * 0.5f, subtract centers
 * through FVEC slot 0x34, and obtain the offset length through slot 0x0C.
 * If native readonly scalar 0x411ADC is strictly less than that length, scale
 * the offset in place by (frozenRadius - currentTargetRadius) / length and
 * add it to the target center. Always store the frozen radius and return one
 * on this path. Keep separate provider calls and original aliases/read timing.
 * RE_ORIGINAL_QUIRK: there is only the incoming-inside-target containment test;
 * the opposite containment direction has no special branch. The half-sum
 * formula must not be replaced by a guaranteed general sphere-union routine.
 * RE_UNKNOWN: coordinate/radius units, finite/nonnegative input guarantees,
 * relative-containment restrictions and permitted pointer aliases. Trace
 * original callers and sphere producers before claiming complete bounds or
 * changing the strict small-distance gate. The readable recovery remains
 * parked: all arithmetic, vector offsets, calls, branches and twelve complete
 * ordered relocations match, but eight stack-immediate words differ (frame
 * 72 versus 80 bytes, incoming home 72 versus 80, radius home 64 versus 60).
 * Original source-local declaration/lifetime evidence is needed; do not add
 * artificial padding, initialize extra scratch or force register placement. */
#line 325 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403294.s")

/* Original scalar endpoint-pair test. Cache the second input's center and
 * squared radius, then compare each consecutive three-float point at offsets
 * 0x00 and 0x0C against that center. Each distance sum is left-associated f32
 * arithmetic; a strict squaredRadius < squaredDistance comparison returns
 * zero immediately. Return one only after both failure tests are bypassed.
 * RE_ORIGINAL_QUIRK: equality passes, unordered comparisons bypass failure,
 * and the radius is squared without checking its sign. Preserve these exact
 * predicates rather than asserting containment for invalid/nonfinite inputs.
 * RE_UNKNOWN: the first input's complete record extent/ownership, coordinate
 * units, valid caller domains and permitted pointer aliases. Trace original
 * callers and sphere/point producers before assigning a physical role or
 * strengthening validation. The readable recovery is parked: native 212
 * bytes versus draft 192, with 53 different instruction words. Both have no
 * calls or relocations and the same per-point mathematical operations and
 * strict branches, but native center.z/difference.y/difference.z stack homes
 * and register lifetimes differ from the draft's radius spills and float
 * allocation (native frame 32 bytes versus 40). No omitted operation or
 * additional source contract is supported by the original evidence. Retain
 * native instructions until genuine declaration/lifetime evidence resolves
 * the code generation; do not add padding, scratch stores or forced registers. */
#line 327 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004033F4.s")

/* Subtract firstPoint from secondPoint, scale the resulting center by0.5,
 * store its length plus the supplied radius addition, then add firstPoint to
 * the center. Reload the vector provider for each call. RE_UNKNOWN:
 * Point/output alias domains, radius sign and vector units are unchecked;
 * preserve the radius store before the final vector call. */
#line 329 "src/modules/uvdyn_rom.c"
/* Build a sphere centered at the point-pair midpoint, with radius equal to
 * half the separation plus extraRadius. Preserve the original vector-export
 * order and in-place output aliases; the original does not clamp extraRadius. */
void uvDynBuildPointPairSphere(DynSphere *outputSphere, Vec3F *firstPoint, Vec3F *secondPoint, f32 radiusAddition) {
    D_uvdyn_rom_00411F74->uvVec3FSub(&outputSphere->center, secondPoint, firstPoint);
    D_uvdyn_rom_00411F74->uvVec3FScale(&outputSphere->center, &outputSphere->center, 0.5f);
    outputSphere->radius = D_uvdyn_rom_00411F74->uvVec3FLen(&outputSphere->center) + radiusAddition;
    D_uvdyn_rom_00411F74->uvVec3FAdd(&outputSphere->center, firstPoint, &outputSphere->center);
}
#line 330 "src/modules/uvdyn_rom.c"

/* Store the shared-scalar address returned by the accessor and clear only the
 * registry count halfword. RE_UNKNOWN: Existing registry slots are not cleared
 * here; registration and reset timing remain unproved. */
#line 331 "src/modules/uvdyn_rom.c"
/* Cache the shared scalar's address and clear the node-registry count.
 * This original initializer does not free or clear registry entries. */
void uvDynInitNodeRegistry(void) {
    D_uvdyn_rom_00411DB8 = uvDynGetGlobalScalarAddress();
    D_uvdyn_rom_00411DE8 = 0;
}
#line 335 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Registry capacity, allocation failure and node ownership are
 * not established. The 0x15A0 allocation and observed field writes do not
 * recover a complete historical structure or physical units for properties
 * 2, 10 and 14. Registration precedes the property and matrix setup calls. */
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

/* First detach the linked collection, then snapshot the registry count and
 * find the first matching node. Decrement the halfword count, shift later
 * entries with live count reads, and write each moved node registry index.
 * RE_UNKNOWN: Pointer validity and registry capacity are unchecked; the former
 * final slot is not cleared and the node is not freed here. */
#line 338 "src/modules/uvdyn_rom.c"
/* Clear linked-collection membership, remove the node from its registry and
 * repair later registry indices. Preserve separate 16-bit scan/shift indices and
 * live count reloads. This unregister routine does not free the node. */
void uvDynUnregisterLinkedNodeState(DynResetState *removedNodeState) {
    u16 foundRegistryIndex;
    u16 registryShiftIndex;
    s32 registryCountSnapshot;
    uvDynSetLinkedCollection((DynLinkedNode *)removedNodeState, NULL);
    registryCountSnapshot = D_uvdyn_rom_00411DE8;
    for (foundRegistryIndex = 0; foundRegistryIndex < registryCountSnapshot; foundRegistryIndex++) {
        if (removedNodeState == D_uvdyn_rom_00411DC0[foundRegistryIndex]) {
            break;
        }
    }
    if (foundRegistryIndex != registryCountSnapshot) {
        D_uvdyn_rom_00411DE8--;
        for (registryShiftIndex = foundRegistryIndex; registryShiftIndex < D_uvdyn_rom_00411DE8; registryShiftIndex++) {
            D_uvdyn_rom_00411DC0[registryShiftIndex] = D_uvdyn_rom_00411DC0[registryShiftIndex + 1];
            D_uvdyn_rom_00411DC0[registryShiftIndex]->registryIndex = registryShiftIndex;
        }
    }
}
#line 339 "src/modules/uvdyn_rom.c"

/* Walk registered nodes with a halfword index and reload the global halfword
 * count after every preparation call. RE_UNKNOWN: Registry capacity, node
 * validity and count mutation across calls are unchecked. */
#line 340 "src/modules/uvdyn_rom.c"
/* Prepare every registered node through the original state-copy/flag helper.
 * Keep the live count reload and original 16-bit registry index. */
void uvDynPrepareRegisteredNodeState(void) {
    u16 registeredNodeIndex;
    for (registeredNodeIndex = 0; registeredNodeIndex < D_uvdyn_rom_00411DE8; registeredNodeIndex++) {
        uvDynPrepareLinkedNodeState(D_uvdyn_rom_00411DC0[registeredNodeIndex]);
    }
}
#line 341 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Attachment/child ownership and nested record validity are
 * unknown beyond the two explicit null checks. Imported slot 0x20 and the
 * attachment helper may affect shared state; their complete effects are
 * not proved by this wrapper. Preserve the live counts and preparation-flag
 * reload after those calls; flag bit zero has no proved gameplay meaning. */
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

/* Node vector-property setter with an observed by-value Vec3F ABI.
 * Properties 2/3/4/5 copy to offsets 0x1520/0x152C/0x1490/0x1538;
 * property 6 writes matrix12EC.xw and calls the translation-update helper.
 * Property 3 also stores the copied vector length at 0x1488, then transforms
 * that vector as a point through matrix12EC into vector146C. Properties
 * 17/18/20/21 copy to offsets 0x14BC/0x14E0/0x14C8/0x14EC. Property 19
 * transforms the incoming vector as a direction through matrix142C into
 * vector14BC. Null state and unsupported properties return without writes.
 * RE_UNKNOWN: historical property identities, vector coordinate frames,
 * physical units and caller-validity domains. The creation caller supplies
 * (1, 1, 1) for property 5 and (0, 0, 0) for property 4; trace other original
 * export callers and field consumers before interpreting further meanings.
 * Preserve the original assembly until native instruction matching resolves
 * the cached property-3 vector pointer's stack home. The isolated C trial
 * retained all original readonly bytes and targets, but three stack offsets
 * still differ; readonly feasibility alone does not establish matching C. */
#line 348 "src/modules/uvdyn_rom.c"
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
#line 362 "src/modules/uvdyn_rom.c"
/* Return the observed node-relative address selected by the property word.
 * RE_ORIGINAL_QUIRK: unhandled nonnull selectors leave result unassigned,
 * matching the original untouched-stack read; this is not a safe fallback.
 * RE_UNKNOWN: full node layout, property meanings, valid selector domains,
 * historical pointer ABI and returned storage ownership remain unproved. */
void *uvDynGetNodePropertyAddress(void *state, s32 property) {
    void *result;

    if (state == NULL) {
        return NULL;
    }
    switch (property) {
        case 2:
        case 3:
        case 5:
            return NULL;
        case 6:
            result = (u8 *)state + 0x131C;
            break;
        case 7:
            result = (u8 *)state + 0x149C;
            break;
        case 17:
            result = (u8 *)state + 0x14BC;
            break;
        case 18:
            result = (u8 *)state + 0x14E0;
            break;
        case 4:
            result = (u8 *)state + 0x1490;
            break;
        default:
            break;
    }
    return result;
}
#line 363 "src/modules/uvdyn_rom.c"
#line 351 "src/modules/uvdyn_rom.c"

/* RE_ORIGINAL_QUIRK: Null state and unsupported selectors leave output
 * untouched; this is not an unconditional output initializer. Selector 19
 * transforms vector14BC through the linear matrix component, while the
 * other handled selectors copy their observed three-word fields.
 * RE_UNKNOWN: Output validity, allowed overlap, units and the physical
 * meanings of these selectors are not established by this getter. */
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

/* RE_ORIGINAL_QUIRK: Only selector 6 performs the relative-transform and
 * external DOBJ update. Selectors 15 and 16 update the observed matrix
 * components and translation vector without those two calls. Preserve the
 * ordered input reads and helper calls when input aliases node storage.
 * RE_UNKNOWN: Valid matrix domains, units and allowed overlap are unproved;
 * only state has a null guard, and input validity remains a caller contract. */
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
/* A zero base returns0. Selectors6,15 and16 return base plus0x12EC,0x13EC
 * and0x142C respectively through the existing signed-word interface.
 * RE_UNKNOWN: Unsupported nonzero-base selectors read an unassigned stack word
 * in the original; callers, historical pointer type and return contract are
 * unproved. Preserve the original default path. */
#line 355 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_00404384(s32 baseAddressWord, s32 memberSelector) {
    s32 selectedAddressWord;

    if (baseAddressWord == 0) {
        return 0;
    }
    switch (memberSelector) {                                 /* irregular */
    case 6:
        selectedAddressWord = baseAddressWord + 0x12EC;
        break;
    case 16:
        selectedAddressWord = baseAddressWord + 0x142C;
        break;
    case 15:
        selectedAddressWord = baseAddressWord + 0x13EC;
        break;
    }
    return selectedAddressWord;
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

/* For a nonnull node, store the supplied word at field14B8; a null node
 * performs no store. RE_UNKNOWN: The stored word meaning and node lifetime are
 * unproved. */
#line 378 "src/modules/uvdyn_rom.c"
/* Store the opaque value at 0x14B8; null state is an original no-op. */
void uvDynSetValue14B8(DynResetState *nodeState, s32 storedWord) {
    if (nodeState == NULL) {
        return;
    }
    nodeState->value14B8 = storedWord;
}
#line 384 "src/modules/uvdyn_rom.c"

/* For a nonnull source, copy vector12DC before freshly reading scalar12E8 into
 * the destination. A null source leaves the destination untouched. RE_UNKNOWN:
 * Source/destination alias domains and output validity are unchecked; the
 * vector provider may affect the subsequent scalar read. */
#line 279 "src/modules/uvdyn_rom.c"
/* Copy the vector at 0x12DC and scalar at 0x12E8 into the output. Null
 * records leave output unchanged; the values have no established gameplay names. */
void uvDynGetVectorScalar12DC(DynVectorFields *sourceRecord, DynVectorScalar *destination) {
    if (sourceRecord != NULL) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&destination->vector, &sourceRecord->vector12DC);
        destination->scalar = sourceRecord->value12E8;
    }
}
#line 280 "src/modules/uvdyn_rom.c"

/* Checks destination count for equality to10 before examining prior
 * membership; removes from the old collection before assigning and inserting
 * the new collection. RE_UNKNOWN: Count validity/capacity and ownership across
 * callbacks remain unproven; equality-to10 must not become a stronger range
 * check. */
#line 281 "src/modules/uvdyn_rom.c"
/* Change the node's linked collection, removing its old membership first.
 * A nonnull destination whose count equals ten is rejected before checking for
 * an unchanged link. Null clears the link; original count invariants are required. */
void uvDynSetLinkedCollection(DynLinkedNode *memberNode, DynLinkedCollection *destinationCollection) {
    if (destinationCollection != NULL && destinationCollection->count == 10) {
        return;
    }
    if (memberNode->linkedCollection != NULL) {
        if (destinationCollection == memberNode->linkedCollection) {
            return;
        }
        uvDynRemoveLinkedNode(memberNode->linkedCollection, memberNode);
    }
    memberNode->linkedCollection = destinationCollection;
    if (destinationCollection != NULL) {
        uvDynInsertUniqueLinkedNode(destinationCollection, memberNode);
    }
}
#line 282 "src/modules/uvdyn_rom.c"

/* Returns the linkedCollection field directly. RE_UNKNOWN: Input validity,
 * lifetime and whether the returned collection is owned or borrowed remain
 * unproven. */
#line 283 "src/modules/uvdyn_rom.c"
/* Return the node's linked collection. The original requires a valid node. */
DynLinkedCollection *uvDynGetLinkedCollection(DynLinkedNode *memberNode) {
    return memberNode->linkedCollection;
}
#line 286 "src/modules/uvdyn_rom.c"

/* Rejects null/duplicate candidates and count==2; appends before scanning the
 * prior owner, then assigns owner and conditionally forwards the DOBJ handle.
 * RE_UNKNOWN: The scan helper performs no removal; do not infer detachment or
 * repair owner/count consistency. Count bounds and provider object validity
 * remain unproven. */
#line 287 "src/modules/uvdyn_rom.c"
/* Add a unique nonnull attachment unless count equals two, set its owner,
 * and in mode zero propagate the DOBJ handle to its intersection record.
 * The previous-owner helper only scans: original code does not remove old
 * membership. Preserve that behavior and the original valid-count contract. */
void uvDynAddUniqueAttachment(DynResetState *destinationOwner, DynAttachmentPrefix *candidateAttachment) {
    u16 attachmentIndex;
    if (candidateAttachment == NULL) {
        return;
    }
    for (attachmentIndex = 0; attachmentIndex < destinationOwner->attachmentCount; attachmentIndex++) {
        if (candidateAttachment == destinationOwner->attachments[attachmentIndex]) {
            return;
        }
    }
    if (destinationOwner->attachmentCount == 2) {
        return;
    }
    destinationOwner->attachments[destinationOwner->attachmentCount] = candidateAttachment;
    destinationOwner->attachmentCount++;
    if (candidateAttachment->owner != NULL) {
        uvDynScanAttachmentMembership(candidateAttachment->owner, candidateAttachment);
    }
    candidateAttachment->owner = destinationOwner;
    if (candidateAttachment->intersectionRecord != NULL && destinationOwner->dobjUpdateMode == 0) {
        D_uvdyn_rom_00411F7C->setDobjHandle(candidateAttachment->intersectionRecord, destinationOwner->dobjHandle);
    }
}
#line 288 "src/modules/uvdyn_rom.c"

/* RE_ORIGINAL_QUIRK: Scans a nonnull owner for pointer equality without field
 * writes. The current C interface is void; native V0 carries scan state at
 * return. RE_UNKNOWN: The historical return contract and caller use of that
 * register are unproved; any intended unlinking role is unknown. Preserve the
 * scan without inventing removal or membership mutation. */
#line 289 "src/modules/uvdyn_rom.c"
/* Preserve the original non-mutating membership scan and early return.
 * This routine neither removes the attachment nor changes its owner, even
 * though the original add routine calls it for a previous owner. */
void uvDynScanAttachmentMembership(DynResetState *owner, DynAttachmentPrefix *candidateAttachment) {
    u16 attachmentIndex;
    if (owner != NULL) {
        for (attachmentIndex = 0; attachmentIndex < owner->attachmentCount; attachmentIndex++) {
            if (candidateAttachment == owner->attachments[attachmentIndex]) {
                return;
            }
        }
    }
}
#line 290 "src/modules/uvdyn_rom.c"

/* RE_ORIGINAL_QUIRK: Returns null only when attachmentCount<index; otherwise
 * indexes the attachment array. RE_UNKNOWN: Equality-to-count and negative
 * indices are not rejected in the native path; caller domain/full storage
 * extent remain unproved. */
#line 291 "src/modules/uvdyn_rom.c"
/* Return the indexed attachment unless index is greater than the live count.
 * Preserve the original inclusive test and missing negative-index check; callers
 * must still supply a valid index. Null state is not supported by the original. */
DynAttachmentPrefix *uvDynGetAttachmentByIndex(DynResetState *owner, s32 attachmentIndex) {
    if (owner->attachmentCount < attachmentIndex) {
        return NULL;
    }
    return owner->attachments[attachmentIndex];
}
#line 297 "src/modules/uvdyn_rom.c"

/* Returns0 for null owner, otherwise its attachmentCount. RE_UNKNOWN: A
 * nonnull count is not validated against the two-pointer focused view;
 * allocation and corruption domains are unknown. */
#line 298 "src/modules/uvdyn_rom.c"
/* Return the live attachment count, or zero for a null state. */
s32 uvDynGetAttachmentCount(DynResetState *owner) {
    if (owner == NULL) {
        return 0;
    }
    return owner->attachmentCount;
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

/* Stores the handle first; only mode0 queries property7, copies the resulting
 * scalar and forwards the handle to each nonnull intersection record.
 * RE_UNKNOWN: Provider may leave a property output unchanged outside its
 * domain; preserve the current read rather than introducing an initializer.
 * Callback mutation/count domains remain unknown. */
#line 319 "src/modules/uvdyn_rom.c"
/* Store the DOBJ handle. In mode zero, read DOBJ property seven into the
 * original scalar pair and propagate the handle to nonnull attachment
 * intersection records. Preserve 16-bit iteration and live count reloads. */
void uvDynSetDobjHandle(DynResetState *owner, s32 inputDobjHandle) {
    u16 attachmentIndex;
    DynAttachmentPrefix *boundAttachment;
    owner->dobjHandle = inputDobjHandle;
    if (owner->dobjUpdateMode == 0) {
        D_uvdyn_rom_00411F84->uvDobjGetProp(inputDobjHandle, 7, &owner->value14AC, 0);
        owner->value14B0 = owner->value14AC;
        for (attachmentIndex = 0; attachmentIndex < owner->attachmentCount; attachmentIndex++) {
            boundAttachment = owner->attachments[attachmentIndex];
            if (boundAttachment->intersectionRecord != NULL) {
                D_uvdyn_rom_00411F7C->setDobjHandle(boundAttachment->intersectionRecord, inputDobjHandle);
            }
        }
    }
}
#line 320 "src/modules/uvdyn_rom.c"

/* Returns dobjHandle directly. RE_UNKNOWN: Handle sentinel/validity, state
 * lifetime and ownership remain unknown. */
#line 321 "src/modules/uvdyn_rom.c"
/* Return the stored DOBJ handle; the original requires a valid state. */
s32 uvDynGetDobjHandle(DynResetState *owner) {
    return owner->dobjHandle;
}
#line 324 "src/modules/uvdyn_rom.c"

/* Stores the supplied signed word at value2C. RE_UNKNOWN: The physical meaning
 * and allowed numeric domain of this field remain unknown. */
#line 325 "src/modules/uvdyn_rom.c"
/* Store the opaque signed word at 0x2C. The original requires a valid state;
 * a more specific gameplay meaning has not been established. */
void uvDynSetValue2C(DynResetState *owner, s32 inputValue2C) {
    owner->value2C = inputValue2C;
}
#line 328 "src/modules/uvdyn_rom.c"

/* Returns value2C directly. RE_UNKNOWN: The physical meaning and allowed
 * numeric domain of this field remain unknown. */
#line 329 "src/modules/uvdyn_rom.c"
/* Return the opaque signed word at 0x2C from a valid state. */
s32 uvDynGetValue2C(DynResetState *owner) {
    return owner->value2C;
}
#line 332 "src/modules/uvdyn_rom.c"

/* Store the incoming raw words in order at node+0x1550+4*index and
 * node+0x1578+4*index. Only when index is 5 and the previous first word is
 * zero, first set bit 0x2 on the node and its kind-zero attachment children.
 * RE_ORIGINAL_QUIRK: the signed index has no range check; both list indices
 * wrap to u16. The original checks the attachment and its intersection
 * pointer, but not the subsequent value or child pointers. Preserve signed
 * count comparisons and count reloads after potentially aliasing child writes.
 * RE_UNKNOWN: callback signatures, slot/bit meanings, valid index/count
 * bounds, complete list capacities and caller alias/reachability guarantees.
 * Trace original table consumers, list producers and callers before adding
 * validation or replacing these raw words with callable declarations. */
#line 333 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404834.s")

#line 335 "src/modules/uvdyn_rom.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}
#line 337 "src/modules/uvdyn_rom.c"

/* Returns0 on null state, otherwise firstParameterCount. RE_UNKNOWN: Count
 * initialization, full bank capacity and valid state extent remain unknown. */
#line 338 "src/modules/uvdyn_rom.c"
/* Return the first parameter-bank count, or zero for a null state. This field
 * is the count consumed by the recovered first-bank indexed output helper. */
s32 uvDynGetFirstParameterCount(DynResetState *parameterState) {
    if (parameterState == NULL) {
        return 0;
    }
    return parameterState->firstParameterCount;
}
#line 344 "src/modules/uvdyn_rom.c"

/* Null or index>=firstCount returns before outputs; valid path writes
 * key/value/kind then invokes vector-copy. RE_UNKNOWN: Output pointer
 * validity/aliasing, bank capacity and key/kind semantics remain unknown.
 * Rejected calls do not initialize outputs. */
#line 345 "src/modules/uvdyn_rom.c"
/* Copy the indexed first-bank key/value, unsigned kind and vector outputs.
 * Null state or index at/above the live count leaves every output unchanged.
 * RE_UNKNOWN: count validity for the four observed slots and key/value/kind
 * meanings; trace bank producers and original callers before assuming bounds. */
void uvDynGetFirstParameterEntry(DynParameterBanks *parameterBanks, u16 parameterIndex, u32 *outKey, u32 *outValue, u16 *outKind, Vec3F *outVector) {
    if (parameterBanks == NULL) {
        return;
    }
    if (parameterIndex >= parameterBanks->firstCount) {
        return;
    }
    *outKey = parameterBanks->firstKeys[parameterIndex];
    *outValue = parameterBanks->firstValues[parameterIndex];
    *outKind = parameterBanks->firstKinds[parameterIndex];
    D_uvdyn_rom_00411F74->uvVec3FCopy(outVector, &parameterBanks->firstVectors[parameterIndex]);
}
#line 346 "src/modules/uvdyn_rom.c"

/* Sets the parameter flag before vector-copy, then writes the two scalar
 * fields. RE_UNKNOWN: Flag meaning, scalar units, record extent and callback-
 * visible aliasing remain unknown; preserve write/call order. */
#line 347 "src/modules/uvdyn_rom.c"
/* Enable the parameter flag, copy the input vector and store the two scalar
 * parameters at their original offsets. The original requires a valid record. */
void uvDynSetVectorParameters(DynVectorFields *parameterRecord, Vec3F *inputVector, f32 scalar12B8, f32 scalar12BC) {
    parameterRecord->parameterFlag = 1;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&parameterRecord->vector12C0, inputVector);
    parameterRecord->value12B8 = scalar12B8;
    parameterRecord->value12BC = scalar12BC;
}
#line 348 "src/modules/uvdyn_rom.c"

/* Snapshots the flag; nonzero path copies vector, writes both scalars and
 * reloads the flag afterward. RE_UNKNOWN: Do not replace the final reload with
 * the initial snapshot; output aliasing and provider effects are unproven.
 * Flag0 leaves outputs untouched. */
#line 349 "src/modules/uvdyn_rom.c"
/* Return the original parameter flag. Only when nonzero, copy the vector
 * and two scalars; reload the flag after the external copy as the original does. */
u16 uvDynGetVectorParameters(DynVectorFields *parameterRecord, Vec3F *outVector, f32 *outScalar12B8, f32 *outScalar12BC) {
    u16 returnedParameterFlag;
    returnedParameterFlag = parameterRecord->parameterFlag;
    if (returnedParameterFlag != 0) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(outVector, &parameterRecord->vector12C0);
        *outScalar12B8 = parameterRecord->value12B8;
        *outScalar12BC = parameterRecord->value12BC;
        returnedParameterFlag = parameterRecord->parameterFlag;
    }
    return returnedParameterFlag;
}
#line 350 "src/modules/uvdyn_rom.c"

/* Writes0 to parameterFlag. RE_UNKNOWN: Meaning and lifecycle of the flag
 * remain unknown; no other fields are reset. */
#line 351 "src/modules/uvdyn_rom.c"
/* Clear the vector-parameter flag in a valid node state. */
void uvDynClearParameterFlag(DynResetState *parameterState) {
    parameterState->parameterFlag = 0;
}
#line 354 "src/modules/uvdyn_rom.c"

/* Returns0 on null banks, otherwise secondCount. RE_UNKNOWN: Count
 * initialization, full bank capacity and valid state extent remain unknown. */
#line 355 "src/modules/uvdyn_rom.c"
/* Return the second parameter-bank count, or zero for a null state. */
s32 uvDynGetSecondParameterCount(DynParameterBanks *parameterBanks) {
    if (parameterBanks == NULL) {
        return 0;
    }
    return parameterBanks->secondCount;
}
#line 361 "src/modules/uvdyn_rom.c"

/* Rejected calls leave outputs unchanged; valid path writes key/value/kind,
 * copies payload vector and freshly reads payload08/0C afterward. RE_UNKNOWN:
 * Payload pointer lifetime, output aliasing, bank capacity and physical field
 * meanings remain unknown; preserve callback/reload ordering. */
#line 362 "src/modules/uvdyn_rom.c"
/* Copy the second-bank key/value/kind and payload vector/words. Null state
 * or index at/above count leaves outputs unchanged; preserve payload reloads.
 * RE_UNKNOWN: four-slot count validity and payload lifetime/aliasing; trace
 * bank producers and callers before treating those input guarantees as proven. */
void uvDynGetSecondParameterEntry(DynParameterBanks *parameterBanks, u16 parameterIndex, u32 *outKey, u32 *outValue, u16 *outKind, Vec3F *outVector, u32 *outPayloadValue08, u32 *outPayloadValue0C) {
    if (parameterBanks == NULL) {
        return;
    }
    if (parameterIndex >= parameterBanks->secondCount) {
        return;
    }
    *outKey = parameterBanks->secondKeys[parameterIndex];
    *outValue = parameterBanks->secondValues[parameterIndex];
    *outKind = parameterBanks->secondKinds[parameterIndex];
    D_uvdyn_rom_00411F74->uvVec3FCopy(outVector, &parameterBanks->secondPayloads[parameterIndex]->vector34);
    *outPayloadValue08 = parameterBanks->secondPayloads[parameterIndex]->value08;
    *outPayloadValue0C = parameterBanks->secondPayloads[parameterIndex]->value0C;
}
#line 363 "src/modules/uvdyn_rom.c"

/* Returns0 on null state, otherwise the unsigned halfword entryCount.
 * RE_UNKNOWN: The count alone does not establish full collection or array
 * capacity. */
#line 364 "src/modules/uvdyn_rom.c"
/* Return the indexed entry count, or zero for a null state. */
u16 uvDynGetIndexedEntryCount(DynIndexedNodeFields *indexedState) {
    if (indexedState == NULL) {
        return 0;
    }
    return indexedState->entryCount;
}
#line 370 "src/modules/uvdyn_rom.c"

/* Rejects null or index>=entryCount; forms an unsigned16-bit collection index
 * from offset+index, then writes the three outputs and returns1. RE_UNKNOWN:
 * Offset addition wraps to16bits in the native path; storage capacity, null
 * collection and output aliasing remain unproven. Rejected calls return0
 * without output initialization. */
#line 371 "src/modules/uvdyn_rom.c"
/* Copy the node-relative indexed collection value, unsigned kind and opaque
 * four-byte aggregate. Null state or index at/above its entry count returns zero
 * without changing outputs; success returns one. The combined collection index
 * wraps to sixteen bits and is not checked against the collection arrays.
 * Preserve the original cached collection pointer and aggregate-copy ABI. */
s32 uvDynGetIndexedCollectionEntry(DynIndexedNodeFields *indexedState, u16 entryIndex, u32 *outValue, u16 *outKind, DynCollectionWord *outWord) {
    u16 wrappedCollectionIndex;
    DynIndexedCollectionFields *collection;
    if (indexedState == NULL) {
        return 0;
    }
    if (entryIndex >= indexedState->entryCount) {
        return 0;
    }
    wrappedCollectionIndex = indexedState->entryOffset + entryIndex;
    collection = indexedState->collection;
    *outValue = collection->values[wrappedCollectionIndex];
    *outKind = collection->kinds[wrappedCollectionIndex];
    *outWord = collection->words[wrappedCollectionIndex];
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

/* Invokes optional callback before clearing first count; copies saved vectors,
 * updates attachment transforms, copies matrix/vector state and sets
 * value14A8=-1. RE_UNKNOWN: Callback lifetime/mutation, live attachment-count
 * validity, null intersection record reachability and scalar physical units
 * remain unknown. Do not infer full-state reset or ownership. */
#line 377 "src/modules/uvdyn_rom.c"
/* Invoke the optional reset callback, clear firstParameterCount, copy the observed
 * vector pairs and matrix, and update each attachment's intersection transform
 * using property three. Finish with the original scalar and -1 sentinel.
 * Preserve the 16-bit attachment loop and unknown gameplay field meanings. */
void uvDynResetLinkedNodeState(DynResetState *nodeState) {
    u16 attachmentIndex;
    void (*callback)(DynResetState *, void *);
    callback = nodeState->callback;
    if (callback != NULL) {
        callback(nodeState, nodeState->callbackContext);
    }
    nodeState->firstParameterCount = 0;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&nodeState->vector14EC, &nodeState->vector14E0);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&nodeState->vector14C8, &nodeState->vector14BC);
    for (attachmentIndex = 0; attachmentIndex < nodeState->attachmentCount; attachmentIndex++) {
        D_uvdyn_rom_00411F7C->setTransformProperty(nodeState->attachments[attachmentIndex]->intersectionRecord, 3, &nodeState->matrix12EC);
    }
    D_uvdyn_rom_00411F70->uvMat4FCopy(&nodeState->matrix132C, &nodeState->matrix12EC);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&nodeState->vector1478, &nodeState->vector146C);
    nodeState->value148C = D_uvdyn_rom_00411CBC;
    nodeState->value14A8 = -1;
}
#line 378 "src/modules/uvdyn_rom.c"

/* Snapshot callback1574; when nonnull, pass the node and its context159C.
 * RE_UNKNOWN: Callback registration, object lifetime and the full historical
 * callback contract remain unproved. */
#line 379 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1574 with this state and the opaque context word
 * at 0x159C. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1574(DynStateCallbacks *nodeState) {
    void (*callback)(void *, s32);
    callback = nodeState->callback1574;
    if (callback != NULL) {
        callback(nodeState, nodeState->context159C);
    }
}
#line 385 "src/modules/uvdyn_rom.c"

/* Snapshot callback1558; when nonnull, pass the node and its context1580.
 * RE_UNKNOWN: Callback registration, object lifetime and the full historical
 * callback contract remain unproved. */
#line 386 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1558 with this state and the opaque context word
 * at 0x1580. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1558(DynStateCallbacks *nodeState) {
    void (*callback)(void *, s32);
    callback = nodeState->callback1558;
    if (callback != NULL) {
        callback(nodeState, nodeState->context1580);
    }
}
#line 392 "src/modules/uvdyn_rom.c"

/* Snapshot callback1568; when nonnull, pass the node and its context1590.
 * RE_UNKNOWN: Callback registration, object lifetime and the full historical
 * callback contract remain unproved. */
#line 393 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1568 with this state and the opaque context word
 * at 0x1590. Cache the pointer once; an absent callback has no effect. */
void uvDynInvokeStateCallback1568(DynStateCallbacks *nodeState) {
    void (*callback)(void *, s32);
    callback = nodeState->callback1568;
    if (callback != NULL) {
        callback(nodeState, nodeState->context1590);
    }
}
#line 399 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: The callback result is an opaque u16, not a proved boolean.
 * Callback/context ownership and request retention are unknown; the request
 * itself is a stack object whose storage ends with this invocation. */
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

/* RE_UNKNOWN: Callback installation, ownership and reentrancy are unknown.
 * The original loads slot 0x1560 once and reads the opaque context word at
 * 0x1588 only on the nonnull path; neither word is reloaded after the call. */
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

/* When callback1570 is nonnull, forward the supplied word and context1598.
 * RE_UNKNOWN: The forwarded word and context are opaque; callback ownership
 * and lifetime are unproved. */
#line 409 "src/modules/uvdyn_rom.c"
/* Invoke callback slot 0x1570 with the supplied value and the opaque context
 * word at 0x1598. The state itself is not passed; an absent callback has no effect. */
void uvDynInvokeValueCallback1570(DynStateCallbacks *nodeState, s32 callbackValue) {
    void (*callback)(s32, s32);
    callback = nodeState->callback1570;
    if (callback != NULL) {
        callback(callbackValue, nodeState->context1598);
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

/* RE_UNKNOWN: The units, valid domain and purpose of value1488 and its
 * thresholds are unknown. Caller state validity and allowed matrix/vector
 * overlap are not established here; preserve the ordered NaN-sensitive gate. */
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

/* Original sphere/query-range refresh. Native 03294 receives the incoming
 * sphere and node sphere at 0x12DC; it returns zero when the first fits inside
 * the second, otherwise enlarges/recenters the second and returns one. A
 * nonzero result rebuilds the stored ranges at 0x12CC..0x12DA: value04 == -1
 * uses native 10250, FC88 and 107FC; other values conditionally use 9010 and
 * zero the remaining counts. The zero result first rebinds the existing query
 * record range through uvDynSetIndexedQueryRecordBank, then optionally
 * refreshes only the indexed range. Native 10AEC rebinds the parameter/indexed
 * ranges on every exit path. Count snapshots remain ordered around calls.
 * RE_ORIGINAL_QUIRK: workspace counts use the pointer saved before 03294,
 * while later helper arguments reload node offset 0x14. The third incoming
 * word is homed as 32 bits, but only its low byte controls optional refresh.
 * Preserve these observed views rather than assuming pointer stability or
 * replacing the gate with a test of the complete incoming word.
 * RE_UNKNOWN: value04's enum, vector frames at 0x135C/0x131C, the scalar at
 * 0x14B4, complete workspace ownership/capacity, attachment validity and the
 * historical input prototype. Trace original callers, workspace/attachment
 * producers and range consumers before assigning units or bounds. The clean
 * draft has all original calls, branch positions and nine complete ordered
 * relocations, but differs in twelve stack-immediate words: original frame
 * 48 bytes versus 56, sphere home 40 versus 44, workspace home 44 versus 52
 * and incoming word home 56 versus 64. Genuine source declaration/lifetime
 * evidence is needed; do not invent padding or force registers. */
#line 432 "src/modules/uvdyn_rom.c"
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

/* RE_UNKNOWN: Coordinate units, state ownership and valid DOBJ handle
 * domains are not established by this wrapper. It adds no validation before
 * forwarding the translated matrix and part zero to the imported provider. */
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

/* Original stored-vector interpolation and matrix update wrapper. Store the
 * first scalar at 0x30, copy matrix 0x12EC to 0x13AC, then copy vectors
 * 0x14BC/0x14E0 to 0x14D4/0x14F8. FVEC subtract/scale/add interpolates
 * 0x14E0 from 0x14EC using the first scalar. A zero flag at 0x154C also
 * interpolates 0x14BC from 0x14C8 before copying matrix 0x132C to 0x12EC;
 * a nonzero flag instead interpolates the FMTX direction-transform results
 * before that matrix copy. Native 0071C then receives the full flag, two
 * matrices, five vector addresses and the second scalar. Finish with the
 * linear 3x3 copy to 0x13EC and native 7C04, 09BC, then 94CC updates.
 * RE_ORIGINAL_QUIRK: for a zero flag, native 0071C writes the first transformed
 * scratch vector before reading it; for a nonzero flag the caller writes it.
 * Zero and exactly one select distinct native helper branches. Preserve the
 * full halfword value and separate in-place provider operations; the final
 * linear 3x3 copy leaves the remaining destination matrix elements untouched.
 * RE_UNKNOWN: vector/matrix frames, scalar units, valid interpolation domains,
 * flag-enum names and historical source-local organization. Trace original
 * callers, stored-bank writers and native 0071C consumers before assigning
 * physical roles or bounds. The clean C recovery is parked: all provider calls,
 * branch positions and ordered relocations match, but the 136-byte frame and
 * stack homes differ from the candidate's 144-byte frame. Genuine source
 * declarations/lifetimes are needed; do not invent padding or force registers. */
#line 444 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040954C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040981C.s")

/* Require candidate value strictly below the best value and strictly above
 * zero. An optional first-attachment callback may veto through its result
 * halfword; otherwise reload the candidate value, update the best value, and
 * copy the record. RE_UNKNOWN: NaN comparisons reject the candidate. The first
 * attachment is unchecked, callback mutation is not revalidated, and
 * alias/record-storage domains are unproved. */
#line 448 "src/modules/uvdyn_rom.c"
/* Accept a lower positive record value unless the first attachment's callback
 * clears request.result. Return 1 after the original 88-byte intersection copy,
 * -1 for callback rejection, or 0 for an ineligible value. Reload the record value
 * after the callback without repeating the eligibility test, as in the original. */
s32 uvDynTryAcceptLowerPositiveRecord(DynResetState *nodeState, void *outputRecord, f32 *bestAcceptedValue, DynCandidateRecord *candidateRecord) {
    void (*callback)(DynCandidateRequest *, s32);
    DynCandidateRequest callbackRequest;
    if (candidateRecord->value < *bestAcceptedValue && 0.0f < candidateRecord->value) {
        callback = ((DynCandidateCallbacks *)nodeState->attachments[0])->callback;
        if (callback != NULL) {
            callbackRequest.result = 1;
            callbackRequest.record = candidateRecord;
            callbackRequest.value = -1;
            callbackRequest.value08 = 0;
            callback(&callbackRequest, ((DynCandidateCallbacks *)nodeState->attachments[0])->callbackContext);
            if (callbackRequest.result == 0) {
                return -1;
            }
        }
        *bestAcceptedValue = candidateRecord->value;
        D_uvdyn_rom_00411F7C->copyRecord(outputRecord, candidateRecord);
        return 1;
    }
    return 0;
}
/* Return the unsigned halfword at byte offset0x12D6 without a null-pointer
 * gate. RE_UNKNOWN: The concrete object type and field meaning are unproved;
 * retain the current interface. */
#line 449 "src/modules/uvdyn_rom.c"

u16 func_uvdyn_rom_00409A40(void *recordBytes) {
    return *(u16 *)((u8 *)recordBytes + 0x12D6);
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

/* RE_UNKNOWN: Allocation failure, both registry capacities and attachment
 * ownership are unchecked here. Property zero with value one also updates
 * a separate pointer registry in the original setter; the master registry
 * and that property-controlled registry must not be treated as one list. */
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

/* RE_ORIGINAL_QUIRK: Disable property zero before snapshotting the master
 * scan count; the later compaction loop reloads the live master count. The
 * removed object index and the final vacated array slot are left unchanged.
 * RE_UNKNOWN: Remaining links and ownership are unknown; this routine does
 * not free the object or establish that other users have released it. */
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
/* Write halfword1 at byte offset0x23C without a null-pointer gate. RE_UNKNOWN:
 * The concrete object type, flag meaning and lifecycle are unproved; retain
 * the current interface. */
#line 473 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00409BC0(void *stateBytes) {
    *(s16 *)((u8 *)stateBytes + 0x23C) = 1;
}

/* Return the attachment owner pointer without a null-attachment gate.
 * RE_UNKNOWN: This accessor does not establish ownership or owner lifetime. */
#line 478 "src/modules/uvdyn_rom.c"
/* Return the owner of a valid attachment; an unattached owner may be null. */
DynResetState *uvDynGetAttachmentOwner(DynAttachmentPrefix *attachmentState) {
    return attachmentState->owner;
}
#line 481 "src/modules/uvdyn_rom.c"

/* Refresh vectors and forward owner matrix12EC to intersection property3. For
 * kind1, subtract the value vector, store its length, and scale the delta by
 * its reciprocal only above the original threshold; then invoke a nonnull
 * callback. RE_UNKNOWN: Pointer validity, vector units, threshold meaning and
 * callback mutation are unproved; preserve fresh field/provider reads around
 * calls. */
#line 482 "src/modules/uvdyn_rom.c"
/* Refresh the attachment and its intersection transform. For a kind-one
 * value record, store vector1C minus the record vector, cache its original
 * length, and normalize the delta only above the original threshold. Invoke
 * the optional attachment callback afterward for every kind. Preserve the
 * original valid-owner/intersection preconditions and live field reloads. */
void uvDynUpdateAttachmentDelta(DynAttachmentUpdateState *attachmentState) {
    DynAttachmentDeltaFields *vectors;
    Vec3F *delta;
    uvDynRefreshAttachmentVectors((DynAttachmentPrefix *)attachmentState);
    D_uvdyn_rom_00411F7C->setTransformProperty(attachmentState->intersectionRecord, 3, &attachmentState->owner->matrix12EC);
    if (((DynIsectKindOneValue *)attachmentState->intersectionRecord->valueRecord)->kind == 1) {
        vectors = &attachmentState->vectors;
        D_uvdyn_rom_00411F74->uvVec3FSub(&attachmentState->vectors.delta, &vectors->first, &((DynIsectKindOneValue *)attachmentState->intersectionRecord->valueRecord)->vector18);
        delta = &vectors->delta;
        vectors->length = D_uvdyn_rom_00411F74->uvVec3FLen(delta);
        if (D_uvdyn_rom_00411D00 < vectors->length) {
            D_uvdyn_rom_00411F74->uvVec3FScale(delta, delta, 1.0f / vectors->length);
        }
    }
    if (attachmentState->callback != NULL) {
        attachmentState->callback(attachmentState, attachmentState->callbackContext);
    }
}
#line 483 "src/modules/uvdyn_rom.c"

/* Kind0 copies each live-count vector pair into consecutive attachment vectors
 * using a halfword index; kind1 copies one vector. Other kinds perform no
 * copy. RE_UNKNOWN: Value/list pointers, count range and destination capacity
 * are unchecked; vector-copy callbacks may change the live count. */
#line 484 "src/modules/uvdyn_rom.c"
/* Refresh attachment vectors from the intersection value record. Kind zero
 * copies each 28-byte record's two vectors into consecutive attachment vectors,
 * preserving 16-bit iteration and live count reloads after export callbacks.
 * Kind one copies only its single vector. Other kinds leave vectors unchanged;
 * the original requires valid intersection pointers and adequate storage. */
void uvDynRefreshAttachmentVectors(DynAttachmentPrefix *attachmentState) {
    DynIsectValuePrefix *intersectionValue;
    DynIsectVectorPairList *vectorPairList;
    u16 pairIndex;
    intersectionValue = ((DynIsectRecordPrefix *)attachmentState->intersectionRecord)->valueRecord;
    switch (intersectionValue->kind) {
        case 0:
            vectorPairList = (DynIsectVectorPairList *)&intersectionValue->children;
            for (pairIndex = 0; pairIndex < vectorPairList->count; pairIndex++) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachmentState)->vectors[pairIndex * 2], &vectorPairList->records[pairIndex].first);
                D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachmentState)->vectors[pairIndex * 2 + 1], &vectorPairList->records[pairIndex].second);
            }
            break;
        case 1:
            D_uvdyn_rom_00411F74->uvVec3FCopy(&((DynAttachmentVectorSequence *)attachmentState)->vectors[0], &((DynIsectKindOneValue *)intersectionValue)->vector18);
            break;
    }
}
#line 485 "src/modules/uvdyn_rom.c"

/* Attachment scalar-property setter: property 0 converts the incoming f32
 * through unsigned conversion and narrows to u16 before storing kind at 0x04;
 * properties 1/2 store the unchanged f32 at 0x14/0x18. Null or other selectors
 * return without writes. Only old-kind 0/new-kind 1 appends to the second
 * shared pointer list; old-kind 1/new-kind 0 removes its first matching entry.
 * RE_ORIGINAL_QUIRK: other transitions do not reconcile list membership.
 * Append capacity is unchecked; list counters/indices narrow to u16, removal
 * preserves order and the trailing stale word. The native scan bound and
 * separately retained shared count are cached before writes. For old kind
 * zero when the first narrowed result is not one, conversion runs again;
 * each conversion restores the floating control word.
 * RE_UNKNOWN: kind/property meanings, scalar units, valid conversion domain,
 * complete list capacity and caller membership/alias guarantees. Direct
 * creation/removal callers pass property 0 with 1.0f/0.0f respectively; trace
 * original indirect export 0xFC callers and list consumers for other inputs. */
#line 486 "src/modules/uvdyn_rom.c"
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409E18.s")

/* Return -1 for null or unsupported selectors; selector0 converts the unsigned
 * kind halfword to float, while1 and2 return fields14 and18. RE_UNKNOWN:
 * Numeric meanings, units and caller handling of the -1 sentinel are unproved. */
#line 488 "src/modules/uvdyn_rom.c"
/* Return the attachment's unsigned kind or scalar fields 0x14/0x18.
 * Their gameplay meanings remain unresolved. Null attachments or unsupported
 * properties return -1; preserve the original unsigned kind conversion. */
f32 uvDynGetAttachmentScalarProperty(DynAttachmentPrefix *attachmentState, s32 propertySelector) {
    if (attachmentState == NULL) {
        return -1.0f;
    }
    switch (propertySelector) {
        case 0:
            return (u32)attachmentState->kind;
        case 1:
            return attachmentState->value14;
        case 2:
            return attachmentState->value18;
        default:
            return -1.0f;
    }
}
#line 489 "src/modules/uvdyn_rom.c"

/* Skip only a repeated nonnull intersection. Store the new pointer before
 * querying value10, then read the current owner and forward its DOBJ handle
 * only in mode0. A null intersection clears value10. RE_UNKNOWN: Query
 * callbacks may alter attachment state; intersection ownership, provider
 * availability and owner/DOBJ validity are unproved. */
#line 490 "src/modules/uvdyn_rom.c"
/* Replace the attachment's intersection link and refresh field 0x10 through
 * the original intersection export. For an owner in mode zero, propagate its
 * DOBJ handle. Null clears the cached word; an unchanged nonnull link is skipped.
 * The cached word's meaning remains unresolved. */
void uvDynSetAttachmentIntersection(DynAttachmentPrefix *attachmentState, void *intersectionRecord) {
    if (attachmentState->intersectionRecord != NULL && intersectionRecord == attachmentState->intersectionRecord) {
        return;
    }
    attachmentState->intersectionRecord = intersectionRecord;
    if (intersectionRecord != NULL) {
        attachmentState->value10 = D_uvdyn_rom_00411F7C->getValue10(intersectionRecord);
        if (attachmentState->owner != NULL && attachmentState->owner->dobjUpdateMode == 0) {
            D_uvdyn_rom_00411F7C->setDobjHandle(intersectionRecord, attachmentState->owner->dobjHandle);
        }
    } else {
        attachmentState->value10 = 0;
    }
}
#line 491 "src/modules/uvdyn_rom.c"

/* Return the current intersection pointer without a null-attachment gate.
 * RE_UNKNOWN: This accessor does not establish intersection ownership,
 * lifetime or concrete full type. */
#line 492 "src/modules/uvdyn_rom.c"
/* Return the intersection record of a valid attachment; the record may be null. */
void *uvDynGetAttachmentIntersection(DynAttachmentPrefix *attachmentState) {
    return attachmentState->intersectionRecord;
}
#line 495 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A188.s")

/* Snapshot callback244; when nonnull, pass the attachment and context25C.
 * RE_UNKNOWN: Callback registration and the full historical callback contract
 * remain unproved. */
#line 498 "src/modules/uvdyn_rom.c"
/* Invoke attachment callback slot 0x244 with the attachment and its paired
 * context at 0x25C. A missing callback is an original no-op. */
void uvDynInvokeAttachmentCallback244(DynAttachmentCallbackSlots *attachmentState) {
    void (*callback)(void *, s32) = attachmentState->callback244;
    if (callback != NULL) {
        callback(attachmentState, attachmentState->context25C);
    }
}
#line 504 "src/modules/uvdyn_rom.c"

/* When callback248 is nonnull, forward the supplied word and context260.
 * RE_UNKNOWN: The word/context domains and callback lifetime remain unproved. */
#line 505 "src/modules/uvdyn_rom.c"
/* Invoke attachment callback slot 0x248 with the supplied opaque value and
 * its paired context at 0x260. Keep this distinct from the pointer callback ABI. */
void uvDynInvokeAttachmentValueCallback248(DynAttachmentCallbackSlots *attachmentState, s32 callbackValue) {
    void (*callback)(s32, s32) = attachmentState->callback248;
    if (callback != NULL) {
        callback(callbackValue, attachmentState->context260);
    }
}
#line 511 "src/modules/uvdyn_rom.c"

/* When the callback is nonnull, fetch an indexed word and kind halfword
 * through separate values-pointer reads, then pass the temporary request and
 * callback context. RE_UNKNOWN: The halfword index is unchecked, the remaining
 * request bytes are unspecified, and callback retention of the stack request
 * is unproved. */
#line 512 "src/modules/uvdyn_rom.c"
/* If installed, invoke the attachment callback with the indexed intersection
 * word and unsigned kind in the original request layout, plus its opaque context
 * word. Preserve the cached callback and original unchecked index/data contract;
 * no narrower gameplay meaning is established for the request values. */
void uvDynInvokeAttachmentValueCallback(DynAttachmentCallbackFields *attachmentState, u16 valueIndex) {
    void (*callback)(DynAttachmentCallbackRequest *, s32);
    DynAttachmentCallbackRequest callbackRequest;
    callback = attachmentState->callback;
    if (callback != NULL) {
        callbackRequest.word = attachmentState->values->words[valueIndex];
        callbackRequest.kind = attachmentState->values->kinds[valueIndex];
        callback(&callbackRequest, attachmentState->callbackContext);
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

/* Require a strictly lower positive candidate value. A nonnegative input word
 * enables the optional callback veto; a negative word bypasses it. After any
 * permitted callback, reload the candidate value, update the best value, and
 * copy the record. RE_UNKNOWN: NaN comparisons reject the candidate; callback
 * mutation is not revalidated. Record aliases, output extent and request-field
 * meanings are unproved. */
#line 524 "src/modules/uvdyn_rom.c"
/* Accept a lower positive record value, allowing an attachment callback to
 * reject it when value is nonnegative. A negative value bypasses the callback.
 * Return 1 for the original 88-byte copy, -1 for rejection, otherwise 0. Preserve
 * callback mutations and the original post-callback value reload. */
s32 uvDynTryAcceptAttachmentRecord(DynCandidateCallbacks *attachmentState, void *outputRecord, f32 *bestAcceptedValue, DynCandidateRecord *candidateRecord, s32 value, u16 value08) {
    void (*callback)(DynCandidateRequest *, s32);
    DynCandidateRequest callbackRequest;
    if (candidateRecord->value < *bestAcceptedValue && 0.0f < candidateRecord->value) {
        if (value >= 0) {
            callback = attachmentState->callback;
            if (callback != NULL) {
                callbackRequest.result = 1;
                callbackRequest.record = candidateRecord;
                callbackRequest.value = value;
                callbackRequest.value08 = value08;
                callback(&callbackRequest, attachmentState->callbackContext);
                if (callbackRequest.result == 0) {
                    return -1;
                }
            }
        }
        *bestAcceptedValue = candidateRecord->value;
        D_uvdyn_rom_00411F7C->copyRecord(outputRecord, candidateRecord);
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

/* RE_UNKNOWN: Allocation failure, registry extent/count overflow and ownership
 * are unchecked. Registration precedes both opaque BD14 property calls;
 * those calls do not establish the collection's gameplay lifecycle here. */
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

/* RE_UNKNOWN: BD14 runs before the registry-count snapshot. Only a found
 * entry is freed; separately allocated work buffers are not explicitly freed
 * here. Nested cleanup, ownership and repeat-destruction validity are unproved. */
#line 536 "src/modules/uvdyn_rom.c"
/* Set collection property zero to zero, find its registry entry, free the
 * collection and compact later pointers/indices. An absent entry is not freed.
 * Preserve the original separate 16-bit loops and live count reloads. This routine
 * makes no explicit frees of the collection's separately allocated work buffers. */
void uvDynDestroyCollection(DynLinkedCollection *collection) {
    u16 registryScanIndex;
    u16 registryShiftIndex;
    s32 registryCountSnapshot;
    func_uvdyn_rom_0040BD14(collection, 0, 0.0f);
    registryCountSnapshot = D_uvdyn_rom_00411F18;
    for (registryScanIndex = 0; registryScanIndex < registryCountSnapshot; registryScanIndex++) {
        if (collection == D_uvdyn_rom_00411EC8[registryScanIndex]) {
            break;
        }
    }
    if (registryScanIndex != registryCountSnapshot) {
        _uvMemFree(collection);
        D_uvdyn_rom_00411F18--;
        for (registryShiftIndex = registryScanIndex; registryShiftIndex < D_uvdyn_rom_00411F18; registryShiftIndex++) {
            D_uvdyn_rom_00411EC8[registryShiftIndex] = D_uvdyn_rom_00411EC8[registryShiftIndex + 1];
            D_uvdyn_rom_00411EC8[registryShiftIndex]->registryIndex = registryShiftIndex;
        }
    }
}
#line 537 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Allocation failure and repeated initialization are unchecked;
 * old work storage is overwritten without an explicit release here. Twenty
 * rows of 0x50 bytes are observed, not a general ownership/lifecycle guarantee. */
#line 538 "src/modules/uvdyn_rom.c"
/* Allocate the collection's two 80-byte work buffers and twenty zeroed
 * 80-byte rows, then set its work flag. The original does not check allocation
 * results or release previous buffers; callers must satisfy its init contract. */
void uvDynAllocateCollectionWorkBuffers(DynLinkedCollection *collection) {
    u16 workRowIndex;
    collection->workCount = 0;
    collection->workBuffer = _uvMemAllocAlign8(0x50);
    collection->workRows = _uvMemAllocAlign8(0x50);
    for (workRowIndex = 0; workRowIndex < 20; workRowIndex++) {
        collection->workRows[workRowIndex] = _uvMemAllocAlign8(0x50);
        uvMemSet(collection->workRows[workRowIndex], 0, 0x50);
    }
    collection->workFlag = 1;
}
#line 539 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: The middle C570 helper's effects remain opaque. Preserve the
 * transforms/C570/resets call order and argument reloads without assigning
 * a physical integration role or assuming the calls cannot mutate members. */
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

/* Return -1 for null or unsupported selectors. Selectors0 and1 convert the
 * unsigned halfwords active and valueF79E to float. RE_UNKNOWN: The field
 * meanings and caller interpretation of the -1 sentinel remain unproved. */
#line 548 "src/modules/uvdyn_rom.c"
/* Return collection property zero (active state) or one (field 0xF79E),
 * converting the unsigned 16-bit field through u32 as in the original.
 * Null collections and unsupported properties return -1. */
f32 uvDynGetCollectionScalarProperty(DynLinkedCollection *linkedCollection, s32 propertySelector) {
    if (linkedCollection == NULL) {
        return -1.0f;
    }
    switch (propertySelector) {
        case 0:
            return (u32)linkedCollection->active;
        case 1:
            return (u32)linkedCollection->valueF79E;
        default:
            return -1.0f;
    }
}
#line 549 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: value04 meaning, valid signed counts and storage capacity are
 * unproved. Duplicate identity exits before insertion; the first value04
 * other than -1 chooses the insertion point. This helper adds no bound check. */
#line 550 "src/modules/uvdyn_rom.c"
/* Insert a unique node before the first member whose value04 is not -1,
 * or append if none qualifies. Preserve member order while shifting the tail.
 * value04's gameplay meaning is unknown. This helper has no capacity check;
 * the association setter rejects a destination count of ten. */
void uvDynInsertUniqueLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 insertionIndex;
    s32 memberIndex;
    insertionIndex = collection->count;
    for (memberIndex = 0; memberIndex < collection->count; memberIndex++) {
        if (node == collection->members[memberIndex]) {
            return;
        }
        if (insertionIndex == collection->count && collection->members[memberIndex]->value04 != -1) {
            insertionIndex = memberIndex;
        }
    }
    for (memberIndex = collection->count - 1; memberIndex >= insertionIndex; memberIndex--) {
        collection->members[memberIndex + 1] = collection->members[memberIndex];
    }
    collection->members[insertionIndex] = node;
    collection->count++;
}
#line 551 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Member validity, capacity and signed-count/u16-index domains
 * remain caller contracts. Preserve first-match removal and the count reload
 * while shifting; an absent pointer leaves the collection unchanged. */
#line 552 "src/modules/uvdyn_rom.c"
/* Remove the first matching node and compact the remaining members.
 * Both scans use the original 16-bit index; the shifting loop reloads the count.
 * An absent node leaves the collection unchanged. */
void uvDynRemoveLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 foundIndex;
    u16 memberIndex;
    foundIndex = -1;
    for (memberIndex = 0; memberIndex < collection->count; memberIndex++) {
        if (node == collection->members[memberIndex]) {
            foundIndex = memberIndex;
            break;
        }
    }
    if (foundIndex != -1) {
        for (memberIndex = foundIndex; memberIndex < collection->count - 1; memberIndex++) {
            collection->members[memberIndex] = collection->members[memberIndex + 1];
        }
        collection->count--;
    }
}
#line 553 "src/modules/uvdyn_rom.c"

/* Scan for pointer equality with a halfword index, reject duplicates and
 * exactly count20, then append and increment the current count. RE_UNKNOWN:
 * Counts above20, negative counts, storage capacity and ownership are
 * unchecked; do not strengthen the original equality-only limit. */
#line 554 "src/modules/uvdyn_rom.c"
/* Append a unique opaque secondary value unless the count equals twenty.
 * Preserve the original 16-bit scan and equality-only capacity guard; the
 * surrounding object's full size and the values' gameplay meaning are unknown. */
void uvDynAppendUniqueSecondaryValue(DynSecondaryCollection *secondaryCollection, void *newMemberValue) {
    u16 memberScanIndex;
    for (memberScanIndex = 0; memberScanIndex < secondaryCollection->count; memberScanIndex++) {
        if (newMemberValue == secondaryCollection->members[memberScanIndex]) {
            return;
        }
    }
    if (secondaryCollection->count == 20) {
        return;
    }
    secondaryCollection->members[secondaryCollection->count] = newMemberValue;
    secondaryCollection->count++;
}
#line 555 "src/modules/uvdyn_rom.c"

/* Find the first matching pointer, shift later entries with a halfword index
 * and live count reads, then decrement count. An absent pointer leaves storage
 * unchanged. RE_UNKNOWN: Count/storage domains are unchecked; the former final
 * slot is not cleared and ownership is not released here. */
#line 556 "src/modules/uvdyn_rom.c"
/* Remove the first matching secondary value and compact the remaining list.
 * Preserve original 16-bit indices and live count reloads while shifting.
 * A missing value leaves the collection unchanged. */
void uvDynRemoveSecondaryValue(DynSecondaryCollection *secondaryCollection, void *removedMemberValue) {
    s32 foundMemberIndex;
    u16 memberShiftIndex;
    foundMemberIndex = -1;
    for (memberShiftIndex = 0; memberShiftIndex < secondaryCollection->count; memberShiftIndex++) {
        if (removedMemberValue == secondaryCollection->members[memberShiftIndex]) {
            foundMemberIndex = memberShiftIndex;
            break;
        }
    }
    if (foundMemberIndex != -1) {
        for (memberShiftIndex = foundMemberIndex; memberShiftIndex < secondaryCollection->count - 1; memberShiftIndex++) {
            secondaryCollection->members[memberShiftIndex] = secondaryCollection->members[memberShiftIndex + 1];
        }
        secondaryCollection->count--;
    }
}
#line 557 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Both member views address one containing collection, without
 * proving historical whole-object types/capacities. Counts and the shared
 * scalar pointer/value are reloaded after calls. Coordinate frames, scalar
 * units/lifetime and nested update effects remain unresolved. */
#line 558 "src/modules/uvdyn_rom.c"
/* Rebuild each linked node's matrix at 0x136C and run its original follow-up
 * update. Then rebuild each secondary member's matrix at 0x98 and pass the
 * shared scalar to its update routine. Preserve 16-bit indices and count reloads;
 * the follow-up routines' broader gameplay meanings remain unresolved. */
void uvDynUpdateCollectionMemberTransforms(DynLinkedCollection *collection) {
    DynResetState *linkedMember;
    DynSecondaryState *secondaryMember;
    u16 memberIndex;
    for (memberIndex = 0; memberIndex < collection->count; memberIndex++) {
        linkedMember = (DynResetState *)collection->members[memberIndex];
        uvDynComposeRelativeTransform(&linkedMember->matrix136C, &linkedMember->matrix12EC, &linkedMember->matrix132C);
        uvDynApplyTranslatedDobjTransform(linkedMember);
    }
    for (memberIndex = 0; memberIndex < ((DynSecondaryCollection *)collection)->count; memberIndex++) {
        secondaryMember = ((DynSecondaryCollection *)collection)->members[memberIndex];
        uvDynComposeRelativeTransform(&secondaryMember->matrix98, &secondaryMember->matrix18, &secondaryMember->matrix58);
        uvDynUpdateSecondaryStateOnce(secondaryMember, *D_uvdyn_rom_00411DB8);
    }
}
#line 559 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Reset names identify the invoked helpers, not a complete
 * lifecycle guarantee. Preserve linked-before-secondary order, u16 iteration
 * and live count reads; member validity and callback mutation are unproved. */
#line 560 "src/modules/uvdyn_rom.c"
/* Run the original per-member state reset for each linked node, then each
 * secondary value. Both collections are views of the same containing object;
 * the original 16-bit loops re-read their counts after each external call. */
void uvDynResetCollectionMemberState(DynLinkedCollection *collection) {
    u16 memberIndex;
    for (memberIndex = 0; memberIndex < collection->count; memberIndex++) {
        uvDynResetLinkedNodeState((DynResetState *)collection->members[memberIndex]);
    }
    for (memberIndex = 0; memberIndex < ((DynSecondaryCollection *)collection)->count; memberIndex++) {
        uvDynResetSecondaryState(((DynSecondaryCollection *)collection)->members[memberIndex]);
    }
}
#line 561 "src/modules/uvdyn_rom.c"

/* For primary members, move14B0 to14B4, load14AC into14B0 and replace14B4 only
 * under strict less-than before building the sphere; clear value04 except its
 * -1 sentinel. Then build secondary spheres in a separate live-count loop.
 * RE_UNKNOWN: Both loops use halfword indices and reload counts after calls.
 * Capacity, field units and phase meaning are unproved; preserve strict
 * comparisons and all field/provider reloads. */
#line 562 "src/modules/uvdyn_rom.c"
/* Build enclosing spheres from each member's previous/current translations.
 * Node spheres use the greater of the old and new extra-radius values; preserve
 * the original ordered comparison and retain value04 == -1 while clearing other
 * values. Secondary spheres use their stored radius. Reload both collection
 * counts after calls and keep the original 16-bit iteration. */
void uvDynBuildCollectionMemberSpheres(DynLinkedCollection *linkedCollection) {
    u16 memberIndex;
    DynResetState *memberState;
    DynSecondaryState *secondaryState;
    for (memberIndex = 0; memberIndex < linkedCollection->count; memberIndex++) {
        memberState = (DynResetState *)linkedCollection->members[memberIndex];
        memberState->value14B4 = memberState->value14B0;
        memberState->value14B0 = memberState->value14AC;
        if (memberState->value14B4 < memberState->value14AC) {
            memberState->value14B4 = memberState->value14AC;
        }
        uvDynBuildPointPairSphere(&memberState->sphere12DC, (Vec3F *)&memberState->matrix132C.xw, (Vec3F *)&memberState->matrix12EC.xw, memberState->value14B4);
        if (memberState->value04 != -1) {
            memberState->value04 = 0;
        }
    }
    for (memberIndex = 0; memberIndex < linkedCollection->secondaryCount; memberIndex++) {
        secondaryState = linkedCollection->secondaryMembers[memberIndex];
        uvDynBuildPointPairSphere(&secondaryState->sphere13C, (Vec3F *)&secondaryState->matrix58.xw, (Vec3F *)&secondaryState->matrix18.xw, secondaryState->radius138);
    }
}
#line 563 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E8E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040F78C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040FC88.s")

u16 uvDynAppendSphereQueryCandidates(DynSphereQueryCollection *collection, s32 excludedDobj, DynSphere *sphere, u8 transformedBounds, void *association) {
    /* Append overlapping node/secondary candidates, then query their DOBJ data.
     * RE_QUIRK: Candidate append stops only at count==30. Null associations
     * never match an existing entry but can be appended; -1 disables that list.
     * A result copy requires count+returned <120, rejecting an exact fill.
     * The return is the added candidate count, not the copied-result count.
     * RE_UNKNOWN: Valid counts, sphere units, provider scratch ownership and
     * association lifetime/aliasing remain caller or provider constraints. */
    u8 excludedFlags;
    Vec3F *center;
    void **resultPointers;
    void *scratchSecond;
    void *scratchFirst;
    f32 radius;
    s32 addedCandidates;
    DynSphereQueryNode *node;
    DynSphereQuerySecondary *secondary;
    void **destination;
    s32 returned;
    u16 objectIndex;
    u16 i;
    u16 copiedResults;
    u16 initialObjectCount;
    u16 j;

    if (excludedDobj != 0xFFFF) {
        excludedFlags = ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->getObjectFlags(excludedDobj);
        if (excludedFlags & 1) {
            ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->setObjectFlags(excludedDobj, excludedFlags - 1);
        }
    }
    initialObjectCount = collection->sphereObjectCount;
    for (i = 0; i < collection->nodeCount; i++) {
        if (collection->sphereObjectCount == 30) {
            break;
        }
        node = collection->nodes[i];
        if (node->dobjHandle == excludedDobj) {
            continue;
        }
        if (transformedBounds) {
            center = &node->center131C;
            radius = node->radius14B4;
        } else {
            center = &node->sphere12DC.center;
            radius = node->sphere12DC.radius;
        }
        if (D_uvdyn_rom_00411F8C->testSpheres(center->x, center->y, center->z, radius, sphere->center.x, sphere->center.y, sphere->center.z, sphere->radius)) {
            collection->sphereObjectIds[collection->sphereObjectCount] = node->dobjHandle;
            collection->sphereOwners[collection->sphereObjectCount] = node;
            collection->sphereKinds[collection->sphereObjectCount] = 3;
            collection->sphereObjectCount++;
            if (node->associationCount != -1 && node->associationCount < 2) {
                for (j = 0; j < node->associationCount; j++) {
                    if (association != NULL && association == node->associations[j]) {
                        break;
                    }
                }
                if (j >= node->associationCount) {
                    node->associations[node->associationCount] = association;
                    node->associationCount++;
                }
            }
        }
    }
    for (i = 0; i < collection->secondaryCount; i++) {
        if (collection->sphereObjectCount == 30) {
            break;
        }
        secondary = collection->secondary[i];
        if (transformedBounds) {
            center = &secondary->center48;
            radius = secondary->radius138;
        } else {
            center = &secondary->sphere13C.center;
            radius = secondary->sphere13C.radius;
        }
        if (D_uvdyn_rom_00411F8C->testSpheres(center->x, center->y, center->z, radius, sphere->center.x, sphere->center.y, sphere->center.z, sphere->radius)) {
            collection->sphereObjectIds[collection->sphereObjectCount] = secondary->dobjHandle;
            collection->sphereOwners[collection->sphereObjectCount] = secondary;
            collection->sphereKinds[collection->sphereObjectCount] = 2;
            collection->sphereObjectCount++;
        }
    }
    addedCandidates = collection->sphereObjectCount - initialObjectCount;
    D_uvdyn_rom_00411F94->setQueryModes(0, 1, 1, 0);
    copiedResults = 0;
    objectIndex = initialObjectCount - 1;
    for (j = 0; j < addedCandidates; j++) {
        objectIndex++;
        if (collection->sphereKinds[objectIndex] == 3) {
            ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->selectQueryObject(collection->sphereObjectIds[objectIndex], ((DynSphereQueryNode *)collection->sphereOwners[objectIndex])->querySelector);
        } else {
            ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->selectQueryObject(collection->sphereObjectIds[objectIndex], -1);
        }
        D_uvdyn_rom_00411F94->setQueryRecordBuffer(&collection->sphereRecords[collection->sphereResultCount], 120 - collection->sphereResultCount);
        destination = &collection->sphereResultPointers[collection->sphereResultCount];
        returned = ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->querySphere(sphere->center.x, sphere->center.y, sphere->center.z, sphere->radius, &resultPointers, &scratchFirst, &scratchSecond);
        if (returned != 0) {
            if (collection->sphereResultCount + returned < 120) {
                _uvMediaCopy(destination, resultPointers, returned * 4);
                copiedResults += returned;
                collection->sphereResultCount += returned;
            }
            if (D_uvdyn_rom_00411F9C < collection->sphereResultCount) {
                D_uvdyn_rom_00411F9C = collection->sphereResultCount;
            }
        }
        collection->sphereRangeEnds[objectIndex] = collection->sphereResultCount;
    }
    D_uvdyn_rom_00411F94->setQueryRecordBuffer(NULL, 0);
    D_uvdyn_rom_00411F94->setQueryModes(0, 1, 0, 0);
    ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->selectQueryObject(-1, -1);
    if (excludedDobj != 0xFFFF) {
        ((DynQueryDobjExports *)D_uvdyn_rom_00411F84)->setObjectFlags(excludedDobj, excludedFlags);
    }
    return addedCandidates;
}
#line 575 "src/modules/uvdyn_rom.c"

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

/* Forward the unsigned halfword value and the indexed record plus its two word
 * addresses to intersection slot0x40. RE_UNKNOWN: The unsigned halfword index
 * is unchecked; bank storage capacity and provider retention of the supplied
 * addresses are unproved. */
#line 578 "src/modules/uvdyn_rom.c"
/* Select the indexed opaque 120-byte intersection record and corresponding
 * word outputs through the lowercase isct module's query-bank setter. Pass the
 * opaque 16-bit value unchanged; the original does not check index or pointers. */
void uvDynSetIndexedQueryRecordBank(DynIntersectionQueryBanks *queryBanks, u16 recordIndex, u16 bankValue) {
    D_uvdyn_rom_00411F7C->setQueryRecordBank(bankValue, &queryBanks->records[recordIndex], &queryBanks->firstWords[recordIndex], &queryBanks->secondWords[recordIndex]);
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

/* RE_UNKNOWN: The observed 0x1A8 allocation is registered before matrix
 * initialization. Allocation failure, registry capacity/overflow, ownership
 * and the physical meanings of the secondary fields remain unchecked. */
#line 589 "src/modules/uvdyn_rom.c"
/* Allocate and zero the original 0x1A8-byte secondary state, register it,
 * initialize matrices 0x18 and 0xD8 to identity and explicitly clear scalar 0x134.
 * Preserve the original unchecked allocation and registry-capacity contract. */
DynSecondaryState *uvDynCreateSecondaryState(void) {
    DynSecondaryState *secondaryState;
    secondaryState = _uvMemAllocAlign8(sizeof(DynSecondaryState));
    uvMemSet(secondaryState, 0, sizeof(DynSecondaryState));
    D_uvdyn_rom_00411DF0[D_uvdyn_rom_00411E68] = secondaryState;
    secondaryState->registryIndex = D_uvdyn_rom_00411E68;
    D_uvdyn_rom_00411E68++;
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&secondaryState->matrix18);
    D_uvdyn_rom_00411F70->uvMat4SetIdentity(&secondaryState->matrixD8);
    secondaryState->value134 = 0.0f;
    return secondaryState;
}
#line 590 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Collection removal precedes the registry-count snapshot. This
 * function does not free the state, and unregistering does not prove ownership
 * transfer. Preserve u16 scans and the live count during pointer compaction. */
#line 591 "src/modules/uvdyn_rom.c"
/* Clear collection membership, find this state in the global registry, and
 * compact later pointers while repairing their registry indices. Preserve
 * separate original 16-bit scan and shift indices. This routine does not free
 * the state; an absent registry entry leaves the registry unchanged. */
void uvDynUnregisterSecondaryState(DynSecondaryState *secondaryState) {
    u16 registryScanIndex;
    u16 registryShiftIndex;
    s32 registryCountSnapshot;
    uvDynSetSecondaryCollection(secondaryState, NULL);
    registryCountSnapshot = D_uvdyn_rom_00411E68;
    for (registryScanIndex = 0; registryScanIndex < registryCountSnapshot; registryScanIndex++) {
        if (secondaryState == D_uvdyn_rom_00411DF0[registryScanIndex]) {
            break;
        }
    }
    if (registryScanIndex != registryCountSnapshot) {
        D_uvdyn_rom_00411E68--;
        for (registryShiftIndex = registryScanIndex; registryShiftIndex < D_uvdyn_rom_00411E68; registryShiftIndex++) {
            D_uvdyn_rom_00411DF0[registryShiftIndex] = D_uvdyn_rom_00411DF0[registryShiftIndex + 1];
            D_uvdyn_rom_00411DF0[registryShiftIndex]->registryIndex = registryShiftIndex;
        }
    }
}
#line 592 "src/modules/uvdyn_rom.c"

/* Walk the registered secondary pointers with a halfword index and reload the
 * global halfword count after every companion-copy call. RE_UNKNOWN: Registry
 * capacity, pointer validity and count mutation across callbacks remain
 * unchecked. */
#line 593 "src/modules/uvdyn_rom.c"
/* Copy companion fields for every registered secondary state. Preserve the
 * original 16-bit index and reload the registry count after each copy. */
void uvDynCopyRegisteredSecondaryCompanions(void) {
    u16 registryIndex;
    for (registryIndex = 0; registryIndex < D_uvdyn_rom_00411E68; registryIndex++) {
        uvDynCopySecondaryCompanionFields(D_uvdyn_rom_00411DF0[registryIndex]);
    }
}
#line 594 "src/modules/uvdyn_rom.c"

/* Copy vector118 to124, matrix18 to58, then vectors14C/164/17C to158/170/188
 * in order; set flag1A0 after all five calls. RE_UNKNOWN: The paired fields do
 * not establish previous/current-frame meaning, units or lifecycle; provider
 * callbacks and object alias domains remain unproved. */
#line 595 "src/modules/uvdyn_rom.c"
/* Copy the four original vector pairs and matrix into companion fields in
 * the observed order, then set the 16-bit flag at 0x1A0 to one. This copy is
 * unconditional; the flag's remaining consumers are not yet fully recovered. */
void uvDynCopySecondaryCompanionFields(DynSecondaryState *secondaryState) {
    D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector124, &secondaryState->vector118);
    D_uvdyn_rom_00411F70->uvMat4FCopy(&secondaryState->matrix58, &secondaryState->matrix18);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector158, &secondaryState->vector14C);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector170, &secondaryState->vector164);
    D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector188, &secondaryState->vector17C);
    secondaryState->flag1A0 = 1;
}
#line 596 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Selector/value domains and physical units are unproved. Keep
 * selector 0's signed-word conversion and selector 9's unsigned-word then
 * halfword truncation; NaN/out-of-range conversion behavior is not repaired. */
#line 597 "src/modules/uvdyn_rom.c"
/* Scalar property zero converts to the opaque signed value at 0x0C;
 * property nine converts through the original unsigned-word/signed-halfword
 * sequence into the 16-bit kind. Null and unsupported properties do nothing. */
void uvDynSetSecondaryScalarProperty(DynSecondaryState *state, s32 selector, f32 inputValue) {
    if (state != NULL) {
        switch (selector) {
            case 0:
                state->value0C = (s32)inputValue;
                return;
            case 9:
                state->kind = (s16)(u32)inputValue;
                break;
        }
    }
}
#line 609 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: The -1.0 return does not establish an error protocol or valid
 * scalar domain. Preserve signed word0C versus unsigned halfword4 conversion;
 * selector meanings and physical units remain unresolved. */
#line 610 "src/modules/uvdyn_rom.c"
/* Property zero converts the signed value at 0x0C to float; property nine
 * converts the unsigned 16-bit kind. Null or unsupported properties return -1.
 * More specific meanings of the value and kind remain unresolved. */
f32 uvDynGetSecondaryScalarProperty(DynSecondaryState *state, s32 selector) {
    if (state == NULL) {
        return -1.0f;
    }
    switch (selector) {
        case 0:
            return state->value0C;
        case 9:
            return (u32)state->kind;
        default:
            return -1.0f;
    }
}
#line 611 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Vector frames/units, overlap and the length/threshold domains
 * are unproved. Keep the by-value vector ABI and strict double comparisons:
 * unordered values use the matrix helper. Selectors 7/8 require kind zero. */
#line 612 "src/modules/uvdyn_rom.c"
/* Set secondary vector properties 2, 3, 7 and 8 from a vector passed by value.
 * Property 2 stores vector194, caches its length at 0x134 and runs the original
 * matrix export. Property 3 updates translation and the related vector cache;
 * the strict double-threshold predicate preserves its original NaN path.
 * Properties 7 and 8 only change kind-zero states; other cases do nothing. */
void uvDynSetSecondaryVectorProperty(DynSecondaryState *state, s32 selector, Vec3F inputVector) {
    if (state == NULL) {
        return;
    }
    switch (selector) {
        case 2:
            D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector194, &inputVector);
            state->value134 = D_uvdyn_rom_00411F74->uvVec3FLen(&state->vector194);
            D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            break;
        case 3:
            state->matrix18.xw = inputVector.x;
            state->matrix18.yw = inputVector.y;
            state->matrix18.zw = inputVector.z;
            if (!(state->value134 < D_uvdyn_rom_00411D38 && D_uvdyn_rom_00411D40 < state->value134)) {
                D_uvdyn_rom_00411F70->uvMat4TransformPoint(&state->matrix18, &state->vector118, &state->vector194);
            } else {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector118, &inputVector);

            }
            break;
        case 7:
            if (state->kind == 0) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector14C, &inputVector);
            }
            break;
        case 8:
            if (state->kind == 0) {
                D_uvdyn_rom_00411F74->uvVec3FCopy(&state->vector17C, &inputVector);
            }
            break;
    }
}
#line 613 "src/modules/uvdyn_rom.c"

#line 1 "dyn-secondary-address-body-109804.c"
/* Return the selected address within the existing secondary-state view.
 * Only the input address, selector and unsigned kind halfword are consumed;
 * selector 3 returns the byte address +0x48 without asserting its object type.
 * RE_ORIGINAL_QUIRK: result is deliberately uninitialized. Selectors 4/5,
 * selectors outside 2..8, and selectors 7/8 with nonzero kind reach the
 * original load of an unwritten SP+4 word. Null input and selector 2 instead
 * return null explicitly. Do not initialize or sanitize those other paths.
 * RE_UNKNOWN: valid caller selectors/kinds, that stack word's provenance,
 * allocation/ownership/lifetime and the historical complete export prototype.
 * This C draft does not establish defined behavior for the unwritten-result
 * paths. Every native word and relocation still requires exact qualification. */
void *uvDynGetSecondaryPropertyAddress(DynSecondaryState *state, s32 selector) {
    void *result;

    if (state == NULL) {
        return NULL;
    }
    switch (selector) {
    case 2:
        return NULL;
    case 3:
        result = (u8 *)state + 0x48;
        break;
    case 6:
        result = &state->vector164;
        break;
    case 7:
        if (state->kind == 0) {
            result = &state->vector14C;
        }
        break;
    case 8:
        if (state->kind == 0) {
            result = &state->vector17C;
        }
        break;
    default:
        break;
    }
    return result;
}

#line 615 "src/modules/uvdyn_rom.c"

/* RE_ORIGINAL_QUIRK: Unlike the setter, selectors 7/8 have no kind-zero gate.
 * RE_UNKNOWN: Null/unsupported selectors leave output untouched; output
 * validity, allowed overlap and vector frames/units remain caller contracts. */
#line 616 "src/modules/uvdyn_rom.c"
/* Copy secondary vector properties 2, 7 and 8 through the vector export;
 * property 3 reads matrix18's translation components directly. A null state or
 * unsupported property leaves the output unchanged. */
void uvDynGetSecondaryVectorProperty(DynSecondaryState *state, s32 selector, Vec3F *outputVector) {
    if (state == NULL) {
        return;
    }
    switch (selector) {
        case 2:
            D_uvdyn_rom_00411F74->uvVec3FCopy(outputVector, &state->vector194);
            break;
        case 3:
            outputVector->x = state->matrix18.xw;
            outputVector->y = state->matrix18.yw;
            outputVector->z = state->matrix18.zw;
            break;
        case 7:
            D_uvdyn_rom_00411F74->uvVec3FCopy(outputVector, &state->vector14C);
            break;
        case 8:
            D_uvdyn_rom_00411F74->uvVec3FCopy(outputVector, &state->vector17C);
            break;
    }
}
#line 617 "src/modules/uvdyn_rom.c"

/* RE_UNKNOWN: Selector 4 consumes only the temporary's linear components;
 * no whole-matrix initialization or general inverse is established. Preserve
 * partial copies, distinct double thresholds, NaN paths and callback order.
 * Matrix domains, coordinate frames and caller overlap remain unresolved. */
#line 618 "src/modules/uvdyn_rom.c"
/* Matrix properties 3 and 4 synchronize the secondary transform pair,
 * refresh vector118 and set the copy flag. Property 4 uses a temporary matrix
 * for the exported conversion. Preserve strict double near-zero comparisons:
 * NaN takes the exported vector-update path. Null/unsupported properties do nothing. */
void uvDynSetSecondaryMatrixProperty(DynSecondaryState *state, s32 selector, Mtx4F *inputMatrix) {
    Mtx4F linearTranspose;
    if (state == NULL) {
        return;
    }
    switch (selector) {
        case 3:
            D_uvdyn_rom_00411F70->uvMat4FCopy(&state->matrix18, inputMatrix);
            if (!(state->value134 < 1e-5 && -1e-5 < state->value134)) {
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
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrixD8, inputMatrix);
            D_uvdyn_rom_00411F70->uvMat4TransposeLinear3x3PreservingRest(&linearTranspose, &state->matrixD8);
            D_uvdyn_rom_00411F70->uvMat4CopyLinear3x3(&state->matrix18, &linearTranspose);
            if (!(state->value134 < 1e-5 && -1e-5 < state->value134)) {
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
/* A zero base returns0. Selectors3,4 and5 return base plus0x18,0xD8 and0x98
 * respectively through the existing signed-word interface. RE_UNKNOWN:
 * Unsupported nonzero-base selectors read an unassigned stack word in the
 * original; callers, historical pointer type and return contract are unproved.
 * Preserve the original default path. */
#line 619 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_00411644(s32 baseAddressWord, s32 memberSelector) {
    s32 selectedAddressWord;

    if (baseAddressWord == 0) {
        return 0;
    }
    switch (memberSelector) {                                 /* irregular */
    case 3:
        selectedAddressWord = baseAddressWord + 0x18;
        break;
    case 4:
        selectedAddressWord = baseAddressWord + 0xD8;
        break;
    case 5:
        selectedAddressWord = baseAddressWord + 0x98;
        break;
    }
    return selectedAddressWord;
}

/* RE_UNKNOWN: Null/unsupported selectors leave output untouched. The three
 * source matrices' coordinate frames and lifecycle roles are unproved; valid
 * output storage and overlap remain caller contracts for the copy helper. */
#line 640 "src/modules/uvdyn_rom.c"
/* Copy the selected secondary-state matrix: property three selects 0x18,
 * four selects 0xD8 and five selects 0x98. Null states or unsupported properties
 * leave output unchanged; the original requires a valid output when copying. */
void uvDynGetSecondaryMatrixProperty(DynSecondaryState *state, s32 selector, Mtx4F *outputMatrix) {
    if (state != NULL) {
        switch (selector) {
            case 3:
                D_uvdyn_rom_00411F70->uvMat4FCopy(outputMatrix, &state->matrix18);
                break;
            case 4:
                D_uvdyn_rom_00411F70->uvMat4FCopy(outputMatrix, &state->matrixD8);
                break;
            case 5:
                D_uvdyn_rom_00411F70->uvMat4FCopy(outputMatrix, &state->matrix98);
                break;
        }
    }
}
#line 641 "src/modules/uvdyn_rom.c"

/* Reject a nonnull destination with count exactly20 before checking whether it
 * already matches. Otherwise remove the old membership, store the new
 * collection and append to a nonnull destination. RE_UNKNOWN: Counts above20
 * and storage/ownership domains remain unchecked. Removal and append effects
 * retain their original order; no allocation or free is performed here. */
#line 642 "src/modules/uvdyn_rom.c"
/* Reassign secondary collection membership, removing the old membership
 * before adding the new one. Null clears the link. A destination count equal
 * to twenty is rejected before the unchanged-link test, as in the original. */
void uvDynSetSecondaryCollection(DynSecondaryState *secondaryState, DynSecondaryCollection *collection) {
    if (collection != NULL && collection->count == 20) {
        return;
    }
    if (secondaryState->collection != NULL) {
        if (collection == secondaryState->collection) {
            return;
        }
        uvDynRemoveSecondaryValue(secondaryState->collection, secondaryState);
    }
    secondaryState->collection = collection;
    if (collection != NULL) {
        uvDynAppendUniqueSecondaryValue(collection, secondaryState);
    }
}
#line 643 "src/modules/uvdyn_rom.c"

/* Return the collection pointer from the secondary state without a null-state
 * gate. RE_UNKNOWN: The accessor does not establish collection ownership or
 * lifetime. */
#line 644 "src/modules/uvdyn_rom.c"
/* Return this secondary state's linked collection. The original requires
 * a valid state and may return null when no collection is linked. */
DynSecondaryCollection *uvDynGetSecondaryCollection(DynSecondaryState *secondaryState) {
    return secondaryState->collection;
}
#line 647 "src/modules/uvdyn_rom.c"

/* Store the DOBJ handle and LOD index before model lookup. Use the
 * selected44-byte entry to evaluate two ordered three-component squared sums,
 * storing the first provider result and replacing it only when strictly below
 * the second. RE_UNKNOWN: Model availability and LOD bounds are unchecked;
 * corner interpretation and units are unproved. Preserve both calls,
 * arithmetic grouping, fresh provider reads and NaN-sensitive strict
 * comparison. */
#line 648 "src/modules/uvdyn_rom.c"
/* Store the DOBJ handle and model level-of-detail index, look up the loaded
 * UVMD model, and cache the larger length of its two LOD vector triplets as the
 * secondary sphere radius. Preserve reloads after the first square-root export,
 * the ordered comparison and the original valid-model/index preconditions. */
void uvDynSetSecondaryModelLod(DynSecondaryState *secondaryState, s32 dobjHandle, s32 lodIndex) {
    ParsedUVMD *loadedModel;
    u16 loadedModelId;
    uvModelLOD_inner *lodBounds;
    f32 secondCornerLength;
    secondaryState->dobjHandle = dobjHandle;
    secondaryState->lodIndex = lodIndex;
    loadedModelId = D_uvdyn_rom_00411F84->uvDobjGetModel(dobjHandle);
    loadedModel = uvGetLoadedFile(0x55564D44, loadedModelId);
    lodBounds = &loadedModel->unk0->unk0[lodIndex].unk8;
    secondaryState->radius138 = D_uvdyn_rom_00411F80->uvSqrtf((lodBounds->unk0 * lodBounds->unk0 + lodBounds->unk4 * lodBounds->unk4) + lodBounds->unk8 * lodBounds->unk8);
    secondCornerLength = D_uvdyn_rom_00411F80->uvSqrtf((lodBounds->unkC * lodBounds->unkC + lodBounds->unk10 * lodBounds->unk10) + lodBounds->unk14 * lodBounds->unk14);
    if (secondaryState->radius138 < secondCornerLength) {
        secondaryState->radius138 = secondCornerLength;
    }
}
#line 649 "src/modules/uvdyn_rom.c"

/* Return the DOBJ handle word from the secondary state without a null-state
 * gate. RE_UNKNOWN: The accessor does not validate handle registration or
 * lifetime. */
#line 650 "src/modules/uvdyn_rom.c"
/* Return the stored secondary-state DOBJ handle from a valid state. */
s32 uvDynGetSecondaryDobjHandle(DynSecondaryState *secondaryState) {
    return secondaryState->dobjHandle;
}
#line 653 "src/modules/uvdyn_rom.c"

/* Skip an already-set updateFlag. Otherwise call the direct helper only when
 * copyFlag is nonzero and kind is1, then set updateFlag to1 even when no
 * helper ran. RE_UNKNOWN: The supplied scalar units, helper side effects and
 * reset timing are unproved; the existing flags do not establish a frame
 * boundary. */
#line 654 "src/modules/uvdyn_rom.c"
/* Skip an already updated state. When the copy flag is set and kind is one,
 * run the original matrix/vector update with the supplied scalar. Mark the
 * state updated even when that call is skipped; reset clears the flag.
 * The kind and update scalar's broader gameplay meanings remain unresolved. */
void uvDynUpdateSecondaryStateOnce(DynSecondaryState *secondaryState, f32 updateScalar) {
    if (secondaryState->updateFlag == 0) {
        if (secondaryState->copyFlag != 0) {
            if (secondaryState->kind == 1) {
                func_uvdyn_rom_00400A14(&secondaryState->matrix18, &secondaryState->matrix58,
                    &secondaryState->vector14C, &secondaryState->vector164, &secondaryState->vector17C,
                    &secondaryState->vector170, &secondaryState->vector188, updateScalar);
            }
        }
        secondaryState->updateFlag = 1;
    }
}
#line 655 "src/modules/uvdyn_rom.c"

/* When copyFlag is nonzero, copy vectors17C to188,14C to158,164 to170,
 * matrix18 to58 and vector118 to124 in that order. After the calls, always
 * clear copyFlag and updateFlag; flag1A0 is untouched. RE_UNKNOWN: Pair
 * naming, units and lifecycle are unproved. Provider callbacks may mutate
 * state; preserve the ordered five calls and final two halfword stores. */
#line 656 "src/modules/uvdyn_rom.c"
/* When the copy flag is set, copy the original four vector pairs and matrix
 * into their companion fields in the observed order. Clear both 16-bit flags
 * afterward. More specific gameplay meanings are not yet established. */
void uvDynResetSecondaryState(DynSecondaryState *secondaryState) {
    if (secondaryState->copyFlag != 0) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector188, &secondaryState->vector17C);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector158, &secondaryState->vector14C);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector170, &secondaryState->vector164);
        D_uvdyn_rom_00411F70->uvMat4FCopy(&secondaryState->matrix58, &secondaryState->matrix18);
        D_uvdyn_rom_00411F74->uvVec3FCopy(&secondaryState->vector124, &secondaryState->vector118);
    }
    secondaryState->copyFlag = 0;
    secondaryState->updateFlag = 0;
}
#line 657 "src/modules/uvdyn_rom.c"

