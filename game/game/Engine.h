#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	int const CONSOLE_WIDTH = 200, CONSOLE_HEIGHT = 50;
	bool gameOver = false;
	Vector2 screenCenter;
};

void InitGame();

void EndGame();

void AlignCenter();