#include "TimeApi.h"

float Time::elapsedTime = 0;
float Time::deltaTime = 0;

void Time::AddElapsedTime(float time) {
	elapsedTime += time;
}

void Time::SetDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

float Time::ElapsedTime() {
	return elapsedTime;
}

float Time::DeltaTime() {
	return deltaTime;
}
