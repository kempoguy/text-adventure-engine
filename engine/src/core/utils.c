/*
 * utils.c - String utility function implementations
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "utils.h"


/**
 * trim_whitespace() - Remove leading and trailing whitespace from string
 * @str: String to trim (modified in place)
 *
 * Modifies the string in place by advancing the start pointer past leading
 * whitespace and null-terminating after the last non-whitespace character.
 *
 * Return: Pointer to trimmed string (same as input)
 */

char* trim_whitespace(char* str) {
    char* end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) {
        return str;
    }
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    end[1] = '\0';
    
    return str;
}


/**
 * str_to_lower() - Convert string to lowercase
 * @str: String to convert (modified in place)
 *
 * Converts all uppercase ASCII characters to lowercase in place.
 * Non-ASCII characters are unchanged.
 *
 * Return: void
 */

void str_tolower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}


// Safe string copy
/**
 * safe_strcopy() - Copy string with buffer overflow protection 
 * @dest: Destination buffer
 * @src: Size of destination buffer in bytes
 *
 * Copies up to dest_size-1 characters from source to destination
 * and always null-terminates the destination buffer.
 *
 * Return: void
 */

void safe_strcpy(char* dest, const char* src, size_t dest_size) {
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}



/**
 * contains_ignore_case() - Case-insensitive substring search
 * @haystack: String to search in
 * @needle: Substring to search for
 *
 * Searches for needle in haystack, ignoring case.
 *
 * Return: 1 if found, 0 if not found
 */

 int contains_ignore_case(const char *haystack, const char *needle) {
    char hay_lower[STRING_MATCH_BUFFER_SIZE];
    char needle_lower[STRING_MATCH_BUFFER_SIZE];
    int i;

    /* Convert both to lowercase */
    for (i = 0; haystack[i] && i < STRING_MATCH_BUFFER_SIZE; i++) 
        hay_lower[i] = tolower(haystack[i]);
    hay_lower[i] = '\0';

    for (i = 0; needle[i] && i < STRING_MATCH_BUFFER_SIZE; i++)
        needle_lower[i] = tolower(needle[i]);
    needle_lower[i] = '\0';

    return strstr(hay_lower, needle_lower) != NULL;
 }
