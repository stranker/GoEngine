#pragma once
#include "Exports.h"
#include "Utils.h"

class ENGINEDLL_API Resource  {
protected:
	unsigned int resourceID;
	string name;
	string path;
public:
	unsigned int GetID() const { return resourceID; };
	void SetName(string const& _name) { name = _name; };
	string GetName() const { return name; };
	string GetPath() const { return path; };
	Resource() {};
	virtual ~Resource() {};
};
