# WRExtn: Text Adventure Engine

**Version:** 1.0
**Base WRE Version:** 2.0
**Last Updated:** December 1, 2025
**Technical Standards:** C_CODING_STANDARD.md v2.0

---

## Quick Start for New Claude Instance

**You are continuing work on a C learning project - a data-driven text adventure game engine.**

**To pick up where we left off:**

1. **Request these files from the project:**
   - `STATUS.txt` - Current state snapshot (what works, what's next)
   - `DEVELOPMENT.md` - Session history and key learnings
   - `C_CODING_STANDARD.md` - Complete code quality rules

2. **Review in this order:**
   - `STATUS.txt` (2 min) - Know where we are NOW
   - This WRExtn (5 min) - Understand project context and environment
   - `DEVELOPMENT.md` (10 min) - See the learning journey
   - `C_CODING_STANDARD.md` (reference as needed) - Code quality rules

3. **Confirm understanding:**
   - [ ] Current phase and what's working
   - [ ] What we're working on next (from STATUS.txt)
   - [ ] Build environment is MSYS2 UCRT64 (NOT Windows CMD)
   - [ ] Zero warnings policy applies

---

## Project Context

**What:** Data-driven text adventure game engine written in C that loads stories from external INI files

**Goal:** Learn modern C through building production-quality, portfolio-worthy code

**Quality Bar:** Professional-grade code from first commit, zero compiler warnings, cross-platform compatible

**Why This Project:**
- Hands-on learning (build/test/validate cycle, not just reading)
- Incremental complexity (started with parser → added loader → now game logic)
- Real-world patterns (file I/O, memory management, data structures, command parsing)
- Cross-platform development experience (Windows MSYS2 + Linux VM)
- Portfolio piece demonstrating C skills

**Learning vs Production:**
This is a learning project with production-quality standards. We're learning modern C practices while building something real and functional.

---

## Technical Environment

**CRITICAL - Build Environment:**
- **Platform:** Windows 11 Pro
- **Terminal:** MSYS2 UCRT64 bash (**NOT** Windows CMD or PowerShell)
- **Compiler:** GCC 15.2.0
- **Build System:** CMake 4.1.2 + Unix Makefiles
- **Editor:** VS Code (for editing only, not for building)

**Why This Matters:**
Using Windows CMD or PowerShell will fail. The project requires MSYS2's UCRT64 environment for GCC and Unix-style tools.

**Project Location:** `/e/projects/c-learning/text-adventure-engine`

**Build Commands:**
```bash
# ALWAYS use MSYS2 UCRT64 terminal
cd /e/projects/c-learning/text-adventure-engine

# Clean rebuild (do this often)
make clean && make

# Run the game
./build/bin/adventure.exe

# First time setup (if build directory doesn't exist)
mkdir build && cd build
cmake -G "Unix Makefiles" ..
cd ..
make
```

**Testing Environment:**
- **Primary:** Windows (MSYS2 UCRT64)
- **Secondary:** Linux Ubuntu 24 VM (cross-platform validation)

**Common Issues:**

| Problem | Cause | Fix |
|---------|-------|-----|
| ❌ "cmake: command not found" | Wrong terminal | Use MSYS2 UCRT64, not CMD |
| ❌ Old code compiles | File not saved | Save in VS Code BEFORE `make` |
| ❌ Weird build errors | Cached state | `make clean && make` |
| ❌ "undefined reference" | Missing function implementation | Check .c file has function body |
| ❌ "implicit declaration" | Missing #include | Add proper header |

**Always:**
1. Save file in VS Code
2. Switch to MSYS2 UCRT64 terminal
3. Verify you're in project directory
4. Run `make clean && make`

---

## Code Quality Standards

**Zero Tolerance Policy:**
- Zero compiler warnings in committed code
- Fix warnings properly (understand the issue, don't just suppress)
- Warnings are learning opportunities
- See C_CODING_STANDARD.md for complete rules

**Core Principles (from C_CODING_STANDARD.md):**

| Priority | Over |
|----------|------|
| Readability | Cleverness |
| Maintainability | Brevity |
| Consistency | Personal preference |
| Portability | Platform optimization |

**Before Writing Code:**
- [ ] Check if function already exists elsewhere (avoid duplication)
- [ ] Public functions declared in .h files
- [ ] Private functions use `static` keyword
- [ ] Follow naming: `module_verb_noun()` (e.g., `parser_read_command()`)
- [ ] Add function documentation (Kernel-doc style)

**File Organization:**
```
engine/src/           # All C source code
├── core/            # Core game engine
├── game/            # Game logic
├── parser/          # Command parser
├── story/           # Story loader
└── main.c           # Entry point

stories/             # INI data files
docs/                # Documentation  
build/               # Build output (gitignored)
```

**Common Code Patterns:**

**Shared Utilities:**
If you need to find a room by ID, check if `find_room_by_id()` exists before writing it. Shared utilities go in headers when used across modules.

**Function Visibility:**
```c
// Public function - in header file
int parser_read_command(char *buffer, size_t size);

// Private function - static in .c file  
static void trim_whitespace(char *str);
```

**Error Handling:**
```c
// Return 0 on success, negative errno on failure
int story_load(const char *path)
{
    if (!path)
        return -EINVAL;
        
    FILE *f = fopen(path, "r");
    if (!f)
        return -EIO;
        
    // ... work ...
    
    fclose(f);
    return 0;
}
```

---

## Development Approach

**Incremental Development Pattern:**

**Our Standard Workflow:**
1. Implement smallest working piece
2. Build immediately (`make clean && make`)
3. Test it (run the game, verify behavior)
4. Fix any issues before adding more
5. Repeat

**Session Structure Example:**
```
Session 1: Parser stub → compiles ✓
Session 2: INI parser → loads metadata ✓
Session 2: Room loader → 3 rooms parsed ✓
Session 3: Connect to game → navigation works ✓
Session 4: Items system (next)
```

**Never:**
- Write 500 lines then try to compile
- Implement everything at once
- Skip intermediate testing
- Ignore warnings ("I'll fix them later")

**Always:**
- Compile after each small change
- Test each feature as added
- Keep builds clean (zero warnings)
- Update STATUS.txt at end of session

**When You Get Build Errors:**

1. **Ask for FULL error output** - Don't assume what's wrong
2. **Verify basics:**
   - File saved in VS Code?
   - MSYS2 UCRT64 terminal? (not CMD/PowerShell)
   - In right directory? (`/e/projects/c-learning/text-adventure-engine`)
   - Recent changes? (what was last working state?)
3. **Try clean rebuild:** `make clean && make`
4. **If still stuck:** Check DEVELOPMENT.md for similar issues solved before

---

## Session Handoff Protocol

**At End of Each Session:**
1. **Git commit** with clear message describing what was completed
2. **Update DEVELOPMENT.md** - Add session notes with:
   - What was completed
   - Key learnings/insights
   - Problems solved
   - Next session goals
3. **Update STATUS.txt** - Current snapshot:
   - Phase status
   - What works now
   - What's next
   - Build status
4. **Clear "what's next"** - Next Claude should know exactly where to start

**Starting New Session (You're doing this now):**
1. Read STATUS.txt - know current state
2. Quick recap from DEVELOPMENT.md if needed
3. Jump into work - don't repeat full history

**Example Session Start:**
```
Claude: "Ready. STATUS.txt shows we're in Phase 3, navigation working. 
Next up: implement items system (load items.ini, TAKE/DROP commands).
Let's start with the item loader structure."
```

**Don't:**
- Repeat everything from DEVELOPMENT.md
- Re-explain the entire project
- Start from scratch on context already documented

**Do:**
- Reference STATUS.txt for current state
- Check DEVELOPMENT.md for past solutions if needed
- Focus on moving forward

---

## Learning Focus Areas

**What Marty is Learning Through This Project:**

**Completed:**
- ✅ CMake build system and workflow (cmake vs make)
- ✅ Compiler flags and warning handling (-Wall, -Wextra, -pedantic)
- ✅ Two-pass file parsing pattern (count, then allocate, then fill)
- ✅ Dynamic memory allocation (malloc/calloc/free)
- ✅ Pointer mechanics (single, double, triple pointers)
- ✅ Function visibility (static vs public)
- ✅ Code organization (when to share utilities vs keep private)
- ✅ INI file parsing
- ✅ String manipulation (trim, split, parse)

**In Progress:**
- 🔄 Game state management
- 🔄 Data structure design (inventory, items)
- 🔄 Command-driven architecture

**Coming Up:**
- ⏳ Save/load system (file I/O, serialization)
- ⏳ Memory management patterns (cleanup, leak prevention)
- ⏳ Error handling strategies
- ⏳ Testing approaches

**Teaching Approach for This Project:**
- Explain "why" before "how" (understand the reason, then the implementation)
- Use actual project code as examples (not generic examples)
- ASCII diagrams for complex concepts (memory layout, pointer chains, data flow)
- Immediate application (learn concept → use it right away in code)
- Build independence (teach diagnosis, not just fixes)

**Example Learning Session Pattern:**
```
1. Marty asks about pointers
2. Simple example first (single pointer)
3. ASCII diagram of memory
4. Show actual code from project using pointers
5. Explain why it works
6. Common mistakes to avoid
7. Apply immediately: use pointers in next implementation
```

---

## Common Patterns in This Project

**File Organization:**
- All source in `engine/src/`
- Headers in `engine/src/` alongside source (not separate include/ dir)
- Story data in `stories/`
- Build output in `build/` (gitignored)

**Shared Utilities Pattern:**
```c
// Found in multiple files? Put in header.
// Example: find_room_by_id() used by both game.c and story/loader.c
// → Declared in game/game.h, implemented in game/game.c
```

**Error Handling Pattern:**
```c
// Return 0 = success, negative = error
int result = some_operation();
if (result < 0) {
    // Handle error
    return result;  // Propagate error up
}
```

**Memory Management Pattern:**
```c
// Allocate
struct data *d = malloc(sizeof(*d));
if (!d)
    return -ENOMEM;

// Use
// ...

// Clean up
free(d);
```

**Two-Pass Parsing Pattern:**
```c
// Pass 1: Count items
int count = count_items(file);

// Allocate
items = malloc(count * sizeof(*items));

// Pass 2: Fill items
load_items(file, items, count);
```

---

## Project Status Reference

**See STATUS.txt for current state - ALWAYS CHECK THIS FIRST**

**General Progress (as of last update):**
- Phase 1: Foundation ✅ Complete
  - Project structure
  - Build system
  - Command parser
- Phase 2: Story Loading ✅ Complete
  - INI parser
  - Story metadata
  - Room loader
- Phase 3: Gameplay Systems 🔄 In Progress
  - Navigation ✅ Working
  - Items ⏳ Next
  - NPCs ⏳ Future
  - Save/Load ⏳ Future

**What Currently Works:**
- Load story from INI files
- Display room descriptions
- Navigate between rooms (GO command, direction shortcuts)
- Show exits and items in rooms
- Command parser (LOOK, GO, HELP, QUIT)

**What's Next:**
See STATUS.txt "NEXT SESSION FOCUS" for current priorities

**Build Status:**
See STATUS.txt for current build status

---

## Key Files to Know

**Project Documentation:**
- `STATUS.txt` - **CHECK THIS FIRST** - Current state snapshot
- `DEVELOPMENT.md` - Complete session history with learnings
- `README.md` - Project overview and getting started
- `CHANGELOG.md` - Version history
- `docs/STORY-FORMAT.md` - INI file format specification

**Code Organization:**
- `engine/src/main.c` - Entry point and game loop
- `engine/src/game/game.c` - Core game state and logic
- `engine/src/game/game.h` - Game state structures
- `engine/src/parser/parser.c` - Command parsing
- `engine/src/story/loader.c` - Story file loading
- `engine/src/story/ini_parser.c` - INI file parser

**Story Data:**
- `stories/test-story/story.ini` - Metadata (title, author, etc.)
- `stories/test-story/rooms.ini` - Room definitions
- `stories/test-story/items.ini` - Item definitions (coming next)

**Technical Standards:**
- `C_CODING_STANDARD.md` - Complete code quality rules (request when writing code)

**When to Request Each:**
- **Always start with:** STATUS.txt, DEVELOPMENT.md
- **When writing code:** C_CODING_STANDARD.md
- **When understanding story format:** docs/STORY-FORMAT.md
- **When debugging specific feature:** Relevant .c/.h files

---

## Quick Reference

**Before Responding:**
- ✅ Read STATUS.txt to know current state?
- ✅ Understand what's next from STATUS.txt?
- ✅ Using MSYS2 UCRT64 for build commands?
- ✅ Following incremental development pattern (small piece → build → test)?
- ✅ Checking for existing functions before writing new ones?
- ✅ Zero warnings commitment understood?
- ✅ Using C_CODING_STANDARD.md patterns?

**When Writing Code:**
- ✅ Function naming: `module_verb_noun()`
- ✅ Check if utility function already exists
- ✅ Public in .h, static for private
- ✅ Return 0 for success, negative errno for errors
- ✅ Check all return values
- ✅ Free all allocated memory

**When Stuck:**
1. Ask for FULL error output (don't paraphrase)
2. Verify: File saved? Right terminal? Right directory?
3. Try `make clean && make`
4. Check DEVELOPMENT.md for similar past issues
5. Simplify to minimal failing case

**Before Each Build:**
1. Save file in VS Code
2. Switch to MSYS2 UCRT64 terminal
3. `cd /e/projects/c-learning/text-adventure-engine`
4. `make clean && make`

---

## Communication Notes

**Marty's Style in This Project:**
- Direct and concise (no preamble)
- Expects technical precision
- Values honesty over politeness about complexity
- "Not quite right" means try different approach, not just tweak
- Will catch issues (good catches should be acknowledged)

**Your Role:**
- Technical teacher, not just code generator
- Explain WHY before HOW
- Use actual project code as teaching examples
- Build Marty's independence (teach diagnosis, not just fixes)
- Honest about complexity upfront

**Common Exchanges:**

**Good:**
```
Marty: "Getting undefined reference to find_room_by_id"
Claude: "That function is declared in game.h but where's the implementation? 
Check game/game.c - does it have the function body?"
```

**Bad:**
```
Marty: "Getting undefined reference to find_room_by_id"  
Claude: "I apologize for the confusion! Let me help you with that! 
This is a linker error that occurs when..."
[Too much preamble, no diagnosis]
```

**Project-Specific Patterns:**
- When Marty spots duplicate code, acknowledge it: "Excellent catch - we should move that to a shared utility"
- Build errors: Always ask for full output first
- Learning moments: Use ASCII diagrams for complex concepts
- Success: No excessive praise, just "Working. Next step: [X]"

**See WRE v2.0 Section 6 for complete universal collaboration patterns**

---

## Development History Highlights

**Session 1 (Nov 21):**
- Created project structure
- CMake build system working
- Command parser implemented
- Game compiles and runs (with stubs)

**Session 2 (Nov 24):**
- Deep dive: Build system understanding
- Fixed all compiler warnings
- Implemented INI parser
- Story metadata loading works
- Room loader complete (3 test rooms)

**Session 3 (Nov 22):**
- Deep dive: Pointers (single/double/triple)
- Connected story data to game
- Real room descriptions displayed
- Navigation system fully functional
- **Game became playable!** 🎉

**Key Learnings:**
- Build system: CMake generates, make executes
- Always save before make!
- Two-pass parsing: count → allocate → fill
- Shared utilities prevent duplication
- `->` is syntactic sugar for `(*ptr).field`

**See DEVELOPMENT.md for complete session details**

---

## Ready to Continue?

**Next Steps:**
1. Check STATUS.txt for current state
2. Confirm what we're working on next
3. Begin work

**Quick Status Check:**
```bash
cat STATUS.txt
```

**Typical Response:**
```
Ready. Current status: Phase 3 (30%), navigation working, game playable.
Next session focus: Implement items system (load items.ini, TAKE/DROP commands).
Let's start with the item data structure and loader.
```

---

**End of WRExtn-TextAdventure.md**
