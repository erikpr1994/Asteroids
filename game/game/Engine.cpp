#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Asteroid.h"
#include "Menu.h"
#include <conio.h>

Game game;

extern Player player;
extern Asteroid asteroid;

void GetConsoleCenter();
void ZoneSpawn();
void miColision(std::string tag1, std::string tag2);
void DrawHUD();

std::string HUDMessage;

bool GetGameOver() {
	return game.gameOver;
}

void SetGameOver(bool gameOver) {
	game.gameOver = gameOver;
}

void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);
	FASG::ShowConsoleCursor(false);
	//FASG::SetFontSizeRatio(FASG::ConsoleFontRatios::_8x8);
    GetConsoleCenter();

	InitMenu();
	ShowMenu();
	// para la portada*********************************************************

	ZoneSpawn();
	InitAsteroid();
    InitPlayer();

	Sprite::SetCollisionCallback(miColision);

    while (!game.gameOver) {
		IsPlayerDeath();
		InputPlayer();
		UpdatePlayer();
        DrawPlayer();
		DrawAsteroid();
		DrawHUD();

		/*
		while (_kbhit > 0)
			_getch();
		*/

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
	player.lastInputPlayer = EInputPlayer::DEATH;
	//HUDMessage = "Colision de " + tag1 + " y " + tag2;
	HUDMessage = tag1 + " ha colisionado con " + tag2;

}

void DrawHUD()
{
	FASG::WriteStringBuffer(0, 0, "FPS: " + std::to_string(1 / FASG::GetDeltaTime()), FASG::EForeColor::LightRed);
	FASG::WriteStringBuffer(0, 2, "Mueve la nave (WASD) para detectar la colision con los asteroides", FASG::EForeColor::LightWhite);
	FASG::WriteStringBuffer(0, 3, "X: para salir ordenadamente del programa", FASG::EForeColor::LightCyan);

	FASG::WriteStringBuffer(game.screenCenter.y, FASG::EAligned::CENTER, HUDMessage, EForeColor::Green);
	HUDMessage = "";
}

void GravityForce()
{
	asteroid.currentSpeed += game.gravity * FASG::GetDeltaTime();
	asteroid.sprite.Location.y += asteroid.currentSpeed * FASG::GetDeltaTime() * 0.5f;
}