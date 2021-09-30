#pragma once
#include <Quad.h>

class Card3D :
    public Quad {
private:
	vector<Resource*> resources;
	Texture* main;
	Texture* noise;
	Texture* foil;
	Texture* mask;
public:
	void Ready();
	void Update(float deltaTime);
	Card3D();
};

