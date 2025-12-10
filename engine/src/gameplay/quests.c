/*
 * quests.c - Quest system implementation
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/constants.h"
#include "core/logger.h"
#include "core/utils.h"
#include "story/ini_parser.h"
#include "quests.h"


/**
 * load_quests() - Load quests from story files
 * @story_dir: Location of story files
 * @quests_out: Pointer to quests array
 *
 * Load quest information from quests.ini, parse quests, allocate array
 * return quest array pointer
 *
 * Return: number of quests loaded or 0 if no quests / error
 */

int load_quests(const char *story_dir, Quest **quests_out) {
	FILE *fp;
	char filepath[INI_VALUE_SIZE];
	char line[INI_LINE_BUFFER_SIZE];
	char section[INI_SECTION_SIZE];
	char current_section[INI_SECTION_SIZE] = "";
	char key[INI_KEY_SIZE];
	char value[INI_VALUE_SIZE];
	Quest *quests;
	int quest_count = 0;
	int current_quest = -1;

	log_function_entry(__func__, "story_dir=%s", story_dir);

	/* Build path to quests.ini */
	snprintf(filepath, sizeof(filepath), "%s/quests.ini", story_dir);
	
	add_log_entry("Opening quests file: %s at %s", filepath, log_timestamp());

	/* Open file */
	fp = fopen(filepath, "r");
	if (!fp) {
		printf("WARNING: Cannot open %s (quests optional)\n", filepath);
		log_function_exit(__func__, 0);
		*quests_out = NULL;
		return 0;
	}

	/* First pass: count quests */
	while (fgets(line, sizeof(line), fp)) {
		line[strcspn(line, "\r\n")] = 0;

		if (parse_ini_section(line, section, sizeof(section))) {
			if (strncmp(section, "QUEST:", 6) == 0) {
				quest_count++;
				add_log_entry("Found section: '%s' at %s", 
				             section, log_timestamp());
			}
		}
	}

	add_log_entry("Pass 1 complete: found %d quests at %s", 
	             quest_count, log_timestamp());

	if (quest_count == 0) {
		fclose(fp);
		*quests_out = NULL;
		log_function_exit(__func__, 0);
		return 0;
	}

	/* Allocate quest array */
	quests = calloc(quest_count, sizeof(Quest));
	if (!quests) {
		fclose(fp);
		log_function_error(__func__, "Failed to allocate quest array");
		log_function_exit(__func__, 0);
		return 0;
	}

	/* Second pass: parse quests */
	rewind(fp);

	while (fgets(line, sizeof(line), fp)) {
		line[strcspn(line, "\r\n")] = 0;

		/* Check for section header */
		if (parse_ini_section(line, section, sizeof(section))) {
			strncpy(current_section, section, sizeof(current_section) - 1);

			/* If it's a QUEST section, start a new quest */
			if (strncmp(section, "QUEST:", 6) == 0) {
				current_quest++;
				if (current_quest >= quest_count)
					break;

				/* Extract quest ID (after "QUEST:") */
				strncpy(quests[current_quest].id, section + 6,
				       sizeof(quests[current_quest].id) - 1);
				
				/* Initialize quest */
				quests[current_quest].completed = false;
				quests[current_quest].required = false;
			}
			continue;
		}

		/* Parse key=value pairs */
		if (current_quest >= 0 &&
		    parse_ini_keyvalue(line, key, sizeof(key),
		                      value, sizeof(value))) {
			Quest *quest = &quests[current_quest];

			if (strcmp(key, "name") == 0) {
				strncpy(quest->name, value, 
				       sizeof(quest->name) - 1);
			} else if (strcmp(key, "description") == 0) {
				strncpy(quest->description, value,
				       sizeof(quest->description) - 1);
			} else if (strcmp(key, "required") == 0) {
				quest->required = (strcmp(value, "true") == 0);
			} else if (strcmp(key, "completion_item") == 0) {
				strncpy(quest->completion_item, value,
				       sizeof(quest->completion_item) - 1);
			} else if (strcmp(key, "completion_npc") == 0) {
				strncpy(quest->completion_npc, value,
				       sizeof(quest->completion_npc) - 1);
			} else if (strcmp(key, "completion_room") == 0) {
				strncpy(quest->completion_room, value,
				       sizeof(quest->completion_room) - 1);
			} else if (strcmp(key, "completion_message") == 0) {
				strncpy(quest->completion_message, value,
				       sizeof(quest->completion_message) - 1);
			}
		}
	}

	fclose(fp);

	/* Print summary */
	printf("Loaded %d quests at %s\n", quest_count, log_timestamp());
	for (int i = 0; i < quest_count; i++) {
		printf("  Quest %d: %s (%s)\n", i, quests[i].name, 
		       quests[i].required ? "required" : "optional");
	}

	*quests_out = quests;
	log_function_exit(__func__, quest_count);
	return quest_count;
}


/**
 * find_quest_by_id() - Locate quest by id
 * @quests: Pointer to quest array
 * @quest_count: Number of quests
 * @quest_id: Quest ID to search for
 *
 *
 * Return: Quest from array or NULL if nothing / error
 */

Quest* find_quest_by_id(Quest *quests, int quest_count, const char *quest_id) {
	if (!quests || !quest_id)
		return NULL;

	for (int i = 0; i < quest_count; i++) {
		if (strcmp(quests[i].id, quest_id) == 0) {
			return &quests[i];
		}
	}

	return NULL;
}


/**
 * check_quest_completion() - Check to see if quest is complete
 * @quest: Quest to check
 * @item_id: Item to be checked for completion
 * @npc_id: NPC to be checked for completion
 * @room_id: Room to be checked for completion
 *
 * Check to see if quest has been completed. 
 * Quests can require items and/or NPC engagement and/or room access
 *
 * Return: True if quest is complete
 */

bool check_quest_completion(Quest *quest, const char *item_id,
                           const char *npc_id, const char *room_id) {
	bool item_match = false;
	bool npc_match = false;
	bool room_match = false;

	if (!quest || quest->completed)
		return false;

	/* Check each condition - empty string means "not required" */
	
	/* Item condition */
	if (strlen(quest->completion_item) == 0) {
		item_match = true;  /* Not required */
	} else if (item_id && strcmp(quest->completion_item, item_id) == 0) {
		item_match = true;
	}

	/* NPC condition */
	if (strlen(quest->completion_npc) == 0) {
		npc_match = true;  /* Not required */
	} else if (npc_id && strcmp(quest->completion_npc, npc_id) == 0) {
		npc_match = true;
	}

	/* Room condition */
	if (strlen(quest->completion_room) == 0) {
		room_match = true;  /* Not required */
	} else if (room_id && strcmp(quest->completion_room, room_id) == 0) {
		room_match = true;
	}

	/* All conditions must be met */
	return item_match && npc_match && room_match;
}