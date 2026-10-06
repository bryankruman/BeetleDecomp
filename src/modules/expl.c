// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

typedef struct UnkStruct_expl_004004B8_s {
    /* 0x00 */ s32 unk0;                            /* inferred */
    /* 0x04 */ Vec3F unk4;                            /* inferred */
    /* 0x10 */ f32 unk10;                           /* inferred */
} UnkStruct_expl_004004B8;                          /* size = 0x14 */

void func_expl_004000AC(void);
void func_expl_004000E0(void);
void func_expl_0040011C(Vec3F *, f32);
void func_expl_004002D0(void);
s32 func_expl_00400370(Vec3F* arg0, f32* arg1);

extern s32 gNumPlayers;

// .bss
s32 B_expl_004004B0[2]; // unreferenced padding
UnkStruct_expl_004004B8 D_expl_004004B8[20];
s32 D_expl_00400648[2];

void __entrypoint_func_expl_400000(Expl_Exports* exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->func_expl_004000AC = func_expl_004000AC;
    exports->func_expl_0040011C = func_expl_0040011C;
    exports->func_expl_004002D0 = func_expl_004002D0; 
    exports->func_expl_00400370 = func_expl_00400370;
#ifdef __sgi
    #line 29
#endif
    uvLoadFile('UVPX', 3);

    for (i = 0; i < ARRAY_COUNT(D_expl_004004B8); i++) {
        D_expl_004004B8[i].unk0 = -1;
    }

    gSndExports->func_snd_00402504(&D_expl_00400648);
}

void func_expl_004000AC(void) {
    gSndExports->func_snd_00401CDC(&D_expl_00400648);
}

void func_expl_004000E0(void) {
    gUvGfxMgrExports->uvGfxSetPrimColorF(1.0f, 1.0f, 1.0f, 1.0f);
}

void func_expl_0040011C(Vec3F *arg0, f32 arg1) {
    UnkStruct_expl_004004B8 *temp_t0;
    Vec3F *temp_v0_2;
    s32 multiPlayer;
    s32 i;


    for (i = 0; i < ARRAY_COUNT(D_expl_004004B8); i++) {
        temp_t0 = &D_expl_004004B8[i];
        if (temp_t0->unk0 < 0) {
            break;
        }
    }

    if (i == 20) {
        return;
    }

    temp_t0->unk0 = gUvPfxExports->func_uvpfx_rom_004002BC(3);
    if (temp_t0->unk0 < 0) {
        return;
    }

    temp_t0->unk10 = arg1;
    temp_t0->unk4.x = arg0->x;
    temp_v0_2 = &temp_t0->unk4;
    temp_t0->unk4.y = arg0->y;
    temp_t0->unk4.z = arg0->z;
    
    if (gNumPlayers >= 2) {
        multiPlayer = TRUE;
    } else {
        multiPlayer = FALSE;
    }

    // uvPfxProps
    gUvPfxExports->func_uvpfx_rom_004004D0(temp_t0->unk0, 0x1010, temp_v0_2->x, temp_v0_2->y,
                                           temp_v0_2->z, 0x1003, arg1, arg1, arg1,
                                           0x1028, func_expl_004000E0, 0, 0x1026, multiPlayer, 0);
    gUvPfxExports->func_uvpfx_rom_00402008(temp_t0->unk0);
    gSndExports->func_snd_00400750((UnkStruct_004005C8 *) &D_expl_00400648, CAREXPLODE, MAX_VOLUME,
                                   gSndExports->func_snd_004014B4(), 1.0f);
}

void func_expl_004002D0(void) {
    s32 pad;
    s32 i;
    s32 sp3C;

    for (i = 0; i < ARRAY_COUNT(D_expl_004004B8); i++) {
        if (D_expl_004004B8[i].unk0 < 0) {
            continue;
        }
        gUvPfxExports->func_uvpfx_rom_004012CC(D_expl_004004B8[i].unk0, 0x1011, &sp3C, 0);
        if (sp3C == 0) {
            D_expl_004004B8[i].unk0 = -1;
        }
    }
}

s32 func_expl_00400370(Vec3F *arg0, f32 *arg1) {
    UnkStruct_expl_004004B8 *var_s0;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 temp_fv0_2;
    f32 var_fv1;
    s32 var_s3;
    s32 i;

    var_s3 = FALSE;
    *arg1 = 0.0f;
    
    for (i = 0; i < ARRAY_COUNT(D_expl_004004B8); i++) {
        var_s0 = &D_expl_004004B8[i];
        if (var_s0->unk0 < 0) {
            continue;
        }

        diffX = arg0->x - var_s0->unk4.x;
        diffY = arg0->y - var_s0->unk4.y;
        diffZ = arg0->z - var_s0->unk4.z;
        temp_fv0_2 = gUvMathExports->uvSqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
        if (temp_fv0_2 < var_s0->unk10) {
            var_fv1 = 0.0f;
        } else {
            var_fv1 = temp_fv0_2 - var_s0->unk10;
        }
        if (var_s3) {
            var_s3 = TRUE;
            if (var_fv1 < *arg1) {
                *arg1 = var_fv1;
            }
        } else {
            var_s3 = TRUE;
            *arg1 = var_fv1;
        }
    }
    return var_s3;
}

// .data
s32 D_expl_004004A0[] = {0x00100000, __entrypoint_func_expl_400000, 0, 0};
