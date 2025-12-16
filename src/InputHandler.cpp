#include "../include/InputHandler.h"
#include <cstdio>

// Mapping key presses to Action enums.
const unordered_map<int, Action> InputHandler::keyMap = {

    // Up
    {'w', UP},
    {'W', UP},
    {72, UP}, // Up Arrow

    // Left
    {'a', LEFT},
    {'A', LEFT},
    {75, LEFT}, // Left Arrow

    // Down
    {'s', DOWN},
    {'S', DOWN},
    {80, DOWN}, // Down Arrow

    // Right
    {'d', RIGHT},
    {'D', RIGHT},
    {77, RIGHT}, // Right Arrow

    // Dig
    {'e', DIG},
    {'E', DIG},
    {13, DIG}, // Enter
    {32, DIG}, // Space

    // Flag
    {'q', FLAG},
    {'Q', FLAG},

    // Quit
    {27, QUIT} // Esc key
};

// Captures a key press from the keyboard and returns its integer value.
int InputHandler::getkey()
{
#ifdef _WIN32
    // Windows: Use _getch() from <conio.h>
    return _getch();
#else
    // Linux/Unix: Use termios to capture key press without echo, mimicking _getch()
    // ! AI GENERATED CODE START ! //
    // ? Prompt: Showed Gemeni the function header along with the message: ? //
    // ? How could I write the same function that _getch() does on Windows but for Linux/Unix systems? ? //
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();

    // Handle escape sequences for arrow keys
    if (ch == 27) // ESC
    {
        int next = getchar();
        if (next == '[')
        {
            int arrow = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            switch (arrow)
            {
            case 'A':
                return 72; // Up
            case 'B':
                return 80; // Down
            case 'C':
                return 77; // Right
            case 'D':
                return 75; // Left
            }
            return 27; // Unknown escape sequence
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return 27; // Just ESC key
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
    // ! AI GENERATED CODE END ! //
#endif
}

// Captures a key press and returns the corresponding Action enum.
Action InputHandler::getAction()
{
    int key = InputHandler::getkey();
    auto action = keyMap.find(key); // Auto type because it can be a string or an int

    // Check if the key exists in the map
    if (keyMap.count(key))
    {
        return keyMap.at(key); // Key found successfully; Action enum returned
    }
    else
    {
        return UNKNOWN; // key not found; return UNKNOWN Action
    }
}