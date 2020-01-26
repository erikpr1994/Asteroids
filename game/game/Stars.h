#pragma once
#include "FAriasSimpleGraphics.h";

struct Stars {
	FASG::Vector2 posicion;
	FASG::EForeColor color;
	char skin;
};

void InitStars();
void DrawStars();
void MoveStars();