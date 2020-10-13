#include "BaseGame.h"

bool BaseGame::Init() {
	entityList = new list<Entity*>();

	window->Init();
	renderer->Init();

	square = new Square(renderer);
	material = new Material();

	square->SetMaterial(material);
	return true;
}

bool BaseGame::Destroy() {
	if (square) {
		square->Destroy();
		delete square;
	}
	if (material) {
		material->Destroy();
		delete material;
	}
	if (renderer) {
		renderer->Destroy();
		delete renderer;
	}
	if (input) {
		delete input;
	}
	if (window) {
		window->Destroy();
		delete window;
	}

	delete entityList;
	return true;
}

void BaseGame::Loop() {
	Color clr = Color().Purple();

	float angle = 0.0f;
	float speed = 100.0f;

	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;


	square->SetPosition(100, 100, 0);

	//Virtual method
	Start();

	while (!window->ShouldClose()) {

		//Virtual method
		Update();

		// Calculo deltaTime
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glm::vec2 velocity = glm::vec2(0.0f);

		// Obtengo Input
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
		renderer->SetClearColor(clr);
		renderer->ClearScreen();

		//================================
		for (eLIterator = entityList->begin(); eLIterator != entityList->end(); eLIterator++)
		{
			(*eLIterator)->Draw();
		}
		//===============================

		square->Draw();


		renderer->SwapBuffers();
		window->PoolEvents();
	}

	//Virtual method
	Stop();
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title) {
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
	input = new Input(window);
}

BaseGame::~BaseGame() {
}

void BaseGame::CreateTriangle(float _x, float _y)
{
	Triangle *triangle = new Triangle(renderer);
	triangle->SetMaterial(material);

	triangle->SetPosition(_x, _y, 0);

	entityList->push_back(triangle);
}
