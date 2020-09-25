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
	
	float angle = 0.0f;
	float speed = 100.0f;
	
	double currentFrame = glfwGetTime();;
	double lastFrame = currentFrame;
	double deltaTime;

	triangle->SetPosition(400, 300, 0);

	while (!window->ShouldClose()){

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::vec2 velocity = glm::vec2(0.0f);

		if (input->IsKeyPressed(Input::KEY_ESCAPE)) {
			window->CloseWindow();
		}
		if (input->IsKeyPressed(Input::KEY_W)) {
			velocity.y += speed;
		}
		if (input->IsKeyPressed(Input::KEY_S)) {
			velocity.y -= speed;
		}
		if (input->IsKeyPressed(Input::KEY_A)) {
			velocity.x -= speed;
		}
		if (input->IsKeyPressed(Input::KEY_D)) {
			velocity.x += speed;
		}
		if (input->IsKeyPressed(Input::KEY_Q)) {
			angle += deltaTime * 20;
		}
		if (input->IsKeyPressed(Input::KEY_E)) {
			angle -= deltaTime * 20;
		}
		if (input->IsKeyPressed(Input::KEY_1)) {
			triangle->SetScale(50, 50, 1);
		}
		if (input->IsKeyPressed(Input::KEY_2)) {
			triangle->SetScale(100, 100, 100);
		}
		if (input->IsKeyPressed(Input::KEY_3)) {
			triangle->SetScale(200, 200, 200);
		}
		renderer->SetClearColor(clr);
		renderer->ClearScreen();

		triangle->Translate(velocity.x * deltaTime, velocity.y * deltaTime);
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
