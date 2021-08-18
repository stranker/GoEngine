#pragma once

#include "Exports.h"
#include "UILayer.h"

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
#include "Quad.h"
#include "Line3D.h"
#include "Light.h"
#include "SpatialMaterial.h"
#include "MeshInstance.h"

class ENGINEDLL_API BaseGame {
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float delta) = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Update(float delta);
	static BaseGame* singleton;
private:
	bool InitEngine();
	bool DestroyEngine();
	void LoopEngine();
	void Render();
	Window* window;
	Renderer* renderer;
	Input* input;
	Node* sceneRoot;
	double currentFrame;
	double lastFrame;
	double deltaTime;
	void ShowDebugUI();
public:
	static BaseGame* GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Camera3D* CreateCamera3D(float width, float height);
	Cube* CreateCube();
	DirectionalLight* CreateDirectional(Vector3 lightColor, float energy, float specular);
	PointLight* CreatePointLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation);
	SpotLight* CreateSpotLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation, float cutOff, float outCutOff);
	Node3D* LoadModel(string const& path);
	Node* GetRoot();
	//WINDOW
	Vector2 GetWindowSize();
#pragma endregion
};
