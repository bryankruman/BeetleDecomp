// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "os.h"

extern UnkStruct_uvear_rom_0040085 *D_uvear_rom_00400854;
extern u16 D_uvear_rom_00400850;
extern s32 D_uvear_rom_00400860[];
extern UvFVec_Rom_Exports *sUvFvecExports;
extern f64 D_uvear_rom_00400858;

void __entrypoint_func_uvear_rom_400000(UvEar_Rom_Exports *exports);
void uvEarModuleCleanup(void);
void uvEarResetSlot(u16 arg0);
void uvEarSetPosition(u16 arg0, Vec3F vec);
void uvEarGetPosition(u16 arg0, Vec3F *arg1);
void uvEarSetSecondaryVector(u16 arg0, Vec3F arg1);
void uvEarGetSecondaryVector(u16 arg0, Vec3F *arg1);
void uvEarSetVectorsFromState(u16 arg0, UnkStruct_uvear_rom_0040085 *arg1);
void uvEarSetVelocity(u16 arg0, Vec3F arg1);
void uvEarGetVelocity(u16 arg0, Vec3F *arg1);
void uvEarUpdateVelocityHistory(u16 arg0);
f32 uvEarMaxAxisDistance(Vec3F *v1, Vec3F *v2);
s32 uvEarFindNearestSlot(s32 arg0, Vec3F *arg1);

void __entrypoint_func_uvear_rom_400000(UvEar_Rom_Exports *exports) {
    u16 i;
    u16 *size;

    uvUpdateFileAllocPtr(exports);
    exports->uvEarModuleCleanup = uvEarModuleCleanup;
    exports->uvEarSetPosition = uvEarSetPosition;
    exports->uvEarGetPosition = uvEarGetPosition;
    exports->uvEarSetSecondaryVector = uvEarSetSecondaryVector;
    exports->uvEarGetSecondaryVector = uvEarGetSecondaryVector;
    exports->uvEarSetVectorsFromState = uvEarSetVectorsFromState;
    exports->uvEarSetVelocity = uvEarSetVelocity;
    exports->uvEarGetVelocity = uvEarGetVelocity;
    exports->uvEarUpdateVelocityHistory = uvEarUpdateVelocityHistory;
    exports->uvEarFindNearestSlot = uvEarFindNearestSlot;
#line 33
    size = uvGetSystemProp(5);
    if (size == NULL) {
        D_uvear_rom_00400850 = 4;
    } else {
        if (*size != 0) {
            D_uvear_rom_00400850 = *size;
        } else {
            D_uvear_rom_00400850 = 4;
        }
    }
    D_uvear_rom_00400854 =
        _uvMemAllocAlign8(D_uvear_rom_00400850 * sizeof(UnkStruct_uvear_rom_0040085));
    for (i = 0; i < D_uvear_rom_00400850; i++) {
        uvEarResetSlot(i);
        D_uvear_rom_00400860[i] = 1;
    }

    uvClkReset(0x6A);
    D_uvear_rom_00400858 = uvClkGetSec(0x6A);
    sUvFvecExports = uvLoadModule('FVEC');
}

#line 55 "src/modules/uvear_rom.c"
/* Free the listener table and unload the floating-vector module. */
void uvEarModuleCleanup(void) {
    _uvMemFree(D_uvear_rom_00400854);
    uvUnloadModule('FVEC');
}
#line 59 "src/modules/uvear_rom.c"

#line 60 "src/modules/uvear_rom.c"
/* Reset original listener vectors, history and velocity scalars,
 * then set the last-update timestamp to -1. Slot bounds remain caller-owned. */
void uvEarResetSlot(u16 index) {
    UnkStruct_uvear_rom_0040085 *listener;

    listener = &D_uvear_rom_00400854[index];
    listener->vec.x = 0.0f;
    listener->vec.y = 0.0f;
    listener->vec.z = 0.0f;
    listener->unkC.x = 0.0f;
    listener->unkC.y = 0.0f;
    listener->unkC.z = 0.0f;
    listener->unk18 = 0.0f;
    listener->unk1C = 0.0f;
    listener->unk20 = 0.0f;
    listener->unk24 = 0.0f;
    listener->unk28 = 0.0f;
    listener->unk2C = 0.0f;
    listener->unk30.x = 0.0f;
    listener->unk30.y = 0.0f;
    listener->unk30.z = 0.0f;
    listener->unk40 = -1.0;
}
#line 81 "src/modules/uvear_rom.c"

#line 82 "src/modules/uvear_rom.c"
/* Store the listener position when the unsigned slot is below the
 * configured count. Out-of-range slots leave state/output unchanged. */
void uvEarSetPosition(u16 index, Vec3F vector) {
    if (index < D_uvear_rom_00400850) {
        D_uvear_rom_00400854[index].vec = vector;
    }
}
#line 87 "src/modules/uvear_rom.c"

#line 88 "src/modules/uvear_rom.c"
/* Copy out the listener position when the unsigned slot is below the
 * configured count. Out-of-range slots leave state/output unchanged. */
void uvEarGetPosition(u16 index, Vec3F *vector) {
    if (index < D_uvear_rom_00400850) {
        *vector = D_uvear_rom_00400854[index].vec;
    }
}
#line 93 "src/modules/uvear_rom.c"

#line 94 "src/modules/uvear_rom.c"
/* Store the listener secondaryvector when the unsigned slot is below the
 * configured count. Out-of-range slots leave state/output unchanged. */
void uvEarSetSecondaryVector(u16 index, Vec3F vector) {
    UnkStruct_uvear_rom_0040085 *temp_t0;

    if (index < D_uvear_rom_00400850) {
        D_uvear_rom_00400854[index].unkC = vector;
    }
}
#line 101 "src/modules/uvear_rom.c"

#line 102 "src/modules/uvear_rom.c"
/* Copy out the listener secondaryvector when the unsigned slot is below the
 * configured count. Out-of-range slots leave state/output unchanged. */
void uvEarGetSecondaryVector(u16 index, Vec3F *vector) {
    if (index < D_uvear_rom_00400850) {
        *vector = D_uvear_rom_00400854[index].unkC;
    }
}
#line 107 "src/modules/uvear_rom.c"

#line 108 "src/modules/uvear_rom.c"
/* Copy the source state position into the listener secondary vector,
 * and its velocity vector into listener position. Preserve the original
 * mapping rather than assuming this copies equal-named fields. */
void uvEarSetVectorsFromState(u16 index, UnkStruct_uvear_rom_0040085 *source) {
    if (index < D_uvear_rom_00400850) {
        D_uvear_rom_00400854[index].unkC.x = source->vec.x;
        D_uvear_rom_00400854[index].unkC.y = source->vec.y;
        D_uvear_rom_00400854[index].unkC.z = source->vec.z;
        D_uvear_rom_00400854[index].vec.x = source->unk30.x;
        D_uvear_rom_00400854[index].vec.y = source->unk30.y;
        D_uvear_rom_00400854[index].vec.z = source->unk30.z;
    }
}
#line 118 "src/modules/uvear_rom.c"

#line 119 "src/modules/uvear_rom.c"
/* Store an explicit listener velocity and clear the automatic-velocity
 * flag for valid unsigned slots. */
void uvEarSetVelocity(u16 index, Vec3F velocity) {
    if (index < D_uvear_rom_00400850) {
        D_uvear_rom_00400860[index] = 0;
        D_uvear_rom_00400854[index].unk30 = velocity;
    }
}
#line 125 "src/modules/uvear_rom.c"

#line 126 "src/modules/uvear_rom.c"
/* Copy out the listener velocity when the unsigned slot is below the
 * configured count. Out-of-range slots leave state/output unchanged. */
void uvEarGetVelocity(u16 index, Vec3F *vector) {
    if (index < D_uvear_rom_00400850) {
        *vector = D_uvear_rom_00400854[index].unk30;
    }
}
#line 131 "src/modules/uvear_rom.c"

#line 132 "src/modules/uvear_rom.c"
/* Once per distinct clock value, update position/secondary-vector history
 * and either derive velocity from displacement/time or retain explicit velocity.
 * Preserve original clock conversion and unsigned slot bounds. */
void uvEarUpdateVelocityHistory(u16 index) {
    Vec3F position;
    Vec3F secondary;
    Vec3F velocity;
    f32 elapsed;

    if (!(index < D_uvear_rom_00400850)) {
        return;
    }

    D_uvear_rom_00400858 = uvClkGetSec(0x6A);
    if (D_uvear_rom_00400858 != D_uvear_rom_00400854[index].unk40) {
        sUvFvecExports->uvVec3FCopy(&position, &D_uvear_rom_00400854[index].vec);
        sUvFvecExports->uvVec3FCopy(&secondary, &D_uvear_rom_00400854[index].unkC);
        if (D_uvear_rom_00400860[index] != 0) {
            elapsed = (f32) (D_uvear_rom_00400858 - D_uvear_rom_00400854[index].unk40);
            sUvFvecExports->uvVec3FSub(&velocity, &position, (Vec3F *) &D_uvear_rom_00400854[index].unk18);
            sUvFvecExports->uvVec3FScale(&velocity, &velocity, 1.0f / elapsed);
        } else {
            sUvFvecExports->uvVec3FCopy(&velocity, &D_uvear_rom_00400854[index].unk30);
        }
        sUvFvecExports->uvVec3FCopy((Vec3F *) &D_uvear_rom_00400854[index].unk18, &position);
        sUvFvecExports->uvVec3FCopy((Vec3F *) &D_uvear_rom_00400854[index].unk24, &secondary);
        sUvFvecExports->uvVec3FCopy(&D_uvear_rom_00400854[index].unk30, &velocity);
        D_uvear_rom_00400854[index].unk40 = D_uvear_rom_00400858;
    }
}
#line 159 "src/modules/uvear_rom.c"

#line 160 "src/modules/uvear_rom.c"
/* Return the largest comparison-based absolute coordinate difference.
 * Preserve original signed-zero and unordered-comparison behavior. */
f32 uvEarMaxAxisDistance(Vec3F *first, Vec3F *second) {
    f32 maximum;
    f32 difference;

    if (second->x < first->x) {
        maximum = first->x - second->x;
    } else {
        maximum = -(first->x - second->x);
    }
    if (second->y < first->y) {
        difference = first->y - second->y;
    } else {
        difference = -(first->y - second->y);
    }
    if (!(difference < maximum)) {
        maximum = difference;
    }
    if (second->z < first->z) {
        difference = first->z - second->z;
    } else {
        difference = -(first->z - second->z);
    }
    if (!(difference < maximum)) {
        maximum = difference;
    }
    return maximum;
}
#line 187 "src/modules/uvear_rom.c"

#line 188 "src/modules/uvear_rom.c"
/* Find the first listener below the original 200000 distance ceiling
 * using maximum-axis distance. Return zero when none qualifies; callers
 * supply a count within the listener table. */
s32 uvEarFindNearestSlot(s32 count, Vec3F *position) {
    f32 distance;
    f32 closestDistance;
    s32 var_s0;
    s32 i;
    s32 found;

    closestDistance = 200000.0f;
    found = 0;

    for (i = 0; i < count; i++) {
        distance = uvEarMaxAxisDistance(position, &D_uvear_rom_00400854[i].vec);
        if (distance < closestDistance) {
            closestDistance = distance;
            found = i;
        }
    }

    return found;
}
#line 208 "src/modules/uvear_rom.c"
