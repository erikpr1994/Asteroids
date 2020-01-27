#include "Menu.h"
#include "FAriasSimpleGraphics.h"
#include "Engine.h"
#include "Asteroid.h"
#include "Player.h"
#include "Stars.h"
#include "Enemies.h"

Menu menu;

char GetAnyKeyPressedInMenu();

void InputMenu();

void UpdateMenu();

void DrawMenu();

bool sonidoCargado = false;
bool sonidoPlay = false;
FASG::MIDISound song;

void InitMenu() {
	menu.sprite.LoadSprite("Menu.txt");
	menu.inMenu = true;
	menu.lastInputMenu = EInputMenu::NONE;
}

bool GetInMenu() {
	return menu.inMenu;
}

void SetInMenu(bool value) {
	menu.inMenu = value;
}

void ShowMenu() {
	if (menu.inMenu) {
		if(!sonidoCargado){
			song.LoadSound("SW.mid");
			sonidoCargado = true;
		}
		if (!sonidoPlay) {
			song.Play();
			sonidoPlay = true;
		}
		InitPlayer();
		InitAsteroids();
		InitShoots();
		InitStars();
		InitEnemies();
		InitEnemyShoots();
		InitShootsSounds();
	}
	while (menu.inMenu) {
		menu.lastInputMenu = EInputMenu::NONE;
		InputMenu();
		UpdateMenu();
		DrawMenu();
	}	
}

char GetAnyKeyPressedInMenu() { // Que devuelve según la tecla presionada
	if (FASG::IsKeyPressed('Z')) {
		return 'Z';
	}
	if (FASG::IsKeyPressed('X')) {
		return 'X';
	}
	else {
		return '\0';
	}
}

void InputMenu() { // Que estado genera según lo que recibe de la tecla presionada
	char key = GetAnyKeyPressedInMenu();

	switch (key)
	{
	case 'Z':
		menu.lastInputMenu = EInputMenu::PLAY;
		song.Stop();
		sonidoPlay = false;
		break;
	case 'X':
		menu.lastInputMenu = EInputMenu::EXIT;
		break;
	}
}

void UpdateMenu() { // Que hace cada estado 
	switch (menu.lastInputMenu)
	{
	case EInputMenu::PLAY:
		SetInMenu(false);
		break;
	case EInputMenu::EXIT:
		SetInMenu(false);
		SetIsGameClosed(true);
		break;
	case EInputMenu::NONE:
		break;
	}
}

void DrawMenu() {
	menu.sprite.Location.x = GetScreenCenterX() - (64/2);
	menu.sprite.Location.y = GetScreenCenterY() - 17;
	
	FASG::WriteSpriteBuffer(menu.sprite.Location.x, menu.sprite.Location.y, menu.sprite);
	
	FASG::RenderFrame();
}