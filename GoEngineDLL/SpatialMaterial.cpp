#include "SpatialMaterial.h"
#include "GlInclude.h"
#include "Renderer.h"

void SpatialMaterial::Use() {
	Material::Use();
	if (shader) {
		shader->SetVec3("viewPos", Renderer::GetSingleton()->GetCameraTransform()->GetPosition());
		shader->SetVec2("screenSize", Renderer::GetSingleton()->GetWindowSize());
		shader->SetFloat("material.metallic", metallic);
		if (albedoTexture) {
			shader->SetTexture("material.albedo_texture", albedoTexture->GetTextureID(), textures.size());
		}
		if (specularTexture) {
			shader->SetTexture("material.specular_texture", specularTexture->GetTextureID(), textures.size() + 1);
		}
		shader->SetBool("material.unshaded", unshaded);
		Renderer::GetSingleton()->ProcessLighting(GetShader());
	}
}

void SpatialMaterial::SetAlbedoMap(const string& filePath) {
	albedoTexture = ResourceManager::LoadTexture(filePath, filePath);
}

void SpatialMaterial::SetSpecularMap(const string& filePath) {
	specularTexture = ResourceManager::LoadTexture(filePath, filePath);
}

void SpatialMaterial::SetUnshaded(bool value) {
	unshaded = value;
}

bool SpatialMaterial::IsUnshaded() const {
	return unshaded;
}

void SpatialMaterial::SetAlbedo(Color color) {
	albedo = color;
}

void SpatialMaterial::SetSpecular(float _specular) {
	specular = _specular;
}

SpatialMaterial::SpatialMaterial(string const& vertexShader, string const& fragmentShader, const string& name)
	: Material(vertexShader, fragmentShader, name) {
	SetAlbedoMap("white_texture.png");
	SetSpecularMap("white_texture.png");
	specular = 0.5f;
	metallic = 0.1f;
}

void ADSSpatialMaterial::Use() {
	Material::Use();
	if (shader) {
		shader->SetVec3("material.ambient", ambient);
	}
	
	//SetVec3("material.diffuse", diffuse);
	//SetVec3("material.specular", specular);
	//SetFloat("material.metallic", shininess);
	//if (diffuseTexture->IsValid()){
	//	SetBool("material.hasTexture", true);
	//	SetTexture("material." + name, diffuseTexture->GetTextureID(), 0);
	//}
	//Renderer::GetSingleton()->ProcessLighting(this);
}

ADSSpatialMaterial::ADSSpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular) {
}

ADSSpatialMaterial::ADSSpatialMaterial(string const& albedoPath, string const& specularPath) {
}

ADSSpatialMaterial::ADSSpatialMaterial() {
}
