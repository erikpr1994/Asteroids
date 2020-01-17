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
}

char GetAnyKeyPressed(){
	if (_kbhit())
		return toupper(_getch());

	return '\0';
}

void InputPlayer() {
	char key = GetAnyKeyPressed();

	switch (key)
	{
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
	case EInputPlayer::UP:
		player.sprite.Location.y--;
		break;
	case EInputPlayer::DOWN:
		player.sprite.Location.y++;
		break;
	case EInputPlayer::LEFT:
		player.sprite.Location.x--;
		break;
	case EInputPlayer::RIGHT:
		player.sprite.Location.x++;
	case EInputPlayer::SHOOT:
		break;
	case EInputPlayer::STILL:
		break;
	}
}

void DrawPlayer(){
	FASG::WriteSpriteBuffer(player.sprite.Location.x, player.sprite.Location.y, player.sprite);
}