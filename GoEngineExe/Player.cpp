#include "Player.h"

void Player::AddSprite(Sprite * _sprite) {
	sprite = _sprite;
}

void Player::SetModulate(Color modulate) {
	sprite->SetModulate(modulate);
}

void Player::SetModulate(float r, float g, float b, float a) {
	Color new_color;
	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	new_color.a = a;
	SetModulate(new_color);
}

void Player::FlipH(bool value) {
	sprite->FlipHorizontal(value);
}

void Player::FlipV(bool value) {
	sprite->FlipVertical(value);
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
		FlipV(false);
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		velocity.x += movementSpeed;
		FlipV(true);
	}
	sprite->Translate(velocity * deltaTime);
}

void Player::Destroy() {
	if (sprite) {
		sprite->Destroy();
		delete sprite;
	}
}

Player::Player() {

}

Player::~Player() {
}
