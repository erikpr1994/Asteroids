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
void GenerateNewAsteroids();
void MoveAsteroid();
void IsAsteroidOutside();
void DrawAsteroid();

void SetActualCoolDownBetweenAsteroids(float coolDownTime);

float GenerateSpeed(int maxSpeed, int minSpeed);
float GenerateRandomXPositionInsideMap();
float GenerateRandomYPositionInsideMap();
float GenerateRandomOutsideMapPosition();

void InitAsteroids() {
	for (int asteroidNumber = 0; asteroidNumber < MAX_NUMBER_OF_ASTEROIDS; asteroidNumber++) {
		SetActiveAsteroids(asteroidNumber, false);
		SetAsteroidYLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
		SetAsteroidXLocation(asteroidNumber, GenerateRandomOutsideMapPosition());
	}
}

void GenerateNewAsteroids() {
	SetActualCoolDownBetweenAsteroids(GetActualCoolDownBetweenAsteroids() - FASG::GetDeltaTime());
	if (GetActualCoolDownBetweenAsteroids() <= 0) {
		SetActualCoolDownBetweenAsteroids(TIME_BETWEEN_ASTEROIDS);
		for (int asteroidNumber = 0; asteroidNumber < GetMaxNumberOfAsteroids(); asteroidNumber++) {
			if(!GetActiveAsteroids(asteroidNumber)){
				SetAsteroidSprite(asteroidNumber);
				SetAsteroidXLocation(asteroidNumber, GenerateRandomXPositionInsideMap());
				SetAsteroidYLocation(asteroidNumber, GetZoneSpawnY()); //Revisar que hace GetZoneSpawnY y cambiar por GenerateRandomYPositionInsideMap()
				SetAsteroidSpeed(asteroidNumber, GenerateSpeed(MAX_ASTEROID_SPEED, MIN_ASTEROID_SPEED));
				SetAsteroidPuntuation(asteroidNumber, GetAsteroidSpeed(asteroidNumber));
				SetAsteroidTagName(asteroidNumber);
				Sprite::AddToCollisionSystem(asteroid[asteroidNumber].sprite, GetAsteroidTagName(asteroidNumber)); // Si da tiempo, crear un sistema de colisiones nuevo
				SetActiveAsteroids(asteroidNumber, true);
				break;
			}
		}
	}
}

void IsAsteroidOutside() {
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

/* FUNCIONES DE USO EXTERNO */

void AsteroidsProcess() {
	GenerateNewAsteroids();
	MoveAsteroid();
	IsAsteroidOutside();
	DrawAsteroid();
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
	// Queda preparado para si hacemos más sprites de asteroides
	// Solo hay que copiar el case y poner el siguiente numero
	int typeOfAsteroid = rand() % 1; // Cambiar por el numero de sprites que tengamos
	std::string asteroidTypeName;
	switch (typeOfAsteroid)
	{
	case 0:
		asteroidTypeName = "Asteroid" + std::to_string(typeOfAsteroid) + ".txt";
		asteroid[asteroidNumber].sprite.LoadSprite(asteroidTypeName);
		break;
	/*Ejemplo de siguiente asteroide
	case 1:
		asteroidTypeName = "Asteroid" + std::to_string(typeOfAsteroid) + ".txt";
		asteroid[asteroidNumber].sprite.LoadSprite(asteroidTypeName);
		break;
	*/
	}
}

void SetAsteroidTagName(int asteroidNumber) {
	asteroid[asteroidNumber].tagName = "asteroid" + std::to_string(asteroidNumber);
}

/* La puntuación se calcula según la velocidad del asteroid. A más velocidad, más puntuación */
void SetAsteroidPuntuation(int asteroidNumber, float speed) {
	asteroid[asteroidNumber].puntuation = speed / PUNTUATION_DIVISOR;
}

void SetActualCoolDownBetweenAsteroids(float coolDownTime) {
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
	return asteroid[asteroidNumber].sprite.Location.x;
}

float GetAsteroidSpeed(int asteroidNumber) {
	return asteroid[asteroidNumber].currentSpeed;
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
float GenerateRandomXPositionInsideMap() {
	float randomX = rand() % (GetScreenEndConsoleX() - 10);
	return randomX;
}

float GenerateRandomYPositionInsideMap() {
	return float(rand() % (GetScreenEndConsoleY() - 10));
}

float GenerateRandomOutsideMapPosition() {
	return rand() % 10000 + 100000;
}

float GenerateSpeed(int maxSpeed, int minSpeed) {
	return float(rand() % maxSpeed + minSpeed);
}