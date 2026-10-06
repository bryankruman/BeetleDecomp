// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

void func_uvgrph_rom_00400078(void);
f32 func_uvgrph_rom_00400080(UvGrphStruct *arg0, f32 arg1);
void func_uvgrph_rom_00400148(s32 arg0, s32 *arg1);
s32 func_uvgrph_rom_00400194(UvGrphStruct *grph, s32 arg1);
s32 func_uvgrph_rom_004002AC(UvGrphStruct *grph, s32 arg1);
void func_uvgrph_rom_0040033C(UvGrphStruct *arg0, f32 arg1);
f32 func_uvgrph_rom_00400370(UvGrphStruct *arg0, f32 arg1, f32 arg2, f32 arg3);
void __entrypoint_func_uvgrph_rom_400000(UvGrph_Exports *exports);

s32 D_uvgrph_rom_004006C0[] = {0x1C0000, __entrypoint_func_uvgrph_rom_400000, 0};

void __entrypoint_func_uvgrph_rom_400000(UvGrph_Exports *exports) {
    uvUpdateFileAllocPtr(exports);
    exports->func_uvgrph_rom_0040033C = func_uvgrph_rom_0040033C;
    exports->func_uvgrph_rom_00400078 = func_uvgrph_rom_00400078;
    exports->func_uvgrph_rom_00400370 = func_uvgrph_rom_00400370;
    exports->func_uvgrph_rom_00400080 = func_uvgrph_rom_00400080;
    exports->func_uvgrph_rom_00400148 = func_uvgrph_rom_00400148;
    exports->func_uvgrph_rom_00400194 = func_uvgrph_rom_00400194;
    exports->func_uvgrph_rom_004002AC = func_uvgrph_rom_004002AC;
}

void func_uvgrph_rom_00400078(void) {
}

f32 func_uvgrph_rom_00400080(UvGrphStruct *arg0, f32 arg1) {
    f32 temp_fv1;
    s32 i;

    if (arg1 <= arg0->arr->unk0) {
        return arg0->arr->unk4;
    }

    if (arg0->arr[arg0->count - 1].unk0 <= arg1) {
        return arg0->arr[arg0->count - 1].unk4;
    }

    for (i = 1; i < arg0->count - 1; i++) {
        if ((arg1 < arg0->arr[i].unk0)) {
            break;
        }
    }

    temp_fv1 = (arg1 - arg0->arr[i - 1].unk0) / (arg0->arr[i].unk0 - arg0->arr[i - 1].unk0);
    return (arg0->arr[i].unk4 * temp_fv1) + (arg0->arr[i - 1].unk4 * (1.0f - temp_fv1));
}

void func_uvgrph_rom_00400148(s32 arg0, s32 *arg1) {
    s32 i;

    if (*arg1 < 0) {
        *arg1 = 0;
    } else if (*arg1 >= 0x15) {
        *arg1 = 0x14;
    }
    // @useless loop
    i = 0;
    while (i < *arg1) {
        i++;
    }
}

s32 func_uvgrph_rom_00400194(UvGrphStruct *grph, s32 arg1) {
    s32 temp_v1;
    s32 i;
    UvGrphStruct *ptr;
    f32 temp_fv0;
    UvGrphInnerStruct *inner;
    if (arg1 < 0) {
        return arg1;
    }
    if (grph->count > 0x13) {
        return arg1;
    } else {
        grph->count++;
    }

    temp_v1 = arg1 + 1;

    for (i = grph->count - 1; i > temp_v1; i--) {
        grph->arr[i].unk0 = grph->arr[i - 1].unk0;
        grph->arr[i].unk4 = grph->arr[i - 1].unk4;
    }

    if (temp_v1 == grph->count - 1) {
        temp_fv0 = grph->arr[arg1].unk0 - grph->arr[arg1 - 1].unk0;
        grph->arr[temp_v1].unk0 = grph->arr[temp_v1 - 1].unk0 + temp_fv0;
        grph->arr[temp_v1].unk4 = grph->arr[temp_v1 - 1].unk4;
    } else {
        grph->arr[temp_v1].unk0 = (grph->arr[arg1].unk0 + grph->arr[arg1 + 2].unk0) * 0.5f;
        grph->arr[temp_v1].unk4 = (grph->arr[arg1].unk4 + grph->arr[arg1 + 2].unk4) * 0.5f;
    }
    arg1++;
    if (grph->count - 1 < arg1) {
        arg1 = grph->count - 1;
    }
    return arg1;
}

s32 func_uvgrph_rom_004002AC(UvGrphStruct *grph, s32 arg1) {
    s32 i;

    if (grph->count < 3) {
        return arg1;
    }

    if ((arg1 < 0) || ((grph->count - 1) < arg1)) {
        return arg1;
    }
    for (i = arg1; i < grph->count - 1; i++) {
        grph->arr[i].unk0 = grph->arr[i + 1].unk0;
        grph->arr[i].unk4 = grph->arr[i + 1].unk4;
    }

    arg1--;
    grph->count = grph->count - 1;
    if (arg1 < 0) {
        arg1 = 0;
    }

    return arg1;
}

void func_uvgrph_rom_0040033C(UvGrphStruct *arg0, f32 arg1) {
    func_uvgrph_rom_00400370(arg0, arg1, 0.0f, 0.0f);
}

f32 func_uvgrph_rom_00400370(UvGrphStruct *arg0, f32 arg1, f32 arg2, f32 arg3) {
    UvGrphInnerStruct *current;
    UvGrphInnerStruct *prev;
    f32 temp_fv1;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_a1;
    s32 var_v1_2;
    s32 var_t0;
    s32 var_v0_2;
    s32 i;

    var_v0_2 = -1;
    if (arg2 == arg3) {
        var_v0_2 = 0;
        var_v1_2 = arg0->count - 1;
    } else {
        var_v0_2 = -1;
        for (i = 0; i < arg0->count; i++) {
            if ((var_v0_2 == -1) && (arg2 < arg0->arr[i].unk0)) {
                var_v0_2 = i;
            }
            if (arg0->arr[i].unk0 < arg3) {
                var_v1_2 = i;
            }
        }
    }

    if ((var_v0_2 == -1) || ((var_v1_2 - var_v0_2) < 0)) {
        return 0.0f;
    }

    var_fv0 = arg0->arr[var_v0_2].unk4;
    var_a1 = var_v0_2;
    var_t0 = var_v0_2;
    var_fv1 = var_fv0;

    for (i = var_v0_2 + 1; i <= var_v1_2; i++) {
        if (arg0->arr[i].unk4 < var_fv1) {
            var_fv1 = arg0->arr[i].unk4;
            var_t0 = i;
        }
        if (var_fv0 < arg0->arr[i].unk4) {
            var_fv0 = arg0->arr[i].unk4;
            var_a1 = i;
        }
    }

    if (var_fv0 <= arg1) {
        return arg0->arr[var_a1].unk0;
    }
    if (arg1 <= var_fv1) {
        return arg0->arr[var_t0].unk0;
    }

    if (var_t0 < var_a1) {
        for (i = var_v0_2 + 1; i <= var_v1_2 - 1; i++) {
            if ((arg1 < arg0->arr[i].unk4)) {
                break;
            }
        }
        current = &arg0->arr[i - 1];
        prev = &arg0->arr[i];
    } else {
        for (i = var_v0_2 + 1; i <= var_v1_2 - 1; i++) {
            if ((arg0->arr[i].unk4 < arg1)) {
                break;
            }
        }
        current = &arg0->arr[i];
        prev = &arg0->arr[i - 1];
    }
    temp_fv1 = (arg1 - current->unk4) / (prev->unk4 - current->unk4);
    return (current->unk0 * (1.0f - temp_fv1)) + (prev->unk0 * temp_fv1);
}
