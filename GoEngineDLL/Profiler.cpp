#include "Profiler.h"

unsigned int Profiler::objectsDrawing = 0;
unsigned int Profiler::totalObjects = 0;

void Profiler::Clear() {
	objectsDrawing = 0;
}
