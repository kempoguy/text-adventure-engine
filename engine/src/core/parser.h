#ifndef PARSER_H
#define PARSER_H

/*
 * Command structure
 * Represents a parsed player command
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
    CMD_HELP,
    CMD_SAVE,
    CMD_LOAD,
    CMD_QUIT
} CommandType;

typedef struct {
    CommandType type;      // Type of command
    char verb[32];         // Original verb (for error messages)
    char noun[64];         // Direct object (item, direction, NPC)
    char preposition[16];  // Preposition (on, with, to, etc.)
    char noun2[64];        // Indirect object
} Command;

/*
 * Parser functions
 */

// Parse player input into a Command structure
Command parse_command(const char* input);

// Get command type from verb string
CommandType get_command_type(const char* verb);

#endif // PARSER_H