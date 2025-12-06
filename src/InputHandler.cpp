
/*
## Feature 0: Input Handling System

**Trigger**: User presses a key on the keyboard.

**Input Needed**: Key press from the user.

**Implementation Flow**:

1. In the `InputHandler` class, implement the static function `getkey()`. This function will use `_getch()` from the `<conio.h>` library to capture a key press on windows. For other operating systems it will use a custom function that captures key presses in a similar way (without printing to the console).
2. Implement the static function `getAction()` in the `InputHandler` class. This function will call `getkey()` to get the key press and then map it to the corresponding `Action` enum value based on the key pressed. For example, 'w' or Up Arrow will map to `Action::UP`, 'a' or Left Arrow to `Action::LEFT`, and so on. It will use the keyMap hashmap to do this.
3. Other classes, mainly the `Game` and `Board` classes, will call `InputHandler::getAction()` to get the user's input and act accordingly.

**Data Modified**: None.

**Completion**:

- The program can capture user key presses and map them to game actions.

**Functions Used**:

- `InputHandler::getkey()`
- `InputHandler::getAction()`
*/

#include "InputHandler.h"

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
    // ! AI GENERATED CODE ! // ! NEEDS TESTING ! //
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
    // ! AI GENERATED CODE ! // ! NEEDS TESTING ! //
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