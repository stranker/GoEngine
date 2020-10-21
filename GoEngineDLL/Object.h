#pragma once
#include "Sprite.h"
#include "Window.h"

class ENGINEDLL_API Object {
protected:
	Sprite *sprite;
public:
	void AddSprite(Sprite *sprite);
	void SetModulate(Color modulate);
	void SetModulate(float r, float g, float b, float a);
	Color GetModulate() const;
	void FlipH(bool value);
	void FlipV(bool value);
	virtual void Update(float deltaTime) = 0;
	void Destroy();
	Object();
	~Object();
};

