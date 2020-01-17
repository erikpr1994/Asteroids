#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"

#include <iostream>
#include <conio.h>

Player player;

extern Game game;

char GetAnyKeyPressed();

void InitPlayer() {
	player.sprite.LoadSprite("Player.txt");
	player.sprite.Location.x = game.screenCenter.x;
	player.sprite.Location.y = game.screenCenter.y;
	player.velocity = 30.f;
	player.diagonalVelocity = player.velocity / (sqrt(2));
}

char GetAnyKeyPressed(){
	if (FASG::IsKeyPressed('W') && FASG::IsKeyPressed('D')) { // ESTO NO FUNCIONA, PERO TAMPOCO DA ERRORES. Cuando consigamos que funcione, hacerlo para los demás casos tambien
		return 'E';
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

void UpdatePlayer() {
	switch (player.lastInputPlayer)
	{
	case EInputPlayer::UPRIGTH:
		player.sprite.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
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