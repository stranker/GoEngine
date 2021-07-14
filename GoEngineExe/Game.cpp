#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
}

void Game::CreateBullets(int count) {
	for (size_t i = 0; i < count; i++){
		TankBullet* b = new TankBullet();
		bullets.push_back(b);
		GetRoot()->AddChildren(b);
		b->SetPosition(Vector3(i * 2, 0, 0));
		b->SetName("Bullet" + to_string(i + 1));
	}
}

void Game::CreateMines(int count) {
	for (size_t i = 0; i < count; i++) {
		Mine* mine = new Mine();
		mines.push_back(mine);
		minesParent->AddChildren(mine);
		mine->SetPosition(Vector3(0, 0 , i * 2));
		mine->SetName("Mine" + to_string(i + 1));
		mine->SetScale(Vector3().One() * 0.5f);
	}
}

void Game::OnUpdate(float delta) {
	if (spotLight) {
		const int spotSpeed = 7;
		Vector3 spotVelocity = Vector3();
		if (Input::IsKeyPressed(Input::KEY_UP)){
			spotVelocity += Vector3().Foward();
		}
		if (Input::IsKeyPressed(Input::KEY_DOWN)) {
			spotVelocity += Vector3().Foward() * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_RIGHT)) {
			spotVelocity += Vector3().Right();
		}
		if (Input::IsKeyPressed(Input::KEY_LEFT)) {
			spotVelocity += Vector3().Right() * -1;
		}
		spotLight->Translate(spotVelocity.Normalize() * delta * spotSpeed);
	}
}

void Game::Start() {
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	GetRoot()->AddChildren(camera);
	//// Cubes
	cube = CreateCube();
	cube2 = CreateCube();
	cube->SetName("Cubo padre");
	cube2->SetName("Cubo hijo");
	cube->AddChildren(cube2);
	cubeMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "cubeMaterial");
	cubeMaterial->CreateMaterial(0.5f, 0.0f, "container2.png", "container2_specular.png");
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube->SetPosition(Vector3(0, 3, 0));
	cube2->SetPosition(Vector3(2, 0, 0));
	//// Lights
	//spotLight = CreateSpotLight(Vector3(1, 0, 1), 1, 0.5f, 3, Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = CreateDirectional(Vector3(1, 1, 1), 1, 0.5f);
	dirLight->SetPosition(Vector3(0, 10, 5));
	dirLight->SetScale(Vector3().One() * 0.2);
	//// Models
	tank = new Tank();
	GetRoot()->AddChildren(tank);
	//CreateBullets(5);
	//minesParent = new Node3D("MinesParent");
	//GetRoot()->AddChildren(minesParent);
	//CreateMines(10);
	//mine = new Mine();
	//GetRoot()->AddChildren(mine);
	//Node3D* ship = ResourceManager::LoadModel("escorpion/tank.gltf", "Ship");
	//GetRoot()->AddChildren(ship);
	return OnStart();
}

void Game::Stop() {
	return OnStop();
}
