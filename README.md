# Text Adventure Engine

A cross-platform text adventure game engine written in C that loads stories from external data files.

## Current Status

🚧 **In Development** - Phase 2 Started: Story loader implemented

## Features (Planned)

- **Data-driven architecture** - Stories defined in INI files, not hardcoded
- **Cross-platform** - Windows (MSYS2) and Linux (Ubuntu)
- **ANSI colors** - Rich terminal output
- **Split-screen UI** - Separate output and input areas
- **Save/Load system** - Multiple save slots per story
- **Story validation** - Tools to check story files for errors

## Project Structure
```
text-adventure-engine/
├── engine/          # Game engine (C code)
├── stories/         # Story data files (INI format)
├── saves/           # Save game files
├── tools/           # Story creation tools
├── docs/            # Documentation
└── tests/           # Unit tests
```

## Building

### Windows (MSYS2)
```bash
cd engine
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

### Linux
```bash
cd engine
mkdir build
cd build
cmake ..
make
```

## First Story

**Quest for the Holy Gravy Boat** - A Monty Python-style medieval comedy adventure.

## Documentation

- [Story File Format](docs/STORY-FORMAT.md) - How to create stories
- [Engine Architecture](docs/ENGINE.md) - Technical design
- [Building](docs/BUILDING.md) - Build instructions

## License

MIT License (see LICENSE file)

## Author

Marty (with Claude's assistance)
