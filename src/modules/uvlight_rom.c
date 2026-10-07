// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "module.h"

typedef struct LightsSettings_s {
    s32 unk0;
    s32 unk4;
    u8 unk8;
} LightsSettings;

void uvLightModuleCleanup(void);
void uvLightResetSelectionCache(s32 arg0);
void uvLightSwapBuffers(s32 arg0);
void uvSetLightColor(s32 n, u32 packedColor);
void uvLoadLights(void);
void uvLightEmitDefaultLights(void);
void func_uvlight_rom_004008D4(s32 arg0);
s32 func_uvlight_rom_00400B64(void);
void func_uvlight_rom_00400C60(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_uvlight_rom_00400D90(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_uvlight_rom_00400EDC(s32 arg0, s32 arg1, Vec3F *arg2);
void func_uvlight_rom_00400FB8(Vec3F *arg0, f32 *arg1, f32 *arg2);
s32 uvLightAllocateSlotIndex(void);
void uvLightSelectBufferSlot(s32 arg0);
void func_uvlight_rom_00401260(s32 *arg0, f32 arg1, f32 arg2, f32 arg3);
UnkStruct_uvlight_rom_00401758 *uvLightGetRecord(s32 arg0);
s32 func_uvlight_rom_00401340(UnkStruct_uvlight_rom_00401758 *arg0);
void uvLightReleaseRecord(s32 arg0);
void uvLightSelectRecord(s32 arg0);

// .data
s32 D_uvlight_rom_004016E0 = 0xFFFFFFFF;
Vec3F D_uvlight_rom_004016E4 = { 0.0f, 0.0f, 1.0f };
Vec3F D_uvlight_rom_004016F0 = { 0.0f, 0.0f, 0.0f };
Vec3F D_uvlight_rom_004016FC = { 0.0f, 0.0f, 1.0f };

// .bss
Ambient sLightAmbient;
Light sLight;
Light *D_uvlight_rom_00401738;
Light* D_uvlight_rom_0040173C;
Light *D_uvlight_rom_00401740;
s32 D_uvlight_rom_00401744;
u8 D_uvlight_rom_00401748;
s32 D_uvlight_rom_0040174C;
u8 D_uvlight_rom_00401750;
u8 D_uvlight_rom_00401751;
u8 sNumLights;
u8 D_uvlight_rom_00401753;
u8 D_uvlight_rom_00401754;
UnkStruct_uvlight_rom_00401758 *D_uvlight_rom_00401758;
s32 D_uvlight_rom_0040175C; // unreferenced padding
UnkStruct_uvlight_rom_00401758 D_uvlight_rom_00401760;
u8 D_uvlight_rom_00401794;
s32 D_uvlight_rom_00401798;
s32 *D_uvlight_rom_0040179C;
s32 *D_uvlight_rom_004017A0;
s32 D_uvlight_rom_004017A4; // more padding
f32 D_uvlight_rom_004017A8[3];
f32 D_uvlight_rom_004017B8[3];
s32 *D_uvlight_rom_004017C4;
s32 *D_uvlight_rom_004017C8;
UvFVec_Rom_Exports *D_uvlight_rom_004017CC;
UvGfxMgr_Exports *D_uvlight_rom_004017D0;
UvCback_Exports *D_uvlight_rom_004017D4;

void __entrypoint_func_uvlight_rom_400000(UvLights_Exports *exports);

#define BAR_gSPLightColor(pkt, n, col)                                                                 \
    {                                                                                                  \
        gMoveWd(pkt, G_MW_LIGHTCOL, n, col);                                                           \
        gMoveWd(pkt, G_MW_LIGHTCOL, n + 4, col);                                                       \
    }

void __entrypoint_func_uvlight_rom_400000(UvLights_Exports *exports) {
    s32 pad;
    s32 i;
    s32 j;
    LightsSettings *settings;
    Vec3F sp54;
    Vec3F sp48;

    uvUpdateFileAllocPtr(exports);
    exports->uvLightModuleCleanup = uvLightModuleCleanup;
    exports->func_uvlight_rom_00401340 = func_uvlight_rom_00401340;
    exports->func_uvlight_rom_004008D4 = func_uvlight_rom_004008D4;
    exports->uvLightReleaseRecord = uvLightReleaseRecord;
    exports->func_uvlight_rom_00400B64 = func_uvlight_rom_00400B64;
    exports->uvLightSelectRecord = uvLightSelectRecord;
    exports->func_uvlight_rom_00400C60 = func_uvlight_rom_00400C60;
    exports->func_uvlight_rom_00400D90 = func_uvlight_rom_00400D90;
    exports->func_uvlight_rom_00400EDC = func_uvlight_rom_00400EDC;
    exports->func_uvlight_rom_00400FB8 = func_uvlight_rom_00400FB8;
    exports->uvLightAllocateSlotIndex = uvLightAllocateSlotIndex;
    exports->uvLightSelectBufferSlot = uvLightSelectBufferSlot;
    exports->uvLightGetRecord = uvLightGetRecord;
#ifdef __sgi
#line 1
#endif
    sp54 = D_uvlight_rom_004016E4;
    sp48 = D_uvlight_rom_004016F0;
    settings = uvGetSystemProp(SYSTEM_PROPID_LIGHTS_SETTINGS);
    if (settings == NULL) {
        D_uvlight_rom_00401794 = 0xA;
        D_uvlight_rom_00401748 = 0x28;
        D_uvlight_rom_00401751 = 7;
    } else {
        if (settings->unk0 != 0) {
            D_uvlight_rom_00401794 = settings->unk0;
        } else {
            D_uvlight_rom_00401794 = 0xA;
        }
        if (settings->unk4 != 0) {
            D_uvlight_rom_00401748 = settings->unk4;
        } else {
            D_uvlight_rom_00401748 = 0x28;
        }
        if (settings->unk8 != 0) {
            D_uvlight_rom_00401751 = settings->unk8;
        } else {
            D_uvlight_rom_00401751 = 7;
        }
    }
    D_uvlight_rom_004017D0 = uvLoadModule('GMGR');
    D_uvlight_rom_004017CC = uvLoadModule('FVEC');
    D_uvlight_rom_004017D4 = uvLoadModule('CBCK');
    D_uvlight_rom_00401740 = _uvMemAlloc(D_uvlight_rom_00401748 * 0x10 * D_uvlight_rom_00401751, 0x10U);
    D_uvlight_rom_00401744 = _uvMemAlloc(D_uvlight_rom_00401748 * 0x10 * D_uvlight_rom_00401751, 0x10U);
    D_uvlight_rom_00401738 = _uvMemAlloc(D_uvlight_rom_00401748 * 8, 0x10);
    D_uvlight_rom_0040173C = _uvMemAlloc(D_uvlight_rom_00401748 * 8, 0x10);
    D_uvlight_rom_00401758 = _uvMemAllocAlign8(D_uvlight_rom_00401794 * 0x34);
    D_uvlight_rom_0040179C = _uvMemAllocAlign8(D_uvlight_rom_00401748 * D_uvlight_rom_00401794 * 4);
    D_uvlight_rom_004017A0 =
        _uvMemAllocAlign8(D_uvlight_rom_00401748 * D_uvlight_rom_00401794 * 4 * D_uvlight_rom_00401751);
    D_uvlight_rom_004017C4 = _uvMemAllocAlign8(D_uvlight_rom_00401794 * 4);
    D_uvlight_rom_004017C8 = _uvMemAllocAlign8(D_uvlight_rom_00401794 * 4);
    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        D_uvlight_rom_00401758[i].refCount = 0;
    }

    for (j = 0; j < D_uvlight_rom_00401748; j++) {
        for (i = 0; i < D_uvlight_rom_00401751; i++) {
            func_uvlight_rom_00400D90(i, j, 0.0f, 0.0f, 0.0f);
            func_uvlight_rom_00400EDC(i, j, &sp54);
        }
        func_uvlight_rom_00400C60(j, 0.0f, 0.0f, 0.0f);
    }

    func_uvlight_rom_00400FB8(&sp54, (f32*)&sp48, (f32*)&sp48);
    D_uvlight_rom_00401750 = 0;
    sNumLights = 0;
    D_uvlight_rom_00401753 = 0;
    D_uvlight_rom_00401754 = 0;
    D_uvlight_rom_004017D4->uvAddCallback(
        D_uvlight_rom_004017D0->uvGfxGetCallbackList(1), (s32) uvLightResetSelectionCache, 0, 0);
    D_uvlight_rom_004017D4->uvAddCallback(
        D_uvlight_rom_004017D0->uvGfxGetCallbackList(2), (s32) uvLightSwapBuffers, 0, 0);
}

#line 62 "src/modules/uvlight_rom.c"
/* Free the seven original light buffers and unload graphics, vector and callback
 * dependencies. Preserve the original allocation ownership and cleanup scope. */
void uvLightModuleCleanup(void) {
    _uvMemFree(D_uvlight_rom_00401738);
    _uvMemFree(D_uvlight_rom_00401740);
    _uvMemFree((void *) D_uvlight_rom_0040173C);
    _uvMemFree((void *) D_uvlight_rom_00401744);
    _uvMemFree(D_uvlight_rom_00401758);
    _uvMemFree(D_uvlight_rom_0040179C);
    _uvMemFree(D_uvlight_rom_004017A0);
    uvUnloadModule('GMGR');
    uvUnloadModule('FVEC');
    uvUnloadModule('CBCK');
}
#line 74 "src/modules/uvlight_rom.c"

#line 75 "src/modules/uvlight_rom.c"
/* Invalidate cached light selections and clear the pending light-state flag.
 * The callback argument is unused by the original implementation. */
void uvLightResetSelectionCache(s32 unusedContext) {
    D_uvlight_rom_00401760.unk2C = D_uvlight_rom_00401760.unk28 = D_uvlight_rom_00401760.unk24 =
        D_uvlight_rom_00401798 = D_uvlight_rom_0040174C = -1;
    D_uvlight_rom_00401754 = 0;
}
#line 80 "src/modules/uvlight_rom.c"

void uvLightSwapBuffers(s32 arg0) {
    s32 temp_t6;
    s32 temp_t7;

    temp_t6 = D_uvlight_rom_00401738;
    D_uvlight_rom_00401738 = D_uvlight_rom_0040173C;
    temp_t7 = D_uvlight_rom_00401740;
    D_uvlight_rom_0040173C = temp_t6;
    D_uvlight_rom_00401740 = D_uvlight_rom_00401744;
    D_uvlight_rom_00401744 = temp_t7;
}

void uvSetLightColor(s32 n, u32 packedColor) {
    Gfx **gdl;
    s32 lightN;

    gdl = D_uvlight_rom_004017D0->uvGetDisplayListHead();
    lightN = n * 0x18;
    gDPPipeSync(gdl[0]++);
    BAR_gSPLightColor(gdl[0]++, lightN, packedColor);
}

void uvLoadLights(void) {
    Gfx **gdl;
    Light *ptr;
    Light *ptr2;
    s32 i;

    gdl = D_uvlight_rom_004017D0->uvGetDisplayListHead();
    gDPPipeSync(gdl[0]++);
    gSPNumLights(gdl[0]++, sNumLights);

    for (i = 0; i < sNumLights; i++) {
        ptr = &D_uvlight_rom_00401740[(D_uvlight_rom_00401748 * i) + D_uvlight_rom_0040174C];
        gSPLight(gdl[0]++, ptr, i + 1);
    }

    ptr2 = (D_uvlight_rom_0040174C * 8) + (u32) D_uvlight_rom_00401738;
    gSPLight(gdl[0]++, ptr2, sNumLights + 1);

    D_uvlight_rom_00401753 = 1;
    D_uvlight_rom_00401754 = 0;
}

#line 125 "src/modules/uvlight_rom.c"
/* Synchronize the display-list pipeline, select one directional light
 * and emit the shared directional/ambient records, then set both state flags. */
void uvLightEmitDefaultLights(void) {
    Gfx **gdl;

    gdl = D_uvlight_rom_004017D0->uvGetDisplayListHead();
    gDPPipeSync(gdl[0]++);
    gSPNumLights(gdl[0]++, NUMLIGHTS_1);
    gSPLight(gdl[0]++, &sLight, 1);
    gSPLight(gdl[0]++, &sLightAmbient, 2);

    D_uvlight_rom_00401753 = 1;
    D_uvlight_rom_00401754 = 1;
}
#line 137 "src/modules/uvlight_rom.c"

void func_uvlight_rom_004008D4(s32 arg0) {
    UnkStruct_uvlight_rom_00401758 *sp34;
    s32 temp_s1;
    s32 i;
    void *temp_v0;

    if (arg0 == -2) {
        arg0 = D_uvlight_rom_004016E0;
    }
    if ((arg0 < 0) || (arg0 >= D_uvlight_rom_00401794)) {
        return;
    }

    // FAKE
    if (arg0) {}

    if (((D_uvlight_rom_0040174C < 0) || (sNumLights == 0))
        && (D_uvlight_rom_00401754 == 0)) {
        uvLightEmitDefaultLights();
    }
    if ((arg0 == D_uvlight_rom_00401798) && (D_uvlight_rom_00401753 == 0)) {
        return;
    }

    sp34 = uvLightGetRecord(arg0);
    if ((sp34->unk28 != D_uvlight_rom_00401760.unk28) || ((u8) D_uvlight_rom_00401753 != 0)) {
        if (D_uvlight_rom_00401754 == 0) {
            temp_s1 =
                ((D_uvlight_rom_00401794 * D_uvlight_rom_0040174C * D_uvlight_rom_00401751) + arg0);
            for (i = 0; i < sNumLights; i++) {
                uvSetLightColor(
                    i, (&D_uvlight_rom_004017A0[D_uvlight_rom_00401794 * i])[temp_s1]);
            }
        } else {
            // 0?
            uvSetLightColor(0, D_uvlight_rom_004017C8[arg0]);
        }
        D_uvlight_rom_00401760.unk28 = sp34->unk28;
    }
    if ((sp34->unk2C != D_uvlight_rom_00401760.unk2C) || (sp34->unk24 != D_uvlight_rom_00401760.unk24)
        || (D_uvlight_rom_00401753 != 0)) {
        if (D_uvlight_rom_00401754 == 0) {
            uvSetLightColor(
                sNumLights,
                D_uvlight_rom_0040179C[D_uvlight_rom_00401794 * D_uvlight_rom_0040174C + arg0]);
        } else {
            uvSetLightColor(LIGHT_1, D_uvlight_rom_004017C4[arg0]);
        }
        D_uvlight_rom_00401760.unk2C = sp34->unk2C;
        D_uvlight_rom_00401760.unk24 = sp34->unk24;
    }
    D_uvlight_rom_00401798 = arg0;
    D_uvlight_rom_00401753 = 0;
}

s32 func_uvlight_rom_00400B64(void) {
    s32 i;
    s32 temp_s1;
    Vec3F sp3C;

    temp_s1 = sNumLights;
    sp3C = D_uvlight_rom_004016FC;
    if (temp_s1 >= D_uvlight_rom_00401751) {
        return -1U;
    }
    for (i = 0; i < D_uvlight_rom_00401748; i++) {
        func_uvlight_rom_00400D90(temp_s1, i, 0.0f, 0.0f, 0.0f);
        func_uvlight_rom_00400EDC(temp_s1, i, &sp3C);
    }
    sNumLights++;
    return temp_s1;
}

void func_uvlight_rom_00400C60(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 i;
    s32 temp_s1;
    UnkStruct_uvlight_rom_00401758 *temp_v0;

    if ((arg0 < 0) || (arg0 >= D_uvlight_rom_00401748)) {
        return;
    }

    temp_s1 = D_uvlight_rom_00401794;
    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        temp_v0 = &D_uvlight_rom_00401758[i];
        if (temp_v0->refCount == 0) {
            continue;
        }

        func_uvlight_rom_00401260(&D_uvlight_rom_0040179C[(D_uvlight_rom_00401794 * arg0) + i],
                                  temp_v0->unk0[0] + (arg1 * temp_v0->unk18),
                                  temp_v0->unk0[1] + (arg2 * temp_v0->unk1C),
                                  temp_v0->unk0[2] + (arg3 * temp_v0->unk20));
    }
}

void func_uvlight_rom_00400D90(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 temp_s4;
    s32 i;

    UnkStruct_uvlight_rom_00401758 *temp_v0;

    if ((arg0 < 0) || (arg0 >= D_uvlight_rom_00401751) || (arg1 < 0)
        || (arg1 >= D_uvlight_rom_00401748)) {
        return;
    }

    temp_s4 =
        (D_uvlight_rom_00401794 * arg1 * D_uvlight_rom_00401751) + (arg0 * D_uvlight_rom_00401794);

    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        temp_v0 = &D_uvlight_rom_00401758[i];
        if (temp_v0->refCount == 0) {
            continue;
        }

        func_uvlight_rom_00401260(&D_uvlight_rom_004017A0[i + temp_s4], temp_v0->unkC * arg2,
                                  temp_v0->unk10 * arg3, temp_v0->unk14 * arg4);
    }
}

void func_uvlight_rom_00400EDC(s32 arg0, s32 arg1, Vec3F *arg2) {
    Vec3F sp24;
    Light *light;

    if ((arg0 < 0) || (arg0 >= D_uvlight_rom_00401751) || (arg1 < 0)
        || (arg1 >= D_uvlight_rom_00401748)) {
        return;
    }

    light = &D_uvlight_rom_00401740[(D_uvlight_rom_00401748 * arg0) + arg1];
    D_uvlight_rom_004017CC->uvVec3FNormalize(&sp24, arg2);
    light->l.dir[0] = 127.0f * sp24.x;
    light->l.dir[1] = 127.0f * sp24.y;
    light->l.dir[2] = 127.0f * sp24.z;
}

void func_uvlight_rom_00400FB8(Vec3F *arg0, f32 *arg1, f32 *arg2) {
    Vec3F sp5C;
    UnkStruct_uvlight_rom_00401758 *temp_s0;
    s32 i;
    Lights1 *a2;

    D_uvlight_rom_004017CC->uvVec3FNormalize(&sp5C, arg0);
    sLight.l.dir[0] = 127.0f * sp5C.x;
    sLight.l.dir[1] = 127.0f * sp5C.y;
    sLight.l.dir[2] = 127.0f * sp5C.z;

    for (i = 0; i < 3; i++) {
        D_uvlight_rom_004017B8[i] = arg1[i];
        D_uvlight_rom_004017A8[i] = arg2[i];
    }

    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        temp_s0 = &D_uvlight_rom_00401758[i];
        if (temp_s0->refCount == 0) {
            continue;
        }

        func_uvlight_rom_00401260(&D_uvlight_rom_004017C8[i], D_uvlight_rom_004017B8[0] * temp_s0->unkC,
                                  D_uvlight_rom_004017B8[1] * temp_s0->unk10,
                                  D_uvlight_rom_004017B8[2] * temp_s0->unk14);

        func_uvlight_rom_00401260(&D_uvlight_rom_004017C4[i],
                                  (D_uvlight_rom_004017A8[0] * temp_s0->unk18) + temp_s0->unk0[0],
                                  (D_uvlight_rom_004017A8[1] * temp_s0->unk1C) + temp_s0->unk0[1],
                                  (D_uvlight_rom_004017A8[2] * temp_s0->unk20) + temp_s0->unk0[2]);
    }
}

#line 308 "src/modules/uvlight_rom.c"
/* Return and increment the next unsigned-byte slot index, or -1 when
 * it has reached the configured capacity. Preserve the original capacity type. */
s32 uvLightAllocateSlotIndex(void) {
    u8 index;

    index = D_uvlight_rom_00401750;
    if (D_uvlight_rom_00401750 >= D_uvlight_rom_00401748) {
        return -1;
    }
    D_uvlight_rom_00401750 += 1;
    return index;
}
#line 318 "src/modules/uvlight_rom.c"

#line 319 "src/modules/uvlight_rom.c"
/* Select a light-buffer slot, rejecting IDs at or above the configured capacity.
 * Negative slots or an empty directional set suppress display-list emission. */
void uvLightSelectBufferSlot(s32 slot) {
    if (slot >= D_uvlight_rom_00401748) {
        PANIC;
    }
    
    D_uvlight_rom_0040174C = slot;

    if ((D_uvlight_rom_0040174C < 0) || (sNumLights <= 0)) {
        return;
    }
    uvLoadLights();
}
#line 331 "src/modules/uvlight_rom.c"

void func_uvlight_rom_00401260(s32 *arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;

    var_v0 = (255.0f * arg1);
    var_a1 = (255.0f * arg2);
    var_a3 = (255.0f * arg3);
    if (var_v0 < 0) {
        var_v0 = 0;
    } else if (var_v0 >= 0x100) {
        var_v0 = 0xFF;
    }
    if (var_a1 < 0) {
        var_a1 = 0;
    } else if (var_a1 >= 0x100) {
        var_a1 = 0xFF;
    }
    if (var_a3 < 0) {
        var_a3 = 0;
    } else if (var_a3 >= 0x100) {
        var_a3 = 0xFF;
    }
    *arg0 = (var_v0 << 0x18) | (var_a1 << 0x10) | (var_a3 << 8);
}

#line 358 "src/modules/uvlight_rom.c"
/* Return the indexed shared light record. Index validity remains caller-owned. */
UnkStruct_uvlight_rom_00401758 *uvLightGetRecord(s32 lightId) {
    return &D_uvlight_rom_00401758[lightId];
}
#line 361 "src/modules/uvlight_rom.c"

s32 func_uvlight_rom_00401340(UnkStruct_uvlight_rom_00401758 *arg0) {
    s32 i;
    s32 freeSlot;
    s32 var_t2;
    UnkStruct_uvlight_rom_00401758 *var_v0;
    static s32 D_uvlight_rom_00401708 = FALSE;
    freeSlot = -1;
    var_t2 = FALSE;

    if (arg0->unk24 == 0x01010100) {
        if (!D_uvlight_rom_00401708) {
            D_uvlight_rom_00401708 = TRUE;
        }
        return -2;
    }

    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        if (D_uvlight_rom_00401758[i].refCount == 0) {
            if (freeSlot == -1) {
                freeSlot = i;
            }
            continue;
        }
        if (((arg0->unk2C == D_uvlight_rom_00401758[i].unk2C)
             && (arg0->unk28 == D_uvlight_rom_00401758[i].unk28))
            && (arg0->unk24 == D_uvlight_rom_00401758[i].unk24)) {
            var_t2 = TRUE;
            D_uvlight_rom_00401758[i].refCount++;
            break;
        }
    }

    if (!var_t2) {
        if (freeSlot == -1) {
            return -1;
        }
        var_v0 = &D_uvlight_rom_00401758[freeSlot];
        var_v0->refCount = 1;
        var_v0->unk2C = arg0->unk2C;
        var_v0->unk28 = arg0->unk28;
        var_v0->unk24 = arg0->unk24;
        var_v0->unk18 = ((var_v0->unk2C >> 0x18) & 0xFF) * 0.0039215f;
        var_v0->unk1C = ((var_v0->unk2C >> 0x10) & 0xFF) * 0.0039215f;
        var_v0->unk20 = ((var_v0->unk2C >> 8) & 0xFF) * 0.0039215f;
        var_v0->unkC = ((var_v0->unk28 >> 0x18) & 0xFF) * 0.0039215f;
        var_v0->unk10 = ((var_v0->unk28 >> 0x10) & 0xFF) * 0.0039215f;
        var_v0->unk14 = ((var_v0->unk28 >> 8) & 0xFF) * 0.0039215f;
        var_v0->unk0[0] = ((var_v0->unk24 >> 0x18) & 0xFF) * 0.0039215f;
        var_v0->unk0[1] = ((var_v0->unk24 >> 0x10) & 0xFF) * 0.0039215f;
        var_v0->unk0[2] = ((var_v0->unk24 >> 8) & 0xFF) * 0.0039215f;
        i = freeSlot;
        func_uvlight_rom_00401260(&D_uvlight_rom_004017C8[i], D_uvlight_rom_004017B8[0] * var_v0->unkC,
                                  D_uvlight_rom_004017B8[1] * var_v0->unk10,
                                  D_uvlight_rom_004017B8[2] * var_v0->unk14);

        func_uvlight_rom_00401260(&D_uvlight_rom_004017C4[i],
                                  (D_uvlight_rom_004017A8[0] * var_v0->unk18) + var_v0->unk0[0],
                                  (D_uvlight_rom_004017A8[1] * var_v0->unk1C) + var_v0->unk0[1],
                                  (D_uvlight_rom_004017A8[2] * var_v0->unk20) + var_v0->unk0[2]);
    }
    return i;
}

#line 425 "src/modules/uvlight_rom.c"
/* Decrement a valid nonnegative light record reference count when nonzero.
 * Preserve the original redundant negative checks and unchecked ownership. */
void uvLightReleaseRecord(s32 lightId) {
    UnkStruct_uvlight_rom_00401758 *record;

    if ((lightId < -2) || (lightId >= D_uvlight_rom_00401794) || (lightId < 0)) {
        return;
    }

    record = &D_uvlight_rom_00401758[lightId];
    if (record->refCount != 0) {
        record->refCount--;
    }
}
#line 437 "src/modules/uvlight_rom.c"

#line 438 "src/modules/uvlight_rom.c"
/* Cache a live light record ID, otherwise use -1. The original guard admits
 * -1 before reading its reference count; preserve that known sentinel hazard
 * here pending a separate caller audit and runtime correction. */
void uvLightSelectRecord(s32 lightId) {
    if ((lightId < -1) || (lightId >= D_uvlight_rom_00401794) || (D_uvlight_rom_00401758[lightId].refCount == 0)) {
        lightId = -1;
    }
    D_uvlight_rom_004016E0 = lightId;
}
#line 444 "src/modules/uvlight_rom.c"

s32 D_uvlight_rom_0040170C[] = { 0x00340000, __entrypoint_func_uvlight_rom_400000, 0, 0 };
