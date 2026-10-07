#ifndef EXPL_H
#define EXPL_H

typedef struct {
    void (*explReleaseSoundHandle)(void);
    void (*explCreateEffectAtPosition)(Vec3F *, f32);
    void (*explClearFinishedParticleHandles)(void);
    s32 (*explGetMinimumSurfaceDistance)(Vec3F*, f32*);
} Expl_Exports;

#endif /* EXPL_H */
