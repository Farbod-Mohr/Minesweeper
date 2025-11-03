# FINAL CIS PROJECT — MINRSWEEPER

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
- Has input support for both keyboard *and* mouse.

---

## How To Build

##### PowerShell:
```powershell
cmake --build "out\build\GCC 6.3.0 mingw32"
```
##### Bash:
```bash
cmake --build "out/build/GCC 6.3.0 mingw32"
```

---

## How To Run

##### PowerShell
```powershell
cmake --build "out\build\GCC 6.3.0 mingw32"; .\out\build\GCC` 6.3.0` mingw32\Minesweeper.exe
```
##### Bash
```bash
cmake --build "out/build/GCC 6.3.0 mingw32" && "./out/build/GCC 6.3.0 mingw32/Minesweeper.exe"
```