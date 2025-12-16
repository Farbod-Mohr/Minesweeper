# Checkpoint 4 Test Cases

## Feature: Time Calculation and High Score Saving

### Test Setup

- **Test file**: `tests/checkpoint4_testing.cpp`
- **Build system**: CMake with CTest
- **Run command**:

```powershell
cd build
cmake ..
cmake --build . --config Debug
ctest --verbose -C Debug
```

---

### Test 1: Normal Operation —> Time String to Seconds Conversion

- **What it tests**: Conversion of HH:MM:SS time format to total seconds
- **Expected result**:
  - "00:00:00" converts to 0 seconds
  - "00:01:00" converts to 60 seconds
  - "01:00:00" converts to 3600 seconds
  - "01:30:45" converts to 5445 seconds
  - "23:59:59" converts to 86399 seconds
- **Result**: ✅ Pass

---

### Test 2: Normal Operation —> Seconds to Time String Conversion

- **What it tests**: Conversion of total seconds to HH:MM:SS time format
- **Expected result**:
  - 0 seconds formats to "00:00:00"
  - 60 seconds formats to "00:01:00"
  - 3600 seconds formats to "01:00:00"
  - 5445 seconds formats to "01:30:45"
  - 86399 seconds formats to "23:59:59"
- **Result**: ✅ Pass

---

### Test 3: Edge Case —> Round Trip Conversion

- **What it tests**: Converting seconds => string => seconds returns the original value
- **Expected result**:
  - Multiple values (0, 1, 59, 3661, 7384) remain unchanged after round-trip
  - Both conversion functions are inverse operations of each other
- **Result**: ✅ Pass

---

### Test 4: Normal Operation —> Add Score and Retrieve

- **What it tests**: Basic score read and write functionality
- **Expected result**:
  - Score "00:05:30" (330 seconds) can be added to "EASY" difficulty
  - Retrieved scores correctly show 330 as the first entry
- **Result**: ✅ Pass

---

### Test 5: Boundary Conditions —> Score Sorting

- **What it tests**: Scores are automatically sorted from best to worst
- **Expected result**:
  - Adding scores in order 600s, 300s, 450s results in sorted order 300, 450, 600
  - Best score (lowest time) is always first in the list
- **Result**: ✅ Pass

---

### Test 6: Boundary Conditions —> Max 5 Scores Limit

- **What it tests**: Only the top 5 scores are kept per difficulty
- **Expected result**:
  - Adding 6 scores keeps only the best 5
  - Worst score (600 seconds) is pushed out when a better 6th score is added
  - Final list contains: 120, 240, 300, 360, 480 seconds
- **Result**: ✅ Pass

---

### Test 7: Edge Case —> Different Difficulties Stored Separately

- **What it tests**: Scores for different difficulties are stored seperately
- **Expected result**:
  - "EASY", "MEDIUM", and "HARD" each have their own score lists
  - Adding a score to one difficulty does not affect others
  - No cross-contamination between difficulty score lists
- **Result**: ✅ Pass

---

### Test 8: Edge Case —> Score Not Good Enough to Save

- **What it tests**: A worse score doesn't replace better scores when the list is full
- **Expected result**:
  - When 5 scores exist (60, 120, 180, 240, 300 seconds), adding 600 seconds does nothing
  - The 5th position still contains 300, not 600
  - Score list remains unchanged when new score is worse than all existing scores
- **Result**: ✅ Pass

---

### CTest Output

```powershell
test 3
    Start 3: HighScoreTests

3: Test command: C:\Users\Farbod\Desktop\Minesweeper\build\Debug\checkpoint4_tests.exe
3: Working Directory: C:/Users/Farbod/Desktop/Minesweeper/build
3: Test timeout computed to be: 10000000
3: 
3: === Running Tests for Checkpoint 4: Time Calculation & High Score Saving ===
3:
3: Test 1: Normal Operation (Time String to Seconds Conversion)... PASSED
3: Test 2: Normal Operation (Seconds to Time String Formatting)... PASSED
3: Test 3: Edge Case (Round Trip Conversion)... PASSED
3: Test 4: Normal Operation (Add Score and Retrieve)... PASSED
3: Test 5: Boundary Conditions (Score Sorting)... PASSED
3: Test 6: Boundary Conditions (Max 5 Scores Limit)... PASSED
3: Test 7: Edge Case (Different Difficulties Stored Separately)... PASSED
3: Test 8: Edge Case (Score Not Good Enough to Save)... PASSED
3:
3: ✅ All tests passed!
3/3 Test #3: HighScoreTests ...................   Passed    0.01 sec
```
