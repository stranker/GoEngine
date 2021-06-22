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
#include "Line3D.h"
#include "Light.h"
#include "SpatialMaterial.h"
#include "MeshInstance.h"

class ENGINEDLL_API BaseGame {
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Update(float deltaTime);
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
public:
	static BaseGame* GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Camera3D* CreateCamera3D(float width, float height);
	Cube* CreateCube();
	DirectionalLight* CreateDirectional(Vector3 lightColor, float energy, float specular, Vector3 direction);
	PointLight* CreatePointLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation);
	SpotLight* CreateSpotLight(Vector3 lightColor, float energy, float specular, float range, Vector3 direction, Vector3 attenuation, float cutOff, float outCutOff);
	Node3D* LoadModel(string const& path);
	Node* GetRoot();
	//WINDOW
	Vector2 GetWindowSize();
#pragma endregion

#pragma region Imgui
	static void IGBegin(const string& panelName, size_t flag);
	static void IGBeginChild(const string& id, Vector2 size, bool border);
	static void IGEndChild();
	static void IGSameLine();
	static void IGSeparator();
	static bool IGTreeNode(const string& name);
	static void IGTreePop();
	static bool IGSelectable(const string& id, bool isSelected);
	static void IGSliderFloat(const string& property, float* v, float vmin, float vmax);
	static void IGSliderFloat3(const string& property, float v[3], float vmin, float vmax);
	static void IGInputFloat3(const string& property, float v[3]);
	static void IGEnd();
	static void IGText(const char* text);
#pragma endregion

};
