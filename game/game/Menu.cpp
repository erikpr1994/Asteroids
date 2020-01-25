#include "Menu.h"
#include "FAriasSimpleGraphics.h"
#include "Engine.h"

Menu menu;

extern Game game;

char GetAnyKeyPressedInMenu();

void InputMenu();

void UpdateMenu();

void DrawMenu();


void InitMenu() {
	menu.sprite.LoadSprite("Menu.txt");
	menu.inMenu = true;
	menu.lastInputMenu = EInputMenu::NONE;

	//menu.sprite.Location.x = game.screenCenter.x;
	//menu.sprite.Location.y = game.screenCenter.y;
}

void ShowMenu() {
	while (menu.inMenu) {
		InputMenu();
		UpdateMenu();
		DrawMenu();
	}
}

char GetAnyKeyPressedInMenu() { // Que devuelve según la tecla presionada
	if (FASG::IsKeyPressed('A')) {
		return 'A';
	}
	if (FASG::IsKeyPressed('S')) {
		return 'S';
	}
	else {
		return '\0';
	}
}

void InputMenu() { // Que estado genera según lo que recibe de la tecla presionada
	char key = GetAnyKeyPressedInMenu();

	switch (key)
	{
	case 'A':
		menu.lastInputMenu = EInputMenu::PLAY;
		break;
	case 'S':
		menu.lastInputMenu = EInputMenu::EXIT;
		break;
	}
}

void UpdateMenu() { // Que hace cada estado 
	switch (menu.lastInputMenu)
	{
	case EInputMenu::PLAY:
		menu.inMenu = false;
		break;
	case EInputMenu::EXIT:
		game.gameOver = true;
		break;
	case EInputMenu::NONE:
		break;
	}
}

void DrawMenu() {
	menu.sprite.Location.x = game.screenCenter.x - (64/2);
	menu.sprite.Location.y = game.screenCenter.y - 17;
	
	FASG::WriteSpriteBuffer(menu.sprite.Location.x, menu.sprite.Location.y, menu.sprite);
	
	FASG::RenderFrame();
}