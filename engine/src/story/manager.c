#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char stories_directory[256];

/*
 * Initialize story manager
 */
void story_manager_init(const char* stories_dir) {
    printf("[STUB] story_manager_init(%s)\n", stories_dir);
    strncpy(stories_directory, stories_dir, sizeof(stories_directory) - 1);
}

/*
 * Cleanup story manager
 */
void story_manager_cleanup(void) {
    printf("[STUB] story_manager_cleanup()\n");
}

/*
 * Scan for available stories
 */
int scan_stories(StoryInfo** story_list) {
    printf("[STUB] scan_stories()\n");
    
    // For now, create a dummy story list with test-story
    *story_list = malloc(sizeof(StoryInfo) * 2);
    
    // Story 1: Test Adventure
    strcpy((*story_list)[0].title, "Test Adventure");
    strcpy((*story_list)[0].author, "Engine Team");
    strcpy((*story_list)[0].version, "0.1.0");
    strcpy((*story_list)[0].description, "A minimal test story");
    strcpy((*story_list)[0].directory, "stories/test-story");
    
    // Story 2: Gravy Boat (not yet implemented)
    strcpy((*story_list)[1].title, "Quest for the Holy Gravy Boat");
    strcpy((*story_list)[1].author, "Marty & Claude");
    strcpy((*story_list)[1].version, "1.0.0");
    strcpy((*story_list)[1].description, "A Monty Python adventure (not yet playable)");
    strcpy((*story_list)[1].directory, "stories/gravy-boat");
    
    return 2;  // Return count
}

/*
 * Select a story
 */
Story* select_story(StoryInfo* story_list, int count) {
    printf("\nSelect a story (1-%d, or 0 to cancel): ", count);
    
    char input[10];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return NULL;
    }
    
    int choice = atoi(input);
    
    if (choice < 1 || choice > count) {
        return NULL;
    }
    
    // Load the selected story
    printf("\nLoading: %s...\n", story_list[choice - 1].title);
    
    // For now, return a stub story
    Story* story = malloc(sizeof(Story));
    if (!story) {
        return NULL;
    }
    
    story->metadata = (StoryMetadata){0};
    strcpy(story->metadata.title, story_list[choice - 1].title);
    strcpy(story->metadata.author, story_list[choice - 1].author);
    strcpy(story->metadata.version, story_list[choice - 1].version);
    strcpy(story->metadata.description, story_list[choice - 1].description);
    strcpy(story->metadata.start_room, "entrance");
    story->metadata.max_inventory_weight = 50;
    story->metadata.victory_score = 1000;
    strcpy(story->metadata.victory_text, "You win! (This is a stub victory message)");
    
    story->rooms = NULL;
    story->room_count = 0;
    story->items = NULL;
    story->item_count = 0;
    story->npcs = NULL;
    story->npc_count = 0;
    strcpy(story->story_dir, story_list[choice - 1].directory);
    
    return story;
}