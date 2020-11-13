#include "Player.h"

Sprite * Player::GetSprite() const{
	return animSprite;
}

void Player::ManageCollision(CollisionInfo collision) {
	animSprite->Translate(collision.displacement);
}

void Player::ManageCollision(vector<CollisionInfo> collisions) {
	for (CollisionInfo colInfo : collisions) {
		ManageCollision(colInfo);
	}
}

void Player::Update(float deltaTime) {
	velocity = Vector2().Zero();
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity.y -= 1;
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity.y += 1;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		velocity.x -= 1;
		animSprite->FlipVertical(true);
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		velocity.x += 1;
		animSprite->FlipVertical(false);
	}
	if (Input::IsKeyPressed(Input::KEY_1)) {
		animSprite->SetPosition(initialPos);
	}
	animSprite->Update(deltaTime);
	animSprite->Translate(velocity.Normalize() * movementSpeed * deltaTime);
}

Player::Player() {
	animSprite = BaseGame::GetSingleton()->CreateAnimSprite("player.png", IMAGETYPE_PNG, 1, 1);
	unsigned int idle[] = {0};
	animSprite->AddAnimation("idle", idle, 1, true, 8);
	animSprite->Play("idle");
	animSprite->SetPosition(Vector2(100, 100));
	initialPos = animSprite->GetPosition();
}

Player::~Player() {
}
