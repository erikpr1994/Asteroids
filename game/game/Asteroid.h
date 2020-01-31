#pragma once
#include "FAriasSimpleGraphics.h"

struct Asteroid {
	FASG::Sprite sprite;

	float currentSpeed;
	float puntuation;
	std::string tagName;
}; 

void AsteroidsProcess();
void InitAsteroids();

// SETTERS
void SetAsteroidSprite(int asteroidNumber);
void SetAsteroidYLocation(int number, float y);
void SetAsteroidXLocation(int number, float x);
void SetAsteroidLocation(int number, float x, float y);
void SetAsteroidSpeed(int asteroidNumber, float speed);
void SetAsteroidPuntuation(int asteroidNumber, float speed);
void SetAsteroidTagName(int asteroidNumber);
void SetActiveAsteroids(int number, bool value);

// GETTERS
float GetAsteroidDeadPuntuation(int number);
bool GetActiveAsteroids(int number);
int GetMaxNumberOfAsteroids();
float GetAsteroidYLocation(int number);
float GetAsteroidXLocation(int number);
float GetAsteroidSpeed(int asteroidNumber);
float GetAsteroidPuntuation(int asteroidNumber);
std::string GetAsteroidTagName(int asteroidNumber);
float GetActualCoolDownBetweenAsteroids();