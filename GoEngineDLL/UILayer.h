#pragma once
#include "Utils.h"
#include "GlInclude.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Transform.h"
#include "Profiler.h"

class Window;
class Node;
class Node3D;
class Light;
class SpotLight;
class DirectionalLight;
class PointLight;
class Line3D;
class SpatialMaterial;

class ENGINEDLL_API UILayer {
private:
	static Node* lastSelected;
	static Node* currentSelected;
	static void _TreeNode(Node* node);
	static void DrawBBox(Node3D* node);
	static void DrawGizmo(Node3D* node);
	static void UpdateBBoxLines();
	static vector<Line3D*> boxLines;
	static vector<Line3D*> gizmoLines;
public:
	static Node* GetCurrentNodeSelected();
	static void CreateContext(Window* window);
	static void Destroy();
	static void NewFrame();
	static void Render();
	static void EndRender();
	static void TreeNode(Node* node);
	static void ShowNode3D(Node3D* node3d);
	static void ShowTransform(Node3D* node);
	static void ShowMaterial(SpatialMaterial* material);
	static void ShowNodeInfo(Node* node);
	static void ShowLightInfo(Light* light);
	static void ShowProfiler();
	static void ShowDebug();
	static void Text(const string& text);
	static void Begin(const string& windowName, bool opened, size_t flags);
	static void End();
};
