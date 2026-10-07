/*__SEEDEXTERNS__*/
typedef struct { char pad[0x10]; int (*unk10)(int); } GfxMgrExp_004000D0;
typedef struct { char pad[0x10]; int (*unk10)(int, void *, int, int); } CbckExp_004000D0;
typedef struct { char pad[0x4]; void (*unk4)(int, int, int *, int); } ChanExp_004000D0;
extern GfxMgrExp_004000D0 *gUvGfxMgrExports;
extern CbckExp_004000D0 *gUvCbckExports;
extern ChanExp_004000D0 *gUvChanExports;
extern void func_glare_004006B0(void);
extern void func_glare_00400BA4(void);
// SPDX-License-Identifier: AGPL-3.0-or-later
#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/__entrypoint_func_glare_400000.s")

void func_glare_004000C8(void) {
}

/* Initialise the glare channel: allocate a GfxMgr slot, register two frame callbacks, then bind the channel. */
#line 17 "src/modules/glare.c"
/* Attach the original glare callbacks to graphics callback host two
 * and channel property-six host, both with priority 200. Preserve callback
 * registration order and the caller-owned channel contract. */
void glareAttachGraphicsAndChannelCallbacks(int channel) {
    int channelCallbackHost;

    gUvCbckExports->unk10(gUvGfxMgrExports->unk10(2), (void *)func_glare_00400BA4, 0, 0xC8);
    gUvChanExports->unk4(channel, 6, &channelCallbackHost, 0);
    gUvCbckExports->unk10(channelCallbackHost, (void *)func_glare_004006B0, 0, 0xC8);
}
#line 24 "src/modules/glare.c"

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_00400170.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_00400518.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_004006B0.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_004009EC.s")

#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/glare/func_glare_00400BA4.s")

