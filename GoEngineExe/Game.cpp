#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	player = new Player();
	container = new Container();
	dragon = new Dragon();
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	container->Update(deltaTime);
	dragon->Update(deltaTime);
	CollisionInfo collision = CollisionManager::CheckCollision(*player->GetSprite(), *dragon->GetSprite());
	if (collision.isColliding) {
		player->ManageCollision(collision);
	}
	collision = CollisionManager::CheckCollision(*player->GetSprite(), *container->GetSprite());
	if (collision.isColliding) {
		player->ManageCollision(collision);
	}
	DrawEntities();
}

void Game::Stop() {
	if (player) {
		delete player;
	}
	if (container) {
		delete container;
	}
	if (dragon) {
		delete dragon;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
