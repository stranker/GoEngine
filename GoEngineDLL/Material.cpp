#include "Material.h"
#include "Renderer.h"

Material* Material::GetNextPass() const {
	return nextPass;
}

void Material::Use(){
	if (shader) {
		shader->Use();
		shader->SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
		shader->SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
		shader->SetFloat("time", Time::ElapsedTime());
		if (!textures.empty()) {
			map<string, Texture*>::iterator it;
			int cont = 0;
			for (it = textures.begin(); it != textures.end(); it++) {
				shader->SetTexture(it->first, it->second->GetTextureID(), cont);
				cont++;
			}
		}
		if (!floatValues.empty()) {
			map<string, Vector3>::iterator it;
			for (it = floatValues.begin(); it != floatValues.end(); it++) {
				shader->SetFloat(it->first, it->second.x);
			}
		}
		if (!vec3Values.empty()) {
			map<string, Vector3>::iterator it;
			for (it = vec3Values.begin(); it != vec3Values.end(); it++) {
				shader->SetVec3(it->first, it->second);
			}
		}
		if (!vec2Values.empty()) {
			map<string, Vector2>::iterator it;
			for (it = vec2Values.begin(); it != vec2Values.end(); it++) {
				shader->SetVec2(it->first, it->second);
			}
		}
		if (!mat4Values.empty()) {
			map<string, glm::mat4>::iterator it;
			for (it = mat4Values.begin(); it != mat4Values.end(); it++) {
				shader->SetMat4(it->first, it->second);
			}
		}
		if (!rect4Values.empty()) {
			map<string, Rect2>::iterator it;
			for (it = rect4Values.begin(); it != rect4Values.end(); it++) {
				shader->SetVec4(it->first, it->second);
			}
		}
		if (!booleanValues.empty()) {
			map<string, bool>::iterator it;
			for (it = booleanValues.begin(); it != booleanValues.end(); it++) {
				shader->SetBool(it->first, it->second);
			}
		}
	}
}


void Material::AddTexture(const string& name, Texture* texture) {
	textures[name] = texture;
}

void Material::AddFloat(const string& name, float value, float min, float max) {
	floatValues[name] = Vector3(value, min, max);
}

void Material::AddVec3(const string& name, Vector3 value) {
	vec3Values[name] = value;
}

void Material::AddVec2(const string& name, Vector2 value) {
	vec2Values[name] = value;
}

void Material::AddMat4(const string& name, glm::mat4 value) {
	mat4Values[name] = value;
}

void Material::AddVec4(const string& name, Rect2 value) {
	rect4Values[name] = value;
}

void Material::AddBool(const string& name, bool value) {
	booleanValues[name] = value;
}

Shader* Material::GetShader() {
	return shader;
}

Material::Material() {
	shader = nullptr;
	nextPass = nullptr;
	SetDefaultName("Material");
}

Material::Material(const string& vertexShader, const string& fragmentShader, const string& _name) : Material() {
	shader = ResourceManager::LoadShader(vertexShader, fragmentShader, _name);
}
