#include "Exports.h"
#include "Renderer.h"
#include "Transform.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer *renderer;
public:
	string name;
	virtual void Draw() = 0;
	Entity(Renderer *renderer);
	~Entity();
};

