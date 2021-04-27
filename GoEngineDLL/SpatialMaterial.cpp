#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	SetFloat("material.metallic", metallic);
	SetTextureProperty("material.diffuse", diffuseMap, 0);
	SetTextureProperty("material.specular", specularMap, 1);
	Renderer::GetSingleton()->ProcessLighting(this);
}

float SpatialMaterial::GetSpecular() const {
	return specular;
}

float SpatialMaterial::GetMetallic() const {
	return metallic;
}

void SpatialMaterial::SetDiffuseMap(const char* filePath, ImageType imageType) {
	diffuseTexture = TextureImporter::LoadTexture(filePath, imageType);
	diffuseMap = Renderer::GetSingleton()->CreateTextureBuffer(diffuseTexture.GetData(), diffuseTexture.GetWidth(), diffuseTexture.Getheight(), diffuseTexture.GetNrChannels());
}

void SpatialMaterial::SetSpecularMap(const char* filePath, ImageType imageType) {
	specularTexture = TextureImporter::LoadTexture(filePath, imageType);
	specularMap = Renderer::GetSingleton()->CreateTextureBuffer(diffuseTexture.GetData(), diffuseTexture.GetWidth(), diffuseTexture.Getheight(), diffuseTexture.GetNrChannels());
}

void SpatialMaterial::SetTextureProperty(const char* property, unsigned int value, unsigned int textureId) {
	unsigned int location = glGetUniformLocation(ID, property);
	glActiveTexture(GL_TEXTURE0 + textureId);
	glBindTexture(GL_TEXTURE_2D, value);
}

TextureData SpatialMaterial::GetDiffuseTexture() {
	return diffuseTexture;
}

TextureData SpatialMaterial::GetSpecularTexture() {
	return specularTexture;
}

SpatialMaterial::SpatialMaterial(float _specular, float _metallic) {
	LoadShaders("Shaders/SpatialMaterial_V1.vs", "Shaders/SpatialMaterial_V5.fs");
	specular = _specular;
	metallic = _metallic;
}

SpatialMaterial::SpatialMaterial() {
}

SpatialMaterial::~SpatialMaterial() {
	TextureImporter::FreeTexture(diffuseTexture);
	TextureImporter::FreeTexture(specularTexture);
}
