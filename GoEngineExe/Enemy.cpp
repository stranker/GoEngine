#include "Enemy.h"

Sprite * Enemy::GetSprite() const {
	return animSprite;
}

void Enemy::SetPosition(Vector2 pos) {
	animSprite->SetPosition(pos);
}

void Enemy::Update(float deltaTime) {
	animSprite->Update(deltaTime);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
	if (animSprite) {
		animSprite->Destroy();
		delete animSprite;
	}
}
