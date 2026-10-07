// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

/* Prefix views grounded in collection indexing and link updates. */
typedef struct DynLinkedCollection DynLinkedCollection;
typedef struct DynLinkedNode {
    u8 unk00[4];
    s32 value04;
    u8 unk08[0xC];
    DynLinkedCollection *linkedCollection;
} DynLinkedNode;
struct DynLinkedCollection {
    u8 unk00[0x94];
    s32 count;
    DynLinkedNode *members[10];
};
typedef struct {
    u8 unk00[0xF748];
    s32 count;
    void *members[20];
} DynSecondaryCollection;


#include "uvfvec_rom.h"
extern UvFVec_Rom_Exports *D_uvdyn_rom_00411F74;
/* Prefix view: field meanings beyond observed copy/flag behavior are unknown. */
typedef struct {
    u8 unk00[0x12B6];
    u16 parameterFlag;
    f32 value12B8;
    f32 value12BC;
    Vec3F vector12C0;
    u8 unk12CC[0x10];
    Vec3F vector12DC;
    f32 value12E8;
} DynVectorFields;
typedef struct { Vec3F vector; f32 scalar; } DynVectorScalar;
typedef struct { s32 value; s32 unk04; s16 unk08; u16 result; } DynCallbackRequest;
typedef struct {
    u8 unk00[0x156C];
    void (*callback)(DynCallbackRequest *, void *);
    u8 unk1570[0x24];
    void *callbackContext;
} DynCallbackPrefix;

extern s32 D_uvdyn_rom_00411BDC[];
extern s32 D_uvdyn_rom_00411D48[];
extern void *D_uvdyn_rom_00411B1C;
extern f32 *D_uvdyn_rom_00411DB8;
extern u16 D_uvdyn_rom_00411DE8;
extern u16 D_uvdyn_rom_00411F18;
extern u16 D_uvdyn_rom_00411F1A;
extern u16 D_uvdyn_rom_00411E68;
void func_uvdyn_rom_004005F4();
void func_uvdyn_rom_00400664();
void func_uvdyn_rom_004006D4(s32 arg0, f32 arg1);
f32 func_uvdyn_rom_004006EC(s32 arg0);
void func_uvdyn_rom_0040071C();
void func_uvdyn_rom_004009BC();
void func_uvdyn_rom_00400A14();
void func_uvdyn_rom_00400C08();
void func_uvdyn_rom_00400E40();
void func_uvdyn_rom_00401014();
void func_uvdyn_rom_00401D54();
void func_uvdyn_rom_0040232C();
void func_uvdyn_rom_00402BD4();
void func_uvdyn_rom_00402E38();
void func_uvdyn_rom_00403294();
void func_uvdyn_rom_004033F4();
void func_uvdyn_rom_004034C8();
void func_uvdyn_rom_00403574();
void func_uvdyn_rom_004035A0();
void func_uvdyn_rom_00403724();
void func_uvdyn_rom_004037F0();
void func_uvdyn_rom_00403860();
void func_uvdyn_rom_00403A1C();
void func_uvdyn_rom_00403C38();
void func_uvdyn_rom_00403D90();
void func_uvdyn_rom_00403F98();
void func_uvdyn_rom_00404018();
void func_uvdyn_rom_004041CC();
s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1);
void func_uvdyn_rom_004043E0();
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output);
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection);
void func_uvdyn_rom_004045B0();
void func_uvdyn_rom_00404674();
s32 func_uvdyn_rom_004046B4();
void * func_uvdyn_rom_004046FC();
void func_uvdyn_rom_00404750();
void func_uvdyn_rom_00404834();
void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_uvdyn_rom_0040495C();
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second);
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second);
void func_uvdyn_rom_00404AF0();
void func_uvdyn_rom_00404BC0();
void func_uvdyn_rom_00404C60();
void func_uvdyn_rom_00404CE8();
void func_uvdyn_rom_00404DE0();
void func_uvdyn_rom_00404F08();
void func_uvdyn_rom_00404F34();
void func_uvdyn_rom_00404F60();
u16 uvDynInvokeValueCallback(DynCallbackPrefix *record, s32 value);
void func_uvdyn_rom_00404FE0();
void func_uvdyn_rom_0040500C();
void func_uvdyn_rom_00405040();
void func_uvdyn_rom_004050EC();
void func_uvdyn_rom_00407594();
void func_uvdyn_rom_0040771C();
void func_uvdyn_rom_004079B8();
void func_uvdyn_rom_00407C04();
void func_uvdyn_rom_00407C98();
void func_uvdyn_rom_00407DF0();
void func_uvdyn_rom_004088EC();
void func_uvdyn_rom_00408ACC();
void func_uvdyn_rom_00408DC8();
void func_uvdyn_rom_00409010();
void func_uvdyn_rom_00409318();
void func_uvdyn_rom_004094CC();
void func_uvdyn_rom_0040954C();
void func_uvdyn_rom_0040981C();
void func_uvdyn_rom_00409960();
s32 func_uvdyn_rom_00409A48();
void func_uvdyn_rom_00409A7C();
void func_uvdyn_rom_00409AF0();
void func_uvdyn_rom_00409BD4();
void func_uvdyn_rom_00409CE4();
void func_uvdyn_rom_00409E18();
void func_uvdyn_rom_0040A05C();
void func_uvdyn_rom_0040A0D8();
void func_uvdyn_rom_0040A188();
void func_uvdyn_rom_0040AFAC();
void func_uvdyn_rom_0040AFD8();
void func_uvdyn_rom_0040B00C();
void func_uvdyn_rom_0040B08C();
void func_uvdyn_rom_0040B75C();
void func_uvdyn_rom_0040B838();
void func_uvdyn_rom_0040BAA0();
void func_uvdyn_rom_0040BAD4();
void func_uvdyn_rom_0040BB5C();
void func_uvdyn_rom_0040BC48();
void func_uvdyn_rom_0040BCE4();
void func_uvdyn_rom_0040BD14();
void func_uvdyn_rom_0040BFD8();
void uvDynInsertUniqueLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node);
void uvDynRemoveLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node);
void uvDynAppendUniqueSecondaryValue(DynSecondaryCollection *collection, void *value);
void func_uvdyn_rom_0040C20C();
void func_uvdyn_rom_0040C2C4();
void func_uvdyn_rom_0040C3B8();
void func_uvdyn_rom_0040C464();
void func_uvdyn_rom_0040C570();
void func_uvdyn_rom_0040E4E8();
void func_uvdyn_rom_0040E8E8();
void func_uvdyn_rom_0040F78C();
void func_uvdyn_rom_0040FC88();
void func_uvdyn_rom_00410250();
void func_uvdyn_rom_004107FC();
void func_uvdyn_rom_00410A88();
void func_uvdyn_rom_00410AEC();
void func_uvdyn_rom_00410C40();
void func_uvdyn_rom_00410D54();
void func_uvdyn_rom_00410D80();
void func_uvdyn_rom_00410E24();
void func_uvdyn_rom_00410EF0();
void func_uvdyn_rom_00410F60();
void func_uvdyn_rom_00411014(void *arg0, s32 arg1, f32 arg2);
void func_uvdyn_rom_004110D4();
void func_uvdyn_rom_00411148();
void func_uvdyn_rom_00411300();
void func_uvdyn_rom_0041138C();
void func_uvdyn_rom_00411454();
s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1);
void func_uvdyn_rom_004116A0();
void func_uvdyn_rom_00411744();
void func_uvdyn_rom_004117C0();
void func_uvdyn_rom_004118D0();
void func_uvdyn_rom_00411954();
extern f32 D_uvdyn_rom_00411DB4;
extern u16 D_uvdyn_rom_00411EC0;
extern u16 D_uvdyn_rom_00411EC2;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/__entrypoint_func_uvdyn_rom_400000.s")

void func_uvdyn_rom_00400564(void) {
    uvUnloadModule(0x464D5458);
    uvUnloadModule(0x46564543);
    uvUnloadModule(0x51554154);
    uvUnloadModule(0x4D415448);
    uvUnloadModule(0x69736374);
    uvUnloadModule(0x444F424A);
    uvUnloadModule(0x54455252);
    uvUnloadModule(0x49534354);
    uvUnloadModule(0x4D4F444C);
    uvUnloadModule(0x51455259);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004005F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400664.s")

void func_uvdyn_rom_004006D4(s32 arg0, f32 arg1) {
    if (arg0 == 0) {
        D_uvdyn_rom_00411DB4 = arg1;
    }
}

f32 func_uvdyn_rom_004006EC(s32 arg0) {
    if (arg0 == 0) {
        return D_uvdyn_rom_00411DB4;
    }
    return -1.0f;
}

f32 *func_uvdyn_rom_00400710(void) {
    return &D_uvdyn_rom_00411DB4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040071C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004009BC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400A14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400C08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00400E40.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401014.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00401D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040232C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00402E38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403294.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004033F4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004034C8.s")

void func_uvdyn_rom_00403574(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411DE8 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004035A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403724.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004037F0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403860.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403A1C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403C38.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403D90.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00403F98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404018.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004041CC.s")

s32 func_uvdyn_rom_00404384(s32 arg0, s32 arg1) {
    s32 sp4;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg1) {                                 /* irregular */
    case 6:
        sp4 = arg0 + 0x12EC;
        break;
    case 16:
        sp4 = arg0 + 0x142C;
        break;
    case 15:
        sp4 = arg0 + 0x13EC;
        break;
    }
    return sp4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004043E0.s")

void func_uvdyn_rom_004044D0(void *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + 0x14B8) = arg1;
}

#line 279 "src/modules/uvdyn_rom.c"
/* Copy the vector at 0x12DC and scalar at 0x12E8 into the output. Null
 * records leave output unchanged; the values have no established gameplay names. */
void uvDynGetVectorScalar12DC(DynVectorFields *record, DynVectorScalar *output) {
    if (record != NULL) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(&output->vector, &record->vector12DC);
        output->scalar = record->value12E8;
    }
}
#line 280 "src/modules/uvdyn_rom.c"

#line 281 "src/modules/uvdyn_rom.c"
/* Change the node's linked collection, removing its old membership first.
 * A nonnull destination whose count equals ten is rejected before checking for
 * an unchanged link. Null clears the link; original count invariants are required. */
void uvDynSetLinkedCollection(DynLinkedNode *node, DynLinkedCollection *collection) {
    if (collection != NULL && collection->count == 10) {
        return;
    }
    if (node->linkedCollection != NULL) {
        if (collection == node->linkedCollection) {
            return;
        }
        uvDynRemoveLinkedNode(node->linkedCollection, node);
    }
    node->linkedCollection = collection;
    if (collection != NULL) {
        uvDynInsertUniqueLinkedNode(collection, node);
    }
}
#line 282 "src/modules/uvdyn_rom.c"

s32 func_uvdyn_rom_004045A8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x14);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004045B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404674.s")

s32 func_uvdyn_rom_004046B4(void *arg0, s32 arg1) {
    if (*(s32 *)((u8 *)arg0 + 0x18) < arg1) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x1C);
}

s32 func_uvdyn_rom_004046E0(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x18);
}

void *func_uvdyn_rom_004046FC(void *arg0, s32 arg1) {
    if (*(s32 *)((u8 *)arg0 + 0x38) < arg1) {
        return NULL;
    }
    return (void *)((u8 *)arg0 + arg1 * 0x170 + 0x3AC);
}

s32 func_uvdyn_rom_00404734(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x38);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404750.s")

s32 func_uvdyn_rom_0040481C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x28);
}

void func_uvdyn_rom_00404824(void *arg0, s32 arg1) {
    *(s32 *)((u8 *)arg0 + 0x2C) = arg1;
}

s32 func_uvdyn_rom_0040482C(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x2C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404834.s")

void func_uvdyn_rom_0040492C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
}

s32 func_uvdyn_rom_00404940(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x120C);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040495C.s")

#line 347 "src/modules/uvdyn_rom.c"
/* Enable the parameter flag, copy the input vector and store the two scalar
 * parameters at their original offsets. The original requires a valid record. */
void uvDynSetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 first, f32 second) {
    record->parameterFlag = 1;
    D_uvdyn_rom_00411F74->uvVec3FCopy(&record->vector12C0, vector);
    record->value12B8 = first;
    record->value12BC = second;
}
#line 348 "src/modules/uvdyn_rom.c"

#line 349 "src/modules/uvdyn_rom.c"
/* Return the original parameter flag. Only when nonzero, copy the vector
 * and two scalars; reload the flag after the external copy as the original does. */
u16 uvDynGetVectorParameters(DynVectorFields *record, Vec3F *vector, f32 *first, f32 *second) {
    u16 flag;
    flag = record->parameterFlag;
    if (flag != 0) {
        D_uvdyn_rom_00411F74->uvVec3FCopy(vector, &record->vector12C0);
        *first = record->value12B8;
        *second = record->value12BC;
        flag = record->parameterFlag;
    }
    return flag;
}
#line 350 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00404ACC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x12B6) = 0;
}

s32 func_uvdyn_rom_00404AD4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x1274);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404AF0.s")

u16 func_uvdyn_rom_00404BA4(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *(u16 *)((u8 *)arg0 + 0x12DA);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404BC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404C60.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404CE8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00404DE0.s")

void func_uvdyn_rom_00404F08(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x1574);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x159C));
    }
}

void func_uvdyn_rom_00404F34(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x1558);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x1580));
    }
}

void func_uvdyn_rom_00404F60(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x1568);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x1590));
    }
}

#line 400 "src/modules/uvdyn_rom.c"
/* Invoke the optional value callback with the original 12-byte request:
 * value, -1, zero and an initial result of one. Return its 16-bit result,
 * or one when absent. Cache the callback once before initializing the request. */
u16 uvDynInvokeValueCallback(DynCallbackPrefix *record, s32 value) {
    void (*callback)(DynCallbackRequest *, void *);
    DynCallbackRequest request;
    callback = record->callback;
    if (callback != NULL) {
        request.result = 1;
        request.value = value;
        request.unk04 = -1;
        request.unk08 = 0;
        callback(&request, record->callbackContext);
        return request.result;
    }
    return 1;
}
#line 401 "src/modules/uvdyn_rom.c"

void func_uvdyn_rom_00404FE0(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x1560);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x1588));
    }
}

void func_uvdyn_rom_0040500C(void *arg0, s32 arg1) {
    void (*fp)(s32, s32) = *(void (**)(s32, s32))((u8 *)arg0 + 0x1570);
    if (fp != NULL) {
        fp(arg1, *(s32 *)((u8 *)arg0 + 0x1598));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00405040.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004050EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407594.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040771C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004079B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C04.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407C98.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00407DF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004088EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408ACC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00408DC8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409010.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409318.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004094CC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040954C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040981C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409960.s")

u16 func_uvdyn_rom_00409A40(void *arg0) {
    return *(u16 *)((u8 *)arg0 + 0x12D6);
}

s32 func_uvdyn_rom_00409A48(void *arg0)
{
  int new_var;
  s32 new_var3;
  u8 *new_var2;
 do { } while (0);
  new_var2 = ((u8 *) arg0) + 0x14;
  new_var3 = *((s32 *) new_var2);
  return (new_var3 + ((*((u16 *) (((u8 *) arg0) + 0x12CE))) * 0x28)) + ((long) (new_var = 0x6EC0));
}

void func_uvdyn_rom_00409A68(void) {
    D_uvdyn_rom_00411EC0 = 0;
    D_uvdyn_rom_00411EC2 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409A7C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409AF0.s")

void func_uvdyn_rom_00409BC0(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x23C) = 1;
}

s32 func_uvdyn_rom_00409BCC(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409BD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409CE4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00409E18.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A05C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A0D8.s")

s32 func_uvdyn_rom_0040A180(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0xC);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040A188.s")

void func_uvdyn_rom_0040AFAC(void *arg0) {
    void (*fp)(void *, s32) = *(void (**)(void *, s32))((u8 *)arg0 + 0x244);
    if (fp != NULL) {
        fp(arg0, *(s32 *)((u8 *)arg0 + 0x25C));
    }
}

void func_uvdyn_rom_0040AFD8(void *arg0, s32 arg1) {
    void (*fp)(s32, s32) = *(void (**)(s32, s32))((u8 *)arg0 + 0x248);
    if (fp != NULL) {
        fp(arg1, *(s32 *)((u8 *)arg0 + 0x260));
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B00C.s")

void func_uvdyn_rom_0040B070(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg0 == NULL) {
        return;
    }
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x240) = arg2;
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x258) = arg3;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B08C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B75C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040B838.s")

void func_uvdyn_rom_0040BAA0(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411F18 = 0;
    D_uvdyn_rom_00411F1A = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BAD4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BB5C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BC48.s")

void func_uvdyn_rom_0040BCE4(void *arg0) {
    func_uvdyn_rom_0040C2C4(arg0);
    func_uvdyn_rom_0040C570(arg0);
    func_uvdyn_rom_0040C3B8(arg0);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BD14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040BFD8.s")

#line 550 "src/modules/uvdyn_rom.c"
/* Insert a unique node before the first member whose value04 is not -1,
 * or append if none qualifies. Preserve member order while shifting the tail.
 * value04's gameplay meaning is unknown. This helper has no capacity check;
 * the association setter rejects a destination count of ten. */
void uvDynInsertUniqueLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 insertionIndex;
    s32 index;
    insertionIndex = collection->count;
    for (index = 0; index < collection->count; index++) {
        if (node == collection->members[index]) {
            return;
        }
        if (insertionIndex == collection->count && collection->members[index]->value04 != -1) {
            insertionIndex = index;
        }
    }
    for (index = collection->count - 1; index >= insertionIndex; index--) {
        collection->members[index + 1] = collection->members[index];
    }
    collection->members[insertionIndex] = node;
    collection->count++;
}
#line 551 "src/modules/uvdyn_rom.c"

#line 552 "src/modules/uvdyn_rom.c"
/* Remove the first matching node and compact the remaining members.
 * Both scans use the original 16-bit index; the shifting loop reloads the count.
 * An absent node leaves the collection unchanged. */
void uvDynRemoveLinkedNode(DynLinkedCollection *collection, DynLinkedNode *node) {
    s32 foundIndex;
    u16 index;
    foundIndex = -1;
    for (index = 0; index < collection->count; index++) {
        if (node == collection->members[index]) {
            foundIndex = index;
            break;
        }
    }
    if (foundIndex != -1) {
        for (index = foundIndex; index < collection->count - 1; index++) {
            collection->members[index] = collection->members[index + 1];
        }
        collection->count--;
    }
}
#line 553 "src/modules/uvdyn_rom.c"

#line 554 "src/modules/uvdyn_rom.c"
/* Append a unique opaque secondary value unless the count equals twenty.
 * Preserve the original 16-bit scan and equality-only capacity guard; the
 * surrounding object's full size and the values' gameplay meaning are unknown. */
void uvDynAppendUniqueSecondaryValue(DynSecondaryCollection *collection, void *value) {
    u16 index;
    for (index = 0; index < collection->count; index++) {
        if (value == collection->members[index]) {
            return;
        }
    }
    if (collection->count == 20) {
        return;
    }
    collection->members[collection->count] = value;
    collection->count++;
}
#line 555 "src/modules/uvdyn_rom.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C20C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C2C4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C3B8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C464.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040C570.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E4E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040E8E8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040F78C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0040FC88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410250.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004107FC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410A88.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410AEC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410C40.s")

void func_uvdyn_rom_00410D54(void) {
    D_uvdyn_rom_00411DB8 = func_uvdyn_rom_00400710();
    D_uvdyn_rom_00411E68 = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410D80.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410E24.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410EF0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00410F60.s")

void func_uvdyn_rom_00411014(void *arg0, s32 arg1, f32 arg2) {
    if (arg0 != NULL) {
        switch (arg1) {                             /* irregular */
        case 0:
            (*(s32 *)((u8 *)arg0 + 0xC)) = (s32) arg2;
            return;
        case 9:
            (*(s16 *)((u8 *)arg0 + 0x4)) = (s16) (u32) arg2;
            break;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004110D4.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411148.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411300.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_0041138C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411454.s")

s32 func_uvdyn_rom_00411644(s32 arg0, s32 arg1) {
    s32 sp4;

    if (arg0 == 0) {
        return 0;
    }
    switch (arg1) {                                 /* irregular */
    case 3:
        sp4 = arg0 + 0x18;
        break;
    case 4:
        sp4 = arg0 + 0xD8;
        break;
    case 5:
        sp4 = arg0 + 0x98;
        break;
    }
    return sp4;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004116A0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411744.s")

s32 func_uvdyn_rom_004117B8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 8);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004117C0.s")

s32 func_uvdyn_rom_004118C8(void *arg0) {
    return *(s32 *)((u8 *)arg0 + 0x10);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_004118D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/uvdyn_rom/func_uvdyn_rom_00411954.s")

