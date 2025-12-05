/*
 * parser.c - Command parsing and tokenisation implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "constants.h"
#include "parser.h"


 /**
 * parse_command() - Parse player input into command structure
 * @input: Raw player input string
 *
 * Tokenizes the input string into verb, noun, preposition, and noun2
 * components. Converts to lowercase and identifies command type.
 * Handles direction shortcuts as special case.
 *
 * Return: Populated Command structure with parsed components
  */
 
Command parse_command(const char* input) {
    Command cmd;
    memset(&cmd, 0, sizeof(Command));
    
    // Make a copy we can modify
    char buffer[PARSER_INPUT_BUFFER_SIZE];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Convert to lowercase
    for (int i = 0; buffer[i]; i++) {
        buffer[i] = tolower(buffer[i]);
    }
    
    // Tokenize the input
    char* token = strtok(buffer, " ");
    
    if (token == NULL) {
        cmd.type = CMD_UNKNOWN;
        return cmd;
    }

    // First token is the verb
    strncpy(cmd.verb, token, sizeof(cmd.verb) - 1);
    cmd.type = get_command_type(token);

    // SPECIAL CASE: If the verb itself is a direction, it's actually GO + direction
    if (cmd.type == CMD_GO && 
        (strcmp(token, "north") == 0 || strcmp(token, "south") == 0 ||
         strcmp(token, "east")  == 0 || strcmp(token, "west")  == 0 ||
         strcmp(token, "n") == 0     || strcmp(token, "s") == 0     ||
         strcmp(token, "e") == 0     || strcmp(token, "w") == 0)) {
            // The direction IS the verb, put it in the noun
            strncpy(cmd.noun, token, sizeof(cmd.noun) -1);
    } else {
        // Second token is the noun (if present)
        token = strtok(NULL, " ");
        if (token) {
            strncpy(cmd.noun, token, sizeof(cmd.noun) - 1);
        }
    }

    // Third token might be preposition
    token = strtok(NULL, " ");
    if (token) {
        strncpy(cmd.preposition, token, sizeof(cmd.preposition) - 1);
    }
    
    // Fourth token is noun2 (if present)
    token = strtok(NULL, " ");
    if (token) {
        strncpy(cmd.noun2, token, sizeof(cmd.noun2) - 1);
    }
    
    return cmd;
}


/**
 * get_command_type() - Determine command type from verb string
 * @verb: Verb string (lowercase)
 *
 * Maps verb strings and their synonyms to CommandType enum values
 * using string comparison.
 *
 * Return: CommandType enum value, or CMD_UNKNOWN if verb not recognized
 */

CommandType get_command_type(const char* verb) {
    // GO commands
    if (strcmp(verb, "go") == 0 || strcmp(verb, "move") == 0 ||
        strcmp(verb, "walk") == 0 || strcmp(verb, "n") == 0 ||
        strcmp(verb, "s") == 0 || strcmp(verb, "e") == 0 ||
        strcmp(verb, "w") == 0 || strcmp(verb, "north") == 0 ||
        strcmp(verb, "south") == 0 || strcmp(verb, "east") == 0 ||
        strcmp(verb, "west") == 0) {
        return CMD_GO;
    }
    
    // LOOK commands
    if (strcmp(verb, "look") == 0 || strcmp(verb, "l") == 0) {
        return CMD_LOOK;
    }
    
    // EXAMINE commands
    if (strcmp(verb, "examine") == 0 || strcmp(verb, "x") == 0 ||
        strcmp(verb, "inspect") == 0) {
        return CMD_EXAMINE;
    }
    
    // TAKE commands
    if (strcmp(verb, "take") == 0 || strcmp(verb, "get") == 0 ||
        strcmp(verb, "grab") == 0 || strcmp(verb, "pick") == 0) {
        return CMD_TAKE;
    }
    
    // DROP commands
    if (strcmp(verb, "drop") == 0 || strcmp(verb, "put") == 0) {
        return CMD_DROP;
    }
    
    // INVENTORY commands
    if (strcmp(verb, "inventory") == 0 || strcmp(verb, "i") == 0 ||
        strcmp(verb, "inv") == 0) {
        return CMD_INVENTORY;
    }
    
    // USE commands
    if (strcmp(verb, "use") == 0) {
        return CMD_USE;
    }
    
    // TALK commands
    if (strcmp(verb, "talk") == 0 || strcmp(verb, "speak") == 0) {
        return CMD_TALK;
    }
    
    // HELP commands
    if (strcmp(verb, "help") == 0 || strcmp(verb, "?") == 0) {
        return CMD_HELP;
    }
    
    // SAVE commands
    if (strcmp(verb, "save") == 0) {
        return CMD_SAVE;
    }
    
    // LOAD commands
    if (strcmp(verb, "load") == 0) {
        return CMD_LOAD;
    }
    
    // QUIT commands
    if (strcmp(verb, "quit") == 0 || strcmp(verb, "exit") == 0 ||
        strcmp(verb, "q") == 0) {
        return CMD_QUIT;
    }
    
    return CMD_UNKNOWN;
}