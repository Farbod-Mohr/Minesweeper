#include <string>
using namespace std;

// DiffInfo is declared here to avoid circular dependency issues. If I were to include the Game class here, it would cause problems since the Game class also includes HighScoreSaver.
struct DiffInfo;

/*
? Description: The HighScoreSaver class is responsible for managing the high scores of the game.
* It contains the user's top 5 high scores for each difficulty (Easy, Medium, Hard) and the path to the text file in which they will be stored.
* It provides methods to add a new score, save scores to the titular file, and load any available scores from the file on program start.
*/

#ifndef HIGHSCORE_SAVER_H
#define HIGHSCORE_SAVER_H

class HighScoreSaver
{
private:
    static const int MAX_SCORES = 5;                     // Keeps top 5 high scores for a given difficulty.
    const string SAVEFILE = "HighScores/highscores.txt"; // The path of the file in which highscores will be kept (relative to project root).
    int highScores[3][MAX_SCORES] = {};                  // Array to store high scores for each difficulty.

    // Helper function that converts HH:MM:SS string to total seconds. Used for comparing and storing scores.
    int timeStringToSeconds(const string &timeStr) const;

    // Helper function that converts difficulty names into indexes for easier sorting and use in the `HighScores` array.
    // Easy is 0, Medium is 1, and Hard is 2.
    int getDifficultyIndex(DiffInfo difficulty) const;

public:
    // Adds a new score to the highScores array for the specified difficulty. If the array exceeds MAX_SCORES, it removes the lowest score.
    void addScore(string time, DiffInfo difficulty);

    // Saves the current highScores array to the highscores.txt file.
    void saveToFile();

    // Loads high scores from the highscores.txt file into the highScores array.
    // If the file has less than 5 entries per difficulty, the remaining scores are filled with zeros.
    // '0' will be displayed as "--------" in the game UI.
    void loadFromFile();

    // ========= Getters ========= //

    // Returns a pointer to the array of high scores for the specified difficulty. Used for rendering the high score screen.
    const int *getHighScores(DiffInfo difficulty) const;
};

#endif // HIGHSCORE_SAVER_H