#include "ResourceManager.h"

void Resource::SetResourceID(unsigned int _id) {
	id = _id;
}

unsigned int Resource::GetResourceID() const {
	return id;
}

Resource::Resource() {
}

Resource::~Resource() {
}

ResourceManager * ResourceManager::singleton = nullptr;

void ResourceManager::AddResource(Resource * resource, const char * path) {
}

ResourceManager * ResourceManager::GetSingleton() {
	return singleton;
}

ResourceManager::ResourceManager() {
	singleton = this;
}

ResourceManager::~ResourceManager() {
	singleton = nullptr;
}
