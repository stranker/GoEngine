#include "Entity.h"
#include "Renderer.h"
#include "Transform.h"

Entity::Entity(Renderer *_renderer) : renderer(_renderer) {
	transform = new Transform();
}

Entity::~Entity() {
}