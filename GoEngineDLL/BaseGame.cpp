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
	sceneRoot = new Node("SceneRoot");
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
		Time::SetDeltaTime(deltaTime);
		Time::AddElapsedTime(deltaTime);
		lastFrame = currentFrame;

		renderer->BeginRender();

		UILayer::NewFrame();

		Update(deltaTime);

		Render();

		UILayer::Render();

		renderer->EndRender();

		window->PoolEvents();
		Profiler::Clear();
	}
	return OnStop();
}

void BaseGame::Render() {
	Get3DCamera();
	if (BSP::HasPartitionPlanes()) {
		BSP::DrawBSPTree(sceneRoot, cam3D->GetGlobalTransform()->GetPosition());
	}
	sceneRoot->Draw();
	UILayer::ShowDebug();
}

void BaseGame::Get3DCamera() {
	if (!cam3D) {
		cam3D = (Camera3D*)renderer->GetCamera();
	}
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
