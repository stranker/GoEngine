#include "Entity.h"

Entity::Entity(Renderer *_renderer) : renderer(_renderer){
	transform = new Transform();
}

Entity::~Entity(){
}

void Entity::Translate(float x, float y, float z) {
	transform->SetPosition(transform->GetPosition().x + x, transform->GetPosition().y + y, transform->GetPosition().z + z);
}
