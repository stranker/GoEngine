#include "Game.h"

int main(){
	Game *game = new Game(1366, 768, "Pokemon");
	game->Start();
	delete game;
	return 0;
}