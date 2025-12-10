/*
 * commands.c - Command execution and handler implementations
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "commands.h"
#include "constants.h"
#include "core/logger.h"
#include "core/utils.h"
#include "game.h"
#include "gameplay/quests.h"
#include "system/save.h"
#include "world/items.h"
#include "world/npcs.h"


/* Static function declarations */
static const char* find_exit(Room* room, const char* direction);


 /**
  * execute_command() - Executes parsed command
  * @game: Pointer to current game state
  * @cmd: Pointer to parsed command structure
  *
  * Dispatches the command to the appropriate handler based on command type. 
  * Handles both implemented and stub commands.
  *
  * Return: CommandResult indicating success, error or quit.
  */
 
CommandResult execute_command(GameState* game, Command* cmd) {
    switch (cmd->type) {
        case CMD_GO:
            return cmd_go(game, cmd);
        case CMD_LOOK:
            return cmd_look(game, cmd);
        case CMD_EXAMINE:
            return cmd_examine(game, cmd);
        case CMD_TAKE:
            return cmd_take(game, cmd);
        case CMD_DROP:
            return cmd_drop(game, cmd);
        case CMD_INVENTORY:
            return cmd_inventory(game, cmd);
        case CMD_USE:
            return cmd_use(game, cmd);
        case CMD_TALK:
            return cmd_talk(game, cmd);
        case CMD_QUESTS:
            return cmd_quests(game, cmd);
        case CMD_HELP:
            return cmd_help(game, cmd);
        case CMD_QUIT:
            return cmd_quit(game, cmd);
        case CMD_SAVE:
            return cmd_save(game, cmd);
        case CMD_LOAD:
            return cmd_load(game, cmd);
        default:
            printf("I don't understand '%s'.\n", cmd->verb);
            return RESULT_INVALID;
    }
}


 /**
  * find_exit() - Find exit destination from current room
  * @room: Pointer to current room
  * @direction: Direction string to search for
  *
  * Searches the room's exit list for a matching direction (case-insensitive)
  * and returns the destination room ID.
  *
  * Return: Room ID string if exit exists, NULL otherwise
  */
 
static const char* find_exit(Room* room, const char* direction) {
    if (!room || !direction) {
        return NULL;
    }

    // Search through exits for atching direction
    for (int i = 0; i < room->exit_count; i++) {
        // Parse "direction:room_id" format
        char exit_copy[PARSER_EXIT_BUFFER_SIZE];
        strncpy(exit_copy, room->exits[i], sizeof(exit_copy) - 1);
        exit_copy[sizeof(exit_copy) - 1] = '\0';

        char* colon = strchr(exit_copy, ':');
        if (colon) {
            *colon = '\0';
            char* exit_direction = exit_copy; // Split string at colon

            // Compare direction (case-insensitive)
            if (strcasecmp(exit_direction, direction) == 0) {
                // Found it! Return the room_id from the original string
                char* original_colon = strchr(room->exits[i], ':');
                return original_colon + 1; // Return room_id part
            }
        }
    }

    return NULL; // Exit not found
}


/**
 * cmd_go() - Handle movement commands
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Processes GO command and direction shortcuts to move the player between
 * rooms. Handles abbreviations (n/s/e/w), validates exits, and updates game 
 * state on successful movement.
 *
 * Return: RESULT_OK on successful movement, RESULT_ERROR if direction invalid
 */

CommandResult cmd_go(GameState* game, Command* cmd) {
    // Check if direction was provided
    if (strlen(cmd->noun) == 0) {
        printf("Go where? (Try: north, south, east, west)\n");
        return RESULT_ERROR;
    }

    const char* direction = cmd->noun;

    // Handle abbreviations
    if (strcmp(direction, "n") == 0) direction = "north";
    else if (strcmp(direction, "s") == 0) direction = "south";
    else if (strcmp(direction, "e") == 0) direction = "east";
    else if (strcmp(direction, "w") == 0) direction = "west";

    // Find the exit
    const char* destination_id = find_exit(game->current_room, direction);

    if (!destination_id) {
        printf("You can't go %s from here.\n", direction);
        return RESULT_ERROR;
    }

    /* Check if exit is locked */
    if (game->current_room->locked && strcmp(direction, game->current_room->locked_exit) == 0) {
        printf("The %s exit is locked. You need to unlock it first.\n", direction);
        add_log_entry("Player tried locked exit: %s at %s", direction, log_timestamp());
        return RESULT_ERROR;
    }

    // Find the destination room
    Room* destination = find_room_by_id(game->story, destination_id);

    if (!destination) {
        printf("ERROR: Exit leads to non-existent room '%s'!\n", destination_id);
        return RESULT_ERROR;
    }

    // Move to the new room
    game->current_room = destination;
    game->turn_count++;

    // Check for quest completion (entering room)
    check_and_complete_quests(game, NULL, NULL, destination->id);

    // Describe the new room;
    look_at_current_room(game);

    return RESULT_OK;
}


/**
 * cmd_look() - Redisplay current room description
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_look(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    look_at_current_room(game);
    return RESULT_OK;
}


/**
 * cmd_examine() - Examine an item in detail
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */
CommandResult cmd_examine(GameState* game, Command* cmd) {
    Item *item;
    Room *room;
    int i;

    log_function_entry(__func__, "noun=%s, room=%s", cmd->noun, game->current_room->id);

    if (strlen(cmd->noun) == 0) {
        printf("Examine what?\n");
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    room = game->current_room;

    /* First check inventory */
    for (i = 0; i < game->inventory_count; i++) {
        item = game->inventory[i];

        if (strcasecmp(item->name, cmd->noun) == 0 ||
            strcasecmp(item->id, cmd->noun) == 0 ||
            contains_ignore_case(item->name, cmd->noun)) {
                printf("\n%s\n", item->description);
                printf("Weight: %d kg\n", item->weight);
                if (item->useable) {
                    printf("You can use this item.\n");
                }

                add_log_entry("Player examined inveotory item: %s at %s", 
                                item->name, log_timestamp());
                log_function_exit(__func__, RESULT_OK);
                return RESULT_OK;
                
            }
    }

    /* Then check room */
    for (i = 0; i < room->item_count; i++) {
        item = find_item_by_id(game->story->items,
                               game->story->item_count,
                               room->items[i]);
        
        if (!item)
            continue;

        if (strcasecmp(item->name, cmd->noun) == 0 ||
            strcasecmp(item->id, cmd->noun) == 0 ||
            contains_ignore_case(item->name, cmd->noun)) {
                printf("\n%s\n", item->description);
                printf("Weight: %d kg\n", item->weight);
                if (item->takeable) {
                    printf("You could take this.\n");
                } else {
                    printf("You can't take this.\n");
                }
                add_log_entry(__func__,"Player examined room item: %s at %s",
                              item->name, log_timestamp());
                log_function_exit(__func__, RESULT_OK);
                return RESULT_OK;
            }
    }

    printf("You dont see any %s here.\n", cmd->noun);
    add_log_entry("Player tried to examine non-existent item %s at %s", cmd->noun, log_timestamp());
    log_function_exit(__func__, RESULT_ERROR);
    return RESULT_ERROR;
}


/**
 * cmd_take() - Pick up an item
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_take(GameState* game, Command* cmd) {
    Item *item;
    Room *room;
    int i;

    log_function_entry(__func__, "noun=%s, room=%s", 
                      cmd->noun, game->current_room->id);

    if (strlen(cmd->noun) == 0) {
        printf("Take what?\n");
        return RESULT_ERROR;
    }

    room = game->current_room;

    /* Search for item in current room by name or ID */
    for (i = 0; i < room->item_count; i++) {
        item = find_item_by_id(game->story->items,
                               game->story->item_count,
                               room->items[i]);
        
        if (!item)
            continue;

        /* Match by name (case-insensitive) or ID */
        if (strcasecmp(item->name, cmd->noun) == 0 ||
            strcasecmp(item->id, cmd->noun) == 0) {
            
            /* Check if item is takeable */
            if (!item->takeable) {
                printf("You can't take the %s.\n", item->name);
                add_log_entry("Player attempted to take non-takeable item: %s at %s", item->name, log_timestamp());
                log_function_exit(__func__, RESULT_ERROR);
                return RESULT_ERROR;
            }

            /* Check inventory weight limit */
            if (game->inventory_weight + item->weight > 
                game->story->metadata.max_inventory_weight) {
                printf("The %s is too heavy. You're carrying too much.\n", 
                       item->name);
                add_log_entry("Player inventory full: tried %s at %s",
                item->name, log_timestamp());
                log_function_exit(__func__, RESULT_ERROR);
                return RESULT_ERROR;
            }

            /* Add to inventory */
            game->inventory = realloc(game->inventory, 
                                     (game->inventory_count + 1) * sizeof(Item*));
            game->inventory[game->inventory_count] = item;
            game->inventory_count++;
            game->inventory_weight += item->weight;

            /* Remove from room */
            for (int j = i; j < room->item_count - 1; j++) {
                room->items[j] = room->items[j + 1];
            }
            room->item_count--;

            printf("You take the %s.\n", item->name);

            /* Check for quest completion (taking item) */
            check_and_complete_quests(game, item->id, NULL, NULL);

            add_log_entry("Player took item: %s (weight=%d, total_weight=%d) at %s", item->name, item->weight, game->inventory_weight,      log_timestamp());
            log_function_exit(__func__, RESULT_OK);
            return RESULT_OK;
        }
    }

    printf("You don't see any '%s' here.\n", cmd->noun);
    add_log_entry("Player tried to take non-existent item: %s at %s",
                 cmd->noun, log_timestamp());
    log_function_exit(__func__, RESULT_ERROR);
    return RESULT_ERROR;
}


/**
 * cmd_drop() - Dropan item from inventory
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_drop(GameState* game, Command* cmd) {
    Item *item;
    Room *room;
    int i;

    log_function_entry(__func__, "noun=%s, room=%s", 
                      cmd->noun, game->current_room->id);

    if (strlen(cmd->noun) == 0) {
        printf("Drop what?\n");
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    /* Search inventory for item */
    for (i = 0; i < game->inventory_count; i++) {
        item = game->inventory[i];

        /* Match by name or ID */
        if (strcasecmp(item->name, cmd->noun) == 0 ||
            strcasecmp(item->id, cmd->noun) == 0) {

            room = game->current_room;

            /* Add item ID to room */
            /* Note: room->items is char** (array of item IDs) */
            room->items = realloc(room->items, 
                                 (room->item_count + 1) * sizeof(char*));
            room->items[room->item_count] = item->id;
            room->item_count++;

            /* Remove from inventory */
            game->inventory_weight -= item->weight;
            for (int j = i; j < game->inventory_count - 1; j++) {
                game->inventory[j] = game->inventory[j + 1];
            }
            game->inventory_count--;

            printf("You drop the %s.\n", item->name);
            add_log_entry("Player dropped item: %s (weight=%d, total_weight=%d) at %s",
                         item->name, item->weight, game->inventory_weight,
                         log_timestamp());
            log_function_exit(__func__, RESULT_OK);
            return RESULT_OK;
        }
    }

    printf("You're not carrying any '%s'.\n", cmd->noun);
    add_log_entry("Player tried to drop item not in inventory: %s at %s",
                 cmd->noun, log_timestamp());
    log_function_exit(__func__, RESULT_ERROR);
    return RESULT_ERROR;
}


/**
 * cmd_inventory() - Display player inventory
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_inventory(GameState* game, Command* cmd) {
    (void)cmd;

    log_function_entry(__func__, "count=%d, weight=%d/%d",
                      game->inventory_count,
                      game->inventory_weight,
                      game->story->metadata.max_inventory_weight);

    printf("\n=== INVENTORY ===\n");

    if (game->inventory_count == 0) {
        printf("You are not carrying anything.\n");
    } else {
        printf("You are carrying:\n");
        for (int i = 0; i < game->inventory_count; i++) {
            Item *item = game->inventory[i];
            printf("  - %s (%d kg)\n", item->name, item->weight);
        }
        printf("\nTotal weight: %d / %d kg\n", 
               game->inventory_weight,
               game->story->metadata.max_inventory_weight);
    }

    log_function_exit(__func__, RESULT_OK);
    return RESULT_OK;
}


/**
 * cmd_use() - Use an item with real effects
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Applies item effects:
 * - Illuminating items: Reveals dark room contents
 * - Unlocking items: Opens locked exits
 *
 * Return: RESULT_OK on success, RESULT_ERROR on failure
 */
CommandResult cmd_use(GameState* game, Command* cmd) {
	Item *item;
	int i;

	log_function_entry(__func__, "noun=%s, room=%s", cmd->noun,
	                  game->current_room->id);

	if (strlen(cmd->noun) == 0) {
		printf("Use what?\n");
		log_function_exit(__func__, RESULT_ERROR);
		return RESULT_ERROR;
	}

	/* Search inventory for item */
	for (i = 0; i < game->inventory_count; i++) {
		item = game->inventory[i];

		/* Match by name, ID, or substring */
		if (strcasecmp(item->name, cmd->noun) == 0 ||
		    strcasecmp(item->id, cmd->noun) == 0 ||
		    contains_ignore_case(item->name, cmd->noun)) {

			if (!item->useable) {
				printf("You can't use the %s.\n", item->name);
				add_log_entry("Player tried to use non-useable item: %s at %s",
				             item->name, log_timestamp());
				log_function_exit(__func__, RESULT_ERROR);
				return RESULT_ERROR;
			}

			/* ILLUMINATION EFFECT */
			if (item->illuminates) {
				if (game->current_room->dark) {
					printf("The %s illuminates the area!\n", item->name);
					printf("\n");
					look_at_current_room(game);
					add_log_entry("Player used illumination in dark room at %s",
					             log_timestamp());
				} else {
					printf("The %s provides light, but you can already see clearly.\n",
					       item->name);
					add_log_entry("Player used illumination in lit room at %s",
					             log_timestamp());
				}
				log_function_exit(__func__, RESULT_OK);
				return RESULT_OK;
			}

			/* UNLOCKING EFFECT */
			if (item->unlocks) {
				if (game->current_room->locked) {
					printf("You use the %s to unlock the %s exit!\n",
					       item->name, game->current_room->locked_exit);
					
					/* Unlock the exit */
					game->current_room->locked = false;
					game->current_room->locked_exit[0] = '\0';
					
					add_log_entry("Player unlocked exit: %s at %s",
					             game->current_room->locked_exit,
					             log_timestamp());
					log_function_exit(__func__, RESULT_OK);
					return RESULT_OK;
				} else {
					printf("There's nothing to unlock here.\n");
					add_log_entry("Player tried to unlock in unlocked room at %s",
					             log_timestamp());
					log_function_exit(__func__, RESULT_OK);
					return RESULT_OK;
				}
			}

			/* Generic useable item (no special effect) */
			printf("You use the %s. Nothing special happens.\n", item->name);
			add_log_entry("Player used generic item: %s at %s",
			             item->name, log_timestamp());
			log_function_exit(__func__, RESULT_OK);
			return RESULT_OK;
		}
	}

	printf("You're not carrying any '%s'.\n", cmd->noun);
	add_log_entry("Player tried to use item not in inventory: %s at %s",
	             cmd->noun, log_timestamp());

	log_function_exit(__func__, RESULT_ERROR);
	return RESULT_ERROR;
}


/**
 * cmd_talk() - Talk to an NPC
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Finds NPC in current room by name or ID (with fuzzy matching) and displays
 * their dialog. Dialog cycles through multiple lines on repeated conversations.
 *
 * Return: RESULT_OK if NPC found and talked to, RESULT_ERROR otherwise
 */

CommandResult cmd_talk(GameState* game, Command* cmd) {
    Room *room;
    NPC *npc;
    int i;

    log_function_entry(__func__, "noun=%s, room=%s",
                      cmd->noun, game->current_room->id);

    if (strlen(cmd->noun) == 0) {
        printf("Talk to whom?\n");
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    room = game->current_room;

    /* Search for NPC in current room */
    for (i = 0; i < room->npc_count; i++) {
        npc = find_npc_by_id(game->story->npcs,
                            game->story->npc_count,
                            room->npcs[i]);
        
        if (!npc)
            continue;

        /* Match by name or ID (with fuzzy matching) */
        if (strcasecmp(npc->name, cmd->noun) == 0 ||
            strcasecmp(npc->id, cmd->noun) == 0 ||
            contains_ignore_case(npc->name, cmd->noun)) {

            /* Check if NPC has dialog */
            if (npc->dialog_count == 0) {
                printf("%s has nothing to say.\n", npc->name);
                log_function_exit(__func__, RESULT_OK);
                return RESULT_OK;
            }

            /* Display current dialog line */
            printf("\n%s says:\n\"%s\"\n", 
                   npc->name, 
                   npc->dialog[npc->dialog_index]);

            /* Advance to next dialog line (cycle) */
            npc->dialog_index = (npc->dialog_index + 1) % npc->dialog_count;

            add_log_entry("Player talked to NPC: %s (line %d/%d) at %s",
                         npc->name, npc->dialog_index, 
                         npc->dialog_count, log_timestamp());

            /* Check for quest completion (talking to NPC) */
            check_and_complete_quests(game, NULL, npc->id, NULL);

            log_function_exit(__func__, RESULT_OK);
            return RESULT_OK;
        }
    }

    printf("There's no '%s' here to talk to.\n", cmd->noun);
    add_log_entry("Player tried to talk to non-existent NPC: %s at %s",
                 cmd->noun, log_timestamp());
    log_function_exit(__func__, RESULT_ERROR);
    return RESULT_ERROR;
}


/**
 * cmd_quests() - Display quest status
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Shows all quests with their completion status. Required quests
 * are marked with an asterisk.
 *
 * Return: RESULT_OK
 */
CommandResult cmd_quests(GameState* game, Command* cmd) {
	int completed_count = 0;
	int required_count = 0;
	int required_completed = 0;

	(void)cmd;

	log_function_entry(__func__, "quest_count=%d", 
	                  game->story->quest_count);

	printf("\n=== QUESTS ===\n");

	if (game->story->quest_count == 0) {
		printf("No quests available.\n");
		log_function_exit(__func__, RESULT_OK);
		return RESULT_OK;
	}

	/* Count quest statistics */
	for (int i = 0; i < game->story->quest_count; i++) {
		Quest *quest = &game->story->quests[i];
		
		if (quest->completed)
			completed_count++;
		
		if (quest->required) {
			required_count++;
			if (quest->completed)
				required_completed++;
		}
	}

	printf("\n");

	/* Display each quest */
	for (int i = 0; i < game->story->quest_count; i++) {
		Quest *quest = &game->story->quests[i];
		
		printf("%s %s\n", 
		       quest->completed ? "[X]" : "[ ]",
		       quest->name);
		
		printf("    %s\n", quest->description);
		
		if (quest->required) {
			printf("    (Required)\n");
		}
		
		printf("\n");
	}

	/* Show summary */
	printf("Progress: %d/%d quests completed\n", 
	       completed_count, game->story->quest_count);
	
	if (required_count > 0) {
		printf("Required: %d/%d completed\n", 
		       required_completed, required_count);
	}

	add_log_entry("Player viewed quests: %d/%d complete at %s",
	             completed_count, game->story->quest_count,
	             log_timestamp());

	log_function_exit(__func__, RESULT_OK);
	return RESULT_OK;
}


/**
 * cmd_help() - Display available commands
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_help(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    printf("\n=== AVAILABLE COMMANDS ===\n\n");
    printf("Movement:\n");
    printf("  go <direction>, north, south, east, west, n, s, e, w\n\n");
    printf("Interaction:\n");
    printf("  look (or l), examine (or x) <object>, take <item>, drop <item>\n");
    printf("  use <item>, talk <npc>, inventory (or i), quests\n\n");
    printf("System:\n");
    printf("  help, save, load, quit\n\n");
    return RESULT_OK;
}


/**
 * cmd_quit() - Quit the game with confirmation
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Quits the game after confirming with player. Does not trigger save.
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_quit(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    printf("\nAre you sure you want to quit? (y/n): ");
    char response[PARSER_RESPONSE_BUFFER_SIZE];
    if (fgets(response, sizeof(response), stdin)) {
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("Thanks for playing!\n");
            return RESULT_QUIT;
        }
    }
    printf("Continuing game...\n");
    return RESULT_OK;
}


/**
 * cmd_save() - Saves a game in progress 
 * @game: State of current game
 * @cmd: Parsed command
 *
 * Save current into 1 of 3 save slots. 
 *
 * Return: RESULT_OK or RESULT_ERROR
 */

CommandResult cmd_save(GameState* game, Command* cmd) {
    int slot = 1;  /* Default slot */
    int result;

    log_function_entry(__func__, "noun=%s, room=%s",
                      cmd->noun, game->current_room->id);

    /* Parse slot number if provided */
    if (strlen(cmd->noun) > 0) {
        slot = atoi(cmd->noun);
        if (slot < 1 || slot > 3) {
            printf("Save slot must be between 1, and %d.\n", SAVE_MAX_SLOTS);
            log_function_exit(__func__, RESULT_ERROR);
            return RESULT_ERROR;
        }
    }

    printf("Saving game to slot %d...\n", slot);
    
    result = save_game(game, slot);
    if (result < 0) {
        printf("Error: Failed to save game.\n");
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    printf("Game saved successfully!\n");
    log_function_exit(__func__, RESULT_OK);
    return RESULT_OK;
}


 /**
  * cmd_load() - Load game from slot
  * @game: State of game
  * @cmd: Parsed command
  *
  * Loads game from 1 of 3 slots, overwrites game in progress.
  *
  * Return: RESULT_OK or RESULT_ERROR
  */
 
CommandResult cmd_load(GameState* game, Command* cmd) {
    int slot = 1;  /* Default slot */
    int result;

    log_function_entry(__func__, "noun=%s", cmd->noun);

    /* Parse slot number if provided */
    if (strlen(cmd->noun) > 0) {
        slot = atoi(cmd->noun);
        if (slot < 1 || slot > 3) {
            printf("Load slot must be between 1 and %d.\n", SAVE_MAX_SLOTS);
            log_function_exit(__func__, RESULT_ERROR);
            return RESULT_ERROR;
        }
    }

    /* Check if save exists */
    if (!save_exists(slot)) {
        printf("No saved game in slot %d.\n", slot);
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    printf("Loading game from slot %d...\n", slot);
    
    result = load_game(game, slot);
    if (result < 0) {
        printf("Error: Failed to load game.\n");
        log_function_exit(__func__, RESULT_ERROR);
        return RESULT_ERROR;
    }

    printf("Game loaded successfully!\n");
    
    /* Show current room after loading */
    look_at_current_room(game);
    
    log_function_exit(__func__, RESULT_OK);
    return RESULT_OK;
}