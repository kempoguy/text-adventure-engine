#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Initialize game state for a story
 */
GameState* init_game_state(Story* story) {
    printf("[STUB] init_game_state()\n");
    
    GameState* game = malloc(sizeof(GameState));
    if (!game) {
        return NULL;
    }
    
    game->story = story;
    game->current_room = NULL;  // Will set this when we implement room system
    game->inventory = NULL;
    game->inventory_count = 0;
    game->inventory_weight = 0;
    game->quest_flags = NULL;
    game->quest_count = 0;
    game->death_count = 0;
    game->turn_count = 0;
    game->score = 0;
    game->game_won = false;
    
    return game;
}

/*
 * Free game state
 */
void free_game_state(GameState* game) {
    printf("[STUB] free_game_state()\n");
    
    if (game) {
        // Free inventory if allocated
        if (game->inventory) {
            free(game->inventory);
        }
        
        // Free quest flags if allocated
        if (game->quest_flags) {
            free(game->quest_flags);
        }
        
        free(game);
    }
}

/*
 * Check if player has won
 */
bool check_victory_condition(GameState* game) {
    // Stub: Always return false for now
    return game->game_won;
}

/*
 * Display current room
 */
void look_at_current_room(GameState* game) {
    (void)game; // TODO
    printf("[STUB] look_at_current_room()\n");
    printf("\nYou are in a test room.\n");
    printf("This is where the room description will appear.\n");
    printf("Exits: north, south, east, west\n");
}