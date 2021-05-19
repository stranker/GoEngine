#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	SetFloat("material.metallic", metallic);
	SetTexture("material.diffuse", diffuseTexture.GetTextureID(), 0);
	SetTexture("material.specular", specularTexture.GetTextureID(), 1);
	Renderer::GetSingleton()->ProcessLighting(this);
}

void SpatialMaterial::SetDiffuseMap(const char* filePath) {
	diffuseTexture = ResourceManager::LoadTexture(filePath, filePath);
}

void SpatialMaterial::SetSpecularMap(const char* filePath) {
	specularTexture = ResourceManager::LoadTexture(filePath, filePath);
}

void SpatialMaterial::ResetTextureActive() {
	glActiveTexture(GL_TEXTURE0);
}

void SpatialMaterial::CreateMaterial(float _specular, float _metallic, string const& diffusePath, string const& specularPath) {
	specular = _specular;
	metallic = _metallic;
	SetDiffuseMap(diffusePath.c_str());
	SetSpecularMap(specularPath.c_str());
}

void ADSSpatialMaterial::Use() {
	Material::Use();
	SetVec3("material.ambient", ambient);
	SetVec3("material.diffuse", diffuse);
	SetVec3("material.specular", specular);
	SetFloat("material.metallic", shininess);
	Renderer::GetSingleton()->ProcessLighting(this);
}

ADSSpatialMaterial::ADSSpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess){
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}