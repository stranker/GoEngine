#include "Game.h"

int main(){
	Game *game = new Game(800, 600, "SKYRIM");
	game->Start();
	game->LoopGame();
	game->Stop();
	delete game;
	return 0;
}