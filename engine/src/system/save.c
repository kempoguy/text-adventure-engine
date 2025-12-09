/*
 * save.c - Game save/load system implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "save.h"
#include "core/constants.h"
#include "core/game.h"
#include "core/logger.h"
#include "story/ini_parser.h"
#include "world/items.h"

/**
 * save_exists() - Check if save file exists
 * @slot: Save slot number (1-3)
 *
 * Return: 1 if save exists, 0 if not
 */
int save_exists(int slot)
{
	char filepath[LOG_FILENAME_SIZE];
	FILE *f;

	if (slot < 1 || slot > SAVE_MAX_SLOTS)
		return 0;

	snprintf(filepath, sizeof(filepath), SAVE_FILENAME_FORMAT, slot);
	f = fopen(filepath, "r");
	if (f) {
		fclose(f);
		return 1;
	}
	return 0;
}


/**
 * save_game() - Save complete game state to file
 * @game: Current game state
 * @slot: Save slot number (1-3)
 *
 * Return: 0 on success, negative errno on failure
 */
int save_game(GameState *game, int slot)
{
	char filepath[LOG_FILENAME_SIZE];
	FILE *f;
	int i;

	log_function_entry(__func__, "slot=%d, room=%s", 
	                  slot, game->current_room->id);

	if (!game || slot < 1 || slot > SAVE_MAX_SLOTS) {
		log_function_error(__func__, "Invalid game or slot");
		log_function_exit(__func__, -EINVAL);
		return -EINVAL;
	}

	/* Build filepath */
	snprintf(filepath, sizeof(filepath), SAVE_FILENAME_FORMAT, slot);

	/* Open file for writing */
	f = fopen(filepath, "w");
	if (!f) {
		log_function_error(__func__, "Failed to open save file");
		log_function_exit(__func__, -EIO);
		return -EIO;
	}

	/* Write metadata */
	fprintf(f, "[METADATA]\n");
	fprintf(f, "story_name=%s\n", game->story->metadata.title);
	fprintf(f, "save_date=%s\n", log_timestamp());
	fprintf(f, "version=1.0\n");
	fprintf(f, "\n");

	/* Write player state */
	fprintf(f, "[PLAYER]\n");
	fprintf(f, "current_room=%s\n", game->current_room->id);
	fprintf(f, "turn_count=%d\n", game->turn_count);
	fprintf(f, "death_count=%d\n", game->death_count);
	fprintf(f, "score=%d\n", game->score);
	fprintf(f, "game_won=%s\n", game->game_won ? "true" : "false");
	fprintf(f, "\n");

	/* Write inventory */
	fprintf(f, "[INVENTORY]\n");
	fprintf(f, "item_count=%d\n", game->inventory_count);
	fprintf(f, "weight=%d\n", game->inventory_weight);
	for (i = 0; i < game->inventory_count; i++) {
		fprintf(f, "item_%d=%s\n", i, game->inventory[i]->id);
	}
	fprintf(f, "\n");

	/* Write quests */
	fprintf(f, "[QUESTS]\n");
	fprintf(f, "quest_count=%d\n", game->quest_count);
	for (i = 0; i < game->quest_count; i++) {
		fprintf(f, "quest_%d=%d\n", i, game->quest_flags[i]);
	}

	fclose(f);

	add_log_entry("Game saved to slot %d at %s", slot, log_timestamp());
	log_function_exit(__func__, 0);
	return 0;
}


/**
 * load_game() - Load game state from file
 * @game: Game state to populate
 * @slot: Save slot number (1-3)
 *
 * Return: 0 on success, negative errno on failure
 */

 int load_game(GameState *game, int slot)
{
	char filepath[LOG_FILENAME_SIZE];
	char line[INI_LINE_BUFFER_SIZE];
	char section[INI_SECTION_SIZE];
	char current_section[INI_SECTION_SIZE] = "";
	char key[INI_KEY_SIZE];
	char value[INI_VALUE_SIZE];
	char room_id[64];
	FILE *f;
	int item_index;

	log_function_entry(__func__, "slot=%d", slot);

	if (!game || slot < 1 || slot > SAVE_MAX_SLOTS) {
		log_function_error(__func__, "Invalid game or slot");
		log_function_exit(__func__, -EINVAL);
		return -EINVAL;
	}

	/* Check if save exists */
	if (!save_exists(slot)) {
		log_function_error(__func__, "Save file does not exist");
		log_function_exit(__func__, -ENOENT);
		return -ENOENT;
	}

	/* Build filepath */
	snprintf(filepath, sizeof(filepath), SAVE_FILENAME_FORMAT, slot);

	/* Open file */
	f = fopen(filepath, "r");
	if (!f) {
		log_function_error(__func__, "Failed to open save file");
		log_function_exit(__func__, -EIO);
		return -EIO;
	}

	/* Parse save file */
	room_id[0] = '\0';

	while (fgets(line, sizeof(line), f)) {
		line[strcspn(line, "\r\n")] = 0;

		/* Check for section */
		if (parse_ini_section(line, section, sizeof(section))) {
			strncpy(current_section, section, sizeof(current_section) - 1);
			continue;
		}

		/* Parse key=value */
		if (!parse_ini_keyvalue(line, key, sizeof(key), value, sizeof(value)))
			continue;

		/* PLAYER section */
		if (strcmp(current_section, "PLAYER") == 0) {
			if (strcmp(key, "current_room") == 0) {
				strncpy(room_id, value, sizeof(room_id) - 1);
			} else if (strcmp(key, "turn_count") == 0) {
				game->turn_count = atoi(value);
			} else if (strcmp(key, "death_count") == 0) {
				game->death_count = atoi(value);
			} else if (strcmp(key, "score") == 0) {
				game->score = atoi(value);
			} else if (strcmp(key, "game_won") == 0) {
				game->game_won = (strcmp(value, "true") == 0);
			}
		}
		/* INVENTORY section */
		else if (strcmp(current_section, "INVENTORY") == 0) {
			if (strncmp(key, "item_", 5) == 0) {
				/* Extract item index */
				item_index = atoi(key + 5);
				
				/* Find item in story */
				Item *item = find_item_by_id(game->story->items,
				                            game->story->item_count,
				                            value);
				if (item && item_index < 100) {
					/* Add to inventory */
					game->inventory = realloc(game->inventory,
					                         (game->inventory_count + 1) * sizeof(Item*));
					game->inventory[game->inventory_count] = item;
					game->inventory_count++;
					game->inventory_weight += item->weight;
				}
			}
		}
		/* QUESTS section */
		else if (strcmp(current_section, "QUESTS") == 0) {
			if (strncmp(key, "quest_", 6) == 0) {
				/* TODO: Implement quest loading when quest system exists */
			}
		}
	}

	fclose(f);

	/* Set current room */
	if (room_id[0] != '\0') {
		game->current_room = find_room_by_id(game->story, room_id);
		if (!game->current_room) {
			log_function_error(__func__, "Saved room not found in story");
			log_function_exit(__func__, -EINVAL);
			return -EINVAL;
		}
	}

	add_log_entry("Game loaded from slot %d at %s", slot, log_timestamp());
	log_function_exit(__func__, 0);
	return 0;
}