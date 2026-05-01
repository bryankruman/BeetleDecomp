// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BAR_FUNCTIONS_H
#define BAR_FUNCTIONS_H
u32 uvFileGetEntryTag(s32 arg0, u32* arg1, void** arg2);
void* _uvMemAllocAlign8(u32);
void _uvMemFree(void*);
void mio0Decode(void* src, u8* dst);
u64 uvMemRead(void* vAddr, u32 nbytes);
void _uvDMA(void* vAddr, u32 devAddr, u32 nbytes);
void _uvMediaCopy(void* vAddr, void* devAddr, u32 nbytes);
void uvMemSet(void* vAddr, u8 value, u32 nbytes);
void *_uvMemAllocAlign8(u32 size);
void* _uvMemAllocAlign16(u32 size);
void uvLoadFormFiles(void);
UnkStruct_8002D1A4* func_800034E0(s32 tag);
void uvSetFileDirOvlPtr(s32);
void* uvLoadModule(s32 tag);
void* uvGetSystemProp(s32 index);
void* _uvMemAlloc(u32 size, u32 alignment);
s32 uvGetFileData(s32 tag, s32 fileId);
void uvConsumeBytes(void* dst, u8** ptr, u32 size);
s32 func_800019B8(s32 tag, s32);
void uvUnloadModule(s32 tag);
void _uvScAddClient(OSSched *sc, OSScClient *client, OSMesgQueue *mq);
void func_8000226C(s32*, s32*, s32*, u32);                   /* extern */
void func_80002088(s32*, s32*, s32*, s32);                   /* extern */
s32 _uvMemGetBlocksSize(void);
void func_8000218C(s32 *arg0, s32 *arg1, s32 *arg2, s32 arg3);
s32 uvGetFilesCount(s32 tag);
s32 func_800017A4(s32 tag, s32 fileId);
void func_80001A68(s32 tag, s32 arg1);
void *func_80001724(s32, s32);

#endif /* BAR_FUNCTIONS_H */
