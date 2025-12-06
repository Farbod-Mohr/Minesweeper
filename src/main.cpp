#include <iostream>
#include "../include/InputHandler.h"
using namespace std;

int main()
{

    // JUST A TEST TO SEE IF THE PROGRAM IS COMPILING CORRECTLY
    cout << "Hello World!" << endl;
    // ---------------------------------------------

    while (true)
    {
        Action action = InputHandler::getAction();
        if (action == UP)
            cout << "UP" << endl;
        else if (action == DOWN)
            cout << "DOWN" << endl;
        else if (action == LEFT)
            cout << "LEFT" << endl;
        else if (action == RIGHT)
            cout << "RIGHT" << endl;
        else if (action == DIG)
            cout << "DIG" << endl;
        else if (action == FLAG)
            cout << "FLAG" << endl;
        else if (action == QUIT)
        {
            cout << "QUIT" << endl;
            break;
        }
        else
        {
            cout << "UNKNOWN KEY" << endl;
        }
    }

    return 0;
}
