#include "BaseGame.h"

bool BaseGame::free()
{
	if (window){
		window->free();
	}
	return true;
}

void BaseGame::init(){
	window->init();
}

void BaseGame::loop(){
	while (!window->should_close()){
		window->set_clear_color(0.5f, 0.0f, 0.5f, 1.0f);
		window->clear_color();
		window->swap_buffers();
		window->pool_events();
	}
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title){
	window = new Window(_screen_width, _screen_height, _screen_title);
}

BaseGame::~BaseGame(){
}
