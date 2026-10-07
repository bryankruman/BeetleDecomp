// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
typedef struct { s32 key; f32 value04,value08,value0C,value10,value14,value18,value1C; } SceneBlendRecord;
typedef struct { u8 unk00[0x24]; f32 selected; } SceneTrackChoice;
typedef struct { u8 unk00[8]; s32 value08; u8 unk0C[0x90]; } SceneTrackRecord;
/* Original GUI C4 is an upper-text byte copier, not a selection setter.
 * RE_UNKNOWN: the complete export table and historical caller declaration. */
typedef struct { u8 unused00[0xC4]; void (*copyUpperTextText)(void *, u8 *); } SceneGuiTextExports;
/*__SEEDEXTERNS__*/
extern s32 D_scene_00402D14;
extern f32 D_scene_00401814;
extern f32 D_scene_00401818;
extern f32 D_scene_0040181C;
extern f32 D_scene_00401820;
extern f32 D_scene_00401824;
extern f32 D_scene_00401828;
extern f32 D_scene_0040182C;
extern f32 D_scene_00401830;
extern f32 D_scene_00401834;
extern s32 D_8002CB8C;
extern s32 D_8002CC64;
extern s32 D_8002D1A8;
extern s32 D_scene_00402CFC;
extern s32 D_scene_00402DA0;
extern s32 D_scene_00402DB8;
extern s32 gCurrentGameState;
extern s8 D_scene_00402E00;
extern s8 D_scene_00402E01;
extern u8 D_scene_00401754;
extern u8 D_scene_0040175C;
extern u8 D_scene_00401764;
extern u8 D_scene_0040176C;
extern u8 D_scene_00401778;
extern u8 D_scene_004017A4;
extern u8 D_scene_004017AC;
extern u8 D_scene_004017B8;
extern u8 D_scene_004017C0;
extern u8 D_scene_004017CC;
extern u8 D_scene_004017D4;
extern u8 D_scene_004017E0;
extern u8 D_scene_004017EC;
extern u8 D_scene_004017F4;
extern u8 D_scene_004017FC;
extern u8 D_scene_00401804;
extern u8 D_scene_00401840;
extern u8 D_scene_00401D3C;
extern u8 D_scene_00402CF0;
extern u8 D_scene_00402DD8;
extern u8 D_scene_00402DF8;
extern u8 D_scene_00402E20;
extern u8 D_scene_00402E4C;
extern u8 D_scene_00402ED0;
extern u8 D_scene_00402ED4;
extern u8 D_scene_00402ED8;
extern u8 D_scene_00402EDC;
extern u8 D_scene_00402EE0;
extern u8 D_scene_00402EE4;
extern u8 D_scene_00402EE8;
extern u8 gCheatTrackMusic;
extern u8 gCurrentTrack;
extern u8 gTrackWeather;
extern void *D_scene_00402EF0;
extern void *gGlareExports;
extern void *gLightExports;
extern void *gRainExports;
extern void *gScrnExports;
extern void *gSndExports;
extern void *gUvCmidiExports;
extern void *gUvDobjExports;
extern void *gUvEnvExports;
extern void *gUvGuiExports;
extern void *gUvIsectExports;
extern void *gUvLightExports;
extern void *gUvMathExports;
extern void *gUvTerraExports;
extern s32 D_scene_00402CF8;
extern s32 D_scene_00402D10;
extern s32 D_scene_00402D34;
extern s32 D_scene_00402D40;
s32 sceneGetClampedSixEntryValue();
s32 sceneGetClampedNineEntryValue();
s32 sceneFindHandleSlot(s32 handle);
void func_scene_00400188();
void sceneRefreshThreeListedModels(void);
void sceneRefreshLoadedModelsWithFlags(void);
void sceneRefreshLoadedModelsWithData(void);
void func_scene_004003F4();
void sceneUpdateSharedEffectState(void);
void func_scene_00400CB8();
void func_scene_00400EC8();
void sceneMarkScreenRecords(s32 arg0);
void sceneApplySelectedTrack(SceneTrackChoice *choice);
void func_scene_00401324();
void sceneCopyEightWordRecord();
void sceneBlendEightWordRecord(SceneBlendRecord *output, SceneBlendRecord *first, SceneBlendRecord *second, f32 fraction);
#line 94 "src/modules/scene.c"
/* Clamp the caller index to zero through five and return that entry
 * from the original scene table. */
s32 sceneGetClampedSixEntryValue(s32 index) {
    if (index >= 6) {
        index = 5;
    } else if (index < 0) {
        index = 0;
    }
    return (&D_scene_00402CF8)[index];
}
#line 102 "src/modules/scene.c"

#line 103 "src/modules/scene.c"
/* Clamp the caller index to zero through eight and return that entry
 * from the original scene table. */
s32 sceneGetClampedNineEntryValue(s32 index) {
    if (index >= 9) {
        index = 8;
    } else if (index < 0) {
        index = 0;
    }
    return (&D_scene_00402D10)[index];
}
#line 111 "src/modules/scene.c"

#line 111 "src/modules/scene.c"
/* Search the original contiguous six-word scene handle table and return
 * the first matching slot. Missing handles return zero, which is also the
 * first slot; preserve this ambiguity and the original compiler unrolling. */
s32 sceneFindHandleSlot(s32 handle) {
    s32 index;
    for (index = 0; index < 6; index++) {
        if (handle == (&D_scene_00402CF8)[index]) return index;
    }
    return 0;
}
#line 112 "src/modules/scene.c"

#line 113 "src/modules/scene.c"
/* Search the original nine-word scene table, returning the first matching
 * slot. A miss returns zero, which also identifies slot zero; preserve the
 * original four-at-a-time comparisons and this ambiguity.
 * RE_UNKNOWN: The scene table value meanings remain unproven.
 * RE_ORIGINAL_QUIRK: A missing value is indistinguishable from a match in slot zero. */
s32 sceneFindNineEntryValueSlot(s32 value) {
    s32 *entries;
    s32 slot;

    if (value == D_scene_00402D10) {
        return 0;
    }
    entries = &D_scene_00402D14;
    slot = 1;
loop_3:
    if (value == entries[0]) {
        return slot;
    }
    if (value == entries[1]) {
        return slot + 1;
    }
    if (value == entries[2]) {
        return slot + 2;
    }
    if (value == entries[3]) {
        return slot + 3;
    }
    slot += 4;
    entries += 4;
    if (slot != 9) {
        goto loop_3;
    }
    return 0;
}
#line 142 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400188.s")

#line 145 "src/modules/scene.c"
/* Invoke the model refresh helper for the three contiguous words beginning
 * at D_scene_00402D34, stopping before D_scene_00402D40. Preserve the original
 * grouped loop shape and callback order.
 * RE_UNKNOWN: the three model slots and their broader lifecycle. */
void sceneRefreshThreeListedModels(void)
{
 do { s32 *modelIds = &D_scene_00402D34; if (1) { do { func_scene_00400188(*modelIds); modelIds++; } while (modelIds != (&D_scene_00402D40)); } } while (0);
}
#line 149 "src/modules/scene.c"

#line 150 "src/modules/scene.c"
/* Visit loaded model IDs and refresh those whose byte-five flags include
 * any bit in mask 0x70. Preserve the original file-count snapshot. */
void sceneRefreshLoadedModelsWithFlags(void) {
    s32 count;
    s32 index;
    void *file;

    count = uvGetFilesCount(0x55564D44);
    index = 0;
    if (count > 0) {
        do {
            file = uvGetLoadedFile(0x55564D44, index);
            if ((file != 0) && (*(u8 *)((u8 *)file + 0x5) & 0x70)) {
                func_scene_00400188(index);
            }
            index += 1;
        } while (index < count);
    }
}
#line 167 "src/modules/scene.c"

#line 168 "src/modules/scene.c"
/* Visit loaded model IDs and refresh those with a nonzero word at 0x20.
 * Preserve the original file-count snapshot and loaded-file null check. */
void sceneRefreshLoadedModelsWithData(void) {
    s32 count;
    s32 index;
    void *file;

    count = uvGetFilesCount(0x55564D44);
    index = 0;
    if (count > 0) {
        do {
            file = uvGetLoadedFile(0x55564D44, index);
            if ((file != 0) && (*(s32 *)((u8 *)file + 0x20) != 0)) {
                func_scene_00400188(index);
            }
            index = index + 1;
        } while (index < count);
    }
}
#line 185 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_004003F4.s")

#line 188 "src/modules/scene.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_scene_00400C58(void) {
}
#line 190 "src/modules/scene.c"

#line 191 "src/modules/scene.c"
/* Run the optional scene export update, then clear the two shared scalars
 * at 0xE8/0xEC when the shared enable word at 0xD8 is zero. */
void sceneUpdateSharedEffectState(void) {
    void *exports;

    exports = D_scene_00402EF0;
    if (exports != 0) {
        (*(void (**)(void))((u8 *)exports + 0x4))();
    }
    if (*(s32 *)((u8 *)&D_scene_00402DF8 + 0xD8) == 0) {
        *(f32 *)((u8 *)&D_scene_00402DF8 + 0xE8) = 0.0f;
        *(f32 *)((u8 *)&D_scene_00402DF8 + 0xEC) = 0.0f;
    }
}
#line 203 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400CB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/__entrypoint_func_scene_400e0c.s")

#line 208 "src/modules/scene.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_scene_00400EC0(void) {
}
#line 210 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00400EC8.s")

#line 213 "src/modules/scene.c"
/* Set each record word at offset 0x21C to one in the screen-export array.
 * Reload the shared array and signed count after each store, preserving the
 * callback parameter home and original traversal.
 * RE_UNKNOWN: meaning of the marker and the complete screen record layout.
 * RE_ORIGINAL_QUIRK: record pointers and signed count are not validated. */
void sceneMarkScreenRecords(s32 unusedCallbackValue)
{
  s32 index;
  s32 byteOffset;
  void *screenRecords;
  void *record;
  *((s32 *) (((u8 *) (&unusedCallbackValue)) + 0x0)) = unusedCallbackValue;
  index = 0;
  screenRecords = *((void **) (((u8 *) gScrnExports) + 0x18));
  byteOffset = 0;
  if ((*((s16 *) (((u8 *) (*((void **) (((u8 *) gScrnExports) + 0x18)))) + 0x10))) > 0)
  {
    do
    {
      record = *((void **) (((u8 *) screenRecords) + byteOffset));
      index += 1;
      byteOffset += 4;
      *((s32 *) (((u8 *) record) + 0x21C)) = 1;
      screenRecords = *((void **) (((u8 *) gScrnExports) + 0x18));
    }
    while (index < (*((s16 *) (((u8 *) screenRecords) + 0x10))));
  }
}
#line 236 "src/modules/scene.c"

#line 237 "src/modules/scene.c"
/* Original empty function; preserve its separate identity and argument ABI.
 * RE_UNKNOWN: purpose, caller-facing role and indirect/export reachability
 * remain unresolved. An empty body alone does not establish that callers can
 * safely omit this function or that it represents missing implementation. */
void func_scene_004012B0(s32 a0) {
}
#line 239 "src/modules/scene.c"

#line 240 "src/modules/scene.c"

#line 241 "src/modules/scene.c"
/* Truncate the floating selection into the current track, then use the stored
 * track to select its original 0x9C-byte record. GUI C4 consumes record word 0x08
 * as the source address for the upper-text copier; this call does not set a
 * selection. Preserve all original unchecked indexing and word representation.
 * RE_UNKNOWN: record word 0x08's original pointer storage/relocation, readable
 * text extent and the complete choice-object layout. Inspect original record
 * data/relocations and creation paths before renaming word 0x08 or claiming a
 * 30-byte array or reachable buffer fault. */
void sceneApplySelectedTrack(SceneTrackChoice *choice) {

    SceneTrackRecord *record;
    gGameSettings->currentTrack = (s32)choice->selected;
    record = &((SceneTrackRecord *)&D_scene_00401840)[gGameSettings->currentTrack];
    ((SceneGuiTextExports *)gUvGuiExports)->copyUpperTextText(choice, (u8 *)record->value08);
}
#line 248 "src/modules/scene.c"
#line 241 "src/modules/scene.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/scene/func_scene_00401324.s")

#line 244 "src/modules/scene.c"
/* Copy the original leading integer and seven floating words in their
 * original order. Preserve explicit scalar copies and the source address ABI. */
void sceneCopyEightWordRecord(void *destination, s32 sourceAddress) {
    *(s32 *)((u8 *)destination + 0x0) = *(s32 *)((u8 *)sourceAddress + 0x0);
    *(f32 *)((u8 *)destination + 0x4) = *(f32 *)((u8 *)sourceAddress + 0x4);
    *(f32 *)((u8 *)destination + 0x8) = *(f32 *)((u8 *)sourceAddress + 0x8);
    *(f32 *)((u8 *)destination + 0xC) = *(f32 *)((u8 *)sourceAddress + 0xC);
    *(f32 *)((u8 *)destination + 0x10) = *(f32 *)((u8 *)sourceAddress + 0x10);
    *(f32 *)((u8 *)destination + 0x14) = *(f32 *)((u8 *)sourceAddress + 0x14);
    *(f32 *)((u8 *)destination + 0x18) = *(f32 *)((u8 *)sourceAddress + 0x18);
    *(f32 *)((u8 *)destination + 0x1C) = *(f32 *)((u8 *)sourceAddress + 0x1C);
}
#line 254 "src/modules/scene.c"

#line 255 "src/modules/scene.c"
/* Blend the seven floating fields, copying endpoint records outside [0, 1].
 * Select a nonzero integer key by the original midpoint rule, except when
 * blended field 0x10 is exactly zero or one. Preserve alias-sensitive read order. */
void sceneBlendEightWordRecord(SceneBlendRecord *output, SceneBlendRecord *first, SceneBlendRecord *second, f32 fraction) {
    f32 inverse;
    s32 firstKey;
    s32 secondKey;
    if (fraction <= 0.0f) {
        sceneCopyEightWordRecord(output, (s32)first);
        return;
    }
    if (fraction >= 1.0f) {
        sceneCopyEightWordRecord(output, (s32)second);
        return;
    }
    inverse = 1.0f - fraction;
    output->value04 = first->value04 * inverse + second->value04 * fraction;
    output->value08 = first->value08 * inverse + second->value08 * fraction;
    output->value0C = first->value0C * inverse + second->value0C * fraction;
    output->value10 = first->value10 * inverse + second->value10 * fraction;
    output->value14 = first->value14 * inverse + second->value14 * fraction;
    output->value18 = first->value18 * inverse + second->value18 * fraction;
    output->value1C = first->value1C * inverse + second->value1C * fraction;
    if (output->value10 == 0.0f || output->value10 == 1.0f) {
        output->key = 0;
        return;
    }
    firstKey = first->key;
    if (firstKey != 0) {
        secondKey = second->key;
        if (secondKey != 0) {
            if (fraction > 0.5f) {
                output->key = secondKey;
                return;
            }
            output->key = firstKey;
            return;
        }
    }
    if (firstKey == 0) {
        output->key = second->key;
        return;
    }
    output->key = firstKey;
}
#line 256 "src/modules/scene.c"

