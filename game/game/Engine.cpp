#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Asteroid.h"
#include "Menu.h"
#include <conio.h>

Game game;

bool isDeath = false;
bool isDeathByOutside = false;
bool isDeathByChoqueConAsteroide = false;
bool isDeathByNaveCabrona = false;

extern Player player;
extern Asteroid asteroid;

void GetConsoleCenter();
void ZoneSpawn();
bool InMapRanged(int x, int y);
void Outside();
void MiColision(std::string tag1, std::string tag2);
void DrawHUD();
void paintDeath();

std::string HUDMessage;

// Todo el tema de gameOver cambiarlo a nombre de ExitGame
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

	ZoneSpawn();
	
	Sprite::SetCollisionCallback(MiColision);

    while (!game.gameOver) {
		ShowMenu();
		Outside();
		IsPlayerDeath();

		InputPlayer();
		UpdatePlayer();
        DrawPlayer();
		Asteroids();
		MoveAsteroid();
		DrawAsteroid();
		DrawHUD();

		FASG::RenderFrame();

		while (isDeath) {
			paintDeath();
			InitAsteroids();

			FASG::RenderFrame();
			while (_kbhit()){
				_getch();

				if(FASG::IsKeyDown(' ')){
					isDeath = false;
					isDeathByOutside = false;
					isDeathByChoqueConAsteroide = false;
				}
			}
		}
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

bool InMapRanged(int x, int y) {
	if ((x >= 0) && (x < game.CONSOLE_WIDTH-13) && (y >= 0) && (y < game.CONSOLE_HEIGHT-7)) {
		return true;
	}
	return false;
}

void Outside() {
	if (!InMapRanged(player.sprite1.Location.x, player.sprite1.Location.y))
	{
		if (player.sprite1.Location.y <= 0) {
			player.sprite1.Location.y = 1;
		}
		else {
			player.sprite2.Location.y = player.sprite1.Location.y;
			player.sprite2.Location.x = player.sprite1.Location.x;
			player.sprite3.Location.y = player.sprite1.Location.y;
			player.sprite3.Location.x = player.sprite1.Location.x;
			isDeath = true;
			isDeathByOutside = true;
			player.lastInputPlayer = EInputPlayer::DEATH;
		}
	}
}

void paintDeath() {
	if (isDeathByOutside) {
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Te has salido de la pantalla", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
	if (isDeathByChoqueConAsteroide) {
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Te has chocado con un meteorito", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA 2 VECES ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
	if(isDeathByNaveCabrona){
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Una nave te ha matado", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(game.CONSOLE_HEIGHT * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
}

void MiColision(std::string tag1, std::string tag2) {
	isDeath = true;
	isDeathByChoqueConAsteroide = true;
	player.lastInputPlayer = EInputPlayer::DEATH;
}

void DrawHUD()
{
	FASG::WriteStringBuffer(0, 0, "FPS: " + std::to_string(1 / FASG::GetDeltaTime()), FASG::EForeColor::LightRed);
	FASG::WriteStringBuffer(0, 2, "Mueve la nave (WASD) para detectar la colision con los asteroides", FASG::EForeColor::LightWhite);
	FASG::WriteStringBuffer(0, 3, "X: para salir ordenadamente del programa", FASG::EForeColor::LightCyan);

	FASG::WriteStringBuffer(game.screenCenter.y, FASG::EAligned::CENTER, HUDMessage, EForeColor::Green);
	HUDMessage = "";
}

