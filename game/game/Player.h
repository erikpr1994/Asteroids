#pragma once
#include "FAriasSimpleGraphics.h"

enum EInputPlayer {
	LEFT, RIGHT, UP, DOWN, SHOOT, STILL, UPRIGTH, UPLEFT, DOWNRIGHT, DOWNLEFT, DEATH
};

struct Player {
	FASG::Sprite sprite1; // Quieto
	FASG::Sprite sprite2; // Hacia arriba
	FASG::Sprite sprite3; // Hacia abajo

	EInputPlayer lastInputPlayer;
	float velocity;
	float diagonalVelocity;
	float life;

	bool isDeath;
	bool isDeathByOutside;
	bool isDeadByCollisionWithAsteroid;
	bool isDeadByShip;
};

struct Disparo{
	FASG::Sprite sprite;
	float shootSpeed;
};

void InitPlayer();

void InputPlayer();

void UpdatePlayer();

void DrawPlayer();

void IsPlayerDeath();

void DrawShoots();

void MoveShoot();

void InitShoots();

// GETTERS Y SETTERS

bool IsPlayerDead();
bool IsPlayerDeadByGoOutsideScreen();
bool IsPlayerDeadByCollisionWithAsteroid();
bool IsPlayerDeadByShip();
int GetMaxNumberOfShoots();

void SetPlayerDead(bool value);
void SetPlayerDeadByGoOutsideScreen(bool value);
void SetPlayerDeadByShip(bool value);
void SetPlayerDeadByCollisionWithAsteroid(bool value);
void SetLastInputPlayer(EInputPlayer value);
void SetShootLocation(float x, float y, int number);
void SetPlayerLife(float life);
float GetPlayerLife();