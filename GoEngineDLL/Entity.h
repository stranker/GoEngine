#include "Renderer.h"

class Entity
{
protected:
	Renderer *renderer;
public:
	void SetRenderer(Renderer *_renderer);
	Entity();
	~Entity();

	virtual void Draw();
};

