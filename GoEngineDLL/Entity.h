#include "Exports.h"
#include "Renderer.h"
#include "Transform.h"
#include "Input.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer *renderer;
	Input *input;
public:
	string name;
	virtual void Draw() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Destroy() = 0;
	void SetInput(Input *_input);
	Entity(Renderer *_renderer);
	~Entity();
};
