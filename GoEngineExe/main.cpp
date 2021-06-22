#include "Game.h"

int main(){
	Game *game = new Game(1280, 720, "Tankargeddon");
	game->Start();
	delete game;
	return 0;
}