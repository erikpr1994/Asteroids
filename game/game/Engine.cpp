#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"

Game game;

void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"

    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);

    GetConsoleCenter();

    InitPlayer();

    while (!game.gameOver) {
		InputPlayer();
		UpdatePlayer();
        DrawPlayer();

        FASG::RenderFrame();
    }
}

void EndGame() {
    FASG::DestroyConsole();
}

void GetConsoleCenter() {
    game.screenCenter.x = game.CONSOLE_WIDTH * 0.5;
    game.screenCenter.y = game.CONSOLE_HEIGHT * 0.5;
}