#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
}

void Game::CreateBullets(int count) {
}

void Game::CreateMines(int count) {
}

void Game::OnUpdate(float delta) {
	if (link) {
		const int spotSpeed = 7;
		Vector3 spotVelocity = Vector3();
		if (Input::IsKeyPressed(Input::KEY_UP)){
			spotVelocity += link->GetGlobalTransform()->GetFoward() * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_DOWN)) {
			spotVelocity += link->GetGlobalTransform()->GetFoward();
		}
		if (Input::IsKeyPressed(Input::KEY_RIGHT)) {
			spotVelocity += link->GetGlobalTransform()->GetRight() * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_LEFT)) {
			spotVelocity += link->GetGlobalTransform()->GetRight();
		}
		link->Translate(spotVelocity.Normalize() * delta * spotSpeed);
	}
}

void Game::Start() {
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	GetRoot()->AddChildren(camera);
	//// Cubes
	Node3D* spatialNode = new Node3D("SpatialNode");
	GetRoot()->AddChildren(spatialNode);
	cubeMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "cubeMaterial");
	cubeMaterial->CreateMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube = new Cube();
	cube->SetName("CuboCentro");
	cube->SetMaterial(cubeMaterial);
	cube->SetPosition(Vector3(0, 0, 0));
	cube->SetScale(Vector3().One() * 0.7);
	spatialNode->AddChildren(cube);
	//// Lights
	//spotLight = CreateSpotLight(Vector3(1, 0, 1), 1, 0.5f, 3, Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = new DirectionalLight(Vector3(1, 1, 1), 1, 0.5f);
	dirLight->RotateY(145);
	dirLight->SetPosition(Vector3(0, 10, 5));
	dirLight->SetScale(Vector3().One() * 0.2);
	spatialNode->AddChildren(dirLight);
	//// Models
	/*tank = new Tank();
	GetRoot()->AddChildren(tank);*/
	blenderScene = ResourceManager::LoadModel("Models/Link.gltf", "LinkScene");
	blenderScene->SetScale(Vector3().One() * 0.4f);
	link = (Node3D*)blenderScene->GetNode("Link");
	spatialNode->AddChildren(blenderScene);
	//RayCast3D* rayCast = new RayCast3D(Vector3().Zero(), Vector3().Right(), 5, Color().Magenta());
	//spatialNode->AddChildren(rayCast);
	return OnStart();
}

void Game::Stop() {
	return OnStop();
}
