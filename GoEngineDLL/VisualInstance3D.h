#pragma once
#include "Entity3D.h"

class Gizmo3D;

class ENGINEDLL_API VisualInstance3D :
	public Entity3D {
private:
	Gizmo3D* gizmo;
protected:
	void DrawGizmo();
	void UpdateGizmo();
public:
	void SetPosition(Vector3 position);
	void Translate(Vector3 position);
	void Rotate(Vector3  rotation);
	void Rotate(float angle, Vector3 axis);
	void SetScale(Vector3 scale);
	void Destroy() override;
	void Draw() override;
	VisualInstance3D();
};

