# FINAL CIS PROJECT — MINESWEEPER

## BASIC INFO

- *Creator:* Farbod Mohr
- *Creation Start Date:* 11/3/2025
- *Creation End Date:* 12/15/2025
- *Description:* A console-based recreation of the classic game of minesweeper in C++.

## KEY FEATURES

- You can choose a preset from a list of provided board sizes and mine counts.
- All gameplay features from the original game are here: flag placement, cell digging, and mine explosions.
- Uses a mine placement algorithm that minimizes the chances of unsolvable boards and 50/50 guesses.
- Saves your high-scores locally. You can view them by selecting the appropriate option from the main menu.
- This project is fully compatible with all Windows, Linux, and Unix systems.

## How To Build

**NOTE 1:** You must have CMake and a C++ compiler (supporting C++17 or higher) installed to build this project.
**NOTE 2:** These commands assume you are in the root directory of the project.

### PowerShell : Build

```powershell
mkdir -Force build
cd build
cmake ..
cmake --build .
cd ..
```

### Bash : Build

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
```

## How To Run

**(IMPORTANT) NOTE 1:** THIS PROJECT REQUIRES C++ 17 OR HIGHER TO RUN PROPERLY.
**NOTE 2:** These commands assume you are in the root directory of the project.

### PowerShell : Run

```powershell
cmake --build "build"; .\build\Debug\Minesweeper.exe
```

### Bash : Run

```bash
cmake --build "build" && ./build/minesweeper
```

## Files of Interest

All implementation plans can be found in [this file](docs/Implementation_Plans.md).
All Features have been fully implemented; have fun playing!
All checkpoint reflections can be found in [this folder](docs/Reflections).
All test code can be found in [this folder](tests) and all test results can be found in [this folder](docs/Test_Results)
