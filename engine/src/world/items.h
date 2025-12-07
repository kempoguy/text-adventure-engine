/*
 * items.h - Item structure and management
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef WORLD_ITEMS_H
#define WORLD_ITEMS_H

#include <stdbool.h>
#include "core/constants.h"
#include "story/story.h"



 /**
  * load_items() - Load items from items.ini file
  * @filename: Path to items.ini file
  * @items: Pointer to store allocated item array
  * @count: Pointer to store number of items loaded
  *
  * Parses items.ini file and allocates array of Item structures.
  * Caller is responsible for freeing the allocated array.
  *
  * Return: 0 on success, negative errno on failure
  */

  int load_items(const char *story_dir, Item **items_out);


  /**
   * find_item_by_id() - Find an item by its identifier
   * @items: Array of items to search
   * @count: Number of items in array
   * @item_id: String identifier to search for
   *
   * Searches the item array for a matching item ID.
   *
   * Return: Pointer to item if found, NULL otherwise
   */
  
   Item *find_item_by_id(Item *items, int count, const char *item_id);
 

#endif /* WORLD_ITEMS_H */
