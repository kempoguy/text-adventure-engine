/*
 * loader.c - Story loading and parsing
 *
 * Loads story files, validates, parses and returns to main game loop.
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "loader.h"


/* Static function declarations */
static int parse_exits(const char* exit_str, char*** exits_out);
static int parse_items(const char* item_str, char*** items_out);
static int parse_keyvalue(char* line, char** key, char** value);
static char* parse_section(char* line);
static char* trim(char* str);


/**
 * trim() - Trims leading nad trailing spaces from strings
 * @str: Pointer to string to be trimmed
 *
 * Return: Trimmed string
 */

static char* trim(char* str) {
    char* end;

    // Trim leading space
    while(isspace((unsigned char)*str)) str++;

    if (*str == 0) {
        return str;
    }

    // Trim trailing space
    end = str + strlen (str) -1;
    while(end > str && isspace((unsigned char)*end)) end --;

    // Write null terminator
    end[1] = '\0';

    return str;
}


 /**
  * parse_section() - Check for section header
  * @line: Pointer to string containing line to be checked
  *
  * Examines string for '[...]' square braces containing content.
  * Calls trim to remove whitespace
  *
  * Return: Trimmed and parsed header string, or NULL if not header
  */
 
static char* parse_section(char* line) {
    line = trim(line);

    if (line[0] == '[') {
        char* end = strchr(line, ']');
        if (end) {
            *end = '\0'; // Terminate at ]
            return trim(line + 1); // Return text between [ and ]
        }
    }

    return NULL;

}


 /**
  * parse-keyvalue() - Parse a key=value line
  * @line: Pointer to input string to be parsed
  * @key: Pointer to key 
  * @value: Pointer to value
  *
  * Modifes key and value pointers to point to the parsed strings
  *
  * Return: 1 if successful, 0 otherwise
  */
 
static int parse_keyvalue(char* line, char** key, char** value) {
    line = trim(line);

    // Skip empty lines and comments
    if (line[0] == '\0' || line[0] == '#' || line [0] == ';') {
        return 0;
    }

    // Find the = sign
    char* equals = strchr(line, '=');
    if (!equals) {
        return 0; // No = sign, not a key=value pair
    }

    // Split at =
    *equals = '\0';
    *key = trim(line);
    *value = (equals + 1);

    return 1;
}


/**
 * load_story() - Loads story metadata from story.ini
 * @story_dir: Pointer to string contianing file path to story 
 *
 * Opens story, allocates resources, parses line by line, closes file, 
 * returns current story
 *
 * Return: Story structure, NULL on failure
 */

Story* load_story(const char* story_dir) {
    printf("Loading story from: %s\n", story_dir);

    // Allocate story structure
    Story* story = malloc(sizeof(Story));
    if (!story) {
        printf("ERROR: Failed to allocate memory for story\n");
        return NULL;
    }

    // Initialise to zero
    memset(story, 0, sizeof(Story));

    // Copy story directory
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/story.ini", story_dir);

    printf("Opening: %s\n", filepath);

    // Open file
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("ERROR: Cannot open %s\n", filepath);
        free(story);
        return NULL;
    }

    // Parse line by line
    char line[512];
    char current_section[64] = "";

    while (fgets(line, sizeof(line), fp)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;

        // Check is this is a section header
        char* section = parse_section(line);
        if (section) {
            strncpy(current_section, section, sizeof(current_section) - 1);
            printf("  [Section: %s]\n", current_section);
            continue;
        }

        // Try to parse as key=value
        char* key;
        char* value;
        if (parse_keyvalue(line, &key, &value)) {
            printf("    %s = %s\n", key, value);

            // If we're in the STORY section, populate metadata
            if (strcmp(current_section, "STORY") == 0) {
                if (strcmp(key, "title") == 0) {
                    strncpy(story->metadata.title, value, sizeof(story->metadata.title) -1);
                }
                else if (strcmp(key, "author") == 0) {
                    strncpy(story->metadata.author, value, sizeof(story->metadata.author) -1);
                }
                else if (strcmp(key, "version") == 0) {
                    strncpy(story->metadata.version, value, sizeof(story->metadata.version) -1);
                }
                else if (strcmp(key, "description") == 0) {
                    strncpy(story->metadata.description, value, sizeof(story->metadata.description) -1);
                }
                else if (strcmp(key, "start_room") == 0) {
                    strncpy(story->metadata.start_room, value, sizeof(story->metadata.start_room) -1);
                }
                else if (strcmp(key, "max_inventory_weight") == 0) {
                    story->metadata.max_inventory_weight = atoi(value);
                }
            }
        }
    }

    fclose(fp);

    printf("  Title: %s\n", story->metadata.title);
    printf("  Author: %s\n", story->metadata.author);
    printf("  Version: %s\n", story->metadata.version);
    printf("  Start Room: %s\n", story->metadata.start_room);

    // Load rooms
    story->room_count = load_rooms(story_dir, &story->rooms);
    if (story->room_count == 0) {
        printf("WARNING: No rooms loaded!\n");
    }
    
    return story;
}

/* 
 * Helper: Parse exit list (e.g., "north:dark_room,south:exit")
 * Return number of exits parsed
 */
static int parse_exits(const char* exit_str, char*** exits_out) { 
    if (!exit_str || strlen(exit_str) == 0) {
        *exits_out = NULL;
        return 0;
    }

    // Make a copy so we can modify
    char buffer[512];
    strncpy(buffer, exit_str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // Count commas to determine number of exits
    int count = 1;
    for (const char* p = buffer; *p; p++) {
        if (*p == ',') count++;
    }

    // Allocate array of string pointers
    char** exits = malloc(sizeof(char*) * count);
    if (!exits) return 0;

    // Parse exits
    int i = 0;
    char* token = strtok(buffer, ",");
    while (token && i < count) {
        exits[i] = strdup(trim(token));
        i++;
        token = strtok(NULL, ",");
    }

    *exits_out = exits;
    return i;
}

/*
 * Helper: Parse item list (e.g., "sword,shield,potion")
 * Returns number of items parsed
 */
static int parse_items(const char* item_str, char*** items_out) {
    if (!item_str || strlen(item_str) == 0) {
        *items_out = NULL;
        return 0;
    }
    
    // Make a copy we can modify
    char buffer[512];
    strncpy(buffer, item_str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    // Count commas to determine number of items
    int count = 1;
    for (const char* p = buffer; *p; p++) {
        if (*p == ',') count++;
    }
    
    // Allocate array of string pointers
    char** items = malloc(sizeof(char*) * count);
    if (!items) return 0;
    
    // Parse items
    int i = 0;
    char* token = strtok(buffer, ",");
    while (token && i < count) {
        items[i] = strdup(trim(token));
        i++;
        token = strtok(NULL, ",");
    }
    
    *items_out = items;
    return i;
}

/*
 * Load rooms from rooms.ini
 */
int load_rooms(const char* story_dir, Room** rooms_out) {
    // Build path to rooms.ini
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/rooms.ini", story_dir);
    
    printf("\nLoading rooms from: %s\n", filepath);
    
    // Open file
    FILE* fp = fopen(filepath, "r");
    if (!fp) {
        printf("ERROR: Cannot open %s\n", filepath);
        return 0;
    }
    
    // First pass: count rooms
    char line[512];
    int room_count = 0;
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        char* section = parse_section(line);
        if (section && strncmp(section, "ROOM:", 5) == 0) {
            room_count++;
        }
    }
    
    printf("  Found %d rooms\n", room_count);
    
    if (room_count == 0) {
        fclose(fp);
        *rooms_out = NULL;
        return 0;
    }
    
    // Allocate room array
    Room* rooms = calloc(room_count, sizeof(Room));
    if (!rooms) {
        fclose(fp);
        return 0;
    }
    
    // Second pass: parse rooms
    rewind(fp);
    
    int current_room = -1;
    char current_section[64] = "";
    
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        
        // Check for section header
        char* section = parse_section(line);
        if (section) {
            strncpy(current_section, section, sizeof(current_section) - 1);
            
            // If it's a ROOM section, start a new room
            if (strncmp(section, "ROOM:", 5) == 0) {
                current_room++;
                if (current_room >= room_count) break;
                
                // Extract room ID (after "ROOM:")
                char* room_id = section + 5;
                strncpy(rooms[current_room].id, room_id, sizeof(rooms[current_room].id) - 1);
                
                printf("  Loading room: %s\n", room_id);
            }
            continue;
        }
        
        // Parse key=value pairs
        char* key;
        char* value;
        if (current_room >= 0 && parse_keyvalue(line, &key, &value)) {
            Room* room = &rooms[current_room];
            
            if (strcmp(key, "name") == 0) {
                strncpy(room->name, value, sizeof(room->name) - 1);
            }
            else if (strcmp(key, "description") == 0) {
                strncpy(room->description, value, sizeof(room->description) - 1);
            }
            else if (strcmp(key, "exits") == 0) {
                room->exit_count = parse_exits(value, &room->exits);
            }
            else if (strcmp(key, "items") == 0) {
                room->item_count = parse_items(value, &room->items);
            }
        }
    }
    
    fclose(fp);
    
    // Print summary
    printf("\n  Loaded %d rooms:\n", room_count);
    for (int i = 0; i < room_count; i++) {
        printf("    - %s (%s)\n", rooms[i].id, rooms[i].name);
        printf("      Exits: %d\n", rooms[i].exit_count);
        printf("      Items: %d\n", rooms[i].item_count);
    }
    
    *rooms_out = rooms;
    return room_count;
}

/*
 * Free story and all its data
 */
void free_story(Story* story) {
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