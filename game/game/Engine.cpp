#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Asteroid.h"

Game game;
void GetConsoleCenter();
void ZoneSpawn();
void miColision(std::string tag1, std::string tag2);
void DrawHUD();

std::string HUDMessage;


void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);
	FASG::ShowConsoleCursor(false);
	//FASG::SetFontSizeRatio(FASG::ConsoleFontRatios::_8x8);
    GetConsoleCenter();
	ZoneSpawn();
	InitAsteroid();
    InitPlayer();

	Sprite::SetCollisionCallback(miColision);

    while (!game.gameOver) {
		InputPlayer();
		UpdatePlayer();
        DrawPlayer();
		DrawAsteroid();
		DrawHUD();

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

void ZoneSpawn() {
	game.zoneSpawn.x = (rand() % (game.CONSOLE_WIDTH - 35)) + 35;
	game.zoneSpawn.y = 0;
}

void miColision(std::string tag1, std::string tag2) {
	HUDMessage = "Colision de " + tag1 + " y " + tag2;
}

void DrawHUD()
{
	FASG::WriteStringBuffer(0, 0, "FPS: " + std::to_string(1 / FASG::GetDeltaTime()), FASG::EForeColor::LightRed);
	FASG::WriteStringBuffer(0, 2, "Mueve la nave (WASD) para detectar la colision con los asteroides", FASG::EForeColor::LightWhite);
	FASG::WriteStringBuffer(0, 3, "X: para salir ordenadamente del programa", FASG::EForeColor::LightCyan);

	FASG::WriteStringBuffer(game.screenCenter.y, FASG::EAligned::CENTER, HUDMessage, EForeColor::Green);
	HUDMessage = "";
}