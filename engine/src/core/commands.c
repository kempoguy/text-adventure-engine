/*
 * commands.c - Command execution and handler implementations
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "commands.h"
#include "game.h"

/* Static function declarations */
static int function_name(void);

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
        case CMD_HELP:
            return cmd_help(game, cmd);
        case CMD_QUIT:
            return cmd_quit(game, cmd);
        case CMD_SAVE:
            printf("Save not yet implemented.\n");
            return RESULT_OK;
        case CMD_LOAD:
            printf("Load not yet implemented.\n");
            return RESULT_OK;
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
        char exit_copy[128];
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

    // Find the destination room
    Room* destination = find_room_by_id(game->story, destination_id);

    if (!destination) {
        printf("ERROR: Exit leads to non-existent room '%s'!\n", destination_id);
        return RESULT_ERROR;
    }

    // Move to the new room
    game->current_room = destination;
    game->turn_count++;

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
    (void)game; // TODO
    (void)cmd; // TODO
    return RESULT_OK;
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
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Take what?\n");
        return RESULT_ERROR;
    }
    return RESULT_OK;
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
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Drop what?\n");
        return RESULT_ERROR;
    }

    return RESULT_OK;
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
    (void)game; // TODO
    (void)cmd; // TODO

    return RESULT_OK;
}


/**
 * cmd_use() - Use an item
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_use(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Use what?\n");
        return RESULT_ERROR;
    }

    return RESULT_OK;
}


/**
 * cmd_talk() - Talk to an NPC
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * STUB
 *
 * Return: CommandResult execution result
 */

CommandResult cmd_talk(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Talk to whom?\n");
        return RESULT_ERROR;
    }

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
    printf("  look, examine <object>, take <item>, drop <item>\n");
    printf("  use <item>, talk <npc>, inventory (or i)\n\n");
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
    char response[10];
    if (fgets(response, sizeof(response), stdin)) {
        if (response[0] == 'y' || response[0] == 'Y') {
            printf("Thanks for playing!\n");
            return RESULT_QUIT;
        }
    }
    printf("Continuing game...\n");
    return RESULT_OK;
}