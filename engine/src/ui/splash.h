/*
 * splash.h - Silly Walk Engine splash screen
 *
 * Displays the engine splash screen on startup with ASCII art
 * and waits for user input to continue.
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SPLASH_H
#define SPLASH_H

#include "ui/colors.h"

/**
 * splash_show() - Display splash screen and wait for keypress
 *
 * Clears the screen, displays the Silly Walk Engine splash screen
 * with ASCII art mountain landscape, and waits for any key press
 * before continuing. Clears screen again after keypress.
 *
 * Return: void
 */
void splash_show(void);

#endif /* SPLASH_H */