/*
 * constants.h - Game constant definitions - because magic numbers are for 
                 assholes
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H



/* Parser buffer sizes */

#define PARSER_EXIT_BUFFER_SIZE       128 /* Room exit parsing */
#define PARSER_INPUT_BUFFER_SIZE      256 /* Player command input */
#define PARSER_NOUN_SIZE              64  /* Command noun/noun2 */
#define PARSER_PREPOSITION_SIZE       16  /* Command preposition */
#define PARSER_RESPONSE_BUFFER_SIZE   10  /* Quit confirmation response */
#define PARSER_VERB_SIZE              32  /* Command verb */


/* Item field sizes */

#define ITEM_ID_SIZE                  64  /* Item identifier */
#define ITEM_NAME_SIZE                64  /* Item display name */
#define ITEM_DESCRIPTION_SIZE         256 /* Item description */


/* INI file parsing */

#define INI_LINE_BUFFER_SIZE          512 /* INI file line buffer */
#define INI_SECTION_SIZE              128 /* INI section name */
#define INI_KEY_SIZE                  64  /* INI key name */
#define INI_VALUE_SIZE                256 /* INI value string */


/* Logging */

#define LOG_TIMESTAMP_SIZE            32  /* Log timestamp buffer size */
#define LOG_FILENAME_SIZE             256 /* Log filename buffer */
#define LOG_MESSAGE_BUFFER_SIZE       512 /* Internal log message formatting */


/* String utilities */

#define STRING_MATCH_BUFFER_SIZE      256 /* String match buffer size */

/* Load/Save funcitons */

#define SAVE_MAX_SLOTS                 3   /* Number of save slots */
#define SAVE_DIRECTORY                 "saves"
#define SAVE_FILENAME_FORMAT           "saves/save_slot_%d.sav"

/* Story data field sizes */
#define STORY_TITLE_SIZE           128
#define STORY_AUTHOR_SIZE          64
#define STORY_VERSION_SIZE         16
#define STORY_DESCRIPTION_SIZE     512
#define STORY_DIRECTORY_SIZE       256

#define ROOM_ID_SIZE               64
#define ROOM_NAME_SIZE             128
#define ROOM_DESCRIPTION_SIZE      512
#define ROOM_LOCKED_EXIT_SIZE      64   /* ID of locked exit direction */

#define NPC_ID_SIZE                64
#define NPC_NAME_SIZE              128
#define NPC_DESCRIPTION_SIZE       256
#define NPC_LOCATION_SIZE          64

/* Quest constants */
#define QUEST_ID_SIZE              64
#define QUEST_NAME_SIZE            128
#define QUEST_DESCRIPTION_SIZE     512
#define QUEST_COMPLETION_ID_SIZE   64
#define COMBAT_MSG_SIZE            512
#define COMBAT_MAX_HP              10
#define COMBAT_BASE_WIN_CHANCE     0.75f
#define COMBAT_ITEM_WIN_CHANCE     0.95f
#define COMBAT_FLEE_CHANCE         0.05f

#endif /* CONSTANTS_H */

