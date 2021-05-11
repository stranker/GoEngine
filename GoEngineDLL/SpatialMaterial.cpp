#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	SetFloat("material.metallic", metallic);
	SetTextureProperty("material.diffuse", diffuseTexture.GetID(), 0);
	SetTextureProperty("material.specular", specularTexture.GetID(), 1);
	Renderer::GetSingleton()->ProcessLighting(this);
}

SpatialMaterial::SpatialMaterial(float _specular, float _metallic, const char* diffusePath, const char* specularPath) {
	LoadShaders("Shaders/SpatialMaterial_V1.vs", "Shaders/SpatialMaterial_V5.fs");
	specular = _specular;
	metallic = _metallic;
	SetDiffuseMap(diffusePath);
	SetSpecularMap(specularPath);
}

void SpatialMaterial::SetDiffuseMap(const char* filePath) {
	diffuseTexture = TextureImporter::LoadTexture(filePath);
}

void SpatialMaterial::SetSpecularMap(const char* filePath) {
	specularTexture = TextureImporter::LoadTexture(filePath);
}

void SpatialMaterial::SetTextureProperty(string const& propertyName, unsigned int id, unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, id);
}

void SpatialMaterial::ResetTextureActive() {
	glActiveTexture(GL_TEXTURE0);
}

SpatialMaterial::SpatialMaterial(float _specular, float _metallic) {
	LoadShaders("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs");
	specular = _specular;
	metallic = _metallic;
}

SpatialMaterial::SpatialMaterial() {
}

SpatialMaterial::SpatialMaterial(const char* pathVertexShader, const char* pathFragmentShader) {
	LoadShaders(pathVertexShader, pathFragmentShader);
	metallic = 0;
	specular = 0;
}

void ADSSpatialMaterial::Use() {
	Material::Use();
	SetVec3("material.ambient", ambient);
	SetVec3("material.diffuse", diffuse);
	SetVec3("material.specular", specular);
	SetFloat("material.metallic", shininess);
	Renderer::GetSingleton()->ProcessLighting(this);
}

ADSSpatialMaterial::ADSSpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess) : ADSSpatialMaterial(){
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}

ADSSpatialMaterial::ADSSpatialMaterial() {
	LoadShaders("Shaders/SpatialMaterial.vs", "Shaders/ADSSpatialMaterial.fs");
}
