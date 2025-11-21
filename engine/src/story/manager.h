#ifndef STORY_MANAGER_H
#define STORY_MANAGER_H

#include "story.h"

/*
 * Story manager functions
 */

// Initialize story manager
void story_manager_init(const char* stories_dir);

// Cleanup story manager
void story_manager_cleanup(void);

// Scan for available stories
int scan_stories(StoryInfo** story_list);

// Select a story (returns loaded story or NULL)
Story* select_story(StoryInfo* story_list, int count);

#endif // STORY_MANAGER_H