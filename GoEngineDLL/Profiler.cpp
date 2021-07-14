#include "Profiler.h"

unsigned int Profiler::objectsDrawing = 0;
unsigned int Profiler::totalObjects = 0;
vector<string> Profiler::nodesDrawing;

void Profiler::Clear() {
	objectsDrawing = 0;
	nodesDrawing.clear();
}
