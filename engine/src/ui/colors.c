/*
 * colors.c - ANSI color system implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "colors.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#ifdef _WIN32
#include <windows.h>
#endif

static bool colors_enabled = true;

/**
 * color_init() - Initialize color system
 *
 * On Windows, enables ANSI escape sequence processing.
 * On other platforms, assumes terminal supports ANSI.
 *
 * Return: void
 */
void color_init(void) {
#ifdef _WIN32
	/* Enable ANSI escape sequences on Windows 10+ */
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	
	if (hOut != INVALID_HANDLE_VALUE) {
		GetConsoleMode(hOut, &dwMode);
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, dwMode);
	}
#endif
	colors_enabled = true;
}

/**
 * color_cleanup() - Cleanup color system
 *
 * Resets terminal to default state.
 *
 * Return: void
 */
void color_cleanup(void) {
	if (colors_enabled) {
		printf(COLOR_RESET);
	}
}

/**
 * color_enabled() - Check if colors are enabled
 *
 * Return: 1 if enabled, 0 if disabled
 */
int color_enabled(void) {
	return colors_enabled;
}

/**
 * print_colored() - Print colored text with auto-reset
 * @text: Text to print
 * @color: ANSI color code
 *
 * Prints text in specified color, then resets to default.
 *
 * Return: void
 */
void print_colored(const char* text, const char* color) {
	if (colors_enabled) {
		printf("%s%s%s", color, text, COLOR_RESET);
	} else {
		printf("%s", text);
	}
}

/**
 * printf_colored() - Printf-style colored output
 * @color: ANSI color code
 * @format: Printf format string
 * @...: Variable arguments for format string
 *
 * Prints formatted text in specified color with auto-reset.
 *
 * Return: void
 */
void printf_colored(const char* color, const char* format, ...) {
	va_list args;
	
	if (colors_enabled) {
		printf("%s", color);
	}
	
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	
	if (colors_enabled) {
		printf("%s", COLOR_RESET);
	}
}