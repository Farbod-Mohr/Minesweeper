# Checkpoint 2 Test Cases

## Feature: Board Rendering and Interaction

### Test Setup

- **Test file**: `tests/checkpoint2_testing.cpp`
- **Build system**: CMake with CTest
- **Run command**:

```powershell
cd build
cmake ..
cmake --build .
ctest --verbose -C Debug
```

---

### Test 1: Normal Operation —> Board Creation and Rendering

- **What it tests**: Creating a board with correct dimensions, wall placement, and initial cell states
- **Expected result**:
  - Board dimensions are correctly set (including +2 for walls)
  - Wall cells are placed on all borders
  - Inner cells are in NORMAL state
  - A cell is selected by default at position (1,1)
- **Result**: ✅ Pass

---

### Test 2: Edge Case —> Cell States and Rendering

- **What it tests**: Rendering of cells in different states (NORMAL, DUG, FLAGGED, EXPLODED, WALL)
- **Expected result**:
  - NORMAL cells render as "+"
  - FLAGGED cells render as "F"
  - EXPLODED cells render as "X"
  - WALL cells render as "#"
  - DUG cells render as " " (empty space) or a number (0-8) based on adjacent mines
  - Selected cells have the Color::Reverse highlighting
- **Result**: ✅ Pass

---

### Test 3: Boundary Conditions —> Cursor Movement and Flagging

- **What it tests**: Cursor movement when met with board boundaries and flag toggling
- **Expected result**:
  - Cursor starts at position (1,1)
  - Cursor cannot move into wall cells
  - Flagging a cell increases 'flag count' and decreases 'mines remaining'
  - Unflagging a cell reverses these counters
- **Result**: ✅ Pass

---

### Test 4: Digging Cells

- **What it tests**: Cell digging logic and mine detection
- **Expected result**:
  - Digging a safe cell changes its state to DUG and increments 'dug count'
  - Digging can only be done on NORMAL cells
  - Digging a cell with a mine returns true and sets state to EXPLODED
- **Result**: ✅ Pass

---

### Test 5: Adjacent Mines Count Display

- **What it tests**: Correct display of adjacent mine count numbers (0-8)
- **Expected result**:
  - Cells with 0 adjacent mines display empty space
  - Cells with 1-8 adjacent mines display the corresponding number
- **Result**: ✅ Pass

---

### Test 6: Board Size Variations

- **What it tests**: Board creation for all three difficulty levels
- **Expected result**:
  - Easy (9x9): 11x11 with walls, 81 playable cells
  - Medium (16x16): 18x18 with walls, 256 playable cells
  - Hard (16x30): 18x32 with walls, 480 playable cells
- **Result**: ✅ Pass

---

### CTest Output

```powershell
test 1
    Start 1: BoardRenderingTests

1: Test command: C:\Users\Farbod\Desktop\Minesweeper\build\Debug\checkpoint2_tests.exe
1: Working Directory: C:/Users/Farbod/Desktop/Minesweeper/build
1: Test timeout computed to be: 10000000
1: 
1: === Running Tests for Checkpoint 2: Board Rendering & Interaction ===
1: 
1: Test 1: Normal Operation (Board Initialization & Cell Rendering)... PASSED
1: Test 2: Edge Case (Cell State Transitions & Rendering)... PASSED
1: Test 3: Boundary Conditions (Cursor Movement & Flagging)... PASSED
1: Test 4: Digging Cells (Cell Dig Logic)... PASSED
1: Test 5: Adjacent Mines Count Display... PASSED
1: Test 6: Board Size Variations (Different Difficulties)... PASSED
1:
1: ✅ All tests passed!
1/3 Test #1: BoardRenderingTests ..............   Passed    0.01 sec
```
