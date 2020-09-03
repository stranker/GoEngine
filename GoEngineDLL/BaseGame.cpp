#include "BaseGame.h"

bool BaseGame::Init() {
	window->Init();
	renderer->Init();
	renderer->CreateTriangleBuffer();
	return true;
}

bool BaseGame::Destroy(){
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
	while (!window->ShouldClose()){
		renderer->SetClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		renderer->ClearScreen();
		renderer->DrawBuffer(3);
		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title){
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
}

BaseGame::~BaseGame(){
}
