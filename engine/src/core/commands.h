/*
 * commands.h - Command execution and handlers
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"
#include "parser.h"


/**
 * enum CommandResult - Result codes for command execution
 * @RESULT_OK: Command executed successfully
 * @RESULT_QUIT: Player wants to quit the game
 * @RESULT_ERROR: Command failed to execute
 * @RESULT_INVALID: Invalid or unrecognized command
 */
 
typedef enum {
    RESULT_OK,           
    RESULT_QUIT,        
    RESULT_ERROR,        
    RESULT_INVALID      
} CommandResult;


/**
 * execute_command() - Execute a parsed command
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command structure
 *
 * Dispatches the command to the appropriate handler based on
 * command type.
 *
 * Return: CommandResult indicating success, error, or quit
 */

CommandResult execute_command(GameState* game, Command* cmd);


/**
 * cmd_go() - Handle movement commands
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Processes GO command and direction shortcuts to move the
 * player between rooms.
 *
 * Return: RESULT_OK on successful movement, RESULT_ERROR if direction invalid
 */

CommandResult cmd_go(GameState* game, Command* cmd);


/**
 * cmd_look() - Redisplay current room description
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_look(GameState* game, Command* cmd);


/**
 * cmd_examine() - Examine an object in detail
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_examine(GameState* game, Command* cmd);


/**
 * cmd_take() - Pick up an item
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_take(GameState* game, Command* cmd);


/**
 * cmd_drop() - Drop an item from inventory
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_drop(GameState* game, Command* cmd);


/**
 * cmd_inventory() - Display player inventory
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_inventory(GameState* game, Command* cmd);


/**
 * cmd_use() - Use an item
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_use(GameState* game, Command* cmd);


/**
 * cmd_talk() - Talk to an NPC
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_talk(GameState* game, Command* cmd);


/**
 * cmd_quests() - List quests
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_quests(GameState* game, Command* cmd); 


/**
 * cmd_help() - Display available commands
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_help(GameState* game, Command* cmd);


/**
 * cmd_quit() - Quit the game with confirmation
 * @game: Pointer to current game state
 * @cmd: Pointer to parsed command
 *
 * Return: Command execution result
 */

CommandResult cmd_quit(GameState* game, Command* cmd);


/**
 * cmd_save() - Saves a game in progress 
 * @game: State of current game
 * @cmd: Parsed command
 *
 * Save current into 1 of 3 save slots. 
 *
 * Return: RESULT_OK or RESULT_ERROR
 */

 CommandResult cmd_save(GameState* game, Command* cmd);

 
 /**
  * cmd_load() - Load game from slot
  * @game: State of game
  * @cmd: Parsed command
  *
  * Loads game from 1 of 3 slots, overwrites game in progress.
  *
  * Return: RESULT_OK or RESULT_ERROR
  */
 
CommandResult cmd_load(GameState* game, Command* cmd);


#endif /* COMMANDS_H */