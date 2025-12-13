#include "../include/HighScoreSaver.h"
#include "../include/Game.h"
#include <fstream>
using namespace std;

int HighScoreSaver::timeStringToSeconds(const string &time_string) const
{
    // ! AI GENERATED CODE START ! //
    // ? Prompt: Showed Gemeni the function header along with the message: ? //
    // ? How could I parse a HH:MM:SS formatted string and convert it to seconds? ? //

    int hours = 0, minutes = 0, seconds = 0;

    sscanf_s(time_string.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);

    return hours * 3600 + minutes * 60 + seconds;

    // ! AI GENERATED CODE START ! //
}

// Helper function to get the difficulty index (0=Easy, 1=Medium, 2=Hard)
int HighScoreSaver::getDifficultyIndex(DiffInfo difficulty) const
{
    if (difficulty.name == "EASY")
    {
        return 0;
    }
    else if (difficulty.name == "MEDIUM")
    {
        return 1;
    }
    else if (difficulty.name == "HARD")
    {
        return 2;
    }

    return -1; // Just to silence compiler warnings. This case should never happen.
}

void HighScoreSaver::addScore(string time, DiffInfo difficulty)
{
    int diffIndex = getDifficultyIndex(difficulty);

    int timeInSeconds = timeStringToSeconds(time);

    // Scores must be sorted from best to worst, meaning that position 0 is the best score (lowest time) and position 4 is the worst score (highest time).

    // Index position to insert the new score
    int insertPos = -1;

    // Find the correct position to insert the new score by comparing it with existing scores.
    for (int i = 0; i < MAX_SCORES; i++)
    {
        if (highScores[diffIndex][i] == 0 || timeInSeconds < highScores[diffIndex][i])
        {
            insertPos = i;
            break;
        }
    }

    // If no valid position found, the score is not good enough and thus will not be saved.
    if (insertPos == -1)
    {
        return;
    }

    // If the new score is valid, scores that are lower than it need to be shifted down by 1 index to make space for it.
    // The score at index 4 (`MAX_SCORES - 1`) will be dropped if the array is already full.
    for (int i = MAX_SCORES - 1; i > insertPos; i--)
    {
        highScores[diffIndex][i] = highScores[diffIndex][i - 1];
    }

    // Insert the new score for the given difficulty.
    highScores[diffIndex][insertPos] = timeInSeconds;

    // Save the updated scores to the file.
    saveToFile();
}

void HighScoreSaver::saveToFile()
{
    // Attempt to open the file for saving.
    ofstream file(SAVEFILE);

    // If the file cannot be opened, throw an error.
    if (!file.is_open())
    {
        throw runtime_error("Couldn't open 'highscores.txt' to save your scores! Perhaps the file path is incorrect?");
    }

    // If the file can be opened, write the high scores to it by looping through the `highScores` array.
    for (int diff = 0; diff < 3; diff++)
    {
        for (int i = 0; i < MAX_SCORES; i++)
        {
            file << highScores[diff][i] << "\n";
        }
    }

    // Close the file when done.
    file.close();
}

void HighScoreSaver::loadFromFile()
{
    // Attempt to open the file for reading.
    ifstream file(SAVEFILE);

    // If the file cannot be opened, throw an error.
    if (!file.is_open())
    {
        throw runtime_error("Couldn't open 'highscores.txt' to load your scores! Perhaps the file path is incorrect?");
    }

    // If the file can be opened, load the high scores into the `highScores` array by looping through it.
    for (int diff = 0; diff < 3; diff++)
    {
        for (int i = 0; i < MAX_SCORES; i++)
        {
            file >> highScores[diff][i];
        }
    }

    // Close the file when done.
    file.close();
}

const int *HighScoreSaver::getHighScores(DiffInfo difficulty) const
{
    // Gets the appropriate index for the given difficulty.
    int diffIndex = getDifficultyIndex(difficulty);

    // Returns a pointer to the array of high scores for the given difficulty.
    return highScores[diffIndex];
}
