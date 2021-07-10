#pragma once
#include "Exports.h"

struct ENGINEDLL_API Profiler {
	static unsigned int objectsDrawing;
	static unsigned int totalObjects;
	static void Clear();
};

