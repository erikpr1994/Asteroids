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

void InitAsteroids() {
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		activeAsteroids[i] = false;
		asteroid[i].sprite.Location.y = rand() % 10000 + 100000;
		asteroid[i].sprite.Location.x = rand() % 10000 + 100000;
	}
}

void Asteroids() {
	coolDownBetweenAsteroids -= FASG::GetDeltaTime();
	if (coolDownBetweenAsteroids <= 0) {
		coolDownBetweenAsteroids = TIME_BETWEEN_ASTEROIDS;
		for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
			if(!activeAsteroids[i]){
				asteroid[i].sprite.LoadSprite("Asteroid.txt");
				asteroid[i].sprite.Location.x = rand()% (GetScreenEndConsoleX ()-10)+10;
				asteroid[i].sprite.Location.y = GetZoneSpawnY();
				asteroid[i].currentSpeed = rand()%30+20;
				Sprite::AddToCollisionSystem(asteroid[i].sprite, "asteroid"+i);
				activeAsteroids[i] = true;
				break;
			}
		}
	}
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		if (asteroid[i].sprite.Location.y >= GetScreenEndConsoleY()) {
			activeAsteroids[i] = false;
		}
	}
}

void DrawAsteroid() {
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		if(activeAsteroids[i]) {
			FASG::WriteSpriteBuffer(asteroid[i].sprite.Location.x, asteroid[i].sprite.Location.y, asteroid[i].sprite);
		}
	}
}

void MoveAsteroid() {
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		if (activeAsteroids[i]) {
			asteroid[i].sprite.Location.y += asteroid[i].currentSpeed * FASG::GetDeltaTime() * 0.5f;
			if(asteroid[i].sprite.Location.y >= GetScreenEndConsoleY()) {
				asteroid[i].sprite.Location.y = rand() % 10000 + 100000;
				asteroid[i].sprite.Location.x = rand() % 10000 + 100000;
			}
		}
	}
}

int GetMaxNumberOfAsteroids() {
	return MAX_NUMBER_OF_ASTEROIDS;
}

void SetAsteroidLocation(float x, float y, int number) {
	asteroid[number].sprite.Location.x = x;
	asteroid[number].sprite.Location.y = y;
}