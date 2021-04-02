#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	/*tilemap = BaseGame::GetSingleton()->CreateTilemap("ForestMap.json");
	player = new Player();
	CreateEnemies();*/
	cube = BaseGame::GetSingleton()->CreateCube();
	camera = BaseGame::GetSingleton()->CreateCamera3D(screenWidth, screenHeight);
	camera->Translate(Vector3(0, 0, -3));
	//gizmo = BaseGame::GetSingleton()->CreateGizmo();
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	if (cube) {
		cube->Rotate(deltaTime * 20, Vector3().Up());
	}
	if (player) {
		player->Update(deltaTime);
	}
	if (camera)	{
		if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)){
			//cout << Input::GetMousePosition().ToString().c_str() << endl;
			if (Input::IsKeyPressed(Input::KEY_W)) {
				camera->Translate(Vector3().Foward() * -cameraVelocity * deltaTime);
			}
			if (Input::IsKeyPressed(Input::KEY_S)) {
				camera->Translate(Vector3().Back() * -cameraVelocity * deltaTime);
			}
			if (Input::IsKeyPressed(Input::KEY_A)) {
				camera->Translate(Vector3().Right() * cameraVelocity * deltaTime);
			}
			if (Input::IsKeyPressed(Input::KEY_D)) {
				camera->Translate(Vector3().Right() * -cameraVelocity * deltaTime);
			}
		}
	}
	for (Enemy *enemy : enemies) {
		enemy->Update(deltaTime);
	}
	//UpdateCollisions();
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
	if (cube){
		cube->Destroy();
		delete cube;
	}
	if (gizmo){
		gizmo->Destroy();
		delete gizmo;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
