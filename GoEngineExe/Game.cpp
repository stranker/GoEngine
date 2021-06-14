#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
}

void Game::Start() {
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	camera->SetPosition(Vector3(0, 0, 0));
	GetRoot()->AddChildren(camera);
	// Cubes
	cube = CreateCube();
	cube2 = CreateCube();
	GetRoot()->AddChildren(cube);
	cube->SetName("Cubo padre");
	cube2->SetName("Cubo hijo");
	cube->AddChildren(cube2);
	cubeMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "cubeMaterial");
	cubeMaterial->CreateMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube->SetPosition(Vector3(0, 3, 0));
	cube2->SetPosition(Vector3(2, 0, 0));
	// Lights
	//spotLight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(1, 1, 1), 1, 0.5f, 3, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = BaseGame::GetSingleton()->CreateDirectional(Vector3(1, 1, 1), 1, 0.5f, Vector3().Foward());
	dirLight->SetPosition(Vector3(0, 10, 5));
	dirLight->SetScale(Vector3().One() * 0.2);
	GetRoot()->AddChildren(dirLight);
	// Models
	cat = LoadModel("cat/cat.fbx");
	GetRoot()->AddChildren(cat);
	//minecraft = BaseGame::GetSingleton()->CreateMeshInstance("minecraft/scene.gltf");
	//minecraft->SetScale(Vector3().One() * 0.1f);
	//beer = BaseGame::GetSingleton()->CreateMeshInstance("beer/scene.gltf");
	//beer->SetPosition(Vector3(-5, 0, 5));
	//beer->Rotate(-90, Vector3().Right());
	//wizard = BaseGame::GetSingleton()->CreateMeshInstance("wizard/scene.gltf");
	//wizard->SetPosition(Vector3(5, 0, 5));
	//wizard->Rotate(-90, Vector3().Right());
	//reptile = BaseGame::GetSingleton()->CreateMeshInstance("reptile/scene.gltf");
	//reptile->SetPosition(Vector3(5, 0, -2));
	//reptile->SetScale(Vector3().One() * 0.01);
	//reptile->Rotate(-90, Vector3().Right());
	////
	tank = new Tank();
	GetRoot()->AddChildren(tank);
	return OnStart();
}

void Game::Stop() {
	return OnStop();
}
