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
void func_uvdobj_rom_004015C0(s32 arg0, DObj *arg1);
void func_uvdobj_rom_00401ABC(s32 arg0, DObj *arg1);
s32 uvDobjFindObjectContainingWorldPoint(f32 arg0, f32 arg1, f32 arg2);
s32 uvDobjCollectCapsuleOverlaps(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                             s32 *arg7);
s32 func_uvdobj_rom_00402420(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 **arg4, f32 **arg5,
                             Vec3F **arg6);
s32 func_uvdobj_rom_00402870(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 **arg6,
                             f32 **arg7, Vec3F **arg8);
s16 func_uvdobj_rom_00402D68(f32 arg0, f32 arg1, f32 arg2, f32 arg3, DObj *arg4);
s16 func_uvdobj_rom_00403054(f32 arg0, f32 arg1, f32 arg2, DObj *arg3);
s16 func_uvdobj_rom_004032DC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, DObj *arg6);
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

void __entrypoint_func_uvdobj_rom_400000(UvDobj_Exports *exports) {
    DobjSettings *settings;
    s32 i;

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
    exports->func_uvdobj_rom_00402420 = func_uvdobj_rom_00402420;
    exports->uvDobjSetFlags = uvDobjSetFlags;
    exports->func_uvdobj_rom_00402870 = func_uvdobj_rom_00402870;
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
    settings = uvGetSystemProp(SYSTEM_PROPID_DOBJ_SETTINGS);
    if (settings == NULL) {
        sDObjsCount = 0x64;
        D_uvdobj_rom_004039C8 = 0x64;
        D_uvdobj_rom_004039CC = 0x12C;
    } else {
        if (settings->dobjsCount != 0) {
            sDObjsCount = settings->dobjsCount;
        } else {
            sDObjsCount = 0x64;
        }
        if (settings->unk4 != 0) {
            D_uvdobj_rom_004039C8 = settings->unk4;
        } else {
            D_uvdobj_rom_004039C8 = 0x64;
        }
        if (settings->unk8 != 0) {
            D_uvdobj_rom_004039CC = settings->unk8;
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
    for (i = 0; i < D_uvdobj_rom_004039F4; i++) {
        D_uvdobj_rom_004039E8[i] = 1.0f;
    }

    sDObjs = _uvMemAllocAlign8(sDObjsCount * sizeof(DObj));
    D_uvdobj_rom_004039B8 = _uvMemAllocAlign8(sDObjsCount * sizeof(s32));
    uvMemSet(sDObjs, 0, sDObjsCount * sizeof(DObj));
    uvMemSet(D_uvdobj_rom_004039B8, 0, sDObjsCount * sizeof(s32));
    for (i = 0; i < sDObjsCount; i++) {
        sDObjs[i].modelId = 0xFFFF;
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
}

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
/* Register the original DOBJ callback on channel property six at priority
 * 0x3C with no insert-before routine; no context argument is supplied. */
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

void uvDobjModel(s32 objId, s32 modelId) {
    f32 temp_fv0;
    u8 temp_v0_3;
    u8 var_s2;
    s32 i;
    ParsedUVMD *temp_v0_2;
    ParsedUVMD *var_s1;
    Mtx4F *sp38;
    DObj *temp_s5;

    temp_s5 = &sDObjs[objId];
    if (modelId == temp_s5->modelId) {
        return;
    }

    if (objId >= sUvDobjId) {
        return;
    }

    var_s1 = NULL;
    if (temp_s5->modelId != 0xFFFF) {
        var_s1 = uvGetLoadedFile('UVMD', temp_s5->modelId);
        if (var_s1 == NULL) {
            PANIC;
        } else {
            // FAKE
            if (var_s1 && var_s1 && var_s1)
                ;
        }
    }
    if (modelId == 0xFFFF) {
        temp_s5->modelId = 0xFFFF;
        if (temp_s5->unk1C != 0) {
            _uvMemFree((void *) temp_s5->unk1C);
            temp_s5->unk1C = 0;
            temp_s5->unk1A = 0;
        }
        return;
    }

    temp_v0_2 = uvGetLoadedFile('UVMD', modelId);
    if (temp_v0_2 == NULL) {
        return;
    }

    temp_s5->unk14 = 0;
    temp_s5->unk10 = temp_v0_2->unkC;
    if (temp_s5->modelId == 0xFFFF) {
        var_s2 = 0;
    } else if (var_s1 != NULL) {
        var_s2 = var_s1->unk6;
    } else {
        var_s2 = 0;
        if (temp_s5->unk1C != 0) {
            _uvMemFree((void *) temp_s5->unk1C);
            temp_s5->unk1C = 0;
            temp_s5->unk1A = 0;
        }
    }
    sp38 = temp_s5->unk1C;
    temp_v0_3 = temp_v0_2->unk6;
    temp_s5->unk1C = _uvMemAllocAlign8(temp_v0_3 << 6);
    temp_s5->unk1A = temp_v0_3;

    for (i = 0; i < var_s2; i++) {
        sUvFMtxExports->uvMat4FCopy((u32) temp_s5->unk1C + i * sizeof(Mtx4F),
                                    (u32) sp38 + i * sizeof(Mtx4F));
        _uvMemFree(sp38);
    }

    for (i = var_s2; i < temp_v0_3; i++) {
        Mtx4F *temp = (u32) temp_s5->unk1C + (i * sizeof(Mtx4F));
        Mtx4F *temp2 = (u32) temp_v0_2->unk8 + (i * sizeof(Mtx4F));
        sUvFMtxExports->uvMat4FCopy(temp, temp2);
    }
    if (var_s2 == 0) {
        if (temp_v0_2->unk10 != 1.0f) {
            temp_fv0 = 1.0f / temp_v0_2->unk10;
            sUvFMtxExports->uvMat4Scale((Mtx4F *) temp_s5->unk1C, temp_fv0, temp_fv0, temp_fv0);
        }
    }
    temp_s5->modelId = modelId;
    if (temp_v0_2->unk5 & 0x76) {
        uvDobjSetFlags(objId, 3);
    } else {
        uvDobjSetFlags(objId, 2);
    }
}

u16 uvDobjGetModel(s32 objId) {
    return sDObjs[objId].modelId;
}

void uvDobjProps(s32 objId, ...) {
    va_list args;
    DObj *temp_s1;
    f32 temp_fs0;
    ParsedUVMD *uvmd;
    s16 temp_v0;

    if (objId >= sDObjsCount) {
        return;
    }
    temp_s1 = &sDObjs[objId];
    va_start(args, objId);
    if (temp_s1->modelId == 0xFFFF) {
        PANIC;
        return;
    }
    while (TRUE) {
        temp_v0 = va_arg(args, s32);
        switch (temp_v0) {
            case 10:
                temp_s1->unk7 = va_arg(args, s32);
                break;
            case 1:
                temp_fs0 = va_arg(args, f64);
                uvmd = uvGetLoadedFile('UVMD', temp_s1->modelId);
                temp_s1->unk10 = uvmd->unkC * temp_fs0;
                break;
            case 7:
                temp_s1->unk10 = va_arg(args, f64);
                break;
            case 2:
                temp_s1->unk14 &= ~(1 << va_arg(args, s32));
                break;
            case 3:
                temp_s1->unk14 |= 1 << va_arg(args, s32);
                break;
            case 6:
                temp_s1->unk14 = va_arg(args, s32);
                break;
            case 4:
                temp_s1->unk20 = va_arg(args, s32);
                temp_s1->unk28 = va_arg(args, s32);
                break;
            case 5:
                temp_s1->unk24 = va_arg(args, s32);
                temp_s1->unk2C = va_arg(args, s32);
                break;
            default:
                PANIC;
                break;
            case 0:
                return;
        }
    }
    va_end(args);
}

void uvDobjGetProp(s32 objId, ...) {
    DObj *obj;
    s16 prop;
    va_list args;

    if (objId >= sUvDobjId) {
        return;
    }
    obj = &sDObjs[objId];
    va_start(args, objId);

    while (TRUE) {
        prop = va_arg(args, s32);
        if (prop == NULL) {
            return;
        }

        switch (prop) {
            case 7:
                *va_arg(args, f32 *) = obj->unk10;
                break;
            case 8:
                *va_arg(args, s32 *) = obj->modelId;
                break;
            case 6:
                *va_arg(args, s32 *) = obj->unk14;
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

s32 uvDobjCreate(void) {
    s32 i;

    for (i = 0; i < sDObjsCount; i++) {
        if (sDObjs[i].unk5 == 0) {
            sDObjs[i].unk5 = 1;
            sDObjs[i].unk2 = -1;
            sDObjs[i].unk7 = 0;
            sDObjs[i].unk20 = 0;
            sDObjs[i].unk24 = 0;
            sDObjs[i].unk1A = 0;
            sDObjs[i].unk1C = 0;
            if (sUvDobjId < i + 1) {
                sUvDobjId = i + 1;
            }
            return i;
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
            && (sUvChannel_Exports->func_uvchannel_rom_004014E8(channel, relativeX, relativeY, relativeZ,
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
            renderCallback = func_uvdobj_rom_00401ABC;
        } else {
            renderCallback = func_uvdobj_rom_004015C0;
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

void func_uvdobj_rom_004015C0(s32 arg0, DObj *arg1) {
    ParsedUVMD_1 *sp154;
    void (*temp_v0)(s32, void *);
    void (*temp_v0_6)(s32, void *);
    ParsedUVMD *temp_s0;
    s32 temp_s2_2;
    s32 var_s0;
    s32 j;
    s32 var_s5;
    s32 temp_s4;
    u32 sp130;
    s32 temp_s1;
    uvModelLOD *temp_s2;
    s32 var_fp;
    s32 sp120;
    s32 sp11C;
    s32 sp118;
    Mtx4F spD8;
    Mtx4F sp98;
    Mtx4F sp58;

    sp118 = 0;
    if (arg1->unk20 != NULL) {
        arg1->unk20(arg1->unk28);
    }
    if (!(arg1->unk4 & 2)) {
        return;
    }

    temp_s1 = arg1->unk6;
    temp_s0 = uvGetLoadedFile('UVMD', arg1->modelId);
    sUvLightExports->uvLightSelectRecord(arg1->unk2);
    D_uvdobj_rom_004039B8[D_uvdobj_rom_004039BC++] = (arg1 - sDObjs);
    if (arg1->unk4 & 8) {
        uvDobjClearFixedDepthImageRectangle();
    }
    sp154 = &temp_s0->unk0[temp_s1];
    var_s5 = 0;
    sp120 = arg1->unk4 & 0x80;
    if (sp120) {
        sp11C = 3;
    } else {
        sp11C = 1;
    }
    sp130 = ~arg1->unk14;
    for (var_fp = 0; var_fp < sp154->unk8; var_fp++) {
        temp_s2 = &sp154->unk0[var_fp];
        if (sp130 < (1 << var_fp)) {
            break;
        }
        if ((arg1->unk14 & (1 << var_fp)) || (((temp_s2->unk7 & 1)))) {
            var_s0 = FALSE;
        } else {
            var_s0 = TRUE;
        }

        if (!var_s0) {
            if (temp_s2->unk7 & 2) {
                var_s5++;
                temp_s2_2 = sp154->unk0[var_fp].unk6 - sp154->unk0[var_fp + 1].unk6;
                for (j = 0; j < temp_s2_2; j++) {
                    sUvFMtxExports->uvGfxMtxFViewPop();
                    var_s5--;
                }
                continue;
            }
        }
        if ((var_fp == 0) || (sp120)) {
            sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&spD8, (u32) arg1->unk1C + temp_s2->unk5 * sizeof(Mtx4F));
            sUvFMtxExports->uvGfxMtxViewLoad(&spD8, 3U);
        } else {
            sUvFMtxExports->uvGfxMtxViewLoad((u32) arg1->unk1C + temp_s2->unk5 * sizeof(Mtx4F),
                                             (u16) sp11C);
        }
        var_s5++;
        if (var_s0) {
            if ((temp_s2->unk20 != 0) && (arg1->unk7 == 0) && (sp118 != 1)) {
                sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&sp98, arg1->unk1C);
                sp118 = 1;
                sUvGfxStateExports->uvGfxEmitLookAtAndOptionalHilites(&sp98, 1);
            }
            if ((arg1->unk7 != 0) && (sp118 != 2)) {
                sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&sp58, arg1->unk1C);
                sp118 = 2;
                sUvGfxStateExports->uvGfxEmitLookAtAndOptionalHilites(&sp58, 0);
            }
            j = 0;
            temp_s4 = temp_s2->unk4;
            if (j < temp_s4) {
                do {
                    if ((arg1->unk4 & 0x20) && (var_fp == 0) && (j == 0)) {
                        int prev = temp_s2->stateTable[j].state;
                        temp_s2->stateTable[j].state |= 0x10000000;
                        sUvGfxStateExports->uvGfxStateDraw(&temp_s2->stateTable[j]);
                        temp_s2->stateTable[j].state = prev;
                        continue;
                    }
                    sUvGfxStateExports->uvGfxStateDraw(&temp_s2->stateTable[j]);
                } while (++j != temp_s4);
            }
        }
        if ((var_fp + 1) == sp154->unk8) {
            break;
        }
        temp_s2_2 = sp154->unk0[var_fp].unk6 - sp154->unk0[var_fp + 1].unk6;
        for (j = 0; j <= temp_s2_2; j++) {
            sUvFMtxExports->uvGfxMtxFViewPop();
            var_s5--;
        }
    }

    for (var_fp = 0; var_fp < var_s5; var_fp++) {
        sUvFMtxExports->uvGfxMtxFViewPop();
    }
    if (arg1->unk24 != NULL) {
        arg1->unk24(arg1->unk2C);
    }
}

void func_uvdobj_rom_00401ABC(s32 arg0, DObj *arg1) {
    ParsedUVMD_1 *spE4;
    s32 var_s7;
    s32 var_s3;
    s32 var_s0;
    s32 temp_s2;
    ParsedUVMD *temp_v0_2;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 var_fv1;
    Mtx4F *spC0;
    u8 temp_s0;
    s32 temp_s1;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    uvModelLOD *temp_s4;
    f32 sp9C;
    f32 sp98;
    s32 j;
    Mtx4F sp54;

    sp9C = arg1->unk8;
    sp98 = arg1->unkC;
    if (arg1->unk20 != NULL) {
        arg1->unk20(arg1->unk28);
    }
    temp_s0 = arg1->unk6;
    temp_v0_2 = uvGetLoadedFile('UVMD', arg1->modelId);
    spB4 = temp_v0_2->unk10;
    D_uvdobj_rom_004039B8[D_uvdobj_rom_004039BC++] = (arg1 - sDObjs);
    spE4 = &temp_v0_2->unk0[temp_s0];
    spC0 = arg1->unk1C;
    spB0 = spC0->m[0][0];
    spAC = spC0->m[0][1];
    spA8 = spC0->m[1][0];
    spA4 = spC0->m[1][1];

    var_fv1 = MAX(1.0f, sUvMathExports->uvSqrtf(SQ(sp9C) + SQ(sp98)));
    sp9C /= var_fv1;
    sp98 /= var_fv1;

    spC0->m[0][0] = -sp98 / spB4;
    spC0->m[1][1] = -sp98 / spB4;
    spC0->m[0][1] = sp9C / spB4;
    spC0->m[1][0] = -sp9C / spB4;
    var_s3 = 0;
    for (var_s7 = 0; var_s7 < spE4->unk8; var_s7++) {
        temp_s4 = &spE4->unk0[var_s7];
        if ((arg1->unk14 & (1 << var_s7)) || (((temp_s4->unk7 & 1) != 0))) {
            var_s0 = FALSE;
        } else {
            var_s0 = TRUE;
        }

        if (!var_s0) {
            if (temp_s4->unk7 & 2) {
                var_s3++;
                temp_s2 = spE4->unk0[var_s7].unk6 - spE4->unk0[var_s7 + 1].unk6;
                for (j = 0; j < temp_s2; j++) {
                    sUvFMtxExports->uvGfxMtxFViewPop();
                    var_s3--;
                }
                continue;
            }
        }
        if (var_s7 == 0) {
            sUvFMtxExports->uvMat4ApplySharedInverseTranslation(&sp54, (u32) arg1->unk1C + var_s7 * sizeof(Mtx4F));
            sUvFMtxExports->uvGfxMtxViewLoad(&sp54, 3);
        } else {
            sUvFMtxExports->uvGfxMtxViewLoad((u32) arg1->unk1C + var_s7 * sizeof(Mtx4F), 1);
        }
        var_s3++;
        if (var_s0) {
            temp_s1 = temp_s4->unk4;
            j = 0;
            if (temp_s1 > 0) {
                do {
                    sUvGfxStateExports->uvGfxStateDraw(&temp_s4->stateTable[j]);
                } while (++j != temp_s1);
            }
        }

        if ((var_s7 + 1) == spE4->unk8) {
            break;
        }

        temp_s2 = spE4->unk0[var_s7].unk6 - spE4->unk0[var_s7 + 1].unk6;
        for (j = 0; j <= temp_s2; j++) {
            sUvFMtxExports->uvGfxMtxFViewPop();
            var_s3--;
        }
    }

    for (var_s7 = 0; var_s7 < var_s3; var_s7++) {
        sUvFMtxExports->uvGfxMtxFViewPop();
    }
    spC0->m[0][0] = spB0;
    spC0->m[0][1] = spAC;
    spC0->m[1][0] = spA8;
    spC0->m[1][1] = spA4;
    if (arg1->unk24 != NULL) {
        arg1->unk24(arg1->unk2C);
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
            if (func_uvdobj_rom_00403054(pointX, pointY, pointZ, object) >= 0) {
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

s32 func_uvdobj_rom_00402420(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 **arg4, f32 **arg5,
                             Vec3F **arg6) {
    char pad[0x14];
    Mtx4F *temp_s1;
    DObj *temp_s0;
    s32 sp78;
    Vec3F *temp_s0_2;
    f32 temp_fa1;
    f32 temp_ft4;
    f32 temp_ft5;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fv1_3;
    s32 var_s4;
    s32 var_v0;
    s32 var_v1;
    ParsedUVMD *temp_s2;
    ParsedUVMD *temp_v0;

    var_v1 = D_uvdobj_rom_004039EC;
    if (var_v1 == -1) {
        var_v0 = 0;
        sp78 = sUvDobjId;
    } else {
        sp78 = D_uvdobj_rom_004039EC + 1;
        var_v0 = D_uvdobj_rom_004039EC;
    }
    *D_uvdobj_rom_004039E4 = 0;
    *D_uvdobj_rom_004039F8 = 0;
    for (var_s4 = var_v0; var_s4 < sp78; var_s4++) {
        temp_s0 = &sDObjs[var_s4];
        if ((temp_s0->modelId == 0xFFFF) || !(temp_s0->unk4 & 1)) {
            continue;
        }
        temp_fv0 = temp_s0->unk10;
        temp_s1 = temp_s0->unk1C;
        temp_fv1 = temp_s1->m[3][0];
        temp_ft4 = temp_s1->m[3][1];
        temp_ft5 = temp_s1->m[3][2];

        if (((arg0 + arg3 + temp_fv0) < temp_fv1)) {
            continue;
        }

        if ((temp_fv1 < ((arg0 - arg3) - temp_fv0))) {
            continue;
        }
        if (((arg1 + arg3 + temp_fv0) < temp_ft4)) {
            continue;
        }

        if ((temp_ft4 < ((arg1 - arg3) - temp_fv0))) {
            continue;
        }

        if (((arg2 + arg3 + temp_fv0) < temp_ft5)) {
            continue;
        }

        if ((temp_ft5 < ((arg2 - arg3) - temp_fv0))
            || (sUvIntersectExports->uvIntersectSpheresOverlap(arg0, arg1, arg2, arg3, temp_fv1,
                                                                   temp_ft4, temp_ft5, temp_fv0)
                == 0)) {
            continue;
        }

        temp_s2 = uvGetLoadedFile('UVMD', temp_s0->modelId);
        *D_uvdobj_rom_004039E0 = var_s4;
        if (temp_s2->unk5 & 0x76) {
            func_uvdobj_rom_00402D68(arg0, arg1, arg2, arg3, temp_s0);
            if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
                break;
            }
            continue;
        }

        D_uvdobj_rom_004039D4[*D_uvdobj_rom_004039E4] = *D_uvdobj_rom_004039E0;
        temp_s0_2 = &D_uvdobj_rom_004039D8[*D_uvdobj_rom_004039E4];
        temp_s0_2->x = arg0 - temp_s1->m[3][0];
        temp_s0_2->y = arg1 - temp_s1->m[3][1];
        temp_s0_2->z = arg2 - temp_s1->m[3][2];
        sUvFVecExports->uvVec3FNormalize(temp_s0_2, temp_s0_2);
        temp_fv1_3 = (temp_s2->unkC
                      - sUvMathExports->uvSqrtf(SQ(temp_s0_2->x) + SQ(temp_s0_2->y) + SQ(temp_s0_2->z)))
                     / arg3;
        if (temp_fv1_3 < 0.0f) {
            D_uvdobj_rom_004039D0[*D_uvdobj_rom_004039E4] = temp_fv1_3;
        } else {
            D_uvdobj_rom_004039D0[*D_uvdobj_rom_004039E4] = 0.0f;
        }
        D_uvdobj_rom_004039DC[*D_uvdobj_rom_004039E4] |= 1;
        *D_uvdobj_rom_004039E4 += 1;
        if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
            break;
        }
    }
    if (*D_uvdobj_rom_004039E4 != 0) {
        *arg4 = D_uvdobj_rom_004039D4;
        *arg5 = D_uvdobj_rom_004039D0;
        *arg6 = D_uvdobj_rom_004039D8;
    }
    return *D_uvdobj_rom_004039E4;
}

s32 func_uvdobj_rom_00402870(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 **arg6,
                             f32 **arg7, Vec3F **arg8) {
    DObj *temp_s0;
    f32 temp_fs0;
    f32 temp_fs1;
    ParsedUVMD *uvmd;
    f32 spBC;
    f32 temp_fs2;
    f32 temp_fs3;
    s32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    u16 temp_v0;
    s32 var_s0;
    s32 var_s1;
    s32 sp88;

    *D_uvdobj_rom_004039E4 = 0;
    if ((arg0 == arg3) && (arg1 == arg4) && (arg2 == arg5)) {
        temp_v0 = uvDobjFindObjectContainingWorldPoint(arg0, arg1, arg2);
        if (temp_v0 == 0xFFFF) {
            *arg6 = NULL;
            *arg7 = NULL;
            *arg8 = NULL;
            return 0;
        }
        *D_uvdobj_rom_004039D4 = temp_v0;
        *D_uvdobj_rom_004039D0 = 0.0f;
        D_uvdobj_rom_004039D8->x = 0.0f;
        D_uvdobj_rom_004039D8->y = 0.0f;
        D_uvdobj_rom_004039D8->z = 1.0f;
        *arg6 = D_uvdobj_rom_004039D4;
        *arg7 = D_uvdobj_rom_004039D0;
        *arg8 = D_uvdobj_rom_004039D8;
        return 1;
    }
    if (D_uvdobj_rom_004039EC == -1) {
        var_s0 = 0;
        spB0 = sUvDobjId;
    } else {
        spB0 = D_uvdobj_rom_004039EC + 1;
        var_s0 = D_uvdobj_rom_004039EC;
    }
    sp88 = spB0 - var_s0;
    if (sp88 >= 6) {
        temp_fs0 = arg3 - arg0;
        temp_fs1 = arg4 - arg1;
        temp_fs2 = arg5 - arg2;
        spA0 = sUvMathExports->uvSqrtf(SQ(temp_fs0) + SQ(temp_fs1) + SQ(temp_fs2)) * 0.5f;
        spAC = (0.5f * temp_fs0) + arg0;
        spA8 = (0.5f * temp_fs1) + arg1;
        spA4 = (0.5f * temp_fs2) + arg2;
    }
    for (var_s1 = var_s0; var_s1 < spB0; var_s1++) {
        temp_s0 = &sDObjs[var_s1];
        if ((temp_s0->modelId == 0xFFFF) || !(temp_s0->unk4 & 1)) {
            continue;
        }

        temp_fs0 = temp_s0->unk10;
        temp_fs1 = temp_s0->unk1C->m[3][0];
        temp_fs2 = temp_s0->unk1C->m[3][1];
        temp_fs3 = temp_s0->unk1C->m[3][2];
        if (((temp_fs1 + temp_fs0) < MIN(arg0, arg3))) {
            continue;
        }

        if ((MAX(arg0, arg3) < (temp_fs1 - temp_fs0))) {
            continue;
        }

        if (((temp_fs2 + temp_fs0) < MIN(arg1, arg4))) {
            continue;
        }

        if ((MAX(arg1, arg4) < (temp_fs2 - temp_fs0))) {
            continue;
        }

        if (((temp_fs3 + temp_fs0) < MIN(arg2, arg5))) {
            continue;
        }

        if ((MAX(arg2, arg5) < (temp_fs3 - temp_fs0))) {
            continue;
        }
        if (((sp88 < 6)
             || (sUvIntersectExports->uvIntersectSpheresOverlap(spAC, spA8, spA4, spA0, temp_fs1,
                                                                    temp_fs2, temp_fs3, temp_fs0)
                 != 0))) {
            if ((sUvIntersectExports->uvIntersectSegmentSphereFraction(
                     arg0, arg1, arg2, arg3, arg4, arg5, temp_fs1, temp_fs2, temp_fs3, temp_fs0, &spBC)
                 == 0)) {
                continue;
            }
            uvmd = uvGetLoadedFile('UVMD', temp_s0->modelId);
            if (!(uvmd->unk5 & 6)) {
                continue;
            }

            *D_uvdobj_rom_004039E0 = var_s1;
            func_uvdobj_rom_004032DC(arg0, arg1, arg2, arg3, arg4, arg5, temp_s0);
        }
    }
    *arg6 = D_uvdobj_rom_004039D4;
    *arg7 = D_uvdobj_rom_004039D0;
    *arg8 = D_uvdobj_rom_004039D8;
    sUvQueryExports->uvQueryDoSorting();
    return *D_uvdobj_rom_004039E4;
}

s16 func_uvdobj_rom_00402D68(f32 arg0, f32 arg1, f32 arg2, f32 arg3, DObj *arg4) {
    char pad[0x10];
    ParsedUVMD_1 *temp_s6;
    ParsedUVMD *sp60;
    s16 temp_s1;
    s16 j;
    s16 var_s2;
    s16 i;
    s32 var_s0;
    s32 temp_s7;
    uvModelLOD *temp_v1;
    s16 unused;

    sp60 = uvGetLoadedFile('UVMD', arg4->modelId);
    temp_s6 = sp60->unk0;
    unused = -1;
    temp_s7 = temp_s6->unk8;
    sUvModelExports->uvModelResetMatrixStack();
    var_s2 = 0;
    for (i = 0; i < temp_s7; i++) {
        if (*D_uvdobj_rom_004039E4 >= sUvQueryExports->uvQueryGetRecordCapacity()) {
            return sUvQueryExports->uvQueryGetRecordCapacity();
        }
        temp_v1 = &temp_s6->unk0[i];

        if ((arg4->unk14 & (1 << i)) || (temp_v1->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (i != D_uvdobj_rom_004039F0))) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if ((var_s0 != 0) || !(temp_v1->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix((u32) arg4->unk1C + i * sizeof(Mtx4F));
            var_s2++;
            if (var_s0 != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (i << 0x18);
                unused += sUvModelExports->func_uvmodel_rom_004006B4(
                    arg0, arg1, arg2, arg3, sUvModelExports->uvModelGetCurrentMatrix(),
                    &temp_s6->unk0[i], sp60);
            }
            if (i == (temp_s7 - 1)) {
                break;
            }

            temp_s1 = temp_s6->unk0[i].unk6 - temp_s6->unk0[i + 1].unk6;
            // clang-format off
            for (j = 0; j <= temp_s1; j++) { \
                sUvModelExports->uvModelPopMatrix(); \
                var_s2 -= 1; \
            } // clang-format on
        }
    }
    for (i = 0; i < var_s2; i++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1;
}

s16 func_uvdobj_rom_00403054(f32 arg0, f32 arg1, f32 arg2, DObj *arg3) {
    s16 temp_s1;
    s16 temp_v0;
    s16 j;
    s16 var_s2;
    s16 i;
    s32 temp_s5;
    s32 var_s0;
    ParsedUVMD_1 *temp_s6;
    s32 temp_s7;
    void *temp_v0_2;
    uvModelLOD *temp_v1;
    ParsedUVMD *uvmd = uvGetLoadedFile('UVMD', arg3->modelId);

    temp_s6 = uvmd->unk0;
    temp_s7 = temp_s6->unk8;
    sUvModelExports->uvModelResetMatrixStack();
    var_s2 = 0;
    for (i = 0; i < temp_s7; i++) {
        temp_v1 = &temp_s6->unk0[i];
        if ((arg3->unk14 & (1 << i)) || (temp_v1->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (i != D_uvdobj_rom_004039F0))) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if ((var_s0 != 0) || !(temp_v1->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix(&arg3->unk1C[i]);
            var_s2++;
            if (var_s0 != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (i << 0x18);
                temp_v0 = sUvModelExports->uvModelTestWorldPointInLodBounds(
                    arg0, arg1, arg2, sUvModelExports->uvModelGetCurrentMatrix(), &temp_s6->unk0[i]);
                if (temp_v0 >= 0) {
                    return temp_v0;
                }
            }
            if ((i + 1) == temp_s7) {
                break;
            }
            temp_s1 = temp_s6->unk0[i].unk6 - temp_s6->unk0[i + 1].unk6;
            // clang-format off
            for (j = 0; j <= temp_s1; j++) { \
                sUvModelExports->uvModelPopMatrix(); \
                var_s2--; \
            } // clang-format on
            continue;
        }
    }
    for (i = 0; i < var_s2; i++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1;
}

s16 func_uvdobj_rom_004032DC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, DObj *arg6) {
    char pad[0x10];
    ParsedUVMD *sp8C;
    ParsedUVMD *temp_v0;
    ParsedUVMD_1 *temp_s6;
    s16 temp_s1;
    s16 j;
    s16 var_s2;
    s16 i;
    s32 var_s0;
    s32 temp_s7;
    uvModelLOD *temp_v0_2;
    uvModelLOD *temp_v1;

    temp_v0 = uvGetLoadedFile('UVMD', arg6->modelId);
    sp8C = temp_v0;
    temp_s6 = temp_v0->unk0;
    temp_s7 = temp_s6->unk8;
    sUvModelExports->uvModelResetMatrixStack();
    var_s2 = 0;
    for (i = 0; i < temp_s7; i++) {
        temp_v1 = &temp_s6->unk0[i];
        if ((arg6->unk14 & (1 << i)) || (temp_v1->unk7 & 1)
            || (((D_uvdobj_rom_004039F0 != -1)) && (i != D_uvdobj_rom_004039F0))) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if ((var_s0 != 0) || !(temp_v1->unk7 & 2)) {
            sUvModelExports->uvModelPushMatrix(&arg6->unk1C[i]);
            var_s2 += 1;
            if (var_s0 != 0) {
                *D_uvdobj_rom_004039E0 = (*D_uvdobj_rom_004039E0 & 0xFFFFFF) | (i << 0x18);
                sUvModelExports->func_uvmodel_rom_0040199C(arg0, arg1, arg2, arg3, arg4, arg5,
                                                           sUvModelExports->uvModelGetCurrentMatrix(),
                                                           &temp_s6->unk0[i], sp8C);
            }
            if (i == (temp_s7 - 1)) {
                break;
            }
            temp_s1 = temp_s6->unk0[i].unk6 - temp_s6->unk0[i + 1].unk6;

            // clang-format off
            for (j = 0; j <= temp_s1; j++) { \
                sUvModelExports->uvModelPopMatrix(); \
                var_s2 -= 1; \
            }
            // clang-format on
        }
    }

    for (i = 0; i < var_s2; i++) {
        sUvModelExports->uvModelPopMatrix();
    }
    return -1;
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
