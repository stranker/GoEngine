#include "Color.h"

Color::Color() {
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
}

Color::Color(float _r, float _g, float _b, float _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

Color::Color(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
	a = 1.0f;
}

Color::Color(Vector3 vec) {
	r = vec.x;
	g = vec.y;
	b = vec.z;
	a = 1.0f;
}

Color Color::Red() const {
	return Color(1, 0, 0);
}

Color Color::Green() const {
	return Color(0, 1, 0);
}

Color Color::Blue() const {
	return Color(0, 0, 1);
}

Color Color::Yellow() const {
	return Color(1, 1, 0);
}

Color Color::Black() const {
	return Color(0, 0, 0);
}

Color Color::White() const {
	return Color(1, 1 ,1);
}

Color Color::Cyan() const {
	return Color(0, 1, 1);
}

Color Color::Magenta() const {
	return Color(1, 0, 1);
}

Color Color::Purple() const {
	return Color(0.4, 0, 0.4);
}

Color Color::Interpolate(const Color & color2, float weight) {
	Color newColor = Color(r,g,b,a);
	newColor.r += (weight * (color2.r - r));
	newColor.g += (weight * (color2.g - g));
	newColor.b += (weight * (color2.b - b));
	newColor.a += (weight * (color2.a - a));
	return newColor;
}
