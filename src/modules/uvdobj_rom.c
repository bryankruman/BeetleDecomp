// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"
#include "stdarg.h"

typedef void (*DObjCallback)(s32 arg0);

typedef struct DObj_s {
    /* 0x00 */ u16 modelId;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5; /* inferred */
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ char pad18[2];
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ Mtx4F *unk1C;
    /* 0x20 */ DObjCallback unk20;
    /* 0x24 */ DObjCallback unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
} DObj; /* size = 0x30 */

typedef struct DobjSettings {
    s32 dobjsCount;
    s32 unk4;
    s32 unk8;
} DobjSettings;

typedef struct UnkTerra_Exports_s {
    /* 0x00 */ char pad0[0xAC];
    /* 0xAC */ void (*func_uvterra_rom_0040D128)(s32, s32, f32, f32, s32 *, void *, f32); /* inferred */
} UnkTerra_Exports; /* size = 0xB0 */

void uvDobjSetSharedQueryIndexPair(s32 arg0, s32 arg1);
s32 func_uvdobj_rom_00400558(s32 arg0, s32 arg1, s32 arg2);
void uvDobjRegisterChannelCallback(s32 arg0);
void uvDobjModuleCleanup(void);
void uvDobjSetLoadedModel(s32 arg0, s32 arg1);
void uvDobjModel(s32 arg0, s32 arg1);
u16 uvDobjGetModel(s32 arg0);
void uvDobjProps(s32 arg0, ...);
void uvDobjGetProp(s32 arg0, ...);
void uvDobjPosm(s32 arg0, s32 arg1, Mtx4F *arg2);
void uvDobjGetPosm(s32 arg0, s32 arg1, Mtx4F *arg2);
void uvDobjSetFlags(s32 arg0, s32 arg1);
void uvDobjSetFlagBits(s32 arg0, s32 arg1);
u8 uvDobjGetFlags(s32 arg0);
void uvDobjClearFlagBits(s32 arg0, s32 arg1);
s32 uvDobjCreate(void);
void uvDobjClearModelAndStateByte(s32 arg0);
void uvDobjQueueChannelObjectsWhenEnabled(s32 arg0);
void uvDobjQueueVisibleChannelObjects(s32 arg0, s32 arg1);
void uvDobjSetReciprocalScalar(s32 arg0, f32 arg1);
void uvDobjDrawHierarchyUsingNodeMatrixIndices(s32 arg0, DObj *arg1);
void uvDobjDrawHierarchyWithPlanarMatrixOverride(s32 arg0, DObj *arg1);
s32 uvDobjFindObjectContainingWorldPoint(f32 arg0, f32 arg1, f32 arg2);
s32 uvDobjCollectCapsuleOverlaps(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                             s32 *arg7);
s32 uvDobjCollectOverlapsWithScalarExtent(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 **arg4, f32 **arg5,
                             Vec3F **arg6);
s32 uvDobjCollectSegmentHierarchyResults(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 **arg6,
                             f32 **arg7, Vec3F **arg8);
s16 uvDobjQueryHierarchyWithScalarExtent(f32 arg0, f32 arg1, f32 arg2, f32 arg3, DObj *arg4);
s16 uvDobjTestHierarchyPointBounds(f32 arg0, f32 arg1, f32 arg2, DObj *arg3);
s16 uvDobjQueryHierarchySegment(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, DObj *arg6);
s32 uvDobjExtractJointQuaternionsFromMatrices(s32 arg0, Quat *arg1, u8 *arg2);
void uvDobjClearFixedDepthImageRectangle(void);
void uvDobjReplaceLightColorRecord(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
u16 uvDobjGetQueryArray(s32 **arg0);
void __entrypoint_func_uvdobj_rom_400000(UvDobj_Exports *exports);

// .data
s32 D_uvdobj_rom_004039A0[] = { 0x00680000, __entrypoint_func_uvdobj_rom_400000, 0, 0 };

// .bss
s32 D_uvdobj_rom_004039B0;
DObj *sDObjs;
s32 *D_uvdobj_rom_004039B8;
u16 D_uvdobj_rom_004039BC;
s16 D_uvdobj_rom_004039BE;
s32 sDObjsCount;
s32 sUvDobjId;
s32 D_uvdobj_rom_004039C8;
s32 D_uvdobj_rom_004039CC;
f32 *D_uvdobj_rom_004039D0;
s32 *D_uvdobj_rom_004039D4;
Vec3F *D_uvdobj_rom_004039D8;
s32 *D_uvdobj_rom_004039DC;
s32 *D_uvdobj_rom_004039E0;
s32 *D_uvdobj_rom_004039E4;
f32 *D_uvdobj_rom_004039E8;
s32 D_uvdobj_rom_004039EC;
s32 D_uvdobj_rom_004039F0;
s32 D_uvdobj_rom_004039F4;
s32 *D_uvdobj_rom_004039F8;
static UvFMtx_Rom_Exports *sUvFMtxExports;
static UvQuat_Exports *sUvQuatExports;
static UvFVec_Rom_Exports *sUvFVecExports;
static UvImtx_Rom_Exports *sUvIMtxExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;
static UvGfxMgr_Exports *sUvGfxMgrExports;
static UvModel_Exports *sUvModelExports;
static UvMath_Exports *sUvMathExports;
static UvChannel_Exports *sUvChannel_Exports;
static UvCback_Exports *sUvCbackExports;
static UvQuery_Exports *sUvQueryExports;
static UvIntersect_Exports *sUvIntersectExports;
static UnkTerra_Exports *sUvTerraExports;
static UvLights_Exports *sUvLightExports;

void __entrypoint_func_uvdobj_rom_400000(UvDobj_Exports *exports) { /* Publish the object-module exports, load provider tables, initialize per-channel scalars and object storage, then bind the shared query arrays. */
    DobjSettings *objectSettings;
    s32 entryIndex;

    uvUpdateFileAllocPtr(exports);
    exports->uvDobjSetSharedQueryIndexPair = uvDobjSetSharedQueryIndexPair;
    exports->func_uvdobj_rom_00400558 = func_uvdobj_rom_00400558;
    exports->uvDobjRegisterChannelCallback = uvDobjRegisterChannelCallback;
    exports->uvDobjSetLoadedModel = uvDobjSetLoadedModel;
    exports->uvDobjModel = uvDobjModel;
    exports->uvDobjGetModel = uvDobjGetModel;
    exports->uvDobjProps = uvDobjProps;
    exports->uvDobjGetProp = uvDobjGetProp;
    exports->uvDobjPosm = uvDobjPosm;
    exports->uvDobjModuleCleanup = uvDobjModuleCleanup;
    exports->uvDobjGetPosm = uvDobjGetPosm;
    exports->uvDobjCollectOverlapsWithScalarExtent = uvDobjCollectOverlapsWithScalarExtent;
    exports->uvDobjSetFlags = uvDobjSetFlags;
    exports->uvDobjCollectSegmentHierarchyResults = uvDobjCollectSegmentHierarchyResults;
    exports->uvDobjSetFlagBits = uvDobjSetFlagBits;
    exports->uvDobjExtractJointQuaternionsFromMatrices = uvDobjExtractJointQuaternionsFromMatrices;
    exports->uvDobjGetFlags = uvDobjGetFlags;
    exports->uvDobjReplaceLightColorRecord = uvDobjReplaceLightColorRecord;
    exports->uvDobjClearFlagBits = uvDobjClearFlagBits;
    exports->uvDobjGetQueryArray = uvDobjGetQueryArray;
    exports->uvDobjCreate = uvDobjCreate;
    exports->uvDobjClearModelAndStateByte = uvDobjClearModelAndStateByte;
    exports->uvDobjSetReciprocalScalar = uvDobjSetReciprocalScalar;
    exports->uvDobjFindObjectContainingWorldPoint = uvDobjFindObjectContainingWorldPoint;
    exports->uvDobjCollectCapsuleOverlaps = uvDobjCollectCapsuleOverlaps;
    exports->D_uvdobj_rom_004039B0 = &D_uvdobj_rom_004039B0;
    objectSettings = uvGetSystemProp(SYSTEM_PROPID_DOBJ_SETTINGS);
    if (objectSettings == NULL) {
        sDObjsCount = 0x64;
        D_uvdobj_rom_004039C8 = 0x64;
        D_uvdobj_rom_004039CC = 0x12C;
    } else {
        if (objectSettings->dobjsCount != 0) {
            sDObjsCount = objectSettings->dobjsCount;
        } else {
            sDObjsCount = 0x64;
        }
        if (objectSettings->unk4 != 0) {
            D_uvdobj_rom_004039C8 = objectSettings->unk4;
        } else {
            D_uvdobj_rom_004039C8 = 0x64;
        }
        if (objectSettings->unk8 != 0) {
            D_uvdobj_rom_004039CC = objectSettings->unk8;
        } else {
            D_uvdobj_rom_004039CC = 0x12C;
        }
    }
    sUvIMtxExports = uvLoadModule('IMTX');
    sUvFMtxExports = uvLoadModule('FMTX');
    sUvQuatExports = uvLoadModule('QUAT');
    sUvFVecExports = uvLoadModule('FVEC');
    sUvGfxStateExports = uvLoadModule('STAT');
    sUvGfxMgrExports = uvLoadModule('GMGR');
    sUvMathExports = uvLoadModule('MATH');
    sUvModelExports = uvLoadModule('MODL');
    sUvChannel_Exports = uvLoadModule('CHAN');
    sUvCbackExports = uvLoadModule('CBCK');
    sUvQueryExports = uvLoadModule('QERY');
    sUvIntersectExports = uvLoadModule('ISCT');
    sUvTerraExports = uvLoadModule('TERR');
    sUvLightExports = uvLoadModule('LGHT');
    sUvChannel_Exports->uvChannelGetProperties(0, 0xD, &D_uvdobj_rom_004039F4, 0);
    D_uvdobj_rom_004039E8 = _uvMemAllocAlign8(D_uvdobj_rom_004039F4 * 4);
    for (entryIndex = 0; entryIndex < D_uvdobj_rom_004039F4; entryIndex++) {
        D_uvdobj_rom_004039E8[entryIndex] = 1.0f;
    }

    sDObjs = _uvMemAllocAlign8(sDObjsCount * sizeof(DObj));
    D_uvdobj_rom_004039B8 = _uvMemAllocAlign8(sDObjsCount * sizeof(s32));
    uvMemSet(sDObjs, 0, sDObjsCount * sizeof(DObj));
    uvMemSet(D_uvdobj_rom_004039B8, 0, sDObjsCount * sizeof(s32));
    for (entryIndex = 0; entryIndex < sDObjsCount; entryIndex++) {
        sDObjs[entryIndex].modelId = 0xFFFF;
    }

    D_uvdobj_rom_004039BE = 0;
    D_uvdobj_rom_004039D0 = sUvQueryExports->uvQueryGetFloatValues();
    D_uvdobj_rom_004039D4 = sUvQueryExports->uvQueryGetIntValues();
    D_uvdobj_rom_004039D8 = sUvQueryExports->uvQueryGetFloatVectors();
    D_uvdobj_rom_004039E4 = sUvQueryExports->uvQueryGetHitCountAddress();
    D_uvdobj_rom_004039E0 = sUvQueryExports->uvQueryGetSharedWord40Address();
    D_uvdobj_rom_004039DC = sUvQueryExports->uvQueryGetAuxiliaryArrayAddress();
    D_uvdobj_rom_004039F8 = sUvQueryExports->uvQueryGetSecondaryCountAddress();
    D_uvdobj_rom_004039EC = -1;
    D_uvdobj_rom_004039F0 = -1;
/* RE_UNKNOWN: Nonzero settings replace defaults 100, 100 and 300 without a positive-range check. Allocation success, repeated initialization and storage ownership remain unproved. */ }

#line 210 "src/modules/uvdobj_rom.c"
/* Store the original shared query index pair without adding range checks. */
void uvDobjSetSharedQueryIndexPair(s32 first, s32 second) {
    D_uvdobj_rom_004039EC = first;
    D_uvdobj_rom_004039F0 = second;
}
#line 214 "src/modules/uvdobj_rom.c"

s32 func_uvdobj_rom_00400558(s32 arg0, s32 arg1, s32 arg2) {
    return 0;
}

#line 219 "src/modules/uvdobj_rom.c"
/*
 * Read channel property 6 into the local callback list, then register the
 * dynamic-object queue callback with zero insertion argument and priority 0x3C.
 * The output local is uninitialized before lookup and no status is checked.
 * RE_UNKNOWN: A valid channel must supply a live list and callbacks must remain
 * valid through registration and teardown; those guarantees are external.
 */
#line 221 "src/modules/uvdobj_rom.c"
void uvDobjRegisterChannelCallback(s32 channel) {
    CallbackList *callbackList;

    sUvChannel_Exports->uvChannelGetProperties(channel, 6, &callbackList, 0);
    sUvCbackExports->uvAddCallback(callbackList, uvDobjQueueChannelObjectsWhenEnabled, 0, 0x3C);
}
#line 225 "src/modules/uvdobj_rom.c"

#line 226 "src/modules/uvdobj_rom.c"
/* Free per-object matrices, shared object/query arrays and unload the
 * original fourteen module dependencies. Preserve ownership and teardown
 * order; no new reinitialization contract is introduced. */
void uvDobjModuleCleanup(void) {
    Mtx4F *matrices;
    s32 i;

    for (i = 0; i < sDObjsCount; i++) {
        matrices = sDObjs[i].unk1C;
        if (matrices != 0) {
            _uvMemFree(matrices);
        }
    }

    _uvMemFree(sDObjs);
    _uvMemFree(D_uvdobj_rom_004039B8);
    uvUnloadModule('FMTX');
    uvUnloadModule('QUAT');
    uvUnloadModule('FVEC');
    uvUnloadModule('IMTX');
    uvUnloadModule('STAT');
    uvUnloadModule('GMGR');
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('QERY');
    uvUnloadModule('ISCT');
    uvUnloadModule('TERR');
    uvUnloadModule('LGHT');
}
#line 254 "src/modules/uvdobj_rom.c"

#line 255 "src/modules/uvdobj_rom.c"
/* For a nonnegative object index and nonsentinel model ID, update the
 * model only when it differs and is loaded. The upper index is unchecked.
 * RE_UNKNOWN: valid object-index domain; trace original callers and allocation. */
void uvDobjSetLoadedModel(s32 objectId, s32 modelId) {
    DObj *object;

    if ((modelId == 0xFFFF) || (objectId < 0)) {
        return;
    }

    object = &sDObjs[objectId];
    if (modelId != object->modelId) {
        if (uvGetLoadedFile('UVMD', modelId) != NULL) {
            object->modelId = modelId;
        }
    }
}
#line 269 "src/modules/uvdobj_rom.c"

void uvDobjModel(s32 objId, s32 modelId) { /* Replace or clear the selected model and update its matrix storage in native order. */
    f32 reciprocalScale;
    u8 newMatrixCount;
    u8 oldMatrixCount;
    s32 i;
    ParsedUVMD *newModel;
    ParsedUVMD *oldModel;
    Mtx4F *oldMatrices;
    DObj *object; /* RE_UNKNOWN: record extents, aliases and lifetime need original allocators and export 0x14 callers; UVMD field roles need independent consumers. */

    object = &sDObjs[objId]; /* RE_ORIGINAL_QUIRK: native reads modelId before the signed upper-only ID gate. RE_UNKNOWN: valid IDs and pre-gate readability need original caller-domain evidence. */
    if (modelId == object->modelId) {
        return;
    }

    if (objId >= sUvDobjId) {
        return;
    }

    oldModel = NULL;
    if (object->modelId != 0xFFFF) {
        oldModel = uvGetLoadedFile('UVMD', object->modelId);
        if (oldModel == NULL) {
            PANIC; /* Preserve the native null store, then remaining control if execution continues. RE_UNKNOWN: missing-model error-path reachability needs original loaders/callers/runtime evidence. */
        } else {
            // FAKE: RE_UNKNOWN: historical compiler workaround; preserve the triple pointer no-op until original declarations/source justify a natural replacement.
            if (oldModel && oldModel && oldModel)
                ;
        }
    }
    if (modelId == 0xFFFF) {
        object->modelId = 0xFFFF;
        if (object->unk1C != 0) {
            _uvMemFree((void *) object->unk1C);
            object->unk1C = 0;
            object->unk1A = 0;
        }
        return;
    }

    newModel = uvGetLoadedFile('UVMD', modelId);
    if (newModel == NULL) {
        return;
    }

    object->unk14 = 0;
    object->unk10 = newModel->unkC;
    if (object->modelId == 0xFFFF) {
        oldMatrixCount = 0;
    } else if (oldModel != NULL) {
        oldMatrixCount = oldModel->unk6; /* Capture this old resource byte before allocation/callbacks. RE_UNKNOWN: old/new count compatibility needs original model-transition producers. */
    } else {
        oldMatrixCount = 0;
        if (object->unk1C != 0) {
            _uvMemFree((void *) object->unk1C);
            object->unk1C = 0;
            object->unk1A = 0;
        }
    }
    oldMatrices = object->unk1C;
    newMatrixCount = newModel->unk6;
    object->unk1C = _uvMemAllocAlign8(newMatrixCount << 6); /* Publish pointer/count without a success gate; native allocator can return null. RE_UNKNOWN: allocation outcomes, capacities and valid zero-count transitions need original resource/lifecycle callers. */
    object->unk1A = newMatrixCount;

    for (i = 0; i < oldMatrixCount; i++) {
        sUvFMtxExports->uvMat4FCopy((u32) object->unk1C + i * sizeof(Mtx4F),
                                    (u32) oldMatrices + i * sizeof(Mtx4F));
        _uvMemFree(oldMatrices); /* RE_ORIGINAL_QUIRK: free the same captured base after each old-matrix copy; no old/new count clamp. RE_UNKNOWN: ownership, repeat-free validity and reachability need original allocation/lifecycle callers. */
    }

    for (i = oldMatrixCount; i < newMatrixCount; i++) {
        Mtx4F *destinationMatrix = (u32) object->unk1C + (i * sizeof(Mtx4F));
        Mtx4F *modelMatrix = (u32) newModel->unk8 + (i * sizeof(Mtx4F));
        sUvFMtxExports->uvMat4FCopy(destinationMatrix, modelMatrix); /* Native copy interleaves loads/stores. RE_UNKNOWN: readable/writable extents, overlap and resource lifetime need original producers/consumers; retain these fresh pointer reads. */
    }
    if (oldMatrixCount == 0) {
        if (newModel->unk10 != 1.0f) {
            reciprocalScale = 1.0f / newModel->unk10; /* Preserve the unequal-to-1 test, including NaN, and scale only the first three matrix rows. RE_UNKNOWN: factor units and finite/nonzero domains need original resource producers and transform consumers. */
            sUvFMtxExports->uvMat4Scale((Mtx4F *) object->unk1C, reciprocalScale, reciprocalScale, reciprocalScale);
        }
    }
    object->modelId = modelId;
    if (newModel->unk5 & 0x76) { /* Reload this byte after callbacks; native flag setter stores one byte. RE_UNKNOWN: flag meanings and its different inclusive upper-ID gate need original callers/consumers. */
        uvDobjSetFlags(objId, 3);
    } else {
        uvDobjSetFlags(objId, 2);
    }
}

u16 uvDobjGetModel(s32 objId) {
    return sDObjs[objId].modelId;
}

void uvDobjProps(s32 objId, ...) { /* Apply the zero-terminated property stream, retaining each selector-specific argument fetch and write. */
    va_list args;
    DObj *object; /* RE_UNKNOWN: object storage extent, aliases and lifetime need original allocators and export 0x1C callers. */
    f32 scalarMultiplier;
    ParsedUVMD *uvmd;
    s16 propertySelector; /* Consume a word, then narrow to signed 16 bits. RE_UNKNOWN: argument types, selector domains and zero termination need original callers and historical declarations. */

    if (objId >= sDObjsCount) { /* RE_ORIGINAL_QUIRK: native checks only the signed upper bound. RE_UNKNOWN: negative-ID reachability needs original caller-domain evidence. */
        return;
    }
    object = &sDObjs[objId];
    va_start(args, objId);
    if (object->modelId == 0xFFFF) {
        PANIC;
        return;
    }
    while (TRUE) {
        propertySelector = va_arg(args, s32);
        switch (propertySelector) {
            case 10:
                object->unk7 = va_arg(args, s32);
                break;
            case 1:
                scalarMultiplier = va_arg(args, f64);
                uvmd = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: lookup can return null, but the next read has no null gate; valid model IDs and resource lifetime need original loaders/callers. */
                object->unk10 = uvmd->unkC * scalarMultiplier;
                break;
            case 7:
                object->unk10 = va_arg(args, f64);
                break;
            case 2:
                object->unk14 &= ~(1 << va_arg(args, s32)); /* Preserve this and case 3 variable shifts. RE_UNKNOWN: C shift domains and historical types need original argument producers; native SLLV alone does not establish valid C inputs. */
                break;
            case 3:
                object->unk14 |= 1 << va_arg(args, s32);
                break;
            case 6:
                object->unk14 = va_arg(args, s32);
                break;
            case 4:
                object->unk20 = va_arg(args, s32); /* Cases 4/5 store the first word before fetching the second. RE_UNKNOWN: word roles and pointee ownership need original consumers; do not infer them from callback-shaped uses. */
                object->unk28 = va_arg(args, s32);
                break;
            case 5:
                object->unk24 = va_arg(args, s32);
                object->unk2C = va_arg(args, s32);
                break;
            default:
                PANIC; /* Preserve native null store, then the loop backedge if control continues; the missing-model path instead returns. RE_UNKNOWN: error-path reachability needs original callers/runtime behavior. */
                break;
            case 0:
                return;
        }
    }
    va_end(args);
}

void uvDobjGetProp(s32 objectId, ...) { /* Read selected object fields into the output pointers consumed from the zero-terminated property stream. */
    DObj *object; /* RE_UNKNOWN: record/output extents, aliases and lifetime need original allocators and export 0x20 callers. */
    s16 propertySelector;
    va_list args;

    if (objectId >= sUvDobjId) { /* RE_ORIGINAL_QUIRK: signed upper-only gate. RE_UNKNOWN: negative-ID reachability needs original caller-domain evidence. */
        return;
    }
    object = &sDObjs[objectId];
    va_start(args, objectId);

    while (TRUE) {
        propertySelector = va_arg(args, s32); /* Consume a word, then narrow to signed 16 bits. RE_UNKNOWN: historical argument types and zero termination need original argument producers. */
        if (propertySelector == NULL) {
            return;
        }

        switch (propertySelector) { /* Unsupported nonzero selectors consume only their selector word; retain this cursor behavior. RE_UNKNOWN: valid selector streams need original export 0x20 callers. */
            case 7:
                *va_arg(args, f32 *) = object->unk10; /* Each case fetches its output pointer, reloads the field, then stores four bytes. RE_UNKNOWN: output writability/overlap and field roles need original producers/consumers. */
                break;
            case 8:
                *va_arg(args, s32 *) = object->modelId; /* Preserve the zero-extended model halfword written as a full word. */
                break;
            case 6:
                *va_arg(args, s32 *) = object->unk14;
                break;
        }
    }
    va_end(args);
}

/* Copy the supplied matrix into the stored part slot, then apply the original
 * model scalar: reciprocal scaling for part zero, translation multiplication
 * for other parts. Preserve repeated model-scalar and stored-matrix reads.
 * RE_ORIGINAL_QUIRK: the copy precedes the loaded-model and upper part-limit
 * checks. Keep the original inclusive object-index and negative-part guards.
 * RE_UNKNOWN: valid object/part and matrix extents, nonzero scalar domain,
 * source/storage aliases and coordinate units. Trace original callers and UVMD
 * producers before changing guard order, adding defaults or assigning frames. */
#line 452 "src/modules/uvdobj_rom.c"
void uvDobjPosm(s32 objectId, s32 partIndex, Mtx4F *sourceMatrix) {
    DObj *object;
    s32 pad;
    ParsedUVMD *model;

    if (sUvDobjId < objectId) {
        return;
    }

    object = &sDObjs[objectId];
    if (object->modelId == 0xFFFF) {
        return;
    }

    if (partIndex < 0) {
        return;
    }

    sUvFMtxExports->uvMat4FCopy((u32) object->unk1C + partIndex * sizeof(Mtx4F), sourceMatrix);

    model = uvGetLoadedFile('UVMD', object->modelId);
    if (model == NULL) {
        return;
    }

    if (partIndex >= model->unk0->unk8) {
        return;
    }

    if (partIndex == 0) {
        if (model->unk10 != 1.0f) {
            sUvFMtxExports->uvMat4Scale((u32) object->unk1C + partIndex * sizeof(Mtx4F),
                                        1.0f / model->unk10, 1.0f / model->unk10,
                                        1.0f / model->unk10);
        }
    } else {
        object->unk1C[partIndex].m[3][0] *= model->unk10;
        object->unk1C[partIndex].m[3][1] *= model->unk10;
        object->unk1C[partIndex].m[3][2] *= model->unk10;
    }
}
#line 493 "src/modules/uvdobj_rom.c"

/* Copy a stored part matrix to the supplied destination, then apply the
 * original model scalar: scaling for part zero, translation division for
 * other parts. Retain per-component reads and stores rather than caching them.
 * RE_ORIGINAL_QUIRK: the copy precedes the loaded-model check; the original
 * guards do not add an upper part-limit test. Preserve their existing order.
 * RE_UNKNOWN: caller object/part and output extents, nonzero scalar domain,
 * output/storage aliases and coordinate units. Trace original callers and UVMD
 * producers before strengthening bounds or assigning a coordinate frame. */
#line 494 "src/modules/uvdobj_rom.c"
void uvDobjGetPosm(s32 objectId, s32 partIndex, Mtx4F *destinationMatrix) {
    DObj *object;
    ParsedUVMD *model;

    if (sUvDobjId < objectId) {
        return;
    }

    object = &sDObjs[objectId];
    if (object->modelId == 0xFFFF) {
        return;
    }

    if (partIndex < 0) {
        return;
    }

    sUvFMtxExports->uvMat4FCopy(destinationMatrix, (u32) object->unk1C + partIndex * sizeof(Mtx4F));

    model = uvGetLoadedFile('UVMD', object->modelId);
    if (model == NULL) {
        return;
    }

    if (partIndex == 0) {
        if (model->unk10 != 1.0f) {
            sUvFMtxExports->uvMat4Scale(destinationMatrix, model->unk10, model->unk10, model->unk10);
        }
    } else {
        destinationMatrix->m[3][0] /= model->unk10;
        destinationMatrix->m[3][1] /= model->unk10;
        destinationMatrix->m[3][2] /= model->unk10;
    }
}
#line 528 "src/modules/uvdobj_rom.c"

#line 529 "src/modules/uvdobj_rom.c"
/* Set the object flag byte through the original object-index guard.
 * Preserve the original inclusive upper-bound and signed-index contract. */
void uvDobjSetFlags(s32 objectId, s32 flags) {
    DObj *object;
    if (sUvDobjId < objectId) {
        return;
    }

    object = &sDObjs[objectId];
    object->unk4 = flags;
}
#line 538 "src/modules/uvdobj_rom.c"

#line 539 "src/modules/uvdobj_rom.c"
/* Add requested object flag bits through the shared setter. Preserve the
 * original guard and low-byte storage behavior. */
void uvDobjSetFlagBits(s32 objectId, s32 mask) {
    if (sUvDobjId < objectId) {
        return;
    }
    uvDobjSetFlags(objectId, sDObjs[objectId].unk4 | mask);
}
#line 545 "src/modules/uvdobj_rom.c"

#line 546 "src/modules/uvdobj_rom.c"
/* Read the object flag byte, returning zero above the original index limit.
 * Signed and inclusive-bound behavior remains unchanged. */
u8 uvDobjGetFlags(s32 objectId) {
    if (sUvDobjId < objectId) {
        return 0U;
    }
    return sDObjs[objectId].unk4;
}
#line 552 "src/modules/uvdobj_rom.c"

#line 553 "src/modules/uvdobj_rom.c"
/* Clear requested object flag bits through the shared setter. Preserve
 * the original guard and low-byte storage behavior. */
void uvDobjClearFlagBits(s32 objectId, s32 mask) {
    if (sUvDobjId < objectId) {
        return;
    }
    uvDobjSetFlags(objectId, sDObjs[objectId].unk4 & ~mask);
}
#line 559 "src/modules/uvdobj_rom.c"

s32 uvDobjCreate(void) { /* Claim the first record whose byte at offset 5 is zero, perform the partial reset and raise the object-ID limit when necessary. */
    s32 objectIndex; /* RE_UNKNOWN: count validity, record extents and allocation lifetime need original settings, allocators and export 0x3C callers. */

    for (objectIndex = 0; objectIndex < sDObjsCount; objectIndex++) { /* Native scans signed indices below the captured count; nonpositive counts return 0xFFFF. */
        if (sDObjs[objectIndex].unk5 == 0) { /* Select the first zero byte at record +0x05. RE_UNKNOWN: occupancy/reuse rules need original release paths and callers. */
            sDObjs[objectIndex].unk5 = 1; /* Publish this byte before the partial reset below; no modelId reset or full-record clear is performed. RE_UNKNOWN: valid reused-record state needs original lifecycle evidence. */
            sDObjs[objectIndex].unk2 = -1;
            sDObjs[objectIndex].unk7 = 0;
            sDObjs[objectIndex].unk20 = 0;
            sDObjs[objectIndex].unk24 = 0;
            sDObjs[objectIndex].unk1A = 0;
            sDObjs[objectIndex].unk1C = 0; /* Preserve every record-base reload and store order. RE_UNKNOWN: aliasing and displaced-buffer ownership need original producers/consumers; no cleanup is inferred here. */
            if (sUvDobjId < objectIndex + 1) { /* Raise the ID limit only when lower; no full-record initialization or capacity guarantee follows. */
                sUvDobjId = objectIndex + 1;
            }
            return objectIndex;
        }
    }

    return 0xFFFF;
}

#line 582 "src/modules/uvdobj_rom.c"
/* Clear the model through sentinel 0xFFFF, then clear state byte five.
 * No additional object-index validation is introduced. */
void uvDobjClearModelAndStateByte(s32 objectId) {
    uvDobjModel(objectId, 0xFFFF);
    sDObjs[objectId].unk5 = 0;
}
#line 586 "src/modules/uvdobj_rom.c"

#line 587 "src/modules/uvdobj_rom.c"
/* Queue objects for this channel only while the shared suppression flag
 * is clear, preserving the original zero value for the helper mode. */
void uvDobjQueueChannelObjectsWhenEnabled(s32 channel) {
    if (D_uvdobj_rom_004039B0 == 0) {
        uvDobjQueueVisibleChannelObjects(channel, 0);
    }
}
#line 592 "src/modules/uvdobj_rom.c"

#line 593 "src/modules/uvdobj_rom.c"
/* Filter active drawable objects against the channel, select the model
 * distance band and queue the appropriate render callback. Retain the
 * original object flags, squared-distance scaling and band selection. */
void uvDobjQueueVisibleChannelObjects(s32 channel, s32 unusedMode) {
    s32 queueMode;
    ParsedUVMD *model;
    f32 relativeZ;
    f32 relativeX;
    f32 relativeY;
    f32 distanceSquared;
    f32 worldX;
    f32 worldY;
    f32 scaledDistanceSquared;
    s32 i;
    u16 temp_a1;
    s32 distanceBand;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    void *renderCallback;
    Vec3F channelPosition;
    DObj *object;
    float worldZ;

    D_uvdobj_rom_004039BC = 0;
    sUvChannel_Exports->uvChannelGetProperties(channel, 7, &channelPosition, 4, &spCC, &spC8, &spC4, &spC0, &spBC,
                                                   &spB8, 0);
    for (i = 0; i < sUvDobjId; i++) {
        object = &sDObjs[i];
        if (object->modelId == 0xFFFF) {
            continue;
        }
        if (!(object->unk4 & 2)) {
            continue;
        }
        if (object->unk4 & 4) {
            continue;
        }
        model = uvGetLoadedFile('UVMD', object->modelId);
        if (model == NULL) {
            continue;
        }
        worldX = object->unk1C->m[3][0];
        worldY = object->unk1C->m[3][1];
        worldZ = object->unk1C->m[3][2];
        relativeX = worldX - channelPosition.x;
        relativeY = worldY - channelPosition.y;
        relativeZ = worldZ - channelPosition.z;
        if (!(object->unk4 & 0x40)
            && (sUvChannel_Exports->uvChannelTestCachedVectorPairs(channel, relativeX, relativeY, relativeZ,
                                                               object->unk10)
                == 0)) {
            continue;
        }

        distanceSquared = (SQ(relativeX) + SQ(relativeY) + SQ(relativeZ));
        if (D_uvdobj_rom_004039E8[channel] == 1.0f) {
            scaledDistanceSquared = distanceSquared;
        } else {
            scaledDistanceSquared = (distanceSquared * D_uvdobj_rom_004039E8[channel]) * D_uvdobj_rom_004039E8[channel];
        }
        distanceBand = sUvModelExports->uvModelFindThresholdBand(model, scaledDistanceSquared);
        if (distanceBand == 0xFF) {
            continue;
        }
        if ((model->unk5 & 1) || (((distanceBand < model->unk7)))) {
            queueMode = 1;
        } else {
            queueMode = 0;
        }

        if (model->unk0[distanceBand].unk9) {
            renderCallback = uvDobjDrawHierarchyWithPlanarMatrixOverride;
        } else {
            renderCallback = uvDobjDrawHierarchyUsingNodeMatrixIndices;
        }
        object->unk6 = distanceBand;
        object->unk8 = relativeX;
        object->unkC = relativeY;
        sUvTerraExports->func_uvterra_rom_0040D128(channel, queueMode, worldX, worldY, renderCallback, object,
                                                   distanceSquared);
    }
}
#line 676 "src/modules/uvdobj_rom.c"

#line 677 "src/modules/uvdobj_rom.c"
/* Store 1.0f / scalar in the object-indexed array without input checks.
 * RE_UNKNOWN: index bounds and divisor domain; trace original callers/storage. */
void uvDobjSetReciprocalScalar(s32 objectId, f32 scalar) {
    D_uvdobj_rom_004039E8[objectId] = 1.0f / scalar;
}
#line 680 "src/modules/uvdobj_rom.c"

void uvDobjClearFixedDepthImageRectangle(); /* */

/* Draw selected model nodes using their matrix indices; preserve light selection, conditional state changes and callback order. */
#line 683 "src/modules/uvdobj_rom.c"
void uvDobjDrawHierarchyUsingNodeMatrixIndices(s32 unusedQueueWord, DObj *object) {
    ParsedUVMD_1 *hierarchy;
    void (*unusedCallbackA)(s32, void *); /* RE_UNKNOWN: historical unused callback declarations/ABI. */
    void (*unusedCallbackB)(s32, void *); /* Retain the original unused declaration. */
    ParsedUVMD *parsedModel;
    s32 depthDifference;
    s32 drawNode;
    s32 stepIndex;
    s32 outstandingPushes;
    s32 stateCount;
    u32 invertedNodeMask;
    s32 selectedLod;
    uvModelLOD *node;
    s32 nodeIndex;
    s32 forceInverseTranslation;
    s32 matrixLoadFlags;
    s32 lookAtMode;
    Mtx4F viewMatrix;
    Mtx4F hiliteMatrix;
    Mtx4F lookAtMatrix;

    lookAtMode = 0;
    if (object->unk20 != NULL) {
        object->unk20(object->unk28); /* RE_UNKNOWN: callback mutation, aliases and storage lifetime need original caller/provider proof. */
    }
    if (!(object->unk4 & 2)) {
        return; /* RE_ORIGINAL_QUIRK: visibility return after pre-callback skips post-callback. */
    }

    selectedLod = object->unk6;
    parsedModel = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/LOD/node/matrix validity and extents need lifecycle/producer proof. */
    sUvLightExports->uvLightSelectRecord(object->unk2); /* RE_UNKNOWN: signed light-ID domain/storage; native selector -1 still reads a record. */
    D_uvdobj_rom_004039B8[D_uvdobj_rom_004039BC++] = (object - sDObjs); /* RE_UNKNOWN: array extent/object membership; retain u16 cursor wrap. */
    if (object->unk4 & 8) {
        uvDobjClearFixedDepthImageRectangle();
    }
    hierarchy = &parsedModel->unk0[selectedLod];
    outstandingPushes = 0;
    forceInverseTranslation = object->unk4 & 0x80;
    if (forceInverseTranslation) {
        matrixLoadFlags = 3;
    } else {
        matrixLoadFlags = 1;
    }
    invertedNodeMask = ~object->unk14; /* Snapshot this mask; later per-node tests still reload object flags. */
    for (nodeIndex = 0; nodeIndex < hierarchy->unk8; nodeIndex++) {
        node = &hierarchy->unk0[nodeIndex];
        if (invertedNodeMask < (1 << nodeIndex)) { /* RE_UNKNOWN: mask/flag meanings and shift-index range need original producers/callers. */
            break;
        }
        if ((object->unk14 & (1 << nodeIndex)) || (((node->unk7 & 1)))) {
            drawNode = FALSE;
        } else {
            drawNode = TRUE;
        }

        if (!drawNode) {
            if (node->unk7 & 2) {
                outstandingPushes++;
                depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6; /* RE_UNKNOWN: next-node readability, depth rules and stack balance need asset/caller proof. */
                for (stepIndex = 0; stepIndex < depthDifference; stepIndex++) {
                    sUvFMtxExports->uvGfxMtxFViewPop();
                    outstandingPushes--;
                }
                continue;
            }
        }
        if ((nodeIndex == 0) || (forceInverseTranslation)) {
            sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&viewMatrix, (u32) object->unk1C + node->unk5 * sizeof(Mtx4F));
            sUvFMtxExports->uvGfxMtxViewLoad(&viewMatrix, 3U);
        } else {
            sUvFMtxExports->uvGfxMtxViewLoad((u32) object->unk1C + node->unk5 * sizeof(Mtx4F),
                                             (u16) matrixLoadFlags);
        }
        outstandingPushes++; /* RE_UNKNOWN: matrix-stack and graphics-buffer capacity need allocation/consumer proof. */
        if (drawNode) {
            if ((node->unk20 != 0) && (object->unk7 == 0) && (lookAtMode != 1)) {
                sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&hiliteMatrix, object->unk1C);
                lookAtMode = 1;
                sUvGfxStateExports->uvGfxEmitLookAtAndOptionalHilites(&hiliteMatrix, 1);
            }
            if ((object->unk7 != 0) && (lookAtMode != 2)) {
                sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&lookAtMatrix, object->unk1C);
                lookAtMode = 2;
                sUvGfxStateExports->uvGfxEmitLookAtAndOptionalHilites(&lookAtMatrix, 0);
            }
            stepIndex = 0;
            stateCount = node->unk4;
            if (stepIndex < stateCount) {
                do {
                    if ((object->unk4 & 0x20) && (nodeIndex == 0) && (stepIndex == 0)) {
                        int savedState = node->stateTable[stepIndex].state;
                        node->stateTable[stepIndex].state |= 0x10000000;
                        sUvGfxStateExports->uvGfxStateDraw(&node->stateTable[stepIndex]);
                        node->stateTable[stepIndex].state = savedState; /* RE_ORIGINAL_QUIRK: re-read stateTable after drawing; aliases may change the restore destination. */
                        continue;
                    }
                    sUvGfxStateExports->uvGfxStateDraw(&node->stateTable[stepIndex]);
                } while (++stepIndex != stateCount);
            }
        }
        if ((nodeIndex + 1) == hierarchy->unk8) {
            break;
        }
        depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6;
        for (stepIndex = 0; stepIndex <= depthDifference; stepIndex++) { /* Keep this inclusive bound; the skipped-node loop is exclusive. */
            sUvFMtxExports->uvGfxMtxFViewPop();
            outstandingPushes--;
        }
    }

    for (nodeIndex = 0; nodeIndex < outstandingPushes; nodeIndex++) {
        sUvFMtxExports->uvGfxMtxFViewPop();
    }
    if (object->unk24 != NULL) {
        object->unk24(object->unk2C);
    }
}

/* Draw selected model nodes while temporarily replacing four matrix coefficients; restore the captured matrix before post-callback. */
#line 802 "src/modules/uvdobj_rom.c"
void uvDobjDrawHierarchyWithPlanarMatrixOverride(s32 unusedQueueWord, DObj *object) {
    ParsedUVMD_1 *hierarchy;
    s32 nodeIndex;
    s32 outstandingPushes;
    s32 drawNode;
    s32 depthDifference;
    ParsedUVMD *parsedModel;
    f32 unusedFloatA; /* RE_UNKNOWN: historical unused floating-point declarations/ABI. */
    f32 unusedFloatB; /* Retain the original unused declaration. */
    f32 normalizationDivisor;
    Mtx4F *capturedMatrix;
    u8 selectedLod;
    s32 stateCount;
    f32 modelScalar;
    f32 savedM00;
    f32 savedM01;
    f32 savedM10;
    f32 savedM11;
    uvModelLOD *node;
    f32 objectScalar8;
    f32 objectScalarC;
    s32 stepIndex;
    Mtx4F viewMatrix;

    objectScalar8 = object->unk8; /* Snapshot +8/+C before pre-callback; do not reload them afterward. */
    objectScalarC = object->unkC;
    if (object->unk20 != NULL) {
        object->unk20(object->unk28); /* RE_UNKNOWN: callback aliases/mutation and input/resource lifetimes need caller/provider proof. */
    }
    selectedLod = object->unk6;
    parsedModel = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/LOD/node/matrix extents and validity need producer/lifecycle proof. */
    modelScalar = parsedModel->unk10;
    D_uvdobj_rom_004039B8[D_uvdobj_rom_004039BC++] = (object - sDObjs); /* RE_UNKNOWN: object membership/array capacity; retain u16 cursor wrap. */
    hierarchy = &parsedModel->unk0[selectedLod];
    capturedMatrix = object->unk1C; /* Restore this captured pointer even if later callbacks retarget object->unk1C. */
    savedM00 = capturedMatrix->m[0][0];
    savedM01 = capturedMatrix->m[0][1];
    savedM10 = capturedMatrix->m[1][0];
    savedM11 = capturedMatrix->m[1][1];

    normalizationDivisor = MAX(1.0f, sUvMathExports->uvSqrtf(SQ(objectScalar8) + SQ(objectScalarC))); /* RE_ORIGINAL_QUIRK: MAX can call sqrt twice; preserve macro evaluation. */
    objectScalar8 /= normalizationDivisor; /* RE_UNKNOWN: scalar meaning, divisor/NaN/FP domains need original callers and FP-mode evidence. */
    objectScalarC /= normalizationDivisor;

    capturedMatrix->m[0][0] = -objectScalarC / modelScalar;
    capturedMatrix->m[1][1] = -objectScalarC / modelScalar;
    capturedMatrix->m[0][1] = objectScalar8 / modelScalar;
    capturedMatrix->m[1][0] = -objectScalar8 / modelScalar;
    outstandingPushes = 0;
    for (nodeIndex = 0; nodeIndex < hierarchy->unk8; nodeIndex++) {
        node = &hierarchy->unk0[nodeIndex];
        if ((object->unk14 & (1 << nodeIndex)) || (((node->unk7 & 1) != 0))) { /* RE_UNKNOWN: mask/flag meanings and shift-index domain need producer/caller proof. */
            drawNode = FALSE;
        } else {
            drawNode = TRUE;
        }

        if (!drawNode) {
            if (node->unk7 & 2) {
                outstandingPushes++;
                depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6; /* RE_UNKNOWN: next-node extent/depth rules need asset/caller proof. */
                for (stepIndex = 0; stepIndex < depthDifference; stepIndex++) {
                    sUvFMtxExports->uvGfxMtxFViewPop();
                    outstandingPushes--;
                }
                continue;
            }
        }
        if (nodeIndex == 0) {
            sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&viewMatrix, (u32) object->unk1C + nodeIndex * sizeof(Mtx4F));
            sUvFMtxExports->uvGfxMtxViewLoad(&viewMatrix, 3);
        } else {
            sUvFMtxExports->uvGfxMtxViewLoad((u32) object->unk1C + nodeIndex * sizeof(Mtx4F), 1);
        }
        outstandingPushes++; /* RE_UNKNOWN: matrix-stack balance/capacity and graphics storage need allocation/consumer proof. */
        if (drawNode) {
            stateCount = node->unk4;
            stepIndex = 0;
            if (stateCount > 0) {
                do {
                    sUvGfxStateExports->uvGfxStateDraw(&node->stateTable[stepIndex]);
                } while (++stepIndex != stateCount);
            }
        }

        if ((nodeIndex + 1) == hierarchy->unk8) {
            break;
        }

        depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6;
        for (stepIndex = 0; stepIndex <= depthDifference; stepIndex++) { /* Keep inclusive pops here and exclusive pops for skipped nodes. */
            sUvFMtxExports->uvGfxMtxFViewPop();
            outstandingPushes--;
        }
    }

    for (nodeIndex = 0; nodeIndex < outstandingPushes; nodeIndex++) {
        sUvFMtxExports->uvGfxMtxFViewPop();
    }
    capturedMatrix->m[0][0] = savedM00;
    capturedMatrix->m[0][1] = savedM01;
    capturedMatrix->m[1][0] = savedM10;
    capturedMatrix->m[1][1] = savedM11;
    if (object->unk24 != NULL) {
        object->unk24(object->unk2C);
    }
}

#line 910 "src/modules/uvdobj_rom.c"
/* Find the first enabled object whose broad-phase sphere contains the
 * point, then perform the model-specific test when required. Preserve
 * the optional single-object filter, packed hit identity and 0xFFFF miss. */
s32 uvDobjFindObjectContainingWorldPoint(f32 pointX, f32 pointY, f32 pointZ) {
    f32 centerY;
    f32 centerZ;
    f32 radius;
    f32 centerX;
    s32 i;
    s32 var_s2;
    s32 endObject;
    s32 firstObject;
    DObj *object;
    s32 selectedObject;

    selectedObject = D_uvdobj_rom_004039EC;
    if (selectedObject == -1) {
        endObject = sUvDobjId;
        firstObject = 0;
    } else {
        firstObject = D_uvdobj_rom_004039EC;
        endObject = D_uvdobj_rom_004039EC + 1;
    }

    for (i = firstObject; i < endObject; i++) {
        object = &sDObjs[i];
        if ((object->modelId == 0xFFFF) || !(object->unk4 & 1)) {
            continue;
        }

        radius = object->unk10;
        centerX = object->unk1C->m[3][0];
        centerY = object->unk1C->m[3][1];
        centerZ = object->unk1C->m[3][2];
        if (!((pointX + radius) < centerX) && !(centerX < (pointX - radius))
            && !((pointY + radius) < centerY) && !(centerY < (pointY - radius))
            && !((pointZ + radius) < centerZ) && !(centerZ < (pointZ - radius))
            && (sUvIntersectExports->uvIntersectPointInsideSphere(pointX, pointY, pointZ, centerX, centerY,
                                                                   centerZ, radius)
                != 0)) {
            ParsedUVMD *model = uvGetLoadedFile('UVMD', object->modelId);
            if (!(model->unk5 & 2)) {
                return i;
            }
            *D_uvdobj_rom_004039E0 = i;
            if (uvDobjTestHierarchyPointBounds(pointX, pointY, pointZ, object) >= 0) {
                return *D_uvdobj_rom_004039E0;
            }
            continue;
        }
    }
    return 0xFFFF;
}
#line 960 "src/modules/uvdobj_rom.c"

#line 961 "src/modules/uvdobj_rom.c"
/* Collect enabled objects whose bounding spheres overlap the segment
 * expanded by the caller radius. Return the shared result count and
 * publish the shared result array only when at least one hit is found. */
s32 uvDobjCollectCapsuleOverlaps(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, f32 radius,
                             s32 *outObjectIds) {
    f32 centerX;
    f32 centerY;
    f32 centerZ;
    f32 objectRadius;
    s32 i;
    s32 var_s1;
    s32 endObject;
    s32 firstObject;
    s32 selectedObject;
    DObj *object;

    *D_uvdobj_rom_004039E4 = 0;
    selectedObject = D_uvdobj_rom_004039EC;
    if (selectedObject == -1) {
        endObject = sUvDobjId;
        firstObject = 0;
    } else {
        firstObject = D_uvdobj_rom_004039EC;
        endObject = D_uvdobj_rom_004039EC + 1;
    }
    for (i = firstObject; i < endObject; i++) {
        object = &sDObjs[i];
        if ((object->modelId == 0xFFFF) || !(object->unk4 & 1)) {
            continue;
        }

        objectRadius = object->unk10;
        centerX = object->unk1C->m[3][0];
        centerY = object->unk1C->m[3][1];
        centerZ = object->unk1C->m[3][2];
        if (((centerX + objectRadius + radius) < MIN(startX, endX))) {
            continue;
        }
        if ((MAX(startX, endX) < ((centerX - objectRadius) - radius))) {
            continue;
        }
        if (((centerY + objectRadius + radius) < MIN(startY, endY))) {
            continue;
        }

        if ((MAX(startY, endY) < ((centerY - objectRadius) - radius))) {
            continue;
        }

        if (((centerZ + objectRadius + radius) < MIN(startZ, endZ))) {
            continue;
        }

        if ((MAX(startZ, endZ) < ((centerZ - objectRadius) - radius))
            || (sUvIntersectExports->func_uvintersect_rom_00400530(
                    centerX, centerY, centerZ, objectRadius, startX, startY, startZ, endX, endY, endZ, radius)
                == 0)) {
            continue;
        }

        D_uvdobj_rom_004039D4[*D_uvdobj_rom_004039E4] = i;
        *D_uvdobj_rom_004039E4 += 1;
        if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
            break;
        }
    }
    if (*D_uvdobj_rom_004039E4 != 0) {
        *outObjectIds = D_uvdobj_rom_004039D4;
    }
    return *D_uvdobj_rom_004039E4;
}
#line 1029 "src/modules/uvdobj_rom.c"

/* Collect shared XYZ/scalar-extent overlap results, dispatching flagged models to hierarchy tests. */
#line 1030 "src/modules/uvdobj_rom.c"
s32 uvDobjCollectOverlapsWithScalarExtent(f32 queryX, f32 queryY, f32 queryZ, f32 queryExtent, s32 **outObjectWords, f32 **outScalars,
                             Vec3F **outVectors) {
    char historicalStorage[0x14]; /* RE_UNKNOWN: historical unused storage/ABI; retain declarations. */
    Mtx4F *objectMatrix;
    DObj *object;
    s32 endObjectIndex;
    Vec3F *resultVector;
    f32 historicalUnusedScalar; /* Retain the original unused scalar. */
    f32 objectY;
    f32 objectZ;
    f32 objectExtent;
    f32 objectX;
    f32 resultScalar;
    s32 objectIndex;
    s32 firstObjectIndex;
    s32 selectedObjectIndex;
    ParsedUVMD *model;
    ParsedUVMD *historicalUnusedModel; /* Retain the original unused pointer. */

    selectedObjectIndex = D_uvdobj_rom_004039EC; /* RE_UNKNOWN: selected-index range and shared-buffer lifetime need caller/allocation proof. */
    if (selectedObjectIndex == -1) {
        firstObjectIndex = 0;
        endObjectIndex = sUvDobjId;
    } else {
        endObjectIndex = D_uvdobj_rom_004039EC + 1;
        firstObjectIndex = D_uvdobj_rom_004039EC;
    }
    *D_uvdobj_rom_004039E4 = 0;
    *D_uvdobj_rom_004039F8 = 0;
    for (objectIndex = firstObjectIndex; objectIndex < endObjectIndex; objectIndex++) {
        object = &sDObjs[objectIndex];
        if ((object->modelId == 0xFFFF) || !(object->unk4 & 1)) {
            continue;
        }
        objectExtent = object->unk10;
        objectMatrix = object->unk1C;
        objectX = objectMatrix->m[3][0];
        objectY = objectMatrix->m[3][1];
        objectZ = objectMatrix->m[3][2];

        if (((queryX + queryExtent + objectExtent) < objectX)) {
            continue;
        }

        if ((objectX < ((queryX - queryExtent) - objectExtent))) {
            continue;
        }
        if (((queryY + queryExtent + objectExtent) < objectY)) {
            continue;
        }

        if ((objectY < ((queryY - queryExtent) - objectExtent))) {
            continue;
        }

        if (((queryZ + queryExtent + objectExtent) < objectZ)) {
            continue;
        }

        if ((objectZ < ((queryZ - queryExtent) - objectExtent))
            || (sUvIntersectExports->uvIntersectSpheresOverlap(queryX, queryY, queryZ, queryExtent, objectX,
                                                                   objectY, objectZ, objectExtent)
                == 0)) {
            continue;
        }

        model = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model residency, flags and bound meanings need producer/lifecycle proof. */
        *D_uvdobj_rom_004039E0 = objectIndex;
        if (model->unk5 & 0x76) {
            uvDobjQueryHierarchyWithScalarExtent(queryX, queryY, queryZ, queryExtent, object);
            if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
                break;
            }
            continue;
        }

        D_uvdobj_rom_004039D4[*D_uvdobj_rom_004039E4] = *D_uvdobj_rom_004039E0; /* RE_ORIGINAL_QUIRK: append precedes capacity test; RE_UNKNOWN: buffer extent/alias domain needs allocation/caller proof. */
        resultVector = &D_uvdobj_rom_004039D8[*D_uvdobj_rom_004039E4];
        resultVector->x = queryX - objectMatrix->m[3][0];
        resultVector->y = queryY - objectMatrix->m[3][1];
        resultVector->z = queryZ - objectMatrix->m[3][2];
        sUvFVecExports->uvVec3FNormalize(resultVector, resultVector); /* RE_ORIGINAL_QUIRK: ignore normalization return, then re-read the vector for the scalar. */
        resultScalar = (model->unkC
                      - sUvMathExports->uvSqrtf(SQ(resultVector->x) + SQ(resultVector->y) + SQ(resultVector->z)))
                     / queryExtent; /* RE_UNKNOWN: zero/nonfinite extent and FP-mode contracts need caller evidence. */
        if (resultScalar < 0.0f) {
            D_uvdobj_rom_004039D0[*D_uvdobj_rom_004039E4] = resultScalar;
        } else {
            D_uvdobj_rom_004039D0[*D_uvdobj_rom_004039E4] = 0.0f;
        }
        D_uvdobj_rom_004039DC[*D_uvdobj_rom_004039E4] |= 1;
        *D_uvdobj_rom_004039E4 += 1;
        if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
            break;
        }
    }
    if (*D_uvdobj_rom_004039E4 != 0) { /* RE_ORIGINAL_QUIRK: zero results leave caller output pointers unchanged. */
        *outObjectWords = D_uvdobj_rom_004039D4;
        *outScalars = D_uvdobj_rom_004039D0;
        *outVectors = D_uvdobj_rom_004039D8;
    }
    return *D_uvdobj_rom_004039E4;
}

/* Collect hierarchy results for an endpoint pair, preserving the coincident-point path and shared-result sort. */
#line 1134 "src/modules/uvdobj_rom.c"
s32 uvDobjCollectSegmentHierarchyResults(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, s32 **outObjectWords,
                             f32 **outScalars, Vec3F **outVectors) {
    DObj *object;
    f32 extentOrDeltaX;
    f32 xOrDeltaY;
    ParsedUVMD *model;
    f32 broadPhaseFraction; /* Provider-written fraction remains unused by this caller. */
    f32 yOrDeltaZ;
    f32 objectZ;
    s32 endObjectIndex;
    f32 midpointX;
    f32 midpointY;
    f32 midpointZ;
    f32 midpointExtent;
    u16 containingObjectId;
    s32 firstObjectIndex;
    s32 objectIndex;
    s32 candidateObjectCount;

    *D_uvdobj_rom_004039E4 = 0; /* RE_UNKNOWN: shared/output storage, aliases and lifetime need allocation/caller proof. */
    if ((startX == endX) && (startY == endY) && (startZ == endZ)) {
        containingObjectId = uvDobjFindObjectContainingWorldPoint(startX, startY, startZ); /* RE_ORIGINAL_QUIRK: keep only the returned low u16. */
        if (containingObjectId == 0xFFFF) {
            *outObjectWords = NULL;
            *outScalars = NULL;
            *outVectors = NULL;
            return 0;
        }
        *D_uvdobj_rom_004039D4 = containingObjectId;
        *D_uvdobj_rom_004039D0 = 0.0f;
        D_uvdobj_rom_004039D8->x = 0.0f;
        D_uvdobj_rom_004039D8->y = 0.0f;
        D_uvdobj_rom_004039D8->z = 1.0f;
        *outObjectWords = D_uvdobj_rom_004039D4;
        *outScalars = D_uvdobj_rom_004039D0;
        *outVectors = D_uvdobj_rom_004039D8;
        return 1; /* RE_ORIGINAL_QUIRK: return one without publishing one to the shared count. */
    }
    if (D_uvdobj_rom_004039EC == -1) {
        firstObjectIndex = 0;
        endObjectIndex = sUvDobjId;
    } else {
        endObjectIndex = D_uvdobj_rom_004039EC + 1;
        firstObjectIndex = D_uvdobj_rom_004039EC;
    }
    candidateObjectCount = endObjectIndex - firstObjectIndex; /* RE_UNKNOWN: index/FP domains need callers; preserve cached threshold and MIN/MAX evaluation. */
    if (candidateObjectCount >= 6) {
        extentOrDeltaX = endX - startX;
        xOrDeltaY = endY - startY;
        yOrDeltaZ = endZ - startZ;
        midpointExtent = sUvMathExports->uvSqrtf(SQ(extentOrDeltaX) + SQ(xOrDeltaY) + SQ(yOrDeltaZ)) * 0.5f;
        midpointX = (0.5f * extentOrDeltaX) + startX;
        midpointY = (0.5f * xOrDeltaY) + startY;
        midpointZ = (0.5f * yOrDeltaZ) + startZ;
    }
    for (objectIndex = firstObjectIndex; objectIndex < endObjectIndex; objectIndex++) {
        object = &sDObjs[objectIndex];
        if ((object->modelId == 0xFFFF) || !(object->unk4 & 1)) {
            continue;
        }

        extentOrDeltaX = object->unk10;
        xOrDeltaY = object->unk1C->m[3][0];
        yOrDeltaZ = object->unk1C->m[3][1];
        objectZ = object->unk1C->m[3][2];
        if (((xOrDeltaY + extentOrDeltaX) < MIN(startX, endX))) {
            continue;
        }

        if ((MAX(startX, endX) < (xOrDeltaY - extentOrDeltaX))) {
            continue;
        }

        if (((yOrDeltaZ + extentOrDeltaX) < MIN(startY, endY))) {
            continue;
        }

        if ((MAX(startY, endY) < (yOrDeltaZ - extentOrDeltaX))) {
            continue;
        }

        if (((objectZ + extentOrDeltaX) < MIN(startZ, endZ))) {
            continue;
        }

        if ((MAX(startZ, endZ) < (objectZ - extentOrDeltaX))) {
            continue;
        }
        if (((candidateObjectCount < 6)
             || (sUvIntersectExports->uvIntersectSpheresOverlap(midpointX, midpointY, midpointZ, midpointExtent, xOrDeltaY,
                                                                    yOrDeltaZ, objectZ, extentOrDeltaX)
                 != 0))) {
            if ((sUvIntersectExports->uvIntersectSegmentSphereFraction(
                     startX, startY, startZ, endX, endY, endZ, xOrDeltaY, yOrDeltaZ, objectZ, extentOrDeltaX, &broadPhaseFraction)
                 == 0)) {
                continue;
            }
            model = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/flag validity and callback mutation need producer/lifecycle proof. */
            if (!(model->unk5 & 6)) {
                continue;
            }

            *D_uvdobj_rom_004039E0 = objectIndex;
            uvDobjQueryHierarchySegment(startX, startY, startZ, endX, endY, endZ, object);
        }
    }
    *outObjectWords = D_uvdobj_rom_004039D4;
    *outScalars = D_uvdobj_rom_004039D0;
    *outVectors = D_uvdobj_rom_004039D8;
    sUvQueryExports->uvQueryDoSorting(); /* RE_ORIGINAL_QUIRK: publish pointers before sorting; keep fresh shared-count return. */
    return *D_uvdobj_rom_004039E4;
}

/* Traverse model nodes for the four-scalar query; preserve shared result writes, capacity early return and ignored signed sum. */
#line 1247 "src/modules/uvdobj_rom.c"
s16 uvDobjQueryHierarchyWithScalarExtent(f32 pointX, f32 pointY, f32 pointZ, f32 scalarExtent, DObj *object) {
    char pad[0x10]; /* RE_UNKNOWN: historical unused pad/local declarations. */
    ParsedUVMD_1 *hierarchy;
    ParsedUVMD *parsedModel;
    s16 depthDifference;
    s16 popIndex;
    s16 outstandingPushes;
    s16 nodeIndex;
    s32 queryNode;
    s32 nodeCount;
    uvModelLOD *node;
    s16 ignoredResultSum;

    parsedModel = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/node/matrix validity and lifetime need producer/caller proof. */
    hierarchy = parsedModel->unk0;
    ignoredResultSum = -1;
    nodeCount = hierarchy->unk8; /* Cache the u8 count before callbacks; keep later node-array reloads. */
    sUvModelExports->uvModelResetMatrixStack();
    outstandingPushes = 0;
    for (nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++) {
        if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
            return sUvQueryExports->uvQueryGetRecordCapacity(); /* RE_ORIGINAL_QUIRK: query capacity again and return without the final pop loop. */
        }
        node = &hierarchy->unk0[nodeIndex];

        if ((object->unk14 & (1 << nodeIndex)) || (node->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (nodeIndex != D_uvdobj_rom_004039F0))) {
            queryNode = 0; /* RE_UNKNOWN: mask/flag meanings and shift-index domain need producer/caller evidence. */
        } else {
            queryNode = 1;
        }
        if ((queryNode != 0) || !(node->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix((u32) object->unk1C + nodeIndex * sizeof(Mtx4F));
            outstandingPushes++; /* RE_UNKNOWN: stack capacity/balance and callback aliases need lifecycle/caller proof. */
            if (queryNode != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (nodeIndex << 0x18);
                ignoredResultSum += sUvModelExports->uvModelAppendScalarExtentLodQueryResults(
                    pointX, pointY, pointZ, scalarExtent, sUvModelExports->uvModelGetCurrentMatrix(),
                    &hierarchy->unk0[nodeIndex], parsedModel); /* RE_ORIGINAL_QUIRK: retain the ignored s16 sum. RE_UNKNOWN: scalar units/FP domain need caller proof. */
            }
            if (nodeIndex == (nodeCount - 1)) {
                break;
            }

            depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6;
            // clang-format off
            for (popIndex = 0; popIndex <= depthDifference; popIndex++) { \
                sUvModelExports->uvModelPopMatrix(); \
                outstandingPushes -= 1; \
            } // clang-format on
        }
    }
    for (nodeIndex = 0; nodeIndex < outstandingPushes; nodeIndex++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1; /* Shared query state carries results; this normal return stays -1. */
}

/* Traverse model nodes and test point bounds; preserve the signed provider result and success early return. */
#line 1305 "src/modules/uvdobj_rom.c"
s16 uvDobjTestHierarchyPointBounds(f32 pointX, f32 pointY, f32 pointZ, DObj *object) {
    s16 depthDifference;
    s16 pointResult;
    s16 popIndex;
    s16 outstandingPushes;
    s16 nodeIndex;
    s32 temp_s5; /* RE_UNKNOWN: historical unused locals retain their original declarations. */
    s32 queryNode;
    ParsedUVMD_1 *hierarchy;
    s32 nodeCount;
    void *temp_v0_2; /* RE_UNKNOWN: historical unused pointer declaration. */
    uvModelLOD *node;
    ParsedUVMD *parsedModel = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/node/matrix validity and lifetime need producer/caller proof. */

    hierarchy = parsedModel->unk0;
    nodeCount = hierarchy->unk8; /* Cache the u8 count before callbacks; keep later node-array reloads. */
    sUvModelExports->uvModelResetMatrixStack();
    outstandingPushes = 0;
    for (nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++) {
        node = &hierarchy->unk0[nodeIndex];
        if ((object->unk14 & (1 << nodeIndex)) || (node->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (nodeIndex != D_uvdobj_rom_004039F0))) {
            queryNode = 0; /* RE_UNKNOWN: mask/flag meanings and shift-index domain need producer/caller evidence. */
        } else {
            queryNode = 1;
        }
        if ((queryNode != 0) || !(node->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix(&object->unk1C[nodeIndex]);
            outstandingPushes++; /* RE_UNKNOWN: stack capacity/balance and callback aliases need lifecycle/caller proof. */
            if (queryNode != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (nodeIndex << 0x18);
                pointResult = sUvModelExports->uvModelTestWorldPointInLodBounds(
                    pointX, pointY, pointZ, sUvModelExports->uvModelGetCurrentMatrix(), &hierarchy->unk0[nodeIndex]);
                if (pointResult >= 0) {
                    return pointResult; /* RE_ORIGINAL_QUIRK: success returns without the final pop loop. */
                }
            }
            if ((nodeIndex + 1) == nodeCount) {
                break;
            }
            depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6;
            // clang-format off
            for (popIndex = 0; popIndex <= depthDifference; popIndex++) { \
                sUvModelExports->uvModelPopMatrix(); \
                outstandingPushes--; \
            } // clang-format on
            continue;
        }
    }
    for (nodeIndex = 0; nodeIndex < outstandingPushes; nodeIndex++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1; /* RE_UNKNOWN: point units, exceptional values and FP contracts need caller/provider evidence. */
}

/* Traverse model nodes for the segment query; preserve shared result writes, ignored provider return and final -1. */
#line 1360 "src/modules/uvdobj_rom.c"
s16 uvDobjQueryHierarchySegment(f32 startX, f32 startY, f32 startZ, f32 endX, f32 endY, f32 endZ, DObj *object) {
    char pad[0x10]; /* RE_UNKNOWN: historical unused pad/local declarations. */
    ParsedUVMD *parsedModel;
    ParsedUVMD *loadedModel;
    ParsedUVMD_1 *hierarchy;
    s16 depthDifference;
    s16 popIndex;
    s16 outstandingPushes;
    s16 nodeIndex;
    s32 queryNode;
    s32 nodeCount;
    uvModelLOD *temp_v0_2; /* RE_UNKNOWN: historical unused pointer declaration. */
    uvModelLOD *node;

    loadedModel = uvGetLoadedFile('UVMD', object->modelId); /* RE_UNKNOWN: model/node/matrix validity and lifetime need producer/caller proof. */
    parsedModel = loadedModel;
    hierarchy = loadedModel->unk0;
    nodeCount = hierarchy->unk8; /* Cache the u8 count before callbacks; keep later node-array reloads. */
    sUvModelExports->uvModelResetMatrixStack();
    outstandingPushes = 0;
    for (nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++) {
        node = &hierarchy->unk0[nodeIndex];
        if ((object->unk14 & (1 << nodeIndex)) || (node->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (nodeIndex != D_uvdobj_rom_004039F0))) {
            queryNode = 0; /* RE_UNKNOWN: mask/flag meanings and shift-index domain need producer/caller evidence. */
        } else {
            queryNode = 1;
        }
        if ((queryNode != 0) || !(node->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix(&object->unk1C[nodeIndex]);
            outstandingPushes += 1; /* RE_UNKNOWN: stack capacity/balance and callback aliases need lifecycle/caller proof. */
            if (queryNode != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (nodeIndex << 0x18);
                sUvModelExports->uvModelAppendSegmentLodQueryResults(startX, startY, startZ, endX, endY, endZ,
                                                           sUvModelExports->uvModelGetCurrentMatrix(),
                                                           &hierarchy->unk0[nodeIndex], parsedModel); /* Retain the ignored provider return and shared result writes. */
            }
            if (nodeIndex == (nodeCount - 1)) {
                break;
            }
            depthDifference = hierarchy->unk0[nodeIndex].unk6 - hierarchy->unk0[nodeIndex + 1].unk6;

            // clang-format off
            for (popIndex = 0; popIndex <= depthDifference; popIndex++) { \
                sUvModelExports->uvModelPopMatrix(); \
                outstandingPushes -= 1; \
            }
            // clang-format on
        }
    }

    for (nodeIndex = 0; nodeIndex < outstandingPushes; nodeIndex++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1; /* RE_UNKNOWN: segment units and FP domain need caller/provider proof; normal return stays -1. */
}

#line 1417 "src/modules/uvdobj_rom.c"
/* Extract quaternions from nonroot object matrices and write one-based joint
 * indices. Return max(model joint count - 1, 0). RE_UNKNOWN: object/model validity
 * and output capacity/lifetime; trace original constructors and callers. */
s32 uvDobjExtractJointQuaternionsFromMatrices(s32 objectId, Quat *quaternions, u8 *jointIndices) {
    DObj *object;
    s32 count;
    s32 i;
    ParsedUVMD *uvmd;

    object = &sDObjs[objectId];
    uvmd = uvGetLoadedFile('UVMD', uvDobjGetModel(objectId));
    if (uvmd->unk6 >= 2) {
        count = uvmd->unk6 - 1;
    } else {
        count = 0;
    }
    for (i = 0; i < count; i++, quaternions++) {
        sUvQuatExports->uvQuatFromRotationMatrix(quaternions, (u32) object->unk1C + (i + 1) * sizeof(Mtx4F));
        jointIndices[i] = i + 1;
    }
    return count;
}
#line 1436 "src/modules/uvdobj_rom.c"

#line 1437 "src/modules/uvdobj_rom.c"
/* Clear the original fixed rectangle (2, 120) through (310, 235) in
 * the depth-image buffer, then restore the current color framebuffer.
 * Preserve every synchronization command and the original render state. */
void uvDobjClearFixedDepthImageRectangle(void) {
    Gfx **displayListHead;
    void *depthImageBuffer;
    void *colorFramebuffer;

    displayListHead = sUvGfxMgrExports->uvGetDisplayListHead();
    depthImageBuffer = sUvGfxMgrExports->uvGfxGetDepthImageBuffer();
    colorFramebuffer = sUvGfxMgrExports->uvGfxGetCurrentFramebuffer();
    sUvGfxStateExports->uvGfxSync();
    gDPSetRenderMode(displayListHead[0]++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    sUvGfxStateExports->uvGfxSync();
    gDPSetCycleType(displayListHead[0]++, G_CYC_FILL);
    sUvGfxStateExports->uvGfxSync();
    gDPSetFillColor(displayListHead[0]++, 0);
    sUvGfxStateExports->uvGfxSync();
    gDPSetColorImage(displayListHead[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sUvGfxMgrExports->uvGetScreenWidth(),
                     osVirtualToPhysical(depthImageBuffer));
    sUvGfxStateExports->uvGfxSync();
    gDPFillRectangle(displayListHead[0]++, 2, 120, 310, 235);
    sUvGfxStateExports->uvGfxSync();
    sUvGfxStateExports->uvGfxSync();
    gDPSetCycleType(displayListHead[0]++, G_CYC_2CYCLE);
    sUvGfxStateExports->uvGfxSync();
    gDPSetColorImage(displayListHead[0]++, G_IM_FMT_RGBA, G_IM_SIZ_16b, sUvGfxMgrExports->uvGetScreenWidth(),
                     osVirtualToPhysical(colorFramebuffer));
    sUvGfxStateExports->uvGfxSync();
}
#line 1464 "src/modules/uvdobj_rom.c"

#line 1465 "src/modules/uvdobj_rom.c"
/* Release the object light record when present, then acquire a record
 * from the three caller packed colors and store its original result. */
void uvDobjReplaceLightColorRecord(s32 objectId, s32 packedColor2C, s32 packedColor28, s32 packedColor24) {
    DObj *object;
    UnkStruct_uvlight_rom_00401758 colors;

    colors.unk2C = packedColor2C;
    colors.unk28 = packedColor28;
    colors.unk24 = packedColor24;
    object = &sDObjs[objectId];
    if (object->unk2 != -1) {
        sUvLightExports->uvLightReleaseRecord(object->unk2);
    }
    object->unk2 = sUvLightExports->uvLightAcquireMatchingColorRecord(&colors);
}
#line 1478 "src/modules/uvdobj_rom.c"

#line 1479 "src/modules/uvdobj_rom.c"
/* Return the shared query-array count and write its base to the caller
 * output. The array lifetime remains owned by the object module. */
u16 uvDobjGetQueryArray(s32 **output) {
    *output = D_uvdobj_rom_004039B8;
    return D_uvdobj_rom_004039BC;
}
#line 1483 "src/modules/uvdobj_rom.c"
