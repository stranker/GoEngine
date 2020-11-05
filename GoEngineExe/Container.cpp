#include "Container.h"

Sprite * Container::GetSprite() const {
	return sprite;
}

void Container::Update(float deltaTime) {
	velocity.x = direction * movementSpeed;
	if (sprite->GetPosition().x >= BaseGame::GetSingleton()->GetWindowSize().x - sprite->GetSize().x) {
		direction = -1;
	}
	else if (sprite->GetPosition().x <= 0) {
		direction = 1;
	}
	velocity.x = direction * movementSpeed;
	sprite->Translate(velocity * deltaTime);
}

Container::Container() {
	sprite = BaseGame::GetSingleton()->CreateSprite("container.jpg", IMAGETYPE_JPG, 1, 1);
	sprite->SetPosition(Vector2(100, 100));
}

Container::~Container() {
}
