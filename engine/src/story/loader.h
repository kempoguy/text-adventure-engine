#ifndef LOADER_H
#define LOADER_H

#include "story.h"

/*
 * Story loading functions
 */

// Load complete story from directory
Story* load_story(const char* story_dir);

// Free story and all its data
void free_story(Story* story);

#endif // LOADER_H