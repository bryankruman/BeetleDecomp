// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
extern f32 D_uvisect_rom_004078B0;
extern s16 D_uvisect_rom_004078C8;
extern s16 D_uvisect_rom_004078CA;
extern s16 D_uvisect_rom_004078D4;
extern s16 D_uvisect_rom_004078D6;
extern s32 D_uvisect_rom_004077C0;
extern s32 D_uvisect_rom_00407898;
extern s32 D_uvisect_rom_004078CC;
extern s32 D_uvisect_rom_004078D0;
extern s32 D_uvisect_rom_004078D8;
extern s32 D_uvisect_rom_004078DC;
extern s32 D_uvisect_rom_004078E0;
extern s32 D_uvisect_rom_004078E4;
extern s32 D_uvisect_rom_004078E8;
extern s32 D_uvisect_rom_004078EC;
extern u8 D_uvisect_rom_00407880;
extern s32 D_uvisect_rom_0040787C;
extern u16 D_uvisect_rom_00407894;
extern f32 D_uvisect_rom_004077B8;
extern s16 D_uvisect_rom_00407820;
extern s32 D_uvisect_rom_004077BC;
extern s32 D_uvisect_rom_004078C4;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/__entrypoint_func_uvisect_rom_400000.s")

void func_uvisect_rom_004003CC(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x46564543);
    uvUnloadModule(0x4D415448);
    uvUnloadModule(0x444F424A);
    uvUnloadModule(0x54455252);
    uvUnloadModule(0x54455854);
    uvUnloadModule(0x49534354);
    uvUnloadModule(0x4D4F444C);
    uvUnloadModule(0x51455259);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400450.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004004F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004005D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004007F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400898.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400920.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400930.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004009A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004009F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004009FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400A40.s")

s32 func_uvisect_rom_00400B80(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x18);
}

s32 func_uvisect_rom_00400B88(s32 arg0) {
    return arg0 + 0x1C;
}

void func_uvisect_rom_00400B90(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x8) = arg1;
}

s32 func_uvisect_rom_00400B98(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x8);
}

void func_uvisect_rom_00400BA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_uvisect_rom_004078E0 = arg0;
    D_uvisect_rom_004078E4 = arg1;
    D_uvisect_rom_004078E8 = arg2;
    D_uvisect_rom_004078EC = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400BC4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00400DC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004013B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004013F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004014FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00401558.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004017D8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00401DA4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004024AC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00402AC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00402B5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403054.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040318C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403208.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040344C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004036A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040397C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403AB4.s")

void func_uvisect_rom_00403CAC(s32 arg0, s32 arg1)
{
  s32 *new_var;
  new_var = &arg0;
  D_uvisect_rom_004077BC = (*new_var) & 0xFFFF;
  D_uvisect_rom_004078C4 = arg1;
}

#line 130 "src/modules/uvisect_rom.c"
/* Append a value only if absent, preserving the original 16-bit scan index.
 * The original routine performs no capacity check; callers own the list limits. */
void uvIsectAppendUniqueValue(s32 value) {
    u16 index;
    for (index = 0; index < D_uvisect_rom_0040787C; index++) {
        if (value == ((s32 *)&D_uvisect_rom_00407880)[index]) return;
    }
    ((s32 *)&D_uvisect_rom_00407880)[D_uvisect_rom_0040787C] = value;
    D_uvisect_rom_0040787C++;
}
#line 131 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403D2C.s")

s32 func_uvisect_rom_00403D70(s32 arg0) {
    if (D_uvisect_rom_0040787C < arg0) {
        return 0;
    }
    return *(s32 *)((u8 *)&D_uvisect_rom_00407880 + arg0 * 4);
}

s32 func_uvisect_rom_00403DA0(void) {
    return D_uvisect_rom_0040787C;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403DAC.s")

u16 func_uvisect_rom_00403E00(void) {
    return D_uvisect_rom_00407894;
}

f32 func_uvisect_rom_00403E0C(void) {
    return D_uvisect_rom_004077B8;
}

void func_uvisect_rom_00403E18(f32 arg0) {
    D_uvisect_rom_004077B8 = arg0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403E24.s")

void func_uvisect_rom_00403E80(void *arg0, s8 arg1) {
    *(s8 *)((u8 *)arg0 + 0x10) = arg1;
}

s32 func_uvisect_rom_00403E8C(void *arg0) {
    return *(u8 *)((u8 *)arg0 + 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403E94.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00403F38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404100.s")

#line 175 "src/modules/uvisect_rom.c"
/* Copy the complete 88-byte intersection record, including opaque fields. */
typedef struct { u32 words[22]; } IsectCopyRecord88;
void uvIsectCopyRecord(IsectCopyRecord88 *destination, IsectCopyRecord88 *source) {
    *destination = *source;
}
#line 176 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040423C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004045A8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004048DC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404A34.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404D74.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00404ED4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405124.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004054F4.s")

#line 195 "src/modules/uvisect_rom.c"
/* Return the nearest side in the XY projection of the bounding box: +1/+2
 * select maximum X/Y and -1/-2 minimum X/Y. Equal distances keep the first side. */
typedef struct {
    f32 minimum[3];
    f32 maximum[3];
} IsectBounds;
s32 uvIsectFindNearestBoxSide(IsectBounds *bounds, f32 *point) {
    f32 distance;
    f32 candidate;
    s32 side;
    distance = bounds->maximum[0] - point[0];
    side = 1;
    candidate = bounds->maximum[1] - point[1];
    if (candidate < distance) { distance = candidate; side = 2; }
    candidate = point[0] - bounds->minimum[0];
    if (candidate < distance) { distance = candidate; side = -1; }
    candidate = point[1] - bounds->minimum[1];
    if (candidate < distance) side = -2;
    return side;
}
#line 196 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405698.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405794.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405C8C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00405EDC.s")

void func_uvisect_rom_004071E4(void) {
    D_uvisect_rom_00407820 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004071F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407250.s")

void func_uvisect_rom_00407328(void *arg0, s32 arg1, f32 arg2) {
    if ((arg0 != NULL) && (arg1 == 1)) {
        (*(s32 *)((u8 *)arg0 + 0x4)) = (s32) arg2;
    }
}

f32 func_uvisect_rom_00407354(void *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return -1.0f;
    }
    if (arg1 == 1) {
        return (f32) (*(s32 *)((u8 *)arg0 + 0x4));
    }
    return -1.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407398.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_0040740C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407468.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004074A0.s")

s32 func_uvisect_rom_004074F0(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x4)) != 0) {
        return 0;
    }
    return (*(s32 *)((u8 *)arg0 + 0x8));
}

#line 247 "src/modules/uvisect_rom.c"
typedef struct UvIntersectionPayload_s { s32 unk0; s32 kind; u8 payload[1]; } UvIntersectionPayload;
/* Only kind-one intersection records expose their inline payload. */
void *uvIsectGetKindOnePayload(UvIntersectionPayload *record) {
 if (record == NULL) return NULL;
 if (record->kind != 1) return NULL;
 return record->payload;
}
#line 248 "src/modules/uvisect_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_00407554.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvisect_rom/func_uvisect_rom_004075E8.s")

