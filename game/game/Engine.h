#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	int const CONSOLE_WIDTH = 150, CONSOLE_HEIGHT = 70; // WIDTH -> ancho // HEIGHT -> alto
	bool isGameClosed = false;
	Vector2 screenCenter;
	Vector2 zoneSpawn;
	float puntuacion;
};

void InitGame();

void EndGame();

/* GETTERS */
int GetScreenCenterX();
int GetScreenCenterY();
int GetScreenEndConsoleX();
int GetScreenStartConsoleX();
int GetScreenEndConsoleY();
int GetScreenStartConsoleY();
int GetZoneSpawnX();
int GetZoneSpawnY();
float GetPuntuation();
bool GetIsGameClosed();
bool IsSoundEnabled();

/* SETTERS */
void SetPuntuation(float value);
void SetIsGameClosed(bool value);
void SetSoundEnabled(bool option);