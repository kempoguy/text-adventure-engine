/*
 * npcs.c - NPC loading and management
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "npcs.h"
#include "core/constants.h"
#include "core/logger.h"
#include "story/ini_parser.h"

/**
 * find_npc_by_id() - Find NPC by ID
 * @npcs: Array of NPCs
 * @count: Number of NPCs
 * @id: NPC ID to search for
 *
 * Return: Pointer to NPC if found, NULL otherwise
 */
NPC *find_npc_by_id(NPC *npcs, int count, const char *id)
{
	int i;

	if (!npcs || !id)
		return NULL;

	for (i = 0; i < count; i++) {
		if (strcmp(npcs[i].id, id) == 0)
			return &npcs[i];
	}

	return NULL;
}

/**
 * load_npcs() - Load NPCs from npcs.ini file
 * @story_dir: Path to story directory
 * @npcs_out: Pointer to store allocated NPC array
 *
 * Return: Number of NPCs loaded, 0 on error or empty
 */
int load_npcs(const char *story_dir, NPC **npcs_out)
{
	FILE *f;
	char filepath[INI_VALUE_SIZE];
	char line[INI_LINE_BUFFER_SIZE];
	char section[INI_SECTION_SIZE];
	char key[INI_KEY_SIZE];
	char value[INI_VALUE_SIZE];
	NPC *npc_array = NULL;
	int npc_count = 0;
	int current_npc = -1;
	int dialog_index;

	log_function_entry(__func__, "story_dir=%s", story_dir);

	if (!story_dir || !npcs_out) {
		log_function_error(__func__, "Invalid parameters");
		log_function_exit(__func__, 0);
		return 0;
	}

	/* Build filepath */
	snprintf(filepath, sizeof(filepath), "%s/npcs.ini", story_dir);
	add_log_entry("Opening NPCs file: %s at %s", filepath, log_timestamp());

	/* Open file */
	f = fopen(filepath, "r");
	if (!f) {
		printf("WARNING: Cannot open %s\n", filepath);
		log_function_error(__func__, "Failed to open npcs.ini");
		log_function_exit(__func__, 0);
		*npcs_out = NULL;
		return 0;
	}

	/* Pass 1: Count NPCs */
	while (fgets(line, sizeof(line), f)) {
		if (parse_ini_section(line, section, sizeof(section))) {
			if (strncmp(section, "NPC:", 4) == 0) {
				npc_count++;
				add_log_entry("Found section: '%s' at %s", 
				             section, log_timestamp());
			}
		}
	}

	add_log_entry("Pass 1 complete: found %d NPCs at %s", 
	             npc_count, log_timestamp());

	if (npc_count == 0) {
		fclose(f);
		*npcs_out = NULL;
		log_function_error(__func__, "No NPCs found in npcs.ini");
		log_function_exit(__func__, 0);
		return 0;
	}

	/* Allocate NPC array */
	npc_array = calloc(npc_count, sizeof(NPC));
	if (!npc_array) {
		fclose(f);
		log_function_error(__func__, "Failed to allocate memory");
		log_function_exit(__func__, 0);
		return 0;
	}

	/* Pass 2: Load NPCs */
	rewind(f);
	current_npc = -1;

	while (fgets(line, sizeof(line), f)) {
		char *trimmed;

		line[strcspn(line, "\r\n")] = 0;

		/* Check for section header */
		if (parse_ini_section(line, section, sizeof(section))) {
			if (strncmp(section, "NPC:", 4) == 0) {
				current_npc++;
				
				/* Extract NPC ID from "NPC:id" */
				strncpy(npc_array[current_npc].id,
				       section + 4,
				       NPC_ID_SIZE - 1);

				/* Initialize dialog array */
				npc_array[current_npc].dialog = NULL;
				npc_array[current_npc].dialog_count = 0;
				npc_array[current_npc].dialog_index = 0;
			}
			continue;
		}

		/* Parse key=value pairs */
		if (current_npc >= 0 &&
		    parse_ini_keyvalue(line, key, sizeof(key),
		                      value, sizeof(value))) {
			NPC *npc = &npc_array[current_npc];

			if (strcmp(key, "name") == 0) {
				strncpy(npc->name, value, NPC_NAME_SIZE - 1);
			} else if (strcmp(key, "description") == 0) {
				strncpy(npc->description, value,
				       NPC_DESCRIPTION_SIZE - 1);
			} else if (strcmp(key, "location") == 0) {
				strncpy(npc->location, value,
				       NPC_LOCATION_SIZE - 1);
			} else if (strncmp(key, "dialog_", 7) == 0) {
				/* Extract dialog index */
				dialog_index = atoi(key + 7);

				/* Expand dialog array if needed */
				if (dialog_index >= npc->dialog_count) {
					npc->dialog = realloc(npc->dialog,
					                     (dialog_index + 1) * sizeof(char*));
					npc->dialog_count = dialog_index + 1;
				}

				/* Store dialog line */
				npc->dialog[dialog_index] = strdup(value);
			}
		}
	}

	fclose(f);

	*npcs_out = npc_array;
	add_log_entry("Loaded %d NPCs at %s", npc_count, log_timestamp());
	
	for (int i = 0; i < npc_count; i++) {
		add_log_entry("  NPC %d: %s (%d dialog lines)", 
		             i, npc_array[i].name, npc_array[i].dialog_count);
	}

	log_function_exit(__func__, npc_count);
	return npc_count;
}