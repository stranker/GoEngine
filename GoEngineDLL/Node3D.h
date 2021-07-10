#pragma once
#include "CanvasNode.h"
#include "Transform.h"
#include "Material.h"

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
	vector<Line3D*> boxLines;
	virtual void OnTransformUpdate() {};
	bool dirtyBBox = false;
private:
	void UpdateBoxLines();
public:
	void AddBBox(const BoundingBox& bbox);
	void AddGlobalBBox(const BoundingBox& bbox);
	void SetBBox(const BoundingBox& bbox);
	virtual void AddChildren(Node* node) override;
	virtual void ShowUI() override;
	virtual void HideUI() override;
	void UpdateChildrensTransform();
	void UpdateParentBBox();
	void UpdateGlobalBBox();
	void UpdateGlobalBBoxChildren();
	void UpdateBBox();
	void SetPosition(Vector3 position);
	void Translate(Vector3 position);
	BoundingBox GetBBox() const;
	BoundingBox GetGlobalBBox() const;
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
	virtual bool IsInsideFrustum() override;
	Vector3 GetScale() const;
	Vector3 GetPosition() const;
	Vector3 GetRotation() const;
	Transform* GetTransform();
	Transform* GetGlobalTransform();
	void Draw() override;
	Node3D();
	Node3D(const string& _name);
};

