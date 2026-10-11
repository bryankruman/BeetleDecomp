#include "PR/os_internal.h"
#include "PR/ultraerror.h"
#include "PR/sptask.h"
#include "PR/rcp.h"
#include "PRinternal/osint.h"

#if BUILD_VERSION < VERSION_J
#ident "$Revision: 1.4 $"
#endif

#define _osVirtualToPhysical(ptr)              \
    if (ptr != NULL) {                         \
        ptr = (void*)osVirtualToPhysical(ptr); \
    } (void)0

static OSTask tmp_task;

/* Copy the task into the shared tmp_task, then use the existing macro to
 * replace each non-NULL task pointer field with its physical address.
 * Return the shared scratch task rather than the caller's task. RE_UNKNOWN:
 * address validity, scratch-task reentrancy and caller synchronization;
 * preserve the macro's in-place assignments and exact selected fields. */
#line 18 "src/libultra/io/sptask.c"
OSTask* _VirtualToPhysicalTask(OSTask* intp) {
    OSTask* tp;
    tp = &tmp_task;
    bcopy(intp, tp, sizeof(OSTask));

    _osVirtualToPhysical(tp->t.ucode);
    _osVirtualToPhysical(tp->t.ucode_data);
    _osVirtualToPhysical(tp->t.dram_stack);
    _osVirtualToPhysical(tp->t.output_buff);
    _osVirtualToPhysical(tp->t.output_buff_size);
    _osVirtualToPhysical(tp->t.data_ptr);
    _osVirtualToPhysical(tp->t.yield_data_ptr);
    return tp;
}

/* Prepare the shared physical task, retain the yielded/loadable-task
 * rewrite, write back that task, then perform the original status, PC and
 * DMA setup with busy retries in order. RE_ORIGINAL_QUIRK: the loadable
 * resume path reads the ucode pointer from yield_data_ptr plus
 * OS_YIELD_DATA_SIZE plus 0x2FC. RE_UNKNOWN: that retained custom layout,
 * DMA buffer bounds and termination/lifetime guarantees; preserve
 * _DEBUG-only checks and the caller flag update. */
#line 33 "src/libultra/io/sptask.c"
void osSpTaskLoad(OSTask* intp) {
    OSTask* tp;

#ifdef _DEBUG
    if ((intp->t.dram_stack != 0x0) && ((u32)intp->t.dram_stack & 0xf)) {
        __osError(ERR_OSSPTASKLOAD_DRAM, 1, intp->t.dram_stack);
        return;
    }
    if ((intp->t.output_buff != 0x0) && ((u32)intp->t.output_buff & 0xf)) {
        __osError(ERR_OSSPTASKLOAD_OUT, 1, intp->t.output_buff);
        return;
    }
    if ((intp->t.output_buff_size != 0x0) && ((u32)intp->t.output_buff_size & 0xf)) {
        __osError(ERR_OSSPTASKLOAD_OUTSIZE, 1, intp->t.output_buff_size);
        return;
    }
    if ((intp->t.yield_data_ptr != 0x0) && ((u32)intp->t.yield_data_ptr & 0xf)) {
        __osError(ERR_OSSPTASKLOAD_YIELD, 1, intp->t.yield_data_ptr);
        return;
    }
#endif

    tp = _VirtualToPhysicalTask(intp);

    if (tp->t.flags & OS_TASK_YIELDED) {
        tp->t.ucode_data = tp->t.yield_data_ptr;
        tp->t.ucode_data_size = tp->t.yield_data_size;
        intp->t.flags &= ~OS_TASK_YIELDED;
        if (tp->t.flags & OS_TASK_LOADABLE) {
            // Had to modify this part..
            tp->t.ucode = (u64*)IO_READ((u32)intp->t.yield_data_ptr + OS_YIELD_DATA_SIZE + 0x2FC);
        }
    }

    osWritebackDCache(tp, sizeof(OSTask));
    __osSpSetStatus(SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_SET_INTR_BREAK);

    while (__osSpSetPc(SP_IMEM_START) == -1) {}

    while (__osSpRawStartDma(1, (SP_IMEM_START - sizeof(*tp)), tp, sizeof(OSTask)) == -1) {}

    while (__osSpDeviceBusy()) {}

    while (__osSpRawStartDma(1, SP_IMEM_START, tp->t.ucode_boot, tp->t.ucode_boot_size) == -1) {}
}

/* Wait until the signal processor is not busy, then issue the existing
 * status bits to leave halt/break/single-step and enable the break
 * interrupt. The task pointer is unused here. RE_UNKNOWN: required prior
 * load, execution ownership and whether the busy wait is guaranteed to
 * terminate. */
#line 79 "src/libultra/io/sptask.c"
void osSpTaskStartGo(OSTask* tp) {
    while (__osSpDeviceBusy()) {}

    __osSpSetStatus(SP_SET_INTR_BREAK | SP_CLR_SSTEP | SP_CLR_BROKE | SP_CLR_HALT);
}
