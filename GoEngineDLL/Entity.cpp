#include "Entity.h"

Entity::Entity(Renderer *_renderer) : renderer(_renderer) {
	transform = new Transform();
}

Entity::~Entity() {
}