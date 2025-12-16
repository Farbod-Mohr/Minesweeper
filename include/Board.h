#include <string>
#include <string_view>
#include <vector>
#include "Cell.h"
using namespace std;

/*
? Description: The Board class represents the minesweeper board, which is a grid of Cell objects.
* It manages the algorithm(s?) for mine placement, calculates the number of adjacent mines for each cell, and provides methods for interacting with the cells (digging, flagging, and selecting).
* It contains information about its own state, such as the number of rows, columns, total cells, total mines, and total amount of safe cells. This data will be used by the Game class to render the board and determine if the current game is won.
* This class, unlike the other screens in the game, handles its own rendering via the `render()` function due to its complexity relative to the other simple UI.
* Every time a game is started, a new board object will be created and thusly destoryed when the game ends. The class does not need a custom destrcutor as vectors handle memory management themselves.
*/

#ifndef BOARD_H
#define BOARD_H

class Board
{
// Instead of private, protected is used here to allow the TestBoard subclass to access these members for CTest purposes.
protected:
    // A 2d vector holding the grid of Cell objects.
    // The board size will be (rows+2) x (cols+2) to make room for the WALL cells.
    vector<vector<Cell>> grid;

    int rows;           // All rows (including walls).
    int cols;           // All columns (including walls).
    int totalCells;     // All actually playable cells (excluding walls).
    int mineCount;      // The amount of mines placed on the board.
    int dugCount;       // Tracks the number of cells that have been dug by the player.
    int flagCount;      // Tracks the number of cells that have been flagged by the player.
    int minesRemaining; // `mineCount` - `flagCount`.

    bool minesPlaced = false; // Whether or not the mines have been placed yet. Used to make sure mines are only place once.

    Cell *selectedCell; // Pointer to the currently selected cell.

    // Returns a reference to the Cell object at the specified row and column.
    Cell &getCell(int r, int c);

    // This is an overload of the normal getCell function.
    // The difference is that this one is a const function and returns a const reference to the Cell object.
    // This is useful for the mine placement algorithm, which does not modify any cells when checking their states.
    // The function for mine placements are const functions, so this const overload is needed to avoid compiler errors.
    const Cell &getCell(int r, int c) const;

    // Places mines randomly on the board, ensuring the cell at (safeX, safeY) along with a 3x3 field around it are not mines.
    // It runs multiple checks to make sure that the board is solvable, attempting to minimize the chances of 50/50 guesses by the player.
    // When a check fails, it will remove one of the mines from the cluster that made the board unsolvable, blacklist the space it was in from ever having a mine again, and attempt to place it somewhere else.
    // This process is repeated until all mines are placed and all the checks pass.
    // If the number of mines that must be placed exeeds the number of available spaces, possibly due to blacklisting, It will subtract the number of excess mines from the total mine count and proceed with placement, starting the game with less mines than requested.
    void placeMines(int safeX, int safeY);

    // ========= Mine Placement Helpers ========= //

    // Checks whether or not adding a mine at a given (r, c) would create a 2x2 block with 3+ mines.
    // This pattern USUALLY forces unavoidable guesses, so it must be avoided in the mine placement algorithm.
    // Keyword: USUALLY. There are some rare cases where this pattern is unavoidable, but the algorithm will do its best to prevent it.
    // There are also cases where this pattern is part of a solvable board, so there are bound to be false positives. However, it is better to be safe than sorry.
    bool formsTwoByTwo(int r, int c) const;

    // Checks horizontal and vertical lines from a given (r, c) to prevent long 4+ straight chains of mines.
    // It counts continuous mines in both directions from (r, c).
    // If 4 or more contiguous mines are found in either direction, it returns true, indicating that placing a mine at (r, c) should be avoided.
    // Like the other helper function, this is not a perfect check and may produce false positives, but it helps reduce the chances of unsolvable boards.
    bool formsLongLine(int r, int c) const;

    // checks whether placing a mine at (r, c) would isolate a safe cell and completely by surround it with mines, making it unreachable and thus, unsolvable.
    // It checks all adjacent cells of each non-mine cell around (r, c) to see if they would all be mines if a mine were placed at (r, c).
    // If such a situation is found, it returns true, indicating that placing a mine at (r, c) should be avoided.
    bool trapsSafeCell(int r, int c) const;

    // When placing mines, an unordered_map is used to keep track of blacklisted positions that have already failed checks from the helper functions above.
    // This function converts coordinate pairs (r, c) into a unique, integer hash key for use in the blacklist.
    int makeKey(int r, int c) const;

    // Checks if a given position key is inside the blacklist.
    bool isBlacklisted(int key, const unordered_map<int, bool> &blacklist) const;

    // ========= Inputs ========= //
    void moveCursorUp();
    void moveCursorRight();
    void moveCursorDown();
    void moveCursorLeft();
    bool digCell(int r, int c);        // Returns true if a mine was dug (game over), false otherwise.
    void toggleFlagCell(int r, int c); // Flags if not flagged, unflags if flagged.
    void selectCell(int r, int c);
    void unselectCell(int r, int c);

    // Calculates the number of adjacent mines for each cell and updates their adjacentMinesCount property.
    void calcAdjacentMines();

    // The function to clear the screen is different based on the operating system, so this function handles that.
    void clear() const;

    // Renders the entire board to the console.
    // Done via calling the print() method of each cell in the grid, along with displaying some extra values.
    void render(string diffName, string_view diffColor) const;

    // Checks if the player has won the game by checking if the number of dug cells (`dugCount`) equals the total number of safe cells `totalCells - mineCount`.
    bool hasWon() const;

    // A helper function that initializes a the gmae grid with WALL cells on the borders and NORMAL cells inside.
    void initializeGrid(int rows, int cols);

public:
    // Constructor
    Board(int rows, int cols, int mineCount);

    // Begins a loop that runs the current minesweeper game.
    // Returns true if the game was won, false if lost.
    // Afterwards, the Game class will handle transitioning to the appropriate end screen.
    bool run(string diffName, string_view diffColor);
};

#endif // BOARD_H