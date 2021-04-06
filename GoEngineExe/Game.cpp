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
	gizmo = BaseGame::GetSingleton()->CreateGizmo();
	light = BaseGame::GetSingleton()->CreateLight();
	light->SetPosition(Vector3().Zero());
	light->SetScale(Vector3().One() * 0.5f);
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	if (light){
		float x = sin(timer) * 10;
		float z = cos(timer) * 10;
		light->SetPosition(Vector3(x, 0, z));
	}
	if (cube) {
		cube->SetLightPosition(light->GetPosition());
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
	if (gizmo){
		gizmo->Destroy();
		delete gizmo;
	}
	if (camera)	{
		camera->Destroy();
		delete camera;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
