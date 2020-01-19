#pragma once
#include "FAriasSimpleGraphics.h"

struct Camera {
	float cameraXStart, cameraXEnd;
	float cameraYStart, cameraYEnd;
	float cameraSpeed;
};

void InitCamera();

void MoveCamera();