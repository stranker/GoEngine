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
	//camera = new GameCamera(screenWidth, screenHeight);
	//camera->SetPosition(Vector3(0, 0, -20));
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
	cubeMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "cubeMaterial");
	cubeMaterial.CreateMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube3->SetMaterial(cubeMaterial);
	// Lights
	spotLight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(1, 1, 1), 1, 0.5f, 3, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = BaseGame::GetSingleton()->CreateDirectional(Vector3(1, 1, 1), 1, 0.5f, Vector3().Foward());
	dirLight->SetPosition(Vector3(0, 10, 0));
	dirLight->SetScale(Vector3().One() * 0.2);
	// Models
	cat = BaseGame::GetSingleton()->CreateMeshInstance("cat/cat.fbx");
	minecraft = BaseGame::GetSingleton()->CreateMeshInstance("minecraft/scene.gltf");
	minecraft->SetScale(Vector3().One() * 0.1f);
	beer = BaseGame::GetSingleton()->CreateMeshInstance("beer/scene.gltf");
	beer->SetPosition(Vector3(-5, 0, 5));
	beer->Rotate(-90, Vector3().Right());
	wizard = BaseGame::GetSingleton()->CreateMeshInstance("wizard/scene.gltf");
	wizard->SetPosition(Vector3(5, 0, 5));
	wizard->Rotate(-90, Vector3().Right());
	reptile = BaseGame::GetSingleton()->CreateMeshInstance("reptile/scene.gltf");
	reptile->SetPosition(Vector3(5, 0, -2));
	reptile->SetScale(Vector3().One() * 0.01);
	reptile->Rotate(-90, Vector3().Right());
	//
	tank = new Tank();
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
	if (camera)	{
		camera->Update(deltaTime);
	}
	if (cat){
		float angle = sin(timer) * deltaTime * 10;
		cat->Translate(Vector3().Left() * deltaTime * 0.5);
		cat->Rotate(angle, Vector3().Foward());
	}
	if (tank){
		tank->Update(deltaTime);
	}
	if (minecraft){
		float dir = sin(timer);
		minecraft->Translate(Vector3().Up() * dir * deltaTime);
		minecraft->Rotate(deltaTime * 50, Vector3().Up());
	}
	if (beer){
		beer->Rotate(deltaTime * -10, Vector3().Foward());
	}
	if (wizard){
		float dir = sin(timer);
		wizard->Rotate(dir * 10 * deltaTime, Vector3().Up());
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
