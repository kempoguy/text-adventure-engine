/*
 * game.c - Core game state management implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui/colors.h"
#include "constants.h"
#include "core/logger.h"
#include "game.h"
#include "world/items.h"
#include "world/npcs.h"



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
    
    add_log_entry("Searching for room: %s at %s", room_id, log_timestamp());

    for (int i = 0; i < story->room_count; i++) {
        if (strcmp(story->rooms[i].id, room_id) == 0) {
            add_log_entry("Found room: %s at %s", room_id, log_timestamp());
            return &story->rooms[i]; /* Return pointer to this room */
        }
    }
    
    add_log_entry("Room not found: %s at %s", room_id, log_timestamp());
    return NULL; /* Not found */
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
    GameState* game; 
    
    log_function_entry(__func__, "story=%s", story->metadata.title);

    game = malloc(sizeof(GameState));
    if (!game) {
        log_function_error(__func__, "Failed to allcoate GameState");
        log_function_exit(__func__, 0);
        return NULL;
    }
    
    game->story = story;

    /* Find the starting room */
    game->current_room = find_room_by_id(story, story->metadata.start_room); 
    if (!game->current_room) {
        printf(COLOR_RED "ERROR: Starting room '%s' not found!\n" COLOR_RESET, story->metadata.start_room);
        free(game);
        log_function_error(__func__, "ERROR: Starting room not found!");
        log_function_exit(__func__, 0);
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
    
    add_log_entry("Game initialized: room=%s, inventory_slots=%d at %s",
                  game->current_room->id, 
                  0,  /* inventory starts empty */
                  log_timestamp());
    
    log_function_exit(__func__, 1);    

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
    
    add_log_entry("Player looking at room: %s at %s", 
                  game->current_room->id, 
                  log_timestamp());

    if (!game->current_room) {
        printf("ERROR: No current room!\n");
        log_function_error(__func__, "ERROR: No current room!");
        log_function_exit(__func__, 0);
        return;
    }

    Room* room = game->current_room;

    /* Print room name */
    printf("%s\n", room->name);

    /* Print room description */
    printf("%s\n", room->description);

    /* Print exits */
    if (room->exit_count > 0) {
        printf("\nExits:");
        for (int i = 0; i < room->exit_count; i++) {
            /* Parse "direction:room_id" format */
            char exit_copy[PARSER_EXIT_BUFFER_SIZE];
            strncpy(exit_copy, room->exits[i], sizeof(exit_copy) - 1);
            exit_copy[sizeof(exit_copy) - 1] = '\0';

            char* colon = strchr(exit_copy, ':');
            if (colon) {
                *colon = '\0'; /* Split at colon */
                char* direction = exit_copy;
                printf(" %s", direction);
            }
        }
        printf("\n");
    } else {
        printf("No obvious exits.\n");
    }

    /* Print items (if any) */
    if (room->item_count > 0) {
        printf("\nYou see:");
        for (int i = 0; i < room->item_count; i++) {
            /* Find the item by ID */
            Item *item = find_item_by_id(game->story->items,
                                         game->story->item_count,
                                         room->items[i]);
            if (item) {
                printf(" %s", item->name);
            } else {
                printf(" [unknown item: %s]", room->items[i]);
            }
        }
        printf("\n");
    }

    /* Print NPCs (if any) */
    if (room->npc_count > 0) {
        printf("\nPresent:");
        for (int i = 0; i < room->npc_count; i++) {
            NPC *npc = find_npc_by_id(game->story->npcs,
                                      game->story->npc_count,
                                      room->npcs[i]);
            if (npc) {
                printf(" %s", npc->name);
            } else {
                printf(" [unknown NPC: %s]", room->npcs[i]);
            }
        }
        printf("\n");
    }

    log_function_exit(__func__, 0);
}