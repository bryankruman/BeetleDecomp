#ifndef MODULE_LOAD_H
#define MODULE_LOAD_H

void uvModuleInit(void);
s32 uvGetModuleFileId(s32 tag);
void *uvGetLoadedModule(s32 tag);
void *uvLoadModule(s32 tag);
void *uvLoadModuleCode(u8 *data);
void uvUnloadModule(s32 tag);
s32 func_80003A14(u32 arg0, s32 *arg1);

#endif /* MODULE_LOAD_H */
