#pragma once
#include "FAriasSimpleGraphics.h"

struct Asteroid {
	FASG::Sprite sprite;

	float currentSpeed;
	float puntuation;
};

void Asteroids();

//void CreateAsteroid();

void MoveAsteroid();

void DrawAsteroid();

//void GravityForce();

void InitAsteroids();

int GetMaxNumberOfAsteroids();

void SetAsteroidLocation(float x, float y, int number);

float GetAsteroidDeadPuntuation(int number);