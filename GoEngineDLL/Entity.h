#include "Renderer.h"
#include "Transform.h"

class Entity
{
protected:
	Renderer *renderer;
public:
	Entity(Renderer* _renderer);
	~Entity();
	virtual void Draw();
};

