/*
 * main.h - Main game flow function declarations
 *
 * Copyright (C) 2025 Marty 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */



#ifndef MAIN_H
#define MAIN_H

#include "core/game.h"
#include "story/story.h"

/*
 * Function declarations for main game flow
 */


/**
 * start_new_game() - Initialize and start a new game
 *
 * Scans for available stories, allows player selection,
 * validates the story, and enters the main game loop.
 *
 * Return: void
 */

void start_new_game(void);


/**
 * load_saved_game() - Load a previously saved game
 *
 * Displays available save files and loads the selected game state.
 *
 * Return: void
 */

void load_saved_game(void);


/**
 * play_game() - Execute the main game loop
 * @game: Pointer to initialized game state
 *
 * Displays the starting location, processes player commands
 * in a loop until quit or victory condition is met.
 *
 * Return: void
 */


void play_game(GameState* game);

#endif /* MAIN_H */