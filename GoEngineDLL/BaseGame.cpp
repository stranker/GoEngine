#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "GlInclude.h"

void BaseGame::Test(){
	printf("Banana");
}

bool BaseGame::InitEngine() {
	window->Init();
	renderer->Init();
	entityList = new list<Entity*>();

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

		renderer->SetClearColor(Color().Magenta());
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
	input = new Input(window);
	singleton = this;
}

BaseGame::~BaseGame() {
	singleton = NULL;
}

#pragma region UserMethods

Sprite* BaseGame::CreateSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames) {
	Sprite *sprite = new Sprite(renderer);
	sprite->SetTexture(filePath, imageType, vFrames, hFrames);
	entityList->push_back(sprite);
	return sprite;
}

AnimatedSprite * BaseGame::CreateAnimSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames) {
	AnimatedSprite *animSprite = new AnimatedSprite(renderer);
	animSprite->SetTexture(filePath, imageType, vFrames, hFrames);
	entityList->push_back(animSprite);
	return animSprite;
}

ParticleSystem * BaseGame::CreateParticleSystem(const char * filePath, ImageType imageType, size_t particleCount) {
	ParticleSystem *ps = new ParticleSystem(renderer);
	ps->SetTexture(filePath, imageType);
	ps->SetParticleCount(particleCount);
	entityList->push_back(ps);
	return ps;
}

Camera3D* BaseGame::CreateCamera3D(float width, float height) {
	Camera3D* camera = new Camera3D(width, height);
	renderer->SetCurrentCamera(camera);
	return camera;
}

Cube* BaseGame::CreateCube() {
	Cube* c = new Cube(renderer);
	entityList->push_back(c);
	return c;
}

Gizmo* BaseGame::CreateGizmo() {
	Gizmo* gizmo = new Gizmo(renderer);
	entityList->push_back(gizmo);
	return gizmo;
}

Line3D* BaseGame::CreateLine3D(Vector3 startPoint, Vector3 endPoint, Color lineColor) {
	Line3D* line = new Line3D(renderer);
	line->CreateLine(startPoint, endPoint, lineColor);
	entityList->push_back(line);
	return line;
}

Tilemap * BaseGame::CreateTilemap(const char * filePath) {
	Tilemap *tilemap = new Tilemap(renderer);
	tilemap->LoadFromFile(filePath);
	entityList->push_back(tilemap);
	return tilemap;
}

Vector2 BaseGame::GetWindowSize(){
	return window->GetSize();
}

#pragma endregion
