#pragma once
#include "Entity.h"
#include "Transform.h"
#include "Material.h"

class ENGINEDLL_API Entity3D :
    public Entity {
protected:
	Transform* transform;
public:
	void SetPosition(Vector3 position);
	void Translate(Vector3 position);
	void Rotate(Vector3  rotation);
	void Rotate(float angle, Vector3 axis);
	void SetScale(Vector3 scale);
	Vector3 GetPosition() const;
	Vector3 GetRotation() const;
	Vector3 GetScale() const;
	void Destroy() override;
	Transform* GetTransform();
	Entity3D();
	~Entity3D();
};