/*
 * quests.h - Quest system interface
 *
 * Copyright (C) 2025 Marty
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef QUESTS_H
#define QUESTS_H

#include "story/story.h"

/**
 * load_quests() - Load quests from quests.ini
 * @story_dir: Path to story directory
 * @quests_out: Pointer to store allocated quest array
 *
 * Uses two-pass approach: counts quests, allocates array,
 * then fills quest data.
 *
 * Return: Number of quests loaded, 0 on error or empty
 */
int load_quests(const char *story_dir, Quest **quests_out);


/**
 * find_quest_by_id() - Find a quest by its identifier
 * @quests: Array of quests
 * @quest_count: Number of quests in array
 * @quest_id: Quest identifier to find
 *
 * Return: Pointer to quest if found, NULL otherwise
 */
Quest* find_quest_by_id(Quest *quests, int quest_count, const char *quest_id);


/**
 * check_quest_completion() - Check if quest conditions are met
 * @quest: Quest to check
 * @item_id: Item just acquired (or NULL)
 * @npc_id: NPC just talked to (or NULL)
 * @room_id: Room just entered (or NULL)
 *
 * Checks if provided IDs match quest completion conditions.
 * Returns true if quest should be marked complete.
 *
 * Return: true if quest completed, false otherwise
 */
bool check_quest_completion(Quest *quest, const char *item_id, 
                           const char *npc_id, const char *room_id);

#endif /* QUESTS_H */