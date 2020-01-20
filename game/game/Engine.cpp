#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"

Game game;

void GetConsoleCenter();

void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);
	FASG::ShowConsoleCursor(false);
    GetConsoleCenter();

	InitMap();

    // InitCamera();

    InitPlayer();

    while (!game.gameOver) {
		InputPlayer();
        // MoveCamera();
		UpdatePlayer();
        // CheckPlayerDeath();
        DrawPlayer();
		PaintMap();

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