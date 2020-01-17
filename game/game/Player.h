#pragma once
#include "FAriasSimpleGraphics.h"

enum EInputPlayer {
	LEFT, RIGHT, UP, DOWN, SHOOT, STILL
};

struct Player {
	FASG::Sprite sprite;
	EInputPlayer lastInputPlayer;
};

void InitPlayer();

void InputPlayer();

void UpdatePlayer();

void DrawPlayer();