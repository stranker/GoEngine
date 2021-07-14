#include "Rect2.h"

Rect2::Rect2(float _x, float _y, float w, float h) {
	x = _x;
	y = _y;
	width = w;
	height = h;
}

Rect2::Rect2(Vector2 pos, Vector2 size) {
	x = pos.x;
	y = pos.y;
	width = size.x;
	height = size.y;
}

float Rect2::Dot(const Rect2& rec) const{
	return x * rec.x + y * rec.y + width * rec.width + height * rec.height;
}
