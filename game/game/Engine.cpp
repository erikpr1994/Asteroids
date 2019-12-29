#include <iostream>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"

Game game;

void InitGame() {
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);

    while (!game.gameOver) {
        std::cout << "Hola, soy la consola.";
        game.gameOver = true;
    }
}

void EndGame() {
    FASG::DestroyConsole();
}