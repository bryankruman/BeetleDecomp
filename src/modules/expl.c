// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

typedef struct UnkStruct_expl_004004B8_s {
    /* 0x00 */ s32 unk0;                            /* inferred */
    /* 0x04 */ Vec3F unk4;                            /* inferred */
    /* 0x10 */ f32 unk10;                           /* inferred */
} UnkStruct_expl_004004B8;                          /* size = 0x14 */

void explReleaseSoundHandle(void);
void explSetOpaqueWhitePrimitiveColor(void);
void explCreateEffectAtPosition(Vec3F *, f32);
void explClearFinishedParticleHandles(void);
s32 explGetMinimumSurfaceDistance(Vec3F* arg0, f32* arg1);

extern s32 gNumPlayers;

// .bss
s32 B_expl_004004B0[2]; // unreferenced padding
UnkStruct_expl_004004B8 D_expl_004004B8[20];
s32 D_expl_00400648[2];
/* After updating the allocation pointer, publish four effect callbacks and load
 * UVPX file 3. Set the first word of each of 20 records to -1, then initialize
 * the shared sound handle.
 * RE_UNKNOWN: file ownership and repeated initialization need loader/callers. */
#line 25 "src/modules/expl.c"
void __entrypoint_func_expl_400000(Expl_Exports* exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->explReleaseSoundHandle = explReleaseSoundHandle;
    exports->explCreateEffectAtPosition = explCreateEffectAtPosition;
    exports->explClearFinishedParticleHandles = explClearFinishedParticleHandles;
    exports->explGetMinimumSurfaceDistance = explGetMinimumSurfaceDistance;
#ifdef __sgi
    #line 29
#endif
    uvLoadFile('UVPX', 3);

    for (i = 0; i < ARRAY_COUNT(D_expl_004004B8); i++) {
        D_expl_004004B8[i].unk0 = -1;
    }

    gSndExports->sndInitializeHandle(&D_expl_00400648);
}

#line 45 "src/modules/expl.c"
/* Release the shared explosion sound handle through the sound module.
 * Preserve the original unconditional call and handle ownership. */
void explReleaseSoundHandle(void) {
    gSndExports->sndReleaseHandle(&D_expl_00400648);
}
#line 48 "src/modules/expl.c"

#line 49 "src/modules/expl.c"
/* Set the graphics primitive color to fully opaque white. */
void explSetOpaqueWhitePrimitiveColor(void) {
    gUvGfxMgrExports->uvGfxSetPrimColorF(1.0f, 1.0f, 1.0f, 1.0f);
}
#line 52 "src/modules/expl.c"

#line 53 "src/modules/expl.c"
/* Use the first free slot in the twenty-entry explosion pool and acquire
 * a kind-three effect. Store its position/radius, apply original particle
 * properties and multiplayer policy, restart it and play the explosion sound.
 * Pool exhaustion or a negative effect handle returns without playback. */
void explCreateEffectAtPosition(Vec3F *position, f32 radius) {
    UnkStruct_expl_004004B8 *effect;
    Vec3F *effectPosition;
    s32 multiplayer;
    s32 slot;


    for (slot = 0; slot < ARRAY_COUNT(D_expl_004004B8); slot++) {
        effect = &D_expl_004004B8[slot];
        if (effect->unk0 < 0) {
            break;
        }
    }

    if (slot == 20) {
        return;
    }

    effect->unk0 = gUvPfxExports->uvPfxAcquireInactiveByKind(3);
    if (effect->unk0 < 0) {
        return;
    }

    effect->unk10 = radius;
    effect->unk4.x = position->x;
    effectPosition = &effect->unk4;
    effect->unk4.y = position->y;
    effect->unk4.z = position->z;

    if (gNumPlayers >= 2) {
        multiplayer = TRUE;
    } else {
        multiplayer = FALSE;
    }

    // uvPfxProps
    gUvPfxExports->func_uvpfx_rom_004004D0(effect->unk0, 0x1010, effectPosition->x, effectPosition->y,
                                           effectPosition->z, 0x1003, radius, radius, radius,
                                           0x1028, explSetOpaqueWhitePrimitiveColor, 0, 0x1026, multiplayer, 0);
    gUvPfxExports->uvPfxRestart(effect->unk0);
    gSndExports->sndPlayManagedSound((UnkStruct_004005C8 *) &D_expl_00400648, CAREXPLODE, MAX_VOLUME,
                                   gSndExports->sndGetSfxVolumeScale(), 1.0f);
}
#line 96 "src/modules/expl.c"

#line 97 "src/modules/expl.c"
/* Query particle property 0x1011 for each active explosion handle;
 * replace the handle with -1 when the returned value is zero. */
void explClearFinishedParticleHandles(void) {
    s32 pad;
    s32 index;
    s32 active;

    for (index = 0; index < ARRAY_COUNT(D_expl_004004B8); index++) {
        if (D_expl_004004B8[index].unk0 < 0) {
            continue;
        }
        gUvPfxExports->func_uvpfx_rom_004012CC(D_expl_004004B8[index].unk0, 0x1011, &active, 0);
        if (active == 0) {
            D_expl_004004B8[index].unk0 = -1;
        }
    }
}
#line 112 "src/modules/expl.c"

#line 113 "src/modules/expl.c"
/* Find the minimum distance from the position to an active explosion
 * surface, clamping points inside each radius to zero. Return whether any
 * active effect exists; when none exists, leave the output at zero. */
s32 explGetMinimumSurfaceDistance(Vec3F *position, f32 *minimumDistance) {
    UnkStruct_expl_004004B8 *effect;
    f32 diffX;
    f32 diffY;
    f32 diffZ;
    f32 centerDistance;
    f32 surfaceDistance;
    s32 found;
    s32 slot;

    found = FALSE;
    *minimumDistance = 0.0f;

    for (slot = 0; slot < ARRAY_COUNT(D_expl_004004B8); slot++) {
        effect = &D_expl_004004B8[slot];
        if (effect->unk0 < 0) {
            continue;
        }

        diffX = position->x - effect->unk4.x;
        diffY = position->y - effect->unk4.y;
        diffZ = position->z - effect->unk4.z;
        centerDistance = gUvMathExports->uvSqrtf(SQ(diffX) + SQ(diffY) + SQ(diffZ));
        if (centerDistance < effect->unk10) {
            surfaceDistance = 0.0f;
        } else {
            surfaceDistance = centerDistance - effect->unk10;
        }
        if (found) {
            found = TRUE;
            if (surfaceDistance < *minimumDistance) {
                *minimumDistance = surfaceDistance;
            }
        } else {
            found = TRUE;
            *minimumDistance = surfaceDistance;
        }
    }
    return found;
}
#line 153 "src/modules/expl.c"

// .data
s32 D_expl_004004A0[] = {0x00100000, __entrypoint_func_expl_400000, 0, 0};
