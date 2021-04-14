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
	cube = BaseGame::GetSingleton()->CreateCube();
	camera = new GameCamera(screenWidth, screenHeight);
	light = BaseGame::GetSingleton()->CreateLight(Vector3().One(), Vector3().One() * 0.2, Vector3().One(), Vector3().One());
	cube->SetScale(Vector3().One());
	cube->SetPosition(Vector3().Zero());
	light->SetScale(Vector3().One() * 0.5f);
	light->SetPosition(Vector3(10, 2, 0));
	cube->SetLight(light);
	cubeMaterial = new SpatialMaterial(Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3().One() * 0.5, 32.0f);
	cube->SetMaterial(cubeMaterial);
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	if (light){
		float x = sin(timer) * 10;
		float z = cos(timer) * 10;
		light->SetPosition(Vector3(x, light->GetPosition().y, z));
	}
	if (cube) {
		Vector3 velocity;
		velocity.x = dir * deltaTime * 2;
		//cube->Translate(velocity);
		if ((int)timer % 2 == 0 && (int)timer != 0){
			dir = -dir;
		}
	}
	if (camera)	{
		camera->Update(deltaTime);
	}
}

void Game::Stop() {
	if (cube){
		cube->Destroy();
		delete cube;
	}
	if (camera)	{
		delete camera;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
