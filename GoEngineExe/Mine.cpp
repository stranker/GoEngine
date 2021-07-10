#include "Mine.h"

Mine::Mine() {
	model = ModelImporter::LoadModel("mine/scene.gltf");
	AddChildren(model);
}
