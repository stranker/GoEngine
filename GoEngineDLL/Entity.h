#include "Exports.h"
#include "Renderer.h"
#include "Transform.h"

class ENGINEDLL_API Entity
{
protected:
	Transform *transform;
	Renderer *renderer;
public:
	string name;
	virtual void Draw() {};
	virtual void Update(float deltaTime) {};
	virtual void Destroy() {};
	Entity(Renderer *_renderer);
	~Entity();
	void Translate(float x, float y, float z);
};
