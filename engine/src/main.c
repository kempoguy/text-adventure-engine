/*
 * Text Adventure Engine - Main Entry Point
 * 
 * This is the top-level game loop. It handles:
 * - Engine initialization
 * - Story selection
 * - Main game loop
 * - Cleanup
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "main.h"
#include "core/game.h"
#include "core/parser.h"
#include "core/commands.h"
#include "ui/display.h"
#include "ui/colors.h"
#include "ui/menu.h"
#include "story/manager.h"
#include "story/loader.h"
#include "story/validator.h"
#include "system/platform.h"

/*
 * Main entry point
 */
int main(int argc, char** argv) {
    (void)argc; // TODO
    (void)argv; // TODO
    printf("Text Adventure Engine v1.0\n");
    printf("Initializing...\n\n");
    
    // Initialize platform-specific code (console setup, etc.)
    platform_init();
    
    // Initialize display system
    display_init();
    
    // Initialize color system
    color_init();
    
    // Initialize story manager
    story_manager_init("stories/");
    
    // Main menu loop
    bool running = true;
    while (running) {
        // Show main menu and get player choice
        MenuChoice choice = show_main_menu();
        
        switch (choice) {
            case MENU_NEW_GAME:
                // Start a new game
                start_new_game();
                break;
                
            case MENU_LOAD_GAME:
                // Load saved game
                load_saved_game();
                break;
                
            case MENU_QUIT:
                // Exit
                running = false;
                break;
                
            default:
                printf("Invalid choice!\n");
                break;
        }
    }
    
    // Cleanup
    printf("\nShutting down...\n");
    story_manager_cleanup();
    color_cleanup();
    display_cleanup();
    platform_cleanup();
    
    printf("Goodbye!\n");
    return 0;
}

/*
 * Start a new game
 * - Scan for available stories
 * - Let player select a story
 * - Load and validate story
 * - Start game loop
 */
void start_new_game(void) {
    printf("\n=== New Game ===\n\n");
    
    // Scan for available stories
    StoryInfo* story_list = NULL;
    int story_count = scan_stories(&story_list);
    
    if (story_count == 0) {
        printf("No stories found in stories/ directory!\n");
        printf("Press any key to continue...\n");
        getchar();
        return;
    }
    
    printf("Found %d story(s):\n", story_count);
    for (int i = 0; i < story_count; i++) {
        printf("%d. %s (by %s)\n", i + 1, story_list[i].title, story_list[i].author);
    }
    
    // Let player select story
    Story* story = select_story(story_list, story_count);
    
    if (story == NULL) {
        printf("No story selected.\n");
        free(story_list);
        return;
    }
    
    // Validate story
    printf("\nValidating story...\n");
    if (!validate_story(story)) {
        printf("Story validation failed! Cannot play this story.\n");
        free_story(story);
        free(story_list);
        printf("Press any key to continue...\n");
        getchar();
        return;
    }
    
    printf("Story validated successfully!\n\n");
    
    // Initialize game state
    GameState* game = init_game_state(story);
    
    // Start the game loop
    play_game(game);
    
    // Cleanup
    free_game_state(game);
    free_story(story);
    free(story_list);
}

/*
 * Load a saved game
 */
void load_saved_game(void) {
    printf("\n=== Load Game ===\n\n");
    printf("(Load game not yet implemented)\n");
    printf("Press any key to continue...\n");
    getchar();
}

/*
 * Main game loop
 * This is where the actual game happens
 */
void play_game(GameState* game) {
    printf("\n");
    printf("========================================\n");
    printf("  %s\n", game->story->metadata.title);
    printf("========================================\n");
    printf("\n");
    
    // Show starting location
    look_at_current_room(game);
    
    // Game loop
    bool playing = true;
    char input[256];
    
    while (playing) {
        // Show prompt
        printf("\n> ");
        
        // Get player input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // EOF or error
        }
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Skip empty input
        if (strlen(input) == 0) {
            continue;
        }
        
        // Parse command
        Command cmd = parse_command(input);
        
        // Execute command
        CommandResult result = execute_command(game, &cmd);
        
        // Check for quit
        if (result == RESULT_QUIT) {
            playing = false;
        }
        
        // Check for victory
        if (check_victory_condition(game)) {
            printf("\n");
            printf("========================================\n");
            printf("  VICTORY!\n");
            printf("========================================\n");
            printf("\n");
            printf("%s\n", game->story->metadata.victory_text);
            printf("\nPress any key to continue...\n");
            getchar();
            playing = false;
        }
    }
}