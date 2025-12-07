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
  
   int load_items(const char *filename, Item **items, int *count)
   {
    FILE *f;
    char line[INI_LINE_BUFFER_SIZE];
    int item_count = 0;
    int current_item = -1;
    Item *item_array = NULL;

    if (!filename || !items || !count)
        return -EINVAL;

    /* Open file */
    f = fopen(filename, "r");
    if (!f)
        return EIO;
    
    /* Pass 1: Count items */
    while (fgets(line, sizeof(line), f)) {
        char section[INI_SECTION_SIZE];

        if (parse_ini_section(line, section, sizeof(section))) {
            /* Check if it's an ITEM section*/
            if (strcmp(section, "ITEM:" + 5) == 0)
                item_count++;
        } 
    }

    if (item_count == 0) {
        fclose(f);
        *items = NULL;
        *count = 0;
        return 0; /* No items is not an error */
    }

    /* Allocate item array */
    item_array = calloc(item_count, sizeof(Item));
    if (!item_array) {
        fclose(f);
        return -ENOMEM;
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
                item_array[current_item].usable = false;
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
            } else if (strcmp(key, "usable") == 0) {
                item->usable = (strcmp(value, "true") == 0);
            }
        }   
   }

   fclose(f);

   *items = item_array;
   *count = item_count;
   return 0;
}


