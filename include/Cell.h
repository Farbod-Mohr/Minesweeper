#include <string>
using namespace std;

/*
? Desctription: The Cell class represents a single cell in the minesweeper grid.
* It contains information about the state of the cell, those being normal, dug, flagged, and exploded, whether or not the cell contains a mine, the number of adjacent mines, and its coordinates in the grid.
* Also tracks whether the cell is being currently selected by the player, which changes its color to cyan when rendered.
* Colors will be added via ANSI escape codes in the print() function.
*/

#ifndef CELL_H
#define CELL_H

enum CellState
{
    NORMAL,   // Rendered as a white square "■".
    DUG,      // Rendered as a white number indicating adjacent mines or a "." if zero.
    FLAGGED,  // Rendered as a orange flag "⚑".
    EXPLODED, // Rendered as an red "X". Game ends shortly after a cell explodes.
    WALL      // Purely to make board rendering easier. It is rendered as a "#" and cannot be selected or interacted with.
    // Whatever the selected board size is, it is increased by 2 in both axis, the first and last rows and columns being walls.
};

class Cell
{
public:
    CellState state;        // Current state of the cell according to the enum above.
    bool hasMine;           // Whether or not the cell contains a mine.
    int adjacentMinesCount; // Number of mines in the 8 surrounding cells. Will be calculated after mine placement within the Board class.
    const int x = 0;        // The Cell's x-coordinate in the grid.
    const int y = 0;        // The Cell's y-coordinate in the grid.
    bool isSelected;        // Whether the cell is currently selected by the player. Affects rendering.

    // Constructor
    Cell(CellState state, int x, int y);

    // Returns the character (with ANSI color codes when needed) that represents the cell's current state for rendering.
    string print() const;

    // ========= Setters ========= //
    void setState(CellState state) { this->state = state; }
    void setSelected(bool isSelected) { this->isSelected = isSelected; }
    void setAdjacentMinesCount(int count) { this->adjacentMinesCount = count; }
    void setHasMine(bool hasMine) { this->hasMine = hasMine; }

    // Setters for others are not included as they are decided on Cell creation.
};

#endif // CELL_H