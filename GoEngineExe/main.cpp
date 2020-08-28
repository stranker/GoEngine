#include "Game.h"

int main(){

	Game *game = new Game(800, 600, "SKYRIM");
	game->free();
	delete game;
	return 0;
}