#pragma once
#include "FAriasSimpleGraphics.h"

struct Asteroid {
	FASG::Sprite sprite;

	float currentSpeed;
};

void Asteroids();

//void CreateAsteroid();

void MoveAsteroid();

void DrawAsteroid();

//void GravityForce();

void InitAsteroids();