#ifndef DISPLAY_H
#define DISPLAY_H

/*
 * Display system functions
 */

// Initialize display system
void display_init(void);

// Cleanup display system
void display_cleanup(void);

// Print formatted text (with word wrapping)
void display_text(const char* text);

// Print formatted text with newline
void display_line(const char* text);

#endif // DISPLAY_H