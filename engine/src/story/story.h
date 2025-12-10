/*
 * story.h - Story data structures
 *
 * Defines core data structures for story content including
 * metadata, rooms, items, and NPCs.
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef STORY_H
#define STORY_H

#include <stdbool.h>

#include "core/constants.h"


/**
 * struct StoryMetadata - Story metadata and settings
 * @title: Story title
 * @author: Story author name
 * @version: Story version string
 * @description: Brief story description
 * @start_room: ID of starting room
 * @max_inventory_weight: Maximum weight player can carry
 * @victory_score: Score needed to win (0 = not used)
 * @victory_text: Text displayed when player wins
 */

typedef struct {
	char title[STORY_TITLE_SIZE];
	char author[STORY_AUTHOR_SIZE];
	char version[STORY_VERSION_SIZE];
	char description[STORY_DESCRIPTION_SIZE];
	char start_room[ROOM_ID_SIZE];
	int max_inventory_weight;
	int victory_score;
	char victory_text[STORY_DESCRIPTION_SIZE];
} StoryMetadata;


/**
 * struct Room - Game location
 * @id: Unique room identifier
 * @name: Display name
 * @description: Full room description
 * @exits: Array of "direction:room_id" strings
 * @exit_count: Number of exits
 * @items: Array of item IDs present in room
 * @item_count: Number of items in room
 * @npcs: Array of NPC IDs present in room
 * @npc_count: Number of NPCs in room
 * @visited: Has player been here before
 */

typedef struct Room {
	char id[ROOM_ID_SIZE];
	char name[ROOM_NAME_SIZE];
	char description[ROOM_DESCRIPTION_SIZE];
	char** exits;
	int exit_count;
	char** items;
	int item_count;
	char** npcs;
	int npc_count;
	bool visited;
} Room;


/**
 * struct Item - Collectible object
 * @id: Unique item identifier
 * @name: Display name
 * @description: Full item description
 * @weight: Item weight in kg
 * @takeable: Can item be picked up
 * @useable: Can item be used
 */

typedef struct Item {
	char id[ITEM_ID_SIZE];           
	char name[ITEM_NAME_SIZE];       
	char description[ITEM_DESCRIPTION_SIZE];  
	int weight;
	bool takeable;
	bool useable;
} Item;


/**
 * struct NPC - Non-player character
 * @id: Unique NPC identifier
 * @name: Display name
 * @description: Full NPC description
 * @location: Room ID where NPC is located
 * @dialog: Array of dialog lines
 * @dialog_count: Number of dialog lines
 * @dialog_index: Current dialog line (cycles through)
 */

typedef struct NPC {
	char id[NPC_ID_SIZE];
	char name[NPC_NAME_SIZE];
	char description[NPC_DESCRIPTION_SIZE];
	char location[NPC_LOCATION_SIZE];
	char **dialog;
	int dialog_count;
	int dialog_index;
} NPC;


/**
 * struct Story - Complete story package
 * @metadata: Story metadata and settings
 * @rooms: Array of rooms
 * @room_count: Number of rooms
 * @items: Array of items
 * @item_count: Number of items
 * @npcs: Array of NPCs
 * @npc_count: Number of NPCs
 * @story_dir: Directory where story files are located
 */

typedef struct {
	StoryMetadata metadata;
	
	Room* rooms;
	int room_count;
	
	Item* items;
	int item_count;
	
	NPC* npcs;
	int npc_count;
	
	char story_dir[STORY_DIRECTORY_SIZE];
} Story;


/**
 * struct StoryInfo - Story info for menu display
 * @title: Story title
 * @author: Story author name
 * @version: Story version string
 * @description: Brief story description
 * @directory: Directory path
 *
 * Lightweight structure for displaying story info
 * without loading complete story data.
 */

typedef struct {
	char title[STORY_TITLE_SIZE];
	char author[STORY_AUTHOR_SIZE];
	char version[STORY_VERSION_SIZE];
	char description[STORY_DESCRIPTION_SIZE];
	char directory[STORY_DIRECTORY_SIZE];
} StoryInfo;

#endif /* STORY_H */