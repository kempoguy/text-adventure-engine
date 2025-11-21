# TEXT ADVENTURE ENGINE - PROJECT FILE STRUCTURE
## Platform Architecture (Multi-Story Support)

**Version:** 2.0  
**Date:** November 21, 2025  
**Architecture:** Engine + Story Data Files

---

## COMPLETE DIRECTORY STRUCTURE

```
text-adventure-engine/              # Project root (renamed from quest-for-gravy-boat)
│
├── .git/                           # Git repository
├── .gitignore                      # Git ignore rules
│
├── README.md                       # Project overview
├── LICENSE                         # License file (MIT suggested)
├── CHANGELOG.md                    # Version history
│
├── docs/                           # Documentation
│   ├── ENGINE.md                   # Engine architecture and design
│   ├── STORY-FORMAT.md             # Story file format specification
│   ├── CREATING-STORIES.md         # Guide for story creators
│   ├── API.md                      # Engine API reference
│   ├── BUILDING.md                 # Build instructions
│   └── DEVELOPMENT.md              # Development notes and TODOs
│
├── engine/                         # Engine source code (compiled)
│   ├── src/
│   │   ├── main.c                  # Entry point, story selection menu
│   │   ├── main.h                  # Main header
│   │   │
│   │   ├── core/                   # Core game engine systems
│   │   │   ├── game.c              # Game state management
│   │   │   ├── game.h
│   │   │   ├── parser.c            # Command parsing
│   │   │   ├── parser.h
│   │   │   ├── commands.c          # Command execution (GO, TAKE, etc.)
│   │   │   ├── commands.h
│   │   │   ├── utils.c             # String utilities, helpers
│   │   │   └── utils.h
│   │   │
│   │   ├── world/                  # Game world systems
│   │   │   ├── rooms.c             # Room management, navigation
│   │   │   ├── rooms.h
│   │   │   ├── items.c             # Item system
│   │   │   ├── items.h
│   │   │   ├── inventory.c         # Player inventory management
│   │   │   ├── inventory.h
│   │   │   ├── npcs.c              # NPC system
│   │   │   └── npcs.h
│   │   │
│   │   ├── gameplay/               # Gameplay features
│   │   │   ├── quests.c            # Quest tracking and logic
│   │   │   ├── quests.h
│   │   │   ├── combat.c            # Combat system
│   │   │   ├── combat.h
│   │   │   ├── puzzles.c           # Puzzle logic
│   │   │   ├── puzzles.h
│   │   │   ├── dialog.c            # Dialog system
│   │   │   └── dialog.h
│   │   │
│   │   ├── ui/                     # User interface
│   │   │   ├── display.c           # Screen management, output
│   │   │   ├── display.h
│   │   │   ├── colors.c            # ANSI color system
│   │   │   ├── colors.h
│   │   │   ├── screen.c            # Split-screen interface
│   │   │   ├── screen.h
│   │   │   ├── menu.c              # Menu system (story selection)
│   │   │   └── menu.h
│   │   │
│   │   ├── story/                  # NEW: Story loading and management
│   │   │   ├── loader.c            # Story file parser
│   │   │   ├── loader.h
│   │   │   ├── manager.c           # Story management (scan, select)
│   │   │   ├── manager.h
│   │   │   ├── story.h             # Story data structures
│   │   │   ├── validator.c         # Story validation
│   │   │   ├── validator.h
│   │   │   ├── scripts.c           # Script system (hardcoded scripts)
│   │   │   └── scripts.h
│   │   │
│   │   └── system/                 # System-level features
│   │       ├── save.c              # Save/load system
│   │       ├── save.h
│   │       ├── platform.c          # Platform-specific code
│   │       └── platform.h
│   │
│   ├── include/                    # Public headers
│   │   └── adventure_engine.h      # Main public API header
│   │
│   ├── build/                      # Build output (gitignored)
│   │   ├── debug/
│   │   ├── release/
│   │   └── obj/
│   │
│   └── CMakeLists.txt              # CMake configuration for engine
│
├── stories/                        # Story data files (NOT compiled)
│   │
│   ├── gravy-boat/                 # The Holy Gravy Boat story
│   │   ├── story.ini               # Main story file (metadata + references)
│   │   ├── rooms.ini               # All room definitions
│   │   ├── items.ini               # All item definitions
│   │   ├── npcs.ini                # All NPC definitions
│   │   ├── dialogs.ini             # All dialog trees
│   │   ├── quests.ini              # All quest definitions
│   │   ├── scripts.ini             # Script references/configs
│   │   ├── README.md               # Story documentation
│   │   └── WALKTHROUGH.md          # Solution guide (spoilers)
│   │
│   ├── test-story/                 # Simple test story for development
│   │   ├── story.ini               # Minimal story (3 rooms, 2 items)
│   │   └── README.md               # Test story notes
│   │
│   └── story-template/             # Template for creating new stories
│       ├── story.ini               # Template with examples
│       ├── rooms.ini               # Example room definitions
│       ├── items.ini               # Example item definitions
│       ├── npcs.ini                # Example NPC definitions
│       ├── dialogs.ini             # Example dialog trees
│       ├── quests.ini              # Example quest definitions
│       └── HOWTO.md                # Story creation guide
│
├── saves/                          # Save game files (organized by story)
│   ├── gravy-boat/
│   │   ├── slot1.sav
│   │   ├── slot2.sav
│   │   └── slot3.sav
│   └── test-story/
│       └── slot1.sav
│
├── tools/                          # Story creation and validation tools
│   ├── story-validator/            # Story file validator
│   │   ├── validator.c
│   │   └── CMakeLists.txt
│   │
│   ├── story-converter/            # Format converter (optional)
│   │   ├── converter.c
│   │   └── CMakeLists.txt
│   │
│   └── map-generator/              # Generate visual maps (optional)
│       ├── mapgen.c
│       └── CMakeLists.txt
│
├── tests/                          # Unit tests
│   ├── test_parser.c               # Parser tests
│   ├── test_loader.c               # Story loader tests
│   ├── test_inventory.c            # Inventory tests
│   ├── test_rooms.c                # Room navigation tests
│   ├── test_validator.c            # Story validation tests
│   └── run_tests.c                 # Test runner
│
├── scripts/                        # Build and utility scripts
│   ├── build_windows.bat           # Windows build script
│   ├── build_linux.sh              # Linux build script
│   ├── clean.bat                   # Windows clean script
│   ├── clean.sh                    # Linux clean script
│   ├── run_validator.bat           # Run story validator (Windows)
│   ├── run_validator.sh            # Run story validator (Linux)
│   └── package.sh                  # Create release package
│
├── assets/                         # Additional assets
│   ├── ascii_art.txt               # ASCII art for title screen
│   └── credits.txt                 # Credits file
│
└── CMakeLists.txt                  # Root CMake configuration
```

---

## KEY DIRECTORY PURPOSES

### `/engine/` - The Game Engine (Compiled Code)

**Purpose:** Contains all C source code that compiles into the game engine executable.

**What goes here:**
- Game mechanics (parser, commands, combat)
- UI systems (display, colors, menus)
- World management (rooms, items, NPCs)
- Story loading and validation
- Save/load system
- Platform abstraction

**What does NOT go here:**
- Actual story content
- Room descriptions
- Dialog text
- Quest definitions

### `/stories/` - Story Content (Data Files)

**Purpose:** Contains all story data files that are loaded at runtime.

**What goes here:**
- Story metadata (title, author, version)
- Room definitions and descriptions
- Item definitions
- NPC definitions and dialog
- Quest definitions
- Script configuration

**File Format:** INI-style text files (see STORY-FORMAT.md)

**Structure per story:**
```
story-name/
├── story.ini      # Main file (metadata + file references)
├── rooms.ini      # All rooms
├── items.ini      # All items
├── npcs.ini       # All NPCs
├── dialogs.ini    # All dialog trees
├── quests.ini     # All quests
└── scripts.ini    # Script configs
```

### `/saves/` - Save Game Files

**Purpose:** Stores player save games, organized by story.

**Organization:**
- Each story gets its own subdirectory
- Save files named `slot1.sav`, `slot2.sav`, `slot3.sav`
- Engine detects story and saves to correct directory

**Format:** Binary or text format (your choice)

### `/tools/` - Development Tools

**Purpose:** Command-line tools for story creation and validation.

**Tools:**
1. **story-validator** - Validates story files for errors
2. **story-converter** - Converts between formats (optional)
3. **map-generator** - Creates visual map from room data (optional)

### `/docs/` - Documentation

**Purpose:** All project documentation.

**Key Documents:**
- **ENGINE.md** - Architecture and design decisions
- **STORY-FORMAT.md** - Complete file format specification
- **CREATING-STORIES.md** - Guide for story creators
- **API.md** - Engine API for script integration
- **BUILDING.md** - Build instructions
- **DEVELOPMENT.md** - TODOs and development notes

---

## NEW SOURCE FILES (Story System)

### `engine/src/story/loader.c` and `loader.h`

**Purpose:** Parse story files and load into memory structures.

**Key Functions:**
```c
// Load entire story from directory
Story* load_story(const char* story_dir);

// Load individual file types
int load_story_metadata(const char* filepath, StoryMetadata* meta);
int load_rooms(const char* filepath, Room** rooms, int* count);
int load_items(const char* filepath, Item** items, int* count);
int load_npcs(const char* filepath, NPC** npcs, int* count);
int load_dialogs(const char* filepath, Dialog** dialogs, int* count);
int load_quests(const char* filepath, Quest** quests, int* count);

// Parsing helpers
char* parse_multiline_text(FILE* fp);
int parse_exit_list(const char* exit_str, Exit* exits, int max_exits);
int parse_string_list(const char* str, char** list, int max_items);

// Cleanup
void free_story(Story* story);
```

**Error Handling:**
- File not found
- Parse errors (invalid syntax)
- Memory allocation failures
- Invalid data (negative weights, etc.)

### `engine/src/story/manager.c` and `manager.h`

**Purpose:** Manage available stories, story selection.

**Key Functions:**
```c
// Initialize story system
void story_manager_init(const char* stories_dir);

// Scan for available stories
int scan_stories(StoryInfo** story_list);

// Display story selection menu
Story* select_story_interactive(void);

// Get story info without loading full story
StoryInfo* get_story_info(const char* story_dir);

// Cleanup
void story_manager_cleanup(void);
```

### `engine/src/story/story.h`

**Purpose:** Define all story-related data structures.

**Key Structures:**
```c
// Story metadata
typedef struct {
    char title[128];
    char author[64];
    char version[16];
    char description[512];
    int start_room_id;
    int max_inventory_weight;
    int victory_score;
} StoryMetadata;

// Complete story package
typedef struct {
    StoryMetadata metadata;
    
    // Content arrays
    Room* rooms;
    int room_count;
    
    Item* items;
    int item_count;
    
    NPC* npcs;
    int npc_count;
    
    Dialog* dialogs;
    int dialog_count;
    
    Quest* quests;
    int quest_count;
    
    // Lookup tables (for O(1) access)
    // Implementation: hash table or sorted array with binary search
    void* room_lookup;
    void* item_lookup;
    void* npc_lookup;
    void* dialog_lookup;
    
    // File paths
    char story_dir[256];
    
} Story;

// Story info (for menu display, without loading full story)
typedef struct {
    char title[128];
    char author[64];
    char version[16];
    char description[512];
    char directory[256];
    int room_count;
    int estimated_playtime;  // minutes
} StoryInfo;
```

### `engine/src/story/validator.c` and `validator.h`

**Purpose:** Validate story files for errors and consistency.

**Key Functions:**
```c
// Validate entire story
bool validate_story(Story* story, ValidationReport* report);

// Specific validation checks
bool validate_room_exits(Story* story);      // All exits point to valid rooms
bool validate_item_references(Story* story); // Items exist when referenced
bool validate_npc_locations(Story* story);   // NPCs placed in valid rooms
bool validate_dialog_chains(Story* story);   // Dialog trees are complete
bool validate_quest_items(Story* story);     // Quest items exist

// Report generation
void print_validation_report(ValidationReport* report);
void save_validation_report(ValidationReport* report, const char* filepath);
```

**Validation Checks:**
- Room exits point to valid room IDs
- Items referenced in rooms exist
- NPCs have valid starting locations
- Dialog chains don't have dead ends
- Quest requirements reference valid items
- No duplicate IDs
- Required fields are present
- Text lengths within limits

### `engine/src/story/scripts.c` and `scripts.h`

**Purpose:** Hardcoded script functions that stories can reference.

**Key Functions:**
```c
// Script registration
void register_builtin_scripts(void);
void register_script(const char* name, ScriptFunction func);

// Script execution
int execute_script(const char* script_name, ScriptContext* context);

// Get script by name
ScriptFunction get_script(const char* name);

// Builtin scripts for Gravy Boat story
int script_killer_rabbit_attack(ScriptContext* ctx);
int script_holy_hand_grenade(ScriptContext* ctx);
int script_dance_challenge(ScriptContext* ctx);
int script_curry_challenge(ScriptContext* ctx);
int script_form_puzzle(ScriptContext* ctx);
int script_bridge_questions(ScriptContext* ctx);
int script_shrubbery_check(ScriptContext* ctx);
```

**Script Context:**
```c
typedef struct {
    GameState* game;
    Story* story;
    Room* current_room;
    Item* item;        // Item being used (if applicable)
    NPC* npc;          // NPC being interacted with
    void* custom_data; // Script-specific data
} ScriptContext;

// Script function signature
typedef int (*ScriptFunction)(ScriptContext* ctx);
```

### `engine/src/ui/menu.c` and `menu.h`

**Purpose:** Menu system for story selection and main menu.

**Key Functions:**
```c
// Display main menu
MenuChoice show_main_menu(void);

// Display story selection menu
Story* show_story_selection_menu(StoryInfo* stories, int story_count);

// Display generic menu
int show_menu(const char* title, const char** options, int option_count);

// Menu display helpers
void draw_menu_header(const char* title);
void draw_menu_option(int number, const char* text, bool selected);
void draw_menu_footer(void);
```

---

## MODIFIED MAIN FLOW

### `engine/src/main.c` - Entry Point

**New Startup Flow:**
```c
int main(int argc, char** argv) {
    // Initialize engine
    platform_init();
    display_init();
    color_init();
    
    // Initialize story system
    story_manager_init("stories/");
    
    // Main menu loop
    while (true) {
        MenuChoice choice = show_main_menu();
        
        switch (choice) {
            case MENU_NEW_GAME:
                // Scan for available stories
                StoryInfo* stories;
                int count = scan_stories(&stories);
                
                // Let player select story
                Story* story = show_story_selection_menu(stories, count);
                
                if (story) {
                    // Validate story
                    if (validate_story(story, NULL)) {
                        // Play the game
                        play_game(story);
                    } else {
                        display_error("Story validation failed!");
                    }
                    
                    // Cleanup
                    free_story(story);
                }
                break;
                
            case MENU_LOAD_GAME:
                load_and_play_saved_game();
                break;
                
            case MENU_QUIT:
                goto cleanup;
        }
    }
    
cleanup:
    story_manager_cleanup();
    platform_cleanup();
    
    return 0;
}
```

---

## STORY FILE LOCATIONS

### Gravy Boat Story Files

```
stories/gravy-boat/
├── story.ini           # Metadata and file references
├── rooms.ini           # All 35 rooms
├── items.ini           # All 40+ items
├── npcs.ini            # All 15+ NPCs
├── dialogs.ini         # All dialog trees
├── quests.ini          # All 5 main quests
├── scripts.ini         # Script configurations
├── README.md           # Story documentation
└── WALKTHROUGH.md      # Solution guide
```

### Test Story Files

```
stories/test-story/
├── story.ini           # Minimal story for testing
└── README.md           # Test notes
```

**Test Story Contents:**
- 3 rooms (Entrance, Room, Exit)
- 2 items (Key, Sword)
- 1 NPC (Guard)
- 1 simple dialog
- 1 simple quest (get key, unlock door)

**Purpose:**
- Test story loader
- Test parser
- Test game mechanics
- Fast iteration during development

---

## CMAKE STRUCTURE

### Root `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.15)
project(TextAdventureEngine C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories
add_subdirectory(engine)
add_subdirectory(tools)

# Optional: Tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

# Install targets
install(DIRECTORY stories/ DESTINATION share/adventure-engine/stories)
install(DIRECTORY docs/ DESTINATION share/doc/adventure-engine)
```

### `engine/CMakeLists.txt`

```cmake
# Collect all source files
file(GLOB_RECURSE ENGINE_SOURCES
    "src/main.c"
    "src/core/*.c"
    "src/world/*.c"
    "src/gameplay/*.c"
    "src/ui/*.c"
    "src/story/*.c"
    "src/system/*.c"
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create executable
add_executable(adventure ${ENGINE_SOURCES})

# Platform-specific libraries
if(WIN32)
    # Windows-specific
    target_link_libraries(adventure)
elseif(UNIX)
    # Linux-specific
    target_link_libraries(adventure m)
endif()

# Install
install(TARGETS adventure DESTINATION bin)
```

### `tools/CMakeLists.txt`

```cmake
# Story validator tool
add_executable(story-validator
    story-validator/validator.c
)

# Shared code from engine (loader, parser utils)
target_include_directories(story-validator PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/src
)

# Install
install(TARGETS story-validator DESTINATION bin)
```

---

## BUILD SCRIPTS

### `scripts/build_windows.bat`

```batch
@echo off
echo Building Text Adventure Engine (Windows)...

if not exist engine\build mkdir engine\build
cd engine\build

cmake -G "MinGW Makefiles" ..
cmake --build .

cd ..\..
echo.
echo Build complete!
echo Engine executable: engine\build\bin\adventure.exe
echo.
echo To run with Gravy Boat story:
echo   engine\build\bin\adventure.exe
pause
```

### `scripts/build_linux.sh`

```bash
#!/bin/bash
echo "Building Text Adventure Engine (Linux)..."

mkdir -p engine/build
cd engine/build

cmake ..
cmake --build .

cd ../..
echo
echo "Build complete!"
echo "Engine executable: engine/build/bin/adventure"
echo
echo "To run with Gravy Boat story:"
echo "  ./engine/build/bin/adventure"
```

---

## .GITIGNORE

```gitignore
# Build directories
engine/build/
tools/*/build/
bin/
obj/
*.o
*.exe
*.out
*.so
*.dll
*.dylib

# IDE files
.vscode/
.vs/
*.suo
*.user
*.swp
*~
.idea/

# OS files
.DS_Store
Thumbs.db

# Save files (optional - include if you want fresh saves)
saves/**/*.sav

# CMake generated files
CMakeCache.txt
CMakeFiles/
cmake_install.cmake
Makefile

# Test outputs
tests/build/
test_results/

# Logs
*.log
debug.txt
```

---

## INITIAL SETUP COMMANDS

### Windows PowerShell Script

Save as `create_structure.ps1`:

```powershell
# Create main directories
$dirs = @(
    "engine/src/core",
    "engine/src/world",
    "engine/src/gameplay",
    "engine/src/ui",
    "engine/src/story",
    "engine/src/system",
    "engine/include",
    "engine/build",
    "stories/gravy-boat",
    "stories/test-story",
    "stories/story-template",
    "saves/gravy-boat",
    "saves/test-story",
    "tools/story-validator",
    "tools/story-converter",
    "tools/map-generator",
    "tests",
    "scripts",
    "assets",
    "docs"
)

foreach ($dir in $dirs) {
    New-Item -ItemType Directory -Force -Path $dir | Out-Null
}

# Create key files
$files = @(
    ".gitignore",
    "README.md",
    "LICENSE",
    "CHANGELOG.md",
    "CMakeLists.txt",
    "engine/CMakeLists.txt",
    "engine/src/main.c",
    "engine/src/main.h",
    
    # Core
    "engine/src/core/game.c",
    "engine/src/core/game.h",
    "engine/src/core/parser.c",
    "engine/src/core/parser.h",
    "engine/src/core/commands.c",
    "engine/src/core/commands.h",
    "engine/src/core/utils.c",
    "engine/src/core/utils.h",
    
    # World
    "engine/src/world/rooms.c",
    "engine/src/world/rooms.h",
    "engine/src/world/items.c",
    "engine/src/world/items.h",
    "engine/src/world/inventory.c",
    "engine/src/world/inventory.h",
    "engine/src/world/npcs.c",
    "engine/src/world/npcs.h",
    
    # Gameplay
    "engine/src/gameplay/quests.c",
    "engine/src/gameplay/quests.h",
    "engine/src/gameplay/combat.c",
    "engine/src/gameplay/combat.h",
    "engine/src/gameplay/puzzles.c",
    "engine/src/gameplay/puzzles.h",
    "engine/src/gameplay/dialog.c",
    "engine/src/gameplay/dialog.h",
    
    # UI
    "engine/src/ui/display.c",
    "engine/src/ui/display.h",
    "engine/src/ui/colors.c",
    "engine/src/ui/colors.h",
    "engine/src/ui/screen.c",
    "engine/src/ui/screen.h",
    "engine/src/ui/menu.c",
    "engine/src/ui/menu.h",
    
    # Story system (NEW)
    "engine/src/story/loader.c",
    "engine/src/story/loader.h",
    "engine/src/story/manager.c",
    "engine/src/story/manager.h",
    "engine/src/story/story.h",
    "engine/src/story/validator.c",
    "engine/src/story/validator.h",
    "engine/src/story/scripts.c",
    "engine/src/story/scripts.h",
    
    # System
    "engine/src/system/save.c",
    "engine/src/system/save.h",
    "engine/src/system/platform.c",
    "engine/src/system/platform.h",
    
    # Include
    "engine/include/adventure_engine.h",
    
    # Docs
    "docs/ENGINE.md",
    "docs/STORY-FORMAT.md",
    "docs/CREATING-STORIES.md",
    "docs/API.md",
    "docs/BUILDING.md",
    "docs/DEVELOPMENT.md",
    
    # Scripts
    "scripts/build_windows.bat",
    "scripts/build_linux.sh",
    "scripts/clean.bat",
    "scripts/clean.sh",
    "scripts/run_validator.bat",
    "scripts/run_validator.sh",
    
    # Story files
    "stories/gravy-boat/story.ini",
    "stories/gravy-boat/rooms.ini",
    "stories/gravy-boat/items.ini",
    "stories/gravy-boat/npcs.ini",
    "stories/gravy-boat/dialogs.ini",
    "stories/gravy-boat/quests.ini",
    "stories/gravy-boat/scripts.ini",
    "stories/gravy-boat/README.md",
    "stories/test-story/story.ini",
    "stories/test-story/README.md"
)

foreach ($file in $files) {
    New-Item -ItemType File -Force -Path $file | Out-Null
}

Write-Host "✓ Project structure created successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "1. Initialize Git: git init"
Write-Host "2. Create .gitignore"
Write-Host "3. Copy storyline doc to docs/"
Write-Host "4. Start with test-story for development"
```

Run with: `powershell -ExecutionPolicy Bypass -File create_structure.ps1`

---

## DEVELOPMENT WORKFLOW

### Phase 1: Foundation (Week 1)

**Goal:** Get basic story loading working

1. Create minimal test story (3 rooms, 2 items, 1 NPC)
2. Implement basic INI parser
3. Load test story into memory
4. Navigate test story
5. Verify engine is truly generic

**Files to work on:**
- `story/loader.c` - Basic parsing
- `story/story.h` - Data structures
- `main.c` - Load and run story
- `stories/test-story/story.ini` - Test content

### Phase 2: Full Parser (Week 2)

**Goal:** Complete story loading system

1. Expand parser to handle all sections
2. Add validation
3. Implement lookup tables
4. Add error handling
5. Test with larger story

**Files to work on:**
- `story/loader.c` - Complete all parse functions
- `story/validator.c` - Validation logic
- `story/manager.c` - Story scanning/selection

### Phase 3: Convert Gravy Boat (Weeks 3-4)

**Goal:** Full story playable

1. Convert rooms to data files
2. Convert items to data files
3. Convert NPCs and dialogs
4. Convert quests
5. Implement scripts
6. Test thoroughly

**Files to work on:**
- `stories/gravy-boat/*.ini` - All story data
- `story/scripts.c` - Hardcoded puzzle scripts

### Phase 4: Polish (Week 5)

**Goal:** Production ready

1. Story selection menu
2. Save/load with story awareness
3. Story validator tool
4. Documentation
5. Bug fixes

---

## KEY DIFFERENCES FROM PREVIOUS STRUCTURE

### What Changed:

1. **Project renamed**: `quest-for-gravy-boat` → `text-adventure-engine`
2. **New `/stories/` directory**: Story content separated from code
3. **New `/engine/src/story/` subsystem**: Story loading, validation, scripts
4. **New `/engine/src/ui/menu.*`**: Story selection menu
5. **Modified `/saves/` organization**: Per-story subdirectories
6. **New `/tools/` directory**: Story validation tools
7. **Modified docs**: ENGINE.md, STORY-FORMAT.md, CREATING-STORIES.md

### What Stayed the Same:

- All core engine systems (parser, commands, UI, world)
- Build system (CMake)
- Platform abstraction
- Save/load system (extended for multi-story)
- Test system

---

## NEXT STEPS

1. **Run structure creation script** on your Windows PC
2. **Create .gitignore** (content provided above)
3. **Initialize Git**: `git init`
4. **Copy storyline doc**: Move to `stories/gravy-boat/README.md`
5. **Create test story**: Simple 3-room story for initial testing
6. **Start coding**: Begin with `story/loader.c` and test story

Ready to proceed!
