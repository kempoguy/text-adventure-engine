/*
 * splash.c - Silly Walk Engine splash screen implementation
 *
 * Displays ASCII art splash screen with the Silly Walk Engine
 * branding and mountain path landscape.
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include "splash.h"
#include "ui/colors.h"

/* ANSI color codes 
#define COLOR_RESET      "\033[0m"
#define COLOR_CYAN       "\033[36m"
#define COLOR_BRIGHT_CYAN "\033[96m"
#define COLOR_YELLOW     "\033[33m"
#define COLOR_WHITE      "\033[37m"
#define COLOR_GRAY       "\033[90m"
#define COLOR_GREEN      "\033[92m"

/* Clear screen ANSI code 
#define COLOR_CLEAR      "\033[2J\033[H"
*/ 

/*
 * Splash screen ASCII art - stored as a single string
 * Colors embedded using ANSI codes
 * Uses pure ASCII characters for maximum compatibility
 */
static const char *splash_art = 
COLOR_CLEAR
"+------------------------------------------------------------------------------+\n"
"|                                                                              |\n"
COLOR_BRIGHT_CYAN
"|   _____ _ _ _        __        __    _ _      _____             _            |\n"
"|  / ____(_) | |       \\ \\      / /_ _| | | __ | ____|_ __   __ _(_)_ __   ___ |\n"
"| | (___  _| | |_   _   \\ \\ /\\ / / _` | | |/ / |  _| | '_ \\ / _` | | '_ \\ / _ \\|\n"
"|  \\___ \\| | | | | | |   \\ V  V / (_| | |   <  | |___| | | | (_| | | | | |  __/|\n"
"|  ____) | | | | |_| |    \\_/\\_/ \\__,_|_|_|\\_\\ |_____|_| |_|\\__, |_|_| |_|\\___||\n"
"| |_____/|_|_|_|\\__, |                                       |___/             |\n"
"|               |___/                                                          |\n"
COLOR_RESET
"|                                                                              |\n"
COLOR_YELLOW
"|                    A Text Adventure Framework                                |\n"
COLOR_RESET
"|                                                                              |\n"
"|                                                                              |\n"
COLOR_WHITE
"|       *                          *                    *                      |\n"
"|      /.\\"
COLOR_GRAY
"                        "
COLOR_WHITE
"/.\\"
COLOR_GRAY
"                  "
COLOR_WHITE
"/.\\"
COLOR_GRAY
"         "
COLOR_WHITE
"*           |\n"
"|     // \\\\"
COLOR_GRAY
"          "
COLOR_WHITE
"*"
COLOR_GRAY
"           "
COLOR_WHITE
"// \\\\"
COLOR_GRAY
"                "
COLOR_WHITE
"// \\\\"
COLOR_GRAY
"     "
COLOR_WHITE
"/.\\"
COLOR_GRAY
"          |\n"
"|    //   \\\\"
COLOR_GRAY
"        "
COLOR_WHITE
"/.\\"
COLOR_GRAY
"         "
COLOR_WHITE
"//   \\\\"
COLOR_GRAY
"     "
COLOR_WHITE
"*"
COLOR_GRAY
"        "
COLOR_WHITE
"//   \\\\"
COLOR_GRAY
"     "
COLOR_WHITE
"// \\\\"
COLOR_GRAY
"         |\n"
"|   /       \\"
COLOR_GRAY
"      "
COLOR_WHITE
"// \\\\"
COLOR_GRAY
"       "
COLOR_WHITE
"/       \\"
COLOR_GRAY
"   "
COLOR_WHITE
"/.\\"
COLOR_GRAY
"      "
COLOR_WHITE
"/       \\"
COLOR_GRAY
"   "
COLOR_WHITE
"//   \\\\"
COLOR_GRAY
"        |\n"
"|  /         \\"
COLOR_GRAY
"    "
COLOR_WHITE
"//   \\\\"
COLOR_GRAY
"     "
COLOR_WHITE
"/         \\"
COLOR_GRAY
" "
COLOR_WHITE
"// \\\\"
COLOR_GRAY
"    "
COLOR_WHITE
"/         \\"
COLOR_GRAY
" "
COLOR_WHITE
"/       \\"
COLOR_GRAY
"       |\n"
"| /           \\"
COLOR_GRAY
"  "
COLOR_WHITE
"/       \\"
COLOR_GRAY
"   "
COLOR_WHITE
"/           "
COLOR_GRAY
"V"
COLOR_WHITE
"     \\"
COLOR_GRAY
"  "
COLOR_WHITE
"/           "
COLOR_GRAY
"V"
COLOR_WHITE
"         \\"
COLOR_GRAY
"      |\n"
"|/             \\"
COLOR_GRAY
"\\/         "
COLOR_WHITE
"\\"
COLOR_GRAY
" /                   "
COLOR_WHITE
"\\/"
COLOR_GRAY
"                       "
COLOR_WHITE
"\\"
COLOR_GRAY
"     |\n"
"|                          V                                              \\"
COLOR_GRAY
"    |\n"
"|    o                                   o                                 "
COLOR_GRAY
"\\"
COLOR_WHITE
"   |\n"
"|   /|\\"
COLOR_GRAY
"           ~  ~         ~              ~       ~                     "
COLOR_WHITE
"\\"
COLOR_GRAY
"  |\n"
"|   / \\"
COLOR_GRAY
"      ~           ~          ~              ~         ~               "
COLOR_WHITE
"\\"
COLOR_GRAY
" |\n"
"|       ~       ~              ~         ~                 ~                   |\n"
"|  ~       ~          ~              ~         ~                               |\n"
COLOR_RESET
"|                                                                              |\n"
COLOR_GRAY
"|                        Created by Marty with Claude                          |\n"
"|                            Version 1.0 - 2025                                |\n"
COLOR_RESET
"|                                                                              |\n"
COLOR_GREEN
"|                      Press any key to continue . . .                         |\n"
COLOR_RESET
"|                                                                              |\n"
"+------------------------------------------------------------------------------+\n"
COLOR_RESET;

/**
 * splash_show() - Display splash screen and wait for keypress
 *
 * Displays the Silly Walk Engine splash screen with ASCII art
 * and waits for user to press any key before continuing.
 *
 * Return: void
 */
void splash_show(void)
{
	/* Display the splash screen */
	printf("%s", splash_art);
	
	/* Wait for any keypress */
	getchar();
	
	/* Clear screen again */
	printf(COLOR_CLEAR);
}