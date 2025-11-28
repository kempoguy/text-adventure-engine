#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "../story/story.h"

/*
 * Game state structure
 * Contains all runtime game data
 */
typedef struct {
    Story* story;              // Currently loaded story
    Room* current_room;        // Current room player is in
    Item** inventory;          // Player inventory (array of pointers)
    int inventory_count;       // Number of items in inventory
    int inventory_weight;      // Total weight carried
    int* quest_flags;          // Quest completion flags
    int quest_count;           // Number of quests
    int death_count;           // Number of times player died
    int turn_count;            // Number of turns taken
    int score;                 // Current score
    bool game_won;             // Has player won?
} GameState;

/*
 * Game state management functions
 */

// Initialize game state for a story
GameState* init_game_state(Story* story);

// Free game state
void free_game_state(GameState* game);

// Check if player has won
bool check_victory_condition(GameState* game);

// Display current room
void look_at_current_room(GameState* game);

// Find room by ID
Room* find_room_by_id(Story* story, const char* room_id);

#endif // GAME_H