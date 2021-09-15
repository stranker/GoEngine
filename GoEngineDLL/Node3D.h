#pragma once
#include "CanvasNode.h"
#include "Transform.h"
#include "Material.h"
#include "BSP.h"

class Line3D;

class ENGINEDLL_API Gizmo3D :
	public CanvasNode {
private:
	Material* lineMaterial;
	vector<Line3D*> lines;
public:
	void Draw(const Transform& transform);
	virtual void Destroy() override;
	Gizmo3D();
};

class ENGINEDLL_API Node3D :
    public CanvasNode {
protected:
	Gizmo3D* gizmo;
	Transform* transform;
	Transform* globalTransform;
	BoundingBox boundingBox;
	BoundingBox globalBoundingBox;
	bool bspEnabled = true;
	virtual void OnTransformUpdate() {};
public:
	virtual void AddChildren(Node* node) override;
	virtual void ShowUI() override;
	virtual void HideUI() override;
	void UpdateChildrensTransform();
	void UpdateGlobalBBoxChildren();
	void SetPosition(Vector3 position);
	void Translate(Vector3 position);
	void Rotate(float angle, Vector3 axis);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void SetScale(Vector3 scale);
	void SetEulerAngles(Vector3 eulerAngles);
	void LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _target);
	void SetGizmoVisible(bool gizmoVisible);
	BoundingBox GetBBox() const;
	BoundingBox GetGlobalBBox() const;
	void AddBBox(const BoundingBox& bbox);
	void AddGlobalBBox(const BoundingBox& bbox);
	void SetBBox(const BoundingBox& bbox);
	void SetGlobalBBox(const BoundingBox& bbox);
	void UpdateParentBBox();
	void UpdateGlobalBBox();
	virtual bool IsInsideFrustum() override;
	Vector3 GetScale() const;
	Vector3 GetPosition() const;
	Vector3 GetRotation() const;
	Transform* GetTransform();
	Transform* GetGlobalTransform();
	void SetBSPEnabled(bool value);
	bool IsBSPEnabled() const;
	void Draw() override;
	bool CanBeDrawed();
	Node3D();
	Node3D(const string& _name);
};

