#pragma once
#include "Entity.h"
#include "Material.h"

class ENGINEDLL_API Entity2D :
	public Entity{
protected:
	Material* material;
	Color selfModulate;
	float rotationDegrees;
	Transform* transform;
public:
	void SetPosition(float x, float y);
	void SetPosition(Vector2 vec);
	void Translate(float x, float y);
	void Translate(Vector2 vec);
	void Rotate(float angle);
	void Scale(float x, float y);
	void Scale(Vector2 vec);
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;
	virtual void Destroy() override;
	void SetModulate(Color _new_modulate);
	Color GetModulate() const;
	Transform *GetTransform();
	Entity2D();
	~Entity2D();
};

