#include <iostream>
#include "../include/Game.h"
#include "../include/Color.h"
using namespace std;

// ! AI GENERATED CODE START ! //
// ? Made For The Purpose Of: Hiding The Cursor In The Console Window ? //
using byte = unsigned char;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

// Hides the little white box that appears to indicate the cursor position in the console. Works on both Windows and Unix-based systems.
void HideCursor()
{
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    std::cout << "\033[?25l";
#endif
}
// ! AI GENERATED CODE END ! //

int main()
{
    HideCursor();

    cout << Color::BgBlack;

    Game game;
    game.init();

    return 0;
}