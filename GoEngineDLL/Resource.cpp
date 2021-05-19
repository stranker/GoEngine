#include "Resource.h"

unsigned int Resource::GetID() const {
    return resourceID;
}

string const& Resource::GetName() {
    return name;
}