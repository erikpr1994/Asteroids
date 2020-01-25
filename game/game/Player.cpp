#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"

#include <iostream>
#include <conio.h>

Player player;

extern Game game;

char GetAnyKeyPressed();

void InitPlayer() {
	player.sprite1.LoadSprite("Player.txt");
	player.sprite2.LoadSprite("Player_up.txt");
	player.sprite3.LoadSprite("Player_down.txt");
		
	//player.sprite1.Location.x = game.screenCenter.x;
	//player.sprite1.Location.y = game.screenCenter.y;

	player.sprite1.Location.y = player.sprite2.Location.y = player.sprite3.Location.y = game.screenCenter.y;
	player.sprite1.Location.x = player.sprite2.Location.x = player.sprite3.Location.x = game.screenCenter.x;

	player.velocity = 70.f;
	player.diagonalVelocity = player.velocity / (sqrt(2));

	Sprite::AddToCollisionSystem(player.sprite1, " La nave");
}

char GetAnyKeyPressed(){ // Que devuelve según que tecla presionemos
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

void InputPlayer() { // Que estado genera según lo que recibe de la tecla presionada
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

void UpdatePlayer() { // Que hace cada estado 
	switch (player.lastInputPlayer)
	{
	case EInputPlayer::UPRIGTH:
		player.sprite1.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UPLEFT:
		player.sprite1.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNRIGHT:
		player.sprite1.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNLEFT:
		player.sprite1.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite2.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite3.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UP:
		player.sprite1.Location.y -= player.velocity * FASG::GetDeltaTime();
		player.sprite2.Location.y -= player.velocity * FASG::GetDeltaTime();
		player.sprite3.Location.y -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWN:
		player.sprite1.Location.y += player.velocity * FASG::GetDeltaTime();
		player.sprite2.Location.y += player.velocity * FASG::GetDeltaTime();
		player.sprite3.Location.y += player.velocity * FASG::GetDeltaTime();		
		break;
	case EInputPlayer::LEFT:
		player.sprite1.Location.x -= player.velocity * FASG::GetDeltaTime();
		player.sprite2.Location.x -= player.velocity * FASG::GetDeltaTime();
		player.sprite3.Location.x -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::RIGHT:
		player.sprite1.Location.x += player.velocity * FASG::GetDeltaTime();
		player.sprite2.Location.x += player.velocity * FASG::GetDeltaTime();
		player.sprite3.Location.x += player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::SHOOT:
		break;
	case EInputPlayer::STILL:
		break;
	}
}

void IsPlayerDeath() {
	bool gameOver = false;
	gameOver = GetGameOver();
	
	if (player.lastInputPlayer == EInputPlayer::DEATH) {
		gameOver = true;
		SetGameOver(gameOver);
	}
}

void DrawPlayer(){ // Dibuja al jugador, diciendo posicion X e Y y el sprite a utilizar
	
	switch (player.lastInputPlayer)
	{
	case EInputPlayer::UP: case EInputPlayer::UPRIGTH: case EInputPlayer::UPLEFT:
		FASG::WriteSpriteBuffer(player.sprite2.Location.x, player.sprite2.Location.y, player.sprite2);
		break;
	case EInputPlayer::DOWN: case EInputPlayer::DOWNRIGHT: case EInputPlayer::DOWNLEFT:
		FASG::WriteSpriteBuffer(player.sprite3.Location.x, player.sprite3.Location.y, player.sprite3);
		break;
	default:
		FASG::WriteSpriteBuffer(player.sprite1.Location.x, player.sprite1.Location.y, player.sprite1);
		break;
	}
}