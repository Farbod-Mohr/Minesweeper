/*
## [] Feature 1: Main Menu Navigation

**Trigger**: User starts the program.

**Input Needed**: User key input (W, S, Up Arrow, Down Arrow, Enter).

**Implementation Flow**:

1. On program start, display main menu options: Start Game, High Scores, and Exit.
2. Get user movement inputs for menu navigation. They can move with W, S, Up Arrow, and Down Arrow keys.
3. In the Game class, use InputHandler to capture user input and set the appropiate elements in the `UIButtons` struct to true.
4. Every time the user gives an input, a game tick passes. Every game tick, first the console is cleared via `Game::clear()`. After that, in the `renderMainMenu()` function, check which button with the `MM_` identifier in the `UIButtons` struct is true and highlight the corresponding menu option.
5. When the user presses Enter, check which menu option is currently set to true in the `UIButtons` struct and navigate to the corresponding screen. (for now it should just print a message to the console).
6. Reset all `UIButtons` struct values with the `MM_` identifier to false after handling the input. (except for MM_newGame which is true by default)
7. These same principals and program flow apply for all the other UI screens in the game, so they will no longer be mentioned in the following features list. Just know that all UI screens will use the `UIButtons` struct to track the user's current selection and render accordingly.

**Data Modified**:

- `UIButtons` struct in the Game class to track which menu option is selected.

**Completion**:

- Brings the user to the appropriate screen based on their selection.

**Functions Used**:

- `Game::renderMainMenu()`
- `Game::renderGameOver()` (in the future)
- `Game::renderWin()` (in the future)
- `Game::renderHighScores()` (in the future)
- `Game::renderExit()` (in the future)
- `Game::clear()`
- `Game::init()`
- `InputHandler::getAction()`
*/

#include "Game.h"
#include "InputHandler.h"
#include <iostream>
#include <cstdlib> // For system("clear") and system("cls")
#include "Color.h"
using namespace std;

void Game::init()
{
    bool gameRunning = true;
    // Main game loop
    while (gameRunning)
    {
        // Clear the screen on every screen change
        clear();

        // Render the appropriate screen based on the currentScreen value
        switch (currentScreen)
        {
        case MAIN_MENU:
            renderMainMenu();
            break;
        case DIFFICULTY_SELECTION:
            renderDiffSelection();
            break;
        case MINESWEEPER:
            // Will call the render function of the minesweeper board object, as it handles its own rendering.
            renderMinesweeper();
            break;
        case LOSS:
            renderGameOver();
            break;
        case WIN:
            renderWin();
            break;
        case HIGH_SCORES:
            renderHighScores();
            break;
        case EXIT:
            renderExit();
            gameRunning = false;
            return; // Exit the game loop
        default:
            break;
        }
    }
}

// Clears the console screen based on the operating system.
void Game::clear() const
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Game::renderExit()
{
    cout << "Thank you for playing! See you next time! :> " << endl;
}

string Game::printDiff(const DiffInfo &diff) const
{
    return " ===> Mines: " + to_string(diff.mineCount) + " | Grid: " + to_string(diff.row) + "x" + to_string(diff.column);
}

void Game::renderMainMenu()
{
    while (true)
    {
        Game::clear();

        cout << Color::Bold << Color::BrightGreen << "=====|||  MAIN MENU  |||=====" << Color::Reset << endl;
        cout << endl;

        // Single line if-else statements are used to determine which menu option is currently selected.
        // I remember using these in javascript a while ago and turns out they work here too!
        cout << (uiButtons.MM_newGame ? Color::Cyan : "") << (uiButtons.MM_newGame ? "> " : "  ") << (uiButtons.MM_newGame ? Color::Underline : "") << "Start New Game" << Color::Reset << endl;
        cout << (uiButtons.MM_highScores ? Color::Cyan : "") << (uiButtons.MM_highScores ? "> " : "  ") << (uiButtons.MM_highScores ? Color::Underline : "") << "High Scores" << Color::Reset << endl;
        cout << (uiButtons.MM_exit ? Color::Cyan : "") << (uiButtons.MM_exit ? "> " : "  ") << (uiButtons.MM_exit ? Color::Underline : "") << "Exit" << Color::Reset << endl;

        // Get user input for menu navigation
        Action act = InputHandler::getAction();

        // Handle user input to navigate the menu
        switch (act)
        {
        case UP:
            if (uiButtons.MM_highScores)
            {
                uiButtons.MM_highScores = false;
                uiButtons.MM_newGame = true;
            }
            else if (uiButtons.MM_exit)
            {
                uiButtons.MM_exit = false;
                uiButtons.MM_highScores = true;
            }
            break;

        case DOWN:
            if (uiButtons.MM_newGame)
            {
                uiButtons.MM_newGame = false;
                uiButtons.MM_highScores = true;
            }
            else if (uiButtons.MM_highScores)
            {
                uiButtons.MM_highScores = false;
                uiButtons.MM_exit = true;
            }
            break;

        case DIG:
            if (uiButtons.MM_newGame)
            {
                currentScreen = DIFFICULTY_SELECTION;
                uiButtons.DS_easy = true;
                return;
            }
            else if (uiButtons.MM_highScores)
            {
                currentScreen = HIGH_SCORES;
                uiButtons.MM_newGame = true;
                uiButtons.MM_highScores = false;
                return;
            }
            else if (uiButtons.MM_exit)
            {
                currentScreen = EXIT;
                uiButtons.MM_newGame = true;
                uiButtons.MM_exit = false;
                return;
            }
            break;

        default:
            break;
        }
    }
}

// ? =========================================================== //
// ! Placeholder implementations for other rendering functions ! //
// ? =========================================================== //

void Game::renderDiffSelection()
{
    while (true)
    {
        Game::clear();

        cout << Color::Bold << Color::BrightGreen << "=====|||  SELECT YOUR DIFFICULTY  |||=====" << Color::Reset << endl;
        cout << endl;

        // Yes I know this looks genuinely horrid, awful, and mortifyingly unreadable, but that's the price I'm willing to pay for a good looking UI :D

        cout << (uiButtons.DS_easy ? Color::Bold : "") << (uiButtons.DS_easy ? Color::BrightGreen : Color::Green) << (uiButtons.DS_easy ? "> " : "  ") << (uiButtons.DS_easy ? Color::Underline : "") << "Easy" << Color::Reset << (uiButtons.DS_easy ? printDiff(Difficulty.at("Easy")) : "") << endl;

        cout << (uiButtons.DS_medium ? Color::Bold : "") << (uiButtons.DS_medium ? Color::BrightYellow : Color::Yellow) << (uiButtons.DS_medium ? "> " : "  ") << (uiButtons.DS_medium ? Color::Underline : "") << "Medium" << Color::Reset << (uiButtons.DS_medium ? printDiff(Difficulty.at("Med")) : "") << endl;

        cout << (uiButtons.DS_hard ? Color::Bold : "") << (uiButtons.DS_hard ? Color::BrightRed : Color::Red) << (uiButtons.DS_hard ? "> " : "  ") << (uiButtons.DS_hard ? Color::Underline : "") << "Hard" << Color::Reset << (uiButtons.DS_hard ? printDiff(Difficulty.at("Hard")) : "") << endl;

        Action act = InputHandler::getAction();

        switch (act)
        {
        case UP:
            if (uiButtons.DS_medium)
            {
                uiButtons.DS_medium = false;
                uiButtons.DS_easy = true;
            }
            else if (uiButtons.DS_hard)
            {
                uiButtons.DS_hard = false;
                uiButtons.DS_medium = true;
            }
            break;

        case DOWN:
            if (uiButtons.DS_easy)
            {
                uiButtons.DS_easy = false;
                uiButtons.DS_medium = true;
            }
            else if (uiButtons.DS_medium)
            {
                uiButtons.DS_medium = false;
                uiButtons.DS_hard = true;
            }
            break;

        case DIG: // ! TEMP

            uiButtons.DS_easy = true;
            uiButtons.DS_medium = false;
            uiButtons.DS_hard = false;
            
            currentScreen = MINESWEEPER;
            return;

        default:
            break;
        }
    }
}

void Game::renderMinesweeper()
{
    while (true)
    {
        Game::clear();
        cout << Color::Bold << Color::BrightGreen << "=====|||  MINESWEEPER  |||=====" << Color::Reset << endl;
        cout << endl;
        cout << "Minesweeper Screen (Not Yet Implemented)" << endl;

        Action act = InputHandler::getAction();
        if (act == DIG) 
        {
            currentScreen = WIN;
            return;
        }
            
    }
}

void Game::renderGameOver()
{
    while (true)
    {
        Game::clear();
        cout << Color::Bold << Color::BrightRed << "=====|||  GAME OVER  |||=====" << Color::Reset << endl;
        cout << endl;
        cout << "Game Over Screen (Not Yet Implemented)" << endl;

        Action act = InputHandler::getAction();
        if (act == DIG)
        {
            currentScreen = MAIN_MENU;
            return;
        }
    }
}

void Game::renderWin()
{
    while (true)
    {
        Game::clear();
        cout << Color::Bold << Color::BrightGreen << "=====|||  YOU WIN!  |||=====" << Color::Reset << endl;
        cout << endl;
        cout << "Win Screen (Not Yet Implemented)" << endl;

        Action act = InputHandler::getAction();
        if (act == DIG)
        {
            currentScreen = MAIN_MENU;
            return;
        }
    }
}

void Game::renderHighScores()
{
    while (true)
    {
        Game::clear();
        cout << Color::Bold << Color::BrightGreen << "=====|||  HIGH SCORES  |||=====" << Color::Reset << endl;
        cout << endl;
        cout << "High Scores Screen (Not Yet Implemented)" << endl;

        Action act = InputHandler::getAction();
        if (act == DIG)
        {
            currentScreen = MAIN_MENU;
            return;
        }
    }
}