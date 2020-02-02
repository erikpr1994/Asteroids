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

bool gameSongLoaded = false;
bool gameSongPlay = false;

FASG::MIDISound gameSong;

FASG::MIDISound deathSong;
bool gameDeathSongLoaded = false;
bool gameDeathSongPlay = false;

void InitGame() {
    srand((unsigned)time(NULL)); // Necesario para hacer el mapa y mostrar las "piedras"
    FASG::InitConsole(game.CONSOLE_WIDTH, game.CONSOLE_HEIGHT);
	FASG::ShowConsoleCursor(false);
		FASG::SetFontSizeRatio(FASG::ConsoleFontRatios::_8x8);
    CalcConsoleCenter();
	SetIsGameClosed(false);

	InitMenu();

	ZoneSpawn();
	
	Sprite::SetCollisionCallback(MiColision);

	while (!GetIsGameClosed()) {
		ShowMenu();
		if (!gameSongLoaded) {
			gameSong.LoadSound("SWM.mid");
			gameSongLoaded = true;
		}
		if (!gameSongPlay) {
			gameSong.Play();
			gameSongPlay = true;
		}

		Outside();
		IsPlayerDeath();

		InputPlayer();
		UpdatePlayer();
		DrawPlayer();
		Asteroids();
		
		Health(); //---
		//DrawHealth();//---
		
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
 			gameSong.Stop();
			gameSongPlay = false;
			if (!gameDeathSongLoaded) {
				deathSong.LoadSound("SWIM.mid");
			}
			if (!gameDeathSongPlay) {
				deathSong.Play();
			}

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
					deathSong.Stop();
					gameDeathSongPlay = false;
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
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "Te has perdido en el espacio", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 2, FASG::EAligned::CENTER, "PUNTUACION FINAL: " + std::to_string(GetPuntuation()), FASG::EForeColor::LightYellow);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);

	}
	if (IsPlayerDeadByCollisionWithAsteroid()) {
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "Te has chocado con un meteorito", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 2, FASG::EAligned::CENTER, "PUNTUACION FINAL: " + std::to_string(GetPuntuation()), FASG::EForeColor::LightYellow);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
	if (IsPlayerDeadByShip()) {
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 5, FASG::EAligned::CENTER, "GAME OVER", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 4, FASG::EAligned::CENTER, "Una nave te ha destruido", FASG::EForeColor::LightRed);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f - 2, FASG::EAligned::CENTER, "PUNTUACION FINAL: " + std::to_string(GetPuntuation()), FASG::EForeColor::LightYellow);
		FASG::WriteStringBuffer(GetScreenEndConsoleY() * 0.5f, FASG::EAligned::CENTER, "PRESIONA ESPACIO PARA VOLVER AL MENU", FASG::EForeColor::LightCyan);
	}
}

void MiColision(std::string tag1, std::string tag2) {
	for(int i = 0; i < GetMaxNumberOfAsteroids() ;i++){
		if(tag1 == "asteroid"+i && tag2 == "nave" || tag1 == "nave" && tag2 == "asteroid"+i){
			SetPlayerDead(true);
			SetPlayerDeadByCollisionWithAsteroid(true);
			SetAsteroidLocation(9452, 9452, i);
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
				SetActiveEnemies(i, false);
			}
		}
	}

	for (int i = 0; i < GetMaxNumberOfEnemiesShoots(); i++) {
		for(int j = 0; j < GetMaxNumberOfEnemies();j++){
			if (tag1 == "nave" && tag2 == "enemyShoot" + i || tag1 == "enemyShoot" + i && tag2 == "nave") {
				int shipWhoShoot = getWhoShoot(i, j);
				switch (shipWhoShoot)
				{
				case 0:
					SetPlayerLife(GetPlayerLife() - GetDamage(0));
					SetShootEnemyLocation(8000, 8000, i);
					break;
				case 1:
					SetPlayerLife(GetPlayerLife() - GetDamage(1));
					SetShootEnemyLocation(8000, 8000, i);
					break;
				case 2:
					SetPlayerLife(GetPlayerLife() - GetDamage(2));
					SetShootEnemyLocation(8000, 8000, i);
					break;
				}
			}
		} 
	}

	for (int i = 0; i < GetMaxNumberOfEnemies(); i++) {
		for(int j = 0; j<GetMaxNumberOfEnemies();j++){
			if (tag1 == "enemy" + i && tag2 == "enemy" + j) {
				float velocidad = GetEnemySpeed(i);
				float movimientoX = velocidad * FASG::GetDeltaTime();
				MoveEnemyIfCollision(movimientoX, i);
			}
		}
	}
}

// Lo queremos mostrar así o diferente?
void DrawHUD()
{
	FASG::WriteStringBuffer(game.CONSOLE_WIDTH - 24, game.CONSOLE_HEIGHT - 7, "PUNTUACION: " + std::to_string(GetPuntuation()), FASG::EForeColor::LightRed);
	//FASG::WriteStringBuffer(game.CONSOLE_WIDTH - 22, game.CONSOLE_HEIGHT - 5, "ESCUDO: " + std::to_string(GetPlayerLife()), FASG::EForeColor::LightYellow);
	FASG::WriteStringBuffer(game.CONSOLE_WIDTH - 22, game.CONSOLE_HEIGHT - 5, "ESCUDO: ", FASG::EForeColor::LightYellow);

	DrawHealth();


	FASG::WriteStringBuffer(5, game.CONSOLE_HEIGHT - 7, "MOVIMIENTO: W A S D", FASG::EForeColor::LightBlue);
	FASG::WriteStringBuffer(5, game.CONSOLE_HEIGHT - 5, "DISPARAR: ESPACIO", FASG::EForeColor::LightBlue);
}