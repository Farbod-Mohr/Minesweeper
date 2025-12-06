#include <iostream>
#include "../include/Board.h"
#include "../include/Color.h"
#include "../include/Game.h"
#include "../include/InputHandler.h"
using namespace std;

// Clears the console screen based on the operating system.
void Board::clear() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Board::initializeGrid(int rows, int cols)
{
    // Initialize the grid with all WALL cells.
    grid.resize(rows + 2, vector<Cell>(cols + 2, Cell(WALL, 0, 0)));

    // Loops through the 2d vector and sets the coordinates of each cell correctly.
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c].setX(c);
            grid[r][c].setY(r);
        }
    }

    // Loops through the inner area and sets those cells to NORMAL.
    for (int r = 1; r <= rows; r++)
    {
        for (int c = 1; c <= cols; c++)
        {
            grid[r][c].setState(NORMAL);
        }
    }

}

Board::Board(int rows, int cols, int mineCount)
{
    this->rows = rows;
    this->cols = cols;
    totalCells = rows * cols;

    this->mineCount = mineCount;
    
    dugCount = 0;
    flagCount = 0;
    minesRemaining = mineCount;
    
    selectedCell = nullptr;

    initializeGrid(rows, cols);
}

bool Board::run()
{
    // TODO: Game loop will be implemented here in the future.
    return true; // Returns true as a placeholder. This indicates the game was won.
}