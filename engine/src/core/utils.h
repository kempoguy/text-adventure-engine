/*
 * utils.h - String utility functions
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */



#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>


/**
 * trim_whitespace() - Remove leading and trailing whitespace from string
 * @str: String to trim (modified in place)
 *
 * Modifies the string in place by moving the start pointer forward
 * and null-terminating after the last non-whitespace character.
 *
 * Return: Pointer to trimmed string (same as input)
 */

char* trim_whitespace(char* str);


/**
 * str_tolower() - Convert string to lowercase
 * @str: String to convert (modified in place)
 *
 * Converts all uppercase ASCII characters to lowercase in place.
 *
 * Return: void
 */

void str_tolower(char* str);


/**
 * safe_strcpy() - Copy string with buffer overflow protection
 * @dest: Destination buffer
 * @src: Source string to copy
 * @dest_size: Size of destination buffer
 *
 * Copies up to dest_size-1 characters and always null-terminates
 * the destination buffer.
 *
 * Return: void
 */

void safe_strcpy(char* dest, const char* src, size_t dest_size);


/**
 * contains_ignore_case() - Case-insensitive substring search
 * @haystack: String to search in
 * @needle: Substring to search for
 *
 * Searches for needle in haystack, ignoring case.
 *
 * Return: 1 if found, 0 if not found
 */

 int contains_ignore_case(const char *haystack, const char *needle);


#endif /* UTILS_H */