/*
 * items.c - Item loading and management implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

 #include <errno.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "core/logger.h"
 #include "items.h"
 #include "story/ini_parser.h"

 /**
  * find_item_by_id() - Find an item by its identifier 
  * @items: Array of items to dearch
  * @count: Number of items in array
  * @item_id: String identifier to search for
  *
  * Searches the item array fora matching item ID
  * 
  * Return: Pointer to item if found, NULL otherwise
  */
 
  Item *find_item_by_id(Item *items, int count, const char *item_id)
  {
    int i;

    if (!items || !item_id)
        return NULL;

    for (i = 0; i < count; i++) {
        if (strcmp(items[i].id, item_id) == 0)
            return &items[i];
    }

    return NULL;
  }


  /**
   * load_items() - Load items from items.ini file
   * @filename: Path to items.ini
   * @items: Pointer to store allocated items array
   * @count: Pointer to store number of items loaded
   * 
   * Parses items.ini file usinf two-pass approach: first counts
   * items, the nallocated and fills the array. Uses INI parser 
   * to read item properties.
   * 
   * Return: Description of return value and error codes
   */
  
   int load_items(const char *story_dir, Item **items_out)
   {
    FILE *f;
    char filepath[INI_VALUE_SIZE];
    char line[INI_LINE_BUFFER_SIZE];
    int item_count = 0;
    int current_item = -1;
    Item *item_array = NULL;

    log_function_entry(__func__, "story_dir=%s", story_dir);

    if (!story_dir || !items_out) {
        log_function_error(__func__, "ERROR: Invalid story directory or items");
        log_function_exit(__func__, 0);
        return 0;
    }

    snprintf(filepath, sizeof(filepath), "%s/items.ini", story_dir);
    add_log_entry("Opening items file: %s at %s", filepath, log_timestamp());

    /* Open file */
    f = fopen(filepath, "r");
    if (!f) {
        printf("WARNING: Cannot open %s\n", filepath);
        log_function_error(__func__, "Failed to open items.ini");
        log_function_exit(__func__, 0);
        return EIO;
    }
    /* Pass 1: Count items */
    while (fgets(line, sizeof(line), f)) {
        char section[INI_SECTION_SIZE];

        if (parse_ini_section(line, section, sizeof(section))) {
            add_log_entry("Found section: '%s' at %s", section, log_timestamp());
            /* Check if it's an ITEM section*/
            if (strncmp(section, "ITEM:", 5) == 0)
                item_count++;
        } 
    }
    add_log_entry("Pass 1 complete: found %d items at %s", item_count,          log_timestamp());
    if (item_count == 0) {
        fclose(f);
        *items_out = NULL;
        log_function_error(__func__, "No items found in items.ini");
        log_function_exit(__func__, 0);
        return 0; /* No items is not an error */
    }

    /* Allocate item array */
    item_array = calloc(item_count, sizeof(Item));
    if (!item_array) {
        fclose(f);
        log_function_error(__func__, "Failed to allocate memory");
        log_function_exit(__func__, 0);
        return 0;
    }


    /* Pass 2: Load items */
    rewind(f);
    current_item = -1;

    while (fgets(line, sizeof(line), f)) {
        char section[INI_SECTION_SIZE];
        char key[INI_KEY_SIZE];
        char value[INI_VALUE_SIZE];

        /* Check for section header */
        if (parse_ini_section(line, section, sizeof(section))) {
            if (strncmp(section, "ITEM:", 5) ==0) {
                current_item++;
                /* Extract item ID from "Item:id" */
                strncpy(item_array[current_item].id,
                    section + 5,
                    ITEM_ID_SIZE - 1);
                /* Set defaults */
                item_array[current_item].weight = 0;
                item_array[current_item].takeable = false;
                item_array[current_item].useable = false;
            }
            continue;
        }

        /* Parse key-value pair */
        if (current_item >= 0 &&
            parse_ini_keyvalue(line, key, sizeof(key),
                    value, sizeof(value))) {
            Item *item = &item_array[current_item];

            if (strcmp(key, "name") == 0) {
                strncpy(item->name, value,
                    ITEM_NAME_SIZE - 1);
            } else if (strcmp(key, "description") == 0) {
                strncpy(item->description, value,
                    ITEM_DESCRIPTION_SIZE - 1);
            } else if (strcmp(key, "weight") == 0) {
                item->weight = atoi(value);
            } else if (strcmp(key, "takeable") == 0) {
                item->takeable = (strcmp(value, "true") == 0);
            } else if (strcmp(key, "useable") == 0) {
                item->useable = (strcmp(value, "true") == 0);
            }
        }   
   }

   fclose(f);

   *items_out = item_array;
   add_log_entry("Loaded %d items at %s", item_count, log_timestamp());
   log_function_exit(__func__, item_count);
   return item_count;
}


