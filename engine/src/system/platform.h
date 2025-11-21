#ifndef PLATFORM_H
#define PLATFORM_H

/*
 * Platform detection
 */
#ifdef _WIN32
    #define PLATFORM_WINDOWS
    #include <windows.h>
    #include <conio.h>
#elif __linux__
    #define PLATFORM_LINUX
    #include <unistd.h>
    #include <termios.h>
#endif

/*
 * Platform abstraction functions
 */

// Initialize platform-specific code
void platform_init(void);

// Cleanup platform-specific code
void platform_cleanup(void);

// Sleep for milliseconds
void platform_sleep(int milliseconds);

// Clear screen
void platform_clear_screen(void);

// Get single keypress (non-blocking)
int platform_get_key(void);

#endif // PLATFORM_H