#include "Container.h"

void Container::Update(float deltaTime) {
	velocity.x = direction * movementSpeed;
	if (BaseGame::GetSingleton()->GetPosition(sprite).x > BaseGame::GetSingleton()->GetWindowSize().x -
		BaseGame::GetSingleton()->GetSpriteSize(sprite).x * 0.5) {
		direction = -1;
	}
	else if (BaseGame::GetSingleton()->GetPosition(sprite).x <
		BaseGame::GetSingleton()->GetSpriteSize(sprite).x * 0.5) {
		direction = 1;
	}
	BaseGame::GetSingleton()->Translate(sprite, velocity.x * deltaTime,velocity.y * deltaTime);
}

Container::Container() {
	sprite = BaseGame::GetSingleton()->CreateSprite("container.jpg", IMAGETYPE_JPG, 1, 1);
	BaseGame::GetSingleton()->SetPosition(sprite, 100, 100);
}

Container::~Container() {
}
