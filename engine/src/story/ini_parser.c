/*
 * ini_parser.c - .ini file parser implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

 #include <ctype.h>
 #include <stdio.h>
 #include <string.h>

 #include "ini_parser.h"
 #include "core/constants.h"
 #include "core/utils.h"


 /**
  * parse_ini_section() - Check for section header in a .ini file
  * @line: Pointer to string containing line to be checked
  * @section: Buffer to store section name
  * @section_size: Size of section buffer
  *
  * Examines string for '[SECTION]' format. Extracts content between brackets 
  * and trims to remove whitespace.
  *
  * Return: 1 if section header found, 0 otherwise
  */
 
int parse_ini_section(const char *line, char *section, size_t section_size) {
    
    const char *start;
    const char *end;
    char temp[INI_SECTION_SIZE];
    char *trimmed;
    size_t len;

    if (!line || !section || section_size == 0)
        return 0;

    /* Find opening bracket */
    start = strchr(line, '[');
    if (!start)
        return 0;
    
    start++; /* Move past '[' */

    /* Find closing bracket */
    end = strchr(start, ']');
    if (!end)
        return 0;
    
    /* Calculate length and check buffer size */
    len = end - start;
    if (len >= sizeof(temp))
        len = sizeof(temp) - 1;
    
    /* Copy section name */
    strncpy(temp, start ,len);
    temp[len] = '\0';

    /* Trim whitespace */
    trimmed = trim_whitespace(temp);

    /* Copy trimmed result to output */
    strncpy(section, trimmed, section_size - 1);
    section[section_size - 1] = '\0';

    return 1;
}


/**
  * parse_ini_keyvalue() - Parse a key=value line from a .ini file
  * @line: Pointer to input string to be parsed
  * @key: Pointer to key 
  * @value: Pointer to value
  *
  * Modifes key and value pointers to point to the parsed strings
  *
  * Return: 1 if successful, 0 otherwise
  */
 
int parse_ini_keyvalue(const char* line, char *key, size_t key_size, 
                       char *value, size_t value_size) 
{
    char buffer[INI_LINE_BUFFER_SIZE];
    char *equals;
    char *key_part;
    char *value_part;
    char *trimmed;

    if (!line || !key || !value || key_size == 0 || value_size == 0)
        return 0;

    /* Copy to working buffer */
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    /* Trim leading/trailing whitespace */
    trimmed = trim_whitespace(buffer);

    /* Skip empty lines and comments */
    if (trimmed[0] == '\0' || trimmed[0] == '#' || trimmed[0] == ';')
        return 0;
    
    /* Find equals sign */
    equals = strchr(trimmed, '=');
    if (!equals)
        return 0;
    
    /* Split at equals */
    *equals = '\0';
    key_part = trimmed;
    value_part = equals + 1;

    /* Trim both parts */
    key_part = trim_whitespace(key_part);
    value_part = trim_whitespace(value_part);

    /* Copy to output buffers */
    strncpy(key, key_part, key_size - 1);
    key[key_size -1] = '\0';

    strncpy(value, value_part, value_size - 1);
    value[value_size - 1] = '\0';

    return 1;
}



