#pragma once
#include "Shape.h"

class ENGINEDLL_API Triangle :
	public Shape {
public:
	void Draw() override;
	Triangle();
	virtual ~Triangle();
};
