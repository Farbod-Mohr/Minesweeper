#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <unordered_map>
using namespace std;

/*
? Description: The InputHandler class is responsible for capturing and returning user input from the keyboard.
* the `getkey()` function captures a key press, using a different method appropirate to the operating system.
* It also contains an `Action` enum that maps specific key presses to different game actions such as movement, digging, and so on.
* Other classes (mainly the Game and Board classes) will use the `getAction()` function to get the player's key press and act accordingly.
! Note: This is a static class, meaning no objects of it can be made.
*/

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

enum Action
{
    UP,     // 'w', 'W' or Up Arrow
    LEFT,   // 'a', 'A' or Left Arrow
    DOWN,   // 's', 'S' or Down Arrow
    RIGHT,  // 'd', 'D' or Right Arrow
    DIG,    // 'e', Space or Enter
    FLAG,   // 'q'
    QUIT,   // esc key
    UNKNOWN // Any other key
};

class InputHandler
{
private:
    // An unordered map that connects key presses to their respective Action enums.
    static const unordered_map<int, Action> keyMap;

    // The constructor and destructor are private to prevent any objects of this class being made.
    InputHandler() {};
    ~InputHandler() {};

    // Captures a key press from the keyboard and returns its integer value.
    // Uses two different methods depending on the operating system.
    static int getkey();

public:
    // Captures a key press and returns the corresponding Action enum.
    static Action getAction();
};

#endif // INPUT_HANDLER_H