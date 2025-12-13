#include "../include/Game.h"
#include "../include/InputHandler.h"
#include "../include/Color.h"
#include "../include/Board.h"
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
using namespace std;

void Game::init()
{
    // Load high scores from file on program start
    highScoreSaver.loadFromFile();

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
            renderLoss();
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

void Game::renderExit() const
{
    cout << endl
         << Color::Bold << "Thank you for playing! See you next time! :> " << endl;
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

        cout << Color::Bold << Color::BrightMagenta << "=====|||  MAIN MENU  |||=====" << Color::Reset << endl;
        cout << endl;

        // If-else statements are used to determine which button is currently selected and render it accordingly.

        if (uiButtons.MM_newGame)
        {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "Start New Game" << Color::Reset << endl;
        }
        else
        {
            cout << Color::Dim << "   Start New Game" << Color::Reset << endl;
        }

        if (uiButtons.MM_highScores)
        {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "High Scores" << Color::Reset << endl;
        }
        else
        {
            cout << Color::Dim << "   High Scores" << Color::Reset << endl;
        }

        if (uiButtons.MM_exit)
        {
            cout << Color::Bold << Color::Cyan << "  > " << Color::Underline << "Exit" << Color::Reset << endl;
        }
        else
        {
            cout << Color::Dim << "   Exit" << Color::Reset << endl;
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

void Game::renderDiffSelection()
{
    while (true)
    {
        Game::clear();

        cout << Color::Bold << Color::BrightMagenta << "=====|||  SELECT YOUR DIFFICULTY  |||=====" << Color::Reset << endl;
        cout << endl;

        if (uiButtons.DS_easy)
        {
            cout << Color::Bold << Color::BrightGreen << "  > " << Color::Underline << "Easy" << Color::Reset << printDiff(Difficulty.at("Easy")) << endl;
        }
        else
        {
            cout << Color::Dim << Color::Green << "   Easy" << Color::Reset << endl;
        }

        if (uiButtons.DS_medium)
        {
            cout << Color::Bold << Color::BrightYellow << "  > " << Color::Underline << "Medium" << Color::Reset << printDiff(Difficulty.at("Med")) << endl;
        }
        else
        {
            cout << Color::Dim << Color::Yellow << "   Medium" << Color::Reset << endl;
        }

        if (uiButtons.DS_hard)
        {
            cout << Color::Bold << Color::BrightRed << "  > " << Color::Underline << "Hard" << Color::Reset << printDiff(Difficulty.at("Hard")) << endl;
        }
        else
        {
            cout << Color::Dim << Color::Red << "   Hard" << Color::Reset << endl;
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

Board Game::makeNewBoard(DiffInfo selected_diff)
{
    // Initialize a new Board object with the selected difficulty's info.
    Board newBoard(selected_diff.row, selected_diff.column, selected_diff.mineCount);

    // When a new board is made, note down the current time as the start time for the game.
    startTime = chrono::steady_clock::now();

    return newBoard;
}

void Game::renderMinesweeper()
{
    while (true)
    {
        Game::clear();

        Board newBoard = makeNewBoard(currentDiff);

        bool won = newBoard.run(currentDiff.name, currentDiff.diffColor);

        if (won)
        {
            // When the game ends in a win, note down the current time as the end time for the game.
            endTime = chrono::steady_clock::now();

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

string Game::calcTime()
{
    // Calculate the elapsed time in seconds between start and end
    chrono::steady_clock::duration timeTaken = endTime - startTime;

    // Convert the duration to seconds
    chrono::seconds timeTakenInSeconds = chrono::duration_cast<chrono::seconds>(timeTaken);

    // Calculate the total seconds spent on the game
    long long totalSeconds = timeTakenInSeconds.count();

    // Return the formatted time string
    return secondsFormat(totalSeconds);
}

void Game::saveScore(string total_time)
{
    highScoreSaver.addScore(total_time, currentDiff);
}

void Game::renderLoss()
{
    while (true)
    {
        Game::clear();

        cout << Color::Bold << Color::BrightRed << "=====|||  GAME OVER  |||=====" << Color::Reset << endl;
        cout << endl;

        cout << "Oops, You hit a mine! Better luck next time!" << endl;
        cout << endl;

        cout << "Press any button to return to the Main Menu..." << Color::Reset;

        Action act = InputHandler::getAction();
        if (act != UNKNOWN)
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

        cout << Color::Bold << "Congrats! You won on " << currentDiff.diffColor << currentDiff.name << Color::Reset << Color::Bold << " mode!" << endl;

        string timeStr = calcTime();
        cout << Color::Bold << "Time Taken: " << timeStr << endl;
        cout << endl;

        // Send the score to the HighScoreSaver to be saved if appropriate.
        saveScore(timeStr);

        cout << "Press any button to return to the Main Menu..." << Color::Reset;

        Action act = InputHandler::getAction();
        if (act != UNKNOWN)
        {
            currentScreen = MAIN_MENU;
            return;
        }
    }
}

string Game::secondsFormat(long long seconds) const
{
    // If the score is 0, it means there is no recorded score, so return "--------"
    if (seconds == 0)
    {
        return "--------";
    }

    const long long hours = seconds / 3600;
    const long long minutes = (seconds % 3600) / 60;
    const long long secs = seconds % 60;

    // ! AI GENERATED CODE START ! //
    // ? Prompt: Showed Gemeni the function along with the message: ? //
    // ? "I need this function to return a string formatted in HH:MM:SS of the current time variables. ? //
    // Formats the time as HH:MM:SS and returns it.

    stringstream ss;
    ss << setfill('0') << setw(2) << hours << ":" << setfill('0') << setw(2) << minutes << ":" << setfill('0') << setw(2) << secs;
    return ss.str();

    // ! AI GENERATED CODE END ! //
}

void Game::renderHighScores()
{
    while (true)
    {
        Game::clear();
        cout << Color::Bold << Color::BrightMagenta << "=====|||  HIGH SCORES  |||=====" << Color::Reset << endl;
        cout << endl;

        // A For-Each loop to go through each difficulty and print its high scores.
        // ! LOOKED UP HOW TO LOOP THROUGH AN UNORDERED_MAP VIA GEMENI ! //
        for (const auto &[diffName, diffInfo] : Difficulty)
        {
            // The difficulty name
            cout << Color::Bold << diffInfo.diffColor << diffInfo.name << Color::Reset << endl;

            // Get highscores for this difficulty
            const int *scores = highScoreSaver.getHighScores(diffInfo);

            // Print each of the 5 high scores for this difficulty
            for (int i = 0; i < 5; i++)
            {
                cout << "  " << (i + 1) << ". " << secondsFormat(scores[i]) << endl;
            }

            cout << endl;
        }

        cout << "Press any button to return to the Main Menu..." << Color::Reset;

        Action act = InputHandler::getAction();
        if (act != UNKNOWN)
        {
            currentScreen = MAIN_MENU;
            return;
        }
    }
}