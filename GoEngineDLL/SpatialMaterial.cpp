#include "SpatialMaterial.h"

void SpatialMaterial::Use() {
	Material::Use();
	SetVec3("material.ambient", ambient);
	SetVec3("material.diffuse", diffuse);
	SetVec3("material.specular", specular);
	SetFloat("material.shininess", shininess);
}

Vector3 SpatialMaterial::GetAmbient() const {
	return ambient;
}

Vector3 SpatialMaterial::GetDiffuse() const {
	return diffuse;
}

Vector3 SpatialMaterial::GetSpecular() const {
	return specular;
}

float SpatialMaterial::GetShininess() const {
	return shininess;
}

SpatialMaterial::SpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess) {
	LoadShaders("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs");
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}

SpatialMaterial::SpatialMaterial(){
	LoadShaders("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs");
	ambient = Vector3().One();
	diffuse = Vector3().One();
	specular = Vector3().One();
	shininess = 0.0f;
}

SpatialMaterial::~SpatialMaterial() {
}
