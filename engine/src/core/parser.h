/*
 * parser.h - Command parsing and tokenisation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include "constants.h" 

#ifndef PARSER_H
#define PARSER_H


/**
 * enum CommandType - Types of commands the parser recognises
 * @CMD_UNKNOWN: Unrecognised command   
 * @CMD_GO: Movement command
 * @CMD_LOOK: Look at current room
 * @CMD_EXAMINE: Examine an object
 * @CMD_TAKE: Take an item
 * @CMD_DROP: Drop an item
 * @CMD_INVENTORY: Show inventory
 * @CMD_USE: Use an item
 * @CMD_TALK: Talk to an NPC
 * @CMD_HELP: Display help
 * @CMD_SAVE: Save game
 * @CMD_LOAD: Load game
 * @CMD_QUIT: Quit game
 *
 */

typedef enum {
    CMD_UNKNOWN,
    CMD_GO,
    CMD_LOOK,
    CMD_EXAMINE,
    CMD_TAKE,
    CMD_DROP,
    CMD_INVENTORY,
    CMD_USE,
    CMD_TALK,
    CMD_ATTACK,
    CMD_QUESTS,
    CMD_HELP,
    CMD_SAVE,
    CMD_LOAD,
    CMD_QUIT
} CommandType;

/**
 * struct Command - Parsed player command
 * @type: Type of command recognised
 * @verb: Original verb string for error messages
 * @noun: Direct object (item, direction, or NPC name)
 * @preposition: Preposiiton word (on, with, to, etc...)
 * @noun2: Indirect object for complex commands
 *
 * Represets a tokenised player input broken into grammatical components for command execution
 */

typedef struct {
    CommandType type;      
    char verb[PARSER_VERB_SIZE];         
    char noun[PARSER_NOUN_SIZE];         
    char preposition[PARSER_PREPOSITION_SIZE];  
    char noun2[PARSER_NOUN_SIZE];        
} Command;



/**
 * parse_command() - Parse player input into command structure
 * @input: Raw player input string
 *
 * Tokenizes the input string and identifies command type, verb, nouns, 
 * and prepositions.
 *
 * Return: Populated Command structure
 */

Command parse_command(const char* input);


/**
 * get_command_type() - Determine command type from verb string
 * @verb: Verb string  (lowercase)
 * @param2: Description of second parameter
 *
 * Maps verb strings and synonyms to CommandType enum values.
 *
 * Return: CommandType enum value, or CMD_UNKNOWN if not recognized
 */

CommandType get_command_type(const char* verb);

#endif /* PARSER_H */