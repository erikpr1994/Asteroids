#include "Menu.h"
#include "FAriasSimpleGraphics.h"
#include "Engine.h"
#include "Asteroid.h"
#include "Player.h"

Menu menu;

char GetAnyKeyPressedInMenu();

void InputMenu();

void UpdateMenu();

void DrawMenu();


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

void ShowMenu() {;
	if (menu.inMenu) {
		InitPlayer();
		InitAsteroids();
		InitShoots();
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