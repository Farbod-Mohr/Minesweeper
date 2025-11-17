# FINAL CIS PROJECT — MINESWEEPER

## BASIC INFO
*Creator:* Farbod Mohr
*Creation Start Date:* 11/3/2025
*Creation End Date:* **N/A**
*Description:* A console-based recreation of the classic game of minesweeper in C++.

---

## KEY FEATURES:
- You can choose a preset from a list of provided board sizes and mine counts, or enter your own.
- All gameplay features from the original game are here: flag placement, cell digging, and mine explosions.
- Saves your high-scores locally.

---

## How To Build

##### PowerShell:
```powershell
mkdir -Force build
cd build
cmake ..
cmake --build .
cd ..
```
##### Bash:
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..
```

---

## How To Run

##### PowerShell
```powershell
cmake --build "build"; .\build\Debug\Minesweeper.exe
```
##### Bash
```bash
cmake --build "build" && ./build/Debug/Minesweeper.exe
```

**IMPORTANT NOTE:** THIS PROJECT REQUIRES C++ 17 OR HIGHER TO RUN PROPERLY.