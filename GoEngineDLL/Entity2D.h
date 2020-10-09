#pragma once
#include "Entity.h"
#include "Material.h"
#include "Color.h"

class ENGINEDLL_API Entity2D :
	public Entity{
protected:
	Transform *transform;
	Material *material;
	float *positionVertex;
	float *colorVertex;
	unsigned int *index;
	GLuint vertexArrayID;
	GLuint positionBuffer;
	GLuint indexBuffer;
	GLuint colorBuffer;
	size_t positionVertexCount;
	Renderer::Primitive primitive;
	Color selfModulate;
public:
	void SetPosition(float x, float y, float z);
	void SetRotation(float angle, glm::vec3 axis);
	void SetScale(float x, float y, float z);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	void SetMaterial(Material *_material);
	void UseMaterial();
	void CreateVertexArrayID();
	void SetPositionVertex(float *_vertex, size_t dataSize, size_t vertexCount);
	void SetIndex(unsigned int *_index, size_t indexSize);
	void SetColorVertex(float *_colorVertex, size_t dataSize);
	void Translate(float x, float y);
	virtual void Draw() = 0;
	void Destroy();
	Entity2D(Renderer* _renderer);
	~Entity2D();
};

