#include "FAriasSimpleGraphics.h"
#include "Asteroid.h"
#include "Engine.h"

#include <iostream>
#include <conio.h>

float coolDownBetweenAsteroids = 0.f;
int const TIME_BETWEEN_ASTEROIDS = 1;
int const MAX_NUMBER_OF_ASTEROIDS = 10;
Asteroid asteroid[MAX_NUMBER_OF_ASTEROIDS];
bool activeAsteroids[MAX_NUMBER_OF_ASTEROIDS];
int const MAX_ASTEROID_SPEED = 30;
int const MIN_ASTEROID_SPEED = 10;
float const PUNTUATION_DIVISOR = 10.f;

/* FUNCIONES DE USO INTERNO */
float GenerateCurrentSpeed() {
	return float(rand() % MAX_ASTEROID_SPEED + MIN_ASTEROID_SPEED);
}

/* FUNCIONES DE USO EXTERNO */
void InitAsteroids() {
	for (int asteroidNumber = 0; asteroidNumber < MAX_NUMBER_OF_ASTEROIDS; asteroidNumber++) {
		SetActiveAsteroids(asteroidNumber, false);
		SetAsteroidYLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
		SetAsteroidXLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
	}
}

void Asteroids() {
	SetActualCoolDownBetweenAsteroids(GetActualCoolDownBetweenAsteroids() - FASG::GetDeltaTime());
	if (GetActualCoolDownBetweenAsteroids() <= 0) {
		SetActualCoolDownBetweenAsteroids(TIME_BETWEEN_ASTEROIDS);
		for (int asteroidNumber = 0; asteroidNumber < GetMaxNumberOfAsteroids(); asteroidNumber++) {
			if(!GetActiveAsteroids(asteroidNumber)){
				SetAsteroidSprite(asteroidNumber);
				SetAsteroidXLocation(asteroidNumber, GenerateRandomXPosition());
				SetAsteroidYLocation(asteroidNumber, GetZoneSpawnY());
				SetActiveAsteroids(asteroidNumber, GenerateCurrentSpeed());
				SetAsteroidPuntuation(asteroidNumber, GetAsteroidSpeed(asteroidNumber));
				SetAsteroidTagName(asteroidNumber);
				Sprite::AddToCollisionSystem(asteroid[asteroidNumber].sprite, GetAsteroidTagName(asteroidNumber));
				SetActiveAsteroids(asteroidNumber, true);
				break;
			}
		}
	}

	for (int asteroidNumber = 0; asteroidNumber < GetMaxNumberOfAsteroids(); asteroidNumber++) {
		if (GetAsteroidYLocation(asteroidNumber) >= GetScreenEndConsoleY()) {
			SetActiveAsteroids(asteroidNumber, false);
		}
	}
}

void DrawAsteroid() {
	for (int asteroidNumber = 0; asteroidNumber < GetMaxNumberOfAsteroids(); asteroidNumber++) {
		if(GetActiveAsteroids(asteroidNumber)) {
			FASG::WriteSpriteBuffer(GetAsteroidXLocation(asteroidNumber), GetAsteroidYLocation(asteroidNumber), asteroid[asteroidNumber].sprite);
		}
	}
}

void MoveAsteroid() {
	for (int asteroidNumber = 0; asteroidNumber < GetMaxNumberOfAsteroids(); asteroidNumber++) {
		if (GetActiveAsteroids(asteroidNumber)) {
			SetAsteroidYLocation(asteroidNumber, GetAsteroidYLocation(asteroidNumber) + GetAsteroidSpeed(asteroidNumber) * FASG::GetDeltaTime() * 0.5f);
			if(GetAsteroidYLocation(asteroidNumber) >= GetScreenEndConsoleY()) {
				SetAsteroidYLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
				SetAsteroidXLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
			}
		}
	}
}

/* SETTERS */
void SetActiveAsteroids(int asteroidNumber, bool value) {
	activeAsteroids[asteroidNumber] = value;
}

void SetAsteroidYLocation(int asteroidNumber, float y){
	asteroid[asteroidNumber].sprite.Location.y = y;
}

void SetAsteroidXLocation(int asteroidNumber, float x){
	asteroid[asteroidNumber].sprite.Location.x = x;
}

void SetAsteroidLocation(int asteroidNumber, float x, float y) {
	SetAsteroidYLocation(asteroidNumber, y);
	SetAsteroidXLocation(asteroidNumber, x);
}

void SetAsteroidSpeed(int asteroidNumber, float speed) {
	asteroid[asteroidNumber].currentSpeed = speed;
}

void SetAsteroidSprite(int asteroidNumber) {
	asteroid[asteroidNumber].sprite.LoadSprite("Asteroid.txt");
}

void SetAsteroidTagName(int asteroidNumber) {
	asteroid[asteroidNumber].tagName = "asteroid" + asteroidNumber;
}

/* La puntuación se calcula según la velocidad del asteroid. A más velocidad, más puntuación */
void SetAsteroidPuntuation(int asteroidNumber, float speed) {
	asteroid[asteroidNumber].puntuation = speed / PUNTUATION_DIVISOR;
}

void SetActualCoolDownBetweenAsteroids(int coolDownTime) {
	coolDownBetweenAsteroids = coolDownTime;
}

/* GETTERS */
int GetMaxNumberOfAsteroids() {
	return MAX_NUMBER_OF_ASTEROIDS;
}

float GetAsteroidDeadPuntuation(int asteroidNumber) {
	return asteroid[asteroidNumber].puntuation;
}

bool GetActiveAsteroids(int asteroidNumber) {
	return activeAsteroids[asteroidNumber];
}

float GetAsteroidYLocation(int asteroidNumber) {
	return asteroid[asteroidNumber].sprite.Location.y;
}

float GetAsteroidXLocation(int asteroidNumber) {
	return asteroid[asteroidNumber].sprite.Location.y;
}

float GetAsteroidSpeed(int asteroidNumber) {
	return asteroid[asteroidNumber].puntuation;
}

float GetAsteroidPuntuation(int asteroidNumber) {
	return asteroid[asteroidNumber].puntuation;
}

std::string GetAsteroidTagName(int asteroidNumber) {
	return asteroid[asteroidNumber].tagName;
}

float GetActualCoolDownBetweenAsteroids() {
	return coolDownBetweenAsteroids;
}


/* PASAR AL ENGINE */
float GenerateRandomXPosition() {
	return float(rand() % (GetScreenEndConsoleX() - 10));
}

float GenerateRandomOutsideMapPosition() {
	return rand() % 10000 + 100000;
}