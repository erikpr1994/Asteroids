#include "FAriasSimpleGraphics.h"
#include "Player.h"
#include "Engine.h"

Player player;

extern Game game;

void InitPlayer() {
	player.sprite.LoadSprite("Player.txt");
	player.sprite.Location.x = game.screenCenter.x;
	player.sprite.Location.y = game.screenCenter.y;
}

void DrawPlayer(){
	FASG::WriteSpriteBuffer(player.sprite.Location.x, player.sprite.Location.y, player.sprite);
}