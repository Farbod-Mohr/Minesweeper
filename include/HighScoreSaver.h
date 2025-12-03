#include <string>
#include <fstream>
#include "Game.h"
using namespace std;

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
    static const int MAX_SCORES = 5;                        // Keeps top 5 high scores for a given difficulty.
    const string SAVEFILE = "../HighScores/highscores.txt"; // The path of the file in which highscores will be kept.
    int highScores[3][MAX_SCORES] = {};                     // Array to store high scores for each difficulty.

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