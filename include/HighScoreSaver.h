#include <string>
#include <fstream>
using namespace std;

/*
? Description: The HighScoreSaver class is responsible for managing the high scores of the game.
* It contains the user's top 3 high scores and the path to the text file in which they will be stored.
* It provides methods to add a new score, save scores to the titular file, and load any available scores from the file on program start.
*/

#ifndef HIGHSCORE_SAVER_H
#define HIGHSCORE_SAVER_H

class HighScoreSaver
{
private:
    static const int MAX_SCORES = 3;                        // Keeps top 3 high scores
    const string SAVEFILE = "../HighScores/highscores.txt"; // The path of the file in which highscores will be kept.
    int highScores[MAX_SCORES] = {};                        // Array to store high scores (initialized to zeros)

public:
    // Adds a new score to the highScores array. If the array exceeds MAX_SCORES, it removes the lowest score.
    void addScore(int score) {}

    // Saves the current highScores array to the highscores.txt file.
    void saveToFile() {}

    // Loads high scores from the highscores.txt file into the highScores array.
    // If the file has less than 3 entries, the remaining scores are filled with zeros.
    // '0' will be displayed as "N/A" in the game UI.
    void loadFromFile() {}

    // ========= Getters ========= //
    const int *getHighScores() const { return highScores; }
    int getMaxScore() const { return MAX_SCORES; }
};

#endif // HIGHSCORE_SAVER_H