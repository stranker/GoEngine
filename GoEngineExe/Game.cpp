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
	cube2 = BaseGame::GetSingleton()->CreateCube();
	cube3 = BaseGame::GetSingleton()->CreateCube();
	camera = new GameCamera(screenWidth, screenHeight);
	camera->SetPosition(Vector3(0, 0, 5));
	spotLight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(0, 0, 1), 1, 0.5f, 3, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = BaseGame::GetSingleton()->CreateDirectional(Vector3(0, 1, 0), 1, 0.5f, Vector3().Foward());
	cube->SetPosition(Vector3().Zero());
	cube->SetScale(Vector3(10, 10, 2));
	cube2->SetPosition(Vector3(1, 1, 3));
	cube3->SetPosition(Vector3(-1, 1, 2));
	cube2->Rotate(45.0f, Vector3().Right());
	cube3->Rotate(70.0f, Vector3().Foward());
	cubeMaterial = new SpatialMaterial();
	cubeMaterial->CubeMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube3->SetMaterial(cubeMaterial);
	backpack = BaseGame::GetSingleton()->CreateMeshInstance("cat/cat.glb");
	backpack->SetPosition(Vector3(0,0,8));
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
	if (backpack){
		backpack->Translate(Vector3(0, 0, 1) * deltaTime);
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
