#pragma once
#include "Entity.h"
#include "Material.h"
#include "Color.h"

class ENGINEDLL_API Entity2D :
	public Entity{
protected:
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
	float rotationDegrees;
public:
	void SetPosition(float x, float y);
	void Translate(float x, float y);
	void Rotate(float angle);
	void Scale(float x, float y);
	glm::vec2 GetPosition();
	float GetRotation();
	glm::vec2 GetScale();
	void CreateVertexArrayID();
	void SetPositionVertex(float *_vertex, size_t dataSize, size_t vertexCount);
	void SetIndex(unsigned int *_index, size_t indexSize);
	void SetColorVertex(float *_colorVertex, size_t dataSize);
	void Destroy() override;
	void SetModulate(Color _new_modulate);
	Entity2D(Renderer* _renderer);
	~Entity2D();
};

