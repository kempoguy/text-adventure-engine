#include "colors.h"
#include <stdio.h>
#include <stdbool.h>

static bool colors_enabled = true;

/*
 * Initialize color system
 */
void color_init(void) {
    printf("[STUB] color_init()\n");
    // On Windows, we might need to enable ANSI codes
    // For now, just assume it works
    colors_enabled = true;
}

/*
 * Cleanup color system
 */
void color_cleanup(void) {
    printf("[STUB] color_cleanup()\n");
}

/*
 * Check if colors are enabled
 */
int color_enabled(void) {
    return colors_enabled;
}

/*
 * Print colored text
 */
void print_colored(const char* text, const char* color) {
    if (colors_enabled) {
        printf("%s%s%s", color, text, COLOR_RESET);
    } else {
        printf("%s", text);
    }
}