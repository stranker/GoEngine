#include "Entity.h"
#include "Renderer.h"

void Entity::CreateVertexArrayID() {
	vertexArrayID = Renderer::GetSingleton()->CreateVertexArrayID();
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
	vertexData.vbo = Renderer::GetSingleton()->CreateVertexBuffer(_vertex, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void Entity::CreateVertexData(unsigned int* _vertex, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID) {
	Renderer::VertexData vertexData;
	vertexData.dataCount = vertexCount;
	vertexData.vbo = Renderer::GetSingleton()->CreateVertexBuffer(_vertex, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void Entity::CreateVertexData(void* _vertexData, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID) {
	Renderer::VertexData vertexData;
	vertexData.dataCount = vertexCount;
	vertexData.vbo = Renderer::GetSingleton()->CreateVertexBuffer(_vertexData, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void Entity::UpdateVertexData(float* _vertex, size_t dataSize, size_t attributeID) {
	for (Renderer::VertexData vertexData : vectorVertexData) {
		if (vertexData.attributeID == attributeID) {
			Renderer::GetSingleton()->BindVertexArray(vertexArrayID);
			vertexData.vbo = Renderer::GetSingleton()->CreateVertexBuffer(_vertex, dataSize, vertexData.bufferType); // Update el VBO
			Renderer::GetSingleton()->BindVertexData(vertexData); // Bindeo el VBO
			break;
		}
	}
}

void Entity::BindVertexObjects() {
	for (size_t i = 0; i < vectorVertexData.size(); i++){
		Renderer::GetSingleton()->BindVertexData(vectorVertexData[i]);
	}
}

void Entity::BindVertexArray() {
	Renderer::GetSingleton()->BindVertexArray(vertexArrayID);
}

void Entity::SetVertexData(vector<Renderer::VertexData> vertexData) {
	vectorVertexData = vertexData;
}

Entity::Entity(){
	name = "Entity";
}

Entity::~Entity() {
}