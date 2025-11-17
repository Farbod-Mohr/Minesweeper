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
private:
    // A 2d vector holding the grid of Cell objects.
    // The board size will be (rows+2) x (cols+2) to make room for the WALL cells.
    vector<vector<Cell>> grid;

    int rows;       // Actual playable rows (excluding walls)
    int cols;       // Actual playable columns (excluding walls)
    int totalCells; // Total playable cells (excluding walls)
    int mineCount;  // The amount of mines placed on the board
    int safeCells;  // The amount of non-mine cells on the board (totalCells - mineCount)

    // Calculates and returns a vector of x-y coordinate pairs that will be used to place mines on the board.
    vector<array<int, 2>> calcMineSpaces() const {}

    int numDugCells = 0;     // Tracks the number of cells that have been dug by the player.
    int numFlaggedCells = 0; // Tracks the number of cells that have been flagged by the player.

public:
    // Constructor
    Board(int rows, int cols, int mineCount) {}

    // Renders the entire board to the console.
    // Done via calling the print() method of each cell in the grid, -
    // - along with extra rendering for mine spaces, flag count, safe spaces, and any other info that should be shown to the player.
    void render() const {}

    // Returns a reference to the Cell object at the specified row and column.
    Cell &getCell(int r, int c) const {}

    // Calculates the number of adjacent mines for each cell and updates their adjacentMinesCount property.
    void calcAdjacentMines() {};

    // ========= Inputs ========= //
    void digCell(int r, int c) {}
    void flagCell(int r, int c) {}
    void unflagCell(int r, int c) {}
    void selectCell(int r, int c) {}
    void unselectCell(int r, int c) {}

    // ========= Getters ========= //
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    int getTotalRows() const { return rows + 2; } // Including walls
    int getTotalCols() const { return cols + 2; } // Including walls
    int getMineCount() const { return mineCount; }
    int getSafeCells() const { return safeCells; }
    int getNumDugCells() const { return numDugCells; }
    int getNumFlaggedCells() const { return numFlaggedCells; }
};

#endif // BOARD_H