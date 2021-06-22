#include "Line3D.h"

void Line3D::Draw(const Transform& transform) {
	BindVertexArray();
	Renderer::GetSingleton()->SetEnableDepthBuffer(false);
	if (lineMaterial) {
		lineMaterial->Use();
		lineMaterial->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform));
		lineMaterial->SetVec4("lineColor", Rect2(lineColor.r, lineColor.g, lineColor.b, lineColor.a));
	}
	Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, 2, false);
	Renderer::GetSingleton()->SetEnableDepthBuffer(true);
}

void Line3D::CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor, Material* material) {
	startPoint = _startPoint;
	endPoint = _endPoint;
	lineColor = _lineColor;
	lineMaterial = material;
	float position_vertex_data[] = {
		startPoint.x, startPoint.y, startPoint.z,
		endPoint.x, endPoint.y, endPoint.z,
	};
	CreateVertexArrayID();
	BindVertexArray();
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0);
	BindVertexObjects();
	primitive = Renderer::LINES;
}

void Line3D::SetMaterial(Material* material) {
	lineMaterial = material;
}

Line3D::Line3D(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor, Material* material){
	CreateLine(_startPoint, _endPoint, _lineColor, material);
	SetDefaultName("Line3D");
}

Line3D::Line3D() {
}