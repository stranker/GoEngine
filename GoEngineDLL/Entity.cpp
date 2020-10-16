#include "Entity.h"

void Entity::SetInput(Input * _input) {
	input = _input;
}

Entity::Entity(Renderer *_renderer) : renderer(_renderer){
}

Entity::~Entity(){
}
