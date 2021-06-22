#include "UILayer.h"
#include "Window.h"
#include "Node3D.h"

Node* UILayer::lastSelected;
Node* UILayer::currentSelected;

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
		}
		for (Node* child : node->GetChildrens()) {
			_TreeNode(child);
		}
		ImGui::TreePop();
	}
	else {
		if (isSelected) {
			currentSelected = node;
		}
	}
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
}

void UILayer::ShowTransform(Node3D* node) {
	Vector3 pos = node->GetPosition();
	Vector3 rot = node->GetRotation();
	Vector3 scl = node->GetScale();
	float newPos[3] = { pos.x, pos.y, pos.z };
	float newRot[3] = { rot.x, rot.y, rot.z };
	float newScl[3] = { scl.x, scl.y, scl.z };
	ImGui::Text("Transform");
	ImGui::InputFloat3("Position", newPos,"%.3f", ImGuiInputTextFlags_CharsDecimal);
	ImGui::InputFloat3("Rotation", newRot, "%.3f", ImGuiInputTextFlags_CharsDecimal);
	ImGui::InputFloat3("Scale", newScl,"%.3f", ImGuiInputTextFlags_CharsDecimal);
	node->SetPosition(Vector3(newPos[0], newPos[1], newPos[2]));
	node->SetEulerAngles(Vector3(newRot[0], newRot[1], newRot[2]));
	node->SetScale(Vector3(newScl[0], newScl[1], newScl[2]));
	ImGui::Separator();
}

void UILayer::ShowNodeInfo(Node* node) {
	ImGui::Begin("Properties");
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

void UILayer::Text(const string& text) {
	ImGui::Text(text.c_str());
}

void UILayer::Begin(const string& windowName, bool opened, size_t flags) {
	ImGui::Begin(windowName.c_str(), &opened, flags);
}

void UILayer::End() {
	ImGui::End();
}
