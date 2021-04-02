#pragma once

#include "Exports.h"
#include "Utils.h"
#include "Transform.h"
#include "Renderer.h"
#include "Material.h"

class ENGINEDLL_API Entity{
protected:
	Transform *transform;
	Renderer *renderer;

	unsigned int vertexArrayID;
	vector<Renderer::VertexData> vectorVertexData;
	Renderer::Primitive primitive;
	void CreateVertexArrayID();
	unsigned int GetVertexArrayID() const;
	vector<Renderer::VertexData> GetVectorVertexData() const;
	void CreateVertexData(float* _vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID);
	void CreateVertexData(unsigned int* _vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID);
	void UpdateVertexData(float* _vertex, size_t dataSize, size_t attributeID);
	void BindVertexObjects();
public:
	string name;
	virtual void Draw() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy() {};
	Entity(Renderer *_renderer);
	~Entity();
};
