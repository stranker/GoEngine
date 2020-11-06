#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Entity2D :
	public Entity{
private:
	unsigned int vertexArrayID;
	vector<Renderer::VertexData> vectorVertexData;
protected:
	Renderer::Primitive primitive;
	Color selfModulate;
	float rotationDegrees;
	void CreateVertexArrayID();
	unsigned int GetVertexArrayID() const;
	vector<Renderer::VertexData> GetVectorVertexData() const;
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
	void CreateVertexData(float *_vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID);
	void CreateVertexData(unsigned int *_vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID);
	void UpdateVertexData(float *_vertex, size_t dataSize, size_t attributeID);
	void BindVertexObjects();
	void Destroy() override;
	void SetModulate(Color _new_modulate);
	Color GetModulate() const;
	Transform *GetTransform();
	Entity2D(Renderer* _renderer);
	~Entity2D();
};

