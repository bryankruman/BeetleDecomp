#ifndef EXPL_H
#define EXPL_H

typedef struct {
    void (*func_expl_004000AC)(void);
    void (*func_expl_0040011C)(Vec3F *, f32);
    void (*explClearFinishedParticleHandles)(void);
    s32 (*func_expl_00400370)(Vec3F*, f32*);
} Expl_Exports;

#endif /* EXPL_H */
