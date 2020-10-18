#pragma once
#include "Shape.h"

class ENGINEDLL_API Triangle :
	public Shape {
public:
	void Draw() override;
	void Update(float deltaTime) override;
	void Destroy() override;
	Triangle(Renderer* _renderer);
	virtual ~Triangle();
};
