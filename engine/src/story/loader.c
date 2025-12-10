/*
 * loader.c - Story loading and parsing
 *
 * Loads story files, validates, parses and returns to main game loop.
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/constants.h"
#include "core/utils.h" 
#include "ini_parser.h"
#include "loader.h"
#include "core/logger.h"
#include "world/items.h"
#include "world/npcs.h"


/* Static function declarations */
static int parse_exits(const char* exit_str, char*** exits_out);
static int parse_items(const char *item_str, char ***items_out);
static int parse_npcs(const char *npc_str, char ***npcs_out);


/**
 * parse_exits() - Parse comma-separates exit list
 * @exit_str: String containing exits (e.g., "north:room1, south:room2")
 * @exits_out: Pointer to store allocated exit array
 *
 * Parses comma-separated list of "direction:room_id" pairs.
 * Caller must free both the strings and the array
 *
 * Return: Number of exits parsed, 0 if empty or error
 */

static int parse_exits(const char* exit_str, char*** exits_out) { 
   
    char buffer[INI_VALUE_SIZE];
    char **exits;
    char *token;
    const char *p;
    int count = 1;
    int i = 0;
    
    if (!exit_str || strlen(exit_str) == 0) {
        *exits_out = NULL;
        return 0;
    }

    // Make a copy so we can modify
    
    strncpy(buffer, exit_str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // Count commas to determine number of exits
    for (p = buffer; *p; p++) {
        if (*p == ',') 
            count++;
    }

    // Allocate array of string pointers
    exits = malloc(sizeof(char *) * count);
    if (!exits) 
        return 0;

    // Parse exits
    token = strtok(buffer, ",");
    while (token && i < count) {
        exits[i] = strdup(trim_whitespace(token));
        i++;
        token = strtok(NULL, ",");
    }

    *exits_out = exits;
    return i;
}



/**
 * parse_items() - Parse comma-separated item list
 * @item_str: String containing items (e.g., "sword,shield,potion")
 * @items_out: Pointer to store allocated item array
 *
 * Parses comma-separated list of item identifiers.
 * Caller must free both the strings and the array.
 *
 * Return: Number of items parsed, 0 if empty or error
 */
static int parse_items(const char* item_str, char*** items_out) {
    
    char buffer[INI_VALUE_SIZE];
	char **items;
	char *token;
	const char *p;
	int count = 1;
	int i = 0;

    if (!item_str || strlen(item_str) == 0) {
        *items_out = NULL;
        return 0;
    }
    
    /* Make a copy we can modify */
    strncpy(buffer, item_str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    /* Count commas to determine number of items */
    for (p = buffer; *p; p++) {
        if (*p == ',') 
            count++;
    }
    
    /* Allocate array of string pointers */
    items = malloc(sizeof(char *) * count);
    if (!items) 
        return 0;
    
    /* Parse items */
    token = strtok(buffer, ",");
    while (token && i < count) {
        items[i] = strdup(trim_whitespace(token));
        i++;
        token = strtok(NULL, ",");
    }
    
    *items_out = items;
    return i;
}


/**
 * parse_npcs() - Parse comma-separated NPC list
 * @npc_str: String containing NPCs (e.g., "wizard,guard,merchant")
 * @npcs_out: Pointer to store allocated NPC array
 *
 * Parses comma-separated list of NPC identifiers.
 * Caller must free both the strings and the array.
 *
 * Return: Number of NPCs parsed, 0 if empty or error
 */
static int parse_npcs(const char* npc_str, char*** npcs_out) {
    
    char buffer[INI_VALUE_SIZE];
    char **npcs;
    char *token;
    const char *p;
    int count = 1;
    int i = 0;

    if (!npc_str || strlen(npc_str) == 0) {
        *npcs_out = NULL;
        return 0;
    }
    
    /* Make a copy we can modify */
    strncpy(buffer, npc_str, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    /* Count commas to determine number of NPCs */
    for (p = buffer; *p; p++) {
        if (*p == ',') 
            count++;
    }
    
    /* Allocate array of string pointers */
    npcs = malloc(sizeof(char *) * count);
    if (!npcs) 
        return 0;
    
    /* Parse NPCs */
    token = strtok(buffer, ",");
    while (token && i < count) {
        npcs[i] = strdup(trim_whitespace(token));
        i++;
        token = strtok(NULL, ",");
    }
    
    *npcs_out = npcs;
    return i;
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
    
    Story *story;
	FILE *fp;
	char filepath[INI_VALUE_SIZE];
	char line[INI_LINE_BUFFER_SIZE];
	char current_section[INI_SECTION_SIZE] = "";
	char section[INI_SECTION_SIZE];
	char key[INI_KEY_SIZE];
	char value[INI_VALUE_SIZE];

    log_function_entry(__func__, "story_dir=%s", story_dir);

    printf("Loading story from: %s\n", story_dir);

    // Allocate story structure
    story = malloc(sizeof(Story));
    if (!story) {
        printf("ERROR: Failed to allocate memory for story\n");
        log_function_error(__func__, "story malloc failed");
        return NULL;
    }

    // Initialise to zero
    memset(story, 0, sizeof(Story));

    /* Build filepath */
    snprintf(filepath, sizeof(filepath), "%s/story.ini", story_dir);
    printf("Opening: %s\n", filepath);

    /* Open file */
    add_log_entry("Opening story file: %s at %s", filepath, log_timestamp());
    fp = fopen(filepath, "r");
    if (!fp) {
        printf("ERROR: Cannot open %s\n", filepath);
        log_function_error(__func__, "ERROR: Failed to open story.ini");
        free(story);
        return NULL;
    }

    /* Parse line by line */
    while (fgets(line, sizeof(line), fp)) {
        /* Remove newline */
        line[strcspn(line, "\r\n")] = 0;

        /* Check is this is a section header */
        if (parse_ini_section(line, section, sizeof(section))) {
            strncpy(current_section, section, sizeof(current_section) - 1);
            printf("  [Section: %s]\n", current_section);
            continue;
        }

        /* Try to parse as key=value */
        if (parse_ini_keyvalue(line, key, sizeof(key), value, sizeof(value))) {
            printf("    %s = %s\n", key, value);

            /* If we're in the STORY section, populate metadata */
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
            }
            /* if we're in the SETTINGS section */
            else if (strcmp(current_section, "SETTINGS") == 0) {
                if (strcmp(key, "max_inventory_weight") == 0) {
                    story->metadata.max_inventory_weight = atoi(value);
                    add_log_entry("Set max_inventory_weight=%d at %s", 
                     story->metadata.max_inventory_weight, 
                     log_timestamp());
                }
            }

        }
    }
    add_log_entry("Closing story file at %s", log_timestamp());
    fclose(fp);

    printf("  Title: %s\n", story->metadata.title);
    printf("  Author: %s\n", story->metadata.author);
    printf("  Version: %s\n", story->metadata.version);
    printf("  Start Room: %s\n", story->metadata.start_room);
    add_log_entry("Story metadata at %s: Title: %s, Author: %s, Version: %s, Start Room: %s", log_timestamp(), story->metadata.title, story->metadata.author, story->metadata.version, story->metadata.start_room);

    /* Load rooms */
    story->room_count = load_rooms(story_dir, &story->rooms);
    if (story->room_count == 0) {
        printf("WARNING: No rooms loaded!\n");
        log_function_error(__func__, "WARNING: No rooms loaded from story");
    }
    
    /* Load items */
    story->item_count = load_items(story_dir, &story->items);
    if (story->item_count == 0) {
        printf("WARNING: No items loaded!\n");
        log_function_error(__func__, "WARNING: No items loaded from story");
    } else {
        add_log_entry("Loaded %d items at %s", story->item_count, log_timestamp());
    }

    /* Load NPCs */
    story->npc_count = load_npcs(story_dir, &story->npcs);
    if (story->npc_count == 0) {
        printf("WARNING: No NPCs loaded!\n");
        log_function_error(__func__, "WARNING: No NPCs loaded from story");
    } else {
        add_log_entry("Loaded %d NPCs at %s", story->npc_count, log_timestamp());
    }

    log_function_exit(__func__, 1);
    return story;
}




/**
 * load_rooms() - Load rooms from rooms.ini
 * @story_dir: Path to story directory
 * @rooms_out: Pointer to store allocated room array
 *
 * Uses two-pass approach: counts rooms, allocates array,
 * then fills room data.
 *
 * Return: Number of rooms loaded, 0 on error or empty
 */
int load_rooms(const char *story_dir, Room **rooms_out) {
    
    FILE *fp;
	char filepath[INI_VALUE_SIZE];
	char line[INI_LINE_BUFFER_SIZE];
	char section[INI_SECTION_SIZE];
	char current_section[INI_SECTION_SIZE] = "";
	char key[INI_KEY_SIZE];
	char value[INI_VALUE_SIZE];
	Room *rooms;
	int room_count = 0;
	int current_room = -1;

    /* Build path to rooms.ini */
    snprintf(filepath, sizeof(filepath), "%s/rooms.ini", story_dir);
    printf("\nLoading rooms from: %s\n", filepath);
    
    /* Open file */
    fp = fopen(filepath, "r");
    if (!fp) {
        printf("ERROR: Cannot open %s\n", filepath);
        return 0;
    }
    
    /* First pass: count rooms */
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;

        if (parse_ini_section(line, section, sizeof(section))) {
            if (strncmp(section, "ROOM:", 5) == 0) 
                room_count++;
        }
    }
    
    printf("  Found %d rooms\n", room_count);
    
    if (room_count == 0) {
        fclose(fp);
        *rooms_out = NULL;
        return 0;
    }
    
    /* Allocate room array */
    rooms = calloc(room_count, sizeof(Room));
    if (!rooms) {
        fclose(fp);
        return 0;
    }
    
    /* Second pass: parse rooms */
    rewind(fp);
    
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        
        /*  Check for section header */
        if (parse_ini_section(line, section, sizeof(section))) {
            strncpy(current_section, section, sizeof(current_section) - 1);
            
            /* If it's a ROOM section, start a new room */
            if (strncmp(section, "ROOM:", 5) == 0) {
                current_room++;
                if (current_room >= room_count) 
                    break;
                
                /* Extract room ID (after "ROOM:") */
                strncpy(rooms[current_room].id, section + 5,
                        sizeof(rooms[current_room].id) - 1);
                
                printf("  Loading room: %s\n", section + 5);
            }
            continue;
        }
        
        /* Parse key=value pairs */
        if (current_room >= 0 && 
            parse_ini_keyvalue(line, key, sizeof(key),
                               value, sizeof(value))) {
            Room *room = &rooms[current_room];
            
            if (strcmp(key, "name") == 0) {
                strncpy(room->name, value, 
                    sizeof(room->name) - 1);
            } else if (strcmp(key, "description") == 0) {
                strncpy(room->description, value, 
                    sizeof(room->description) - 1);
            } else if (strcmp(key, "exits") == 0) {
                room->exit_count = parse_exits(value, 
                    &room->exits);
            } else if (strcmp(key, "items") == 0) {
                room->item_count = parse_items(value, 
                    &room->items);
            } else if (strcmp(key, "npcs") == 0) {
                room->npc_count = parse_npcs(value, 
                    &room->npcs);
            }
        }
    }
    
    fclose(fp);
    
    /* Print summary */
    printf("\n  Loaded %d rooms:\n", room_count);
    for (int i = 0; i < room_count; i++) {
        printf("    - %s (%s)\n", rooms[i].id, rooms[i].name);
        printf("      Exits: %d\n", rooms[i].exit_count);
        printf("      Items: %d\n", rooms[i].item_count);
        printf("      NPCs: %d\n", rooms[i].npc_count);
    }
    
    *rooms_out = rooms;
    return room_count;
}

/**
 * free_story() - Free story and all associated data
 * @story: Pointer to story to free
 *
 * Frees all allocated memory including rooms, items, NPCs.
 *
 * Return: void
 */
void free_story(Story* story) {
    if (story) {
        /* Free rooms */
        if (story->rooms) {
            // TODO: Free individual room data
            free(story->rooms);
        }
        
        /* Free items */
        if (story->items) {
            // TODO: Free individual item data
            free(story->items);
        }
        
        /* Free NPCs */
        if (story->npcs) {
            // TODO: Free individual NPC data
            free(story->npcs);
        }
        
        free(story);
    }
}