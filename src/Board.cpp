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

Board::Board(int rows, int cols, int mineCount)
{
    this->rows = rows + 2; // Account for walls
    this->cols = cols + 2; // Account for walls
    totalCells = rows * cols;

    this->mineCount = mineCount;

    dugCount = 0;
    flagCount = 0;
    minesRemaining = mineCount;

    selectedCell = nullptr;

    initializeGrid(this->rows, this->cols);

    // ! MAKE SURE THERE IS ALWAYS A SELECTED CELL WHEN THE BOARD IS CREATED ! //
    // ! THE PROGRAM IMPLODES INTO ASH AND DUST IF NOT !//
    if (this->rows > 0 && this->cols > 0)
    {
        selectCell(1, 1);
    }
}

void Board::initializeGrid(int rows, int cols)
{
    // Initialize the grid with all WALL cells.
    grid.resize(rows, vector<Cell>(cols, Cell(WALL, 0, 0)));

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
    for (int r = 1; r < rows - 1; r++)
    {
        for (int c = 1; c < cols - 1; c++)
        {
            grid[r][c].setState(NORMAL);
        }
    }
}

bool Board::run(string diffName, string_view diffColor)
{
    // Game loop
    while (true)
    {
        // Clear the screen and render the board
        clear();
        render(diffName, diffColor);

        // Get user input for the current game tick
        Action act = InputHandler::getAction();

        // Handle user input
        switch (act)
        {
        case UP:
            moveCursorUp();
            break;

        case DOWN:
            moveCursorDown();
            break;

        case LEFT:
            moveCursorLeft();
            break;

        case RIGHT:
            moveCursorRight();
            break;

        case DIG:
        { // ! WIP ! //

            if (!minesPlaced)
            {
                minesPlaced = true;
                placeMines(selectedCell->x, selectedCell->y);
            }

            bool hitMine = digCell(selectedCell->y, selectedCell->x);

            if (hitMine)
            {
                return false; // Game lost
            }

            // Check for win condition after digging
            if (hasWon())
            {
                return true; // Game won
            }

            break;
        }

        case FLAG:
            toggleFlagCell(selectedCell->y, selectedCell->x);

            // Check for win condition after digging
            if (hasWon())
            {
                return true; // Game won
            }

            break;

        case QUIT:
            return false; // Exit the current game. This is treated as a loss.

        default:
            break;
        }
    }
}

void Board::calcAdjacentMines()
{
    // Loops through all cells excluding walls
    for (int r = 1; r < rows - 1; r++)
    {
        for (int c = 1; c < cols - 1; c++)
        {
            Cell &cell = getCell(r, c);

            // If a cell has a mine, it does not need its adjacent mine count calculated since it loses the game when dug.
            if (cell.hasMine)
            {
                continue;
            }

            int mineCount = 0;

            // Check all 8 surrounding cells. `i` is row offset, `j` is column offset.
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue; // Skip the cell itself
                    }

                    Cell &neighborCell = getCell(r + i, c + j);

                    if (neighborCell.hasMine)
                    {
                        mineCount++;
                    }
                }
            }

            // After calculations are done, set the adjacent mine count for the cell.
            cell.setAdjacentMinesCount(mineCount);
        }
    }
}

void Board::placeMines(int safeX, int safeY)
{
    // !!! PLACEHOLDER FOR NOW !!! //
    // ? Simply places mines randomly around the board. Logic will be added later ? //

    int placedMines = 0;

    while (placedMines < mineCount)
    {
        // Get a random position within the playable area of the board.
        int r = rand() % (rows - 2) + 1;
        int c = rand() % (cols - 2) + 1;

        // Ensure the safe cell does not get a mine.
        if (c == safeX && r == safeY)
        {
            continue;
        }

        Cell &cell = getCell(r, c);

        if (!cell.hasMine)
        {
            cell.setHasMine(true);
            placedMines++;
        }
    }

    calcAdjacentMines();
}

void Board::render(string diffName, string_view diffColor) const
{

    cout << Color::Bold << "=====|||  MINESWEEPER  |||=====" << Color::Reset << endl;

    // Easy and Hard have two less letters than medium, so extra space is added on the sides for alignment.
    if (diffName == "EASY" || diffName == "HARD")
    {
        cout << Color::Bold << diffColor << "=====|||   " << diffName << " MODE   |||=====" << Color::Reset << endl;
    }
    else
    {
        cout << Color::Bold << diffColor << "=====|||  " << diffName << " MODE  |||=====" << Color::Reset << endl;
    }

    cout << endl;

    // The amount of mines remaning and the number of dug cells are displayed here.
    // Extra spaces and characters are added to keep the text aligned properly when the mine count goes below zero.
    // This is mainly for aesthetic purposes. As the kids say, "for the funny".
    cout << Color::Bold << Color::BrightWhite << "Mines Remaining: " << (minesRemaining < 0 ? "" : " ") << minesRemaining << (minesRemaining < 0 ? " ? " : "   ") << "|   Cells Dug: " << dugCount << "/" << totalCells << Color::Reset << endl;
    cout << endl;

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            // Highlight the selected cell
            if (selectedCell != nullptr && selectedCell->x == c && selectedCell->y == r)
            {
                cout << Color::BgWhite << Color::Bold << grid[r][c].print() << Color::Reset << " ";
            }
            else
            {
                cout << grid[r][c].print() << " ";
            }
        }
        cout << endl;
    }
}

bool Board::hasWon() const
{
    return dugCount == (totalCells - mineCount);
}

Cell &Board::getCell(int r, int c)
{
    return grid[r][c];
}

void Board::moveCursorUp()
{
    Cell *attemptedSelect = &getCell(selectedCell->y - 1, selectedCell->x);

    // Wall check
    if (attemptedSelect->state != WALL)
    {
        selectCell(selectedCell->y - 1, selectedCell->x);
    }
}

void Board::moveCursorRight()
{
    Cell *attemptedSelect = &getCell(selectedCell->y, selectedCell->x + 1);

    // Wall check
    if (attemptedSelect->state != WALL)
    {
        selectCell(selectedCell->y, selectedCell->x + 1);
    }
}

void Board::moveCursorDown()
{
    Cell *attemptedSelect = &getCell(selectedCell->y + 1, selectedCell->x);

    // Wall check
    if (attemptedSelect->state != WALL)
    {
        selectCell(selectedCell->y + 1, selectedCell->x);
    }
}

void Board::moveCursorLeft()
{
    Cell *attemptedSelect = &getCell(selectedCell->y, selectedCell->x - 1);

    // Wall check
    if (attemptedSelect->state != WALL)
    {
        selectCell(selectedCell->y, selectedCell->x - 1);
    }
}

void Board::selectCell(int r, int c)
{
    // Unselect the currently selected cell
    if (selectedCell != nullptr)
    {
        selectedCell->setSelected(false);
    }

    // Select the new cell
    selectedCell = &getCell(r, c);
    selectedCell->setSelected(true);
}

void Board::unselectCell(int r, int c)
{
    Cell &cell = getCell(r, c);
    cell.setSelected(false);
}

void Board::toggleFlagCell(int r, int c)
{
    Cell &cell = getCell(r, c);

    if (cell.state == NORMAL)
    {
        cell.setState(FLAGGED);
        flagCount++;
        minesRemaining--;
    }
    else if (cell.state == FLAGGED)
    {
        cell.setState(NORMAL);
        flagCount--;
        minesRemaining++;
    }
}

bool Board::digCell(int r, int c)
{
    Cell &cell = getCell(r, c);

    // Do nothing to non-normal cells.
    if (cell.state != NORMAL)
    {
        return false;
    }

    // If the cell has a mine, set it to EXPLODED and return true (game over).
    if (cell.hasMine)
    {
        cell.setState(EXPLODED);
        return true;
    }

    // Set the cell to DUG
    cell.setState(DUG);
    dugCount++;

    // If the cell has zero adjacent mines, recursively dig surrounding cells.
    if (cell.adjacentMinesCount == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0)
                {
                    continue; // Skip the cell itself
                }

                Cell &neighborCell = getCell(r + i, c + j);

                // Only dig if the neighbor is NORMAL.
                if (neighborCell.state == NORMAL)
                {
                    digCell(r + i, c + j);
                }
            }
        }
    }

    return false; // No mine was hit
}