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
s32 uvLightAllocateDirectionalSet(void);
void uvLightUpdateChannelAmbient(s32 arg0, f32 arg1, f32 arg2, f32 arg3);
void uvLightUpdateSetChannelDiffuse(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void uvLightSetChannelDirection(s32 arg0, s32 arg1, Vec3F *arg2);
void uvLightSetDefaultDirectionAndColors(Vec3F *arg0, f32 *arg1, f32 *arg2);
s32 uvLightAllocateSlotIndex(void);
void uvLightSelectBufferSlot(s32 arg0);
void uvLightPackClampedRgb(s32 *arg0, f32 arg1, f32 arg2, f32 arg3);
UnkStruct_uvlight_rom_00401758 *uvLightGetRecord(s32 arg0);
s32 uvLightAcquireMatchingColorRecord(UnkStruct_uvlight_rom_00401758 *arg0);
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

void __entrypoint_func_uvlight_rom_400000(UvLights_Exports *exports) { /* Publish the thirteen light exports, load settings with per-field defaults, allocate the original buffers, initialize record/channel state and register two callbacks. RE_UNKNOWN: Full settings ownership, allocation success/capacities and dependency lifetimes remain unproved. */
    s32 pad; /* RE_ORIGINAL_QUIRK: Keep the inherited unused local and allocation order. */
    s32 entryIndex;
    s32 channelIndex;
    LightsSettings *lightSettings;
    Vec3F defaultDirection;
    Vec3F zeroColorVector;

    uvUpdateFileAllocPtr(exports);
    exports->uvLightModuleCleanup = uvLightModuleCleanup;
    exports->uvLightAcquireMatchingColorRecord = uvLightAcquireMatchingColorRecord;
    exports->func_uvlight_rom_004008D4 = func_uvlight_rom_004008D4;
    exports->uvLightReleaseRecord = uvLightReleaseRecord;
    exports->uvLightAllocateDirectionalSet = uvLightAllocateDirectionalSet;
    exports->uvLightSelectRecord = uvLightSelectRecord;
    exports->uvLightUpdateChannelAmbient = uvLightUpdateChannelAmbient;
    exports->uvLightUpdateSetChannelDiffuse = uvLightUpdateSetChannelDiffuse;
    exports->uvLightSetChannelDirection = uvLightSetChannelDirection;
    exports->uvLightSetDefaultDirectionAndColors = uvLightSetDefaultDirectionAndColors;
    exports->uvLightAllocateSlotIndex = uvLightAllocateSlotIndex;
    exports->uvLightSelectBufferSlot = uvLightSelectBufferSlot;
    exports->uvLightGetRecord = uvLightGetRecord;
#ifdef __sgi
#line 1
#endif
    defaultDirection = D_uvlight_rom_004016E4;
    zeroColorVector = D_uvlight_rom_004016F0;
    lightSettings = uvGetSystemProp(SYSTEM_PROPID_LIGHTS_SETTINGS);
    if (lightSettings == NULL) {
        D_uvlight_rom_00401794 = 0xA;
        D_uvlight_rom_00401748 = 0x28;
        D_uvlight_rom_00401751 = 7;
    } else {
        if (lightSettings->unk0 != 0) { /* Test the complete word before the original byte store; do not add range validation. */
            D_uvlight_rom_00401794 = lightSettings->unk0;
        } else {
            D_uvlight_rom_00401794 = 0xA;
        }
        if (lightSettings->unk4 != 0) {
            D_uvlight_rom_00401748 = lightSettings->unk4;
        } else {
            D_uvlight_rom_00401748 = 0x28;
        }
        if (lightSettings->unk8 != 0) {
            D_uvlight_rom_00401751 = lightSettings->unk8;
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
    for (entryIndex = 0; entryIndex < D_uvlight_rom_00401794; entryIndex++) { /* Only each record reference count is initialized here. */
        D_uvlight_rom_00401758[entryIndex].refCount = 0;
    }

    for (channelIndex = 0; channelIndex < D_uvlight_rom_00401748; channelIndex++) {
        for (entryIndex = 0; entryIndex < D_uvlight_rom_00401751; entryIndex++) {
            uvLightUpdateSetChannelDiffuse(entryIndex, channelIndex, 0.0f, 0.0f, 0.0f);
            uvLightSetChannelDirection(entryIndex, channelIndex, &defaultDirection);
        }
        uvLightUpdateChannelAmbient(channelIndex, 0.0f, 0.0f, 0.0f);
    }

    uvLightSetDefaultDirectionAndColors(&defaultDirection, (f32*)&zeroColorVector, (f32*)&zeroColorVector);
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

#line 81 "src/modules/uvlight_rom.c"

void uvLightSwapBuffers(s32 unusedContext) {
    s32 firstBufferAddress;
    s32 secondBufferAddress;

    firstBufferAddress = D_uvlight_rom_00401738;
    D_uvlight_rom_00401738 = D_uvlight_rom_0040173C;
    secondBufferAddress = D_uvlight_rom_00401740;
    D_uvlight_rom_0040173C = firstBufferAddress;
    D_uvlight_rom_00401740 = D_uvlight_rom_00401744;
    D_uvlight_rom_00401744 = secondBufferAddress;
}
#line 92 "src/modules/uvlight_rom.c"

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

void func_uvlight_rom_004008D4(s32 recordIndex) { /* Resolve the selected-record sentinel, reject invalid IDs and refresh packed color output only when the compared record words or shared dirty flag require it. RE_UNKNOWN: Record ownership, backing extents, selector reachability and cache lifetimes remain unproved. */
    UnkStruct_uvlight_rom_00401758 *lightRecord;
    s32 packedColorIndex;
    s32 lightIndex;
    void *temp_v0; /* RE_ORIGINAL_QUIRK: Preserve the inherited unused local. */

    if (recordIndex == -2) {
        recordIndex = D_uvlight_rom_004016E0;
    }
    if ((recordIndex < 0) || (recordIndex >= D_uvlight_rom_00401794)) {
        return;
    }

    // RE_ORIGINAL_QUIRK: Preserve the inherited empty nonzero-selector branch.
    if (recordIndex) {}

    if (((D_uvlight_rom_0040174C < 0) || (sNumLights == 0))
        && (D_uvlight_rom_00401754 == 0)) {
        uvLightEmitDefaultLights();
    }
    if ((recordIndex == D_uvlight_rom_00401798) && (D_uvlight_rom_00401753 == 0)) {
        return;
    }

    lightRecord = uvLightGetRecord(recordIndex);
    if ((lightRecord->unk28 != D_uvlight_rom_00401760.unk28) || ((u8) D_uvlight_rom_00401753 != 0)) {
        if (D_uvlight_rom_00401754 == 0) {
            packedColorIndex =
                ((D_uvlight_rom_00401794 * D_uvlight_rom_0040174C * D_uvlight_rom_00401751) + recordIndex);
            for (lightIndex = 0; lightIndex < sNumLights; lightIndex++) {
                uvSetLightColor(
                    lightIndex, (&D_uvlight_rom_004017A0[D_uvlight_rom_00401794 * lightIndex])[packedColorIndex]);
            }
        } else {
            // Send this record's cached packed color to light index zero.
            uvSetLightColor(0, D_uvlight_rom_004017C8[recordIndex]);
        }
        D_uvlight_rom_00401760.unk28 = lightRecord->unk28; /* Reload after the color-helper calls before publishing this cache word. */
    }
    if ((lightRecord->unk2C != D_uvlight_rom_00401760.unk2C) || (lightRecord->unk24 != D_uvlight_rom_00401760.unk24)
        || (D_uvlight_rom_00401753 != 0)) {
        if (D_uvlight_rom_00401754 == 0) {
            uvSetLightColor(
                sNumLights,
                D_uvlight_rom_0040179C[D_uvlight_rom_00401794 * D_uvlight_rom_0040174C + recordIndex]);
        } else {
            uvSetLightColor(LIGHT_1, D_uvlight_rom_004017C4[recordIndex]);
        }
        D_uvlight_rom_00401760.unk2C = lightRecord->unk2C; /* These final cache writes likewise retain their fresh record reads. */
        D_uvlight_rom_00401760.unk24 = lightRecord->unk24;
    }
    D_uvlight_rom_00401798 = recordIndex;
    D_uvlight_rom_00401753 = 0;
}

#line 193 "src/modules/uvlight_rom.c"
/* Allocate the next directional-light set when below capacity. For
 * every channel, initialize RGB to zero and direction to the shared default,
 * then advance the set count. Return -1 when full. */
s32 uvLightAllocateDirectionalSet(void) {
    s32 i;
    s32 setIndex;
    Vec3F direction;

    setIndex = sNumLights;
    direction = D_uvlight_rom_004016FC;
    if (setIndex >= D_uvlight_rom_00401751) {
        return -1U;
    }
    for (i = 0; i < D_uvlight_rom_00401748; i++) {
        uvLightUpdateSetChannelDiffuse(setIndex, i, 0.0f, 0.0f, 0.0f);
        uvLightSetChannelDirection(setIndex, i, &direction);
    }
    sNumLights++;
    return setIndex;
}
#line 210 "src/modules/uvlight_rom.c"

#line 211 "src/modules/uvlight_rom.c"
/* For a valid channel, update ambient colors of referenced records
 * from each record baseline plus its component scales times the supplied
 * triple. Preserve original arithmetic order and record ownership. */
#line 214 "src/modules/uvlight_rom.c"

void uvLightUpdateChannelAmbient(s32 channel, f32 red, f32 green, f32 blue) {
    s32 i;
    s32 recordCountSnapshot;
    UnkStruct_uvlight_rom_00401758 *record;

    if ((channel < 0) || (channel >= D_uvlight_rom_00401748)) {
        return;
    }

    recordCountSnapshot = D_uvlight_rom_00401794;
    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        record = &D_uvlight_rom_00401758[i];
        if (record->refCount == 0) {
            continue;
        }

        uvLightPackClampedRgb(&D_uvlight_rom_0040179C[(D_uvlight_rom_00401794 * channel) + i],
                                  record->unk0[0] + (red * record->unk18),
                                  record->unk0[1] + (green * record->unk1C),
                                  record->unk0[2] + (blue * record->unk20));
    }
}
#line 236 "src/modules/uvlight_rom.c"
#line 233 "src/modules/uvlight_rom.c"

#line 234 "src/modules/uvlight_rom.c"
/* For a valid set/channel pair, update each referenced record diffuse
 * color using its component factors times the supplied RGB triple. */
void uvLightUpdateSetChannelDiffuse(s32 setIndex, s32 channel, f32 red, f32 green, f32 blue) {
    s32 baseIndex;
    s32 i;

    UnkStruct_uvlight_rom_00401758 *record;

    if ((setIndex < 0) || (setIndex >= D_uvlight_rom_00401751) || (channel < 0)
        || (channel >= D_uvlight_rom_00401748)) {
        return;
    }

    baseIndex =
        (D_uvlight_rom_00401794 * channel * D_uvlight_rom_00401751) + (setIndex * D_uvlight_rom_00401794);

    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        record = &D_uvlight_rom_00401758[i];
        if (record->refCount == 0) {
            continue;
        }

        uvLightPackClampedRgb(&D_uvlight_rom_004017A0[i + baseIndex], record->unkC * red,
                                  record->unk10 * green, record->unk14 * blue);
    }
}
#line 258 "src/modules/uvlight_rom.c"

#line 259 "src/modules/uvlight_rom.c"
/* For a valid set/channel pair, normalize the supplied direction and
 * store its components scaled by 127 in the SDK directional-light bytes.
 * Zero-vector handling remains the vector library contract. */
void uvLightSetChannelDirection(s32 setIndex, s32 channel, Vec3F *direction) {
    Vec3F normalized;
    Light *light;

    if ((setIndex < 0) || (setIndex >= D_uvlight_rom_00401751) || (channel < 0)
        || (channel >= D_uvlight_rom_00401748)) {
        return;
    }

    light = &D_uvlight_rom_00401740[(D_uvlight_rom_00401748 * setIndex) + channel];
    D_uvlight_rom_004017CC->uvVec3FNormalize(&normalized, direction);
    light->l.dir[0] = 127.0f * normalized.x;
    light->l.dir[1] = 127.0f * normalized.y;
    light->l.dir[2] = 127.0f * normalized.z;
}
#line 274 "src/modules/uvlight_rom.c"

#line 275 "src/modules/uvlight_rom.c"
/* Normalize and store the shared light direction, retain diffuse and
 * ambient triples, then regenerate packed colors for referenced records.
 * Preserve the original record scaling and ambient baseline addition. */
void uvLightSetDefaultDirectionAndColors(Vec3F *direction, f32 *diffuse, f32 *ambient) {
    Vec3F normalized;
    UnkStruct_uvlight_rom_00401758 *record;
    s32 i;
    Lights1 *unusedLight;

    D_uvlight_rom_004017CC->uvVec3FNormalize(&normalized, direction);
    sLight.l.dir[0] = 127.0f * normalized.x;
    sLight.l.dir[1] = 127.0f * normalized.y;
    sLight.l.dir[2] = 127.0f * normalized.z;

    for (i = 0; i < 3; i++) {
        D_uvlight_rom_004017B8[i] = diffuse[i];
        D_uvlight_rom_004017A8[i] = ambient[i];
    }

    for (i = 0; i < D_uvlight_rom_00401794; i++) {
        record = &D_uvlight_rom_00401758[i];
        if (record->refCount == 0) {
            continue;
        }

        uvLightPackClampedRgb(&D_uvlight_rom_004017C8[i], D_uvlight_rom_004017B8[0] * record->unkC,
                                  D_uvlight_rom_004017B8[1] * record->unk10,
                                  D_uvlight_rom_004017B8[2] * record->unk14);

        uvLightPackClampedRgb(&D_uvlight_rom_004017C4[i],
                                  (D_uvlight_rom_004017A8[0] * record->unk18) + record->unk0[0],
                                  (D_uvlight_rom_004017A8[1] * record->unk1C) + record->unk0[1],
                                  (D_uvlight_rom_004017A8[2] * record->unk20) + record->unk0[2]);
    }
}
#line 307 "src/modules/uvlight_rom.c"

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

#line 332 "src/modules/uvlight_rom.c"
/* Scale RGB components by 255, truncate to signed integers, clamp to
 * byte range and pack into the high three bytes. Preserve original float
 * conversion behavior and leave the low byte zero. */
void uvLightPackClampedRgb(s32 *output, f32 red, f32 green, f32 blue) {
    s32 greenByte;
    s32 blueByte;
    s32 redByte;

    redByte = (255.0f * red);
    greenByte = (255.0f * green);
    blueByte = (255.0f * blue);
    if (redByte < 0) {
        redByte = 0;
    } else if (redByte >= 0x100) {
        redByte = 0xFF;
    }
    if (greenByte < 0) {
        greenByte = 0;
    } else if (greenByte >= 0x100) {
        greenByte = 0xFF;
    }
    if (blueByte < 0) {
        blueByte = 0;
    } else if (blueByte >= 0x100) {
        blueByte = 0xFF;
    }
    *output = (redByte << 0x18) | (greenByte << 0x10) | (blueByte << 8);
}
#line 357 "src/modules/uvlight_rom.c"

#line 358 "src/modules/uvlight_rom.c"
/* Return the indexed shared light record. RE_UNKNOWN: valid index/backing extent needs original record allocation, ID producers and callers. */
UnkStruct_uvlight_rom_00401758 *uvLightGetRecord(s32 lightId) {
    return &D_uvlight_rom_00401758[lightId];
}
#line 361 "src/modules/uvlight_rom.c"

#line 362 "src/modules/uvlight_rom.c"
/* Reuse a referenced record with the same three packed colors or
 * initialize the first free record and its derived RGB caches. Preserve
 * the special -2 sentinel, reference counts and -1 capacity failure. */
s32 uvLightAcquireMatchingColorRecord(UnkStruct_uvlight_rom_00401758 *colors) {
    s32 i;
    s32 freeSlot;
    s32 foundExisting;
    UnkStruct_uvlight_rom_00401758 *record;
    static s32 D_uvlight_rom_00401708 = FALSE;
    freeSlot = -1;
    foundExisting = FALSE;

    if (colors->unk24 == 0x01010100) {
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
        if (((colors->unk2C == D_uvlight_rom_00401758[i].unk2C)
             && (colors->unk28 == D_uvlight_rom_00401758[i].unk28))
            && (colors->unk24 == D_uvlight_rom_00401758[i].unk24)) {
            foundExisting = TRUE;
            D_uvlight_rom_00401758[i].refCount++;
            break;
        }
    }

    if (!foundExisting) {
        if (freeSlot == -1) {
            return -1;
        }
        record = &D_uvlight_rom_00401758[freeSlot];
        record->refCount = 1;
        record->unk2C = colors->unk2C;
        record->unk28 = colors->unk28;
        record->unk24 = colors->unk24;
        record->unk18 = ((record->unk2C >> 0x18) & 0xFF) * 0.0039215f;
        record->unk1C = ((record->unk2C >> 0x10) & 0xFF) * 0.0039215f;
        record->unk20 = ((record->unk2C >> 8) & 0xFF) * 0.0039215f;
        record->unkC = ((record->unk28 >> 0x18) & 0xFF) * 0.0039215f;
        record->unk10 = ((record->unk28 >> 0x10) & 0xFF) * 0.0039215f;
        record->unk14 = ((record->unk28 >> 8) & 0xFF) * 0.0039215f;
        record->unk0[0] = ((record->unk24 >> 0x18) & 0xFF) * 0.0039215f;
        record->unk0[1] = ((record->unk24 >> 0x10) & 0xFF) * 0.0039215f;
        record->unk0[2] = ((record->unk24 >> 8) & 0xFF) * 0.0039215f;
        i = freeSlot;
        uvLightPackClampedRgb(&D_uvlight_rom_004017C8[i], D_uvlight_rom_004017B8[0] * record->unkC,
                                  D_uvlight_rom_004017B8[1] * record->unk10,
                                  D_uvlight_rom_004017B8[2] * record->unk14);

        uvLightPackClampedRgb(&D_uvlight_rom_004017C4[i],
                                  (D_uvlight_rom_004017A8[0] * record->unk18) + record->unk0[0],
                                  (D_uvlight_rom_004017A8[1] * record->unk1C) + record->unk0[1],
                                  (D_uvlight_rom_004017A8[2] * record->unk20) + record->unk0[2]);
    }
    return i;
}
#line 424 "src/modules/uvlight_rom.c"

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
/* Cache a live record ID, otherwise -1. RE_ORIGINAL_QUIRK: the lower guard admits
 * -1, which reaches the reference-count read when the upper guard passes.
 * RE_UNKNOWN: sentinel reachability/storage domain need original caller and layout evidence. */
void uvLightSelectRecord(s32 lightId) {
    if ((lightId < -1) || (lightId >= D_uvlight_rom_00401794) || (D_uvlight_rom_00401758[lightId].refCount == 0)) {
        lightId = -1;
    }
    D_uvlight_rom_004016E0 = lightId;
}
#line 444 "src/modules/uvlight_rom.c"

s32 D_uvlight_rom_0040170C[] = { 0x00340000, __entrypoint_func_uvlight_rom_400000, 0, 0 };
