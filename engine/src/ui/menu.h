#ifndef MENU_H
#define MENU_H

/*
 * Menu choices
 */
typedef enum {
    MENU_NEW_GAME,
    MENU_LOAD_GAME,
    MENU_QUIT,
    MENU_INVALID
} MenuChoice;

/*
 * Menu functions
 */

// Display main menu and get player choice
MenuChoice show_main_menu(void);

#endif // MENU_H