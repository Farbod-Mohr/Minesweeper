#include <chrono>
#include <iostream>
#include <random>
#include <unordered_map>
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

bool Board::formsTwoByTwo(int r, int c) const
{
    // Loops through the four possible 2x2 blocks that (r, c) could be a part of.
    // Basically, a given (r, c) can be the top-left, top-right, bottom-left, or bottom-right cell of a 2x2 block.
    // It checks all those possible configurations for 3+ mines.
    // If any of them have 3+ mines, it returns true. Otherwise, it returns false.
    for (int i = -1; i <= 0; i++)
    {
        for (int j = -1; j <= 0; j++)
        {

            // For a given 2x2 block, the `top` and `left` variables represent the coordinates of its top-left cell.
            // The rest of the block can be derived from this.
            int top = r + i;
            int left = c + j;

            // The number of mines in the current 2x2 block being checked.
            int minesInBlock = 0;

            // Whether or not the current 2x2 block being checked contains a WALL cell.
            // If it does, we skip checking this block since WALL cells are not part of the playable area and prevent this unsolvable pattern from forming.
            bool containsWall = false;

            // Loop through the 2x2 block and count mines.
            // It should be noted that if a wall is found, two seperate `break` statements are needed since the loop is 2d.
            for (int x_offset = 0; x_offset < 2; x_offset++)
            {
                for (int y_offset = 0; y_offset < 2; y_offset++)
                {
                    const Cell &cell = getCell(top + x_offset, left + y_offset);

                    if (cell.state == WALL)
                    {
                        containsWall = true;
                        break; // breaks from the inner loop (y_offset)
                    }

                    if (cell.hasMine)
                    {
                        minesInBlock++; // If the cell has a mine, increment the count.
                    }
                }

                if (containsWall)
                {
                    break; // breaks from the outer loop (x_offset)
                }
            }

            if (containsWall)
            {
                continue; // Skip to the next 2x2 block if a wall was found.
            }

            if (minesInBlock >= 3)
            {
                return true; // Found a 2x2 block with 3+ mines; return true.
            }
        }
    }

    return false; // No 2x2 block with 3+ mines was found; return false.
}

bool Board::formsLongLine(int r, int c) const
{
    // Check horizontal
    {
        // The count always starts at 1 to account for the mine already destined to be placed at (r, c).
        int count = 1;

        // Checks to the right
        int cOffset = c + 1;

        // Loops until a WALL cell is reached, counting continuous mines.
        // When a non-mine or wall is reached, the loop stops.
        while (getCell(r, cOffset).state != WALL && getCell(r, cOffset).hasMine)
        {
            count++;
            cOffset++;
        }

        // Checks to the left
        cOffset = c - 1;

        // Same as the above loop, but checks to the left.
        while (getCell(r, cOffset).state != WALL && getCell(r, cOffset).hasMine)
        {
            count++;
            cOffset--;
        }

        // If 4 or more mines are found horizontally, return true.
        if (count >= 4)
        {
            return true;
        }
    }

    // Check vertical
    {
        // The count always starts at 1 to account for the mine already destined to be placed at (r, c).
        int count = 1;

        // Checks downwards
        int rOffset = r + 1;

        // Loops until a WALL cell is reached, counting continuous mines.
        // When a non-mine or wall is reached, the loop stops.
        while (getCell(rOffset, c).state != WALL && getCell(rOffset, c).hasMine)
        {
            count++;
            rOffset++;
        }

        // Checks upwards
        rOffset = r - 1;

        // Same as the above loop, but checks upwards.
        while (getCell(rOffset, c).state != WALL && getCell(rOffset, c).hasMine)
        {
            count++;
            rOffset--;
        }

        // If 4 or more mines are found vertically, return true.
        if (count >= 4)
        {
            return true;
        }
    }

    // Return false if pattern is not found in either direction.
    return false;
}

bool Board::trapsSafeCell(int r, int c) const
{
    // Loop through all 8 adjacent cells around (r, c)
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Skips (r, c) itself
            if (i == 0 && j == 0)
            {
                continue;
            }

            // Calculate the neighbor's coordinates
            int nr = r + i;
            int nc = c + j;

            // Get reference to the neighbor cell
            const Cell &neighbor = getCell(nr, nc);

            // Skip if the neighbor is a WALL, since they neither playable nor need to be checked.
            if (neighbor.state == WALL)
            {
                continue;
            }

            // Skip if the neighbor already has a mine. We're only concerned about isolating safe cells.
            if (neighbor.hasMine)
            {
                continue;
            }

            // Count how many non-mine tiles are adjacent to this neighbor cell
            int emptyCells = 0;

            // Check all 8 cells surrounding the neighbor (including (r, c) itself)
            for (int y_offset = -1; y_offset <= 1; y_offset++)
            {
                for (int x_offset = -1; x_offset <= 1; x_offset++)
                {
                    // Skip the neighbor cell itself
                    if (y_offset == 0 && x_offset == 0)
                    {
                        continue;
                    }

                    const Cell &cell = getCell(nr + y_offset, nc + x_offset);

                    // Skip walls
                    if (cell.state == WALL)
                    {
                        continue;
                    }

                    // If the surrounding cell doesn't have a mine, increment the counter
                    if (!cell.hasMine)
                    {
                        emptyCells++;
                    }
                }
            }

            // If a safe neighbor cell has no adjacent empty cells, it is trapped.
            if (emptyCells == 0)
            {
                return true;
            }
        }
    }

    // No trapped cells found; mine placement is valid
    return false;
}

int Board::makeKey(int r, int c) const
{
    return r * cols + c;
}

bool Board::isBlacklisted(int key, const unordered_map<int, bool> &blacklist) const
{
    return blacklist.count(key) > 0;
}

void Board::placeMines(int safeX, int safeY)
{
    // A vector of all possible positions to place mines. These positions are represented as (row, column) pairs.
    // The safe cell and its surrounding 3x3 area are excluded from this list.
    vector<pair<int, int>> candidates;

    // Resevation is done here to reduce reallocations during `push_back()`.
    // The upper bound is `totalCells - 1` since we know that at least one cell (safeX, safeY) is excluded.
    candidates.reserve(totalCells - 1);

    // Fill the candidates vector with all possible (r, c) pairs. This excludes the safe zone.
    for (int r = 1; r < rows - 1; r++)
    {
        for (int c = 1; c < cols - 1; c++)
        {
            // Checks if a given (r, c) is within the 3x3 safe zone around (safeX, safeY).
            bool inSafeZone = (r >= safeY - 1 && r <= safeY + 1) && (c >= safeX - 1 && c <= safeX + 1);

            if (inSafeZone)
            {
                continue; // Skip adding this position to candidates if it's in the safe zone.
            }

            // The (r, c) pair is valid and thus added.
            candidates.push_back({r, c});
        }
    }

    // The amount of mines requested to be placed by the difficulty settings.
    const int requestedMines = mineCount;

    // A vector to store blacklisted positions that have already failed checks from the helper functions.
    // Positions in this vector will not be attempted again for mine placement.
    unordered_map<int, bool> blacklist;

    // ! CODE FROM STACKOVERFLOW ! //
    // Creates a seeded random number generator based on the current time for random number generation.
    // The shuffle function needs this to randomize the candidates list.
    mt19937 rng = std::mt19937(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));

    // ! CODE FROM STACKOVERFLOW ! //
    // Shuffle the candidates list to randomize mine placement.
    shuffle(candidates.begin(), candidates.end(), rng);

    // The number of mines that have been successfully placed so far.
    int placedMines = 0;

    // The size of the candidates vector, casted to be an int.
    int candidateSize = static_cast<int>(candidates.size());

    // The maximum amount of rerolls allowed when placing mines. If this reaches zero, the loop will give up on placing any more mines.
    // This prevents infinite loops in cases where placing a mine is impossible due to excessive blacklisting.
    // The max amount of rerolls is set to three times the number of candidates, giving ample opportunity for placement while still making sure that the program doesn't run forever.
    // Why this specific number? I made it up. :]
    int maxRerolls = candidateSize * 3;

    // The current index in the candidates vector. Increments each iteration to try the next candidate.
    int i = 0;

    // The main placement loop. This continues until all mines are placed or all rerolls are exhausted.
    while (placedMines < requestedMines && maxRerolls > 0)
    {
        // If we've cycled through all candidates, re-shuffle and start from the beginning.
        if (i >= candidateSize)
        {
            shuffle(candidates.begin(), candidates.end(), rng);
            i = 0;
        }

        // Get the candidate position from the shuffled list.
        pair<int, int> currentCandidate = candidates[i];

        // Set r and c according to the candidate pair.
        int r = currentCandidate.first;
        int c = currentCandidate.second;

        // Increment the index for the next iteration.
        i++;

        // If this position is blacklisted, skip it.
        if (isBlacklisted(makeKey(r, c), blacklist))
        {
            continue;
        }

        // Get the cell at this candidate position.
        Cell &cell = getCell(r, c);

        // Skip if a mine is already placed at this position.
        if (cell.hasMine)
        {
            continue;
        }

        // Place a mine at this candidate position.
        cell.setHasMine(true);

        // Check if placing this mine creates any unsolvable patterns (2x2 block, long line, or trapped cell).
        // If any pattern checks fail, remove the mine, blacklist the position, and decrement the reroll budget.
        // Then, continue to the next candidate position.
        if (formsTwoByTwo(r, c) || formsLongLine(r, c) || trapsSafeCell(r, c))
        {
            cell.setHasMine(false);
            blacklist[makeKey(r, c)] = true;
            maxRerolls--;
            continue;
        }

        // Finally, if all checks pass and all is well and hell has frozen over and pigs have flown and the cows have come home, place the mine.
        placedMines++;
    }

    // If after the loop, fewer mines were able to be placed than requested, adjust the mine count and notify the player.
    if (placedMines < requestedMines)
    {
        // Calculate how many mines couldn't be placed.
        int eatenMines = requestedMines - placedMines;

        // Update the mine count to reflect the actual number of placed mines.
        mineCount = placedMines;

        // Update the remaining mines counter.
        // ! IMPORTANT: FLAG COUNT IS VITAL HERE SINCE SOMEONE MIGHT PLACE FLAGS BEFORE THE MINES ARE PLACED ! //
        // ? Had to have someone playtest to find this one out. >-> ? //
        minesRemaining = mineCount - flagCount;

        // Notify the player that some mines were removed to ensure the board is solvable.
        cout << Color::Magenta << "Oops! The hungry hungry caterpillar ate " << eatenMines << " mine" << (eatenMines == 1 ? "" : "s") << " while placing the mines! That's my bad... :[" << Color::Reset << endl;
    }
    else
    {
        // All requested mines were successfully placed; update the counters.
        mineCount = placedMines;
        minesRemaining = mineCount - flagCount;
    }

    // Calculate the adjacent mine count.
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
                cout << Color::Reverse << Color::Bold << grid[r][c].print() << Color::Reset << " ";
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

const Cell &Board::getCell(int r, int c) const
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