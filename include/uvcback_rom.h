#ifndef UVCBACK_ROM_H
#define UVCBACK_ROM_H

typedef void (*CallbackRoutine)(s32 arg0);

typedef struct CallbackEntry {
    CallbackRoutine callback;
    s32 priority;
} CallbackEntry;

typedef struct CallbackList_s {
    s32 capacity;
    CallbackEntry entries[];
} CallbackList;

typedef struct UvCback_Exports_s {
    /* 0x00 */ void (*uvCallbackUnused)(void);                      /* inferred */
    /* 0x04 */ void *(*uvCreateCallbackList)(s32);                  /* inferred */
    /* 0x08 */ void (*uvCallbackFree)(void *);                /* inferred */
    /* 0x0C */ void (*uvExecuteCallbacks)(CallbackList *, s32); /* inferred */
    /* 0x10 */ s32 (*uvAddCallback)(CallbackList *, CallbackRoutine, CallbackRoutine, s32); /* inferred */
    /* 0x14 */ s32 (*uvRemoveCallback)(CallbackList *, CallbackRoutine); /* inferred */
    /* 0x18 */ s32 (*uvContainsCallback)(CallbackList *, CallbackRoutine, u8); /* inferred */
} UvCback_Exports;
#endif /* UVCBACK_ROM_H */
