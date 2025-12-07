#ifndef STORY_H
#define STORY_H

#include <stdbool.h>

/*
 * Story metadata
 */
typedef struct {
    char title[128];
    char author[64];
    char version[16];
    char description[512];
    char start_room[64];           // ID of starting room
    int max_inventory_weight;
    int victory_score;
    char victory_text[512];
} StoryMetadata;

/*
 * Room structure
 */
typedef struct Room {
    char id[64];
    char name[128];
    char description[512];
    char** exits;           // Array of "direction:room_id" strings
    int exit_count;
    char** items;           // Array of item IDs in this room
    int item_count;
    char** npcs;            // Array of NPC IDs in this room
    int npc_count;
    bool visited;
} Room;

/*
 * Item structure
 */
typedef struct Item {
    char id[64];
    char name[128];
    char description[256];
    int weight;
    bool takeable;
    bool useable;
    // bool quest_item;
} Item;

/*
 * NPC structure
 */
typedef struct NPC {
    char id[64];
    char name[128];
    char description[256];
    char location[64];      // Room ID
} NPC;

/*
 * Complete story package
 */
typedef struct {
    StoryMetadata metadata;
    
    Room* rooms;
    int room_count;
    
    Item* items;
    int item_count;
    
    NPC* npcs;
    int npc_count;
    
    char story_dir[256];    // Directory where story files are located
} Story;

/*
 * Story info (for menu display, without loading full story)
 */
typedef struct {
    char title[128];
    char author[64];
    char version[16];
    char description[512];
    char directory[256];
} StoryInfo;

#endif // STORY_H