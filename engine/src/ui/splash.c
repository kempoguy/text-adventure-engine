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


/*
 * Define splash-screen ASCII art char array
*/

static const char *splash_art = 
"                                          |"
COLOR_RED
">>>\n"
COLOR_RESET
"                                          |\n"
"                       |"
COLOR_GREEN
">>>"
COLOR_RESET
"           _  _|_  _             |"
COLOR_BLUE
">>>\n"
COLOR_RESET
"                       |             [;]|[;]|[;]            |\n"
"                   _  _|_  _         \\  .   . /        _  _|_  _\n"
"                  [;]_[;]_[;]         \\ :  , /        [;]_[;]_[;]\n"
"                  \\..       /         ||;  . |        \\ : . .   /\n"
"                   \\.     ,/          ||:  : |         \\.  .   /\n"
"                    ||:    |_   _   _ |::  _ | _   _   _||:   :|\n"
"                    ||:  . |||_[;]_[;]_[;]_[;]_[;]_[;]_|||:    |\n"
"                    ||: .  ||.    .       .       .     ||:   .|\n"
"                    ||:    ||  .    .   .        .      ||: .  |\n"
"                    ||:  . ||   .           .       .   ||:    |\n"
"                    ||:    || ,       /"
COLOR_YELLOW
"+++++++"
COLOR_RESET
"\\         ||:  , |\n"
"                    ||: .  ||.        |"
COLOR_YELLOW
"+++++++"
COLOR_RESET
"|         ||:    |\n"
COLOR_GREEN
"                __"
COLOR_RESET
"  ||:  . ||:        |"
COLOR_YELLOW
"+++++++"
COLOR_RESET
"|        "
COLOR_GREEN
"_"
COLOR_RESET
"||"
COLOR_GREEN
"_"
COLOR_RESET
" .  |\n"
COLOR_GREEN
"            --`~   `--~   __"
COLOR_RESET
"|.        |"
COLOR_YELLOW
"++++"
COLOR_RESET
"|"
COLOR_GREEN
"------~     ~ ----,\n"
"        ____                ~---    __|,--~`                  ~~----         ~~----\n"
"   -~--~                                                             _____\n"
COLOR_RESET

COLOR_MAGENTA
"    _____ _ _ _\n"
"   / ____(_) | |       __        __    _ _      _____                       \n"
"  | (___  _| | |_   _  \\ \\      / /_ _| | | __ | ____|_ __   __  (_) ___   ___\n"
"   \\____\\| | | | | | |  \\ \\ /\\ / / _` | | |/ / |  _| | '_ \\ / _` | | '_ \\ / _ \\\n"
"   ____) | | | | |_| |   \\ V  V / (_| | |   <  | |___| | | | (_| | | | | |  __/\n"
"  |_____/|_|_|_|\\___,|    \\_/\\_/ \\__,_|_|_|\\_\\ |_____|_| |_|\\__, |_|_| |_|\\___|\n"
"                |___/                                        |___/             \n"
" \n"
COLOR_RESET
"                              A Text Adventure Engine\n"
"                             Created by Marty & Claude\n"
"                                v1.0 December, 2025\n\n"
COLOR_RED
"                               PRESS ANY KEY TO BEGIN\n"
COLOR_RESET;
/*
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




const char *splash_screen = 
"                                          |" COLOR_RED ">>>\n"
"                                          |\n"
"                       |>>>           _  _|_  _             |>>>\n"
"                       |             [;]|[;]|[;]            |\n"
"                   _  _|_  _         \\  .   . /        _  _|_  _\n"
"                  [;]_[;]_[;]         \\ :  , /        [;]_[;]_[;]\n"
"                  \\..      /         ||;  .  |        \\ : . .  /\n"
"                   \\.    ,/          ||:  :  |         \\.  .  /\n"
"                   ||:     |_   _   _ |::   _ | _   _  _||:   :|\n"
"                   ||:   . |||_[;]_[;]_[;]_[;]_[;]_[;]_|||:    |\n"
"                   ||: .   ||.    .       .       .     ||:   .|\n"
"                   ||:     ||  .    .   .        .      ||: .  |\n"
"                   ||:   . ||   .           .       .   ||:    |\n"
"                   ||:     || ,       /+++++++\\        ||:  , |\n"
"                   ||: .   ||.        |+++++++|         ||:    |\n"
"                __ ||:   . ||:        |+++++++|        _||_ .  |\n"
"            --`~   `--~   __|.        |++++___|------~     ~ ----,\n"
"        ____                ~---    __|,--~`                  ~~----               ~~----\n"
"   -~--~                                                             _____\n"
"|   _____ _ _ _        __        __    _ _      _____       _            |\n"
"|  / ____(_) | |       \\ \\      / /_ _| | | __ | ____|_ __   __ _(_)_ _____\n"
"| | (___  _| | |_   _   \\ \\ /\\ / / _` | | |/ / |  _| | '_ \\ / _` | | '_ \\ / _ \\|\n"
"|  \\___ \\| | | | | | |   \\ V  V / (_| | |   <  | |___| | | | (_| | | | | |  __/|\n"
"|  ____) | | | | |_| |    \\_/\\_/ \\__,_|_|_|\\_\\ |_____|_| |_|\\__, |_|_| |_|\\___||\n"
"| |_____/|_|_|_|\\__, |                                       |___/             |\n"
"|               |___/   
*/


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