#pragma once
#include "FAriasSimpleGraphics.h"

enum EInputPlayer {
	LEFT, RIGHT, UP, DOWN, SHOOT, STILL, UPRIGTH, UPLEFT, DOWNRIGHT, DOWNLEFT, DEATH
};

struct Player {
	FASG::Sprite sprite1; // Quieto
	FASG::Sprite sprite2; // Hacia arriba
	FASG::Sprite sprite3; // Hacia abajo
	//FASG::Sprite sprite4; 

	EInputPlayer lastInputPlayer;
	float velocity;
	float diagonalVelocity;
};

void InitPlayer();

void InputPlayer();

void UpdatePlayer();

void DrawPlayer();

void IsPlayerDeath();