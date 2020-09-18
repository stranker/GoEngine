#include "BaseGame.h"

bool BaseGame::Init() {
	window->Init();
	renderer->Init();
	triangle = new Triangle(renderer);
	material = new Material();
	triangle->SetMaterial(material);
	return true;
}

bool BaseGame::Destroy(){
	if (triangle) {
		triangle->Destroy();
		delete triangle;
	}
	if (material) {
		material->Destroy();
		delete material;
	}
	if (renderer){
		renderer->Destroy();
		delete renderer;
	}
	if (window){
		window->Destroy();
		delete window;
	}
	return true;
}

void BaseGame::Loop(){
	Color clr = Color().Purple();
	float velocity = 0;
	float angle = 0;

	double currentFrame = glfwGetTime();;
	double lastFrame = currentFrame;
	double deltaTime;

	while (!window->ShouldClose()){

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (input->IsKeyPressed(Input::KEY_ESCAPE)) {
			window->CloseWindow();
		}
		if (input->IsKeyPressed(Input::KEY_UP)) {
			velocity += deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_DOWN)) {
			velocity -= deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_LEFT)) {
			angle += deltaTime * 10;
		}
		if (input->IsKeyPressed(Input::KEY_RIGHT)) {
			angle -= deltaTime * 10;
		}
		if (input->IsKeyPressed(Input::KEY_0)) {
			triangle->SetScale(0.2, 0.2, 0.2);
		}
		if (input->IsKeyPressed(Input::KEY_1)) {
			triangle->SetScale(1, 1, 1);
		}
		if (input->IsKeyPressed(Input::KEY_2)) {
			triangle->SetScale(2, 2, 2);
		}
		renderer->SetClearColor(clr);
		renderer->ClearScreen();

		triangle->SetPosition(0, velocity, 0);
		triangle->SetRotation(angle, glm::vec3(0.0f, 0.0f, 1.0f));
		triangle->Draw();
	
		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title){
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
	input = new Input(window);
}

BaseGame::~BaseGame(){
}
