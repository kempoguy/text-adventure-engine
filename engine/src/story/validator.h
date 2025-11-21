#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdbool.h>
#include "story.h"

/*
 * Story validation functions
 */

// Validate story (returns true if valid)
bool validate_story(Story* story);

#endif // VALIDATOR_H