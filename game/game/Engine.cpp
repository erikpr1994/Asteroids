#include <iostream>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"

Game game;

extern Player player;

void InitGame() {
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);

    InitPlayer();

    while (!game.gameOver) {
        std::cout << "Hola, soy la consola.";
        game.gameOver = true;
    }
}

void EndGame() {
    FASG::DestroyConsole();
}

void AlignCenter() {
    game.screenCenter.x = game.CONSOLE_WIDTH * 0.5;
    game.screenCenter.y = game.CONSOLE_HEIGHT * 0.5;
}