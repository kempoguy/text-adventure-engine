#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/*
 * String utility functions
 */

// Trim whitespace from both ends
char* trim_whitespace(char* str);

// Convert string to lowercase
void str_tolower(char* str);

// Safe string copy
void safe_strcpy(char* dest, const char* src, size_t dest_size);

#endif // UTILS_H