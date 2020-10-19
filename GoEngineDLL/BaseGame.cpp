#include "BaseGame.h"

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	entityList = new list<Entity*>();
	material = new Material();
	return true;
}

bool BaseGame::DestroyEngine() {
	delete entityList;
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
	return true;
}

void BaseGame::LoopEngine() {
	Color clr = Color().Purple();

	while (!window->ShouldClose()) {

		if (input->IsKeyPressed(Input::KEY_ESCAPE)) {
			window->CloseWindow();
		}

		// Calculo deltaTime
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer->SetClearColor(clr);
		renderer->ClearScreen();

		Update(deltaTime);

		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title) {
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
	input = new Input(window);
}

BaseGame::~BaseGame() {
}

void BaseGame::CreateSprite(float x, float y) {
	Sprite *sprite = new Sprite(renderer);
	sprite->SetTexture("player.png", TextureData::IT_PNG);
	sprite->SetPosition(x, y, 0);
	sprite->SetInput(input);
	entityList->push_back(sprite);
}

void BaseGame::CreateTriangle(float _x, float _y)
{
	Triangle *triangle = new Triangle(renderer);

	triangle->SetMaterial(material);

	triangle->SetPosition(_x, _y, 0);

	triangle->SetInput(input);

	entityList->push_back(triangle);
}

void BaseGame::UpdateEntities(float deltaTime) {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Update(deltaTime);
	}
}

void BaseGame::DrawEntities() {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Draw();
	}
}
