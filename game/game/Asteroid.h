#pragma once
#include "FAriasSimpleGraphics.h"

struct Asteroid {
	FASG::Sprite sprite;

	float currentSpeed = 2.f;
};

void InitAsteroid();

void CreateAsteroid();

void MoveAsteroid();

void DrawAsteroid();

