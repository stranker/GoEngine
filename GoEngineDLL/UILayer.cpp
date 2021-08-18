#include "UILayer.h"
#include "Window.h"
#include "Node3D.h"
#include "Light.h"
#include "Line3D.h"

Node* UILayer::lastSelected;
Node* UILayer::currentSelected;
vector<Line3D*> UILayer::boxLines;

void UILayer::TreeNode(Node* node) {
	_TreeNode(node);
	if (currentSelected) {
		currentSelected->ShowUI();
		End();
	}
	if (lastSelected) {
		if (lastSelected != currentSelected){
			lastSelected->HideUI();
			lastSelected = currentSelected;
		}
	}
}

void UILayer::_TreeNode(Node* node) {
	if (node->IsUILocked()) { return; }
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (node == currentSelected) {
		flags |= ImGuiTreeNodeFlags_Selected;
	}
	if (node->GetChildrens().empty()) {
		flags |= ImGuiTreeNodeFlags_Leaf;
	}
	bool isOpened = ImGui::TreeNodeEx(node->GetName().c_str(), flags);
	bool isSelected = ImGui::IsItemClicked();
	if (isOpened) {
		if (isSelected) {
			if (!lastSelected) {
				lastSelected = node;
			}
			else {
				lastSelected = currentSelected;
			}
			currentSelected = node;
			UpdateBBoxLines();
		}
		for (Node* child : node->GetChildrens()) {
			_TreeNode(child);
		}
		ImGui::TreePop();
	}
	else {
		if (isSelected) {
			currentSelected = node;
			UpdateBBoxLines();
		}
	}
}

void UILayer::DrawBBox(Node3D* node) {
	if (Renderer::GetSingleton()->GetBBoxDrawDebug()) {
		UpdateBBoxLines();
		for (size_t i = 0; i < 12; i++) {
			boxLines[i]->Draw(*node->GetGlobalTransform());
		}
	}
}

void UILayer::UpdateBBoxLines() {
	if (currentSelected->GetClass() == "Node") return;
	Vector3 minVtx = ((Node3D*)currentSelected)->GetBBox().min;
	Vector3 maxVtx = ((Node3D*)currentSelected)->GetBBox().max;
	boxLines[0]->SetLine(Vector3(minVtx.x, minVtx.y, minVtx.z), Vector3(maxVtx.x, minVtx.y, minVtx.z));
	boxLines[1]->SetLine(Vector3(minVtx.x, minVtx.y, minVtx.z), Vector3(minVtx.x, maxVtx.y, minVtx.z));
	boxLines[2]->SetLine(Vector3(minVtx.x, minVtx.y, minVtx.z), Vector3(minVtx.x, minVtx.y, maxVtx.z));

	boxLines[3]->SetLine(Vector3(maxVtx.x, maxVtx.y, minVtx.z), Vector3(maxVtx.x, minVtx.y, minVtx.z));
	boxLines[4]->SetLine(Vector3(maxVtx.x, maxVtx.y, minVtx.z), Vector3(minVtx.x, maxVtx.y, minVtx.z));
	boxLines[5]->SetLine(Vector3(maxVtx.x, maxVtx.y, minVtx.z), Vector3(maxVtx.x, maxVtx.y, maxVtx.z));

	boxLines[6]->SetLine(Vector3(minVtx.x, maxVtx.y, maxVtx.z), Vector3(minVtx.x, maxVtx.y, minVtx.z));
	boxLines[7]->SetLine(Vector3(minVtx.x, maxVtx.y, maxVtx.z), Vector3(maxVtx.x, maxVtx.y, maxVtx.z));
	boxLines[8]->SetLine(Vector3(minVtx.x, maxVtx.y, maxVtx.z), Vector3(minVtx.x, minVtx.y, maxVtx.z));

	boxLines[9]->SetLine(Vector3(maxVtx.x, minVtx.y, maxVtx.z), Vector3(maxVtx.x, maxVtx.y, maxVtx.z));
	boxLines[10]->SetLine(Vector3(maxVtx.x, minVtx.y, maxVtx.z), Vector3(minVtx.x, minVtx.y, maxVtx.z));
	boxLines[11]->SetLine(Vector3(maxVtx.x, minVtx.y, maxVtx.z), Vector3(maxVtx.x, minVtx.y, minVtx.z));
}

Node* UILayer::GetCurrentNodeSelected() {
	return currentSelected;
}

void UILayer::CreateContext(Window* window) {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->GetWindowPtr(), true);
	ImGui_ImplOpenGL3_Init();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	for (size_t i = 0; i < 12; i++) {
		boxLines.push_back(new Line3D(Vector3().Zero(), Vector3().Zero(), Color().Cyan()));
	}
}

void UILayer::Destroy() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UILayer::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UILayer::Render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UILayer::ShowNode3D(Node3D* node3D) {
	ShowTransform(node3D);
	DrawBBox(node3D);
}

void UILayer::ShowTransform(Node3D* node) {
	bool visible = node->IsVisible();
	if (ImGui::Checkbox("Visible", &visible)) {
		node->SetVisible(visible);
	}
	Vector3 pos = node->GetPosition();
	Vector3 rot = node->GetRotation();
	Vector3 scl = node->GetScale();
	float newPos[3] = { pos.x, pos.y, pos.z };
	float newRot[3] = { rot.x, rot.y, rot.z };
	float newScl[3] = { scl.x, scl.y, scl.z };
	ImGui::Text("Transform");
	if (ImGui::InputFloat3("Position", newPos, "%.3f", ImGuiInputTextFlags_CharsDecimal || ImGuiInputTextFlags_EnterReturnsTrue)) {
		node->SetPosition(Vector3(newPos[0], newPos[1], newPos[2]));
	}
	if (ImGui::InputFloat3("Rotation", newRot, "%.3f", ImGuiInputTextFlags_CharsDecimal || ImGuiInputTextFlags_EnterReturnsTrue)) {
		node->SetEulerAngles(Vector3(newRot[0], newRot[1], newRot[2]));
	}
	if (ImGui::InputFloat3("Scale", newScl, "%.3f", ImGuiInputTextFlags_CharsDecimal || ImGuiInputTextFlags_EnterReturnsTrue)) {
		node->SetScale(Vector3(newScl[0], newScl[1], newScl[2]));
	}
	ImGui::Separator();
	/*ImGui::Text("Global Transform");
	Vector3 gPos = node->GetGlobalTransform()->GetPosition();
	Vector3 gRot = node->GetGlobalTransform()->GetRotation();
	Vector3 gScl = node->GetGlobalTransform()->GetScale();
	float newGPos[3] = { gPos.x, gPos.y, gPos.z };
	float newGRot[3] = { gRot.x, gRot.y, gRot.z };
	float newGScl[3] = { gScl.x, gScl.y, gScl.z };
	ImGui::InputFloat3("GPosition", newGPos, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat3("GRotation", newGRot, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat3("GScale", newGScl, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::Separator();*/
	/*
	ImGui::Text("Local AABB");
	Vector3 minAABB = node->GetBBox().min;
	Vector3 maxAABB = node->GetBBox().max;
	float min[3] = { minAABB.x,minAABB.y,minAABB.z };
	float max[3] = { maxAABB.x,maxAABB.y,maxAABB.z };
	ImGui::InputFloat3("Min", min, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat3("Max", max, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::Text("Global AABB");
	Vector3 minGlobalAABB = node->GetGlobalBBox().min;
	Vector3 maxGlobalAABB = node->GetGlobalBBox().max;
	float minG[3] = { minGlobalAABB.x,minGlobalAABB.y,minGlobalAABB.z };
	float maxG[3] = { maxGlobalAABB.x,maxGlobalAABB.y,maxGlobalAABB.z };
	ImGui::InputFloat3("Min", minG, "%.3f", ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat3("Max", maxG, "%.3f", ImGuiInputTextFlags_ReadOnly);*/
	if (ImGui::Button("Toggle Render mode")) {
		node->ToogleRenderMode();
	}
	ImGui::Separator();
}

void UILayer::ShowNodeInfo(Node* node) {
	ImGui::Begin("Properties",0 , ImGuiWindowFlags_NoCollapse);
	ImGui::Separator();
	ImGui::Text(string("Type:" + node->GetClass()).c_str());
	static char buf[254];
	memcpy(buf, (void*)&node->GetName()[0], node->GetName().size());
	if (ImGui::InputText("Name", buf, 254, ImGuiInputTextFlags_EnterReturnsTrue)) {
		node->SetName(string(buf));
	}
	memset(buf, 0, 254);
	ImGui::Separator();
}

void UILayer::ShowLightInfo(Light* light) {
	ImGui::Text("Light");
	Color lColor = Color(light->GetLightColor());
	float newColor[3] = { lColor.r, lColor.g, lColor.b };
	float specular = light->GetSpecular();
	float energy = light->GetEnergy();
	ImGui::ColorEdit3("Color", newColor, ImGuiColorEditFlags_NoAlpha);
	ImGui::SliderFloat("Energy", &energy, 1, 16);
	ImGui::SliderFloat("Specular", &specular, 0, 1);
	light->SetLightColor(Vector3(newColor[0], newColor[1], newColor[2]));
	light->SetEnergy(energy);
	light->SetSpecular(specular);
	if (light->GetType() == Renderer::LightType::SPOT) {
		float cutOff = ((SpotLight*)light)->GetCutOff();
		float outerCutOff = ((SpotLight*)light)->GetOuterCutOff();
		float range = ((SpotLight*)light)->GetRange();
		ImGui::SliderFloat("CutOff", &cutOff, 0, outerCutOff);
		ImGui::SliderFloat("Outer CutOff", &outerCutOff, cutOff, 100);
		ImGui::SliderFloat("Range", &range, 0, 256);
		((SpotLight*)light)->SetCutOff(cutOff);
		((SpotLight*)light)->SetOuterCutOff(outerCutOff);
		((SpotLight*)light)->SetRange(range);
	}
	ImGui::Separator();
}

void UILayer::ShowProfiler() {
	ImGui::Begin("Profiler");
	ImGui::Text(string("Objects Drawing:" + to_string(Profiler::objectsDrawing)).c_str());
	ImGui::Text(string("Total objects:" + to_string(Profiler::totalObjects)).c_str());

	ImGui::End();
}

void UILayer::ShowDebug() {
	ImGui::Separator();
	ImGui::Begin("Debug");
	if (ImGui::Button("Toggle Draw AABB")) {
		Renderer::GetSingleton()->EnableBBoxDrawDebug(!Renderer::GetSingleton()->GetBBoxDrawDebug());
	}
	ImGui::Separator();
	ImGui::Text(string("Objects Drawing:" + to_string(Profiler::objectsDrawing)).c_str());
	ImGui::Separator();
	ImGui::Text(string("Total objects:" + to_string(Profiler::totalObjects)).c_str());
	ImGui::Separator();
	ImGui::Text("Drawing node names:");
	if (!Profiler::nodesDrawing.empty()) {
		for (size_t i = 0; i < Profiler::nodesDrawing.size(); i++) {
			ImGui::Text(Profiler::nodesDrawing[i].c_str());
		}
	}
	ImGui::End();
}

void UILayer::Text(const string& text) {
	ImGui::Text(text.c_str());
}

void UILayer::Begin(const string& windowName, bool opened, size_t flags) {
	ImGui::Begin(windowName.c_str(), &opened, flags);
}

void UILayer::End() {
	ImGui::End();
}
