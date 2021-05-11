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
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	camera->SetPosition(Vector3(0, 0, -20));
	// Cubes
	cube = BaseGame::GetSingleton()->CreateCube();
	cube2 = BaseGame::GetSingleton()->CreateCube();
	cube3 = BaseGame::GetSingleton()->CreateCube();
	cube->SetPosition(Vector3(20, 0, 1));
	cube->SetScale(Vector3(10, 10, 2));
	cube2->SetPosition(Vector3(5, 1, 3));
	cube3->SetPosition(Vector3(-5, 1, 2));
	cube2->Rotate(45.0f, Vector3().Right());
	cube3->Rotate(70.0f, Vector3().Foward());
	cubeMaterial = new SpatialMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube3->SetMaterial(cubeMaterial);
	// Lights
	spotLight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(1, 1, 1), 1, 0.5f, 3, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = BaseGame::GetSingleton()->CreateDirectional(Vector3(1, 1, 1), 1, 0.5f, Vector3().Foward());
	dirLight->SetPosition(Vector3(0, 10, 0));
	dirLight->SetScale(Vector3().One() * 0.2);
	// Model
	cat = BaseGame::GetSingleton()->CreateMeshInstance("cat/cat.fbx");
	//
	tank = new Tank();
	camera->SetTarget(cat);
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	if (spotLight){
		const float velocity = 5 * deltaTime;
		if (Input::IsKeyPressed(Input::KEY_UP)){
			spotLight->Translate(spotLight->GetTransform()->GetFoward() * velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_DOWN)) {
			spotLight->Translate(spotLight->GetTransform()->GetFoward() * -velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_RIGHT)) {
			spotLight->Translate(spotLight->GetTransform()->GetRight() * velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_LEFT)) {
			spotLight->Translate(spotLight->GetTransform()->GetRight() * -velocity);
		}
	}
	if (cube) {
	}
	if (camera)	{
		camera->Update(deltaTime);
	}
	if (cat){
		float angle = sin(timer) * 10;
		cat->Translate(Vector3().Left() * deltaTime * 0.5);
		cat->Rotate(angle, Vector3().Foward());
	}
	if (tank) 	{
		tank->Update(deltaTime);
	}
}

void Game::Stop() {
	if (cube){
		cube->Destroy();
		delete cube;
	}
	if (cube2){
		cube2->Destroy();
		delete cube2;
	}
	if (cube3) {
		cube3->Destroy();
		delete cube3;
	}
	if (camera)	{
		delete camera;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
