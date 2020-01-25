#pragma once
#include "FAriasSimpleGraphics.h"

struct Asteroid {
	FASG::Sprite sprite;

	float currentSpeed = 0.f;
};

void InitAsteroid();

void CreateAsteroid();

void MoveAsteroid();

void DrawAsteroid();

