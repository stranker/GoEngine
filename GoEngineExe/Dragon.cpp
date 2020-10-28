#include "Dragon.h"

void Dragon::Update(float deltaTime) {
	sprite->Update(deltaTime);
}

Dragon::Dragon() {
	sprite = BaseGame::GetSingleton()->CreateAnimSprite("dragon.png", IMAGETYPE_PNG, 3, 4);
	unsigned int idle[] = { 3, 4, 5, 4};
	sprite->AddAnimation("idle", idle, 4, true, 8);
	sprite->Play("idle");
	sprite->SetPosition(Vector2(500, 200));
}

Dragon::~Dragon() {
}
