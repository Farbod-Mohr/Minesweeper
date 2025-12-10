#define _CRT_SECURE_NO_WARNI
#include "../include/Game.h"
#include "../include/InputHandler.h"
#include "../include/Color.h"
#include "../include/Board.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <cstdlib> // For system("clear") and system("cls")
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

void const Game::renderExit()
{
    cout << endl << Color::Bold << "Thank you for playing! See you next time! :> " << endl;
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

        // If-else statements are used to determine which button is currently selected and render it accordingly.

        if (uiButtons.MM_newGame) {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "Start New Game" << Color::Reset << endl;
        } else {
            cout << "   Start New Game" << endl;
        }

        if (uiButtons.MM_highScores) {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "High Scores" << Color::Reset << endl;
        } else {
            cout << "   High Scores" << endl;
        }

        if (uiButtons.MM_exit) {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "Exit" << Color::Reset << endl;
        } else {
            cout << "   Exit" << endl;
        }

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
                return;
            }
            else if (uiButtons.MM_exit)
            {
                currentScreen = EXIT;
                return;
            }
            break;

        case QUIT:
            currentScreen = EXIT;
            return;

        default:
            break;
        }
    }
}

// ? ======================================================== ? //
// ! Placeholder implementations for some rendering functions ! //
// ? ======================================================== ? //

void Game::renderDiffSelection()
{
    while (true)
    {
        Game::clear();

        cout << Color::Bold << Color::BrightGreen << "=====|||  SELECT YOUR DIFFICULTY  |||=====" << Color::Reset << endl;
        cout << endl;

        // Yes I know this looks genuinely horrid, awful, and mortifyingly unreadable, but that's the price I'm willing to pay for a good looking UI :D

        if (uiButtons.DS_easy) {
            cout << Color::Bold << Color::BrightGreen << "  > " << Color::Underline << "Easy" << Color::Reset << printDiff(Difficulty.at("Easy")) << endl;
        } else {
            cout << Color::Green << "   Easy" << Color::Reset << endl;
        }

        if (uiButtons.DS_medium) {
            cout << Color::Bold << Color::BrightYellow << "  > " << Color::Underline << "Medium" << Color::Reset << printDiff(Difficulty.at("Med")) << endl;
        } else {
            cout << Color::Yellow << "   Medium" << Color::Reset << endl;
        }

        if (uiButtons.DS_hard) {
            cout << Color::Bold << Color::BrightRed << "  > " << Color::Underline << "Hard" << Color::Reset << printDiff(Difficulty.at("Hard")) << endl;
        } else {
            cout << Color::Red << "   Hard" << Color::Reset << endl;
        }

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

        case DIG:
        {
            string selectedDiff;

            if (uiButtons.DS_easy)
            {
                selectedDiff = "Easy";
            }
            else if (uiButtons.DS_hard)
            {
                selectedDiff = "Hard";
            }
            else if (uiButtons.DS_medium)
            {
                selectedDiff = "Med";
            }

            currentDiff = Difficulty.at(selectedDiff);

            // Reset the selector so it always opens highlighting Easy next time.
            uiButtons.DS_easy = true;
            uiButtons.DS_medium = false;
            uiButtons.DS_hard = false;

            currentScreen = MINESWEEPER;
            return;
        }
        case QUIT:

            currentScreen = MAIN_MENU;

            // Reset the selector so it always opens highlighting Easy next time.
            uiButtons.DS_easy = true;
            uiButtons.DS_medium = false;
            uiButtons.DS_hard = false;

            return;

        default:
            break;
        }
    }
}

Board Game::makeNewGame(DiffInfo selected_diff)
{
    // Initialize a new Board object with the selected difficulty's info.
    Board newBoard(selected_diff.row, selected_diff.column, selected_diff.mineCount);

    auto now = chrono::system_clock::now();
    startTime = chrono::system_clock::to_time_t(now);

    return newBoard;
}

void Game::renderMinesweeper()
{
    while (true)
    {
        Game::clear();

        Board newBoard = makeNewGame(currentDiff);

        bool won = newBoard.run(currentDiff.name, currentDiff.diffColor);

        if (won)
        {
            auto now = chrono::system_clock::now();
            endTime = chrono::system_clock::to_time_t(now);
            currentScreen = WIN;
            return;
        }
        else
        {
            currentScreen = LOSS;
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
        else if (act == QUIT)
        {
            currentScreen = EXIT;
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

        cout << "Congrats! You won on " << currentDiff.name << " mode!" << endl;

        // The function to calculate the time taken will be implemented later. This is just a test for now.
        // cout << "Your start time was: " << ctime(&startTime);
        // cout << "Your end time was: " << ctime(&endTime);

        Action act = InputHandler::getAction();
        if (act == DIG)
        {
            currentScreen = MAIN_MENU;
            return;
        }
        else if (act == QUIT)
        {
            currentScreen = EXIT;
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
        else if (act == QUIT)
        {
            currentScreen = EXIT;
            return;
        }
    }
}