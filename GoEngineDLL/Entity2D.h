#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Entity2D :
	public Entity{
protected:
	float *positionVertex;
	float *colorVertex;
	unsigned int *index;
	unsigned int vertexArrayID;
	unsigned int positionBuffer;
	unsigned int indexBuffer;
	unsigned int colorBuffer;
	size_t positionVertexCount;
	Renderer::Primitive primitive;
	Color selfModulate;
	float rotationDegrees;
	void CreateVertexArrayID();
public:
	void SetPosition(float x, float y);
	void SetPosition(Vector2 vec);
	void Translate(float x, float y);
	void Translate(Vector2 vec);
	void Rotate(float angle);
	void Scale(float x, float y);
	void Scale(Vector2 vec);
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;
	void SetPositionVertex(float *_vertex, size_t dataSize, size_t vertexCount);
	void SetIndex(unsigned int *_index, size_t indexSize);
	void SetColorVertex(float *_colorVertex, size_t dataSize);
	void Destroy() override;
	void SetModulate(Color _new_modulate);
	Color GetModulate() const;
	Transform *GetTransform();
	Entity2D(Renderer* _renderer);
	~Entity2D();
};

