#include "Game.h"

int main(){

	Game *game = new Game();
	game->create_window();
	delete game;
	return 0;
}