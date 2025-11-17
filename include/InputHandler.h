#include <conio.h> // For _getch()

/*
? Description: The InputHandler class is responsible for capturing and returning user input from the keyboard.
* the `getkey()` function captures a key press, using a different method appropirate to the operating system.
* It also contains an `Action` enum that maps specific key presses to different game actions such as movement, digging, and so on.
* Other classes (mainly the Game and Board classes) will use the `getAction()` function to get the player's key press and act accordingly.
*/

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

enum Action
{
    UP,     // 'w' or Up Arrow
    LEFT,   // 'a' or Left Arrow
    DOWN,   // 's' or Down Arrow
    RIGHT,  // 'd' or Right Arrow
    DIG,    // 'e', Space, or Enter
    FLAG,   // 'f'
    QUIT,   // 'q'
    UNKNOWN // Any other key
};

class InputHandler
{
public:
    // Records a key press and returns the ASCII value of the pressed key.
    // Uses different methods based on the OS.
    int getkey() {}

    // Gets a key press and maps it to an Action enum. It then returns that Action.
    // The Board and Game classes will use this to determine what to do.
    Action getAction() {}
};

#endif // INPUT_HANDLER_H