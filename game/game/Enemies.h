#pragma once
#include "FAriasSimpleGraphics.h"

struct Enemy {
	FASG::Sprite sprite;
	float velocity;
	float diagonalVelocity;
	int type;
	float damage;
	float points;
};

struct Shoot {
	FASG::Sprite sprite;
	float shootSpeed;
};

void InitEnemies();
void Enemies();
void MoveEnemies();
void DrawEnemies();
void DrawEnemyShoots();
void InitEnemyShoots();
void MoveEnemyShoots();

int GetMaxNumberOfEnemiesShoots();
int getWhoShoot(int number, int ship);
int GetDamage(int ship);
void SetShootEnemyLocation(float x, float y, int number);
int GetMaxNumberOfEnemies();
void SetEnemyLocation(float x, float y, int number);
float GetEnemyPoints(int number);
void SetCoolDownBetweenShoots(float number);