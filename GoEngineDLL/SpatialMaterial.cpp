#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	switch (LIGHT_SHADER_VERSION)
	{
	case 0:
		break;
	case 1:
		SetVec3("material.ambient", ambient);
		SetVec3("material.diffuse", diffuse);
		SetVec3("material.specular", specular);
		SetFloat("material.shininess", shininess);
		break;
	case 2:
		SetFloat("material.shininess", shininess);
		break;
	case 3:
		SetFloat("material.shininess", shininess);
		SetTextureProperty("material.diffuse", diffuseMap, 0);
		SetTextureProperty("material.specular", specularMap, 1);
		break;
	default:
		break;
	}
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
	switch (textureId){
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE2);
		break;
	default:
		glActiveTexture(GL_TEXTURE0);
		break;
	}
	glBindTexture(GL_TEXTURE_2D, value);
}

TextureData SpatialMaterial::GetDiffuseTexture() {
	return diffuseTexture;
}

TextureData SpatialMaterial::GetSpecularTexture() {
	return specularTexture;
}

SpatialMaterial::SpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess) {
	const char* fragment_shader = "Shaders/SpatialMaterial.vs";
	const char* vertex_shader = "Shaders/SpatialMaterial.vs";;
	switch (LIGHT_SHADER_VERSION){
		case 0:
			fragment_shader = "Shaders/SpatialMaterial_V1.fs";
			break;
		case 1:
			fragment_shader = "Shaders/SpatialMaterial_V2.fs";
			break;
		case 2:
			vertex_shader = "Shaders/SpatialMaterial_V1.vs";
			fragment_shader = "Shaders/SpatialMaterial_V3.fs";
			break;
		case 3:
			vertex_shader = "Shaders/SpatialMaterial_V1.vs";
			fragment_shader = "Shaders/SpatialMaterial_V4.fs";
			break;
		default:
			fragment_shader = "Shaders/SpatialMaterial_V1.fs";
			break;
	}
	LoadShaders(vertex_shader, fragment_shader);
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
}

SpatialMaterial::SpatialMaterial(){
	LoadShaders("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial_V1.fs");
	ambient = Vector3().One();
	diffuse = Vector3().One();
	specular = Vector3().One();
	shininess = 0.0f;
}

SpatialMaterial::~SpatialMaterial() {
	TextureImporter::FreeTexture(diffuseTexture);
	TextureImporter::FreeTexture(specularTexture);
}
