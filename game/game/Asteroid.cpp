#include "FAriasSimpleGraphics.h"
#include "Asteroid.h"
#include "Engine.h"

#include <iostream>
#include <conio.h>

Asteroid asteroid;

extern Game game;

void InitAsteroid() {
	asteroid.sprite.LoadSprite("Asteroid.txt");
	asteroid.sprite.Location.x = game.zoneSpawn.x;
	asteroid.sprite.Location.y = game.zoneSpawn.y;

	Sprite::AddToCollisionSystem(asteroid.sprite, "Asteroid1");
}

void CreateAsteroid()
{
	
}

void DrawAsteroid() {
	FASG::WriteSpriteBuffer(asteroid.sprite.Location.x, asteroid.sprite.Location.y, asteroid.sprite);
}

