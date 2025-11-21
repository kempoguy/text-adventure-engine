#include "loader.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Load complete story from directory
 */
Story* load_story(const char* story_dir) {
    printf("[STUB] load_story(%s)\n", story_dir);
    
    // This will be implemented later to actually parse INI files
    // For now, just return NULL
    return NULL;
}

/*
 * Free story and all its data
 */
void free_story(Story* story) {
    printf("[STUB] free_story()\n");
    
    if (story) {
        // Free rooms
        if (story->rooms) {
            // TODO: Free individual room data
            free(story->rooms);
        }
        
        // Free items
        if (story->items) {
            // TODO: Free individual item data
            free(story->items);
        }
        
        // Free NPCs
        if (story->npcs) {
            // TODO: Free individual NPC data
            free(story->npcs);
        }
        
        free(story);
    }
}