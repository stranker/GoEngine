#pragma once
#include "Exports.h"

#define PI 3.14159265

enum ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

enum UniformType {
	INT,
	FLOAT,
	BOOL,
	VECTOR2,
	VECTOR3,
	VECTOR4,
	MAT4,
	TEXTURE,
};