#include <iostream>
#include "FAriasSimpleGraphics.h"

// Constantes y variables del juego
const int CONSOLE_WIDTH = 200, CONSOLE_HEIGHT = 50;
bool gameOver = false;

using namespace FASG;

int main()
{
    InitConsole(CONSOLE_WIDTH, CONSOLE_HEIGHT);

    while(!gameOver){}

    DestroyConsole();
}