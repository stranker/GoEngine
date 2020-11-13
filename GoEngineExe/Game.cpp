#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	tilemap = BaseGame::GetSingleton()->CreateTilemap("ForestMap.json");
	player = new Player();
	dragon = new Dragon();
	dragon->SetPlayer(player);
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	dragon->Update(deltaTime);
	UpdateCollisions();
}

void Game::UpdateCollisions() {
	CollisionInfo collision;
	collision = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), dragon->GetSprite()->GetAABB());
	if (collision.isColliding) {
		player->ManageCollision(collision);
	}
	vector<CollisionInfo> tilemapCollisions = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), *tilemap);
	if (!tilemapCollisions.empty()) {
		player->ManageCollision(tilemapCollisions);
	}

}

void Game::Stop() {
	if (player) {
		delete player;
	}
	if (dragon) {
		delete dragon;
	}
	if (tilemap) {
		delete tilemap;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
