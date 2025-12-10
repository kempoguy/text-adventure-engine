/*
 * npcs.h - NPC management
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef WORLD_NPCS_H
#define WORLD_NPCS_H

#include "story/story.h"

/**
 * load_npcs() - Load NPCs from npcs.ini file
 * @story_dir: Path to story directory
 * @npcs_out: Pointer to store allocated NPC array
 *
 * Parses npcs.ini file using two-pass approach: first counts
 * NPCs, then allocates and fills the array.
 *
 * Return: Number of NPCs loaded, 0 on error or empty
 */
int load_npcs(const char *story_dir, NPC **npcs_out);

/**
 * find_npc_by_id() - Find NPC by ID
 * @npcs: Array of NPCs
 * @count: Number of NPCs
 * @id: NPC ID to search for
 *
 * Return: Pointer to NPC if found, NULL otherwise
 */
NPC *find_npc_by_id(NPC *npcs, int count, const char *id);

#endif /* WORLD_NPCS_H */