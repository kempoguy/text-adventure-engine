#include "commands.h"
#include <stdio.h>
#include <string.h>

/*
 * Execute a parsed command
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

/*
 * Individual command handlers (STUBS)
 */

CommandResult cmd_go(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    printf("[STUB] You try to go %s.\n", 
           strlen(cmd->noun) > 0 ? cmd->noun : "somewhere");
    return RESULT_OK;
}

CommandResult cmd_look(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    look_at_current_room(game);
    return RESULT_OK;
}

CommandResult cmd_examine(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    printf("[STUB] You examine the %s.\n", 
           strlen(cmd->noun) > 0 ? cmd->noun : "area");
    return RESULT_OK;
}

CommandResult cmd_take(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Take what?\n");
        return RESULT_ERROR;
    }
    printf("[STUB] You take the %s.\n", cmd->noun);
    return RESULT_OK;
}

CommandResult cmd_drop(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Drop what?\n");
        return RESULT_ERROR;
    }
    printf("[STUB] You drop the %s.\n", cmd->noun);
    return RESULT_OK;
}

CommandResult cmd_inventory(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    printf("[STUB] Inventory:\n");
    printf("  - Nothing (inventory system not implemented yet)\n");
    return RESULT_OK;
}

CommandResult cmd_use(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Use what?\n");
        return RESULT_ERROR;
    }
    printf("[STUB] You try to use the %s.\n", cmd->noun);
    return RESULT_OK;
}

CommandResult cmd_talk(GameState* game, Command* cmd) {
    (void)game; // TODO
    (void)cmd; // TODO
    if (strlen(cmd->noun) == 0) {
        printf("Talk to whom?\n");
        return RESULT_ERROR;
    }
    printf("[STUB] You try to talk to %s.\n", cmd->noun);
    return RESULT_OK;
}

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