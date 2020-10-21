#pragma once
#include <Object.h>
class Dragon :
	public Object {
public:
	void Update(float deltaTime) override;
	Dragon();
	~Dragon();
};

