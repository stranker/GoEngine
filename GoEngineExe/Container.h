#pragma once
#include <Cube.h>
class Container :
    public Cube {
private:
public:
	void Ready();
	void Update(float deltaTime);
	Container();
};

