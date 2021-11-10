#pragma once
#include "Node.h"
#include "Material.h"
#include "Renderer.h"

class ENGINEDLL_API CanvasNode : public Node {
private:
	bool visible = true;
	unsigned int vertexArrayID = 0;
	vector<Renderer::VertexData> vectorVertexData;
protected:
	void CreateVertexArrayID();
	unsigned int GetVertexArrayID() const;
	Renderer::Primitive primitive;
	void CreateVertexData(void* _vertexData, size_t dataSize, size_t vertexCount, Renderer::BufferType bufferType, size_t attributeID);
	void UpdateVertexData(void* _vertex, size_t dataSize, size_t attributeID);
	void BindVertexObjects();
	void BindVertexArray();
	void SetVertexData(vector<Renderer::VertexData> vertexData);
	bool canScale = true;
public:
	vector<Renderer::VertexData> GetVectorVertexData() const;
	bool IsVisible() const;
	void SetVisible(bool isVisible);
	virtual bool IsInsideFrustum() { return false; };
	void Show();
	void Hide();
	void Draw() override;
	void ToggleRenderMode();
	CanvasNode();
};

