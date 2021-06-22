#include "Mine.h"

Mine::Mine() {
	Node3D* model = ModelImporter::LoadModel("mine/scene.gltf");
	AddChildren(model);
}
