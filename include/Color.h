#include <string_view>
using namespace std;

#ifndef COLORS_H
#define COLORS_H

/*
! THIS FILE HAS BEEN GENERATED VIA AN AI PROGRAM AND IS NOT MY OWN WORK, NOR DO I CLAIM IT TO BE.
! I AM INCLUDING IT HERE TO MAKE THE RENDERING OF THE MINESWEEPER BOARD PRETTIER AND MORE COLORFUL.
? Description: The Color namespace contains ANSI escape codes for various text colors, background colors, and text styles.
* These will be used in the rendering of the minesweeper board within the terminal.

??? Example Usage:
```cpp
#include "Color.h"
#include <iostream>
using namespace std;

cout << Color::Red << "This text is red!" << Color::Reset << endl;
```
*/

namespace Color
{
    // Reset
    inline constexpr string_view Reset = "\033[0m";

    // Regular colors
    inline constexpr string_view Black = "\033[30m";
    inline constexpr string_view Red = "\033[31m";
    inline constexpr string_view Green = "\033[32m";
    inline constexpr string_view Yellow = "\033[33m";
    inline constexpr string_view Blue = "\033[34m";
    inline constexpr string_view Magenta = "\033[35m";
    inline constexpr string_view Cyan = "\033[36m";
    inline constexpr string_view White = "\033[37m";

    // Bright/Bold colors
    inline constexpr string_view BrightBlack = "\033[90m";
    inline constexpr string_view BrightRed = "\033[91m";
    inline constexpr string_view BrightGreen = "\033[92m";
    inline constexpr string_view BrightYellow = "\033[93m";
    inline constexpr string_view BrightBlue = "\033[94m";
    inline constexpr string_view BrightMagenta = "\033[95m";
    inline constexpr string_view BrightCyan = "\033[96m";
    inline constexpr string_view BrightWhite = "\033[97m";

    // Background colors
    inline constexpr string_view BgBlack = "\033[40m";
    inline constexpr string_view BgRed = "\033[41m";
    inline constexpr string_view BgGreen = "\033[42m";
    inline constexpr string_view BgYellow = "\033[43m";
    inline constexpr string_view BgBlue = "\033[44m";
    inline constexpr string_view BgMagenta = "\033[45m";
    inline constexpr string_view BgCyan = "\033[46m";
    inline constexpr string_view BgWhite = "\033[47m";

    // Bright background colors
    inline constexpr string_view BgBrightBlack = "\033[100m";
    inline constexpr string_view BgBrightRed = "\033[101m";
    inline constexpr string_view BgBrightGreen = "\033[102m";
    inline constexpr string_view BgBrightYellow = "\033[103m";
    inline constexpr string_view BgBrightBlue = "\033[104m";
    inline constexpr string_view BgBrightMagenta = "\033[105m";
    inline constexpr string_view BgBrightCyan = "\033[106m";
    inline constexpr string_view BgBrightWhite = "\033[107m";

    // Text styles
    inline constexpr string_view Bold = "\033[1m";
    inline constexpr string_view Dim = "\033[2m";
    inline constexpr string_view Italic = "\033[3m";
    inline constexpr string_view Underline = "\033[4m";
    inline constexpr string_view Blink = "\033[5m";
    inline constexpr string_view Reverse = "\033[7m";
    inline constexpr string_view Hidden = "\033[8m";
    inline constexpr string_view Strikethrough = "\033[9m";
}

#endif // COLORS_H