// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

typedef struct UnkStruct_Powerup_004004D4_s {
    u8 unk0;
    u8 pad1[3];
    s32 objId;
    u16 unk8;
    u8 unkA;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} UnkStruct_Powerup_004004D4;


typedef struct UnkStruct_Powerup_00400368_s {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    f32 alpha;
} UnkStruct_Powerup_00400368;

extern UnkStruct_Powerup_004003C0 D_powerup_004003C0[];
void powerupReleaseObjectPoolAndModel(void);
void powerupCreateObjectAtPosition(s32, Vec3F*);
UnkStruct_Powerup_004003C0* powerupGetDescriptorOrDefault(s32);
void powerupSetDescriptorPrimitiveColor(UnkStruct_Powerup_00400368*);

// .bss
extern UnkStruct_Powerup_004004D4* D_powerup_004004D4;
extern s32 D_powerup_004004E8;

void __entrypoint_func_powerup_400000(Powerup_Exports* arg0) {
    s32 i;
    UnkStruct_Powerup_004004D4* var_v0;

    uvUpdateFileAllocPtr(arg0);
    arg0->powerupReleaseObjectPoolAndModel = powerupReleaseObjectPoolAndModel;
    arg0->powerupCreateObjectAtPosition = powerupCreateObjectAtPosition;
    arg0->powerupGetDescriptorOrDefault = powerupGetDescriptorOrDefault;
    D_powerup_004004D4 = _uvMemAllocAlign8(30 * sizeof(UnkStruct_Powerup_004004D4));
    D_powerup_004004E8 = 0;
    for (i = 0; i < 30; i++) {
        var_v0 = &D_powerup_004004D4[i];
        var_v0->unk0 = 0;
        var_v0->objId = -1;
    }

    uvLoadFile('UVMD', 52);
}

#line 63 "src/modules/powerup.c"
/* Reset each nonnegative draw-object handle in the thirty-entry powerup
 * pool, free the pool and unload UVMD model 52. */
void powerupReleaseObjectPoolAndModel(void) {
    s32 objectId;
    s32 index;

    for (index = 0; index < 30; index++) {
        objectId = D_powerup_004004D4[index].objId;
        if (objectId >= 0) {
            gUvDobjExports->uvDobjClearModelAndStateByte(objectId);
        }
    }

    _uvMemFree(D_powerup_004004D4);
    uvUnloadFile('UVMD', 52);
}
#line 77 "src/modules/powerup.c"

#line 78 "src/modules/powerup.c"
/* For descriptor zero through twelve, use the first inactive slot in
 * the thirty-entry pool, create its object and initialize model, callback,
 * transform and original scalar state. Preserve the original nonnegative
 * object-create check, including its existing failure-sentinel contract.
 * RE_UNKNOWN: Physical meanings of the remaining initialized scalar fields are not established.
 * RE_ORIGINAL_QUIRK: The original object-create check accepts every nonnegative result; do not silently repair its failure-sentinel contract. */
void powerupCreateObjectAtPosition(s32 descriptorIndex, Vec3F *position) {
    Mtx4F transform;
    s32 slot;
    UnkStruct_Powerup_004004D4 *entry;

    if (descriptorIndex < 0) {
        return;
    } else if (descriptorIndex >= 0xD) {
        return;
    }

    for (slot = 0; slot < 30; slot++) {
        entry = &D_powerup_004004D4[slot];
        if (entry->unk0 == 0) {
            break;
        }
    }

    if (slot == 30) {
        return;
    }

    entry->objId = gUvDobjExports->uvDobjCreate();
    if (entry->objId >= 0) {
        gUvDobjExports->uvDobjModel(entry->objId, D_powerup_004003C0[descriptorIndex].unk0);
        gUvDobjExports->uvDobjProps(entry->objId, 4, powerupSetDescriptorPrimitiveColor, entry, 0);
        gUvDobjExports->uvDobjSetFlagBits(entry->objId, 2);
        gUvDobjExports->uvDobjClearFlagBits(entry->objId, 1);
        gUvFmtxExports->uvMat4SetIdentity(&transform);
        transform.m[3][0] = position->x;
        transform.m[3][1] = position->y;
        transform.m[3][2] = position->z;
        gUvDobjExports->uvDobjPosm(entry->objId, 0, &transform);
        entry->unk0 = 1;
        entry->unk8 = descriptorIndex;
        entry->unkC = 0.0f;
        entry->unkA = 1;
        entry->unk10 = position->x;
        entry->unk14 = position->y;
        entry->unk18 = position->z;
        entry->unk1C = 0.0f;
        entry->unk20 = 1.0f;
    }
}
#line 122 "src/modules/powerup.c"


#line 124 "src/modules/powerup.c"
/* Return descriptor zero for an index outside zero through twelve;
 * otherwise return the requested original descriptor. */
UnkStruct_Powerup_004003C0* powerupGetDescriptorOrDefault(s32 index) {
    if ((index < 0) || (index >= 0xD)) {
        return &D_powerup_004003C0[0];
    }
    return &D_powerup_004003C0[index];
}
#line 130 "src/modules/powerup.c"

#line 131 "src/modules/powerup.c"
/* Look up the object descriptor and set its RGB components with the
 * object alpha. Preserve the original signed-short descriptor index and
 * unchecked array access. */
void powerupSetDescriptorPrimitiveColor(UnkStruct_Powerup_00400368* object) {
    UnkStruct_Powerup_004003C0* descriptor;

    descriptor = &D_powerup_004003C0[object->unk8];
    gUvGfxMgrExports->uvGfxSetPrimColorF(descriptor->red, descriptor->green, descriptor->blue, object->alpha);
}
#line 137 "src/modules/powerup.c"

