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

    // Places mines randomly on the board, ensuring the cell at (safeX, safeY) is not a mine.
    // It runs multiple checks to make sure that the board is solvable, attempting to minimize the chances of 50/50 guesses by the player.
    // When a check fails, it will remove one of the mines from the cluster that made the board unsolvable, blacklist the space it was in from ever having a mine again, and attempts to place it somewhere else.
    // This process is repeated until all mines are placed and all the checks pass.
    // If the number of mines that must be placed exeeds the number of available spaces, possibly due to blacklisting, It will subtract the number of excess mines from the total mine count and proceed with placement, starting the game with less mines than requested.
    void placeMines(int safeX, int safeY);

    // ========= Inputs ========= //
    void moveCursorUp();
    void moveCursorRight();
    void moveCursorDown();
    void moveCursorLeft();
    bool digCell(int r, int c); // Returns true if a mine was dug (game over), false otherwise.
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