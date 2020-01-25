#pragma once
#include "FAriasSimpleGraphics.h"


enum EInputMenu {
	PLAY, EXIT
};

struct Menu {
	FASG::Sprite sprite;
	EInputMenu lastInputMenu;
	bool inMenu;
};

void ShowMenu();

void InitMenu();


