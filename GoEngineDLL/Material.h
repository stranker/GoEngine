#pragma once

#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Material
{
private:
	GLuint ID;
public:
	void Use();
	void Destroy();
	void LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
	Material();
	virtual ~Material();
};

