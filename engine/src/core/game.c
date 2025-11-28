#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Helper: Find a room by ID
*/
Room* find_room_by_id(Story* story, const char* room_id) {
    for (int i = 0; i < story->room_count; i++) {
        if (strcmp(story->rooms[i].id, room_id) == 0) {
            return &story->rooms[i]; // Return pointer to this room
        }
    }
    return NULL; // Not found
}


/*
 * Initialize game state for a story
 */
GameState* init_game_state(Story* story) {
    printf("[STUB] init_game_state()\n");
    
    GameState* game = malloc(sizeof(GameState));
    if (!game) {
        return NULL;
    }
    
    game->story = story;

    // Find the starting room
    game->current_room = find_room_by_id(story, story->metadata.start_room); 
    if (!game->current_room) {
        printf("ERROR: Starting room '%s' not found!\n", story->metadata.start_room);
        free(game);
        return NULL;
    }

    printf("[DEBUG] Starting room: %s (%s)\n",
            game->current_room->id,
        game->current_room->name);

    game->inventory = NULL;
    game->inventory_count = 0;
    game->inventory_weight = 0;
    game->quest_flags = NULL;
    game->quest_count = 0;
    game->death_count = 0;
    game->turn_count = 0;
    game->score = 0;
    game->game_won = false;
    
    return game;
}

/*
 * Free game state
 */
void free_game_state(GameState* game) {
    printf("[STUB] free_game_state()\n");
    
    if (game) {
        // Free inventory if allocated
        if (game->inventory) {
            free(game->inventory);
        }
        
        // Free quest flags if allocated
        if (game->quest_flags) {
            free(game->quest_flags);
        }
        
        free(game);
    }
}

/*
 * Check if player has won
 */
bool check_victory_condition(GameState* game) {
    return game->game_won;
}

/*
 * Display current room
 */
void look_at_current_room(GameState* game) {
    if (!game->current_room) {
        printf("ERROR: No current room!\n");
        return;
    }

    Room* room = game->current_room;

    // Print room name
    printf("%s\n", room->name);

    // Print room description
    printf("%s\n", room->description);

    // Print exits
    if (room->exit_count > 0) {
        printf("\nExits:");
        for (int i = 0; i < room->exit_count; i++) {
            // Parse "direction:room_id" format
            char exit_copy[128];
            strncpy(exit_copy, room->exits[i], sizeof(exit_copy) - 1);
            exit_copy[sizeof(exit_copy) - 1] = '\0';

            char* colon = strchr(exit_copy, ':');
            if (colon) {
                *colon = '\0'; // Split at colon
                char* direction = exit_copy;
                printf(" %s", direction);
            }
        }
        printf("\n");
    } else {
        printf("No obvious exits.\n");
    }

    // Print items (if any)
    if (room->item_count > 0) {
        printf("\n you see:");
        for (int i = 0; i < room->item_count; i++) {
            printf(" %s", room->items[i]);
        }
        printf("\n");
    }
}