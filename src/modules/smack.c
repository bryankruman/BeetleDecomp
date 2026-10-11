// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "uvfvec_rom.h"
#include "uvquat_rom.h"
#include "uvdobj_rom.h"
extern UvDobj_Exports *gUvDobjExports;
typedef struct { u8 unk00[0x18]; Vec3F position; u8 unk24[8]; s32 objectId; u8 unk30[8]; u8 active; u8 unk39; u8 blocked; } SmackObjectRecord;
void func_smack_004000E8();
void func_smack_00400290();
void func_smack_0040038C();
SmackObjectRecord *func_smack_0040062C(s32, s32);
SmackObjectRecord *smackAttachObjectRecord(s32 objectId);
void func_smack_00400824();
void smackDetachActiveRecord();
void func_smack_0040097C();
void func_smack_00400E00();
void func_smack_00400FB4();
void func_smack_00401240();
s32 smackGetPlayerValue(u8 player);
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/__entrypoint_func_smack_400000.s")

#line 22 "src/modules/smack.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_smack_004000E0(void) {
}
#line 24 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_004000E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400290.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040038C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040062C.s")

#line 33 "src/modules/smack.c"
/* Find the effect record for this object model. Unless blocked, activate it,
 * retain the object ID and copy the object matrix translation into position.
 * Return the original lookup result even when the record is blocked. */
SmackObjectRecord *smackAttachObjectRecord(s32 objectId) {
    SmackObjectRecord *record;
    Mtx4F matrix;
    record = func_smack_0040062C(gUvDobjExports->uvDobjGetModel(objectId), objectId);
    if (record != NULL && record->blocked == 0) {
        record->active = 1;
        record->objectId = objectId;
        gUvDobjExports->uvDobjGetPosm(objectId, 0, &matrix);
        record->position = *(Vec3F *)&matrix.m[3][0];
    }
    return record;
}
#line 34 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400824.s")

#line 37 "src/modules/smack.c"
/* When record byte 0x39 is active, set its object word at 0x2C to -1
 * and clear that byte. Leave inactive records unchanged. */
void smackDetachActiveRecord(void *record) {
    if (*(u8 *)((u8 *)record + 0x39) != 0) {
        *(s32 *)((u8 *)record + 0x2C) = -1;
        *(u8 *)((u8 *)record + 0x39) = 0;
    }
}
#line 43 "src/modules/smack.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_0040097C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400E00.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00400FB4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/smack/func_smack_00401240.s")

#line 47 "src/modules/smack.c"
extern s16 D_smack_00401630[];
/* Return zero for player indices at least four; otherwise return the selected
 * signed halfword from the shared four-entry table.
 * RE_UNKNOWN: table meaning and refresh lifetime require consumers. */
#line 49 "src/modules/smack.c"
s32 smackGetPlayerValue(u8 player) {
    if (player >= 4) { return 0; }
    return D_smack_00401630[player];
}
#line 53 "src/modules/smack.c"
#line 48 "src/modules/smack.c"

