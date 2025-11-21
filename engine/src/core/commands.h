#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"
#include "parser.h"

/*
 * Command execution results
 */
typedef enum {
    RESULT_OK,           // Command executed successfully
    RESULT_QUIT,         // Player wants to quit
    RESULT_ERROR,        // Command failed
    RESULT_INVALID       // Invalid command
} CommandResult;

/*
 * Command execution functions
 */

// Execute a parsed command
CommandResult execute_command(GameState* game, Command* cmd);

// Individual command handlers
CommandResult cmd_go(GameState* game, Command* cmd);
CommandResult cmd_look(GameState* game, Command* cmd);
CommandResult cmd_examine(GameState* game, Command* cmd);
CommandResult cmd_take(GameState* game, Command* cmd);
CommandResult cmd_drop(GameState* game, Command* cmd);
CommandResult cmd_inventory(GameState* game, Command* cmd);
CommandResult cmd_use(GameState* game, Command* cmd);
CommandResult cmd_talk(GameState* game, Command* cmd);
CommandResult cmd_help(GameState* game, Command* cmd);
CommandResult cmd_quit(GameState* game, Command* cmd);

#endif // COMMANDS_H