#include "Player.h"

Sprite * Player::GetSprite() const{
	return animSprite;
}

void Player::ManageCollision(CollisionInfo collision) {
	animSprite->Translate(collision.displacement);
}

void Player::Update(float deltaTime) {
	velocity = Vector2().Zero();
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity.y -= movementSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity.y += movementSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		velocity.x -= movementSpeed;
		animSprite->FlipVertical(true);
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		velocity.x += movementSpeed;
		animSprite->FlipVertical(false);
	}
	animSprite->Update(deltaTime);
	animSprite->Translate(velocity * deltaTime);
}

Player::Player() {
	animSprite = BaseGame::GetSingleton()->CreateAnimSprite("player.png", IMAGETYPE_PNG, 1, 1);
	unsigned int idle[] = {0};
	animSprite->AddAnimation("idle", idle, 1, true, 8);
	animSprite->Play("idle");
	animSprite->SetPosition(Vector2(100, 100));
}

Player::~Player() {
}
