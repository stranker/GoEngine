#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	tilemap = BaseGame::GetSingleton()->CreateTilemap("ForestMap.json");
	player = new Player();
	CreateEnemies();
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	for (Enemy *enemy : enemies) {
		enemy->Update(deltaTime);
	}
	UpdateCollisions();
}

void Game::CreateEnemies() {
	for (size_t i = 0; i < tilemap->GetMapObjects().size(); i++) {
		CreateEnemy(tilemap->GetMapObjects()[i].attribute, tilemap->GetMapObjects()[i].position);
	}
}

void Game::CreateEnemy(int attribute, Vector2 position) {
	if (attribute == 0) { // enemy type
		Bat *bat = new Bat();
		bat->SetPosition(position);
		enemies.push_back(bat);
	}
	else if (attribute == 1) { // enemy type
		Dragon *dragon = new Dragon();
		dragon->SetPosition(position);
		dragon->SetPlayer(player);
		enemies.push_back(dragon);
	}
}

void Game::UpdateCollisions() {
	for (Enemy *enemy : enemies) {
		collision = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), enemy->GetSprite()->GetAABB());
		if (collision.isColliding) {
			player->ManageCollision(collision);
		}
	}
	tilemapCollisions = CollisionManager::CheckCollision(player->GetSprite()->GetAABB(), *tilemap);
	if (!tilemapCollisions.empty()) {
		player->ManageCollision(tilemapCollisions);
	}
}

void Game::Stop() {
	if (player) {
		delete player;
	}
	if (tilemap) {
		delete tilemap;
	}
	if (!enemies.empty()) {
		for (Enemy *enemy : enemies) {
			delete enemy;
		}
		enemies.clear();
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
