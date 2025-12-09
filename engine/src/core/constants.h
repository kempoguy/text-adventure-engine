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

#endif /* CONSTANTS_H */

