#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	entityList = new list<Entity*>();

	currentFrame = glfwGetTime();
	lastFrame = currentFrame;
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
	while (!window->ShouldClose()) {

		if (input->IsKeyPressed(Input::KEY_ESCAPE)) {
			window->CloseWindow();
		}

		// Calculo deltaTime
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer->SetClearColor(Color().Purple());
		renderer->ClearScreen();

		Update(deltaTime);

		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

BaseGame * BaseGame::GetSingleton(){
	return singleton;
}

BaseGame* BaseGame::singleton = nullptr;

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title) {
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
	input = new Input();
	input->SetWindow(window);
	singleton = this;
}

BaseGame::~BaseGame() {
	singleton = NULL;
}

#pragma region UserMethods

Sprite* BaseGame::CreateSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames) {
	Sprite *sprite = new Sprite(renderer);
	sprite->SetTexture(filePath, imageType, vFrames, hFrames);
	entityList->push_back(sprite);
	return sprite;
}

AnimatedSprite * BaseGame::CreateAnimSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames) {
	AnimatedSprite *animSprite = new AnimatedSprite(renderer);
	animSprite->SetTexture(filePath, imageType, vFrames, hFrames);
	entityList->push_back(animSprite);
	return animSprite;
}

void BaseGame::DrawEntities() {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Draw();
	}
}

#pragma endregion
