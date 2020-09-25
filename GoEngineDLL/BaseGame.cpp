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
	glm::vec2 velocity = glm::vec2(0.0f);
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
		if (input->IsKeyPressed(Input::KEY_W)) {
			velocity.y += deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_S)) {
			velocity.y -= deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_A)) {
			velocity.x -= deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_D)) {
			velocity.x += deltaTime;
		}
		if (input->IsKeyPressed(Input::KEY_Q)) {
			angle += deltaTime * 10;
		}
		if (input->IsKeyPressed(Input::KEY_E)) {
			angle -= deltaTime * 10;
		}
		if (input->IsKeyPressed(Input::KEY_1)) {
			triangle->SetScale(0.2, 0.2, 0.2);
		}
		if (input->IsKeyPressed(Input::KEY_2)) {
			triangle->SetScale(1, 1, 1);
		}
		if (input->IsKeyPressed(Input::KEY_3)) {
			triangle->SetScale(2, 2, 2);
		}
		renderer->SetClearColor(clr);
		renderer->ClearScreen();

		triangle->SetPosition(velocity.x, velocity.y, 0);
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
