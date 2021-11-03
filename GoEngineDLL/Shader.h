#pragma once
#include "Exports.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextureImporter.h"
#include "Resource.h"

class ENGINEDLL_API Shader : public Resource {
private:
	const string spatialVertex = "Shaders/SpatialMaterial.vs";
	const string spatialFragment = "Shaders/SpatialMaterial.fs";
	unsigned int shaderID;
	string ConvertUberShader(const string& filePath, ShaderType type);
	string vertexCode;
	string fragmentCode;
public:
	void SetMat4(const string& property, glm::mat4 matrix) const;
	void SetVec2(const string& property, Vector2 vec) const;
	void SetVec3(const string& property, Vector3 vec) const;
	void SetVec4(const string& property, glm::vec4 value) const;
	void SetVec4(const string& property, Rect2 value) const;
	void SetBool(const string& property, bool value) const;
	void SetInt(const string& property, int value) const;
	void SetFloat(const string& property, float value) const;
	void SetTexture(const string& property, unsigned int textureId, unsigned int index);
	void LoadShader(const string& vertexShader, const string& fragmentShader);
	void Use();
	void Unbind();
	void Destroy();
	Shader();
	Shader(const string& vertexShader, const string& fragmentShader);
	~Shader();
};

