#pragma once

#include "Exports.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <iterator>

class Window;
class Renderer;

#include "Utils.h"
#include "Input.h"
#include "Tilemap.h"
#include "AnimatedSprite.h"
#include "ParticleSystem.h"
#include "CollisionManager.h"
#include "Camera3D.h"
#include "Cube.h"
#include "Line3D.h"
#include "Gizmo.h"
#include "Light.h"
#include "SpatialMaterial.h"

class ENGINEDLL_API BaseGame {
protected:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Stop() = 0;
	bool InitEngine();
	bool DestroyEngine();
	void LoopEngine();
	void DrawEntities();
	static BaseGame* singleton;
private:
	Window* window;
	Renderer* renderer;
	Input* input;
	list<Entity*>* entityList;
	list<Entity*>::iterator entityIterator;
	double currentFrame;
	double lastFrame;
	double deltaTime;
public:
	static BaseGame* GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Camera3D* CreateCamera3D(float width, float height);
	Cube* CreateCube();
	Gizmo* CreateGizmo();
	Line3D* CreateLine3D(Vector3 startPoint, Vector3 endPoint, Color lineColor);
	Light* CreateLight(Vector3 lightColor, Vector3 ambient, Vector3 diffuse, Vector3 specular);
	Light* CreateLight(Vector3 lightColor);
	//WINDOW
	Vector2 GetWindowSize();

#pragma endregion
};
