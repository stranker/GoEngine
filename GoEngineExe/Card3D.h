#pragma once
#include <Quad.h>

class Card3D :
    public Quad {
private:
	Texture* main;
	Texture* noise;
	Texture* foil;
	Texture* mask;
	Texture* normal;
public:
	void Ready();
	void Update(float deltaTime);
	Card3D();
};

