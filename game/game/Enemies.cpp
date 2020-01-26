#include "Enemies.h"
#include "Engine.h"

int const MAX_NUMBER_ENEMIES = 3;
int const TIME_BETWEEN_ENEMIES = 5;

float coolDownBetweenEnemies = 0.f;
Enemy enemy[MAX_NUMBER_ENEMIES];
bool activeEnemies[MAX_NUMBER_ENEMIES];

int const NUMERO_DISPAROS_A_LA_VEZ_MAX = 10;
Shoot shoot[NUMERO_DISPAROS_A_LA_VEZ_MAX];
float TIEMPO_ENTRE_DISPAROS = 0.1f;
float coolDownBetweenShoots = 5.f;
bool activeShoots[NUMERO_DISPAROS_A_LA_VEZ_MAX];
int whoShoot[NUMERO_DISPAROS_A_LA_VEZ_MAX][MAX_NUMBER_ENEMIES];

int SetSpriteRandomlyAndReturnType(int number);
void EnemiesShoots();

int getWhoShoot(int number, int ship) {
	return whoShoot[number][ship];
}

int GetDamage(int ship) {
	return enemy[ship].damage;
}

int GetMaxNumberOfEnemies() {
	return MAX_NUMBER_ENEMIES;
}

void SetEnemyLocation(float x, float y, int number) {
	enemy[number].sprite.Location.x = x;
	enemy[number].sprite.Location.y = y;
}

float GetEnemyPoints(int number) {
	return enemy[number].points;
}

void InitEnemies() {
	for (int i = 0; i < MAX_NUMBER_ENEMIES; i++) {
		activeEnemies[i] = false;
		enemy[i].sprite.Location.y = rand() % 10000 + 100000;
		enemy[i].sprite.Location.x = rand() % 10000 + 100000;
		coolDownBetweenShoots = 10.f;
		coolDownBetweenEnemies = 5.f;
	}
}

void SetCoolDownBetweenShoots(float number){
	coolDownBetweenShoots = number;
}

void Enemies() {
	coolDownBetweenEnemies -= FASG::GetDeltaTime();
	if(coolDownBetweenEnemies <= 0){
		coolDownBetweenEnemies = TIME_BETWEEN_ENEMIES;
		for (int i = 0; i < MAX_NUMBER_ENEMIES; i++) {
			if (!activeEnemies[i]) {
				enemy[i].type = SetSpriteRandomlyAndReturnType(i);
				enemy[i].sprite.Location.x = rand() % (GetScreenEndConsoleX() - 10);
				enemy[i].sprite.Location.y = -30;
				switch (enemy[i].type)
				{
				case 0:
					enemy[i].velocity = 10.f;
					enemy[i].diagonalVelocity = enemy[i].velocity / (sqrt(2));
					enemy[i].damage = 10.f;
					enemy[i].points = 10.f;
					Sprite::AddToCollisionSystem(enemy[i].sprite, "enemy" + i);
					break;
				case 1:
					enemy[i].velocity = 50.f;
					enemy[i].diagonalVelocity = enemy[i].velocity / (sqrt(2));
					enemy[i].damage = 20.f;
					enemy[i].points = 20.f;
					Sprite::AddToCollisionSystem(enemy[i].sprite, "enemy" + i);
					break;
				case 2:
					enemy[i].velocity = 100.f;
					enemy[i].diagonalVelocity = enemy[i].velocity / (sqrt(2));
					enemy[i].damage = 30.f;
					enemy[i].points = 30.f;
					Sprite::AddToCollisionSystem(enemy[i].sprite, "enemy" + i);
					break;
				default:
					break;
				}
				activeEnemies[i] = true;
				break;
			}
		}
	}
	EnemiesShoots();
}

void SetActiveEnemies(int number, bool life) {
	activeEnemies[number] = life;
}

int SetSpriteRandomlyAndReturnType(int number) {
	int spriteType = rand() % 3;
	switch (spriteType) {
		case 0:
			enemy[number].sprite.LoadSprite("Enemy1.txt");
			return 0;
			break;

		case 1:
			enemy[number].sprite.LoadSprite("Enemy2.txt");
			return 1;
			break;
		case 2:
			enemy[number].sprite.LoadSprite("Enemy3.txt");
			return 2;
			break;
	}
}

void MoveEnemies() {
	for (int i = 0; i < MAX_NUMBER_ENEMIES; i++) {
		int movimiento = rand() % 4;
		if (enemy[i].sprite.Location.y < 5) {
			enemy[i].sprite.Location.y += FASG::GetDeltaTime() * enemy[i].velocity;
		} else {
			switch (movimiento)
			{
			case 0:
				enemy[i].sprite.Location.x += FASG::GetDeltaTime() * enemy[i].velocity;
				break;
			case 1:
				enemy[i].sprite.Location.x -= FASG::GetDeltaTime() * enemy[i].velocity;
				break;
			}

			if (enemy[i].sprite.Location.x <= 0) {
				enemy[i].sprite.Location.x = 0;
			}
			if (enemy[i].sprite.Location.x >= GetScreenEndConsoleX()) {
				enemy[i].sprite.Location.x = GetScreenEndConsoleX()-5;
			}
		}
	}
}

void DrawEnemies() {
	for (int i = 0; i < MAX_NUMBER_ENEMIES; i++) {
		if (activeEnemies[i]) {
			FASG::WriteSpriteBuffer(enemy[i].sprite.Location.x, enemy[i].sprite.Location.y, enemy[i].sprite);
		}
	}
}

void EnemiesShoots() {
	coolDownBetweenShoots -= FASG::GetDeltaTime();
	if (coolDownBetweenShoots <= 0) {
		coolDownBetweenShoots = TIEMPO_ENTRE_DISPAROS;
		for (int x = 0; x < NUMERO_DISPAROS_A_LA_VEZ_MAX; x++) {
			if (!activeShoots[x]) {
				int EnemyWhoShoot = rand() % 3;
				switch (EnemyWhoShoot)
				{
				case 0:
					shoot[x].sprite.LoadSprite("Shoot.txt");
					shoot[x].sprite.Location.x = enemy[0].sprite.Location.x + 6;
					shoot[x].sprite.Location.y = enemy[0].sprite.Location.y + 7;
					shoot[x].shootSpeed = 75.f;
					Sprite::AddToCollisionSystem(shoot[x].sprite, "enemyShoot" + x);
					whoShoot[x][0] = 0;
					break;
				case 1:
					shoot[x].sprite.LoadSprite("Shoot.txt");
					shoot[x].sprite.Location.x = enemy[1].sprite.Location.x + 6;
					shoot[x].sprite.Location.y = enemy[1].sprite.Location.y + 7;
					shoot[x].shootSpeed = 75.f;
					Sprite::AddToCollisionSystem(shoot[x].sprite, "enemyShoot" + x);
					whoShoot[x][1] = 1;
					break;
				case 2:
					shoot[x].sprite.LoadSprite("Shoot.txt");
					shoot[x].sprite.Location.x = enemy[2].sprite.Location.x + 6;
					shoot[x].sprite.Location.y = enemy[2].sprite.Location.y + 7;
					shoot[x].shootSpeed = 75.f;
					Sprite::AddToCollisionSystem(shoot[x].sprite, "enemyShoot" + x);
					whoShoot[x][2] = 2;
					break;
				}
				activeShoots[x] = true;
				break;
			}
		}
	}

	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ_MAX; i++) {
		if (shoot[i].sprite.Location.y >= GetScreenEndConsoleY()){
			activeShoots[i] = false;
			whoShoot[i][0] = 5;
			whoShoot[i][1] = 5;
			whoShoot[i][2] = 5;
		}
	}
}

void InitEnemyShoots() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ_MAX; i++) {
		activeShoots[i] = false;
		shoot[i].sprite.Location.y = rand() % 10000 + 100000;
		shoot[i].sprite.Location.x = rand() % 10000 + 100000;
	}
}

void MoveEnemyShoots() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ_MAX; i++) {
		if (activeShoots[i]) {
			shoot[i].sprite.Location.y += shoot[i].shootSpeed * FASG::GetDeltaTime() * 0.5f;
			if (shoot[i].sprite.Location.y >= GetScreenEndConsoleY()) {
				shoot[i].sprite.Location.y = rand() % 10000 + 100000;
				shoot[i].sprite.Location.x = rand() % 10000 + 100000;
			}
		}
	}
}

void DrawEnemyShoots() {
	for (int i = 0; i < NUMERO_DISPAROS_A_LA_VEZ_MAX; i++) {
		if (activeShoots[i]) {
			FASG::WriteSpriteBuffer(shoot[i].sprite.Location.x, shoot[i].sprite.Location.y, shoot[i].sprite);
		}
	}
}

int GetMaxNumberOfEnemiesShoots() {
	return NUMERO_DISPAROS_A_LA_VEZ_MAX;
}

void SetShootEnemyLocation(float x, float y, int number) {
	shoot[number].sprite.Location.x = x;
	shoot[number].sprite.Location.y = y;
}