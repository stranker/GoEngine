#pragma once
#include "Exports.h"
#include <iostream>
#include <unordered_map>

using namespace std;

enum ResourceType{
	RESOURCE_NULL = 0,
	RESOURCE_TEXTURE = 1
};

class ENGINEDLL_API Resource {
protected:
	unsigned int id;
	const char* resourcePath;
	ResourceType resourceType;
public:
	virtual void LoadResource() = 0;
	virtual void UnloadResource() = 0;

	void SetResourceID(unsigned int _id);
	unsigned int GetResourceID() const;

	Resource();
	virtual ~Resource();
};


class ENGINEDLL_API ResourceManager {
private:
	static ResourceManager* singleton;
	unordered_map<unsigned int, Resource*> resources;
public:
	void AddResource(Resource* resource, const char* path);
	ResourceManager* GetSingleton();
	ResourceManager();
	virtual ~ResourceManager();
};

