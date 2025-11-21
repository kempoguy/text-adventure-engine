@echo off
echo Creating Text Adventure Engine project structure...
echo.

REM Navigate to project directory
cd /d E:\projects\c-learning

REM Create root directory
if not exist text-adventure-engine mkdir text-adventure-engine
cd text-adventure-engine

echo Creating directories...

REM Engine directories
mkdir engine\src\core 2>nul
mkdir engine\src\world 2>nul
mkdir engine\src\gameplay 2>nul
mkdir engine\src\ui 2>nul
mkdir engine\src\story 2>nul
mkdir engine\src\system 2>nul
mkdir engine\include 2>nul
mkdir engine\build 2>nul

REM Story directories
mkdir stories\gravy-boat 2>nul
mkdir stories\test-story 2>nul
mkdir stories\story-template 2>nul

REM Saves directories
mkdir saves\gravy-boat 2>nul
mkdir saves\test-story 2>nul

REM Tools directories
mkdir tools\story-validator 2>nul
mkdir tools\story-converter 2>nul
mkdir tools\map-generator 2>nul

REM Other directories
mkdir tests 2>nul
mkdir scripts 2>nul
mkdir assets 2>nul
mkdir docs 2>nul

echo Creating root files...

REM Root files
type nul > README.md
type nul > LICENSE
type nul > CHANGELOG.md
type nul > .gitignore
type nul > CMakeLists.txt

echo Creating engine source files...

REM Main files
type nul > engine\src\main.c
type nul > engine\src\main.h
type nul > engine\CMakeLists.txt

REM Core
type nul > engine\src\core\game.c
type nul > engine\src\core\game.h
type nul > engine\src\core\parser.c
type nul > engine\src\core\parser.h
type nul > engine\src\core\commands.c
type nul > engine\src\core\commands.h
type nul > engine\src\core\utils.c
type nul > engine\src\core\utils.h

REM World
type nul > engine\src\world\rooms.c
type nul > engine\src\world\rooms.h
type nul > engine\src\world\items.c
type nul > engine\src\world\items.h
type nul > engine\src\world\inventory.c
type nul > engine\src\world\inventory.h
type nul > engine\src\world\npcs.c
type nul > engine\src\world\npcs.h

REM Gameplay
type nul > engine\src\gameplay\quests.c
type nul > engine\src\gameplay\quests.h
type nul > engine\src\gameplay\combat.c
type nul > engine\src\gameplay\combat.h
type nul > engine\src\gameplay\puzzles.c
type nul > engine\src\gameplay\puzzles.h
type nul > engine\src\gameplay\dialog.c
type nul > engine\src\gameplay\dialog.h

REM UI
type nul > engine\src\ui\display.c
type nul > engine\src\ui\display.h
type nul > engine\src\ui\colors.c
type nul > engine\src\ui\colors.h
type nul > engine\src\ui\screen.c
type nul > engine\src\ui\screen.h
type nul > engine\src\ui\menu.c
type nul > engine\src\ui\menu.h

REM Story system
type nul > engine\src\story\loader.c
type nul > engine\src\story\loader.h
type nul > engine\src\story\manager.c
type nul > engine\src\story\manager.h
type nul > engine\src\story\story.h
type nul > engine\src\story\validator.c
type nul > engine\src\story\validator.h
type nul > engine\src\story\scripts.c
type nul > engine\src\story\scripts.h

REM System
type nul > engine\src\system\save.c
type nul > engine\src\system\save.h
type nul > engine\src\system\platform.c
type nul > engine\src\system\platform.h

REM Include
type nul > engine\include\adventure_engine.h

echo Creating documentation files...

type nul > docs\ENGINE.md
type nul > docs\STORY-FORMAT.md
type nul > docs\CREATING-STORIES.md
type nul > docs\API.md
type nul > docs\BUILDING.md
type nul > docs\DEVELOPMENT.md

echo Creating script files...

type nul > scripts\build_windows.bat
type nul > scripts\build_linux.sh
type nul > scripts\clean.bat
type nul > scripts\clean.sh
type nul > scripts\run_validator.bat
type nul > scripts\run_validator.sh

echo Creating story files...

REM Gravy Boat
type nul > stories\gravy-boat\story.ini
type nul > stories\gravy-boat\rooms.ini
type nul > stories\gravy-boat\items.ini
type nul > stories\gravy-boat\npcs.ini
type nul > stories\gravy-boat\dialogs.ini
type nul > stories\gravy-boat\quests.ini
type nul > stories\gravy-boat\scripts.ini
type nul > stories\gravy-boat\README.md
type nul > stories\gravy-boat\WALKTHROUGH.md

REM Test story
type nul > stories\test-story\story.ini
type nul > stories\test-story\README.md

REM Template
type nul > stories\story-template\story.ini
type nul > stories\story-template\rooms.ini
type nul > stories\story-template\items.ini
type nul > stories\story-template\npcs.ini
type nul > stories\story-template\dialogs.ini
type nul > stories\story-template\quests.ini
type nul > stories\story-template\HOWTO.md

echo Creating test files...

type nul > tests\test_parser.c
type nul > tests\test_loader.c
type nul > tests\test_inventory.c
type nul > tests\test_rooms.c
type nul > tests\test_validator.c
type nul > tests\run_tests.c
type nul > tests\CMakeLists.txt

echo Creating tool files...

type nul > tools\story-validator\validator.c
type nul > tools\story-validator\CMakeLists.txt

echo.
echo ============================================
echo Project structure created successfully!
echo ============================================
echo.
echo Location: E:\projects\c-learning\text-adventure-engine
echo.
echo Next steps:
echo 1. Copy documentation files to docs\ folder
echo 2. Create .gitignore file
echo 3. Initialize Git: git init
echo 4. Make first commit
echo.
pause