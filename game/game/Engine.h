#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	float const CONSOLE_WIDTH = 150, CONSOLE_HEIGHT = 80;
	bool gameOver = false;
	Vector2 screenCenter;
};

void InitGame();

void EndGame();

void GetConsoleCenter();