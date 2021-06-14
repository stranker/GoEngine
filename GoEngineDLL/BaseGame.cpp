#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "GlInclude.h"

void BaseGame::OnStart() {
	rootNode->Ready();
	LoopEngine();
}

void BaseGame::OnStop() {
	rootNode->Destroy();
	DestroyEngine();
}

void BaseGame::Update(float deltaTime) {
	rootNode->Update(deltaTime);
}

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	input->SetCurrentWindow(window);
	currentFrame = glfwGetTime();
	lastFrame = currentFrame;
	rootNode = new Node3D("rootNode");
	return true;
}

bool BaseGame::DestroyEngine() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Update(deltaTime);

		Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		renderer->DisableClientState();
		renderer->SwapBuffers();
		window->PoolEvents();
	}
}

void BaseGame::Render() {
	rootNode->Draw();
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
	DestroyEngine();
}

#pragma region UserMethods

Camera3D* BaseGame::CreateCamera3D(float width, float height) {
	Camera3D* camera = new Camera3D(width, height);
	renderer->SetCurrentCamera(camera);
	rootNode->AddChildren(camera);
	return camera;
}

Cube* BaseGame::CreateCube() {
	Cube* c = new Cube();
	rootNode->AddChildren(c);
	return c;
}

DirectionalLight* BaseGame::CreateDirectional(Vector3 lightColor, float energy, float specular, Vector3 direction) {
	DirectionalLight* dl = new DirectionalLight(lightColor, energy, specular, direction);
	Renderer::GetSingleton()->AddLight(dl);
	return dl;
}

PointLight* BaseGame::CreatePointLight(Vector3 lightColor, float energy, float specular, float range, Vector3 attenuation) {
	PointLight* pl = new PointLight(lightColor, energy, specular, range, attenuation);
	Renderer::GetSingleton()->AddLight(pl);
	return pl;
}

SpotLight* BaseGame::CreateSpotLight(Vector3 lightColor, float energy, float specular, float range, Vector3 direction, Vector3 attenuation, float cutOff, float outCutOff) {
	SpotLight* sl = new SpotLight(lightColor, energy, specular, range, direction, attenuation, cutOff, outCutOff);
	Renderer::GetSingleton()->AddLight(sl);
	return sl;
}

Node3D* BaseGame::LoadModel(string const& path) {
	Node3D* modelRootNode = ModelImporter::LoadModel(path);
	return modelRootNode;
}

Node3D* BaseGame::GetRoot() {
	return rootNode;
}

Vector2 BaseGame::GetWindowSize(){
	return window->GetSize();
}

void BaseGame::IGBegin(const char* panelName) {
	ImGui::Begin(panelName);
}

void BaseGame::IGSliderFloat(const char* property, float* v, float vmin, float vmax) {
	ImGui::SliderFloat(property, v, vmin, vmax);
}

void BaseGame::IGSliderFloat3(const char* property, float v[3], float vmin, float vmax) {
	ImGui::SliderFloat3(property, v, vmin, vmax);
}

void BaseGame::IGInputFloat3(const char* property, float v[3]) {
	ImGui::InputFloat3(property, v);
}

void BaseGame::IGEnd() {
	ImGui::End();
}

void BaseGame::IGText(const char* text) {
	ImGui::Text(text);
}

#pragma endregion
