#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"
#include "Camera.h"

#include <iostream>
#include <conio.h>

Player player;

extern Game game;
extern Camera camera;

char GetAnyKeyPressed();

void InitPlayer() {
	player.sprite.LoadSprite("Player.txt");
	player.sprite.Location.x = game.screenCenter.x;
	player.sprite.Location.y = game.screenCenter.y;
	player.velocity = 30.f;
	player.diagonalVelocity = player.velocity / (sqrt(2));
}

char GetAnyKeyPressed(){
	if (FASG::IsKeyPressed('W') && FASG::IsKeyPressed('D')) {
		return 'E';
	}

	if (FASG::IsKeyPressed('W') && FASG::IsKeyPressed('A')) {
		return 'Q';
	}
	if (FASG::IsKeyPressed('S') && FASG::IsKeyPressed('D')) {
		return 'Z';
	}
	if (FASG::IsKeyPressed('S') && FASG::IsKeyPressed('A')) {
		return 'X';
	}
	if (FASG::IsKeyPressed('W')) {
		return 'W';
	}
	if (FASG::IsKeyPressed('D')) {
		return 'D';
	}
	if (FASG::IsKeyPressed('A')) {
		return 'A';
	}
	if (FASG::IsKeyPressed('S')) {
		return 'S';
	}
	if (FASG::IsKeyPressed(' ')) {
		return ' ';
	}
	else {
		return '\0';
	}
}

void InputPlayer() {
	char key = GetAnyKeyPressed();

	switch (key)
	{
	case 'E':
		player.lastInputPlayer = EInputPlayer::UPRIGTH;
		break;
	case 'Q':
		player.lastInputPlayer = EInputPlayer::UPLEFT;
		break;
	case 'Z':
		player.lastInputPlayer = EInputPlayer::DOWNRIGHT;
		break;
	case 'X':
		player.lastInputPlayer = EInputPlayer::DOWNLEFT;
		break;
	case 'W':
		player.lastInputPlayer = EInputPlayer::UP;
		break;
	case 'A':
		player.lastInputPlayer = EInputPlayer::LEFT;
		break;
	case 'D':
		player.lastInputPlayer = EInputPlayer::RIGHT;
		break;
	case 'S':
		player.lastInputPlayer = EInputPlayer::DOWN;
		break;
	case ' ':
		player.lastInputPlayer = EInputPlayer::SHOOT;
		break;
	default:
		player.lastInputPlayer = EInputPlayer::STILL;
		break;
	}
}

void CheckPlayerDeath() {
	if (player.sprite.Location.y >= camera.cameraYStart) {
		player.sprite.Location.y = camera.cameraYStart -1;
	}

	if (player.sprite.Location.y <= camera.cameraYEnd) {
		player.sprite.Location.y = camera.cameraYEnd+1;
	}

	if (player.sprite.Location.x <= camera.cameraXStart) {
		player.sprite.Location.x = camera.cameraXStart+1;
	}
	if (player.sprite.Location.x >= camera.cameraXEnd) {
		player.sprite.Location.x = camera.cameraXEnd-1;
	}
}

void UpdatePlayer() {
	switch (player.lastInputPlayer)
	{
	case EInputPlayer::UPRIGTH:
		player.sprite.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UPLEFT:
		player.sprite.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNRIGHT:
		player.sprite.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNLEFT:
		player.sprite.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UP:
		player.sprite.Location.y -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWN:
		player.sprite.Location.y += player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::LEFT:
		player.sprite.Location.x -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::RIGHT:
		player.sprite.Location.x += player.velocity * FASG::GetDeltaTime();
	case EInputPlayer::SHOOT:
		break;
	case EInputPlayer::STILL:
		break;
	}
}

void DrawPlayer(){
	FASG::WriteSpriteBuffer(player.sprite.Location.x, player.sprite.Location.y, player.sprite);
}