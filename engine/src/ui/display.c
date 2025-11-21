#include "display.h"
#include <stdio.h>

/*
 * Initialize display system
 */
void display_init(void) {
    printf("[STUB] display_init()\n");
}

/*
 * Cleanup display system
 */
void display_cleanup(void) {
    printf("[STUB] display_cleanup()\n");
}

/*
 * Print formatted text
 */
void display_text(const char* text) {
    printf("%s", text);
}

/*
 * Print formatted text with newline
 */
void display_line(const char* text) {
    printf("%s\n", text);
}