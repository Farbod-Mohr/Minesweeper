#include <string>
#include <unordered_map>
#include "../include/Color.h"
#include "../include/Board.h"
using namespace std;

/*
? Description: The Game class manages the overall state and flow of the program.
* Its intended use is to create an object of it in `main()` and then call its `init()` function to begin the game loop.
* It handles getting user input via the InputHandler class and affects the game state accordingly.
* It has information about the UI screens in the game, along with handling their rendering. The only screen that handles its own rendering is the minesweeper board, which is done via the Board class.
* It manages the timer for each game, calculating the total time taken when a game ends and displaying it to the player.
* It calculates the player's score based on time taken and difficulty, sending it to the HighScoreSaver class to be dealt with.
*/

#ifndef GAME_H
#define GAME_H

enum Screen
{
    MAIN_MENU,            // The screen in which the player can choose to start a new game, see high scores, or exit.
    DIFFICULTY_SELECTION, // The screen in which the player selects a difficulty for the new game.
    MINESWEEPER,          // The screen in which the player plays minesweeper.
    LOSS,                 // The screen shown when the player hits a mine. They can return to the main menu from here.
    WIN,                  // The screen shown when the player successfully clears the board without hitting any mines. They can return to the main menu from here.
    HIGH_SCORES,          // The screen showing the player's 5 highest scores for each mode. They can return to the main menu from here.
    EXIT                  // The screen shown when the player chooses to exit the game. It will have display a goodbye message and end the program.
};

// Represents the information about a difficulty level.
struct DiffInfo
{
    string name;           // The name of the difficulty (Easy/Medium/Hard). This is mainly for display purposes.
    int row;               // The row count of the board (excluding walls).
    int column;            // The column count of the board (excluding walls).
    int mineCount;         // The number of mines on the board.
    string_view diffColor; // The color associated with the difficulty for rendering purposes. Green for Easy, Yellow for Medium, Red for Hard.

    // Constructor
    DiffInfo(string name, int row, int column, int mineCount) : name(name), row(row), column(column), mineCount(mineCount)
    {
        if (name == "EASY")
        {
            diffColor = Color::BrightGreen;
        }
        else if (name == "MEDIUM")
        {
            diffColor = Color::BrightYellow;
        }
        else if (name == "HARD")
        {
            diffColor = Color::BrightRed;
        }
        else // To handle the default "Nil" difficulty.
        {
            diffColor = Color::White;
        }
    }
};

// An unordered map that connects difficulty names to their respective DiffInfo structs.
const unordered_map<string, DiffInfo> Difficulty = {
    {"Easy", {"EASY", 9, 9, 10}},
    {"Med", {"MEDIUM", 16, 16, 40}},
    {"Hard", {"HARD", 16, 30, 99}}};

class Game
{
private:
    Screen currentScreen = MAIN_MENU; // The current screen the player is on. Always starts at the main menu.
    time_t startTime = 0;             // The time at which the game started. This will be used to figure out how long a game takes.
    time_t endTime = 0;               // The time at which the game ended. This will be used to figure out how long a game takes.

    DiffInfo currentDiff = DiffInfo{"Nil", 0, 0, 0}; // The difficulty selected for the current game. Used to create the board and calculate score.

    // struct holding boolean values for each button in the UI.
    // These will be set to true when the corresponding button is selected, changing the rendering from white to bright cyan.
    // They will also be used to determine what action to take when the player pressed the DIG key (Enter/Space/'e').
    // they will also be used to determine what happens when the player attempts to navigate the UI using the movement keys (wasd/arrow keys).
    // When the game loads, MM_newGame will be selected by default.
    struct UIButtons
    {
        // Main Menu
        bool MM_newGame = true; // Selected on program start
        bool MM_highScores = false;
        bool MM_exit = false;

        // Difficulty Selection
        bool DS_easy = false;
        bool DS_medium = false;
        bool DS_hard = false;

        // Game Over
        bool GO_return = false;

        // Win
        bool W_return = false;

        // High Scores
        bool HS_return = false;

    } uiButtons;

    // The function to clear the screen is different based on the operating system, so this function handles that.
    void clear() const;

    // Makes the Board for a new game with the selected difficulty.
    // It creates a new Board object with the appropriate parameters and resets the timer.
    // It then returns the created Board object to be run.
    Board makeNewGame(DiffInfo selected_diff);

    // Returns a formatted string of the total time taken for the current game via the `startTime` and `endTime` variables.
    // The timer isn't actually displayed during gameplay, due to the unfortunate fact that the methods to get user input are halting functions.
    // A player's time will only be shown on the WIN screen after they successfully clear the board.
    // Yes, this means that the user can TECHNICALLY cheat by changing their system clock to have a negative time taken, but they would never do that... right? >->
    string calcTime();

    // Sends both the time taken to beat the game (as decided by the `calcTime()` function) and the `currentDiff` variable to the HighScoreSaver class to be saved.
    // The HighScoreSaver aver class will handle saving the score if appropriate.
    // A 'score' is just the time taken to beat a given difficulty. The 5 best times for each difficulty are kept as high scores.
    void saveScore(string total_time);

    // A helper function that returns a formatted string representing the given DiffInfo struct. Useful for rendering difficulty information in the UI.
    string printDiff(const DiffInfo &diff) const;

    // ======== Rendering Functions ========= //
    void renderMainMenu();
    void renderDiffSelection();
    void renderMinesweeper();
    void renderGameOver();
    void renderWin();
    void renderHighScores();
    void renderExit() const;

public:
    // Starts the main game loop, creating any needed objects and begins the process of rendering and input handling.
    // Rendering functions will be called from within this function based on the currentScreen value.
    void init();
};

#endif // GAME_H