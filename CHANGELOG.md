# Changelog

## [Unreleased]



### Added - 2025-11-21
- Initial project structure with CMake build system
- Complete stub implementation of game engine
- Command parser with full verb/noun parsing
- Story manager framework (stub implementation)
- Cross-platform support (Windows MSYS2 + Linux)
- Basic game loop with menu system
- Documentation: Story file format specification
- Documentation: Platform architecture design
- Test story structure created

### Known Issues
- Story loader not implemented (returns hardcoded data)
- Multiple compiler warnings (unused parameters)
- Empty stub files generate pedantic warnings
- Story validation is minimal

## [0.1.0] - Phase 1 Complete
- Working stub engine
- Compiles and runs on Windows (MSYS2 UCRT64)
- Ready for story loader implementation
```

### 4. Quick Status Check

Create `STATUS.txt` in root:
```
PROJECT STATUS - November 21, 2025
===================================

PHASE 1: FOUNDATION - ✅ COMPLETE
- Project structure created
- Build system working
- Stub implementation compiling
- Command parser functional

NEXT: PHASE 2: STORY LOADING
- Implement INI file parser
- Load rooms, items, NPCs from files
- Story validation
- Test with test-story

BUILD STATUS: ✅ Compiles with warnings
RUNNABLE: ✅ Yes (stub functionality)
PLAYABLE: ❌ No (needs story loader)

Last Build: November 21, 2025 23:xx
Build Command: cmake -G "Unix Makefiles" .. && make
Platform: MSYS2 UCRT64, GCC 15.2.0