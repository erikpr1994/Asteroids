#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	int const CONSOLE_WIDTH = 150, CONSOLE_HEIGHT = 70; // WIDTH -> ancho // HEIGHT -> alto
	bool isGameClosed = false;
	Vector2 screenCenter;
	Vector2 zoneSpawn;

	float gravity = 10.f;
};

bool GetIsGameClosed();

void SetIsGameClosed(bool value);

void InitGame();

void EndGame();

// GETTERS Y SETTERS
int GetScreenCenterX();
int GetScreenCenterY();
int GetScreenEndConsoleX();
int GetScreenStartConsoleX();
int GetScreenEndConsoleY();
int GetScreenStartConsoleY();
int GetZoneSpawnX();
int GetZoneSpawnY();