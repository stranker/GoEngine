#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "GlInclude.h"

void BaseGame::OnStart() {
	sceneRoot->Ready();
	LoopEngine();
}

void BaseGame::OnStop() {
	sceneRoot->Destroy();
	DestroyEngine();
}

void BaseGame::Update(float deltaTime) {
	ShowDebugUI();
	sceneRoot->Update(deltaTime);
	return OnUpdate(deltaTime);
}

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	input->SetCurrentWindow(window);
	currentFrame = glfwGetTime();
	lastFrame = currentFrame;
	sceneRoot = new Node("sceneRoot");
	return true;
}

bool BaseGame::DestroyEngine() {
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
	ResourceManager::Clear();
	NodeManager::Clear();
	UILayer::Destroy();
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

		UILayer::NewFrame();

		Update(deltaTime);

		Render();

		UILayer::Render();

		renderer->DisableClientState();
		renderer->SwapBuffers();
		window->PoolEvents();
		Profiler::Clear();
	}
	return OnStop();
}

void BaseGame::Render() {
	sceneRoot->Draw();
	UILayer::ShowDebug();
}

void BaseGame::ShowDebugUI() {
	UILayer::Begin("Node Hierarchy", 0, 4);
	UILayer::TreeNode(sceneRoot);
	UILayer::End();
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
	if (!InitEngine()){
		DestroyEngine();
	}
}

BaseGame::~BaseGame() {
	singleton = NULL;
}

#pragma region UserMethods

Camera3D* BaseGame::CreateCamera3D(float width, float height) {
	Camera3D* camera = new Camera3D(width, height);
	renderer->SetCurrentCamera(camera);
	sceneRoot->AddChildren(camera);
	return camera;
}

Cube* BaseGame::CreateCube() {
	Cube* c = new Cube();
	sceneRoot->AddChildren(c);
	return c;
}

DirectionalLight* BaseGame::CreateDirectional(Vector3 lightColor, float energy, float specular) {
	DirectionalLight* dl = new DirectionalLight(lightColor, energy, specular);
	Renderer::GetSingleton()->AddLight(dl);
	sceneRoot->AddChildren(dl);
	return dl;
}

PointLight* BaseGame::CreatePointLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation) {
	PointLight* pl = new PointLight(lightColor, energy, specular, range, attenuation);
	Renderer::GetSingleton()->AddLight(pl);
	sceneRoot->AddChildren(pl);
	return pl;
}

SpotLight* BaseGame::CreateSpotLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation, float cutOff, float outCutOff) {
	SpotLight* sl = new SpotLight(lightColor, energy, specular, range, attenuation, cutOff, outCutOff);
	Renderer::GetSingleton()->AddLight(sl);
	sceneRoot->AddChildren(sl);
	return sl;
}

Node3D* BaseGame::LoadModel(string const& path) {
	Node3D* modelRootNode = ModelImporter::LoadModel(path);
	return modelRootNode;
}

Node* BaseGame::GetRoot() {
	return sceneRoot;
}

Vector2 BaseGame::GetWindowSize(){
	return window->GetSize();
}

#pragma endregion
