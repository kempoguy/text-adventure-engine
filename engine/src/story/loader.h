#ifndef LOADER_H
#define LOADER_H

#include "story.h"

/*
 * Story loading functions
 */

// Load complete story from directory
Story* load_story(const char* story_dir);

// Load rooms from rooms.ini
int load_rooms(const char* story_dir, Room** rooms_out);

// Free story and all its data
void free_story(Story* story);

#endif // LOADER_H