#include "Object.h"

void Object::AddSprite(Sprite * _sprite) {
	sprite = _sprite;
}

void Object::SetModulate(Color modulate) {
	sprite->SetModulate(modulate);
}

void Object::SetModulate(float r, float g, float b, float a) {
	Color new_color;
	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	new_color.a = a;
	SetModulate(new_color);
}

void Object::SetPosition(Vector2 position) {
	sprite->SetPosition(position);
}

Color Object::GetModulate() const {
	return sprite->GetModulate();
}

void Object::FlipH(bool value) {
	sprite->FlipHorizontal(value);
}

void Object::FlipV(bool value) {
	sprite->FlipVertical(value);
}

void Object::Destroy() {
	if (sprite) {
		sprite->Destroy();
		delete sprite;
	}
}

Object::Object() {

}

Object::~Object() {
}