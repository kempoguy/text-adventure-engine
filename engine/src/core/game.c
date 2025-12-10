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
#include "gameplay/quests.h"
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
 *
 * Checks if all required quests are completed. If so, sets the
 * game_won flag.
 *
 * Return: True if player has won, false otherwise
 */
bool check_victory_condition(GameState* game) {
	int required_count = 0;
	int required_completed = 0;

	/* Check existing flag first */
	if (game->game_won)
		return true;

	/* If no quests, check old flag */
	if (game->story->quest_count == 0)
		return game->game_won;

	/* Count required quests and their completion */
	for (int i = 0; i < game->story->quest_count; i++) {
		Quest *quest = &game->story->quests[i];
		
		if (quest->required) {
			required_count++;
			if (quest->completed)
				required_completed++;
		}
	}

	/* All required quests must be complete */
	if (required_count > 0 && required_completed == required_count) {
		game->game_won = true;
		add_log_entry("Victory condition met: all %d required quests complete at %s",
		             required_count, log_timestamp());
		return true;
	}

	return false;
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
    Room *room;
    bool has_light = false;
    int i;


    add_log_entry("Player looking at room: %s at %s", 
                  game->current_room->id, 
                  log_timestamp());

    if (!game->current_room) {
        printf("ERROR: No current room!\n");
        log_function_error(__func__, "ERROR: No current room!");
        log_function_exit(__func__, 0);
        return;
    }

    room = game->current_room;

    /* Check if player has a light source in inventory */
    if (room->dark) {
        for (i = 0; i < game->inventory_count; i++) {
            if (game->inventory[i]->illuminates) {
                has_light = true;
                break;
            }
        }
    }

    /* Print room name */
    printf("%s\n", room->name);

    /* Print room description */
    printf("%s\n", room->description);

    /* If dark and no light, hide details */
    if (room->dark && !has_light) {
        printf("\nIt's too dark to see anything!\n");
        add_log_entry("Room is dark, player has no light at %s", log_timestamp());
        log_function_exit(__func__,0);
        return;
    }


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
                
                /* Show if exit is locked */
                if (room->locked && strcmp(direction, room->locked_exit) == 0) {
                    printf(" %s (locked)", direction);
                } else {
                    printf(" %s", direction);
                }
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


/**
 * check_and_complete_quests() - Check if any quests completed
 * @game: Pointer to current game state
 * @item_id: Item just acquired (or NULL)
 * @npc_id: NPC just talked to (or NULL)
 * @room_id: Room just entered (or NULL)
 *
 * Checks all incomplete quests to see if completion conditions are met.
 * Displays completion message and updates quest status.
 *
 * Return: void
 */
void check_and_complete_quests(GameState* game, const char* item_id,
                               const char* npc_id, const char* room_id) {
	int i;
	Quest *quest;

	if (!game || game->story->quest_count == 0)
		return;

	for (i = 0; i < game->story->quest_count; i++) {
		quest = &game->story->quests[i];

		if (quest->completed)
			continue;

		if (check_quest_completion(quest, item_id, npc_id, room_id)) {
			quest->completed = true;

			printf("\n*** QUEST COMPLETED: %s ***\n", quest->name);
			
			if (strlen(quest->completion_message) > 0) {
				printf("%s\n", quest->completion_message);
			}
			
			printf("\n");

			add_log_entry("Quest completed: %s (item=%s, npc=%s, room=%s) at %s",
			             quest->id,
			             item_id ? item_id : "none",
			             npc_id ? npc_id : "none",
			             room_id ? room_id : "none",
			             log_timestamp());
            
            /* Check if this completed all requried quests */
            check_victory_condition(game);
		}
	}
}

