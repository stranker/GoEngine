#include "BaseGame.h"

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

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

		if (input->IsKeyPressed(KEY_ESCAPE)) {
			window->CloseWindow();
		}

		// Calculo deltaTime
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer->SetClearColor(Color().Purple());
		renderer->ClearScreen();

		Update(deltaTime);

		renderer->SwapBuffers();
		window->PoolEvents();
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
	input->SetWindow(window);
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

void BaseGame::UpdateAnimSprite(AnimatedSprite* _as, float _deltaTime)
{
	_as->Update(_deltaTime);
}

void BaseGame::AddAnimation(AnimatedSprite * _as, const char * animName, unsigned int * frames,
							int framesSize, bool looped, float speed)
{
	_as->AddAnimation(animName, frames, framesSize, looped, speed);
}

void BaseGame::PlayAnimation(AnimatedSprite * _as, const char * animName)
{
	_as->Play(animName);
}

void BaseGame::FlipSpriteH(Sprite * _entity, bool _flip)
{
	_entity->FlipHorizontal(_flip);
}

void BaseGame::FlipSpriteH(AnimatedSprite * _entity, bool _flip)
{
	_entity->FlipHorizontal(_flip);
}

void BaseGame::FlipSpriteV(Sprite * _entity, bool _flip)
{
	_entity->FlipVertical(_flip);
}

void BaseGame::FlipSpriteV(AnimatedSprite * _entity, bool _flip)
{
	_entity->FlipVertical(_flip);
}

Vector2 BaseGame::GetSpriteSize(Sprite * _entity)
{
	return _entity->GetSize();
}

Vector2 BaseGame::GetSpriteSize(AnimatedSprite * _entity)
{
	return _entity->GetSize();
}

void BaseGame::DrawEntities() {
	for (entityIterator = entityList->begin(); entityIterator != entityList->end(); entityIterator++) {
		Entity *entity = *entityIterator;
		entity->Draw();
	}
}

void BaseGame::SetPosition(Sprite* _entity, float _x, float _y)
{
	Vector2 pos;
	pos.x = _x;
	pos.y = _y;
	_entity->SetPosition(pos);
}

void BaseGame::SetPosition(AnimatedSprite * _entity, float _x, float _y)
{
	_entity->SetPosition(_x, _y);
}

void BaseGame::Translate(Sprite * _entity, float _x, float _y)
{
	_entity->Translate(_x, _y);
}

void BaseGame::Translate(AnimatedSprite * _entity, float _x, float _y)
{
	_entity->Translate(_x,_y);
}

void BaseGame::Rotate(Sprite * _entity, float angle)
{
	_entity->Rotate(angle);
}

void BaseGame::Rotate(AnimatedSprite * _entity, float angle)
{
	_entity->Rotate(angle);
}

void BaseGame::Scale(Sprite * _entity, float _x, float _y)
{
	_entity->Scale(_x, _y);
}

void BaseGame::Scale(AnimatedSprite * _entity, float _x, float _y)
{
	_entity->Scale(_x, _y);
}

Vector2 BaseGame::GetPosition(Sprite * _entity)
{
	return _entity->GetPosition();
}

Vector2 BaseGame::GetPosition(AnimatedSprite * _entity)
{
	return _entity->GetPosition();
}

float BaseGame::GetRotation(Sprite * _entity)
{
	return _entity->GetRotation();
}

float BaseGame::GetRotation(AnimatedSprite * _entity)
{
	return _entity->GetRotation();
}

Vector2 BaseGame::GetScale(Sprite * _entity)
{
	return _entity->GetScale();
}

Vector2 BaseGame::GetScale(AnimatedSprite * _entity)
{
	return _entity->GetScale();
}

bool BaseGame::KeyPressed(KeyCode _key)
{
	return input->IsKeyPressed(_key);
}

Vector2 BaseGame::GetWindowSize()
{
	return window->GetSize();
}

#pragma endregion
