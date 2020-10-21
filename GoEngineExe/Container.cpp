#include "Container.h"

void Container::Update(float deltaTime) {
	velocity.x = direction * movementSpeed;
	if (sprite->GetPosition().x > Window::GetSingleton()->GetSize().x - sprite->GetSize().x * 0.5) {
		direction = -1;
	}
	else if (sprite->GetPosition().x < sprite->GetSize().x * 0.5) {
		direction = 1;
	}
	sprite->Translate(velocity * deltaTime);
}
