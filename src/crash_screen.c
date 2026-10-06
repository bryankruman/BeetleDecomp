
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#ifdef ISPRINT

#include <ultra64.h>
#include "stdarg.h"
// #include "lib/src/printf.h"

u8 gCrashScreenCharToGlyph[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 43, -1, -1, 37, 38, -1, 42,
    -1, 39, 44, -1, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  36, -1, -1, -1, -1, 40, -1, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, -1, -1, -1, -1, -1,
};

// A height of seven pixels for each Character * nine rows of characters + one row unused.
u32 gCrashScreenFont[7 * 9 + 1] = {
    0x70871C30, 0x8988A250, 0x88808290, 0x88831C90, 0x888402F8, 0x88882210, 0x71CF9C10, 0xF9CF9C70,
    0x8228A288, 0xF200A288, 0x0BC11C78, 0x0A222208, 0x8A222288, 0x71C21C70, 0x23C738F8, 0x5228A480,
    0x8A282280, 0x8BC822F0, 0xFA282280, 0x8A28A480, 0x8BC738F8, 0xF9C89C08, 0x82288808, 0x82088808,
    0xF2EF8808, 0x82288888, 0x82288888, 0x81C89C70, 0x8A08A270, 0x920DA288, 0xA20AB288, 0xC20AAA88,
    0xA208A688, 0x9208A288, 0x8BE8A270, 0xF1CF1CF8, 0x8A28A220, 0x8A28A020, 0xF22F1C20, 0x82AA0220,
    0x82492220, 0x81A89C20, 0x8A28A288, 0x8A28A288, 0x8A289488, 0x8A2A8850, 0x894A9420, 0x894AA220,
    0x70852220, 0xF8011000, 0x08020800, 0x10840400, 0x20040470, 0x40840400, 0x80020800, 0xF8011000,
    0x70800000, 0x88822200, 0x08820400, 0x108F8800, 0x20821000, 0x00022200, 0x20800020, 0x00000000,
};

char *gCauseDesc[18] = {
    "Interrupt",
    "TLB modification",
    "TLB exception on load",
    "TLB exception on store",
    "Address error on load",
    "Address error on store",
    "Bus error on inst.",
    "Bus error on data",
    "System call exception",
    "Breakpoint exception",
    "Reserved instruction",
    "Coprocessor unusable",
    "Arithmetic overflow",
    "Trap exception",
    "Virtual coherency on inst.",
    "Floating point exception",
    "Watchpoint exception",
    "Virtual coherency on data",
};

char *gFpcsrDesc[6] = {
    "Unimplemented operation", "Invalid operation", "Division by zero", "Overflow", "Underflow",
    "Inexact operation",
};



extern u64 osClockRate;

struct {
    OSThread thread;
    u64 stack[0x800 / sizeof(u64)];
    OSMesgQueue mesgQueue;
    OSMesg mesg;
    u16 *framebuffer;
    u16 width;
    u16 height;
} gCrashScreen;

void uvCrashScreenDrawRect(s32 x, s32 y, s32 w, s32 h) {
    u16 *ptr;
    s32 i, j;

    ptr = gCrashScreen.framebuffer + gCrashScreen.width * y + x;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            // 0xe738 = 0b1110011100111000
            *ptr = ((*ptr & 0xe738) >> 2) | 1;
            ptr++;
        }
        ptr += gCrashScreen.width - w;
    }
}

void uvCrashScreenDrawGlyph(s32 x, s32 y, s32 glyph) {
    const u32 *data;
    u16 *ptr;
    u32 bit;
    u32 rowMask;
    s32 i, j;

    data = &gCrashScreenFont[glyph / 5 * 7];
    ptr = gCrashScreen.framebuffer + gCrashScreen.width * y + x;

    for (i = 0; i < 7; i++) {
        bit = 0x80000000U >> ((glyph % 5) * 6);
        rowMask = *data++;

        for (j = 0; j < 6; j++) {
            *ptr++ = (bit & rowMask) ? 0xffff : 1;
            bit >>= 1;
        }
        ptr += gCrashScreen.width - 6;
    }
}

static char *write_to_buf(char *buffer, const char *data, unsigned long size) {
    return (char *) memcpy(buffer, data, size) + size;
}

void uvCrashScreenPrint(s32 x, s32 y, const char *fmt, ...) {
    char *ptr;
    u32 glyph;
    s32 size;
    char buf[0x100];

    va_list args;
    va_start(args, fmt);

    size = _Printf(write_to_buf, buf, fmt, args);

    if (size > 0) {
        ptr = buf;

        while (*ptr) {

            glyph = gCrashScreenCharToGlyph[*ptr & 0x7f];

            if (glyph != 0xff) {
                uvCrashScreenDrawGlyph(x, y, glyph);
            }


            ptr++;
            x += 6;
        }
    }

    va_end(args);
}

extern OSTime __osCurrentTime;

void uvSetTime(OSTime time) {
    __osCurrentTime = time;
}

void uvCrashScreenSleep(s32 ms) {
    u64 cycles = ms * 1000LL * osClockRate / 1000000ULL;
    uvSetTime(0);
    while (osGetTime() < cycles) {
    }
}

void uvCrashScreenPrintFloatReg(s32 x, s32 y, s32 regNum, void *addr) {
    u32 bits;
    s32 exponent;

    bits = *(u32 *) addr;
    exponent = ((bits & 0x7f800000U) >> 0x17) - 0x7f;
    if ((exponent >= -0x7e && exponent <= 0x7f) || bits == 0) {
        uvCrashScreenPrint(x, y, "F%02d:%.3e", regNum, *(f32 *) addr);
    } else {
        uvCrashScreenPrint(x, y, "F%02d:---------", regNum);
    }
}

void uvCrashScreenPrintFpcsr(u32 fpcsr) {
    s32 i;
    u32 bit;

    bit = 1 << 17;
    uvCrashScreenPrint(30, 155, "FPCSR:%08XH", fpcsr);
    for (i = 0; i < 6; i++) {
        if (fpcsr & bit) {
            uvCrashScreenPrint(132, 155, "(%s)", gFpcsrDesc[i]);
            return;
        }
        bit >>= 1;
    }
}

void uvDrawCrashScreen(OSThread *thread) {
    s16 cause;
    __OSThreadContext *tc = &thread->context;

    cause = (tc->cause >> 2) & 0x1f;
    if (cause == 23) { // EXC_WATCH
        cause = 16;
    }
    if (cause == 31) { // EXC_VCED
        cause = 17;
    }

    uvCrashScreenDrawRect(25, 20, 270, 25);
    uvCrashScreenPrint(30, 25, "THREAD:%d  (%s)", thread->id, gCauseDesc[cause]);
    uvCrashScreenPrint(30, 35, "PC:%08XH   SR:%08XH   VA:%08XH", tc->pc, tc->sr, tc->badvaddr);
    uvCrashScreenSleep(2000);
    uvCrashScreenDrawRect(25, 45, 270, 185);
    osSyncPrintf("Oh no!, your beetle just crashed!\n");

    uvCrashScreenPrint(30, 50, "AT:%08XH   V0:%08XH   V1:%08XH", (u32) tc->at, (u32) tc->v0,
                       (u32) tc->v1);
    uvCrashScreenPrint(30, 60, "A0:%08XH   A1:%08XH   A2:%08XH", (u32) tc->a0, (u32) tc->a1,
                       (u32) tc->a2);
    uvCrashScreenPrint(30, 70, "A3:%08XH   T0:%08XH   T1:%08XH", (u32) tc->a3, (u32) tc->t0,
                       (u32) tc->t1);
    uvCrashScreenPrint(30, 80, "T2:%08XH   T3:%08XH   T4:%08XH", (u32) tc->t2, (u32) tc->t3,
                       (u32) tc->t4);
    uvCrashScreenPrint(30, 90, "T5:%08XH   T6:%08XH   T7:%08XH", (u32) tc->t5, (u32) tc->t6,
                       (u32) tc->t7);
    uvCrashScreenPrint(30, 100, "S0:%08XH   S1:%08XH   S2:%08XH", (u32) tc->s0, (u32) tc->s1,
                       (u32) tc->s2);
    uvCrashScreenPrint(30, 110, "S3:%08XH   S4:%08XH   S5:%08XH", (u32) tc->s3, (u32) tc->s4,
                       (u32) tc->s5);
    uvCrashScreenPrint(30, 120, "S6:%08XH   S7:%08XH   T8:%08XH", (u32) tc->s6, (u32) tc->s7,
                       (u32) tc->t8);
    uvCrashScreenPrint(30, 130, "T9:%08XH   GP:%08XH   SP:%08XH", (u32) tc->t9, (u32) tc->gp,
                       (u32) tc->sp);
    uvCrashScreenPrint(30, 140, "S8:%08XH   RA:%08XH", (u32) tc->s8, (u32) tc->ra);
    uvCrashScreenPrintFpcsr(tc->fpcsr);
    uvCrashScreenPrintFloatReg(30, 170, 0, &tc->fp0.f.f_even);
    uvCrashScreenPrintFloatReg(120, 170, 2, &tc->fp2.f.f_even);
    uvCrashScreenPrintFloatReg(210, 170, 4, &tc->fp4.f.f_even);
    uvCrashScreenPrintFloatReg(30, 180, 6, &tc->fp6.f.f_even);
    uvCrashScreenPrintFloatReg(120, 180, 8, &tc->fp8.f.f_even);
    uvCrashScreenPrintFloatReg(210, 180, 10, &tc->fp10.f.f_even);
    uvCrashScreenPrintFloatReg(30, 190, 12, &tc->fp12.f.f_even);
    uvCrashScreenPrintFloatReg(120, 190, 14, &tc->fp14.f.f_even);
    uvCrashScreenPrintFloatReg(210, 190, 16, &tc->fp16.f.f_even);
    uvCrashScreenPrintFloatReg(30, 200, 18, &tc->fp18.f.f_even);
    uvCrashScreenPrintFloatReg(120, 200, 20, &tc->fp20.f.f_even);
    uvCrashScreenPrintFloatReg(210, 200, 22, &tc->fp22.f.f_even);
    uvCrashScreenPrintFloatReg(30, 210, 24, &tc->fp24.f.f_even);
    uvCrashScreenPrintFloatReg(120, 210, 26, &tc->fp26.f.f_even);
    uvCrashScreenPrintFloatReg(210, 210, 28, &tc->fp28.f.f_even);
    uvCrashScreenPrintFloatReg(30, 220, 30, &tc->fp30.f.f_even);
#ifdef VERSION_EU
    osWritebackDCacheAll();
#endif
    osViBlack(FALSE);
    osViSwapBuffer(gCrashScreen.framebuffer);
}

OSThread *uvGetCrashedThread(void) {
    OSThread *thread;

    thread = __osGetActiveQueue();
    while (thread->priority != -1) {
        if (thread->priority > OS_PRIORITY_IDLE && thread->priority < OS_PRIORITY_APPMAX
            && (thread->flags & 3) != 0) {
            return thread;
        }
        thread = thread->tlnext;
    }
    return NULL;
}

void uvCrashScreenThread(void *arg) {
    OSMesg mesg;
    OSThread *thread;

    osSetEventMesg(OS_EVENT_CPU_BREAK, &gCrashScreen.mesgQueue, (OSMesg) 1);
    osSetEventMesg(OS_EVENT_FAULT, &gCrashScreen.mesgQueue, (OSMesg) 2);
    do {
        osRecvMesg(&gCrashScreen.mesgQueue, &mesg, 1);
        thread = uvGetCrashedThread();
    } while (thread == NULL);
    uvDrawCrashScreen(thread);
    for (;;) {
    }
}

void uvCrashScreenSetFrameBuf(u16 *framebuffer, u16 width, u16 height) {
#ifdef VERSION_EU
    gCrashScreen.framebuffer = framebuffer;
#else
    gCrashScreen.framebuffer = (u16 *)((u32)framebuffer | 0xa0000000);
#endif
    gCrashScreen.width = width;
    gCrashScreen.height = height;
}

void uvCrashScreenInit(void* fb) {
    gCrashScreen.framebuffer = fb;
    gCrashScreen.width = SCREEN_WIDTH;
    gCrashScreen.height = SCREEN_HEIGHT;
    osCreateMesgQueue(&gCrashScreen.mesgQueue, &gCrashScreen.mesg, 1);
    osCreateThread(
        &gCrashScreen.thread, 2, uvCrashScreenThread, NULL,
        (u8 *) gCrashScreen.stack + sizeof(gCrashScreen.stack),
#ifdef VERSION_EU
        OS_PRIORITY_APPMAX
#else
        OS_PRIORITY_RMON
#endif
    );
    osStartThread(&gCrashScreen.thread);
}

#endif

#undef TARGET_N64
#undef VERSION_EU