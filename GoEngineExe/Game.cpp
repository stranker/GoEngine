#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	player = new Player();
	player->AddSprite(CreateSprite("player.png", IMAGETYPE_PNG, 100, 100));
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	DrawEntities();
}

void Game::Stop() {
	if (player) {
		player->Destroy();
		delete player;
	}
	DestroyEngine();
}
