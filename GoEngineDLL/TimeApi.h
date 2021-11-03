#pragma once
#include "Utils.h"

class ENGINEDLL_API Time {
private:
	static float elapsedTime;
	static float deltaTime;
public:
	static void AddElapsedTime(float time);
	static void SetDeltaTime(float deltaTime);
	static float ElapsedTime();
	static float DeltaTime();
};

