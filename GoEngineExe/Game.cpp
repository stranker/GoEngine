#include "Game.h"

Game::Game(int _screen_width, int _screen_height, const char* _screen_title) : BaseGame(_screen_width, _screen_height, _screen_title) {

}

Game::~Game() {
}

void Game::Start() { CreateTriangle(100, 100); }
void Game::Update() {}
void Game::Stop() { printf("Game::Stop"); }
