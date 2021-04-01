#include "Line3D.h"

void Line3D::Draw() {
	if (material){
		material->Use();
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
		material->SetVec4("lineColor", Rect2(lineColor.r, lineColor.g, lineColor.b, lineColor.a));
	}
	renderer->Draw(GetVertexArrayID(), primitive, 2, false);
}

void Line3D::CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor) {
	startPoint = _startPoint;
	endPoint = _endPoint;
	lineColor = _lineColor;
	float position_vertex_data[] = {
		startPoint.x, startPoint.y, startPoint.z,
		endPoint.x, endPoint.y, endPoint.z,
	};
	CreateVertexArrayID();
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0);
	BindVertexObjects();
	primitive = Renderer::LINES;
	material = new Material();
	material->LoadShaders("Shaders/SimpleVertex3dShader.shader", "Shaders/LineFragmentShader.shader");
}

Line3D::Line3D(Renderer* _renderer) : Entity3D(_renderer){
}

Line3D::~Line3D() {
}
