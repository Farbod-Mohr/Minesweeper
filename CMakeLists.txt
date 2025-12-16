cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory
include_directories(include)

# Source files
set(
    SOURCES  
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Cell.cpp
    src/InputHandler.cpp
    src/HighScoreSaver.cpp
)

# Create executable  
add_executable(minesweeper ${SOURCES})

# ========= Testing ========= #

enable_testing()

# Test executable for Checkpoint 2: Board Creation, Rendering and Interaction
add_executable(checkpoint2_tests 
    tests/checkpoint2_testing.cpp 
    src/Board.cpp 
    src/Cell.cpp 
    src/InputHandler.cpp
)

add_test(NAME BoardRenderingTests COMMAND checkpoint2_tests)

# Test executable for Checkpoint 3: Mine Placement Algorithm
add_executable(checkpoint3_tests 
    tests/checkpoint3_testing.cpp 
    src/Board.cpp 
    src/Cell.cpp 
    src/InputHandler.cpp
)

add_test(NAME MinePlacementTests COMMAND checkpoint3_tests)

# Test executable for Checkpoint 4: Time Calculation and High Score Saving
add_executable(checkpoint4_tests 
    tests/checkpoint4_testing.cpp 
    src/HighScoreSaver.cpp
    src/Game.cpp
    src/Board.cpp
    src/Cell.cpp
    src/InputHandler.cpp
)

add_test(NAME HighScoreTests COMMAND checkpoint4_tests)