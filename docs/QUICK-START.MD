# Quick Start Guide

## Building the Game

### Windows (MSYS2 UCRT64)
```bash
cd /e/projects/c-learning/text-adventure-engine
cd build
make
```

### Running
```bash
cd /e/projects/c-learning/text-adventure-engine
./build/bin/adventure.exe
```

## Playing the Game

### Available Commands

**Movement:**
- `go north` or `north` or `n` - Move north
- `go south` or `south` or `s` - Move south  
- `go east` or `east` or `e` - Move east
- `go west` or `west` or `w` - Move west

**Information:**
- `look` or `l` - Look at current room
- `help` - Show all commands

**System:**
- `quit` - Exit game

### Currently Implemented
- ✅ Story loading from files
- ✅ Room navigation
- ✅ Room descriptions
- ✅ Exit display

### Coming Soon
- ⏳ Item pickup/drop
- ⏳ Inventory management
- ⏳ NPCs and dialog
- ⏳ Quests

## Test Story

The test story has 3 rooms:
1. **Cave Entrance** - Starting location (exits: north, south)
2. **Dark Room** - Contains a sword (exits: south)
3. **Cave Exit** - Victory location (exits: north)

Try navigating between all three rooms!