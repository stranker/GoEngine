#pragma once

#include "Exports.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TextureImporter.h"

class ENGINEDLL_API Material
{
protected:
	unsigned int ID;
public:
	void SetMat4(const char* property, glm::mat4 matrix) const;
	void SetVec2(const char* property, Vector2 vec) const;
	void SetVec3(const char* property, Vector3 vec) const;
	void SetVec4(const char* property, glm::vec4 value) const;
	void SetVec4(const char* property, Rect2 value) const;
	void SetBool(const char* property, bool value) const;
	void SetInt(const char* property, int value) const;
	void SetFloat(const char* property, float value) const;
	void Use();
	void Destroy();
	void LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
	Material();
	virtual ~Material();
};

