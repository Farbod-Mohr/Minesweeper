# Checkpoint 3 Test Cases

## Feature: Mine Placement Algorithm

### Test Setup

- **Test file**: `tests/checkpoint3_testing.cpp`
- **Build system**: CMake with CTest
- **Run command**:

```powershell
cd build
cmake ..
cmake --build . --config Debug
ctest --verbose -C Debug
```

---

### Test 1: Normal Operation —> Basic Mine Placement

- **What it tests**: Basic mine placement with safe zone protection
- **Expected result**:
  - Mines are placed on the board
  - Mine count does not exceed requested amount
  - 3x3 safe zone around the first click has no mines
- **Result**: ✅ Pass

---

### Test 2: Edge Case —> `formsTwoByTwo` Detection

- **What it tests**: Detection of 2x2 blocks with 3+ mines
- **Expected result**:
  - Returns true when placing a mine would create a 2x2 block with 3+ mines
  - Returns false when no such pattern would form
- **Result**: ✅ Pass

---

### Test 3: Edge Case —> `formsLongLine` Detection

- **What it tests**: Detection of 4+ consecutive mines in a row/column
- **Expected result**:
  - Returns true when 4+ horizontal mines are detected
  - Returns true when 4+ vertical mines are detected
  - Returns false when only 3 or fewer consecutive mines exist
- **Result**: ✅ Pass

---

### Test 4: Edge Case —> `trapsSafeCell` Detection

- **What it tests**: Detection of mine placement that would isolate a safe cell
- **Expected result**:
  - Returns true when placing a mine would completely surround a safe cell with mines
  - Returns false when safe cells still have accessible neighbors
- **Result**: ✅ Pass

---

### Test 5: Boundary Conditions —> `makeKey` and `isBlacklisted`

- **What it tests**: Whether or not makeKey and isBlacklisted work as intended
- **Expected result**:
  - makeKey produces unique keys for different (r, c) positions
  - isBlacklisted correctly identifies if a key is in the blacklist
- **Result**: ✅ Pass

---

### Test 6: Normal Operation —> `calcAdjacentMines`

- **What it tests**: Whether adjacent mine counts are calculated correctly
- **Expected result**:
  - Cells adjacent to a single mine have adjacentMinesCount = 1
  - Cells adjacent to multiple mines have correct counts
  - Cells not adjacent to any mines have adjacentMinesCount = 0
- **Result**: ✅ Pass

---

### Test 7: Boundary Conditions —> Safe Zone at Board Corners

- **What it tests**: Safe zone (3x3 around first dig) protection works correctly when first dig is at board corners
- **Expected result**:
  - Safe zone at top-left corner (1,1) has no mines
  - Safe zone at bottom-right corner has no mines
  - Safe zone correctly handles board walls
- **Result**: ✅ Pass

---

### Test 8: Stress Test —> High Mine Density

- **What it tests**: Mine placement algorithm properly stops placing mines when faced with too many blacklisted cells
- **Expected result**:
  - Algorithm stops without hanging the program
  - Places as many mines as possible without unsolvable patterns
  - Safe zone still protected even with high mine density
- **Result**: ✅ Pass

---

### CTest Output

```powershell
test 2
    Start 2: MinePlacementTests

2: Test command: C:\Users\Farbod\Desktop\Minesweeper\build\Debug\checkpoint3_tests.exe
2: Working Directory: C:/Users/Farbod/Desktop/Minesweeper/build
2: Test timeout computed to be: 10000000
2: 
2: === Running Tests for Checkpoint 3: Mine Placement Algorithm ===
2:
2: Test 1: Normal Operation (Mine Placement Basic Functionality)... PASSED
2: Test 2: Edge Case (formsTwoByTwo Detection)... PASSED
2: Test 3: Edge Case (formsLongLine Detection)... PASSED
2: Test 4: Edge Case (trapsSafeCell Detection)... PASSED
2: Test 5: Boundary Conditions (makeKey & isBlacklisted)... PASSED
2: Test 6: Normal Operation (calcAdjacentMines)... PASSED
2: Test 7: Boundary Conditions (Safe Zone at Board Corners)... PASSED
2: Test 8: Stress Test (High Mine Density)... Oops! The hungry hungry caterpillar ate 27 mines while we were creating your board! Thats my bad...
2:  PASSED
2:
2: ✅ All tests passed!
2/3 Test #2: MinePlacementTests ...............   Passed    0.01 sec
```
