#include <iostream>
#include "../include/Game.h"
using namespace std;

int main()
{
    // Hides the cursor in the console window. This code is also called in Color::Reset, so the cursor will remain hidden after the reset code is used.
    cout << "\033[?25l";

    Game game;
    game.init();

    return 0;
}