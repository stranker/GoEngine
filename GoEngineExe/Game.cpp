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
	light = BaseGame::GetSingleton()->CreateLight(Vector3().One());
	cube->SetPosition(Vector3().Zero());
	cube->SetScale(Vector3(10, 10, 2));
	cube2->SetPosition(Vector3(1, 1, 3));
	cube3->SetPosition(Vector3(-1, 1, 2));
	cube2->Rotate(45.0f, Vector3().Right());
	cube3->Rotate(70.0f, Vector3().Foward());
	cubeMaterial = new SpatialMaterial(Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3().One() * 0.5, 32.0f);
	cubeMaterial->SetDiffuseMap("container2.png", ImageType::IMAGETYPE_PNG);
	cubeMaterial->SetSpecularMap("container2_specular.png", ImageType::IMAGETYPE_PNG);
	cube->SetMaterial(cubeMaterial);
	cube2->SetMaterial(cubeMaterial);
	cube3->SetMaterial(cubeMaterial);
	cube->SetLight(light);
	cube2->SetLight(light);
	cube3->SetLight(light);
}

void Game::Update(float deltaTime) {
	timer += deltaTime;
	if (light){
		const float velocity = 5 * deltaTime;
		if (Input::IsKeyPressed(Input::KEY_UP)){
			light->Translate(light->GetTransform()->GetFoward() * velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_DOWN)) {
			light->Translate(light->GetTransform()->GetFoward() * -velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_RIGHT)) {
			light->Translate(light->GetTransform()->GetRight() * velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_LEFT)) {
			light->Translate(light->GetTransform()->GetRight() * -velocity);
		}
		if (Input::IsKeyPressed(Input::KEY_Q)) {
			cout << light->GetRange() << endl;
			light->SetRange(light->GetRange() - deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_E)) {
			cout << light->GetRange() << endl;
			light->SetRange(light->GetRange() + deltaTime);
		}
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
