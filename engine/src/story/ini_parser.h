/*
 * ini_parser.h - Functions for parsing story .ini files
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef STORY_INI_PARSER_H 
#define STORY_INI_PARSER_H

#include <stdbool.h>
#include "core/constants.h"
#include "core/utils.h"


/**
 * parse_ini_section() - Parses a line looking for a section header
 * @line: String read from .ini file
 * @section: Buffer to store section name
 * @section_size: Size of section buffer
 * 
 * Parses a line in "[SECTION]" or "[TYPE:id]" format.
 * Extracts the content between brackets.
 *
 * Return: 1 if section header found, 0 otherwise
 */

int parse_ini_section(const char *line, char *section, size_t section_size);


/**
  * parse_ini_keyvalue() - Parse a key=value line from a .ini file
  * @line: Input line to parse
  * @key: Buffer to store parsed key
  * @key_size: Size of key buffer
  * @value: Buffer to store value
  * @value_size: Size of value buffer
  * 
  * Parses a line in "key = value" format. Trims whitespace from
  * both key and value. Modifies buffers in place.
  *
  * Return: 1 if successfully parsed, 0 otherwise
  */
 
int parse_ini_keyvalue(const char *line, char *key, size_t key_size, char *value, size_t value_size);




#endif /* STORY_INI_PARSER_H */

