// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"
#include "global_exports.h"

#define WEAPON_COUNT 12

extern UnkStruct_weapon_00400184* D_weapon_00400184;
extern s32 D_weapon_00400198;
extern void weaponReleaseObjectPoolAndModel(void);

void __entrypoint_func_weapon_400000(Weapon_Exports *exports) {
    s32 i;

    uvUpdateFileAllocPtr(exports);
    exports->weaponReleaseObjectPoolAndModel = weaponReleaseObjectPoolAndModel;
    D_weapon_00400184 = _uvMemAllocAlign8(WEAPON_COUNT * sizeof(UnkStruct_weapon_00400184));
    D_weapon_00400198 = 0;

    for (i = 0; i < 12; i++) {
        UnkStruct_weapon_00400184* v0 = &D_weapon_00400184[i];
        v0->unk0 = -1;
        v0->unk4 = 0;
        v0->unk8 = 0.0f;
        v0->unk14 = 0;

    }
    uvLoadFile('UVMD', 4);
}

#line 31 "src/modules/weapon.c"
/* Reset each nonnegative draw-object handle in the twelve-entry weapon
 * pool, free the pool and unload UVMD model four. */
void weaponReleaseObjectPoolAndModel(void) {
    s32 index;

    for (index = 0; index < 12; index++) {
        UnkStruct_weapon_00400184* entry = &D_weapon_00400184[index];
        if (entry->unk0 >= 0) {
            gUvDobjExports->uvDobjClearModelAndStateByte(entry->unk0);
        }
    }
    _uvMemFree(D_weapon_00400184);
    uvUnloadFile('UVMD', 4);
}
#line 43 "src/modules/weapon.c"
