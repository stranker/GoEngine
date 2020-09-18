#pragma once

#include "Exports.h"
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ENGINEDLL_API Material
{
private:
	GLuint ID;
public:
	void SetMatrixProperty(const char* property, glm::mat4 matrix);
	void Use();
	void Destroy();
	void LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
	Material();
	virtual ~Material();
};

