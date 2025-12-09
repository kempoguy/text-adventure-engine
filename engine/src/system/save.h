/*
 * save.h - Game save/load system
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SYSTEM_SAVE_H
#define SYSTEM_SAVE_H

#include "core/game.h"

/**
 * save_game() - Save game state to file
 * @game: Current game state
 * @slot: Save slot number (1-3)
 *
 * Saves current game state to saves/save_slot_N.sav
 *
 * Return: 0 on success, negative errno on failure
 */
int save_game(GameState *game, int slot);

/**
 * load_game() - Load game state from file
 * @game: Game state to populate
 * @slot: Save slot number (1-3)
 *
 * Loads game state from saves/save_slot_N.sav
 *
 * Return: 0 on success, negative errno on failure
 */
int load_game(GameState *game, int slot);

/**
 * save_exists() - Check if save file exists
 * @slot: Save slot number (1-3)
 *
 * Return: 1 if save exists, 0 if not
 */
int save_exists(int slot);

#endif /* SYSTEM_SAVE_H */