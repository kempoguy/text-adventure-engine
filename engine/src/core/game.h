/*
 * game.h - Core game state and management
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "core/logger.h"
#include "story/story.h"


/**
 * struct GameState - Runtime game state
 * @story: Pointer to currently loaded story
 * @current_room: Pointer to room player is currently in
 * @inventory: Player inventory (array or pointers)
 * @inventory_count: Number of items currently in inventory
 * @inventory_weight: Total weight of items being carried
 * @quest_flags: Array of quest completion flags
 * @quest_count: Number of quests in current story
 * @death_count: Number of times player has died
 * @turn_count: Number of turns elapsed
 * @score: Current player score
 * @respawn_room: Room to respawn after death
 * @combat_npc: Currently fighting this NPC (NULL if not in combat)
 * @player_combat_hp: Player HP in current combat
 * @game_won: True if player has achieved victory
 *
 * Contains all mutable game state including player position, inventory, 
 * progress tracking, and statistics.
 */

typedef struct {
    Story* story;             
    Room* current_room;        
    Item** inventory;          
    int inventory_count;      
    int inventory_weight;     
    int* quest_flags;        
    int quest_count;          
    int death_count;         
    int turn_count;         
    int score;               
    char respawn_room[ROOM_ID_SIZE];

    /* Combat state */
    NPC *combat_npc;
    int player_combat_hp;
    bool game_won;            
} GameState;



/**
 * init_game_state() - Create and initialise game state for a story
 * @story: Pointer to loaded story
 *
 * Allocates and initializes a new GameState structure, sets the starting room,
 * and initializes all counters to zero.
 *
 * Return: Pointer to initialized GameState, or NULL on allocation failure
 */

GameState* init_game_state(Story* story);


/**
 * free_game_state() - Free game state and associated resources
 * @game: Pointer to game state to free
 * 
 * Frees inventory, quest flags, and the game state structure itself.
 *
 * Return: void
 */

void free_game_state(GameState* game);


/**
 * check_victory_condition() - Check if player has won the game
 * @game: Pointer to current game state
 *
 * Checks the game_won flag to determine victory status.
 *
 * Return: True if player has won, false otherwise
 */

bool check_victory_condition(GameState* game);


/**
 * look_at_current_room() - Display current room information
 * @game: Pointer to current game state
 *
 * Prints room name, description, available exits, and visible items.
 *
 * Return: void
 */

void look_at_current_room(GameState* game);


/**
 * check_and_complete_quests() - Check if any quests completed
 * @game: Pointer to current game state
 * @item_id: Item just acquired (or NULL)
 * @npc_id: NPC just talked to (or NULL)
 * @room_id: Room just entered (or NULL)
 *
 * Checks all incomplete quests to see if completion conditions are met.
 * Displays completion message and updates quest status.
 *
 * Return: void
 */

void check_and_complete_quests(GameState* game, const char* item_id, 
                               const char* npc_id, const char* room_id);


/**
 * find_room_by_id() - Find a room by its identifier
 * @story: Pointer to story data
 * @room_id: String identifier of room to find
 *
 * Searches the story's room array for a matching room ID.
 *
 * Return: Pointer to room if found, NULL otherwise
 */

Room* find_room_by_id(Story* story, const char* room_id);

#endif /* GAME_H */