#include "Line3D.h"

void Line3D::Draw(Transform* transform) {
	if (spatialMaterial) {
		spatialMaterial->Use();
		spatialMaterial->GetShader()->SetVec4("lineColor", Rect2(lineColor.r, lineColor.g, lineColor.b, lineColor.a));
		spatialMaterial->GetShader()->SetMat4("model", transform->GetTransform());
	}
	Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, 2, false);
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
	BindVertexArray();
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0);
	BindVertexObjects();
	primitive = Renderer::LINES;
}

void Line3D::SetLine(Vector3 _startPoint, Vector3 _endPoint) {
	startPoint = _startPoint;
	endPoint = _endPoint;
	float position_vertex_data[] = {
		startPoint.x, startPoint.y, startPoint.z,
		endPoint.x, endPoint.y, endPoint.z,
	};
	UpdateVertexData(position_vertex_data, sizeof(position_vertex_data), 0);
}

void Line3D::SetLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor) {
	SetLine(_startPoint, _endPoint);
	lineColor = _lineColor;
}

Line3D::Line3D(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor) : Line3D(){
	CreateLine(_startPoint, _endPoint, _lineColor);
}

Line3D::Line3D() {
	SetDefaultName("Line3D");
	spatialMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/Line3D.fs", "lineMaterial");
}