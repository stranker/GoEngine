#include "Resource.h"

void Resource::SetDefaultName(const string& _name) {
	name = _name + to_string(resourceID);
}
