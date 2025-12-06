#define _CRT_SECURE_NO_WARNINGS
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

            if (uiButtons.DS_easy)
            {
                currentDiff = Difficulty.at("Easy");
            }
            else if (uiButtons.DS_medium)
            {
                currentDiff = Difficulty.at("Med");
            }
            else if (uiButtons.DS_hard)
            {
                currentDiff = Difficulty.at("Hard");
            }

            currentScreen = MINESWEEPER;
            return;

        default:
            break;
        }
    }
}

Board Game::startNewGame(DiffInfo selected_diff)
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
        cout << Color::Bold << Color::BrightGreen << "=====|||  MINESWEEPER  |||=====" << Color::Reset << endl;
        cout << endl;
        cout << "Minesweeper Screen (Not Yet Implemented)" << endl;

        Board newBoard = startNewGame(currentDiff);

        bool won = newBoard.run(); // Does nothing for now; always returns true.

        if (!won)
        {
            currentScreen = LOSS;
            return;
        }
        else
        {
            auto now = chrono::system_clock::now();
            endTime = chrono::system_clock::to_time_t(now);
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

        cout << "Congrats! You won on " << currentDiff.name << " mode!" << endl;

        // The function to calculate the time taken will be implemented later. This is just a test for now.
        cout << "Your start time was: " << ctime(&startTime);
        cout << "Your end time was: " << ctime(&endTime);

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