#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"
#include "Menu.h"

#include <iostream>
#include <conio.h>

Player player;

float const MIN_TIEMPO_ENTRE_DISPAROS = 0.1f;
int const NUMERO_DISPAROS_A_LA_VEZ = 5;
Disparo disparo[NUMERO_DISPAROS_A_LA_VEZ];
float coolDownBetweenDisparos = 0.f;
bool disparosActivos[NUMERO_DISPAROS_A_LA_VEZ];

//---------------------------------------------------------------//
int const VIDA_MAXIMA = 5;
Vida vida[VIDA_MAXIMA];
bool vidaActiva[VIDA_MAXIMA]; 
//---------------------------------------------------------------//

char GetAnyKeyPressed();

void InitPlayer() {
	player.sprite1.LoadSprite("Player.txt");
	player.sprite2.LoadSprite("Player_up.txt");
	player.sprite3.LoadSprite("Player_down.txt");
		
	player.sprite1.Location.y = player.sprite2.Location.y = player.sprite3.Location.y = GetScreenCenterY();
	player.sprite1.Location.x = player.sprite2.Location.x = player.sprite3.Location.x = GetScreenCenterX();

	player.velocity = 70.f;
	player.diagonalVelocity = player.velocity / (sqrt(2));

	Sprite::AddToCollisionSystem(player.sprite1, "nave");

	player.life = VIDA_MAXIMA; //---

	player.isDeath = false;
	player.isDeathByOutside = false;
	player.isDeadByCollisionWithAsteroid = false;
	player.isDeadByShip = false;
	player.lastInputPlayer = EInputPlayer::STILL;
}
//---------------------------------------------------------------//---------------------------------------------------------------//
void Health() {
	for (int i = 0; i < VIDA_MAXIMA; i++) {
		if (!vidaActiva[i]) {
			vida[i].sprite.LoadSprite("Life.txt");
			if (i == 0) {
				vida[i].sprite.Location.x = 120;
			} else {
				vida[i].sprite.Location.x = vida[i-1].sprite.Location.x +2;
			}
			vida[i].sprite.Location.y = GetScreenEndConsoleY() - 22;
			
			
			vidaActiva[i] = true;
		}
	}
}

void DrawHealth() { 
	for (int i = player.life; i > 0; i--) {
		if (vidaActiva[i]) {
			FASG::WriteSpriteBuffer(vida[i].sprite.Location.x, vida[i].sprite.Location.y, GetLifeSprite(i));
		}
	}
}
//---------------------------------------------------------------//---------------------------------------------------------------//

FASG::WAVESound shootSound[NUMERO_DISPAROS_A_LA_VEZ];
bool shootSoundLoad[NUMERO_DISPAROS_A_LA_VEZ];

void InitShootsSounds() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
		if (!shootSoundLoad[i]) {
			shootSound[i].LoadSound("blaster.wav");
			shootSoundLoad[i] = true;
		}
	}
}

void disparos() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
		if (disparo[i].sprite.Location.y <= 0) {
			disparosActivos[i] = false;
			shootSound[i].Stop();
		}
	}
	if (coolDownBetweenDisparos <= 0) {
		coolDownBetweenDisparos = MIN_TIEMPO_ENTRE_DISPAROS;
		for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
			if (!disparosActivos[i]) {
				disparo[i].sprite.LoadSprite("Disparo.txt");
				disparo[i].sprite.Location.x = player.sprite1.Location.x + 6;
				disparo[i].sprite.Location.y = player.sprite1.Location.y-2;
				disparo[i].shootSpeed = 100.f;
				Sprite::AddToCollisionSystem(disparo[i].sprite, "disparo" + i);
				disparosActivos[i] = true;
				shootSound[i].Play();
				break;
			}
		}
	}
}

void InitShoots() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
		disparosActivos[i] = false;
		disparo[i].sprite.Location.y = rand() % 10000 + 100000;
		disparo[i].sprite.Location.x = rand() % 10000 + 100000;
	}
}

void MoveShoot() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
		if (disparosActivos[i]) {
			disparo[i].sprite.Location.y -= disparo[i].shootSpeed * FASG::GetDeltaTime() * 0.5f;
			if (disparo[i].sprite.Location.y >= GetScreenEndConsoleY()) {
				disparo[i].sprite.Location.y = rand() % 10000 + 100000;
				disparo[i].sprite.Location.x = rand() % 10000 + 100000;
			}
		}
	}
}

void DrawShoots() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ; i++) {
		if (disparosActivos[i]) {
			FASG::WriteSpriteBuffer(disparo[i].sprite.Location.x, disparo[i].sprite.Location.y, disparo[i].sprite);
		}
	}
}

void SetShootLocation(float x, float y, int number) {
	disparo[number].sprite.Location.x = x;
	disparo[number].sprite.Location.y = y;
}

// GETTERS
bool IsPlayerDead() {
	return player.isDeath;
}

bool IsPlayerDeadByGoOutsideScreen() {
	return player.isDeathByOutside;
}

bool IsPlayerDeadByCollisionWithAsteroid() {
	return player.isDeadByCollisionWithAsteroid;
}

bool IsPlayerDeadByShip() {
	return player.isDeadByShip;
}

int GetMaxNumberOfShoots() {
	return NUMERO_DISPAROS_A_LA_VEZ;
}

float GetPlayerLife() {
	return player.life;
}

FASG::Sprite GetLifeSprite(int numVida) {
	return vida[numVida].sprite;
}

// SETTERS
void SetPlayerDead(bool value) {
	player.isDeath = value;
}

void SetPlayerDeadByGoOutsideScreen(bool value) {
	player.isDeathByOutside = value;
}

void SetPlayerDeadByShip(bool value) {
	player.isDeadByShip = value;
}

void SetPlayerDeadByCollisionWithAsteroid(bool value) {
	player.isDeadByCollisionWithAsteroid = value;
}

void SetLastInputPlayer(EInputPlayer value) {
	player.lastInputPlayer = value;
}

void SetPlayerLife(float number) {
	player.life = number;
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

void UpdatePlayer() {
	coolDownBetweenDisparos -= FASG::GetDeltaTime();

	switch (player.lastInputPlayer)
	{
	case EInputPlayer::UPRIGTH:
		player.sprite1.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UPLEFT:
		player.sprite1.Location.y -= player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNRIGHT:
		player.sprite1.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x += player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWNLEFT:
		player.sprite1.Location.y += player.diagonalVelocity * FASG::GetDeltaTime();
		player.sprite1.Location.x -= player.diagonalVelocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::UP:
		player.sprite1.Location.y -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::DOWN:
		player.sprite1.Location.y += player.velocity * FASG::GetDeltaTime();	
		break;
	case EInputPlayer::LEFT:
		player.sprite1.Location.x -= player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::RIGHT:
		player.sprite1.Location.x += player.velocity * FASG::GetDeltaTime();
		break;
	case EInputPlayer::SHOOT:
		disparos();
		break;
	case EInputPlayer::STILL:
		break;
	}

	player.sprite2.Location.y = player.sprite1.Location.y;
	player.sprite2.Location.x = player.sprite1.Location.x;
	player.sprite3.Location.y = player.sprite1.Location.y;
	player.sprite3.Location.x = player.sprite1.Location.x;
}

void IsPlayerDeath() {
	if (player.life <= 0) {
		player.isDeadByShip = true;
		player.isDeath = true;
		SetLastInputPlayer(EInputPlayer::DEATH);
	}

	if (player.lastInputPlayer == EInputPlayer::DEATH) {
		SetInMenu(true);
	}
}

void DrawPlayer(){
	
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

bool InMapRanged(int x, int y) {
	if ((x >= 0) && (x < GetScreenEndConsoleX() - 12) && (y >= 0) && (y < GetScreenEndConsoleY()-7)) {
		return true;
	}
	return false;
}

void Outside() {
	if (!InMapRanged(player.sprite1.Location.x, player.sprite1.Location.y))
	{
		if (player.sprite1.Location.y <= 0) {
			player.sprite1.Location.y = 1;
		}
		else {
			player.sprite2.Location.y = player.sprite1.Location.y;
			player.sprite2.Location.x = player.sprite1.Location.x;
			player.sprite3.Location.y = player.sprite1.Location.y;
			player.sprite3.Location.x = player.sprite1.Location.x;
			SetPlayerDead(true); // USAR SETTER
			SetPlayerDeadByGoOutsideScreen(true); // USAR SETTER
			player.lastInputPlayer = EInputPlayer::DEATH;
		}
	}
}