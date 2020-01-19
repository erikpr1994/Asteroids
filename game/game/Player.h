#pragma once
#include "FAriasSimpleGraphics.h"

enum EInputPlayer {
	LEFT, RIGHT, UP, DOWN, SHOOT, STILL, UPRIGTH, UPLEFT, DOWNRIGHT, DOWNLEFT
};

struct Player {
	FASG::Sprite sprite;
	EInputPlayer lastInputPlayer;
	float velocity;
	float diagonalVelocity;
};

void InitPlayer();

void InputPlayer();

void UpdatePlayer();

void DrawPlayer();

void CheckPlayerDeath();