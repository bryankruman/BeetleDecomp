// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "uvquat_rom.h"

/*
 * D_uvjanim_rom_00401760 = uvLoadModule(0x4D415448, arg0);
 * D_uvjanim_rom_00401764 = uvLoadModule(0x4D4F444C);
 * D_uvjanim_rom_00401768 = uvLoadModule(0x444F424A);
 * D_uvjanim_rom_0040176C = uvLoadModule(0x464D5458);
 * D_uvjanim_rom_00401770 = uvLoadModule(0x51554154)
 */

typedef struct UnkModelExports_s {
    char pad[0x14];
    void (*unk14)(s32, s32, Mtx4F *);
} UnkModelExports;

typedef struct UnkStruct_UvJanim_rom_00400144_s {
    /* 0x00 */ Quat *unk0;
    /* 0x04 */ Vec3F *unk4;
    /* 0x08 */ Vec3F *unk8;
    /* 0x0C */ u8 *unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u16 unk12;
} UnkStruct_UvJanim_rom_00400144;

extern UvQuat_Exports *D_uvjanim_rom_00401770;
extern UnkDobjExports *D_uvjanim_rom_00401768;
extern UnkModelExports *D_uvjanim_rom_00401764;
extern UvFMtx_Rom_Exports *D_uvjanim_rom_0040176C;

void func_uvjanim_rom_00400434(UnkStruct_UvJanim_rom_00400144 *arg0,
                               UnkStruct_UvJanim_rom_00400144 *arg1,
                               UnkStruct_UvJanim_rom_00400144 *arg2, f32 arg3);

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/__entrypoint_func_uvjanim_rom_400000.s")

void func_uvjanim_rom_004000F0(void) {
    uvUnloadModule('MATH');
    uvUnloadModule('MODL');
    uvUnloadModule('DOBJ');
    uvUnloadModule('FMTX');
    uvUnloadModule('QUAT');
}

void func_uvjanim_rom_00400144(UnkStruct_UvJanim_rom_00400144 *arg0,
                               UnkStruct_UvJanim_rom_00400144 *arg1) {
    if (arg0->unk12 >= arg1->unk10) {
        if (arg1->unk0 != NULL) {
            if ((arg0->unk0 != NULL) && (arg1->unk11 & 1)) {
                _uvMediaCopy(arg0->unk0, arg1->unk0, arg1->unk10 * 0x10);
            }
        }
        if (arg1->unk4 != NULL) {
            if ((arg0->unk4 != NULL) && (arg1->unk11 & 2)) {
                _uvMediaCopy(arg0->unk4, arg1->unk4, arg1->unk10 * 0xC);
            }
        }
        if (arg1->unk8 != NULL) {
            if ((arg0->unk8 != NULL) && (arg1->unk11 & 4)) {
                _uvMediaCopy(arg0->unk8, arg1->unk8, arg1->unk10 * 0xC);
            }
        }
        if (arg1->unkC != NULL) {
            if (arg0->unkC != NULL) {
                _uvMediaCopy(arg0->unkC, arg1->unkC, (u32) arg1->unk10);
            }
        }
        arg0->unk11 = arg1->unk11;
        arg0->unk10 = arg1->unk10;
    }
}

void func_uvjanim_rom_00400278(s32 arg0, UnkStruct_UvJanim_rom_00400144 *arg1) {
    Mtx4F sp68;
    s32 i; // s4
    Quat *s0;
    s32 temp_v0;
    Vec3F *s1;
    Vec3F *s2;
    s32 s7;

    temp_v0 = D_uvjanim_rom_00401768->unk18();
    s0 = arg1->unk0;
    s1 = arg1->unk4;
    s2 = arg1->unk8;
    s7 = arg1->unk10;

    for (i = 0; i < s7; i++) {
        D_uvjanim_rom_00401764->unk14(temp_v0, arg1->unkC[i], &sp68);
        if ((arg1->unk11 & 1) && (s0 != NULL)) {
            D_uvjanim_rom_0040176C->func_0040246C(&sp68, s0->x, s0->y, s0->z, s0->w);
            s0++;
        }

        if ((arg1->unk11 & 2) && (s1 != NULL)) {
            sp68.m[3][0] += s1->x;
            sp68.m[3][1] += s1->y;
            sp68.m[3][2] += s1->z;
            s1++;
        }
        if ((arg1->unk11 & 4) && (s2 != NULL)) {
            D_uvjanim_rom_0040176C->func_004014D0(&sp68, s2->x, s2->y, s2->z);
            s2++;
            // FAKE
            if (s7)
                ;
        }
        // FAKE
        if (&D_uvjanim_rom_00401768)
            ;

        D_uvjanim_rom_00401768->unk24(arg0, arg1->unkC[i], &sp68);
    }
}

void func_uvjanim_rom_00400434(UnkStruct_UvJanim_rom_00400144 *arg0,
                               UnkStruct_UvJanim_rom_00400144 *arg1,
                               UnkStruct_UvJanim_rom_00400144 *arg2, f32 arg3) {
    Vec3F *temp_a1;
    f32 var_fv0;
    s32 var_t4;
    s32 var_t0;
    s32 var_t3;
    s32 var_t1;
    s32 var_t2;
    Vec3F *temp_a2;
    Vec3F *temp_a3;
    Vec3F *var_a0;
    Vec3F *var_v0;
    Vec3F *var_v1;
    f32 var_fa1;
    Quat *var_a0_3;
    Quat *var_a1;
    Quat *var_a2;

    var_t4 = 0;
    if (arg3 > 1.0f) {
        var_fv0 = 1.0f;
    } else {
        var_fv0 = arg3;
    }
    if (var_fv0 < 0.0f) {
        var_fv0 = 0.0f;
    }
    var_fa1 = 1.0f - var_fv0;
    arg0->unk11 = 0;
    if (arg0->unk4 != NULL) {
        if (arg1->unk4 != NULL) {
            if (arg2->unk4 != NULL) {
                var_v0 = arg0->unk4;
                var_v1 = arg1->unk4;
                var_a0 = arg2->unk4;
                if (arg1->unk11 & arg2->unk11 & 2) {
                    var_t1 = arg1->unk10;
                    var_t3 = 0;
                    var_t0 = 0;
                    var_t2 = arg2->unk10;
                    while (((var_t1 != 0) || (var_t2 != 0)) && (var_t4 < arg0->unk12)) {
                        if ((var_t1 != 0) && (var_t2 != 0)
                            && (arg1->unkC[var_t0] == arg2->unkC[var_t3])) {
                            var_v0->x = ((var_a0->x * var_fv0) + (var_v1->x * var_fa1));
                            var_v0->y = ((var_a0->y * var_fv0) + (var_v1->y * var_fa1));
                            var_v0->z = ((var_a0->z * var_fv0) + (var_v1->z * var_fa1));
                            var_v0++;
                            var_t1--;
                            var_v1++;
                            var_t3++;
                            var_t2--;
                            var_a0++;
                            arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            var_t0++;
                        } else if ((var_t2 != 0)
                                   && ((var_t1 == 0)
                                       || ((s32) arg2->unkC[var_t3] < (s32) arg1->unkC[var_t0]))) {
                            var_t2--;
                            if (var_fv0 > 0.0f) {
                                var_v0->x = var_a0->x;
                                var_v0->y = var_a0->y;
                                var_v0->z = var_a0->z;
                                var_v0++;
                                arg0->unkC[var_t4++] = arg2->unkC[var_t3];
                            }
                            var_t3++;
                            var_a0++;
                        } else if ((var_t1 != 0)
                                   && ((var_t2 == 0)
                                       || ((s32) arg1->unkC[var_t0] < (s32) arg2->unkC[var_t3]))) {
                            var_t1--;
                            if (var_fa1 > 0.0f) {
                                var_v0->x = var_v1->x;
                                var_v0->y = var_v1->y;
                                var_v0->z = var_v1->z;
                                var_v0++;
                                arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            }

                            var_t0++;
                            var_v1++;
                        }
                    }
                    arg0->unk11 |= 2;
                }
            }
        }
    }
    if (arg0->unk8 != NULL) {
        if (arg1->unk8 != NULL) {
            if (arg2->unk8 != NULL) {
                var_v0 = arg0->unk8;
                var_v1 = arg1->unk8;
                var_a0 = arg2->unk8;
                if (arg1->unk11 & arg2->unk11 & 4) {
                    var_t1 = arg1->unk10;
                    var_t3 = 0;
                    var_t0 = 0;
                    var_t4 = 0;
                    var_t2 = arg2->unk10;
                    while (((var_t1 != 0) || (var_t2 != 0)) && (var_t4 < arg0->unk12)) {
                        if ((var_t1 != 0) && (var_t2 != 0)
                            && (arg1->unkC[var_t0] == arg2->unkC[var_t3])) {
                            var_v0->x = ((var_a0->x * var_fv0) + (var_v1->x * var_fa1));
                            var_v0->y = ((var_a0->y * var_fv0) + (var_v1->y * var_fa1));
                            var_v0->z = ((var_a0->z * var_fv0) + (var_v1->z * var_fa1));
                            var_v0++;
                            var_t1--;
                            var_v1++;
                            var_t3++;
                            var_t2--;
                            var_a0++;
                            arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            var_t0++;
                        } else if ((var_t2 != 0)
                                   && ((var_t1 == 0) || (arg2->unkC[var_t3] < arg1->unkC[var_t0]))) {
                            var_t2--;
                            if (var_fv0 > 0.0f) {
                                var_v0->x = var_a0->x;
                                var_v0->y = var_a0->y;
                                var_v0->z = var_a0->z;
                                var_v0++;
                                arg0->unkC[var_t4++] = arg2->unkC[var_t3];
                            }
                            var_t3++;
                            var_a0++;
                        } else if ((var_t1 != 0)
                                   && ((var_t2 == 0) || (arg1->unkC[var_t0] < arg2->unkC[var_t3]))) {
                            var_t1 -= 1;
                            if (var_fa1 > 0.0f) {
                                var_v0->x = var_v1->x;
                                var_v0->y = var_v1->y;
                                var_v0->z = var_v1->z;
                                var_v0++;
                                arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            }
                            var_t0++;
                            var_v1++;
                        }
                    }
                    arg0->unk11 |= 4;
                }
            }
        }
    }
    if (arg0->unk0 != NULL) {
        if (arg1->unk0 != NULL) {
            if (arg2->unk0 != NULL) {
                var_a0_3 = arg0->unk0;
                var_a1 = arg1->unk0;
                var_a2 = arg2->unk0;
                if (arg1->unk11 & arg2->unk11 & 1) {
                    var_t1 = arg1->unk10;
                    var_t3 = 0;
                    var_t0 = 0;
                    var_t4 = 0;
                    var_t2 = arg2->unk10;
                    while (((var_t1 != 0) || (var_t2 != 0)) && (var_t4 < arg0->unk12)) {
                        if ((var_t1 != 0) && (var_t2 != 0)
                            && (arg1->unkC[var_t0] == arg2->unkC[var_t3])) {
                            D_uvjanim_rom_00401770->func_uvquat_rom_004009BC(var_a0_3, var_a1, var_a2,
                                                                             var_fv0);
                            var_a0_3++;
                            var_a1++;
                            var_a2++;
                            var_t1--;
                            var_t2--;
                            var_t3++;
                            arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            var_t0++;
                        } else if ((var_t2 != 0)
                                   && ((var_t1 == 0)
                                       || ((s32) arg2->unkC[var_t3] < (s32) arg1->unkC[var_t0]))) {
                            var_t2 -= 1;
                            if (var_fv0 > 0.0f) {
                                var_a0_3->x = var_a2->x;
                                var_a0_3->y = var_a2->y;
                                var_a0_3->z = var_a2->z;
                                var_a0_3->w = var_a2->w;
                                var_a0_3++;
                                arg0->unkC[var_t4++] = arg2->unkC[var_t3];
                            }
                            var_t3++;
                            var_a2++;
                        } else if ((var_t1 != 0)
                                   && ((var_t2 == 0)
                                       || ((s32) arg1->unkC[var_t0] < (s32) arg2->unkC[var_t3]))) {
                            var_t1 -= 1;
                            if (var_fa1 > 0.0f) {
                                var_a0_3->x = var_a1->x;
                                var_a0_3->y = var_a1->y;
                                var_a0_3->z = var_a1->z;
                                var_a0_3->w = var_a1->w;
                                var_a0_3++;
                                arg0->unkC[var_t4++] = arg1->unkC[var_t0];
                            }
                            var_t0++;
                            var_a1++;
                        }
                    }
                    arg0->unk11 |= 1;
                }
            }
        }
    }
    arg0->unk10 = var_t4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/func_uvjanim_rom_00400C0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/func_uvjanim_rom_00400CFC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/func_uvjanim_rom_00401288.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/func_uvjanim_rom_00401380.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvjanim_rom/func_uvjanim_rom_00401704.s")
