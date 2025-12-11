/*
 * menu.c - Main menu system implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "menu.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * show_main_menu() - Display main menu and get player choice
 *
 * Displays colorized main menu with options for new game, load game,
 * or quit. Validates input and returns appropriate choice.
 *
 * Return: MenuChoice enum value
 */
MenuChoice show_main_menu(void) {
	char input[10];
	int choice;

	printf("\n");
	printf_colored(COLOR_BOLD COLOR_CYAN, "========================================\n");
	printf_colored(COLOR_BOLD COLOR_CYAN, "    TEXT ADVENTURE ENGINE v1.0\n");
	printf_colored(COLOR_BOLD COLOR_CYAN, "========================================\n");
	printf("\n");
	printf_colored(COLOR_BRIGHT_GREEN, "1. ");
	printf("New Game\n");
	printf_colored(COLOR_BRIGHT_YELLOW, "2. ");
	printf("Load Game\n");
	printf_colored(COLOR_BRIGHT_RED, "3. ");
	printf("Quit\n");
	printf("\n");
	printf_colored(COLOR_BOLD, "Choice: ");
	
	if (fgets(input, sizeof(input), stdin) == NULL) {
		return MENU_INVALID;
	}
	
	choice = atoi(input);
	
	switch (choice) {
	case 1:
		return MENU_NEW_GAME;
	case 2:
		return MENU_LOAD_GAME;
	case 3:
		return MENU_QUIT;
	default:
		printf_colored(COLOR_ERROR, "Invalid choice!\n");
		return MENU_INVALID;
	}
}