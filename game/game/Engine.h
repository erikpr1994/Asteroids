#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	int const CONSOLE_WIDTH = 150, CONSOLE_HEIGHT = 70; // WIDTH -> ancho // HEIGHT -> alto
	bool gameOver = false;
	Vector2 screenCenter;
	Vector2 zoneSpawn;

	float gravity = 10.f;
};

bool GetGameOver();

void SetGameOver(bool gameOver);

void InitGame();

void EndGame();
