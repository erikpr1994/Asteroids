#include "Camera.h"
#include "Engine.h"

extern Game game;

Camera camera;

void setCameraPoints() {
	camera.cameraYStart = game.CONSOLE_HEIGHT;
	camera.cameraYEnd = game.CONSOLE_HEIGHT - game.CONSOLE_HEIGHT;
	camera.cameraXStart = game.CONSOLE_WIDTH - game.CONSOLE_WIDTH;
	camera.cameraXEnd = game.CONSOLE_WIDTH;
}

void InitCamera() {
	setCameraPoints();
	camera.cameraSpeed = 15.f;
}

void MoveCamera() {
	camera.cameraYStart -= camera.cameraSpeed * FASG::GetDeltaTime();
	camera.cameraYEnd -= camera.cameraSpeed * FASG::GetDeltaTime();
}