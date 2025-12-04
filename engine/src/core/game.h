/*
 * game.h - Core game state and management
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "../story/story.h"


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
 * @game_won: True if player has achieved victory
 *
 * Contains all mutable game state including player position, inventory, 
 * progress tracking, and statistics.
 */

typedef struct {
    Story* story;              // Currently loaded story
    Room* current_room;        // Current room player is in
    Item** inventory;          // Player inventory (array of pointers)
    int inventory_count;       // Number of items in inventory
    int inventory_weight;      // Total weight carried
    int* quest_flags;          // Quest completion flags
    int quest_count;           // Number of quests
    int death_count;           // Number of times player died
    int turn_count;            // Number of turns taken
    int score;                 // Current score
    bool game_won;             // Has player won?
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