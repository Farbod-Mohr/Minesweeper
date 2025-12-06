#include "../include/Cell.h"
#include "../include/Color.h"
using namespace std;

Cell::Cell(CellState state, int x, int y)
{
    this->state = state;
    this->x = x;
    this->y = y;
    this->hasMine = false;
    this->adjacentMinesCount = 0;
    this->isSelected = false;
}

string Cell::print() const
{
    string display;

    // Determine the character to display based on the cell state
    switch (state)
    {
    case NORMAL:
        display = "■";
        break;
    case DUG:
        if (adjacentMinesCount > 0)
            display = to_string(adjacentMinesCount);
        else
            display = ".";
        break;
    case FLAGGED:
        display = "⚑";
        break;
    case EXPLODED:
        display = "X";
        break;
    case WALL:
        display = "#";
        break;
    default:
        display = " ";
        break;
    }

    // Determine the color based on selection and state
    if (isSelected)
    {
        display = string(Color::Cyan) + display + string(Color::Reset);
    }
    else
    {
        switch (state)
        {
        case NORMAL:
            display = string(Color::White) + display + string(Color::Reset);
            break;
        case DUG:
            display = string(Color::White) + display + string(Color::Reset);
            break;
        case FLAGGED:
            display = string(Color::Yellow) + display + string(Color::Reset);
            break;
        case EXPLODED:
            display = string(Color::Red) + display + string(Color::Reset);
            break;
        case WALL:
            display = string(Color::Gray) + display + string(Color::Reset);
            break;
        default:
            break;
        }
    }

    return display;
}