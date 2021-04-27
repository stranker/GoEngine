#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "GlInclude.h"

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	entityList = new list<Entity*>();
	input->SetCurrentWindow(window);
	currentFrame = glfwGetTime();
	lastFrame = currentFrame;
	return true;
}

bool BaseGame::DestroyEngine() {
	delete entityList;
	if (renderer) {
		renderer->Destroy();
		delete renderer;
	}
	if (input) {
		delete input;
	}
	if (window) {
		window->Destroy();
		delete window;
	}
	return true;
}

void BaseGame::LoopEngine() {
	while (!window->ShouldClose()) {

		if (Input::IsKeyPressed(Input::KEY_ESCAPE)) {
			window->CloseWindow();
		}

		// Calculo deltaTime
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer->SetClearColor(Color(0.1,0.1,0.1,1));
		renderer->ClearScreen();
		renderer->EnableClientState();

		Update(deltaTime);

		DrawEntities();

		renderer->DisableClientState();
		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

void BaseGame::DrawEntities() {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Draw();
	}
}

BaseGame * BaseGame::GetSingleton(){
	return singleton;
}

BaseGame* BaseGame::singleton = nullptr;

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title) {
	window = new Window(_screen_width, _screen_height, _screen_title);
	renderer = new Renderer(window);
	input = new Input();
	singleton = this;
}

BaseGame::~BaseGame() {
	singleton = NULL;
}

#pragma region UserMethods

Camera3D* BaseGame::CreateCamera3D(float width, float height) {
	Camera3D* camera = new Camera3D(width, height);
	renderer->SetCurrentCamera(camera);
	return camera;
}

Cube* BaseGame::CreateCube() {
	Cube* c = new Cube();
	entityList->push_back(c);
	return c;
}

Gizmo* BaseGame::CreateGizmo() {
	Gizmo* gizmo = new Gizmo();
	entityList->push_back(gizmo);
	return gizmo;
}

Line3D* BaseGame::CreateLine3D(Vector3 startPoint, Vector3 endPoint, Color lineColor) {
	Line3D* line = new Line3D();
	line->CreateLine(startPoint, endPoint, lineColor);
	entityList->push_back(line);
	return line;
}

DirectionalLight* BaseGame::CreateDirectional(Vector3 lightColor, float energy, float specular, Vector3 direction) {
	DirectionalLight* dl = new DirectionalLight(lightColor, energy, specular, direction);
	Renderer::GetSingleton()->AddLight(dl);
	entityList->push_back(dl);
	return dl;
}

PointLight* BaseGame::CreatePointLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation) {
	PointLight* pl = new PointLight(lightColor, energy, specular, range, attenuation);
	Renderer::GetSingleton()->AddLight(pl);
	entityList->push_back(pl);
	return pl;
}

SpotLight* BaseGame::CreateSpotLight(Vector3 lightColor, float energy, float specular, float range, Vector3 direction, Vector3 attenuation, float cutOff, float outCutOff) {
	SpotLight* sl = new SpotLight(lightColor, energy, specular, range, direction, attenuation, cutOff, outCutOff);
	Renderer::GetSingleton()->AddLight(sl);
	entityList->push_back(sl);
	return sl;
}

Vector2 BaseGame::GetWindowSize(){
	return window->GetSize();
}

#pragma endregion
