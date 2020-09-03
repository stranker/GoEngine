#include "Game.h"

int main(){

	Game *game = new Game(800, 600, "SKYRIM");
	game->Init();
	game->Loop();
	game->Destroy();
	delete game;
	return 0;
}