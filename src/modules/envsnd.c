// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"


// module functions
void __entrypoint_func_envsnd_400000(EnvSnd_Exports *exports);
void envsndNoOpModuleCleanup(void);
void func_envsnd_0040005C(s32 arg0, UnkStruct_envsnd_0040005C *arg1);
s32 envSndIsPositionInsideSoundRegion(UnkStruct_envsnd_0040005C *arg0, Vec3F *arg1);
void envSndUpdateRegionsForPlayer(UnkStruct_envsnd_00400250 *arg0);
void func_envsnd_00400444(s32 arg0, s32 arg1);

// .data
s32 D_envsnd_00400460[] = {0x00100000, __entrypoint_func_envsnd_400000, 0, 0};

// .bss
s32 B_envsnd_00400470; // unreferenced padding
UnkStruct_envsnd_0040005C *D_envsnd_00400474;
s32 D_envsnd_00400478;
s32 B_envsnd_0040047C; // more padding
UnkStruct_004005C8 D_envsnd_00400480[94];
u8 D_envsnd_00400770[96];


void __entrypoint_func_envsnd_400000(EnvSnd_Exports* exports) {
    uvUpdateFileAllocPtr(exports);
    exports->envsndNoOpModuleCleanup = envsndNoOpModuleCleanup;
    exports->func_envsnd_0040005C = func_envsnd_0040005C;
    exports->envSndUpdateRegionsForPlayer = envSndUpdateRegionsForPlayer;
    exports->func_envsnd_00400444 = func_envsnd_00400444;
}

#line 35 "src/modules/envsnd.c"
/* Original no-op cleanup hook in module export slot zero. The generic
 * UVMO unload path invokes this hook before freeing the module exports; this
 * function releases no additional resources. Preserve its distinct identity
 * and original void(void) ABI.
 * RE_UNKNOWN: broader module resource ownership and any additional caller roles. */
void envsndNoOpModuleCleanup(void) {
}
#line 37 "src/modules/envsnd.c"

void func_envsnd_0040005C(s32 arg0, UnkStruct_envsnd_0040005C *arg1) {
    UnkStruct_envsnd_0040005C *s0;
    s32 i;

    D_envsnd_00400478 = arg0;
    D_envsnd_00400474 = arg1;

    /* RE_UNKNOWN: this matching-only empty count test affects IDO register
     * allocation. A natural loop preserves the observed effects but fails
     * instruction matching; recover the original count-read source structure.
     * Count/table producers must also establish the 94-handle capacity and
     * valid lifetime, aliases and finite representable squared radii. */
#line 46 "src/modules/envsnd.c"
    if (D_envsnd_00400478) {
    }
    for (i = 0; i < D_envsnd_00400478; i++) {
        gSndExports->sndInitializeHandle(&D_envsnd_00400480[i]);
        arg1[i].unk20 = SQ(arg1[i].unk1C);
    }
}

#line 54 "src/modules/envsnd.c"
/* Test the position against the stored squared-radius limit, then
 * apply the original sound-ID height exclusions, including track ten.
 * The radius limit is stored as a signed word; preserve that quantization. */
s32 envSndIsPositionInsideSoundRegion(UnkStruct_envsnd_0040005C *region, Vec3F *position) {
    Vec3F offset;
    s32 inside;

    offset.x = position->x - region->unkC.x;
    offset.y = position->y - region->unkC.y;
    offset.z = position->z - region->unkC.z;
    if ((gUvFvecExports->uvVec3FDot(&offset, &offset) < region->unk20)) {
        inside = TRUE;
        if ((region->unk0 == 0x18) && (position->z < 290.0f)) {
            inside = FALSE;
        }
        if ((gGameSettings->currentTrack == 0xA)
            && ((region->unk0 == 0x48) || (region->unk0 == 0x49) || (region->unk0 == 0x4A)
                || (region->unk0 == 0x4B))
            && (((position->z > 28.7f)) || (position->z < 19.0f))) {
            inside = FALSE;
        }
    } else {
        inside = FALSE;
    }
    return inside;
}
#line 77 "src/modules/envsnd.c"

#line 78 "src/modules/envsnd.c"
/* Unless paused, player index zero clears region presence; other calls accumulate it and index numPlayers-1 starts/releases sounds.
 * RE_UNKNOWN: callers must group index zero first and the final index last; prove that ordering in original dispatch callers.
 * RE_UNKNOWN: original producers must respect the declared 94-handle/96-presence-byte extents; trace the count setter and table producers. */
void envSndUpdateRegionsForPlayer(UnkStruct_envsnd_00400250 *context) {
    UnkStruct_envsnd_0040005C *region;
    s32 playerIndex;
    Vec3F position;
    s32 regionIndex;
    u8 emitterId;
    playerIndex = context->unk4->unkC;
    if (gGameSettings->pauseFlag) {
        return;
    }

    gSndExports->sndSetSfxVol(gGameSettings->optionsSfxVol);
    position.x = context->unk0->unk618.x;
    position.y = context->unk0->unk618.y;
    position.z = context->unk0->unk618.z;

    region = D_envsnd_00400474;
    for (regionIndex = 0; regionIndex < D_envsnd_00400478; regionIndex++, region++) {
        if (playerIndex == 0) {
            D_envsnd_00400770[regionIndex] = 0;
        }
        if (envSndIsPositionInsideSoundRegion(region, &position) != 0) {
            D_envsnd_00400770[regionIndex] = 1;
        }
        if ((playerIndex + 1) == gGameSettings->numPlayers) {
            if (D_envsnd_00400770[regionIndex] != 0) {
                if (region->unk24 == 0) {
                    emitterId = gSndExports->func_snd_00401914(
                        &D_envsnd_00400480[regionIndex], region->unk0, 0x61A8,
                        gSndExports->sndGetSfxVolumeScale() * region->unk4, region->unk18, region->unk1C,
                         &region->unkC);

                    if (emitterId != 0xFF) {
                        region->unk24 = 1;
                        region->unk1 = emitterId;
                    }
                }
            } else if (region->unk24 != 0) {
                region->unk24 = 0;
                gSndExports->sndReleaseHandle(&D_envsnd_00400480[regionIndex]);
            }
        }
    }
}
#line 122 "src/modules/envsnd.c"

#line 123 "src/modules/envsnd.c"
/* Original no-op exported at envsnd export slot 0x0C. Retain this
 * separate function and its original argument ABI even though the body has no
 * effect.
 * RE_UNKNOWN: caller-facing role remains unresolved; this export binding alone
 * does not establish an update, reset or cleanup action. */
void func_envsnd_00400444(s32 arg0, s32 arg1) {

}
#line 126 "src/modules/envsnd.c"