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

s32 func_uvpfx_rom_004002BC(s32 arg0);
s32 func_uvpfx_rom_00400398(s32 arg0);
void func_uvpfx_rom_00400488(s32 arg0, Mtx4F *arg1);
void func_uvpfx_rom_004004D0(s32 arg0, ...);
void func_uvpfx_rom_004012CC(s32 arg0, ...);
void func_uvpfx_rom_00401810(void);
void func_uvpfx_rom_00401888(s32 arg0, s32 arg1);
void func_uvpfx_rom_004019A4(s32 arg0, f32 arg1, s32 arg2);
s32 func_uvpfx_rom_00401C6C(s32 arg0);
void func_uvpfx_rom_00401D88(f32 arg0);
void func_uvpfx_rom_00401E7C(s32 arg0);
void func_uvpfx_rom_00402008(s32 arg0);
void func_uvpfx_rom_004020D4(s32 arg0);
void func_uvpfx_rom_0040211C(s32 arg0);
void func_uvpfx_rom_004021FC(s32 arg0, f32 arg1);
void func_uvpfx_rom_0040374C(s32 arg0);
void func_uvpfx_rom_0040381C(s32 arg0, f32 arg1);
void func_uvpfx_rom_00403848(s32 arg0, s32 arg1, s16 arg2);
void func_uvpfx_rom_00403898(s32 arg0);
void func_uvpfx_rom_00404A60(Vec3F *arg0, Vec3F *arg1, Vec3F *arg2, f32 arg3, f32 arg4, PfxVtxInfo *arg5, PfxVtxInfo *arg6);
void func_uvpfx_rom_00404D2C(void);
void func_uvpfx_rom_0040242C(s32 arg0, s32 arg1);
void __entrypoint_func_uvpfx_rom_400000(UvPfx_Exports *exports);
void func_uvpfx_rom_004019A4(s32, f32, s32);           /* extern */
void func_uvpfx_rom_00400264(s32 arg0);
void func_uvpfx_rom_00403AC8(s32 arg0, s32 arg1);

void __entrypoint_func_uvpfx_rom_400000(UvPfx_Exports* exports) {
    s32 i;
    s32* temp_v0;

    uvUpdateFileAllocPtr(exports);
    exports->func_uvpfx_rom_00401810 = func_uvpfx_rom_00401810;
    exports->func_uvpfx_rom_00402008 = func_uvpfx_rom_00402008;
    exports->func_uvpfx_rom_00400264 = func_uvpfx_rom_00400264;
    exports->func_uvpfx_rom_004020D4 = func_uvpfx_rom_004020D4;
    exports->func_uvpfx_rom_004002BC = func_uvpfx_rom_004002BC;
    exports->func_uvpfx_rom_0040211C = func_uvpfx_rom_0040211C;
    exports->func_uvpfx_rom_00400398 = func_uvpfx_rom_00400398;
    exports->func_uvpfx_rom_0040374C = func_uvpfx_rom_0040374C;
    exports->func_uvpfx_rom_00400488 = func_uvpfx_rom_00400488;
    exports->func_uvpfx_rom_0040381C = func_uvpfx_rom_0040381C;
    exports->func_uvpfx_rom_004004D0 = func_uvpfx_rom_004004D0;
    exports->func_uvpfx_rom_00403848 = func_uvpfx_rom_00403848;
    exports->func_uvpfx_rom_004012CC = func_uvpfx_rom_004012CC;
    exports->func_uvpfx_rom_00401C6C = func_uvpfx_rom_00401C6C;
    exports->func_uvpfx_rom_00401D88 = func_uvpfx_rom_00401D88;
    exports->func_uvpfx_rom_00401E7C = func_uvpfx_rom_00401E7C;
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

void func_uvpfx_rom_00400264(s32 arg0) {
    CallbackList* callbackList;

    D_uvpfx_rom_00405BC4->func_uvchannel_rom_00400288(arg0, 6, &callbackList, 0);
    D_uvpfx_rom_00405BC8->uvAddCallback(callbackList, func_uvpfx_rom_00401E7C, NULL, 0x65);
}

extern f32 D_uvpfx_rom_00404D40;
s32 func_uvpfx_rom_004002BC(s32 arg0) {
    s32 i;
    s32 indexFound;
    UnkStruct_uvpfx_rom_00404FA0* var_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* v1;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_a0;

    indexFound = -1;
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        v1 = D_uvpfx_rom_00404FA0[i].unk0;
        temp_a0 = D_uvpfx_rom_00404FA0[i].unk4;
        if ((arg0 == v1->unk2) && (temp_a0->unk24 == 0)) {
            temp_a0->unk24 = -1;
            temp_a0->unkC = D_uvpfx_rom_00404D40 /* 1000000.0f */;
            indexFound = i;
            break;
        } 
        
    }
    if (indexFound < 0) {
        return -1;
    }
    v1 = D_uvpfx_rom_00404FA0[indexFound].unk0; 
    if (v1->unk4 == 1) {
        func_uvpfx_rom_0040374C(indexFound);
    } else {
        func_uvpfx_rom_0040211C(indexFound);
    }
    return indexFound;
}

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
        func_uvpfx_rom_0040374C(var_a3);
    } else {
        func_uvpfx_rom_0040211C(var_a3);
    }
    return var_a3;
}

void func_uvpfx_rom_00400488(s32 arg0, Mtx4F* arg1) {
    UnkStruct_uvpfx_rom_00404FA0_unk4* v1 = D_uvpfx_rom_00404FA0[arg0].unk4;
    D_uvpfx_rom_00405BB0->uvMat4FCopy(&v1->unk80, arg1);
}

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

void func_uvpfx_rom_00401810(void) {
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('MATH');
    uvUnloadModule('DGEO');
    uvUnloadModule('STAT');
    uvUnloadModule('CHAN');
    uvUnloadModule('CBCK');
    uvUnloadModule('TSEQ');
}

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
        func_uvpfx_rom_004019A4(i, var_fs0, arg0);
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

void func_uvpfx_rom_004019A4(s32 arg0, f32 arg1, s32 arg2) {
    f32 sp88[2];
    f32 sp80[2];
    f32 sp78[2];
    Mtx4F sp38;
    Vec3F sp2C;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_s0;

    temp_s0 = D_uvpfx_rom_00404FA0[arg2].unk4;
    D_uvpfx_rom_00405BB0->uvMat4SetIdentity(&sp38);
    D_uvpfx_rom_00405BB0->uvMat4RotateAxis(&sp38, arg1, 0x7A);
    D_uvpfx_rom_00405BB4->uvVec3FSet(&sp2C, 0.0f, 1.0f, 0.0f);
    D_uvpfx_rom_00405BB0->func_uvfmtx_rom_004030FC(&sp38, &sp2C, &sp2C);
    sp88[0] = sp2C.x + 0.5f;
    sp88[1] = sp2C.y + 0.5f;
    D_uvpfx_rom_00405BB4->uvVec3FSet(&sp2C, -0.866f, -0.5f, 0.0f);
    D_uvpfx_rom_00405BB0->func_uvfmtx_rom_004030FC(&sp38, &sp2C, &sp2C);
    sp80[0] = sp2C.x + 0.5f;
    sp80[1] = sp2C.y + 0.5f;
    D_uvpfx_rom_00405BB4->uvVec3FSet(&sp2C, 0.866f, -0.5f, 0.0f);
    D_uvpfx_rom_00405BB0->func_uvfmtx_rom_004030FC(&sp38, &sp2C, &sp2C);
    sp78[0] = sp2C.x + 0.5f;
    sp78[1] = sp2C.y + 0.5f;
    temp_s0->unk32[arg0][0] = ((s16) (sp88[0] * temp_s0->unk2E) << 5);
    temp_s0->unk32[arg0][1] = ((s16) (sp88[1] * temp_s0->unk2E) << 5);
    temp_s0->unk32[arg0][2] = ((s16) (sp80[0] * temp_s0->unk2E) << 5);
    temp_s0->unk32[arg0][3] = ((s16) (sp80[1] * temp_s0->unk2E) << 5);
    temp_s0->unk32[arg0][4] = ((s16) (sp78[0] * temp_s0->unk2E) << 5);
    temp_s0->unk32[arg0][5] = ((s16) (sp78[1] * temp_s0->unk2E) << 5);
}

extern f32 D_uvpfx_rom_00404F40;
s32 func_uvpfx_rom_00401C6C(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v1;
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_a1;
    f32 temp_fa0;
    f32 temp_fv0;
    f32 temp_fv1;
    s16 temp_v1_2;
    s32 out;

    temp_v0 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_a1 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_a1->unk8 = (D_uvpfx_rom_00404F40 - temp_a1->unkC) - temp_a1->unk4;
    if (temp_a1->unk8 < 0.0f) {
        temp_a1->unk24 = -1;
        out = 0;
    }
    else if (temp_a1->unk10 < temp_a1->unk8) {
        temp_a1->unk24 = 0;
        out = 0;
    }
    else if (temp_a1->unk24 == 3) {
        temp_fa0 = (temp_a1->unk8 + 1.0f) - temp_a1->unk10;
        if ((temp_fa0 > 0.0f) && (temp_v0->unk14 != 0)) {
            temp_a1->unk26 = ((1.0f - temp_fa0) * 254.0f);
        } else {
            temp_a1->unk26 = 0xFF;
        }
        out = 1;
    } else if (temp_a1->unk24 == 2) {
        temp_a1->unk24 = 3;
        out = 1;
    } else {
        temp_a1->unk24 = 2;
        out = 1;
    }
    return out;
}

s32 func_uvpfx_rom_00401C6C(s32);       /* extern */
void func_uvpfx_rom_004021FC(s32, f32); /* extern */
void func_uvpfx_rom_00403898(s32);      /* extern */
extern f32 D_uvpfx_rom_00404F40;

void func_uvpfx_rom_00401D88(f32 arg0) {
    s32 i;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *temp_s0;

    D_uvpfx_rom_00404F40 += arg0;
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        temp_s0 = D_uvpfx_rom_00404FA0[i].unk0;
        if (temp_s0 == NULL) {
            continue;
        }

        if (func_uvpfx_rom_00401C6C(i) != 0) {
            if (temp_s0->unk4 == 1) {
                func_uvpfx_rom_00403898(i);
            } else if (temp_s0->unk4 == 2) {
                func_uvpfx_rom_004021FC(i, arg0);
            }
        }
    }
}

void func_uvpfx_rom_00401E7C(s32 arg0) {
    s32 i;
    UnkStruct_uvpfx_rom_00404FA0_unk4 *temp_a0;
    UnkStruct_uvpfx_rom_00404FA0_unk0 *temp_v0;
    f32 sp40;
    f32 sp3C;
    
    if (D_uvpfx_rom_00404FAC != 0) {
        return;
    }

    D_uvpfx_rom_00405BB8->uvGfxStatePush();
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_004020DC(&sp40, &sp3C);
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_00401F54(0, 0.0f);
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_00401CE8();
    for (i = 0; i < D_uvpfx_rom_00404FA8; i++) {
        temp_v0 = D_uvpfx_rom_00404FA0[i].unk0;
        if (temp_v0 == NULL) {
            continue;
        }

        temp_a0 = D_uvpfx_rom_00404FA0[i].unk4;
        if ((temp_a0->unk24 > 0) && (temp_a0->unk0 == 0) && (temp_v0->unk2 != -1)) {
            if (temp_v0->unk4 == 1) {
                func_uvpfx_rom_00403AC8(i, arg0);
            } else {
                func_uvpfx_rom_0040242C(i, arg0);
            }
        }
    }
    D_uvpfx_rom_00405BB8->func_uvgfxstate_rom_00401F54(sp40, sp3C);
    D_uvpfx_rom_00405BB8->uvGfxStatePop();
}

void func_uvpfx_rom_00402008(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_t0;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_v1;

    temp_v1 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_t0 = D_uvpfx_rom_00404FA0[arg0].unk0;
    if (temp_v1->unk28 != 0xFF) {
        D_uvpfx_rom_00405BD0->uvTexSeqProps(temp_v1->unk28, TSEQ_PROP_ACTIVE(TRUE), TSEQ_PROP_CURR_FRAME(0), TSEQ_PROP_END);
    }
    temp_v1->unkC = D_uvpfx_rom_00404F40;
    if (temp_t0->unk4 == 1) {
        func_uvpfx_rom_0040374C(arg0);
    } else {
        func_uvpfx_rom_0040211C(arg0);
    }
    temp_v1->unk24 = -1;
}

void func_uvpfx_rom_004020D4(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_v0;

    temp_v0 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_v0->unkC = ((D_uvpfx_rom_00404F40 - temp_v0->unk10) + 1.0f) - temp_v0->unk4;
}

void func_uvpfx_rom_0040211C(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_s2;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_v0;
    Vec3F* var_s1;
    s32 i;

    temp_s2 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_v0 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_v0->unk20 = 0;
    temp_v0->unk14 = 0.0f;
    temp_v0->unk4 = 0.0f;
    if (temp_s2->unk2C->unk0 != 9) {
        return;
    }
        
    var_s1 = D_uvpfx_rom_00404FA0[arg0].unk8;
    for (i = 0; i < temp_s2->unk10; i++) {
        D_uvpfx_rom_00405BB4->uvVec3FSet(&var_s1[i], 0.0f, 0.0f, 0.0f);
    }
}



void func_uvpfx_rom_004021FC(s32 arg0, f32 arg1) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_s3;
    UnkStruct_uvpfx_rom_00404FA0_unk2C* temp_s6;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_s2;
    Vec3F* temp_s4;
    f32 temp_fa0;
    f32 temp_fv0;
    s16 temp_v1;
    s16 i;
    s32 var_v0;

    temp_s3 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_s2 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_s4 = D_uvpfx_rom_00404FA0[arg0].unk8;
    temp_s6 = temp_s3->unk2C;

    switch (temp_s6->unk8) {                              /* irregular */
    case 0:

        if (temp_s2->unk10 < 2.0f * temp_s6->unkC) {
            temp_s2->unk10 = 2.0f * temp_s6->unkC;
        }
        break;
    case 1:
        if (temp_s2->unk10 < temp_s6->unkC) {
            temp_s2->unk10 = temp_s6->unkC;
        }
        break;
    }
    var_v0 = (s32) (temp_s2->unk10 / temp_s6->unkC);
    if (var_v0 <= 0) {
        var_v0 = 1;
    }
    temp_s2->unk10 = (f32) var_v0 * temp_s6->unkC;
    if (temp_s2->unk24 != 0) {
        if (temp_s2->unk20 >= (var_v0 - 1)) {
            temp_s2->unk22 = 1;
        } else {
            temp_s2->unk22 = 0;
        }
        temp_s2->unk14 += arg1;
    } else {
        temp_s2->unk2 = 1;
        return;
    }

    if (temp_s6->unkC < temp_s2->unk14) {
        temp_s2->unk20 += 1;
        temp_s2->unk14 = 0.0f;
    }
    if (temp_s2->unk2 != 0) {
        temp_s2->unk20 = 1;
        temp_s2->unk2 = 0;
        if (temp_s6->unk0 == 9) {
            for (i = 0; i < temp_s3->unk10; i++) {
                D_uvpfx_rom_00405BB4->uvVec3FSet(&temp_s4[i], 0.0f, 0.0f, 0.0f);
            }
        }
        if (temp_s6->unk8 == 0) {
            temp_s2->unk14 = 0.0f - temp_s6->unkC;
        } else {
            temp_s2->unk14 = 0.0f;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvpfx_rom/func_uvpfx_rom_0040242C.s")

void func_uvpfx_rom_0040374C(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_s2;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_v1;
    Vec3F* var_s1;
    s32 i;

    temp_s2 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_v1 = D_uvpfx_rom_00404FA0[arg0].unk4;
    var_s1 = D_uvpfx_rom_00404FA0[arg0].unk8;
    temp_v1->unk22 = -1;
    temp_v1->unk14 = 0.0f;
    
    for (i = 0; i < temp_s2->unk28->unk0; i++) {
        D_uvpfx_rom_00405BB4->uvVec3FSet(&var_s1[i], 0, 0, 0);
    }
}

void func_uvpfx_rom_0040381C(s32 arg0, f32 arg1) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* v0;
    UnkStruct_uvpfx_rom_00404FA0_unk28* v1;

    v0 = D_uvpfx_rom_00404FA0[arg0].unk0;
    v1 = v0->unk28;
    v1->unk18 = arg1;
}

void func_uvpfx_rom_00403848(s32 arg0, s32 arg1, s16 arg2) {
    UnkStruct_uvpfx_rom_00404FA0_unk0* v0;
    UnkStruct_uvpfx_rom_00404FA0_unk28* temp_v1;
    s16 temp_a3;

    v0 = D_uvpfx_rom_00404FA0[arg0].unk0;
    temp_v1 = v0->unk28;
    if (arg2 < temp_v1->unk0) {
        temp_v1->unk8 = arg2;
    } else {
        temp_v1->unk8 = temp_v1->unk0;
    }
    temp_v1->unk4 = arg1;
}


void func_uvpfx_rom_00403898(s32 arg0) {
    UnkStruct_uvpfx_rom_00404FA0* temp_v0;
    UnkStruct_uvpfx_rom_00404FA0_unk0* temp_t0;
    UnkStruct_uvpfx_rom_00404FA0_unk4* temp_s3;
    UnkStruct_uvpfx_rom_00404FA0_unk28* sp38;
    Vec3F* temp_s6;
    f32 temp_fv0;
    s16 i;

    temp_fv0 = D_uvpfx_rom_00405BBC->func_uvgfxmgr_rom_00401004();
    temp_s3 = D_uvpfx_rom_00404FA0[arg0].unk4;
    temp_s6 = D_uvpfx_rom_00404FA0[arg0].unk8;
    sp38 = D_uvpfx_rom_00404FA0[arg0].unk0->unk28;
    if (temp_s3->unk22 == -1) {
        temp_s3->unk22 = 0;
        temp_s3->unk20 = 0;
        temp_s3->unkCC = temp_s3->unk80.m[3][0];
        temp_s3->unkD0 = temp_s3->unk80.m[3][1];
        temp_s3->unkD4 = temp_s3->unk80.m[3][2];
        return;
    }
    if ((temp_s3->unk22 < sp38->unk0) && (temp_s3->unk20 == 0)) {
        temp_s3->unk22++;
    }
    temp_s3->unkCC -= temp_s3->unk80.m[3][0] - (temp_s3->unkD8 * temp_fv0);
    temp_s3->unkD0 -= temp_s3->unk80.m[3][1] - (temp_s3->unkDC * temp_fv0);
    temp_s3->unkD4 -= temp_s3->unk80.m[3][2] - (temp_s3->unkE0 * temp_fv0);

    for (i = temp_s3->unk22 - 1; i > 0; i--) {
        D_uvpfx_rom_00405BB4->uvVec3FCopy(&temp_s6[i], &temp_s6[i - 1]);
        D_uvpfx_rom_00405BB4->uvVec3FAdd(&temp_s6[i], &temp_s6[i], (Vec3F* ) &temp_s3->unkCC);
    }
    D_uvpfx_rom_00405BB4->uvVec3FSet(temp_s6, 0, 0, 0.0f);
    temp_s3->unkCC = temp_s3->unk80.m[3][0];
    temp_s3->unkD0 = temp_s3->unk80.m[3][1];
    temp_s3->unkD4 = temp_s3->unk80.m[3][2];
    temp_s3->unk14 += temp_s3->unk18;
    if ((sp38->unk0 - 1) <= temp_s3->unk14) {
        temp_s3->unk14 = temp_s3->unk14 - (sp38->unk0 - 1);
    }
}


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

void func_uvpfx_rom_00404D2C(void) {

}
