#include "Container.h"

void Container::Ready() {
}

void Container::Update(float deltaTime) {
}

Container::Container() {
	name = "Container";
	spatialMaterial->SetAlbedoMap("container.png");
	spatialMaterial->SetSpecularMap("container_specular.png");
}
