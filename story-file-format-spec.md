# STORY FILE FORMAT SPECIFICATION
## Text Adventure Engine Story Data Format

**Version:** 1.0  
**Date:** November 21, 2025  
**Format:** INI-style Configuration Files

---

## OVERVIEW

### Purpose

This document defines the file format for story data files used by the Text Adventure Engine. Story files contain all content (rooms, items, NPCs, dialog, quests) in a human-readable, editable text format.

### Design Goals

1. **Human-readable** - Easy to read and edit in any text editor
2. **Simple to parse** - Can be parsed in C without external libraries
3. **Extensible** - Can add new fields without breaking old parsers
4. **Validatable** - Errors can be detected and reported clearly
5. **Version-tolerant** - Future versions can add features gracefully

### Format Choice: INI-Style

We use an INI-style format with enhancements:
- Section headers: `[SECTION_TYPE:id]`
- Key-value pairs: `key=value`
- Lists: `key=value1,value2,value3`
- Multi-line text: `key=|Line 1\n|Line 2`
- Comments: `# This is a comment`

---

## FILE STRUCTURE

### Story Directory Layout

Each story lives in its own directory under `stories/`:

```
stories/
└── story-name/
    ├── story.ini       # Main metadata file (REQUIRED)
    ├── rooms.ini       # Room definitions (REQUIRED)
    ├── items.ini       # Item definitions (REQUIRED)
    ├── npcs.ini        # NPC definitions (OPTIONAL)
    ├── dialogs.ini     # Dialog trees (OPTIONAL)
    ├── quests.ini      # Quest definitions (OPTIONAL)
    ├── scripts.ini     # Script configurations (OPTIONAL)
    └── README.md       # Story documentation (OPTIONAL)
```

### Loading Order

1. `story.ini` - Metadata and file references
2. `rooms.ini` - All rooms
3. `items.ini` - All items
4. `npcs.ini` - All NPCs (if file exists)
5. `dialogs.ini` - All dialogs (if file exists)
6. `quests.ini` - All quests (if file exists)
7. `scripts.ini` - Script configs (if file exists)

After loading, validation pass checks all cross-references.

---

## GENERAL SYNTAX RULES

### Section Headers

Format: `[SECTION_TYPE:identifier]`

- Must start with `[` and end with `]`
- Section type is uppercase (e.g., ROOM, ITEM, NPC)
- Colon separates type from identifier
- Identifier is unique within that type
- Identifiers: alphanumeric, underscores, hyphens only

**Examples:**
```ini
[ROOM:throne_room]
[ITEM:rusty_sword]
[NPC:king_blorgen]
[DIALOG:king_greeting_1]
[QUEST:main_quest]
```

### Key-Value Pairs

Format: `key=value`

- One per line
- No spaces around `=` (trimmed by parser)
- Keys are lowercase with underscores
- Values depend on type (see below)

**Examples:**
```ini
name=Throne Room
weight=5
takeable=true
```

### Value Types

**String (single-line):**
```ini
name=Throne Room
description=A shabby throne room with water damage.
```

**Integer:**
```ini
weight=5
room_count=35
start_room_id=1
```

**Boolean:**
```ini
takeable=true
quest_item=false
visited=false
```
Valid values: `true`, `false`, `yes`, `no`, `1`, `0`

**List (comma-separated):**
```ini
exits=north:great_hall,east:treasury,west:kitchen
items=scroll,sword,shield
tags=funny,dangerous,important
```

**Multi-line Text:**
```ini
description=|A surprisingly shabby throne room with water damage on the ceiling.
|The king looks simultaneously bored and irritated.
|There's a faint smell of gravy.
```
Each continuation line starts with `|`

**Key-Value Pairs (in value):**
```ini
exits=north:great_hall,east:treasury
responses=1:Yes sire,2:No way
attributes=strength:10,wisdom:5
```

### Comments

```ini
# This is a comment
name=Test Room  # Inline comments allowed

# Multi-line comment block:
# This room is the starting location.
# Players begin here with no items.
```

### Empty Lines

- Empty lines are ignored
- Use for readability between sections

### Special Characters

- **Escape sequences** in strings:
  - `\n` - Newline
  - `\t` - Tab
  - `\\` - Literal backslash
  - `\|` - Literal pipe (in multiline text)

---

## FILE FORMATS

### 1. story.ini - Story Metadata

**Purpose:** Main story file with metadata and file references.

**Required Sections:**
- `[STORY]` - Basic story information
- `[FILES]` - References to other story files

**Example:**
```ini
# Quest for the Holy Gravy Boat
# Story metadata and configuration

[STORY]
title=Quest for the Holy Gravy Boat
author=Marty & Claude
version=1.0.0
description=|A Monty Python-style medieval adventure where you must recover
|the Holy Gravy Boat from the Castle of Excessive Bureaucracy.
start_room=throne_room
max_inventory_weight=50
victory_score=1000

[FILES]
rooms=rooms.ini
items=items.ini
npcs=npcs.ini
dialogs=dialogs.ini
quests=quests.ini
scripts=scripts.ini

[SETTINGS]
# Optional gameplay settings
color_enabled=true
autosave=true
hint_cost=10
debug_mode=false
```

**Field Definitions:**

**[STORY] Section:**
- `title` (string, REQUIRED) - Story title
- `author` (string, REQUIRED) - Story author(s)
- `version` (string, REQUIRED) - Version number (semver)
- `description` (multiline, REQUIRED) - Story description
- `start_room` (string, REQUIRED) - ID of starting room
- `max_inventory_weight` (int, OPTIONAL) - Default: 100
- `victory_score` (int, OPTIONAL) - Score for winning, default: 1000

**[FILES] Section:**
- All fields optional (if file doesn't exist, that content type is unavailable)
- Values are filenames relative to story directory

**[SETTINGS] Section:**
- All optional
- Override engine defaults

---

### 2. rooms.ini - Room Definitions

**Purpose:** Define all rooms in the game world.

**Section Format:** `[ROOM:room_id]`

**Example:**
```ini
# Throne Room - Starting location
[ROOM:throne_room]
name=Throne Room
short_name=throne room
description=|A surprisingly shabby throne room with water damage on the ceiling.
|The king looks simultaneously bored and irritated.
exits=north:great_hall,east:treasury
items=scroll
npcs=king_blorgen
visited=false
first_visit_text=|You've never seen such a disappointing throne room.
dark=false
locked=false

# Great Hall
[ROOM:great_hall]
name=Great Hall
short_name=hall
description=|A drafty hall that smells faintly of old cabbage and regret.
|Long tables line the walls.
exits=south:throne_room,north:courtyard,west:kitchen,east:armory
items=table,bench,tapestry
npcs=sir_robin
visited=false
tags=large,social_hub
```

**Field Definitions:**

**Required Fields:**
- `name` (string) - Full room name (for display)
- `description` (multiline) - Room description
- `exits` (list of dir:room_id) - Available exits

**Optional Fields:**
- `short_name` (string) - Shorter name for "You are in the [short_name]"
- `items` (list of item_id) - Items in room (default: empty)
- `npcs` (list of npc_id) - NPCs in room (default: empty)
- `visited` (bool) - Has player visited? (default: false)
- `first_visit_text` (multiline) - Text shown on first visit only
- `dark` (bool) - Room is dark without light source (default: false)
- `locked` (bool) - Room is locked (needs key or script) (default: false)
- `lock_item` (item_id) - Item needed to unlock
- `lock_script` (script_name) - Script to run when attempting entry
- `tags` (list of strings) - Arbitrary tags for grouping/searching

**Exit Format:**
- `direction:destination_room_id`
- Valid directions: `north`, `south`, `east`, `west`, `up`, `down`, `in`, `out`
- Can use abbreviations: `n`, `s`, `e`, `w`, `u`, `d`

**Example Exits:**
```ini
exits=north:great_hall,east:treasury,west:garden
exits=n:cave_entrance,s:forest_path,up:tower_top
exits=in:cottage,out:village_square
```

---

### 3. items.ini - Item Definitions

**Purpose:** Define all items in the game.

**Section Format:** `[ITEM:item_id]`

**Example:**
```ini
# Holy Hand Grenade of Antioch
[ITEM:holy_hand_grenade]
name=Holy Hand Grenade of Antioch
short_name=grenade
description=A sacred weapon blessed by Saint Attila.
examine_text=|The Holy Hand Grenade glows with divine power.
|Instructions on the side read: "First shalt thou take out the Holy Pin.
|Then shalt thou count to three, no more, no less."
weight=3
takeable=true
quest_item=true
use_script=holy_hand_grenade_use
use_consumable=false
initial_location=museum
tags=weapon,holy,explosive

# Rusty Sword
[ITEM:rusty_sword]
name=Rusty Sword
short_name=sword
description=A sword that has seen better days. Many better days.
examine_text=The blade is more rust than metal. It's a wonder it hasn't crumbled.
weight=5
takeable=true
quest_item=false
use_script=none
attack_bonus=1
tags=weapon,melee,useless

# Wooden Throne (not takeable)
[ITEM:wooden_throne]
name=Wooden Throne
short_name=throne
description=A disappointing throne with visible wear.
examine_text=|Upon closer inspection, this throne appears to be made of cheap pine.
|There's a distinct butt-groove worn into the seat.
weight=200
takeable=false
initial_location=throne_room
tags=furniture,fixed
```

**Field Definitions:**

**Required Fields:**
- `name` (string) - Full item name
- `description` (string/multiline) - Brief description (for LOOK)
- `weight` (int) - Item weight (for inventory management)
- `takeable` (bool) - Can player take this item?

**Optional Fields:**
- `short_name` (string) - Shorter name for commands (default: same as name)
- `examine_text` (multiline) - Detailed description (for EXAMINE)
- `quest_item` (bool) - Is this required for a quest? (default: false)
- `use_script` (script_name) - Script to run when used (default: none)
- `use_consumable` (bool) - Item consumed on use? (default: false)
- `use_target` (item_id) - Must be used ON another item/NPC
- `initial_location` (room_id) - Starting room (default: none/in inventory)
- `combine_with` (item_id) - Can combine with another item
- `combine_result` (item_id) - Result of combination
- `attack_bonus` (int) - Combat bonus if used as weapon (default: 0)
- `defense_bonus` (int) - Combat bonus if used as armor (default: 0)
- `tags` (list) - Arbitrary tags

**Special Values:**
- `use_script=none` - Item has no use function
- `initial_location=player` - Starts in player inventory
- `initial_location=nowhere` - Not placed in world initially

---

### 4. npcs.ini - NPC Definitions

**Purpose:** Define all non-player characters.

**Section Format:** `[NPC:npc_id]`

**Example:**
```ini
# King Blörgenstein
[NPC:king_blorgen]
name=King Blörgenstein
short_name=king
description=A bored-looking monarch with a gravy stain on his tunic.
greeting_dialog=king_greeting_1
location=throne_room
moveable=false
friendly=true
quest_giver=main_quest
tags=royalty,important

# Killer Rabbit of Caerbannog
[NPC:killer_rabbit]
name=Killer Rabbit of Caerbannog
short_name=rabbit
description=|An adorable white rabbit with big floppy ears.
|Its eyes glow red when it detects movement.
greeting_dialog=rabbit_attack
location=cave_caerbannog
moveable=false
friendly=false
hostile=true
attack_script=killer_rabbit_attack
health=100
tags=monster,dangerous,cute

# Brother Maynard
[NPC:brother_maynard]
name=Brother Maynard
short_name=maynard
description=A cheerful monk running a surprisingly commercial operation.
greeting_dialog=maynard_welcome
location=grenade_museum
moveable=false
friendly=true
merchant=true
inventory=postcard,fridge_magnet,t_shirt
tags=merchant,monk
```

**Field Definitions:**

**Required Fields:**
- `name` (string) - Full NPC name
- `description` (string/multiline) - NPC description
- `location` (room_id) - Starting location

**Optional Fields:**
- `short_name` (string) - Shorter name for commands
- `greeting_dialog` (dialog_id) - Dialog shown when talked to (default: generic)
- `moveable` (bool) - Can NPC move between rooms? (default: false)
- `movement_script` (script_name) - Controls NPC movement
- `friendly` (bool) - Is NPC friendly? (default: true)
- `hostile` (bool) - Will NPC attack on sight? (default: false)
- `attack_script` (script_name) - Combat behavior
- `health` (int) - Health points (default: 10)
- `quest_giver` (quest_id) - Quest this NPC gives
- `merchant` (bool) - Can trade with this NPC? (default: false)
- `inventory` (list of item_id) - Items NPC has (for trading/stealing)
- `tags` (list) - Arbitrary tags

---

### 5. dialogs.ini - Dialog Trees

**Purpose:** Define all dialog interactions with NPCs.

**Section Format:** `[DIALOG:dialog_id]`

**Example:**
```ini
# King's opening dialog
[DIALOG:king_greeting_1]
speaker=King Blörgenstein
text=|Right, you there! Sir... uh... Galahad the... Confused, is it?
color=cyan
responses=1:Yes, sire.|2:No, I'm someone else.
next=1:king_quest_start|2:king_confused
state_required=0

# Player confirms identity
[DIALOG:king_quest_start]
speaker=King Blörgenstein
text=|The Holy Gravy Boat has been stolen! Do you know what this means?!
color=cyan
responses=1:That we can't have gravy?|2:I have no idea, sire.
next=1:king_quest_explain|2:king_quest_explain
set_state=1

# King explains quest
[DIALOG:king_quest_explain]
speaker=King Blörgenstein
text=|PRECISELY! Well, we can, but it tastes wrong. WRONG, I SAY! You must retrieve it!
color=cyan
responses=1:I'll do my best.|2:Where is it?
next=1:king_quest_accepted|2:king_no_idea
quest_action=start:main_quest

# King doesn't know where it is
[DIALOG:king_no_idea]
speaker=King Blörgenstein
text=|How should I know?! That's why I'm sending YOU! Now off with you!
color=cyan
auto_continue=king_quest_accepted

# Quest accepted
[DIALOG:king_quest_accepted]
speaker=King Blörgenstein
text=Take that coconut-clapping fellow. What's his name? Patsy. Yes, take him.
color=cyan
responses=1:Thank you, sire.|2:Can I have some money?
next=1:dialog_end|2:king_no_money
quest_action=accept:main_quest
```

**Field Definitions:**

**Required Fields:**
- `speaker` (string) - Who is speaking (NPC name or "Player")
- `text` (multiline) - Dialog text

**Optional Fields:**
- `color` (color_name) - Text color (default: cyan for NPCs, white for player)
- `responses` (list of num:text) - Player response options
- `next` (list of num:dialog_id) - Next dialog based on response
- `auto_continue` (dialog_id) - Automatically continue to this dialog
- `state_required` (int) - NPC must be in this dialog state (default: any)
- `set_state` (int) - Set NPC dialog state after this dialog
- `quest_action` (action:quest_id) - Quest action to perform
- `item_required` (item_id) - Player must have this item
- `item_given` (item_id) - NPC gives this item
- `item_taken` (item_id) - NPC takes this item
- `script` (script_name) - Run script during this dialog
- `condition` (condition_expr) - Conditional display (advanced)

**Valid Colors:**
- `red`, `green`, `yellow`, `blue`, `magenta`, `cyan`, `white`
- `bright_red`, `bright_green`, etc.

**Quest Actions:**
- `start:quest_id` - Start a quest
- `accept:quest_id` - Player accepts quest
- `complete:quest_id` - Complete quest
- `fail:quest_id` - Fail quest

**Special Dialog IDs:**
- `dialog_end` - End dialog, return to game
- `dialog_repeat` - Repeat current dialog

---

### 6. quests.ini - Quest Definitions

**Purpose:** Define all quests and objectives.

**Section Format:** `[QUEST:quest_id]`

**Example:**
```ini
# Main quest
[QUEST:main_quest]
name=Retrieve the Holy Gravy Boat
short_name=Main Quest
description=|The king has tasked you with recovering the Holy Gravy Boat
|from the Castle of Excessive Bureaucracy.
quest_giver=king_blorgen
start_dialog=king_quest_start
required_items=gravy_boat
required_quests=rabbit_quest,knights_quest,museum_quest,curry_quest,dance_quest
completion_check=script:check_main_quest
reward_items=none
reward_score=1000
reward_text=|The kingdom rejoices! The gravy tastes slightly less off!
|You are hailed as a hero! Mostly because you were the only one who tried.

# Defeat the Killer Rabbit
[QUEST:rabbit_quest]
name=Defeat the Killer Rabbit
description=Use the Holy Hand Grenade to deal with the Killer Rabbit.
required_items=holy_hand_grenade
completion_check=script:check_rabbit_defeated
reward_items=password_nibble
reward_score=200

# Satisfy the Knights Who Say Ekki-ekki
[QUEST:knights_quest]
name=Bring the Knights a Shrubbery
description=|The Knights Who Say Ekki-ekki-ekki-ptang-zoom-boing demand
|a shrubbery. A nice one.
required_items=nice_shrubbery
completion_check=script:check_shrubbery_quality
reward_items=password_ni
reward_score=150
```

**Field Definitions:**

**Required Fields:**
- `name` (string) - Quest name
- `description` (multiline) - Quest description

**Optional Fields:**
- `short_name` (string) - Abbreviated name (default: same as name)
- `quest_giver` (npc_id) - NPC who gives this quest
- `start_dialog` (dialog_id) - Dialog that starts quest
- `required_items` (list of item_id) - Items needed to complete
- `required_quests` (list of quest_id) - Other quests that must be done first
- `completion_check` (script_name) - Script to check if complete
- `reward_items` (list of item_id) - Items given on completion
- `reward_score` (int) - Score awarded (default: 0)
- `reward_text` (multiline) - Text shown on completion
- `failure_possible` (bool) - Can quest be failed? (default: false)
- `failure_condition` (script_name) - Script to check for failure
- `time_limit` (int) - Turn limit (default: none)
- `hidden` (bool) - Hidden until discovered (default: false)

---

### 7. scripts.ini - Script Configurations

**Purpose:** Configure hardcoded scripts (custom puzzle logic).

**Section Format:** `[SCRIPT:script_name]`

**Example:**
```ini
# Holy Hand Grenade usage
[SCRIPT:holy_hand_grenade_use]
type=item_use
description=Use the Holy Hand Grenade on the Killer Rabbit
target_required=killer_rabbit
success_text=|And the Lord did grin, and the people did feast upon the lambs and sloths...
|[BOOM!] The rabbit is destroyed!
failure_text=You must count to three! Not five! THREE!
remove_item=true
kill_target=true

# Killer Rabbit attack
[SCRIPT:killer_rabbit_attack]
type=combat
description=The rabbit attacks!
damage=9999
death_text=|The rabbit's got a vicious streak a mile wide!
|[CHOMP] You have died. The rabbit returns to washing its whiskers.
respawn_location=forest_entrance

# Dance challenge
[SCRIPT:dance_challenge]
type=mini_game
description=Interpretive dance battle with Tim the Enchanter
difficulty=medium
success_reward=password_boom
failure_penalty=death
failure_text=|Your terrible dancing opens a portal to the anti-dance dimension!
|[SUCKED IN] You have died.

# Curry challenge
[SCRIPT:curry_challenge]
type=multi_choice
description=Survive the Beast's deadly curry
choices=1:Drink water|2:Drink milk|3:Keep eating|4:Give up
correct_choice=2
failure_choices=1,4
death_text=FOOL! Everyone knows milk is for spice! [FLAMES] You have died.
success_text=The Beast is impressed! You've survived his curry!
success_reward=password_spicy
```

**Field Definitions:**

**Required Fields:**
- `type` (string) - Script type
- `description` (string) - What this script does

**Optional Fields (depend on type):**
- `target_required` (item_id/npc_id) - Must be used on this target
- `success_text` (multiline) - Text shown on success
- `failure_text` (multiline) - Text shown on failure
- `remove_item` (bool) - Remove item after use
- `kill_target` (bool) - Remove target after use
- `damage` (int) - Damage dealt
- `death_text` (multiline) - Text shown on player death
- `respawn_location` (room_id) - Where to respawn
- `difficulty` (easy/medium/hard) - Puzzle difficulty
- `choices` (list of num:text) - Multiple choice options
- `correct_choice` (int) - Correct choice number
- `failure_choices` (list of int) - Wrong choice numbers
- `success_reward` (item_id) - Item given on success
- `failure_penalty` (death/damage/item_loss) - What happens on failure

**Script Types:**
- `item_use` - Custom item usage
- `combat` - Combat behavior
- `mini_game` - Interactive puzzle
- `multi_choice` - Multiple choice challenge
- `puzzle` - General puzzle logic
- `trigger` - Room/event trigger

---

## VALIDATION RULES

### Cross-Reference Validation

The story validator checks:

1. **Room exits** point to valid room IDs
2. **Items in rooms** reference valid item IDs
3. **NPCs in rooms** reference valid NPC IDs
4. **NPC locations** reference valid room IDs
5. **NPC dialogs** reference valid dialog IDs
6. **Dialog next** references point to valid dialog IDs
7. **Quest items** reference valid item IDs
8. **Quest givers** reference valid NPC IDs
9. **Script targets** reference valid items/NPCs
10. **Item locations** reference valid room IDs

### Data Validation

1. **Weights** must be positive integers
2. **Boolean fields** must be true/false/yes/no/1/0
3. **Required fields** must be present
4. **IDs must be unique** within their type
5. **IDs must be valid** (alphanumeric, underscores, hyphens only)
6. **Multiline text** must have at least one line
7. **Lists** must not be empty if field is required
8. **Numeric ranges** must be valid (health > 0, etc.)

### Logical Validation

1. **Start room** must exist
2. **At least one room** must be defined
3. **Quest chains** must not be circular
4. **Dialog trees** must not have dead ends (unless dialog_end)
5. **Items** referenced in quests must be obtainable
6. **Locked rooms** must have a way to unlock

---

## BEST PRACTICES

### Naming Conventions

**IDs:**
- Use lowercase with underscores: `throne_room`, `rusty_sword`
- Descriptive: `holy_hand_grenade` not `item_42`
- Consistent prefixes if helpful: `quest_main`, `dialog_king_1`

**Displayed Names:**
- Use proper capitalization: "Throne Room", "Rusty Sword"
- Be consistent in style

### Organization

**File Organization:**
- Group related items in comments
- Use blank lines between sections
- Order logically (rooms by region, items by type)

**Example:**
```ini
##################################################
# CASTLE BLÖRGENSTEIN - Starting Area
##################################################

[ROOM:throne_room]
# ... fields ...

[ROOM:great_hall]
# ... fields ...

[ROOM:courtyard]
# ... fields ...

##################################################
# VILLAGE AREA
##################################################

[ROOM:village_square]
# ... fields ...
```

### Text Content

**Descriptions:**
- Keep room descriptions 2-4 sentences
- Be evocative but concise
- Use humor where appropriate
- Test for readability

**Dialog:**
- Keep responses under 80 characters if possible
- Number responses clearly
- Be consistent with character voice
- Test dialog trees thoroughly

### Testing

**Start Small:**
- Create minimal test story first
- Add complexity gradually
- Test each section independently
- Validate frequently

**Test Thoroughly:**
- Walk through all rooms
- Try all items
- Talk to all NPCs
- Complete all quests
- Try to break it

---

## ERROR MESSAGES

### Parse Errors

**Syntax Error:**
```
ERROR in rooms.ini, line 42:
Expected '=' in key-value pair
Line: "exits north:great_hall,east:treasury"
      ^
Should be: "exits=north:great_hall,east:treasury"
```

**Invalid Section:**
```
ERROR in items.ini, line 10:
Invalid section header format
Line: "[ITEM rusty_sword]"
Should be: "[ITEM:rusty_sword]"
```

### Validation Errors

**Broken Reference:**
```
ERROR: Room 'throne_room' exit points to non-existent room 'great_hallway'
Did you mean 'great_hall'?
```

**Missing Required Field:**
```
ERROR: Item 'rusty_sword' missing required field 'weight'
```

**Duplicate ID:**
```
ERROR: Duplicate room ID 'throne_room' found at:
  - Line 10 in rooms.ini
  - Line 150 in rooms.ini
```

---

## EXAMPLE MINIMAL STORY

### test-story/story.ini

```ini
[STORY]
title=Test Adventure
author=Engine Team
version=0.1.0
description=A minimal test story for development.
start_room=entrance

[FILES]
rooms=rooms.ini
items=items.ini
npcs=npcs.ini
dialogs=dialogs.ini
```

### test-story/rooms.ini

```ini
[ROOM:entrance]
name=Cave Entrance
description=You stand at the entrance to a dark cave. Light filters in from outside.
exits=north:dark_room,south:exit

[ROOM:dark_room]
name=Dark Room
description=A dark room. You can barely see.
exits=south:entrance
items=sword
dark=true

[ROOM:exit]
name=Cave Exit
description=You've found the exit! Sunlight beckons.
exits=north:entrance
```

### test-story/items.ini

```ini
[ITEM:sword]
name=Old Sword
description=An old sword, rusty but serviceable.
weight=5
takeable=true
initial_location=dark_room

[ITEM:torch]
name=Torch
description=A lit torch that provides light.
weight=2
takeable=true
initial_location=player
```

### test-story/npcs.ini

```ini
[NPC:guard]
name=Cave Guard
description=A stern-looking guard blocks your path.
location=entrance
greeting_dialog=guard_greeting
```

### test-story/dialogs.ini

```ini
[DIALOG:guard_greeting]
speaker=Cave Guard
text=Halt! Who goes there?
responses=1:A friend.|2:None of your business!
next=1:guard_friendly|2:guard_hostile

[DIALOG:guard_friendly]
speaker=Cave Guard
text=Very well. Pass, friend.
responses=1:Thank you.
next=1:dialog_end

[DIALOG:guard_hostile]
speaker=Cave Guard
text=Then you shall not pass!
responses=1:Sorry, sorry!
next=1:guard_greeting
```

---

## VERSION HISTORY

### Version 1.0 (November 21, 2025)
- Initial specification
- INI-style format defined
- All core section types documented
- Validation rules established

### Future Versions
- 1.1: Add conditional expressions
- 1.2: Add variable system
- 2.0: Add embedded scripting language support

---

## MIGRATION GUIDE

### From Hardcoded to Data Files

**Step 1:** Extract room data from C structs to `rooms.ini`
**Step 2:** Extract item data from C arrays to `items.ini`
**Step 3:** Extract NPC data to `npcs.ini`
**Step 4:** Extract dialog text to `dialogs.ini`
**Step 5:** Define quests in `quests.ini`
**Step 6:** Configure scripts in `scripts.ini`
**Step 7:** Create `story.ini` with metadata
**Step 8:** Validate with story-validator tool
**Step 9:** Test in engine
**Step 10:** Iterate and fix issues

---

## TOOLS SUPPORT

### story-validator

Command-line tool to validate story files:

```bash
$ story-validator stories/gravy-boat/

Validating story: Quest for the Holy Gravy Boat
✓ story.ini loaded
✓ rooms.ini loaded (35 rooms)
✓ items.ini loaded (42 items)
✓ npcs.ini loaded (18 NPCs)
✓ dialogs.ini loaded (127 dialogs)
✓ quests.ini loaded (5 quests)
✓ scripts.ini loaded (12 scripts)

Validation checks:
✓ All room exits valid
✓ All item references valid
✓ All NPC locations valid
✓ All dialog chains valid
✓ All quest items obtainable
✗ Warning: Room 'secret_room' not reachable from start

1 warning, 0 errors
Story is playable but may have unreachable content.
```

---

## APPENDIX: Complete Field Reference

### [ROOM] Fields
| Field | Type | Required | Default | Description |
|-------|------|----------|---------|-------------|
| name | string | Yes | - | Full room name |
| short_name | string | No | name | Short name |
| description | multiline | Yes | - | Room description |
| exits | list | Yes | - | Available exits |
| items | list | No | empty | Items in room |
| npcs | list | No | empty | NPCs in room |
| visited | bool | No | false | Been here before |
| first_visit_text | multiline | No | - | First visit message |
| dark | bool | No | false | Requires light |
| locked | bool | No | false | Requires unlock |
| lock_item | item_id | No | - | Key item |
| lock_script | script | No | - | Unlock script |
| tags | list | No | empty | Tags |

### [ITEM] Fields
| Field | Type | Required | Default | Description |
|-------|------|----------|---------|-------------|
| name | string | Yes | - | Item name |
| short_name | string | No | name | Short name |
| description | string | Yes | - | Brief description |
| examine_text | multiline | No | description | Detailed description |
| weight | int | Yes | - | Item weight |
| takeable | bool | Yes | - | Can be taken |
| quest_item | bool | No | false | Quest critical |
| use_script | script | No | none | Use behavior |
| use_consumable | bool | No | false | Consumed on use |
| use_target | id | No | - | Required target |
| initial_location | room_id | No | - | Starting location |
| combine_with | item_id | No | - | Combine target |
| combine_result | item_id | No | - | Combination result |
| attack_bonus | int | No | 0 | Attack modifier |
| defense_bonus | int | No | 0 | Defense modifier |
| tags | list | No | empty | Tags |

### [NPC] Fields
| Field | Type | Required | Default | Description |
|-------|------|----------|---------|-------------|
| name | string | Yes | - | NPC name |
| short_name | string | No | name | Short name |
| description | multiline | Yes | - | NPC description |
| greeting_dialog | dialog_id | No | - | Initial dialog |
| location | room_id | Yes | - | Starting room |
| moveable | bool | No | false | Can move |
| movement_script | script | No | - | Movement AI |
| friendly | bool | No | true | Friendly |
| hostile | bool | No | false | Attacks on sight |
| attack_script | script | No | - | Combat behavior |
| health | int | No | 10 | Health points |
| quest_giver | quest_id | No | - | Quest offered |
| merchant | bool | No | false | Can trade |
| inventory | list | No | empty | Items owned |
| tags | list | No | empty | Tags |

### [DIALOG] Fields
| Field | Type | Required | Default | Description |
|-------|------|----------|---------|-------------|
| speaker | string | Yes | - | Who speaks |
| text | multiline | Yes | - | Dialog text |
| color | color | No | cyan | Text color |
| responses | list | No | - | Player choices |
| next | list | No | - | Next dialog |
| auto_continue | dialog_id | No | - | Auto-continue |
| state_required | int | No | any | Required state |
| set_state | int | No | - | New state |
| quest_action | action | No | - | Quest action |
| item_required | item_id | No | - | Required item |
| item_given | item_id | No | - | Given item |
| item_taken | item_id | No | - | Taken item |
| script | script | No | - | Run script |

### [QUEST] Fields
| Field | Type | Required | Default | Description |
|-------|------|----------|---------|-------------|
| name | string | Yes | - | Quest name |
| short_name | string | No | name | Short name |
| description | multiline | Yes | - | Quest description |
| quest_giver | npc_id | No | - | NPC giver |
| start_dialog | dialog_id | No | - | Start dialog |
| required_items | list | No | empty | Required items |
| required_quests | list | No | empty | Prerequisite quests |
| completion_check | script | No | - | Check script |
| reward_items | list | No | empty | Reward items |
| reward_score | int | No | 0 | Score reward |
| reward_text | multiline | No | - | Victory text |
| failure_possible | bool | No | false | Can fail |
| failure_condition | script | No | - | Fail check |
| time_limit | int | No | none | Turn limit |
| hidden | bool | No | false | Hidden quest |

---

**END OF SPECIFICATION**

*This document will evolve as the engine develops. Maintain backward compatibility when adding new features.*
