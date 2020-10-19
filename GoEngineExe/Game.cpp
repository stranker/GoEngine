#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}

void Game::Start() {
	InitEngine();
	nAKELS = CreateSprite(100, 100);
	tri = CreateTriangle(100, 200);
}

void Game::Update(float deltaTime) {
	if (KeyPressed(Input::KEY_A))
		nAKELS->Translate(-100 * deltaTime, 0, 0);
	if (KeyPressed(Input::KEY_D))
		nAKELS->Translate(100 * deltaTime, 0, 0);
	if (KeyPressed(Input::KEY_W))
		nAKELS->Translate(0, 100 * deltaTime, 0);
	if (KeyPressed(Input::KEY_S))
		nAKELS->Translate(0, -100 * deltaTime, 0);

	if (KeyPressed(Input::KEY_LEFT))
		tri->Translate(-100 * deltaTime, 0, 0);
	if (KeyPressed(Input::KEY_RIGHT))
		tri->Translate(100 * deltaTime, 0, 0);
	if (KeyPressed(Input::KEY_UP))
		tri->Translate(0, 100 * deltaTime, 0);
	if (KeyPressed(Input::KEY_DOWN))
		tri->Translate(0, -100 * deltaTime, 0);

	//UpdateEntities(deltaTime);
	DrawEntities();
}

void Game::Stop() {
	DestroyEngine();
}
