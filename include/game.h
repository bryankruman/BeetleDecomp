// SPDX-License-Identifier: AGPL-3.0-or-later
enum gameState {
        INIT = -1,    // used during game init
        NONE = 0,
        UNUSED_PARADIGM_LOGO = 1,
        INTRO,
        DEMO,         // Attract demo while idling at main menu
        CREDITS,      // Demo with staff roll
        RACE,         // Single and Multiplayer
        BATTLE,       // Beetle Battle
        VICTORY,      // Championship win screen
        UFO_CAMERA,   // Free look camera
        SCENE_EDITOR, // General model viewer 
        TASK_EDITOR,  // Track editor
        AI_EDIT,      // AI Path editor
        TEXTURE_VIEWER, // Broken in final build
        COLOR_BARS,   // color bars test screen
        SELECTION,    // Save file select and main menu (game starts here)
        PROFILE_CAR   // Additional car model viewer
};

typedef enum GameLanguage_e {
  LANGUAGE_EN,
  LANGUAGE_DE,
  LANGUAGE_FR
} GameLanguage;

typedef enum GameTournament_e {
  TOURN_NOVICE,
  TOURN_ADVANCED,
  TOURN_PRO,
  TOURN_BONUS,
} GameTournament;

typedef enum GameTournRaceCount_e {
  TOURN_NOVICE_RACE_COUNT = 3,
  TOURN_ADVANCED_RACE_COUNT,
  TOURN_PRO_RACE_COUNT,
  TOURN_BONUS_RACE_COUNT
} GameTournRaceCount;

typedef enum GameOptionsMap_e {
  OPTIONS_MAP_OFF,
  OPTIONS_MAP_ZOOM,
  OPTIONS_MAP_FULL
} GameOptionsMap;

typedef enum GameOptionsSound_e {
  OPTIONS_SOUND_STEREO,
  OPTIONS_SOUND_MONO
} GameOptionsSound;

typedef enum GameOptionsSpeed_e {
  OPTIONS_SPEED_KPH,
  OPTIONS_SPEED_MPH
} GameOptionsSpeed;

typedef enum GameOptionsDisplay_e {
  OPTIONS_DISPLAY_OFF,
  OPTIONS_DISPLAY_ON
} GameOptionsDisplay;
