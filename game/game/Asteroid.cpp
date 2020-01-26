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

extern Game game;

void InitAsteroids() {
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		activeAsteroids[i] = false;
		asteroid[i].sprite.Location.y=game.CONSOLE_HEIGHT;
	}
}

void Asteroids() {
	coolDownBetweenAsteroids -= FASG::GetDeltaTime();
	if (coolDownBetweenAsteroids <= 0) {
		coolDownBetweenAsteroids = TIME_BETWEEN_ASTEROIDS;
		for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
			if(!activeAsteroids[i]){
				asteroid[i].sprite.LoadSprite("Asteroid.txt");
				asteroid[i].sprite.Location.x = rand()%game.CONSOLE_WIDTH-10;
				asteroid[i].sprite.Location.y = game.zoneSpawn.y;
				asteroid[i].currentSpeed = rand()%30+20;
				Sprite::AddToCollisionSystem(asteroid[i].sprite, "EL ASTEROIDE"+i);
				activeAsteroids[i] = true;
				break;
			}
		}
	}
	for (int i = 0; i < MAX_NUMBER_OF_ASTEROIDS; i++) {
		if (asteroid[i].sprite.Location.y >= game.CONSOLE_HEIGHT) {
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
		}
	}
}