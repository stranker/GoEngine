#pragma once
#include "Exports.h"
#include "Utils.h"
#include "Renderer.h"

class ENGINEDLL_API Entity{
protected:
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
	string name;
public:
	virtual void Draw() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy() {cout << "Destroy Entity" << endl;};
	Entity();
	~Entity();
};
