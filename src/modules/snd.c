#include "common.h"
#include "module.h"
/*__SEEDEXTERNS__*/
typedef struct UnkSnd_00402504_s {
    f32 unk0;
    u8 unk4;
} UnkSnd_00402504;
typedef struct UnkSnd_004064F0_s {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ char pad0C[0x14 - 0x0C];
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ char pad1C[0x1D - 0x1C];
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ char pad1E[0x1F - 0x1E];
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ char pad20[0x24 - 0x20];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char pad26[0x28 - 0x26];
} UnkSnd_004064F0;
typedef struct { char pad0[0x2C]; f32 (*unk2C)(s32, s32); } SndReplayExports;
extern UvEmitter_Exports *gUvEmitterExports;
extern UvCMidi_Exports *gUvCmidiExports;
extern SndReplayExports *gReplayExports;
extern f32 D_snd_004045D0;
extern f32 D_snd_004045D4;
extern u8 D_snd_00406194;
extern UnkSnd_004064F0 D_snd_004064C8[];
extern UnkSnd_004064F0 D_snd_004064D0[];
extern UnkSnd_004064F0 D_snd_004064D4[];
extern s32 D_snd_0040616C[];
extern u8 D_snd_004064EF;
extern void *D_snd_00406198;
void func_snd_004004F8();
void func_snd_004005C8();
void func_snd_00400750();
void func_snd_00400854();
void func_snd_0040094C(s16, s32);
void func_snd_00400A64();
s32 func_snd_00400B0C();
void func_snd_00400B54();
s32 func_snd_00400CD8(s32);
void func_snd_00400DDC();
void func_snd_00400EC0();
void func_snd_00401038();
void func_snd_00401304(u8);
void func_snd_004013DC();
void func_snd_00401434();
void func_snd_00401474();
f32 func_snd_004014B4(void);
f32 func_snd_004014C4(void);
void func_snd_004014E0();
void func_snd_00401564();
void func_snd_00401650();
s32 func_snd_00401694(UnkSnd_00402504 *, s32, s32, s32);
void func_snd_00401800();
void func_snd_00401914();
s32 func_snd_00401A28(UnkSnd_00402504 *);
u8 func_snd_00401AA8(UnkSnd_00402504 *, s32, s32, s32);
void func_snd_00401CDC();
void func_snd_00401D14();
void func_snd_00401D54();
void func_snd_00401DA0();
void func_snd_00401E08();
void func_snd_00401E70();
void func_snd_00401EB8();
void func_snd_00401F48();
void func_snd_00401FD8();
void func_snd_00402020();
void func_snd_00402084();
void func_snd_004020D0();
void func_snd_0040211C();
void func_snd_0040216C();
void func_snd_0040221C();
void func_snd_004022D0();
void func_snd_0040231C();
f32 func_snd_00402368(s32);
s32 func_snd_00402388();
s32 func_snd_004023A8(s32);
u8 func_snd_004023D4();
s32 func_snd_004023F4(s32);
void func_snd_00402424();
void func_snd_00402504(void *);
void func_snd_0040252C();
void func_snd_0040260C();
void func_snd_00402660(s32);
void func_snd_004027E8();
void func_snd_0040284C(s32);
void func_snd_00402B40();
extern u8 D_snd_004063B8[];
extern u8 D_snd_004064B8[];
extern u8 D_snd_00406168;
extern u16 D_snd_00406190;
extern s32 D_snd_004064BC;
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/__entrypoint_func_snd_400000.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004004F8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004005C8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400750.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400854.s")

void func_snd_0040094C(s16 arg0, s32 arg1) {
    u8 ret;

    ret = gUvEmitterExports->func_uvemitter_rom_004006FC();
    gUvEmitterExports->func_uvemitter_rom_00400E60(ret, arg1);
    if (ret == 0xFF) {
        return;
    }
    gUvEmitterExports->func_uvemitter_rom_004007B4(ret, arg0);
    gUvEmitterExports->func_uvemitter_rom_00400D48(ret, (f32) func_snd_004023A8(arg0) / D_snd_004045D0);
    gUvEmitterExports->func_uvemitter_rom_00400EBC(ret, 5, 0x30, 0);
    gUvEmitterExports->func_uvemitter_rom_00400BE8(ret, func_snd_004014B4() * D_snd_004045D4);
    gUvEmitterExports->func_uvemitter_rom_00401010(ret);
}

/* func_snd_00400A64(u8 arg0) -> s16: allocate an emitter slot via
 * gUvEmitterExports->unk4(); if it returns 0xFF, return 0xFF. Otherwise
 * configure the slot: unkC(slot, arg0); unk30(slot, 0); unk54(slot); return slot.
 * Logic verified; byte-match blocked on IDO reg-alloc (masked slot wants $s0,
 * with andi in the branch delay slot + per-arg re-mask). Needs decomp-permuter. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400A64.s")


#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400B0C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400B54.s")

/* TODO(snd-grind, from synamaxmusic/bar-decomp `snd`): s32 func_snd_00400CD8(s32 arg0)
 * -> return TRUE if any slot i in 0..D_snd_00406168 has D_snd_004064B8[i]==0 and
 * |gReplayExports->unk2C(i, arg0)| > 0.7f. Their C ports & COMPILES here (gReplayExports
 * view type + unk2C@0x2C staged at top) but byte-mismatches; blocker undiagnosed. Next:
 * objdump-diff built .o vs this .s (check unk2C offset, double unk2C call vs cached temp,
 * f32-compare shape). Source: `git show upstream/snd:src/modules/snd.c`. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400CD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400DDC.s")

void func_snd_00400E90(s32 a0) {
    D_snd_004064B8[a0] = 0;
}

void func_snd_00400EA0(s32 a0) {
    D_snd_004064B8[a0] = 1;
}

void func_snd_00400EB4(s32 a0) {
    D_snd_00406168 = a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00400EC0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401038.s")

void func_snd_004012F4(u16 a0) {
    D_snd_00406190 = a0;
}

void func_snd_00401304(u8 arg0) {
    switch (arg0) {
    case 0:
    case 3:
        func_snd_0040252C(0);
        if (D_snd_00406194 != 0) {
            gUvCmidiExports->func_uvcmidi_rom_00400940();
        }

        gUvCmidiExports->func_uvcmidi_rom_0040062C(D_snd_00406190);
        gUvCmidiExports->func_uvcmidi_rom_004006F4();
        D_snd_00406194 = 1;
        break;
    case 2:
    case 1:
        if (D_snd_00406194 != 0) {
            gUvCmidiExports->func_uvcmidi_rom_00400940();
            D_snd_00406194 = 0;
        }
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004013DC.s")

void func_snd_00401434(s32 a0) {
    (*(void (**)(s32, s32, s32))((u8 *)gUvEmitterExports + 0x94))(0, D_snd_0040616C[a0], a0);
}

void func_snd_00401474(s32 a0) {
    (*(void (**)(s32, s32, s32))((u8 *)gUvEmitterExports + 0x94))(1, D_snd_0040616C[a0], a0);
}

f32 func_snd_004014B4(void) {
    return 1.0f;
}

f32 func_snd_004014C4(void) {
    return 1.0f;
}

void func_snd_004014D4(s32 a0) {
    D_snd_004064BC = a0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004014E0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401564.s")

void func_snd_00401650(void) {
    s16 i = 1;
    do {
        func_snd_00401564(i & 0xFF);
        i++;
    } while (i < 0x28);
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401694.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401800.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401914.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401A28.s")

/* TODO(snd-grind, from synamaxmusic/bar-decomp `snd`):
 * u8 func_snd_00401AA8(UnkSnd_00402504* arg0, s32 arg1, s32 arg2, s32 arg3) -> emitter
 * (re)configure with several early-outs; indexes D_snd_004064D0/D4[arg0->unk4]
 * (UnkSnd_004064F0, staged at top) and calls gUvEmitterExports->func_uvemitter_rom_*.
 * Their C COMPILES here but byte-mismatches (complex control flow / IDO reg-alloc) --
 * a decomp-permuter candidate: seed the permuter with their body. Source:
 * `git show upstream/snd:src/modules/snd.c`. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401AA8.s")

void func_snd_00401CDC(UnkSnd_00402504* arg0) {
    if (func_snd_00401A28(arg0) != 0) {
        func_snd_00401564(arg0->unk4);
        func_snd_00402504(arg0);
    }
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401D14.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401D54.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401DA0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401E08.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401E70.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401EB8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401F48.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00401FD8.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00402020.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00402084.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004020D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040211C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040216C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040221C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004022D0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040231C.s")

f32 func_snd_00402368(s32 arg0) {
    return *(f32 *)((u8 *)D_snd_00406198 + arg0 * 0x1C + 0xC);
}

s32 func_snd_00402388(s32 a0) {
    return *(s32 *)((u8 *)D_snd_00406198 + a0 * 0x1C + 4);
}

s32 func_snd_004023A8(s32 arg0) {
    return *(f32 *)((u8 *)D_snd_00406198 + arg0 * 0x1C + 8);
}

u8 func_snd_004023D4(s32 a0) {
    return *(u8 *)((u8 *)D_snd_00406198 + a0 * 0x1C + 0x18);
}

s32 func_snd_004023F4(s32 arg0) {
    if (arg0 >= 0) {
        return *(s32 *)((u8 *)D_snd_00406198 + arg0 * 0x1C);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00402424.s")

void func_snd_00402504(void *arg0) {
    if (arg0 == NULL) {
        *(s32 *)0 = 0;
        return;
    }
    *(u8 *)((u8 *)arg0 + 4) = 0xFF;
    *(f32 *)arg0 = -1.0f;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040252C.s")

u8 func_snd_004025EC(s32 a0) {
    return D_snd_004063B8[a0];
}

void func_snd_004025FC(s32 a0) {
    D_snd_004063B8[a0] = 0;
}

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040260C.s")

void func_snd_0040264C(s32 a0) {
    D_snd_004063B8[a0] = 1;
}

/* TODO(snd-grind, from synamaxmusic/bar-decomp `snd`): void func_snd_00402660(s32 arg0)
 * -> stop the emitter slot(s) (j=1..39) whose D_snd_004064C8[j].unk24 matches an active
 * emitter id from func_uvemitter_rom_00402754.
 * BLOCKER (module relocation, SHARED with func_snd_0040284C below): because the loop runs
 * j=1..39, the ORIGINAL references the symbol D_snd_004064F0 (= &D_snd_004064C8[1], addend 0);
 * IDO compiles `D_snd_004064C8[j]` to a `D_snd_004064C8 + 0x28` reloc instead -> identical
 * LINKED bytes but a DIFFERENT relocatable-module reloc entry, so the module hash differs.
 * This is structural, NOT a permuter near-miss. Tried: D_snd_004064C8[j], D_snd_004064F0[j-1],
 * and an explicit pointer -- all mismatch. Fix must make the base reloc land on D_snd_004064F0
 * (source-form or splat-symbol trick). Source: `git show upstream/snd:src/modules/snd.c`. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00402660.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_004027E8.s")

/* TODO(snd-grind, from synamaxmusic/bar-decomp `snd`): void func_snd_0040284C(s32 arg0)
 * -> like func_snd_00402660 but ramps each matching emitter's volume down to 0 (steps of
 * 0.1f, clamped) before stopping it. SAME D_snd_004064F0-vs-(D_snd_004064C8 + 0x28)
 * module-relocation blocker as func_snd_00402660 above -- see that note. Source:
 * `git show upstream/snd:src/modules/snd.c`. */
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_0040284C.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/snd/func_snd_00402B40.s")

extern void *gUvAudiomgrExports;

void func_snd_00402DC0(char arg0)
{
  if (arg0)
  {
    arg0 = arg0;
    (*((void (**)(s32)) (((u8 *) gUvAudiomgrExports) + 0x24)))(1);
    return;
  }
  (*((void (**)(s32)) (((u8 *) gUvAudiomgrExports) + 0x24)))(2);
}

void func_snd_00402E1C(void) {
}

