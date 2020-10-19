#include "Entity.h"

Entity::Entity(Renderer *_renderer) : renderer(_renderer) {
	transform = new Transform();
}

Entity::~Entity() {
}

void Entity::Translate(float x, float y, float z) {
	transform->SetPosition(transform->GetPosition().x + x, transform->GetPosition().y + y, transform->GetPosition().z + z);
}

void Entity::Rotate(float _angle, RotationAxis _axis)
{
	glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);
	float angle = 0.0f;

	switch (_axis)
	{
	case Entity::X:
		axis = glm::vec3(1.0f, 0.0f, 0.0f);
		angle = transform->GetRotation().x + _angle;
		break;
	case Entity::Y:
		axis = glm::vec3(0.0f, 1.0f, 0.0f);
		angle = transform->GetRotation().y + _angle;
		break;
	case Entity::Z:
		axis = glm::vec3(0.0f, 0.0f, 1.0f);
		angle = transform->GetRotation().z + _angle;
		break;
	default:
		break;
	}

	transform->SetRotation(angle, axis);
}

void Entity::Scale(float x, float y, float z)
{
	transform->SetScale(transform->GetScale().x + x, transform->GetScale().y + y, transform->GetScale().z + z);
}
