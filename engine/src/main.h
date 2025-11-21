#ifndef MAIN_H
#define MAIN_H

#include "core/game.h"
#include "story/story.h"

/*
 * Function declarations for main game flow
 */

// Start a new game (story selection and initialization)
void start_new_game(void);

// Load a saved game
void load_saved_game(void);

// Main game loop
void play_game(GameState* game);

#endif // MAIN_H