#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	if (defaultCube) {
		SetFloat("material.metallic", metallic);
		SetTextureProperty("material.diffuse", diffuseTexture.GetID(), 0);
		SetTextureProperty("material.specular", specularTexture.GetID(), 1);
	}
	Renderer::GetSingleton()->ProcessLighting(this);
}

void SpatialMaterial::Destroy() {
	Material::Destroy();
}

float SpatialMaterial::GetSpecular() const {
	return specular;
}

float SpatialMaterial::GetMetallic() const {
	return metallic;
}

void SpatialMaterial::SetDiffuseMap(const char* filePath) {
	diffuseTexture = TextureImporter::LoadTexture(filePath);
}

void SpatialMaterial::SetSpecularMap(const char* filePath) {
	specularTexture = TextureImporter::LoadTexture(filePath);
}

void SpatialMaterial::SetTextureProperty(string const& propertyName, unsigned int id, unsigned int index) {
	glActiveTexture(GL_TEXTURE0 + index);
	//unsigned int location = glGetUniformLocation(ID, propertyName.c_str());
	//glUniform1i(location, id);
	glBindTexture(GL_TEXTURE_2D, id);
}

void SpatialMaterial::ResetTextureActive() {
	glActiveTexture(GL_TEXTURE0);
}

TextureData SpatialMaterial::GetDiffuseTexture() {
	return diffuseTexture;
}

TextureData SpatialMaterial::GetSpecularTexture() {
	return specularTexture;
}

void SpatialMaterial::CubeMaterial(float _specular, float _metallic, const char* diffusePath, const char* specularPath) {
	LoadShaders("Shaders/SpatialMaterial_V1.vs", "Shaders/SpatialMaterial_V5.fs");
	specular = _specular;
	metallic = _metallic;
	SetDiffuseMap(diffusePath);
	SetSpecularMap(specularPath);
	defaultCube = true;
}

SpatialMaterial::SpatialMaterial(float _specular, float _metallic) {
	LoadShaders("Shaders/SpatialMaterial_V1.vs", "Shaders/SpatialMaterial_V5.fs");
	specular = _specular;
	metallic = _metallic;
}

SpatialMaterial::SpatialMaterial() {
}

SpatialMaterial::~SpatialMaterial() {
}
