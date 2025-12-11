/*
 * colors.h - ANSI color system
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef COLORS_H
#define COLORS_H

/*
 * ANSI color codes - Regular
 */
#define COLOR_RESET         "\033[0m"
#define COLOR_BLACK         "\033[30m"
#define COLOR_RED           "\033[31m"
#define COLOR_GREEN         "\033[32m"
#define COLOR_YELLOW        "\033[33m"
#define COLOR_BLUE          "\033[34m"
#define COLOR_MAGENTA       "\033[35m"
#define COLOR_CYAN          "\033[36m"
#define COLOR_WHITE         "\033[37m"

/*
 * ANSI color codes - Bright
 */
#define COLOR_BRIGHT_BLACK      "\033[90m"
#define COLOR_BRIGHT_RED        "\033[91m"
#define COLOR_BRIGHT_GREEN      "\033[92m"
#define COLOR_BRIGHT_YELLOW     "\033[93m"
#define COLOR_BRIGHT_BLUE       "\033[94m"
#define COLOR_BRIGHT_MAGENTA    "\033[95m"
#define COLOR_BRIGHT_CYAN       "\033[96m"
#define COLOR_BRIGHT_WHITE      "\033[97m"

/*
 * ANSI formatting
 */
#define COLOR_BOLD          "\033[1m"
#define COLOR_DIM           "\033[2m"
#define COLOR_UNDERLINE     "\033[4m"

/*
 * Utility codes
 */
#define COLOR_CLEAR         "\033[2J\033[H"
#define COLOR_GRAY          COLOR_BRIGHT_BLACK

/*
 * Semantic color aliases (what they represent)
 */
#define COLOR_SUCCESS       COLOR_GREEN
#define COLOR_ERROR         COLOR_RED
#define COLOR_WARNING       COLOR_YELLOW
#define COLOR_INFO          COLOR_CYAN
#define COLOR_DANGER        COLOR_BRIGHT_RED
#define COLOR_QUEST         COLOR_BRIGHT_YELLOW
#define COLOR_NPC           COLOR_CYAN
#define COLOR_ITEM          COLOR_YELLOW
#define COLOR_MAGIC         COLOR_MAGENTA
#define COLOR_COMBAT_HIT    COLOR_GREEN
#define COLOR_COMBAT_MISS   COLOR_RED
#define COLOR_DEATH         COLOR_BRIGHT_RED

/*
 * Color system functions
 */

/* Initialize color system */
void color_init(void);

/* Cleanup color system */
void color_cleanup(void);

/* Check if colors are enabled */
int color_enabled(void);

/* Print colored text (auto-resets) */
void print_colored(const char* text, const char* color);

/* Printf-style colored output */
void printf_colored(const char* color, const char* format, ...);

#endif /* COLORS_H */