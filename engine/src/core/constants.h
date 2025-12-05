/*
 * constants.h - Game constant definitions
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H


/*
 * Parser buffer sizes
 * 
 * Because magic numbers are for assholes.
 */

#define PARSER_EXIT_BUFFER_SIZE       128 /* Room exit parsing */
#define PARSER_INPUT_BUFFER_SIZE      256 /* Player command input */
#define PARSER_NOUN_SIZE              64  /* Command noun/noun2 */
#define PARSER_PREPOSITION_SIZE       16  /* Command preposition */
#define PARSER_RESPONSE_BUFFER_SIZE   10  /* Quit confirmation response */
#define PARSER_VERB_SIZE              32  /* Command verb */

#endif /* CONSTANTS_H */

