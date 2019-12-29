#pragma once

struct Game {
	int const CONSOLE_WIDTH = 200, CONSOLE_HEIGHT = 50;
	bool gameOver = false;
};

void InitGame();

void EndGame();