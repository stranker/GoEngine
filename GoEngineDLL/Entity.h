#include "Exports.h"
#include "Renderer.h"
#include "Transform.h"
#include "Input.h"

class ENGINEDLL_API Entity
{
protected:
	Transform *transform;
	Renderer *renderer;
public:
	enum RotationAxis
	{
		X,
		Y,
		Z
	};
	string name;
	virtual void Draw() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy() {};
	Entity(Renderer *_renderer);
	~Entity();
	void Translate(float x, float y, float z);
	void Rotate(float angle, RotationAxis axis);
	void Scale(float x, float y, float z);
};
