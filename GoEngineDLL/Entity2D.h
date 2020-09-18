#pragma once
#include "Entity.h"
#include "Material.h"

class Entity2D :
	public Entity
{
protected:
	Transform *transform;
	Material *material;
	float *positionVertex;
	float *colorVertex;
	GLuint positionBuffer;
	GLuint colorBuffer;
	size_t positionVertexCount;
	size_t colorVertexCount;
public:
	string name;
	void SetPosition(float x, float y, float z);
	void SetRotation(float angle, glm::vec3 axis);
	void SetScale(float x, float y, float z);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	void SetMaterial(Material *_material);
	void UseMaterial();
	void SetPositionVertex(float *_vertex, size_t dataSize, size_t vertexCount);
	void SetColorVertex(float *_colorVertex, size_t dataSize, size_t vertexCount);
	virtual void Draw() = 0;
	void Destroy();
	Entity2D(Renderer* _renderer);
	~Entity2D();
};

