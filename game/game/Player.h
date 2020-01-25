#pragma once
#include "FAriasSimpleGraphics.h"

enum EInputPlayer {
	LEFT, RIGHT, UP, DOWN, SHOOT, STILL, UPRIGTH, UPLEFT, DOWNRIGHT, DOWNLEFT, DEATH
};

struct Player {
	FASG::Sprite sprite1;// [3] = { FASG::Sprite("Player.txt"), FASG::Sprite("Player_propeller.txt"), FASG::Sprite("Player_death.txt") };
	FASG::Sprite sprite2;
	FASG::Sprite sprite3;
	FASG::Sprite sprite4;

	EInputPlayer lastInputPlayer;
	float velocity;
	float diagonalVelocity;
};

void InitPlayer();

void InputPlayer();

void UpdatePlayer();

void DrawPlayer();

void IsPlayerDeath();