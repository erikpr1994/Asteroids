#pragma once
#include "FAriasSimpleGraphics.h"


enum EInputMenu {
	PLAY, EXIT, NONE
};

struct Menu {
	FASG::Sprite sprite;
	EInputMenu lastInputMenu;
	bool inMenu;
};

void ShowMenu();

void InitMenu();

// GETTERS Y SETTERS
bool GetInMenu();

void SetInMenu(bool value);