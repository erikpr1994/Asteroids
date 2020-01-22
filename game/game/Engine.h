#pragma once
#include "FAriasSimpleGraphics.h"

using namespace FASG;

struct Game {
	float const CONSOLE_WIDTH = 150, CONSOLE_HEIGHT = 90; // WIDTH -> ancho // HEIGHT -> alto
	//*************************************************************************************************************
	int zoneSpawn = (rand() % (150 - maximo_muro_derecho) - maximo_muro_izquierdo) + maximo_muro_izquierdo;
	int maximo_muro_derecho = 5;
	int maximo_muro_izquierdo = 5;
	// zoneSpawn = (rand() % (maximo_ancho_pantalla - maximo_muro_derecho) - maximo_muro_izquierdo) + maximo_muro_izquierdo;
	//								  H						K						   J						J
	//*************************************************************************************************************
	bool gameOver = false;
	Vector2 screenCenter;
};

void InitGame();

void EndGame();