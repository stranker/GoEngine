#include "Line3D.h"

void Line3D::Draw() {
	BindVertexArray();
	Renderer::GetSingleton()->SetEnableDepthBuffer(false);
	if (lineMaterial){
		lineMaterial->Use();
		lineMaterial->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform->GetTransform()));
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
	transform->SetCanScale(canScale);
}

void Line3D::SetMaterial(Material* material) {
	lineMaterial = material;
}

Line3D::Line3D(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor, Material* material){
	CreateLine(_startPoint, _endPoint, _lineColor, material);
	canScale = false;
}

Line3D::Line3D() {
	canScale = false;
}

void Gizmo3D::Draw() {
	for (size_t i = 0; i < lines.size(); i++) {
		lines.at(i)->Draw();
	}
}

void Gizmo3D::Destroy() {
	if (lineMaterial) {
		lineMaterial->Destroy();
		delete lineMaterial;
	}
	if (!lines.empty()) {
		lines.clear();
	}
}

void Gizmo3D::UpdateGizmo(Transform* transform) {
	for (size_t i = 0; i < lines.size(); i++) {
		lines.at(i)->SetTransform(transform);
	}
}

Gizmo3D::Gizmo3D() {
	lineMaterial = new Material();
	lineMaterial->LoadShaders("Shaders/SimpleVertex3dShader.shader", "Shaders/LineFragmentShader.shader");
	Line3D* redLine = new Line3D(Vector3().Zero(), Vector3().Right() * 1.5f, Color().Red(), lineMaterial);
	Line3D* blueLine = new Line3D(Vector3().Zero(), Vector3().Foward() * 1.5f, Color().Blue(), lineMaterial);
	Line3D* greenLine = new Line3D(Vector3().Zero(), Vector3().Up() * 1.5f, Color().Green(), lineMaterial);
	lines.push_back(redLine);
	lines.push_back(blueLine);
	lines.push_back(greenLine);
}