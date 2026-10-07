// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

typedef struct PfxVtxInfo_s {
    /* 0x00 */ s16 unk0;                            /* inferred */
    /* 0x02 */ s16 unk2;                            /* inferred */
    /* 0x04 */ s16 unk4;                            /* inferred */
    /* 0x06 */ s16 unk6;                            /* inferred */
    /* 0x08 */ s16 unk8;                            /* inferred */
    /* 0x0A */ s16 unkA;                            /* inferred */
} PfxVtxInfo;  


// exports
extern UvFMtx_Rom_Exports* D_uvpfx_rom_00405BB0;
extern UvFVec_Rom_Exports* D_uvpfx_rom_00405BB4;
extern UvMath_Exports* D_uvpfx_rom_00405BC0;
extern UvDGeom_Rom_Exports* D_uvpfx_rom_00405BCC;
extern UvGfxState_Rom_Exports* D_uvpfx_rom_00405BB8;
extern UvGfxMgr_Exports* D_uvpfx_rom_00405BBC;
extern UvChannel_Exports* D_uvpfx_rom_00405BC4;
extern UvCback_Exports* D_uvpfx_rom_00405BC8;
extern UvTSeq_Exports* D_uvpfx_rom_00405BD0;

// other variables
extern s32 D_uvpfx_rom_00404FAC;
extern s32 D_uvpfx_rom_00404FA4;
extern Vec3F D_uvpfx_rom_00404FB0[256];
extern UnkStruct_uvpfx_rom_00404FA0* D_uvpfx_rom_00404FA0;
extern s32 D_uvpfx_rom_00404FA8;

s32 uvPfxAcquireInactiveByKind(s32 arg0);
s32 func_uvpfx_rom_00400398(s32 arg0);
void uvPfxSetMatrix(s32 arg0, Mtx4F *arg1);
void func_uvpfx_rom_004004D0(s32 arg0, ...);
void func_uvpfx_rom_004012CC(s32 arg0, ...);
void uvPfxModuleCleanup(void);
void func_uvpfx_rom_00401888(s32 arg0, s32 arg1);
void uvPfxSetTriangleTextureOrientation(s32 arg0, f32 arg1, s32 arg2);
s32 uvPfxUpdateLifetimeState(s32 arg0);
void uvPfxAdvanceTimeAndUpdate(f32 arg0);
void uvPfxDrawActiveEffects(s32 arg0);
void uvPfxRestart(s32 arg0);
void uvPfxBeginFinalInterval(s32 arg0);
void uvPfxResetTypeTwoState(s32 arg0);
void uvPfxAdvanceDiscreteStepState(s32 arg0, f32 arg1);
void uvPfxResetTypeOneState(s32 arg0);
void uvPfxSetTypeOneScalar18(s32 arg0, f32 arg1);
void uvPfxSetTypeOneCountAndValue(s32 arg0, s32 arg1, s16 arg2);
void uvPfxAdvancePositionTrail(s32 arg0);
void func_uvpfx_rom_00404A60(Vec3F *arg0, Vec3F *arg1, Vec3F *arg2, f32 arg3, f32 arg4, PfxVtxInfo *arg5, PfxVtxInfo *arg6);
void uvPfxReservedCallback(void);
void func_uvpfx_rom_0040242C(s32 arg0, s32 arg1);
void __entrypoint_func_uvpfx_rom_400000(UvPfx_Exports *exports);
void uvPfxSetTriangleTextureOrientation(s32, f32, s32);           /* extern */
void uvPfxAttachChannelCallback(s32 arg0);
void func_uvpfx_rom_00403AC8(s32 arg0, s32 arg1);

void __entrypoint_func_uvpfx_rom_400000(UvPfx_Exports* exports) {
    s32 i;
    s32* temp_v0;

    uvUpdateFileAllocPtr(exports);
    exports->uvPfxModuleCleanup = uvPfxModuleCleanup;
    exports->uvPfxRestart = uvPfxRestart;
    exports->uvPfxAttachChannelCallback = uvPfxAttachChannelCallback;
    exports->uvPfxBeginFinalInterval = uvPfxBeginFinalInterval;
    exports->uvPfxAcquireInactiveByKind = uvPfxAcquireInactiveByKind;
    exports->uvPfxResetTypeTwoState = uvPfxResetTypeTwoState;
    exports->func_uvpfx_rom_00400398 = func_uvpfx_rom_00400398;
    exports->uvPfxResetTypeOneState = uvPfxResetTypeOneState;
    exports->uvPfxSetMatrix = uvPfxSetMatrix;
    exports->uvPfxSetTypeOneScalar18 = uvPfxSetTypeOneScalar18;
    exports->func_uvpfx_rom_004004D0 = func_uvpfx_rom_004004D0;
    exports->uvPfxSetTypeOneCountAndValue = uvPfxSetTypeOneCountAndValue;
    exports->func_uvpfx_rom_004012CC = func_uvpfx_rom_004012CC;
    exports->uvPfxUpdateLifetimeState = uvPfxUpdateLifetimeState;
    exports->uvPfxAdvanceTimeAndUpdate = uvPfxAdvanceTimeAndUpdate;
    exports->uvPfxDrawActiveEffects = uvPfxDrawActiveEffects;
    exports->D_uvpfx_rom_00404FA0 = &D_uvpfx_rom_00404FA0;
    exports->D_uvpfx_rom_00404FA4 = &D_uvpfx_rom_00404FA4;
    exports->D_uvpfx_rom_00404FA8 = &D_uvpfx_rom_00404FA8;
    exports->D_uvpfx_rom_00404FAC = &D_uvpfx_rom_00404FAC;
    D_uvpfx_rom_00404FA8 = 0;
    temp_v0 = uvGetSystemProp(0x13);
    if (temp_v0 == NULL) {
        D_uvpfx_rom_00404FA4 = 0x100;
    } else {
        // clang-format off
        if (*temp_v0 != 0) { D_uvpfx_rom_00404FA4 = *temp_v0;} else {    D_uvpfx_rom_00404FA4 = 0x100; }
        // clang-format on
    }
    D_uvpfx_rom_00404FA0 = _uvMemAllocAlign8(D_uvpfx_rom_00404FA4 * 0xC);
    for (i = 0; i < D_uvpfx_rom_00404FA4; i++) {
        D_uvpfx_rom_00404FA0[i].unk0 = 0;
    }
    D_uvpfx_rom_00405BB0 = uvLoadModule('FMTX');
    D_uvpfx_rom_00405BB4 = uvLoadModule('FVEC');
    D_uvpfx_rom_00405BC0 = uvLoadModule('MATH');
    D_uvpfx_rom_00405BCC = uvLoadModule('DGEO');
    D_uvpfx_rom_00405BB8 = uvLoadModule('STAT');
    D_uvpfx_rom_00405BBC = uvLoadModule('GMGR');
    D_uvpfx_rom_00405BC4 = uvLoadModule('CHAN');
    D_uvpfx_rom_00405BC8 = uvLoadModule('CBCK');
    D_uvpfx_rom_00405BD0 = uvLoadModule('TSEQ');
}

#line 110 "src/modules/uvpfx_rom.c"
/* Attach particle rendering to channel property six at priority 0x65. */
void uvPfxAttachChannelCallback(s32 channel) {
    CallbackList* callbackList;

    D_uvpfx_rom_00405BC4->uvChannelGetProperties(channel, 6, &callbackList, 0);
    D_uvpfx_rom_00405BC8->uvAddCallback(callbackList, uvPfxDrawActiveEffects, NULL, 0x65);
}
#line 116 "src/modules/uvpfx_rom.c"

extern f32 D_uvpfx_rom_00404D40;
#line 118 "src/modules/uvpfx_rom.c"
/* Claim the first inactive matching effect, reset its type-specific state
 * and return its index. Return -1 when no matching inactive effect exists. */
s32 uvPfxAcquireInactiveByKind(s32 kind) {
    s32 i;
    s32 indexFound;
    UnkStruct_uvpfx_rom_00404FA0* unused;
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;

    indexFound = -1;
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        definition = D_uvpfx_rom_00404FA0[i].unk0;
        state = D_uvpfx_rom_00404FA0[i].unk4;
        if ((kind == definition->unk2) && (state->unk24 == 0)) {
            state->unk24 = -1;
            state->unkC = D_uvpfx_rom_00404D40 /* 1000000.0f */;
            indexFound = i;
            break;
        } 
        
    }
    if (indexFound < 0) {
        return -1;
    }
    definition = D_uvpfx_rom_00404FA0[indexFound].unk0;
    if (definition->unk4 == 1) {
        uvPfxResetTypeOneState(indexFound);
    } else {
        uvPfxResetTypeTwoState(indexFound);
    }
    return indexFound;
}
#line 148 "src/modules/uvpfx_rom.c"

extern f32 D_uvpfx_rom_00404D44;
s32 func_uvpfx_rom_00400398(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0_unk0 *a1;
    s32 sp28;
    s32 var_a3;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *temp_v1;
    f32 var_fv1;
    s32 i;

    var_a3 = -1;
    var_fv1 = D_uvpfx_rom_00404D44 /* -2000000.0f */;
    
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        a1 = D_uvpfx_rom_00404FA0[i].unk0;
        temp_v1 = D_uvpfx_rom_00404FA0[i].unk4;
        if (arg0 == a1->unk2) {
            if (var_fv1 < temp_v1->unk8) {
                var_fv1 = temp_v1->unk8;
                sp28 = i;
            }
            if (temp_v1->unk24 == 0) {
                var_a3 = i;
            }
        }
    }
    if (var_a3 < 0) {
        var_a3 = sp28;
    }
    
    a1 = D_uvpfx_rom_00404FA0[var_a3].unk0;
    if (a1->unk4 == 1) {
        uvPfxResetTypeOneState(var_a3);
    } else {
        uvPfxResetTypeTwoState(var_a3);
    }
    return var_a3;
}

#line 187 "src/modules/uvpfx_rom.c"
/* Copy the supplied matrix into the selected effect state. Index and state
 * validity remain with the caller. */
void uvPfxSetMatrix(s32 effectId, Mtx4F* matrix) {
    UnkStruct_uvpfx_rom_00404FA0_unk4* state = D_uvpfx_rom_00404FA0[effectId].unk4;
    D_uvpfx_rom_00405BB0->uvMat4FCopy(&state->unk80, matrix);
}
#line 191 "src/modules/uvpfx_rom.c"

// Requires the entry point match
#ifdef NEEDS_ENTRYPOINT
void func_uvpfx_rom_004004D0(s32 arg0, ...) {
    va_list args;
    UnkStruct_uvpfx_rom_00404FA0 *temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *temp_s3;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *temp_s1;
    f32 var_fa0;
    f32 var_fv0;
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_a1;
    ParsedUVTX* var_v1_3;
    s32 sp3C;
    UnkStruct_uvpfx_rom_00404FA0_unk28 *temp_s5;
   
    temp_s3 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_s1 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_s5 = temp_s3->unk28;
    va_start(args, arg0);
    
    while (TRUE) {
        temp_v0_2 = va_arg(args, s32);
        if (((temp_v0_2 & 0x2000) && (temp_s3->unk4 == 1))
            || ((temp_v0_2 & 0x4000) && (temp_s3->unk4 == 2))) {
            break;
        }

        switch (temp_v0_2) { /* irregular */
            case 0x1001:
                temp_s1->unk10 = va_arg(args, f64);
                break;
            case 0x1019:
                temp_s1->unk7C = va_arg(args, f64);
                break;
            case 0x1002:
                temp_s1->unk4 = va_arg(args, f64);
                break;
            case 0x1014:
                temp_s1->unk2A = va_arg(args, s32);
                break;
            case 0x1013:
                temp_a1 =  (s16)(va_arg(args, s16*)); // TODO: This is wrong...
                if (temp_a1 != 0xFF) {
                    var_v1_3 = NULL;
                    temp_s1->unk28 = D_uvpfx_rom_00405BD0->uvTexSeqFindFree();
                    if (temp_s1->unk28 != 0xFF) {
                        D_uvpfx_rom_00405BD0->uvTexSeqModel(temp_s1->unk28, temp_a1);
                        sp3C = D_uvpfx_rom_00405BD0->uvTexSeqGetCurFrameTexture((s32) temp_s1->unk28);
                    }
                    if (sp3C != 0xFFF) {
                        var_v1_3 = uvLoadFile('UVTX', sp3C);
                    }
                    if (var_v1_3 != NULL) {
                        temp_s1->unk2C = 0xFFF;
                        temp_s1->unk2E = (u16) var_v1_3->width;
                        temp_s1->unk30 = (u16) var_v1_3->height;
                        func_uvpfx_rom_00401888(arg0, 0);
                    }
                } else {
                    temp_s1->unk28 = 0xFF;
                }
                break;
            case 0x1007:
                temp_s1->unk1C = va_arg(args, f64);
                break;
            case 0x1008:
                temp_s1->unk2C = va_arg(args, s32);
                if (temp_s1->unk2C != 0xFFF) {
                    var_v1_3 = uvLoadFile('UVTX', temp_s1->unk2C);
                    if (var_v1_3 != NULL) {
                        temp_s1->unk2E = (u16) var_v1_3->width;
                        temp_s1->unk30 = (u16) var_v1_3->height;
                        func_uvpfx_rom_00401888(arg0, 0);
                    }
                    temp_s1->unk28 = 0xFF;
                }
                break;
            case 0x1015:
                func_uvpfx_rom_00401888(arg0, va_arg(args, s32));
                break;
            case 0x1003:
                D_uvpfx_rom_00405BB4->uvVec3FSet(&temp_s1->unk70, va_arg(args, f64),
                                                 va_arg(args, f64), va_arg(args, f64));
                if (temp_s1->unk70.y < temp_s1->unk70.x) {
                    var_fv0 = temp_s1->unk70.x;
                } else {
                    var_fv0 = temp_s1->unk70.y;
                }
                if (var_fv0 < temp_s1->unk70.z) {
                    var_fa0 = temp_s1->unk70.z;
                } else {
                    var_fa0 = var_fv0;
                }
                temp_s3->unk38 = (temp_s3->unk34 * var_fa0 * 0.5f);
                break;
            case 0x1025:
                D_uvpfx_rom_00405BB4->uvVec3FSet(&temp_s1->unkC0, va_arg(args, f64), va_arg(args, f64), va_arg(args, f64));
                break;
            case 0x2004:
                temp_s3->unk1E = va_arg(args, s32);
                break;
            case 0x1005:
                temp_s3->unk16 = ((f32)va_arg(args, f64) * 255.0f);
                temp_s3->unk18 = ((f32)va_arg(args, f64)  * 255.0f);
                temp_s3->unk1A = ((f32)va_arg(args, f64) * 255.0f);
                temp_s3->unk1C = ((f32)va_arg(args, f64) * 255.0f);
                break;
            case 0x4026:
                if (temp_s3->unk4 == 1) {
                    temp_s5->unkE = ((f32)va_arg(args, f64) * 255.0f);
                    temp_s5->unk10 = ((f32)va_arg(args, f64) * 255.0f);
                    temp_s5->unk12 = ((f32)va_arg(args, f64) * 255.0f);
                    temp_s5->unk14 = ((f32)va_arg(args, f64) * 255.0f);
                } else {
                    f32 unused1 = va_arg(args, f64);
                    f32 unused2 = va_arg(args, f64);
                    f32 unused3 = va_arg(args, f64);
                    f32 unused4 = va_arg(args, f64);
                }
                break;
            case 0x1010:
                temp_s1->unk80.m[3][0] = va_arg(args, f64);
                temp_s1->unk80.m[3][1] = va_arg(args, f64);
                temp_s1->unk80.m[3][2] = va_arg(args, f64);
                break;
            case 0x1020:
                temp_s1->unk0 = va_arg(args, s32);
                break;
            case 0x1022:
                temp_s3->unk12 = (f32)va_arg(args, f64);
                break;
            case 0x1023:
                temp_s3->unk14 = va_arg(args, s32);
                break;
            case 0x1024:
                if (va_arg(args, s32) != 0) {
                    temp_s3->unk8 = (s32) (temp_s3->unk8 | 0x400000);
                    temp_s3->unkC = (s32) (temp_s3->unkC & 0xFFBFFFFF);
                } else {
                    temp_s3->unkC = (s32) (temp_s3->unkC | 0x400000);
                    temp_s3->unk8 = (s32) (temp_s3->unk8 & 0xFFBFFFFF);
                }
                break;
            case 0x1026:
                if (va_arg(args, s32) != 0) {
                    temp_s3->unk8 = (s32) (temp_s3->unk8 | 0x200000);
                    temp_s3->unkC = (s32) (temp_s3->unkC & 0xFFDFFFFF);
                } else {
                    temp_s3->unkC = (s32) (temp_s3->unkC | 0x200000);
                    temp_s3->unk8 = (s32) (temp_s3->unk8 & 0xFFDFFFFF);
                }
                break;
            case 0x4027:
                var_fv0 = va_arg(args, f64);
                temp_s5->unkA = (var_fv0 * 100.0f);
                break;
            case 0x1027:
                temp_s1->unk6E = va_arg(args, s32);
                break;
            case 0x1028:
                temp_s1->unkE4 = va_arg(args, s32);
                temp_s1->unkE8 = va_arg(args, s32);
                break;
            case 0x4029:
                var_fv0 = va_arg(args, f64);
                temp_s5->unkC = (var_fv0 * 100.0f);
                break;
            case 0x4030:
                temp_s1->unk18 = (s16)va_arg(args, s32);
                break;
            case 0x4033:
                temp_s1->unkD8 = (f32)va_arg(args, f64);
                temp_s1->unkDC = (f32)va_arg(args, f64);
                temp_s1->unkE0 = (f32)va_arg(args, f64);
                break;
            case 0:
                return;
            default:
                return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_004004D0.s")
#endif

#ifdef NEEDS_RODATA
void func_uvpfx_rom_004012CC(s32 arg0, ...) {
    va_list args;
    UnkStruct_uvpfx_rom_00404FA0 *temp_v1;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk28 *temp_a1;
    UnkStruct_uvpfx_rom_00404FA0_unk2C *temp_a2;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *temp_a0;
    s16 prop;

    temp_v0 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_a0 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_a1 = temp_v0->unk28;
    temp_a2 = temp_v0->unk2C;
    va_start(args, arg0);

    while (TRUE) {
        prop = (s32) va_arg(args, s32);
        switch (prop) { /* irregular */
            case 0x1001:
                *va_arg(args, f32 *) = temp_a0->unk10;
                break;
            case 0x1019:
                *va_arg(args, f32 *) = temp_a0->unk7C;
                break;
            case 0x1002:
                *va_arg(args, f32 *) = temp_a0->unk4;
                break;
            case 0x1013:
                *va_arg(args, s32 *) = temp_a0->unk28;
                break;
            case 0x1014:
                *va_arg(args, s32 *) = temp_a0->unk2A;
                break;
            case 0x1007:
                *va_arg(args, f32 *) = temp_a0->unk1C;
                break;
            case 0x1008:
                *va_arg(args, s32 *) = (s32) temp_a0->unk2C;
                break;
            case 0x1003:
                *va_arg(args, f32 *) = temp_a0->unk70.x;
                *va_arg(args, f32 *) = temp_a0->unk70.y;
                *va_arg(args, f32 *) = temp_a0->unk70.z;
                break;
            case 0x2004:
                *va_arg(args, s16 *) = temp_v0->unk1E;
                break;
            case 0x1005:
                *va_arg(args, f32 *) = (f32) temp_v0->unk16 / 255.0f;
                *va_arg(args, f32 *) = (f32) temp_v0->unk18 / 255.0f;
                *va_arg(args, f32 *) = (f32) temp_v0->unk1A / 255.0f;
                *va_arg(args, f32 *) = (f32) temp_v0->unk1C / 255.0f;
                break;
            case 0x4026:
                if (temp_v0->unk4 == 1) {
                    *va_arg(args, f32 *) = (f32) temp_a1->unkE / 255.0f;
                    *va_arg(args, f32 *) = (f32) temp_a1->unk10 / 255.0f;
                    *va_arg(args, f32 *) = (f32) temp_a1->unk12 / 255.0f;
                    *va_arg(args, f32 *) = (f32) temp_a1->unk14 / 255.0f;
                } else {
                    *va_arg(args, f32 *) = 1.0f;
                    *va_arg(args, f32 *) = 1.0f;
                    *va_arg(args, f32 *) = 1.0f;
                    *va_arg(args, f32 *) = 1.0f;
                }
                break;
            case 0x1010:
                *va_arg(args, f32 *) = temp_a0->unk80.m[3][0];
                *va_arg(args, f32 *) = temp_a0->unk80.m[3][1];
                *va_arg(args, f32 *) = temp_a0->unk80.m[3][2];
                break;
            case 0x1011:
                *va_arg(args, s32 *) = temp_a0->unk24 > 0;
                break;
            case 0x1012:
                *va_arg(args, f32*)  = temp_a2->unkC;
                break;
            case 0x1022:
                *va_arg(args, f32 *) = temp_v0->unk12;
                break;
            case 0x1023:
                *va_arg(args, s8 *) = temp_v0->unk14;
                break;
            case 0x1024:
                *va_arg(args, s16 *) = temp_v0->unk8 & 0x400000;
                break;
            case 0x1026:
                *va_arg(args, s16 *) = temp_v0->unk8 & 0x200000;
                break;
            case 0x4027:
                *va_arg(args, f32 *) = (f32) temp_a1->unkA * 0.01f;
                break;
            case 0x4029:
                *va_arg(args, f32 *) = temp_a1->unkC * 0.01f;
                break;
            case 0x4030:
                *va_arg(args, s16 *) = temp_a0->unk18;
                break;
            case 0x4033:
                *va_arg(args, f32 *) = temp_a0->unkD8;
                *va_arg(args, f32 *) = temp_a0->unkDC;
                *va_arg(args, f32 *) = temp_a0->unkE0;
                break;
            case 0:
                return;
            default:
                return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_004012CC.s")
#endif

#line 494 "src/modules/uvpfx_rom.c"
/* Unload the eight original particle-module dependencies in order. */
void uvPfxModuleCleanup(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('MATH');
    uvUnloadModule('DGEO');
    uvUnloadModule('STAT');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('TSEQ');
}
#line 504 "src/modules/uvpfx_rom.c"

#define PI 3.1415927f

#ifdef NEEDS_RODATA
void func_uvpfx_rom_00401888(s32 arg0, s32 arg1) {
    Vec3F* var_s0;
    f32 temp_fs1;
    f32 var_fs0;
    s32 i;

    var_fs0 = 0.0f;
    for (i = 0; i < 5; i++) {
        if (arg1 != 0) {
            var_fs0 = 2.0f * D_uvpfx_rom_00405BC0->uvRandFLcg() * PI;
        }
        uvPfxSetTriangleTextureOrientation(i, var_fs0, arg0);
    }
    for (i = 0; i < 256; i++) {
        D_uvpfx_rom_00404FB0[i].x = 2.0f * (D_uvpfx_rom_00405BC0->uvRandFLcg() - 0.5f);
        D_uvpfx_rom_00404FB0[i].y = 2.0f * (D_uvpfx_rom_00405BC0->uvRandFLcg() - 0.5f);
        D_uvpfx_rom_00404FB0[i].z = (f32) (2.0f * (D_uvpfx_rom_00405BC0->uvRandFLcg() - 0.5f));
    } 
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_00401888.s")
#endif

#line 531 "src/modules/uvpfx_rom.c"
/* Rotate the original triangle about Z, offset its coordinates by 0.5,
 * scale by the texture dimension and store fixed-point coordinates for one slot. */
void uvPfxSetTriangleTextureOrientation(s32 slot, f32 angle, s32 effectId) {
    f32 first[2];
    f32 second[2];
    f32 third[2];
    Mtx4F matrix;
    Vec3F point;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;

    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    D_uvpfx_rom_00405BB0->uvMat4SetIdentity(&matrix);
    D_uvpfx_rom_00405BB0->uvMat4RotateAxis(&matrix, angle, 0x7A);
    D_uvpfx_rom_00405BB4->uvVec3FSet(&point, 0.0f, 1.0f, 0.0f);
    D_uvpfx_rom_00405BB0->uvMat4TransformDirection(&matrix, &point, &point);
    first[0] = point.x + 0.5f;
    first[1] = point.y + 0.5f;
    D_uvpfx_rom_00405BB4->uvVec3FSet(&point, -0.866f, -0.5f, 0.0f);
    D_uvpfx_rom_00405BB0->uvMat4TransformDirection(&matrix, &point, &point);
    second[0] = point.x + 0.5f;
    second[1] = point.y + 0.5f;
    D_uvpfx_rom_00405BB4->uvVec3FSet(&point, 0.866f, -0.5f, 0.0f);
    D_uvpfx_rom_00405BB0->uvMat4TransformDirection(&matrix, &point, &point);
    third[0] = point.x + 0.5f;
    third[1] = point.y + 0.5f;
    state->unk32[slot][0] = ((s16) (first[0] * state->unk2E) << 5);
    state->unk32[slot][1] = ((s16) (first[1] * state->unk2E) << 5);
    state->unk32[slot][2] = ((s16) (second[0] * state->unk2E) << 5);
    state->unk32[slot][3] = ((s16) (second[1] * state->unk2E) << 5);
    state->unk32[slot][4] = ((s16) (third[0] * state->unk2E) << 5);
    state->unk32[slot][5] = ((s16) (third[1] * state->unk2E) << 5);
}
#line 561 "src/modules/uvpfx_rom.c"

extern f32 D_uvpfx_rom_00404F40;
#line 563 "src/modules/uvpfx_rom.c"
/* Compute elapsed effect time, preserve pending/expired state transitions
 * and update fade alpha during the final interval. Return whether to update. */
s32 uvPfxUpdateLifetimeState(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v1;
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;
    f32 fadeTime;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v1_2;
    s32 shouldUpdate;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    state->unk8 = (D_uvpfx_rom_00404F40 - state->unkC) - state->unk4;
    if (state->unk8 < 0.0f) {
        state->unk24 = -1;
        shouldUpdate = 0;
    }
    else if (state->unk10 < state->unk8) {
        state->unk24 = 0;
        shouldUpdate = 0;
    }
    else if (state->unk24 == 3) {
        fadeTime = (state->unk8 + 1.0f) - state->unk10;
        if ((fadeTime > 0.0f) && (definition->unk14 != 0)) {
            state->unk26 = ((1.0f - fadeTime) * 254.0f);
        } else {
            state->unk26 = 0xFF;
        }
        shouldUpdate = 1;
    } else if (state->unk24 == 2) {
        state->unk24 = 3;
        shouldUpdate = 1;
    } else {
        state->unk24 = 2;
        shouldUpdate = 1;
    }
    return shouldUpdate;
}
#line 601 "src/modules/uvpfx_rom.c"

s32 uvPfxUpdateLifetimeState(s32);       /* extern */
void uvPfxAdvanceDiscreteStepState(s32, f32); /* extern */
void uvPfxAdvancePositionTrail(s32);      /* extern */
extern f32 D_uvpfx_rom_00404F40;

#line 607 "src/modules/uvpfx_rom.c"
/* Advance the shared clock, update effect lifetimes and dispatch active
 * type-one/type-two simulation. Missing definitions are skipped. */
void uvPfxAdvanceTimeAndUpdate(f32 interval) {
    s32 i;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *definition;

    D_uvpfx_rom_00404F40 += interval;
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        definition = D_uvpfx_rom_00404FA0[i].unk0;
        if (definition == NULL) {
            continue;
        }

        if (uvPfxUpdateLifetimeState(i) != 0) {
            if (definition->unk4 == 1) {
                uvPfxAdvancePositionTrail(i);
            } else if (definition->unk4 == 2) {
                uvPfxAdvanceDiscreteStepState(i, interval);
            }
        }
    }
}
#line 627 "src/modules/uvpfx_rom.c"

#line 628 "src/modules/uvpfx_rom.c"
/* Unless globally hidden, save graphics state, draw visible active effects
 * through their type-specific renderer and restore the previous values/state. */
void uvPfxDrawActiveEffects(s32 channel) {
    s32 i;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *state;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *definition;
    f32 savedFirst;
    f32 savedSecond;
    
    if (D_uvpfx_rom_00404FAC != 0) {
        return;
    }

    D_uvpfx_rom_00405BB8->uvGfxStatePush();
    D_uvpfx_rom_00405BB8->uvGfxGetFogParameters(&savedFirst, &savedSecond);
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_00401F54(0, 0.0f);
    D_uvpfx_rom_00405BB8->uvGfxResetDefaultRenderState();
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        definition = D_uvpfx_rom_00404FA0[i].unk0;
        if (definition == NULL) {
            continue;
        }

        state = D_uvpfx_rom_00404FA0[i].unk4;
        if ((state->unk24 > 0) && (state->unk0 == 0) && (definition->unk2 != -1)) {
            if (definition->unk4 == 1) {
                func_uvpfx_rom_00403AC8(i, channel);
            } else {
                func_uvpfx_rom_0040242C(i, channel);
            }
        }
    }
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_00401F54(savedFirst, savedSecond);
    D_uvpfx_rom_00405BB8->uvGfxStatePop();
}
#line 661 "src/modules/uvpfx_rom.c"

#line 662 "src/modules/uvpfx_rom.c"
/* Restart an assigned texture sequence, reset the effect time and its
 * type-specific simulation, then mark the effect pending. */
void uvPfxRestart(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;

    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    if (state->unk28 != 0xFF) {
        D_uvpfx_rom_00405BD0->uvTexSeqProps(state->unk28, TSEQ_PROP_ACTIVE(TRUE), TSEQ_PROP_CURR_FRAME(0), TSEQ_PROP_END);
    }
    state->unkC = D_uvpfx_rom_00404F40;
    if (definition->unk4 == 1) {
        uvPfxResetTypeOneState(effectId);
    } else {
        uvPfxResetTypeTwoState(effectId);
    }
    state->unk24 = -1;
}
#line 679 "src/modules/uvpfx_rom.c"

#line 680 "src/modules/uvpfx_rom.c"
/* Adjust the effect start time to the original final one-second interval. */
void uvPfxBeginFinalInterval(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;

    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    state->unkC = ((D_uvpfx_rom_00404F40 - state->unk10) + 1.0f) - state->unk4;
}
#line 686 "src/modules/uvpfx_rom.c"

#line 687 "src/modules/uvpfx_rom.c"
/* Clear original simulation counters and delay. Definition subtype nine
 * also clears each vector in the caller-sized per-effect array. */
void uvPfxResetTypeTwoState(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;
    Vec3F* vectors;
    s32 i;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    state->unk20 = 0;
    state->unk14 = 0.0f;
    state->unk4 = 0.0f;
    if (definition->unk2C->unk0 != 9) {
        return;
    }
        
    vectors = D_uvpfx_rom_00404FA0[effectId].unk8;
    for (i = 0; i < definition->unk10; i++) {
        D_uvpfx_rom_00405BB4->uvVec3FSet(&vectors[i], 0.0f, 0.0f, 0.0f);
    }
}
#line 707 "src/modules/uvpfx_rom.c"



#line 710 "src/modules/uvpfx_rom.c"
/* Quantize the configured duration into whole steps, advance active
 * state and apply its original restart rules. Preserve mode-dependent
 * minimum steps, reset marker and type-nine vector initialization. */
void uvPfxAdvanceDiscreteStepState(s32 effectId, f32 delta) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk2C* stepConfig;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;
    Vec3F* vectors;
    f32 temp_fa0;
    f32 temp_fv0;
    s16 temp_v1;
    s16 i;
    s32 stepCount;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    vectors = D_uvpfx_rom_00404FA0[effectId].unk8;
    stepConfig = definition->unk2C;

    switch (stepConfig->unk8) {                              /* irregular */
    case 0:

        if (state->unk10 < 2.0f * stepConfig->unkC) {
            state->unk10 = 2.0f * stepConfig->unkC;
        }
        break;
    case 1:
        if (state->unk10 < stepConfig->unkC) {
            state->unk10 = stepConfig->unkC;
        }
        break;
    }
    stepCount = (s32) (state->unk10 / stepConfig->unkC);
    if (stepCount <= 0) {
        stepCount = 1;
    }
    state->unk10 = (f32) stepCount * stepConfig->unkC;
    if (state->unk24 != 0) {
        if (state->unk20 >= (stepCount - 1)) {
            state->unk22 = 1;
        } else {
            state->unk22 = 0;
        }
        state->unk14 += delta;
    } else {
        state->unk2 = 1;
        return;
    }

    if (stepConfig->unkC < state->unk14) {
        state->unk20 += 1;
        state->unk14 = 0.0f;
    }
    if (state->unk2 != 0) {
        state->unk20 = 1;
        state->unk2 = 0;
        if (stepConfig->unk0 == 9) {
            for (i = 0; i < definition->unk10; i++) {
                D_uvpfx_rom_00405BB4->uvVec3FSet(&vectors[i], 0.0f, 0.0f, 0.0f);
            }
        }
        if (stepConfig->unk8 == 0) {
            state->unk14 = 0.0f - stepConfig->unkC;
        } else {
            state->unk14 = 0.0f;
        }
    }
}
#line 776 "src/modules/uvpfx_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_0040242C.s")

#line 779 "src/modules/uvpfx_rom.c"
/* Reset the original type-one index/time and zero every per-effect vector. */
void uvPfxResetTypeOneState(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;
    Vec3F* vectors;
    s32 i;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    vectors = D_uvpfx_rom_00404FA0[effectId].unk8;
    state->unk22 = -1;
    state->unk14 = 0.0f;
    
    for (i = 0; i < definition->unk28->unk0; i++) {
        D_uvpfx_rom_00405BB4->uvVec3FSet(&vectors[i], 0, 0, 0);
    }
}
#line 796 "src/modules/uvpfx_rom.c"

#line 797 "src/modules/uvpfx_rom.c"
/* Store the type-one definition scalar at offset 0x18; its role is unproven. */
void uvPfxSetTypeOneScalar18(s32 effectId, f32 value) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk28* typeOne;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    typeOne = definition->unk28;
    typeOne->unk18 = value;
}
#line 805 "src/modules/uvpfx_rom.c"

#line 806 "src/modules/uvpfx_rom.c"
/* Store the supplied word at type-one payload offset four and clamp the
 * signed count to its original upper limit. Negative counts retain behavior.
 * RE_UNKNOWN: the supplied word's ownership and address/value contract. The
 * original loader initially stores an allocated pointer at this offset and
 * the release routine frees its current contents. Trace exported setter
 * callers before interpreting the word as an ordinary scalar. */
void uvPfxSetTypeOneCountAndValue(s32 effectId, s32 value, s16 count) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* definition;
    UnkStruct_uvpfx_rom_00404FA0_unk28* typeOne;
    s16 temp_a3;

    definition = D_uvpfx_rom_00404FA0[effectId].unk0;
    typeOne = definition->unk28;
    if (count < typeOne->unk0) {
        typeOne->unk8 = count;
    } else {
        typeOne->unk8 = typeOne->unk0;
    }
    typeOne->unk4 = value;
}
#line 820 "src/modules/uvpfx_rom.c"


#line 822 "src/modules/uvpfx_rom.c"
/* Initialize or extend the position trail, shift stored points and
 * offset them by source movement and configured velocity. Retain the
 * original first-point reset and single-subtraction phase wrapping. */
void uvPfxAdvancePositionTrail(s32 effectId) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_t0;
    UnkStruct_uvpfx_rom_00404FA0_unk4* state;
    UnkStruct_uvpfx_rom_00404FA0_unk28* trailConfig;
    Vec3F* trailPoints;
    f32 delta;
    s16 i;

    delta = D_uvpfx_rom_00405BBC->uvGfxMgrGetScalarOverrideOrCurrent();
    state = D_uvpfx_rom_00404FA0[effectId].unk4;
    trailPoints = D_uvpfx_rom_00404FA0[effectId].unk8;
    trailConfig = D_uvpfx_rom_00404FA0[effectId].unk0->unk28;
    if (state->unk22 == -1) {
        state->unk22 = 0;
        state->unk20 = 0;
        state->unkCC = state->unk80.m[3][0];
        state->unkD0 = state->unk80.m[3][1];
        state->unkD4 = state->unk80.m[3][2];
        return;
    }
    if ((state->unk22 < trailConfig->unk0) && (state->unk20 == 0)) {
        state->unk22++;
    }
    state->unkCC -= state->unk80.m[3][0] - (state->unkD8 * delta);
    state->unkD0 -= state->unk80.m[3][1] - (state->unkDC * delta);
    state->unkD4 -= state->unk80.m[3][2] - (state->unkE0 * delta);

    for (i = state->unk22 - 1; i > 0; i--) {
        D_uvpfx_rom_00405BB4->uvVec3FCopy(&trailPoints[i], &trailPoints[i - 1]);
        D_uvpfx_rom_00405BB4->uvVec3FAdd(&trailPoints[i], &trailPoints[i], (Vec3F* ) &state->unkCC);
    }
    D_uvpfx_rom_00405BB4->uvVec3FSet(trailPoints, 0, 0, 0.0f);
    state->unkCC = state->unk80.m[3][0];
    state->unkD0 = state->unk80.m[3][1];
    state->unkD4 = state->unk80.m[3][2];
    state->unk14 += state->unk18;
    if ((trailConfig->unk0 - 1) <= state->unk14) {
        state->unk14 = state->unk14 - (trailConfig->unk0 - 1);
    }
}
#line 863 "src/modules/uvpfx_rom.c"


#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_00403AC8.s")

#ifdef NEEDS_RODATA
void func_uvpfx_rom_00404A60(Vec3F* arg0, Vec3F* arg1, Vec3F* arg2, f32 arg3, f32 arg4, PfxVtxInfo* arg5, PfxVtxInfo* arg6) {
    Vec3S vtxPoints[3];
    f32 temp_ft5;
    f32 temp_ft4;
    f32 temp_ft2;
    f32 temp_fa1;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_fv1;

    temp_ft4 = (arg1->x * (-0.5f * arg3));
    temp_ft5 = arg1->y * (-0.5f * arg3);
    temp_fv1 = 0.866f * arg4;
    sp50 = arg1->z * (-0.5f * arg3);
    sp4C = arg2->x * temp_fv1;
    sp48 = arg2->y * temp_fv1;
    sp44 = arg2->z * temp_fv1;
    vtxPoints[0].x = (arg0->x + (arg1->x * arg3));
    vtxPoints[0].y = (arg0->y + (arg1->y * arg3));
    vtxPoints[0].z = (arg0->z + (arg1->z * arg3));
    vtxPoints[1].x = (arg0->x + temp_ft4 + sp4C);
    vtxPoints[1].y = (arg0->y + temp_ft5 + sp48);
    vtxPoints[1].z = (arg0->z + sp50 + sp44);
    vtxPoints[2].x = ((arg0->x + temp_ft4) - sp4C);
    vtxPoints[2].y = ((arg0->y + temp_ft5) - sp48);
    vtxPoints[2].z = ((arg0->z + sp50) - sp44);

    D_uvpfx_rom_00405BBC->uvGfxSetPrimColor(arg6->unk0, arg6->unk2, arg6->unk4, arg6->unk6);
    D_uvpfx_rom_00405BCC->uvVtxBeginPoly();
    D_uvpfx_rom_00405BCC->uvVtx(vtxPoints[0].x, vtxPoints[0].y, vtxPoints[0].z, arg5->unk0, arg5->unk2, arg6->unk0, arg6->unk2, arg6->unk4, arg6->unk6);
    D_uvpfx_rom_00405BCC->uvVtx(vtxPoints[1].x, vtxPoints[1].y, vtxPoints[1].z, arg5->unk4, arg5->unk6, arg6->unk0, arg6->unk2, arg6->unk4, arg6->unk6);
    D_uvpfx_rom_00405BCC->uvVtx(vtxPoints[2].x, vtxPoints[2].y, vtxPoints[2].z, arg5->unk8, arg5->unkA, arg6->unk0, arg6->unk2, arg6->unk4, arg6->unk6);
    D_uvpfx_rom_00405BCC->uvVtxEndPoly();
}
#else
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_00404A60.s")
#endif

#line 908 "src/modules/uvpfx_rom.c"
/* Original empty callback; retain its entry point. */
void uvPfxReservedCallback(void) {

}
#line 911 "src/modules/uvpfx_rom.c"
