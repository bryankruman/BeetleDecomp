// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvasset_types.h"

s32 func_uvmodel_rom_00402224(f32 arg0, f32 arg1, f32 arg2, uvModelLOD_inner *arg3);
void uvModelGetProps(s32 arg0, ...);
s16 func_uvmodel_rom_004006B4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Mtx4F *arg4, uvModelLOD *arg5,
                              ParsedUVMD *arg6);
s16 func_uvmodel_rom_0040199C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F *arg6,
                              uvModelLOD *arg7, ParsedUVMD *arg8);
void func_uvmodel_rom_004002BC(void);
void func_uvmodel_rom_0040031C(s32 arg0);
void func_uvmodel_rom_00400324(s32 arg0, s32 arg1);
void func_uvmodel_rom_00400330(s32 arg0, s32 arg1, s32 arg2);
s32 func_uvmodel_rom_00400340(s32 arg0);
void uvModelGetPosm(s32 fileId, s32 arg1, Mtx4F *arg2);
void uvModelGetProps(s32 arg0, ...);
u8 func_uvmodel_rom_00400608(ParsedUVMD *arg0, f32 arg1);
s16 func_uvmodel_rom_0040215C(f32 x, f32 y, f32 z, Mtx4F *arg3, uvModelLOD *arg4);
s32 func_uvmodel_rom_00402224(f32 arg0, f32 arg1, f32 arg2, uvModelLOD_inner *arg3);
u8 func_uvmodel_rom_004022E4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                             UnkUVMD_24_Unk4 *arg6, f32 *arg7, f32 *arg8, s16 *arg9, s16 *arg10);
void func_uvmodel_rom_00402AD0(void);
Mtx4F *func_uvmodel_rom_00402AE0(void);
void func_uvmodel_rom_00402AFC(Mtx4F *src);
void func_uvmodel_rom_00402B98(void);
void func_uvmodel_rom_00402BB8(ParsedUVMD *uvmd, s32 arg1, s32 arg2);
s32 func_uvmodel_rom_00402CEC(ParsedUVMD *uvmd, uvGfxState **stateTable, s32 arg2);
void func_uvmodel_rom_00402E50(s32 id, s32 arg1);
void __entrypoint_func_uvmodel_rom_400000(UvModel_Exports *exports);

// .rodata
static const char sDevString[] = { "        checking bboxs %f %f %f\n" };
static const char sDevString1[] = { "        passed bbox test\n" };
static const char sDevString2[] = { "in bbox\n" };
static const char sDevString3[] = { "   tv = %f %f %f\n" };
static const char sDevString4[] = { "   inside case\n" };
static const char sDevString5[] = { "   max = %f  face = %d _dbnhits = %d\n" };
static const char sDevString6[] = { "   outside case\n" };
static const char sDevString7[] = { "  hits = %d  dist = %f  nrm = %f %f %f\n" };
static const char sDevString8[] = { "       checking surfaces for sphere\n" };
static const char sDevString9[] = { "         hit surf with *_dbnhits = %d\n" };
static const char sDevString10[] = { "             checking seg in bbox returned %d hits\n" };
static const char sDevString11[] = { "               no surfaces %d hits\n" };
static const char sDevString12[] = { "                checking surfaces for seg\n" };
static const char sDevString13[] = { "          seg: (%.1f %.1f %.1f) - (%.1f %.1f %.1f)\n" };
static const char sDevString14[] = { "          v0:  (%d %d %d)\n" };
static const char sDevString15[] = { "          v1:  (%d %d %d)\n" };
static const char sDevString16[] = { "          v2:  (%d %d %d)\n" };
static const char sDevString17[] = { "          hit a surface\n" };

// .data
s32 D_uvmodel_rom_00403130 = 0;
s32 D_uvmodel_rom_00403134[] = { 0x00500000, __entrypoint_func_uvmodel_rom_400000, 0 };

// .bss
s32 D_uvmodel_rom_00403140;
f32 *D_uvmodel_rom_00403144;
s32 *D_uvmodel_rom_00403148;
s32 *D_uvmodel_rom_0040314C;
Vec3F *D_uvmodel_rom_00403150;
s32 *D_uvmodel_rom_00403154;
s32 *D_uvmodel_rom_00403158;
s32 *D_uvmodel_rom_0040315C;
Mtx4F *D_uvmodel_rom_00403160;
static UvFMtx_Rom_Exports *sUvFmtxExports;
static UvFVec_Rom_Exports *sUvFvecExports;
static UvQuery_Exports *sUvQueryExports;
static UvIntersect_Exports *sUvIntersectExports;
static UvMath_Exports *sUvMathExports;
static UvGfxState_Rom_Exports *sUvGfxStateExports;

void __entrypoint_func_uvmodel_rom_400000(UvModel_Exports *exports) {
    s32 *mtxCount;

    uvUpdateFileAllocPtr(exports);
    exports->func_uvmodel_rom_0040031C = func_uvmodel_rom_0040031C;
    exports->func_uvmodel_rom_00400324 = func_uvmodel_rom_00400324;
    exports->func_uvmodel_rom_00400330 = func_uvmodel_rom_00400330;
    exports->func_uvmodel_rom_00400340 = func_uvmodel_rom_00400340;
    exports->uvModelGetPosm = uvModelGetPosm;
    exports->uvModelGetProps = uvModelGetProps;
    exports->func_uvmodel_rom_00400608 = func_uvmodel_rom_00400608;
    exports->func_uvmodel_rom_004006B4 = func_uvmodel_rom_004006B4;
    exports->func_uvmodel_rom_0040199C = func_uvmodel_rom_0040199C;
    exports->func_uvmodel_rom_004002BC = func_uvmodel_rom_004002BC;
    exports->func_uvmodel_rom_0040215C = func_uvmodel_rom_0040215C;
    exports->func_uvmodel_rom_00402224 = func_uvmodel_rom_00402224;
    exports->func_uvmodel_rom_004022E4 = func_uvmodel_rom_004022E4;
    exports->func_uvmodel_rom_00402AD0 = func_uvmodel_rom_00402AD0;
    exports->func_uvmodel_rom_00402AE0 = func_uvmodel_rom_00402AE0;
    exports->func_uvmodel_rom_00402AFC = func_uvmodel_rom_00402AFC;
    exports->func_uvmodel_rom_00402B98 = func_uvmodel_rom_00402B98;
    exports->func_uvmodel_rom_00402BB8 = func_uvmodel_rom_00402BB8;
    exports->func_uvmodel_rom_00402CEC = func_uvmodel_rom_00402CEC;
    exports->func_uvmodel_rom_00402E50 = func_uvmodel_rom_00402E50;
    mtxCount = uvGetSystemProp(SYSTEM_PROPID_MODEL_MTX_COUNT);
    if (mtxCount == NULL) {
        D_uvmodel_rom_00403140 = 5;
    } else {
        if (*mtxCount != 0) {
            D_uvmodel_rom_00403140 = *mtxCount;
        } else {
            D_uvmodel_rom_00403140 = 5;
        }
    }

    D_uvmodel_rom_00403160 = _uvMemAllocAlign8(D_uvmodel_rom_00403140 * sizeof(Mtx4F));
    uvMemSet(D_uvmodel_rom_00403160, 0, D_uvmodel_rom_00403140 * sizeof(Mtx4F));
    sUvFmtxExports = uvLoadModule('FMTX');
    sUvFvecExports = uvLoadModule('FVEC');
    sUvQueryExports = uvLoadModule('QERY');
    sUvIntersectExports = uvLoadModule('ISCT');
    sUvMathExports = uvLoadModule('MATH');
    // ! unused export
    sUvGfxStateExports = uvLoadModule('STAT');
    D_uvmodel_rom_00403144 = sUvQueryExports->uvQueryGetFloatValues();
    D_uvmodel_rom_00403148 = sUvQueryExports->uvQueryGetIntValues();
    D_uvmodel_rom_00403150 = sUvQueryExports->uvQueryGetFloatVectors();
    D_uvmodel_rom_00403158 = sUvQueryExports->func_uvquery_rom_00400270();
    D_uvmodel_rom_00403154 = sUvQueryExports->func_uvquery_rom_0040027C();
    D_uvmodel_rom_0040314C = sUvQueryExports->func_uvquery_rom_00400288();
    D_uvmodel_rom_0040315C = sUvQueryExports->func_uvquery_rom_004005F8();
}

void func_uvmodel_rom_004002BC(void) {
    _uvMemFree(D_uvmodel_rom_00403160);
    uvUnloadModule('FMTX');
    uvUnloadModule('FVEC');
    uvUnloadModule('QERY');
    uvUnloadModule('ISCT');
    uvUnloadModule('MATH');
}

void func_uvmodel_rom_0040031C(s32 arg0) {
}

void func_uvmodel_rom_00400324(s32 arg0, s32 arg1) {
}

void func_uvmodel_rom_00400330(s32 arg0, s32 arg1, s32 arg2) {
}

s32 func_uvmodel_rom_00400340(s32 arg0) {
    ParsedUVMD *uvmd;

    uvmd = uvGetLoadedFile('UVMD', arg0);
    if (uvmd == NULL) {
        return 0;
    }
    if (uvmd->unk0->unk0->unk4 == 0) {
        return 0;
    }
    return &uvmd->unk0->unk0->stateTable->state;
}

void uvModelGetPosm(s32 modelId, s32 partIndex, Mtx4F *posm) {
    ParsedUVMD *uvmd;

    uvmd = uvGetLoadedFile('UVMD', modelId);
    if ((uvmd == NULL) || (partIndex >= uvmd->unk0->unk8)) {
        return;
    }
    sUvFmtxExports->uvMat4FCopy(posm, &uvmd->unk8[partIndex]);
    posm->m[3][0] /= uvmd->unk10;
    posm->m[3][1] /= uvmd->unk10;
    posm->m[3][2] /= uvmd->unk10;
}

void uvModelGetProps(s32 modelId, ...) {
    s32 temp_lo;
    u8 var_a0;
    u32 prop;
    uvModelLOD *modelLod;
    ParsedUVMD *uvmd;
    va_list args;

    if (modelId == 0xFFFF) {
        return;
    }
    uvmd = uvGetLoadedFile('UVMD', modelId);
    va_start(args, modelId);
    if (uvmd == NULL) {
        return;
    }

    while (TRUE) {
        prop = va_arg(args, s32);
        switch (prop) {
            case 2:
                *va_arg(args, s32 *) = uvmd->unk4;
                break;
            case 5:
                modelLod = uvmd->unk0->unk0;
                if (modelLod->unk4 == 0) {
                    var_a0 = FALSE;
                } else {
                    if (modelLod->stateTable->state & 0x02000000) {
                        var_a0 = TRUE;
                    } else {
                        var_a0 = FALSE;
                    }
                }
                *va_arg(args, u8 *) = var_a0;
                break;
            case 4:
                *va_arg(args, s32 *) = uvmd->unk0->unk8;
                break;
            case 1:
                *va_arg(args, f32 *) = uvmd->unkC;
                break;
            case 9:
                *va_arg(args, f32 *) = uvmd->unk10;
                break;
            case 8:
                *va_arg(args, s32 *) = uvmd->unk5;
                break;
            case 7:
                temp_lo = va_arg(args, s32);
                *va_arg(args, s32 *) = uvmd->unk0->unk0[temp_lo].unk6;
                break;
            case 0:
                return;
            default:
                break;
        }
    }
}

u8 func_uvmodel_rom_00400608(ParsedUVMD *arg0, f32 arg1) {
    s32 var_a1;
    s32 var_v0;
    u8 temp_v0;
    ParsedUVMD_1 *temp_v1;
    u8 i;

    temp_v0 = arg0->unk4;
    temp_v1 = arg0->unk0;

    if (temp_v1->unk4 == 0.0f) {
        return 0;
    }
    if (temp_v1[temp_v0 - 1].unk4 <= arg1) {
        return 0xFF;
    }

    for (i = temp_v0; i > 0; i--) {
        if (temp_v1[i - 1].unk4 < arg1) {
            return i;
        }
    }

    return 0;
}

s16 func_uvmodel_rom_004006B4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, Mtx4F *arg4, uvModelLOD *arg5,
                              ParsedUVMD *arg6) {
    Mtx4F sp1E8;
    Vec3F sp1DC;
    Vec3F sp1D0;
    uvModelLOD_inner *sp1CC;
    Vec3F *temp_s0_5;
    f32 temp_fv0_2;
    s32 sp1C0;
    f32 var_fa0;
    s32 sp1B8;
    f32 var_fs0;
    f32 var_fs1;
    f32 var_fv0;
    f32 var_fv1;
    f64 temp_fv0_7;
    s32 sp19C;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0_2;
    f32 sp18C;
    f32 sp188;
    f32 sp184;
    f32 sp180;
    f32 sp17C;
    f32 sp178;
    s32 var_s4;
    s32 temp_t4;
    Vec3F sp164;
    Vtx *sp160;
    Gfx *sp15C;
    s32 spDC[32];
    u32 var_a0;
    u32 var_v0_5;
    u32 var_v1_3;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    uvModelLOD_inner *temp_s0;
    query_78 *temp_s0_6;
    query_28 *temp_s1;
    s32 spB4;
    u32 var_a3;
    s32 i;

    sp1C0 = *D_uvmodel_rom_00403158;
    // clang-format off
    sp1DC.x = arg0;sp1DC.y = arg1;sp1DC.z = arg2;
    // clang-format on
    if (arg2) {
    }
    sp1D0.x = arg3;
    sp1D0.y = arg3;
    sp1D0.z = arg3;

    if (sUvFmtxExports->func_uvfmtx_rom_00401790(&sp1E8, arg4) == 0) {
        return -1;
    }
    sUvFmtxExports->func_uvfmtx_rom_00401D0C(&sp1E8, &sp1DC, &sp1DC);
    sUvFmtxExports->func_uvfmtx_rom_004030FC(&sp1E8, &sp1D0, &sp1D0);
    sp1D0.x = (sp1D0.x > 0.00f) ? (sp1D0.x) : (-sp1D0.x);
    sp1D0.y = (sp1D0.y > 0.00f) ? (sp1D0.y) : (-sp1D0.y);
    sp1D0.z = (sp1D0.z > 0.00f) ? (sp1D0.z) : (-sp1D0.z);
    if (sp1D0.y < sp1D0.x) {
        var_fv0 = sp1D0.x;
    } else {
        var_fv0 = sp1D0.y;
    }

    if (sp1D0.z < var_fv0) {
        if (sp1D0.y < sp1D0.x) {
            var_fv0 = sp1D0.x;
        } else {
            var_fv0 = sp1D0.y;
        }
        var_fs1 = var_fv0;
    } else {
        var_fs1 = sp1D0.z;
    }
    sUvQueryExports->uvQueryGetProps(0, 1, &sp1B8, 0);
    if (arg6->unk5 & 2) {
        sp1CC = &arg5->unk8;
        sp18C = arg5->unk8.unk0 - sp1DC.x;
        if (var_fs1 < sp18C) {
            return -1;
        }
        sp188 = sp1DC.x - sp1CC->unkC;
        if (var_fs1 < sp188) {
            return -1;
        }
        sp184 = sp1CC->unk4 - sp1DC.y;
        if (var_fs1 < sp184) {
            return -1;
        }
        sp180 = sp1DC.y - sp1CC->unk10;
        if (var_fs1 < sp180) {
            return -1;
        }
        sp17C = sp1CC->unk8 - sp1DC.z;
        if (var_fs1 < sp17C) {
            return -1;
        }
        sp178 = sp1DC.z - sp1CC->unk14;
        if (var_fs1 < sp178) {
            return -1;
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
        if (1) {
        }
    }
    if (arg6->unk5 & 0x10) {
        if ((sp1B8 != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->func_uvquery_rom_00400610())) {
            var_fa0 = (var_fs1 * var_fs1) - ((sp1DC.y * sp1DC.y) + (sp1DC.z * sp1DC.z));
            if (((sp1DC.y * sp1DC.y) + (sp1DC.z * sp1DC.z)) <= (var_fs1 * var_fs1)) {
                temp_fv0_2 = sUvMathExports->uvSqrtf(var_fa0);
                temp_s0 = &arg5->unk8;
                var_fs0 = temp_s0->unkC - temp_s0->unk0;
                if (var_fs0 > 0.00001f) {
                    if ((temp_s0->unk0 <= (sp1DC.x + temp_fv0_2))
                        && ((sp1DC.x - temp_fv0_2) <= temp_s0->unkC)) {
                        temp_s1 =
                            sUvQueryExports->func_uvquery_rom_004005EC() + (*D_uvmodel_rom_0040315C);
                        temp_s1->unk0 = *D_uvmodel_rom_00403154;
                        sp164.x = temp_s0->unk0;
                        sp164.y = 0.0f;
                        sp164.z = 0.0f;
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk14,
                                                                 (Vec3F *) (&sp164));
                        sp164.x = temp_s0->unkC;
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk8,
                                                                 (Vec3F *) (&sp164));
                        temp_s1->unk20 = var_fs0;
                        temp_s1->unk24 = (-temp_s0->unk0) / var_fs0;
                        if (arg5->unk4 != 0) {
                            temp_s1->unk4 = (s32) arg5->stateTable->state;
                            if (temp_s0_6) {
                            }
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (arg6->unk5 & 0x20) {
        if ((sp1B8 != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->func_uvquery_rom_00400610())) {
            var_fa0 = (var_fs1 * var_fs1) - ((sp1DC.x * sp1DC.x) + (sp1DC.z * sp1DC.z));
            if (((sp1DC.x * sp1DC.x) + (sp1DC.z * sp1DC.z)) <= (var_fs1 * var_fs1)) {
                temp_fv0_2 = sUvMathExports->uvSqrtf(var_fa0);
                temp_s0 = &arg5->unk8;
                var_fs0 = temp_s0->unk10 - temp_s0->unk4;
                if (var_fs0 > 0.00001f) {
                    if ((temp_s0->unk4 <= (sp1DC.y + temp_fv0_2))
                        && ((sp1DC.y - temp_fv0_2) <= temp_s0->unk10)) {
                        temp_s1 =
                            sUvQueryExports->func_uvquery_rom_004005EC() + (*D_uvmodel_rom_0040315C);
                        temp_s1->unk0 = (s32) (*D_uvmodel_rom_00403154);
                        sp164.y = temp_s0->unk4;
                        sp164.x = (sp164.z = 0.0f);
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk14, &sp164);
                        sp164.y = temp_s0->unk10;
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk8, &sp164);
                        temp_s1->unk20 = var_fs0;
                        temp_s1->unk24 = (-temp_s0->unk4) / var_fs0;
                        if (arg5->unk4 != 0) {
                            temp_s1->unk4 = (s32) arg5->stateTable->state;
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (arg6->unk5 & 0x40) {
        if ((sp1B8 != 0)
            && ((*D_uvmodel_rom_0040315C) < sUvQueryExports->func_uvquery_rom_00400610())) {
            var_fa0 = (var_fs1 * var_fs1) - ((sp1DC.x * sp1DC.x) + (sp1DC.y * sp1DC.y));
            if (((sp1DC.x * sp1DC.x) + (sp1DC.y * sp1DC.y)) <= (var_fs1 * var_fs1)) {
                temp_fv0_2 = sUvMathExports->uvSqrtf(var_fa0);
                temp_s0 = &arg5->unk8;
                var_fs0 = temp_s0->unk14 - temp_s0->unk8;
                if (var_fs0 > 0.00001f) {
                    if ((temp_s0->unk8 <= (sp1DC.z + temp_fv0_2))
                        && ((sp1DC.z - temp_fv0_2) <= temp_s0->unk14)) {
                        temp_s1 =
                            &sUvQueryExports->func_uvquery_rom_004005EC()[*D_uvmodel_rom_0040315C];
                        temp_s1->unk0 = *D_uvmodel_rom_00403154;
                        sp164.z = temp_s0->unk8;
                        sp164.x = (sp164.y = 0.0f);
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk14, &sp164);
                        sp164.z = temp_s0->unk14;
                        sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s1->unk8, &sp164);
                        temp_s1->unk20 = var_fs0;
                        temp_s1->unk24 = (-temp_s0->unk8) / var_fs0;
                        if (arg5->unk4 != 0) {
                            temp_s1->unk4 = (s32) arg5->stateTable->state;
                        }
                        *D_uvmodel_rom_0040315C += 1;
                    }
                }
            }
        }
    } else if (!(arg6->unk5 & 4)) {
        spC4 = (spC8 = (spCC = 0.0f));
        temp_s0_5 = &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158];
        if (sp18C > 0.0f) {
            spC4 += sp18C / var_fs1;
        }
        if (sp188 > 0.0f) {
            spC4 += sp188 / var_fs1;
        }
        if (sp184 > 0.0f) {
            spC8 += sp184 / var_fs1;
        }
        if (sp180 > 0.0f) {
            if (1) {
                spC8 += sp180 / var_fs1;
            }
        }
        if (sp17C > 0.0f) {
            spCC += sp17C / var_fs1;
        }
        if (sp178 > 0.0f) {
            spCC += sp178 / var_fs1;
        }
        if (((spC4 == 0.0f) && (spC8 == 0.0f)) && (spCC == 0.0f)) {
            var_fs0 = -10000000000.0f;
            if (var_fs0 < sp188) {
                var_fs0 = sp188;
                spB4 = 1;
            }
            if (var_fs0 < sp18C) {
                var_fs0 = sp18C;
                spB4 = -1;
            }
            if (var_fs0 < sp180) {
                var_fs0 = sp180;
                spB4 = 2;
            }
            if (var_fs0 < sp184) {
                var_fs0 = sp184;
                spB4 = -2;
            }
            if (var_fs0 < sp178) {
                var_fs0 = sp178;
                spB4 = 3;
            }
            if (var_fs0 < sp17C) {
                var_fs0 = sp17C;
                spB4 = -3;
            }
            sUvIntersectExports->func_uvintersect_rom_004020A0(arg4, spB4, temp_s0_5);
            temp_fv0_7 = (-var_fs0) / var_fs1;
            // clang-format off
            if (temp_fv0_7 < 1.0) { D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = temp_fv0_7; } else { temp_fv0_7 = 1.0; D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = temp_fv0_7;
            }
            // clang-format on
            D_uvmodel_rom_0040314C[*D_uvmodel_rom_00403158] |= 1;
        } else {
            temp_fv0_2 = sUvMathExports->uvSqrtf(((spC4 * spC4) + (spC8 * spC8)) + (spCC * spCC));
            if (temp_fv0_2 > 1.0f) {
                return -1;
            }
            temp_s0_5->x = (-spC4) / temp_fv0_2;
            temp_s0_5->y = (-spC8) / temp_fv0_2;
            temp_s0_5->z = (-spCC) / temp_fv0_2;
            sUvFmtxExports->func_uvfmtx_rom_004030FC(arg4, temp_s0_5, temp_s0_5);
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = temp_fv0_2;
        }
        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
        if (sp1B8 != 0) {
            temp_s0_6 = sUvQueryExports->func_uvquery_rom_004004CC() + (*D_uvmodel_rom_00403158);
            temp_s0_6->unk0.x = sp1CC->unk0;
            temp_s0_6->unk0.y = sp1CC->unk4;
            temp_s0_6->unk0.z = sp1CC->unk8;
            temp_s0_6->unkC.x = sp1CC->unkC;
            temp_s0_6->unkC.y = sp1CC->unk10;
            temp_s0_6->unkC.z = sp1CC->unk14;
            sUvFmtxExports->uvMat4FCopy(&temp_s0_6->unk30, &sp1E8);
            temp_s0_6->unk70 &= ~1;
            if (arg5->unk4 != 0) {
                temp_s0_6->unk74 = (s32) arg5->stateTable->state;
            }
        }
        *D_uvmodel_rom_00403158 += 1;
        return 1;
    }
    if (!(arg6->unk5 & 4)) {
        return (s16) ((*D_uvmodel_rom_00403158) - sp1C0);
    }
    sp160 = arg6->vtxTable;
    for (i = 0; i < 32; i++) {
        spDC[i] = -1;
    }

    for (i = 0; i < arg5->unk4; i++) {
        sp15C = arg5->stateTable[i].displayList;
        for (sp15C = ((u32) sp15C) | 0x80000000;; sp15C++) {
            temp_s5 = sp15C->words.w0;
            temp_s6 = sp15C->words.w1;
            sp19C = ((u32) (temp_s5 & 0xFF000)) >> 0xC;
            temp_v0_2 = temp_s5 & 0xFF000000;
            if (temp_v0_2 == 0xDF000000) {
                break;
            }
            if (temp_v0_2 == 0x01000000) {
                temp_v0_2 = ((u32) temp_s6) - ((u32) arg6->vtxTable);
                temp_v0_2 = ((u32) ((void *) (((u32) temp_v0_2) + 0x80000000))) / (sizeof(Vtx));
                var_a3 = temp_s5 & 0xFF000;
                temp_t4 = var_a3 >> 0xC;
                for (var_s4 = 0; var_s4 < temp_t4; var_s4++) {
                    s32 temp = (((u32) (temp_s5 & 0xFE)) >> 1) - sp19C;
                    spDC[var_s4 + temp] = var_s4 + temp_v0_2;
                }

            } else {
                sp19C = 1;
                if (temp_v0_2 == 0x06000000) {
                    sp19C = 2;
                }
                for (var_s4 = 0; var_s4 < sp19C; var_s4++) {
                    if (var_s4 == 0) {
                        var_v0_5 = ((u32) (temp_s5 & 0xFF0000)) >> 0x11;
                        var_v1_3 = ((u32) (temp_s5 & 0xFF00)) >> 9;
                        var_a0 = ((u32) (temp_s5 & 0xFF)) >> 1;
                    } else {
                        var_v0_5 = ((u32) (temp_s6 & 0xFF0000)) >> 0x11;
                        var_v1_3 = ((u32) (temp_s6 & 0xFF00)) >> 9;
                        var_a0 = ((u32) (temp_s6 & 0xFF)) >> 1;
                    }
                    var_v0_5 = spDC[var_v0_5];
                    var_v1_3 = spDC[var_v1_3];
                    var_a0 = spDC[var_a0];
                    temp_v0_2 = sUvIntersectExports->func_uvintersect_rom_0040093C(
                        sp1DC.x, sp1DC.y, sp1DC.z, var_fs1, 1.0f, sp160[var_v0_5].v.ob[0],
                        sp160[var_v0_5].v.ob[1], sp160[var_v0_5].v.ob[2], sp160[var_v1_3].v.ob[0],
                        sp160[var_v1_3].v.ob[1], sp160[var_v1_3].v.ob[2], sp160[var_a0].v.ob[0],
                        sp160[var_a0].v.ob[1], sp160[var_a0].v.ob[2],
                        &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                        &D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158]);
                    if (temp_v0_2 != 0) {
                        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
                        D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] /= -var_fs1;
                        if (temp_v0_2 == 1) {
                            D_uvmodel_rom_0040314C[*D_uvmodel_rom_00403158] |= 1;
                        }
                        sUvFmtxExports->func_uvfmtx_rom_004030FC(
                            arg4, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        sUvFvecExports->uvVec3FNormalize(
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        if (sp1B8 != 0) {
                            temp_s0_6 =
                                &sUvQueryExports->func_uvquery_rom_004004CC()[*D_uvmodel_rom_00403158];
                            temp_s0_6->unk0.x = sp160[var_v0_5].v.ob[0];
                            temp_s0_6->unk0.y = sp160[var_v0_5].v.ob[1];
                            temp_s0_6->unk0.z = sp160[var_v0_5].v.ob[2];
                            temp_s0_6->unkC.x = sp160[var_v1_3].v.ob[0];
                            temp_s0_6->unkC.y = sp160[var_v1_3].v.ob[1];
                            temp_s0_6->unkC.z = sp160[var_v1_3].v.ob[2],
                            temp_s0_6->unk18.x = sp160[var_a0].v.ob[0];
                            temp_s0_6->unk18.y = sp160[var_a0].v.ob[1];
                            temp_s0_6->unk18.z = sp160[var_a0].v.ob[2];
                            temp_s0_6->unk70 |= 1;
                            temp_s0_6->unk74 = arg5->stateTable[i].state;
                            sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s0_6->unk0,
                                                                     &temp_s0_6->unk0);
                            sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s0_6->unkC,
                                                                     &temp_s0_6->unkC);
                            sUvFmtxExports->func_uvfmtx_rom_00401D0C(arg4, &temp_s0_6->unk18,
                                                                     &temp_s0_6->unk18);
                            temp_s0_6->unk24 = D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158];
                        }
                        if ((++(*D_uvmodel_rom_00403158))
                            >= sUvQueryExports->func_uvquery_rom_00400224()) {
                            --(*D_uvmodel_rom_00403158);
                            return (*D_uvmodel_rom_00403158) - sp1C0;
                        }
                    }
                }
            }
        }
    }

    return (*D_uvmodel_rom_00403158) - sp1C0;
}

s16 func_uvmodel_rom_0040199C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, Mtx4F *arg6,
                              uvModelLOD *arg7, ParsedUVMD *arg8) {
    Mtx4F sp178;
    Vec3F sp16C;
    Vec3F sp160;
    u8 sp15F;
    f32 sp158;
    f32 sp154;
    f32 sp150;
    s16 sp14E;
    s16 sp14C;
    s16 var_s1;
    s16 sp148;
    s16 sp146;
    s16 i;
    Gfx *sp140;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_t6;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_fp;
    s32 var_t0;
    s32 var_t1;
    s32 temp;
    s32 pad1;
    s32 sp98[32];
    s32 pad;
    if (sUvFmtxExports->func_uvfmtx_rom_00401790(&sp178, arg6) == 0) {
        return -1;
    }
    sp16C.x = arg0;
    sp16C.y = arg1;
    sp16C.z = arg2;
    sp160.x = arg3;
    sp160.y = arg4;
    sp160.z = arg5;
    sUvFmtxExports->func_uvfmtx_rom_00401D0C(&sp178, (Vec3F *) (&sp16C), (Vec3F *) (&sp16C));
    sUvFmtxExports->func_uvfmtx_rom_00401D0C(&sp178, (Vec3F *) (&sp160), (Vec3F *) (&sp160));
    sp14E = 0;
    if (arg8->unk5 & 2) {
        sp15F = func_uvmodel_rom_004022E4(sp16C.x, sp16C.y, sp16C.z, sp160.x, sp160.y, sp160.z,
                                          (UnkUVMD_24_Unk4 *) (&arg7->unk8), &sp154, &sp150, &sp148,
                                          &sp146);
        if (sp15F == 0) {
            return -1;
        }
    }
    if (!(arg8->unk5 & 4)) {
        sUvIntersectExports->func_uvintersect_rom_004020A0(
            arg6, sp148, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
        sUvFvecExports->uvVec3FScale(&D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                                     &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], arg8->unk10);
        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
        if (sp15F == 1) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = sp154;
        } else if (sp15F == 2) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = sp154;
            *D_uvmodel_rom_00403158 += 1;
            D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
            sUvIntersectExports->func_uvintersect_rom_004020A0(
                arg6, sp146, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
            sUvFvecExports->uvVec3FScale(&D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                                         &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], arg8->unk10);
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = sp150;
        } else if (sp15F == 3) {
            D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = 1.0f;
        }
        *D_uvmodel_rom_00403158 += 1;
        return 1;
    }
    for (i = 0; i < 32; i++) {
        sp98[i] = -1;
    }

    for (sp14C = 0; sp14C < arg7->unk4; sp14C++) {
        sp140 = arg7->stateTable[sp14C].displayList;
        for (sp140 = (Gfx *) (((u32) sp140) | 0x80000000);; sp140++) {
            temp_s2 = sp140->words.w0;
            temp_s3 = sp140->words.w1;
            temp_v0_2 = temp_s2 & 0xFF000000;
            if (temp_v0_2 == (0xdf << 24)) {
                break;
            }
            if (temp_v0_2 == (0x01 << 24)) {
                temp_v0_2 = ((u32) temp_s3) - ((u32) arg8->vtxTable);
                temp_v0_2 = ((u32) ((void *) (((u32) temp_v0_2) + 0x80000000))) / (sizeof(Vtx));
                var_a1 = (u32) (temp_s2 & 0xFF000);
                pad = var_a1 >> 0xC;
                // clang-format off
                for (var_s1 = 0; var_s1 < pad; var_s1++) { \
                    temp = ((temp_s2 & 0xFE) >> 1) - (var_a1 >> 0xC); \
                    sp98[var_s1 + temp] = var_s1 + temp_v0_2; \
                } \
                // clang-format off
            } else {
                var_fp = 1;
                if (temp_v0_2 == (0x06 << 24)) {
                    var_fp = 2;
                }
                for (var_s1 = 0; var_s1 < var_fp; var_s1++) {
                    if (var_s1 == 0) {
                        var_a1 = (temp_s2 & 0xFF0000) >> 17;
                        var_t0 = (temp_s2 & 0xFF00) >> 9;
                        var_t1 = (temp_s2 & 0xFF) >> 1;
                    } else {
                        var_a1 = (temp_s3 & 0xFF0000) >> 17;
                        var_t0 = (temp_s3 & 0xFF00) >> 9;
                        var_t1 = (temp_s3 & 0xFF) >> 1;
                    }
                    var_a1 = sp98[var_a1];
                    var_t0 = sp98[var_t0];
                    var_t1 = sp98[var_t1];
                    if (sUvIntersectExports->func_uvintersect_rom_00401318(
                            sp16C.x, sp16C.y, sp16C.z, sp160.x, sp160.y, sp160.z,
                            arg8->vtxTable[var_a1].v.ob[0], arg8->vtxTable[var_a1].v.ob[1],
                            arg8->vtxTable[var_a1].v.ob[2], arg8->vtxTable[var_t0].v.ob[0],
                            arg8->vtxTable[var_t0].v.ob[1], arg8->vtxTable[var_t0].v.ob[2],
                            arg8->vtxTable[var_t1].v.ob[0], arg8->vtxTable[var_t1].v.ob[1],
                            arg8->vtxTable[var_t1].v.ob[2], 1.0f, 1.0f, &sp158,
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158])
                        != 0) {
                        D_uvmodel_rom_00403148[*D_uvmodel_rom_00403158] = *D_uvmodel_rom_00403154;
                        D_uvmodel_rom_00403144[*D_uvmodel_rom_00403158] = sp158;
                        sUvFmtxExports->func_uvfmtx_rom_004030FC(
                            arg6, &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158]);
                        sUvFvecExports->uvVec3FScale(
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158],
                            &D_uvmodel_rom_00403150[*D_uvmodel_rom_00403158], arg8->unk10);
                        *D_uvmodel_rom_00403158 += 1;
                        sp14E += 1;
                    }
                }
            }
        }
    }

    if (sp14E != 0) {
        return sp14E;
    }
    return -1;
}

s16 func_uvmodel_rom_0040215C(f32 x, f32 y, f32 z, Mtx4F *arg3, uvModelLOD *arg4) {
    Mtx4F mtx4F;
    Vec3F vec;

    if (arg4->unk8.unk0 == 10000000000.0f) {
        return -1;
    }

    vec.x = x;
    vec.y = y;
    vec.z = z;

    if (sUvFmtxExports->func_uvfmtx_rom_00401790(&mtx4F, arg3) == 0) {
        return -1;
    }
    sUvFmtxExports->func_uvfmtx_rom_00401D0C(&mtx4F, &vec, &vec);
    if (func_uvmodel_rom_00402224(vec.x, vec.y, vec.z, &arg4->unk8) != 0) {
        return 0;
    }
    return -1;
}

s32 func_uvmodel_rom_00402224(f32 arg0, f32 arg1, f32 arg2, uvModelLOD_inner *arg3) {
    if (arg0 < arg3->unk0) {
        return FALSE;
    }
    if (arg3->unkC < arg0) {
        return FALSE;
    }
    if (arg1 < arg3->unk4) {
        return FALSE;
    }
    if (arg3->unk10 < arg1) {
        return FALSE;
    }
    if (arg2 < arg3->unk8) {
        return FALSE;
    }
    if (arg3->unk14 < arg2) {
        return FALSE;
    }
    return TRUE;
}

u8 func_uvmodel_rom_004022E4(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                             UnkUVMD_24_Unk4 *arg6, f32 *arg7, f32 *arg8, s16 *arg9, s16 *arg10) {
    s32 i;
    f32 *sp5C[2];
    s16 *sp54[2];
    s32 pad[2];
    f32 var_fa0;
    f32 sp44;
    f32 sp40;
    f32 var_fa1;
    f32 sp38;
    f32 sp34;
    f32 var_fv1;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 temp_fa0;
    f32 temp_fa1;

    i = 0;

    sp5C[0] = arg7;
    sp5C[1] = arg8;
    sp54[0] = arg9;
    sp54[1] = arg10;
    if (arg3 < arg0) {
        sp44 = arg0;
        sp38 = arg3;
    } else {
        sp44 = arg3;
        sp38 = arg0;
    }
    if (arg4 < arg1) {
        sp40 = arg1;
        sp34 = arg4;
    } else {
        sp40 = arg4;
        sp34 = arg1;
    }
    if (arg5 < arg2) {
        var_fa1 = arg2;
        var_fv1 = arg5;
    } else {
        // clang-format off
        var_fa1 = arg5; \
        var_fv1 = arg2;
        // clang format on
    }

    if (sp44 < arg6->unk0) {
        *sp54[i] = -1;
        return 0;
    }

    if (arg6->unkC < sp38) {
        *sp54[i] = 1;
        return 0;
    }

    if (sp40 < arg6->unk4) {
        *sp54[i] = -2;
        return 0;
    }

    if (arg6->unk10 < sp34) {
        *sp54[i] = 2;
        return 0;
    }

    if (var_fa1 < arg6->unk8) {
        *sp54[i] = -3;
        return 0;
    }

    if (arg6->unk14 < var_fv1) {
        *sp54[i] = 3;
        return 0;
    }
    if ((sp44 <= arg6->unkC) && (arg6->unk0 <= sp38) && (sp40 <= arg6->unk10) && (arg6->unk4 <= sp34) && (var_fa1 <= arg6->unk14) && (arg6->unk8 <= var_fv1)) {
        *sp54[i] = -1;
        return 3;
    }

    temp_fa1 = arg3 - arg0;
    temp_fa0 = arg4 - arg1;
    temp_fv1 = arg5 - arg2;

    if (var_fv1 <= arg6->unk8) {
        if (temp_fv1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk8 - arg2) / temp_fv1;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -3;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unk14 <= var_fa1) {
        if (temp_fv1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk14 - arg2) / temp_fv1;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 3;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (sp34 <= arg6->unk4) {
        if (temp_fa0 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk4 - arg1) / temp_fa0;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fv1) + arg2;
            if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -2;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unk10 <= sp40) {
        if (temp_fa0 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk10 - arg1) / temp_fa0;
        }
        temp_fv0 = (var_fa0 * temp_fa1) + arg0;
        if ((arg6->unk0 <= temp_fv0) && (temp_fv0 <= arg6->unkC)) {
            temp_fv0 = (var_fa0 * temp_fv1) + arg2;
            if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 2;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (sp38 <= arg6->unk0) {
        if (temp_fa1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unk0 - arg0) / temp_fa1;
        }
        temp_fv0 = (var_fa0 * temp_fv1) + arg2;
        if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = -1;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    if (arg6->unkC <= sp44) {
        if (temp_fa1 == 0.0f) {
            var_fa0 = 0.0f;
        } else {
            var_fa0 = (arg6->unkC - arg0) / temp_fa1;
        }
        temp_fv0 = (var_fa0 * temp_fv1) + arg2;
        if ((arg6->unk8 <= temp_fv0) && (temp_fv0 <= arg6->unk14)) {
            temp_fv0 = (var_fa0 * temp_fa0) + arg1;
            if ((arg6->unk4 <= temp_fv0) && (temp_fv0 <= arg6->unk10)) {
                *sp5C[i] = var_fa0;
                *sp54[i] = 1;
                i++;
                if (i == 2) {
                    return 2;
                }
            }
        }
    }

    return i;
}

void func_uvmodel_rom_00402AD0(void) {
    D_uvmodel_rom_00403130 = -1;
}

Mtx4F* func_uvmodel_rom_00402AE0(void) {
    return &D_uvmodel_rom_00403160[D_uvmodel_rom_00403130];
}

void func_uvmodel_rom_00402AFC(Mtx4F* src) {
    Mtx4F* mtx4F;
    
    if (++D_uvmodel_rom_00403130 >= D_uvmodel_rom_00403140) {
        return;
    }
    if (D_uvmodel_rom_00403130 == 0) {
        mtx4F = (Mtx4F*)D_uvmodel_rom_00403160 + D_uvmodel_rom_00403130;
        sUvFmtxExports->uvMat4FCopy(mtx4F, src);
    } else {
        mtx4F = (Mtx4F*)D_uvmodel_rom_00403160 + (D_uvmodel_rom_00403130);
        sUvFmtxExports->uvMat4Mul(mtx4F, mtx4F - 1, src);
    }
}

void func_uvmodel_rom_00402B98(void) {
    if (D_uvmodel_rom_00403130 >= 0) {
        D_uvmodel_rom_00403130--;
    }
}

void func_uvmodel_rom_00402BB8(ParsedUVMD* uvmd, s32 arg1, s32 arg2) {
    s32 i;
    s32 j;
    s32 k;
    uvModelLOD* modelLod;
    ParsedUVMD_1* temp_fp;
    s32 pad;
    
    for (i = 0; i < uvmd->unk4; i++) {
        temp_fp = &uvmd->unk0[i];
        for (j = 0; j < temp_fp->unk8; j++) {
            modelLod = &temp_fp->unk0[j];
            for (k = 0; k < modelLod->unk4; k++) {
                sUvGfxStateExports->func_uvgfxstate_rom_00401418(&modelLod->stateTable[k], arg1, arg2);
            }
        }
    }
}

s32 func_uvmodel_rom_00402CEC(ParsedUVMD* uvmd, uvGfxState** stateTable, s32 arg2) {
    s32 i;
    s32 j;
    s32 k;
    s32 stateCount;
    ParsedUVMD_1* temp_t0;
    uvGfxState* state;
    uvModelLOD* modelLod;

    stateCount = 0;
    for (i = 0; i < uvmd->unk4; i++) {
        temp_t0 = &uvmd->unk0[i];
        for (j = 0; j < temp_t0->unk8; j++) {
            modelLod = &temp_t0->unk0[j];
            for (k = 0; k < modelLod->unk4; k++) {
                state = &modelLod->stateTable[k];
                if (sUvGfxStateExports->func_uvgfxstate_rom_0040143C(state, arg2) != 0) {
                    stateTable[stateCount++] = state;
                }
            }
        }
    }

    return stateCount;
}

void func_uvmodel_rom_00402E50(s32 id, s32 arg1) {
    ParsedUVMD* uvmd;

    uvmd = uvGetLoadedFile('UVMD', id);
    if (uvmd == NULL) {
        return;
    }
    if (uvmd->unk20 != NULL) {
        uvmd->unk20->unk38 = arg1;
    }
}
