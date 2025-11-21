#include "platform.h"
#include <stdio.h>

/*
 * Initialize platform-specific code
 */
void platform_init(void) {
    printf("[STUB] platform_init()\n");
    
#ifdef PLATFORM_WINDOWS
    // On Windows, enable ANSI color codes
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

/*
 * Cleanup platform-specific code
 */
void platform_cleanup(void) {
    printf("[STUB] platform_cleanup()\n");
}

/*
 * Sleep for milliseconds
 */
void platform_sleep(int milliseconds) {
#ifdef PLATFORM_WINDOWS
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

/*
 * Clear screen
 */
void platform_clear_screen(void) {
#ifdef PLATFORM_WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

/*
 * Get single keypress (stub for now)
 */
int platform_get_key(void) {
#ifdef PLATFORM_WINDOWS
    if (_kbhit()) {
        return _getch();
    }
#endif
    return -1;  // No key pressed
}