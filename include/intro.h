// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BAR_INTRO_H
#define BAR_INTRO_H

typedef struct Intro_Exports_s {
    /* 0x00 */ void (*introRestoreSavedRaceSettings)(void);                      /* inferred */
    /* 0x04 */ void (*introUpdatePlaybackAndAdvanceTrack)(void);
    /* 0x08 */ void (*introRenderEnabledSpritePair)(void);
} Intro_Exports;

#endif /* BAR_INTRO_H */
