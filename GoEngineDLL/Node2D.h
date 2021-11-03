#ifndef ENGINE_3D
#pragma once
#include "CanvasNode.h"
#include "Transform.h"
#include "Material.h"

class ENGINEDLL_API Node2D :
	public CanvasNode {
protected:
	Material* material;
	Color selfModulate;
	float rotationDegrees;
	Transform* transform;
public:
	void SetPosition(Vector2 vec);
	void Translate(Vector2 vec);
	void Rotate(float angle);
	void Scale(Vector2 vec);
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;
	void SetModulate(Color _new_modulate);
	Color GetModulate() const;
	Transform* GetTransform();
	Node2D();
};
#endif // !ENGINE_3D


