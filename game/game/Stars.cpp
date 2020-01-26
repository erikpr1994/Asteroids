#include "Stars.h"
#include "Engine.h"
#include <iostream>
#include <conio.h>

int const MAX_STARS = 100;

Stars star[MAX_STARS];

void InitStars() {
	for (int i = 0; i < MAX_STARS; i++) {
		int xAleatoria = GetScreenEndConsoleX();
		int yAleatoria = GetScreenEndConsoleY();
		star[i].posicion.x = rand()%xAleatoria;
		star[i].posicion.y = rand() % yAleatoria;
		star[i].color = EForeColor::LightYellow;
		star[i].skin = '*';
	}
}

void DrawStars() {
	for (int i = 0; i < MAX_STARS; i++) {
		FASG::WriteCharBuffer(star[i].posicion.x, star[i].posicion.y, star[i].skin, star[i].color);
	}
}

void MoveStars() {
	for (int i = 0; i < MAX_STARS; i++) {
		int movimiento = rand() % 3;
		switch(movimiento){
			case 0:
				star[i].posicion.y -= FASG::GetDeltaTime()*10;
				break;
			case 1:
				star[i].posicion.y -= FASG::GetDeltaTime() * 10;
				star[i].posicion.x -= FASG::GetDeltaTime() * 5;
				break;
			case 2:
				star[i].posicion.y -= FASG::GetDeltaTime() * 10;
				star[i].posicion.x += FASG::GetDeltaTime() * 5;
				break;
		}
		if (star[i].posicion.y <= 0) {
			int yAleatoria = GetScreenEndConsoleY();
			star[i].posicion.y = rand() % yAleatoria;
		}
	}
}