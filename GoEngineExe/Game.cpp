#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	tilemap = BaseGame::GetSingleton()->CreateTilemap("ForestMap.json");
	tilemap->SetTexture("tileset.png", IMAGETYPE_PNG, 21, 23);
	player = new Player();
	container = new Container();
	dragon = new Dragon();
	dragon->SetPlayer(player);
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	container->Update(deltaTime);
	dragon->Update(deltaTime);
	CollisionInfo collision;
	collision = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), dragon->GetSprite()->GetAABB());
	if (collision.isColliding) {
		player->ManageCollision(collision);
	}
	collision = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), container->GetSprite()->GetAABB());
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
	if (container) {
		delete container;
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
