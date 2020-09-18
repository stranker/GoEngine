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

Color Color::Blue() {
	return Color(0,0,1);
}

Color Color::Red() {
	return Color(1, 0, 0);
}

Color Color::Green() {
	return Color(0, 1, 0);
}

Color Color::Yellow() {
	return Color(1, 1, 0);
}

Color Color::Black() {
	return Color(1, 1, 1);
}

Color Color::Cyan() {
	return Color(0, 1, 1);
}

Color Color::Magenta() {
	return Color(1, 0, 1);
}

Color Color::Purple() {
	return Color(0.4,0,0.4);
}


Color::~Color() {
}
