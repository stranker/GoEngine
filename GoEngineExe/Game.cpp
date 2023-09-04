#include "Game.h"

Game::Game(int _screenWidth, int _screenHeight, const char* _screenTitle) : BaseGame(_screenWidth, _screenHeight, _screenTitle) {
	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	screenTitle = _screenTitle;
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
	if (plight) {
		float x = cos(Time::ElapsedTime()) * 9;
		float z = sin(Time::ElapsedTime()) * 9;
		plight->SetPosition(Vector3(x, 0, z));
	}
	if (plight2) {
		float x = cos(Time::ElapsedTime()) * 9;
		plight2->SetPosition(Vector3(x, plight2->GetPosition().y, plight2->GetPosition().z));
	}
}

void Game::Start() {
	// Camera
	camera = new GameCamera(screenWidth, screenHeight);
	GetRoot()->AddChildren(camera);
	//// Cubes
	Node3D* spatialNode = new Node3D("SpatialNode");
	GetRoot()->AddChildren(spatialNode);

	//container = new Container();
	//spatialNode->AddChildren(container);
	//// Lights
	//spotLight = CreateSpotLight(Vector3(1, 0, 1), 1, 0.5f, 3, Vector3(1, 0.09, 0.032), 12, 15);
	dirLight = new DirectionalLight(Vector3(1, 1, 1), 1, 0.5f);
	dirLight->RotateY(145);
	dirLight->SetPosition(Vector3(0, 10, 5));
	dirLight->SetScale(Vector3().One() * 0.2);
	spatialNode->AddChildren(dirLight);

	plight = new PointLight();
	plight->SetPosition(Vector3(0,0,9));
	spatialNode->AddChildren(plight);

	plight2 = new PointLight();
	plight2->SetPosition(Vector3(0, 2, 3));
	spatialNode->AddChildren(plight2);
	// Models
	//blenderScene = ResourceManager::LoadModel("Models/Link.gltf", "LinkScene");
	//blenderScene->SetScale(Vector3().One() * 0.4f);
	//link = (Node3D*)blenderScene->GetNode("Link");
	//spatialNode->AddChildren(blenderScene);

	Card3D* card = new Card3D();
	spatialNode->AddChildren(card);

	return OnStart();
}

void Game::Stop() {
	return OnStop();
}
