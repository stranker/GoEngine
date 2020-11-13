#pragma once
#include "BaseGame.h"
class Enemy {
protected:
	AnimatedSprite* animSprite;
public:
	Sprite *GetSprite() const;
	void SetPosition(Vector2 pos);
	virtual void Update(float deltaTime);
	Enemy();
	virtual ~Enemy();
};

