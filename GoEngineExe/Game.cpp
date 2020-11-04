#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {

}
Sprite* a;
void Game::Start() {
	InitEngine();
	a = CreateSprite("player.png", IMAGETYPE_PNG, 1, 1);
	SetPosition(a, 100, 100);

	player = new Player();
	container = new Container();
	dragon = new Dragon();
}

void Game::Update(float deltaTime) {
	player->Update(deltaTime);
	container->Update(deltaTime);
	dragon->Update(deltaTime);
	Translate(a, 50 * deltaTime, 50 * deltaTime);
	Scale(a, GetScale(a).x + 50 * deltaTime, GetScale(a).x + 50 * deltaTime);
	Rotate(a, GetRotation(a) + 50 * deltaTime);
	DrawEntities();
}

void Game::Stop() {
	if (player) {
		delete player;
	}
	if (container) {
		delete container;
	}
	if (dragon) {
		delete dragon;
	}
	DestroyEngine();
}

void Game::LoopGame() {
	LoopEngine();
}
