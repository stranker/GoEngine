#include "BaseGame.h"

bool BaseGame::free()
{
	if (window){
		window->free();
	}
	return true;
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title){
	window = new Window(_screen_width, _screen_height, _screen_title);
	window->init();
	window->pool_events();
}

BaseGame::~BaseGame(){
}
