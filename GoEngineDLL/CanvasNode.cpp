#include "CanvasNode.h"

void CanvasNode::CreateVertexArrayID() {
	vertexArrayID = Renderer::GetSingleton()->CreateVertexArrayID();
}

unsigned int CanvasNode::GetVertexArrayID() const {
	return vertexArrayID;
}

vector<Renderer::VertexData> CanvasNode::GetVectorVertexData() const {
	return vectorVertexData;
}

bool CanvasNode::IsVisible() const {
	return visible;
}

void CanvasNode::SetVisible(bool isVisible) {
	if (isVisible == visible) { return; };
	if (isVisible) {
		Show();
	}
	else {
		Hide();
	}
}

void CanvasNode::Show() {
	visible = true;
}

void CanvasNode::Hide() {
	visible = false;
}

void CanvasNode::Draw() {
	if (!visible) { return; };
	Node::Draw();
}

void CanvasNode::ToggleRenderMode() {
	primitive = primitive == Renderer::TRIANGLES ? Renderer::LINE_STRIP : Renderer::TRIANGLES;
}

CanvasNode::CanvasNode() {
	className = "CanvasNode";
	SetDefaultName(className);
}

void CanvasNode::CreateVertexData(void* _vertexData, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID) {
	Renderer::VertexData vertexData;
	vertexData.dataCount = vertexCount;
	vertexData.vbo = Renderer::GetSingleton()->CreateVertexBuffer(_vertexData, dataSize, bufferType);
	vertexData.bufferType = bufferType;
	vertexData.attributeID = attributeID;
	vectorVertexData.push_back(vertexData);
}

void CanvasNode::UpdateVertexData(void* _vertex, size_t dataSize, size_t attributeID) {
	for (Renderer::VertexData vertexData : vectorVertexData) {
		if (vertexData.attributeID == attributeID) {
			Renderer::GetSingleton()->BindVertexArray(vertexArrayID);
			Renderer::GetSingleton()->UpdateVertexBuffer(vertexData.vbo, _vertex, dataSize, vertexData.bufferType);
			Renderer::GetSingleton()->BindVertexData(vertexData);
			break;
		}
	}
}

void CanvasNode::BindVertexObjects() {
	for (size_t i = 0; i < vectorVertexData.size(); i++) {
		Renderer::GetSingleton()->BindVertexData(vectorVertexData[i]);
	}
}

void CanvasNode::BindVertexArray() {
	Renderer::GetSingleton()->BindVertexArray(vertexArrayID);
}

void CanvasNode::SetVertexData(vector<Renderer::VertexData> vertexData) {
	vectorVertexData = vertexData;
}