#include "BaseGame.h"

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	entityList = new list<Entity*>();
	return true;
}

bool BaseGame::DestroyEngine() {
	delete entityList;
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
	input = new Input();
	input->SetWindow(window);
}

BaseGame::~BaseGame() {
}

#pragma region UserMethods

Sprite* BaseGame::CreateSprite(const char* filePath, ImageType imageType, float x, float y) {
	Sprite *sprite = new Sprite(renderer);
	sprite->SetTexture(filePath, imageType);
	sprite->SetPosition(x, y);
	entityList->push_back(sprite);
	return sprite;
}

void BaseGame::DrawEntities() {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Draw();
	}
}

#pragma endregion
