#pragma once
#include "Utils.h"

struct ENGINEDLL_API Profiler {
	static unsigned int objectsDrawing;
	static unsigned int totalObjects;
	static vector<string> nodesDrawing;
	static void Clear();
};

