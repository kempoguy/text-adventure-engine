/*
 * game.c - Core game state management implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"



/**
 * find_room_by_id() - Find a room by its identifier
 * @story: Pointer to story data
 * @room_id: String identifier of room to find
 *
 * Searches the story's room array for a matching room ID using string
 *  comparison.
 *
 * Return: Pointer to room if found, NULL otherwise
 */

Room* find_room_by_id(Story* story, const char* room_id) {
    for (int i = 0; i < story->room_count; i++) {
        if (strcmp(story->rooms[i].id, room_id) == 0) {
            return &story->rooms[i]; // Return pointer to this room
        }
    }
    return NULL; // Not found
}



 /**
  * init_game_state() - Create and Initialise game state for a story
  * @story: Pointer to a loaded story
  *
  * Allocates and initializes a new GameState structure, finds and sets the
  * starting room from story metadata, and initializes all counters and flags 
  * to zero.
  *
  * Return: Pointer to initialized GameState, or NULL on allocation failure
  */
 
GameState* init_game_state(Story* story) {
    
    GameState* game = malloc(sizeof(GameState));
    if (!game) {
        return NULL;
    }
    
    game->story = story;

    // Find the starting room
    game->current_room = find_room_by_id(story, story->metadata.start_room); 
    if (!game->current_room) {
        printf("ERROR: Starting room '%s' not found!\n", story->metadata.start_room);
        free(game);
        return NULL;
    }

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


 /**
  * free_game_state() - Free game state and associated resources
  * @game: Pointer to game state to free
  *
  * Frees inventory array, quest flags array, and the game state structure
  * itself. Handles NULL pointers safely.
  *
  * Return: void
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


 /**
  * check_victory_condition() - Check if player has won the game
  * @game: Pointer to current game state
  * @param2: Description of second parameter
  *
  * Checks the game_won flag to determine if victory condition has been met.
  *
  * Return: True if player has won, false otherwise
  */
 
bool check_victory_condition(GameState* game) {
    return game->game_won;
}


 /**
  * look_at_current_room() - Display current room description
  * @game: Pointer to current game state
  * Prints room name, description, available exits with directions, and visible 
  * items in the room
  *
  * Return: void
  */
 
void look_at_current_room(GameState* game) {
    if (!game->current_room) {
        printf("ERROR: No current room!\n");
        return;
    }

    Room* room = game->current_room;

    // Print room name
    printf("%s\n", room->name);

    // Print room description
    printf("%s\n", room->description);

    // Print exits
    if (room->exit_count > 0) {
        printf("\nExits:");
        for (int i = 0; i < room->exit_count; i++) {
            // Parse "direction:room_id" format
            char exit_copy[128];
            strncpy(exit_copy, room->exits[i], sizeof(exit_copy) - 1);
            exit_copy[sizeof(exit_copy) - 1] = '\0';

            char* colon = strchr(exit_copy, ':');
            if (colon) {
                *colon = '\0'; // Split at colon
                char* direction = exit_copy;
                printf(" %s", direction);
            }
        }
        printf("\n");
    } else {
        printf("No obvious exits.\n");
    }

    // Print items (if any)
    if (room->item_count > 0) {
        printf("\n you see:");
        for (int i = 0; i < room->item_count; i++) {
            printf(" %s", room->items[i]);
        }
        printf("\n");
    }
}