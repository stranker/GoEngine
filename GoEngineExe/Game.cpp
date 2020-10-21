#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	player = new Player();
	player->AddSprite(CreateSprite("player.png", IMAGETYPE_PNG, 100, 100));
	container = new Container();
	container->AddSprite(CreateSprite("container.jpg", IMAGETYPE_JPG, 20, 20));
	dragon = new Dragon();
	dragon->AddSprite(CreateSprite("dragon.png", IMAGETYPE_PNG, 600, 100));
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	container->Update(deltaTime);
	DrawEntities();
}

void Game::Stop() {
	if (player) {
		player->Destroy();
		delete player;
	}
	if (container) {
		container->Destroy();
		delete container;
	}
	DestroyEngine();
}
