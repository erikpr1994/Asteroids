#include <iostream>
#include <time.h>
#include "Engine.h"
#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Asteroid.h"
#include "Menu.h"
#include "Stars.h"
#include "Enemies.h"
#include <conio.h>

Game game;

void CalcConsoleCenter();
void ZoneSpawn();
bool InMapRanged(int x, int y);
void Outside();
void MiColision(std::string tag1, std::string tag2);
void DrawHUD();
void paintDeath();

// Todo el tema de gameOver cambiarlo a nombre de ExitGame
bool GetIsGameClosed() {
	return game.isGameClosed;
}

void SetIsGameClosed(bool value) {
	game.isGameClosed = value;
}

float GetPuntuation() {
	return game.puntuacion;
}

void UpdatePuntuation() {
	float puntuation = GetPuntuation();
	puntuation += FASG::GetDeltaTime()*0.1f;
	SetPuntuation(puntuation);
}

void SetPuntuation(float value) {
	game.puntuacion = value;
}

void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);
	FASG::ShowConsoleCursor(false);
	// FASG::SetFontSizeRatio(FASG::ConsoleFontRatios::_8x8);
    CalcConsoleCenter();
	SetIsGameClosed(false);

	InitMenu();

	ZoneSpawn();
	
	Sprite::SetCollisionCallback(MiColision);

	while (!GetIsGameClosed()) {
		ShowMenu();
		Outside();
		IsPlayerDeath();

		InputPlayer();
		UpdatePlayer();
		DrawPlayer();
		Asteroids();
		MoveAsteroid();
		DrawAsteroid();
		Enemies();
		MoveEnemies();
		DrawEnemies();
		MoveEnemyShoots();
		DrawEnemyShoots();
		MoveShoot();
		DrawShoots();
		MoveStars();
		DrawStars();
		UpdatePuntuation();
		DrawHUD();

		FASG::RenderFrame();

		while (IsPlayerDead()) {
			paintDeath();
			
			FASG::RenderFrame();
			while (_kbhit()){
				_getch();

				if(FASG::IsKeyDown(' ')){
					SetPlayerDead(false);
					SetPlayerDeadByCollisionWithAsteroid(false);
					SetPlayerDeadByGoOutsideScreen(false);
					SetPlayerDeadByShip(false);
					SetPuntuation(0);
				}
			}
		}
	} 
}


void EndGame() {
    FASG::DestroyConsole();
}

void CalcConsoleCenter() {
    game.screenCenter.x = game.CONSOLE_WIDTH * 0.5;
    game.screenCenter.y = game.CONSOLE_HEIGHT * 0.5;
}

int GetScreenCenterX() {
	return game.screenCenter.x;
}

int GetScreenCenterY() {
	return game.screenCenter.y;
}

int GetScreenEndConsoleX() {
	return game.CONSOLE_WIDTH;
}

int GetScreenStartConsoleX() {
	return 0;
}

int GetScreenEndConsoleY() {
	return game.CONSOLE_HEIGHT;
}

int GetScreenStartConsoleY() {
	return 0;
}

int GetZoneSpawnX() {
	return game.zoneSpawn.x;
}

int GetZoneSpawnY() {
	return game.zoneSpawn.y;
}

void ZoneSpawn() {
	game.zoneSpawn.x = (rand() % (game.CONSOLE_WIDTH - 35)) + 35;
	game.zoneSpawn.y = 0;
}


void paintDeath() {
	if (IsPlayerDeadByGoOutsideScreen()) {
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Te has perdido en el espacio", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
	if (IsPlayerDeadByCollisionWithAsteroid()) {
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Te has chocado con un meteorito", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA 2 VECES ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
	if(IsPlayerDeadByShip()){
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER: Una nave te ha destruido", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
}

void MiColision(std::string tag1, std::string tag2) {
	for(int i = 0; i < GetMaxNumberOfAsteroids() ;i++){
		if(tag1 == "asteroid"+i && tag2 == "nave" || tag1 == "nave" && tag2 == "asteroid"+i){
			SetPlayerDead(true);
			SetPlayerDeadByCollisionWithAsteroid(true);
			SetLastInputPlayer(EInputPlayer::DEATH);
		}
	}

	for (int i = 0; i < GetMaxNumberOfAsteroids(); i++) {
		for(int j = 0; j < GetMaxNumberOfShoots();j++){
			if (tag1 == "asteroid" + i && tag2 == "disparo"+j || tag1 == "disparo"+j && tag2 == "asteroid" + i) {
				SetAsteroidLocation(9452, 9452, i);
				SetShootLocation(-8000, -8000, j);
				float puntuation = GetPuntuation() + GetAsteroidDeadPuntuation(i);
				SetPuntuation(puntuation);
			}
		}
	}

	for (int i = 0; i < GetMaxNumberOfEnemies(); i++) {
		for (int j = 0; j < GetMaxNumberOfShoots(); j++) {
			if (tag1 == "enemy" + i && tag2 == "disparo" + j || tag1 == "disparo" + j && tag2 == "enemy" + i) {
				SetEnemyLocation(9452, 9452, i);
				SetShootLocation(-8000, -8000, j);
				float puntuation = GetPuntuation() + GetEnemyPoints(i);
				SetPuntuation(puntuation);
				SetCoolDownBetweenShoots(5.f);
			}
		}
	}

	for (int i = 0; i < GetMaxNumberOfEnemiesShoots(); i++) {
		for(int j = 0; j < GetMaxNumberOfEnemies();j++){
			int shipWhoShoot = getWhoShoot(i, j);
			if (tag1 == "nave" && tag2 == "enemyShoot" + i || tag1 == "enemyShoot" + i && tag2 == "nave") {
			switch (shipWhoShoot)
				{
				case 0:
					SetPlayerLife(GetPlayerLife() - GetDamage(0));
					break;
				case 1:
					SetPlayerLife(GetPlayerLife() - GetDamage(1));
					break;
				case 2:
					SetPlayerLife(GetPlayerLife() - GetDamage(2));
					break;
				}
				SetShootEnemyLocation(8000, 8000, i);
			}
		}
		break;
	}
}

// Lo queremos mostrar así o diferente?
void DrawHUD()
{
	FASG::WriteStringBuffer(0, 0, "Puntuacion: " + std::to_string(GetPuntuation()), FASG::EForeColor::LightRed);
	FASG::WriteStringBuffer(0, 1, "Vida: " + std::to_string(GetPlayerLife()), FASG::EForeColor::LightRed);
}