#include "Entity.h"
#include "Renderer.h"
#include "Transform.h"

void Entity::CreateVertexArrayID() {
	vertexArrayID = renderer->CreateVertexArrayID();
}

unsigned int Entity::GetVertexArrayID() const {
	return vertexArrayID;
}

vector<Renderer::VertexData> Entity::GetVectorVertexData() const {
	return vectorVertexData;
}

void Entity::CreateVertexData(float* _vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID) {
	Renderer::VertexData vertexData;
	vertexData.dataCount = vertexCount;
	vertexData.vbo = renderer->CreateVertexBuffer(_vertex, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void Entity::CreateVertexData(unsigned int* _vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID) {
	Renderer::VertexData vertexData;
	vertexData.dataCount = vertexCount;
	vertexData.vbo = renderer->CreateVertexBuffer(_vertex, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void Entity::UpdateVertexData(float* _vertex, size_t dataSize, size_t attributeID) {
	// Posicion, Color, UV
	for (Renderer::VertexData vertexData : vectorVertexData) {
		if (vertexData.attributeID == attributeID) {
			renderer->BindVertexArray(vertexArrayID); // Bindeo el VAO
			vertexData.vbo = renderer->CreateVertexBuffer(_vertex, dataSize, vertexData.bufferType); // Update el VBO
			renderer->BindVertexData(vertexData); // Bindeo el VBO
			break;
		}
	}
}

void Entity::BindVertexObjects() {
	for (Renderer::VertexData vertexData : vectorVertexData) {
		renderer->BindVertexData(vertexData);
	}
}

Entity::Entity(Renderer *_renderer) : renderer(_renderer) {
	name = "Entity";
	transform = new Transform();
}

Entity::~Entity() {
}