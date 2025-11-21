#include "validator.h"
#include <stdio.h>
#include <string.h>

/*
 * Validate story
 */
bool validate_story(Story* story) {
    printf("[STUB] validate_story()\n");
    
    if (!story) {
        printf("ERROR: Story is NULL\n");
        return false;
    }
    
    // Basic validation
    if (strlen(story->metadata.title) == 0) {
        printf("ERROR: Story has no title\n");
        return false;
    }
    
    printf("Story '%s' passed basic validation\n", story->metadata.title);
    
    // For now, always return true
    return true;
}