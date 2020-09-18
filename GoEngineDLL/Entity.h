#include "Renderer.h"
#include "Transform.h"

class Entity
{
protected:
	Renderer *renderer;
public:
	string name;
	virtual void Draw() = 0;
	Entity(Renderer *renderer);
	~Entity();
};

