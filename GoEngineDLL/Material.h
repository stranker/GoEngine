#pragma once

#include "Exports.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextureImporter.h"
#include "Resource.h"

class ENGINEDLL_API Material : public Resource
{
protected:
	unsigned int shaderID = 0;
public:
	void SetMat4(string const& property, glm::mat4 matrix) const;
	void SetVec2(string const& property, Vector2 vec) const;
	void SetVec3(string const& property, Vector3 vec) const;
	void SetVec4(string const& property, glm::vec4 value) const;
	void SetVec4(string const& property, Rect2 value) const;
	void SetBool(string const& property, bool value) const;
	void SetInt(string const& property, int value) const;
	void SetFloat(string const& property, float value) const;
	void SetTexture(string const& property, unsigned int textureId, unsigned int index);
	virtual void Use();
	unsigned int GetID();
	virtual void Destroy() {};
	void LoadShaders(string const& vertex_file_path, string const& fragment_file_path);
	void ResetTextureActive();
	Material();
};
