#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
}

void Game::Start() {
	InitEngine();
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	camera->SetPosition(Vector3(0, 0, 0));
	GetRoot()->AddChildren(camera);
	// Cubes
	cube = BaseGame::GetSingleton()->CreateCube();
	cube2 = BaseGame::GetSingleton()->CreateCube();
	cube3 = BaseGame::GetSingleton()->CreateCube();
	GetRoot()->AddChildren(cube);
	GetRoot()->AddChildren(cube3);
	cube->SetName("Cubo padre");
	cube2->SetName("Cubo hijo");
	cube->AddChildren(cube2);
	cubeMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "cubeMaterial");
	cubeMaterial->CreateMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube3->SetMaterial(cubeMaterial);
	cube->SetPosition(Vector3(0, 3, 0));
	cube2->SetPosition(Vector3(2, 0, 0));
	cube3->SetPosition(Vector3(0, 0, 0));
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
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	//if (spotLight){
	//	const float velocity = 5 * deltaTime;
	//	if (Input::IsKeyPressed(Input::KEY_UP)){
	//		spotLight->Translate(spotLight->GetTransform().GetFoward() * velocity);
	//	}
	//	if (Input::IsKeyPressed(Input::KEY_DOWN)) {
	//		spotLight->Translate(spotLight->GetTransform().GetFoward() * -velocity);
	//	}
	//	if (Input::IsKeyPressed(Input::KEY_RIGHT)) {
	//		spotLight->Translate(spotLight->GetTransform().GetRight() * velocity);
	//	}
	//	if (Input::IsKeyPressed(Input::KEY_LEFT)) {
	//		spotLight->Translate(spotLight->sGetTransform().GetRight() * -velocity);
	//	}
	//}
	if (camera)	{
		camera->Update(deltaTime);
	}
	if (cube){

		float rotationX = cube->GetRotation().x;
		float rotationY = cube->GetRotation().y;
		float rotationZ = cube->GetRotation().z;
		float rotation2X = cube2->GetRotation().x;
		float rotation2Y = cube2->GetRotation().y;
		float rotation2Z = cube2->GetRotation().z;
		ImguiBegin("Cubes");
		ImguiText("Cube1");
		ImguiSliderFloat("rotationX", &rotationX, 0, 360);
		ImguiSliderFloat("rotationY", &rotationY, 0, 360);
		ImguiSliderFloat("rotationZ", &rotationZ, 0, 360);
		ImguiText("Cube2");
		ImguiSliderFloat("rotation2X", &rotation2X, 0, 360);
		ImguiSliderFloat("rotation2Y", &rotation2Y, 0, 360);
		ImguiSliderFloat("rotation2Z", &rotation2Z, 0, 360);
		ImguiEnd();
		cube->SetEulerAngles(Vector3(rotationX, rotationY, rotationZ));
		cube2->SetEulerAngles(Vector3(rotation2X, rotation2Y, rotation2Z));
	}
	if (cat){
		float angle = sin(timer) * deltaTime * 10;
		cat->Translate(Vector3().Left() * deltaTime * 0.5);
		//cat->Rotate(angle, Vector3().Foward());
	}
	if (tank){
		tank->Update(deltaTime);
	}
	//if (minecraft){
	//	float dir = sin(timer);
	//	minecraft->Translate(Vector3().Up() * dir * deltaTime);
	//	minecraft->Rotate(deltaTime * 50, Vector3().Up());
	//}
	//if (beer){
	//	beer->Rotate(deltaTime * -10, Vector3().Foward());
	//}
	//if (wizard){
	//	float dir = sin(timer);
	//	wizard->Rotate(dir * 10 * deltaTime, Vector3().Up());
	//}
}

void Game::Stop() {
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
