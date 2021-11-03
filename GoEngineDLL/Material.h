#pragma once

#include "Exports.h"
#include "Utils.h"
#include "Shader.h"
#include "ResourceManager.h"

class ENGINEDLL_API Material : public Resource
{
public:
	Material* nextPass;
protected:
	map<string, Texture*> textures;
	map<string, Vector3> floatValues;
	map<string, Rect2> rect4Values;
	map<string, Vector3> vec3Values;
	map<string, Vector2> vec2Values;
	map<string, glm::mat4> mat4Values;
	map<string, bool> booleanValues;
	Shader* shader;
public:
	Material* GetNextPass() const;
	virtual void Use();
	void AddTexture(const string& name, Texture* texture);
	void AddFloat(const string& name, float value, float min, float max);
	void AddVec3(const string& name, Vector3 value);
	void AddVec2(const string& name, Vector2 value);
	void AddMat4(const string& name, glm::mat4 value);
	void AddVec4(const string& name, Rect2 value);
	void AddBool(const string& name, bool value);
	Shader* GetShader();
	map<string, Texture*> GetTextures() { return textures; };
	map<string, Vector3> GetFloats() { return floatValues; };
	Material();
	Material(const string& vertexShader, const string& fragmentShader, const string& _name);
};
