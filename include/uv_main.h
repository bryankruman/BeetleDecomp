#ifndef UV_MAIN_H
#define UV_MAIN_H
void _uvDebugPrintf(char *fmt, ...);
void _uvDMA(void *vAddr, u32 devAddr, u32 nbytes);
u8 uvContMesgInit(OSMesgQueue **siContQ, OSContStatus **contStatus);
void func_80005570(void);
#endif /* UV_MAIN_H */
