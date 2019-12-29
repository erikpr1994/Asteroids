#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"

extern Game game;

Player player;

void InitPlayer() {
	player.sprite.Location.x = game.screenCenter.x;
	player.sprite.Location.y = game.screenCenter.y;
	player.sprite.LoadSprite("Player.txt");
}