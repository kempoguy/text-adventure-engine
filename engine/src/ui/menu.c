#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Display main menu and get player choice
 */
MenuChoice show_main_menu(void) {
    printf("\n");
    printf("========================================\n");
    printf("    TEXT ADVENTURE ENGINE v1.0\n");
    printf("========================================\n");
    printf("\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Quit\n");
    printf("\n");
    printf("Choice: ");
    
    char input[10];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return MENU_INVALID;
    }
    
    int choice = atoi(input);
    
    switch (choice) {
        case 1:
            return MENU_NEW_GAME;
        case 2:
            return MENU_LOAD_GAME;
        case 3:
            return MENU_QUIT;
        default:
            printf("Invalid choice!\n");
            return MENU_INVALID;
    }
}