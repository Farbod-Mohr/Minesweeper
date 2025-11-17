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
)

# Create executable  
add_executable(recipe_manager ${SOURCES})